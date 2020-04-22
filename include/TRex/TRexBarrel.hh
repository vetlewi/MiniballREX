/*
 * TRexBarrel.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARREL_HH_
#define TREXBARREL_HH_

#include "TRexBaseDetector.hh"
#include "TRexBarrelDeltaE.hh"
#include "TRexBarrelErest.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexBarrel : public TRexBaseDetector {
	public:
		TRexBarrel();
		TRexBarrel(std::string name, std::string direction, int nbOfTelescopes);
		virtual ~TRexBarrel();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		std::string fDirection;
		int fNbOfTelescopes;

		TRexBarrelDeltaE* fBarrelDeltaE;
		TRexBarrelErest* fBarrelErest;
};

#endif /* TREXBARREL_HH_ */
