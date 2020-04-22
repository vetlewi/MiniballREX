/*
 * TRexBarrelDeltaESingleSensitiveDetector.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARRELDELTAESINGLESENSITIVEDETECTOR_HH_
#define TREXBARRELDELTAESINGLESENSITIVEDETECTOR_HH_

#include "TRexHit.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4AffineTransform.hh"

#include "Randomize.hh"

#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"

class TRexBarrelDeltaESingleSensitiveDetector : public G4VSensitiveDetector {
	public:
		//TRexBarrelDeltaESensitiveDetector();
		TRexBarrelDeltaESingleSensitiveDetector(G4String name, G4String direction, int id);
		virtual ~TRexBarrelDeltaESingleSensitiveDetector();

		// initialize hit collection
		void Initialize(G4HCofThisEvent*);

		G4bool ProcessHits(G4Step*, G4TouchableHistory*);

		G4bool ProcessHits_constStep(const G4Step * aStep, G4TouchableHistory*);

		// to write the data into a root file
		void EndOfEvent(G4HCofThisEvent*);

		ParticleMC* GetParticleMC() { return fBarrelDeltaESingle; }

	private:
		G4double GetTotalEnergyDeposition();
		int GetStripNumber(G4ThreeVector localPos);
		int GetRingNumber(G4ThreeVector localPos);
		int IsStopped(int hitIndex, double &resKinEnergy);

		G4String fName;
		G4String fBaseName;
		G4String fDirection;
		int fID;

		G4double fLengthX;
		G4double fLengthY;
		G4double fStripWidth;
		int fTransferTo16Strips;

		G4double fEnergyResolution;

		TRexHitsCollection* fHitCollection;
		G4int fCollectionID;

		ParticleMC* fBarrelDeltaESingle;

		TFile* testFile;
		TH2F* histoXvsY;
		TH1F* histoZ;
};

#endif /* TREXBARRELDELTAESINGLESENSITIVEDETECTOR_HH_ */
