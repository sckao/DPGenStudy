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

    gROOT->LoadMacro("CMS_lumi.C");

    
    TString plotname  = "Final2012/test_PhotPt1.png" ;
    TString plotname1 = "Final2012/test_photPt2.png" ;
    string xlable = "Photon P_{T} (GeV/c) " ;
    string hTitle = "Photon P_{T}" ;
    //string hName = "h_lateGPt" ;
    //string hName = "h_g1Pt" ;
    //string hName = "m_RecoPt" ;
    string hName = "reco_gPt" ;
    
    /*
    TString plotname  = "Final2012/GMSB_MET.png" ;
    TString plotname1 = "Final2012/MET_Comparison.png" ;
    string xlable = "Missing E_{T} (GeV/c) " ;
    string hTitle = " Missing E_{T}" ;
    string hName  = "h_met" ;
    */

    
    TFile *file0  = TFile::Open("TCuts_GMSB_L100/GMSB2J_100_6000.root");
    TFile *file1  = TFile::Open("TCuts_GMSB_L140/GMSB2J_140_6000.root");
    TFile *file2  = TFile::Open("TCuts_GMSB_L180/GMSB2J_180_6000.root");
    TFile *file3  = TFile::Open("TCuts_GMSB_L220/GMSB2J_220_6000.root");
    //TFile *file0  = TFile::Open("TCuts_GMSB_L180/GMSB2J_180_10450.root");
    //TFile *file1  = TFile::Open("TCuts_GMSB_L140/GMSB2J_140_10450.root");
    //TFile *file2  = TFile::Open("TCuts_GMSB_L100/GMSB2J_100_9330.root");
    //TFile *file3  = TFile::Open("TCuts_GMSB_L300/GMSB2J_300_10450.root");
    TFile *file4  = TFile::Open("TCuts_RunBCD_new/testRunD_2J.root");
    TFile *file5  = TFile::Open("MCQCD/test_gjets.root");

    TH1D* h0_Pt  = (TH1D *) file0->Get( hName.c_str() )  ;
    TH1D* h1_Pt  = (TH1D *) file1->Get( hName.c_str() )  ;
    TH1D* h2_Pt  = (TH1D *) file2->Get( hName.c_str() )  ;
    TH1D* h3_Pt  = (TH1D *) file3->Get( hName.c_str() )  ;

    TH1D* hData_Pt  = (TH1D *) file4->Get( hName.c_str() )  ;
    TH1D* hGJet_Pt  = (TH1D *) file5->Get( hName.c_str() )  ;

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
    gStyle->SetLabelSize(0.05, "XYZ");
    //gPad->SetGridx();

    
    // Plot
    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.05);
    c0->SetLogy() ;

    c0->cd();

    h0_Pt->SetTitle( hTitle.c_str() ) ;
    h0_Pt->SetMaximum( 8000 );
    //h0_Pt->SetMinimum( 0.0 );
    //h0_Pt->SetMarkerColor(1);
    //h0_Pt->SetMarkerStyle(22);
    //h0_Pt->SetMarkerSize(1);
    h0_Pt->SetLineColor(1);
    h0_Pt->SetLineWidth(2);
    h0_Pt->GetXaxis()->SetTitleOffset(0.9);
    h0_Pt->GetYaxis()->SetTitleOffset(1.25);

    h0_Pt->GetXaxis()->SetTitleSize(0.06);
    h0_Pt->GetYaxis()->SetTitleSize(0.06);

    h0_Pt->GetXaxis()->SetTitle( xlable.c_str() ) ;
    h0_Pt->GetYaxis()->SetTitle(" Entries / 10 GeV ") ;
    //h0_Pt->GetXaxis()->SetLimits( xMin2, xMax2 );
    h0_Pt->GetYaxis()->SetLimits( 1, 4000. );
    double n180 = h0_Pt->Integral() ;
    h0_Pt->Scale( 10000. / n180 ) ;
 
    h0_Pt->Draw();
    c0->Update();
    
    //h1_Pt->SetMarkerColor(2);
    //h1_Pt->SetMarkerStyle(21);
    //h1_Pt->SetMarkerSize(1);
    h1_Pt->SetLineColor(2);
    h1_Pt->SetLineWidth(2);
    double n140 = h1_Pt->Integral() ;
    h1_Pt->Scale( 10000. / n140 ) ;
    h1_Pt->Draw("sames");
    c0->Update();

    //h2_Pt->SetMarkerColor(4);
    //h2_Pt->SetMarkerStyle(20);
    //h2_Pt->SetMarkerSize(1);
    h2_Pt->SetLineColor(4);
    h2_Pt->SetLineWidth(2);
    double n100 = h2_Pt->Integral() ;
    h2_Pt->Scale( 10000. / n100  ) ;
    h2_Pt->Draw("sames");
    c0->Update();

    h3_Pt->SetLineColor(6);
    h3_Pt->SetLineWidth(2);
    double n300 = h3_Pt->Integral() ;
    h3_Pt->Scale( 10000. / n300 ) ;
    h3_Pt->Draw("sames");
    c0->Update();

    // Legend
    TLegend* leg1  = new TLegend(.7, .7, .9, .9 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30], RStr2[30], RStr3[30], RStr4[30] ;
    //sprintf( RStr0,  "#Lambda 100 (%d)", h2_Pt->Integral(5,51) ) ;
    //sprintf( RStr1,  "#Lambda 140 (%d)", h1_Pt->Integral(5,51) ) ;
    //sprintf( RStr2,  "#Lambda 180 (%d)", h0_Pt->Integral(5,51) ) ;
    //sprintf( RStr3,  "#Lambda 300 (%d)", h3_Pt->Integral(5,51) ) ;
    
    sprintf( RStr0,  "#Lambda 100" ) ;
    sprintf( RStr1,  "#Lambda 140" ) ;
    sprintf( RStr2,  "#Lambda 180" ) ;
    sprintf( RStr3,  "#Lambda 220" ) ;

    /* 
    sprintf( RStr0,  "c#tau   1 m" ) ;
    sprintf( RStr1,  "c#tau   6 m" ) ;
    sprintf( RStr2,  "c#tau  10 m" ) ;
    sprintf( RStr3,  "c#tau  0.5m" ) ;
    */

    leg1->AddEntry( h0_Pt, RStr0,  "L");
    leg1->AddEntry( h1_Pt, RStr1,  "L");
    leg1->AddEntry( h2_Pt, RStr2,  "L");
    leg1->AddEntry( h3_Pt, RStr3,  "L");
    
    leg1->Draw("SAME") ;    
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname );

     cout<<"  === plot 2  === "<<endl ;
    // Plot 2
    c0->Clear() ;
    hData_Pt->SetTitle( hTitle.c_str() ) ;
    //hData_Pt->SetMaximum( 5000 );
    //hData_Pt->SetMinimum( 0.0 );
    //hData_Pt->SetMarkerColor(1);
    //hData_Pt->SetMarkerStyle(22);
    //hData_Pt->SetMarkerSize(1);
    hData_Pt->SetLineColor(1);
    hData_Pt->SetLineWidth(2);
    hData_Pt->GetXaxis()->SetTitleOffset(0.9);
    hData_Pt->GetYaxis()->SetTitleOffset(1.25);

    hData_Pt->GetXaxis()->SetTitleSize(0.06);
    hData_Pt->GetYaxis()->SetTitleSize(0.06);

    hData_Pt->GetXaxis()->SetTitle( xlable.c_str() ) ;
    hData_Pt->GetYaxis()->SetTitle(" Entries / 10 GeV ") ;
    //hData_Pt->GetXaxis()->SetLimits( xMin2, xMax2 );
    hData_Pt->GetYaxis()->SetLimits( 1, 4000. );
    double nData = hData_Pt->Integral() ;
    //cout<<" nData = "<< nData <<" -> " << 10000/nData <<endl ;
    hData_Pt->Scale( 10000. / nData ) ;
 
    hData_Pt->Draw();
    c0->Update();

    hGJet_Pt->SetLineColor(2);
    hGJet_Pt->SetLineWidth(2);
    double nGJet = hGJet_Pt->Integral() ;
    hGJet_Pt->Scale( 10000. / nGJet ) ;
    hGJet_Pt->Draw("sames");
    c0->Update();

    h1_Pt->SetLineColor(4);
    h1_Pt->SetLineWidth(2);
    h1_Pt->Scale( 10000. / n140 ) ;
    h1_Pt->Draw("sames");
    c0->Update();

    TLegend* leg2  = new TLegend(.63, .72, .92, .92 );
    leg2->Clear();
    leg2->SetTextSize(0.03) ;

    leg2->AddEntry( hData_Pt, "Data",  "L");
    leg2->AddEntry( hGJet_Pt, "#gamma + Jets",  "L");
    leg2->AddEntry( h1_Pt,  "GMSB (#Lambda 180TeV)",  "L");
    
    leg2->Draw("SAME") ;    
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname1 );

    delete c0 ;
}


