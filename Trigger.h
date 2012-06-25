#ifndef Trigger_H
#define Trigger_H

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
#include <TLatex.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TGraphErrors.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "DPSelection.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXGEN 20
#define MAXMU 5

class Trigger : public TObject {

public:

   Trigger( string datacardfile = "DataCard.txt");     
   ~Trigger();     
   
   void ReadTree( string dataName ) ;
   void EffPlot( TH1D* hCut, TH1D* hAll, double minBinContent, string graphName ) ;
   void EffProbPlot( double N_pass, double N_all ) ;
   pair<double,double> EffError( double N_all, double N_pass ) ;
   static Double_t BinomialErr( Double_t* x, Double_t* par ) ;


private:

   AnaInput*     Input;
   DPSelection*  select;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;
   int isData ;
   double TCut ;

   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], dR_TrkPho[MAXPHO], pt_TrkPho[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO] ;
   float seedTimeErr[MAXPHO], aveTimeErr[MAXPHO], aveTimeErr1[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float muE[MAXMU] ;

   float metPx, metPy, metE ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, nVertices, triggered, L1a ;
   int   runId ;

   //ClassDef(Trigger, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Trigger);
#endif

