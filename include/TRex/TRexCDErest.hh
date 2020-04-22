/*
 * TRexCDErest.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCDEREST_HH_
#define TREXCDEREST_HH_

#include "TRexBaseDetector.hh"
#include "TRexCDErestSingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexCDErest : public TRexBaseDetector {
	public:
		TRexCDErest();
		TRexCDErest(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexCDErest();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexCDErestSingle*> fCDErestSingles;
};

#endif /* TREXCDEREST_HH_ */
