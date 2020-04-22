/*
 * TRexTrapezoidErestSingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTrapezoidErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexTrapezoidErestSingleSensitiveDetector::TRexTrapezoidErestSingleSensitiveDetector() {
//}

TRexTrapezoidErestSingleSensitiveDetector::TRexTrapezoidErestSingleSensitiveDetector(G4String name, G4String direction, int id) :
	G4VSensitiveDetector(name) {
	fName = name;
	fDirection = direction;
	fID = id;
	fCollectionID = -1;

	collectionName.insert("Collection" + name);

	fTrapezoidErestSingle = new ParticleMC();

	if(fDirection == "forward") {
		fEnergyResolution = TRexSettings::Get()->GetFTrapezoidErestSingleEnergyResolution();
	} else if(fDirection == "backward") {
		fEnergyResolution = TRexSettings::Get()->GetBTrapezoidErestSingleEnergyResolution();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}
}

TRexTrapezoidErestSingleSensitiveDetector::~TRexTrapezoidErestSingleSensitiveDetector() {
	// TODO Auto-generated destructor stub
}

// initialize event
void TRexTrapezoidErestSingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4std::cout << "Initialize sensitive detector" << G4std::endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}


// process hits
G4bool TRexTrapezoidErestSingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}


G4bool TRexTrapezoidErestSingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
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
void TRexTrapezoidErestSingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fTrapezoidErestSingle->ClearParticleMC();

	G4double totalEnergy = GetTotalEnergyDeposition();

	if(GetTotalEnergyDeposition() > 0) {
		fTrapezoidErestSingle->ID(fID);

		if(TRexSettings::Get()->IncludeEnergyResolution()) {
			fTrapezoidErestSingle->SetEdet((totalEnergy + CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV) / keV);
		} else {
			fTrapezoidErestSingle->SetEdet(totalEnergy / keV);
		}

		if(fHitCollection->entries() > 0) {
			fTrapezoidErestSingle->SetTime((*fHitCollection)[0]->GetTime() / ns);
			fTrapezoidErestSingle->SetZ((*fHitCollection)[0]->GetParticleZ());
			fTrapezoidErestSingle->SetA((*fHitCollection)[0]->GetParticleA());
			fTrapezoidErestSingle->SetTrackID((*fHitCollection)[0]->GetTrackID());

			double resKinEnergy;
			fTrapezoidErestSingle->SetStopped(IsStopped(fHitCollection->entries() - 1, resKinEnergy));
			fTrapezoidErestSingle->SetResKinEnergy(resKinEnergy);
		} else {
			fTrapezoidErestSingle->SetStopped(-10);
		}
	}
}

G4double TRexTrapezoidErestSingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}


int TRexTrapezoidErestSingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
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
