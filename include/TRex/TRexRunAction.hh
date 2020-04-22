/*
 * TRexRunAction.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXRUNACTION_HH_
#define TREXRUNACTION_HH_

#include "TRexData.hh"
#include "TRexPrimaryGeneratorAction.hh"
#include "TRexEventAction.hh"

#include "G4UserRunAction.hh"

#include "TFile.h"
#include "TTree.h"

class TRexRunAction : public G4UserRunAction {
	public:
		TRexRunAction();
		TRexRunAction(TRexData &data,TRexPrimaryGeneratorAction* generator, TRexEventAction* eventAction);

		virtual ~TRexRunAction();

		// processed every time a run starts
		void BeginOfRunAction(const G4Run*);

		// processed every time a run ends
		void EndOfRunAction(const G4Run*);


	private:
		TRexData fData;

		TRexPrimaryGeneratorAction* fGenerator;
		TRexEventAction* fEventAction;

		TFile* fOutputFile;
		TTree* fGeneratorTree;
		TTree* fDetectorTree;
};

#endif /* TREXRUNACTION_HH_ */
