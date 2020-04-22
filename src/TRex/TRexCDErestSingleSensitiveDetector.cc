/*
 * TRexCDErestSingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexCDErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexCDErestSingleSensitiveDetector::TRexCDErestSingleSensitiveDetector() {
//}

TRexCDErestSingleSensitiveDetector::TRexCDErestSingleSensitiveDetector(G4String name, G4String direction, int id) :
	G4VSensitiveDetector(name)
{
	fName = name;
	fID = id;
	fDirection = direction;
	fCollectionID = -1;

	// TODO Auto-generated constructor stub
	collectionName.insert("Collection" + name);

	fCDErestSingle = new ParticleMC();

	if(fDirection == "forward") {
		fEnergyResolution = TRexSettings::Get()->GetFCDErestSingleEnergyResolution();
	} else if(fDirection == "backward") {
		fEnergyResolution = TRexSettings::Get()->GetBCDErestSingleEnergyResolution();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward or backward." << std::endl;
	}
}

TRexCDErestSingleSensitiveDetector::~TRexCDErestSingleSensitiveDetector() {
	// TODO Auto-generated destructor stub
}

// initialize event
void TRexCDErestSingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4cout << "Initialize sensitive detector" << G4endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}


// process hits
G4bool TRexCDErestSingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}


G4bool TRexCDErestSingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
		G4TouchableHistory* ROHist) {
	// only primary particle hits are considered (no secondaries)
	if(aStep->GetTrack()->GetParentID() != 0 || aStep->GetTotalEnergyDeposit() < 1.*eV) {
		return false;
	}

	TRexHit* hit = new TRexHit(aStep, ROHist);

	fHitCollection->insert(hit);

	return true;
}


// write into root file
void TRexCDErestSingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fCDErestSingle->ClearParticleMC();

	G4double totalEnergy = GetTotalEnergyDeposition();

	//G4cout << "NbOfHits = " << fHitCollection->entries() << G4endl;
	//G4cout << "Deposited energy = " << totalEnergy << G4endl;

	if(GetTotalEnergyDeposition() > 0) {
		fCDErestSingle->ID(fID);

		if(TRexSettings::Get()->IncludeEnergyResolution()) {
			fCDErestSingle->SetEdet((totalEnergy + CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV) / keV);
		} else {
			fCDErestSingle->SetEdet(totalEnergy / keV);
		}

		if(fHitCollection->entries() > 0) {
			fCDErestSingle->SetTime((*fHitCollection)[0]->GetTime() / ns);
			fCDErestSingle->SetZ((*fHitCollection)[0]->GetParticleZ());
			fCDErestSingle->SetA((*fHitCollection)[0]->GetParticleA());
			fCDErestSingle->SetTrackID((*fHitCollection)[0]->GetTrackID());

			double resKinEnergy;
			fCDErestSingle->SetStopped(IsStopped(fHitCollection->entries() - 1, resKinEnergy));
			fCDErestSingle->SetResKinEnergy(resKinEnergy);
		} else {
			fCDErestSingle->SetStopped(-10);
		}
	}
}


G4double TRexCDErestSingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexCDErestSingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
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
