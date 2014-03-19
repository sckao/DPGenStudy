#ifndef HaloStudy_H
#define HaloStudy_H

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

class HaloStudy : public TObject {

public:

   HaloStudy( string datacardfile = "DataCard.txt");     
   ~HaloStudy();     
   
   void Create( TFile* hFile = NULL ) ;
   void Open( TFile* hFile = NULL ) ;
   void Write() ;
   void Run( vector<objID>& selectPho, vector<objID>& selectJets,  Rtuple& rt, double weight = 1. ) ;
   void DrawHistograms( hDraw* h_draw = NULL ) ;
   void GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) ;


   bool HaloTag( Rtuple& rt, int k ) ;
   static Double_t HaloFunction( Double_t* eta, Double_t* par ) ;
   void ABCD_Report() ;

   // Histograms set
   TH2D* haloTest_sMaj_sMin ;
   TH1D* haloTest_cscdPhi ;

   TH2D* haloCS_sMaj_sMin ;
   TH2D* haloCS_sMaj_Eta ;
   TH2D* haloCS_sMaj_Phi ;
   TH2D* haloCS_Eta_Time ;
   TH1D* haloCS_cscdPhi ;
   TH1D* haloCS_cscdPhi1 ;

   TH1D* haloAB_Pt_eta[4] ;
   TH1D* haloAB_MET_eta[4] ;
   TH1D* haloCD_Pt_eta[4] ;
   TH1D* haloCD_MET_eta[4] ;

   TH1D* halo_Eta[2] ;
   TH1D* sMaj_eta[7] ;
   TH1D* sMaj_eta_csc[7] ;
   
   TH2D* halo_Eta_Time ;
   TH2D* halo_Phi_Time ;
   TH2D* halo_Pt_Time ;
   TH2D* halo_MET_Time ;
   TH2D* halo_MET_Time_0J ;
   TH2D* halo_MET_Time_1J ;
   TH2D* halo_MET_Time_2J ;
   TH2D* halo_MET2_Time_0J ;
   TH2D* halo_MET2_Time_1J ;
   TH2D* halo_MET2_Time_2J ;
   TH2D* halo_sMin_Time ;
   TH2D* halo_sMaj_Time ;
   TH2D* halo_photIso_Time ;
   TH2D* halo_nHadIso_Time ;
   TH2D* halo_sMaj_sMin ;
   TH1D* halo_sigIeta ;
   TH1D* halo_Time ;
   TH2D* halo_sMaj_sigIeta ;
   TH2D* halo_sMin_sigIeta ;
   TH2D* halo_eta_rho ;
   TH2D* halo_eta_sMaj ;
   TH2D* halo_ecalT_rho ;
   TH1D* halo_nXtl ;
   TH1D* halo_swissX ;
   TH1D* halo_tChi2 ;

   TH2D* haloFN_Eta_Time ;
   TH2D* haloFN_Phi_Time ;
   TH2D* haloFN_Pt_Time ;
   TH2D* haloFN_MET_Time ;
   TH2D* haloFN_sMaj_sMin ;
   TH1D* haloFN_cscdPhi ;

   TH1D* noHalo_Time ;
   TH2D* noHalo_sMaj_Time ;
   TH2D* noHalo_sMin_Time ;
   TH1D* noHalo_nXtl_side ;
   TH1D* noHalo_nXtl_center ;
   TH1D* noHalo_tChi2 ;

   TH2D* halo_T_dPhi_gMET_0J ;
   TH2D* halo_T_dPhi_gMET_1J ;
   TH2D* halo_T_dPhi_gMET_2J ;

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int ProcessEvents ;
   int isData ;

   vector<double> photonCuts ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;
   vector<double> haloEff ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   bool createFile ;

   Rtuple tp ;
   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;


   //ClassDef(HaloStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(HaloStudy);
#endif

