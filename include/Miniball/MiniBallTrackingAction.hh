/************************************************************************
 * \file MiniBallTrackingAction.hh
 *
 * \class MiniBallTrackingAction
 * \brief Actions that are taken for all secondaries of one primary event
 *
 * \author v.bildstein@mpi-hd.mpg.de
 *
 ************************************************************************/

#ifndef MiniBallTrackingAction_h
#define MiniBallTrackingAction_h 

class G4Track;
#include "G4UserTrackingAction.hh"
#include "globals.hh"

class MiniBallTrackingAction : public G4UserTrackingAction 
{
  public:
    MiniBallTrackingAction();
    virtual ~MiniBallTrackingAction();
   
    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

  private:
};

#endif
