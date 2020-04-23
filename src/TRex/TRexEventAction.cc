/*
 * TRexEventAction.cc
 *
 *  Created on: Jun 17, 2014
 *      Author: sklupp
 */

#include "TRex/TRexEventAction.hh"
#include "TRex/TRexSettings.hh"

#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4TrajectoryContainer.hh>
#include <G4Trajectory.hh>
#include <G4ios.hh>


TRexEventAction::TRexEventAction(TRexDetectorConstruction* detectorConst, MiniBallHistoManager* miniballHistoManager) :
  fDetectorConst(detectorConst),
  fMbHistoMan(miniballHistoManager),
  fTree(0),
  fDataOfDetectors(std::vector<std::vector<ParticleMC>* >(fDetectorConst->GetAllDetectors().size())),
  fMiniball(0),
  fIsHit(false),
  fMiniballHit(false) {
  // set resolution of detectors
  fMbHistoMan->SetAllSigma(CORE, TRexSettings::Get()->GetMiniballEnergyResolutionCore());
  fMbHistoMan->SetAllSigma(ALL_SEG, TRexSettings::Get()->GetMiniballEnergyResolutionSegment());

  // fill always the detector tree regardless if a detector was hit or not ?
  fWriteAllEvents = TRexSettings::Get()->WriteAllEvents();
}

TRexEventAction::~TRexEventAction() {
	ClearDetectorData();
}

void TRexEventAction::BeginOfEventAction(const G4Event*) {
	if(TRexSettings::Get()->SimulateGammas()) {
		// clear old event
		for(unsigned int i = 0; i < fMiniball->size(); i++) {
			(*fMiniball)[i].ClearGermanium();
		}

		fMiniball->clear();
	}
}

void TRexEventAction::EndOfEventAction(const G4Event* evt) {
	if(TRexSettings::Get()->SimulateGammas()) {
		MiniballEndOfEventAction(evt);
		CollectMiniballData();
	}

	CollectDataFromDetectors();

	fIsHit = false;

	// check if at least one detector is hit
	// ---> if yes, than fill the tree
	for(unsigned int i = 0; i < fDetectorConst->GetAllDetectors().size(); i++) {
		// loop over all sub-detectors
		for(unsigned int ii = 0; ii < fDataOfDetectors[i]->size(); ii++) {
			if((*fDataOfDetectors[i])[ii].GetEdet() > 0.001 ||
					(*fDataOfDetectors[i])[ii].GetRingNr().size()  > 0 || (*fDataOfDetectors[i])[ii].GetStripNr().size() > 0) {
				//cout << "detector = " << i << " , subDetector = " << ii << endl;
				fIsHit = true;
			}
		}
	}

	if(fIsHit == true || fMiniballHit == true || fWriteAllEvents == true) {
		fTree->Fill();
	}

	// periodic printing
	G4int event_id = evt->GetEventID();

	if(event_id < 100) {
		std::cout<<">>> Event "<<evt->GetEventID()<<"\r"<<std::flush;
	} else if(event_id == 100 || event_id%1000 == 0) {
		std::cout<<">>> Event "<<evt->GetEventID()<<"\r"<<std::endl;
	}
}

void TRexEventAction::MiniballEndOfEventAction(const G4Event* evt) {
	G4int event_id = evt->GetEventID();
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();

	for(int det_id = 0; det_id < fMbHistoMan->GetNbOfDetectors(); det_id++) {
		//every detector has its own HitsCollection
		G4int HCID = fMbHistoMan->GetMBHitsCollectionID(det_id);

		if(HCID < 0) {
			std::cout << "MiniBallHitsCollection of detector id "<< det_id << " is missing" << std::endl;
			continue;
		}

		MiniBallHitsCollection* HPGeHC = (MiniBallHitsCollection*)(HCE->GetHC(HCID));

		if(HPGeHC != NULL) {
			// loop over all hits in the current detector during this event

			//if(HPGeHC->entries() > 0) {
			//	cout << "nbOfHits in detector " << det_id << " (clu = " << det_id / 3 << " , cry = " << det_id % 3 << ") : " << HPGeHC->entries() << endl;
			//}

			for(int hit_nb = 0; hit_nb < HPGeHC->entries(); hit_nb++) {
				//every hit is prozessed singularly
				fMbHistoMan->StartOfInteraction();

				//every hit is not prozessed singularly (doe NOT use !!)
				//fMbHistoMan->StartOfEvent();

				// energy deposited in the detector
				G4double Edep = (*HPGeHC)[hit_nb]->GetEdep();

				// if(Edep > 2000*keV) {
				// 	cout << "Edep = " << Edep / keV << " , nbOfHits in detector " << det_id << " (clu = " << det_id / 3 << " , cry = " << det_id % 3 << ") : " << HPGeHC->entries() << endl;
				// }

				if(Edep > 0) {
					//position in detector
					G4ThreeVector positionID = (*HPGeHC)[hit_nb]->GetPosInDet();
					//position in world
					G4ThreeVector positionIW = (*HPGeHC)[hit_nb]->GetPos();
					G4int trace_id = (*HPGeHC)[hit_nb]->GetTraceID();

					size_t det_id = (*HPGeHC)[hit_nb]->GetDetectorID();
					size_t seg_id = (*HPGeHC)[hit_nb]->GetSegmentID();

					fMbHistoMan->SetMBInteraction(det_id, seg_id, Edep, event_id, trace_id, positionID, positionIW);

					//if(data->MiniballEndOfEventAction) {
					//MiniBallEventAction::EndOfEventAction(evt);
					//}
				}
			} // loop over all hits
		}//if(HPGeHC)

	}// loop over all detectors

	//fMbHistoMan->AddGaussian();
}

void TRexEventAction::CollectDataFromDetectors() {
	//clear old data
	ClearDetectorData();
	// loop over all detectors
	for(unsigned int i = 0; i < fDetectorConst->GetAllDetectors().size(); i++) {
		//cout << "Collecting data ...." << endl;
		//fDataOfDetectors.push_back(fDetectorConst->GetAllDetectors()[i]->GetParticleMC()); // not working !!!
		//fDataOfDetectors[i]=(fDetectorConst->GetAllDetectors()[i]->GetParticleMC());
		fDataOfDetectors[i] = (fDetectorConst->GetAllDetectors()[i]->GetParticleMCvector());
	}
}

void TRexEventAction::ClearDetectorData() {
	for(unsigned int i =0; i < fDataOfDetectors.size(); i++)	{
		delete fDataOfDetectors[i];
		fDataOfDetectors[i] = 0;
	}
}

void TRexEventAction::CollectMiniballData() {
	// clear old event
	for(unsigned int i = 0; i < fMiniball->size(); i++) {
		(*fMiniball)[i].ClearGermanium();
	}

	fMiniball->clear();

	std::vector<MiniBallCryostatHisto*>* cryostats = fMbHistoMan->GetCryostats();

	// loop over all clusters
	for(unsigned int c = 0; c < cryostats->size(); c++) {
		Germanium Cluster;
		Cluster.SetCluID(c);
		fMiniballHit = false;

		double time = 0.;

		// loop over all crystals
		for(unsigned int cry = 0; cry < (*cryostats)[c]->detectorIDs.size(); cry++) {
			unsigned int det = (*cryostats)[c]->detectorIDs[cry];

			std::vector<MiniBallDetectorHisto*>* detectors = fMbHistoMan->GetDetectors();

			// check if crystal was hit
			if((*detectors)[det]->CoreEnAccu > 0) {
				Cluster.SetCore(cry, (*detectors)[det]->CoreEnAccu/keV, time);

				//cout << "coreE = " << (*detectors)[det]->CoreEnAccu/keV << endl;

				// loop over all segments
				for(int seg = 0; seg < NB_OF_SEGMENTS; seg++) {
					// check if segment was hit
					if((*detectors)[det]->SegmentEnAccu[seg] > 0) {
						//cout << "segE = " << (*detectors)[det]->SegmentEn[seg]/keV << endl;
						Cluster.SetSegment(cry, seg, (*detectors)[det]->SegmentEnAccu[seg]/keV,time);
					}
				}
				fMiniballHit = true;
			}
		}
		if(fMiniballHit) {
			fMiniball->push_back(Cluster);
		}
	}

	// resets all entries for accumulation of energy during an event
	fMbHistoMan->InitMBAccumulation();
	//resets all entries
	fMbHistoMan->InitMBInteraction();
}

void TRexEventAction::SetTree(TTree *tree) {
	fTree = tree;
}

void TRexEventAction::CreateBranches() {
	// loop over all detectors
	for(unsigned int i = 0; i < fDetectorConst->GetAllDetectors().size(); i++) {
		//cout << fDetectorConst->GetAllDetectors()[i]->GetName() << endl;
		fTree->Branch((fDetectorConst->GetAllDetectors()[i]->GetName() + "MC").c_str(), &(fDataOfDetectors[i]));
	}

	if(TRexSettings::Get()->SimulateGammas()) {
		// include Miniball in the tree
		fTree->Branch("Miniball", &fMiniball);
	}
}
