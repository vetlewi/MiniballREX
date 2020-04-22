/*
 * TRexTrapezoidDeltaE.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXTRAPEZOIDDELTAE_HH_
#define TREXTRAPEZOIDDELTAE_HH_

#include "TRexBaseDetector.hh"
#include "TRexTrapezoidDeltaESingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexTrapezoidDeltaE : public TRexBaseDetector {
	public:
		TRexTrapezoidDeltaE();
		TRexTrapezoidDeltaE(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexTrapezoidDeltaE();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexTrapezoidDeltaESingle*> fTrapezoidDeltaESingles;
};

#endif /* TREXBARRELDELTAE_HH_ */
