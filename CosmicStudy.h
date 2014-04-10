#ifndef CosmicStudy_H
#define CosmicStudy_H

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

class CosmicStudy : public TObject {

public:

   CosmicStudy( string datacardfile = "DataCard.txt");     
   ~CosmicStudy();     
   
   void Create( TFile* hFile = NULL ) ;
   void Open( TFile* hFile = NULL ) ;
   void Write() ;
   void Run( vector<objID>& selectPho, vector<objID>& selectJets,  Rtuple& rt, double weight = 1. ) ;
   void DrawHistograms( hDraw* h_draw = NULL ) ;
   void GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) ;

   bool CosmicTag( Rtuple& rt, int k ) ;
   void ABCD_Report() ;

   // histograms
   TH1D* cosmic_tChi2 ;
   TH2D* cosmic_Eta_Time ;
   TH2D* cosmic_Phi_Time ;
   TH2D* cosmic_Pt_Time ;
   TH2D* cosmic_MET_Time ;
   TH2D* cosmic_MET_Time_0J ;
   TH2D* cosmic_MET_Time_1J ;
   TH2D* cosmic_MET_Time_2J ;
   TH2D* cosmic_MET2_Time_0J ;
   TH2D* cosmic_MET2_Time_1J ;
   TH2D* cosmic_MET2_Time_2J ;
   TH2D* cosmic_sMin_Time ;
   TH2D* cosmic_sMaj_Time ;
   TH2D* cosmic_photIso_Time ;
   TH2D* cosmic_sMaj_sMin ;
   TH2D* cosmic_seedE_photE ;
   TH1D* cosmic_Time ;
   TH1D* cosmic_nXtl ;

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
   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

   //ClassDef(CosmicStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(CosmicStudy);
#endif

