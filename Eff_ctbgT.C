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

    gROOT->LoadMacro("CMS_lumi.C");

    TString hfolder   = "Final2012/" ;
    TString fileName  = "TCuts_GMSB_L180/GMSB2J_180_" ;
    TString plotname1 = "Eff_dt1dt2.png" ;

    // Lambda 180
    double nGen[5]   = { 50000,  50000,  50000,  50000,  50000  } ;
    TString names[5] = { "1000", "2000", "3950", "6000", "10450" } ;
    string tnames[5] = {  "3.33", "6.67", "13.33", "20", "34.83" } ;
    int color[5]     = {    1,     2,        4,      6,       8  } ;
    const int nModel = 5;

  
    /*
    // Lambda 160
    double nGen[8]   = { 50000,  50000,  50000,  50000,  50000,  50000,  50000,  50000 } ;
    TString names[8] = { "245",  "490",  "975", "1945", "2930", "3910", "5875", "9815" } ;
    int color[8]     = {     1,      2,      3,      4,      5,      6,      7,     8  } ;
    const int nModel = 8 ;
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

    */
    
    TString plotname  = "Accp_ctbgT.png" ;
    string hNameD = "reco_ctbgT" ;
    string hNameN = "lateR_ctbgT" ;
   

    int rbin = 2 ;
    float ymax = 1.0 ;
    float xmax = 1800. ;
    TLegend* leg1  = new TLegend(.55, .60, .78, .88 );
    leg1->Clear() ;
    string legTitle1 = " #Lambda = 180 TeV" ;
    leg1->SetHeader( legTitle1.c_str() );

    //TLegend* leg1  = new TLegend(.40, .25, .65, .55 );
   /*
    TString plotname  = "Eff_acc_ctbgT.png" ;
    string hNameD = "h_ctbgT" ;
    string hNameN = "lateR_ctbgT" ;

    TString plotname = "Eff_reco_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "reco_ctbgT" ;

    TString plotname  = "Eff_hlt_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "hlt_ctbgT" ;

    */
  
    /*
    string hName1 = "h_ctbgT" ;      // All
    string hName2 = "obs_ctbgT" ;    // T available 
    string hName3 = "late_ctbgT" ;   // T > 3ns
    string hName4 = "hlt_ctbgT" ;    // HLT 
    string hName5 = "reco_ctbgT" ;   // EB + Pt > 1 GeV 
    string hName6 = "lateR_ctbgT" ;  // EB + Pt > 1 GeV  + T > 3ns
    string hName6 = "lateR_ctbgT1" ;  // EB + Pt > 1 GeV  + T > 3ns + dt2 < 0.5 
    string hName6 = "lateR_ctbgT2" ;  // EB + Pt > 1 GeV  + T > 3ns + dt2 > 0.5 
    string hName7 = "sel_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60)
    string hName8 = "acc_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60) + T > 3ns
    */

    TFile* hfile[ nModel ] ;
    TH1D*  D_ctbgT[ nModel ] ;
    TH1D*  N_ctbgT[ nModel ] ;

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
    // For the frame:
    gStyle->SetFrameBorderMode(0);
    gStyle->SetFrameBorderSize(1);
    gStyle->SetFrameFillColor(0);
    gStyle->SetFrameFillStyle(0);
    gStyle->SetFrameLineColor(1);
    gStyle->SetFrameLineStyle(1);
    gStyle->SetFrameLineWidth(1);

    gStyle->SetOptStat(kFALSE);
    //gStyle->SetOptFit(111);
    gStyle->SetOptTitle(0);
    //gStyle->SetTitleFontSize(0.05);

    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.04, "XYZ");
 
    // Plots
    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);

    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.05);
    c0->SetLogy();

    //gPad->SetGridx();
    //gPad->SetGridy();
    c0->cd();

    TGraphAsymmErrors* eff[nModel] ;
    for ( int i=0; i< nModel; i++ ) {

        eff[i]= new TGraphAsymmErrors();

        D_ctbgT[i]->Rebin( rbin ) ;
        N_ctbgT[i]->Rebin( rbin ) ;

        eff[i]->Divide( N_ctbgT[i], D_ctbgT[i] );    

        eff[i]->SetMarkerColor( color[i] );
        eff[i]->SetLineColor( color[i] );
        eff[i]->SetLineWidth(2);
        TString entryName =  tnames[i]+" ns" ;
        leg1->AddEntry( eff[i], entryName ,  "L");

        if ( i ==0 ) {
           c0->cd();
           c0->SetLogy(0);

           eff[i]->SetMaximum( ymax );
           eff[i]->SetMinimum( 0.0 );
           eff[i]->SetMarkerStyle(22);
           eff[i]->SetMarkerSize(1);

           eff[i]->GetXaxis()->SetTitleOffset(0.9);
           eff[i]->GetYaxis()->SetTitleOffset(1.25);
	   eff[i]->GetXaxis()->SetTitleSize(0.06);
	   eff[i]->GetYaxis()->SetTitleSize(0.06);
         
           eff[i]->GetXaxis()->SetTitle("Transverse Decay Length (mm)") ;
           eff[i]->GetYaxis()->SetTitle("Efficiency / 100 mm") ;
           eff[i]->GetXaxis()->SetRangeUser(0, xmax ) ;
           eff[i]->Draw("AP");
        } else {
           eff[i]->Draw("SAMEPS");
        }
    }
    leg1->Draw("sames") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( hfolder + plotname );

    // Another plot 
    //TFile* hfile1 = TFile::Open( fileName+names[nModel-2]+".root" );
    //cout<<  fileName+names[nModel-2]+".root" << endl ;

    TH1D*  h_reco   = (TH1D *) hfile[nModel-1]->Get( "reco_ctbgT" )  ;
    TH1D*  h_dt1    = (TH1D *) hfile[nModel-1]->Get( "lateR_ctbgT1" )  ;
    TH1D*  h_dt2    = (TH1D *) hfile[nModel-1]->Get( "lateR_ctbgT2" )  ;

    TGraphAsymmErrors* eff_dt1 = new TGraphAsymmErrors(); ;
    TGraphAsymmErrors* eff_dt2 = new TGraphAsymmErrors(); ;
    leg1->Clear() ;

    //h_reco->Rebin( rbin ) ;
    h_dt1->Rebin( rbin ) ;
    h_dt2->Rebin( rbin ) ;

    eff_dt1->Divide( h_dt1, h_reco );    
    eff_dt2->Divide( h_dt2, h_reco );    

    eff_dt1->SetMarkerColor( 2 );
    eff_dt1->SetLineColor( 2 );
    eff_dt1->SetMarkerSize(1);
    eff_dt1->SetLineWidth(2);
    eff_dt2->SetMarkerColor( 4 );
    eff_dt2->SetLineColor( 4 );
    eff_dt2->SetMarkerSize(1);
    eff_dt2->SetLineWidth(2);
    //eff_dt2->SetMarkerStyle(22);

    c0->cd();
    c0->SetLogy(0);

    eff_dt1->SetMaximum( 1.0 );
    eff_dt1->SetMinimum( 0.0 );

    eff_dt1->GetXaxis()->SetTitleOffset(0.9);
    eff_dt1->GetYaxis()->SetTitleOffset(1.25);
    eff_dt1->GetXaxis()->SetTitleSize(0.06);
    eff_dt1->GetYaxis()->SetTitleSize(0.06);

    eff_dt1->GetXaxis()->SetTitle("Transverse Decay Length (mm)") ;
    eff_dt1->GetYaxis()->SetTitle("Efficiency / 100 mm") ;
    eff_dt1->GetXaxis()->SetRangeUser(0, xmax ) ;
    eff_dt1->Draw("AP");

    eff_dt2->Draw("SAMEPS");
    c0->Update();

    TLegend* leg2  = new TLegend(.55, .65, .8, .88 );
    TString legTitle = " #tau = " + tnames[nModel-2] + " ns " ;
    leg2->SetTextSize(0.030) ;
    leg2->SetHeader( legTitle );
    leg2->AddEntry( eff_dt1, "#Delta t2 < 0.5 ns" ,  "L");
    leg2->AddEntry( eff_dt2, "#Delta t2 > 0.5 ns" ,  "L");
    leg2->Draw("sames") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( hfolder + plotname1 );
    delete c0 ;
}

