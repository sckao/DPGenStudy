#ifndef Rtuple_h
#define Rtuple_h

#include "TChain.h" 

//#define MAXPHO 10
//#define MAXVTX 10
#define MAXPHO 12
#define MAXVTX 30
#define MAXJET 15
#define MAXMU 5
#define MAXELE 5
#define MAXGEN 20


struct Rtuple {

   unsigned int eventId ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], dR_TrkPho[MAXPHO], fSpike[MAXPHO], timeChi2[MAXPHO] ;
   float phoHovE[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], sigmaIeta[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO] ;
   float photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;
   float cscdPhi[MAXPHO] , dtdPhi[MAXPHO], dtdEta[MAXPHO], cscRho[MAXPHO], cscTime[MAXPHO] ;
   int   nXtals[MAXPHO] ;

   //float vtxX[MAXVTX],    vtxY[MAXVTX] ; 
   float vtxZ[MAXVTX], vtxChi2[MAXVTX], vtxNdof[MAXVTX];
   float jetPx[MAXJET],   jetPy[MAXJET], jetPz[MAXJET],  jetE[MAXJET] ;
   float jetNDau[MAXJET], jetCM[MAXJET], jetCEF[MAXJET], jetCHF[MAXJET], jetNHF[MAXJET], jetNEF[MAXJET];
   float jecUnc[MAXJET],  jerUnc[MAXJET] ;

   float muPx[MAXMU], muPy[MAXMU], muPz[MAXMU], muE[MAXMU] ;
   //float muEcalIso[MAXOBJ], muHcalIso[MAXOBJ], muTrkIso[MAXOBJ] ;
   float elePx[MAXELE], elePy[MAXELE], elePz[MAXELE], eleE[MAXELE] ;
   float eleEcalIso[MAXELE], eleHcalIso[MAXELE], eleTrkIso[MAXELE] ;
   int   eleNLostHits[MAXELE] ;

   float metPx, metPy, metE, met_dx1, met_dy1, met_dx2, met_dy2, met_dx3, met_dy3 ;
   int   nJets, nPhotons, nElectrons, nVertices, totalNVtx, nMuons, triggered, L1a ;

} ;

// ------------------------------------------------------------------------
//! branch addresses settings
void setRtupleAddresses(TTree* chain, Rtuple& Vars );

//! create branches for a tree
//void setRtupleBranches(TTree* chain, Rtuple& treeVars);

//! initialize branches
//void initRtuple(TTree* chain, Rtuple& treeVars);



#endif
