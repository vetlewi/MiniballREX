//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 30 12:45:23 2020 by ROOT version 6.20/04
// from TTree treeDet/Detector tree
// found on file: /Volumes/RootTrees/result/Eg_100/Eg100.root
//////////////////////////////////////////////////////////

#ifndef AnalyseLaBr_h
#define AnalyseLaBr_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <TRex/ParticleMC.hh>
#include <TRex/Germanium.hh>

class AnalyseLaBr {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxFCDMC = 1;
   static constexpr Int_t kMaxBBarrelDeltaEMC = 1;
   static constexpr Int_t kMaxBBarrelErestMC = 2;
   static constexpr Int_t kMaxMiniball = 3;

   // Declaration of leaf types
   Int_t           FCDMC_;
   UInt_t          FCDMC_fUniqueID[kMaxFCDMC];   //[FCDMC_]
   UInt_t          FCDMC_fBits[kMaxFCDMC];   //[FCDMC_]
   Int_t           FCDMC_fID[kMaxFCDMC];   //[FCDMC_]
   vector<int>     FCDMC_fStripNr[kMaxFCDMC];
   vector<double>  FCDMC_fStripEnergy[kMaxFCDMC];
   vector<int>     FCDMC_fStripA[kMaxFCDMC];
   vector<int>     FCDMC_fStripZ[kMaxFCDMC];
   vector<int>     FCDMC_fStripTrackID[kMaxFCDMC];
   vector<double>  FCDMC_fStripTime[kMaxFCDMC];
   vector<int>     FCDMC_fStripStopped[kMaxFCDMC];
   vector<int>     FCDMC_fRingNr[kMaxFCDMC];
   vector<double>  FCDMC_fRingEnergy[kMaxFCDMC];
   vector<int>     FCDMC_fRingA[kMaxFCDMC];
   vector<int>     FCDMC_fRingZ[kMaxFCDMC];
   vector<int>     FCDMC_fRingTrackID[kMaxFCDMC];
   vector<double>  FCDMC_fRingTime[kMaxFCDMC];
   vector<int>     FCDMC_fRingStopped[kMaxFCDMC];
   Int_t           FCDMC_fA[kMaxFCDMC];   //[FCDMC_]
   Int_t           FCDMC_fZ[kMaxFCDMC];   //[FCDMC_]
   Int_t           FCDMC_fTrackID[kMaxFCDMC];   //[FCDMC_]
   Double_t        FCDMC_fTime[kMaxFCDMC];   //[FCDMC_]
   Int_t           FCDMC_fStopped[kMaxFCDMC];   //[FCDMC_]
   Double_t        FCDMC_fResKinEnergy[kMaxFCDMC];   //[FCDMC_]
   Int_t           FCDMC_fMult[kMaxFCDMC];   //[FCDMC_]
   Double_t        FCDMC_fRear[kMaxFCDMC];   //[FCDMC_]
   Double_t        FCDMC_fEdet[kMaxFCDMC];   //[FCDMC_]
   Int_t           BBarrelDeltaEMC_;
   UInt_t          BBarrelDeltaEMC_fUniqueID[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   UInt_t          BBarrelDeltaEMC_fBits[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelDeltaEMC_fID[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   vector<int>     BBarrelDeltaEMC_fStripNr[kMaxBBarrelDeltaEMC];
   vector<double>  BBarrelDeltaEMC_fStripEnergy[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fStripA[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fStripZ[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fStripTrackID[kMaxBBarrelDeltaEMC];
   vector<double>  BBarrelDeltaEMC_fStripTime[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fStripStopped[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fRingNr[kMaxBBarrelDeltaEMC];
   vector<double>  BBarrelDeltaEMC_fRingEnergy[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fRingA[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fRingZ[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fRingTrackID[kMaxBBarrelDeltaEMC];
   vector<double>  BBarrelDeltaEMC_fRingTime[kMaxBBarrelDeltaEMC];
   vector<int>     BBarrelDeltaEMC_fRingStopped[kMaxBBarrelDeltaEMC];
   Int_t           BBarrelDeltaEMC_fA[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelDeltaEMC_fZ[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelDeltaEMC_fTrackID[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Double_t        BBarrelDeltaEMC_fTime[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelDeltaEMC_fStopped[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Double_t        BBarrelDeltaEMC_fResKinEnergy[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelDeltaEMC_fMult[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Double_t        BBarrelDeltaEMC_fRear[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Double_t        BBarrelDeltaEMC_fEdet[kMaxBBarrelDeltaEMC];   //[BBarrelDeltaEMC_]
   Int_t           BBarrelErestMC_;
   UInt_t          BBarrelErestMC_fUniqueID[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   UInt_t          BBarrelErestMC_fBits[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           BBarrelErestMC_fID[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   vector<int>     BBarrelErestMC_fStripNr[kMaxBBarrelErestMC];
   vector<double>  BBarrelErestMC_fStripEnergy[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fStripA[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fStripZ[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fStripTrackID[kMaxBBarrelErestMC];
   vector<double>  BBarrelErestMC_fStripTime[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fStripStopped[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fRingNr[kMaxBBarrelErestMC];
   vector<double>  BBarrelErestMC_fRingEnergy[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fRingA[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fRingZ[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fRingTrackID[kMaxBBarrelErestMC];
   vector<double>  BBarrelErestMC_fRingTime[kMaxBBarrelErestMC];
   vector<int>     BBarrelErestMC_fRingStopped[kMaxBBarrelErestMC];
   Int_t           BBarrelErestMC_fA[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           BBarrelErestMC_fZ[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           BBarrelErestMC_fTrackID[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Double_t        BBarrelErestMC_fTime[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           BBarrelErestMC_fStopped[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Double_t        BBarrelErestMC_fResKinEnergy[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           BBarrelErestMC_fMult[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Double_t        BBarrelErestMC_fRear[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Double_t        BBarrelErestMC_fEdet[kMaxBBarrelErestMC];   //[BBarrelErestMC_]
   Int_t           Miniball_;
   UInt_t          Miniball_fUniqueID[kMaxMiniball];   //[Miniball_]
   UInt_t          Miniball_fBits[kMaxMiniball];   //[Miniball_]
   vector<Crystal> Miniball_fCrystal[kMaxMiniball];
   Int_t           Miniball_fClusterID[kMaxMiniball];   //[Miniball_]
   Int_t           Miniball_fStrange[kMaxMiniball];   //[Miniball_]

   // List of branches
   TBranch        *b_FCDMC_;   //!
   TBranch        *b_FCDMC_fUniqueID;   //!
   TBranch        *b_FCDMC_fBits;   //!
   TBranch        *b_FCDMC_fID;   //!
   TBranch        *b_FCDMC_fStripNr;   //!
   TBranch        *b_FCDMC_fStripEnergy;   //!
   TBranch        *b_FCDMC_fStripA;   //!
   TBranch        *b_FCDMC_fStripZ;   //!
   TBranch        *b_FCDMC_fStripTrackID;   //!
   TBranch        *b_FCDMC_fStripTime;   //!
   TBranch        *b_FCDMC_fStripStopped;   //!
   TBranch        *b_FCDMC_fRingNr;   //!
   TBranch        *b_FCDMC_fRingEnergy;   //!
   TBranch        *b_FCDMC_fRingA;   //!
   TBranch        *b_FCDMC_fRingZ;   //!
   TBranch        *b_FCDMC_fRingTrackID;   //!
   TBranch        *b_FCDMC_fRingTime;   //!
   TBranch        *b_FCDMC_fRingStopped;   //!
   TBranch        *b_FCDMC_fA;   //!
   TBranch        *b_FCDMC_fZ;   //!
   TBranch        *b_FCDMC_fTrackID;   //!
   TBranch        *b_FCDMC_fTime;   //!
   TBranch        *b_FCDMC_fStopped;   //!
   TBranch        *b_FCDMC_fResKinEnergy;   //!
   TBranch        *b_FCDMC_fMult;   //!
   TBranch        *b_FCDMC_fRear;   //!
   TBranch        *b_FCDMC_fEdet;   //!
   TBranch        *b_BBarrelDeltaEMC_;   //!
   TBranch        *b_BBarrelDeltaEMC_fUniqueID;   //!
   TBranch        *b_BBarrelDeltaEMC_fBits;   //!
   TBranch        *b_BBarrelDeltaEMC_fID;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripNr;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripEnergy;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripA;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripZ;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripTrackID;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripTime;   //!
   TBranch        *b_BBarrelDeltaEMC_fStripStopped;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingNr;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingEnergy;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingA;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingZ;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingTrackID;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingTime;   //!
   TBranch        *b_BBarrelDeltaEMC_fRingStopped;   //!
   TBranch        *b_BBarrelDeltaEMC_fA;   //!
   TBranch        *b_BBarrelDeltaEMC_fZ;   //!
   TBranch        *b_BBarrelDeltaEMC_fTrackID;   //!
   TBranch        *b_BBarrelDeltaEMC_fTime;   //!
   TBranch        *b_BBarrelDeltaEMC_fStopped;   //!
   TBranch        *b_BBarrelDeltaEMC_fResKinEnergy;   //!
   TBranch        *b_BBarrelDeltaEMC_fMult;   //!
   TBranch        *b_BBarrelDeltaEMC_fRear;   //!
   TBranch        *b_BBarrelDeltaEMC_fEdet;   //!
   TBranch        *b_BBarrelErestMC_;   //!
   TBranch        *b_BBarrelErestMC_fUniqueID;   //!
   TBranch        *b_BBarrelErestMC_fBits;   //!
   TBranch        *b_BBarrelErestMC_fID;   //!
   TBranch        *b_BBarrelErestMC_fStripNr;   //!
   TBranch        *b_BBarrelErestMC_fStripEnergy;   //!
   TBranch        *b_BBarrelErestMC_fStripA;   //!
   TBranch        *b_BBarrelErestMC_fStripZ;   //!
   TBranch        *b_BBarrelErestMC_fStripTrackID;   //!
   TBranch        *b_BBarrelErestMC_fStripTime;   //!
   TBranch        *b_BBarrelErestMC_fStripStopped;   //!
   TBranch        *b_BBarrelErestMC_fRingNr;   //!
   TBranch        *b_BBarrelErestMC_fRingEnergy;   //!
   TBranch        *b_BBarrelErestMC_fRingA;   //!
   TBranch        *b_BBarrelErestMC_fRingZ;   //!
   TBranch        *b_BBarrelErestMC_fRingTrackID;   //!
   TBranch        *b_BBarrelErestMC_fRingTime;   //!
   TBranch        *b_BBarrelErestMC_fRingStopped;   //!
   TBranch        *b_BBarrelErestMC_fA;   //!
   TBranch        *b_BBarrelErestMC_fZ;   //!
   TBranch        *b_BBarrelErestMC_fTrackID;   //!
   TBranch        *b_BBarrelErestMC_fTime;   //!
   TBranch        *b_BBarrelErestMC_fStopped;   //!
   TBranch        *b_BBarrelErestMC_fResKinEnergy;   //!
   TBranch        *b_BBarrelErestMC_fMult;   //!
   TBranch        *b_BBarrelErestMC_fRear;   //!
   TBranch        *b_BBarrelErestMC_fEdet;   //!
   TBranch        *b_Miniball_;   //!
   TBranch        *b_Miniball_fUniqueID;   //!
   TBranch        *b_Miniball_fBits;   //!
   TBranch        *b_Miniball_fCrystal;   //!
   TBranch        *b_Miniball_fClusterID;   //!
   TBranch        *b_Miniball_fStrange;   //!

   AnalyseLaBr(TTree *tree=0);
   virtual AnalyseLaBr();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalyseLaBr_cxx
AnalyseLaBr::AnalyseLaBr(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Volumes/RootTrees/result/Eg_100/Eg100.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Volumes/RootTrees/result/Eg_100/Eg100.root");
      }
      f->GetObject("treeDet",tree);

   }
   Init(tree);
}

AnalyseLaBr::~AnalyseLaBr()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalyseLaBr::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalyseLaBr::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnalyseLaBr::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("FCDMC", &FCDMC_, &b_FCDMC_);
   fChain->SetBranchAddress("FCDMC.fUniqueID", FCDMC_fUniqueID, &b_FCDMC_fUniqueID);
   fChain->SetBranchAddress("FCDMC.fBits", FCDMC_fBits, &b_FCDMC_fBits);
   fChain->SetBranchAddress("FCDMC.fID", FCDMC_fID, &b_FCDMC_fID);
   fChain->SetBranchAddress("FCDMC.fStripNr", FCDMC_fStripNr, &b_FCDMC_fStripNr);
   fChain->SetBranchAddress("FCDMC.fStripEnergy", FCDMC_fStripEnergy, &b_FCDMC_fStripEnergy);
   fChain->SetBranchAddress("FCDMC.fStripA", FCDMC_fStripA, &b_FCDMC_fStripA);
   fChain->SetBranchAddress("FCDMC.fStripZ", FCDMC_fStripZ, &b_FCDMC_fStripZ);
   fChain->SetBranchAddress("FCDMC.fStripTrackID", FCDMC_fStripTrackID, &b_FCDMC_fStripTrackID);
   fChain->SetBranchAddress("FCDMC.fStripTime", FCDMC_fStripTime, &b_FCDMC_fStripTime);
   fChain->SetBranchAddress("FCDMC.fStripStopped", FCDMC_fStripStopped, &b_FCDMC_fStripStopped);
   fChain->SetBranchAddress("FCDMC.fRingNr", FCDMC_fRingNr, &b_FCDMC_fRingNr);
   fChain->SetBranchAddress("FCDMC.fRingEnergy", FCDMC_fRingEnergy, &b_FCDMC_fRingEnergy);
   fChain->SetBranchAddress("FCDMC.fRingA", FCDMC_fRingA, &b_FCDMC_fRingA);
   fChain->SetBranchAddress("FCDMC.fRingZ", FCDMC_fRingZ, &b_FCDMC_fRingZ);
   fChain->SetBranchAddress("FCDMC.fRingTrackID", FCDMC_fRingTrackID, &b_FCDMC_fRingTrackID);
   fChain->SetBranchAddress("FCDMC.fRingTime", FCDMC_fRingTime, &b_FCDMC_fRingTime);
   fChain->SetBranchAddress("FCDMC.fRingStopped", FCDMC_fRingStopped, &b_FCDMC_fRingStopped);
   fChain->SetBranchAddress("FCDMC.fA", FCDMC_fA, &b_FCDMC_fA);
   fChain->SetBranchAddress("FCDMC.fZ", FCDMC_fZ, &b_FCDMC_fZ);
   fChain->SetBranchAddress("FCDMC.fTrackID", FCDMC_fTrackID, &b_FCDMC_fTrackID);
   fChain->SetBranchAddress("FCDMC.fTime", FCDMC_fTime, &b_FCDMC_fTime);
   fChain->SetBranchAddress("FCDMC.fStopped", FCDMC_fStopped, &b_FCDMC_fStopped);
   fChain->SetBranchAddress("FCDMC.fResKinEnergy", FCDMC_fResKinEnergy, &b_FCDMC_fResKinEnergy);
   fChain->SetBranchAddress("FCDMC.fMult", FCDMC_fMult, &b_FCDMC_fMult);
   fChain->SetBranchAddress("FCDMC.fRear", FCDMC_fRear, &b_FCDMC_fRear);
   fChain->SetBranchAddress("FCDMC.fEdet", FCDMC_fEdet, &b_FCDMC_fEdet);
   fChain->SetBranchAddress("BBarrelDeltaEMC", &BBarrelDeltaEMC_, &b_BBarrelDeltaEMC_);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fUniqueID", BBarrelDeltaEMC_fUniqueID, &b_BBarrelDeltaEMC_fUniqueID);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fBits", BBarrelDeltaEMC_fBits, &b_BBarrelDeltaEMC_fBits);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fID", BBarrelDeltaEMC_fID, &b_BBarrelDeltaEMC_fID);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripNr", BBarrelDeltaEMC_fStripNr, &b_BBarrelDeltaEMC_fStripNr);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripEnergy", BBarrelDeltaEMC_fStripEnergy, &b_BBarrelDeltaEMC_fStripEnergy);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripA", BBarrelDeltaEMC_fStripA, &b_BBarrelDeltaEMC_fStripA);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripZ", BBarrelDeltaEMC_fStripZ, &b_BBarrelDeltaEMC_fStripZ);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripTrackID", BBarrelDeltaEMC_fStripTrackID, &b_BBarrelDeltaEMC_fStripTrackID);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripTime", BBarrelDeltaEMC_fStripTime, &b_BBarrelDeltaEMC_fStripTime);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStripStopped", BBarrelDeltaEMC_fStripStopped, &b_BBarrelDeltaEMC_fStripStopped);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingNr", BBarrelDeltaEMC_fRingNr, &b_BBarrelDeltaEMC_fRingNr);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingEnergy", BBarrelDeltaEMC_fRingEnergy, &b_BBarrelDeltaEMC_fRingEnergy);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingA", BBarrelDeltaEMC_fRingA, &b_BBarrelDeltaEMC_fRingA);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingZ", BBarrelDeltaEMC_fRingZ, &b_BBarrelDeltaEMC_fRingZ);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingTrackID", BBarrelDeltaEMC_fRingTrackID, &b_BBarrelDeltaEMC_fRingTrackID);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingTime", BBarrelDeltaEMC_fRingTime, &b_BBarrelDeltaEMC_fRingTime);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRingStopped", BBarrelDeltaEMC_fRingStopped, &b_BBarrelDeltaEMC_fRingStopped);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fA", BBarrelDeltaEMC_fA, &b_BBarrelDeltaEMC_fA);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fZ", BBarrelDeltaEMC_fZ, &b_BBarrelDeltaEMC_fZ);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fTrackID", BBarrelDeltaEMC_fTrackID, &b_BBarrelDeltaEMC_fTrackID);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fTime", BBarrelDeltaEMC_fTime, &b_BBarrelDeltaEMC_fTime);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fStopped", BBarrelDeltaEMC_fStopped, &b_BBarrelDeltaEMC_fStopped);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fResKinEnergy", BBarrelDeltaEMC_fResKinEnergy, &b_BBarrelDeltaEMC_fResKinEnergy);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fMult", BBarrelDeltaEMC_fMult, &b_BBarrelDeltaEMC_fMult);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fRear", BBarrelDeltaEMC_fRear, &b_BBarrelDeltaEMC_fRear);
   fChain->SetBranchAddress("BBarrelDeltaEMC.fEdet", BBarrelDeltaEMC_fEdet, &b_BBarrelDeltaEMC_fEdet);
   fChain->SetBranchAddress("BBarrelErestMC", &BBarrelErestMC_, &b_BBarrelErestMC_);
   fChain->SetBranchAddress("BBarrelErestMC.fUniqueID", BBarrelErestMC_fUniqueID, &b_BBarrelErestMC_fUniqueID);
   fChain->SetBranchAddress("BBarrelErestMC.fBits", BBarrelErestMC_fBits, &b_BBarrelErestMC_fBits);
   fChain->SetBranchAddress("BBarrelErestMC.fID", BBarrelErestMC_fID, &b_BBarrelErestMC_fID);
   fChain->SetBranchAddress("BBarrelErestMC.fStripNr", BBarrelErestMC_fStripNr, &b_BBarrelErestMC_fStripNr);
   fChain->SetBranchAddress("BBarrelErestMC.fStripEnergy", BBarrelErestMC_fStripEnergy, &b_BBarrelErestMC_fStripEnergy);
   fChain->SetBranchAddress("BBarrelErestMC.fStripA", BBarrelErestMC_fStripA, &b_BBarrelErestMC_fStripA);
   fChain->SetBranchAddress("BBarrelErestMC.fStripZ", BBarrelErestMC_fStripZ, &b_BBarrelErestMC_fStripZ);
   fChain->SetBranchAddress("BBarrelErestMC.fStripTrackID", BBarrelErestMC_fStripTrackID, &b_BBarrelErestMC_fStripTrackID);
   fChain->SetBranchAddress("BBarrelErestMC.fStripTime", BBarrelErestMC_fStripTime, &b_BBarrelErestMC_fStripTime);
   fChain->SetBranchAddress("BBarrelErestMC.fStripStopped", BBarrelErestMC_fStripStopped, &b_BBarrelErestMC_fStripStopped);
   fChain->SetBranchAddress("BBarrelErestMC.fRingNr", BBarrelErestMC_fRingNr, &b_BBarrelErestMC_fRingNr);
   fChain->SetBranchAddress("BBarrelErestMC.fRingEnergy", BBarrelErestMC_fRingEnergy, &b_BBarrelErestMC_fRingEnergy);
   fChain->SetBranchAddress("BBarrelErestMC.fRingA", BBarrelErestMC_fRingA, &b_BBarrelErestMC_fRingA);
   fChain->SetBranchAddress("BBarrelErestMC.fRingZ", BBarrelErestMC_fRingZ, &b_BBarrelErestMC_fRingZ);
   fChain->SetBranchAddress("BBarrelErestMC.fRingTrackID", BBarrelErestMC_fRingTrackID, &b_BBarrelErestMC_fRingTrackID);
   fChain->SetBranchAddress("BBarrelErestMC.fRingTime", BBarrelErestMC_fRingTime, &b_BBarrelErestMC_fRingTime);
   fChain->SetBranchAddress("BBarrelErestMC.fRingStopped", BBarrelErestMC_fRingStopped, &b_BBarrelErestMC_fRingStopped);
   fChain->SetBranchAddress("BBarrelErestMC.fA", BBarrelErestMC_fA, &b_BBarrelErestMC_fA);
   fChain->SetBranchAddress("BBarrelErestMC.fZ", BBarrelErestMC_fZ, &b_BBarrelErestMC_fZ);
   fChain->SetBranchAddress("BBarrelErestMC.fTrackID", BBarrelErestMC_fTrackID, &b_BBarrelErestMC_fTrackID);
   fChain->SetBranchAddress("BBarrelErestMC.fTime", BBarrelErestMC_fTime, &b_BBarrelErestMC_fTime);
   fChain->SetBranchAddress("BBarrelErestMC.fStopped", BBarrelErestMC_fStopped, &b_BBarrelErestMC_fStopped);
   fChain->SetBranchAddress("BBarrelErestMC.fResKinEnergy", BBarrelErestMC_fResKinEnergy, &b_BBarrelErestMC_fResKinEnergy);
   fChain->SetBranchAddress("BBarrelErestMC.fMult", BBarrelErestMC_fMult, &b_BBarrelErestMC_fMult);
   fChain->SetBranchAddress("BBarrelErestMC.fRear", BBarrelErestMC_fRear, &b_BBarrelErestMC_fRear);
   fChain->SetBranchAddress("BBarrelErestMC.fEdet", BBarrelErestMC_fEdet, &b_BBarrelErestMC_fEdet);
   fChain->SetBranchAddress("Miniball", &Miniball_, &b_Miniball_);
   fChain->SetBranchAddress("Miniball.fUniqueID", Miniball_fUniqueID, &b_Miniball_fUniqueID);
   fChain->SetBranchAddress("Miniball.fBits", Miniball_fBits, &b_Miniball_fBits);
   fChain->SetBranchAddress("Miniball.fCrystal", Miniball_fCrystal, &b_Miniball_fCrystal);
   fChain->SetBranchAddress("Miniball.fClusterID", Miniball_fClusterID, &b_Miniball_fClusterID);
   fChain->SetBranchAddress("Miniball.fStrange", Miniball_fStrange, &b_Miniball_fStrange);
   Notify();
}

Bool_t  AnalyseLaBr::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void  AnalyseLaBr::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t  AnalyseLaBr::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalyseLaBr_cxx
