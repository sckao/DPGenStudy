#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Eff_ctbgT() {

    TString hfolder  = "TCuts_GMSB_L160/" ;
    TString fileName = "TCuts_GMSB_L160/GMSB2J_160_" ;

    // Lambda 160
    double nGen[8]   = { 50000,  50000,  50000,  50000,  50000,  50000,  50000,  50000 } ;
    TString names[8] = { "245",  "490",  "975", "1945", "2930", "3910", "5875", "9815" } ;
    int color[8]     = {     1,      2,      3,      4,      5,      6,      7,     8  } ;
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
    
   /*
    TString plotname_hlt  = "Eff_hlt_ctbgT.png" ;
    TString plotname_reco = "Eff_reco_ctbgT.png" ;
    TString plotname_sel  = "Eff_sel_ctbgT.png" ;
   */
    TString plotname  = "Eff_lateReco_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "lateR_ctbgT" ;
  
    string xlable = "ctbgT" ;
    int rbin = 2 ;
    float ymax = 0.8 ;
    float xmax = 1800. ;
    /*
    string hName1 = "h_ctbgT" ;      // All
    string hName2 = "obs_ctbgT" ;    // T available 
    string hName3 = "late_ctbgT" ;   // T > 3ns
    string hName4 = "hlt_ctbgT" ;    // HLT 
    string hName5 = "reco_ctbgT" ;   // EB + Pt > 1 GeV 
    string hName6 = "lateR_ctbgT" ;  // EB + Pt > 1 GeV  + T > 3ns
    string hName7 = "sel_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60)
    string hName8 = "acc_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60) + T > 3ns
    */

    TFile* hfile[ nModel ] ;
    TH1D*  D_ctbgT[ nModel ] ;
    TH1D*  N_ctbgT[ nModel ] ;

    /*
    TH1D*  h_ctbgT[ nModel ] ;
    TH1D*  Obs_ctbgT[ nModel ] ;
    TH1D*  Late_ctbgT[ nModel ] ;
    TH1D*  HLT_ctbgT[ nModel ] ;
    TH1D*  Reco_ctbgT[ nModel ] ;
    TH1D*  LRec_ctbgT[ nModel ] ;
    TH1D*  Sel_ctbgT[ nModel ] ;
    TH1D*  Acc_ctbgT[ nModel ] ;
    */

    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );

        D_ctbgT[i]    = (TH1D *) hfile[i]->Get( hNameD.c_str() )  ;
        N_ctbgT[i]    = (TH1D *) hfile[i]->Get( hNameN.c_str() )  ;
        /*
        h_ctbgT[i]      = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        Obs_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
	Late_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
        HLT_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
        Reco_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
        LRec_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
        Sel_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
        Acc_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName8.c_str() )  ;
        */
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

    TLegend* leg1  = new TLegend(.80, .65, .95, .90 );
    TGraphAsymmErrors* eff[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {

        eff[i]= new TGraphAsymmErrors();

        D_ctbgT[i]->Rebin( rbin ) ;
        N_ctbgT[i]->Rebin( rbin ) ;
        /*
        h_ctbgT[i]->Rebin(2) ;
	Obs_ctbgT[i]->Rebin(2) ;
	Late_ctbgT[i]->Rebin(2) ;
	HLT_ctbgT[i]->Rebin(2) ;
	Reco_ctbgT[i]->Rebin(2) ;
	LRec_ctbgT[i]->Rebin(2) ;
	Sel_ctbgT[i]->Rebin(2) ;
	Acc_ctbgT[i]->Rebin(2) ;
        */

        eff[i]->Divide( N_ctbgT[i], D_ctbgT[i] );    

        eff[i]->SetMarkerColor( color[i] );
        eff[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff[i], names[i] ,  "L");

        if ( i ==0 ) {
           c0->cd();
           c0->SetLogy(0);

           eff[i]->SetTitle(" Efficiency") ;
           eff[i]->SetMaximum( ymax );
           eff[i]->SetMinimum( 0.0 );
           eff[i]->SetMarkerStyle(22);
           eff[i]->SetMarkerSize(1);
           eff[i]->SetLineWidth(2);
           eff[i]->GetXaxis()->SetTitleOffset(1.34);
           eff[i]->GetYaxis()->SetTitleOffset(1.41);

           eff[i]->GetXaxis()->SetTitle("Neutralino Decay Length (mm)") ;
           eff[i]->GetYaxis()->SetTitle("Efficiency") ;
           eff[i]->GetXaxis()->SetRangeUser(0, xmax ) ;
           eff[i]->Draw("AP");
        } else {
           eff[i]->Draw("SAMEPS");
        }
    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname );

    // Plot 1 
    /*
    TLegend* leg1  = new TLegend(.80, .65, .95, .90 );
    TGraphAsymmErrors* eff_hlt[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {

        eff_hlt[i]= new TGraphAsymmErrors();

        h_ctbgT[i]->Rebin(2) ;
	Obs_ctbgT[i]->Rebin(2) ;
	Late_ctbgT[i]->Rebin(2) ;
	HLT_ctbgT[i]->Rebin(2) ;
	Reco_ctbgT[i]->Rebin(2) ;
	LRec_ctbgT[i]->Rebin(2) ;
	Sel_ctbgT[i]->Rebin(2) ;
	Acc_ctbgT[i]->Rebin(2) ;
  
        //eff_ctbgT[i]->BayesDivide( ActbgT[i], hctbgT[i] );
        eff_hlt[i]->BayesDivide( HLT_ctbgT[i], Obs_ctbgT[i] );    // including other event selection like MET ...
        eff_hlt[i]->SetMarkerColor( color[i] );
        eff_hlt[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_hlt[i], names[i] ,  "L");

        if ( i ==0 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_hlt[i]->SetTitle(" Efficiency") ;
           eff_hlt[i]->SetMaximum( 1.0 );
           eff_hlt[i]->SetMinimum( 0.0 );
           eff_hlt[i]->SetMarkerStyle(22);
           eff_hlt[i]->SetMarkerSize(1);
           eff_hlt[i]->SetLineWidth(2);
           eff_hlt[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_hlt[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_hlt[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           eff_hlt[i]->GetYaxis()->SetTitle(" HLT Efficiency ") ;
           eff_hlt[i]->Draw("AP");
        } else {
           eff_hlt[i]->Draw("SAMEPS");
        }
    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname_hlt );

    // Plot 2
    TGraphAsymmErrors* eff_reco[nModel] ;
    leg1->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_reco[i]= new TGraphAsymmErrors();

        eff_reco[i]->BayesDivide( Reco_ctbgT[i], Obs_ctbgT[i] );
        eff_reco[i]->SetMarkerColor( color[i] );
        eff_reco[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_reco[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_reco[i]->SetTitle(" Efficiency") ;
           eff_reco[i]->SetMaximum( 1.0 );
           eff_reco[i]->SetMinimum( 0.0 );
           eff_reco[i]->SetMarkerStyle(22);
           eff_reco[i]->SetMarkerSize(1);
           eff_reco[i]->SetLineWidth(2);
           eff_reco[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_reco[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_reco[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           eff_reco[i]->GetYaxis()->SetTitle(" Reco Efficiency ") ;
           eff_reco[i]->Draw("AP");
        } else {
           eff_reco[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname_reco );
   

    // Plot 3
    TGraphAsymmErrors* eff_sel[nModel] ;
    leg1->Clear() ;

    for ( int i=1; i< nModel; i++ ) {

        eff_sel[i]= new TGraphAsymmErrors();
        eff_sel[i]->BayesDivide( Sel_ctbgT[i], Obs_ctbgT[i] );
        eff_sel[i]->SetMarkerColor( color[i] );
        eff_sel[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_sel[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_sel[i]->SetTitle(" Efficiency") ;
           eff_sel[i]->SetMaximum( 0.5 );
           eff_sel[i]->SetMinimum( 0.0 );
           eff_sel[i]->SetMarkerStyle(22);
           eff_sel[i]->SetMarkerSize(1);
           eff_sel[i]->SetLineWidth(2);
           eff_sel[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_sel[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_sel[i]->GetXaxis()->SetTitle(" Neutralino Decay Length (mm) " ) ;
           eff_sel[i]->GetYaxis()->SetTitle(" Selection Efficiency ") ;
           eff_sel[i]->Draw("AP");
        } else {
           eff_sel[i]->Draw("SAMEPS");
        }

        
    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname_sel );
    */

    delete c0 ;
}

