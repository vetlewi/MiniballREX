/*
 * TRexAlphaSource.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexGammaSource.hh"

#include "TRex/TRexSettings.hh"

#include <G4ParticleGun.hh>
#include <G4Gamma.hh>
#include <Randomize.hh>
#include <G4SystemOfUnits.hh>

TRexGammaSource::TRexGammaSource() {
    fParticleGun = new G4ParticleGun(1);
}

TRexGammaSource::~TRexGammaSource() {
    // TODO Auto-generated destructor stub
}

/************************************************************
 *
 * Simulates a quadruple alpha source
 *
 ************************************************************/
void TRexGammaSource::GeneratePrimaries(G4Event *anEvent) {

    fReactionEnergy = TRexSettings::Get()->GetGammaSourceEnergy();



    // shoot the gamma emission point
    ShootReactionPosition();

    //fParticleGun->SetParticleDefinition(G4Alpha::AlphaDefinition());
    fParticleGun->SetParticleDefinition(G4Gamma::GammaDefinition());
    fParticleGun->SetParticlePosition(G4ThreeVector(fReactionX, fReactionY, fReactionZ));
    fParticleGun->SetParticleEnergy(fReactionEnergy);

    // isotropic distribution, if reaction_z < 0 shoot only to negative z's (theta < 90) otherwise only to positive z's (theta > 90)
    CreateIsotropicDistribution();

    G4ThreeVector direction;
    direction.set(1,1,1);
    direction.setMag(1.);
    direction.setTheta(fThetaCM);
    direction.setPhi(fPhi);
    fParticleGun->SetParticleMomentumDirection(direction);

    fParticleGun->GeneratePrimaryVertex(anEvent);

    FillTree();
}

void TRexGammaSource::ShootReactionPosition() {
    G4double alphaSourceDiameter = TRexSettings::Get()->GetAlphaSourceDiameter() / mm;
    G4double alphaSourceThickness = TRexSettings::Get()->GetAlphaSourceThickness();

    do {
        fReactionX = CLHEP::RandFlat::shoot(-alphaSourceDiameter / 2., alphaSourceDiameter / 2.);
        fReactionY = CLHEP::RandFlat::shoot(-alphaSourceDiameter / 2., alphaSourceDiameter / 2.);
    } while(sqrt(pow(fReactionX,2) + pow(fReactionY,2)) > alphaSourceDiameter / 2.);

    fReactionX *= mm;
    fReactionY *= mm;

    // alpha source: only from the surface of the 'target' (i.e. the source)
    double tmp = CLHEP::RandFlat::shoot(0.,2.);

    if(tmp < 1.) {
        fReactionZ = -alphaSourceThickness;
    } else {
        fReactionZ = alphaSourceThickness;
    }
}

void TRexGammaSource::CreateIsotropicDistribution() {
    if(fReactionZ < 0) {
        fThetaCM = CLHEP::RandFlat::shoot(-1., 0.);
    } else {
        fThetaCM = CLHEP::RandFlat::shoot(0., 1.);
    }
    fThetaCM = acos(fThetaCM)*radian;

    fPhi = CLHEP::RandFlat::shoot(-M_PI,M_PI)*radian;
    //fPhi = CLHEP::RandFlat::shoot(0., 2.* M_PI)*radian;
    //fPhi = CLHEP::RandFlat::shoot(-M_PI / 2.,M_PI + M_PI / 2.)*radian;
}

void TRexGammaSource::CreateTreeBranches() {
    if(!fTree) {
        std::cout << "\n\n\nTRexAlphaSource: Tree doesn't exist!\n\n" << std::endl;
    }
    fTree->Branch("reactionEnergy", &fReactionEnergy, "reactionEnergy/D");
    fTree->Branch("reactionX", &fReactionX, "reactionX/D");
    fTree->Branch("reactionY", &fReactionY, "reactionY/D");
    fTree->Branch("reactionZ", &fReactionZ, "reactionZ/D");
    fTree->Branch("thetaCM", &fThetaCM, "thetaCM/D");
    fTree->Branch("phi", &fPhi, "phi/D");
}



