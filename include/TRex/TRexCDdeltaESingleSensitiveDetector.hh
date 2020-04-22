/*
 * TRexCDdeltaESingleSensitiveDetector.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDDELTAESINGLESENSITIVEDETECTOR_HH_
#define TREXCDDELTAESINGLESENSITIVEDETECTOR_HH_

#include "TRexHit.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4AffineTransform.hh"

#include "Randomize.hh"

#include "TTree.h"

#include <string>

class TRexCDdeltaESingleSensitiveDetector  : public G4VSensitiveDetector {
	public:
		//TRexCDdeltaESensitiveDetector();
		TRexCDdeltaESingleSensitiveDetector(G4String name, G4String direction, int id);
		virtual ~TRexCDdeltaESingleSensitiveDetector();

		// initialize hit collection
		void Initialize(G4HCofThisEvent*);

		G4bool ProcessHits(G4Step*, G4TouchableHistory*);

		G4bool ProcessHits_constStep(const G4Step * aStep, G4TouchableHistory*);

		// to write the data into a root file
		void EndOfEvent(G4HCofThisEvent*);

		ParticleMC* GetParticleMC() { return fCDdeltaESingle; }

	private:
		G4double GetTotalEnergyDeposition();
		int GetRingNumber(G4ThreeVector localPos);
		int GetStripNumber(G4ThreeVector localPos);
		void SetRingsOrStrips(std::string ringOrStrip);
		int IsStopped(int hitIndex, double &resKinEnergy);

		G4String fName;
		G4String fDirection;
		int fID;

		G4double fInnerRadius;
		G4double fRingWidth;
		G4double fStartAngle;
		G4double fSpanningAngle;
		G4double fStripWidth;
		int fTransferTo16Strips;
		G4double fEnergyResolution;

		TRexHitsCollection* fHitCollection;
		G4int fCollectionID;

		ParticleMC* fCDdeltaESingle;
};

#endif /* TREXCDDELTAESINGLESENSITIVEDETECTOR_HH_ */
