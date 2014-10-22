#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
// This is the histogram plotter for GenAna.cc

double effA[300] = {

 0.00883, 0.00202, 0.00007, 0.00006, 0.00016, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07921, 0.03803, 0.01314, 0.00590, 0.00175, 0.00158, 0.00160, 0.00000, 0.00076, 0.00042, 0.00023, 0.00134, 0.00000, 0.00000, 0.00000,
 0.06286, 0.07152, 0.04148, 0.02171, 0.01337, 0.00527, 0.00371, 0.00405, 0.00239, 0.00176, 0.00000, 0.00186, 0.00169, 0.00000, 0.00000,
 0.08642, 0.11777, 0.08223, 0.05737, 0.04098, 0.02742, 0.01214, 0.00746, 0.00863, 0.00791, 0.00524, 0.00557, 0.00180, 0.00000, 0.00128,
 0.15094, 0.12662, 0.11846, 0.10376, 0.06917, 0.06004, 0.02487, 0.01679, 0.01541, 0.01248, 0.00621, 0.00681, 0.00276, 0.00000, 0.00000,
 0.20513, 0.13992, 0.16803, 0.15035, 0.13655, 0.09185, 0.07235, 0.02441, 0.01782, 0.00349, 0.00275, 0.00181, 0.00000, 0.00000, 0.00000,
 0.17857, 0.17857, 0.16817, 0.19282, 0.14246, 0.11058, 0.08717, 0.06250, 0.02199, 0.00717, 0.00789, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20000, 0.14400, 0.15884, 0.16745, 0.18861, 0.14891, 0.12462, 0.09236, 0.05870, 0.01333, 0.01010, 0.00000, 0.00000, 0.00000, 0.00000,
 0.16667, 0.15455, 0.10599, 0.13580, 0.17279, 0.15584, 0.12842, 0.06301, 0.06867, 0.01754, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.10526, 0.19355, 0.13125, 0.14610, 0.20117, 0.16566, 0.11816, 0.07538, 0.04000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.23077, 0.15556, 0.21212, 0.15909, 0.17407, 0.17176, 0.16749, 0.07792, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.06667, 0.24390, 0.19835, 0.14368, 0.11538, 0.11834, 0.08271, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.20930, 0.13043, 0.12057, 0.09655, 0.07576, 0.09375, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.21875, 0.21687, 0.16541, 0.12687, 0.07317, 0.50000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.30769, 0.12903, 0.12963, 0.06173, 0.05882, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.22222, 0.10417, 0.08696, 0.12698, 0.28571, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.07143, 0.12500, 0.12727, 0.12500, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.06250, 0.20513, 0.08108, 0.14286, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.25000, 0.33333, 0.16216, 0.02778, 0.20000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.10000, 0.11034, 0.13158, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000
} ;

double err_u[300] = {
 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.01400, 0.00500, 0.00200, 0.00100, 0.00100, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000,
 0.02000, 0.00800, 0.00500, 0.00300, 0.00200, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100, 0.00100, 0.00100, 0.00000,
 0.03400, 0.01500, 0.00900, 0.00600, 0.00500, 0.00400, 0.00300, 0.00200, 0.00200, 0.00200, 0.00200, 0.00200, 0.00100, 0.00000, 0.00200,
 0.05300, 0.01900, 0.01300, 0.01000, 0.00700, 0.00600, 0.00400, 0.00400, 0.00300, 0.00300, 0.00200, 0.00300, 0.00200, 0.00100, 0.00200,
 0.06800, 0.02200, 0.01700, 0.01400, 0.01100, 0.00900, 0.00700, 0.00400, 0.00400, 0.00300, 0.00200, 0.00300, 0.00200, 0.00400, 0.01100,
 0.07800, 0.03000, 0.02100, 0.01700, 0.01300, 0.01100, 0.01000, 0.00800, 0.00400, 0.00300, 0.00300, 0.00400, 0.01500, 0.20400, 0.00000,
 0.09500, 0.03300, 0.02200, 0.01800, 0.01600, 0.01400, 0.01300, 0.01200, 0.01100, 0.00600, 0.02100, 0.11800, 0.00000, 0.00000, 0.00000,
 0.08300, 0.03600, 0.02200, 0.02000, 0.01800, 0.01700, 0.01500, 0.01300, 0.01800, 0.02400, 0.21200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.08300, 0.05300, 0.02800, 0.02100, 0.02200, 0.02100, 0.01800, 0.02000, 0.03500, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.12200, 0.05800, 0.03600, 0.02500, 0.02400, 0.02400, 0.02700, 0.03400, 0.31700, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.08400, 0.06900, 0.03800, 0.02800, 0.02200, 0.02600, 0.02500, 0.15600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.09800, 0.06500, 0.03700, 0.02900, 0.02600, 0.02500, 0.05900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.11800, 0.07600, 0.04700, 0.03400, 0.03000, 0.03200, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.15000, 0.09200, 0.04600, 0.03400, 0.03000, 0.05000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.31700, 0.08400, 0.04900, 0.04700, 0.04500, 0.16800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20400, 0.09000, 0.05200, 0.04900, 0.04800, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20400, 0.08000, 0.06800, 0.05200, 0.15300, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.21200, 0.18200, 0.06500, 0.03800, 0.18900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07700, 0.03600, 0.02700, 0.04200, 0.21200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000
} ;

double err_d[300] = {
 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.01200, 0.00400, 0.00200, 0.00100, 0.00100, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00100, 0.00000, 0.00000, 0.00000,
 0.01600, 0.00800, 0.00500, 0.00300, 0.00200, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100, 0.00100, 0.00100, 0.00000,
 0.02800, 0.01400, 0.00800, 0.00600, 0.00400, 0.00300, 0.00200, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100,
 0.04400, 0.01800, 0.01200, 0.00900, 0.00700, 0.00600, 0.00300, 0.00300, 0.00300, 0.00200, 0.00200, 0.00300, 0.00200, 0.00000, 0.00000,
 0.05800, 0.02100, 0.01700, 0.01300, 0.01000, 0.00900, 0.00600, 0.00400, 0.00400, 0.00200, 0.00100, 0.00200, 0.00000, 0.00000, 0.00000,
 0.06300, 0.02800, 0.01900, 0.01700, 0.01300, 0.01100, 0.00900, 0.00800, 0.00400, 0.00300, 0.00200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07700, 0.02900, 0.02100, 0.01800, 0.01600, 0.01300, 0.01200, 0.01100, 0.01000, 0.00400, 0.01400, 0.00000, 0.00000, 0.00000, 0.00000,
 0.06500, 0.03200, 0.01900, 0.01800, 0.01700, 0.01600, 0.01500, 0.01100, 0.01500, 0.01300, 0.15200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.05600, 0.04600, 0.02500, 0.01900, 0.02100, 0.02000, 0.01700, 0.01700, 0.02200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.09800, 0.04800, 0.03400, 0.02400, 0.02200, 0.02200, 0.02500, 0.02700, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.04700, 0.06200, 0.03400, 0.02500, 0.01900, 0.02300, 0.02200, 0.12200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.05600, 0.03200, 0.02500, 0.02300, 0.02100, 0.04300, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.06600, 0.04200, 0.03000, 0.02700, 0.02500, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.08300, 0.03800, 0.03000, 0.02300, 0.03200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.07100, 0.03800, 0.03600, 0.03800, 0.13600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.05000, 0.04200, 0.04000, 0.03900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.04400, 0.05800, 0.03700, 0.09400, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.15200, 0.15300, 0.05400, 0.02000, 0.12600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.03000, 0.02400, 0.03500, 0.15200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000
} ;


void GenInfo2() {

    TString hfolder  = "NewGMSB_L180/" ;
    TString fileName = "NewGMSB_L180/GMSB180_Gen_" ;

    TString plotname1 = "ctau_All.png" ;
    TString plotname2 = "ctbg_All.png" ;
    TString plotname3 = "Beta_Neutralino.png" ;
    TString plotname4 = "LateX_beta.png" ;
    TString plotname5 = "LateX_ctau.png" ;
    TString plotname6 = "LateX_ctbgT.png" ;
    TString plotname7 = "ctbgT_All.png" ;
    TString plotname8 = "ctbgT_Sel.png" ;
    TString plotname9 = "ctbgT_Obs.png" ;
    TString plotname10 = "Eff_ctau.png" ;
    TString plotname11 = "EffxAccp_ctau.png" ;
    TString plotname12 = "Accp_ctau.png" ;
    TString plotname13 = "EffxAccp_ctbgT.png" ;
    TString plotname14 = "Eff_ctbgT.png" ;
    TString plotname15 = "Accp_ctbgT.png" ;
    TString plotname16 = "Eta_Neutralino.png" ;
    TString plotname17 = "Eta_SelectedNeutralino.png" ;
    TString plotname18 = "ctbgT1_Obs.png" ;
    TString plotname19 = "Accp_ctbgT1.png" ;
    TString plotname20 = "EcalTime_gen.png" ;
    TString plotname21 = "nLate_Ctau.png" ;
    TString plotname22 = "nReco_Ctau.png" ;
    TString plotname23 = "Accp_ctbgT2.png" ;
    TString plotname24 = "EcalTime_reco.png" ;

    string hName1 = "h_ctau" ;
    string hName2 = "h_ctbg" ;
    string hName3 = "h_Xbeta" ;
    string hName4 = "h_lateXbeta" ;
    string hName5 = "h_lateXctau" ;
    string hName6 = "h_lateXctbgT" ;
    string hName7 = "h_ctbgT" ;
    string hName8 = "reco_ctbgT" ;
    string hName9 = "acc_ctbgT0" ;
    string hName10 = "h_XEta" ;
    string hName11 = "sel_XEta" ;
    string hName12 = "acc_ctbgT1" ;
    string hName13 = "sel_ctbgT" ;
    string hName14 = "acc_ctbgT" ;
    string hName15 = "h_Time" ;
    string hName16 = "acc_ctbgT2" ;
    string hName17 = "selTime" ;
    string hName18 = "xPt_ctbgT" ;

    double nGen[6] = { 50112, 50112, 50112, 50112, 50112, 50112 } ;
    TString names[6] = { "500","1000", "2000", "3000", "6000", "12000" } ;
    int color[6]     = {     1,    2,      4,      6,     8,    5  } ;
    const int nModel = 6;
    

    TFile* hfile[ nModel ] ;

    TH1D*  hctau[ nModel ] ;
    TH1D*  hctbg[ nModel ] ;
    TH1D*  hXbeta[ nModel ] ;
    TH1D*  lateXbeta[ nModel ] ;
    TH1D*  lateXctau[ nModel ] ;
    TH1D*  lateXctbgT[ nModel ] ;
    TH1D*  hctbgT[ nModel ] ;
    TH1D*  RctbgT[ nModel ] ;
    TH1D*  ActbgT0[ nModel ] ;
    TH1D*  hXeta[ nModel ] ;
    TH1D*  sel_Xeta[ nModel ] ;
    TH1D*  ActbgT1[ nModel ] ;
    TH1D*  ActbgT2[ nModel ] ;
    TH1D*  SctbgT[ nModel ] ;
    TH1D*  ActbgT[ nModel ] ;
    TH1D*  hTime[ nModel ] ;
    TH1D*  STime[ nModel ] ;
    TH2D*  reco_xPt_ct[ nModel ] ;


    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );

        hctau[i]      = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        hctbg[i]      = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
        hXbeta[i]     = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
        lateXbeta[i]  = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
        lateXctau[i]  = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
        lateXctbgT[i] = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
        hctbgT[i]     = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
	RctbgT[i]     = (TH1D *) hfile[i]->Get( hName8.c_str() )  ;
        ActbgT0[i]    = (TH1D *) hfile[i]->Get( hName9.c_str() )  ;
        hXeta[i]      = (TH1D *) hfile[i]->Get( hName10.c_str() )  ;
        sel_Xeta[i]   = (TH1D *) hfile[i]->Get( hName11.c_str() )  ;
        ActbgT1[i]    = (TH1D *) hfile[i]->Get( hName12.c_str() )  ;
	SctbgT[i]     = (TH1D *) hfile[i]->Get( hName13.c_str() )  ;
	ActbgT[i]     = (TH1D *) hfile[i]->Get( hName14.c_str() )  ;
	hTime[i]      = (TH1D *) hfile[i]->Get( hName15.c_str() )  ;
        ActbgT2[i]    = (TH1D *) hfile[i]->Get( hName16.c_str() )  ;
	STime[i]      = (TH1D *) hfile[i]->Get( hName17.c_str() )  ;
        reco_xPt_ct[i] = (TH2D *) hfile[i]->Get( hName18.c_str() )  ;

    }

    gStyle->SetOptStat("");
 
    // Plots Setup
    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    gPad->SetGridx();
    //gPad->SetGridy();
    c0->SetLeftMargin(0.15);
    c0->SetRightMargin(0.12);
    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.12);

    c0->cd();
    //gStyle->SetOptStat(kTRUE);
    //gStyle->SetOptFit(111);
    c0->SetLogy();

    TLegend* leg1  = new TLegend(.70, .65, .95, .90 );
    leg1->Clear();
    char legStr[100] ;
    float nEntry = 0 ;

    // Plot1 - ctau of neutralino
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        hctau[i]->SetLineColor( color[i] ) ;
        nEntry =  hctau[i]->Integral() ;
        if ( i ==0 )  hctau[i]->Draw() ;
        else          hctau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( hctau[i], names[i] + legStr,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname1 );

    // Plot2 - ctbg distribution of neutralino
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        hctbg[i]->SetLineColor( color[i] ) ;
        nEntry =  hctbg[i]->Integral() ;
        if ( i == 0 )  hctbg[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  hctbg[i]->Draw() ;
        else           hctbg[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( hctbg[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+plotname2 );

    // Plot3 - neutralino's beta
    TLegend* leg2  = new TLegend(.20, .65, .45, .90 );
    leg2->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0; i < nModel; i++ ) {
        hXbeta[i]->SetLineColor( color[i] ) ;
        nEntry =  hXbeta[i]->Integral() ;
        if ( i == 0 )  hXbeta[i]->Draw() ;
        else           hXbeta[i]->Draw("SAMES") ;
        leg2->AddEntry( hXbeta[i], names[i] ,  "L");
        c0->Update() ;  
    }
    leg2->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname3 );

    // Plot4
    leg1->Clear() ;
    for ( int i = nModel-1 ; i >= 0; i-- ) {
        lateXbeta[i]->SetLineColor( color[i] ) ;
        if ( i == nModel-1 )  lateXbeta[i]->Draw() ;
        else                  lateXbeta[i]->Draw("SAMES") ;
        leg1->AddEntry( lateXbeta[i], names[i] ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname4 );

    // Plot5 -  late Neutralino's ctau
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0; i < nModel; i++ ) {
        lateXctau[i]->SetLineColor( color[i] ) ;
        nEntry =  lateXctau[i]->Integral() ;
        if ( i == 0 )  lateXctau[i]->Draw() ;
        else           lateXctau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( lateXctau[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname5 );

    // Plot6 -  late Neutralino's ctbgT
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0; i < nModel; i++ ) {
        lateXctbgT[i]->SetLineColor( color[i] ) ;
        nEntry =  lateXctbgT[i]->Integral() ;
        if ( i == 0 )  lateXctbgT[i]->Draw() ;
        else           lateXctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( lateXctau[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname6 );

    // Plot7 - All ctbgT 
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        hctbgT[i]->SetLineColor( color[i] ) ;
        //hctbgT[i]->SetAxisRange( 0, 1500 ) ;
        nEntry =  hctbgT[i]->Integral() ;
        if ( i == 0 )  hctbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  hctbgT[i]->Draw() ;
        else           hctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( hctbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname7 );

    // Plot8 - selected ctbgT
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        RctbgT[i]->SetLineColor( color[i] ) ;
        //RctbgT[i]->SetAxisRange( 0, 1500 ) ;
        nEntry =  RctbgT[i]->Integral() ;
        if ( i == 0 )  RctbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  RctbgT[i]->Draw() ;
        else           RctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( RctbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname8 );

    // Plot9 - accepted ctbgT 
    leg1->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0 ; i < nModel ; i++ ) {
        ActbgT0[i]->SetLineColor( color[i] ) ;
        nEntry =  ActbgT0[i]->Integral() ;
        //Octbg[i]->Rebin() ;
        if ( i == 0 )  ActbgT0[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  ActbgT0[i]->SetMaximum( 600 ) ;
        if ( i == 0 )  ActbgT0[i]->Draw() ;
        else           ActbgT0[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( ActbgT0[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname9 );

    // Plot18 - accepted ctbgT1 
    leg1->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0 ; i < nModel ; i++ ) {
        ActbgT1[i]->SetLineColor( color[i] ) ;
        nEntry =  ActbgT1[i]->Integral() ;
        //Octbg[i]->Rebin() ;
        if ( i == 0 )  ActbgT1[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  ActbgT1[i]->SetMaximum( 600 ) ;
        if ( i == 0 )  ActbgT1[i]->Draw() ;
        else           ActbgT1[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", nEntry  ) ;
        leg1->AddEntry( ActbgT1[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname18 );

    cout<<" Section Done ! "<<endl ;
    // Plot10 ~ 12 - Efficiency Plots in different ctau Models
    TH1D* hObs      = new TH1D("hObs", " ",  nModel,  0, nModel );
    TH1D* hRec      = new TH1D("hRec", " ",  nModel,  0, nModel );
    TH1D* hGen      = new TH1D("hGen", " ",  nModel,  0, nModel );
    for ( int i=0; i< nModel ; i++ ) {
        double n_sel = SctbgT[i]->Integral(0, SctbgT[i]->GetNbinsX()+1 ) ;
        double n_acc = ActbgT[i]->Integral(0, ActbgT[i]->GetNbinsX()+1 ) ;
        double n_gen = hctbgT[i]->Integral(0, hctbgT[i]->GetNbinsX()+1 ) ;
        printf(" All: %.1f , sel: %.1f , acc: %.1f \n", n_gen, n_sel, n_acc ) ;
        hObs->SetBinContent( i+1 , n_acc ) ;
        hRec->SetBinContent( i+1 , n_sel ) ;
        hGen->SetBinContent( i+1 , n_gen ) ;
    }
    TGraphAsymmErrors* acc_x0 = new TGraphAsymmErrors();
    acc_x0->BayesDivide( hObs, hGen );
    TGraphAsymmErrors* eff_x0 = new TGraphAsymmErrors();
    eff_x0->BayesDivide( hRec, hGen );
    TGraphAsymmErrors* acp_x0 = new TGraphAsymmErrors();
    acp_x0->BayesDivide( hObs, hRec );

    c0->cd();
    c0->SetLogy(0);

    eff_x0->SetTitle(" Reco_Efficiency ") ;
    eff_x0->SetMaximum( 0.1 );
    eff_x0->SetMinimum( 0.0 );
    eff_x0->SetMarkerColor(4);
    eff_x0->SetMarkerStyle(22);
    eff_x0->SetMarkerSize(1);
    eff_x0->SetLineColor(1);
    eff_x0->SetLineWidth(2);
    eff_x0->GetXaxis()->SetTitleOffset(1.34);
    eff_x0->GetYaxis()->SetTitleOffset(1.41);

    eff_x0->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    eff_x0->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
    eff_x0->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname10 );

    acc_x0->SetTitle(" Efficiency*Acceptance ") ;
    acc_x0->SetMaximum( 0.01 );
    acc_x0->SetMinimum( 0.0 );
    acc_x0->SetMarkerColor(4);
    acc_x0->SetMarkerStyle(22);
    acc_x0->SetMarkerSize(1);
    acc_x0->SetLineColor(1);
    acc_x0->SetLineWidth(2);
    acc_x0->GetXaxis()->SetTitleOffset(1.34);
    acc_x0->GetYaxis()->SetTitleOffset(1.5);

    acc_x0->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    acc_x0->GetYaxis()->SetTitle(" Efficiency*Acceptance ") ;
    acc_x0->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname11 );

    acp_x0->SetTitle(" Acceptance ") ;
    acp_x0->SetMaximum( 0.6 );
    acp_x0->SetMinimum( 0.0 );
    acp_x0->SetMarkerColor(4);
    acp_x0->SetMarkerStyle(22);
    acp_x0->SetMarkerSize(1);
    acp_x0->SetLineColor(1);
    acp_x0->SetLineWidth(2);
    acp_x0->GetXaxis()->SetTitleOffset(1.34);
    acp_x0->GetYaxis()->SetTitleOffset(1.5);

    acp_x0->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    acp_x0->GetYaxis()->SetTitle(" Acceptance ") ;
    acp_x0->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname12 );

    // Plot 13
    TGraphAsymmErrors* acc_ctbgT[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {
        acc_ctbgT[i]= new TGraphAsymmErrors();
        ActbgT0[i]->Rebin(2) ;
        hctbgT[i]->Rebin(2) ;
        RctbgT[i]->Rebin(2) ; // rebin together
        ActbgT1[i]->Rebin(2) ; // rebin together
        ActbgT2[i]->Rebin(2) ; // rebin together

        leg1->AddEntry( ActbgT0[i], names[i]  ,  "L");
        acc_ctbgT[i]->BayesDivide( ActbgT0[i], hctbgT[i] );
	acc_ctbgT[i]->SetMarkerColor( color[i] );
	acc_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==0 ) {
           c0->cd();
	   c0->SetLogy(0);

	   acc_ctbgT[i]->SetTitle(" Efficiency*Acceptance ") ;
	   acc_ctbgT[i]->SetMaximum( 0.6 );
	   acc_ctbgT[i]->SetMinimum( 0.0 );
	   acc_ctbgT[i]->SetMarkerStyle(22);
	   acc_ctbgT[i]->SetMarkerSize(1);
	   acc_ctbgT[i]->SetLineWidth(2);
	   acc_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
	   acc_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

	   acc_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
	   acc_ctbgT[i]->GetYaxis()->SetTitle(" Efficiency*Acceptance ") ;
	   acc_ctbgT[i]->Draw("AP");
        } else {
	   acc_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname13 );

    // Plot 14
    TGraphAsymmErrors* eff_ctbgT[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {
        eff_ctbgT[i]= new TGraphAsymmErrors();

        leg1->AddEntry( RctbgT[i], names[i]  ,  "L");
        eff_ctbgT[i]->BayesDivide( RctbgT[i], hctbgT[i] );
	eff_ctbgT[i]->SetMarkerColor( color[i] );
	eff_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==0 ) {
           c0->cd();
	   c0->SetLogy(0);

	   eff_ctbgT[i]->SetTitle(" Efficiency") ;
	   eff_ctbgT[i]->SetMaximum( 1.0 );
	   eff_ctbgT[i]->SetMinimum( 0.0 );
	   eff_ctbgT[i]->SetMarkerStyle(22);
	   eff_ctbgT[i]->SetMarkerSize(1);
	   eff_ctbgT[i]->SetLineWidth(2);
	   eff_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
	   eff_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

	   eff_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
	   eff_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
	   eff_ctbgT[i]->Draw("AP");
        } else {
	   eff_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname14 );

    // Plot 15
    TGraphAsymmErrors* acp_ctbgT[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {
        acp_ctbgT[i]= new TGraphAsymmErrors();

        leg1->AddEntry( ActbgT0[i], names[i]  ,  "L");
        acp_ctbgT[i]->BayesDivide( ActbgT0[i], RctbgT[i] );
	acp_ctbgT[i]->SetMarkerColor( color[i] );
	acp_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==0 ) {
           c0->cd();
	   c0->SetLogy(0);

	   acp_ctbgT[i]->SetTitle(" Acceptance ") ;
	   acp_ctbgT[i]->SetMaximum( 1.0 );
	   acp_ctbgT[i]->SetMinimum( 0.0 );
	   acp_ctbgT[i]->SetMarkerStyle(22);
	   acp_ctbgT[i]->SetMarkerSize(1);
	   acp_ctbgT[i]->SetLineWidth(2);
	   acp_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
	   acp_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

	   acp_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
	   acp_ctbgT[i]->GetYaxis()->SetTitle(" Acceptance ") ;
	   acp_ctbgT[i]->Draw("AP");
        } else {
	   acp_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname15 );

    // Plot16 - neutralino's eta
    leg1->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0; i < nModel; i++ ) {
        hXeta[i]->SetLineColor( color[i] ) ;
        nEntry =  hXeta[i]->Integral() ;
        if ( i == 0 )  hXeta[i]->Draw() ;
        else           hXeta[i]->Draw("SAMES") ;
        leg1->AddEntry( hXeta[i], names[i] ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname16 );

    // Plot17 - neutralino's eta pass selection
    leg1->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0; i < nModel; i++ ) {
        sel_Xeta[i]->SetLineColor( color[i] ) ;
        nEntry =  sel_Xeta[i]->Integral() ;
        if ( i == 0 )  sel_Xeta[i]->Draw() ;
        else           sel_Xeta[i]->Draw("SAMES") ;
        leg1->AddEntry( sel_Xeta[i], names[i] ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname17 );


    // Plot 19
    TGraphAsymmErrors* acp_ctbgT1[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {
        acp_ctbgT1[i]= new TGraphAsymmErrors();

        leg1->AddEntry( ActbgT1[i], names[i]  ,  "L");
        acp_ctbgT1[i]->BayesDivide( ActbgT1[i], RctbgT[i] );
	acp_ctbgT1[i]->SetMarkerColor( color[i] );
	acp_ctbgT1[i]->SetLineColor( color[i] );

        if ( i ==0 ) {
           c0->cd();
	   c0->SetLogy(0);

	   acp_ctbgT1[i]->SetTitle(" Acceptance ") ;
	   acp_ctbgT1[i]->SetMaximum( 1.0 );
	   acp_ctbgT1[i]->SetMinimum( 0.0 );
	   acp_ctbgT1[i]->SetMarkerStyle(22);
	   acp_ctbgT1[i]->SetMarkerSize(1);
	   acp_ctbgT1[i]->SetLineWidth(2);
	   acp_ctbgT1[i]->GetXaxis()->SetTitleOffset(1.34);
	   acp_ctbgT1[i]->GetYaxis()->SetTitleOffset(1.41);

	   acp_ctbgT1[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
	   acp_ctbgT1[i]->GetYaxis()->SetTitle(" Acceptance ") ;
	   acp_ctbgT1[i]->Draw("AP");
        } else {
	   acp_ctbgT1[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname19 );

    // Plot 23
    TGraphAsymmErrors* acp_ctbgT2[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {
        acp_ctbgT2[i]= new TGraphAsymmErrors();

        leg1->AddEntry( ActbgT1[i], names[i]  ,  "L");
        acp_ctbgT2[i]->BayesDivide( ActbgT2[i], RctbgT[i] );
	acp_ctbgT2[i]->SetMarkerColor( color[i] );
	acp_ctbgT2[i]->SetLineColor( color[i] );

        if ( i ==0 ) {
           c0->cd();
	   c0->SetLogy(0);

	   acp_ctbgT2[i]->SetTitle(" Acceptance ") ;
	   acp_ctbgT2[i]->SetMaximum( 1.0 );
	   acp_ctbgT2[i]->SetMinimum( 0.0 );
	   acp_ctbgT2[i]->SetMarkerStyle(22);
	   acp_ctbgT2[i]->SetMarkerSize(1);
	   acp_ctbgT2[i]->SetLineWidth(2);
	   acp_ctbgT2[i]->GetXaxis()->SetTitleOffset(1.34);
	   acp_ctbgT2[i]->GetYaxis()->SetTitleOffset(1.41);

	   acp_ctbgT2[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
	   acp_ctbgT2[i]->GetYaxis()->SetTitle(" Acceptance ") ;
	   acp_ctbgT2[i]->Draw("AP");
        } else {
	   acp_ctbgT2[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname23 );

    // Plot20 - EcalTime (sim)
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0; i < nModel; i++ ) {
        hTime[i]->SetLineColor( color[i] ) ;
        //RctbgT[i]->SetAxisRange( 0, 1500 ) ;
        nEntry =  hTime[i]->Integral(71,160) ;
        if ( i == 0 )  hTime[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  hTime[i]->Draw() ;
        else           hTime[i]->Draw("SAMES") ;
        sprintf( legStr,  ": %.0f ", nEntry  ) ;
        leg1->AddEntry( hTime[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname20 );

    // Plot24 - EcalTime (reco)
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0; i < nModel; i++ ) {
        STime[i]->SetLineColor( color[i] ) ;
        //RctbgT[i]->SetAxisRange( 0, 1500 ) ;
        //nEntry =  STime[i]->Integral(71,160) ;
        nEntry =  STime[i]->Integral(1,160) ;
        if ( i == 0 )  STime[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  STime[i]->Draw() ;
        else           STime[i]->Draw("SAMES") ;
        sprintf( legStr,  ": %.0f ", nEntry  ) ;
        leg1->AddEntry( STime[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname24 );

    // Plot21 - EcalTime(Gen) Fit 
    c0->SetLogy(0) ;                     
    double fitCtau[12] = { 185, 368, 492, 733,  982, 1076, 1444, 1931, 2161, 2878, 5774, 10366 } ;
    double nLate[12]   = { 842,3449,5404,8345,10583,11310,12529,13160,13112,12426, 9449,  6397 } ;
    TGraph* g_ctauFit = new TGraph(12, fitCtau , nLate ) ;
    g_ctauFit->SetMarkerStyle(21) ;
    g_ctauFit->SetMarkerSize(1);
    g_ctauFit->SetMarkerColor(2);
    g_ctauFit->Draw("ALP") ;
    c0->Update();
    for ( int i =0; i < 12; i++) {
        printf(" Scaling for [%.0f] = %.3f \n", fitCtau[i], nLate[i]/13112. ) ;
    }
    c0->Print( hfolder + plotname21 );

    // Plot22 - EcalTime(Reco) Fit
    double fitCtau1[12] = { 185, 368, 492 , 733,   982 , 1076, 1444, 1931 , 2161, 2878 , 5774 , 10366 } ;
    //double nReco[12]    = {  32, 258, 791 , 857,  1479 , 1234, 1331, 1794 , 1300, 1645 , 1219 ,   804 } ; 
    double nReco[12]    = {  32, 258, 421 , 857,  954 , 1234, 1331, 1282 , 1300, 1231 , 950 , 637 } ; 
    TGraph* g_recoFit = new TGraph( 12, fitCtau1, nReco ) ;
    g_recoFit->SetMarkerStyle(22) ;
    g_recoFit->SetMarkerSize(1);
    g_recoFit->SetMarkerColor(4);
    g_recoFit->Draw("ALP") ;
    c0->Update();
    c0->Print( hfolder + plotname22 );

    // scaling uncertainty
    for ( int m=0; m< nModel; m++ ) {
        double sumErr_u = 0. ;
        double sumErr_d = 0. ;
        reco_xPt_ct[m]->RebinY(2);
        for ( int j= 1 ; j <= reco_xPt_ct[m]->GetNbinsY();  j++ ) {
            for ( int i=1; i<= reco_xPt_ct[m]->GetNbinsX(); i++ ) {
                if ( i >= 16 ) continue ;

                double ib = reco_xPt_ct[m]->GetBinContent(i,j) ;
                int k = ((j-1)*15) + (i-1) ;
                sumErr_u += ( (ib*err_u[k]*ib*err_u[k]) + (ib*effA[k]*effA[k]) ) ;
                sumErr_d += ( (ib*err_d[k]*ib*err_d[k]) + (ib*effA[k]*effA[k]) ) ;
            }
        }
        sumErr_u = sqrt( sumErr_u ) ;
        sumErr_d = sqrt( sumErr_d ) ;
        printf(" model %d  +%.2f -%.2f \n", m, sumErr_u, sumErr_d ) ;
    }

    delete c0 ;
}

