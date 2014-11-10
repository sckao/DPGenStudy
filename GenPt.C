#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void GenPt() {

    TString plotname = "GMSB_PhotPt.png" ;
    string xlable = "Photon P_{T} (GeV/c) " ;
    string hTitle = "Late Photon P_{T}" ;
    string hName = "h_lateGPt" ;
    //string hName = "h_g1Pt" ;
    
    /*
    TString plotname = "GMSB_MET.png" ;
    string xlable = "Missing E_{T} (GeV/c) " ;
    string hTitle = " Missing E_{T}" ;
    string hName = "h_met" ;
    */

    TFile *file0  = TFile::Open("TCuts_GMSB_L180/GMSB2J_180_10450.root");
    TFile *file1  = TFile::Open("TCuts_GMSB_L140/GMSB2J_140_10450.root");
    TFile *file2  = TFile::Open("TCuts_GMSB_L100/GMSB2J_100_9330.root");
    TFile *file3  = TFile::Open("TCuts_GMSB_L300/GMSB2J_300_12000.root");

    TH1D* h180_Pt  = (TH1D *) file0->Get( hName.c_str() )  ;
    TH1D* h140_Pt  = (TH1D *) file1->Get( hName.c_str() )  ;
    TH1D* h100_Pt  = (TH1D *) file2->Get( hName.c_str() )  ;
    TH1D* h300_Pt  = (TH1D *) file3->Get( hName.c_str() )  ;

    gStyle->SetOptStat("");
    
    // Plot
    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    //gPad->SetGridx();
    //gPad->SetGridy();
    c0->SetLeftMargin(0.15);
    c0->SetRightMargin(0.12);
    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.12);
    c0->SetLogy() ;

    c0->cd();
    gStyle->SetOptStat(kFALSE);
    //gStyle->SetOptFit(111);

    h180_Pt->SetTitle( hTitle.c_str() ) ;
    h180_Pt->SetMaximum( 5000 );
    //h180_Pt->SetMinimum( 0.0 );
    //h180_Pt->SetMarkerColor(1);
    //h180_Pt->SetMarkerStyle(22);
    //h180_Pt->SetMarkerSize(1);
    h180_Pt->SetLineColor(1);
    h180_Pt->SetLineWidth(2);
    h180_Pt->GetXaxis()->SetTitleOffset(1.34);
    h180_Pt->GetYaxis()->SetTitleOffset(1.39);

    h180_Pt->GetXaxis()->SetTitle( xlable.c_str() ) ;
    //h180_Pt->GetYaxis()->SetTitle(" Efficiency ") ;
    //h180_Pt->GetXaxis()->SetLimits( xMin2, xMax2 );
    h180_Pt->GetYaxis()->SetLimits( 0, 4000. );
    
    //h180_Pt->Scale( 10000. / h180_Pt->Integral() ) ;
 
    h180_Pt->Draw();
    c0->Update();
    
    //h140_Pt->SetMarkerColor(2);
    //h140_Pt->SetMarkerStyle(21);
    //h140_Pt->SetMarkerSize(1);
    h140_Pt->SetLineColor(2);
    h140_Pt->SetLineWidth(2);
    //h140_Pt->Scale( 10000. / h140_Pt->Integral() ) ;
    h140_Pt->Draw("sames");
    c0->Update();

    //h100_Pt->SetMarkerColor(4);
    //h100_Pt->SetMarkerStyle(20);
    //h100_Pt->SetMarkerSize(1);
    h100_Pt->SetLineColor(4);
    h100_Pt->SetLineWidth(2);
    //h100_Pt->Scale( 10000. / h100_Pt->Integral() ) ;
    h100_Pt->Draw("sames");
    c0->Update();

    h300_Pt->SetLineColor(6);
    h300_Pt->SetLineWidth(2);
    //h300_Pt->Scale( 10000. / h100_Pt->Integral() ) ;
    h300_Pt->Draw("sames");
    c0->Update();

    // Legend
    TLegend* leg1  = new TLegend(.65, .7, .9, .9 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30], RStr2[30], RStr3[30] ;
    sprintf( RStr0,  "#Lambda 100 (%d)", h100_Pt->Integral(5,51) ) ;
    sprintf( RStr1,  "#Lambda 140 (%d)", h140_Pt->Integral(5,51) ) ;
    sprintf( RStr2,  "#Lambda 180 (%d)", h180_Pt->Integral(5,51) ) ;
    sprintf( RStr3,  "#Lambda 300 (%d)", h300_Pt->Integral(5,51) ) ;

    leg1->AddEntry( h100_Pt, RStr0,  "L");
    leg1->AddEntry( h140_Pt, RStr1,  "L");
    leg1->AddEntry( h180_Pt, RStr2,  "L");
    leg1->AddEntry( h300_Pt, RStr3,  "L");
    
    leg1->Draw("SAME") ;    
    c0->Update();

    c0->Print( plotname );

    delete c0 ;
}


