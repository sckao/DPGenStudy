#ifndef Ntuple_h
#define Ntuple_h

#include "TChain.h" 

#define MAXVTX 10
#define MAXJET 15
#define MAXPHO 12
#define MAXMU 5
#define MAXELE 5
#define MAXGEN 20

struct Ntuple
{
  
  unsigned int runId;
  unsigned int lumiSection;
  unsigned int orbit;
  unsigned int bx;
  unsigned int eventId;
  int triggered ;
  int L1a;  

  // vertex variables
  int   nVertices;
  int   totalNVtx ;
  float vtxNTracks[MAXVTX];
  float vtxChi2[MAXVTX];
  float vtxNdof[MAXVTX];
  float vtxX[MAXVTX];
  float vtxDx[MAXVTX];
  float vtxY[MAXVTX];
  float vtxDy[MAXVTX];
  float vtxZ[MAXVTX];
  float vtxDz[MAXVTX];
  
  // reco variables
  int   nJets ;
  float jetPx[MAXJET];
  float jetPy[MAXJET];
  float jetPz[MAXJET];
  float jetE[MAXJET];
  int   jetNDau[MAXJET];
  int   jetCM[MAXJET];
  float jetCEF[MAXJET];
  float jetCHF[MAXJET];
  float jetNHF[MAXJET];
  float jetNEF[MAXJET];
  
  float metPx;
  float metPy;
  float met;

  int   nElectrons ;
  float elePx[MAXELE];
  float elePy[MAXELE];
  float elePz[MAXELE];
  float eleE[MAXELE];
  int   eleNLostHits[MAXELE] ;
  float eleEcalIso[MAXELE];
  float eleHcalIso[MAXELE];
  float eleTrkIso[MAXELE];

  int   nMuons ;
  float muPx[MAXMU];
  float muPy[MAXMU];
  float muPz[MAXMU];
  float muE[MAXMU];

  int   nPhotons ;
  float phoPx[MAXPHO];
  float phoPy[MAXPHO];
  float phoPz[MAXPHO];
  float phoE[MAXPHO];
  float phoEcalIso[MAXPHO];
  float phoHcalIso[MAXPHO];
  float phoTrkIso[MAXPHO];
  float dR_TrkPho[MAXPHO];
  float pt_TrkPho[MAXPHO];
  float phoHoverE[MAXPHO];
  float sMinPho[MAXPHO];
  float sMajPho[MAXPHO];
  float seedTime[MAXPHO];
  float seedTimeErr[MAXPHO];
  float aveTime[MAXPHO];
  float aveTime1[MAXPHO];
  float aveTimeErr[MAXPHO];
  float aveTimeErr1[MAXPHO];
  float timeChi2[MAXPHO] ;
  float fSpike[MAXPHO] ;
  float seedSwissX[MAXPHO] ;
  int   nXtals[MAXPHO] ;
  int   nBC[MAXPHO] ;


  // Gen Particle information
  int nGen ; 
  int pdgId[MAXGEN] ;
  int momId[MAXGEN] ;
  float genPx[MAXGEN] ; 
  float genPy[MAXGEN] ; 
  float genPz[MAXGEN] ; 
  float genE[MAXGEN] ; 
  float genM[MAXGEN] ; 
  float genVx[MAXGEN] ; 
  float genVy[MAXGEN] ; 
  float genVz[MAXGEN] ; 
  float genT[MAXGEN] ; 

};

// ------------------------------------------------------------------------
//! branch addresses settings
void setBranchAddresses(TTree* chain, Ntuple& treeVars);

//! create branches for a tree
void setBranches(TTree* chain, Ntuple& treeVars);

//! initialize branches
void initializeBranches(TTree* chain, Ntuple& treeVars);



#endif
