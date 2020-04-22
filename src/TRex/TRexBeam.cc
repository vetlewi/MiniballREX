/*
 * TRexBeam.cc
 *
 *  Created on: Jun 16, 2014
 *      Author: sklupp
 */

#include "TRex/TRexBeam.hh"
#include "TRex/TRexSettings.hh"

#include <G4ParticleGun.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleTable.hh>
#include <G4IonTable.hh>

TRexBeam::TRexBeam() :
	fGammaTheta(new std::vector<G4double>(0)), fGammaPhi(new std::vector<G4double>(0)), fGammaEnergy(new std::vector<G4double>(0)),
	fGammaLab(new std::vector<G4LorentzVector>(0)) {
	// define guns
	fParticleGunEjectile = new G4ParticleGun(1);
	fParticleGunRecoil = new G4ParticleGun(1);
	fParticleGunGamma = new G4ParticleGun(1);

	fBeamEnergy = TRexSettings::Get()->GetBeamEnergy();
	fBeamWidth = TRexSettings::Get()->GetBeamWidth();
	fReactionEnergy = 0.;

	// define nuclei
	DefineNuclei();

	// define reaction kinematics and energy loss calculations
	fTargetMaterial = GetTargetMaterial();
	std::cout << "TargetMaterialName for energy loss calculation in the target = " << fTargetMaterial->Name() << std::endl;
	fKinematics = new Kinematic(&fProjectile, fTargetMaterial, TRexSettings::Get()->GetTargetThickness()/(mg/cm2));

	// energy loss in the target
	fEnergyVsTargetDepth = *(fKinematics->EnergyVsThickness(fBeamEnergy / MeV, TRexSettings::Get()->GetTargetThickness() / 1000 / (mg/cm2)));

	//	TFile bla("bla.root", "recreate");
	//	bla.cd();
	//	fEnergyVsTargetDepth.Write();
	//	bla.Close();

	// set minimal thetaCM
	fThetaCM_min = TRexSettings::Get()->GetThetaCmMin();
}

TRexBeam::~TRexBeam() {
	// TODO Auto-generated destructor stub
}

void TRexBeam::ShootReactionPosition() {
	//select random x and y position on a disk with diameter beamWidth
	do {
		fReactionX = CLHEP::RandFlat::shoot(-fBeamWidth / 2., fBeamWidth / 2.) * mm;
		fReactionY = CLHEP::RandFlat::shoot(-fBeamWidth / 2., fBeamWidth / 2.) * mm;
	} while(sqrt(pow(fReactionX,2)+pow(fReactionY,2)) > fBeamWidth / 2.);

	// choose z according to a flat distribution in the target
	//fReactionZ = CLHEP::RandFlat::shoot(-TRexSettings::Get()->GetTargetThickness() / (2. * TRexSettings::Get()->GetTargetMaterialDensity()) / um,
	//			     TRexSettings::Get()->GetTargetThickness() / (2. * TRexSettings::Get()->GetTargetMaterialDensity()) / um) * um;
	//fReactionZ = CLHEP::RandFlat::shoot(-0.5, 0.5) * mm;
	fReactionZ = CLHEP::RandFlat::shoot(-TRexSettings::Get()->GetTargetPhysicalLength()/(2*um), TRexSettings::Get()->GetTargetPhysicalLength()/(2*um))*um;
}

void TRexBeam::DefineNuclei() {
	fProjectileZ = TRexSettings::Get()->GetProjectileZ();
	fProjectileA = TRexSettings::Get()->GetProjectileA();
	fTargetZ = TRexSettings::Get()->GetTargetZ();
	fTargetA = TRexSettings::Get()->GetTargetA();
	fEjectileZ = TRexSettings::Get()->GetEjectileZ();
	fEjectileA = TRexSettings::Get()->GetEjectileA();
	fRecoilZ = TRexSettings::Get()->GetRecoilZ();
	fRecoilA = TRexSettings::Get()->GetRecoilA();

	// masses
	fProjectileRestMass = ParticleDefinition(fProjectileZ, fProjectileA - fProjectileZ, 0)->GetPDGMass();
	fTargetRestMass = ParticleDefinition(fTargetZ, fTargetA - fTargetZ, 0)->GetPDGMass();
	fEjectileRestMass = ParticleDefinition(fEjectileZ, fEjectileA - fEjectileZ, 0)->GetPDGMass();
	fRecoilRestMass = ParticleDefinition(fRecoilZ, fRecoilA - fRecoilZ, 0)->GetPDGMass();

	// define isotopes
	std::cout<<"Reading isotopes from '"<<TRexSettings::Get()->GetMassFile()<<"' ... ";
	fIsotopeTable = new Isotopes(TRexSettings::Get()->GetMassFile().c_str());
	if(fIsotopeTable->NumberOfIsotopes() == 0) {
		std::cout<<"failed to read mass file!"<<std::endl;
		exit(1);
	}
	std::cout<<"read "<<fIsotopeTable->NumberOfIsotopes()<<" isotopes"<<std::endl;

	fProjectile = *(fIsotopeTable->Search((char*)TRexSettings::Get()->GetProjectileName().c_str()));
	fTarget = *(fIsotopeTable->Search((char*)TRexSettings::Get()->GetTargetName().c_str()));
	//fTarget = *(IsotopeTable->Search(fTargetZ, fTargetA - fTargetZ));
	fEjectile = *(fIsotopeTable->Search((char*)TRexSettings::Get()->GetEjectileName().c_str()));
	fRecoil = *(fIsotopeTable->Search((char*)TRexSettings::Get()->GetRecoilName().c_str()));

	std::cout << "Shooting the projectile " << fProjectile.A() << fProjectile.Name() << " with (Z,A) = (" << fProjectileZ << "," <<  fProjectileA
		<< ") on the target " << fTarget.A() << fTarget.Name() << " with (Z,A) = (" << fTargetZ << "," << fTargetA << ") => ejectile "
		<< fEjectile.A() << fEjectile.Name() << " with (Z,A) = (" << fEjectileZ << "," << fEjectileA  << ") with recoil "
		<< fRecoil.A() << fRecoil.Name() << " with (Z,A) = (" << fRecoilZ << "," << fRecoilA << ")." << std::endl;

	// check settings
	if(fProjectile.Z() != fProjectileZ || fProjectile.A() != fProjectileA ||
			fTarget.Z() != fTargetZ || fTarget.A() != fTargetA ||
			fEjectile.Z() != fEjectileZ || fEjectile.A() != fEjectileA ||
			fRecoil.Z() != fRecoilZ || fRecoil.A() != fRecoilA) {
		std::cerr << "Given particle names do not match to the given charge and mass numbers!" << std::endl;
		exit(1);
	}
}

Material* TRexBeam::GetTargetMaterial() {
	Material* TargetMaterial;

	//PE and MY are implemented as materials, everything else should be the name of the element
	if(((G4String)TRexSettings::Get()->GetTargetMaterialName()).contains("PE") || ((G4String)TRexSettings::Get()->GetTargetMaterialName()).contains("MY")) {
		TargetMaterial = new Material((char*)TRexSettings::Get()->GetTargetMaterialName().c_str());
	} else {
		//if target material name is the same as the name of the scattering target build set the material to only this element
		if(TRexSettings::Get()->GetTargetMaterialName() == TRexSettings::Get()->GetTargetName() || TRexSettings::Get()->GetTargetMaterialName() == "dummy" ||
				TRexSettings::Get()->GetTargetMaterialName() == "SolidDeuterium") {        
			TargetMaterial = new Material((char*)TRexSettings::Get()->GetTargetName().c_str(),false);
		} else {
			std::cout<<"'"<<TRexSettings::Get()->GetTargetMaterialName()<<"' != '"<<TRexSettings::Get()->GetTargetName()<<"'"<<std::endl;
			char* ElementNames[] = {(char*)TRexSettings::Get()->GetTargetMaterialName().c_str(), (char*)TRexSettings::Get()->GetTargetName().c_str()};

			std::string strCarrierA = TRexSettings::Get()->GetTargetMaterialName();
			strCarrierA.erase(strCarrierA.find_first_not_of("0123456789"));
			int CarrierA = atoi(strCarrierA.c_str());

			std::string strTargetA = TRexSettings::Get()->GetTargetName();
			strTargetA.erase(strTargetA.find_first_not_of("0123456789"));
			int TargetA = atoi(strTargetA.c_str());

			G4double TargetRatio = TargetA * TRexSettings::Get()->GetTargetAtomicRatio() / (TargetA * TRexSettings::Get()->GetTargetAtomicRatio() + CarrierA);
			std::cout<<"TargetRatio = "<<TargetRatio<<" ("<<TargetA<<"*"<<TRexSettings::Get()->GetTargetAtomicRatio()<<"/("<<TargetA<<"*"<<TRexSettings::Get()->GetTargetAtomicRatio()<<"+"<<CarrierA<<"))"<<std::endl;

			double ElementRatios[] = {1-TargetRatio,TargetRatio};
			std::cout << "Element 0: " << ElementNames[0] << " with ratio " << ElementRatios[0] << std::endl;
			std::cout << "Element 1: " << ElementNames[1] << " with ratio " << ElementRatios[1] << std::endl;
			TargetMaterial = new Material(2,ElementNames,ElementRatios,false);

			//TargetMaterial = new Material((char*)TRexSettings::Get()->GetTargetMaterialName().c_str(),false);
		}
	}

	return TargetMaterial;
}


void TRexBeam::CalculateReactionEnergyInTheTarget() {
	G4double reactionPosInTarget = fReactionZ * TRexSettings::Get()->GetTargetMaterialDensity() + TRexSettings::Get()->GetTargetThickness() / 2.;

	fReactionEnergy = fEnergyVsTargetDepth.Eval(reactionPosInTarget /(mg/cm2))*MeV;

	//std::cout << "fReactionZ = " << fReactionZ << " ,x = " << reactionPosInTarget /(mg/cm2) << " , E(x) = " << fReactionEnergy / MeV << std::endl;
}

void TRexBeam::CreateTreeBranches() {
	if(!fTree) {
		std::cout << "\n\n\nTRexBeam: Tree doesn't exist!\n\n" << std::endl;
	}
	fTree->Branch("beamEnergy", &fBeamEnergy, "beamEnergy/D");
	fTree->Branch("beamWidth", &fBeamWidth, "beamWidth/D");
	fTree->Branch("reactionEnergy", &fReactionEnergy, "reactionEnergy/D");
	fTree->Branch("reactionX", &fReactionX, "reactionX/D");
	fTree->Branch("reactionY", &fReactionY, "reactionY/D");
	fTree->Branch("reactionZ", &fReactionZ, "reactionZ/D");
	fTree->Branch("thetaCM", &fThetaCM, "thetaCM/D");
	fTree->Branch("ejectileTheta", &fEjectileTheta, "ejectileTheta/D");
	fTree->Branch("recoilTheta", &fRecoilTheta, "recoilTheta/D");
	fTree->Branch("ejectilePhi", &fEjectilePhi, "ejectilePhi/D");
	fTree->Branch("recoilPhi", &fRecoilPhi, "recoilPhi/D");
	fTree->Branch("ejectileEnergy", &fEjectileEnergy, "ejectileEnergy/D");
	fTree->Branch("recoilEnergy", &fRecoilEnergy, "recoilEnergy/D");
	fTree->Branch("projectileZ", &fProjectileZ, "projectileZ/I");
	fTree->Branch("projectileA", &fProjectileA, "projectileA/I");
	fTree->Branch("targetZ", &fTargetZ, "targetZ/I");
	fTree->Branch("targetA", &fTargetA, "targetA/I");
	fTree->Branch("ejectileZ", &fEjectileZ, "ejectileZ/I");
	fTree->Branch("ejectileA", &fEjectileA, "ejectileA/I");
	fTree->Branch("recoilZ", &fRecoilZ, "recoilZ/I");
	fTree->Branch("recoilA", &fRecoilA, "recoilA/I");
	fTree->Branch("scatteringProbability", &fScatteringProbability, "scatteringProbability/D");
	fTree->Branch("reaction", &fReaction, "reaction/i");

	fTree->Branch("gammaTheta", &fGammaTheta);
	fTree->Branch("gammaPhi", &fGammaPhi);
	fTree->Branch("gammaEnergy", &fGammaEnergy);
}

G4ParticleDefinition* TRexBeam::ParticleDefinition(int Z, int N, double eex) {
	if(Z+N > 4) { // create ion from ion table
		return G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(Z, Z+N, eex);
	} else {
		if(Z == 1 && N == 0) { // proton
			return G4Proton::ProtonDefinition();
		} else if(Z == 1 && N == 1) { // deuteron
			return G4Deuteron::DeuteronDefinition();
		} else if(Z == 1 && N == 2) { // triton
			return G4Triton::TritonDefinition();
		} else if(Z == 2 && N == 1) { // 3He
			return G4He3::He3Definition();
		} else if(Z == 2 && N == 2) { // alpha
			return G4Alpha::AlphaDefinition();
		}
	}

	std::cerr << "Error in " << __PRETTY_FUNCTION__ << "shouldn't be able to reach this stage (Z = " << Z << ", N = " << N << ")" << std::endl;
	exit(1);
}

void TRexBeam::SetEjectileGun(G4Event *anEvent) {
	if(TRexSettings::Get()->SimulateEjectiles()) {
		// particle definition
		fParticleGunEjectile->SetParticleDefinition(ParticleDefinition(fEjectileZ, fEjectileA - fEjectileZ, fReactionEnergy));

		// emission point
		fParticleGunEjectile->SetParticlePosition(G4ThreeVector(fReactionX, fReactionY, fReactionZ));

		// set energy
		fParticleGunEjectile->SetParticleEnergy(fEjectileLab.e() - fEjectileRestMass);

		// direction
		fParticleGunEjectile->SetParticleMomentumDirection(fEjectileLab.vect());

		// generate primary vertex
		fParticleGunEjectile->GeneratePrimaryVertex(anEvent);
	}

	// set variables for the tree
	fEjectileTheta = fEjectileLab.theta() / radian;
	fEjectilePhi = fEjectileLab.phi() / radian;
	fEjectileEnergy = (fEjectileLab.e() - fEjectileRestMass) / keV;
}

void TRexBeam::SetRecoilGun(G4Event *anEvent) {
	// particle definition
	fParticleGunRecoil->SetParticleDefinition(ParticleDefinition(fRecoilZ, fRecoilA - fRecoilZ, 0));

	// emission point
	fParticleGunRecoil->SetParticlePosition(G4ThreeVector(fReactionX, fReactionY, fReactionZ));

	// energy
	fParticleGunRecoil->SetParticleEnergy(fRecoilLab.e() - fRecoilRestMass);

	// direction
	fParticleGunRecoil->SetParticleMomentumDirection(fRecoilLab.vect());

	// generate primary vertex
	fParticleGunRecoil->GeneratePrimaryVertex(anEvent);

	// set variables for the tree
	fRecoilTheta = fRecoilLab.theta() / radian;
	fRecoilPhi = fRecoilLab.phi() / radian;
	fRecoilEnergy = (fRecoilLab.e() - fRecoilRestMass) / keV;
}

void TRexBeam::SetGammaGun(G4Event *anEvent) {
	// clear old event
	fGammaTheta->resize(0);
	fGammaPhi->resize(0);
	fGammaEnergy->resize(0);

	// loop over all gammas
	for(unsigned int i = 0; i < fGammaLab->size(); i++) {
		// particle definition
		fParticleGunGamma->SetParticleDefinition(G4Gamma::GammaDefinition());

		// emission point
		fParticleGunGamma->SetParticlePosition(G4ThreeVector(fReactionX, fReactionY, fReactionZ));

		// energy
		fParticleGunGamma->SetParticleEnergy((*fGammaLab)[i].e());

		// direction
		fParticleGunGamma->SetParticleMomentumDirection((*fGammaLab)[i].vect());

		// generate primary vertex
		fParticleGunGamma->GeneratePrimaryVertex(anEvent);

		// set variables for the tree
		fGammaTheta->push_back((*fGammaLab)[i].theta() / radian);
		fGammaPhi->push_back((*fGammaLab)[i].phi() / radian);
		fGammaEnergy->push_back((*fGammaLab)[i].e() / keV);

		//std::cout << "fGammaEnergy[" << i << "] = " << (*fGammaEnergy)[i] << std::endl;
	}
}
