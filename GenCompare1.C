#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void GenCompare1() {

    TString hfolder  = "Compare_GMSB_L180/" ;
    TFile *file0  = TFile::Open("TCuts_GMSB_L180/GMSB180_2J_6000.root");
    TFile *file1  = TFile::Open("NewGMSB_L180/GMSB180_2000.root");

    TString plotname1 = "PhotonTime.png" ;

    TH1D* h_time0  = (TH1D *) file0->Get( "obsTime" )  ;
    TH1D* h_time1  = (TH1D *) file1->Get( "sel_Time" )  ;

    gStyle->SetOptStat("");

    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    gPad->SetGridx();
    //c0->SetLeftMargin(0.15);
    //c0->SetRightMargin(0.12);
    //c0->SetTopMargin(0.1);
    //c0->SetBottomMargin(0.12);

    c0->cd();
    c0->SetLogy();
    gStyle->SetOptStat(kFALSE);
    
    // Plot 1
    h_time0->SetLineColor(2) ;
    h_time0->Draw() ;
    c0->Update();

    h_time1->SetLineColor(4) ;
    h_time1->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    TLegend* leg1  = new TLegend(.62, .75, .9, .90 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;
    char legStr0[100], legStr1[100] ;
    sprintf( legStr0, "Old (6k): %.0f/%.0f = %.2f", h_time0->Integral(71,160), h_time0->Integral(), h_time0->Integral(71,160)/h_time0->Integral() ) ;
    sprintf( legStr1, "New (2k): %.0f/%.0f = %.2f", h_time1->Integral(71,160), h_time1->Integral(), h_time1->Integral(71,160)/h_time1->Integral() ) ;

    leg1->AddEntry( h_time0, legStr0,  "L");
    leg1->AddEntry( h_time1, legStr1,  "L");
    
    leg1->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname1 );

    delete c0 ;
}

