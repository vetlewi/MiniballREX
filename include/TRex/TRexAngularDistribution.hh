/*
 * TRexAngularDistribution.hh
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */


#ifndef TREXANGULARDISTRIBUTION_HH_
#define TREXANGULARDISTRIBUTION_HH_

#include "TRex/TRexBeam.hh"

#include <Miniball/MBglobals.hh>
#include <Miniball/MiniBallSource.hh>

#include <G4ParticleGun.hh>
#include <Randomize.hh>

#include <TH1F.h>
#include <TGraph.h>
#include <TMath.h>
#include <TVectorF.h>

#include <vector>

class TRexAngularDistribution : public TRexBeam, public MiniBallSource {
	public:
		TRexAngularDistribution();
		virtual ~TRexAngularDistribution();

		void GeneratePrimaries(G4Event *anEvent) override;

	private:
		void ShootEjectileAndRecoilDirections();
		void ShootGamma();
		void CalculateArealDensity();
		void CalculateCrossSectionIntegral();
		void CalculateScatteringProbability();

		void ReadLevelFile();
		void FillMiniballLevels();
		void FillAngularDistributionGraphs();
		void FillAngularDistributionHistos();
		void SetEjectileAndRecoil();
		void ShootThetaCm(int levelNb);
		void ShootReactionTypeAndExcitationEnergy();


		size_t fNbOfLevels;
		std::vector<G4double> fLevelEnergy;
		std::vector<double> fFeedingProbability;
		std::vector<int> fNbOfDecays;
		std::vector<double> fLevelSpin;
		std::vector<int> fLevelParity;
		std::vector<int> fLevelID;
		std::vector<std::vector<int> > fDecayLevel;
		std::vector<std::vector<double> > fDecayProbability;
		std::vector<std::vector<int> > fDecayType;
		std::vector<std::vector<double> > fDecayDelta;
		//std::vector<std::vector<MiniBallSourceLevel> > fLevelsMB;
		std::vector<MiniBallSourceLevel> fLevelsMB;
		MiniBallSourceLevel fFeedingMB;

		G4double fExcitationEnergy;

		//std::vector<TGraph> fGraphs;
		std::vector<TGraph> fGraphsSin;
		std::vector<TH1F> fHistos;

		std::vector<G4double> fArealDensity;
		std::vector<G4double> fCrossSectionIntegral;
		std::vector<G4double> fScatteringProbabilitySingle;
};

#endif /* TREXANGULARDISTRIBUTION_HH_ */
