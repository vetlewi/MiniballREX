/*
 * TRexBarrelDeltaESingle.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXTRAPEZOIDDELTAESINGLE_HH_
#define TREXTRAPEZOIDDELTAESINGLE_HH_

#include "TRexBaseDetector.hh"
#include "TRexMaterials.hh"
#include "TRexTrapezoidDeltaESingleSensitiveDetector.hh"
#include "TRexColour.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"

#include <vector>
#include <string>

class TRexTrapezoidDeltaESingle : public TRexBaseDetector {
	public:
		TRexTrapezoidDeltaESingle();
		TRexTrapezoidDeltaESingle(std::string name, std::string direction, int id);
		virtual ~TRexTrapezoidDeltaESingle();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		ParticleMC* GetParticleMC() { return fTrapezoidDeltaESingleSensitiveDetector->GetParticleMC(); }
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		void SetPcbParameters();
		void SetSiliconParameters();
		void SetFoilParameters();
		void ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		void ConstructPCB(G4LogicalVolume* experimentalHall_log);
		void ConstructFoil(G4LogicalVolume* experimentalHall_log);

		TRexTrapezoidDeltaESingleSensitiveDetector* fTrapezoidDeltaESingleSensitiveDetector;

		// Silicon detector
		G4double fDetectorInnerRadius;
		G4double fDetectorOuterRadius;
		G4double fDetectorDeltaZ;
		G4double fThicknessDetector;
		G4double fStartAngleDetector;
		G4double fBaseLarge;
		G4double fBaseSmall;
		G4double fLength;
		G4double fBeta;

		// Pcb
		G4double fPcbOuterRadius;
		G4double fPcbInnerRadius;
		G4double fThicknessPcb;
		G4double fhOutPcb;
		G4double fhInPcb;
		G4double fPcbBaseLarge;
		G4double fPcbBaseSmall;
		G4double fPcbLength;
		G4double fPcbBeta;

		// foil
		G4double fFoilOuterRadius;
		G4double fFoilInnerRadius;
		G4double fFoilThickness;
		G4double fhOutFoil;
		G4double fhInFoil;
		G4double fFoilBaseLarge;
		G4double fFoilBaseSmall;
		G4double fFoilLength;
		G4double fFoilBeta;

		G4double fPosZ;
		G4ThreeVector fPos;
		G4ThreeVector fPcbPos;
		G4ThreeVector fFoilPos;

		G4RotationMatrix* fRotMatrix;
		G4RotationMatrix* fRotMatrixPcb;
		G4RotationMatrix* fRotMatrixFoil;
};

#endif /* TREXBARRELDELTAESINGLE_HH_ */
