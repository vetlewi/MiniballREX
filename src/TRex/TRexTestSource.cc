/*
 * TRexTestSource.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexTestSource.hh"
#include "TRex/TRexSettings.hh"

#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>

TRexTestSource::TRexTestSource() {
	fParticleGun = new G4ParticleGun(1);
}

TRexTestSource::~TRexTestSource() {
	// TODO Auto-generated destructor stub
}

/************************************************************
 *
 * Simulates a test source
 *
 ************************************************************/
void TRexTestSource::GeneratePrimaries(G4Event *anEvent) {

	fReactionEnergy = TRexSettings::Get()->GetTestSourceEnergy();

	// shoot the alpha emission point
	ShootReactionPosition();

	fParticleGun->SetParticleDefinition(G4Proton::ProtonDefinition());
	fParticleGun->SetParticlePosition(G4ThreeVector(fReactionX, fReactionY, fReactionZ));
	fParticleGun->SetParticleEnergy(fReactionEnergy);

	// isotropic distribution
	CreateIsotropicDistribution();

	G4ThreeVector direction;
	direction.set(1,1,1);
	direction.setMag(1.);
	direction.setTheta(fThetaCM);
	direction.setPhi(fPhi);
	//direction.setTheta(45* degree);
	//direction.setPhi(2.0* degree);
	fParticleGun->SetParticleMomentumDirection(direction);

	fParticleGun->GeneratePrimaryVertex(anEvent);

	FillTree();
}

void TRexTestSource::ShootReactionPosition() {
	fReactionX = 0.0 * mm;
	fReactionY = 0.0 * mm;
	fReactionZ = 0.0 * mm;
}

void TRexTestSource::CreateIsotropicDistribution() {
	fThetaCM = CLHEP::RandFlat::shoot(-1., 1.);

	fThetaCM = acos(fThetaCM)*radian;

	fPhi = CLHEP::RandFlat::shoot(-M_PI,M_PI)*radian;
	//fPhi = CLHEP::RandFlat::shoot(0., 2.* M_PI)*radian;
	//fPhi = CLHEP::RandFlat::shoot(-M_PI / 2.,M_PI + M_PI / 2.)*radian;
}

void TRexTestSource::CreateTreeBranches() {
	if(!fTree) {
		std::cout<<std::endl<<std::endl<<"TRexTestSource: Tree doesn't exist!"<<std::endl<<std::endl;
	}
	fTree->Branch("reactionEnergy", &fReactionEnergy, "reactionEnergy/D");
	fTree->Branch("reactionX", &fReactionX, "reactionX/D");
	fTree->Branch("reactionY", &fReactionY, "reactionY/D");
	fTree->Branch("reactionZ", &fReactionZ, "reactionZ/D");
	fTree->Branch("thetaCM", &fThetaCM, "thetaCM/D");
	fTree->Branch("phi", &fPhi, "phi/D");
}

