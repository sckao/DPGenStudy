#include <vector>
#include <stdio.h>
#include <TFile.h>
#include <iostream>
#include <fstream>

// define the fitting function
void ReadNtuple( string fileName ) {


    TString theFileName = fileName + ".root" ;
    TChain* theChain = new TChain( "CutFlow" ) ;
    theChain->Add( theFileName ) ;
    TTree* tr =  theChain ;

    int counter[12] = { 0. } ;
    tr->SetBranchAddress("counter",    counter);

    TH1D* h1 = new TH1D("h1", "cut flows", 12, 0,12 ) ; 

    int totalN = tr->GetEntries();
    for ( int i=0; i < totalN ; i++ ) {
        cout<<" ("<<i <<")"<<endl ;
        tr->GetEntry( i );
        for ( int k=0; k<12; k++ ) {
            h1->Fill( k , counter[k] ) ;
        }
    }
   

    gStyle->SetOptStat("");
 
    /*
    TLegend* leg1  = new TLegend(.65, .7, .9, .9 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30] ;
    sprintf( RStr0,  "No Iso (%d)", h0->Integral()  ) ;
    sprintf( RStr1,  "PF Iso (%d)", h1->Integral()  ) ;

    leg1->AddEntry( h0, RStr0,  "L");
    leg1->AddEntry( h1, RStr1,  "L");
    */

     TCanvas *c1 = new TCanvas("c1","",900,720);
     c1->cd();
     c1->SetFillColor(10);
     c1->SetFillColor(10);
     //c1->Divide(1,2);
     //c1->cd(1) ;
     c1->SetLogy() ;   

     h1->GetXaxis()->SetTitle( " counters  " );
     h1->SetLineColor(1) ;
     h1->Draw() ;
     c1->Update() ;

     /* 
     h1->SetLineColor(2) ;
     h1->DrawCopy("SAME") ;
     c1->Update() ;

     h2->SetLineColor(4) ;
     h2->DrawCopy("SAME") ;
     c1->Update() ;

     leg1->Draw("sames") ;
     c1->Update() ;
     */

     TString plotname = fileName + ".png" ;
     c1->Print( plotname ) ;

}

