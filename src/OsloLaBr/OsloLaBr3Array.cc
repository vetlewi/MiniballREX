//
// Created by Vetle Wegner Ingeberg on 22/04/2020.
//

#include "OsloLaBr/OsloLaBr3Array.hh"
#include "OsloLaBr/OCLParameters.hh"

#include <Miniball/MiniBallWorld.hh>

#include <G4RotationMatrix.hh>

G4ThreeVector SpherToCatG4three(G4double r,G4double theta,G4double phi){
    return r * G4ThreeVector( sin(theta) * cos(phi),
                              sin(theta) * sin(phi),
                              cos(theta));
}

OsloLaBr3DetectorArray::OsloLaBr3DetectorArray(MiniBallHistoManager *HM,
                                               G4VPhysicalVolume *p_mother,
                                               G4int p_nb_of_detectors,
                                               std::vector<std::string> p_name,
                                               std::vector<G4double> p_rho,
                                               std::vector<G4double> p_theta,
                                               std::vector<G4double> p_phi)
    : histoManager(HM), mother(p_mother), nb_of_detectors(p_nb_of_detectors), name( )
    , rho( p_rho ), theta( p_theta ), phi( p_phi )
{
    for ( auto i = 0 ; i < nb_of_detectors ; ++i ){
        name.push_back(p_name[i]);
    }
    GetTransformations(p_rho, p_theta, p_phi, std::vector<G4double>(p_rho.size(), 90*degree));
}

void OsloLaBr3DetectorArray::GetTransformations(std::vector<G4double> &p_rho,
                                                std::vector<G4double> &p_theta,
                                                std::vector<G4double> &p_phi,
                                                std::vector<G4double> p_spin)
{
    for(G4int clust=0; clust< nb_of_detectors; clust++)
    {
        G4RotationMatrix cluster_rotation;
        //cluster_rotation.rotateZ(p_spin[clust]);
        cluster_rotation.rotateX(M_PI);
        cluster_rotation.rotateY(M_PI/2.);

        cluster_rotation.rotateZ(p_phi[clust]);
        cluster_rotation.rotateY(p_theta[clust]);



        G4double trans_mag = p_rho[clust]+detectorHalfinclPMT;
        G4ThreeVector cluster_translation(trans_mag, 0., 0.);
        //G4ThreeVector cluster_translation(0., 0., 0.);//trans_mag);
        //G4ThreeVector cluster_translation(trans_mag*cos(p_phi[clust]+90.*degree)*sin(p_theta[clust]),
        //                                  trans_mag*sin(p_phi[clust]+90.*degree)*sin(p_theta[clust]),
        //                                  trans_mag*cos(p_theta[clust]));


        cluster_translation.rotateZ(p_phi[clust]);
        cluster_translation.rotateY(p_theta[clust]);

        G4Transform3D cluster_transformation(cluster_rotation,
                                             cluster_translation);
        transform.push_back(cluster_transformation);
    }
}


G4VPhysicalVolume* OsloLaBr3DetectorArray::Construct()
{
    // if no mother volume is given an world volume is created
    if(mother == NULL)
    {
        MiniBallWorld* world = new MiniBallWorld();
        mother=world->Construct();
    }

    for ( auto i = 0 ; i < nb_of_detectors ; ++i ){

        G4ThreeVector pos = SpherToCatG4three(rho[i]+detectorHalfinclPMT, theta[i], phi[i]);
        std::string name = "/labr_" + std::to_string(i);
        detector.push_back( new OCLLaBr3(histoManager, name));

        //detector.back()->SetRotation(transform[i].getRotation());
        //detector.back()->SetPosition(transform[i].getTranslation());
        detector.back()->SetTransform(transform[i]);
        detector.back()->Placement(i, mother, false);
    }

    return mother;
}
