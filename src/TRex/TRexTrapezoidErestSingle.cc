/*
 * TRexTrapezoidErestSingle.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidErestSingle.hh"
#include "TRex/TRexTrapezoidErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexTrapezoidErestSingle::TRexTrapezoidErestSingle() {
}

TRexTrapezoidErestSingle::TRexTrapezoidErestSingle(std::string name, std::string direction, int id) {
	fName = name;
	fId = id;
	fDirection = direction;

	if(fDirection == "forward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetFTrapezoidErestSingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetFTrapezoidErestSingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetFTrapezoidErestSingleDeltaZ();
		fThicknessDetector = TRexSettings::Get()->GetFTrapezoidErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetFTrapezoidErestSingleStartAngle()[fId];
		fPosZ = TRexSettings::Get()->GetFTrapezoidErestSinglePosZ()[fId];
	} else if(fDirection == "backward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetBTrapezoidErestSingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetBTrapezoidErestSingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetBTrapezoidErestSingleDeltaZ();
		fThicknessDetector = TRexSettings::Get()->GetBTrapezoidErestSingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetBTrapezoidErestSingleStartAngle()[fId];
		fPosZ = TRexSettings::Get()->GetBTrapezoidErestSinglePosZ()[fId];
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}

	// set geometrical parameters (Pcb has to be set before silicon !!!!)
	SetPcbParameters();
	SetSiliconParameters();
}

TRexTrapezoidErestSingle::~TRexTrapezoidErestSingle() {
	// TODO Auto-generated destructor stub
}


void TRexTrapezoidErestSingle::SetPcbParameters() {
	// radii
	fPcbOuterRadius = fDetectorOuterRadius * 1.3;
	fPcbInnerRadius = fDetectorInnerRadius * 1.3;
	fThicknessPcb = 2.0 * mm;

	// base length of the trapezoid panel
	fPcbBaseLarge = fPcbOuterRadius * sqrt(2. - sqrt(2.)) / 2.;
	fPcbBaseSmall = fPcbInnerRadius * sqrt(2. - sqrt(2.)) / 2.;

	// outer and inner height of the detector
	fhOutPcb = fPcbBaseLarge * (1. + sqrt(2.));
	fhInPcb = fPcbBaseSmall * (1. + sqrt(2.));

	// length of the trapezoid panel
	fPcbLength = sqrt(pow((fhOutPcb - fhInPcb) / 2., 2) + pow(fDetectorDeltaZ, 2));

	// tilt angle
	fPcbBeta = asin(fDetectorDeltaZ / fPcbLength);

	// set position
	fPcbPos = G4ThreeVector(0, (fhOutPcb / 2. + fhInPcb / 2. + fThicknessPcb * sin(fPcbBeta)) / 2., fPosZ);

	std::cout << "fPcbPos.Y = " << fPcbPos.y() << std::endl;

	fPcbPos.rotateZ(fStartAngleDetector);

	// set rotation matrix
	fRotMatrixPcb = new G4RotationMatrix;
	if(fDirection == "forward") {
		fRotMatrixPcb->rotateX(-fPcbBeta);
	} else if(fDirection == "backward") {
		fRotMatrixPcb->rotateX(fPcbBeta);
	}
	fRotMatrixPcb->rotateZ(fStartAngleDetector);
}

void TRexTrapezoidErestSingle::SetSiliconParameters() {
	// base length of the trapezoid panel detector
	fBaseLarge = fDetectorOuterRadius * sqrt(2. - sqrt(2.)) / 2.;
	fBaseSmall = fDetectorInnerRadius * sqrt(2. - sqrt(2.)) / 2.;

	// outer and inner height of the detector
	G4double hOut = fBaseLarge * (1. + sqrt(2.));
	G4double hIn = fBaseSmall * (1. + sqrt(2.));

	// length of the trapezoid panel
	fLength = sqrt(pow((hOut - hIn) / 2., 2) + pow(fDetectorDeltaZ, 2));

	// beta: angle between the y-axis and the trapezoid panel
	// 90deg - beta: angle between the z-axis and the trapezoid panel
	//fBeta = asin(fDetectorDeltaZ / fLength);
	fBeta = asin(fDetectorDeltaZ / fPcbLength);

	std::cout << "fDetectorDeltaZ = " << fDetectorDeltaZ << " , fPcbLength = " << fPcbLength << " , fBeta = " << fBeta / degree << std::endl;

	// set position
	//fPos = G4ThreeVector(0, (hOut - hIn) / 2., fPosZ);
	fPos = G4ThreeVector(0, (fhOutPcb / 2. + fhInPcb / 2. + fThicknessPcb * sin(fPcbBeta)) / 2., fPosZ);
	// rotate position
	fPos.rotateZ(fStartAngleDetector);

	// set rotation matrix
	fRotMatrix = new G4RotationMatrix;
	if(fDirection == "forward") {
		fRotMatrix->rotateX(-fBeta);
	} else if(fDirection == "backward") {
		fRotMatrix->rotateX(fBeta);
	}
	fRotMatrix->rotateZ(fStartAngleDetector);
}

void TRexTrapezoidErestSingle::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// active detector
	ConstructSilicon(experimentalHall_log, SDMan);

	// PCB
	if(TRexSettings::Get()->ConstructPCB()) {
		ConstructPCB(experimentalHall_log);
	}
}

void TRexTrapezoidErestSingle::ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("silicon");

	// original Gaspard simulation
	//	fSolid = new G4Trap("detector", Length/2, 0*deg, 0*deg,
	//		                            Height/2, BaseLarge/2, BaseSmall/2, 0*deg,
	//		                            Height/2, BaseLarge/2, BaseSmall/2, 0*deg);

	fSolid = new G4Trap("detector", fThicknessDetector/2., 0*deg, 0*deg,
			fLength/2., fBaseSmall/2., fBaseLarge/2., 0*deg,
			fLength/2., fBaseSmall/2., fBaseLarge/2., 0*deg);

	fLogicalVolume = new G4LogicalVolume(fSolid, detectorMaterial, fName + "_log", 0,0 ,0);

	// does not work! -> gets local hit position wrong !!!!
	//fPhysicalVolume = new G4PVPlacement(fRotMatrix, fPos,
	//		fLogicalVolume, "TrapezoidErest", experimentalHall_log, false, 0); // rotation of the mother volume !
	// does work! -> gets local hit position correct !!!! // rotation of the object in the mother volume
	fPhysicalVolume = new G4PVPlacement(G4Transform3D(*fRotMatrix, fPos),
			fLogicalVolume, "TrapezoidErest", experimentalHall_log, false, 0);

	// register sensitive detector
	SDMan = G4SDManager::GetSDMpointer();
	fTrapezoidErestSingleSensitiveDetector = new TRexTrapezoidErestSingleSensitiveDetector(G4String(fName), fDirection, fId);
	SDMan->AddNewDetector(fTrapezoidErestSingleSensitiveDetector);
	fLogicalVolume->SetSensitiveDetector(fTrapezoidErestSingleSensitiveDetector);

	if(TRexSettings::Get()->Colours()) {
		fLogicalVolume->SetVisAttributes(TRexColour::Get()->yellow);
	}
}

void TRexTrapezoidErestSingle::ConstructPCB(G4LogicalVolume* experimentalHall_log) {
	G4Material* detectorMaterial = TRexMaterials::Get()->GetMaterial("pcb");

	G4Trap *pcb = new G4Trap("detector_pcb", fThicknessPcb/2., 0*deg, 0*deg,
			fPcbLength/2., fPcbBaseSmall/2., fPcbBaseLarge/2., 0*deg,
			fPcbLength/2., fPcbBaseSmall/2., fPcbBaseLarge/2., 0*deg);

	G4Trap *pcbHole = new G4Trap("detector", fThicknessPcb, 0*deg, 0*deg,
			fLength/2., fBaseSmall/2., fBaseLarge/2., 0*deg,
			fLength/2., fBaseSmall/2., fBaseLarge/2., 0*deg);

	// subtract hole for detector
	G4SubtractionSolid* pcbTotal = new G4SubtractionSolid("deltaPCB_solid", pcb, pcbHole, 0, G4ThreeVector(0, 0, 0));

	G4LogicalVolume* pcb_log = new G4LogicalVolume(pcbTotal, detectorMaterial, fName + "_log", 0,0 ,0);


	// does not work! -> gets local hit position wrong !!!!
	//fPhysicalVolume = new G4PVPlacement(fRotMatrix, fPos,
	//		fLogicalVolume, "TrapezoidErest", experimentalHall_log, false, 0); // rotation of the mother volume !
	// does work! -> gets local hit position correct !!!! // rotation of the object in the mother volume
	new G4PVPlacement(G4Transform3D(*fRotMatrixPcb, fPcbPos),
			pcb_log, "TrapezoidErest_pcb", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		pcb_log->SetVisAttributes(TRexColour::Get()->darkgreen);
	}
}

std::vector<ParticleMC>* TRexTrapezoidErestSingle::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>;

	particleMCvector->push_back(*fTrapezoidErestSingleSensitiveDetector->GetParticleMC());

	return particleMCvector;
}
