#ifndef Tester_H
#define Tester_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <TRandom.h>
#include <TString.h>
#include <TSystem.h>
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

/*
#define MAXPHO 10
#define MAXVTX 10
#define MAXJET 15
#define MAXGEN 20
#define MAXMU 5
*/

class Tester : public TObject {

public:

   Tester( string datacardfile = "DataCard.txt");     
   ~Tester();     
   
   void ReadTree( string dataName ) ;
   int  TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV, double& match_dR, double dR_cut = 0.5 )  ;

   void Plot() ;
   void HistoInit() ;
   void HistoWrite() ;
   void HistoOpen();

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw ;

   TFile* theFile ;

   vector<objID> selectPho ;
   vector<objID> selectJets ;
   vector<double> jetCuts ;
   vector<double> photonCuts ;

   string hfolder  ;
   string plotType ;
   string hfName  ;
   int ProcessEvents ;
   int isData ;

   int nX0, n2X0_g, n1X0_g, n0X0_g  ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO], dR_TrkPho[MAXPHO], pt_TrkPho[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO] ;
   float phoEcalIso[MAXPHO], phoHcalIso[MAXPHO], phoTrkIso[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO] ;
   float phoHovE[MAXPHO], photIso[MAXPHO], cHadIso[MAXPHO], nHadIso[MAXPHO] ;
   float cscdPhi[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO], seedSwissX[MAXPHO] ;

   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float jetPx[MAXJET], jetPy[MAXJET] ;

   float metPx, metPy, metE;
   float t_metPx, t_metPy, t_metE, t_phoPx, t_phoPy, t_phoPz, t_phoE, t_metdR , t_phodR ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, nVertices, triggered, L1a, totalNVtx ;
   int   runId ;

   //float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN], genT[MAXGEN] ;
   int pdgId[MAXGEN], momId[MAXGEN] ;

   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

   //Histograms
   TH1D* h_PhotPt      ;
   TH1D* h_AllPhotPt      ;

   //ClassDef(Tester, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Tester);
#endif

