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

using namespace std;

class Background {

    public:

    //friend class TestGen ;
    Background( string datacardfile ) ;

    ~Background() ;

    void OpenHistograms() ;
    void KSTest( TH1D* h1, TH1D* h2, int minBin, int maxBin, double minX = 0. , double binWidth = 1. ) ;
    void SpikeShape() ;

    private:

    AnaInput*     Input ;
    hDraw*        h_draw ;
    TFile*        hFile1 ;
    TFile*        hFile2 ;

    string hfolder  ;
    string plotType ;
    int isData ;

    TH1D* TimeLT3Jets1    ;
    TH1D* TimeLT3Jets2    ;

};

#endif
