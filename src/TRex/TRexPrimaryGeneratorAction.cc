/*
 * TRexPrimaryGeneratorAction.cc
 *
 *  Created on: Jun 15, 2014
 *      Author: sklupp
 */

#include "TRex/TRexPrimaryGeneratorAction.hh"
#include "TRex/TRexSettings.hh"

TRexPrimaryGeneratorAction::TRexPrimaryGeneratorAction() {
	// set the primary generator
	SetGenerator();
}

TRexPrimaryGeneratorAction::~TRexPrimaryGeneratorAction() {
	// TODO Auto-generated destructor stub
}

void TRexPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent) {
	fCurrentGenerator->GeneratePrimaries(anEvent);
}

void TRexPrimaryGeneratorAction::SetGenerator() {
	std::string generatorName = TRexSettings::Get()->GetPrimaryGenerator();
	if(generatorName == "TestSource") {
		std::cout<<std::endl<<"Using test source ....\n"<<std::endl;
		fCurrentGenerator = new TRexTestSource;
	} else if(generatorName == "Rutherford") {
		std::cout<<std::endl<<"Using Rutherford scattering ....\n"<<std::endl;
		fCurrentGenerator = new TRexRutherford;
	} else if(generatorName == "AngularDistribution") {
		std::cout<<std::endl<<"Using given angular distribution ....\n"<<std::endl;
		fCurrentGenerator = new TRexAngularDistribution;
	} else if(generatorName == "AlphaSource") {
		std::cout<<std::endl<<"Using alpha source ....\n"<<std::endl;
		fCurrentGenerator = new TRexAlphaSource;
	} else if (generatorName == "gammaSource") {
	    std::cout<<std::endl<<"Using gamma source ....\n"<<std::endl;
	    fCurrentGenerator = new TRexGammaSource;
	}
}

void TRexPrimaryGeneratorAction::SetTree(TTree* tree) {
	fCurrentGenerator->SetTree(tree);
	fCurrentGenerator->CreateTreeBranches();
}
