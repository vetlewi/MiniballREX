/*
 * TRexTrapezoidErestSingleSensitiveDetector.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXTRAPEZOIDERESTSINGLESENSITIVEDETECTOR_HH_
#define TREXTRAPEZOIDERESTSINGLESENSITIVEDETECTOR_HH_

#include "TRexHit.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4AffineTransform.hh"

#include "Randomize.hh"

#include "TTree.h"
#include "TFile.h"
#include "TH2F.h"

#include <string>

class TRexTrapezoidErestSingleSensitiveDetector  : public G4VSensitiveDetector {
	public:
		//TRexTrapezoidErestSensitiveDetector();
		TRexTrapezoidErestSingleSensitiveDetector(G4String name, G4String direction, int id);
		virtual ~TRexTrapezoidErestSingleSensitiveDetector();

		// initialize hit collection
		void Initialize(G4HCofThisEvent*);

		G4bool ProcessHits(G4Step*, G4TouchableHistory*);

		G4bool ProcessHits_constStep(const G4Step * aStep, G4TouchableHistory*);

		// to write the data into a root file
		void EndOfEvent(G4HCofThisEvent*);

		ParticleMC* GetParticleMC() { return fTrapezoidErestSingle; }

	private:
		G4double GetTotalEnergyDeposition();
		int GetRingNumber(G4ThreeVector localPos);
		int GetStripNumber(G4ThreeVector localPos);
		void SetRingsOrStrips(std::string ringOrStrip);
		int IsStopped(int hitIndex, double &resKinEnergy);

		G4double fDetectorInnerRadius;
		G4double fDetectorOuterRadius;
		G4double fBaseLarge;
		G4double fBaseSmall;
		G4double fLength;
		G4double fDetectorDeltaZ;

		G4double fTotalDeltaPhi;
		G4double fRingWidth;
		G4double fStripWidth;
		int fNbOfRings;
		int fNbOfStrips;

		G4String fName;
		G4String fDirection;
		int fID;

		G4double fEnergyResolution;

		TRexHitsCollection* fHitCollection;
		G4int fCollectionID;

		ParticleMC* fTrapezoidErestSingle;
};

#endif /* TREXTRAPEZOIDERESTSINGLESITIVEDETECTOR_HH_ */
