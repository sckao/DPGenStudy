#ifndef DPSelection_H
#define DPSelection_H

#include "TObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TTree.h>
#include "TLorentzVector.h"

#include "AnaInput.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXJET 15
#define MAXMU 5
#define MAXELE 5
#define MAXGEN 20

typedef pair<int, TLorentzVector> objID ;

//class DPSelection : public TObject {
class DPSelection {

public:

   DPSelection( string datacardfile = "DataCard.txt");     
   ~DPSelection();     
   //friend class Sync ;   

   void Init( TTree* tr ) ;

   bool HLTFilter();
   bool L1Filter();
   bool PhotonFilter();
   bool JetMETFilter( bool usePFClean = false );
   bool VertexFilter();
   bool ElectronFilter();
   bool MuonFilter();

   bool GammaJetsBackground() ; 

   bool SignalSelection( bool isTightPhoton = false ) ; 
   bool MCSignalSelection( bool isTightPhoton = false ) ; 
   bool GammaJetsControlSample( bool isTightPhoton = true ) ; 
   bool QCDControlSample() ; 

   void ResetCuts( string cutName, vector<int>& cutId, vector<double>& newValue ) ;
   void ResetCuts( string cutName, int cutId, double newValue ) ;
   void ResetCuts( string cutName = "All" ) ; // set cuts to default values from datacard 
   void ResetCounter() ;

   void GetCollection( string collName, vector<objID>& coll ) ;
   void ResetCollection( string cutName = "All" ) ; // clean the storage containers 
   void PrintCutFlow() ;
   inline int GetPhotonCutFlow() { return photonCutFlow ; }

private:

   AnaInput*       Input;

   vector<objID> phoV ;
   vector<objID> jetV ;
   vector<objID> eleV ;
   vector<objID> muV ;

   vector<double> photonCuts ;
   vector<double> photonIso ;
   vector<double> photonPFIso ;
   vector<double> vtxCuts ;
   vector<double> jetCuts ;
   vector<double> electronCuts ;
   vector<double> muonCuts ;
   vector<int>    trigBits ;

   unsigned int eventId ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], dR_TrkPho[MAXPHO], fSpike[MAXPHO] ;
   float phoHovE[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], sigmaIeta[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO] ;
   float photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;

   float vtxX[MAXVTX],    vtxY[MAXVTX],  vtxZ[MAXVTX],   vtxChi2[MAXVTX], vtxNdof[MAXVTX];
   float jetPx[MAXJET],   jetPy[MAXJET], jetPz[MAXJET],  jetE[MAXJET] ;
   float jetNDau[MAXJET], jetCM[MAXJET], jetCEF[MAXJET], jetCHF[MAXJET], jetNHF[MAXJET], jetNEF[MAXJET];
   float jecUnc[MAXJET],  jerUnc[MAXJET] ;

   float muPx[MAXMU], muPy[MAXMU], muPz[MAXMU], muE[MAXMU] ;
   //float muEcalIso[MAXOBJ], muHcalIso[MAXOBJ], muTrkIso[MAXOBJ] ;
   float elePx[MAXELE], elePy[MAXELE], elePz[MAXELE], eleE[MAXELE] ;
   float eleEcalIso[MAXELE], eleHcalIso[MAXELE], eleTrkIso[MAXELE] ;
   int   eleNLostHits[MAXELE] ;

   float metPx, metPy, metE, met_dx1, met_dy1, met_dx2, met_dy2, met_dx3, met_dy3 ;
   int   nJets, nPhotons, nElectrons, nVertices, nMuons, triggered, L1a ;

   int isData ;
   int UseL1 ;
   int systType ;
   int usePFIso ;
   vector<int> trigCuts ;

   // counters for cutflow  
   int counter[8] ;
   int gCounter[8] ;
   int photonCutFlow ;

   //ClassDef(DPSelection, 1);
};

//#if !defined(__CINT__)
//    ClassImp(DPSelection);
#endif

