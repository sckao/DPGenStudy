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
    TH1D* isoTime     ;
    TH1D* isoTime1    ;
    TH1D* obsTime1    ;
    TH1D* obsTime2    ;
    TH1D* aveObsTime  ;
    TH1D* aveObsTime1 ;

    TH2D* seedTime_Chi2  ;
    TH2D* ctbg_RZ0  ;
    TH2D* ctbg_RZ1  ;

    TH1D* xPhot_pt1 ;
    TH1D* xPhot_pt2 ;
    TH1D* xPhot_pt3 ;
    TH1D* xPhot_pt4 ;

    TH1D* h_matchRecoTime ;
    TH1D* h_matchGenTime  ;
    TH1D* h_matchTime     ;
    TH1D* h_genTime       ;
    TH1D* h_TimeRes0      ;
    TH1D* h_TimeRes1      ;
    TH1D* h_TimeRes2      ;
    TH1D* h_TimeRes3      ;
    TH1D* h_PtRes         ;

    TH1D* h_HoverE ;
    TH1D* h_sigIeta;
    TH1D* h_sigEta;
    TH1D* h_Time   ;
    TH1D* h_dT0   ;
    TH1D* simTime   ;
    TH1D* h_nChi2  ;
    TH1D* h_ctau   ;
    TH1D* sel_ctau   ;
    TH1D* acc_ctau   ;
    TH1D* h_ctbg   ;
    TH1D* sel_ctbg   ;
    TH1D* acc_ctbg   ;
    TH1D* h_ctbgT   ;
    TH1D* reco_ctbgT   ;
    TH1D* late_ctbgT   ;
    TH1D* lateR_ctbgT   ;
    TH1D* obs_ctbgT   ;
    TH1D* hlt_ctbgT   ;
    TH1D* sel_ctbgT   ;
    TH1D* acc_ctbgT   ;
    TH1D* h_xbeta  ;
    TH1D* reco_xbeta  ;
    TH1D* sel_xbeta  ;
    TH1D* h_lateXbeta  ;
    TH1D* h_lateXctau  ;
    TH1D* reco_xPt  ;
    TH1D* sel_xPt  ;
    TH2D* reco_xPt_ctbgT  ;
    TH2D* sel_xPt_ctbgT  ;
    TH1D* reco_gPt  ;
    TH1D* sel_gPt  ;
    TH1D* h_XPt  ;
    TH1D* h_lateXPt  ;
    TH1D* h_lateGPt  ;
    TH2D* dt1_dt2 ;
    TH2D* dt1_dt2_late ;
    TH2D* ctbgT_dPt ;

    TH1D* h_TrkIsoR  ;
    TH1D* h_HcalIsoR ;
    TH1D* h_EcalIsoR ;

    TH1D* h_cHadIso ;
    TH1D* h_nHadIso ;
    TH1D* h_photIso ;
    TH2D* h_cHadIso_t ;
    TH2D* h_nHadIso_t ;
    TH2D* h_photIso_t ;
    TH2D* h_gPt_time ;

    TH2D* h_sMaj_sMin ;
    TH2D* h_sMaj_sMin_late ;
    TH2D* h_photIso_nXtl ;
    TH2D* h_photIso_nBC ;

    TH1D* h_maxSwissEB ; 
    TH1D* h_maxSwissEE ; 
    TH1D* h_seedSwiss  ;
    TH1D* h_fSpike    ;
    TH1D* h_nXtals    ;
    TH1D* h_nBC       ;
    TH1D* h_sMin      ;

    TH2D* h_Pt_Eta   ;
    TH1D* h_Eta        ;
    TH1D* h_g1Pt       ;
    TH1D* h_met        ;
    TH1D* h_met1       ;
    TH1D* h_met2       ;
    TH1D* h_genMET     ; 
    TH1D* h_METRes     ; 
    TH1D* h_METdPhi    ; 
    TH1D* h_gen1RecoPt ;
    TH2D* h_XBR ;
    TH2D* m_nPhot ;
    TH2D* m2_nPhot ;
    TH2D* m1_nPhot ;
    TH2D* m0_nPhot ;
    TH2D* nPhot_g_r ;
    TH1D* failGen_Eta        ;
    TH1D* failGen_Pt       ;

    TH1D* h_nVtx       ;
    TH1D* h_nPhotons   ;
    TH1D* h_nGenPhotons; 
    TH1D* h_nJets      ; 
    TH1D* h_nMuons     ;
    TH1D* h_nElectrons ;

    TH2D* Gh_Eta_Time ;
    TH2D* Gh_Eta_Time1 ;
    TH2D* h_Eta_Time ;
    TH2D* h_Phi_Time ;
    TH2D* h_Pt_Time ;
    TH2D* h_sMaj_Time ;
    TH2D* h_sMin_Time ;
    TH2D* h_cscdPhi_Time ;
    TH2D* h_sigIeta_Time ;

    TH1D* pureTime ;
    TH1D* ghostTime ;

    TH1D* m_recoPhoTime ;
    TH1D* m_genPhoTime ;
    TH1D* m_xBeta ;
    TH1D* m_xPt ;

    TH1D* m_RecoPt ;
    TH1D* m_GenPt ;
    TH2D* m_sMaj_sMin ;

    TH1D* dR_GenReco ;
    TH2D* dR_Time ;
    TH2D* dR_XTime ;
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
    Histogram() ;

    ~Histogram() {
        
        //delete Input ;
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
    vector<double> TCut ;
    double FitCtau ;
    vector<double> fitRange ;

};

#endif
