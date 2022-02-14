
#include "TRex/Germanium.hh"

#include "zstr.hpp"

#include "ThreadPool.h"
#include "jthread.hpp"

#include <concurrentqueue.h>
#include <blockingconcurrentqueue.h>
#include <indicators/dynamic_progress.hpp>
#include <indicators/progress_bar.hpp>

#include <TTree.h>
#include <TFile.h>
#include <TApplication.h>
#include <TROOT.h>

using pair_t = std::pair<double, double>;

std::vector<double> GetEnergies(){
    std::vector<double> energies;
    energies.push_back(100);
    for ( int en = 200 ; en <= 10000 ; en += 200 ){
        energies.push_back(en);
    }
    return energies;
}

/*int main()
{
    TFile infile("/Volumes/RootTrees/result/Eg_4000/Eg4000.root");
    TTree *trGen = (TTree*)infile.Get("treeGen");
    TTree *tr = (TTree*)infile.Get("treeDet");

    std::vector<Germanium> *mBall = {nullptr};

    tr->SetBranchAddress("Miniball", &mBall);


    double reactionEnergy;
    trGen->SetBranchAddress("reactionEnergy", &reactionEnergy);

}*/

void ReadFileToQueue(const char *file, moodycamel::BlockingConcurrentQueue<pair_t> &queue,
                     indicators::DynamicProgress<indicators::ProgressBar> &bars, int bnum)
{
    TFile *infile = TFile::Open(file);
    TTree *trGen = (TTree*)infile->Get("treeGen");
    TTree *tr = (TTree*)infile->Get("treeDet");

    std::vector<Germanium> *mBall = {nullptr};


    tr->SetBranchAddress("Miniball", &mBall);


    double reactionEnergy;
    trGen->SetBranchAddress("reactionEnergy", &reactionEnergy);

    bars[bnum].set_option(indicators::option::MaxProgress(tr->GetEntries() / 10000));

    for ( Long64_t i = 0 ; i < tr->GetEntries() ; ++i ){

        tr->GetEntry(i);
        trGen->GetEntry(i);

        if ( i % 10000 == 0 )
            bars[bnum].tick();

        // Loop over MB
        for ( auto cluster : *mBall ){

            auto cluID = cluster.GetCluID();

            if ( cluID < 6 )
                continue; // We do not check MB detectors

            double energy = 0;
            for ( auto crystal : cluster.GetCrystal() )
                energy += crystal.GetCore();
            queue.enqueue(pair_t(reactionEnergy*1.0e3, energy));
        }
    }
    bars[bnum].mark_as_completed();
}

int main()
{
    //TApplication a("a", 0, 0);
    ROOT::EnableThreadSafety();
    std::ofstream outfile("result.csv");
    outfile << "actual,measured\n";

    moodycamel::BlockingConcurrentQueue<pair_t> queue;

    std::jthread writer([&queue, &outfile](const std::stop_token &st)
                        {
                            pair_t entry;
                            while ( !st.stop_requested() ){
                                if ( queue.try_dequeue(entry) ){
                                    outfile << entry.first << "," << entry.second << '\n';
                                } else {
                                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                                }
                            }

                            while ( queue.try_dequeue(entry) ){
                                outfile << entry.first << "," << entry.second << '\n';
                            }

                        });

    auto energies = GetEnergies();

    /*indicators::ProgressBar progress{
            indicators::option::BarWidth(50),
            indicators::option::ShowElapsedTime{true},
            indicators::option::ShowRemainingTime{true},
            indicators::option::PrefixText{"Progress: "},
            indicators::option::MaxProgress{energies.size()}
    };*/


    indicators::DynamicProgress<indicators::ProgressBar> bars;//(progress);
    bars.set_option(indicators::option::HideBarWhenComplete{true});
    int i = 0;

    ThreadPool pool(std::thread::hardware_concurrency() );

    std::vector< std::future<double> > res(energies.size());
    for ( auto energy : energies ){
        res.push_back(pool.enqueue([&queue, &bars](double energy, int i) -> double {

            char fname[16384];
            indicators::ProgressBar bar{
                    indicators::option::BarWidth(50),
                    indicators::option::ShowElapsedTime{true},
                    indicators::option::ShowRemainingTime{true},
                    indicators::option::PrefixText{"Processing energy " + std::to_string(energy) + " "}};
            bars.push_back(bar);

            sprintf(fname, "/Volumes/RootTrees/result/Eg_%d/Eg%d.root", int(energy), int(energy));
            ReadFileToQueue(fname, queue, bars, i);

            return energy;
        }, energy, i++));
    }
    pool.wait();
    /*for ( auto &r : res ){
        r.wait();
        r.get();
    }*/

    writer.request_stop();

    if ( writer.joinable() )
        writer.join();

}