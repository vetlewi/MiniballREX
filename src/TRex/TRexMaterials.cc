#include "TRex/TRexMaterials.hh"
#include "TRex/TRexSettings.hh"

#include <Miniball/MiniBallMaterial.hh>

#include <G4PhysicalConstants.hh>
#include <G4SystemOfUnits.hh>

#include <string>
#include <iomanip>
#include <ios>

TRexMaterials* TRexMaterials::fMaterials = NULL;

TRexMaterials* TRexMaterials::Get() {
	if(fMaterials == NULL) {
		fMaterials = new TRexMaterials();
	}
	return fMaterials;
}

TRexMaterials::TRexMaterials() {
    fMaterials = this;
	DefineIndex();

	fManager = G4NistManager::Instance();

	fElH = fManager->FindOrBuildElement("H");
	fElC = fManager->FindOrBuildElement("C");
	fElN = fManager->FindOrBuildElement("N");
	fElO = fManager->FindOrBuildElement("O");
	fElF = fManager->FindOrBuildElement("F");
	fElFe = fManager->FindOrBuildElement("Fe");
	fElRb = fManager->FindOrBuildElement("Rb");
	fElMo = fManager->FindOrBuildElement("Mo");
	fElSb = fManager->FindOrBuildElement("Sb");
	fElCs = fManager->FindOrBuildElement("Cs");
	fElNi = fManager->FindOrBuildElement("Ni");
	fElCr = fManager->FindOrBuildElement("Cr");
	fElCu = fManager->FindOrBuildElement("Cu");

	fIso_H2 = new G4Isotope("H2",1,2,2.014*g/mole);
	fElD = new G4Element("Deuterium Atom","D",1);
	fElD->AddIsotope(fIso_H2, 100.*perCent);

	BuildAir();
	BuildBc408();
	BuildBc408_noOptical();
	BuildPlexiglass();
	BuildGlass();
	G4Material* aluminium = BuildAluminium();
	BuildBialkali();
	BuildC4F10();
	BuildC4F10_noOptical();
	BuildDeuterium();
	BuildDeuteratedPE();
	BuildSolidDeuterium();

	G4Material* c2h6 = new G4Material("c2h6", 1.290 * mg/cm3, 2);
	c2h6->AddElement(fElC, 0.25);
	c2h6->AddElement(fElH, 0.75);

	G4Material* neon = fManager->FindOrBuildMaterial("G4_Ne");
	neon->SetName("neon");

	G4Material* borosilicate = fManager->FindOrBuildMaterial("G4_Pyrex_Glass");
	borosilicate->SetName("borosilicate");

	G4Material* plasticFoam = new G4Material("PlasticFoam", 0.15 * g/cm3, 3);
	plasticFoam->AddElement(fElC, 2);
	plasticFoam->AddElement(fElH, 2);
	plasticFoam->AddElement(fElO, 1);

	G4Material* carbonFibre = new G4Material("CarbonFibre", 1.8 * g/cm3, 2);
	carbonFibre->AddElement(fElC, 10);
	carbonFibre->AddElement(fElN, 1);

	G4Material* carbonLH2 = new G4Material("carbonLH2", 2.073 * g/cm3, 2);
	carbonLH2->AddElement(fElC, 10);
	carbonLH2->AddElement(fElN, 1);

	G4Material* epoxy = new G4Material("epoxy", 1.2 * g/cm3, 3);
	epoxy->AddElement(fElC, 21);
	epoxy->AddElement(fElH, 25);
	epoxy->AddElement(fElO, 5);

	G4Material* concrete = fManager->FindOrBuildMaterial("G4_CONCRETE");
	concrete->SetName("concrete");

	G4Material* beryllium = fManager->FindOrBuildMaterial("G4_Be");
	beryllium->SetName("beryllium");

	G4Material* lh2 = fManager->FindOrBuildMaterial("G4_lH2");
	lh2->SetName("LH2");

	G4Material* mylar = fManager->FindOrBuildMaterial("G4_MYLAR");
	mylar->SetName("mylar");

	G4Material* stainlessSteel = new G4Material("Stainless Steel",
			7.9 * g/cm3, 3, kStateSolid, 50.0 * kelvin, 1.0 * atmosphere);
	stainlessSteel->AddElement(fElC, 1);
	stainlessSteel->AddElement(fElFe, 10);
	stainlessSteel->AddElement(fElMo, 1);

	G4Material* polyethylene = fManager->FindOrBuildMaterial("G4_POLYETHYLENE");
	polyethylene->SetName("polyethylene");

	G4Material* polypropylene = fManager->FindOrBuildMaterial("G4_POLYPROPYLENE");
	polypropylene->SetName("polypropylene");

	G4Material* polystyrene = fManager->FindOrBuildMaterial("G4_POLYSTYRENE");
	polystyrene->SetName("polystyrene");

	//fManager->BuildMaterialWithNewDensity("airexC70", "G4_POLYVINYL_CHLORIDE", 40 * kg/m3);

	G4Material* bgo = fManager->FindOrBuildMaterial("G4_BGO");
	bgo->SetName("BGO");

	G4Material* iron = fManager->FindOrBuildMaterial("G4_Fe");
	iron->SetName("iron");

	G4Material* silver = fManager->FindOrBuildMaterial("G4_Ag");
	silver->SetName("silver");

	G4Material* helium = fManager->FindOrBuildMaterial("G4_He");
	helium->SetName("helium");

	G4Material* argon = fManager->FindOrBuildMaterial("G4_Ar");
	argon->SetName("argon");

	G4Material* co2 = fManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
	co2->SetName("CO2");

	G4Material* copper = fManager->FindOrBuildMaterial("G4_Cu");
	copper->SetName("copper");

	G4Material* gold = fManager->FindOrBuildMaterial("G4_Au");
	gold->SetName("gold");

	G4Material* lead = fManager->FindOrBuildMaterial("G4_Pb");
	lead->SetName("lead");

	G4Material* ethan = fManager->FindOrBuildMaterial("G4_ETHANE");
	ethan->SetName("ethan");

	G4Material* cf4 = new G4Material("CF4", 3.72 * mg/cm3, 2);
	cf4->AddElement(fElC, 1);
	cf4->AddElement(fElF, 4);

	G4Material* g11 = new G4Material("G11", 1.9 * g/cm3, 3);
	g11->AddElement(fElC, 5);
	g11->AddElement(fElH, 8);
	g11->AddElement(fElO, 2);

	G4Material* dc4gas = new G4Material("dc4gas", 1.65 * mg/cm3, 3); // density = 1.37 * density_air
	dc4gas->AddMaterial(argon, 0.45);
	dc4gas->AddMaterial(ethan, 0.45);
	dc4gas->AddMaterial(cf4, 0.1);

	G4Material* strawGas = new G4Material("strawGas", 2.08 * mg/cm3, 3);
	strawGas->AddMaterial(argon, 0.74);
	strawGas->AddMaterial(co2, 0.06);
	strawGas->AddMaterial(cf4, 0.20);

	G4Material* w45Gas = new G4Material("w45Gas", 1.88 * mg/cm3, 3);
	w45Gas->AddMaterial(argon, 0.85);
	w45Gas->AddMaterial(co2, 0.05);
	w45Gas->AddMaterial(cf4, 0.10);

	G4Material* mw1Gas = new G4Material("mw1Gas", 1.716 * mg/cm3, 2);
	mw1Gas->AddMaterial(argon, 0.7);
	mw1Gas->AddMaterial(co2, 0.3);

	G4Material* mw2Gas = new G4Material("mw2Gas", 1.41 * mg/cm3, 2); // density = 1.17 * density_air
	mw2Gas->AddMaterial(argon, 0.75);
	mw2Gas->AddMaterial(ethan, 0.25);

	G4Material* ecalShashlik = new G4Material("ecalShashlik", 4.639 * g/cm3,
			2);
	ecalShashlik->AddMaterial(lead, 0.348);
	ecalShashlik->AddMaterial(polystyrene, 0.652);

	G4Material* ecalMainz = new G4Material("ecalMainz", 5.176 * g/cm3, 2);
	ecalMainz->AddMaterial(lead, 0.4);
	ecalMainz->AddMaterial(polystyrene, 0.6);

	G4Material* ecalOlga = new G4Material("ecalOlga", 4.49 * g/cm3, 2);
	ecalOlga->AddMaterial(lead, 0.33);
	ecalOlga->AddMaterial(polystyrene, 0.67);

	G4Material* hcal1Material = new G4Material("hcal1Material", 6.51 * g/cm3,
			2);
	hcal1Material->AddMaterial(iron, 0.8);
	hcal1Material->AddMaterial(polystyrene, 0.2);

	G4Material* hcal2Material = new G4Material("hcal2Material", 10.25 * g/cm3,
			2);
	hcal2Material->AddMaterial(lead, 0.893);
	hcal2Material->AddMaterial(polystyrene, 0.107);

	G4Material* kapton = new G4Material("Kapton", 1.42 * g/cm3, 4);
	kapton->AddElement(fElH, 0.0273);
	kapton->AddElement(fElC, 0.7213);
	kapton->AddElement(fElN, 0.0765);
	kapton->AddElement(fElO, 0.1749);

	G4Material* plastic = fManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	plastic->SetName("plastic");

	G4Material* rohacell = new G4Material("rohacell", 51.3 * kg/m3, 4); // C9 H13 N O2  0.0513 g/cc
	rohacell->AddElement(fElC, 9);
	rohacell->AddElement(fElH, 13);
	rohacell->AddElement(fElN, 1);
	rohacell->AddElement(fElO, 2);

	G4Material* innox = new G4Material("innox", 7.90 * g/cm3, 3);
	innox->AddElement(fElC, 0.002737583);
	innox->AddElement(fElCr, 0.664841611);
	innox->AddElement(fElNi, 0.332420806);

	G4Material* silicon = fManager->FindOrBuildMaterial("G4_Si");
	silicon->SetName("silicon");

	G4Material* siliconMaterial = fManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
	siliconMaterial->SetName("silicondioxide");

	G4Material* gemMaterial = new G4Material("gem-material", 4.49 * g/cm3, 2);
	gemMaterial->AddMaterial(kapton, 0.91);
	gemMaterial->AddMaterial(copper, 0.09);

	G4Material* mwpcGas = new G4Material("mwpcGas", 2.08 * mg/cm3, 3);
	mwpcGas->AddMaterial(argon, 0.74);
	mwpcGas->AddMaterial(co2, 0.06);
	mwpcGas->AddMaterial(cf4, 0.20);

	G4Material* mwpcMaterial = new G4Material("mwpc-material", 4.49 * g/cm3, 2);
	mwpcMaterial->AddMaterial(mwpcGas, 0.893);
	mwpcMaterial->AddMaterial(polystyrene, 0.107);

	G4Material* micromegasGas = new G4Material("micromegasGas", 0.95 * mg/cm3, 3);
	micromegasGas->AddMaterial(neon, 0.80);
	micromegasGas->AddMaterial(c2h6, 0.1);
	micromegasGas->AddMaterial(cf4, 0.1);

	G4Material* micromegasMaterial = new G4Material("micromega-material",
			4.49 * g/cm3, 4);
	micromegasMaterial->AddMaterial(micromegasGas, 0.893);
	micromegasMaterial->AddMaterial(polystyrene, 0.047);
	micromegasMaterial->AddMaterial(plastic, 0.05);
	micromegasMaterial->AddMaterial(aluminium, 0.01);

	G4Material* pixelGEMMaterial = new G4Material("pgem-material",
			4.49 * g/cm3, 2);
	pixelGEMMaterial->AddMaterial(kapton, 0.91);
	pixelGEMMaterial->AddMaterial(copper, 0.09);

	G4Material* richwallGas = new G4Material("w45Gas", 2.08 * mg/cm3, 3);
	richwallGas->AddMaterial(argon, 0.74);
	richwallGas->AddMaterial(co2, 0.06);
	richwallGas->AddMaterial(cf4, 0.20);

	G4Material* richWallMaterial = new G4Material("richwall-material",
			4.49 * g/cm3, 3);
	richWallMaterial->AddMaterial(aluminium, 0.044);
	richWallMaterial->AddMaterial(stainlessSteel, 0.015);
	richWallMaterial->AddMaterial(richwallGas, 0.941);

	G4Material* fiberGlass = new G4Material("fiberGlass", 2.5 * g/cm3, 5);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE"),  0.54);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_BORON_OXIDE"), 0.10);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_CALCIUM_OXIDE"), 0.175);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_ALUMINUM_OXIDE"), 0.14);
	fiberGlass->AddMaterial(fManager->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE"), 0.045);

	G4Material* pcb = new G4Material("pcb", 1.8 * g/cm3, 3);
	pcb->AddMaterial(fiberGlass, 0.70);
	pcb->AddMaterial(epoxy, 0.25);
	pcb->AddElement(fElCu, 0.05);

	BuildSurfaceBc408Air();
	BuildSurfaceAirBc408();
	BuildSurfaceBc408Plexiglass();
	BuildSurfacePlexiglassGlass();
	BuildSurfacePlexiglassAir();
	BuildSurfaceAirPlexiglass();
	BuildSurfaceGlassVacuum();
	BuildSurfaceVacuumBialkali();
	BuildSurfaceAluminium();
	BuildSurfaceMirror();

	//build target material
	if(TRexSettings::Get()->GetGasTargetLength() > 0.) {
		fManager->ConstructNewGasMaterial("target", TRexSettings::Get()->GetTargetMaterialName(), STP_Temperature, TRexSettings::Get()->GetTargetPressure());
	} else {
		G4Material* material = GetMaterial(TRexSettings::Get()->GetTargetMaterialName());
		G4Material* target = new G4Material("target", material->GetDensity(), material->GetNumberOfElements());
		for(size_t i = 0; i < material->GetNumberOfElements(); ++i) {
			target->AddElement(material->GetElementVector()->at(i), material->GetFractionVector()[i]);
		}
	}

	//build chamber gas material
	fManager->ConstructNewGasMaterial("chamberGas", TRexSettings::Get()->GetVacuumChamberGas(), STP_Temperature, TRexSettings::Get()->GetVacuumChamberGasPressure());
}

void TRexMaterials::DefineIndex() {
	fBc408Index = 1.58;
	fBc408AbsorptionLength = 3.80 * m; // bulk light attenuation length
	fBc408Yield = 0.64 * 2 / (100 * eV); // 64% anthracene
	fPlexiglassIndex = 1.49;
	fPlexiglassAbsLength = 10.0 * m;
	fGlassIndex = 1.474;
	fAluminiumReflectivity = 0.97;

	fSpecularLobe[0] = 1.0;
	fSpecularLobe[1] = 1.0;
	fSpecularSpike[0] = 0.0;
	fSpecularSpike[1] = 0.0;
	fBackScatter[0] = 0.0;
	fBackScatter[1] = 0.0;

	fPhotonEnergyShort[0] = 2.0 * eV; // 619.92 nm
	fPhotonEnergyShort[1] = 7.14 * eV; // 173.65 nm
	fPhotonEnergyLong[0] = 2.08 * eV; // 596.08 nm
	fPhotonEnergyLong[1] = 2.38 * eV; // 520.94 nm
	fPhotonEnergyLong[2] = 2.58 * eV; // 480.56 nm
	fPhotonEnergyLong[3] = 2.70 * eV; // 459.20 nm
	fPhotonEnergyLong[4] = 2.76 * eV; // 449.22 nm
	fPhotonEnergyLong[5] = 2.82 * eV; // 439.66 nm
	fPhotonEnergyLong[6] = 2.92 * eV; // 424.60 nm
	fPhotonEnergyLong[7] = 2.95 * eV; // 420.29 nm
	fPhotonEnergyLong[8] = 3.02 * eV; // 410.54 nm
	fPhotonEnergyLong[9] = 3.10 * eV; // 399.95 nm
	fPhotonEnergyLong[10] = 3.26 * eV; // 380.32 nm
	fPhotonEnergyLong[11] = 3.44 * eV; // 360.42 nm

	fAirRefractiveIndex[0] = 1.0;
	fAirRefractiveIndex[1] = 1.0;
	fAirAbsorpiton[0] = 10.0 * m;
	fAirAbsorpiton[1] = 10.0 * m;
	fPlexiglassRefractiveIndex[0] = fPlexiglassIndex;
	fPlexiglassRefractiveIndex[1] = fPlexiglassIndex;
	fPlexiglassAbsorpiton[0] = fPlexiglassAbsLength;
	fPlexiglassAbsorpiton[1] = fPlexiglassAbsLength;
	fGlassRefractiveIndex[0] = fGlassIndex;
	fGlassRefractiveIndex[1] = fGlassIndex;
	fBc408RefractiveIndex[0] = fBc408Index;
	fBc408RefractiveIndex[1] = fBc408Index;
}

void TRexMaterials::BuildAir() {
	G4Material* air = fManager->FindOrBuildMaterial("G4_AIR");
	air->SetName("air");
	// G4Material(name, density, nComponents or nAtoms)
	G4Material* vacuum = new G4Material("Vacuum", 1.0e-5 * 1.290 * mg/cm3, 2);
	vacuum->AddElement(fElN, 0.7);
	vacuum->AddElement(fElO, 0.3);

	G4Material* air_noOptical = new G4Material("Air_noOptical",
			1.290 * mg/cm3, 2);
	air_noOptical->AddElement(fElN, 0.7);
	air_noOptical->AddElement(fElO, 0.3);

	G4MaterialPropertiesTable* airMaterialProperties =	new G4MaterialPropertiesTable();
	airMaterialProperties->AddProperty("RINDEX", fPhotonEnergyShort, fAirRefractiveIndex, nEntryShort);
	airMaterialProperties->AddProperty("ABSLENGTH", fPhotonEnergyShort, fAirAbsorpiton, nEntryShort);
	air->SetMaterialPropertiesTable(airMaterialProperties);
	vacuum->SetMaterialPropertiesTable(airMaterialProperties);
}

G4Material* TRexMaterials::BuildBc408() {
	G4double lessOpticalFactor = 1;
	// todo implement this into interface and check for output.

	G4Material* bc408 = new G4Material("Scintillator", 1.032 * g/cm3, 2);
	bc408->AddElement(fElC, 9);
	bc408->AddElement(fElH, 10);

	G4double bc408RefractiveIndex[nEntryLong];
	G4double bc408Absorption[nEntryLong];
	for (G4int i = 0; i < nEntryLong; i++) {
		bc408RefractiveIndex[i] = fBc408Index;
		bc408Absorption[i] = fBc408AbsorptionLength;
	}
	G4double bc408Scintillation[nEntryLong] = { 0.01, 0.03, 0.17, 0.40, 0.55, 0.83, 1.00, 0.84, 0.49, 0.20, 0.07, 0.04 };

	G4MaterialPropertiesTable *bc408MaterialProperties = new G4MaterialPropertiesTable();
	bc408MaterialProperties->AddProperty("RINDEX", fPhotonEnergyLong, bc408RefractiveIndex, nEntryLong);
	bc408MaterialProperties->AddProperty("ABSLENGTH", fPhotonEnergyLong, bc408Absorption, nEntryLong);
	bc408MaterialProperties->AddProperty("FASTCOMPONENT", fPhotonEnergyLong, bc408Scintillation, nEntryLong);
	bc408MaterialProperties->AddConstProperty("SCINTILLATIONYIELD", fBc408Yield / lessOpticalFactor);
	bc408MaterialProperties->AddConstProperty("RESOLUTIONSCALE", 1.0);
	bc408MaterialProperties->AddConstProperty("FASTTIMECONSTANT", 0.9 * ns); // rise time
	bc408MaterialProperties->AddConstProperty("SLOWTIMECONSTANT", 2.1 * ns); // decay time
	bc408MaterialProperties->AddConstProperty("YIELDRATIO", 0.27);

	bc408->SetMaterialPropertiesTable(bc408MaterialProperties);
	bc408->GetIonisation()->SetBirksConstant(0.126 * mm/MeV);

	return bc408;
}

G4Material* TRexMaterials::BuildBc408_noOptical() {
	G4Material* bc408_noOptical = new G4Material("Scintillator_noOptical",
			1.032 * g/cm3, 2);
	bc408_noOptical->AddElement(fElC, 9);
	bc408_noOptical->AddElement(fElH, 10);

	return bc408_noOptical;
}

G4Material* TRexMaterials::BuildPlexiglass() {
	G4Material* plexiglass = fManager->FindOrBuildMaterial("G4_PLEXIGLASS");
	plexiglass->SetName("plexiglass");

	G4double plexiglassEnergy[nEntryShort] = { 7.14 * eV, 2.0 * eV };
	G4MaterialPropertiesTable* plexiglassMaterialProperties = new G4MaterialPropertiesTable();
	plexiglassMaterialProperties->AddProperty("RINDEX", plexiglassEnergy, fPlexiglassRefractiveIndex, nEntryShort);
	plexiglassMaterialProperties->AddProperty("ABSLENGTH", plexiglassEnergy, fPlexiglassAbsorpiton, nEntryShort);
	plexiglass->SetMaterialPropertiesTable(plexiglassMaterialProperties);

	return plexiglass;
}

G4Material* TRexMaterials::BuildGlass() {
	G4Material* glass = fManager->FindOrBuildMaterial("G4_GLASS_PLATE");
	glass->SetName("glass");

	G4MaterialPropertiesTable* glassMaterialProperties = new G4MaterialPropertiesTable();
	glassMaterialProperties->AddProperty("RINDEX", fPhotonEnergyShort, fGlassRefractiveIndex, nEntryShort);
	glass->SetMaterialPropertiesTable(glassMaterialProperties);

	return glass;
}

G4Material* TRexMaterials::BuildAluminium() {
	G4Material* aluminium = fManager->FindOrBuildMaterial("G4_Al");
	aluminium->SetName("aluminium");

	G4double aluminiumEnergy[nEntryShort] = { 2.0 * eV, 3.5 * eV };
	G4double aluminiumRefractiveIndex[nEntryShort] = { 1.51, 1.61 };
	G4double aluminiumAbsorpiton[nEntryShort] = { 1.0e-20 * m, 1.0e-20 * m };
	G4MaterialPropertiesTable* aluminiumMaterialProperties = new G4MaterialPropertiesTable();
	aluminiumMaterialProperties->AddProperty("RINDEX", aluminiumEnergy, aluminiumRefractiveIndex, nEntryShort);
	aluminiumMaterialProperties->AddProperty("ABSLENGTH", aluminiumEnergy, aluminiumAbsorpiton, nEntryShort);
	aluminium->SetMaterialPropertiesTable(aluminiumMaterialProperties);

	return aluminium;
}

G4Material* TRexMaterials::BuildBialkali() {
	G4Material* bialkali = new G4Material("bialkali", 3 * g/cm3, 3, kStateSolid);
	bialkali->AddElement(fElSb, 1);
	bialkali->AddElement(fElRb, 1);
	bialkali->AddElement(fElCs, 1);
	G4MaterialPropertiesTable* bialkaliProperties = new G4MaterialPropertiesTable();
	G4double bialkaliAbsorption[nEntryShort] = { 1.0e-6 * mm, 1.0e-6 * mm };
	bialkaliProperties->AddProperty("ABSLENGTH", fPhotonEnergyShort, bialkaliAbsorption, nEntryShort);
	bialkaliProperties->AddProperty("RINDEX", fPhotonEnergyShort, fGlassRefractiveIndex, nEntryShort);
	bialkali->SetMaterialPropertiesTable(bialkaliProperties);

	return bialkali;
}

G4Material* TRexMaterials::BuildC4F10() {
	G4Material* c4f10 = new G4Material("C4F10", 11.21 * kg/m3, 2, kStateGas, 298 * kelvin, 1.0 * atmosphere);
	c4f10->AddElement(fElC, 4);
	c4f10->AddElement(fElF, 10);

	G4double photonEnergy[11];
	G4double c4f10RefractiveIndex[11];

	photonEnergy[0] = 1.77 * eV; // 700 nm
	photonEnergy[1] = 2.07 * eV; // 600 nm
	photonEnergy[2] = 2.25 * eV; // 550 nm
	photonEnergy[3] = 2.48 * eV; // 500 nm
	photonEnergy[4] = 2.76 * eV; // 450 nm
	photonEnergy[5] = 3.10 * eV; // 400 nm
	photonEnergy[6] = 3.54 * eV; // 350 nm
	photonEnergy[7] = 4.13 * eV; // 300 nm
	photonEnergy[8] = 4.96 * eV; // 250 nm
	photonEnergy[9] = 6.20 * eV; // 200 nm
	photonEnergy[10] = 10.0 * eV; // 123.98 nm

	c4f10RefractiveIndex[0] = 1.00147;
	c4f10RefractiveIndex[1] = 1.001475;
	c4f10RefractiveIndex[2] = 1.00148;
	c4f10RefractiveIndex[3] = 1.00149;
	c4f10RefractiveIndex[4] = 1.0015;
	c4f10RefractiveIndex[5] = 1.00152;
	c4f10RefractiveIndex[6] = 1.00153;
	c4f10RefractiveIndex[7] = 1.00156;
	c4f10RefractiveIndex[8] = 1.0016;
	c4f10RefractiveIndex[9] = 1.0017;
	c4f10RefractiveIndex[10] = 1.0017;

	G4double c4f10Absorpiton[nEntryLong];
	for (G4int i = 0; i < nEntryLong; i++) {
		c4f10Absorpiton[i] = 10.00 * m; //TODO
	}

	G4MaterialPropertiesTable *c4f10MaterialProperties = new G4MaterialPropertiesTable();
	c4f10MaterialProperties->AddProperty("RINDEX", photonEnergy, c4f10RefractiveIndex, 11);
	c4f10MaterialProperties->AddProperty("ABSLENGTH", fPhotonEnergyLong, c4f10Absorpiton, nEntryLong);
	c4f10MaterialProperties->AddConstProperty("SCINTILLATIONYIELD", 100.0/MeV);

	c4f10->SetMaterialPropertiesTable(c4f10MaterialProperties);

	return c4f10;
}

G4Material* TRexMaterials::BuildC4F10_noOptical() {
	G4Material* c4f10_noOptical = new G4Material("C4F10_noOptical", 11.21 * kg/m3, 2, kStateGas, 298 * kelvin, 1.0 * atmosphere);
	c4f10_noOptical->AddElement(fElC, 4);
	c4f10_noOptical->AddElement(fElF, 10);

	return c4f10_noOptical;
}

void TRexMaterials::BuildSurfaceBc408Air() {
	fSurfaceBc408Air = new G4OpticalSurface("bc408AirSurface");
	fSurfaceBc408Air->SetType(dielectric_dielectric);
	fSurfaceBc408Air->SetModel(unified);
	fSurfaceBc408Air->SetFinish(ground);
	fSurfaceBc408Air->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fAirRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceBc408Air->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAirBc408() {
	fSurfaceAirBc408 = new G4OpticalSurface("airBc408Surface");
	fSurfaceAirBc408->SetType(dielectric_dielectric);
	fSurfaceAirBc408->SetModel(unified);
	fSurfaceAirBc408->SetFinish(ground);
	fSurfaceAirBc408->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fBc408RefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceAirBc408->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceBc408Plexiglass() {
	fSurfaceBc408Plexiglass = new G4OpticalSurface("bc408PlexiglassSurface");
	fSurfaceBc408Plexiglass->SetType(dielectric_dielectric);
	fSurfaceBc408Plexiglass->SetModel(unified);
	fSurfaceBc408Plexiglass->SetFinish(ground);
	fSurfaceBc408Plexiglass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fPlexiglassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceBc408Plexiglass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfacePlexiglassGlass() {
	fSurfacePlexiglassGlass = new G4OpticalSurface("plexiglassGlassSurface");
	fSurfacePlexiglassGlass->SetType(dielectric_dielectric);
	fSurfacePlexiglassGlass->SetModel(unified);
	fSurfacePlexiglassGlass->SetFinish(ground);
	fSurfacePlexiglassGlass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fGlassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfacePlexiglassGlass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfacePlexiglassAir() {
	fSurfacePlexiglassAir = new G4OpticalSurface("plexiglassAirSurface");
	fSurfacePlexiglassAir->SetType(dielectric_dielectric);
	fSurfacePlexiglassAir->SetModel(unified);
	fSurfacePlexiglassAir->SetFinish(ground);
	fSurfacePlexiglassAir->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fAirRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfacePlexiglassAir->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAirPlexiglass() {
	fSurfaceAirPlexiglass = new G4OpticalSurface("airPlexiglassSurface");
	fSurfaceAirPlexiglass->SetType(dielectric_dielectric);
	fSurfaceAirPlexiglass->SetModel(unified);
	fSurfaceAirPlexiglass->SetFinish(ground);
	fSurfaceAirPlexiglass->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fPlexiglassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceAirPlexiglass->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceGlassVacuum() {
	fSurfaceGlassVacuum = new G4OpticalSurface("glassVacuumSurface");
	fSurfaceGlassVacuum->SetType(dielectric_dielectric);
	fSurfaceGlassVacuum->SetModel(unified);
	fSurfaceGlassVacuum->SetFinish(ground); //groundair
	fSurfaceGlassVacuum->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fAirRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceGlassVacuum->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceVacuumBialkali() {
	fSurfaceVacuumBialkali = new G4OpticalSurface("vacuumBialkaliSurface");
	fSurfaceVacuumBialkali->SetType(dielectric_dielectric);
	fSurfaceVacuumBialkali->SetModel(unified);
	fSurfaceVacuumBialkali->SetFinish(ground);
	fSurfaceVacuumBialkali->SetSigmaAlpha(0.035);

	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("RINDEX", fPhotonEnergyShort,
			fGlassRefractiveIndex, nEntryShort);
	surfaceProperties->AddProperty("SPECULARLOBECONSTANT", fPhotonEnergyShort,
			fSpecularLobe, nEntryShort);
	surfaceProperties->AddProperty("SPECULARSPIKECONSTANT", fPhotonEnergyShort,
			fSpecularSpike, nEntryShort);
	surfaceProperties->AddProperty("BACKSCATTERCONSTANT", fPhotonEnergyShort,
			fBackScatter, nEntryShort);
	fSurfaceVacuumBialkali->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceAluminium() {
	fSurfaceAluminium = new G4OpticalSurface("aluminiumSurface");
	fSurfaceAluminium->SetType(dielectric_metal);
	fSurfaceAluminium->SetModel(unified);
	fSurfaceAluminium->SetFinish(ground);
	fSurfaceAluminium->SetPolish(0.0);

	G4double aluminiumReflectivityShort[nEntryShort] = { fAluminiumReflectivity, fAluminiumReflectivity };
	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("REFLECTIVITY", fPhotonEnergyShort, aluminiumReflectivityShort, nEntryShort);
	fSurfaceAluminium->SetMaterialPropertiesTable(surfaceProperties);
}

void TRexMaterials::BuildSurfaceMirror() {
	fSurfaceMirror = new G4OpticalSurface("mirrorSurface");
	fSurfaceMirror->SetModel(unified);
	fSurfaceMirror->SetType(dielectric_dielectric);
	fSurfaceMirror->SetFinish(polishedfrontpainted);

	G4double aluminiumReflectivityShort[nEntryShort] = { 1.0, 1.0 };
	G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
	surfaceProperties->AddProperty("REFLECTIVITY", fPhotonEnergyShort, aluminiumReflectivityShort, nEntryShort);
	fSurfaceAluminium->SetMaterialPropertiesTable(surfaceProperties);
}

G4Material* TRexMaterials::BuildDeuterium() {
	//G4Material* Deuterium = new G4Material("DeuteriumGas", density=0.08*g/m3, ncomponents=2, kStateGas, 
	//                                       temperature=293.15*kelvin, chamberPressure=0.005*bar);
	G4Material* deuteriumGas = new G4Material("2H", 0.180 * kg/m3, 1,
			kStateGas, 298 * kelvin, 10.0e-3 * atmosphere);

	deuteriumGas->AddElement(fElD,2);

	return deuteriumGas;
}

G4Material* TRexMaterials::BuildDeuteratedPE() {
	G4Material* deuteratedPE = new G4Material("DeuteratedPE", 0.92 * g/cm3, 2);
	deuteratedPE->AddElement(fElC, 2);
	deuteratedPE->AddElement(fElD, 4);

	return deuteratedPE;
}

G4Material* TRexMaterials::BuildSolidDeuterium() {
	//G4Material* Deuterium = new G4Material("DeuteriumGas", density=0.08*g/m3, ncomponents=2, kStateGas, 
	//                                       temperature=293.15*kelvin, chamberPressure=0.005*bar);
	G4Material* solidDeuterium = new G4Material("SolidDeuterium", 196.7 * kg/m3, 1, kStateSolid);

	solidDeuterium->AddElement(fElD,2);

	return solidDeuterium;
}


G4Material* TRexMaterials::GetMaterial(std::string name) {//, double pressure) {
	//// if the pressure is non-zero, we add it (in mbar) to the name (with two digits precision)
	//if(pressure != 0.) {
	//	std::ostringstream str;
	//	str<<name<<"_"<<std::fixed<<std::setprecision(2)<<1000.*pressure/bar<<std::defaultfloat<<"mbar";
	//	name = str.str();
	//}
	G4Material* material = G4Material::GetMaterial(name);
	if(material != NULL) { 
		return material; 
	}

	if(name == "vacuum" || name == "dummy") {
		material = MiniBallMaterial::Get()->GetMaterialVacuum();
	} else if(((G4String)name).contains("G4_")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial(name);
	} else if(((G4String)name).contains("48Ti")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial("G4_Ti");
	} else if(((G4String)name).contains("109Ag")) {
		material = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial("G4_Ag");
	} else {
		G4String matName = name;
		G4int splitIndex = matName.find_first_not_of("0123456789");
		G4String massNumberString = matName.substr(0,splitIndex);
		G4String elementName = matName.substr(splitIndex,  std::string::npos);
		G4int massNumber = atoi(massNumberString);
		G4String elname = "G4_" + elementName;

		G4Material* bufferMaterial = TRexMaterials::Get()->GetNistManager()->FindOrBuildMaterial(elname);
		G4double density = bufferMaterial->GetDensity();
		G4double molarMass = TRexMaterials::Get()->GetNistManager()->GetAtomicMass(bufferMaterial->GetZ(),massNumber)*(g/mole)/amu_c2;
		std::cout << "matName " << matName << " massNrString " << massNumber << " elementName " << elementName << " Z " << bufferMaterial->GetZ() <<" molar mass " << std::setprecision(5)<<
			molarMass/(g/mole) << " density " << density/(g/cm3)<< std::endl;
		material = new G4Material(matName,bufferMaterial->GetZ(), molarMass, density );
	}

	std::cout<<"got material "<<material->GetName()<<" from "<<name<<std::endl;

	return material;
}
