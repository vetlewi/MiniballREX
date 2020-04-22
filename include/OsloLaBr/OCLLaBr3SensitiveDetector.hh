//
// Created by Vetle Wegner Ingeberg on 22/04/2020.
//

#ifndef OCLLABR3SENSITIVEDETECTOR_H
#define OCLLABR3SENSITIVEDETECTOR_H

#include <G4VSensitiveDetector.hh>

#include <OsloLaBr/LaBrHit.hh>

class MiniBallHistoManager;

class OCLLaBr3SensitiveDetector  : public G4VSensitiveDetector
{

public:
    OCLLaBr3SensitiveDetector(G4String name);
    OCLLaBr3SensitiveDetector(MiniBallHistoManager* HM, G4String name);
    ~OCLLaBr3SensitiveDetector() = default;

    void   Initialize(G4HCofThisEvent*);
    G4bool ProcessHits(G4Step*, G4TouchableHistory*);
    void   EndOfEvent(G4HCofThisEvent*);

    G4int GetDetectorID() { return detectorID; }

private:
    LaBrHitsCollection* hitsCollection;
    G4String HCname;

    MiniBallHistoManager* histoManager;

    G4int detectorID;
    G4int tracecounter;

    G4int HCID;
};

#endif // OCLLABR3SENSITIVEDETECTOR_H
