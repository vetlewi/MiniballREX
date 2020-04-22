/*
 * TRexHit.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexHit.hh"

#include <G4ios.hh>
#include <G4UnitsTable.hh>
#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4Color.hh>
#include <G4VisAttributes.hh>
#include <G4Step.hh>
#include <G4TouchableHistory.hh>
#include <G4SystemOfUnits.hh>

// define allocator
G4Allocator<TRexHit> HitAllocator;

TRexHit::TRexHit() {
	// TODO Auto-generated constructor stub

}

TRexHit::TRexHit(const G4Step* aStep, G4TouchableHistory*) {
	SetParticle(aStep->GetTrack()->GetDefinition()->GetParticleName());
	SetParticleZ(aStep->GetTrack()->GetDefinition()->GetAtomicNumber());
	SetParticleA(aStep->GetTrack()->GetDefinition()->GetAtomicMass());
	SetParentID(aStep->GetTrack()->GetParentID());
	SetEnergyDeposition(aStep->GetTotalEnergyDeposit());
	SetKineticEnergy(aStep->GetPostStepPoint()->GetKineticEnergy());
	SetVertexKineticEnergy(aStep->GetTrack()->GetVertexKineticEnergy());
	SetTime(aStep->GetPostStepPoint()->GetGlobalTime());
	SetTrackID(aStep->GetTrack()->GetTrackID());

	// global position
	G4ThreeVector position = 0.5*(aStep->GetPreStepPoint()->GetPosition() + aStep->GetPostStepPoint()->GetPosition());
	SetHitPosition(position);

	// calculate local hit position
	G4TouchableHandle theTouchable = aStep->GetPreStepPoint()->GetTouchableHandle();
	G4ThreeVector localPosition = theTouchable->GetHistory()->GetTopTransform().TransformPoint(position);
	SetLocalHitPosition(localPosition);
}

TRexHit::~TRexHit() {
	// TODO Auto-generated destructor stub
}

// print
void TRexHit::Print() {
	std::cout << "particle = " << fParticle << " : " << fPos[0]/mm
		<< " mm , " << fPos[1]/mm << " mm , " << fPos[2]/mm
		<< " mm , process = " << fProcess << " , time = " << fTime
		<< "  , trackLength = " << fTrackLength
		<< "  , energy deposition = " << fEnergy
		<<  std::endl;
}

// draw
void TRexHit::Draw()
{
	G4VVisManager *visMan = G4VVisManager::GetConcreteInstance();
	if(visMan) {
		G4Circle circle(fPos);
		circle.SetScreenSize(5);
		circle.SetFillStyle(G4Circle::filled);
		G4Color color(1.0, 0.0, 0.5);
		G4VisAttributes attribs(color);
		circle.SetVisAttributes(attribs);
		visMan->Draw(circle);
	}
}
