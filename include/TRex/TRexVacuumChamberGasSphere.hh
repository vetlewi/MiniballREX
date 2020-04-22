/*
 * TRexVacuumChamberGasSphere.hh
 *
 *  Created on: Jan 31, 2017
 *      Author: vbildste
 */

#ifndef TREXVACUUMCHAMBERGASSHPERE_HH_
#define TREXVACUUMCHAMBERGASSHPERE_HH_

#include "TRexVacuumChamberGas.hh"
#include "TRexMaterials.hh"
#include "TRexColour.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

class TRexVacuumChamberGasSphere : public TRexVacuumChamberGas {
	public:
		TRexVacuumChamberGasSphere();
		~TRexVacuumChamberGasSphere();

		G4LogicalVolume* ConstructChamberGas(G4LogicalVolume* experimentalHall_log);

	private:

};

#endif /* TREXVACUUMCHAMBERGASSHPERE_HH_ */
