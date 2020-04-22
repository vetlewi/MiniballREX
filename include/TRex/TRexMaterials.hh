#ifndef TREXMATERIALS_HH_
#define TREXMATERIALS_HH_

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4OpticalSurface.hh"
#include "G4MaterialTable.hh"
#include "G4MaterialPropertiesTable.hh"
#include "G4NistManager.hh"
#include "G4LogicalBorderSurface.hh"

class TRexMaterials {
	public:
		static TRexMaterials* Get();
		~TRexMaterials() {}
		G4Material* GetMaterial(std::string name);

		G4NistManager* GetNistManager() { return fManager; }

	private:
		TRexMaterials(void);
		static TRexMaterials* fMaterials;

		void DefineIndex(void);
		void BuildAir(void);
		G4Material* BuildBc408(void);
		G4Material* BuildBc408_noOptical(void);
		G4Material* BuildPlexiglass(void);
		G4Material* BuildGlass(void);
		G4Material* BuildAluminium(void);
		G4Material* BuildBialkali(void);
		G4Material* BuildC4F10(void);
		G4Material* BuildC4F10_noOptical(void);
		G4Material* BuildDeuterium(void);
		G4Material* BuildDeuteratedPE(void);
		G4Material* BuildSolidDeuterium(void);

		void BuildSurfaceBc408Air(void);
		void BuildSurfaceAirBc408(void);
		void BuildSurfaceBc408Plexiglass(void);
		void BuildSurfacePlexiglassGlass(void);
		void BuildSurfacePlexiglassAir(void);
		void BuildSurfaceAirPlexiglass(void);
		void BuildSurfaceGlassVacuum(void);
		void BuildSurfaceVacuumBialkali(void);
		void BuildSurfaceAluminium(void);
		void BuildSurfaceMirror(void);

		G4NistManager* fManager;

		static const G4int nEntryLong = 12;
		static const G4int nEntryShort = 2;

		G4Element* fElH;
		G4Element* fElD;
		G4Element* fElC;
		G4Element* fElN;
		G4Element* fElO;
		G4Element* fElF;
		G4Element* fElFe;
		G4Element* fElRb;
		G4Element* fElMo;
		G4Element* fElSb;
		G4Element* fElCs;
		G4Element* fElCr;
		G4Element* fElNi;
		G4Element* fElCu;
		G4Isotope* fIso_H2;
		G4Element* fEle_D;

		G4OpticalSurface* fSurfaceBc408Air;
		G4OpticalSurface* fSurfaceAirBc408;
		G4OpticalSurface* fSurfaceBc408Plexiglass;
		G4OpticalSurface* fSurfacePlexiglassGlass;
		G4OpticalSurface* fSurfacePlexiglassAir;
		G4OpticalSurface* fSurfaceAirPlexiglass;
		G4OpticalSurface* fSurfaceGlassVacuum;
		G4OpticalSurface* fSurfaceVacuumBialkali;
		G4OpticalSurface* fSurfaceAluminium;
		G4OpticalSurface* fSurfaceMirror;

		G4double fBc408Index;
		G4double fBc408AbsorptionLength;
		G4double fBc408Yield;
		G4double fPlexiglassIndex;
		G4double fPlexiglassAbsLength;
		G4double fGlassIndex;
		G4double fAluminiumReflectivity;

		G4double fSpecularLobe[nEntryShort];
		G4double fSpecularSpike[nEntryShort];
		G4double fBackScatter[nEntryShort];

		G4double fPhotonEnergyShort[nEntryShort];
		G4double fPhotonEnergyLong[nEntryLong];

		G4double fAirRefractiveIndex[nEntryShort];
		G4double fAirAbsorpiton[nEntryShort];
		G4double fPlexiglassRefractiveIndex[nEntryShort];
		G4double fPlexiglassAbsorpiton[nEntryShort];
		G4double fGlassRefractiveIndex[nEntryShort];
		G4double fBc408RefractiveIndex[nEntryShort];
};

#endif /* TREXMATERIALS_HH_ */
