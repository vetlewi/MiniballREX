/*
 * TRexVacuumChamberCylinder.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXVACUUMCHAMBERCYLINDER_HH_
#define TREXVACUUMCHAMBERCYLINDER_HH_

#include "TRexVacuumChamber.hh"
#include "TRexMaterials.hh"
#include "TRexColour.hh"

#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

class TRexVacuumChamberCylinder : public TRexVacuumChamber {
	public:
		TRexVacuumChamberCylinder();
		virtual ~TRexVacuumChamberCylinder();

		void ConstructChamber(G4LogicalVolume* experimentalHall_log);

	private:

};

#endif /* TREXVACUUMCHAMBERCYLINDER_HH_ */
