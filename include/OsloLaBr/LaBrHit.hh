//
// Created by Vetle Wegner Ingeberg on 22/04/2020.
//

#ifndef LABRHIT_H
#define LABRHIT_H

#include <TObject.h>
#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>
#include <Randomize.hh>


// Hit in a LaBr detector
class LaBrHit : public G4VHit
{
public:
    LaBrHit() = default;
    ~LaBrHit() = default;
    LaBrHit(const LaBrHit&);
    const LaBrHit& operator=(const LaBrHit&);
    int operator==(const LaBrHit&) const;

    inline void *operator new(size_t);
    inline void  operator delete(void *aHit);

    void Draw();
    void Print();

public:

    void SetTraceID   (G4int trace)      { traceID = trace; };
    void SetDetectorID(G4int det)        { detectorID = det; };
    void SetEdep      (G4double de)      { edep = de; };
    void SetPos       (G4ThreeVector xyz){ pos = xyz; };
    void SetPosInDet  (G4ThreeVector xyz){ posInDet = xyz; };
    void SetProcName  (G4String name)    { procName = name; };

    G4int GetTraceID()          { return traceID; };
    G4int GetDetectorID()       { return detectorID; };
    G4double GetEdep()          { return edep; };
    G4ThreeVector GetPos()      { return pos; };
    G4ThreeVector GetPosInDet() { return posInDet; };
    G4String GetProcName()      { return procName; };

private:

    G4int         traceID, detectorID;
    G4double      edep;
    G4ThreeVector pos, posInDet;
    G4String      procName;

};

typedef G4THitsCollection<LaBrHit> LaBrHitsCollection;

extern G4Allocator<LaBrHit> LaBrHitAllocator;

inline void* LaBrHit::operator new(size_t)
{
    void *aHit;
    aHit = (void *) LaBrHitAllocator.MallocSingle();
    return aHit;
}

inline void LaBrHit::operator delete(void *aHit)
{
    LaBrHitAllocator.FreeSingle((LaBrHit*) aHit);
}

#endif // LABRHIT_H
