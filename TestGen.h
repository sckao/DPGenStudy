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

#include "AnaInput.h"
#include "DPSelection.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXGEN 20

class TestGen : public TObject {

public:

   TestGen( string datacardfile = "DataCard.txt");     
   ~TestGen();     
   
   void ReadTree( string dataName ) ;
   bool Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;
   bool Propagator1( TLorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;
   static Double_t fExp(Double_t *v, Double_t *par) ;


private:

   AnaInput*     Input;
   DPSelection*  select;

   string hfolder  ;
   string plotType ;
   string rfolder  ;
   int ProcessEvents ;
   int isData ;
   double TCut ;
   double FitCtau ;

   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN], genM[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;
   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO] ;
   //float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;
   float metPx, metPy, metE ;
   int   nGen, nPhotons, nJets, nMuons, nElectrons, triggered ;

   //ClassDef(TestGen, 1);
};

//#if !defined(__CINT__)
//    ClassImp(TestGen);
#endif

