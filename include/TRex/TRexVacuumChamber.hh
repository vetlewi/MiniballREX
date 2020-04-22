/*
 * TRexVacuumChamber.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXVACUUMCHAMBER_HH_
#define TREXVACUUMCHAMBER_HH_

#include "TRexMaterials.hh"
#include "TRexColour.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

class TRexVacuumChamber {
	public:
		TRexVacuumChamber();
		virtual ~TRexVacuumChamber();

		virtual void ConstructChamber(G4LogicalVolume*) {};

	protected:
};

#endif /* TREXVACUUMCHAMBER_HH_ */
