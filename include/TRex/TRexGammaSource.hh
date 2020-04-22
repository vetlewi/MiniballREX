//
// Created by Vetle Wegner Ingeberg on 28/11/2019.
//

#ifndef MINIBALLREX_TREXGAMMASOURCE_HH
#define MINIBALLREX_TREXGAMMASOURCE_HH

#include "TRex/TRexBaseGenerator.hh"

class G4ParticleGun;

class TRexGammaSource : public TRexBaseGenerator {
public:
    TRexGammaSource();
    virtual ~TRexGammaSource();

    void GeneratePrimaries(G4Event *anEvent);
    //void CreateTreeBranches(TTree &tree);
    //void FillTree(TTree &tree);
    void CreateTreeBranches();

private:
    // shoot fReactionX, fReactionY, fReactionZ at the surface of the alpha source
    void ShootReactionPosition();

    // shoot fThetaCM and fPhi isotropically in a half sphere
    void CreateIsotropicDistribution();

    G4ParticleGun* fParticleGun;

    G4double fReactionEnergy;
    G4double fReactionX;
    G4double fReactionY;
    G4double fReactionZ;
    G4double fThetaCM, fPhi;
};

#endif //MINIBALLREX_TREXGAMMASOURCE_HH
