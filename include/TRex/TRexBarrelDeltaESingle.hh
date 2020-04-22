/*
 * TRexBarrelDeltaESingle.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARRELDELTAESINGLE_HH_
#define TREXBARRELDELTAESINGLE_HH_

#include "TRexBaseDetector.hh"
#include "TRexMaterials.hh"
#include "TRexBarrelDeltaESingleSensitiveDetector.hh"
#include "TRexColour.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"

#include <vector>
#include <string>

class TRexBarrelDeltaESingle : public TRexBaseDetector {
	public:
		TRexBarrelDeltaESingle();
		TRexBarrelDeltaESingle(std::string name, std::string direction, int id);
		virtual ~TRexBarrelDeltaESingle();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		ParticleMC* GetParticleMC() {return fBarrelDeltaESingleSensitiveDetector->GetParticleMC(); };
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		void ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		void ConstructPCB(G4LogicalVolume* experimentalHall_log);
		void ConstructDeadLayer(G4LogicalVolume* experimentalHall_log);
		void ConstructFoil(G4LogicalVolume* experimentalHall_log);

		TRexBarrelDeltaESingleSensitiveDetector* fBarrelDeltaESingleSensitiveDetector;

		G4double fDetectorLengthX;
		G4double fDetectorLengthY;
		G4double fThicknessDetector;
		G4double fStartAngleDetector;
		G4double fDeadLayer;
		G4double fFoilThickness;

		G4ThreeVector fPos;
		G4RotationMatrix* fRotMatrix;
		G4RotationMatrix* fRotMatrixPcb;
};

#endif /* TREXBARRELDELTAESINGLE_HH_ */
