/*
 * TRexAngularDistribution.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexAngularDistribution.hh"
#include "TRex/TRexSettings.hh"

#include <G4SystemOfUnits.hh>
#include <G4PhysicalConstants.hh>

TRexAngularDistribution::TRexAngularDistribution() :
	fScatteringProbabilitySingle(0) {
	// read the level file
	ReadLevelFile();
	FillMiniballLevels();

	// write the given angular distribution from the text file into Root histograms
	FillAngularDistributionGraphs();
	FillAngularDistributionHistos();

	// calculate scattering probability
	CalculateArealDensity();
	CalculateCrossSectionIntegral();
	CalculateScatteringProbability();
}

TRexAngularDistribution::~TRexAngularDistribution() {
	// TODO Auto-generated destructor stub
}


void TRexAngularDistribution::GeneratePrimaries(G4Event *anEvent) {
	// clear old event
	fGammaTheta->resize(0);
	fGammaPhi->resize(0);
	fGammaEnergy->resize(0);

	// shoot the emission point
	ShootReactionPosition();

	// calculate reaction energy in the target
	CalculateReactionEnergyInTheTarget();

	// shoot reaction type and extract the corresponding excitation energy
	ShootReactionTypeAndExcitationEnergy();

	// choose right ejectile and the recoil depending on the reaction
	SetEjectileAndRecoil();

	// shoot thetaCM angle
	ShootThetaCm(fReaction);

	// shoot energy and direction
	ShootEjectileAndRecoilDirections();

	if(TRexSettings::Get()->SimulateGammas() && fReaction < fNbOfLevels) {
		// shoot energy and direction of the gamma
		ShootGamma();
	}

	// set the gun properties and create the primary vertex
	SetEjectileGun(anEvent);
	SetRecoilGun(anEvent);

	if(TRexSettings::Get()->SimulateGammas() && fReaction < fNbOfLevels) {
		SetGammaGun(anEvent);
	}

	FillTree();
}

void TRexAngularDistribution::SetEjectileAndRecoil() {
	// Transfer or Coulex reaction
	if(fReaction < fNbOfLevels) {
		fTargetZ = TRexSettings::Get()->GetTargetZ();
		fTargetA = TRexSettings::Get()->GetTargetA();
		fEjectileZ = TRexSettings::Get()->GetEjectileZ();
		fEjectileA = TRexSettings::Get()->GetEjectileA();
		fRecoilZ = TRexSettings::Get()->GetRecoilZ();
		fRecoilA = TRexSettings::Get()->GetRecoilA();
	} else { // elastic Rutherford scattering
		size_t index = fReaction - fNbOfLevels;

		fTargetZ = fTargetMaterial->GetElement(index)->Z();
		fTargetA = fTargetMaterial->GetElement(index)->A();
		fEjectileZ = TRexSettings::Get()->GetProjectileZ();
		fEjectileA = TRexSettings::Get()->GetProjectileA();
		fRecoilZ = fTargetMaterial->GetElement(index)->Z();
		fRecoilA = fTargetMaterial->GetElement(index)->A();
	}

	fTarget = *(fIsotopeTable->Search(fTargetZ, fTargetA - fTargetZ));
	fEjectile = *(fIsotopeTable->Search(fEjectileZ, fEjectileA - fEjectileZ));
	fRecoil = *(fIsotopeTable->Search(fRecoilZ, fRecoilA - fRecoilZ));
}

void TRexAngularDistribution::ShootThetaCm(int levelNb) {
	// get a random number (thetaCM) distributed according the histogram bin contents, i.e. the cross section sigma * sin(thetaCM)
	if(fReaction < fNbOfLevels) {
		fThetaCM = fHistos[levelNb].GetRandom() * rad;
	} else {
		// normalization constant
		double norm = 1./  (1./(sin(fThetaCM_min/rad * 0.5) * sin(fThetaCM_min/rad * 0.5)) -1);
		G4double rand = CLHEP::RandFlat::shoot(0., 1.);
		fThetaCM = 2.* asin(1. / sqrt(1. / sin(fThetaCM_min*0.5) / sin(fThetaCM_min*0.5) - rand / norm));

		//std::cout << "fThetaCM = " << fThetaCM / degree << std::endl;
	}
}


void TRexAngularDistribution::ShootReactionTypeAndExcitationEnergy() {
	// decide whether to simulate transfer reaction / Coulex reaction or elastic Rutherford scattering
	double tmp = CLHEP::RandFlat::shoot(0.,1.);

	if(tmp < TRexSettings::Get()->GetTransferOrCoulexProbability()) { //transfer reaction or Coulex
		// shoot transfer / Coulex reaction channel
		tmp = CLHEP::RandFlat::shoot(0., fScatteringProbabilitySingle[fNbOfLevels - 1]);

		for(fReaction = 0; tmp > fScatteringProbabilitySingle[fReaction]; fReaction++) {
			//nothing else, after this loop reaction is the reaction channel to be used (from 0 to NumberOfLevel-1 or NumberOfLevel+NumberOfElements-1)
		}

		fExcitationEnergy = fLevelEnergy[fReaction];
	} else { // elastic Rutherford scattering => reaction based on cross sections for elastic scattering on the different elements in the target
		if(fTargetMaterial->NumberOfElements() == 1) { //easy, only one element in target => chose element 0
			fReaction = fNbOfLevels;
		} else {
			// shoot elastic Rutherford channel
			double tmp = CLHEP::RandFlat::shoot(fScatteringProbabilitySingle[fNbOfLevels - 1],
					fScatteringProbabilitySingle[fNbOfLevels + fTargetMaterial->NumberOfElements() - 1]);

			for(fReaction = fNbOfLevels; tmp > fScatteringProbabilitySingle[fReaction]; fReaction++) {
				//nothing else, after this loop reaction is the reaction channel to be used (from 0 to NumberOfLevel-1 or NumberOfLevel+NumberOfElements-1)
			}
		}

		fExcitationEnergy = 0.;
	}
}

void TRexAngularDistribution::ShootEjectileAndRecoilDirections() {
	//fThetaCM = 70. * degree;

	// particle momentum direction
	fEjectilePhi = CLHEP::RandFlat::shoot(-M_PI, M_PI) * rad;
	//fEjectilePhi = 80.0 * degree;
	fRecoilPhi = -fEjectilePhi;

	//std::cout << "fReaction = " << fReaction << ": projectile = " << fProjectile.A() << " , target = " << fTarget.A()
	//		<< " , ejectile = " << fEjectile.A() << " , recoil = " << fRecoil.A() << std::endl;

	// set ejectile energy and thetaLab
	fKinematics->orbits(&fProjectile, &fTarget, &fRecoil, &fEjectile, fReactionEnergy / MeV, fThetaCM / degree, fExcitationEnergy / MeV,
			0, fEjectileEnergy, fEjectileTheta);

	fEjectileEnergy *= MeV;
	fEjectileTheta *= radian;

	// set recoil energy and thetaLab
	fKinematics->orbits(&fProjectile, &fTarget, &fRecoil, &fEjectile, fReactionEnergy / MeV, fThetaCM / degree, fExcitationEnergy / MeV,
			1, fRecoilEnergy, fRecoilTheta);

	fRecoilEnergy *= MeV;
	fRecoilTheta *= radian;

	//G4std::cout << "fReactionEnergy = " << fReactionEnergy << std::endl;
	//G4std::cout << "fThetaCM  = " << fThetaCM << std::endl;
	//G4std::cout << "fEjectileTheta  = " << fEjectileTheta << std::endl;
	//G4std::cout << "fRecoilTheta  = " << fRecoilTheta << std::endl;

	// set ejectile Lorentz vector
	G4ThreeVector ejectileMomentumVectorLab;
	ejectileMomentumVectorLab.setRThetaPhi(fKinematics->Momentum(fEjectileEnergy, fEjectileRestMass), fEjectileTheta, fEjectilePhi);

	fEjectileLab.setE(fEjectileRestMass + fEjectileEnergy);
	fEjectileLab.setVect(ejectileMomentumVectorLab);

	// set recoil Lorentz vector
	G4ThreeVector recoilMomentumVectorLab;
	recoilMomentumVectorLab.setRThetaPhi(fKinematics->Momentum(fRecoilEnergy, fRecoilRestMass), fRecoilTheta, fRecoilPhi);

	fRecoilLab.setE(fRecoilRestMass + fRecoilEnergy);
	fRecoilLab.setVect(recoilMomentumVectorLab);


	// set ejectile Lorentz vector after target if gammas are simulated (needed for the calculation of the Doppler shift)
	if(TRexSettings::Get()->SimulateGammas()) {
		// travel length of the ejectile through the target
		G4double travelLength;

		if(fEjectileTheta / degree < 90*degree) {
			travelLength = 1. / fabs(cos(fEjectileTheta)) *
				(TRexSettings::Get()->GetTargetThickness() - (fReactionZ * TRexSettings::Get()->GetTargetMaterialDensity() + TRexSettings::Get()->GetTargetThickness() / 2.));
		} else {
			travelLength = 1. / fabs(cos(fEjectileTheta)) *
				(fReactionZ * TRexSettings::Get()->GetTargetMaterialDensity() + TRexSettings::Get()->GetTargetThickness() / 2.);
		}

		// energy loss of the ejectile in the target
		Kinematic targetreco(&fEjectile, fTargetMaterial, travelLength / (mg/cm2));
		G4double energyAfterTarget = fEjectileEnergy - targetreco.EnergyLoss(fEjectileEnergy / MeV) * MeV;

		//std::cout << "energyMiddle = " << fEjectileEnergy << " , energyLoss = " << targetreco.EnergyLoss(fEjectileEnergy / MeV) << " , energy after = " << energyAfterTarget << std::endl;

		ejectileMomentumVectorLab.setRThetaPhi(fKinematics->Momentum(energyAfterTarget, fEjectileRestMass), fEjectileTheta, fEjectilePhi);
		fEjectileLabAfterTarget.setE(fEjectileRestMass + energyAfterTarget);
		fEjectileLabAfterTarget.setVect(ejectileMomentumVectorLab);
	}
}


void TRexAngularDistribution::ShootGamma() {
	// clear old event
	fGammaLab->clear();

	G4LorentzVector boostedGamma;

	if(fNbOfDecays[fReaction] > 0) {

		GenerateDecay(fReaction);
        //GenerateDecay();

		for(int i = 0; i < GetNbOfGammas(); i++) {
			// gamma in the CM frame
			boostedGamma.set(GetGammaEnergy(i), GetGammaDirection(i));

			// boot CM frame to the lab frame (assumption: gamma is emitted in the middle of the target!)
			//boostedGamma.boost(fEjectileLab.vect(), fEjectileLab.beta());

			// boot CM frame to the lab frame (assumption: gamma is emitted after the target!)
			boostedGamma.boost(fEjectileLabAfterTarget.vect(), fEjectileLabAfterTarget.beta());

			//G4std::cout << "fEjectileLab.beta() = " << fEjectileLab.beta() << " , fEjectileLabAfterTarget.beta() = " << fEjectileLabAfterTarget.beta() << std::endl;

			//std::cout << "fReaction = " << fReaction << " , EGamCM = " << GetGammaEnergy(i) << " , EGamLab = " << boostedGamma.e() << std::endl;

			fGammaLab->push_back(boostedGamma);
		}
	}
}

void TRexAngularDistribution::FillAngularDistributionGraphs() {
	std::ifstream file(TRexSettings::Get()->GetAngularDistributionFile().c_str());

	if(file.bad()) {
		std::cerr << "Unable to open " << TRexSettings::Get()->GetAngularDistributionFile() << "!\nexiting ... \n";
		exit(2);
	} else {
		std::cout << "\nReading angular distribution file " << TRexSettings::Get()->GetAngularDistributionFile() << " ... \n"<< std::endl;
	}


	// number of theta angles = number of lines
	int nbOfThetaAngles;

	for(size_t i = 0; i < fNbOfLevels; i++) {
		file >> nbOfThetaAngles;
	}
	//std::cout << "nfOfThetaAngles = " << nbOfThetaAngles << std::endl;

	std::vector<TVectorF> theta    = std::vector<TVectorF>(fNbOfLevels, TVectorF(nbOfThetaAngles));
	std::vector<TVectorF> sigma    = std::vector<TVectorF>(fNbOfLevels, TVectorF(nbOfThetaAngles));
	std::vector<TVectorF> thetaSin = std::vector<TVectorF>(fNbOfLevels, TVectorF(nbOfThetaAngles));
	std::vector<TVectorF> sigmaSin = std::vector<TVectorF>(fNbOfLevels, TVectorF(nbOfThetaAngles));

	// loop over all lines
	for(int th = 0; th < nbOfThetaAngles; th++) {
		// loop over all states
		for(size_t i = 0; i < fNbOfLevels; i++) {
			file >> theta[i][th] >> sigma[i][th];
			//std::cout << theta[i][th] << " " << sigma[i][th] << std::endl;
			thetaSin[i][th] = theta[i][th] / 180 * TMath::Pi();
			sigmaSin[i][th] = sigma[i][th] * sin(thetaSin[i][th]);
			//std::cout << thetaSin[i][th] << " " << sigmaSin[i][th] << std::endl;
		}
	}

	// loop over all states
	for(size_t i = 0; i < fNbOfLevels; i++) {
		//fGraphs.push_back(TGraph(theta[i], sigma[i]));
		fGraphsSin.push_back(TGraph(thetaSin[i], sigmaSin[i]));
	}

	file.close();

	//		TFile testFile("angDist.root", "recreate");
	//		testFile.cd();
	//
	//		for(int i = 0; i < fNbOfLevels; i++) {
	//			//fGraphs[i].SetName(Form("Graph_%i", i));
	//			//fGraphs[i].Write();
	//		}
}

void TRexAngularDistribution::FillAngularDistributionHistos() {
	// loop over all levels
	for(size_t i = 0; i < fNbOfLevels; i++) {
		// binning of the histogram
		int nbOfBins = fGraphsSin[i].GetN() * 100;

		double thetaMin, sigmaMin;
		fGraphsSin[i].GetPoint(0, thetaMin, sigmaMin);

		double thetaMax, sigmaMax;
		fGraphsSin[i].GetPoint(fGraphsSin[i].GetN()-1, thetaMax, sigmaMax);

		double binWidth = (thetaMax - thetaMin) / nbOfBins;

		// create angular distribution histogram
		fHistos.push_back(TH1F(Form("AngularDistributionHisto_%d", (int) i), Form("AngularDistributionHisto_%d", (int) i),
					nbOfBins + 1, thetaMin - binWidth/2., thetaMax + binWidth/2.));

		double sigma;

		// loop over all theta angles and fill the histogram
		for(double theta = thetaMin; theta < thetaMax + binWidth; theta += binWidth) {
			sigma = fGraphsSin[i].Eval(theta);

			if(theta >  fThetaCM_min / rad) {
				// fill histogram
				fHistos[i].Fill(theta, sigma);
			}
		}
	}

	//		TFile testFile("angDistHisto.root", "recreate");
	//		testFile.cd();
	//
	//		for(size_t i = 0; i < fNbOfLevels; i++) {
	//			fHistos[i].Write();
	//		}
}

void TRexAngularDistribution::CalculateArealDensity() {
	if(fTargetMaterial->NumberOfElements() == 1) {
		fArealDensity.push_back(TRexSettings::Get()->GetTargetThickness() * Avogadro / (fTargetMaterial->GetElement(0)->A() * g/mole));
	} else {
		double atomicRatio[2] = {1.0, TRexSettings::Get()->GetTargetAtomicRatio()};

		for(size_t i = 0; i < fTargetMaterial->NumberOfElements(); ++i) {
			fArealDensity.push_back(atomicRatio[i] * TRexSettings::Get()->GetTargetThickness() * Avogadro /
					(fTargetMaterial->GetElement(0)->A() * g/mole + TRexSettings::Get()->GetTargetAtomicRatio() * fTargetMaterial->GetElement(1)->A() * g/mole));
		}
	}

	for(size_t i = 0; i < fTargetMaterial->NumberOfElements(); ++i) {
		std::cout << "Areal density[" << i << "] = " << fArealDensity[i] *cm2 << " / cm2" << std::endl;
	}
}

void TRexAngularDistribution::CalculateCrossSectionIntegral() {
	int firstPoint = 0;

	for(unsigned int i = 0; i < fGraphsSin.size(); i++) {
		firstPoint = 0;

		while(fGraphsSin[i].GetX()[firstPoint] < fThetaCM_min / rad - 0.00001) {
			firstPoint ++;
		}

		std::cout << "first Point = " << fGraphsSin[i].GetX()[firstPoint] << " , fThetaCM_min = " << fThetaCM_min / rad << std::endl;

		fCrossSectionIntegral.push_back(fGraphsSin[i].Integral(firstPoint, -1) * millibarn);
		std::cout << "fCrossSectionIntegral[" << i << "] = " << fCrossSectionIntegral[i] / millibarn << std::endl;
	}

	// elastic scattering (using Rutherford scattering)
	for(size_t i = 0; i < fTargetMaterial->NumberOfElements(); ++i) {
		// Rutherford factor
		G4double RF = fProjectileZ * fTargetMaterial->Z(i) * eplus * eplus / (16. * M_PI * epsilon0);
		RF *= RF;

		G4double fBeamEnergyMiddleTarget = fEnergyVsTargetDepth.Eval(TRexSettings::Get()->GetTargetThickness() / 2. /(mg/cm2))*MeV;

		//std::cout << "fBeamEnergyMiddleTarget = " << fBeamEnergyMiddleTarget / MeV << std::endl;

		// total energy in the CM frame in the middle of the target
		G4double E_CM = fBeamEnergyMiddleTarget * fTargetMaterial->Mass(i) / (fProjectileRestMass + fTargetMaterial->Mass(i));

		//std::cout << "Ecm = " << E_CM / MeV << std::endl;

		fCrossSectionIntegral.push_back(-4. * M_PI * RF / (E_CM * E_CM) * (1. - 1./ (sin(fThetaCM_min / radian *0.5) * sin(fThetaCM_min / radian * 0.5))));

		std::cout << "elastic: fCrossSectionIntegral[" << i << "] = " << fCrossSectionIntegral[i + fGraphsSin.size()] / millibarn << std::endl;
	}
}

void TRexAngularDistribution::CalculateScatteringProbability() {
	fScatteringProbabilitySingle.push_back(fCrossSectionIntegral[0] * fArealDensity[fTargetMaterial->NumberOfElements()-1]);

	//	bool Transfer = true;
	//	int index;
	//
	//	if(Transfer) {
	//		for(index = 1; index < fNbOfLevels + targetMaterial.NumberOfElements();index++) {
	//			// transfer cross sections
	//			if(index < fNbOfLevels) {
	//				ScatteringProbability[index] = ScatteringProbability[index-1] +  fArealDensity[targetMaterial.NumberOfElements()-1] * fCrossSectionIntegral[index];
	//
	//				std::cout << "index = " << index << " , fArealDensity = " << fArealDensity[targetMaterial.NumberOfElements()-1] * cm2  << " , fCrossSectionIntegral = " << fCrossSectionIntegral[index] / millibarn << std::endl;
	//			}
	//			else{ // elastic cross sections
	//				ScatteringProbability[index] = ScatteringProbability[index-1] +  fArealDensity[index - fNbOfLevels] * fCrossSectionIntegral[index];
	//
	//				std::cout << "index = " << index << " , fArealDensity = " << fArealDensity[index - fNbOfLevels] * cm2 << " , fCrossSectionIntegral = " << fCrossSectionIntegral[index] / millibarn << std::endl;
	//			}
	//			std::cout << "ScatteringProbability(transfer)[" << index << "] = " << ScatteringProbability[index] << std::endl;
	//		}
	//	}
	//	else{ // Coulex
	//
	//		ScatteringProbability[fNbOfLevels] = fArealDensity[targetMaterial.NumberOfElements()-1] * fCrossSectionIntegral[0];
	//
	//		for(index = 1; index < fNbOfLevels; index++) {
	//			ScatteringProbability[index] = ScatteringProbability[index-1] + fArealDensity[targetMaterial.NumberOfElements()-1] * fCrossSectionIntegral[index];
	//			ScatteringProbability[fNbOfLevels] += fArealDensity[targetMaterial.NumberOfElements()-1] * fCrossSectionIntegral[index];
	//
	//			std::cout << "ScatteringProbability(Coulex)[" << index << "] = " << ScatteringProbability[index] << std::endl;
	//		}
	//		std::cout << "ScatteringProbability(Coulex)[" << fNbOfLevels << "] = " << ScatteringProbability[fNbOfLevels] << std::endl;
	//	}


	for(size_t index = 1; index < fNbOfLevels + fTargetMaterial->NumberOfElements(); ++index) {
		// transfer or Coulex cross sections
		if(index < fNbOfLevels) {
			fScatteringProbabilitySingle.push_back(fScatteringProbabilitySingle[index-1] +
					fArealDensity[fTargetMaterial->NumberOfElements()-1] * fCrossSectionIntegral[index]);

			std::cout << "index = " << index << " , fArealDensity = " << fArealDensity[fTargetMaterial->NumberOfElements()-1] * cm2
				<< " , fCrossSectionIntegral = " << fCrossSectionIntegral[index] / millibarn << std::endl;
		} else { // elastic Rutherford cross sections
			fScatteringProbabilitySingle.push_back(fScatteringProbabilitySingle[index-1] +  fArealDensity[index - fNbOfLevels] * fCrossSectionIntegral[index]);

			std::cout << "index = " << index << " , fArealDensity = " << fArealDensity[index - fNbOfLevels] * cm2 << " , fCrossSectionIntegral = " << fCrossSectionIntegral[index] / millibarn << std::endl;
		}
		std::cout << "ScatteringProbability(transfer)[" << index << "] = " << fScatteringProbabilitySingle[index] << std::endl;
	}

	// set total scattering probability
	fScatteringProbability = fScatteringProbabilitySingle[fNbOfLevels - 1] * TRexSettings::Get()->GetTransferOrCoulexProbability() +
		fScatteringProbabilitySingle[fNbOfLevels + fTargetMaterial->NumberOfElements() - 1] * (1 - TRexSettings::Get()->GetTransferOrCoulexProbability());

	if(fThetaCM < 0.00001 * degree) {
		fScatteringProbability = fScatteringProbabilitySingle[fNbOfLevels - 1] * TRexSettings::Get()->GetTransferOrCoulexProbability();
	}
	//std::cout << "ScatteringProbabilityTree = " << fScatteringProbability << " = ? "<< fScatteringProbabilitySingle[fNbOfLevels - 1] * TRexSettings::Get()->GetTransferOrCoulexProbability() << std::endl;
}


void TRexAngularDistribution::ReadLevelFile() {
	std::ifstream file(TRexSettings::Get()->GetLevelFile().c_str());

	if(file.bad()) {
		std::cerr << "Unable to open " << TRexSettings::Get()->GetLevelFile() << "!\nexiting ... \n";
		exit(2);
	} else {
		std::cout << "\nReading level file " << TRexSettings::Get()->GetLevelFile() << " ... \n"<< std::endl;
	}

	// ignore the first 3 lines as they are only comments
	file.ignore(1000, '\n');
	file.ignore(1000, '\n');
	file.ignore(1000, '\n');

	// read the total number of levels
	file >> fNbOfLevels;

	std::cout << "NbOfLevels = " << fNbOfLevels << std::endl;

	// resize the vectors
	fLevelID.resize(fNbOfLevels);
	fLevelEnergy.resize(fNbOfLevels);
	fFeedingProbability.resize(fNbOfLevels);
	fLevelSpin.resize(fNbOfLevels);
	fLevelParity.resize(fNbOfLevels);
	fNbOfDecays.resize(fNbOfLevels);
	fDecayLevel.resize(fNbOfLevels);
	fDecayProbability.resize(fNbOfLevels);
	fDecayType.resize(fNbOfLevels);
	fDecayDelta.resize(fNbOfLevels);

	// ignore the next comment line
	//file.ignore(1000, '\n');

	double totalFeedingProbability = 0.;

	for(size_t i = 0; i < fNbOfLevels; i++) {
		fLevelID[i] = i;

		file >> fLevelEnergy[i] >> fFeedingProbability[i] >> fLevelSpin[i] >> fLevelParity[i] >> fNbOfDecays[i];

		fLevelEnergy[i] *= keV;
		totalFeedingProbability += fFeedingProbability[i];

		std::cout << "E[" << i << "] = " << fLevelEnergy[i] / keV << " , feeding Prob = " << fFeedingProbability[i] << " , spin = " << fLevelSpin[i]
			<< " , parity = " << fLevelParity[i] << " , nbOfDecays = " << fNbOfDecays[i] << std::endl;

		for(int ii = 0; ii < fNbOfDecays[i]; ii++) {
			fDecayLevel[i].resize(fNbOfDecays[i]);
			fDecayProbability[i].resize(fNbOfDecays[i]);
			fDecayType[i].resize(fNbOfDecays[i]);
			fDecayDelta[i].resize(fNbOfDecays[i]);

			file >> fDecayLevel[i][ii] >> fDecayProbability[i][ii] >> fDecayType[i][ii] >> fDecayDelta[i][ii];
			std::cout << "\t" << ii << ": i decays in = " << fDecayLevel[i][ii] << " with prob = " << fDecayProbability[i][ii] << " , type = " << fDecayType[i][ii]
				<< " , delta = " << fDecayDelta[i][ii] << std::endl;
		}
	}

	// normalize feeding probability
	for(size_t i = 0; i < fNbOfLevels; i++) {
		fFeedingProbability[i] /= totalFeedingProbability;

		if(i > 0) {
			fFeedingProbability[i] += fFeedingProbability[i - 1];
		}
	}

	file.close();
}


void TRexAngularDistribution::FillMiniballLevels() {
	fLevelsMB.resize(fNbOfLevels);

	for(size_t i = 0; i < fNbOfLevels; i++) {
		fLevelsMB[i] = MiniBallSourceLevel(fLevelEnergy[i], fLevelSpin[i], fLevelParity[i]);

		level_structure.push_back(&fLevelsMB[i]);

		fFeedingMB.decay.push_back(i);

		fFeedingMB.prob.push_back(fFeedingProbability[i]);

		for(int ii = 0; ii < fNbOfDecays[i]; ii++) {
			std::cout << "i = " << i << " , ii = " << ii << std::endl;
			std::cout << "fDecayLevel[i][ii] = " << fDecayLevel[i][ii] << std::endl;
			std::cout << "fLevelID = " << fLevelID[fDecayLevel[i][ii]] << std::endl;
			std::cout << "prob = " << fDecayProbability[i][ii] << std::endl;
			std::cout << "type = " << fDecayType[i][ii] << std::endl;
			std::cout << "delta = " << fDecayDelta[i][ii] << std::endl;
			fLevelsMB[i].AddDecay(fLevelID[fDecayLevel[i][ii]], fDecayProbability[i][ii], fDecayType[i][ii], fDecayDelta[i][ii]);
		}
	}
}
