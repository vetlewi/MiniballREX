/*
 * TRexTrapezoidDeltaESingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidDeltaESingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexTrapezoidDeltaESingleSensitiveDetector::TRexTrapezoidDeltaESingleSensitiveDetector() {
//}

TRexTrapezoidDeltaESingleSensitiveDetector::TRexTrapezoidDeltaESingleSensitiveDetector(G4String name, G4String direction, int id):
	G4VSensitiveDetector(name) {
	fName = name;
	fDirection = direction;
	fID = id;
	fCollectionID = -1;

	collectionName.insert("Collection" + name);

	fTrapezoidDeltaESingle = new ParticleMC();

	if(fDirection == "forward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetFTrapezoidDeltaESingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetFTrapezoidDeltaESingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetFTrapezoidDeltaESingleDeltaZ();
		fNbOfRings = TRexSettings::Get()->GetFTrapezoidDeltaESingleNbOfRings();
		fNbOfStrips = TRexSettings::Get()->GetFTrapezoidDeltaESingleNbOfStrips();
		fEnergyResolution = TRexSettings::Get()->GetFTrapezoidDeltaESingleEnergyResolution();
	} else if(fDirection == "backward") {
		fDetectorInnerRadius = TRexSettings::Get()->GetBTrapezoidDeltaESingleInnerRadius();
		fDetectorOuterRadius = TRexSettings::Get()->GetBTrapezoidDeltaESingleOuterRadius();
		fDetectorDeltaZ = TRexSettings::Get()->GetBTrapezoidDeltaESingleDeltaZ();
		fNbOfRings = TRexSettings::Get()->GetBTrapezoidDeltaESingleNbOfRings();
		fNbOfStrips = TRexSettings::Get()->GetBTrapezoidDeltaESingleNbOfStrips();
		fEnergyResolution = TRexSettings::Get()->GetBTrapezoidDeltaESingleEnergyResolution();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}

	// base length of the trapezoid panel detector
	fBaseLarge = fDetectorOuterRadius * sqrt(2. - sqrt(2.)) / 2.;
	fBaseSmall = fDetectorInnerRadius * sqrt(2. - sqrt(2.)) / 2.;

	// outer and inner height of the detector
	G4double hOut = fBaseLarge * (1. + sqrt(2.));
	G4double hIn = fBaseSmall * (1. + sqrt(2.));

	// length of the trapezoid panel
	fLength = sqrt(pow((hOut - hIn) / 2., 2) + pow(fDetectorDeltaZ, 2));

	// strip and ring width
	fRingWidth = fLength / fNbOfRings;

	//fTotalDeltaPhi = 2. * atan(fBaseLarge / 2. / hOut);
	fTotalDeltaPhi = 2. * atan(1. / (2. + 2. * sqrt(2.)));

	fStripWidth = fTotalDeltaPhi / fNbOfStrips;

	std::cout << "TotalDeltaPhi = " << fTotalDeltaPhi / degree << " = " <<  2. * atan(fBaseSmall / 2. / hIn) / degree << std::endl;
	std::cout << "Ring width = " << fRingWidth << " , strip width = " << fStripWidth / degree << std::endl;
}

TRexTrapezoidDeltaESingleSensitiveDetector::~TRexTrapezoidDeltaESingleSensitiveDetector() {
	// TODO Auto-generated destructor stub
}

// initialize event
void TRexTrapezoidDeltaESingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4std::cout << "Initialize sensitive detector" << G4std::endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}


// process hits
G4bool TRexTrapezoidDeltaESingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}


G4bool TRexTrapezoidDeltaESingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
		G4TouchableHistory* ROHist) {
	// only primary particle hits are considered (no secondaries)
	if(aStep->GetTrack()->GetParentID() != 0 || aStep->GetTotalEnergyDeposit() < 1.*eV) {
		return false;
	}

	TRexHit *hit = new TRexHit(aStep, ROHist);

	fHitCollection->insert(hit);

	return true;
}


// write into root file
void TRexTrapezoidDeltaESingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fTrapezoidDeltaESingle->ClearParticleMC();

	if(GetTotalEnergyDeposition() > 0) {
		fTrapezoidDeltaESingle->ID(fID);

		SetRingsOrStrips("ring");
		SetRingsOrStrips("strip");
	}
}

G4double TRexTrapezoidDeltaESingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexTrapezoidDeltaESingleSensitiveDetector::GetRingNumber(G4ThreeVector localPos) {
	G4double y = localPos.y() + fLength / 2.;
	//std::cout << "localPos.y = " << localPos.y() << " , y = " << y << " ringNb = " << (int)((y / fRingWidth) - 1.e-5) << std::endl;

	return (int)((y / fRingWidth) - 1.e-5);
}


int TRexTrapezoidDeltaESingleSensitiveDetector::GetStripNumber(G4ThreeVector localPos) {
	G4double distanceToCenter = fLength/(fBaseLarge/fBaseSmall -1);   //fDetectorInnerRadius * cos(fTotalDeltaPhi / 2.);
	G4double y = localPos.y() + fLength / 2.;

	// x position after transformation
	G4double x = localPos.x()*distanceToCenter/(y+distanceToCenter);

	// x in [-fLength / 2, fLength / 2] -> x in [0, fLength]
	x += fBaseSmall / 2;

	int stripNb = (int)((x / fBaseSmall) * fNbOfStrips - 1.e-5);

	// forward or backward ????
	if(fDirection == "backward") {
		stripNb = fNbOfStrips - 1 - stripNb;
	}

	return stripNb ;
}


void TRexTrapezoidDeltaESingleSensitiveDetector::SetRingsOrStrips(std::string ringOrStrip) {
	// initialize first and second strips
	int firstRingOrStripNb = -99;
	G4double firstRingOrStripEnergy = 0. * keV;
	int firstRingOrStripA, firstRingOrStripZ;
	int firstRingOrStripTrackID;
	G4double firstRingOrStripTime;
	int firstRingOrStripStopped;

	int secondRingOrStripNb = -99;
	G4double secondRingOrStripEnergy = 0. * keV;
	int secondRingOrStripA, secondRingOrStripZ;
	int secondRingOrStripTrackID;
	G4double secondRingOrStripTime;
	int secondRingOrStripStopped;

	int currentRingOrStripNb;
	double resEnergy;


	for(int i = 0; i < fHitCollection->entries(); i++) {
		if(ringOrStrip == "strip") {
			currentRingOrStripNb = GetStripNumber((*fHitCollection)[i]->GetLocalHitPosition());
		} else if(ringOrStrip == "ring") {
			currentRingOrStripNb = GetRingNumber((*fHitCollection)[i]->GetLocalHitPosition());
		} else {
			std::cout << "Error: CDdeltaESingleSensitiveDetector: choose between ring or strip" << std::endl;
		}

		if(firstRingOrStripNb == -99 || firstRingOrStripNb == currentRingOrStripNb) {
		// check if the first strip is hit (for the first time or more than once)
			firstRingOrStripNb = currentRingOrStripNb;
			firstRingOrStripEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
			firstRingOrStripA = (*fHitCollection)[i]->GetParticleA();
			firstRingOrStripZ = (*fHitCollection)[i]->GetParticleZ();
			firstRingOrStripTrackID = (*fHitCollection)[i]->GetTrackID();
			firstRingOrStripTime = (*fHitCollection)[i]->GetTime();
			firstRingOrStripStopped = IsStopped(i, resEnergy);
		} else if(secondRingOrStripNb == -99 || secondRingOrStripNb == currentRingOrStripNb) {
		// check if the second RingOrStrip is hit (for the first time or more than once)
			secondRingOrStripNb = currentRingOrStripNb;
			secondRingOrStripEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
			secondRingOrStripA = (*fHitCollection)[i]->GetParticleA();
			secondRingOrStripZ = (*fHitCollection)[i]->GetParticleZ();
			secondRingOrStripTrackID = (*fHitCollection)[i]->GetTrackID();
			secondRingOrStripTime = (*fHitCollection)[i]->GetTime();
			secondRingOrStripStopped = IsStopped(i, resEnergy);
		} else {
		// more than two different strips have been hit
			std::cout << "There are more than two different hit strips in the BarrelDeltaE detector." << std::endl;
		}
	}

	if(ringOrStrip == "strip") {
		if(firstRingOrStripNb != -99 && secondRingOrStripNb == -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fTrapezoidDeltaESingle->AddStrip(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
		} else if(firstRingOrStripNb != -99 && secondRingOrStripNb != -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
				secondRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fTrapezoidDeltaESingle->AddStrip(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
			fTrapezoidDeltaESingle->AddStrip(secondRingOrStripNb, secondRingOrStripEnergy / keV, secondRingOrStripA, secondRingOrStripZ,
					secondRingOrStripTrackID, secondRingOrStripTime / ns, secondRingOrStripStopped);
		}
	} else if(ringOrStrip == "ring") {
		if(firstRingOrStripNb != -99 && secondRingOrStripNb == -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fTrapezoidDeltaESingle->AddRing(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
		} else if(firstRingOrStripNb != -99 && secondRingOrStripNb != -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
				secondRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fTrapezoidDeltaESingle->AddRing(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
			fTrapezoidDeltaESingle->AddRing(secondRingOrStripNb, secondRingOrStripEnergy / keV, secondRingOrStripA, secondRingOrStripZ,
					secondRingOrStripTrackID, secondRingOrStripTime / ns, secondRingOrStripStopped);
		}
	} else {
		std::cout << "Error: CDdeltaESingleSensitiveDetector: choose between ring or strip" << std::endl;
	}
}

int TRexTrapezoidDeltaESingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
	// set default value resKinEnergy (residual energy of punch through particles)
	resKinEnergy = -100.;

	// check if particle  is primary
	if((*fHitCollection)[hitIndex]->GetParentID() != 0)
		return -3;

	// check if the hitIndex is the last particle hit
	bool isLastHit;
	if(hitIndex == fHitCollection->entries() - 1) {
		isLastHit = true;
	} else if(fabs((*fHitCollection)[hitIndex]->GetVertexKineticEnergy() - (*fHitCollection)[hitIndex + 1]->GetVertexKineticEnergy()) < 0.001*eV ) { // check if it is the same particle
		isLastHit = false;
	} else {
		isLastHit = true;
	}

	if(isLastHit == false)
		return -2;

	resKinEnergy = (*fHitCollection)[hitIndex]->GetKineticEnergy() / keV;

	// check if particle is stopped
	if(fabs((*fHitCollection)[hitIndex]->GetKineticEnergy()) < 0.001*eV) {
		// stopped
		return 1;
	} else {
		// not stopped
		return 0;
	}
}
