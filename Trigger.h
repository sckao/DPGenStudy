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
#include "Rtuple.h"
/*
#define MAXPHO 10
#define MAXVTX 10
#define MAXJET 15
#define MAXGEN 20
#define MAXMU 5
*/

class Trigger : public TObject {

public:

   Trigger( string datacardfile = "DataCard.txt");     
   ~Trigger();     
   
   void ReadTree( string dataName ) ;
   int  TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV, double& match_dR, double dR_cut = 0.5 )  ;
   void Plot() ;
   void EventList( string dataName ) ;
   void CutFlow( string dataName ) ;

   void HistoWrite() ;
   void HistoOpen();

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw ;

   TFile* theFile ;

   vector<objID> selectPho ;
   vector<objID> selectJets ;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   string hfName  ;
   int ProcessEvents ;
   int isData ;
   Rtuple rt ;

   //float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   //float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   //int   pdgId[MAXGEN], momId[MAXGEN] ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], dR_TrkPho[MAXPHO], pt_TrkPho[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO] ;
   float phoHovE[MAXPHO], photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;
   float cscdPhi[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;

   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float jetPx[MAXJET], jetPy[MAXJET] ;

   float metPx, metPy, metE;
   float t_metPx, t_metPy, t_metE, t_phoPx, t_phoPy, t_phoPz, t_phoE, t_metdR , t_phodR ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, nVertices, triggered, L1a, totalNVtx ;
   int   runId ;

   //Histograms
   TH1D* h_gPt      ;
   TH1D* h_trg_gPt  ;
   TH1D* dR_TrgReco_Pho ;
   TH1D* dR_TrgReco_Met ;
   TH1D* dR_Pho90 ;
   TH1D* dR_Pho50 ;

   TH1D* h_gPt_sel ;  
   TH1D* h_gPt_trg ;

   TH1D* h_met     ; 
   TH1D* h_met_sel ; 
   TH1D* h_trg_met ;
   TH1D* h_met_trg ;

   TH2D* hEff_Sel ;
   TH2D* hEff_Trg ;
   TH2D* hEff_2D ;

   TH1D* hTime_sel ;

   //ClassDef(Trigger, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Trigger);
#endif

