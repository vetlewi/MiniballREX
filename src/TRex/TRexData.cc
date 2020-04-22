/*
 * TRexData.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexData.hh"
#include "TRex/TRexSettings.hh"

#include <CommandLineInterface/CommandLineInterface.hh>

#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>
#include <globals.hh>

#include <sys/stat.h>
#include <G4UIExecutive.hh>

TRexData::TRexData() :
	fOutputFileName("TRexGeant4.root"), fNbOfEvents(0), fVis(false), fVisCut(false), fInteractive(false) {
		// no visualization or interactive mode by default
}

TRexData::TRexData(int argc, char* argv[]) :
	fOutputFileName("TRexGeant4.root"), fNbOfEvents(0), fVis(false), fVisCut(false), fInteractive(false) {
	// write the command line in the fCommandLine variable
	for(int i = 0; i < argc; i++) {
		std::cout<<argv[i]<<" ";
		fCommandLine += argv[i];
		fCommandLine += " ";
	}
	std::cout<<std::endl;

	// instance of command line interface used to read the command line flags
	CommandLineInterface* interface = new CommandLineInterface();
	interface->Add("-f",  "<output filename>", &fOutputFileName);
	interface->Add("-n",  "<# of events>", &fNbOfEvents);
	interface->Add("-s", "<settings file>                        (specify file with the settings)", &fSettingsFileName);
	interface->Add("-v",  "start visualization", &fVis);
	interface->Add("-c",  "use visualization cut", &fVisCut);
	interface->Add("-i",  "interactive mode", &fInteractive);

	if(!interface->CheckFlags(argc, argv)) {
		exit(1);
	}

	if(fSettingsFileName.empty()) {
		std::cerr<<"Need a settings file!"<<std::endl;
		exit(1);
	}

	//copied from techbytes.ca and added check if it's a directory
	struct stat fileInfo;
	// Attempt to get the file attributes and check if it's a directory
	if(stat(fSettingsFileName.c_str(),&fileInfo) != 0 || S_ISDIR(fileInfo.st_mode)) {
		std::cerr<<"Settings file '"<<fSettingsFileName<<"' doesn't exist!"<<std::endl;
		exit(1);
	}

	if(fVisCut && !fVis) {
		std::cerr<<"Using a visualization cut without visualization makes no sense, deactivating the cut!"<<std::endl;
		fVisCut = false;
	}

	//set visualization cut in settings
	TRexSettings::Get()->VisualizationCut(fVisCut);

	std::cout<<"Number of simulated events: "<<fNbOfEvents<<std::endl
		<<"Visualization "<<fVis<<std::endl
		<<"Visualization Cut "<<fVisCut<<std::endl
		<<"Interactive "<<fInteractive<<std::endl;
	}

TRexData::~TRexData() {
	// TODO Auto-generated destructor stub
}

void TRexData::run(G4RunManager* runManager, int argc, char* argv[]) {
	if(fInteractive || fVis) {
		// Define UI terminal for interactive mode
		//G4UIsession* session = new G4UIterminal(new G4UItcsh);
        G4UIExecutive* session = new G4UIExecutive(argc, argv);

		if(fVis) {
			G4UImanager* UI = G4UImanager::GetUIpointer();
			UI->ApplyCommand("/control/execute init_vis.mac");
		}
		session->SessionStart();
		delete session;
	} else if(fNbOfEvents > 0) {
		runManager->BeamOn(fNbOfEvents);
	}
}

