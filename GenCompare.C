#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void GenCompare() {

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TFile *file0  = TFile::Open("TCuts_GMSB_L180/GMSB180_2J_4000.root");
    TFile *file1  = TFile::Open("TCuts_GMSB_L100/GMSB100_2J_2000.root");

    string hName1 = "h_gen1RecoPt" ;
    string hName2 = "h_met" ;
    string hName3 = "h_xbeta" ;
    string hName4 = "h_lateXbeta" ;
    string hName5 = "h_lateXctau" ;

    TString plotname1 = "GenPhotonPt.png" ;
    TString plotname2 = "pfMET.png" ;
    TString plotname3 = "NeutralinoBeta.png" ;
    TString plotname4 = "LateNeutralinoBeta.png" ;
    TString plotname5 = "LateNeutralinoCtau.png" ;

    TH1D* h_pt0  = (TH1D *) file0->Get( hName1.c_str() )  ;
    TH1D* h_pt1  = (TH1D *) file1->Get( hName1.c_str() )  ;

    TH1D* h_met0  = (TH1D *) file0->Get( hName2.c_str() )  ;
    TH1D* h_met1  = (TH1D *) file1->Get( hName2.c_str() )  ;

    TH1D* h_beta0 = (TH1D *) file0->Get( hName3.c_str() )  ;
    TH1D* h_beta1 = (TH1D *) file1->Get( hName3.c_str() )  ;

    TH1D* h_lateBeta0 = (TH1D *) file0->Get( hName4.c_str() )  ;
    TH1D* h_lateBeta1 = (TH1D *) file1->Get( hName4.c_str() )  ;

    TH1D* h_lateCtau0 = (TH1D *) file0->Get( hName5.c_str() )  ;
    TH1D* h_lateCtau1 = (TH1D *) file1->Get( hName5.c_str() )  ;

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
    h_pt1->SetLineColor(2) ;
    h_pt1->Draw() ;
    c0->Update();

    h_pt0->SetLineColor(4) ;
    h_pt0->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    TLegend* leg1  = new TLegend(.62, .75, .9, .90 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    leg1->AddEntry( h_pt0, "#Lambda 180, c#tau 4000mm",  "L");
    leg1->AddEntry( h_pt1, "#Lambda 100, c#tau 2000mm",  "L");
    
    leg1->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname1 );

    // Plot 2
    h_met1->SetLineColor(2) ;
    h_met1->Draw() ;
    c0->Update();

    h_met0->SetLineColor(4) ;
    h_met0->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    leg1->AddEntry( h_met0, "#Lambda 180, c#tau 4000mm",  "L");
    leg1->AddEntry( h_met1, "#Lambda 100, c#tau 2000mm",  "L");
    
    leg1->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname2 );

    // Plot 3
    c0->SetLogy(0) ;
    h_beta0->SetLineColor(4) ;
    h_beta0->Draw() ;
    c0->Update();

    //h_beta1->Scale( h_beta0->Integral()/h_beta1->Integral() ) ;
    h_beta1->SetLineColor(2) ;
    h_beta1->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    TLegend* leg2  = new TLegend(.15, .75, .43, .90 );
    leg2->Clear();
    leg2->SetTextSize(0.03) ;
    
    leg2->AddEntry( h_beta0, "#Lambda 180, c#tau 4000mm",  "L");
    leg2->AddEntry( h_beta1, "#Lambda 100, c#tau 2000mm",  "L");
    
    leg2->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname3 );

    // Plot 4
    c0->SetLogy(0) ;
    h_lateBeta0->SetLineColor(4) ;
    h_lateBeta0->Draw() ;
    c0->Update();

    h_lateBeta1->Scale( h_lateBeta0->Integral()/h_lateBeta1->Integral() ) ;
    h_lateBeta1->SetLineColor(2) ;
    h_lateBeta1->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    leg1->Clear();
    leg1->SetTextSize(0.03) ;
    
    leg1->AddEntry( h_lateBeta0, "#Lambda 180, c#tau 4000mm",  "L");
    leg1->AddEntry( h_lateBeta1, "#Lambda 100, c#tau 2000mm",  "L");
    
    leg1->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname4 );

    // Plot 5
    h_lateCtau0->SetLineColor(4) ;
    h_lateCtau0->Draw() ;
    c0->Update();

    h_lateCtau1->Scale( h_lateCtau0->Integral()/h_lateCtau1->Integral() ) ;
    h_lateCtau1->SetLineColor(2) ;
    h_lateCtau1->DrawCopy("SAMES") ;
    c0->Update();
    
    // Legend
    leg1->Clear();
    leg1->SetTextSize(0.03) ;
    
    leg1->AddEntry( h_lateCtau0, "#Lambda 180, c#tau 4000mm",  "L");
    leg1->AddEntry( h_lateCtau1, "#Lambda 100, c#tau 2000mm",  "L");
    
    leg1->Draw("SAMES") ;    
    c0->Update();

    c0->Print( hfolder + plotname5 );

    delete c0 ;
}

