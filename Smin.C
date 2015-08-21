#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void Smin() {

    gROOT->LoadMacro("CMS_lumi.C");

    TString plotname = "Final2012/SminorCut.png" ;
    string xlable = " S_{minor} " ;
    string ylable = " Entries/0.25 " ;
    string hTitle = "S_{minor}" ;
    string hName = "h_sMin_Time_EB" ;
    string hName1 = "h_sMin_Time" ;


    TFile *file0  = TFile::Open("Phot50/bg_phot50.root");
    TFile *file1  = TFile::Open("TCuts_GMSB_L180/GMSB2J_180_5980_noSmin.root");

    TH2D* smin_t_phot50  = (TH2D *) file0->Get( hName.c_str() )  ;
    TH2D* smin_t_gmsb    = (TH2D *) file1->Get( hName1.c_str() )  ;

    smin_t_phot50->ProjectionX("smin_phot50" ) ;
    smin_t_gmsb->ProjectionX("smin_gmsb", 92,160 ) ;
    //smin_t_phot50->ProjectionX("smin_phot50_late", 92, 160 ) ;

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

    // Plot
    TCanvas* c0 = new TCanvas("c0","", 800, 600);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    c0->SetTopMargin(0.05);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.05);
    c0->SetLogy() ;

    //gPad->SetGridx();
    //gPad->SetGridy();
    c0->cd();

    //smin_phot50->SetTitleFont(42);
    //smin_phot50->SetTitle( hTitle.c_str() ) ;

    //smin_phot50->SetMaximum( 5000 );
    //smin_phot50->SetMinimum( 0.0 );
    //smin_phot50->SetMarkerColor(1);
    //smin_phot50->SetMarkerStyle(22);
    //smin_phot50->SetMarkerSize(1);
    smin_phot50->SetLineColor(1);
    smin_phot50->SetLineWidth(2);
    smin_phot50->GetXaxis()->SetTitleOffset(0.9);
    smin_phot50->GetYaxis()->SetTitleOffset(1.25);
    smin_phot50->GetXaxis()->SetTitleSize(0.06);
    smin_phot50->GetYaxis()->SetTitleSize(0.06);

    smin_phot50->GetXaxis()->SetTitle( xlable.c_str() ) ;
    smin_phot50->GetYaxis()->SetTitle( ylable.c_str() ) ;
    //smin_phot50->GetYaxis()->SetTitle(" Efficiency ") ;
    //smin_phot50->GetXaxis()->SetLimits( xMin2, xMax2 );
    float n_g50 = (float)smin_phot50->Integral() ;
    smin_phot50->Scale( 5000. / n_g50 ) ;
 
    smin_phot50->Draw();
    c0->Update();
    
    //smin_gmsb->SetMarkerColor(2);
    //smin_gmsb->SetMarkerStyle(21);
    //smin_gmsb->SetMarkerSize(1);
    smin_gmsb->SetLineColor(2);
    smin_gmsb->SetLineWidth(2);
    float n_gmsb = (float)smin_gmsb->Integral() ;
    smin_gmsb->Scale( 5000. / n_gmsb ) ;
    smin_gmsb->Draw("sames");
    c0->Update();

    /*
    smin_phot50_late->SetLineColor(4);
    smin_phot50_late->SetLineWidth(2);
    float n_g50_late = (float)smin_phot50_late->Integral() ;
    smin_phot50_late->Scale( 100. / n_g50_late ) ;
    smin_phot50_late->Draw("sames");
    c0->Update();
    */

    // Legend
    TLegend* leg1  = new TLegend(.65, .77, .95, .95 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30], RStr2[30] ;
    sprintf( RStr0,  "Photon50 " ) ;
    sprintf( RStr1,  "GMSB180, T > 3ns" ) ;
    //sprintf( RStr2,  "Photon50 , t > 3ns" ) ;

    leg1->AddEntry( smin_phot50, RStr0,  "L");
    leg1->AddEntry( smin_gmsb, RStr1,  "L");
    //leg1->AddEntry( smin_phot50_late, RStr2,  "L");
    
    leg1->Draw("SAME") ;    
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname );

    delete c0 ;
}


