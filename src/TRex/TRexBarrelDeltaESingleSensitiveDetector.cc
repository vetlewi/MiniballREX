/*
 * TRexBarrelDeltaESingleSensitiveDetector.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBarrelDeltaESingleSensitiveDetector.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>

//TRexBarrelDeltaESingleSensitiveDetector::TRexBarrelDeltaESingleSensitiveDetector() {
//}

TRexBarrelDeltaESingleSensitiveDetector::TRexBarrelDeltaESingleSensitiveDetector(G4String name, G4String direction, int id):
	G4VSensitiveDetector(name) {
	fName = name;
	fDirection = direction;
	fID = id;
	fCollectionID = -1;

	fBaseName = fName;
	fBaseName.erase(fBaseName.end()-1, fBaseName.end());

	collectionName.insert("Collection" + name);

	fBarrelDeltaESingle = new ParticleMC();

	if(fBaseName == "FBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetFBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetFBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetFBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetFBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "SecondFBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetSecondFBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetSecondFBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetSecondFBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetSecondFBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "MBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetMBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetMBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetMBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetMBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "BBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetBBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetBBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetBBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetBBarrelDeltaESingleEnergyResolution();
	} else if(fBaseName == "SecondBBarrelDeltaESingle") {
		fLengthX = TRexSettings::Get()->GetSecondBBarrelDeltaESingleLengthX();
		fLengthY = TRexSettings::Get()->GetSecondBBarrelDeltaESingleLengthY();
		fStripWidth = TRexSettings::Get()->GetSecondBBarrelDeltaESingleStripWidth();
		fEnergyResolution = TRexSettings::Get()->GetSecondBBarrelDeltaESingleEnergyResolution();
	} else {
		std::cerr<<"Detector Name "<<fBaseName<<" is wrong!"<<std::endl;
	}

	//histoXvsY = new TH2F(Form("histoXvsY_%d", fID), "histoXvsY", 600, -30, 30, 700, 0, 70);
	//histoZ = new TH1F(Form("histoZ_%d", fID), "histoZ", 500, 0, 50);
}

TRexBarrelDeltaESingleSensitiveDetector::~TRexBarrelDeltaESingleSensitiveDetector() {
	// TODO Auto-generated destructor stub

	//histoXvsY->SaveAs(Form("histoXvsY_%d.root", fID));
	//histoZ->SaveAs(Form("histoZ_%d.root", fID));

	delete fBarrelDeltaESingle;
	//delete fHitCollection;
}

// initialize event
void TRexBarrelDeltaESingleSensitiveDetector::Initialize(G4HCofThisEvent *HCE) {
	//G4std::cout<<"Initialize sensitive detector"<<G4std::endl;

	fHitCollection = new TRexHitsCollection(SensitiveDetectorName, collectionName[0]);

	if(fCollectionID < 0) {
		fCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
	}

	HCE->AddHitsCollection(fCollectionID, fHitCollection);
}

// process hits
G4bool TRexBarrelDeltaESingleSensitiveDetector::ProcessHits(G4Step *aStep,
		G4TouchableHistory *ROHist) {
	return ProcessHits_constStep(aStep, ROHist);
}

G4bool TRexBarrelDeltaESingleSensitiveDetector::ProcessHits_constStep(const G4Step * aStep,
		G4TouchableHistory* ROHist) {
	// only primary particle hits are considered (no secondaries)
	if(aStep->GetTrack()->GetParentID() != 0 || aStep->GetTotalEnergyDeposit() < 1.*eV) {
		return false;
	}

	TRexHit *hit = new TRexHit(aStep, ROHist);
	fHitCollection->insert(hit);
	//TRexHit hit(aStep, ROHist);
	//fHitCollection->insert(&hit);

	return true;
}

// write into root file
void TRexBarrelDeltaESingleSensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
	// clear old event
	fBarrelDeltaESingle->ClearParticleMC();

	if(GetTotalEnergyDeposition() > 0) {
		fBarrelDeltaESingle->ID(fID);

		double resEnergy;

		// initialize strips
		// in the following strips are perpendicular to the beam direction,
		// and rings are parallel to the beam direction
		std::vector<int> stripNb;
		std::vector<G4double> stripEnergy;
		std::vector<int> stripA;
		std::vector<int> stripZ;
		std::vector<int> stripTrackID;
		std::vector<G4double> stripTime;
		std::vector<int> stripStopped;
		std::vector<int> ringNb;
		std::vector<G4double> ringEnergy;
		std::vector<int> ringA;
		std::vector<int> ringZ;
		std::vector<int> ringTrackID;
		std::vector<G4double> ringTime;
		std::vector<int> ringStopped;

		int currentStripNb = -1;
		int currentRingNb = -1;
		double posAlongStrip = -99.;

		for(int i = 0; i < fHitCollection->entries(); i++) {
			currentStripNb = GetStripNumber((*fHitCollection)[i]->GetLocalHitPosition());
			if(TRexSettings::Get()->ResistiveStrips()) {
				posAlongStrip = ((*fHitCollection)[i]->GetLocalHitPosition().y() + fLengthX / 2.) / fLengthX;
			} else {
				currentRingNb = GetRingNumber((*fHitCollection)[i]->GetLocalHitPosition());
			}

			//loop over the strips perpendicular to the beam we already have and see if we can find the current one
			size_t j;
			for(j = 0; j < stripNb.size(); ++j) {
				//same strip number
				if(currentStripNb == stripNb[j]) {
					if(TRexSettings::Get()->ResistiveStrips()) {
						stripEnergy[j] += (*fHitCollection)[i]->GetEnergyDeposition() * posAlongStrip;
						break;
					} else {
						stripEnergy[j] += (*fHitCollection)[i]->GetEnergyDeposition();
						break;
					}
				}
			}
			if(j == stripNb.size()) {
				//new strip
				stripNb.push_back(currentStripNb);
				if(TRexSettings::Get()->ResistiveStrips()) {
					stripEnergy.push_back((*fHitCollection)[i]->GetEnergyDeposition() * posAlongStrip);
				} else {
					stripEnergy.push_back((*fHitCollection)[i]->GetEnergyDeposition());
				}
				stripA.push_back((*fHitCollection)[i]->GetParticleA());
				stripZ.push_back((*fHitCollection)[i]->GetParticleZ());
				stripTrackID.push_back((*fHitCollection)[i]->GetTrackID());
				stripTime.push_back((*fHitCollection)[i]->GetTime());
				stripStopped.push_back(IsStopped(i, resEnergy));
			}
			// for double-sided strip detectors we have to do the same for the strips parallel to the beam (called rings here)
			if(!TRexSettings::Get()->ResistiveStrips()) {
				//loop over the strips perpendicular to the beam we already have and see if we can find the current one
				size_t j;
				for(j = 0; j < ringNb.size(); ++j) {
					//same ring number
					if(currentRingNb == ringNb[j]) {
						ringEnergy[j] += (*fHitCollection)[i]->GetEnergyDeposition();
						break;
					}
				}
				if(j == ringNb.size()) {
					//new ring
					ringNb.push_back(currentRingNb);
					if(TRexSettings::Get()->ResistiveStrips()) {
						ringEnergy.push_back((*fHitCollection)[i]->GetEnergyDeposition() * posAlongStrip);
					} else {
						ringEnergy.push_back((*fHitCollection)[i]->GetEnergyDeposition());
					}
					ringA.push_back((*fHitCollection)[i]->GetParticleA());
					ringZ.push_back((*fHitCollection)[i]->GetParticleZ());
					ringTrackID.push_back((*fHitCollection)[i]->GetTrackID());
					ringTime.push_back((*fHitCollection)[i]->GetTime());
					ringStopped.push_back(IsStopped(i, resEnergy));
				}
			}
		}

		// loop over all strips we've found and add them
		for(size_t i = 0; i < stripNb.size(); ++i) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
					stripEnergy[i] += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}
			fBarrelDeltaESingle->AddStrip(stripNb[i], stripEnergy[i]/keV, stripA[i], stripZ[i], stripTrackID[i], stripTime[i], stripStopped[i]);
		}

		// loop over all rings we've found and add them
		for(size_t i = 0; i < ringNb.size(); ++i) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
					ringEnergy[i] += CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV;
			}
			fBarrelDeltaESingle->AddRing(ringNb[i], ringEnergy[i]/keV, ringA[i], ringZ[i], ringTrackID[i], ringTime[i], ringStopped[i]);
		}

		// for a resistive strip detector we set the energy of the rear to the total energy deposited
		if(fHitCollection->entries() > 0 && TRexSettings::Get()->ResistiveStrips()) {
			if(TRexSettings::Get()->IncludeEnergyResolution()) {
				fBarrelDeltaESingle->SetRear((GetTotalEnergyDeposition() + CLHEP::RandGauss::shoot(0., fEnergyResolution / keV) * keV) / keV);
			} else {
				fBarrelDeltaESingle->SetRear(GetTotalEnergyDeposition() / keV);
			}
		}
		//fBarrelDeltaESingle->SetRear(posAlongStrip);
	}
}

G4double TRexBarrelDeltaESingleSensitiveDetector::GetTotalEnergyDeposition() {
	G4double totalEnergy = 0.;

	// loop over all hits
	for(G4int i = 0; i < fHitCollection->entries(); i++) {
		totalEnergy += (*fHitCollection)[i]->GetEnergyDeposition();
	}

	return totalEnergy;
}

int TRexBarrelDeltaESingleSensitiveDetector::GetStripNumber(G4ThreeVector localPos) {
	// this is the strip number for strips perpendicular to the beam
	G4double z;
	int stripNb = -1;

	if(fDirection == "forward") {
		z = localPos.z() + fLengthY / 2.;
	} else if(fDirection == "middle") {
		z = localPos.z() - fLengthY / 2.;
	} else {
		z = localPos.z() - fLengthY / 2.;
	}

	z = fabs(z);
	if(z == fLengthY) {
		//counts on the edge are counted towards the highest strip
		z -= 1e-5;
	}

	stripNb =  static_cast<int>(z/fStripWidth);

	if(stripNb > static_cast<int>(fLengthY/fStripWidth) || stripNb < 0) {
		std::cout<<"Problem: fID = "<<fID<<" , localZ = "<<z<<" , stripNb = "<<stripNb<<std::endl;
		return -1;
	}

	return stripNb ;
}

int TRexBarrelDeltaESingleSensitiveDetector::GetRingNumber(G4ThreeVector localPos) {
	// this is the strip number for strips parallel to the beam
	G4double y;
	int ringNb = -1;

	y = localPos.y() + fLengthX / 2.;
	if(y == fLengthX) {
		//counts on the edge are counted towards the highest ring
		y -= 1e-5;
	}

	ringNb =  static_cast<int>(y/fStripWidth);

	if(ringNb > static_cast<int>(fLengthX/fStripWidth) || ringNb < 0) {
		std::cout<<"Problem: fID = "<<fID<<" , localZ = "<<y<<" , ringNb = "<<ringNb<<std::endl;
		return -1;
	}

	return ringNb ;
}

int TRexBarrelDeltaESingleSensitiveDetector::IsStopped(int hitIndex, double &resKinEnergy) {
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
