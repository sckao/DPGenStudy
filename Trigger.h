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
#include "hDraw.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXJET 15
#define MAXGEN 20
#define MAXMU 5

class Trigger : public TObject {

public:

   Trigger( string datacardfile = "DataCard.txt");     
   ~Trigger();     
   
   void ReadTree( string dataName ) ;
   int TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV )  ;
   void EventList( string dataName ) ;
   void CutFlow( string dataName ) ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw ;

   vector<objID> phoV ;
   vector<objID> jetV ;
   vector<objID> muonV ;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;
   int isData ;
   double TCut ;
   vector<double> thresPhoMET ;
   vector<int>  minBinContent ;
   vector<double> photonPFIso ;
   int usePFIso ;
   int purity[10] ;

   //float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   //float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   //int   pdgId[MAXGEN], momId[MAXGEN] ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], dR_TrkPho[MAXPHO], pt_TrkPho[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO], sMinPho[MAXPHO] ;
   float phoHovE[MAXPHO], photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;

   float fSpike[MAXPHO] ;
   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float jetPx[MAXJET], jetPy[MAXJET] ;
   float muE[MAXMU], muPx[MAXMU], muPy[MAXMU] ;

   float metPx, metPy, metE;
   float t_metPx, t_metPy, t_metE, t_phoPx, t_phoPy, t_phoPz, t_phoE, t_metdR , t_phodR ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, nVertices, triggered, L1a ;
   int   runId ;

   //ClassDef(Trigger, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Trigger);
#endif

