/*
 * TRexVacuumChamberGas.hh
 *
 *  Created on: Jan 31, 2017
 *      Author: vbildste
 */

#ifndef TREXVACUUMCHAMBERGAS_HH_
#define TREXVACUUMCHAMBERGAS_HH_

#include "TRexMaterials.hh"
#include "TRexColour.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

class TRexVacuumChamberGas {
	public:
		TRexVacuumChamberGas();
		virtual ~TRexVacuumChamberGas();

		virtual G4LogicalVolume* ConstructChamberGas(G4LogicalVolume*) { return NULL; }

	protected:
};

#endif /* TREXVACUUMCHAMBERGAS_HH_ */
