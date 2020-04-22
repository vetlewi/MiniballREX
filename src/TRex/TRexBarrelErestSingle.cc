/*
 * TRexBarrelErestSingle.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrelErestSingle.hh"
#include "TRex/TRexBarrelErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexBarrelErestSingle::TRexBarrelErestSingle() {
}

TRexBarrelErestSingle::TRexBarrelErestSingle(std::string name, std::string direction, int id) {
	fName = name;
	fId = id;
	fDirection = direction;

	if(fDirection == "forward") {
		fDetectorLengthX = TRexSettings::Get()->GetFBarrelErestSingleLengthX();
		fDetectorLengthY = TRexSettings::Get()->GetFBarrelErestSingleLengthY();
		fThicknessDetector = TRexSettings::Get()->GetFBarrelErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetFBarrelErestSingleStartAngle()[fId];

		fDeadLayer = TRexSettings::Get()->GetFBarrelErestSingleDeadLayer();

		fPos = G4ThreeVector(TRexSettings::Get()->GetFBarrelErestSingleDistanceToBeam()[fId] * cos(fStartAngleDetector / rad),
									TRexSettings::Get()->GetFBarrelErestSingleDistanceToBeam()[fId] * sin(fStartAngleDetector / rad),
									TRexSettings::Get()->GetFBarrelErestSinglePosZ()[fId]);
	} else if(fDirection == "middle") {
		fDetectorLengthX = TRexSettings::Get()->GetMBarrelErestSingleLengthX();
		fDetectorLengthY = TRexSettings::Get()->GetMBarrelErestSingleLengthY();
		fThicknessDetector = TRexSettings::Get()->GetMBarrelErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetMBarrelErestSingleStartAngle()[fId];

		fDeadLayer = TRexSettings::Get()->GetMBarrelErestSingleDeadLayer();

		fPos = G4ThreeVector(TRexSettings::Get()->GetMBarrelErestSingleDistanceToBeam()[fId] * cos(fStartAngleDetector / rad),
									TRexSettings::Get()->GetMBarrelErestSingleDistanceToBeam()[fId] * sin(fStartAngleDetector / rad),
									TRexSettings::Get()->GetMBarrelErestSinglePosZ()[fId]);
	} else if(fDirection == "backward") {
		fDetectorLengthX = TRexSettings::Get()->GetBBarrelErestSingleLengthX();
		fDetectorLengthY = TRexSettings::Get()->GetBBarrelErestSingleLengthY();
		fThicknessDetector = TRexSettings::Get()->GetBBarrelErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetBBarrelErestSingleStartAngle()[fId];

		fDeadLayer = TRexSettings::Get()->GetBBarrelErestSingleDeadLayer();

		fPos = G4ThreeVector(TRexSettings::Get()->GetBBarrelErestSingleDistanceToBeam()[fId] * cos(fStartAngleDetector / rad),
									TRexSettings::Get()->GetBBarrelErestSingleDistanceToBeam()[fId] * sin(fStartAngleDetector / rad),
									TRexSettings::Get()->GetBBarrelErestSinglePosZ()[fId]);
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}

	fRotMatrix = new G4RotationMatrix;
	fRotMatrix->rotateZ(fStartAngleDetector);
}

TRexBarrelErestSingle::~TRexBarrelErestSingle() {
	// TODO Auto-generated destructor stub
}

void TRexBarrelErestSingle::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
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

void TRexBarrelErestSingle::ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("silicon");

	fSolid = new G4Box("detector", fThicknessDetector / 2. - fDeadLayer, fDetectorLengthX / 2., fDetectorLengthY / 2.);

	fLogicalVolume = new G4LogicalVolume(fSolid, detectorMaterial, fName + "_log", 0,0 ,0);

	// does not work! -> gets local hit position wrong !!!!
	//fPhysicalVolume = new G4PVPlacement(fRotMatrix, fPos,
	//		fLogicalVolume, "detectorWithHole", experimentalHall_log, false, 0);
	// does work! -> gets local hit position correct !!!!
	fPhysicalVolume = new G4PVPlacement(G4Transform3D(*fRotMatrix, fPos),
			fLogicalVolume, "detectorWithHole", experimentalHall_log, false, 0);

	// register sensitive detector
	SDMan = G4SDManager::GetSDMpointer();
	fBarrelErestSingleSensitiveDetector = new TRexBarrelErestSingleSensitiveDetector(G4String(fName), fDirection, fId);
	SDMan->AddNewDetector(fBarrelErestSingleSensitiveDetector);
	fLogicalVolume->SetSensitiveDetector(fBarrelErestSingleSensitiveDetector);

	if(TRexSettings::Get()->Colours()) {
		fLogicalVolume->SetVisAttributes(TRexColour::Get()->red);
	}
}

void TRexBarrelErestSingle::ConstructPCB(G4LogicalVolume* experimentalHall_log) {
	G4Material* pcb = TRexMaterials::Get()->GetMaterial("pcb");

	G4double pcbWidth = 89 * mm;
	G4double pcbThickness = 1.5 * mm;
	G4double pcbLength = 54 * mm;
	G4double pcbRecessWidth = 23 * mm;
	G4double pcbRecessLength = 22 * mm;
	G4double barrelDisplacement = 16.5 * mm;
	//G4double pcbEdgeWidth = 78 * mm;

	G4Box* PCB_dE = new G4Box("PCB_dE", pcbThickness / 2., pcbWidth / 2., pcbLength / 2.);

	G4Box* PCB_hole = new G4Box("PCB_hole", pcbThickness/1.9, fDetectorLengthX / 2., fDetectorLengthY/2.);
	G4Box* PCB_corner = new G4Box("PCB_corner", pcbThickness / 1.9, pcbRecessWidth /2. + 0.1, pcbRecessLength /2. + 0.1);

	//G4Box* PCB_edge = new G4Box("PCB_edge", pcbThickness / 1.9, (pcbRecessWidth - pcbEdgeWidth) /2. + 0.1, pcbLength /2. + 0.1);

	// subtract hole for detector
	G4SubtractionSolid* PCBQuadrant_solid = new G4SubtractionSolid("deltaPCB_solid", PCB_dE, PCB_hole, new G4RotationMatrix(),
			G4ThreeVector(0, barrelDisplacement, 0));

	// subtract corner
	PCBQuadrant_solid = new G4SubtractionSolid("deltaPCB_solid", PCBQuadrant_solid, PCB_corner, new G4RotationMatrix(),
			G4ThreeVector(0,  -(pcbWidth / 2.- pcbRecessWidth /2.), pcbLength /2. - pcbRecessLength/2.));

	//PCBQuadrant_solid = new G4SubtractionSolid("EPCB_solid", PCBQuadrant_solid, PCB_edge, new G4RotationMatrix(),
	//		G4ThreeVector(0, -(pcbWidth - (pcbWidth - pcbEdgeWidth)/2.) /2., 0));

	G4LogicalVolume* PCBCD_log = new G4LogicalVolume(PCBQuadrant_solid, pcb, "PCBForwardBarrel_log");

	fRotMatrixPcb = fRotMatrix;

	G4ThreeVector pcbPos = fPos;
	pcbPos.setX(fPos.x() - barrelDisplacement * sin(fStartAngleDetector / rad));
	pcbPos.setY(fPos.y() - barrelDisplacement * cos(fStartAngleDetector / rad));

	if(fabs(fPos.x()) < 0.1) {
		fRotMatrixPcb->rotateX(180.*degree);
		pcbPos.setX(fPos.x() + barrelDisplacement * sin(fStartAngleDetector / rad));
		pcbPos.setY(fPos.y() + barrelDisplacement * cos(fStartAngleDetector / rad));
	}

	if(fDirection == "backward") {
		pcbPos.setX(fPos.x() - barrelDisplacement * sin(fStartAngleDetector / rad));
		pcbPos.setY(fPos.y() - barrelDisplacement * cos(fStartAngleDetector / rad));

		if(fabs(fPos.y()) < 0.1) {
			fRotMatrixPcb->rotateY(180.*degree);
			pcbPos.setX(fPos.x() + barrelDisplacement * sin(fStartAngleDetector / rad));
			pcbPos.setY(fPos.y() + barrelDisplacement * cos(fStartAngleDetector / rad));
		}

		fRotMatrixPcb->rotateZ(-180.*degree);
	}

	//G4VPhysicalVolume* phys_vol =
	new G4PVPlacement(fRotMatrixPcb, pcbPos, PCBCD_log, "PCBForwardBarrel1", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		PCBCD_log->SetVisAttributes(TRexColour::Get()->darkgreen);
	}
}

void TRexBarrelErestSingle::ConstructDeadLayer(G4LogicalVolume* experimentalHall_log) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("silicon");

	// total detector volume
	G4Box* deadLayerWithDetector_solid = new G4Box("detectorAndDeadLayer", fThicknessDetector / 2.,
			fDetectorLengthX / 2., fDetectorLengthY / 2.);

	// subtract the active detector volume to get only the dead layer volume
	G4SubtractionSolid* deadLayer_solid = new G4SubtractionSolid("deadLayer_solid", deadLayerWithDetector_solid, fSolid);

	G4LogicalVolume* deadLayer_log = new G4LogicalVolume(deadLayer_solid, detectorMaterial, fName + "_deadLayer_log");

	//G4VPhysicalVolume* phys_vol =
	new G4PVPlacement(G4Transform3D(*fRotMatrix, fPos), deadLayer_log, "deadLayerBarrelErest", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		fLogicalVolume->SetVisAttributes(TRexColour::Get()->yellow);
	}
}

std::vector<ParticleMC>* TRexBarrelErestSingle::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	particleMCvector->push_back(*fBarrelErestSingleSensitiveDetector->GetParticleMC());

	return particleMCvector;
}
