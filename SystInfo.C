#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void SystInfo() {

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TString fileName = "TCuts_GMSB_L180/GMSB180_2J_250" ;

    TString plotname0 = "Syst_nJets.png" ;
    TString plotname1 = "Syst_met1.png" ;
    TString plotname2 = "Syst_met2.png" ;

    string hName0 = "h_nJets" ;
    string hName1 = "h_met1" ;
    string hName2 = "h_met2" ;

    /* 
    double nGen[7]   = { 50112, 50112, 50112,  50112,  50112,  46944,  50112 } ;
    TString names[7] = { "250", "500","1000", "2000", "3000", "4000", "6000" } ;
    int color[7]     = {     1,     2,     4,      5,      6,      7,      8 } ;
    const int nModel = 7;
    */
    TString names[3] = { "Scale-Up", "Nominal", "Scale-Down" } ;
    int color[3]     = {         2,          1,     4 } ;

    TFile* hfile[3] ;

    TH1D* h_nJets[3] ;
    TH1D* h_met1[3] ;
    TH1D* h_met2[3] ;

    hfile[0]  = TFile::Open( fileName+"_syst3.root" );
    hfile[1]  = TFile::Open( fileName+".root" );
    hfile[2]  = TFile::Open( fileName+"_syst4.root" );

    for ( int i=0 ; i< 3 ; i++ ) {
        h_nJets[i]  = (TH1D *) hfile[i]->Get( hName0.c_str() )  ;
        h_met1[i]    = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        h_met2[i]    = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
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

    // Plot0 
    leg1->Clear() ;
    c0->SetLogy(0);
    for ( int i=0; i< 3; i++ ) {

        h_nJets[i]->SetLineColor( color[i] ) ;

        double n2j = h_nJets[i]->Integral(3,10) ;
        sprintf( legStr,  ":  %.0f  ", n2j  ) ;
        leg1->AddEntry( h_nJets[i], names[i]+legStr  ,  "L");

        if ( i ==0 ) {
           c0->cd();

           h_nJets[i]->Draw();
        } else {
           h_nJets[i]->Draw("sames");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname0 );

    // Plot1
    leg1->Clear() ;
    c0->SetLogy(0);

    for ( int i=0; i< 3; i++ ) {
        h_met1[i]->SetLineColor( color[i] ) ;

        double n60 = h_met1[i]->Integral(7,51) ;
        sprintf( legStr,  ":  %.0f  ", n60  ) ;
        leg1->AddEntry( h_met1[i], names[i]+legStr  ,  "L");

        if ( i ==0 ) {
           c0->cd();

           h_met1[i]->Draw();
        } else {
           h_met1[i]->Draw("sames");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname1 );

    // Plot2
    leg1->Clear() ;
    c0->SetLogy(0);

    for ( int i=0; i< 3; i++ ) {
        h_met2[i]->SetLineColor( color[i] ) ;

        double n60 = h_met2[i]->Integral(7,51) ;
        sprintf( legStr,  ":  %.0f  ", n60  ) ;
        leg1->AddEntry( h_met2[i], names[i]+legStr  ,  "L");

        if ( i ==0 ) {
           c0->cd();

           h_met2[i]->Draw();
        } else {
           h_met2[i]->Draw("sames");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname2 );



    delete c0 ;


}


