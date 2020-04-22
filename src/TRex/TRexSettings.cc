/*
 * TRexSettings.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>
#include <G4UnitsTable.hh>
#include <globals.hh>

#include <algorithm>

ClassImp(TRexSettings)

TRexSettings* TRexSettings::fSettings = NULL;

TRexSettings* TRexSettings::Get() {
	if(fSettings == NULL) {
		fSettings = new TRexSettings;
	}

	return fSettings;
}

TRexSettings::TRexSettings() : 
	fMiniballClusterNames(0) {
}

TRexSettings::~TRexSettings() {
	// TODO Auto-generated destructor stub
}

void TRexSettings::ReadSettingsFile(std::string settingsFile) {
	fSettingsFile = settingsFile; 
	TEnv sett(fSettingsFile.c_str());

	fPrimaryGenerator = sett.GetValue("PrimaryGenerator", "beam");

	fSimulateEjectiles = sett.GetValue("SimulateEjectiles", false);
	fSimulateGammas = sett.GetValue("SimulateGammas", false);
	fIncludeEnergyResolution = sett.GetValue("IncludeEnergyResolution", 0);

    fGammaEnergy = sett.GetValue("gammaEnergy", 1332.) * keV;

	//vacuum chamber
	fIncludeVacuumChamber = sett.GetValue("IncludeVacuumChamber", 1);
	fVacuumChamberType = sett.GetValue("VacuumChamberType", "sphere");
	fVacuumChamberGas = sett.GetValue("VacuumChamberGas", "helium");
	fVacuumChamberGasPressure = sett.GetValue("VacuumChamberGasPressure", 1e-6) /1000. * bar;

	fTestSourceEnergy = sett.GetValue("TestSourceEnergy", 5000.0) * keV;

	//beam properties
	fBeamEnergy = sett.GetValue("BeamEnergy", 100.0) * MeV;
	fBeamWidth = sett.GetValue("BeamWidth", 3.0) * mm;
	fThetaCmMin = sett.GetValue("ThetaCmMin", 2.0) * degree;

	//reaction
	fProjectileZ = sett.GetValue("ProjectileZ", 30);
	fProjectileA = sett.GetValue("ProjectileA", 72);
	fTargetZ = sett.GetValue("TargetZ", 1);
	fTargetA = sett.GetValue("TargetA", 3);
	fEjectileZ = sett.GetValue("EjectileZ", 30);
	fEjectileA = sett.GetValue("EjectileA", 74);
	fRecoilZ = sett.GetValue("RecoilZ", 1);
	fRecoilA = sett.GetValue("RecoilA", 1);
	fProjectileName = sett.GetValue("ProjectileName", "72Zn");
	fTargetName = sett.GetValue("TargetName", "3H");
	fEjectileName = sett.GetValue("EjectileName", "74Zn");
	fRecoilName = sett.GetValue("RecoilName", "1H");

	std::string simDir = "";
	fLevelFile = sett.GetValue("LevelFile", "dummy.dat");
	if(fLevelFile.find("LevelFiles/") == 0) {
		fLevelFile.insert(0, "/");
		fLevelFile.insert(0, simDir);
	}
	fAngularDistributionFile = sett.GetValue("AngularDistributionFile", "dummy.dat");
	if(fAngularDistributionFile.find("AngularDistributionFiles/") == 0) {
		fAngularDistributionFile.insert(0, "/");
		fAngularDistributionFile.insert(0, simDir);
	}
	fMassFile = sett.GetValue("MassFile", "MassFile.dat");
	if(fMassFile.find("MassFile.dat") == 0) {
		//fMassFile.insert(0, "/");
		//fMassFile.insert(0, simDir);
	}

	fAlphaSourceDiameter = sett.GetValue("AlphaSourceDiameter", 3) * mm;
	fAlphaSourceThickness = sett.GetValue("AlphaSourceThickness", 3) * mm;

	fTargetDiameter = sett.GetValue("TargetDiameter", 3) * mm;
	fTargetThickness = sett.GetValue("TargetThickness", 0.5) * mg/cm2;
	fGasTargetLength = sett.GetValue("GasTargetLength", 0.0) * cm;
	fTargetPressure = sett.GetValue("TargetPressure", 0.0) /1000. * bar;
	//fTargetMaterial = sett.GetValue("TargetMaterial", "vacuum");
	fTargetMaterialDensity = sett.GetValue("TargetMaterialDensity", 4.507) * g/cm3;

	fTargetMaterialName = sett.GetValue("TargetMaterialName", "dummy");
	//std::cout<<"from '"<<fTargetMaterialName<<"' to ";
	//std::transform(fTargetMaterialName.begin(), fTargetMaterialName.end(), fTargetMaterialName.begin(), ::tolower);
	//std::cout<<"'"<<fTargetMaterialName<<"'"<<std::endl;
	fTargetAtomicRatio = sett.GetValue("TargetAtomicRatio", 1.5);
	fTransferOrCoulexProbability = sett.GetValue("TransferOrCoulexProbability", 1.0);

	fColours = sett.GetValue("SetColours", 0);
	//fVisualizationCut = sett.GetValue("VisualizationCut", false); // this is actually set by TRexData!
	// fill always the detector tree regardless if a detector was hit or not ?
	fWriteAllEvents = sett.GetValue("WriteAllEvents", 0);
	fConstructPCB =  sett.GetValue("ConstructPCB", true);
	fResistiveStrips =  sett.GetValue("ResistiveStrips", true);

	// FCD deltaE
	fUseFCDdeltaE = sett.GetValue("UseFCDdeltaE", 0);
	fNbOfFCDdeltaESingles = sett.GetValue("NbOfFCDdeltaESingles", 4);
	for(int i = 0; i < fNbOfFCDdeltaESingles; i++){
		fFCDdeltaESinglePosX.push_back(sett.GetValue(Form("FCDdeltaESingles.%d.X", i), 0) * mm);
		fFCDdeltaESinglePosY.push_back(sett.GetValue(Form("FCDdeltaESingles.%d.Y", i), 0) * mm);
		fFCDdeltaESinglePosZ.push_back(sett.GetValue(Form("FCDdeltaESingles.%d.Z", i), 64.0) * mm);
		fFCDdeltaESingleStartAngle.push_back(sett.GetValue(Form("FCDdeltaESingles.%d.StartAngle", i), 49.2 - i*90) * deg);
		fFCDdeltaESingleThickness.push_back(sett.GetValue(Form("FCDdeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fFCDdeltaESingleDeadLayer = sett.GetValue("FCDdeltaESinglesDeadLayer", 0.0) * um;
	fFCDdeltaESingleInnerRadius = sett.GetValue("FCDdeltaESinglesInnerRadius", 9.0) * mm;
	fFCDdeltaESingleOuterRadius = sett.GetValue("FCDdeltaESinglesOuterRadius", 41.0) * mm;
	fFCDdeltaESingleRingWidth = sett.GetValue("FCDdeltaESinglesRingWidth", 2.0) * mm;
	fFCDdeltaESingleSpanningAngle = sett.GetValue("FCDdeltaESinglesSpanningAngle", 81.6) * deg;
	fFCDdeltaESingleStripWidth = sett.GetValue("FCDdeltaESinglesStripWidth", 3.4) * deg;
	fFCDTransferTo16Strips = sett.GetValue("FCDTransferTo16Strips", 1);
	fFCDdeltaESingleEnergyResolution = sett.GetValue("FCDdeltaESinglesEnergyResolution", 50) * keV;
	fFCDdeltaESingleFoilThickness = sett.GetValue("FCDdeltaESinglesFoilThickness", -1.) * um;

	// FCD Erest
	fUseFCDErest = sett.GetValue("UseFCDErest", 0);
	fNbOfFCDErestSingles = sett.GetValue("NbOfFCDErestSingles", 4);
	for(int i = 0; i < fNbOfFCDErestSingles; i++){
		fFCDErestSinglePosX.push_back(sett.GetValue(Form("FCDErestSingles.%d.X", i), 0) * mm);
		fFCDErestSinglePosY.push_back(sett.GetValue(Form("FCDErestSingles.%d.Y", i), 0) * mm);
		fFCDErestSinglePosZ.push_back(sett.GetValue(Form("FCDErestSingles.%d.Z", i), 72.5) * mm);
		fFCDErestSingleStartAngle.push_back(sett.GetValue(Form("FCDErestSingles.%d.StartAngle", i), 49.2 - i*90) * deg);
		fFCDErestSingleThickness.push_back(sett.GetValue(Form("FCDErestSingles.%d.Thickness", i), 1000.0) * um);
	}
	fFCDErestSingleDeadLayer = sett.GetValue("FCDErestSingles.DeadLayer", 0.0) * um;
	fFCDErestSingleInnerRadius = sett.GetValue("FCDErestSinglesInnerRadius", 9.0) * mm;
	fFCDErestSingleOuterRadius = sett.GetValue("FCDErestSinglesOuterRadius", 50.0) * mm;
	fFCDErestSingleSpanningAngle = sett.GetValue("FCDErestSinglesSpanningAngle", 81.6) * deg;
	fFCDErestSingleEnergyResolution = sett.GetValue("FCDErestSinglesEnergyResolution", 50) * keV;

	// BCD deltaE
	fUseBCDdeltaE = sett.GetValue("UseBCDdeltaE", 0);
	fNbOfBCDdeltaESingles = sett.GetValue("NbOfBCDdeltaESingles", 4);
	for(int i = 0; i < fNbOfBCDdeltaESingles; i++){
		fBCDdeltaESinglePosX.push_back(sett.GetValue(Form("BCDdeltaESingles.%d.X", i), 0) * mm);
		fBCDdeltaESinglePosY.push_back(sett.GetValue(Form("BCDdeltaESingles.%d.Y", i), 0) * mm);
		fBCDdeltaESinglePosZ.push_back(sett.GetValue(Form("BCDdeltaESingles.%d.Z", i), -64.0) * mm);
		fBCDdeltaESingleStartAngle.push_back(sett.GetValue(Form("BCDdeltaESingles.%d.StartAngle", i), 49.2 - i*90) * deg);
		fBCDdeltaESingleThickness.push_back(sett.GetValue(Form("BCDdeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fBCDdeltaESingleDeadLayer = sett.GetValue("BCDdeltaESinglesDeadLayer", 0.0) * um;
	fBCDdeltaESingleInnerRadius = sett.GetValue("BCDdeltaESinglesInnerRadius", 9.0) * mm;
	fBCDdeltaESingleOuterRadius = sett.GetValue("BCDdeltaESinglesOuterRadius", 41.0) * mm;
	fBCDdeltaESingleRingWidth = sett.GetValue("BCDdeltaESinglesRingWidth", 2.0) * mm;
	fBCDdeltaESingleSpanningAngle = sett.GetValue("BCDdeltaESinglesSpanningAngle", 81.6) * deg;
	fBCDdeltaESingleStripWidth = sett.GetValue("BCDdeltaESinglesStripWidth", 3.4) * deg;
	fBCDTransferTo16Strips = sett.GetValue("BCDTransferTo16Strips", 1);
	fBCDdeltaESingleEnergyResolution = sett.GetValue("BCDdeltaESinglesEnergyResolution", 20) * keV;
	fBCDdeltaESingleFoilThickness = sett.GetValue("BCDdeltaESinglesFoilThickness", -1.) * um;

	// BCD Erest
	fUseBCDErest = sett.GetValue("UseBCDErest", 0);
	fNbOfBCDErestSingles = sett.GetValue("NbOfBCDErestSingles", 4);
	for(int i = 0; i < fNbOfBCDErestSingles; i++){
		fBCDErestSinglePosX.push_back(sett.GetValue(Form("BCDErestSingles.%d.X", i), 0) * mm);
		fBCDErestSinglePosY.push_back(sett.GetValue(Form("BCDErestSingles.%d.Y", i), 0) * mm);
		fBCDErestSinglePosZ.push_back(sett.GetValue(Form("BCDErestSingles.%d.Z", i), -72.5) * mm);
		fBCDErestSingleStartAngle.push_back(sett.GetValue(Form("BCDErestSingles.%d.StartAngle", i), 49.2 - i*90) * deg);
		fBCDErestSingleThickness.push_back(sett.GetValue(Form("BCDErestSingles.%d.Thickness", i), 1000.0) * um);
	}
	fBCDErestSingleDeadLayer = sett.GetValue("BCDErestSingles.DeadLayer", 0.0) * um;
	fBCDErestSingleInnerRadius = sett.GetValue("BCDErestSinglesInnerRadius", 9.0) * mm;
	fBCDErestSingleOuterRadius = sett.GetValue("BCDErestSinglesOuterRadius", 50.0) * mm;
	fBCDErestSingleSpanningAngle = sett.GetValue("BCDErestSinglesSpanningAngle", 81.6) * deg;
	fBCDErestSingleEnergyResolution = sett.GetValue("BCDErestSinglesEnergyResolution", 20) * keV;


	// FBarrel deltaE
	fUseFBarrelDeltaE = sett.GetValue("UseFBarrelDeltaE", 0);
	fNbOfFBarrelDeltaESingles = sett.GetValue("NbOfFBarrelDeltaESingles", 4);
	for(int i = 0; i < fNbOfFBarrelDeltaESingles; i++){
		//fFBarrelDeltaESinglePosX.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.X", i), 0) * mm);
		//fFBarrelDeltaESinglePosY.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.Y", i), 0) * mm);
		fFBarrelDeltaESinglePosZ.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.Z", i), 33.0) * mm);
		fFBarrelDeltaESingleDistanceToBeam.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.DistanceToBeam", i), 29.0) * mm);
		fFBarrelDeltaESingleStartAngle.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fFBarrelDeltaESingleThickness.push_back(sett.GetValue(Form("FBarrelDeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fFBarrelDeltaESingleDeadLayer = sett.GetValue("FBarrelDeltaESinglesDeadLayer", 0.0) * um;
	fFBarrelDeltaESingleLengthX = sett.GetValue("FBarrelDeltaESinglesLength.X", 50.0) * mm;
	fFBarrelDeltaESingleLengthY = sett.GetValue("FBarrelDeltaESinglesLength.Y", 50.0) * mm;
	fFBarrelDeltaESingleStripWidth = sett.GetValue("FBarrelDeltaESinglesStripWidth", 3.125) * mm;
	fFBarrelDeltaESingleEnergyResolution = sett.GetValue("FBarrelDeltaESinglesEnergyResolution", 50) * keV;
	fFBarrelDeltaESingleFoilThickness = sett.GetValue("FBarrelDeltaESinglesFoilThickness", -1.) * um;

	// FBarrel Erest
	fUseFBarrelErest = sett.GetValue("UseFBarrelErest", 0);
	fNbOfFBarrelErestSingles = sett.GetValue("NbOfFBarrelErestSingles", 4);
	for(int i = 0; i < fNbOfFBarrelErestSingles; i++){
		//fFBarrelErestSinglePosX.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.X", i), 0) * mm);
		//fFBarrelErestSinglePosY.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.Y", i), 0) * mm);
		fFBarrelErestSinglePosZ.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.Z", i), 33.0) * mm);
		fFBarrelErestSingleDistanceToBeam.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.DistanceToBeam", i), 31.7) * mm);
		fFBarrelErestSingleStartAngle.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fFBarrelErestSingleThickness.push_back(sett.GetValue(Form("FBarrelErestSingles.%d.Thickness", i), 1000.0) * um);
	}
	fFBarrelErestSingleDeadLayer = sett.GetValue("FBarrelErestSingles.DeadLayer", 0.0) * um;
	fFBarrelErestSingleLengthX = sett.GetValue("FBarrelErestSinglesLength.X", 50.0) * mm;
	fFBarrelErestSingleLengthY = sett.GetValue("FBarrelErestSinglesLength.Y", 50.0) * mm;
	fFBarrelErestSingleEnergyResolution = sett.GetValue("FBarrelErestSinglesEnergyResolution", 50) * keV;

	// Second FBarrel deltaE
	fUseSecondFBarrelDeltaE = sett.GetValue("UseSecondFBarrelDeltaE", 0);
	fNbOfSecondFBarrelDeltaESingles = sett.GetValue("NbOfSecondFBarrelDeltaESingles", 4);
	for(int i = 0; i < fNbOfSecondFBarrelDeltaESingles; i++){
		fSecondFBarrelDeltaESinglePosZ.push_back(sett.GetValue(Form("SecondFBarrelDeltaESingles.%d.Z", i), 33.0) * mm);
		fSecondFBarrelDeltaESingleDistanceToBeam.push_back(sett.GetValue(Form("SecondFBarrelDeltaESingles.%d.DistanceToBeam", i), 29.0) * mm);
		fSecondFBarrelDeltaESingleStartAngle.push_back(sett.GetValue(Form("SecondFBarrelDeltaESingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fSecondFBarrelDeltaESingleThickness.push_back(sett.GetValue(Form("SecondFBarrelDeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fSecondFBarrelDeltaESingleDeadLayer = sett.GetValue("SecondFBarrelDeltaESinglesDeadLayer", 0.0) * um;
	fSecondFBarrelDeltaESingleLengthX = sett.GetValue("SecondFBarrelDeltaESinglesLength.X", 50.0) * mm;
	fSecondFBarrelDeltaESingleLengthY = sett.GetValue("SecondFBarrelDeltaESinglesLength.Y", 50.0) * mm;
	fSecondFBarrelDeltaESingleStripWidth = sett.GetValue("SecondFBarrelDeltaESinglesStripWidth", 3.125) * mm;
	fSecondFBarrelDeltaESingleEnergyResolution = sett.GetValue("SecondFBarrelDeltaESinglesEnergyResolution", 50) * keV;
	fSecondFBarrelDeltaESingleFoilThickness = sett.GetValue("SecondFBarrelDeltaESinglesFoilThickness", -1.) * um;

	// MBarrel deltaE
	fUseMBarrelDeltaE = sett.GetValue("UseMBarrelDeltaE", 0);
	fNbOfMBarrelDeltaESingles = sett.GetValue("NbOfMBarrelDeltaESingles", 4);
	for(int i = 0; i < fNbOfMBarrelDeltaESingles; i++){
		//fMBarrelDeltaESinglePosX.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.X", i), 0) * mm);
		//fMBarrelDeltaESinglePosY.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.Y", i), 0) * mm);
		fMBarrelDeltaESinglePosZ.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.Z", i), 33.0) * mm);
		fMBarrelDeltaESingleDistanceToBeam.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.DistanceToBeam", i), 29.0) * mm);
		fMBarrelDeltaESingleStartAngle.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fMBarrelDeltaESingleThickness.push_back(sett.GetValue(Form("MBarrelDeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fMBarrelDeltaESingleDeadLayer = sett.GetValue("MBarrelDeltaESinglesDeadLayer", 0.0) * um;
	fMBarrelDeltaESingleLengthX = sett.GetValue("MBarrelDeltaESinglesLength.X", 50.0) * mm;
	fMBarrelDeltaESingleLengthY = sett.GetValue("MBarrelDeltaESinglesLength.Y", 50.0) * mm;
	fMBarrelDeltaESingleStripWidth = sett.GetValue("MBarrelDeltaESinglesStripWidth", 3.125) * mm;
	fMBarrelDeltaESingleEnergyResolution = sett.GetValue("MBarrelDeltaESinglesEnergyResolution", 50) * keV;
	fMBarrelDeltaESingleFoilThickness = sett.GetValue("MBarrelDeltaESinglesFoilThickness", -1.) * um;

	// MBarrel Erest
	fUseMBarrelErest = sett.GetValue("UseMBarrelErest", 0);
	fNbOfMBarrelErestSingles = sett.GetValue("NbOfMBarrelErestSingles", 4);
	for(int i = 0; i < fNbOfMBarrelErestSingles; i++){
		//fMBarrelErestSinglePosX.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.X", i), 0) * mm);
		//fMBarrelErestSinglePosY.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.Y", i), 0) * mm);
		fMBarrelErestSinglePosZ.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.Z", i), 33.0) * mm);
		fMBarrelErestSingleDistanceToBeam.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.DistanceToBeam", i), 31.7) * mm);
		fMBarrelErestSingleStartAngle.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fMBarrelErestSingleThickness.push_back(sett.GetValue(Form("MBarrelErestSingles.%d.Thickness", i), 1000.0) * um);
	}
	fMBarrelErestSingleDeadLayer = sett.GetValue("MBarrelErestSingles.DeadLayer", 0.0) * um;
	fMBarrelErestSingleLengthX = sett.GetValue("MBarrelErestSinglesLength.X", 50.0) * mm;
	fMBarrelErestSingleLengthY = sett.GetValue("MBarrelErestSinglesLength.Y", 50.0) * mm;
	fMBarrelErestSingleEnergyResolution = sett.GetValue("MBarrelErestSinglesEnergyResolution", 50) * keV;


	// BBarrel deltaE
	fUseBBarrelDeltaE = sett.GetValue("UseBBarrelDeltaE", 0);
	fNbOfBBarrelDeltaESingles = sett.GetValue("NbOfBBarrelDeltaESingles", 4);
	for(int i = 0; i < fNbOfBBarrelDeltaESingles; i++){
		//fBBarrelDeltaESinglePosX.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.X", i), 0) * mm);
		//fFBarrelDeltaESinglePosY.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.Y", i), 0) * mm);
		fBBarrelDeltaESinglePosZ.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.Z", i), -33.0) * mm);
		fBBarrelDeltaESingleDistanceToBeam.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.DistanceToBeam", i), 29.0) * mm);
		fBBarrelDeltaESingleStartAngle.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fBBarrelDeltaESingleThickness.push_back(sett.GetValue(Form("BBarrelDeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fBBarrelDeltaESingleDeadLayer = sett.GetValue("BBarrelDeltaESinglesDeadLayer", 0.0) * um;
	fBBarrelDeltaESingleLengthX = sett.GetValue("BBarrelDeltaESinglesLength.X", 50.0) * mm;
	fBBarrelDeltaESingleLengthY = sett.GetValue("BBarrelDeltaESinglesLength.Y", 50.0) * mm;
	fBBarrelDeltaESingleStripWidth = sett.GetValue("BBarrelDeltaESinglesStripWidth", 3.125) * mm;
	fBBarrelDeltaESingleEnergyResolution = sett.GetValue("BBarrelDeltaESinglesEnergyResolution", 50) * keV;
	fBBarrelDeltaESingleFoilThickness = sett.GetValue("BBarrelDeltaESinglesFoilThickness", -1.) * um;

	// BBarrel Erest
	fUseBBarrelErest = sett.GetValue("UseBBarrelErest", 0);
	fNbOfBBarrelErestSingles = sett.GetValue("NbOfBBarrelErestSingles", 4);
	for(int i = 0; i < fNbOfBBarrelErestSingles; i++){
		//fBBarrelErestSinglePosX.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.X", i), 0) * mm);
		//fBBarrelErestSinglePosY.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.Y", i), 0) * mm);
		fBBarrelErestSinglePosZ.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.Z", i), -33.0) * mm);
		fBBarrelErestSingleDistanceToBeam.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.DistanceToBeam", i), 31.7) * mm);
		fBBarrelErestSingleStartAngle.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fBBarrelErestSingleThickness.push_back(sett.GetValue(Form("BBarrelErestSingles.%d.Thickness", i), 1000.0) * um);
	}
	fBBarrelErestSingleDeadLayer = sett.GetValue("BBarrelErestSingles.DeadLayer", 0.0) * um;
	fBBarrelErestSingleLengthX = sett.GetValue("BBarrelErestSinglesLength.X", 50.0) * mm;
	fBBarrelErestSingleLengthY = sett.GetValue("BBarrelErestSinglesLength.Y", 50.0) * mm;
	fBBarrelErestSingleEnergyResolution = sett.GetValue("BBarrelErestSinglesEnergyResolution", 50) * keV;

	// Second BBarrel deltaE
	fUseSecondBBarrelDeltaE = sett.GetValue("UseSecondBBarrelDeltaE", 0);
	fNbOfSecondBBarrelDeltaESingles = sett.GetValue("NbOfSecondBBarrelDeltaESingles", 4);
	for(int i = 0; i < fNbOfSecondBBarrelDeltaESingles; i++){
		fSecondBBarrelDeltaESinglePosZ.push_back(sett.GetValue(Form("SecondBBarrelDeltaESingles.%d.Z", i), 33.0) * mm);
		fSecondBBarrelDeltaESingleDistanceToBeam.push_back(sett.GetValue(Form("SecondBBarrelDeltaESingles.%d.DistanceToBeam", i), 29.0) * mm);
		fSecondBBarrelDeltaESingleStartAngle.push_back(sett.GetValue(Form("SecondBBarrelDeltaESingles.%d.StartAngle", i), 90.0 - i*90) * deg);
		fSecondBBarrelDeltaESingleThickness.push_back(sett.GetValue(Form("SecondBBarrelDeltaESingles.%d.Thickness", i), 140.0) * um);
	}
	fSecondBBarrelDeltaESingleDeadLayer = sett.GetValue("SecondBBarrelDeltaESinglesDeadLayer", 0.0) * um;
	fSecondBBarrelDeltaESingleLengthX = sett.GetValue("SecondBBarrelDeltaESinglesLength.X", 50.0) * mm;
	fSecondBBarrelDeltaESingleLengthY = sett.GetValue("SecondBBarrelDeltaESinglesLength.Y", 50.0) * mm;
	fSecondBBarrelDeltaESingleStripWidth = sett.GetValue("SecondBBarrelDeltaESinglesStripWidth", 3.125) * mm;
	fSecondBBarrelDeltaESingleEnergyResolution = sett.GetValue("SecondBBarrelDeltaESinglesEnergyResolution", 50) * keV;
	fSecondBBarrelDeltaESingleFoilThickness = sett.GetValue("SecondBBarrelDeltaESinglesFoilThickness", -1.) * um;

	// Forward Trapezoid deltaE
	fUseFTrapezoidDeltaE = sett.GetValue("UseFTrapezoidDeltaE", 0);
	fNbOfFTrapezoidDeltaESingles = sett.GetValue("NbOfFTrapezoidDeltaESingles", 8);
	for(int i = 0; i < fNbOfFTrapezoidDeltaESingles; i++){
		fFTrapezoidDeltaESinglePosZ.push_back(sett.GetValue(Form("FTrapezoidDeltaESingles.%d.Z", i), 25.0) * mm);
		fFTrapezoidDeltaESingleThickness.push_back(sett.GetValue(Form("FTrapezoidDeltaESingles.%d.Thickness", i), 140.0) * um);
		fFTrapezoidDeltaESingleStartAngle.push_back(sett.GetValue(Form("FTrapezoidDeltaESingles.%d.StartAngle", i), -i*45) * deg);
	}
	fFTrapezoidDeltaESingleInnerRadius = sett.GetValue("FTrapezoidDeltaESingleInnerRadius", 15.) * mm;
	fFTrapezoidDeltaESingleOuterRadius = sett.GetValue("FTrapezoidDeltaESingleOuterRadius", 60.) * mm;
	fFTrapezoidDeltaESingleDeltaZ = sett.GetValue("FTrapezoidDeltaESingleDeltaZ", 30.) * mm;
	fFTrapezoidDeltaESingleNbOfRings = sett.GetValue("FTrapezoidDeltaESingleNbOfRings", 16);
	fFTrapezoidDeltaESingleNbOfStrips = sett.GetValue("FTrapezoidDeltaESingleNbOfStrips", 16);
	fFTrapezoidDeltaESingleEnergyResolution = sett.GetValue("FTrapezoidDeltaESingleEnergyResolution", 50) * keV;
	fFTrapezoidDeltaESingleFoilThickness = sett.GetValue("FTrapezoidDeltaESinglesFoilThickness", -1.) * um;

	// Forward Trapezoid Erest
	fUseFTrapezoidErest = sett.GetValue("UseFTrapezoidErest", 0);
	fNbOfFTrapezoidErestSingles = sett.GetValue("NbOfFTrapezoidErestSingles", 8);
	for(int i = 0; i < fNbOfFTrapezoidErestSingles; i++){
		fFTrapezoidErestSinglePosZ.push_back(sett.GetValue(Form("FTrapezoidErestSingles.%d.Z", i), 25.0) * mm);
		fFTrapezoidErestSingleThickness.push_back(sett.GetValue(Form("FTrapezoidErestSingles.%d.Thickness", i), 1000.0) * um);
		fFTrapezoidErestSingleStartAngle.push_back(sett.GetValue(Form("FTrapezoidErestSingles.%d.StartAngle", i), -i*45) * deg);
	}
	fFTrapezoidErestSingleInnerRadius = sett.GetValue("FTrapezoidErestSingleInnerRadius", 25.) * mm;
	fFTrapezoidErestSingleOuterRadius = sett.GetValue("FTrapezoidErestSingleOuterRadius", 80.) * mm;
	fFTrapezoidErestSingleDeltaZ = sett.GetValue("FTrapezoidErestSingleDeltaZ", 30.) * mm;
	fFTrapezoidErestSingleEnergyResolution = sett.GetValue("FTrapezoidErestSingleEnergyResolution", 50) * keV;

	// Backward Trapezoid deltaE
	fUseBTrapezoidDeltaE = sett.GetValue("UseBTrapezoidDeltaE", 0);
	fNbOfBTrapezoidDeltaESingles = sett.GetValue("NbOfBTrapezoidDeltaESingles", 8);
	for(int i = 0; i < fNbOfBTrapezoidDeltaESingles; i++){
		fBTrapezoidDeltaESinglePosZ.push_back(sett.GetValue(Form("BTrapezoidDeltaESingles.%d.Z", i), 20.0) * mm);
		fBTrapezoidDeltaESingleThickness.push_back(sett.GetValue(Form("BTrapezoidDeltaESingles.%d.Thickness", i), 140.0) * um);
		fBTrapezoidDeltaESingleStartAngle.push_back(sett.GetValue(Form("BTrapezoidDeltaESingles.%d.StartAngle", i), -i*45) * deg);
	}
	fBTrapezoidDeltaESingleInnerRadius = sett.GetValue("BTrapezoidDeltaESingleInnerRadius", 20.) * mm;
	fBTrapezoidDeltaESingleOuterRadius = sett.GetValue("BTrapezoidDeltaESingleOuterRadius", 60.) * mm;
	fBTrapezoidDeltaESingleDeltaZ = sett.GetValue("BTrapezoidDeltaESingleDeltaZ", 20.) * mm;
	fBTrapezoidDeltaESingleNbOfRings = sett.GetValue("BTrapezoidDeltaESingleNbOfRings", 32);
	fBTrapezoidDeltaESingleNbOfStrips = sett.GetValue("BTrapezoidDeltaESingleNbOfStrips", 16);
	fBTrapezoidDeltaESingleEnergyResolution = sett.GetValue("BTrapezoidDeltaESingleEnergyResolution", 50) * keV;
	fBTrapezoidDeltaESingleFoilThickness = sett.GetValue("BTrapezoidDeltaESinglesFoilThickness", -1.) * um;

	// Backward Trapezoid Erest
	fUseBTrapezoidErest = sett.GetValue("UseBTrapezoidErest", 0);
	fNbOfBTrapezoidErestSingles = sett.GetValue("NbOfBTrapezoidErestSingles", 8);
	for(int i = 0; i < fNbOfBTrapezoidErestSingles; i++){
		fBTrapezoidErestSinglePosZ.push_back(sett.GetValue(Form("BTrapezoidErestSingles.%d.Z", i), 25.0) * mm);
		fBTrapezoidErestSingleThickness.push_back(sett.GetValue(Form("BTrapezoidErestSingles.%d.Thickness", i), 1000.0) * um);
		fBTrapezoidErestSingleStartAngle.push_back(sett.GetValue(Form("BTrapezoidErestSingles.%d.StartAngle", i), -i*45) * deg);
	}
	fBTrapezoidErestSingleInnerRadius = sett.GetValue("BTrapezoidErestSingleInnerRadius", 25.) * mm;
	fBTrapezoidErestSingleOuterRadius = sett.GetValue("BTrapezoidErestSingleOuterRadius", 80.) * mm;
	fBTrapezoidErestSingleDeltaZ = sett.GetValue("BTrapezoidErestSingleDeltaZ", 30.) * mm;
	fBTrapezoidErestSingleEnergyResolution = sett.GetValue("BTrapezoidErestSingleEnergyResolution", 50) * keV;


	// Miniball
	fNbOfMiniballClusters = sett.GetValue("NbOfMiniballClusters", 8);
	for(int clu = 0; clu < fNbOfMiniballClusters; clu++){
		fMiniballClusterNames.push_back(sett.GetValue(Form("MiniballCluster.Name.%i", clu), Form("cluster%i", clu)));
		fMiniballClusterTypes.push_back(sett.GetValue(Form("MiniballCluster.Type.%i", clu), 3));
		fMiniballClusterRho.push_back(sett.GetValue(Form("MiniballCluster.Rho.%i", clu), 100.) * mm);
		fMiniballClusterTheta.push_back(sett.GetValue(Form("MiniballCluster.Theta.%i", clu), 0.) * degree);
		fMiniballClusterPhi.push_back(sett.GetValue(Form("MiniballCluster.Phi.%i", clu), 0.) * degree);
		fMiniballClusterSpin.push_back(sett.GetValue(Form("MiniballCluster.Spin.%i", clu), 0.) * degree);
	}
	fMiniballEnergyResolutionCore = sett.GetValue("MiniballEnergyResolutionCore", 2.4) * keV;
	fMiniballEnergyResolutionSegment = sett.GetValue("MiniballEnergyResolutionSegment", 1.9) * keV;

	// LaBr
	fNbOfLaBrDetectors = sett.GetValue("NbOfLaBrDetectors", 6);
	for ( int det = 0 ; det < fNbOfLaBrDetectors ; ++det ){
	    fLaBrDetectorNames.push_back(sett.GetValue(Form("LaBrDetector.Name.%i", det), Form("LaBrDetector%i", det)));
	    fLaBrDetectorRho.push_back(sett.GetValue(Form("LaBrDetector.Rho.%i", det), 100.)* mm);
        fLaBrDetectorTheta.push_back(sett.GetValue(Form("LaBrDetector.Theta.%i", det), 0.)* degree);
        fLaBrDetectorPhi.push_back(sett.GetValue(Form("LaBrDetector.Phi.%i", det), 0.)* degree);
	}
}

void TRexSettings::Print(Option_t* opt) const {
	std::cout<<"TRexSettings: "<<opt<<std::endl
		<<"fPrimaryGenerator = "<<fPrimaryGenerator<<std::endl
		<<"fSimulateEjectiles = "<<fSimulateEjectiles<<std::endl
		<<"fSimulateGammas = "<<fSimulateGammas<<std::endl
		<<"fIncludeEnergyResolution = "<<fIncludeEnergyResolution<<std::endl
		<<"fIncludeVacuumChamber = "<<fIncludeVacuumChamber<<std::endl
		<<"fVacuumChamberType = "<<fVacuumChamberType<<std::endl
		<<"fVacuumChamberGas = "<<fVacuumChamberGas<<std::endl
		<<"fVacuumChamberGasPressure = "<<fVacuumChamberGasPressure*1000./bar<<" mbar"<<std::endl
		<<"fTestSourceEnergy = "<<fTestSourceEnergy/MeV<<" MeV"<<std::endl
		<<"---------- beam properties"<<std::endl
		<<"fBeamEnergy = "<<fBeamEnergy/MeV<<" MeV"<<std::endl
		<<"fBeamWidth = "<<fBeamWidth/mm<<" mm"<<std::endl
		<<"fThetaCmMin = "<<fThetaCmMin/degree<<" degree"<<std::endl
		<<"---------- reaction"<<std::endl
		<<"fProjectileZ = "<<fProjectileZ<<std::endl
		<<"fProjectileA = "<<fProjectileA<<std::endl
		<<"fTargetZ = "<<fTargetZ<<std::endl
		<<"fTargetA = "<<fTargetA<<std::endl
		<<"fEjectileZ = "<<fEjectileZ<<std::endl
		<<"fEjectileA = "<<fEjectileA<<std::endl
		<<"fRecoilZ = "<<fRecoilZ<<std::endl
		<<"fRecoilA = "<<fRecoilA<<std::endl
		<<"fProjectileName = "<<fProjectileName<<std::endl
		<<"fTargetName = "<<fTargetName<<std::endl
		<<"fEjectileName = "<<fEjectileName<<std::endl
		<<"fRecoilName = "<<fRecoilName<<std::endl
		<<"---------- other files"<<std::endl
		<<"fLevelFile = "<<fLevelFile<<std::endl
		<<"fAngularDistributionFile = "<<fAngularDistributionFile<<std::endl
		<<"fMassFile = "<<fMassFile<<std::endl
		<<"---------- alpha source"<<std::endl
		<<"fAlphaSourceDiameter = "<<fAlphaSourceDiameter/mm<<" mm"<<std::endl
		<<"fAlphaSourceThickness = "<<fAlphaSourceThickness/mm<<" mm"<<std::endl
		<<"---------- target"<<std::endl
		<<"fTargetDiameter = "<<fTargetDiameter/mm<<" mm"<<std::endl
		<<"fTargetThickness = "<<fTargetThickness/(mg/cm2)<<" mg/cm2"<<std::endl
		<<"fGasTargetLength = "<<fGasTargetLength/mm<<" mm"<<std::endl
		<<"fTargetPressure = "<<fTargetPressure*1000./bar<<" mbar"<<std::endl
		<<"fTargetMaterialDensity = "<<fTargetMaterialDensity/(g/cm3)<<" g/cm3"<<std::endl
		<<"fTargetMaterialName = "<<fTargetMaterialName<<std::endl
		<<"fTargetAtomicRatio = "<<fTargetAtomicRatio<<std::endl
		<<"fTransferOrCoulexProbability = "<<fTransferOrCoulexProbability<<std::endl
		<<"---------- "<<std::endl
		<<"fColours = "<<fColours<<std::endl
		<<"fVisualizationCut = "<<fVisualizationCut<<std::endl
		<<"fWriteAllEvents = "<<fWriteAllEvents<<std::endl
		<<"fConstructPCB =  "<<fConstructPCB<<std::endl
		<<std::endl;
}

G4double TRexSettings::GetTargetPhysicalLength(){
	if(GetGasTargetLength() > 0.) {
		return GetGasTargetLength();
	}
	G4double thickness = GetTargetThickness() / GetTargetMaterialDensity() ;

	return (thickness);
}

double TRexSettings::GetTargetThicknessMgPerCm2() { 
	return fTargetThickness/(mg/cm2); 
}
