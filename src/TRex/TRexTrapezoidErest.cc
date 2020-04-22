/*
 * TRexTrapezoidErest.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidErest.hh"

TRexTrapezoidErest::TRexTrapezoidErest() {
}

TRexTrapezoidErest::TRexTrapezoidErest(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fTrapezoidErestSingles.push_back(new TRexTrapezoidErestSingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexTrapezoidErest::~TRexTrapezoidErest() {
	// TODO Auto-generated destructor stub
}

void TRexTrapezoidErest::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all FCDErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fTrapezoidErestSingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexTrapezoidErest::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		if(fTrapezoidErestSingles[i]->GetParticleMC()->GetEdet() > 0.001) {
			particleMCvector->push_back(*fTrapezoidErestSingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
