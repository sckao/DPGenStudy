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
#include <TFile.h>
#include <TString.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "DPSelection.h"
#include "hDraw.h"

#define MAXPHO 10
#define MAXVTX 10
#define MAXGEN 20
#define MAXMU 5

class BackgroundStudy : public TObject {

public:

   BackgroundStudy( string datacardfile = "DataCard.txt");     
   ~BackgroundStudy();     
   
   //void Run( string dataName, double weight = 1. ) ;
   void init( string dataname = "") ;
   void Create() ;
   void Open() ;
   void Write() ;
   void Run( double weight = 1. ) ;
   void DrawHistograms() ;

   // ABCD Method
   void ABCD( TH2D* hA, TH2D* hB, TH2D* hC, TH2D* hD ) ;
   double GetEstimation( TH2D* hCount, bool getQCD = true ) ;
   vector<double> GetComponent( int eta_i, double B12, double h_B12, double s_B12, double c_B12 ) ;
   vector<double> GetComponent( int eta_i, int B12,    int h_B12,    int s_B12,    int c_B12 ) ;

   // Very naive ABCD Method
   double ABCD( TH1D* h_sg, TH1D* h_cs, double lowT = -3, double upT = 2 ) ;
   double GetQCDComponent( TH1D* h_qcd, TH1D* h_sg, double lowX = -2, double upX = 2 ) ;

   TLorentzVector JetVectorSum( vector<objID>& jetV ) ;
   static Double_t HaloFunction( Double_t* eta, Double_t* par ) ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw; 

   Double_t* haloEff ;
   Double_t* spikeEff ;
   Double_t* haloMis ;
   Double_t* spikeMis ;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int ProcessEvents ;
   int SkipEvents ;
   int isData ;

   int runId, lumiSection, eventId ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float sMinPho[MAXPHO], sMajPho[MAXPHO];
   float photIso[MAXPHO] , cHadIso[MAXPHO], nHadIso[MAXPHO], phoHoverE[MAXPHO] ;
   float fSpike[MAXPHO] ;
   int   nXtals[MAXPHO], nBC[MAXPHO] ;
   float sigmaEta[MAXPHO], sigmaIeta[MAXPHO], cscdPhi[MAXPHO], cscRho[MAXPHO], cscTime[MAXPHO] ;
   float dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX], vtxDx[MAXVTX], vtxDy[MAXVTX], vtxDz[MAXVTX] ;
   int nTrkZ0[34] ;

   float metPx, metPy, metE ;
   int   nPhotons, nJets, nMuons, nElectrons, triggered, nVertices, totalNVtx ;
   int   nHaloHits , nHaloTracks ;
   float haloPhi , haloRho ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;
 
   vector<double> photonCuts ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   bool writeHist ;

   int totalN ;
   TTree* tr ;
   TChain* tr1 ;

   // Histograms set
   TH1D* obsTime ;

   TH1D* h_EB_Time ;
   TH1D* h_EB_Time0 ;
   TH1D* h_EB_Time1 ;
   TH1D* h_EB_Time2 ;
   TH1D* h_EE_Time ;
   TH1D* h_EE_Time0 ;
   TH1D* h_EE_Time1 ;
   TH1D* h_EE_Time2 ;

   TH1D* h_Time_EB ;
   TH1D* h_Time_EE ;
   TH1D* h_haloTime_EE ;

   TH2D* h_Eta_Time ;
   TH2D* h_Phi_Time ;
   TH2D* h_cscdPhi_Time ;
   TH2D* h_ecalT_cscT ;
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
   TH2D* h_cHadIso_Time ;
   TH2D* h_nHadIso_Time ;
   TH2D* h_photIso_Time ;
   TH2D* h_Time_nZ0 ;
   TH1D* a_Z0 ;
   TH1D* b_Z0 ;
   TH1D* c_Z0 ;
   TH1D* d_Z0 ;
   TH1D* h_Z0 ;

   TH1D* a_nVtx ;
   TH1D* b_nVtx ;
   TH1D* c_nVtx ;
   TH1D* d_nVtx ;
   TH1D* h_nVtx ;
   TH1D* l_nVtx ;

   TH2D* h_sMaj_Eta  ;
   TH2D* h_sMaj_Phi  ;
   TH2D* h_sigIeta_sMaj_late ;
   TH2D* h_nXtl_Eta ;

   TH2D* sg_Eta_Time ;
   TH2D* sg_Eta_Time_halo ;
   TH2D* sg_Eta_Time_spike ;
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
   TH2D* sg_sMaj_sigIeta ;
   TH2D* sg_sMin_sigIeta ;
   TH2D* sg_sMaj_sMin ;
   //TH1D* sg_gg_dR ;

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
   TH2D* cs_sMaj_sMin  ;
   TH2D* cs_cHadIso_Time ;
   TH2D* cs_nHadIso_Time ;
   TH2D* cs_photIso_Time ;
   TH2D* cs_dtdPhidEta ;

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
   TH1D* sideband_nXtl_u ;
   TH1D* sideband_nXtl_d ;
   TH1D* sideband_sMaj ;
   TH1D* sideband_dtdR ;
   TH2D* sideband_dtdPhidEta ;
   TH2D* sideband_Pt_nJet ;

   TH1D* sideband_nVtx_0J ;
   TH1D* sideband_nVtx_1J ;
   TH1D* sideband_nVtx_2J ;
   TH1D* noG_nVtx_0J ;
   TH1D* noG_nVtx_1J ;
   TH1D* noG_nVtx_2J ;

   TH2D* bg_Eta_Time ;

   TH2D* abcd_Pt_Time ;
   TH2D* abcd_MET_Time ;
   TH2D* abcd_NJet_Time ;
   TH2D* ab_Pt_MET ;
   TH2D* cd_Pt_MET ;
   TH1D* ab_dPhi_gMET ;
   TH1D* cd_dPhi_gMET ;
  
   TH2D* haloTest_sMaj_sMin ;
   TH1D* haloTest_cscdPhi ;

   TH2D* haloCS_sMaj_sMin ;
   TH2D* haloCS_sMaj_Eta ;
   TH2D* haloCS_sMaj_Phi ;
   TH2D* haloCS_Eta_Time ;
   TH2D* haloCS_Eta_Time1 ;
   TH1D* haloCS_cscdPhi ;
   TH1D* haloCS_cscdPhi1 ;

   TH1D* haloAB_Pt_eta[4] ;
   TH1D* haloAB_MET_eta[4] ;
   TH1D* haloCD_Pt_eta[4] ;
   TH1D* haloCD_MET_eta[4] ;

   TH2D* spikeCS_Eta_Time1 ;
   TH2D* spikeCS_Eta_Time ;
   TH2D* spikeCS_nXtl_Eta ;
   TH2D* spikeCS_Phi_Time ;
   TH2D* spikeCS_sMaj_sMin ;
   TH1D* spikeCS_nXtl ;

   TH1D* halo_Eta[2] ;
   TH1D* spike_Eta[2] ;
   TH1D* sMaj_eta[7] ;
   TH1D* sMaj_eta_csc[7] ;

   TH2D* cosmic_Eta_Time ;
   TH2D* cosmic_Phi_Time ;
   TH2D* cosmic_Pt_Time ;
   TH2D* cosmic_MET_Time ;
   TH2D* cosmic_sMin_Time ;
   TH2D* cosmic_sMaj_Time ;
   TH2D* cosmic_photIso_Time ;
   TH2D* cosmic_sMaj_sMin ;
   TH1D* cosmic_sigIeta ;
   TH1D* cosmic_Time ;
   TH1D* cosmic_nXtl ;

   TH2D* halo_Eta_Time ;
   TH2D* halo_Eta_Time_1J ;
   TH2D* halo_Eta_Time_0J ;
   TH2D* halo_Phi_Time ;
   TH2D* halo_Pt_Time ;
   TH2D* halo_MET_Time ;
   TH2D* halo_sMin_Time ;
   TH2D* halo_sMaj_Time ;
   TH2D* halo_photIso_Time ;
   TH2D* halo_sMaj_sMin ;
   TH1D* halo_sigIeta ;
   TH1D* halo_Time ;
   TH2D* halo_sMaj_sigIeta ;
   TH2D* halo_sMin_sigIeta ;
   TH2D* halo_eta_rho ;
   TH2D* halo_eta_sMaj ;
   TH2D* halo_ecalT_rho ;
   TH2D* halo_ecalT_cscT ;

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

   TH2D* spike_Eta_Time ;
   TH2D* spike_Phi_Time ;
   TH2D* spike_Pt_Time ;
   TH2D* spike_MET_Time ;
   TH2D* spike_sMaj_sMin ;
   TH2D* spike_sMaj_Time ;
   TH2D* spike_sMin_Time ;
   TH2D* spike_photIso_Time ;
   TH1D* spike_sigIeta ;
   TH1D* spike_Time ;
   TH2D* spike_sMaj_sigIeta ;
   TH2D* spike_sMin_sigIeta ;
   TH2D* noSpike_sMaj_Time ;
   TH2D* noSpike_sMin_Time ;
   TH1D* noSpike_Time ;

   TH1D* notSpike_nXtl ;

   TH1D* pure_Time ;

   TH1D* nJets_center ;
   TH1D* nJets_halo ;
   TH1D* nJets_spike ;
   TH1D* nJets_cosmic ;

   TH1D* nHL_Eta ;
   TH1D* nSpk_Eta ;
   TH1D* nCS_Eta ;

   TH2D* hBg_D ;
   TH2D* hBg_C ;
   TH2D* hBg_B ;
   TH2D* hBg_A ;

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

   TH2D* halo_T_dPhi_gMET_0J ;
   TH2D* halo_T_dPhi_gMET_1J ;
   TH2D* halo_T_dPhi_gMET_2J ;

   TH2D* spike_T_dPhi_gMET_0J ;
   TH2D* spike_T_dPhi_gMET_1J ;
   TH2D* spike_T_dPhi_gMET_2J ;


   //ClassDef(BackgroundStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(BackgroundStudy);
#endif

