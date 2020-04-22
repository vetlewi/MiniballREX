/*
 * TRexBarrelErest.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrelErest.hh"

#include <G4SystemOfUnits.hh>

TRexBarrelErest::TRexBarrelErest() {
}

TRexBarrelErest::TRexBarrelErest(std::string name, std::string direction, int nbOfSingles) {
	fName = name;
	fDirection = direction;
	fNbOfSingles = nbOfSingles;

	for(int i = 0; i < fNbOfSingles; i++) {
		fBarrelErestSingles.push_back(new TRexBarrelErestSingle(fName + Form("Single%d", i), direction, i));
	}
}

TRexBarrelErest::~TRexBarrelErest() {
	// TODO Auto-generated destructor stub
}

void TRexBarrelErest::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// loop over all BarrelErest single detectors
	for(int i = 0; i < fNbOfSingles; i++) {
		fBarrelErestSingles[i]->Construct(experimentalHall_log, SDMan);
	}
}

std::vector<ParticleMC>* TRexBarrelErest::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	for(int i = 0; i < fNbOfSingles; i++) {
		// include only detectors with a hit
		if(fBarrelErestSingles[i]->GetParticleMC()->GetEdet() > 0.001 * eV) {
			particleMCvector->push_back(*fBarrelErestSingles[i]->GetParticleMC());
		}
	}

	return particleMCvector;
}
