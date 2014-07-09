#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// Draw the generator information for a particular ctau model
void GenInfo1() {

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TString fileName = "TCuts_GMSB_L180/GMSB100_6000" ;

    TString plotname  = "xPhot_pt.png" ;
    TString plotname1 = "ctbgT_Eff.png" ;
    TString plotname2 = "ctbgT_Acc.png" ;

    TString names[4] = { "ct < 30 ","30 ~ 60 ","60 ~ 90", " > 90 " } ;
    string hName[4] = { "xPhot_pt1", "xPhot_pt2", "xPhot_pt3", "xPhot_pt4" } ;

    string hName1[3] = { "h_ctbgT", "sel_ctbgT", "acc_ctbgT" } ;


    int color[5]     = {     1,    2,     4,    6,  8 } ;
     
    TFile* hfile = TFile::Open( fileName+".root" );

    TH1D*  hPt[4] ;
    for ( int i=0 ; i< 4 ; i++ ) {
        hPt[i]  = (TH1D *) hfile->Get( hName[i].c_str() )  ;
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
    for ( int i = 0; i < 4; i++ ) {
        n_late = hPt[i]->Integral() ;
        hPt[i]->SetLineColor( color[i] ) ;
        //hctbg[i]->SetAxisRange(0,1500) ;
        if ( i == 0 )  hPt[i]->Draw() ;
        else           hPt[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f  ", n_late  ) ;
        leg1->AddEntry( hPt[i], names[i]+legStr ,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( hfolder+plotname );


    // Plot13 and 14 
    TH1D*  hctbgT[3] ;
    for ( int i=0 ; i< 3 ; i++ ) {
        hctbgT[i]  = (TH1D *) hfile->Get( hName1[i].c_str() )  ;
    }

    TH1D* gen_dl_ = hctbgT[0]->Rebin() ;
    TH1D* sel_dl_ = hctbgT[1]->Rebin() ;
    TH1D* acc_dl_ = hctbgT[2]->Rebin() ;

    TH1D* gen_dl  = new TH1D("gen_dl", " ",  25,  0, 2500 );
    TH1D* sel_dl  = new TH1D("sel_dl", " ",  25,  0, 2500 );
    TH1D* acc_dl  = new TH1D("acc_dl", " ",  25,  0, 2500 );
    for ( int i=1; i< 26 ; i++ ) {
        gen_dl->SetBinContent( i , gen_dl_->GetBinContent(i) ) ;
        sel_dl->SetBinContent( i , sel_dl_->GetBinContent(i) ) ;
        acc_dl->SetBinContent( i , acc_dl_->GetBinContent(i) ) ;
    }

    TGraphAsymmErrors* eff_x = new TGraphAsymmErrors();
    eff_x->BayesDivide( sel_dl, gen_dl );
    TGraphAsymmErrors* acc_x = new TGraphAsymmErrors();
    acc_x->BayesDivide( acc_dl, gen_dl );
    c0->cd();
    c0->SetLogy(0);

    eff_x->SetTitle(" Reco_Efficiency ") ;
    eff_x->SetMaximum( 0.4 );
    eff_x->SetMinimum( 0.0 );
    eff_x->SetMarkerColor(4);
    eff_x->SetMarkerStyle(22);
    eff_x->SetMarkerSize(1);
    eff_x->SetLineColor(1);
    eff_x->SetLineWidth(2);
    eff_x->GetXaxis()->SetTitleOffset(1.34);
    eff_x->GetYaxis()->SetTitleOffset(1.41);

    eff_x->GetXaxis()->SetTitle(" Transverse Neutralino Decay length in lab frame (mm) " ) ;
    eff_x->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
    eff_x->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname1 );

    acc_x->SetTitle(" Efficiency*Acceptance ") ;
    acc_x->SetMaximum( 0.2 );
    acc_x->SetMinimum( 0.0 );
    acc_x->SetMarkerColor(4);
    acc_x->SetMarkerStyle(22);
    acc_x->SetMarkerSize(1);
    acc_x->SetLineColor(1);
    acc_x->SetLineWidth(2);
    acc_x->GetXaxis()->SetTitleOffset(1.34);
    acc_x->GetYaxis()->SetTitleOffset(1.41);

    acc_x->GetXaxis()->SetTitle(" Transverse Neutralino Decay length in lab frame (mm) " ) ;
    acc_x->GetYaxis()->SetTitle(" Reco_Efficiency*Time_Acceptance ") ;
    acc_x->Draw("AP");
    c0->Update();
    c0->Print( hfolder + plotname2 );


    delete c0 ;


}

