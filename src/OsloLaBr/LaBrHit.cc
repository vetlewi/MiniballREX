
#include "OsloLaBr/LaBrHit.hh"

#include <G4UnitsTable.hh>

#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

G4Allocator<LaBrHit> MiniBallHitAllocator;

LaBrHit::LaBrHit(const LaBrHit& right)
        : G4VHit()
{
    traceID    = right.traceID;
    detectorID = right.detectorID;
    edep       = right.edep;
    pos        = right.pos;
    posInDet   = right.posInDet;
    procName   = right.procName;
}

const LaBrHit& LaBrHit::operator=(const LaBrHit& right)
{
    traceID    = right.traceID;
    detectorID = right.detectorID;
    edep       = right.edep;
    pos        = right.pos;
    posInDet   = right.posInDet;
    procName   = right.procName;
    return *this;
}

int LaBrHit::operator==(const LaBrHit& right) const
{
    return (this==&right) ? 1 : 0;
}

void LaBrHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();

    if(pVVisManager)
    {
        G4Circle circle(pos);
        circle.SetScreenSize(0.04);
        circle.SetFillStyle(G4Circle::filled);
        G4Colour colour(1.,0.,0.);
        G4VisAttributes attribs(colour);
        circle.SetVisAttributes(attribs);
        pVVisManager->Draw(circle);
    }
}

void LaBrHit::Print()
{
    std::cout << " MiniBall: " << std::endl;
    std::cout << "  traceID: " << traceID
              << " energy deposit: " << G4BestUnit(edep, "Energy")
              << " position: " << G4BestUnit(pos, "Length")
              << " proc name: " << procName << std::endl;
    std::cout << "  detectorID: " << detectorID
              << " position in detector: " << G4BestUnit(posInDet, "Length")
              << std::endl;
}