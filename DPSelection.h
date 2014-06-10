#ifndef DPSelection_H
#define DPSelection_H

#include "TObject.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TTree.h>
#include "TLorentzVector.h"
#include "TH3.h"

#include "AnaInput.h"
#include "Rtuple.h"

/*
#define MAXPHO 10
#define MAXVTX 10
#define MAXJET 15
#define MAXMU 5
#define MAXELE 5
#define MAXGEN 20
typedef pair<int, TLorentzVector> objID ;
*/


//class DPSelection : public TObject {
class DPSelection {

public:

   DPSelection( string datacardfile = "DataCard.txt");     
   ~DPSelection();     
   //friend class Sync ;   

   void Init( TTree* tr ) ;
   void Init( Rtuple& rt ) ;
   void SetArray( int a[], int b[], int size ) ;
   void SetArray( float a[], float b[], int size ) ;


   bool HLTFilter();
   bool L1Filter();
   bool PhotonFilter() ;
   bool JetMETFilter( bool usePFClean = false );
   bool VertexFilter() ;
   bool ElectronFilter() ;
   bool MuonFilter() ;
   bool CorrectMET() ;

   bool GetEventStat( string flagName ) ;

   bool SignalSelection( bool isTightPhoton = false ) ; 
   uint32_t  EventIdentification() ;

   bool HaloTag( double cscdPhi, double sMaj, double sMin, double eta ) ;
   bool SpikeTag( int nXtl, double sMaj, double sMin , double swissX, double eta ) ;
   bool CosmicTag( double dtdEta , double dtdPhi ) ;

   void ResetCuts( string cutName, vector<int>& cutId, vector<double>& newValue ) ;
   void ResetCuts( string cutName, int cutId, double newValue ) ;
   void ResetCuts( string cutName = "All" ) ; // set cuts to default values from datacard 
   void ResetCounter() ;

   void GetCollection( string collName, vector<objID>& coll ) ;
   void ResetCollection( string cutName = "All" ) ; // clean the storage containers 
   void PrintCutFlow() ;
   inline int GetPhotonCutFlow() { return photonCutFlow ; }

   // return background prediction , upward error, downward error
   vector<double> ABCD_ABCD( vector<TH3D*>& hColls , vector<TH3D*>& hMIBs ) ; 
   vector<double> ABCD_Collision( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD ) ;
   vector<double> ABCD( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD, TH3D* hE, TH3D* hF ) ;

   double GetEstimation( TH3D* hCount, bool getQCD = true ) ;
   vector<double> GetComponent( int eta_i, double B12, double h_B12, double s_B12, double c_B12 ) ;
   vector<double> GetComponent( int eta_i, int B12,    int h_B12,    int s_B12,    int c_B12 ) ;

   

   // results
   bool passL1 ;
   bool passHLT ;
   bool passTrigger ;
   bool passVtx ;
   bool passPho ;
   bool passJet ;
   bool passMET ;
   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;
   TLorentzVector theMET ;

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
   float seedTime[MAXPHO], aveTime[MAXPHO], timeChi2[MAXPHO], dR_TrkPho[MAXPHO] ;
   float phoHovE[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], sigmaIeta[MAXPHO], seedSwissX[MAXPHO], seedE[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO] ;
   float photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;
   float cscdPhi[MAXPHO] , cscRho[MAXPHO], cscTime[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   int   nXtals[MAXPHO] ;

   //float vtxX[MAXVTX],    vtxY[MAXVTX] ; 
   float vtxZ[MAXVTX], vtxChi2[MAXVTX], vtxNdof[MAXVTX];
   float jetPx[MAXJET],   jetPy[MAXJET], jetPz[MAXJET],  jetE[MAXJET] ;
   float jetNDau[MAXJET], jetCM[MAXJET], jetCEF[MAXJET], jetCHF[MAXJET], jetNHF[MAXJET], jetNEF[MAXJET];
   float jecUnc[MAXJET],  jerUnc[MAXJET], jetTime[MAXJET], jetTimeErr[MAXJET] ;

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
   int counter[9] ;
   int gCounter[9] ;
   int photonCutFlow ;

   // Efficiency and mis-tag rate for background taggers
   vector<double> haloEff ;
   vector<double> spikeEff ;
   vector<double> cosEff ;
   vector<double> haloMis ;
   vector<double> spikeMis ;
   vector<double> cosMis ;
   int useInFlight ;


   // MET Correction
   double met1x, met1y, met1E ;
   double met2x, met2y, met2E ;

   // Systematic
   double metCorrX ;
   double metCorrY ;

   //ClassDef(DPSelection, 1);
};

//#if !defined(__CINT__)
//    ClassImp(DPSelection);
#endif

