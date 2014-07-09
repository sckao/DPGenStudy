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

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TString fileName = "TCuts_GMSB_L180/GMSB180_2J_" ;

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
    TString plotname17 = "Accept_ctau.png" ;

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

    /* 
    double nGen[5] = { 50112, 50112, 50112, 50112, 50112 } ;
    TString names[5] = { "250","500", "2000", "4000", "6000" } ;
    int color[5]     = {     1,    2,      4,      6,     8  } ;
    const int nModel = 5;
    */
    
    double nGen[7]   = { 50112, 50112, 50112,  50112,  50112,  46944,  50112 } ;
    TString names[7] = { "250", "500","1000", "2000", "3000", "4000", "6000" } ;
    int color[7]     = {     1,     2,     4,      5,      6,      7,      8 } ;
    const int nModel = 7;
    
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
    TH1D*  Octbg[ nModel ] ;
    TH1D*  ActbgT[ nModel ] ;

    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );
        hctbg[i]  = (TH1D *) hfile[i]->Get( hName.c_str() )  ;
        hCtau[i]  = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        Sel_Ctau[i]   = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
        Acc_Ctau[i]   = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
        hlateXbeta[i] = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
        hXbeta[i]     = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
        PassCtau[i] = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
        lateXPt[i]  = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
        hXPt[i]     = (TH1D *) hfile[i]->Get( hName8.c_str() )  ;
        hctbgT[i]   = (TH1D *) hfile[i]->Get( hName9.c_str() )  ;
	SctbgT[i]   = (TH1D *) hfile[i]->Get( hName10.c_str() )  ;
        OctbgT[i]   = (TH1D *) hfile[i]->Get( hName11.c_str() )  ;
        Octbg[i]    = (TH1D *) hfile[i]->Get( hName12.c_str() )  ;
        ActbgT[i]   = (TH1D *) hfile[i]->Get( hName13.c_str() )  ;
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
        if ( i ==0 )  hCtau[i]->Draw() ;
        else          hCtau[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
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

    // Plot16 and 17 - Efficiency Plots in different ctau Models
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
    //TGraphAsymmErrors* acp_x0 = new TGraphAsymmErrors();
    //acp_x0->BayesDivide( hObs, hRec );

    c0->cd();
    c0->SetLogy(0);

    eff_x0->SetTitle(" Reco_Efficiency ") ;
    eff_x0->SetMaximum( 0.9 );
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
    acc_x0->GetYaxis()->SetTitleOffset(1.41);

    acc_x0->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    acc_x0->GetYaxis()->SetTitle(" Reco_Efficiency*Time_Acceptance ") ;
    acc_x0->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname17 );


    delete c0 ;
}

