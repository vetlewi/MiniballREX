/*
 * TRexCDErest.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCDErest.hh"


TRexCDErest::TRexCDErest() {
}

TRexCDErest::TRexCDErest(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fCDErestSingles.push_back(new TRexCDErestSingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexCDErest::~TRexCDErest() {
	// TODO Auto-generated destructor stub
}

void TRexCDErest::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all CDErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fCDErestSingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexCDErest::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		if(fCDErestSingles[i]->GetParticleMC()->GetEdet() > 0.001) {
			particleMCvector->push_back(*fCDErestSingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
