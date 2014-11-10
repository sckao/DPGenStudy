#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void GenInfo() {

    TString hfolder  = "TCuts_GMSB_L160/" ;
    TString fileName = "TCuts_GMSB_L160/GMSB2J_160_" ;

    TString plotname0 = "ctbg_All.png" ;
    TString plotname1 = "ctau_All.png" ;
    TString plotname2 = "ctau_Sel.png" ;
    TString plotname3 = "ctau_Obs.png" ;
    TString plotname4 = "LateBeta_Neutralino.png" ;
    TString plotname5 = "Beta_Neutralino.png" ;
    TString plotname6 = "Pass_GenCTau.png" ;
    TString plotname7 = "Late_XPt.png" ;
    TString plotname8 = "All_XPt.png" ;
    TString plotname9 = "ctbgT_All.png" ;
    TString plotname10 = "ctbgT_Sel.png" ;
    TString plotname11 = "ctbgT_Obs.png" ;
    TString plotname12 = "ctbg_Obs.png" ;
    TString plotname15 = "ctbgT_inEcal.png" ;
    TString plotname16 = "Eff_ctau.png" ;
    TString plotname17 = "EffxAccept_ctau.png" ;
    TString plotname18 = "Accept_ctau.png" ;
    TString plotname19 = "EcalTime_Gen.png" ;
    TString plotname20 = "EcalTime_Reco.png" ;
    TString plotname21 = "Eff_Obs_ctbgT.png" ;
    TString plotname22 = "Eff_Reco_ctbgT.png" ;
    TString plotname23 = "Normal_Eff_ctbgT.png" ;
    TString plotname24 = "Acc_Reco_ctbgT.png" ;
    TString plotname25 = "Acc_Obs_ctbgT.png" ;
    TString plotname26 = "Normal_Acc_ctbgT.png" ;
    TString plotname27 = "EcalTime_Sim.png" ;

    string xlable = "ECAL Time (ns) " ;

    string hName  = "h_ctbg" ;
    string hName1 = "h_ctau" ;
    string hName2 = "sel_ctau" ;
    string hName3 = "acc_ctau" ;
    string hName4 = "h_lateXbeta" ;
    string hName5 = "h_xbeta" ;
    string hName6 = "sel_ctbg" ;
    string hName7 = "h_lateXPt" ;
    string hName8 = "h_XPt" ;
    string hName9 = "h_ctbgT" ;
    string hName10 = "sel_ctbgT" ;
    string hName11 = "acc_ctbgT" ;
    string hName12 = "acc_ctbg" ;
    string hName13 = "obs_ctbgT" ;
    string hName14 = "h_genTime" ;
    string hName15 = "obsTime" ;
    string hName16 = "reco_ctbgT" ;
    string hName17 = "lateR_ctbgT" ;
    string hName18 = "late_ctbgT" ;
    string hName19 = "simTime" ;


    // Lambda 160
    double nGen[8]   = { 50112,  50000,  50000,  50000,  50000,  50000,  50000,   50000 } ;
    TString names[8] = { "250",  "500", "1000", "2000", "3000", "4000", "6000", "12000" } ;
    int color[8]     = {     1,      2,      3,      4,      5,      6,      7,      8  } ;
    const int nModel = 8 ;
    /*
    // Lambda 120
    double nGen[11]   = { 50000, 50000, 50000, 50000,  50000,  50000,  50000,  50000,  50000,  50000,  50000  } ;
    //TString names[11] = {  "95", "185", "370", "730", "1075", "1445", "2160", "3000", "4000", "6000", "12000" } ;
    TString names[11] = {  "161", "323", "645", "1282", "1933", "2558", "2937", "3877", "3961", "5948", "9995" } ;
    int color[11]     = {     1,     2,     3,     4,      5,      6,      7,      8,      9,     11,     12  } ;
    const int nModel = 11;

    // Lambda 100
    double nGen[9]   = { 50000, 50000, 50000,   50000,  50000,  50000,  50000,  50000,  50000  } ;
    //TString names[9] = {  "95", "185",  "730", "1445", "2160", "3000", "4000", "6000", "12000" } ;
    TString names[9] = {  "212", "425",  "1691", "2870", "3384", "3941", "4977", "5860", "9300" } ;
    int color[9]     = {      1,     2,     3,     4,      5,      6,      7,      8,     9   } ;
    const int nModel = 9;

    // Lambda 140
    double nGen[10]   = { 50000, 50000, 50000, 50000,  50000,  50000,  50000,  50000,  50000,  50000  } ;
    //TString names[10] = {  "185", "370", "730","1075", "1445", "2160", "3000", "4000", "6000", "12000" } ;
    TString names[10] = {  "130", "515", "1021","1542", "2047", "2899", "3048", "3927", "6061", "10151" } ;
    int color[10]     = {     1,     2,     3,     4,      5,      6,      7,      8,     9 ,     11  } ;
    const int nModel = 10;

    double nGen[10]   = { 50000, 50000, 50000, 50000,  50000,  50000, 50000,  50000,   50000,  50000  } ;
    TString names[10] = { "182", "365", "734","1093", "1457", "2202", "2959", "4087", "5863", "10352" } ;
    int color[10]     = {     1,     2,     3,     4,      5,      6,      7,      8,     9,     11   } ;
    const int nModel = 10;

    */


    

    TFile* hfile[ nModel ] ;
    TH1D*  hctbg[ nModel ] ;
    TH1D*  hCtau[ nModel ] ;
    TH1D*  Sel_Ctau[ nModel ] ;
    TH1D*  Acc_Ctau[ nModel ] ;
    TH1D*  hlateXbeta[ nModel ] ;
    TH1D*  hXbeta[ nModel ] ;
    TH1D*  PassCtau[ nModel ] ;
    TH1D*  lateXPt[ nModel ] ;
    TH1D*  hXPt[ nModel ] ;
    TH1D*  hctbgT[ nModel ] ;
    TH1D*  SctbgT[ nModel ] ;
    TH1D*  OctbgT[ nModel ] ;
    TH1D*  RctbgT[ nModel ] ;
    TH1D*  LctbgT[ nModel ] ;
    TH1D*  BctbgT[ nModel ] ;
    TH1D*  Octbg[ nModel ] ;
    TH1D*  ActbgT[ nModel ] ;
    TH1D*  hTime[ nModel ] ;
    TH1D*  obsTime[ nModel ] ;
    TH1D*  simTime[ nModel ] ;

    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );
        hctbg[i]  = (TH1D *) hfile[i]->Get( hName.c_str() )  ;
        hCtau[i]  = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        Sel_Ctau[i]   = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
        Acc_Ctau[i]   = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
        hlateXbeta[i] = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
        hXbeta[i]     = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
        PassCtau[i]   = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
        lateXPt[i]    = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
        hXPt[i]       = (TH1D *) hfile[i]->Get( hName8.c_str() )  ;
        hctbgT[i]     = (TH1D *) hfile[i]->Get( hName9.c_str() )  ;
	SctbgT[i]     = (TH1D *) hfile[i]->Get( hName10.c_str() )  ;
        OctbgT[i]     = (TH1D *) hfile[i]->Get( hName11.c_str() )  ;
        Octbg[i]      = (TH1D *) hfile[i]->Get( hName12.c_str() )  ;
        ActbgT[i]     = (TH1D *) hfile[i]->Get( hName13.c_str() )  ;
        hTime[i]      = (TH1D *) hfile[i]->Get( hName14.c_str() )  ;
        obsTime[i]    = (TH1D *) hfile[i]->Get( hName15.c_str() )  ;
        RctbgT[i]     = (TH1D *) hfile[i]->Get( hName16.c_str() )  ;
        LctbgT[i]     = (TH1D *) hfile[i]->Get( hName17.c_str() )  ;
        BctbgT[i]     = (TH1D *) hfile[i]->Get( hName18.c_str() )  ;
        simTime[i]    = (TH1D *) hfile[i]->Get( hName19.c_str() )  ;
    }

    gStyle->SetOptStat("");
 
    // Plots
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
    float n_late = 0 ;

    // Plot0
    for ( int i = 0; i < nModel; i++ ) {
        // calculate the number 
        // Setup color and draw histogram
        n_late = hctbg[i]->Integral() ;
        hctbg[i]->SetLineColor( color[i] ) ;
        //hctbg[i]->SetAxisRange(0,1500) ;
        if ( i == 0 )  hctbg[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  hctbg[i]->Draw() ;
        else           hctbg[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( hctbg[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+plotname0 );

    // Plot1
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        hCtau[i]->SetLineColor( color[i] ) ;
        n_late =  hCtau[i]->Integral() ;
        hCtau[i]->Rebin(2) ;
        hCtau[i]->Fit("expo", "N") ;
        double fit_ct =  -1. / expo->GetParameter(1) ;

        if ( i ==0 )  hCtau[i]->Draw() ;
        else          hCtau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", fit_ct  ) ;
        leg1->AddEntry( hCtau[i], names[i] + legStr,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname1 );

    // Plot2
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        Sel_Ctau[i]->SetLineColor( color[i] ) ;
        n_late =  Sel_Ctau[i]->Integral() ;
        Sel_Ctau[i]->Rebin(2) ;
        if ( i ==0 )  Sel_Ctau[i]->Draw() ;
        else          Sel_Ctau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( Sel_Ctau[i], names[i] + legStr,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname2 );

    // Plot3
    leg1->Clear() ;
    for ( int i = nModel-1 ; i >=0 ; i-- ) {
        Acc_Ctau[i]->SetLineColor( color[i] ) ;
        n_late =  Acc_Ctau[i]->Integral() ;
        Acc_Ctau[i]->Rebin(2) ;
        if ( i ==nModel-1 )  Acc_Ctau[i]->Draw() ;
        else          Acc_Ctau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( Acc_Ctau[i], names[i] + legStr,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname3 );

    // Plot4
    leg1->Clear() ;
    for ( int i = nModel-1 ; i >= 0; i-- ) {
        hlateXbeta[i]->SetLineColor( color[i] ) ;
        if ( i == nModel-1 )  hlateXbeta[i]->Draw() ;
        else           hlateXbeta[i]->Draw("SAMES") ;
        leg1->AddEntry( hlateXbeta[i], names[i] ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname4 );

    // Plot5
    TLegend* leg2  = new TLegend(.20, .65, .45, .90 );
    leg2->Clear() ;
    c0->SetLogy(0);
    for ( int i = 0; i < nModel; i++ ) {
        hXbeta[i]->SetLineColor( color[i] ) ;
        n_late =  hXbeta[i]->Integral() ;
        if ( i == 0 )  hXbeta[i]->Draw() ;
        else           hXbeta[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg2->AddEntry( hXbeta[i], names[i] + legStr ,  "L");
        c0->Update() ;  
    }
    leg2->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname5 );

    // Plot6
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0; i < nModel; i++ ) {
        PassCtau[i]->SetLineColor( color[i] ) ;
        n_late =  PassCtau[i]->Integral() ;
        if ( i == 0 )  PassCtau[i]->Draw() ;
        else           PassCtau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( PassCtau[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname6 );

    // Plot7
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = nModel-1 ; i >= 0; i-- ) {
        lateXPt[i]->SetLineColor( color[i] ) ;
        n_late =  lateXPt[i]->Integral() ;
        if ( i == nModel-1 )  lateXPt[i]->Draw() ;
        else           lateXPt[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( lateXPt[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname7 );

    // Plot8
    leg1->Clear() ;
    for ( int i = 0 ; i < nModel; i++ ) {
        hXPt[i]->SetLineColor( color[i] ) ;
        n_late =  hXPt[i]->Integral() ;
        if ( i == 0 )  hXPt[i]->Draw() ;
        else           hXPt[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( hXPt[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname8 );

    // Plot9
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        hctbgT[i]->SetLineColor( color[i] ) ;
        //hctbgT[i]->SetAxisRange( 0, 1500 ) ;
        n_late =  hctbgT[i]->Integral() ;
        if ( i == 0 )  hctbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  hctbgT[i]->Draw() ;
        else           hctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( hctbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname9 );

    // Plot10
    leg1->Clear() ;
    for ( int i = 0; i < nModel; i++ ) {
        SctbgT[i]->SetLineColor( color[i] ) ;
        //SctbgT[i]->SetAxisRange( 0, 1500 ) ;
        n_late =  SctbgT[i]->Integral() ;
        if ( i == 0 )  SctbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  SctbgT[i]->Draw() ;
        else           SctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( SctbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname10 );

    // Plot11
    leg1->Clear() ;
    for ( int i = nModel-1 ; i >= 0; i-- ) {
        OctbgT[i]->SetLineColor( color[i] ) ;
        n_late =  OctbgT[i]->Integral() ;
        //OctbgT[i]->Rebin() ;
        if ( i == nModel-1 )  OctbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == nModel-1 )  OctbgT[i]->Draw() ;
        else           OctbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( OctbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname11 );

    // Plot12
    leg1->Clear() ;
    for ( int i = nModel-1 ; i >= 0; i-- ) {
        Octbg[i]->SetLineColor( color[i] ) ;
        n_late =  Octbg[i]->Integral() ;
        //Octbg[i]->Rebin() ;
        if ( i == nModel-1 )  Octbg[i]->SetMinimum( 0.1 ) ;
        if ( i == nModel-1 )  Octbg[i]->Draw() ;
        else           Octbg[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( Octbg[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname12 );

    // Plot15
    leg1->Clear() ;
    c0->SetLogy();
    for ( int i = 0 ; i < nModel ; i++ ) {
        ActbgT[i]->SetLineColor( color[i] ) ;
        n_late =  ActbgT[i]->Integral() ;
        //Octbg[i]->Rebin() ;
        if ( i == 0 )  ActbgT[i]->SetMinimum( 0.1 ) ;
        if ( i == 0 )  ActbgT[i]->Draw() ;
        else           ActbgT[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( ActbgT[i], names[i]+legStr  ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+ plotname15 );

    // Plot16 ~ 18 - Efficiency Plots in different ctau Models
    TH1D* hObs      = new TH1D("hObs", " ",  nModel,  0, nModel );
    TH1D* hRec      = new TH1D("hRec", " ",  nModel,  0, nModel );
    TH1D* hGen      = new TH1D("hGen", " ",  nModel,  0, nModel );
    for ( int i=0; i< nModel ; i++ ) {
        double n_acc = Acc_Ctau[i]->Integral(0, Acc_Ctau[i]->GetNbinsX()+1 ) ;
        double n_sel = Sel_Ctau[i]->Integral(0, Acc_Ctau[i]->GetNbinsX()+1 ) ;
        printf(" All: %.1f , sel: %.1f , acc: %.1f \n", nGen[i], n_sel, n_acc ) ;
        hObs->SetBinContent( i+1 , n_acc ) ;
        hRec->SetBinContent( i+1 , n_sel ) ;
        hGen->SetBinContent( i+1 , nGen[i] ) ;
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
    eff_x0->SetMaximum( 0.8 );
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
    c0->Print( hfolder + plotname16 );

    acc_x0->SetTitle(" Efficiency*Acceptance ") ;
    acc_x0->SetMaximum( 0.05 );
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
    c0->Print( hfolder + plotname17 );

    acp_x0->SetTitle(" Acceptance ") ;
    acp_x0->SetMaximum( 0.5 );
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
    c0->Print( hfolder + plotname18 );


    // Plot19
    printf(" GenTime \n") ;
    leg1->Clear() ;
    c0->SetLogy() ; 
    double nGen[ nModel ] = { 0 } ;
    double nReco[ nModel ] = { 0 } ;
    for ( int i = 0; i < nModel; i++ ) {
        n_late = hTime[i]->Integral(71,160) ;
        //n_late = hTime[i]->Integral(1,160) ;
        hTime[i]->SetLineColor( color[i] ) ;
        hTime[i]->Rebin(2) ;
        if ( i == 0 )  hTime[i]->Draw() ;
        else           hTime[i]->Draw("SAMES") ;
        sprintf( legStr,  ": %.0f ", n_late  ) ;
        nGen[i] = n_late ;
        leg1->AddEntry( hTime[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder + plotname19 );

    // Plot20
    printf(" RecoTime \n") ;
    leg1->Clear() ;
    c0->SetLogy() ; 
    for ( int i = 0; i < nModel; i++ ) {
        n_late = obsTime[i]->Integral(71,160) ;
        //n_late = obsTime[i]->Integral(1,160) ;
        obsTime[i]->Rebin(2) ;
        obsTime[i]->SetLineColor( color[i] ) ;
        if ( i == 0 )  obsTime[i]->Draw() ;
        else           obsTime[i]->Draw("SAMES") ;
        sprintf( legStr,  ": %.0f ", n_late  ) ;
        nReco[i] = n_late ;
        leg1->AddEntry( obsTime[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder + plotname20 );

    
    for ( int i = 0; i < nModel; i++ ) {
        printf("(%d) nR: %.2f / nG: %.2f = Eff %f \n", i, nReco[i], nGen[i], nReco[i]/nGen[i]) ;
    }

    // Plot27
    printf(" SimTime \n") ;
    leg1->Clear() ;
    c0->SetLogy() ; 
    //for ( int i = 0; i < nModel; i++ ) {
    for ( int i = nModel-1; i >=0; i-- ) {
        //n_late = simTime[i]->Integral(71,160) ;
        n_late = simTime[i]->Integral(1,160) ;
        simTime[i]->Rebin(2) ;
        simTime[i]->SetLineColor( color[i] ) ;
        if ( i == nModel-1 )  simTime[i]->Draw() ;
        else           simTime[i]->Draw("SAMES") ;
        sprintf( legStr,  ": %.0f ", n_late  ) ;
        nReco[i] = n_late ;
        leg1->AddEntry( simTime[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder + plotname27 );

    // Plot 21 
    TLegend* leg3  = new TLegend(.80, .65, .95, .90 );
    TGraphAsymmErrors* eff_ctbgT[nModel] ;
    leg3->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_ctbgT[i]= new TGraphAsymmErrors();

        ActbgT[i]->Rebin(2) ;
        RctbgT[i]->Rebin(2) ;
        SctbgT[i]->Rebin(2) ;
        hctbgT[i]->Rebin(2) ;
        OctbgT[i]->Rebin(2) ;
        LctbgT[i]->Rebin(2) ;
        BctbgT[i]->Rebin(2) ;

        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");
        //eff_ctbgT[i]->BayesDivide( ActbgT[i], hctbgT[i] );
        eff_ctbgT[i]->BayesDivide( SctbgT[i], hctbgT[i] );    // including other event selection like MET ...
        eff_ctbgT[i]->SetMarkerColor( color[i] );
        eff_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
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
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname21 );

    // Plot 22
    TGraphAsymmErrors* eff1_ctbgT[nModel] ;
    leg3->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff1_ctbgT[i]= new TGraphAsymmErrors();

        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");
        eff1_ctbgT[i]->BayesDivide( RctbgT[i], hctbgT[i] );
        eff1_ctbgT[i]->SetMarkerColor( color[i] );
        eff1_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff1_ctbgT[i]->SetTitle(" Efficiency") ;
           eff1_ctbgT[i]->SetMaximum( 1.0 );
           eff1_ctbgT[i]->SetMinimum( 0.0 );
           eff1_ctbgT[i]->SetMarkerStyle(22);
           eff1_ctbgT[i]->SetMarkerSize(1);
           eff1_ctbgT[i]->SetLineWidth(2);
           eff1_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
           eff1_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

           eff1_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           eff1_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff1_ctbgT[i]->Draw("AP");
        } else {
           eff1_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname22 );
   

    // Plot 23
    TGraphAsymmErrors* eff2_ctbgT[nModel] ;
    leg3->Clear() ;

    int nBin1 = RctbgT[1]->GetNbinsX() ;
    TH1D* hRec1   = new TH1D("hRec1", " ",  nBin1,  0, 4000. );
    TH1D* hObs1   = new TH1D("hObs1", " ",  nBin1,  0, 4000. );
    for ( int i=1; i< nModel; i++ ) {

	for ( int j= 1; j <= nBin1 ; j++ ) {
            double nA1 = SctbgT[i]->GetBinContent(j) ;
	    double nR1 = RctbgT[i]->GetBinContent(j) ;
	    if ( nA1 > nR1 ) nA1 = nR1 ;
	    hObs1->SetBinContent( j, nA1 ) ;
	    hRec1->SetBinContent( j, nR1 ) ;
            if ( i == nModel -1 ) printf(" (%d) eff = %.3f \n", j , nA1/nR1 ) ;
        }

        eff2_ctbgT[i]= new TGraphAsymmErrors();
        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");
        //eff2_ctbgT[i]->BayesDivide( ActbgT[i], RctbgT[i] );
        eff2_ctbgT[i]->Divide( hObs1, hRec1 );
        eff2_ctbgT[i]->SetMarkerColor( color[i] );
        eff2_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff2_ctbgT[i]->SetTitle(" Efficiency") ;
           eff2_ctbgT[i]->SetMaximum( 0.5 );
           eff2_ctbgT[i]->SetMinimum( 0.0 );
           eff2_ctbgT[i]->SetMarkerStyle(22);
           eff2_ctbgT[i]->SetMarkerSize(1);
           eff2_ctbgT[i]->SetLineWidth(2);
           eff2_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
           eff2_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

           eff2_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           eff2_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff2_ctbgT[i]->Draw("AP");
        } else {
           eff2_ctbgT[i]->Draw("SAMEPS");
        }

        
    }
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname23 );

    // Plot 24
    cout<<" Plot 24 "<<endl;
    TGraphAsymmErrors* tcut_ctbgT[nModel] ;
    leg3->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        tcut_ctbgT[i]= new TGraphAsymmErrors();

        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");
        //tcut_ctbgT[i]->BayesDivide( LctbgT[i], BctbgT[i] );
        tcut_ctbgT[i]->BayesDivide( LctbgT[i], RctbgT[i] );
        tcut_ctbgT[i]->SetMarkerColor( color[i] );
        tcut_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           tcut_ctbgT[i]->SetTitle(" Efficiency") ;
           tcut_ctbgT[i]->SetMaximum( 1.0 );
           tcut_ctbgT[i]->SetMinimum( 0.0 );
           tcut_ctbgT[i]->SetMarkerStyle(22);
           tcut_ctbgT[i]->SetMarkerSize(1);
           tcut_ctbgT[i]->SetLineWidth(2);
           tcut_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
           tcut_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

           tcut_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           tcut_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           tcut_ctbgT[i]->Draw("AP");
        } else {
           tcut_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname24 );

    // Plot 25
    cout<<" Plot 25 "<<endl;
    TGraphAsymmErrors* tcut1_ctbgT[nModel] ;
    leg3->Clear() ;
    TH1D* hRec2   = new TH1D("hRec2", " ",  nBin1,  0, 4000. );
    TH1D* hObs2   = new TH1D("hObs2", " ",  nBin1,  0, 4000. );
    for ( int i=1; i< nModel; i++ ) {

        tcut1_ctbgT[i]= new TGraphAsymmErrors();
	for ( int j= 1; j <= nBin1 ; j++ ) {
            double nO2 = OctbgT[i]->GetBinContent(j) ;
	    double nR2 = RctbgT[i]->GetBinContent(j) ;
	    if ( nO2 > nR2 ) nO2 = nR2 ;
	    hObs2->SetBinContent( j, nO2 ) ;
	    hRec2->SetBinContent( j, nR2 ) ;
        }
        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");

        tcut1_ctbgT[i]->Divide( hObs2, hRec2 );
        tcut1_ctbgT[i]->SetMarkerColor( color[i] );
        tcut1_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           tcut1_ctbgT[i]->SetTitle(" Efficiency") ;
           tcut1_ctbgT[i]->SetMaximum( 0.2 );
           tcut1_ctbgT[i]->SetMinimum( 0.0 );
           tcut1_ctbgT[i]->SetMarkerStyle(22);
           tcut1_ctbgT[i]->SetMarkerSize(1);
           tcut1_ctbgT[i]->SetLineWidth(2);
           tcut1_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
           tcut1_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

           tcut1_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           tcut1_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           tcut1_ctbgT[i]->Draw("AP");
        } else {
           tcut1_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname25 );
   

    // Plot 26
    cout<<" Plot 26 "<<endl;
    TGraphAsymmErrors* tcut2_ctbgT[nModel] ;
    leg3->Clear() ;

    //int nBin2 = RctbgT[0]->GetNbinsX() ;
    TH1D* hLate1    = new TH1D("hLate1",  " ",  nBin1,  0, 4000. );
    TH1D* hFinal1   = new TH1D("hFinal1", " ",  nBin1,  0, 4000. );
    for ( int i=1; i< nModel; i++ ) {

	for ( int j= 1; j <= nBin1 ; j++ ) {
            double nO1 = OctbgT[i]->GetBinContent(j) ;
	    double nL1 = LctbgT[i]->GetBinContent(j) ;
	    if ( nO1 > nL1 ) nO1 = nL1 ;
	    hFinal1->SetBinContent( j, nO1 ) ;
	    hLate1->SetBinContent( j, nL1 ) ;
        }

        tcut2_ctbgT[i]= new TGraphAsymmErrors();
        leg3->AddEntry( hctbgT[i], names[i]  ,  "L");
        //tcut2_ctbgT[i]->BayesDivide( ActbgT[i], RctbgT[i] );
        tcut2_ctbgT[i]->Divide( hFinal1, hLate1 );
        tcut2_ctbgT[i]->SetMarkerColor( color[i] );
        tcut2_ctbgT[i]->SetLineColor( color[i] );

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           tcut2_ctbgT[i]->SetTitle(" Efficiency") ;
           tcut2_ctbgT[i]->SetMaximum( 0.5 );
           tcut2_ctbgT[i]->SetMinimum( 0.0 );
           tcut2_ctbgT[i]->SetMarkerStyle(22);
           tcut2_ctbgT[i]->SetMarkerSize(1);
           tcut2_ctbgT[i]->SetLineWidth(2);
           tcut2_ctbgT[i]->GetXaxis()->SetTitleOffset(1.34);
           tcut2_ctbgT[i]->GetYaxis()->SetTitleOffset(1.41);

           tcut2_ctbgT[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           tcut2_ctbgT[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           tcut2_ctbgT[i]->Draw("AP");
        } else {
           tcut2_ctbgT[i]->Draw("SAMEPS");
        }

    }
    leg3->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname26 );


    delete c0 ;
}

