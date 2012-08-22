#ifndef TestGen_H
#define TestGen_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <TMath.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TRandom.h>
#include <TLeaf.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TLorentzVector.h"

#include <algorithm>

#include "AnaInput.h"
#include "DPSelection.h"
#include "hDraw.h"
#include "Histogram.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXGEN 20
#define MAXMU 5

struct iMatch {

   int    idg ; // the matching id for gen
   int    idr ; // the matching id for reco
   int    ig ; // position in gen collection
   int    ir ; // position in reco collection
   double dr ;
   double dPt ; 

} ;

class TestGen : public TObject {

public:

   TestGen( string datacardfile = "DataCard.txt");     
   ~TestGen();     
   
   void ReadTree( string dataName ) ;
   bool Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;
   bool Propagator1( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;

   void HistoWrite( string theFolder , TFile* file ) ;

   //vector<int> GlobalDRMatch( vector<objID> vr, vector<objID> vg, vector<double>& v_dr ) ;
   vector<iMatch> GlobalDRMatch( vector<objID> vr, vector<objID> vg ) ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw ;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;
   int SkipEvents ;
   int isData ;
   double TCut ;
   double FitCtau ;

   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float seedTimeErr[MAXPHO], aveTimeErr[MAXPHO], aveTimeErr1[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO], sMinPho[MAXPHO] ;
   float fSpike[MAXPHO], maxSwissX[MAXPHO], seedSwissX[MAXPHO], dR_TrkPho[MAXPHO] ;
   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float muE[MAXMU] ;

   float metPx, metPy, metE ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, triggered, nVertices, totalNVtx ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;
   vector<objID> recoPho ;
   vector<objID> genPho ;
   vector<double> recoTs ;
   vector<double> genTs ;
 
   vector<double> photonCuts ;
   vector<double> jetCuts ;

   double decayR ;
  
   // histogram definition
   TFile *theFile ;
   string hfName ;

   TH1D* obsTime     ;
   TH1D* aveObsTime  ;
   TH1D* aveObsTime1 ;
   TH1D* aveObsTime2 ;
   TH1D* obsEBTimeErr  ;
   TH1D* obsEETimeErr  ;
   TH1D* aveObsEBTimeErr ;
   TH1D* aveObsEETimeErr ;
   TH1D* aveObsEBTimeErr1 ;
   TH1D* aveObsEETimeErr1 ;

   TH2D* seedTime_Chi2  ;

   TH1D* badPhoTime     ;
   TH1D* TimeLT3Jets    ;
   TH1D* TimeGE3Jets    ;
   TH1D* TimeLowMET     ;
   TH1D* TimeBigMET     ;

   TH1D* SpikeEtaP      ;
   TH1D* SpikeEtaN      ;
   TH1D* Vz_P           ;
   TH1D* Vz_N           ;

   TH1D* h_matchRecoTime ;
   TH1D* h_matchGenTime  ;
   TH1D* h_matchTime     ;
   TH1D* h_genTime       ;
   TH1D* h_TimeRes1      ;
   TH1D* h_TimeRes2      ;
   TH1D* h_TimeRes3      ;
   TH1D* h_aTimeRes1     ;
   TH1D* h_aTimeRes2     ;
   TH1D* h_aTimeRes3     ;
   TH1D* h_PtRes         ;

   TH2D* Time_R  ;
   TH2D* Time_Z  ;

   TH1D* h_Time   ;
   TH1D* h_nChi2  ;
   TH1D* h_ctau   ;
   TH1D* h_xbeta  ;
   TH1D* h_TrkIso   ;
   TH1D* h_HcalIso  ;
   TH1D* h_EcalIso  ;
   TH1D* h_TrkIsoR  ;
   TH1D* h_HcalIsoR ;
   TH1D* h_EcalIsoR ;

   TH1D* h_maxSwissEB ;
   TH1D* h_maxSwissEE ;
   TH1D* h_seedSwiss  ;
   TH1D* h_fSpike    ;
   TH1D* h_nXtals    ;
   TH1D* h_nBC       ;
   TH1D* h_sMin      ;

   TH1D* h_met        ;
   TH1D* h_g1Pt       ;
   TH1D* h_gen1Pt     ;
   TH1D* h_gen1RecoPt ;

   TH1D* h_nVtx       ;
   TH1D* h_nPhotons   ;
   TH1D* h_nGenPhotons;
   TH1D* h_nJets      ;
   TH1D* h_nMuons     ;
   TH1D* h_nElectrons ;

   //ClassDef(TestGen, 1);
};

//#if !defined(__CINT__)
//    ClassImp(TestGen);
#endif

