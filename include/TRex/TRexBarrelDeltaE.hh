/*
 * TRexBarrelDeltaE.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARRELDELTAE_HH_
#define TREXBARRELDELTAE_HH_

#include "TRexBaseDetector.hh"
#include "TRexBarrelDeltaESingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexBarrelDeltaE : public TRexBaseDetector {
	public:
		TRexBarrelDeltaE();
		TRexBarrelDeltaE(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexBarrelDeltaE();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexBarrelDeltaESingle*> fBarrelDeltaESingles;
};

#endif /* TREXBARRELDELTAE_HH_ */
