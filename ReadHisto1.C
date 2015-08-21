#include <vector>
#include <stdio.h>
#include <TFile.h>
#include <iostream>
#include <fstream>

// define the fitting function
void ReadHisto1() {

    TFile *file0  = TFile::Open("HaloTest/halo/bgStudy1.root");

    TH1D* h_a    = (TH1D *) file0->Get( "haloCS_nXtl_a3"  )  ;
    TH1D* s_a    = (TH1D *) file0->Get( "spikeCS_nXtl_a3"  )  ;

    TH1D* h_b    = (TH1D *) file0->Get( "haloCS_nXtl_b3"  )  ;
    TH1D* s_b    = (TH1D *) file0->Get( "spikeCS_nXtl_b3"  )  ;

    TH1D* h_c    = (TH1D *) file0->Get( "haloCS_nXtl_c2"  )  ;
    TH1D* s_c    = (TH1D *) file0->Get( "spikeCS_nXtl_c2"  )  ;

    h_a->Add( s_a );
    h_b->Add( s_b );
    h_c->Add( s_c );

    // Normalization 
    h_a->Scale( 1./ h_a->Integral() ) ;
    h_b->Scale( 1./ h_b->Integral() ) ;
    h_c->Scale( 1./ h_c->Integral() ) ;
    
    gStyle->SetOptStat("");

    h_b->SetFillColor(5) ;
    h_b->SetLineWidth(2) ;
    h_a->SetLineWidth(2) ;
    h_c->SetLineWidth(2) ;

    TLegend* leg1  = new TLegend(.65, .7, .9, .9 );
    leg1->Clear();
    //leg1->SetTextSize(0.03) ;

    leg1->AddEntry( h_b, "t  < -3 ns",  "F");
    leg1->AddEntry( h_a, "t  > 3 ns",  "L");
    leg1->AddEntry( h_c, "|t| < 2 ns",  "L");

     TCanvas *c1 = new TCanvas("c1","",800,600);
     c1->cd();
     c1->SetFillColor(10);
     c1->SetFillColor(10);
     //c1->Divide(1,2);
     //c1->cd(1) ;
     c1->SetLogy() ;   

     h_b->GetXaxis()->SetTitle( " N of Crystal  " );

     h_b->SetLineColor(1) ;
     h_b->Draw() ;
     c1->Update() ;

     h_a->DrawCopy("SAME") ;
     c1->Update() ;

     h_c->DrawCopy("SAME") ;
     c1->Update() ;

     leg1->Draw("sames") ;
     c1->Update() ;

     TString plotname = "DOE_NXtal.png" ;
     c1->Print( plotname ) ;

}

