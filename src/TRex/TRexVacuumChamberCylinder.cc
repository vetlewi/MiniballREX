/*
 * TRexVacuumChamberCylinder.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexVacuumChamberCylinder.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexVacuumChamberCylinder::TRexVacuumChamberCylinder() {
}

TRexVacuumChamberCylinder::~TRexVacuumChamberCylinder() {
	// TODO Auto-generated destructor stub
}

void TRexVacuumChamberCylinder::ConstructChamber(G4LogicalVolume* experimentalHall_log) {
	G4Material* chamberMaterial = TRexMaterials::Get()->GetMaterial("aluminium");

	G4Tubs *chamber_tubs;
	//G4Tubs *chamber_tubs1;
	//G4Tubs *chamber_tubs2;
	//G4Tubs *chamber_tubs3;
	G4Cons *chamber_cons1;
	G4Cons *chamber_cons2;

	if(TRexSettings::Get()->VisualizationCut()) {
		//chamber_tubs = new G4Tubs("ChamberTubs",70.*mm,72.*mm,62.*mm,270.*degree,360.*degree);
		chamber_tubs = new G4Tubs("ChamberTubs",70.*mm,72.*mm,112.*mm,270.*degree,180.*degree);
		//chamber_tubs1 = new G4Tubs("ChamberTubs1",70.*mm,72.*mm,34.*mm,270.*degree,180.*degree);
		//chamber_tubs2 = new G4Tubs("ChamberTubs2",70.*mm,90.*mm,62.5*mm,270.*degree,180.*degree);
		//chamber_tubs3 = new G4Tubs("ChamberTubs3",51.*mm,54.*mm,41.5*mm,270.*degree,180.*degree);
		chamber_cons1 = new G4Cons("ChamberCons1",59.*mm,61.*mm,70.*mm,72.*mm,10.*mm,270.*degree,180.*degree);
		chamber_cons2 = new G4Cons("ChamberCons2",12.5*mm,14.5*mm,59.*mm,61.*mm,9.5*mm,270.*degree,180.*degree);
	} else {
		//chamber_tubs = new G4Tubs("ChamberTubs",70.*mm,72.*mm,62.*mm,0.*degree,360.*degree);
		chamber_tubs = new G4Tubs("ChamberTubs",70.*mm,72.*mm,112.*mm,0.*degree,360.*degree);
		//chamber_tubs1 = new G4Tubs("ChamberTubs1",70.*mm,72.*mm,34.*mm,0.*degree,360.*degree);
		//chamber_tubs2 = new G4Tubs("ChamberTubs2",70.*mm,90.*mm,62.5*mm,0.*degree,360.*degree);
		//chamber_tubs3 = new G4Tubs("ChamberTubs3",51.*mm,54.*mm,41.5*mm,0.*degree,360.*degree);
		chamber_cons1 = new G4Cons("ChamberCons1",59.*mm,61.*mm,70.*mm,72.*mm,10.*mm,0.*degree,360.*degree);
		chamber_cons2 = new G4Cons("ChamberCons2",12.5*mm,14.5*mm,59.*mm,61.*mm,9.5*mm,0.*degree,360.*degree);
	}

	G4UnionSolid* chamber_cons = new G4UnionSolid("chamber_cons", chamber_cons1, chamber_cons2, new G4RotationMatrix(),G4ThreeVector(0,0,-19.5*mm));

	//G4UnionSolid* chamber_solid = new G4UnionSolid("chamber_solid", chamber_tubs, chamber_cons, new G4RotationMatrix(),G4ThreeVector(0,0,-72.05*mm));
	G4UnionSolid* chamber_solid = new G4UnionSolid("chamber_solid", chamber_tubs, chamber_cons, new G4RotationMatrix(),G4ThreeVector(0,0,-122.05*mm));

	// logical volume
	G4LogicalVolume* chamber_log = new G4LogicalVolume(chamber_solid, chamberMaterial, "chamber_log");

	// physical volume
	new G4PVPlacement(0, G4ThreeVector(0,0,0), chamber_log, "chamber", experimentalHall_log, false, 0);

	// grey color
	//chamber_log->SetVisAttributes(new G4VisAttributes(true, G4Colour(0.7,0.7,0.7)));
	chamber_log->SetVisAttributes(TRexColour::Get()->gray);
	//chamber_log->SetVisAttributes(TRexColour::Get()->yellow);
}
