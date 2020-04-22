/*
 * TRexVacuumChamberSphere.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXVACUUMCHAMBERSHPERE_HH_
#define TREXVACUUMCHAMBERSHPERE_HH_

#include "TRexVacuumChamber.hh"
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

class TRexVacuumChamberSphere : public TRexVacuumChamber {
	public:
		TRexVacuumChamberSphere();
		virtual ~TRexVacuumChamberSphere();

		void ConstructChamber(G4LogicalVolume* experimentalHall_log);

	private:

};

#endif /* TREXVACUUMCHAMBERSHPERE_HH_ */
