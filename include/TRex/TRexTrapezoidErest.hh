/*
 * TRexTrapezoidErest.shh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXTRAPEZOIDEREST_HH_
#define TREXTRAPEZOIDEREST_HH_

#include "TRexBaseDetector.hh"
#include "TRexTrapezoidErestSingle.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexTrapezoidErest : public TRexBaseDetector {
	public:
		TRexTrapezoidErest();
		TRexTrapezoidErest(std::string name, std::string direction, int nbOfSingles);
		virtual ~TRexTrapezoidErest();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		int fNbOfSingles;
		std::vector<TRexTrapezoidErestSingle*> fTrapezoidErestSingles;
};

#endif /* TREXTRAPEZOIDEREST_HH_ */
