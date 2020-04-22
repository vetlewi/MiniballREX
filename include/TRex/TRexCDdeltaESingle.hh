/*
 * TRexCDErestSingle.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDDELTAESINGLE_HH_
#define TREXCDDELTAESINGLE_HH_

#include "TRexBaseDetector.hh"
#include "TRexMaterials.hh"
#include "TRexCDdeltaESingleSensitiveDetector.hh"
#include "TRexColour.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"

#include <vector>
#include <string>

class TRexCDdeltaESingle : public TRexBaseDetector {
	public:
		TRexCDdeltaESingle();
		TRexCDdeltaESingle(std::string name, std::string direction, int id);
		virtual ~TRexCDdeltaESingle();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		ParticleMC* GetParticleMC() { return fCDdeltaESingleSensitiveDetector->GetParticleMC(); }
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		void ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		void ConstructPCB(G4LogicalVolume* experimentalHall_log);
		void ConstructDeadLayer(G4LogicalVolume* experimentalHall_log);
		void ConstructFoil(G4LogicalVolume* experimentalHall_log);

		TRexCDdeltaESingleSensitiveDetector* fCDdeltaESingleSensitiveDetector;

		G4double fInnerRadiusDetector;
		G4double fOuterRadiusDetector;
		G4double fThicknessDetector;
		G4double fStartAngleDetector;
		G4double fSpanningAngleDetector;
		G4double fDeadLayer;
		G4double fFoilThickness;

		G4ThreeVector fPos;
};

#endif /* TREXCDDELTAESINGLE_HH_ */
