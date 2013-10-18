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
#include <TRandom3.h>
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
   
   void ReadTree( string dataName = "0", double weight = 1. ) ;
   bool Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;
   bool Propagator1( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;

   //vector<int> GlobalDRMatch( vector<objID> vr, vector<objID> vg, vector<double>& v_dr ) ;
   vector<iMatch> GlobalDRMatch( vector<objID> vr, vector<objID> vg ) ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   Histogram*    Hist ;

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
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO];
   float photIso[MAXPHO] , cHadIso[MAXPHO], nHadIso[MAXPHO], phoHoverE[MAXPHO] ;
   float fSpike[MAXPHO], maxSwissX[MAXPHO], seedSwissX[MAXPHO], dR_TrkPho[MAXPHO] ;
   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float sigmaEta[MAXPHO], sigmaIeta[MAXPHO], cscdPhi[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float muE[MAXMU] ;

   float metPx, metPy, metE ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, triggered, nVertices, totalNVtx ;
   int   nHaloHits , nHaloTracks ;
   float haloPhi , haloRho ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;
   vector<objID> recoPho ;
   vector<objID> genPho ;
   vector<double> recoTs ;
   vector<double> genTs ;
   vector<double> genXTs ;
   vector<TLorentzVector> genPs ;
 
   vector<double> photonCuts ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;

   double decayR ;
  
   // Root File for Rootuple or histograms
   TFile *theFile ;
   string hfName ;
   // Histograms set
   hSet   h ;

   //ClassDef(TestGen, 1);
};

//#if !defined(__CINT__)
//    ClassImp(TestGen);
#endif

