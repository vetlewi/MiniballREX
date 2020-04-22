/*************************************************************************
 * 
 *  fill histogramms at the end of an event
 * 
 *************************************************************************/

#include "Miniball/MiniBallEventAction.hh"
#include "Miniball/MiniBallHistoManager.hh"
#include "Miniball/MiniBallHit.hh"
#include "Miniball/MBglobals.hh"

#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4HCofThisEvent.hh>
#include <G4VHitsCollection.hh>
#include <G4SDManager.hh>
#include <G4ios.hh>
#include <G4UnitsTable.hh>

using namespace std;

MiniBallEventAction::MiniBallEventAction(MiniBallHistoManager *HM)
  : histoManager(HM)
{ }

MiniBallEventAction::~MiniBallEventAction()
{ }

void MiniBallEventAction::BeginOfEventAction(const G4Event*)
{
  if(histoManager)
    histoManager->StartOfEvent();
}

void MiniBallEventAction::EndOfEventAction(const G4Event* evt)
{
  if(histoManager)
    {
      G4int event_id=evt->GetEventID();
      G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

      size_t nb_detectors = histoManager->GetNbOfDetectors();
      
      for(size_t det_id=0; det_id<nb_detectors; det_id++)
	{ 
	  //every detector has its own HitsCollection 
	  G4int HCID = histoManager->GetMBHitsCollectionID(det_id);
	  if(HCID<0)
	    {
	      std::cerr << "MiniBallHitsCollection of detector id "
		     << det_id << " is missing" << std::endl;
	      continue;
	    }

	  MiniBallHitsCollection* HPGeHC
	    = (MiniBallHitsCollection*)(HCE->GetHC(HCID));
	  
	  if(HPGeHC)
	    {
	      //Number of hits in the current detector during this event
	      G4int n_hit = HPGeHC->entries();
	      
	      for(G4int hit_nb=0; hit_nb<n_hit; hit_nb++)
		{
		  //every hit is prozessed singularly
		  histoManager->StartOfInteraction();
		  
		  //Energie deposited in the detector
		  G4double Edep = (*HPGeHC)[hit_nb]->GetEdep();
		  if(Edep>0)
		    {
		      //position in detector
		      G4ThreeVector positionID 
			= (*HPGeHC)[hit_nb]->GetPosInDet();
		      //position in world
		      G4ThreeVector positionIW
			= (*HPGeHC)[hit_nb]->GetPos();
		      G4int trace_id=(*HPGeHC)[hit_nb]->GetTraceID();
		     
		      size_t det_id = (*HPGeHC)[hit_nb]->GetDetectorID();
		      size_t seg_id = (*HPGeHC)[hit_nb]->GetSegmentID();
			  
		      histoManager->SetMBInteraction(det_id,
						     seg_id,
						     Edep,
						     event_id,
						     trace_id,
						     positionID,
						     positionIW);
		    }
		  histoManager->EndOfInteraction();
		}
	    }
	}
      histoManager->EndOfEvent();
    }
}




