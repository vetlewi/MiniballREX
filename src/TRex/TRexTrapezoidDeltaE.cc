/*
 * TRexTrapezoidDeltaE.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidDeltaE.hh"


TRexTrapezoidDeltaE::TRexTrapezoidDeltaE() {
}

TRexTrapezoidDeltaE::TRexTrapezoidDeltaE(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fTrapezoidDeltaESingles.push_back(new TRexTrapezoidDeltaESingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexTrapezoidDeltaE::~TRexTrapezoidDeltaE() {
	// TODO Auto-generated destructor stub
}

void TRexTrapezoidDeltaE::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all FCDErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fTrapezoidDeltaESingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexTrapezoidDeltaE::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		if(fTrapezoidDeltaESingles[i]->GetParticleMC()->GetRingNr().size() > 0 || fTrapezoidDeltaESingles[i]->GetParticleMC()->GetStripNr().size() > 0) {
			particleMCvector->push_back(*fTrapezoidDeltaESingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
