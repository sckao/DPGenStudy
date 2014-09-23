#ifndef GenAna_H
#define GenAna_H

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
#include "Ntuple.h"
#include "hDraw.h"
/*
#define MAXPHO 10
#define MAXVTX 10
#define MAXGEN 20
#define MAXMU 5
*/

class GenAna : public TObject {

public:

   GenAna( string datacardfile = "DataCard.txt");     
   ~GenAna();     
   
   void ReadTree( string dataName = "0", double weight = 1. ) ;
   bool Propagator( TLorentzVector& v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;

   void WriteHisto() ;
   void OpenHisto() ;

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;
   int SkipEvents ;

   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;

   float jetPx[10], jetPy[10], jetPz[10], jetE[10] ;

   float metPx, metPy, metE ;
   int   nGen, nJets ;


   vector<objID> genPho ;
   vector<double> v_time ;
   vector<double> genXTs ;
   vector<double> v_ctbgT ;
 
   vector<double> timeCalib ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   string hfName ;

   // Histograms set
   TH1D* h_ctbg ;
   TH1D* h_ctbgT ;
   TH1D* h_ctau ;
   TH1D* h_Time ;
   TH1D* selTime ;
   TH1D* h_Xbeta ;
   TH1D* h_XPt ;
   TH1D* h_XEta ;
   TH2D* hTime_Xbeta ;
   TH2D* hTime_ctbgT ;

   TH1D* sel_ctbgT ;
   TH1D* acc_ctbgT ;
   TH1D* reco_ctbgT ;
   TH1D* acc_ctbgT0 ;
   TH1D* acc_ctbgT1 ;
   TH1D* acc_ctbgT2 ;
   TH1D* sel_XEta ;
   TH1D* xPt_T1 ;
   TH1D* xPt_T2 ;
   TH1D* xCtau_T1 ;
   TH1D* xCtau_T2 ;
   TH1D* xBeta_T1 ;
   TH1D* xBeta_T2 ;

   TH2D* h_ctbg_RZ ;
   TH2D* dt1_dt2 ;
   TH2D* dt1_dt2_late ;

   TH1D* h_lateXctau ;
   TH1D* h_lateXctbgT ;
   TH1D* h_lateXbeta ;
   TH1D* h_lateXPt ;

   TH1D* h_GMET ;
   TH1D* h_genMET ; 
   TH1D* h_METRes ;
   TH1D* h_METdPhi ;

   TH1D* h_gen1RecoPt ;
   TH1D* h_gen1Pt ;

   TH1D* h_nJet ;
   TH1D* h_j1Pt ;

   //ClassDef(GenAna, 1);
};

//#if !defined(__CINT__)
//    ClassImp(GenAna);
#endif

