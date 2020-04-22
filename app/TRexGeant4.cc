/*
 * TRexGeant4.cc
 *
 *  Created on: Jun 15, 2014
 *      Author: sklupp
 */

#include <G4RunManager.hh>
#include <G4MTRunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>

#ifdef G4VIS_USE
#include <G4VisExecutive.hh>
//#include <G4OpenGLStoredX.hh>
#include <G4OpenGLStoredQt.hh>
#endif

#include <TRex/TRexDetectorConstruction.hh>
//#include "TRexPhysicsList.hh"
#include <TRex/PhysicsList.hh>
#include <TRex/TRexPrimaryGeneratorAction.hh>
#include <TRex/TRexRunAction.hh>
#include <TRex/TRexEventAction.hh>
#include <TRex/TRexData.hh>
#include <TRex/TRexSettings.hh>

#include <Miniball/MiniBallHistoManager.hh>
#include <Miniball/MiniBallHistoGenerator.hh>
#include <Miniball/MiniBallRootGenerator.hh>

#include <Randomize.hh>

#include <thread>


using namespace std;
using namespace CLHEP;

int main(int argc,char** argv) {
  // class to organize command line
  TRexData data(argc, argv);

  // class which contains the settings stored in the settings file
  TRexSettings::Get()->ReadSettingsFile(data.GetSettingsFileName());

  // choose the Random engine
  HepRandom::setTheEngine(new RanecuEngine);
  G4long seed;
  seed = time(0);
  HepRandom::setTheSeed(seed);

  // Construct the default run manager  //
#if USE_MT
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(std::thread::hardware_concurrency());
#else
    G4RunManager* runManager = new G4RunManager;
#endif // USE_MT

  // initalize Miniball
  MiniBallRootGenerator* miniballHistoGen = new MiniBallRootGenerator(data.GetOutputFileName(), 5);
  MiniBallHistoManager* miniballHistoManager = new MiniBallHistoManager(miniballHistoGen);
  miniballHistoManager->SetMBTupleType(EVENT);
  miniballHistoManager->SetEnergyUnit(keV);

  // set mandatory initialization classes  //
  G4VUserDetectorConstruction* detector = new TRexDetectorConstruction(miniballHistoManager);
  runManager->SetUserInitialization(detector);

  //G4VUserPhysicsList* physics = new TRexPhysicsList;
  G4VUserPhysicsList* physics = new PhysicsList;
  runManager->SetUserInitialization(physics);

  runManager->Initialize();

  // set mandatory user action class
  G4VUserPrimaryGeneratorAction* gen_action = new TRexPrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);

  G4UserEventAction* event_action = new TRexEventAction((TRexDetectorConstruction*) detector, miniballHistoManager);
  runManager->SetUserAction(event_action);

  G4UserRunAction* run_action = new TRexRunAction(data, (TRexPrimaryGeneratorAction*)gen_action, (TRexEventAction*) event_action);
  runManager->SetUserAction(run_action);


  // Initialize G4 kernel
  //runManager->Initialize();

  // visualization
  #ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  //visManager->RegisterGraphicsSystem(new G4OpenGLStoredX);
  visManager->RegisterGraphicsSystem(new G4OpenGLStoredQt);
  visManager->Initialize();
  #endif

  // define UI terminal
  //G4UIsession* session = new G4UIterminal(new G4UItcsh);

  // run command
  data.run(runManager, argc, argv);

  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
  delete runManager;
  #ifdef G4VIS_USE
  delete visManager;
  #endif
  //delete session;

  return 0;
}





