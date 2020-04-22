/*
 * TRexCDErestSingle.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDERESTSINGLE_HH_
#define TREXCDERESTSINGLE_HH_

#include "TRexBaseDetector.hh"
#include "TRexMaterials.hh"
#include "TRexCDErestSingleSensitiveDetector.hh"
#include "TRexColour.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"

#include <string>
#include <vector>

class TRexCDErestSingle : public TRexBaseDetector {
	public:
		TRexCDErestSingle();
		TRexCDErestSingle(std::string name, std::string direction, int id);
		virtual ~TRexCDErestSingle();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		ParticleMC* GetParticleMC() { return fCDErestSingleSensitiveDetector->GetParticleMC(); }
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		void ConstructSilicon(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		void ConstructPCB(G4LogicalVolume* experimentalHall_log);
		void ConstructDeadLayer(G4LogicalVolume* experimentalHall_log);

		TRexCDErestSingleSensitiveDetector* fCDErestSingleSensitiveDetector;

		G4double fInnerRadiusDetector;
		G4double fOuterRadiusDetector;
		G4double fThicknessDetector;
		G4double fStartAngleDetector;
		G4double fSpanningAngleDetector;
		G4double fDeadLayer;

		G4ThreeVector fPos;
};

#endif /* TREXCDEREST_HH_ */
