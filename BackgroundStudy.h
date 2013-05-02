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

   double ABCD( TH1D* h_sg, TH1D* h_cs, double lowT = -3, double upT = 2 ) ;
   void ABCD( TH2D* hA, TH2D* hB, TH2D* hC, TH2D* hD ) ;

   double GetEstimation( TH2D* hCount ) ;
   double GetQCDComponent( TH1D* h_qcd, TH1D* h_sg, double lowX = -2, double upX = 2 ) ;
   vector<double> GetComponent( int eta_i, double B12, double h_B12, double s_B12 ) ;
   vector<double> GetComponent( int eta_i, int B12, int h_B12, int s_B12 ) ;

private:

   AnaInput*     Input;
   DPSelection*  select;
   hDraw*        h_draw; 

   int s_Count[5] ;
   int h_Count[5] ;
   int B_Count[5] ;

   int st_Count[5] ;
   int ht_Count[5] ;
   int Bt_Count[5] ;

   int sm_Count[5] ;
   int hm_Count[5] ;
   int Bm_Count[5] ;

   int sa_Count[5] ;
   int ha_Count[5] ;
   int Ba_Count[5] ;

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
   float sigmaEta[MAXPHO], sigmaIeta[MAXPHO], cscdPhi[MAXPHO] ;
   float vtxX[MAXVTX], vtxY[MAXVTX], vtxZ[MAXVTX] ;

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
   TH1D* h_EB_Time3 ;
   TH1D* h_EE_Time ;
   TH1D* h_EE_Time0 ;
   TH1D* h_EE_Time1 ;
   TH1D* h_EE_Time2 ;
   TH1D* h_EE_Time3 ;

   TH2D* h_Eta_Time ;
   TH2D* h_Phi_Time ;
   TH2D* h_cscdPhi_Time ;
   TH2D* h_sMaj_Time_EB ;
   TH2D* h_sMaj_Time_EE ;
   TH2D* h_sMin_Time_EB ;
   TH2D* h_sMin_Time_EE ;
   TH2D* h_sigIeta_Time_EB ;
   TH2D* h_sigIeta_Time_EE ;
   TH2D* h_Pt_Time_EB ;
   TH2D* h_Pt_Time_EE ;
   TH2D* h_MET_Time_EB ;
   TH2D* h_MET_Time_EE ;
   TH2D* h_cHadIso_Time ;
   TH2D* h_nHadIso_Time ;
   TH2D* h_photIso_Time ;

   TH2D* h_sMaj_Eta  ;
   TH2D* h_sMaj_Phi  ;
   TH2D* h_sMaj_sMin ;
   TH2D* h_sigEta_sMaj ;
   TH2D* h_sigEta_sMaj_late ;
   TH2D* h_nXtl_Eta ;
   TH2D* h_nXtl_Pt  ;

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
   TH2D* sg_cHadIso_Time ;
   TH2D* sg_nHadIso_Time ;
   TH2D* sg_photIso_Time ;
   TH2D* sg_photIso_sMaj ;
   TH2D* sg_photIso_sMin ;
   TH2D* sg_photIso_sigIeta ;
   TH2D* sg_sMaj_Time ;
   TH2D* sg_sMaj_Eta ;
   TH2D* sg_sMin_Time ;
   TH2D* sg_sMin_Eta ;
   //TH1D* sg_gg_dR ;

   TH1D* sel_Time  ;
   TH2D* sel_Eta_Time ;
   TH2D* sel_Phi_Time ;
   TH2D* sel_sMaj_Time ;
   TH2D* sel_sMaj_Eta ;
   TH2D* sel_sMin_Time ;
   TH2D* sel_sMin_Eta ;
   
   TH2D* cs_Eta_Time ;
   TH2D* cs_Phi_Time ;
   TH2D* cs_sigIeta_Time ;
   TH1D* cs_cscdPhi ;
   TH1D* cs_nXtl  ;
   TH2D* cs_nXtl_Eta  ;
   TH2D* cs_cHadIso_Time ;
   TH2D* cs_nHadIso_Time ;
   TH2D* cs_photIso_Time ;

   TH2D* sideband_photIso_cscdPhi ;
   TH2D* sideband_sMaj_Time ;
   TH2D* sideband_sMaj_Phi ;
   TH2D* sideband_sMaj_sMin ;
   TH2D* sideband_sMaj_Eta ;
   TH2D* sideband_nXtl_Eta ;
   TH1D* sideband_cscdPhi ;
   TH1D* sideband_nXtl ;
   TH1D* sideband_sMaj ;
   TH1D* sideband_cscdPhi_a3 ;
   TH1D* sideband_cscdPhi_b3 ;
   TH1D* sideband_cscdPhi_c2 ;

   TH2D* bg_Eta_Time ;

   TH1D* qcdCS_Time ;
   TH2D* qcdCS_Eta_Time ;

   TH1D* haloCS_nXtl_a3 ;
   TH1D* haloCS_nXtl_b3 ;
   TH1D* haloCS_nXtl_c2 ;
   TH1D* spikeCS_nXtl_a3 ;
   TH1D* spikeCS_nXtl_b3 ;
   TH1D* spikeCS_nXtl_c2 ;

   TH2D* haloCS_sMaj_Eta ;
   TH2D* haloCS_sMaj_Phi ;
   TH2D* haloCS_Eta_Time ;
   TH2D* haloCS_Eta_Time1 ;

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

   TH2D* halo_Eta_Time ;
   TH2D* halo_Phi_Time ;
   TH2D* halo_sMin_Time ;
   TH2D* halo_sMaj_Time ;
   TH2D* halo_photIso_Time ;
   TH2D* halo_sMaj_sMin ;
   TH1D* halo_sigEta ;
   TH1D* halo_sigIeta ;
   TH1D* halo_Time ;

   TH1D* noHalo_sigEta ;
   TH1D* noHalo_sigIeta ;
   TH1D* noHalo_Time ;
   TH2D* noHalo_Phi_Time ;
   TH2D* noHalo_Eta_Time ;
   TH2D* noHalo_sMaj_sMin ;
   TH2D* noHalo_sMaj_Time ;
   TH2D* noHalo_sMin_Time ;

   TH1D* noHalo_nXtl_side ;
   TH1D* noHalo_nXtl_center ;

   TH2D* spike_Eta_Time ;
   TH2D* spike_Phi_Time ;
   TH2D* spike_sMaj_sMin ;
   TH2D* spike_sMaj_Time ;
   TH2D* spike_sMin_Time ;
   TH2D* spike_photIso_Time ;
   TH1D* spike_sigEta ;
   TH1D* spike_sigIeta ;
   TH1D* spike_Time ;

   TH2D* noSpike_Phi_Time ;
   TH2D* noSpike_Eta_Time ;
   TH2D* noSpike_sMaj_sMin ;
   TH2D* noSpike_sMaj_Time ;
   TH2D* noSpike_sMin_Time ;
   TH1D* noSpike_sigEta ;
   TH1D* noSpike_sigIeta ;
   TH1D* noSpike_Time ;

   TH1D* notSpike_nXtl ;

   TH1D* pure_Time ;
   TH2D* pure_Eta_Time ;
   TH2D* pure_Phi_Time ;
   TH2D* pure_sMaj_sMin ;

   TH1D* nHL_Eta ;
   TH1D* nSpk_Eta ;
   TH1D* nCS_Eta ;

   TH2D* hBg_sg ;
   TH2D* hBg_m ;
   TH2D* hBg_t ;
   TH2D* hBg_mt ;

   //ClassDef(BackgroundStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(BackgroundStudy);
#endif

