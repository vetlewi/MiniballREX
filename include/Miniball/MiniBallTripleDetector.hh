/************************************************************************
 * \file MiniBallTripleDetector.hh
 *
 * \class MiniBallTripleDetector   
 * \brief Design of an MiniBall Triple-Cluster
 *
 * \author hans.boie@mpi-hd.mpg.de
 *
 ************************************************************************/

#ifndef MiniBallTripleDetector_H
#define MiniBallTripleDetector_H 1

#include "MiniBallSingleDetector.hh"

#include "math.h"

/// Design of an MiniBall Triple-Cluster
class MiniBallTripleDetector : public G4VUserDetectorConstruction
{
public:
  /** \brief Constructor for a triple-cluster detector
   * 
   *  The position of the triple-cluster can be specified in various 
   *  ways, e.g. by polar coordinates rho, phi, theta, or by a giving
   *  G4Transform3D. The parameter spin rotates the triple-cluster
   *  around its own axis (in the MiniBall colaboration this angle
   *  is sometimes also called alpha). The distance rho from the origin is
   *  taken with respect to the common sphere on which the crystal fronts
   *  are placed. To position the cluster with respect to the front plane
   *  of the cryostat add the value returned by the static method
   *  MiniBallTripleDetector::GetDistanceToFrontPlane(), similiar to 
   *  position the cluster with respect to the front of the cap use the
   *  method MiniBallTripleDetector::GetDistanceToFront(). 
   *  
   *  \param name name of the triple cluster 
   *  \param rho radius in polar coordinates
   *  \param theta theta angle in polar coordinates
   *  \param phi phi anlge in polar coordinates
   *  \param spin anlge for the rotation of the triple-cluster 
   *         around its own axis
   *  \param transform transformation to position the triple-cluster
   *  \param mother mother volume, if this is not specified a mother
   *         volume is created (e.g. a MiniBallWorld object)
   *  \param histoManager a MiniBallHistoManager object for the readout
   *  \param materials a MiniBallMaterial class
   *  \param capsule flag determining if the crystal capsule should be
   *         simulated
   *  \param cryowall flag determining if the aluminum wall of the cryostat
   *         should be simulated
   *  \see MiniBallHistoManager
   *  \see MiniBallMaterial
   *  \see MiniBallWorld
   */
 
  MiniBallTripleDetector(G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4VPhysicalVolume* mother, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(G4VPhysicalVolume* mother, G4double rho, 
			 G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4VPhysicalVolume* mother, G4double rho, 
			 G4double theta, G4double phi, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);
  
  MiniBallTripleDetector(G4VPhysicalVolume* mother, 
			 G4Transform3D* transform,
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(G4VPhysicalVolume* mother, G4Transform3D* transform,
			 G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false); 
  
  MiniBallTripleDetector(G4String name, G4VPhysicalVolume* mother, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(G4String name,
			 G4VPhysicalVolume* mother, G4double rho, 
			 G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4String name,
			 G4VPhysicalVolume* mother, G4double rho, 
			 G4double theta, G4double phi, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);
  
  MiniBallTripleDetector(G4String name, G4VPhysicalVolume* mother, 
			 G4Transform3D* transform,
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(G4String name,
			 G4VPhysicalVolume* mother, G4Transform3D* transform,
			 G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(G4double rho, G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4double rho, 
			 G4double theta, G4double phi, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4Transform3D* transform,
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(G4Transform3D* transform, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4VPhysicalVolume* mother, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4VPhysicalVolume* mother, 
			 G4double rho, G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4VPhysicalVolume* mother, 
                         G4double rho, G4double theta, 
			 G4double phi, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4VPhysicalVolume* mother, 
			 G4Transform3D* transform, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4VPhysicalVolume* mother, 
			 G4Transform3D* transform, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4String name, G4VPhysicalVolume* mother, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4String name, G4VPhysicalVolume* mother, 
			 G4double rho, G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4String name, G4VPhysicalVolume* mother, 
                         G4double rho, G4double theta, 
			 G4double phi, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4String name, G4VPhysicalVolume* mother, 
			 G4Transform3D* transform, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4String name, G4VPhysicalVolume* mother, 
			 G4Transform3D* transform, G4double spin, 
			 G4bool capsule=false, G4bool cryowall=false); 

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4double rho, G4double theta, G4double phi, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4double rho, G4double theta, G4double phi, 
			 G4double spin,
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4Transform3D* transform, 
			 G4bool capsule=false, G4bool cryowall=false);

  MiniBallTripleDetector(MiniBallHistoManager* histoManager,
			 G4Transform3D* transform, G4double spin,
			 G4bool capsule=false, G4bool cryowall=false);

  ~MiniBallTripleDetector();

public:
  /** \brief construction of physical detector volumes
   *  
   *  To add a triple-cluster detector in your own DetectorConstruction class
   *  create a MiniBallTripleCluster object and invoke the Construct()
   *  method.
   *
   *  \return mother volume
   */
  G4VPhysicalVolume* Construct();

  /** \brief returns the ID of the cryostat
   *
   *  The returned ID is needed to address the cryostat in the readout
   *
   *  \return ID of cryostat
   *  \see MiniBallHistoManager
   */
  G4int GetCryostatID() { return CryostatID; };

  /** \brief returns the ID of a detector within the cryostat
   *
   *  The returned ID is needed to address the detector in the readout
   *
   *  \return ID of detector 
   *  \see MiniBallHistoManager
   */
  G4int GetADetectorID() { return ADetectorID; };
  G4int GetBDetectorID() { return BDetectorID; };
  G4int GetCDetectorID() { return CDetectorID; };

  /** \brief returns the distance from the detector referrence sphere
   *         to the front of the cryostat cap 
   *
   *  The triple-cluster is positioned with respect to the common sphere
   *  on which the cryostal fronts are placed. To position the detector
   *  with respect to the front of the cryostat cap (including bump) add
   *  this value to your radius rho.
   *
   *  \return distance to front of the cryostat cap
   */
  static G4double GetDistanceToFront();

  /** \brief returns the distance from the detector referrence sphere
   *         to the front plane of the cryostat cap 
   *
   *  To position the detector with respect to the front plane 
   *  of the cryostat cap (NOT including bump) add
   *  this value to your radius rho.
   *
   *  \return distance to front plane of the cryostat cap
   */
  static G4double GetDistanceToFrontPlane();

  /** \brief sets the relative efficiency of a detector within the cryostat
   *
   *  When setting the realtive efficiency of a detector the dimensions of
   *  the crystal are scaled correspondingly. 
   *  This is only a rough approximation.
   *  See also the efficiency example HPGeEff for more detail.
   *
   *  \param percent relative efficiency of the detector in percent
   *  \see HPGeEff
   */
  void SetRelativeEfficiencyDetA(G4double percent);
  void SetRelativeEfficiencyDetB(G4double percent);
  void SetRelativeEfficiencyDetC(G4double percent);

  /** \brief sets the scaling factor for the efficiency correction
   *  of a detector within the cryostat
   *
   *  When setting the scaling factor for the efficiency correction 
   *  of a detector the dimensions of the crystal are scaled correspondingly. 
   *  This is only a rough approximation.
   *  See also the efficiency example HPGeEff for more detail.
   *
   *  \param eff_fact efficiency factor (scaling factor)
   *  \see HPGeEff
   */
  void SetEfficiencyFactorDetA(G4double eff_fact);
  void SetEfficiencyFactorDetB(G4double eff_fact);
  void SetEfficiencyFactorDetC(G4double eff_fact);

  /** \brief sets the deadlayer thickness of a detector within the cryostat
   *
   *  This method sets the thickness of the deadlayer and the type of
   *  deadlayer implementation (possible values are: DEADLAYER_FRONT - only
   *  the front of the detector has a deadlayer (default), 
   *  DEADLAYER_OUTER_CONTACT - the whole outer contact has a deadlayer
   *  (more realistic, but slower)
   *
   *  \param thickness thickness of the deadlayer
   *  \param type type of deadlayer implementation
   */
  void SetDeadlayerDetA(G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);
  void SetDeadlayerDetB(G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);
  void SetDeadlayerDetC(G4double thickness, G4int type=DEFAULT_DEADLAYER_TYPE);

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

  /** \brief use the colors for the detectors as labeled on the cryostat
   *
   *  Use following colors: blue for detector A, 
   *  green for detector B and red for detector C
   */
  void UseLabeledDetectorColors() { use_labeled_colors=true; };

  /** \brief visualize a cut cryostat
   *
   *  The geometry of the cryostat is simulated cut open to have a glance
   *  inside the structure of the simulated cryostat.
   * 
   *  \warning Only use this method for visualisation means!
   */
  void CutCryostatVisualisation();

  /** \brief visualize a cut detector capsules
   *
   *  The geometry of the detector capsule is simulated cut open 
   *  to have a glance inside the structure of the simulated capsule.
   * 
   *  \warning Only use this method for visualisation means!
   */
  void CutCapsuleVisualisation();

  /** \brief visualize a cut detectors
   *
   *  The geometry of the detector is simulated cut open 
   *  to have a glance inside the structure of the simulated detector.
   * 
   *  \warning Only use this method for visualisation means!
   */
  void CutDetectorVisualisation();

private:
  static G4double GetMaxRadius();

private:
  G4VPhysicalVolume* TripleCluster;
  
  MiniBallSingleDetector* HPGe_detector_1;
  MiniBallSingleDetector* HPGe_detector_2;
  MiniBallSingleDetector* HPGe_detector_3;

  G4int CryostatID;
  G4int ADetectorID;
  G4int BDetectorID;
  G4int CDetectorID;
  
  G4String name;
  G4VPhysicalVolume* mother;

  G4double rho;
  G4double phi;
  G4double theta;
  G4double spin;
  G4Transform3D* Cluster_transformation;

  G4bool capsule;
  G4bool cryowall;

  MiniBallHistoManager* histoManager;

  G4double eff_factA, eff_factB, eff_factC;

  G4double deadlayerA, deadlayerB, deadlayerC;
  G4int deadlayer_typeA, deadlayer_typeB, deadlayer_typeC;

  const G4VisAttributes* det_vis_att;
  const G4VisAttributes* capsule_vis_att;
  const G4VisAttributes* cryo_vis_att;
  
  G4bool use_labeled_colors;

  G4bool cryo_cut;
  G4bool capsule_cut;
  G4bool det_cut;
};

#endif






