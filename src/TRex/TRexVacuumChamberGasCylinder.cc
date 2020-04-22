/*
 * TRexVacuumChamberGasCylinder.cc
 *
 *  Created on: Jan 31, 2017
 *      Author: vbildste
 */

#include "TRex/TRexVacuumChamberGasCylinder.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexVacuumChamberGasCylinder::TRexVacuumChamberGasCylinder() {
}

TRexVacuumChamberGasCylinder::~TRexVacuumChamberGasCylinder() {
	// TODO Auto-generated destructor stub
}

G4LogicalVolume* TRexVacuumChamberGasCylinder::ConstructChamberGas(G4LogicalVolume* experimentalHall_log) {
	G4Material* chamberGasMaterial = TRexMaterials::Get()->GetMaterial("chamberGas");

	G4Tubs *chamberGas_tubs;
	G4Cons *chamberGas_cons1;
	G4Cons *chamberGas_cons2;

	if(TRexSettings::Get()->VisualizationCut()) {
		chamberGas_tubs = new G4Tubs("ChamberTubs",0.*mm,70.*mm,112.*mm,270.*degree,180.*degree);
		chamberGas_cons1 = new G4Cons("ChamberCons1",0.*mm,59.*mm,0.*mm,70.*mm,10.*mm,270.*degree,180.*degree);
		chamberGas_cons2 = new G4Cons("ChamberCons2",0.*mm,12.5*mm,0.*mm,59.*mm,9.5*mm,270.*degree,180.*degree);
	} else {
		chamberGas_tubs = new G4Tubs("ChamberTubs",0.*mm,70.*mm,112.*mm,0.*degree,360.*degree);
		chamberGas_cons1 = new G4Cons("ChamberCons1",0.*mm,59.*mm,0.*mm,70.*mm,10.*mm,0.*degree,360.*degree);
		chamberGas_cons2 = new G4Cons("ChamberCons2",0.*mm,12.5*mm,0.*mm,59.*mm,9.5*mm,0.*degree,360.*degree);
	}

	G4UnionSolid* chamberGas_cons = new G4UnionSolid("chambergas_cons", chamberGas_cons1, chamberGas_cons2, new G4RotationMatrix(),G4ThreeVector(0,0,-19.5*mm));

	G4UnionSolid* chamberGas_solid = new G4UnionSolid("chambergas_solid", chamberGas_tubs, chamberGas_cons, new G4RotationMatrix(),G4ThreeVector(0,0,-122.05*mm));

	// logical volume
	G4LogicalVolume* chamberGas_log = new G4LogicalVolume(chamberGas_solid, chamberGasMaterial, "chambergas_log");

	// physical volume
	new G4PVPlacement(0, G4ThreeVector(0,0,0), chamberGas_log, "chamber_gas", experimentalHall_log, false, 0);

	return chamberGas_log;
}
