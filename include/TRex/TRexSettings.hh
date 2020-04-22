/*
 * TRexSettings.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#ifndef TREXSETTINGS_HH_
#define TREXSETTINGS_HH_

#include "TEnv.h"

//#include "globals.hh"

#include <string>

class TRexSettings : public TObject {
	public:
		static TRexSettings* Get();
		virtual ~TRexSettings();

		void SetSettingsFile(std::string settingsFile) { fSettingsFile = settingsFile; }  //SetSettingsFile
		void ReadSettingsFile(std::string settingsFile);
		std::string GetSettingsFile() { return fSettingsFile; }  //GetSettingsFile
		std::string GetPrimaryGenerator() { return fPrimaryGenerator; }

		bool SimulateEjectiles() { return fSimulateEjectiles; }
		bool SimulateGammas() { return fSimulateGammas; }
		int IncludeEnergyResolution() { return fIncludeEnergyResolution; }
		int IncludeVacuumChamber() { return fIncludeVacuumChamber; }
		std::string GetVacuumChamberType() { return fVacuumChamberType; }
		std::string GetVacuumChamberGas() { return fVacuumChamberGas; }
		double GetVacuumChamberGasPressure() { return fVacuumChamberGasPressure; }

		void Print(Option_t* opt = "") const;

		// test source parameters
		double GetTestSourceEnergy() { return fTestSourceEnergy; }

		// gamma source parameter
		double GetGammaSourceEnergy() { return fGammaEnergy; }

		// beam parameters
		double GetBeamEnergy() { return fBeamEnergy; }
		double GetBeamWidth() { return fBeamWidth; }
		double GetThetaCmMin() { return fThetaCmMin; }

		int GetProjectileZ() { return fProjectileZ; }
		int GetProjectileA() { return fProjectileA; }
		int GetTargetZ() { return fTargetZ; }
		int GetTargetA() { return fTargetA; }
		int GetEjectileZ() { return fEjectileZ; }
		int GetEjectileA() { return fEjectileA; }
		int GetRecoilZ() { return fRecoilZ; }
		int GetRecoilA() { return fRecoilA; }
		std::string GetProjectileName() { return fProjectileName; }
		std::string GetTargetName() { return fTargetName; }
		std::string GetEjectileName() { return fEjectileName; }
		std::string GetRecoilName() { return fRecoilName; }

		std::string GetTargetMaterialName() { return fTargetMaterialName; }
		double GetTargetAtomicRatio() { return fTargetAtomicRatio; }
		double GetTransferOrCoulexProbability() { return fTransferOrCoulexProbability; }

		std::string GetLevelFile() { return fLevelFile; }
		std::string GetAngularDistributionFile() { return fAngularDistributionFile; }
		std::string GetMassFile() { return fMassFile; }

		// alpha source  parameters
		double GetAlphaSourceDiameter() { return fAlphaSourceDiameter; }
		double GetAlphaSourceThickness() { return fAlphaSourceThickness; }

		// target dimensions (or inactive alpha source dimensions)
		double GetTargetDiameter() { return fTargetDiameter; }
		double GetTargetThickness() { return fTargetThickness; }
		double GetTargetThicknessMgPerCm2();
		double GetGasTargetLength() { return fGasTargetLength; }
		double GetTargetPressure() { return fTargetPressure; }
		// returns the target length in um
		double GetTargetPhysicalLength();
		//std::string GetTargetMaterial() { return fTargetMaterial; }
		double GetTargetMaterialDensity() { return fTargetMaterialDensity; }
		void SetTargetMaterialDensity(double density) { fTargetMaterialDensity = density; }
		void SetTargetThickness(double thickness) { fTargetThickness = thickness; }

		// visualization
		int Colours() { return fColours; }
		bool VisualizationCut() { return fVisualizationCut; }
		void VisualizationCut(bool cut) { fVisualizationCut = cut; }

		// fill always the detector tree regardless if a detector was hit or not ?
		int WriteAllEvents() { return fWriteAllEvents; }


		//////////////////
		// detectors
		//////////////////
		bool ConstructPCB() { return fConstructPCB; }
		bool ResistiveStrips() { return fResistiveStrips; }

		// FCD deltaE
		int UseFCDdeltaE() { return fUseFCDdeltaE; }
		int GetNbOfFCDdeltaESingles() { return fNbOfFCDdeltaESingles; }
		std::vector<double> GetFCDdeltaESinglePosX() { return fFCDdeltaESinglePosX; }
		std::vector<double> GetFCDdeltaESinglePosY() { return fFCDdeltaESinglePosY; }
		std::vector<double> GetFCDdeltaESinglePosZ() { return fFCDdeltaESinglePosZ; }
		std::vector<double> GetFCDdeltaESingleStartAngle() { return fFCDdeltaESingleStartAngle; }
		std::vector<double> GetFCDdeltaESingleThickness() { return fFCDdeltaESingleThickness; }
		double GetFCDdeltaESingleDeadLayer() { return fFCDdeltaESingleDeadLayer; }
		double GetFCDdeltaESingleInnerRadius() { return fFCDdeltaESingleInnerRadius; }
		double GetFCDdeltaESingleOuterRadius() { return fFCDdeltaESingleOuterRadius; }
		double GetFCDdeltaESingleRingWidth() { return fFCDdeltaESingleRingWidth; }
		double GetFCDdeltaESingleSpanningAngle() { return fFCDdeltaESingleSpanningAngle; }
		double GetFCDdeltaESingleStripWidth() { return fFCDdeltaESingleStripWidth; }
		int FCDTransferTo16Strips() { return fFCDTransferTo16Strips; }
		double GetFCDdeltaESingleEnergyResolution() { return fFCDdeltaESingleEnergyResolution; }
		double GetFCDdeltaESingleFoilThickness() { return fFCDdeltaESingleFoilThickness; }
		// FCD Erest
		int UseFCDErest() { return fUseFCDErest; }
		int GetNbOfFCDErestSingles() { return fNbOfFCDErestSingles; }
		std::vector<double> GetFCDErestSinglePosX() { return fFCDErestSinglePosX; }
		std::vector<double> GetFCDErestSinglePosY() { return fFCDErestSinglePosY; }
		std::vector<double> GetFCDErestSinglePosZ() { return fFCDErestSinglePosZ; }
		std::vector<double> GetFCDErestSingleStartAngle() { return fFCDErestSingleStartAngle; }
		std::vector<double> GetFCDErestSingleThickness() { return fFCDErestSingleThickness; }
		double GetFCDErestSingleDeadLayer() { return fFCDErestSingleDeadLayer; }
		double GetFCDErestSingleInnerRadius() { return fFCDErestSingleInnerRadius; }
		double GetFCDErestSingleOuterRadius() { return fFCDErestSingleOuterRadius; }
		double GetFCDErestSingleSpanningAngle() { return fFCDErestSingleSpanningAngle; }
		double GetFCDErestSingleEnergyResolution() { return fFCDErestSingleEnergyResolution; }

		// BCD deltaE
		int UseBCDdeltaE() { return fUseBCDdeltaE; }
		int GetNbOfBCDdeltaESingles() { return fNbOfBCDdeltaESingles; }
		std::vector<double> GetBCDdeltaESinglePosX() { return fBCDdeltaESinglePosX; }
		std::vector<double> GetBCDdeltaESinglePosY() { return fBCDdeltaESinglePosY; }
		std::vector<double> GetBCDdeltaESinglePosZ() { return fBCDdeltaESinglePosZ; }
		std::vector<double> GetBCDdeltaESingleStartAngle() { return fBCDdeltaESingleStartAngle; }
		std::vector<double> GetBCDdeltaESingleThickness() { return fBCDdeltaESingleThickness; }
		double GetBCDdeltaESingleDeadLayer() { return fBCDdeltaESingleDeadLayer; }
		double GetBCDdeltaESingleInnerRadius() { return fBCDdeltaESingleInnerRadius; }
		double GetBCDdeltaESingleOuterRadius() { return fBCDdeltaESingleOuterRadius; }
		double GetBCDdeltaESingleRingWidth() { return fBCDdeltaESingleRingWidth; }
		double GetBCDdeltaESingleSpanningAngle() { return fBCDdeltaESingleSpanningAngle; }
		double GetBCDdeltaESingleStripWidth() { return fBCDdeltaESingleStripWidth; }
		int BCDTransferTo16Strips() { return fBCDTransferTo16Strips; }
		double GetBCDdeltaESingleEnergyResolution() { return fBCDdeltaESingleEnergyResolution; }
		double GetBCDdeltaESingleFoilThickness() { return fBCDdeltaESingleFoilThickness; }
		// BCD Erest
		int UseBCDErest() { return fUseBCDErest; }
		int GetNbOfBCDErestSingles() { return fNbOfBCDErestSingles; }
		std::vector<double> GetBCDErestSinglePosX() { return fBCDErestSinglePosX; }
		std::vector<double> GetBCDErestSinglePosY() { return fBCDErestSinglePosY; }
		std::vector<double> GetBCDErestSinglePosZ() { return fBCDErestSinglePosZ; }
		std::vector<double> GetBCDErestSingleStartAngle() { return fBCDErestSingleStartAngle; }
		std::vector<double> GetBCDErestSingleThickness() { return fBCDErestSingleThickness; }
		double GetBCDErestSingleDeadLayer() { return fBCDErestSingleDeadLayer; }
		double GetBCDErestSingleInnerRadius() { return fBCDErestSingleInnerRadius; }
		double GetBCDErestSingleOuterRadius() { return fBCDErestSingleOuterRadius; }
		double GetBCDErestSingleSpanningAngle() { return fBCDErestSingleSpanningAngle; }
		double GetBCDErestSingleEnergyResolution() { return fBCDErestSingleEnergyResolution; }

		// FBarrel deltaE
		int UseFBarrelDeltaE() { return fUseFBarrelDeltaE; }
		int GetNbOfFBarrelDeltaESingles() { return fNbOfFBarrelDeltaESingles; }
		//std::vector<double> GetFBarrelDeltaESinglePosX() { return fFBarrelDeltaESinglePosX; }
		//std::vector<double> GetFBarrelDeltaESinglePosY() { return fFBarrelDeltaESinglePosY; }
		std::vector<double> GetFBarrelDeltaESinglePosZ() { return fFBarrelDeltaESinglePosZ; }
		std::vector<double> GetFBarrelDeltaESingleDistanceToBeam() { return fFBarrelDeltaESingleDistanceToBeam; }
		std::vector<double> GetFBarrelDeltaESingleStartAngle() { return fFBarrelDeltaESingleStartAngle; }
		std::vector<double> GetFBarrelDeltaESingleThickness() { return fFBarrelDeltaESingleThickness; }
		double GetFBarrelDeltaESingleDeadLayer() { return fFBarrelDeltaESingleDeadLayer; }
		double GetFBarrelDeltaESingleLengthX() { return fFBarrelDeltaESingleLengthX; }
		double GetFBarrelDeltaESingleLengthY() { return fFBarrelDeltaESingleLengthY; }
		double GetFBarrelDeltaESingleStripWidth() { return fFBarrelDeltaESingleStripWidth; }
		double GetFBarrelDeltaESingleEnergyResolution() { return fFBarrelDeltaESingleEnergyResolution; }
		double GetFBarrelDeltaESingleFoilThickness() { return fFBarrelDeltaESingleFoilThickness; }
		// FBarrel Erest
		int UseFBarrelErest() { return fUseFBarrelErest; }
		int GetNbOfFBarrelErestSingles() { return fNbOfFBarrelErestSingles; }
		//std::vector<double> GetFBarrelErestSinglePosX() { return fFBarrelErestSinglePosX; }
		//std::vector<double> GetFBarrelErestSinglePosY() { return fFBarrelErestSinglePosY; }
		std::vector<double> GetFBarrelErestSinglePosZ() { return fFBarrelErestSinglePosZ; }
		std::vector<double> GetFBarrelErestSingleDistanceToBeam() { return fFBarrelErestSingleDistanceToBeam; }
		std::vector<double> GetFBarrelErestSingleStartAngle() { return fFBarrelErestSingleStartAngle; }
		std::vector<double> GetFBarrelErestSingleThickness() { return fFBarrelErestSingleThickness; }
		double GetFBarrelErestSingleDeadLayer() { return fFBarrelErestSingleDeadLayer; }
		double GetFBarrelErestSingleLengthX() { return fFBarrelErestSingleLengthX; }
		double GetFBarrelErestSingleLengthY() { return fFBarrelErestSingleLengthY; }
		double GetFBarrelErestSingleEnergyResolution() { return fFBarrelErestSingleEnergyResolution; }
		// Second FBarrel deltaE
		int UseSecondFBarrelDeltaE() { return fUseSecondFBarrelDeltaE; }
		int GetNbOfSecondFBarrelDeltaESingles() { return fNbOfSecondFBarrelDeltaESingles; }
		std::vector<double> GetSecondFBarrelDeltaESinglePosZ() { return fSecondFBarrelDeltaESinglePosZ; }
		std::vector<double> GetSecondFBarrelDeltaESingleDistanceToBeam() { return fSecondFBarrelDeltaESingleDistanceToBeam; }
		std::vector<double> GetSecondFBarrelDeltaESingleStartAngle() { return fSecondFBarrelDeltaESingleStartAngle; }
		std::vector<double> GetSecondFBarrelDeltaESingleThickness() { return fSecondFBarrelDeltaESingleThickness; }
		double GetSecondFBarrelDeltaESingleDeadLayer() { return fSecondFBarrelDeltaESingleDeadLayer; }
		double GetSecondFBarrelDeltaESingleLengthX() { return fSecondFBarrelDeltaESingleLengthX; }
		double GetSecondFBarrelDeltaESingleLengthY() { return fSecondFBarrelDeltaESingleLengthY; }
		double GetSecondFBarrelDeltaESingleStripWidth() { return fSecondFBarrelDeltaESingleStripWidth; }
		double GetSecondFBarrelDeltaESingleEnergyResolution() { return fSecondFBarrelDeltaESingleEnergyResolution; }
		double GetSecondFBarrelDeltaESingleFoilThickness() { return fSecondFBarrelDeltaESingleFoilThickness; }

		// MBarrel deltaE
		int UseMBarrelDeltaE() { return fUseMBarrelDeltaE; }
		int GetNbOfMBarrelDeltaESingles() { return fNbOfMBarrelDeltaESingles; }
		//std::vector<double> GetMBarrelDeltaESinglePosX() { return fMBarrelDeltaESinglePosX; }
		//std::vector<double> GetMBarrelDeltaESinglePosY() { return fMBarrelDeltaESinglePosY; }
		std::vector<double> GetMBarrelDeltaESinglePosZ() { return fMBarrelDeltaESinglePosZ; }
		std::vector<double> GetMBarrelDeltaESingleDistanceToBeam() { return fMBarrelDeltaESingleDistanceToBeam; }
		std::vector<double> GetMBarrelDeltaESingleStartAngle() { return fMBarrelDeltaESingleStartAngle; }
		std::vector<double> GetMBarrelDeltaESingleThickness() { return fMBarrelDeltaESingleThickness; }
		double GetMBarrelDeltaESingleDeadLayer() { return fMBarrelDeltaESingleDeadLayer; }
		double GetMBarrelDeltaESingleLengthX() { return fMBarrelDeltaESingleLengthX; }
		double GetMBarrelDeltaESingleLengthY() { return fMBarrelDeltaESingleLengthY; }
		double GetMBarrelDeltaESingleStripWidth() { return fMBarrelDeltaESingleStripWidth; }
		double GetMBarrelDeltaESingleEnergyResolution() { return fMBarrelDeltaESingleEnergyResolution; }
		double GetMBarrelDeltaESingleFoilThickness() { return fMBarrelDeltaESingleFoilThickness; }
		// MBarrel Erest
		int UseMBarrelErest() { return fUseMBarrelErest; }
		int GetNbOfMBarrelErestSingles() { return fNbOfMBarrelErestSingles; }
		//std::vector<double> GetMBarrelErestSinglePosX() { return fMBarrelErestSinglePosX; }
		//std::vector<double> GetMBarrelErestSinglePosY() { return fMBarrelErestSinglePosY; }
		std::vector<double> GetMBarrelErestSinglePosZ() { return fMBarrelErestSinglePosZ; }
		std::vector<double> GetMBarrelErestSingleDistanceToBeam() { return fMBarrelErestSingleDistanceToBeam; }
		std::vector<double> GetMBarrelErestSingleStartAngle() { return fMBarrelErestSingleStartAngle; }
		std::vector<double> GetMBarrelErestSingleThickness() { return fMBarrelErestSingleThickness; }
		double GetMBarrelErestSingleDeadLayer() { return fMBarrelErestSingleDeadLayer; }
		double GetMBarrelErestSingleLengthX() { return fMBarrelErestSingleLengthX; }
		double GetMBarrelErestSingleLengthY() { return fMBarrelErestSingleLengthY; }
		double GetMBarrelErestSingleEnergyResolution() { return fMBarrelErestSingleEnergyResolution; }

		// BBarrel deltaE
		int UseBBarrelDeltaE() { return fUseBBarrelDeltaE; }
		int GetNbOfBBarrelDeltaESingles() { return fNbOfBBarrelDeltaESingles; }
		//std::vector<double> GetBBarrelDeltaESinglePosX() { return fBBarrelDeltaESinglePosX; }
		//std::vector<double> GetBBarrelDeltaESinglePosY() { return fBBarrelDeltaESinglePosY; }
		std::vector<double> GetBBarrelDeltaESinglePosZ() { return fBBarrelDeltaESinglePosZ; }
		std::vector<double> GetBBarrelDeltaESingleDistanceToBeam() { return fBBarrelDeltaESingleDistanceToBeam; }
		std::vector<double> GetBBarrelDeltaESingleStartAngle() { return fBBarrelDeltaESingleStartAngle; }
		std::vector<double> GetBBarrelDeltaESingleThickness() { return fBBarrelDeltaESingleThickness; }
		double GetBBarrelDeltaESingleDeadLayer() { return fBBarrelDeltaESingleDeadLayer; }
		double GetBBarrelDeltaESingleLengthX() { return fBBarrelDeltaESingleLengthX; }
		double GetBBarrelDeltaESingleLengthY() { return fBBarrelDeltaESingleLengthY; }
		double GetBBarrelDeltaESingleStripWidth() { return fBBarrelDeltaESingleStripWidth; }
		double GetBBarrelDeltaESingleEnergyResolution() { return fBBarrelDeltaESingleEnergyResolution; }
		double GetBBarrelDeltaESingleFoilThickness() { return fBBarrelDeltaESingleFoilThickness; }
		// BBarrel Erest
		int UseBBarrelErest() { return fUseBBarrelErest; }
		int GetNbOfBBarrelErestSingles() { return fNbOfBBarrelErestSingles; }
		//std::vector<double> GetBBarrelErestSinglePosX() { return fBBarrelErestSinglePosX; }
		//std::vector<double> GetBBarrelErestSinglePosY() { return fBBarrelErestSinglePosY; }
		std::vector<double> GetBBarrelErestSinglePosZ() { return fBBarrelErestSinglePosZ; }
		std::vector<double> GetBBarrelErestSingleDistanceToBeam() { return fBBarrelErestSingleDistanceToBeam; }
		std::vector<double> GetBBarrelErestSingleStartAngle() { return fBBarrelErestSingleStartAngle; }
		std::vector<double> GetBBarrelErestSingleThickness() { return fBBarrelErestSingleThickness; }
		double GetBBarrelErestSingleDeadLayer() { return fBBarrelErestSingleDeadLayer; }
		double GetBBarrelErestSingleLengthX() { return fBBarrelErestSingleLengthX; }
		double GetBBarrelErestSingleLengthY() { return fBBarrelErestSingleLengthY; }
		double GetBBarrelErestSingleEnergyResolution() { return fBBarrelErestSingleEnergyResolution; }
		// Second BBarrel deltaE
		int UseSecondBBarrelDeltaE() { return fUseSecondBBarrelDeltaE; }
		int GetNbOfSecondBBarrelDeltaESingles() { return fNbOfSecondBBarrelDeltaESingles; }
		std::vector<double> GetSecondBBarrelDeltaESinglePosZ() { return fSecondBBarrelDeltaESinglePosZ; }
		std::vector<double> GetSecondBBarrelDeltaESingleDistanceToBeam() { return fSecondBBarrelDeltaESingleDistanceToBeam; }
		std::vector<double> GetSecondBBarrelDeltaESingleStartAngle() { return fSecondBBarrelDeltaESingleStartAngle; }
		std::vector<double> GetSecondBBarrelDeltaESingleThickness() { return fSecondBBarrelDeltaESingleThickness; }
		double GetSecondBBarrelDeltaESingleDeadLayer() { return fSecondBBarrelDeltaESingleDeadLayer; }
		double GetSecondBBarrelDeltaESingleLengthX() { return fSecondBBarrelDeltaESingleLengthX; }
		double GetSecondBBarrelDeltaESingleLengthY() { return fSecondBBarrelDeltaESingleLengthY; }
		double GetSecondBBarrelDeltaESingleStripWidth() { return fSecondBBarrelDeltaESingleStripWidth; }
		double GetSecondBBarrelDeltaESingleEnergyResolution() { return fSecondBBarrelDeltaESingleEnergyResolution; }
		double GetSecondBBarrelDeltaESingleFoilThickness() { return fSecondBBarrelDeltaESingleFoilThickness; }

		// Forward Trapezoid deltaE
		int UseFTrapezoidDeltaE() { return fUseFTrapezoidDeltaE; }
		int GetNbOfFTrapezoidDeltaESingles() { return fNbOfFTrapezoidDeltaESingles; }
		std::vector<double> GetFTrapezoidDeltaESinglePosZ() { return fFTrapezoidDeltaESinglePosZ; }
		double GetFTrapezoidDeltaESingleInnerRadius() { return fFTrapezoidDeltaESingleInnerRadius; }
		double GetFTrapezoidDeltaESingleOuterRadius() { return fFTrapezoidDeltaESingleOuterRadius; }
		double GetFTrapezoidDeltaESingleDeltaZ() { return fFTrapezoidDeltaESingleDeltaZ; }
		std::vector<double> GetFTrapezoidDeltaESingleThickness() { return fFTrapezoidDeltaESingleThickness; }
		std::vector<double> GetFTrapezoidDeltaESingleStartAngle() { return fFTrapezoidDeltaESingleStartAngle; }
		double GetFTrapezoidDeltaESingleNbOfRings() { return fFTrapezoidDeltaESingleNbOfRings; }
		double GetFTrapezoidDeltaESingleNbOfStrips() { return fFTrapezoidDeltaESingleNbOfStrips; }
		double GetFTrapezoidDeltaESingleEnergyResolution() { return fFTrapezoidDeltaESingleEnergyResolution; }
		double GetFTrapezoidDeltaESingleFoilThickness() { return fFTrapezoidDeltaESingleFoilThickness; }
		// Forward Trapezoid Erest
		int UseFTrapezoidErest() { return fUseFTrapezoidErest; }
		int GetNbOfFTrapezoidErestSingles() { return fNbOfFTrapezoidErestSingles; }
		std::vector<double> GetFTrapezoidErestSinglePosZ() { return fFTrapezoidErestSinglePosZ; }
		double GetFTrapezoidErestSingleInnerRadius() { return fFTrapezoidErestSingleInnerRadius; }
		double GetFTrapezoidErestSingleOuterRadius() { return fFTrapezoidErestSingleOuterRadius; }
		double GetFTrapezoidErestSingleDeltaZ() { return fFTrapezoidErestSingleDeltaZ; }
		std::vector<double> GetFTrapezoidErestSingleThickness() { return fFTrapezoidErestSingleThickness; }
		std::vector<double> GetFTrapezoidErestSingleStartAngle() { return fFTrapezoidErestSingleStartAngle; }
		double GetFTrapezoidErestSingleEnergyResolution() { return fFTrapezoidErestSingleEnergyResolution; }

		// Backward Trapezoid deltaE
		int UseBTrapezoidDeltaE() { return fUseBTrapezoidDeltaE; }
		int GetNbOfBTrapezoidDeltaESingles() { return fNbOfBTrapezoidDeltaESingles; }
		std::vector<double> GetBTrapezoidDeltaESinglePosZ() { return fBTrapezoidDeltaESinglePosZ; }
		double GetBTrapezoidDeltaESingleInnerRadius() { return fBTrapezoidDeltaESingleInnerRadius; }
		double GetBTrapezoidDeltaESingleOuterRadius() { return fBTrapezoidDeltaESingleOuterRadius; }
		double GetBTrapezoidDeltaESingleDeltaZ() { return fBTrapezoidDeltaESingleDeltaZ; }
		std::vector<double> GetBTrapezoidDeltaESingleThickness() { return fBTrapezoidDeltaESingleThickness; }
		std::vector<double> GetBTrapezoidDeltaESingleStartAngle() { return fBTrapezoidDeltaESingleStartAngle; }
		double GetBTrapezoidDeltaESingleNbOfRings() { return fBTrapezoidDeltaESingleNbOfRings; }
		double GetBTrapezoidDeltaESingleNbOfStrips() { return fBTrapezoidDeltaESingleNbOfStrips; }
		double GetBTrapezoidDeltaESingleEnergyResolution() { return fBTrapezoidDeltaESingleEnergyResolution; }
		double GetBTrapezoidDeltaESingleFoilThickness() { return fBTrapezoidDeltaESingleFoilThickness; }
		// Backward Trapezoid Erest
		int UseBTrapezoidErest() { return fUseBTrapezoidErest; }
		int GetNbOfBTrapezoidErestSingles() { return fNbOfBTrapezoidErestSingles; }
		std::vector<double> GetBTrapezoidErestSinglePosZ() { return fBTrapezoidErestSinglePosZ; }
		double GetBTrapezoidErestSingleInnerRadius() { return fBTrapezoidErestSingleInnerRadius; }
		double GetBTrapezoidErestSingleOuterRadius() { return fBTrapezoidErestSingleOuterRadius; }
		double GetBTrapezoidErestSingleDeltaZ() { return fBTrapezoidErestSingleDeltaZ; }
		std::vector<double> GetBTrapezoidErestSingleThickness() { return fBTrapezoidErestSingleThickness; }
		std::vector<double> GetBTrapezoidErestSingleStartAngle() { return fBTrapezoidErestSingleStartAngle; }
		double GetBTrapezoidErestSingleEnergyResolution() { return fBTrapezoidErestSingleEnergyResolution; }

		// Miniball
		int GetNbOfMiniballClusters() { return fNbOfMiniballClusters; }
		std::vector<std::string> GetMiniballClusterNames() { return fMiniballClusterNames; }
		std::vector<int> GetMiniballClusterTypes() { return fMiniballClusterTypes; }
		std::vector<double> GetMiniballClusterRho() { return fMiniballClusterRho; }
		std::vector<double> GetMiniballClusterTheta() { return fMiniballClusterTheta; }
		std::vector<double> GetMiniballClusterPhi() { return fMiniballClusterPhi; }
		std::vector<double> GetMiniballClusterSpin() { return fMiniballClusterSpin; }
		double GetMiniballEnergyResolutionCore() { return fMiniballEnergyResolutionCore; }
		double GetMiniballEnergyResolutionSegment() { return fMiniballEnergyResolutionSegment; }

		// LaBr
		int GetNbOfLaBrDetectors() { return fNbOfLaBrDetectors; }
		std::vector<std::string> GetLaBrDetectorNames() { return fLaBrDetectorNames; }
		std::vector<double> GetLaBrDetectorRho() { return fLaBrDetectorRho; }
        std::vector<double> GetLaBrDetectorTheta() { return fLaBrDetectorTheta; }
        std::vector<double> GetLaBrDetectorPhi() { return fLaBrDetectorPhi; }
		
		// this constructor has to be public to be able to
		// write the class to file, but it should never be used!
		TRexSettings();
	private:
		static TRexSettings* fSettings;

		std::string fSettingsFile;
		std::string fPrimaryGenerator;
		bool fSimulateEjectiles;
		bool fSimulateGammas;
		int fIncludeEnergyResolution;
		int fIncludeVacuumChamber;
		std::string fVacuumChamberType;
		std::string fVacuumChamberGas;
		double fVacuumChamberGasPressure;

		double fTestSourceEnergy;
		double fBeamEnergy;
		double fBeamWidth;
		double fThetaCmMin;

		int fProjectileZ, fProjectileA;
		int fTargetZ, fTargetA;
		int fEjectileZ, fEjectileA;
		int fRecoilZ, fRecoilA;
		std::string fProjectileName, fTargetName, fEjectileName, fRecoilName;

		std::string fTargetMaterialName;
		double fTargetAtomicRatio;
		double fTransferOrCoulexProbability;

		std::string fLevelFile;
		std::string fAngularDistributionFile;
		std::string fMassFile;

		double fAlphaSourceDiameter;
		double fAlphaSourceThickness;

		double fGammaEnergy;

		double fTargetDiameter;
		double fTargetThickness;
		double fGasTargetLength;
		double fTargetPressure;
		//std::string fTargetMaterial;
		double fTargetMaterialDensity;

		int fColours;
		int fWriteAllEvents;
		bool fVisualizationCut;

		bool fConstructPCB;
		bool fResistiveStrips;

		// FCD deltaE
		int fUseFCDdeltaE;
		int fNbOfFCDdeltaESingles;
		std::vector<double> fFCDdeltaESinglePosX;
		std::vector<double> fFCDdeltaESinglePosY;
		std::vector<double> fFCDdeltaESinglePosZ;
		std::vector<double> fFCDdeltaESingleStartAngle;
		std::vector<double> fFCDdeltaESingleThickness;
		double fFCDdeltaESingleDeadLayer;
		double fFCDdeltaESingleInnerRadius;
		double fFCDdeltaESingleOuterRadius;
		double fFCDdeltaESingleRingWidth;
		double fFCDdeltaESingleSpanningAngle;
		double fFCDdeltaESingleStripWidth;
		int fFCDTransferTo16Strips;
		double fFCDdeltaESingleEnergyResolution;
		double fFCDdeltaESingleFoilThickness;
		// FCD Erest
		int fUseFCDErest;
		int fNbOfFCDErestSingles;
		std::vector<double> fFCDErestSinglePosX;
		std::vector<double> fFCDErestSinglePosY;
		std::vector<double> fFCDErestSinglePosZ;
		std::vector<double> fFCDErestSingleStartAngle;
		std::vector<double> fFCDErestSingleThickness;
		double fFCDErestSingleDeadLayer;
		double fFCDErestSingleInnerRadius;
		double fFCDErestSingleOuterRadius;
		double fFCDErestSingleSpanningAngle;
		double fFCDErestSingleEnergyResolution;

		// BCD deltaE
		int fUseBCDdeltaE;
		int fNbOfBCDdeltaESingles;
		std::vector<double> fBCDdeltaESinglePosX;
		std::vector<double> fBCDdeltaESinglePosY;
		std::vector<double> fBCDdeltaESinglePosZ;
		std::vector<double> fBCDdeltaESingleStartAngle;
		std::vector<double> fBCDdeltaESingleThickness;
		double fBCDdeltaESingleDeadLayer;
		double fBCDdeltaESingleInnerRadius;
		double fBCDdeltaESingleOuterRadius;
		double fBCDdeltaESingleRingWidth;
		double fBCDdeltaESingleSpanningAngle;
		double fBCDdeltaESingleStripWidth;
		int fBCDTransferTo16Strips;
		double fBCDdeltaESingleEnergyResolution;
		double fBCDdeltaESingleFoilThickness;
		// BCD Erest
		int fUseBCDErest;
		int fNbOfBCDErestSingles;
		std::vector<double> fBCDErestSinglePosX;
		std::vector<double> fBCDErestSinglePosY;
		std::vector<double> fBCDErestSinglePosZ;
		std::vector<double> fBCDErestSingleStartAngle;
		std::vector<double> fBCDErestSingleThickness;
		double fBCDErestSingleDeadLayer;
		double fBCDErestSingleInnerRadius;
		double fBCDErestSingleOuterRadius;
		double fBCDErestSingleSpanningAngle;
		double fBCDErestSingleEnergyResolution;

		// FBarrel deltaE
		int fUseFBarrelDeltaE;
		int fNbOfFBarrelDeltaESingles;
		//std::vector<double> fFBarrelDeltaESinglePosX;
		//std::vector<double> fFBarrelDeltaESinglePosY;
		std::vector<double> fFBarrelDeltaESinglePosZ;
		std::vector<double> fFBarrelDeltaESingleDistanceToBeam;
		std::vector<double> fFBarrelDeltaESingleStartAngle;
		std::vector<double> fFBarrelDeltaESingleThickness;
		double fFBarrelDeltaESingleDeadLayer;
		double fFBarrelDeltaESingleLengthX;
		double fFBarrelDeltaESingleLengthY;
		double fFBarrelDeltaESingleStripWidth;
		double fFBarrelDeltaESingleEnergyResolution;
		double fFBarrelDeltaESingleFoilThickness;
		// FBarrel Erest
		int fUseFBarrelErest;
		int fNbOfFBarrelErestSingles;
		//std::vector<double> fFBarrelErestSinglePosX;
		//std::vector<double> fFBarrelErestSinglePosY;
		std::vector<double> fFBarrelErestSinglePosZ;
		std::vector<double> fFBarrelErestSingleDistanceToBeam;
		std::vector<double> fFBarrelErestSingleStartAngle;
		std::vector<double> fFBarrelErestSingleThickness;
		double fFBarrelErestSingleDeadLayer;
		double fFBarrelErestSingleLengthX;
		double fFBarrelErestSingleLengthY;
		double fFBarrelErestSingleEnergyResolution;
		// Second FBarrel deltaE
		int fUseSecondFBarrelDeltaE;
		int fNbOfSecondFBarrelDeltaESingles;
		std::vector<double> fSecondFBarrelDeltaESinglePosZ;
		std::vector<double> fSecondFBarrelDeltaESingleDistanceToBeam;
		std::vector<double> fSecondFBarrelDeltaESingleStartAngle;
		std::vector<double> fSecondFBarrelDeltaESingleThickness;
		double fSecondFBarrelDeltaESingleDeadLayer;
		double fSecondFBarrelDeltaESingleLengthX;
		double fSecondFBarrelDeltaESingleLengthY;
		double fSecondFBarrelDeltaESingleStripWidth;
		double fSecondFBarrelDeltaESingleEnergyResolution;
		double fSecondFBarrelDeltaESingleFoilThickness;

		// MBarrel deltaE
		int fUseMBarrelDeltaE;
		int fNbOfMBarrelDeltaESingles;
		//std::vector<double> fMBarrelDeltaESinglePosX;
		//std::vector<double> fMBarrelDeltaESinglePosY;
		std::vector<double> fMBarrelDeltaESinglePosZ;
		std::vector<double> fMBarrelDeltaESingleDistanceToBeam;
		std::vector<double> fMBarrelDeltaESingleStartAngle;
		std::vector<double> fMBarrelDeltaESingleThickness;
		double fMBarrelDeltaESingleDeadLayer;
		double fMBarrelDeltaESingleLengthX;
		double fMBarrelDeltaESingleLengthY;
		double fMBarrelDeltaESingleStripWidth;
		double fMBarrelDeltaESingleEnergyResolution;
		double fMBarrelDeltaESingleFoilThickness;
		// MBarrel Erest
		int fUseMBarrelErest;
		int fNbOfMBarrelErestSingles;
		//std::vector<double> fMBarrelErestSinglePosX;
		//std::vector<double> fMBarrelErestSinglePosY;
		std::vector<double> fMBarrelErestSinglePosZ;
		std::vector<double> fMBarrelErestSingleDistanceToBeam;
		std::vector<double> fMBarrelErestSingleStartAngle;
		std::vector<double> fMBarrelErestSingleThickness;
		double fMBarrelErestSingleDeadLayer;
		double fMBarrelErestSingleLengthX;
		double fMBarrelErestSingleLengthY;
		double fMBarrelErestSingleEnergyResolution;

		// BBarrel deltaE
		int fUseBBarrelDeltaE;
		int fNbOfBBarrelDeltaESingles;
		//std::vector<double> fBBarrelDeltaESinglePosX;
		//std::vector<double> fBBarrelDeltaESinglePosY;
		std::vector<double> fBBarrelDeltaESinglePosZ;
		std::vector<double> fBBarrelDeltaESingleDistanceToBeam;
		std::vector<double> fBBarrelDeltaESingleStartAngle;
		std::vector<double> fBBarrelDeltaESingleThickness;
		double fBBarrelDeltaESingleDeadLayer;
		double fBBarrelDeltaESingleLengthX;
		double fBBarrelDeltaESingleLengthY;
		double fBBarrelDeltaESingleStripWidth;
		double fBBarrelDeltaESingleEnergyResolution;
		double fBBarrelDeltaESingleFoilThickness;
		// BBarrel Erest
		int fUseBBarrelErest;
		int fNbOfBBarrelErestSingles;
		//std::vector<double> fBBarrelErestSinglePosX;
		//std::vector<double> fBBarrelErestSinglePosY;
		std::vector<double> fBBarrelErestSinglePosZ;
		std::vector<double> fBBarrelErestSingleDistanceToBeam;
		std::vector<double> fBBarrelErestSingleStartAngle;
		std::vector<double> fBBarrelErestSingleThickness;
		double fBBarrelErestSingleDeadLayer;
		double fBBarrelErestSingleLengthX;
		double fBBarrelErestSingleLengthY;
		double fBBarrelErestSingleEnergyResolution;
		// Second BBarrel deltaE
		int fUseSecondBBarrelDeltaE;
		int fNbOfSecondBBarrelDeltaESingles;
		std::vector<double> fSecondBBarrelDeltaESinglePosZ;
		std::vector<double> fSecondBBarrelDeltaESingleDistanceToBeam;
		std::vector<double> fSecondBBarrelDeltaESingleStartAngle;
		std::vector<double> fSecondBBarrelDeltaESingleThickness;
		double fSecondBBarrelDeltaESingleDeadLayer;
		double fSecondBBarrelDeltaESingleLengthX;
		double fSecondBBarrelDeltaESingleLengthY;
		double fSecondBBarrelDeltaESingleStripWidth;
		double fSecondBBarrelDeltaESingleEnergyResolution;
		double fSecondBBarrelDeltaESingleFoilThickness;

		// Forward Trapezoid deltaE
		int fUseFTrapezoidDeltaE;
		int fNbOfFTrapezoidDeltaESingles;
		std::vector<double> fFTrapezoidDeltaESinglePosZ;
		double fFTrapezoidDeltaESingleInnerRadius;
		double fFTrapezoidDeltaESingleOuterRadius;
		double fFTrapezoidDeltaESingleDeltaZ;
		std::vector<double> fFTrapezoidDeltaESingleThickness;
		std::vector<double> fFTrapezoidDeltaESingleStartAngle;
		int fFTrapezoidDeltaESingleNbOfRings;
		int fFTrapezoidDeltaESingleNbOfStrips;
		double fFTrapezoidDeltaESingleEnergyResolution;
		double fFTrapezoidDeltaESingleFoilThickness;
		// Forward Trapezoid Erest
		int fUseFTrapezoidErest;
		int fNbOfFTrapezoidErestSingles;
		std::vector<double> fFTrapezoidErestSinglePosZ;
		double fFTrapezoidErestSingleInnerRadius;
		double fFTrapezoidErestSingleOuterRadius;
		double fFTrapezoidErestSingleDeltaZ;
		std::vector<double> fFTrapezoidErestSingleThickness;
		std::vector<double> fFTrapezoidErestSingleStartAngle;
		double fFTrapezoidErestSingleEnergyResolution;

		// Backward Trapezoid deltaE
		int fUseBTrapezoidDeltaE;
		int fNbOfBTrapezoidDeltaESingles;
		std::vector<double> fBTrapezoidDeltaESinglePosZ;
		double fBTrapezoidDeltaESingleInnerRadius;
		double fBTrapezoidDeltaESingleOuterRadius;
		double fBTrapezoidDeltaESingleDeltaZ;
		std::vector<double> fBTrapezoidDeltaESingleThickness;
		std::vector<double> fBTrapezoidDeltaESingleStartAngle;
		int fBTrapezoidDeltaESingleNbOfRings;
		int fBTrapezoidDeltaESingleNbOfStrips;
		double fBTrapezoidDeltaESingleEnergyResolution;
		double fBTrapezoidDeltaESingleFoilThickness;
		// Backward Trapezoid Erest
		int fUseBTrapezoidErest;
		int fNbOfBTrapezoidErestSingles;
		std::vector<double> fBTrapezoidErestSinglePosZ;
		double fBTrapezoidErestSingleInnerRadius;
		double fBTrapezoidErestSingleOuterRadius;
		double fBTrapezoidErestSingleDeltaZ;
		std::vector<double> fBTrapezoidErestSingleThickness;
		std::vector<double> fBTrapezoidErestSingleStartAngle;
		double fBTrapezoidErestSingleEnergyResolution;

		// Miniball
		int fNbOfMiniballClusters;
		std::vector<std::string> fMiniballClusterNames;
		std::vector<int> fMiniballClusterTypes;
		std::vector<double> fMiniballClusterRho;
		std::vector<double> fMiniballClusterTheta;
		std::vector<double> fMiniballClusterPhi;
		std::vector<double> fMiniballClusterSpin;
		double fMiniballEnergyResolutionCore;
		double fMiniballEnergyResolutionSegment;

		// LaBr
		int fNbOfLaBrDetectors;
		std::vector<std::string> fLaBrDetectorNames;
		std::vector<double> fLaBrDetectorRho;
		std::vector<double> fLaBrDetectorTheta;
		std::vector<double> fLaBrDetectorPhi;

		ClassDef(TRexSettings, 1)
};

#endif /* TREXSETTINGS_HH_ */
