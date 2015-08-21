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
   void Open( TFile* hFile = NULL ) ;
   void Write() ;
   void Run( vector<objID>& selectPho, vector<objID>& selectJets,  Rtuple& rt, double weight = 1. ) ;
   void DrawHistograms( hDraw* h_draw = NULL ) ;
   void GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) ;

   bool MIBTag( Rtuple& rt, int k ) ;
   void ABCD_Report() ;

   // histograms

   TH2D* qcd_corMET_Time ;
   TH2D* qcd_orgMET_Time ;
   TH2D* qcd_MET_Time_0J ;
   TH2D* qcd_MET_Time_1J ;
   TH2D* qcd_MET_Time_2J ;
   TH2D* qcd_MET2_Time_0J ;
   TH2D* qcd_MET2_Time_1J ;
   TH2D* qcd_MET2_Time_2J ;
   TH2D* qcd_dPhi_gMET_Time ;
   TH2D* qcd_dPhi_gMET2_Time ;

   TH2D* qcd_MET0_Time ;
   TH2D* qcd_MET2_Time ;
   TH2D* qcd_photIso_Time ;
   TH2D* qcd_nHadIso_Time ;
   TH2D* qcd_cHadIso_Time ;

   TH2D* qcd_HcalIso_Time ;
   TH2D* qcd_EcalIso_Time ;
   TH2D* qcd_TrkIso_Time ;

   TH2D* qcd_Eta_Time ;
   TH2D* qcd_Phi_Time ;
   TH2D* qcd_Pt_Time ;
   TH1D* qcd_Time ;
   TH1D* qcd_Time1 ;
   TH1D* qcd_tChi2 ;
   TH1D* qcd_nXtl ;
   TH1D* qcd_dT ;
   TH1D* qcd_dT_off ;
   TH1D* qcd_dT_in ;
   TH2D* qcd_sMaj_sMin ;

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int isData ;

   vector<double> photonCuts ;
   vector<double> photonIso ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   bool createFile ;

   Rtuple tp ;
   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

   //ClassDef(QCDStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(QCDStudy);
#endif

