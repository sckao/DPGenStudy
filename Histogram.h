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

    TH2D* seedTime_Chi2  ;
    TH2D* Time_R  ; 
    TH2D* Time_Z  ;

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

    TH2D* h_Pt_Eta ;
    TH1D* h_Eta        ;
    TH1D* h_met        ;
    TH1D* h_g1Pt       ;
    TH1D* h_gen1Pt     ; 
    TH1D* h_genMET     ; 
    TH1D* h_METRes     ; 
    TH1D* h_METdPhi    ; 
    TH1D* h_gen1RecoPt ;

    TH1D* h_nVtx       ;
    TH1D* h_nPhotons   ;
    TH1D* h_nGenPhotons; 
    TH1D* h_nJets      ; 
    TH1D* h_nMuons     ;
    TH1D* h_nElectrons ;

    TH2D* Gh_rho_dT ;
    TH2D* Gh_rho_Time ;
    TH2D* Gh_Phi_Time ;
    TH2D* Gh_Eta_Time ;
    TH2D* Gh_Eta_Time1 ;
    TH2D* h_Eta_Time ;
    TH2D* h_Phi_Time ;
    TH2D* h_Pt_Time ;
    TH2D* h_sMaj_Time ;
    TH2D* h_sMin_Time ;
    TH2D* h_cscdPhi_Time ;
    TH2D* h_sigIeta_Time ;

    TH2D* h_RhoPhi_Halo ;
    TH1D* h_nHaloHits ;
    TH1D* h_nHaloTracks ;

    TH1D* pureTime ;
    TH1D* ghostTime ;

    TH2D* m_sigIeta_time ;
    TH2D* m_sMaj_sMin ;
    TH2D* m_sMaj_time ;
    TH2D* m_sMin_time ;
    TH2D* m_cHadIso_time ;
    TH2D* m_nHadIso_time ;
    TH2D* m_photIso_time ;

    TH1D* dR_GenReco ;
    TH2D* dR_Time ;
    TH2D* dR_XTime ;
    TH2D* dR_sigIeta ;
    TH2D* dR_sMaj ;
    TH2D* dR_sMin ;
    TH2D* dR_photIso ;
    TH2D* dR_nHadIso ;
    TH2D* dR_cHadIso ;
    TH2D* sMaj_sMin ;
    TH2D* XTime_genTime ;
 
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
    static Double_t HaloFunction( Double_t* eta, Double_t* par ) ;

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
