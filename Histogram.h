#ifndef Histogram_H
#define Histogram_H

#include <TObject.h>
#include <TMath.h>
#include <TString.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TSystem.h>

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "hDraw.h"
#include "AnaInput.h"

using namespace std;

struct hSet {

    TH1D* obsTime     ;
    TH1D* aveObsTime  ;
    TH1D* aveObsTime1 ;
    TH1D* aveObsTime2 ;
    TH1D* obsEBTimeErr  ;
    TH1D* obsEETimeErr  ;
    TH1D* aveObsEBTimeErr ;
    TH1D* aveObsEETimeErr ;
    TH1D* aveObsEBTimeErr1 ;
    TH1D* aveObsEETimeErr1 ;

    TH2D* seedTime_Chi2  ;
    TH2D* Time_R  ; 
    TH2D* Time_Z  ;

    TH1D* badPhoTime     ;
    TH1D* TimeLT3Jets    ;
    TH1D* TimeGE3Jets    ;
    TH1D* TimeLowMET     ;
    TH1D* TimeBigMET     ;

    TH1D* h_matchRecoTime ;
    TH1D* h_matchGenTime  ;
    TH1D* h_matchTime     ;
    TH1D* h_genTime       ;
    TH1D* h_TimeRes1      ;
    TH1D* h_TimeRes2      ;
    TH1D* h_TimeRes3      ;
    TH1D* h_aTimeRes1     ;
    TH1D* h_aTimeRes2     ;
    TH1D* h_aTimeRes3     ;
    TH1D* h_PtRes         ;

    TH1D* h_HoverE ;
    TH1D* h_sigIeta;
    TH1D* h_sigEta;
    TH1D* h_Time   ;
    TH1D* h_nChi2  ;
    TH1D* h_ctau   ;
    TH1D* h_xbeta  ;
    TH1D* h_TrkIso   ;
    TH1D* h_HcalIso  ;
    TH1D* h_EcalIso  ;
    TH1D* h_TrkIsoR  ;
    TH1D* h_HcalIsoR ;
    TH1D* h_EcalIsoR ;

    TH1D* h_cHadIso ;
    TH1D* h_nHadIso ;
    TH1D* h_photIso ;
    TH2D* h_cHadIso_t ;
    TH2D* h_nHadIso_t ;
    TH2D* h_photIso_t ;

    TH1D* h_maxSwissEB ; 
    TH1D* h_maxSwissEE ; 
    TH1D* h_seedSwiss  ;
    TH1D* h_fSpike    ;
    TH1D* h_nXtals    ;
    TH1D* h_nBC       ;
    TH1D* h_sMin      ;

    TH1D* h_met        ;
    TH1D* h_g1Pt       ;
    TH1D* h_gen1Pt     ; 
    TH1D* h_gen1RecoPt ;

    TH1D* h_nVtx       ;
    TH1D* h_nPhotons   ;
    TH1D* h_nGenPhotons; 
    TH1D* h_nJets      ; 
    TH1D* h_nMuons     ;
    TH1D* h_nElectrons ;

    TH2D* h_nXtl_Eta ;
    TH2D* h_nXtl_Pt  ;
    TH2D* h_Eta_Time ;
    TH2D* h_Phi_Time ;
    TH2D* h_sMaj_Time ;
    TH2D* h_sMin_Time ;
    TH2D* h_sMaj_Eta  ;
    TH2D* h_sMaj_Phi  ;
    TH2D* h_sMaj_sMin ;
    TH2D* h_cscdPhi_Time ;
    TH2D* h_sigIeta_Time ;
    TH2D* h_sigIeta_Time1 ;
    TH2D* h_sigEta_sMaj ;
    TH2D* h_sigEta_sMaj_late ;
    TH2D* h_HoverE_Time ;

    TH2D* h_RhoPhi_Halo ;
    TH1D* h_nHaloHits ;
    TH1D* h_nHaloTracks ;

    TH1D* spike_sigEta ;
    TH1D* spike_sigIeta ;
    TH1D* spike_Time ;
    TH2D* spike_Eta_Time ;
    TH2D* spike_Phi_Time ;
    TH2D* spike_sMaj_sMin ;
    TH2D* spike_sMaj_Time ;
    TH2D* spike_sMin_Time ;

    TH1D* noSpike_sigEta ;
    TH1D* noSpike_sigIeta ;
    TH1D* noSpike_Time ;
    TH2D* noSpike_Phi_Time ;
    TH2D* noSpike_Eta_Time ;
    TH2D* noSpike_sMaj_sMin ;
    TH2D* noSpike_sMaj_Time ;
    TH2D* noSpike_sMin_Time ;

    TH1D* halo_sigEta ;
    TH1D* halo_sigIeta ;
    TH1D* halo_Time ;
    TH2D* halo_Eta_Time ;
    TH2D* halo_Phi_Time ;
    TH2D* halo_sMaj_sMin ;
    TH2D* halo_sMaj_Time ;
    TH2D* halo_sMin_Time ;

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
    
    TH1D* sideband_cscdPhi_EB ;
    TH1D* sideband_sMaj_EB ;
    TH1D* sideband_cscdPhi_EE ;
    TH1D* sideband_sMaj_EE ;
    TH2D* sideband_sMaj_Time ;
    TH2D* sideband_sMaj_Phi ;
    TH2D* sideband_sMaj_sMin ;
    TH2D* sideband_sMaj_Eta ;
    TH2D* sideband_nXtl_Eta ;
    TH1D* sideband_nXtl ;

    TH2D* gjCS_sMaj_Eta ;
    TH2D* gjCS_nXtl_Eta ;

    TH1D* sMaj_eta[7] ;
    TH1D* sMaj_eta_csc[7] ;
    TH1D* notSpike_nXtl ;

    TH1D* haloCS_cscdPhi ;
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

    TH2D* ghostCS_Eta_Time1 ;
    TH2D* ghostCS_Eta_Time ;
    TH2D* ghostCS_Phi_Time ;
    TH2D* ghostCS_sMaj_sMin ;
    TH2D* ghostCS_sMaj_Eta ;

    TH1D* ghost_Time ;
    TH2D* ghost_Eta_Time ;
    TH2D* ghost_Phi_Time ;
    TH2D* ghost_sMaj_sMin ;
    TH1D* pure_Time ;
    TH2D* pure_Eta_Time ;
    TH2D* pure_Phi_Time ;
    TH2D* pure_sMaj_sMin ;

    TH1D* nHL_Eta ;
    TH1D* nSpk_Eta ;
    TH1D* nGhS_Eta ;
    TH1D* nCS_Eta ;
} ;

class Histogram {

    public:

    //friend class TestGen ;
    Histogram( string datacardfile ) ;

    ~Histogram() {
        
        delete Input ;
        delete h_draw ;
        //hFile->Close() ;
        cout<<" exit histogram "<<endl ;
    }

    void Init( hSet& hs_ ) ;
    void Open( ) ;
    void DrawHistograms() ;
    void Write( string theFolder , TFile* file  ) ;

    private:

    AnaInput*     Input ;
    hDraw*        h_draw ;
    TFile*        hFile ;
    hSet          h ;
 
    string hfolder  ;
    string plotType ;
    string hfName ;
    int isData ;
    double TCut ;
    double FitCtau ;

};

#endif
