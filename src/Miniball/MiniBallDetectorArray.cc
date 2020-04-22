/************************************************************************
 * \file MiniBallDetectorArray.hh
 *
 * \class MiniBallDetectorArray
 * \brief Design of a MiniBall detector array
 *
 * \author Tanja Striepling (tanja@ikp.uni-koeln.de)
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#include "Miniball/MiniBallDetectorArray.hh"

#include <cmath>

using namespace std;


// include-files for visualisation
#ifdef G4VIS_USE
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#endif

// constructor
MiniBallDetectorArray::MiniBallDetectorArray(G4int p_nb_of_clusters,
                                             G4int* p_cluster_type, G4double* p_rho, G4double* p_theta, G4double* p_phi,
                                             G4double* p_spin, G4bool p_capsule, G4bool p_cryowall)
        : histoManager(NULL), mother(NULL), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(G4int p_nb_of_clusters,
                                             G4int* p_cluster_type, G4Transform3D* p_transform,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(NULL), mother(NULL), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);
        type.push_back(p_cluster_type[clust]);
        transform.push_back(p_transform[clust]);

        PushBackDefaultParameters();
    }
}

MiniBallDetectorArray::MiniBallDetectorArray(G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters, G4String *p_name,
                                             G4int* p_cluster_type, G4double* p_rho, G4double* p_theta, G4double* p_phi,
                                             G4double* p_spin, G4bool p_capsule, G4bool p_cryowall)
        : histoManager(NULL), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters,
                                             std::vector<G4String> p_name,
                                             std::vector<G4int> p_cluster_type,
                                             std::vector<G4double> p_rho,
                                             std::vector<G4double> p_theta,
                                             std::vector<G4double> p_phi,
                                             std::vector<G4double> p_spin,
                                             G4bool p_capsule,
                                             G4bool p_cryowall)
        : histoManager(NULL), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}


MiniBallDetectorArray::MiniBallDetectorArray(G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters,
                                             std::vector<std::string> p_name,
                                             std::vector<G4int> p_cluster_type,
                                             std::vector<G4double> p_rho,
                                             std::vector<G4double> p_theta,
                                             std::vector<G4double> p_phi,
                                             std::vector<G4double> p_spin,
                                             G4bool p_capsule,
                                             G4bool p_cryowall)
        : histoManager(NULL), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}


MiniBallDetectorArray::MiniBallDetectorArray(G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters, G4String* p_name,
                                             G4int* p_cluster_type, G4Transform3D* p_transform,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(NULL), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);
        transform.push_back(p_transform[clust]);

        PushBackDefaultParameters();
    }
}


MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4int p_nb_of_clusters, G4int* p_cluster_type, G4double* p_rho,
                                             G4double* p_theta, G4double* p_phi, G4double* p_spin,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(HM), mother(NULL), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);

        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4int p_nb_of_clusters, G4int* p_cluster_type, G4Transform3D* p_transform,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(HM), mother(NULL), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);

        type.push_back(p_cluster_type[clust]);

        transform.push_back(p_transform[clust]);

        PushBackDefaultParameters();
    }
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters,
                                             std::vector<G4String> p_name,
                                             std::vector<G4int> p_cluster_type,
                                             std::vector<G4double> p_rho,
                                             std::vector<G4double> p_theta,
                                             std::vector<G4double> p_phi,
                                             std::vector<G4double> p_spin,
                                             G4bool p_capsule,
                                             G4bool p_cryowall)
        : histoManager(HM), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4VPhysicalVolume* p_mother,
                                             G4int p_nb_of_clusters,
                                             std::vector<std::string> p_name,
                                             std::vector<G4int> p_cluster_type,
                                             std::vector<G4double> p_rho,
                                             std::vector<G4double> p_theta,
                                             std::vector<G4double> p_phi,
                                             std::vector<G4double> p_spin,
                                             G4bool p_capsule,
                                             G4bool p_cryowall)
        : histoManager(HM), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4VPhysicalVolume* p_mother, G4int p_nb_of_clusters, G4String* p_name,
                                             G4int* p_cluster_type, G4Transform3D* p_transform,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(HM), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        name.push_back(p_name[clust]);
        type.push_back(p_cluster_type[clust]);
        transform.push_back(p_transform[clust]);

        PushBackDefaultParameters();
    }
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4VPhysicalVolume* p_mother, G4int p_nb_of_clusters,
                                             G4int* p_cluster_type, G4double* p_rho, G4double* p_theta, G4double* p_phi,
                                             G4double* p_spin, G4bool p_capsule, G4bool p_cryowall)
        : histoManager(HM), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);

        type.push_back(p_cluster_type[clust]);

        PushBackDefaultParameters();
    }

    GetTransformations(p_rho, p_theta, p_phi, p_spin);
}

MiniBallDetectorArray::MiniBallDetectorArray(MiniBallHistoManager* HM,
                                             G4VPhysicalVolume* p_mother, G4int p_nb_of_clusters,
                                             G4int* p_cluster_type, G4Transform3D* p_transform,
                                             G4bool p_capsule, G4bool p_cryowall)
        : histoManager(HM), mother(p_mother), nb_of_clusters(p_nb_of_clusters),
        capsule(p_capsule), cryowall(p_cryowall),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4String new_name="cluster";
        name.push_back(new_name);

        type.push_back(p_cluster_type[clust]);
        transform.push_back(p_transform[clust]);

        PushBackDefaultParameters();
    }
}

MiniBallDetectorArray::~MiniBallDetectorArray()
{
    for(size_t clust=0; clust<cluster.size(); clust++)
    {
        delete cluster[clust];
    }
}

void MiniBallDetectorArray::GetTransformations(G4double* p_rho,
                                               G4double* p_theta,
                                               G4double* p_phi,
                                               G4double* p_spin)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4RotationMatrix cluster_rotation;
        cluster_rotation.rotateZ(p_spin[clust]);
        cluster_rotation.rotateX(M_PI);
        cluster_rotation.rotateY(p_theta[clust]);
        cluster_rotation.rotateZ(p_phi[clust]);

        G4double trans_mag = p_rho[clust];

        G4ThreeVector cluster_translation(0., 0., trans_mag);
        cluster_translation.rotateY(p_theta[clust]);
        cluster_translation.rotateZ(p_phi[clust]);

        G4Transform3D cluster_transformation(cluster_rotation,
                                             cluster_translation);
        transform.push_back(cluster_transformation);
    }
}

void MiniBallDetectorArray::GetTransformations(std::vector<G4double> &p_rho,
                                               std::vector<G4double> &p_theta,
                                               std::vector<G4double> &p_phi,
                                               std::vector<G4double> &p_spin)
{
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        G4RotationMatrix cluster_rotation;
        cluster_rotation.rotateZ(p_spin[clust]);
        cluster_rotation.rotateX(M_PI);
        cluster_rotation.rotateY(p_theta[clust]);
        cluster_rotation.rotateZ(p_phi[clust]);

        G4double trans_mag = p_rho[clust];

        G4ThreeVector cluster_translation(0., 0., trans_mag);
        cluster_translation.rotateY(p_theta[clust]);
        cluster_translation.rotateZ(p_phi[clust]);

        G4Transform3D cluster_transformation(cluster_rotation,
                                             cluster_translation);
        transform.push_back(cluster_transformation);
    }
}

// construction of detector array
G4VPhysicalVolume* MiniBallDetectorArray::Construct()
{
    // if no mother volume is given an world volume is created
    if(mother == NULL)
    {
        MiniBallWorld* world = new MiniBallWorld();
        mother=world->Construct();
    }


    //Position of the clusters in mother volume
    for(G4int clust=0; clust<nb_of_clusters; clust++)
    {
        MiniBallTripleDetector* new_cluster = NULL;

        if(type[clust] == TRIPLE_CLUSTER)
        {
            if(histoManager)
            {
                new_cluster = new MiniBallTripleDetector(histoManager,
                                                         name[clust], mother,
                                                         &transform[clust],
                                                         capsule, cryowall);
                if(det_vis_att)
                    new_cluster->SetDetectorVisAttributes(det_vis_att);
                else if(use_labeled_colors)
                    new_cluster->UseLabeledDetectorColors();
                if(capsule_vis_att)
                    new_cluster->SetCapsuleVisAttributes(capsule_vis_att);
                if(cryo_vis_att)
                    new_cluster->SetCryostatVisAttributes(cryo_vis_att);

                if(eff_factA[clust]>0)
                    new_cluster->SetEfficiencyFactorDetA(eff_factA[clust]);
                if(eff_factB[clust]>0)
                    new_cluster->SetEfficiencyFactorDetB(eff_factB[clust]);
                if(eff_factC[clust]>0)
                    new_cluster->SetEfficiencyFactorDetC(eff_factC[clust]);

                if(deadlayerA[clust]>0)
                    new_cluster->SetDeadlayerDetA(deadlayerA[clust],
                                                  deadlayer_typeA[clust]);
                if(deadlayerB[clust]>0)
                    new_cluster->SetDeadlayerDetB(deadlayerB[clust],
                                                  deadlayer_typeB[clust]);
                if(deadlayerC[clust]>0)
                    new_cluster->SetDeadlayerDetC(deadlayerC[clust],
                                                  deadlayer_typeC[clust]);

                new_cluster->Construct();
            }
            else
            {
                new_cluster = new MiniBallTripleDetector(name[clust], mother,
                                                         &transform[clust],
                                                         capsule, cryowall);
                if(det_vis_att)
                    new_cluster->SetDetectorVisAttributes(det_vis_att);
                else if(use_labeled_colors)
                    new_cluster->UseLabeledDetectorColors();
                if(capsule_vis_att)
                    new_cluster->SetCapsuleVisAttributes(capsule_vis_att);
                if(cryo_vis_att)
                    new_cluster->SetCryostatVisAttributes(cryo_vis_att);

                new_cluster->Construct();
            }
        }
        // add new cluster to clusterlist
        cluster.push_back(new_cluster);
    }

    return(mother);
}

void MiniBallDetectorArray::PushBackDefaultParameters()
{
    eff_factA.push_back(0.);
    eff_factB.push_back(0.);
    eff_factC.push_back(0.);

    deadlayerA.push_back(0.);
    deadlayerB.push_back(0.);
    deadlayerC.push_back(0.);

    deadlayer_typeA.push_back(DEFAULT_DEADLAYER_TYPE);
    deadlayer_typeB.push_back(DEFAULT_DEADLAYER_TYPE);
    deadlayer_typeC.push_back(DEFAULT_DEADLAYER_TYPE);
}

void MiniBallDetectorArray::SetEfficiencyFactorDetA(G4int cluster_nb,
                                                    G4double eff_fact)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factA.size())
        return;

    eff_factA[cluster_nb] = eff_fact;
}

void MiniBallDetectorArray::SetRelativeEfficiencyDetA(G4int cluster_nb,
                                                      G4double percent)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factA.size())
        return;

    eff_factA[cluster_nb] =
            MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}

void MiniBallDetectorArray::SetEfficiencyFactorDetB(G4int cluster_nb,
                                                    G4double eff_fact)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factB.size())
        return;

    eff_factB[cluster_nb] = eff_fact;
}

void MiniBallDetectorArray::SetRelativeEfficiencyDetB(G4int cluster_nb,
                                                      G4double percent)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factB.size())
        return;

    eff_factB[cluster_nb] =
            MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}

void MiniBallDetectorArray::SetEfficiencyFactorDetC(G4int cluster_nb,
                                                    G4double eff_fact)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factC.size())
        return;

    eff_factC[cluster_nb] = eff_fact;
}

void MiniBallDetectorArray::SetRelativeEfficiencyDetC(G4int cluster_nb,
                                                      G4double percent)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)eff_factC.size())
        return;

    eff_factC[cluster_nb] =
            MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}

void MiniBallDetectorArray::SetDeadlayerDetA(G4int cluster_nb,
                                             G4double p_dead, G4int p_type)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)deadlayerA.size())
        return;

    deadlayerA[cluster_nb] = p_dead;
    deadlayer_typeA[cluster_nb] = p_type;
}

void MiniBallDetectorArray::SetDeadlayerDetB(G4int cluster_nb,
                                             G4double p_dead, G4int p_type)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)deadlayerB.size())
        return;

    deadlayerB[cluster_nb] = p_dead;
    deadlayer_typeB[cluster_nb] = p_type;
}

void MiniBallDetectorArray::SetDeadlayerDetC(G4int cluster_nb,
                                             G4double p_dead, G4int p_type)
{
    if(cluster_nb < 0 || cluster_nb >= (G4int)deadlayerC.size())
        return;

    deadlayerC[cluster_nb] = p_dead;
    deadlayer_typeC[cluster_nb] = p_type;
}

void MiniBallDetectorArray::SetAllDeadlayer(G4double p_dead, G4int p_type)
{
    for(size_t cluster_nb=0; cluster_nb<deadlayerA.size(); cluster_nb++)
    {
        deadlayerA[cluster_nb] = p_dead;
        deadlayer_typeA[cluster_nb] = p_type;

        deadlayerB[cluster_nb] = p_dead;
        deadlayer_typeB[cluster_nb] = p_type;

        deadlayerC[cluster_nb] = p_dead;
        deadlayer_typeC[cluster_nb] = p_type;
    }
}

void MiniBallDetectorArray::SetDetectorVisAttributes(
        const G4VisAttributes* pvis_att)
{
    det_vis_att = pvis_att;
}

void MiniBallDetectorArray::SetDetectorVisAttributes(
        const G4VisAttributes& vis_att)
{
    det_vis_att = &vis_att;
}

void MiniBallDetectorArray::SetCapsuleVisAttributes(
        const G4VisAttributes* pvis_att)
{
    capsule_vis_att = pvis_att;
}

void MiniBallDetectorArray::SetCapsuleVisAttributes(
        const G4VisAttributes& vis_att)
{
    capsule_vis_att = &vis_att;
}

void MiniBallDetectorArray::SetCryostatVisAttributes(
        const G4VisAttributes* pvis_att)
{
    cryo_vis_att = pvis_att;
}

void MiniBallDetectorArray::SetCryostatVisAttributes(
        const G4VisAttributes& vis_att)
{
    cryo_vis_att = &vis_att;
}


