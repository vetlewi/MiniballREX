/*
 * TRexTrapezoidDeltaESingle.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidDeltaESingle.hh"
#include "TRex/TRexTrapezoidDeltaESingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

TRexTrapezoidDeltaESingle::TRexTrapezoidDeltaESingle() {
}

TRexTrapezoidDeltaESingle::TRexTrapezoidDeltaESingle(std::string name, std::string direction, int id) {
	fName = name;
	fId = id;
	fDirection = direction;

	if(fDirection == "forward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetFTrapezoidDeltaESingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetFTrapezoidDeltaESingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetFTrapezoidDeltaESingleDeltaZ();
		fThicknessDetector = TRexSettings::Get()->GetFTrapezoidDeltaESingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetFTrapezoidDeltaESingleStartAngle()[fId];
		fPosZ = TRexSettings::Get()->GetFTrapezoidDeltaESinglePosZ()[fId];
		fFoilThickness = TRexSettings::Get()->GetFTrapezoidDeltaESingleFoilThickness();
	} else if(fDirection == "backward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetBTrapezoidDeltaESingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetBTrapezoidDeltaESingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetBTrapezoidDeltaESingleDeltaZ();
		fThicknessDetector = TRexSettings::Get()->GetBTrapezoidDeltaESingleThickness()[fId];
		fStartAngleDetector = TRexSettings::Get()->GetBTrapezoidDeltaESingleStartAngle()[fId];
		fPosZ = TRexSettings::Get()->GetBTrapezoidDeltaESinglePosZ()[fId];
		fFoilThickness = TRexSettings::Get()->GetBTrapezoidDeltaESingleFoilThickness();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}

	// set geometrical parameters (Pcb has to be set before silicon !!!!)
	SetPcbParameters();
	SetSiliconParameters();
	SetFoilParameters();
}

TRexTrapezoidDeltaESingle::~TRexTrapezoidDeltaESingle() {
	// TODO Auto-generated destructor stub
}


void TRexTrapezoidDeltaESingle::SetPcbParameters() {
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

void TRexTrapezoidDeltaESingle::SetSiliconParameters() {
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

void TRexTrapezoidDeltaESingle::SetFoilParameters() {
	// radii
	fFoilOuterRadius = fPcbOuterRadius - (5.0 + 2.0)*mm;
	fFoilInnerRadius = fPcbInnerRadius - (5.0 + 2.0)*mm;

	// base length of the trapezoid panel
	fFoilBaseLarge = fFoilOuterRadius * sqrt(2. - sqrt(2.)) / 2.;
	fFoilBaseSmall = fFoilInnerRadius * sqrt(2. - sqrt(2.)) / 2.;

	// outer and inner height of the detector
	fhOutFoil = fFoilBaseLarge * (1. + sqrt(2.));
	fhInFoil = fFoilBaseSmall * (1. + sqrt(2.));

	// length of the trapezoid panel
	fFoilLength = sqrt(pow((fhOutFoil - fhInFoil) / 2., 2) + pow(fDetectorDeltaZ, 2));

	// tilt angle
	fFoilBeta = asin(fDetectorDeltaZ / fFoilLength);

	// set position
	fFoilPos = G4ThreeVector(0, (fhOutFoil / 2. + fhInFoil / 2. + fFoilThickness * sin(fFoilBeta)) / 2., fPosZ);

	fFoilPos.rotateZ(fStartAngleDetector);

	// set rotation matrix
	fRotMatrixFoil = new G4RotationMatrix;
	if(fDirection == "forward") {
		fRotMatrixFoil->rotateX(-fFoilBeta);
	}
	else if(fDirection == "backward") {
		fRotMatrixFoil->rotateX(fFoilBeta);
	}
	fRotMatrixFoil->rotateZ(fStartAngleDetector);
}

void TRexTrapezoidDeltaESingle::Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
	// active detector
	ConstructSilicon(experimentalHall_log, SDMan);

	// PCB
	if(TRexSettings::Get()->ConstructPCB()) {
		ConstructPCB(experimentalHall_log);
	}

	// protection foils ?
	if(fFoilThickness > 0.1*um) {
		ConstructFoil(experimentalHall_log);
	}
}

void TRexTrapezoidDeltaESingle::ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan) {
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
	//		fLogicalVolume, "TrapezoidDeltaE", experimentalHall_log, false, 0); // rotation of the mother volume !
	// does work! -> gets local hit position correct !!!! // rotation of the object in the mother volume
	fPhysicalVolume = new G4PVPlacement(G4Transform3D(*fRotMatrix, fPos),
			fLogicalVolume, "TrapezoidDeltaE", experimentalHall_log, false, 0);

	// register sensitive detector
	SDMan = G4SDManager::GetSDMpointer();
	fTrapezoidDeltaESingleSensitiveDetector = new TRexTrapezoidDeltaESingleSensitiveDetector(G4String(fName), fDirection, fId);
	SDMan->AddNewDetector(fTrapezoidDeltaESingleSensitiveDetector);
	fLogicalVolume->SetSensitiveDetector(fTrapezoidDeltaESingleSensitiveDetector);

	if(TRexSettings::Get()->Colours()) {
		fLogicalVolume->SetVisAttributes(TRexColour::Get()->yellow);
	}
}

void TRexTrapezoidDeltaESingle::ConstructPCB(G4LogicalVolume* experimentalHall_log) {
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
	//		fLogicalVolume, "TrapezoidDeltaE", experimentalHall_log, false, 0); // rotation of the mother volume !
	// does work! -> gets local hit position correct !!!! // rotation of the object in the mother volume
	new G4PVPlacement(G4Transform3D(*fRotMatrixPcb, fPcbPos),
			pcb_log, "TrapezoidDeltaE_pcb", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		pcb_log->SetVisAttributes(TRexColour::Get()->darkgreen);
	}
}


void TRexTrapezoidDeltaESingle::ConstructFoil(G4LogicalVolume* experimentalHall_log) {
	G4Material* foilMaterial = TRexMaterials::Get()->GetMaterial("mylar");

	G4Trap *foil_solid = new G4Trap("detector_foil", fFoilThickness/2., 0*deg, 0*deg,
			fFoilLength/2., fFoilBaseSmall/2., fFoilBaseLarge/2., 0*deg,
			fFoilLength/2., fFoilBaseSmall/2., fFoilBaseLarge/2., 0*deg);

	G4LogicalVolume* foil_log = new G4LogicalVolume(foil_solid, foilMaterial, fName + "_log", 0,0 ,0);


	// does not work! -> gets local hit position wrong !!!!
	//fPhysicalVolume = new G4PVPlacement(fRotMatrix, fPos,
	//		fLogicalVolume, "TrapezoidDeltaE", experimentalHall_log, false, 0); // rotation of the mother volume !
	// does work! -> gets local hit position correct !!!! // rotation of the object in the mother volume
	new G4PVPlacement(G4Transform3D(*fRotMatrixFoil, fFoilPos),
			foil_log, "TrapezoidDeltaE_foil", experimentalHall_log, false, 0);

	if(TRexSettings::Get()->Colours()) {
		foil_log->SetVisAttributes(TRexColour::Get()->silver);
	}
}

std::vector<ParticleMC>* TRexTrapezoidDeltaESingle::GetParticleMCvector() {
	std::vector<ParticleMC>* particleMCvector = new std::vector<ParticleMC>(0);

	particleMCvector->push_back(*fTrapezoidDeltaESingleSensitiveDetector->GetParticleMC());

	return particleMCvector;
}
