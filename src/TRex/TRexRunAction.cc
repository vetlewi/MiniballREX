/*
 * TRexRunAction.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexRunAction.hh"
#include "TRex/TRexSettings.hh"

TRexRunAction::TRexRunAction() {
}

TRexRunAction::TRexRunAction(TRexData &data, TRexPrimaryGeneratorAction* generator, TRexEventAction* eventAction) :
	fData(data), fGenerator(generator), fEventAction(eventAction) {
}

TRexRunAction::~TRexRunAction() {
	// TODO Auto-generated destructor stub
}

void TRexRunAction::BeginOfRunAction(const G4Run*) {
	// open result Root file
	fOutputFile = new TFile(fData.GetOutputFileName().c_str(), "recreate");
	fOutputFile->cd();

	// create trees
	fGeneratorTree = new TTree("treeGen", "Primary generator tree");
	fDetectorTree = new TTree("treeDet", "Detector tree");

	// set the trees
	fGenerator->SetTree(fGeneratorTree);
	fEventAction->SetTree(fDetectorTree);
	fEventAction->CreateBranches();

	// write the settings
	TRexSettings::Get()->Write("settings",TObject::kOverwrite);
}


void TRexRunAction::EndOfRunAction(const G4Run*) {
	fOutputFile->cd();
	fGeneratorTree->Write();
	fDetectorTree->Write();

	fOutputFile->Close();
}
