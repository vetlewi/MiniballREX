/*
 * TRexCD.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXCD_HH_
#define TREXCD_HH_

#include "TRexBaseDetector.hh"
#include "TRexCDdeltaE.hh"
#include "TRexCDErest.hh"
#include "ParticleMC.hh"
#include "Annular.hh"

#include <vector>
#include <string>

class TRexCD : public TRexBaseDetector {
	public:
		TRexCD();
		TRexCD(std::string name, std::string direction, int nbOfTelescopes);
		virtual ~TRexCD();

		void Construct(G4LogicalVolume* experimentalHall_log, G4SDManager *SDMan);
		std::vector<ParticleMC>* GetParticleMCvector();

	private:
		std::string fDirection;
		int fNbOfTelescopes;

		TRexCDdeltaE* fCDdeltaE;
		TRexCDErest* fCDErest;
};

#endif /* TREXCD_HH_ */
