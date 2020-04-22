/*
 * TRexBarrelDeltaE.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrelDeltaE.hh"

TRexBarrelDeltaE::TRexBarrelDeltaE() {
}

TRexBarrelDeltaE::TRexBarrelDeltaE(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fBarrelDeltaESingles.push_back(new TRexBarrelDeltaESingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexBarrelDeltaE::~TRexBarrelDeltaE() {
	// TODO Auto-generated destructor stub
}

void TRexBarrelDeltaE::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all FCDErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fBarrelDeltaESingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexBarrelDeltaE::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		//if(fBarrelDeltaESingles[i]->GetParticleMC()->GetEdet() > 0.001) {
		if(fBarrelDeltaESingles[i]->GetParticleMC()->GetRingNr().size() > 0 || fBarrelDeltaESingles[i]->GetParticleMC()->GetStripNr().size() > 0) {
			particleMCvector->push_back(*fBarrelDeltaESingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
