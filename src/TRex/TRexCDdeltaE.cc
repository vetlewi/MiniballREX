/*
 * TRexCDdeltaE.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCDdeltaE.hh"

TRexCDdeltaE::TRexCDdeltaE() {
}

TRexCDdeltaE::TRexCDdeltaE(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fCDdeltaESingles.push_back(new TRexCDdeltaESingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexCDdeltaE::~TRexCDdeltaE() {
	// TODO Auto-generated destructor stub
}

void TRexCDdeltaE::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all FCDErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fCDdeltaESingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexCDdeltaE::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		if(fCDdeltaESingles[i]->GetParticleMC()->GetRingNr().size() > 0 || fCDdeltaESingles[i]->GetParticleMC()->GetStripNr().size() > 0) {
			particleMCvector->push_back(*fCDdeltaESingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
