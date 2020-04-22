/************************************************************************
 * \file MiniBallTrackingAction.hh
 *
 * \class MiniBallTrackingAction
 * \brief Actions that are taken for all secondaries of one primary event
 *
 * \author v.bildstein@mpi-hd.mpg.de
 *
 ************************************************************************/

#include "Miniball/MiniBallTrackingAction.hh"
#include "Miniball/MiniBallTrackInformation.hh"

#include <G4TrackingManager.hh>
#include <G4Track.hh>
#include <G4VProcess.hh>

MiniBallTrackingAction::MiniBallTrackingAction()
{;}

MiniBallTrackingAction::~MiniBallTrackingAction()
{;}

void MiniBallTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
   // Check if the track already has track information
  if(aTrack->GetUserInformation()!=0) return;


  // Check if the track has one creator process (not the case for primaries)
  const G4VProcess* creatorProcess = aTrack->GetCreatorProcess();
  if(!creatorProcess) return;

  MiniBallTrackInformation* anInfo = new MiniBallTrackInformation(aTrack);

  G4Track* theTrack = (G4Track*)aTrack;
  theTrack->SetUserInformation(anInfo);

}

void MiniBallTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  // Check if the track already has track information
  MiniBallTrackInformation* info
    = (MiniBallTrackInformation*)(aTrack->GetUserInformation());
  if(info==0) return;

  // Copy parent's track information to its daughters
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if(secondaries)
  {
    size_t nSeco = secondaries->size();
    for(size_t i=0;i<nSeco;i++)
    { 
      MiniBallTrackInformation* infoNew = new MiniBallTrackInformation(info);
      (*secondaries)[i]->SetUserInformation(infoNew);
    }
  }
}
