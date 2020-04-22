/*
 * TRexVacuumChamberGasSphere.cc
 *
 *  Created on: Jan 31, 2017
 *      Author: vbildste
 */

#include "TRex/TRexVacuumChamberGasSphere.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexVacuumChamberGasSphere::TRexVacuumChamberGasSphere() {
}

TRexVacuumChamberGasSphere::~TRexVacuumChamberGasSphere() {
	// TODO Auto-generated destructor stub
}

G4LogicalVolume* TRexVacuumChamberGasSphere::ConstructChamberGas(G4LogicalVolume* experimentalHall_log) {
	G4Material* chamberGasMaterial = TRexMaterials::Get()->GetMaterial("chamberGas");

	// commented values: T-REX spherical vaccum chamber
	// current values: adapted to Coulex chamber
	G4double chamberInnerRadius = 81. * mm;// 98. * mm;

	//the sphere
	G4Sphere* chamberGas_sphere;

	if(TRexSettings::Get()->VisualizationCut()) {
		chamberGas_sphere = new G4Sphere("ChamberGasSphere", 0. , chamberInnerRadius ,
				270.*degree, 180.*degree, 0.*degree, 180.*degree);
	} else {
		chamberGas_sphere = new G4Sphere("ChamberGasSphere", 0., chamberInnerRadius,
				0.*degree, 360.*degree, 0.*degree, 180.*degree);
	}

	G4LogicalVolume* chamberGas_log = new G4LogicalVolume(chamberGas_sphere, chamberGasMaterial, "chamberGas_log");
	new G4PVPlacement(0, G4ThreeVector(0,0,0), chamberGas_log, "chamberGas", experimentalHall_log, false, 0);

	return chamberGas_log;
}
