#ifndef Background_H
#define Background_H

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
#include "DPSelection.h"

using namespace std;
#define MAXPHO 10
#define MAXVTX 10
#define MAXMU 5

class Background {

    public:

    //friend class TestGen ;
    Background( string datacardfile ) ;

    ~Background() ;
 
    void RunEstimation( string dataName );
    vector<double> GetComponent( int eta_i, int B12, int h_B12, int s_B12 ) ;
    void GetScale( int h_O12, int s_O12, int h_O34, int s_O34, double S12, double H12, double Q12, double sc_Q ) ;
    vector<double> GetScale( int O34[], int h_O34[], int s_O34[], int O12[], int h_O12[], int s_O12[] )  ; 
    void OpenHistograms() ;
    void KSTest( TH1D* h1, TH1D* h2, int minBin, int maxBin, double minX = 0. , double binWidth = 1. ) ;
    void SpikeShape() ;

    private:

    AnaInput*     Input ;
    DPSelection*  select;

    hDraw*        h_draw ;
    TFile*        hFile1 ;
    TFile*        hFile2 ;

    string hfolder  ;
    string plotType ;
    int isData ;
    int    ProcessEvents ;
    int    SkipEvents ;

    vector<objID> selectJets ;
    vector<objID> selectPho ;

    TH1D* TimeLT3Jets1    ;
    TH1D* TimeLT3Jets2    ;

};

#endif
