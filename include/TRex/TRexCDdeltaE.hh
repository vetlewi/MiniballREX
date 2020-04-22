/*
 * TRexCDdeltaE.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDDELTAE_HH_
#define TREXCDDELTAE_HH_

#include "TRexBaseDetector.hh"
#include "TRexCDdeltaESingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexCDdeltaE : public TRexBaseDetector {
	public:
		TRexCDdeltaE();
		TRexCDdeltaE(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexCDdeltaE();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexCDdeltaESingle*> fCDdeltaESingles;
};

#endif /* TREXCDDELTAE_HH_ */
