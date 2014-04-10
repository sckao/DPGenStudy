#ifndef BackgroundStudy_H
#define BackgroundStudy_H

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
#include <TH3.h>
#include <TFile.h>
#include <TString.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "DPSelection.h"
#include "hDraw.h"
#include "Rtuple.h"
#include "QCDStudy.h"
#include "HaloStudy.h"
#include "SpikeStudy.h"
#include "CosmicStudy.h"

class BackgroundStudy : public TObject {

public:

   BackgroundStudy( string datacardfile = "DataCard.txt");     
   ~BackgroundStudy();     
   
   //void init( string dataName = "") ;
   void Create() ;
   void Open( TFile* hFile = NULL ) ;
   void OpenAllHistograms() ;
   void CreateHistograms() ;
   void WriteDrawHistograms() ;
   void Write() ;

   void RawInfo( vector<objID>& selectPho, vector<objID>& selectJets, double weight = 1. ) ;
   void ControlStudy( vector<objID>& selectPho, vector<objID>& selectJets, double weight = 1. ) ;
   void SimpleRun( string dataName = "", double weight = 1. ) ;

   void DrawHistograms( hDraw* h_draw = NULL ) ;
   void DrawAllHistograms() ;
   // ABCD Method
   vector<double> ABCD_Collision( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD ) ;
   vector<double> ABCD( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD, TH3D* hE, TH3D* hF ) ;
   void ABCD_ABCD() ;
   double GetEstimation( TH3D* hCount, bool getQCD = true ) ;
   vector<double> GetComponent( int eta_i, double B12, double h_B12, double s_B12, double c_B12 ) ;
   vector<double> GetComponent( int eta_i, int B12,    int h_B12,    int s_B12,    int c_B12 ) ;

   TLorentzVector JetVectorSum( vector<objID>& jetV ) ;
   static Double_t HaloFunction( Double_t* eta, Double_t* par ) ;

   // Histograms set
   TH1D* obsTime ;
   TH1D* pure_Time ;

   TH1D* h_EB_Time ;
   TH1D* h_EB_Time0 ;
   TH1D* h_EB_Time1 ;
   TH1D* h_EB_Time2 ;
   TH1D* h_EE_Time ;
   TH1D* h_EE_Time0 ;
   TH1D* h_EE_Time1 ;
   TH1D* h_EE_Time2 ;
   TH1D* h_EE_haloTime ;

   TH2D* h_Eta_Phi ;
   TH2D* h_Eta_Time ;
   TH2D* h_Eta_Time1 ;
   TH2D* h_Eta_Time2 ;
   TH2D* h_Eta_Time3 ;
   TH2D* h_Eta_Time4 ;
   TH2D* h_Phi_Time ;
   TH2D* h_cscdPhi_Time ;
   TH2D* h_cscdPhi_cscTime ;
   TH2D* h_cscdPhi_rho ;
   TH2D* h_sMaj_Time_EB ;
   TH2D* h_sMaj_Time_EE ;
   TH2D* h_sMin_Time_EB ;
   TH2D* h_sMin_Time_EE ;
   TH2D* h_sMaj_sigIeta_EB ;
   TH2D* h_sMaj_sigIeta_EE ;
   TH2D* h_sMaj_sMin_EB ;
   TH2D* h_sMin_sigIeta_EB ;
   TH2D* h_sMin_sigIeta_EE ;
   TH2D* h_sigIeta_Time_EB ;
   TH2D* h_sigIeta_Time_EE ;
   TH2D* h_nXtl_Pt_EB  ;
   TH2D* h_Pt_MET ;
   TH2D* h_Pt_Time_EB ;
   TH2D* h_Pt_Time_EE ;
   TH2D* h_MET_Time_EB ;
   TH2D* h_MET_Time_EE ;
   TH2D* h_hltMET_Time_EB ;
   TH2D* h_hltMET_Time_EE ;
   TH2D* h_cHadIso_Time ;
   TH2D* h_nHadIso_Time ;
   TH2D* h_photIso_Time ;
   TH2D* h_seedE_Time ;
   TH2D* h_met_met1;
   TH2D* h_met_met2;
   TH1D* h_nPhoton ;

   TH2D* h_jet_phot_Time ;
   TH1D* h_jetTime ;
   TH1D* h_jetTimeErr ;
  
   TH1D* h_tChi2 ;
   TH1D* halo_tChi2 ;
   TH1D* spike_tChi2 ;
   TH1D* noHalo_tChi2 ;
   TH1D* cosmic_tChi2 ;
   TH1D* cs_tChi2 ;

   TH2D* h_nVtx_tChi2 ;
   TH1D* h_nVtx ;
   TH1D* h_pfMET ;
   TH1D* h_hltMET ;

   TH2D* h_sMaj_Eta  ;
   TH2D* h_sMaj_Phi  ;
   TH2D* h_sigIeta_sMaj_late ;
   TH2D* h_nXtl_Eta ;

   TH2D* sg_Eta_Time ;
   TH2D* sg_Phi_Time ;
   TH2D* sg_sigIeta_Time ;
   TH1D* sg_cscdPhi ;
   TH1D* sg_nXtl  ;
   TH2D* sg_nXtl_Eta  ;
   TH1D* sg_Time  ;
   TH1D* sg_Time_halo  ;
   TH1D* sg_Time_spike  ;
   TH1D* sg_Time_cosmic ;
   TH2D* sg_sMaj_Time ;
   TH2D* sg_sMaj_Eta ;
   TH2D* sg_sMin_Time ;
   TH2D* sg_sMin_Eta ;
   TH2D* sg_sMaj_sMin ;

   TH1D* sel_Time  ;
   TH2D* sel_weirdXtl ;
   TH2D* sel_Eta_Time ;
   TH2D* sel_Phi_Time ;
   TH2D* sel_sMaj_Time ;
   TH2D* sel_sMaj_Eta ;
   TH2D* sel_sMin_Time ;
   TH2D* sel_sMin_Eta ;
   TH2D* sel_cHadIso_Time ;
   TH2D* sel_nHadIso_Time ;
   TH2D* sel_photIso_Time ;
   TH2D* sel_photIso_sMaj ;
   TH2D* sel_photIso_sMin ;
   TH2D* sel_photIso_sigIeta ;
   
   TH2D* cs_Eta_Time ;
   TH2D* cs_Phi_Time ;
   TH2D* cs_sigIeta_Time ;
   TH1D* cs_cscdPhi ;
   TH1D* cs_nXtl  ;
   TH1D* cs_swissX  ;
   TH2D* cs_sMaj_sMin  ;
   TH2D* cs_cHadIso_Time ;
   TH2D* cs_nHadIso_Time ;
   TH2D* cs_photIso_Time ;
   TH2D* cs_dtdPhidEta ;
   TH2D* cs_seedE_photE ;

   TH2D* sideband_photIso_cscdPhi ;
   TH2D* sideband_sMin_Time ;
   TH2D* sideband_sMaj_Time ;
   TH2D* sideband_sMaj_Phi ;
   TH2D* sideband_sMaj_sMin ;
   TH2D* sideband_sMaj_Eta ;
   TH2D* sideband_nXtl_Eta ;
   TH2D* sideband_cscT_ecalT ;
   TH1D* sideband_cscdPhi_u ;
   TH1D* sideband_cscdPhi_d ;
   TH1D* sideband_sMaj ;
   TH1D* sideband_dtdR ;
   TH2D* sideband_dtdPhidEta ;
   TH2D* sideband_Pt_nJet ;

   TH2D* abcd_Pt_Time ;
   TH2D* abcd_MET_Time ;
   TH2D* abcd_MET2_Time ;
   TH2D* abcd_MET1_Time_sMET2 ;
   TH2D* abcd_MET1_Time_bMET2 ;
   TH2D* abcd_NJet_Time ;

   TH1D* nJets_center ;
   TH1D* nJets_halo ;
   TH1D* nJets_spike ;
   TH1D* nJets_cosmic ;

   TH1D* nHL_Eta ;
   TH1D* nSpk_Eta ;
   TH1D* nCS_Eta ;

   TH3D* hBg_F ;
   TH3D* hBg_E ;
   TH3D* hBg_D ;
   TH3D* hBg_C ;
   TH3D* hBg_B ;
   TH3D* hBg_A ;

   TH3D* hCol_F ;
   TH3D* hCol_E ;
   TH3D* hCol_D ;
   TH3D* hCol_C ;
   TH3D* hCol_B ;
   TH3D* hCol_A ;

   TH2D* sel_T_dPhi_gMET_1J ;
   TH2D* sel_T_dPhi_gMET_2J ;
   TH2D* sel_T_dPhi_gMET_3J ;
   TH2D* sg_dPhi_MET_csc ;
   TH2D* sg_dPhi_MET_Jet1 ;
   TH2D* sg_dPhi_MET_Jet2 ;
   TH2D* sg_dPhi_MET_Jet3 ;

   TH2D* sideband_dPhi_MET_csc ;
   TH2D* sideband_dPhi_MET_Jet1 ;
   TH2D* sideband_dPhi_MET_Jet2 ;
   TH2D* sideband_dPhi_MET_Jet3 ;

   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   QCDStudy*     qcdS;
   HaloStudy*    haloS;
   SpikeStudy*   spikeS;
   CosmicStudy*  cosmicS ; 

   hDraw* h_draw_ ;

   // Halo and Spike Efficiency 
   vector<double> haloEff ;
   vector<double> spikeEff ;
   vector<double> cosEff ;
   vector<double> haloMis ;
   vector<double> spikeMis ;
   vector<double> cosMis ;
   int useInFlight ;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int ProcessEvents ;
   int SkipEvents ;
   int isData ;
   int systType ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;
 
   vector<double> photonCuts ;
   vector<double> photonPFIso ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;

   // Root File for Rootuple or histograms
   TFile *theFile ;

   int totalN ;
   TTree* tr ;
   Rtuple rt ;

   

   //ClassDef(BackgroundStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(BackgroundStudy);
#endif

