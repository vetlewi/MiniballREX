/*
 * TRexBarrelErest.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXBARRELEREST_HH_
#define TREXBARRELEREST_HH_

#include "TRexBaseDetector.hh"
#include "TRexBarrelErestSingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexBarrelErest : public TRexBaseDetector {
	public:
		TRexBarrelErest();
		TRexBarrelErest(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexBarrelErest();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexBarrelErestSingle*> fBarrelErestSingles;
};

#endif /* TREXBARRELEREST_HH_ */
