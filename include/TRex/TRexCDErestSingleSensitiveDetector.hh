/*
 * TRexCDErestSingleSensitiveDetector.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDERESTSINGLESENSITIVEDETECTOR_HH_
#define TREXCDERESTSINGLESENSITIVEDETECTOR_HH_

#include "TRexHit.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "G4AffineTransform.hh"

#include "Randomize.hh"

#include "TTree.h"

class TRexCDErestSingleSensitiveDetector  : public G4VSensitiveDetector {
	public:
		//TRexCDErestSensitiveDetector();
		TRexCDErestSingleSensitiveDetector(G4String name, G4String direction, int id);
		virtual ~TRexCDErestSingleSensitiveDetector();

		// initialize hit collection
		void Initialize(G4HCofThisEvent*);

		G4bool ProcessHits(G4Step *, G4TouchableHistory*);

		G4bool ProcessHits_constStep(const G4Step * aStep, G4TouchableHistory*);

		// to write the data into a root file
		void EndOfEvent(G4HCofThisEvent*);

		ParticleMC* GetParticleMC() { return fCDErestSingle; }

	private:
		G4double GetTotalEnergyDeposition();
		int IsStopped(int hitIndex, double &resKinEnergy);

		G4String fName;
		G4String fDirection;
		int fID;

		G4double fEnergyResolution;

		TRexHitsCollection* fHitCollection;
		G4int fCollectionID;

		ParticleMC* fCDErestSingle;
};

#endif /* TREXCDERESTSINGLESENSITIVEDETECTOR_HH_ */
