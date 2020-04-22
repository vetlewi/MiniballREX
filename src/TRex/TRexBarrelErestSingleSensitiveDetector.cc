/*
 * TRexBarrelErestSingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrelErestSingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexBarrelErestSingleSensitiveDetector::TRexBarrelErestSingleSensitiveDetector() {
//}

TRexBarrelErestSingleSensitiveDetector::TRexBarrelErestSingleSensitiveDetector(G4String name, G4String direction, int id):
	G4VSensitiveDetector(name),
	fDirection(direction),
	fID(0)
{
	fCollectionID =-1;
	fName = name;
	fID = id;

	// TODO Auto-generated constructor stub
	collectionName.insert("Collection" + name);

	fBarrelErestSingle = new ParticleMC();

	if(fDirection == "forward") {
		fEnergyResolution = TRexSettings::Get()->GetFBarrelErestSingleEnergyResolution();
	} else if(fDirection == "middle") {
		fEnergyResolution = TRexSettings::Get()->GetMBarrelErestSingleEnergyResolution();
	} else if(fDirection == "backward") {
		fEnergyResolution = TRexSettings::Get()->GetBBarrelErestSingleEnergyResolution();
	} else {
		std::cerr << "Direction " << fDirection << " is wrong! Use forward, middle or backward." << std::endl;
	}
}

TRexBarrelErestSingleSensitiveDetector::~TRexBarrelErestSingleSensitiveDetector() {
	// TODO Auto-generated destructor stub
  
  delete fBarrelErestSingle;
  //delete fHitCollection;
}

// initialize event
void TRexBarrelErestSingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
  //G4std::cout << "Initialize sensitive detector" << G4std::endl;

  fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

  if(fCollectionID < 0) {
	  fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  }

  HCE->AddHitsCollection(fCollectionID, fHitCollection);
}


// process hits
G4bool TRexBarrelErestSingleSensitiveDetector::ProcessHits(G4Step *aStep,
				      G4TouchableHistory *ROHist) {
  return ProcessHits_constStep(aStep, ROHist);
}


G4bool TRexBarrelErestSingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
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
void TRexBarrelErestSingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fBarrelErestSingle->ClearParticleMC();

	G4double totalEnergy = GetTotalEnergyDeposition();

	//G4std::cout << "NbOfHits = " << fHitCollection->entries() << G4std::endl;
	//G4std::cout << "Deposited energy = " << totalEnergy / keV << G4std::endl;

	if(GetTotalEnergyDeposition() > 0) {
		fBarrelErestSingle->ID(fID);

		if(TRexSettings::Get()->IncludeEnergyResolution()) {
			fBarrelErestSingle->SetEdet((totalEnergy + CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV) / keV);
		} else {
			fBarrelErestSingle->SetEdet(totalEnergy / keV);
		}

		if(fHitCollection->entries() > 0) {
			fBarrelErestSingle->SetTime((*fHitCollection)[0]->GetTime() / ns);
			fBarrelErestSingle->SetZ((*fHitCollection)[0]->GetParticleZ());
			fBarrelErestSingle->SetA((*fHitCollection)[0]->GetParticleA());
			fBarrelErestSingle->SetTrackID((*fHitCollection)[0]->GetTrackID());

			double resKinEnergy;
			fBarrelErestSingle->SetStopped(IsStopped(fHitCollection->entries() - 1, resKinEnergy));
			fBarrelErestSingle->SetResKinEnergy(resKinEnergy);
		} else {
			fBarrelErestSingle->SetStopped(-10);
		}
	}
}

G4double TRexBarrelErestSingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexBarrelErestSingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
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
  }  else {
    // not stopped
    return 0;
  }
}
