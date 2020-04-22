/*
 * TRexHit.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXHIT_HH_
#define TREXHIT_HH_

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"


class G4Step;
class G4TouchableHistory;

class TRexHit : public G4VHit {
	public:
		TRexHit();
		TRexHit(const G4Step * aStep, G4TouchableHistory* ROHist);

		virtual ~TRexHit();

		// memory allocation operators
		inline void* operator new(size_t);
		inline void operator delete(void*);

		// verbose operators
		void Draw();
		void Print();

		// set and get methods
		G4ThreeVector GetHitPosition() { return fPos; }
		G4ThreeVector GetLocalHitPosition() { return fLocalPos; }
		G4String GetParticle() { return fParticle; }
		G4int GetParticleZ() { return fParticleZ; }
		G4int GetParticleA() { return fParticleA; }
		G4int GetParentID() { return fParentID; }
		G4String GetProcess() { return fProcess; }
		G4double GetTime() { return fTime; }
		G4int GetTrackID() { return fTrackID; }
		G4double GetTrackLength() { return fTrackLength; }
		G4double GetEnergyDeposition() { return fEnergy; }
		G4double GetKineticEnergy() { return fKinEnergy; }
		G4String GetCreatorProcess() { return fCreatorProcess; }
		G4double GetVertexKineticEnergy() { return fVertexKinEnergy; }
		G4ThreeVector GetVertexPosition() { return fVertexPos; }
		G4String GetVertexLogicalVolume() { return fLogVol; }

		void SetHitPosition(G4ThreeVector pos) { fPos = pos; }
		void SetLocalHitPosition(G4ThreeVector localPos) { fLocalPos = localPos; }
		void SetParticle(G4String particle) { fParticle = particle; }
		void SetParticleZ(G4int particleZ) { fParticleZ = particleZ; }
		void SetParticleA(G4int particleA) { fParticleA = particleA; }
		void SetParentID(G4int parentID) { fParentID = parentID; }
		void SetProcess(G4String process) { fProcess = process; }
		void SetTime(G4double time) { fTime = time; }
		void SetTrackID(G4int trackID) { fTrackID = trackID; }
		void SetTrackLength(G4double trackLength) { fTrackLength = trackLength; }
		void SetEnergyDeposition(G4double energy) { fEnergy = energy; }
		void SetKineticEnergy(G4double kinEnergy) { fKinEnergy = kinEnergy; }
		void SetCreatorProcess(G4String creatorProcess) { fCreatorProcess = creatorProcess; }
		void SetVertexKineticEnergy(G4double vertexKinEnergy) { fVertexKinEnergy = vertexKinEnergy; }
		void SetVertexPosition(G4ThreeVector vertexPos) { fVertexPos = vertexPos; }
		void SetVertexLogicalVolume(G4String logVol) { fLogVol = logVol; }

	private:
		G4ThreeVector fPos;
		G4ThreeVector fLocalPos;
		G4String fParticle;
		G4int fParticleZ;
		G4int fParticleA;
		G4int fParentID;
		G4String fProcess;
		G4double fTime;
		G4int fTrackID;
		G4double fTrackLength;
		G4double fEnergy;
		G4double fKinEnergy;
		G4String fCreatorProcess;
		G4double fVertexKinEnergy;
		G4ThreeVector fVertexPos;
		G4String fLogVol;
};

typedef G4THitsCollection<TRexHit> TRexHitsCollection;

extern G4Allocator<TRexHit> HitAllocator;

inline void* TRexHit::operator new(size_t) {
	void* aHit;
	aHit = (void*) HitAllocator.MallocSingle();
	return aHit;
}

inline void TRexHit::operator delete(void* aHit) {
	HitAllocator.FreeSingle((TRexHit*) aHit);
}

#endif /* TREXHIT_HH_ */
