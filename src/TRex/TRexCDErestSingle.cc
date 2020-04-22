/*
 * TRexCDErestSingle.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCDErestSingle.hh"
#include "TRex/TRexCDErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexCDErestSingle::TRexCDErestSingle() {
}

TRexCDErestSingle::TRexCDErestSingle(std::string name, std::string direction, int id) {
	fName = name;
	fId = id;
	fDirection = direction;

	if(fDirection == "forward") {
		fInnerRadiusDetector = TRexSettings::Get()->GetFCDErestSingleInnerRadius();
		fOuterRadiusDetector = TRexSettings::Get()->GetFCDErestSingleOuterRadius();
		fThicknessDetector = TRexSettings::Get()->GetFCDErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetFCDErestSingleStartAngle()[fId];
		fSpanningAngleDetector = TRexSettings::Get()->GetFCDErestSingleSpanningAngle();
		fDeadLayer = TRexSettings::Get()->GetFCDErestSingleDeadLayer();

		fPos = G4ThreeVector(TRexSettings::Get()->GetFCDErestSinglePosX()[fId],
									TRexSettings::Get()->GetFCDErestSinglePosY()[fId],
									TRexSettings::Get()->GetFCDErestSinglePosZ()[fId] - fThicknessDetector / 2.);
	} else if(fDirection == "backward") {
		fInnerRadiusDetector = TRexSettings::Get()->GetBCDErestSingleInnerRadius();
		fOuterRadiusDetector = TRexSettings::Get()->GetBCDErestSingleOuterRadius();
		fThicknessDetector = TRexSettings::Get()->GetBCDErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetBCDErestSingleStartAngle()[fId];
		fSpanningAngleDetector = TRexSettings::Get()->GetBCDErestSingleSpanningAngle();
		fDeadLayer = TRexSettings::Get()->GetBCDErestSingleDeadLayer();

		fPos = G4ThreeVector(TRexSettings::Get()->GetBCDErestSinglePosX()[fId],
									TRexSettings::Get()->GetBCDErestSinglePosY()[fId],
									TRexSettings::Get()->GetBCDErestSinglePosZ()[fId] - fThicknessDetector / 2.);
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}
}

TRexCDErestSingle::~TRexCDErestSingle() {
	// TODO Auto-generated destructor stub
}

void TRexCDErestSingle::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
        // active detector
	ConstructSilicon(experimentalHall_log, SDMan);

	// PCB
	if(TRexSettings::Get()->ConstructPCB()) {
	  ConstructPCB(experimentalHall_log);
	}

	// include dead layers ?
	if(fDeadLayer > 0.1*um) {
		ConstructDeadLayer(experimentalHall_log);
	}
}

void TRexCDErestSingle::ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("silicon");

	fSolid = new G4Tubs("detector", fInnerRadiusDetector, fOuterRadiusDetector,
			fThicknessDetector / 2. - fDeadLayer, fStartAngleDetector, fSpanningAngleDetector);

	fLogicalVolume = new G4LogicalVolume(fSolid, detectorMaterial, fName + "_log", 0,0 ,0);

	//G4RotationMatrix* rotMatrix = new G4RotationMatrix;
	//rotMatrix->rotateX(90.*deg);
	//fPhysicalVolume = new G4PVPlacement(rotMatrix, fPos,
	//		fLogicalVolume, "detectorWithHole", experimentalHall_log, false, 0);

	fPhysicalVolume = new G4PVPlacement(0, fPos, fLogicalVolume, "detectorWithHole", experimentalHall_log, false, 0);

	// register sensitive detector
	SDMan = G4SDManager::GetSDMpointer();
	fCDErestSingleSensitiveDetector = new TRexCDErestSingleSensitiveDetector(G4String(fName), fDirection, fId);
	SDMan->AddNewDetector(fCDErestSingleSensitiveDetector);
	fLogicalVolume->SetSensitiveDetector(fCDErestSingleSensitiveDetector);

	if(TRexSettings::Get()->Colours()) {
		fLogicalVolume->SetVisAttributes(TRexColour::Get()->red);
	}
}

void TRexCDErestSingle::ConstructPCB(G4LogicalVolume* experimentalHall_log) {
	G4Material* pcb = TRexMaterials::Get()->GetMaterial("pcb");

	G4double pcbInnerRadius = 7.4 * mm;
	G4double pcbOuterRadius = 61.0 * mm;
	G4double pcbThickness = 2.0 * mm;

	// pcb start volume
	G4Tubs* pcbtot_solid = new G4Tubs("PCB1_solid", 0., pcbOuterRadius, pcbThickness /2., fStartAngleDetector - 4*degree, 90.*degree);

	// inner quadratic hole
	G4Box* pcbhole = new G4Box("PCBHole_solid", pcbInnerRadius/sqrt(2.), pcbInnerRadius/sqrt(2.), pcbThickness*2.);

	// subtract the inner quadratic hole
	G4SubtractionSolid* PCBQuadrant_solid = new G4SubtractionSolid("tmpPCB_solid", pcbtot_solid, pcbhole);

	// detector with larger thickness needed for subtraction
	G4Tubs* PCBQuadrant_tmp = new G4Tubs(Form("FEPCBQuadrant%d_tmp",fId), fInnerRadiusDetector, fOuterRadiusDetector,
			pcbThickness*2., fStartAngleDetector, fSpanningAngleDetector);

	// subtract the detector with the larger thickness to get the final pcb board
	PCBQuadrant_solid = new G4SubtractionSolid("tmpPCB_solid", PCBQuadrant_solid, PCBQuadrant_tmp);

	G4LogicalVolume* PCBCD_log = new G4LogicalVolume(PCBQuadrant_solid, pcb, "PCBForwardCD_log");

	//G4VPhysicalVolume* phys_vol =
	new G4PVPlacement(0, fPos, PCBCD_log, "PCBForwardCD1", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		PCBCD_log->SetVisAttributes(TRexColour::Get()->darkgreen);
	}
}

void TRexCDErestSingle::ConstructDeadLayer(G4LogicalVolume* experimentalHall_log) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("silicon");

	// total detector volume
	G4Tubs* deadLayerWithDetector_solid = new G4Tubs("detector", fInnerRadiusDetector, fOuterRadiusDetector,
			fThicknessDetector / 2., fStartAngleDetector, fSpanningAngleDetector);

	// subtract the active detector volume to get only the dead layer volume
	G4SubtractionSolid* deadLayer_solid = new G4SubtractionSolid("deadLayer_solid", deadLayerWithDetector_solid, fSolid);

	G4LogicalVolume* deadLayer_log = new G4LogicalVolume(deadLayer_solid, detectorMaterial, "deadLayer_log");
	//G4VPhysicalVolume* phys_vol =
	new G4PVPlacement(0, fPos, deadLayer_log, "deadLayer", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		deadLayer_log->SetVisAttributes(TRexColour::Get()->red);
	}
}

std::vector<ParticleMC>* TRexCDErestSingle::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	particleMCvector->push_back(*fCDErestSingleSensitiveDetector->GetParticleMC());

	return particleMCvector;
}
