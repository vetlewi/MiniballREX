/*
 * TRexBarrelErestSingle.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARRELERESTSINGLE_HH_
#define TREXBARRELERESTSINGLE_HH_

#include "TRexBaseDetector.hh"
#include "TRexMaterials.hh"
#include "TRexBarrelErestSingleSensitiveDetector.hh"
#include "TRexColour.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"

#include <string>
#include <vector>

class TRexBarrelErestSingle : public TRexBaseDetector {
	public:
		TRexBarrelErestSingle();
		TRexBarrelErestSingle(std::string name, std::string direction, int id);
		virtual ~TRexBarrelErestSingle();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		ParticleMC* GetParticleMC() { return fBarrelErestSingleSensitiveDetector->GetParticleMC(); }
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		void ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		void ConstructPCB(G4LogicalVolume* experimentalHall_log);
		void ConstructDeadLayer(G4LogicalVolume* experimentalHall_log);

		TRexBarrelErestSingleSensitiveDetector* fBarrelErestSingleSensitiveDetector;

		G4double fDetectorLengthX;
		G4double fDetectorLengthY;
		G4double fThicknessDetector;
		G4double fStartAngleDetector;
		G4double fDeadLayer;

		G4ThreeVector fPos;
		G4RotationMatrix* fRotMatrix;
		G4RotationMatrix* fRotMatrixPcb;
};

#endif /* TREXBARRELEREST_HH_ */
