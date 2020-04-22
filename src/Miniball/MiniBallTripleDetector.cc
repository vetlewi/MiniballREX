/************************************************************************
 * \file MiniBallTripleDetector.cc
 *
 * \class MiniBallTripleDetector   
 * \brief Design of an MiniBall Triple-Cluster
 *
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#include "Miniball/MiniBallTripleDetector.hh"

#include <G4Colour.hh>
#include <G4VisAttributes.hh>

using namespace std;

// constructors
MiniBallTripleDetector::MiniBallTripleDetector(G4bool p_capsule,
                                               G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}


MiniBallTripleDetector::MiniBallTripleDetector(
        G4VPhysicalVolume* p_mother, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0), theta(0),
        spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(
        G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta,
        G4double p_phi, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(
        G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta,
        G4double p_phi, G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(
        G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
        G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0), theta(0),
        spin(0), Cluster_transformation(p_transform), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(
        G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
        G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0), theta(0),
        spin(p_spin), Cluster_transformation(p_transform), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4String p_name,
                                               G4VPhysicalVolume* p_mother, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0), theta(0),
        spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4String p_name,
                                               G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta,
                                               G4double p_phi, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4String p_name,
                                               G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta,
                                               G4double p_phi, G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4String p_name,
                                               G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0), theta(0),
        spin(0), Cluster_transformation(p_transform), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4String p_name,
                                               G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0), theta(0),
        spin(p_spin), Cluster_transformation(p_transform), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(p_rho),
        phi(p_phi), theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4double p_spin, G4bool p_capsule,
                                               G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(p_rho),
        phi(p_phi), theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4Transform3D* p_transform,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(G4Transform3D* p_transform,
                                               G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(p_spin), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(0),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4VPhysicalVolume* p_mother,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4VPhysicalVolume* p_mother, G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4VPhysicalVolume* p_mother, G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4double p_spin, G4bool p_capsule,
                                               G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(p_mother), rho(0), phi(0),
        theta(0), spin(p_spin), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4String p_name, G4VPhysicalVolume* p_mother,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(NULL), capsule(p_capsule),
        cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4String p_name, G4VPhysicalVolume* p_mother, G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4String p_name, G4VPhysicalVolume* p_mother, G4double p_rho,
                                               G4double p_theta, G4double p_phi, G4double p_spin, G4bool p_capsule,
                                               G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(p_rho), phi(p_phi),
        theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4String p_name, G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4String p_name, G4VPhysicalVolume* p_mother, G4Transform3D* p_transform,
                                               G4double p_spin, G4bool p_capsule, G4bool p_cryowall)
        :name(p_name), mother(p_mother), rho(0), phi(0),
        theta(0), spin(p_spin), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4double p_rho, G4double p_theta, G4double p_phi, G4bool p_capsule,
                                               G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(p_rho),
        phi(p_phi), theta(p_theta), spin(0), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(p_rho),
        phi(p_phi), theta(p_theta), spin(p_spin), Cluster_transformation(NULL),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4Transform3D* p_transform, G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(0), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::MiniBallTripleDetector(MiniBallHistoManager* HM,
                                               G4Transform3D* p_transform, G4double p_spin,
                                               G4bool p_capsule, G4bool p_cryowall)
        :name("/TripleCluster"), mother(NULL), rho(0), phi(0),
        theta(0), spin(p_spin), Cluster_transformation(p_transform),
        capsule(p_capsule), cryowall(p_cryowall), histoManager(HM),
        eff_factA(0.), eff_factB(0.), eff_factC(0.),
        deadlayerA(0.), deadlayerB(0.), deadlayerC(0.),
        deadlayer_typeA(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeB(DEFAULT_DEADLAYER_TYPE),
        deadlayer_typeC(DEFAULT_DEADLAYER_TYPE),
        det_vis_att(NULL), capsule_vis_att(NULL), cryo_vis_att(NULL),
        use_labeled_colors(false),
        cryo_cut(false), capsule_cut(false), det_cut(false)
{}

MiniBallTripleDetector::~MiniBallTripleDetector()
{
    if(HPGe_detector_1)
        delete HPGe_detector_1;
    if(HPGe_detector_2)
        delete HPGe_detector_2;
    if(HPGe_detector_3)
        delete HPGe_detector_3;
}

// construction of the detector, if no mother volume is given an world
// volume is created, gives back either the mothervolume with the
// detector is placed in or the new created world volume

G4VPhysicalVolume* MiniBallTripleDetector::Construct()
{
    if(histoManager)
    {
        G4int det_nb = histoManager->GetNbOfCryostats();

        std::ostringstream tmp_strm;
        tmp_strm.clear();
        tmp_strm << det_nb;
        name += "_" + tmp_strm.str();
    }

    if(name.at(0) != '/')
        name = "/"+name;

    // if no mothervolume is specified in constructor, create world volume
    if(mother == NULL)
    {
        MiniBallWorld* world = new MiniBallWorld();
        mother =world->Construct();
    }

    // visualisation attributes
#ifdef G4VIS_USE
    if(!cryo_vis_att)
    {
      G4VisAttributes* AlVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
      AlVisAtt->SetVisibility(true);
      cryo_vis_att = AlVisAtt;
    }
#endif

    // transformation of the three detectors
    G4double front    = DETECTOR_FRONT;
    G4double front_2  = front/2;

    G4double ang_alpha = DETECTOR_ANGLE;
    G4double ang_theta = asin(2/sqrt(3.)*sin(ang_alpha));
    G4double dist = (GAP_BETWEEN_DETECTORS/2+GAP_TO_CAPSULE+CAPSULE_THICKNESS)
                    /(sqrt(3.)/2);

    // calculating the right position of the detectors
    G4double h1, h2, h;
    G4double q3;
    G4double z;

    G4double cos_theta = cos(ang_theta);
    G4double sin_theta = sin(ang_theta);
    G4double tan_theta = tan(ang_theta);

    G4double env_det_pos
            = MiniBallSingleDetector::MoveToDetectorFront();

    h1 = front_2*cos_theta;

    h2 = env_det_pos*sin_theta;

    h  = h1 + h2 + dist;
    G4double radius = h/sin_theta - env_det_pos;

    q3 = h/tan_theta;

    z = q3 - radius;

    G4RotationMatrix HPGe_1_rotation;
    HPGe_1_rotation.rotateY(-ang_theta);

    G4ThreeVector HPGe_1_translation(h, 0., -z);

    G4Transform3D* HPGe_1_transformation
            = new G4Transform3D(HPGe_1_rotation, HPGe_1_translation);

    G4RotationMatrix HPGe_2_rotation;
    HPGe_2_rotation.rotateY(-ang_theta);
    HPGe_2_rotation.rotateZ(120*deg);

    G4ThreeVector HPGe_2_translation(h, 0., -z);
    HPGe_2_translation.rotateZ(120*deg);

    G4Transform3D* HPGe_2_transformation
            = new G4Transform3D(HPGe_2_rotation, HPGe_2_translation);

    G4RotationMatrix HPGe_3_rotation;
    HPGe_3_rotation.rotateY(-ang_theta);
    HPGe_3_rotation.rotateZ(-120*deg);

    G4ThreeVector HPGe_3_translation(h, 0., -z);
    HPGe_3_translation.rotateZ(-120*deg);

    G4Transform3D* HPGe_3_transformation
            = new G4Transform3D(HPGe_3_rotation, HPGe_3_translation);

    // cap of the triple cryostat

    std::vector<G4LogicalVolume*> cryowall_log;
    std::vector<G4Transform3D> cryowall_trans;

    G4RotationMatrix Rotation_0;

    G4RotationMatrix Rotation_60;
    Rotation_60.rotateZ(60*deg);
    G4Transform3D Transform_60(Rotation_60, G4ThreeVector(0, 0, 0));

    G4RotationMatrix Rotation_m60;
    Rotation_m60.rotateZ(-60*deg);

    G4RotationMatrix Rotation_120;
    Rotation_120.rotateZ(120*deg);
    G4Transform3D Transform_120(Rotation_120, G4ThreeVector(0, 0, 0));

    G4RotationMatrix Rotation_m120;
    Rotation_m120.rotateZ(-120*deg);
    G4Transform3D Transform_m120(Rotation_m120, G4ThreeVector(0, 0, 0));

    G4RotationMatrix Rotation_180;
    Rotation_180.rotateZ(180*deg);

    G4RotationMatrix Rotation_x180;
    Rotation_x180.rotateX(180*deg);
    G4Transform3D Transform_x180(Rotation_x180, G4ThreeVector(0, 0, 0));

    if(cryowall)
    {
        G4Material* Al = MiniBallMaterial::Get()->GetMaterialAl();

        // construct cap

        G4double visangle=360.*deg;
        if(cryo_cut)
            visangle=180.*deg;

        G4double cos30 = sqrt(3.)/2.;
        G4double sin30 = .5;

        G4double z_pos
                = GetDistanceToFrontPlane()-CRYOSTAT_THICKNESS/2;

        G4Transform3D z_translation(Rotation_0, G4ThreeVector(0, 0, z_pos));

        G4double fr_z[] = {-CRYOSTAT_THICKNESS/2, CRYOSTAT_THICKNESS/2};
        G4double fr_rmin[] = {0, 0};
        G4double fr_rmax[] = {CRYOSTAT_FRONT/2, CRYOSTAT_FRONT/2};

        G4Polyhedra* fr;
        if(!cryo_cut)
            fr = new G4Polyhedra(name+"/front_part", 0*deg, 360.*deg,
                                 6, 2, fr_z, fr_rmin, fr_rmax);
        else
            fr = new G4Polyhedra(name+"/front_part", 0*deg, visangle,
                                 3, 2, fr_z, fr_rmin, fr_rmax);

        G4Sphere* cut
                = new G4Sphere(name+"cut", CAP_RADIUS-CAP_HEIGHT, CAP_RADIUS,
                               0.*deg, 360.*deg, 0.*deg, CAP_DELTA_THETA+1*deg);

        G4SubtractionSolid* fr_cut
                = new G4SubtractionSolid(name+"/fr_cut",
                                         fr, cut, &Rotation_0,
                                         G4ThreeVector(0, 0,
                                                       -CRYOSTAT_THICKNESS/2-CAP_RADIUS+CAP_HEIGHT));

        G4Sphere* cap
                = new G4Sphere(name+"/cap", CAP_RADIUS, CAP_RADIUS+CRYOSTAT_THICKNESS,
                               0.*deg, visangle, 0.*deg, CAP_DELTA_THETA);

        G4UnionSolid* fr_cap
                = new G4UnionSolid(name+"/fr_cap", fr_cut, cap, &Rotation_0,
                                   G4ThreeVector(0, 0, -CAP_RADIUS+CAP_HEIGHT
                                                       -CRYOSTAT_THICKNESS/2));

        cryowall_trans.push_back(z_translation);

        G4LogicalVolume* front_log =
                new G4LogicalVolume(fr_cap, Al, name+"/front_log");

#ifdef G4VIS_USE
        front_log->SetVisAttributes(cryo_vis_att);
#endif
        cryowall_log.push_back(front_log);

        G4ThreeVector x[8];

        G4double Dz, Theta, Phi;
        G4double Dy1, Dx1, Dx2, Alp1;
        G4double Dy2, Dx3, Dx4, Alp2;

        G4double a=CRYOSTAT_FRONT/2;
        G4double b=(CRYOSTAT_FRONT/2)/cos30;

        x[0].setX(-b/2.);
        x[0].setY(a);
        x[0].setZ(-CRYOSTAT_THICKNESS/2);
        x[1]=x[0];
        x[1].setX(-3*b/2.);
        x[2].setX(-b);
        x[2].setY(0.);
        x[2].setZ(-CRYOSTAT_THICKNESS/2);
        x[3]=x[2];
        x[3].setX(-2.*b);
        x[4]=x[0];
        x[4].setZ(CRYOSTAT_THICKNESS/2);
        x[5]=x[1];
        x[5].setZ(CRYOSTAT_THICKNESS/2);
        x[6]=x[2];
        x[6].setZ(CRYOSTAT_THICKNESS/2);
        x[7]=x[3];
        x[7].setZ(CRYOSTAT_THICKNESS/2);

        G4Transform3D new_trap_trans
                = MiniBallGeom::GetTrap(x, &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* new_trap_sol
                = new G4Trap(name+"/new_trap_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* new_trap_log
                = new G4LogicalVolume(new_trap_sol, Al, name+"/new_trap_log");

#ifdef G4VIS_USE
        new_trap_log->SetVisAttributes(cryo_vis_att);
#endif

        // trap1
        cryowall_log.push_back(new_trap_log);
        cryowall_trans.push_back(z_translation*new_trap_trans);

        if(!cryo_cut)
        {
            // trap2
            cryowall_log.push_back(new_trap_log);
            cryowall_trans.push_back(z_translation*Transform_120
                                     *new_trap_trans);
        }

        // trap3
        cryowall_log.push_back(new_trap_log);
        cryowall_trans.push_back(z_translation*Transform_m120*new_trap_trans);

        if(!cryo_cut)
        {
            // trap4
            cryowall_log.push_back(new_trap_log);
            cryowall_trans.push_back(z_translation*Transform_x180
                                     *new_trap_trans);

            // trap5
            cryowall_log.push_back(new_trap_log);
            cryowall_trans.push_back(z_translation*Transform_120
                                     *Transform_x180*new_trap_trans);
        }
        // trap6
        cryowall_log.push_back(new_trap_log);
        cryowall_trans.push_back(z_translation*Transform_m120
                                 *Transform_x180*new_trap_trans);

        // construct sides
        G4ThreeVector z_dir(0, 0, 1);
        G4ThreeVector origin(0, 0, 0);

        // top, middle, and bottom, planes
        MiniBallPlane top_plane(G4ThreeVector(0, 0, -CRYOSTAT_THICKNESS/2),
                                z_dir);
        MiniBallPlane middle_plane(G4ThreeVector(0, 0, -CRYOSTAT_THICKNESS/2
                                                       -CRYOSTAT_SIDE_HEIGHT1),
                                   z_dir);
        MiniBallPlane bottom_plane(G4ThreeVector(0, 0, -CRYOSTAT_THICKNESS/2
                                                       -CRYOSTAT_SIDE_HEIGHT1
                                                       -CRYOSTAT_SIDE_HEIGHT2),
                                   z_dir);

        // cut planes
        MiniBallPlane cut1(origin, z_dir, G4ThreeVector(-b/2., a, 0));
        MiniBallPlane cut3(origin, z_dir, G4ThreeVector(-1, 0, 0));
        MiniBallPlane cut5(origin, z_dir, G4ThreeVector(-b/2., -a, 0));

        // side planes
        G4ThreeVector side_position1(-3.*b/2., a, 0);
        G4ThreeVector side_position2(-3.*b/2., -a, 0);

        G4RotationMatrix det_angle_rot;
        det_angle_rot.rotateX(ang_alpha);

        G4RotationMatrix det_rot;
        det_rot.rotateY(ang_theta);

        G4ThreeVector normal1 = det_angle_rot*G4ThreeVector(0, 1, 0);
        G4ThreeVector out_position1 = side_position1;
        G4ThreeVector in_position1 = out_position1-CRYOSTAT_THICKNESS*normal1;

        MiniBallPlane side1_out(out_position1, normal1);
        MiniBallPlane side1_in(in_position1, normal1);

        G4ThreeVector normal2 = det_rot*Rotation_60*normal1;
        G4ThreeVector out_position2 = side_position1;
        G4ThreeVector in_position2 = out_position2-CRYOSTAT_THICKNESS*normal2;

        MiniBallPlane side2_out(out_position2, normal2);
        MiniBallPlane side2_in(in_position2, normal2);

        G4ThreeVector normal3 = det_rot*Rotation_120*normal1;

        G4ThreeVector out_position3 = side_position2;
        G4ThreeVector in_position3 = out_position3-CRYOSTAT_THICKNESS*normal3;

        MiniBallPlane side3_out(out_position3, normal3);
        MiniBallPlane side3_in(in_position3, normal3);

        G4ThreeVector normal4 = Rotation_180*normal1;

        G4ThreeVector out_position4 = side_position2;
        G4ThreeVector in_position4 = out_position4-CRYOSTAT_THICKNESS*normal4;

        MiniBallPlane side4_out(out_position4, normal4);
        MiniBallPlane side4_in(in_position4, normal4);

        MiniBallLine edge1_out = cut1.Intersect(side1_out);
        MiniBallLine edge1_in = cut1.Intersect(side1_in);

        MiniBallLine edge2_out = side1_out.Intersect(side2_out);
        MiniBallLine edge2_in = side1_in.Intersect(side2_in);

        MiniBallLine edge3_out = side2_out.Intersect(cut3);
        MiniBallLine edge3_in = side2_in.Intersect(cut3);

        MiniBallLine edge4_out = side3_out.Intersect(side4_out);
        MiniBallLine edge4_in = side3_in.Intersect(side4_in);

        MiniBallLine edge5_out = side4_out.Intersect(cut5);
        MiniBallLine edge5_in = side4_in.Intersect(cut5);

        MiniBallPlane cut2(middle_plane.Intersect(edge2_out),
                           middle_plane.Intersect(edge2_out)
                           -middle_plane.Intersect(edge2_in),
                           middle_plane.Intersect(edge2_out)
                           -top_plane.Intersect(edge2_out));
        MiniBallPlane cut4(middle_plane.Intersect(edge4_out),
                           middle_plane.Intersect(edge4_out)
                           -middle_plane.Intersect(edge4_in),
                           middle_plane.Intersect(edge4_out)
                           -top_plane.Intersect(edge4_out));

        // side 1
        G4Transform3D side1_trans
                = MiniBallGeom::GetTrap(cut1, cut2,
                                        side1_out, side1_in,
                                        middle_plane, top_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side1_sol
                = new G4Trap(name+"/side1_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side1_log
                = new G4LogicalVolume(side1_sol, Al, name+"/side1_log");

        // side 2
        G4Transform3D side2_trans
                = MiniBallGeom::GetTrap(cut2, cut3,
                                        side2_out, side2_in,
                                        middle_plane, top_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side2_sol
                = new G4Trap(name+"/side2_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side2_log
                = new G4LogicalVolume(side2_sol, Al, name+"/side2_log");

        // side 3
        G4Transform3D side3_trans
                = MiniBallGeom::GetTrap(cut3, cut4,
                                        side3_out, side3_in,
                                        middle_plane, top_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side3_sol
                = new G4Trap(name+"/side3_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side3_log
                = new G4LogicalVolume(side3_sol, Al, name+"/side3_log");

        // side 4
        G4Transform3D side4_trans
                = MiniBallGeom::GetTrap(cut4, cut5,
                                        side4_out, side4_in,
                                        middle_plane, top_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side4_sol
                = new G4Trap(name+"/side4_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side4_log
                = new G4LogicalVolume(side4_sol, Al, name+"/side4_log");

#ifdef G4VIS_USE
        side1_log->SetVisAttributes(cryo_vis_att);
       side2_log->SetVisAttributes(cryo_vis_att);
       side3_log->SetVisAttributes(cryo_vis_att);
       side4_log->SetVisAttributes(cryo_vis_att);
#endif

        // add logical volumes to vector
        cryowall_log.push_back(side1_log);
        cryowall_trans.push_back(z_translation*side1_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side1_log);
            cryowall_trans.push_back(z_translation*Transform_120*side1_trans);
        }

        cryowall_log.push_back(side1_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side1_trans);

        cryowall_log.push_back(side2_log);
        cryowall_trans.push_back(z_translation*side2_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side2_log);
            cryowall_trans.push_back(z_translation*Transform_120*side2_trans);
        }

        cryowall_log.push_back(side2_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side2_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side3_log);
            cryowall_trans.push_back(z_translation*side3_trans);

            cryowall_log.push_back(side3_log);
            cryowall_trans.push_back(z_translation*Transform_120*side3_trans);
        }

        cryowall_log.push_back(side3_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side3_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side4_log);
            cryowall_trans.push_back(z_translation*side4_trans);

            cryowall_log.push_back(side4_log);
            cryowall_trans.push_back(z_translation*Transform_120*side4_trans);
        }

        cryowall_log.push_back(side4_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side4_trans);

        // lower part of sides
        G4ThreeVector middle[5];
        middle[0] = middle_plane.Intersect(edge1_in);
        middle[1] = middle_plane.Intersect(edge2_in);
        middle[2] = middle_plane.Intersect(edge3_in);
        middle[3] = middle_plane.Intersect(edge4_in);
        middle[4] = middle_plane.Intersect(edge5_in);

        G4ThreeVector bottom[6];
        bottom[0] = bottom_plane.Intersect(edge1_out);
        bottom[1] = bottom_plane.Intersect(edge2_out);
        bottom[2] = bottom_plane.Intersect(edge4_out);
        bottom[3] = bottom_plane.Intersect(edge5_out);
        bottom[4] = bottom[1] + G4ThreeVector(-CRYOSTAT_SIDE_THICKNESS2*cos30,
                                              -CRYOSTAT_SIDE_THICKNESS2*sin30,
                                              0);
        bottom[5] = bottom[2] + G4ThreeVector(-CRYOSTAT_SIDE_THICKNESS2*cos30,
                                              CRYOSTAT_SIDE_THICKNESS2*sin30,
                                              0);

        MiniBallPlane side1_in2(middle[1], middle[1]-middle[0],
                                middle[1]-bottom[4]);
        MiniBallPlane side4_in2(middle[3], middle[3]-middle[4],
                                middle[3]-bottom[5]);

        MiniBallLine edge2_in2 = side1_in2.Intersect(cut2);
        MiniBallLine edge4_in2 = side4_in2.Intersect(cut4);

        MiniBallPlane side2_in2(middle[1], middle[1]-middle[2],
                                middle[1]-bottom_plane.Intersect(edge2_in2));
        MiniBallPlane side3_in2(middle[3], middle[3]-middle[2],
                                middle[3]-bottom_plane.Intersect(edge4_in2));

        // lower side 1
        G4Transform3D side1_l_trans
                = MiniBallGeom::GetTrap(cut1, cut2,
                                        side1_out, side1_in2,
                                        bottom_plane, middle_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side1_l_sol
                = new G4Trap(name+"/side1_l_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side1_l_log
                = new G4LogicalVolume(side1_l_sol, Al, name+"/side1_l_log");

        // lower side 2
        G4Transform3D side2_l_trans
                = MiniBallGeom::GetTrap(cut2, cut3,
                                        side2_out, side2_in2,
                                        bottom_plane, middle_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side2_l_sol
                = new G4Trap(name+"/side2_l_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side2_l_log
                = new G4LogicalVolume(side2_l_sol, Al, name+"/side2_l_log");

        // lower side 3
        G4Transform3D side3_l_trans
                = MiniBallGeom::GetTrap(cut3, cut4,
                                        side3_out, side3_in2,
                                        bottom_plane, middle_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side3_l_sol
                = new G4Trap(name+"/side3_l_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side3_l_log
                = new G4LogicalVolume(side3_l_sol, Al, name+"/side3_l_log");

        // lower side 4
        G4Transform3D side4_l_trans
                = MiniBallGeom::GetTrap(cut4, cut5,
                                        side4_out, side4_in2,
                                        bottom_plane, middle_plane,
                                        &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* side4_l_sol
                = new G4Trap(name+"/side4_l_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* side4_l_log
                = new G4LogicalVolume(side4_l_sol, Al, name+"/side4_l_log");

#ifdef G4VIS_USE
        side1_l_log->SetVisAttributes(cryo_vis_att);
       side2_l_log->SetVisAttributes(cryo_vis_att);
       side3_l_log->SetVisAttributes(cryo_vis_att);
       side4_l_log->SetVisAttributes(cryo_vis_att);
#endif

        // add logical volumes to vector
        cryowall_log.push_back(side1_l_log);
        cryowall_trans.push_back(z_translation*side1_l_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side1_l_log);
            cryowall_trans.push_back(z_translation*Transform_120*side1_l_trans);
        }

        cryowall_log.push_back(side1_l_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side1_l_trans);

        cryowall_log.push_back(side2_l_log);
        cryowall_trans.push_back(z_translation*side2_l_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side2_l_log);
            cryowall_trans.push_back(z_translation*Transform_120*side2_l_trans);
        }

        cryowall_log.push_back(side2_l_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side2_l_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side3_l_log);
            cryowall_trans.push_back(z_translation*side3_l_trans);

            cryowall_log.push_back(side3_l_log);
            cryowall_trans.push_back(z_translation*Transform_120*side3_l_trans);
        }

        cryowall_log.push_back(side3_l_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side3_l_trans);

        if(!cryo_cut)
        {
            cryowall_log.push_back(side4_l_log);
            cryowall_trans.push_back(z_translation*side4_l_trans);

            cryowall_log.push_back(side4_l_log);
            cryowall_trans.push_back(z_translation*Transform_120*side4_l_trans);
        }

        cryowall_log.push_back(side4_l_log);
        cryowall_trans.push_back(z_translation*Transform_m120*side4_l_trans);

        // lower cap
        G4ThreeVector cryostat_back_width = bottom[1]-bottom[2];
        G4ThreeVector cryostat_back_length = bottom[0]-bottom[1];

        a=cryostat_back_width.mag()/2;
        b=(cryostat_back_width.mag()/2)/cos30;
        G4double c=cryostat_back_length.mag();

        G4double fr2_z[] = {-3*CRYOSTAT_THICKNESS/2
                            -CRYOSTAT_SIDE_HEIGHT1
                            -CRYOSTAT_SIDE_HEIGHT2,
                            -CRYOSTAT_THICKNESS/2
                            -CRYOSTAT_SIDE_HEIGHT1
                            -CRYOSTAT_SIDE_HEIGHT2};
        G4double fr2_rmin[] = {0, 0};
        G4double fr2_rmax[] = {a, a};

        G4double fr2_z_pos
                = -CRYOSTAT_THICKNESS-CRYOSTAT_SIDE_HEIGHT1-CRYOSTAT_SIDE_HEIGHT2;
        G4Transform3D fr2_z_translation(Rotation_0,
                                        G4ThreeVector(0, 0, fr2_z_pos));

        G4Polyhedra* fr2;
        if(!cryo_cut)
            fr2 = new G4Polyhedra(name+"/back_part", 0*deg, 360.*deg,
                                  6, 2, fr2_z, fr2_rmin, fr2_rmax);
        else
            fr2 = new G4Polyhedra(name+"/back_part", 0*deg, visangle,
                                  3, 2, fr2_z, fr2_rmin, fr2_rmax);

        G4Tubs* fr2_cut
                = new G4Tubs(name+"/fr2_cut", 0.*mm, CRYOSTAT_NOZZLE_INNER_RAD[0],
                             CRYOSTAT_THICKNESS/2+1.*mm, 0.*deg, 360.*deg);

        G4SubtractionSolid* fr2_sol
                = new G4SubtractionSolid(name+"/fr2_sol",
                                         fr2, fr2_cut, &Rotation_0,
                                         G4ThreeVector(0, 0,
                                                       -CRYOSTAT_THICKNESS
                                                       -CRYOSTAT_SIDE_HEIGHT1
                                                       -CRYOSTAT_SIDE_HEIGHT2));

        cryowall_trans.push_back(z_translation);

        G4LogicalVolume* back_log
                = new G4LogicalVolume(fr2_sol, Al, name+"/back_log");

#ifdef G4VIS_USE
        back_log->SetVisAttributes(cryo_vis_att);
#endif
        cryowall_log.push_back(back_log);

        x[0].setX(-b/2.);
        x[0].setY(a);
        x[0].setZ(-CRYOSTAT_THICKNESS/2);
        x[1]=x[0];
        x[1].setX(-b/2.-c);
        x[2].setX(-b);
        x[2].setY(0.);
        x[2].setZ(-CRYOSTAT_THICKNESS/2);
        x[3]=x[2];
        x[3].setX(-b-c);
        x[4]=x[0];
        x[4].setZ(CRYOSTAT_THICKNESS/2);
        x[5]=x[1];
        x[5].setZ(CRYOSTAT_THICKNESS/2);
        x[6]=x[2];
        x[6].setZ(CRYOSTAT_THICKNESS/2);
        x[7]=x[3];
        x[7].setZ(CRYOSTAT_THICKNESS/2);

        G4Transform3D back_trap_trans
                = MiniBallGeom::GetTrap(x, &Dz, &Theta, &Phi,
                                        &Dy1, &Dx1, &Dx2, &Alp1,
                                        &Dy2, &Dx3, &Dx4, &Alp2);

        G4Trap* back_trap_sol
                = new G4Trap(name+"/back_trap_sol", Dz, Theta, Phi,
                             Dy1, Dx1, Dx2, Alp1, Dy2, Dx3, Dx4, Alp2);

        G4LogicalVolume* back_trap_log
                = new G4LogicalVolume(back_trap_sol, Al, name+"/back_trap_log");

#ifdef G4VIS_USE
        back_trap_log->SetVisAttributes(cryo_vis_att);
#endif

        // trap1
        cryowall_log.push_back(back_trap_log);
        cryowall_trans.push_back(z_translation*fr2_z_translation
                                 *back_trap_trans);

        if(!cryo_cut)
        {
            // trap2
            cryowall_log.push_back(back_trap_log);
            cryowall_trans.push_back(z_translation*fr2_z_translation
                                     *Transform_120*back_trap_trans);
        }

        // trap3
        cryowall_log.push_back(back_trap_log);
        cryowall_trans.push_back(z_translation*fr2_z_translation
                                 *Transform_m120*back_trap_trans);

        if(!cryo_cut)
        {
            // trap4
            cryowall_log.push_back(back_trap_log);
            cryowall_trans.push_back(z_translation*fr2_z_translation
                                     *Transform_x180*back_trap_trans);

            // trap5
            cryowall_log.push_back(back_trap_log);
            cryowall_trans.push_back(z_translation*fr2_z_translation
                                     *Transform_120*Transform_x180
                                     *back_trap_trans);
        }
        // trap6
        cryowall_log.push_back(back_trap_log);
        cryowall_trans.push_back(z_translation*fr2_z_translation
                                 *Transform_m120*Transform_x180
                                 *back_trap_trans);

        //construct nozzle
        G4Polycone* nozzle_sol
                = new G4Polycone(name+"/nozzle_sol",
                                 0.*deg, visangle,
                                 CRYOSTAT_NOZZLE_NB_OF_Z_PLANES,
                                 CRYOSTAT_NOZZLE_Z_PLANE,
                                 CRYOSTAT_NOZZLE_INNER_RAD,
                                 CRYOSTAT_NOZZLE_OUTER_RAD);

        G4LogicalVolume* nozzle_log
                = new G4LogicalVolume(nozzle_sol, Al, "nozzle_log");

        G4Transform3D nozzle_z_trans(Rotation_0,
                                     G4ThreeVector(0, 0,
                                                   fr2_z_pos-CRYOSTAT_THICKNESS/2));

        cryowall_trans.push_back(z_translation*nozzle_z_trans);

#ifdef G4VIS_USE
        nozzle_log->SetVisAttributes(cryo_vis_att);
#endif

        cryowall_log.push_back(nozzle_log);
    }

    // set position of detector in mother volume

    if(Cluster_transformation == NULL)
    {
        G4RotationMatrix Cluster_rotation;
        Cluster_rotation.rotateZ(spin);
        Cluster_rotation.rotateX(M_PI);
        Cluster_rotation.rotateY(theta);
        Cluster_rotation.rotateZ(phi);

        G4double trans_mag = rho;

        G4ThreeVector Cluster_translation(0., 0., trans_mag);
        Cluster_translation.rotateY(theta);
        Cluster_translation.rotateZ(phi);

        Cluster_transformation
                = new G4Transform3D(Cluster_rotation, Cluster_translation);
    }
    else if(spin != 0)
    {
        G4RotationMatrix Cl_rotation = Cluster_transformation->getRotation();
        G4ThreeVector Cl_translation = Cluster_transformation->getTranslation();
        G4RotationMatrix spin_rotation;
        spin_rotation.rotateZ(-spin);

        Cl_rotation *= spin_rotation;

        Cluster_transformation
                = new G4Transform3D(Cl_rotation, Cl_translation);
    }

    // apply cluster transformation

    *HPGe_1_transformation = (*Cluster_transformation)*(*HPGe_1_transformation);
    *HPGe_2_transformation = (*Cluster_transformation)*(*HPGe_2_transformation);
    *HPGe_3_transformation = (*Cluster_transformation)*(*HPGe_3_transformation);

    // place the single detectors

#ifdef G4VIS_USE
    G4VisAttributes* HPGe_blue = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
   HPGe_blue->SetVisibility(true);
   G4VisAttributes* HPGe_red = new G4VisAttributes(G4Colour(1.0,0.0,0.0));
   HPGe_red->SetVisibility(true);
   G4VisAttributes* HPGe_green = new G4VisAttributes(G4Colour(0.0,1.0,0.0));
   HPGe_green->SetVisibility(true);
#endif

    if(histoManager)
        HPGe_detector_1
                = new MiniBallSingleDetector(histoManager, name+"/HPGe_A", mother,
                                             HPGe_1_transformation, capsule);
    else
        HPGe_detector_1
                = new MiniBallSingleDetector(name+"/HPGe_A", mother,
                                             HPGe_1_transformation, capsule);
    if(eff_factA>0)
        HPGe_detector_1->SetEfficiencyFactor(eff_factA);
    if(deadlayerA>0)
        HPGe_detector_1->SetDeadlayer(deadlayerA, deadlayer_typeA);
    if(det_vis_att)
        HPGe_detector_1->SetDetectorVisAttributes(det_vis_att);
    else if(use_labeled_colors)
        HPGe_detector_1->SetDetectorVisAttributes(HPGe_blue);
    if(capsule_vis_att)
        HPGe_detector_1->SetCapsuleVisAttributes(capsule_vis_att);
    if(det_cut)
    {
        if(cryo_cut)
            HPGe_detector_1->CutDetectorVisualisation(1);
        else
            HPGe_detector_1->CutDetectorVisualisation();
    }
    if(capsule_cut)
    {
        if(cryo_cut)
            HPGe_detector_1->CutCapsuleVisualisation(1);
        else
            HPGe_detector_1->CutCapsuleVisualisation();
    }

    HPGe_detector_1->Construct();

    if(histoManager)
        HPGe_detector_2
                = new MiniBallSingleDetector(histoManager, name+"/HPGe_B", mother,
                                             HPGe_2_transformation, capsule);
    else
        HPGe_detector_2
                = new MiniBallSingleDetector(name+"/HPGe_B", mother,
                                             HPGe_2_transformation, capsule);
    if(eff_factB>0)
        HPGe_detector_2->SetEfficiencyFactor(eff_factB);
    if(deadlayerB>0)
        HPGe_detector_2->SetDeadlayer(deadlayerB, deadlayer_typeB);
    if(det_vis_att)
        HPGe_detector_2->SetDetectorVisAttributes(det_vis_att);
    else if(use_labeled_colors)
        HPGe_detector_2->SetDetectorVisAttributes(HPGe_green);
    if(capsule_vis_att)
        HPGe_detector_2->SetCapsuleVisAttributes(capsule_vis_att);
    if(det_cut)
        HPGe_detector_2->CutDetectorVisualisation();
    if(capsule_cut && !cryo_cut)
        HPGe_detector_2->CutCapsuleVisualisation();

    HPGe_detector_2->Construct();

    if(histoManager)
        HPGe_detector_3
                = new MiniBallSingleDetector(histoManager, name+"/HPGe_C", mother,
                                             HPGe_3_transformation, capsule);
    else
        HPGe_detector_3
                = new MiniBallSingleDetector(name+"/HPGe_C", mother,
                                             HPGe_3_transformation, capsule);
    if(eff_factC>0)
        HPGe_detector_3->SetEfficiencyFactor(eff_factC);
    if(deadlayerC>0)
        HPGe_detector_3->SetDeadlayer(deadlayerC, deadlayer_typeC);
    if(det_vis_att)
        HPGe_detector_3->SetDetectorVisAttributes(det_vis_att);
    else if(use_labeled_colors)
        HPGe_detector_3->SetDetectorVisAttributes(HPGe_red);
    if(capsule_vis_att)
        HPGe_detector_3->SetCapsuleVisAttributes(capsule_vis_att);
    if(det_cut)
        HPGe_detector_3->CutDetectorVisualisation();
    if(capsule_cut)
        HPGe_detector_3->CutCapsuleVisualisation();

    HPGe_detector_3->Construct();

    if(histoManager)
    {
        CryostatID = histoManager->AddCryostat(name);

        ADetectorID = HPGe_detector_1->GetDetectorID();
        BDetectorID = HPGe_detector_2->GetDetectorID();
        CDetectorID = HPGe_detector_3->GetDetectorID();

        histoManager->AddToCryostat(CryostatID, ADetectorID);
        histoManager->AddToCryostat(CryostatID, BDetectorID);
        histoManager->AddToCryostat(CryostatID, CDetectorID);
    }

    if(cryowall)
    {
        for(size_t tr_nb=0; tr_nb<cryowall_log.size(); tr_nb++)
        {
            char buffer[20];
            sprintf(buffer, "/front_plate_%d", (int)tr_nb);
            new G4PVPlacement((*Cluster_transformation)*Transform_60
                              *cryowall_trans[tr_nb],
                              name+buffer,
                              cryowall_log[tr_nb], mother, false, 0);
        }
    }

    return(mother);
}

// calculated the distance of the frontcap from the radius of the surfaces
// of the detectors

G4double MiniBallTripleDetector::GetDistanceToFront()
{
    G4double dist_to_front_plane = GetDistanceToFrontPlane();
    return(dist_to_front_plane + CAP_HEIGHT);
}

G4double MiniBallTripleDetector::GetDistanceToFrontPlane()
{
    G4double front    = DETECTOR_FRONT;
    G4double front_2  = front/2;

    G4double ang_alpha = DETECTOR_ANGLE;
    G4double ang_theta = asin(2/sqrt(3.)*sin(ang_alpha));
    G4double dist = (GAP_BETWEEN_DETECTORS/2+GAP_TO_CAPSULE
                     +CAPSULE_THICKNESS)/(sqrt(3.)/2);
    G4double h1;
    G4double q1, q2;
    G4double x1, x2, x;
    G4double radius;

    G4double cos_theta = cos(ang_theta/rad);
    G4double sin_theta = sin(ang_theta/rad);

    q1 = dist/cos_theta;
    q2 = front_2+q1;

    h1 = q2*cos_theta;

    radius = h1*sin_theta;

    x1 = radius*(1-cos_theta);

    x2 = front_2*sin_theta;

    x  = x1 + x2 + GAP_TO_CAPSULE + CAPSULE_THICKNESS
         + GAP_TO_CRYOSTAT + CRYOSTAT_THICKNESS;

    return(x);
}

// claculates the maximal radius of the TripleDetector
G4double MiniBallTripleDetector::GetMaxRadius()
{
    G4double ang_alpha = DETECTOR_ANGLE;
    G4double ang_theta = asin(2/sqrt(3.)*sin(ang_alpha));
    G4double dist = GAP_BETWEEN_DETECTORS/sqrt(3.) + GAP_TO_CAPSULE
                    + CAPSULE_THICKNESS;

    G4double cos_theta = cos(ang_theta/rad);

    G4double hyp = DETECTOR_FRONT + GAP_TO_CRYOSTAT + CRYOSTAT_THICKNESS
                   + dist/cos_theta;
    G4double x = hyp*cos_theta;

    return(x);
}

void MiniBallTripleDetector::SetDetectorVisAttributes(
        const G4VisAttributes* pvis_att)
{
    det_vis_att = pvis_att;
}

void MiniBallTripleDetector::SetDetectorVisAttributes(
        const G4VisAttributes& vis_att)
{
    det_vis_att = &vis_att;
}

void MiniBallTripleDetector::SetCapsuleVisAttributes(
        const G4VisAttributes* pvis_att)
{
    capsule_vis_att = pvis_att;
}

void MiniBallTripleDetector::SetCapsuleVisAttributes(
        const G4VisAttributes& vis_att)
{
    capsule_vis_att = &vis_att;
}

void MiniBallTripleDetector::SetCryostatVisAttributes(
        const G4VisAttributes* pvis_att)
{
    cryo_vis_att = pvis_att;
}

void MiniBallTripleDetector::SetCryostatVisAttributes(
        const G4VisAttributes& vis_att)
{
    cryo_vis_att = &vis_att;
}

void MiniBallTripleDetector::CutCryostatVisualisation()
{
    std::cout << name << ": using cut cryostat geometry "
           << "- use this option only for visualisation!" << std::endl;
    cryo_cut=true;
}

void MiniBallTripleDetector::CutCapsuleVisualisation()
{
    std::cout << name << ": using cut capsule geometry "
           << "- use this option only for visualisation!" << std::endl;
    capsule_cut=true;
}

void MiniBallTripleDetector::CutDetectorVisualisation()
{
    std::cout << name << ": using cut detector geometry "
           << "- use this option only for visualisation!" << std::endl;
    det_cut=true;
}

void MiniBallTripleDetector::SetEfficiencyFactorDetA(G4double p_eff_fact)
{
    eff_factA = p_eff_fact;
}

void MiniBallTripleDetector::SetRelativeEfficiencyDetA(G4double percent)
{
    eff_factA = MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}


void MiniBallTripleDetector::SetEfficiencyFactorDetB(G4double p_eff_fact)
{
    eff_factB = p_eff_fact;
}

void MiniBallTripleDetector::SetRelativeEfficiencyDetB(G4double percent)
{
    eff_factB = MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}


void MiniBallTripleDetector::SetEfficiencyFactorDetC(G4double p_eff_fact)
{
    eff_factC = p_eff_fact;
}

void MiniBallTripleDetector::SetRelativeEfficiencyDetC(G4double percent)
{
    eff_factC = MiniBallSingleDetector::CalculateEfficiencyFactor(percent);
}

void MiniBallTripleDetector::SetDeadlayerDetA(G4double p_dead, G4int p_type)
{
    deadlayerA = p_dead;
    deadlayer_typeA = p_type;
}

void MiniBallTripleDetector::SetDeadlayerDetB(G4double p_dead, G4int p_type)
{
    deadlayerB = p_dead;
    deadlayer_typeB = p_type;
}

void MiniBallTripleDetector::SetDeadlayerDetC(G4double p_dead, G4int p_type)
{
    deadlayerC = p_dead;
    deadlayer_typeC = p_type;
}

void MiniBallTripleDetector::SetAllDeadlayer(G4double p_dead, G4int p_type)
{
    SetDeadlayerDetA(p_dead, p_type);
    SetDeadlayerDetB(p_dead, p_type);
    SetDeadlayerDetC(p_dead, p_type);
}
