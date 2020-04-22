/*
 * TRexVacuumChamberGasCylinder.hh
 *
 *  Created on: Jan 31, 2017
 *      Author: vbildste
 */

#ifndef TREXVACUUMCHAMBERGASCYLINDER_HH_
#define TREXVACUUMCHAMBERGASCYLINDER_HH_

#include "TRexVacuumChamberGas.hh"
#include "TRexMaterials.hh"
#include "TRexColour.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

class TRexVacuumChamberGasCylinder : public TRexVacuumChamberGas {
	public:
		TRexVacuumChamberGasCylinder();
		~TRexVacuumChamberGasCylinder();

		G4LogicalVolume* ConstructChamberGas(G4LogicalVolume* experimentalHall_log);

	private:

};

#endif /* TREXVACUUMCHAMBERGASCYLINDER_HH_ */
