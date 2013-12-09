#ifndef QCDStudy_H
#define QCDStudy_H

#include <TObject.h>
#include <TSystem.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TString.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "hDraw.h"
#include "Rtuple.h"

class QCDStudy : public TObject {

public:

   QCDStudy( string datacardfile = "DataCard.txt");     
   ~QCDStudy();     
   
   void Create( TFile* hFile = NULL ) ;
   void Open() ;
   void Write() ;
   void Run( vector<objID>& selectPho, vector<objID>& selectJets,  Rtuple& rt, double weight = 1. ) ;
   void DrawHistograms( hDraw* h_draw = NULL ) ;
   bool MIBTag( Rtuple& rt, int k ) ;
   void ABCD_Report() ;

   // histograms

   TH2D* qcd_MET_Time_0J ;
   TH2D* qcd_MET_Time_1J ;
   TH2D* qcd_MET_Time_2J ;
   TH2D* qcd_dPhi_gMET_Time ;

   TH2D* qcd_MET0_Time ;
   TH2D* qcd_MET1_Time ;
   TH2D* qcd_MET2_Time ;
   TH2D* qcd_photIso_Time ;
   TH2D* qcd_nHadIso_Time ;
   TH2D* qcd_cHadIso_Time ;

   TH2D* qcd_Eta_Time ;
   TH2D* qcd_Phi_Time ;
   TH2D* qcd_Pt_Time ;
   TH1D* qcd_Time ;
   TH1D* qcd_Time1 ;
   TH1D* qcd_tChi2 ;
   TH1D* qcd_nXtl ;
   TH2D* qcd_sMaj_sMin ;

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int isData ;

   vector<double> photonCuts ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   bool createFile ;

   Rtuple tp ;


   //ClassDef(QCDStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(QCDStudy);
#endif

