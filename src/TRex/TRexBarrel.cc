/*
 * TRexBarrel.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrel.hh"


TRexBarrel::TRexBarrel() {
}

TRexBarrel::TRexBarrel(std::string name, std::string direction, int nbOfTelescopes) {
	fName = name;
	fDirection = direction;
	fNbOfTelescopes = nbOfTelescopes;

	fBarrelDeltaE = new TRexBarrelDeltaE(fName + "DeltaE", fDirection, fNbOfTelescopes);
	fBarrelErest = new TRexBarrelErest(fName + "Erest", fDirection, fNbOfTelescopes);
}

TRexBarrel::~TRexBarrel() {
	// TODO Auto-generated destructor stub
}

void TRexBarrel::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	fBarrelDeltaE->Construct(experimentalHall_log, SDMan);
	fBarrelErest->Construct(experimentalHall_log, SDMan);
}

std::vector<ParticleMC>* TRexBarrel::GetParticleMCvector() {
	return CombineDeltaEErestData(fBarrelDeltaE, fBarrelErest);
}
