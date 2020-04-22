//////////////////////////////////////////////////////////////////////////////
/**  \file
 *   \brief filling of histogramms at the end of an event
 */ 
///////////////////////////////////////////////////////////////////////////////

#ifndef MiniBallEventAction_h
#define MiniBallEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class MiniBallHistoManager;

/// filling of histogramms at the end of an event
class MiniBallEventAction : public G4UserEventAction
{
public:
  MiniBallEventAction(MiniBallHistoManager *histoManager=NULL);
  ~MiniBallEventAction();
  
public:
  ///Actions that take place before the event is processed
  void BeginOfEventAction(const G4Event*);
  ///Actions that take place after the event has been dealed with
  void EndOfEventAction(const G4Event*);
  
private:
  MiniBallHistoManager* histoManager;
};

#endif

    
