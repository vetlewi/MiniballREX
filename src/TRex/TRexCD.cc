/*
 * TRexCD.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCD.hh"


TRexCD::TRexCD() {
}

TRexCD::TRexCD(std::string name, std::string direction, int nbOfTelescopes) {
	fName = name;
	fDirection = direction;
	fNbOfTelescopes = nbOfTelescopes;

	fCDdeltaE = new TRexCDdeltaE(fName + "deltaE", fDirection, fNbOfTelescopes);
	fCDErest = new TRexCDErest(fName + "Erest", fDirection, fNbOfTelescopes);
}

TRexCD::~TRexCD() {
	// TODO Auto-generated destructor stub
}

void TRexCD::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	fCDdeltaE->Construct(experimentalHall_log, SDMan);
	fCDErest->Construct(experimentalHall_log, SDMan);
}

std::vector<ParticleMC>* TRexCD::GetParticleMCvector() {
	return CombineDeltaEErestData(fCDdeltaE, fCDErest);
}
