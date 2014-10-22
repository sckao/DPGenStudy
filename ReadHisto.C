#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void ReadHisto() {


    TString hfolder  = "TCuts_RunBCD_new/" ;
    TString plotname = hfolder + "TriggerPhotonPt.png" ;

    TString fName0 = "histo_trig_pho50.root" ;
    TString fName1 = "histo_trig_gmsb.root" ;
    TString fName2 = "histo_trig_gj80.root" ;

    TFile *file0  = TFile::Open( hfolder+fName0 );
    TFile *file1  = TFile::Open( hfolder+fName1 );
    TFile *file2  = TFile::Open( hfolder+fName2 );

    string hName = "h_gPt_trg" ;

    TH1D* h_data  = (TH1D *) file0->Get( hName.c_str() )  ;
    TH1D* h_gmsb  = (TH1D *) file1->Get( hName.c_str() )  ;
    TH1D* h_gjet  = (TH1D *) file2->Get( hName.c_str() )  ;


    gStyle->SetOptStat("");
 
    // Plot

    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
 
    // Style setup    
    gPad->SetGridx();
    gPad->SetGridy();
    c0->SetLeftMargin(0.15);
    c0->SetRightMargin(0.12);
    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.12);

    c0->cd();
    gStyle->SetOptStat(kFALSE);
    c0->SetLogy() ;

    // draw the histograms
    h_data->GetXaxis()->SetTitle( " P_{T}  GeV/c" );

    h_data->SetLineColor(1) ;
    h_data->SetLineWidth(2) ;
    h_data->Draw() ;

    h_gmsb->SetLineColor(2) ;  // red
    h_gmsb->SetLineWidth(2) ;
    h_gmsb->DrawCopy("sames") ;

    h_gjet->SetLineColor(4) ;  // blue
    h_gjet->SetLineWidth(2) ;
    h_gjet->DrawCopy("sames") ;

    // Set up Legend
    TLegend* leg1  = new TLegend(.7, .7, .9, .9 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    leg1->AddEntry( h_data, "Data",   "L");
    leg1->AddEntry( h_gmsb, "GMSB",   "L");
    leg1->AddEntry( h_gjet, "G+jets", "L");
    
    leg1->Draw("SAME") ;    
    c0->Update();

    c0->Print( plotname );

    delete c0 ;
}

