#ifndef Systematic_H
#define Systematic_H

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
#include <TStyle.h>
#include <TFrame.h>
#include "TLorentzVector.h"

#include <algorithm>

#include "AnaInput.h"
#include "DPSelection.h"
#include "hDraw.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXMU 5


class Systematic : public TObject {

public:

   Systematic( string datacardfile = "DataCard.txt");     
   ~Systematic();     
   
   void McDataCompare() ;

   void RunData( string dataName, int nSample = -1 ) ;
   void RunMC( string mcName, int nSample = -1, double weight = 1 ) ;
   void ComparePlot( TH1D* hData, TH1D* hMC, string plotName );

   void ShiftPeak( TH1D* h1, TH1D* h2 ) ;
   void WriteDataHisto() ;
   void WriteMcHisto() ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw;

   string hfolder  ;
   string plotType ;
   int    ProcessEvents ;
   int    SkipEvents ;
   // Root File for Rootuple or histograms
   //TFile *theFile ;
   //string hfName ;

   vector<double> timeCalib ;
   vector<double> normV ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;

   TH1D* h_dataTime  ;
   TH1D* h_dataTimeA  ;
   TH1D* h_dataMET       ;
   TH1D* h_mcTime  ;
   TH1D* h_mcTimeC  ;
   TH1D* h_mcTimeA  ;
   TH1D* h_mcMET   ;

   //ClassDef(Systematic, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Systematic);
#endif

