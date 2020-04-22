/*
 * TRexTrapezoid.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoid.hh"


TRexTrapezoid::TRexTrapezoid() {
}

TRexTrapezoid::TRexTrapezoid(std::string name, std::string direction, int nbOfTelescopes) {
	fName = name;
	fDirection = direction;
	fNbOfTelescopes = nbOfTelescopes;

	fTrapezoidDeltaE = new TRexTrapezoidDeltaE(fName + "DeltaE", fDirection, fNbOfTelescopes);
	fTrapezoidErest = new TRexTrapezoidErest(fName + "Erest", fDirection, fNbOfTelescopes);
}

TRexTrapezoid::~TRexTrapezoid() {
	// TODO Auto-generated destructor stub
}

void TRexTrapezoid::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	fTrapezoidDeltaE->Construct(experimentalHall_log, SDMan);
	fTrapezoidErest->Construct(experimentalHall_log, SDMan);
}

std::vector<ParticleMC>* TRexTrapezoid::GetParticleMCvector() {
	return CombineDeltaEErestData(fTrapezoidDeltaE, fTrapezoidErest);
}
