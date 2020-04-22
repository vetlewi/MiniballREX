/*
 * TRexCD.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXTRAPEZOID_HH_
#define TREXTRAPEZOID_HH_

#include "TRexBaseDetector.hh"
#include "TRexTrapezoidDeltaE.hh"
#include "TRexTrapezoidErest.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexTrapezoid : public TRexBaseDetector {
	public:
		TRexTrapezoid();
		TRexTrapezoid(std::string name, std::string direction, int nbOfTelescopes);
		virtual ~TRexTrapezoid();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		std::string fDirection;
		int fNbOfTelescopes;

		TRexTrapezoidDeltaE* fTrapezoidDeltaE;
		TRexTrapezoidErest* fTrapezoidErest;
};

#endif /* TREXTRAPEZOID_HH_ */
