

#include <TChain.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>


#include "../include/TRex/Germanium.hh"

void AnalyseLaBr(std::string fname, TH1 *sim, TH1 *simfold)
{
	TChain chain("treeDet");
	chain.Add(fname.c_str());

	int n_miniball;
	int clu_id[3];

	std::vector<Crystal> crystal[3];

	std::vector<Germanium> miniball;

	chain.SetBranchAddress("Miniball", &miniball);
	//chain.SetBranchAddress("Miniball.fClusterID", clu_id);
	//chain.SetBranchAddress("Miniball.fCrystal", crystal);
	int found = 0;
	for ( int i =  0 ; i < chain.GetEntries() ; ++i ){
		chain.GetEvent(i);

		for ( int i = 0  ; i < miniball.size() ; ++i ){
			if ( miniball[i].GetCluID() > 6 ){
				std::cout << "Found detector: " << miniball[i].GetCluID() << std::endl;
				++found;
			}
		}
		if ( found == 100 )
			break;

	}

}