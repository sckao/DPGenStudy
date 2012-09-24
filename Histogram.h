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

    TH1D* SpikeEtaP      ;
    TH1D* SpikeEtaN      ;
    TH1D* Vz_P           ;
    TH1D* Vz_N           ;

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

    TH2D* h_Eta_Time ;
    TH2D* h_Phi_Time ;
    TH2D* h_Phi_Time1 ;

    TH2D* h_RhoPhi_Halo ;
    TH1D* h_nHaloHits ;
    TH1D* h_nHaloTracks ;
    TH2D* h_PhiTimeHalo ;
    TH2D* h_EtaTimeHalo ;
    TH2D* h_EtaTimeNoHalo ;
    TH1D* h_TimeNoHalo ;
    
    TH1D* h_SigEtaHalo ;
    TH1D* h_SigIetaHalo ;
    TH1D* h_SigEta ;
    TH1D* h_SigIeta ;

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
