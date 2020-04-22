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

#ifndef MiniBallDetectorArray_h
#define MiniBallDetectorArray_h 1

#include "globals.hh"

#include "MBglobals.hh"

#include "MiniBallTripleDetector.hh"
#include "MiniBallWorld.hh"
#include "MiniBallHistoManager.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"

#include "G4VUserDetectorConstruction.hh"

#include <vector>

class G4VPhysicalVolume;
class MiniBallHistoManager;

class G4VisAttributes;

/// arrangement of several cryostats
class MiniBallDetectorArray : public G4VUserDetectorConstruction
{
public:
  /** \brief Constructor for a MiniBall detector array
   * 
   *  The types and positions of MiniBall cryostats in the detector array
   *  are given in arrays with nb_of_clusters enrtires. The parameter 
   *  nb_of_clusters gives the number of cryostats in the detector array.
   *  The positions are specified by polar coordinates rho, phi and 
   *  theta for each cluster or by G4Transform3D transformations. The
   *  array spin gives the rotations around their own axis for each cryostat.
   *  The distances rho from the origin are taken with respect to the common 
   *  sphere of a cryostat on which the crystal fronts are placed. 
   *  To position the clusters with respect to the front plane
   *  of the cryostat add the value returned by the static method
   *  MiniBallTripleDetector::GetDistanceToFrontPlane(), similiar to 
   *  position the clusters with respect to the front of the cap use the
   *  method MiniBallTripleDetector::GetDistanceToFront().
   *  At the moment only triple cluster detectors are implemented, 
   *  so the value for the cluster types should be TRIPLE_CLUSTER.
   *  
   *  \param nb_of_clusters number of MiniBall clusters in the detector array
   *  \param cluster_type array of types of MiniBall clusters
   *  \param rho array of radii of cryostats in polar coordinates
   *  \param theta array of theta angles of cryostats in polar coordinates
   *  \param phi array of phi anlges of cryostats in polar coordinates
   *  \param spin array of anlges for the rotations of the cryostats
   *         around their own axis
   *  \param transform array of transformation for positioning the cryostats
   *  \param mother mother volume, if this is not specified a mother
   *         volume is created (e.g. a MiniBallWorld object)
   *  \param histoManager a MiniBallHistoManager object for the readout
   *  \param capsule flag determining if the crystal capsule should be
   *         simulated
   *  \param cryowall flag determining if the aluminum wall of the cryostat
   *         should be simulated
   *  \see MiniBallHistoManager
   *  \see MiniBallWorld
   *  \see TRIPLE_CLUSTER
   */
  MiniBallDetectorArray(G4int nb_of_clusters, G4int* cluster_type,
			G4double* rho, G4double* theta, G4double* phi,
			G4double* spin,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(G4int nb_of_clusters, G4int* cluster_type,
			G4Transform3D* transform, 
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(G4VPhysicalVolume* mother, G4int nb_of_clusters,
			G4String* name, G4int* cluster_type,
			G4double* rho, G4double* theta, G4double* phi,
			G4double* spin,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(G4VPhysicalVolume* mother, G4int nb_of_clusters,
		       std::vector<G4String> name, std::vector<G4int> cluster_type,
		       std::vector<G4double> rho, std::vector<G4double> theta, 
		       std::vector<G4double> phi, std::vector<G4double> spin,
		       G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(G4VPhysicalVolume* mother, G4int nb_of_clusters,
		       std::vector<std::string> name, std::vector<G4int> cluster_type,
		       std::vector<G4double> rho, std::vector<G4double> theta, 
		       std::vector<G4double> phi, std::vector<G4double> spin,
		       G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(G4VPhysicalVolume* mother, G4int nb_of_clusters,
			G4String* name, G4int* cluster_type,
			G4Transform3D* transform,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4int nb_of_clusters, G4int* cluster_type,
			G4double* rho, G4double* theta, G4double* phi,
			G4double* spin,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
		       G4VPhysicalVolume* mother, G4int nb_of_clusters,
		       std::vector<G4String> name, std::vector<G4int> cluster_type,
		       std::vector<G4double> rho, std::vector<G4double> theta, 
		       std::vector<G4double> phi, std::vector<G4double> spin,
		       G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
		       G4VPhysicalVolume* mother, G4int nb_of_clusters,
		       std::vector<std::string> name, std::vector<G4int> cluster_type,
		       std::vector<G4double> rho, std::vector<G4double> theta, 
		       std::vector<G4double> phi, std::vector<G4double> spin,
		       G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4int nb_of_clusters, G4int* cluster_type,
			G4Transform3D* transform,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4VPhysicalVolume* mother,
			G4int nb_of_clusters,
			G4String* name, G4int* cluster_type,
			G4double* rho, G4double* theta, G4double* phi,
			G4double* spin,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4VPhysicalVolume* mother,
			G4int nb_of_clusters,
			G4String* name, G4int* cluster_type,
			G4Transform3D* transform,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4VPhysicalVolume* mother,
			G4int nb_of_clusters, G4int* cluster_type,
			G4double* rho, G4double* theta, G4double* phi,
			G4double* spin,
			G4bool capsule=true, G4bool cryowall=true);

  MiniBallDetectorArray(MiniBallHistoManager* histoManager,
			G4VPhysicalVolume* mother,
			G4int nb_of_clusters, G4int* cluster_type,
			G4Transform3D* transform,
			G4bool capsule=true, G4bool cryowall=true);

  // destructor
  ~MiniBallDetectorArray();

public:

  /** \brief construction of physical detector volumes
   *  
   *  To add a detector array in your own DetectorConstruction class
   *  create a MiniBallTripleCluster object and invoke the Construct()
   *  method.
   *
   *  \return mother volume
   */
  G4VPhysicalVolume* Construct();

  /** \brief sets the relative efficiency of a detector within a cryostat
   *
   *  When setting the realtive efficiency of a detector the dimensions of
   *  the crystal are scaled correspondingly. 
   *  This is only a rough approximation.
   *  See also the efficiency example HPGeEff for more detail.
   *
   *  \param cluster_nb number of cluster in the detector array 
   *                    (range 0..nb_of_cluster-1)
   *  \param percent relative efficiency of the detector in percent
   *  \see HPGeEff
   */
  void SetRelativeEfficiencyDetA(G4int cluster_nb, G4double percent);
  void SetRelativeEfficiencyDetB(G4int cluster_nb, G4double percent);
  void SetRelativeEfficiencyDetC(G4int cluster_nb, G4double percent);

  /** \brief sets the scaling factor for the efficiency correction
   *  of a detector within a cryostat
   *
   *  When setting the scaling factor for the efficiency correction 
   *  of a detector the dimensions of the crystal are scaled correspondingly. 
   *  This is only a rough approximation.
   *  See also the efficiency example HPGeEff for more detail.
   *
   *  \param cluster_nb number of cluster in the detector array
   *                    (range 0..nb_of_cluster-1)
   *  \param eff_fact efficiency factor (scaling factor)
   *  \see HPGeEff
   */
  void SetEfficiencyFactorDetA(G4int cluster_nb, G4double eff_fact);
  void SetEfficiencyFactorDetB(G4int cluster_nb, G4double eff_fact);
  void SetEfficiencyFactorDetC(G4int cluster_nb, G4double eff_fact);

  /** \brief sets the deadlayer thickness of a detector within a cryostat
   *
   *  This method sets the thickness of the deadlayer and the type of
   *  deadlayer implementation (possible values are: DEADLAYER_FRONT - only
   *  the front of the detector has a deadlayer (default), 
   *  DEADLAYER_OUTER_CONTACT - the whole outer contact has a deadlayer
   *  (more realistic, but slower)
   *
   *  \param cluster_nb number of cluster in the detector array
   *                    (range 0..nb_of_cluster-1)
   *  \param thickness thickness of the deadlayer
   *  \param type type of deadlayer implementation
   */
  void SetDeadlayerDetA(G4int cluster_nb,
			G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);
  void SetDeadlayerDetB(G4int cluster_nb,
			G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);
  void SetDeadlayerDetC(G4int cluster_nb,
			G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);

  void SetAllDeadlayer(G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);

  /** \brief sets the visualisation attributes for the detectors
   *
   *  \param pvis_att pointer to a G4VisAttributes object
   */
  void SetDetectorVisAttributes(const G4VisAttributes* pvis_att);

  /** \brief sets the visualisation attributes for the detectors
   *
   *  \param vis_att G4VisAttributes object
   */
  void SetDetectorVisAttributes(const G4VisAttributes& vis_att);

  /** \brief sets the visualisation attributes for the detector capsules
   *
   *  \param pvis_att pointer to a G4VisAttributes object
   */
  void SetCapsuleVisAttributes(const G4VisAttributes* pvis_att);

  /** \brief sets the visualisation attributes for the detector capsules
   *
   *  \param vis_att G4VisAttributes object
   */
  void SetCapsuleVisAttributes(const G4VisAttributes& vis_att);

  /** \brief sets the visualisation attributes for the cryostat
   *
   *  \param pvis_att pointer to a G4VisAttributes object
   */
  void SetCryostatVisAttributes(const G4VisAttributes* pvis_att);

  /** \brief sets the visualisation attributes for the cryostat
   *
   *  \param vis_att G4VisAttributes object
   */
  void SetCryostatVisAttributes(const G4VisAttributes& vis_att);

  /** \brief use the colors for the detectors as labeled on the cryostats
   *
   *  Use following colors: blue for detector A, 
   *  green for detector B and red for detector C
   */
  void UseLabeledDetectorColors() { use_labeled_colors=true; };
    
private:
  void GetTransformations(G4double* rho, G4double* theta,
			  G4double* phi, G4double* spin);

  void GetTransformations(std::vector<G4double> &rho, std::vector<G4double> &theta,
			  std::vector<G4double> &phi, std::vector<G4double> &spin);

  void PushBackDefaultParameters();

private:
  ///used histoManager
  MiniBallHistoManager* histoManager;

  G4VPhysicalVolume* mother;

  ///list of cryostats
  G4int nb_of_clusters;
  
  std::vector<G4VUserDetectorConstruction*> cluster;

  ///list of parameters
  std::vector<G4int> type;
  std::vector<G4Transform3D> transform;
  std::vector<G4String> name;

  std::vector<G4double> eff_factA;
  std::vector<G4double> eff_factB;
  std::vector<G4double> eff_factC;

  std::vector<G4double> deadlayerA;
  std::vector<G4double> deadlayerB;
  std::vector<G4double> deadlayerC;

  std::vector<G4int> deadlayer_typeA;
  std::vector<G4int> deadlayer_typeB;
  std::vector<G4int> deadlayer_typeC;

  G4bool capsule;
  G4bool cryowall;

  const G4VisAttributes* det_vis_att;
  const G4VisAttributes* capsule_vis_att;
  const G4VisAttributes* cryo_vis_att;
  
  G4bool use_labeled_colors;
};

#endif






