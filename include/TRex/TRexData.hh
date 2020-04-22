/*
 * TRexData.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXDATA_HH_
#define TREXDATA_HH_


#include <G4RunManager.hh>

#include <iostream>
#include <string>

class TRexData {
	public:
		TRexData();
		TRexData(int argc, char* argv[]);
		virtual ~TRexData();

		void run(G4RunManager*, int argc, char* argv[]);

		inline std::string GetOutputFileName() { return fOutputFileName; }
		inline std::string GetSettingsFileName() { return fSettingsFileName; }
		inline int GetNbOfEvents() { return fNbOfEvents; }
		inline bool VisualizationCut() { return fVisCut; }

	private:
		std::string fCommandLine;
		std::string fOutputFileName;
		std::string fSettingsFileName;
		int fNbOfEvents;
		bool fVis;
		bool fVisCut;
		bool fInteractive;
};

#endif /* TREXDATA_HH_ */
