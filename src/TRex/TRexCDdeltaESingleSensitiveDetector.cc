/*
 * TRexCDdeltaESingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCDdeltaESingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexCDdeltaESingleSensitiveDetector::TRexCDdeltaESingleSensitiveDetector() {
//}

TRexCDdeltaESingleSensitiveDetector::TRexCDdeltaESingleSensitiveDetector(G4String name, G4String direction, int id) :
	G4VSensitiveDetector(name) {
	fName = name;
	fDirection = direction;
	fID = id;
	fCollectionID = -1;

	collectionName.insert("Collection" + name);

	fCDdeltaESingle = new ParticleMC();

	if(fDirection == "forward") {
		fInnerRadius = TRexSettings::Get()->GetFCDdeltaESingleInnerRadius();
		fRingWidth = TRexSettings::Get()->GetFCDdeltaESingleRingWidth();
		fStartAngle = TRexSettings::Get()->GetFCDdeltaESingleStartAngle()[fID];
		fSpanningAngle = TRexSettings::Get()->GetFCDdeltaESingleSpanningAngle();
		fStripWidth = TRexSettings::Get()->GetFCDdeltaESingleStripWidth();
		fTransferTo16Strips = TRexSettings::Get()->FCDTransferTo16Strips();
		fEnergyResolution = TRexSettings::Get()->GetFCDdeltaESingleEnergyResolution();
	} else if(fDirection == "backward") {
		fInnerRadius = TRexSettings::Get()->GetBCDdeltaESingleInnerRadius();
		fRingWidth = TRexSettings::Get()->GetBCDdeltaESingleRingWidth();
		fStartAngle = TRexSettings::Get()->GetBCDdeltaESingleStartAngle()[fID];
		fSpanningAngle = TRexSettings::Get()->GetBCDdeltaESingleSpanningAngle();
		fStripWidth = TRexSettings::Get()->GetBCDdeltaESingleStripWidth();
		fTransferTo16Strips = TRexSettings::Get()->BCDTransferTo16Strips();
		fEnergyResolution = TRexSettings::Get()->GetBCDdeltaESingleEnergyResolution();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}
}

TRexCDdeltaESingleSensitiveDetector::~TRexCDdeltaESingleSensitiveDetector() {
	// TODO Auto-generated destructor stub
	//delete fCDdeltaESingle;
	//delete fHitCollection;
}

// initialize event
void TRexCDdeltaESingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4std::cout << "Initialize sensitive detector" << G4std::endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}


// process hits
G4bool TRexCDdeltaESingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}


G4bool TRexCDdeltaESingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
		G4TouchableHistory* ROHist) {
	// only primary particle hits are considered (no secondaries)
	if(aStep->GetTrack()->GetParentID() != 0 || aStep->GetTotalEnergyDeposit() < 1.*eV) {
		return false;
	}

	TRexHit *hit = new TRexHit(aStep, ROHist);
	fHitCollection->insert(hit);

	//delete hit;
	//TRexHit hit(aStep, ROHist);
	//fHitCollection->insert(&hit);

	return true;
}


// write into root file
void TRexCDdeltaESingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fCDdeltaESingle->ClearParticleMC();

	if(GetTotalEnergyDeposition() > 0) {
		fCDdeltaESingle->ID(fID);

		SetRingsOrStrips("ring");
		SetRingsOrStrips("strip");
	}
}

G4double TRexCDdeltaESingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexCDdeltaESingleSensitiveDetector::GetRingNumber(G4ThreeVector localPos) {
	G4double radius = sqrt(localPos.x() * localPos.x() + localPos.y() * localPos.y());

	return (int)(((radius - fInnerRadius) / fRingWidth) - 1.e-5) / mm ;
}

int TRexCDdeltaESingleSensitiveDetector::GetStripNumber(G4ThreeVector localPos) {
	G4double phi = localPos.phi();

	G4double phiInDet = phi - fStartAngle;

	if(phiInDet < 0) {
		phiInDet += 360*deg;
	}

	if(phiInDet > fSpanningAngle) {
		phiInDet -= 360 * deg;
	}

	int stripNb = (int) (phiInDet / fStripWidth - 1.e-5);

	// transfer from 24 to 16 strips
	if(fTransferTo16Strips) {
		if(stripNb > 3 && stripNb < 20) {
			stripNb = (stripNb - 4) / 2 + 4;
		} else if(stripNb > 19) {
			stripNb -= 8;
		}
	}

	//std::cout <<  "Id = " << fID << ", phi = " << phi / deg << " , phiInDet = " << phiInDet / deg
	//			<< " stripNb(24) = " << stripNb << "\n" << std::endl;

	// forward or backward ????
	if(fDirection == "backward") {
		stripNb = 15 - stripNb;
	}

	return stripNb ;
}

void TRexCDdeltaESingleSensitiveDetector::SetRingsOrStrips(std::string ringOrStrip) {
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

			fCDdeltaESingle->AddStrip(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
		} else if(firstRingOrStripNb != -99 && secondRingOrStripNb != -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
				secondRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fCDdeltaESingle->AddStrip(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
			fCDdeltaESingle->AddStrip(secondRingOrStripNb, secondRingOrStripEnergy / keV, secondRingOrStripA, secondRingOrStripZ,
					secondRingOrStripTrackID, secondRingOrStripTime / ns, secondRingOrStripStopped);
		}
	} else if(ringOrStrip == "ring") {
		if(firstRingOrStripNb != -99 && secondRingOrStripNb == -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fCDdeltaESingle->AddRing(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
		} else if(firstRingOrStripNb != -99 && secondRingOrStripNb != -99) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				firstRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
				secondRingOrStripEnergy += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}

			fCDdeltaESingle->AddRing(firstRingOrStripNb, firstRingOrStripEnergy / keV, firstRingOrStripA, firstRingOrStripZ,
					firstRingOrStripTrackID, firstRingOrStripTime / ns, firstRingOrStripStopped);
			fCDdeltaESingle->AddRing(secondRingOrStripNb, secondRingOrStripEnergy / keV, secondRingOrStripA, secondRingOrStripZ,
					secondRingOrStripTrackID, secondRingOrStripTime / ns, secondRingOrStripStopped);
		}
	} else {
		std::cout << "Error: CDdeltaESingleSensitiveDetector: choose between ring or strip" << std::endl;
	}
}

int TRexCDdeltaESingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
	// set default value resKinEnergy (residual energy of punch through particles)
	resKinEnergy = -100.;

	// check if particle  is primary
	if((*fHitCollection)[hitIndex]->GetParentID() != 0)
		return -3;

	// check if the hitIndex is the last particle hit
	bool isLastHit;
	if(hitIndex == fHitCollection->entries() - 1) {
		isLastHit = true;
	} else if(fabs((*fHitCollection)[hitIndex]->GetVertexKineticEnergy() - (*fHitCollection)[hitIndex + 1]->GetVertexKineticEnergy()) < 0.001*eV ) {
		isLastHit = false;
	} else {
		isLastHit = true;
	}

	if(isLastHit == false) {
		return -2;
	}

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
