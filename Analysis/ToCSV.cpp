
#include "../include/TRex/Germanium.hh"

#include "zstr.hpp"

#include "ThreadPool.h"
#include "jthread.hpp"

#include "concurrentqueue.h"

#include <TTree.h>
#include <TFile.h>



struct Entry_t {
    uint64_t eventID;
    uint16_t cluID;
    uint16_t coreID;
    double energy;
};


std::ostream &operator<<(std::ostream &os, const Entry_t &entry)
{

    os << entry.eventID << "," << entry.cluID << "," << entry.coreID << "," << entry.energy;
    return os;
}

std::vector<double> GetEnergies(){
    std::vector<double> energies;
    energies.push_back(100);
    for ( int en = 200 ; en <= 10000 ; en += 200 ){
        energies.push_back(en);
    }
    return energies;
}

void ReadFileToQueue(const char *file, moodycamel::BlockingConcurrentQueue<Entry_t> &queue)
{
    TFile infile(file);
    TTree *trGen = (TTree*)infile.Get("treeGen");
    TTree *tr = (TTree*)infile.Get("treeDet");

    std::vector<Germanium> *mBall;


    tr->SetBranchAddress("Miniball", &mBall);


    double reactionEnergy;
    trGen->SetBranchAddress("reactionEnergy", &reactionEnergy);

    auto entries = tr->GetEntries();

    for ( Long64_t i = 0 ; i < tr->GetEntries() ; ++i ){

        tr->GetEntry(i);
        trGen->GetEntry(i);

        // Loop over MB
        for ( auto &cluster : *mBall ){
            auto cluID = cluster.GetCluID();
            for ( auto &crystal : cluster.GetCrystal() ){
                queue.enqueue(Entry_t(i, cluID, crystal.GetCryID, crystal.GetCore()));
            }
        }
    }
}

int main()
{
    std::ofstream outfile("result.csv");
    outfile << "cluster,crystal,measured\n";

    moodycamel::BlockingConcurrentQueue<Entry_t> queue;

    std::jthread writer([&queue, &outfile](const std::stop_token &st)
    {
        Entry_t entry;
        while ( !st.stop_requested() ){
            if ( !queue.wait_dequeue(entry, std::chrono::milliseconds(250)) )
                continue;
            outfile << entry << '\n';
        }

        while ( queue.try_dequeue(entry) ){
            outfile << entry << '\n';
        }

    });

    ThreadPool pool(std::thread::hardware_concurrency()-1);
    std::vector< std::future<double> > res;
    for ( auto &energy : GetEnergies() ){
        res.push_back(
        pool.enqueue([&queue](double energy) -> double {
            char fname[16384];
            sprintf(fname, "/Volumes/RootTrees/result/Eg_%d/Eg%d.root", energy, energy);
            ReadFileToQueue(fname, queue);
            return energy;
        }, energy));
    }

    for ( auto &r : res ){
        r.wait();
        std::cout << "Done processing energy: " << r.get() << std::endl;
    }

    //ReadFile("/Volumes/RootTrees/result/Eg_4000/Eg4000.root", outfile);
    writer.request_stop();
    
    if ( writer.joinable() )
        writer.join();

}