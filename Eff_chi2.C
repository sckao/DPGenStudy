#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Eff_chi2() {

    gROOT->LoadMacro("CMS_lumi.C");

    TString hfolder  = "Final2012/" ;

    TString fileName0 = "TCuts_GMSB_L100/GMSB2J_100_6000.root" ;
    TString fileName1 = "TCuts_GMSB_L140/GMSB2J_140_6000.root" ;
    TString fileName2 = "TCuts_GMSB_L180/GMSB2J_180_5980.root" ;
    TString fileName3 = "TCuts_GMSB_L300/GMSB2J_300_6000.root" ;

    // Lambda 180
    double nGen[4]   = { 50000,  50000,  50000,  50000 } ;
    TString names[4] = { "100",  "140",  "180",  "300" } ;
    int color[4]     = {     4,     2,     1,      6,  } ;
    const int nModel = 4;

    TLegend* leg1  = new TLegend(.40, .65, .65, .9 );
    TString plotname  = "Eff_PhotSel_dR0.png" ;
    string hNameN = "h_nVtx_sel" ;
    //TLegend* leg1  = new TLegend(.40, .3, .65, .5 );
    //TString plotname  = "Eff_chi2.png" ;
    //string hNameN = "h_nVtx_chi2" ;
    string hNameD = "h_nVtx" ;
   
    int rbin = 3 ;
    float ymax = 0.6 ;
    float xmax = 50. ;

   /*
    TString plotname  = "Eff_hlt_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "hlt_ctbgT" ;

    TString plotname = "Eff_lambad_reco_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "reco_ctbgT" ;

    TString plotname  = "Eff_sel_ctbgT.png" ;
    string hNameD = "obs_ctbgT" ;
    string hNameN = "sel_ctbgT" ;
    */
  
    /*
    string hName1 = "h_ctbgT" ;      // All
    string hName2 = "obs_ctbgT" ;    // T available 
    string hName3 = "late_ctbgT" ;   // T > 3ns
    string hName4 = "hlt_ctbgT" ;    // HLT 
    string hName5 = "reco_ctbgT" ;   // EB + Pt > 1 GeV 
    string hName6 = "lateR_ctbgT" ;  // EB + Pt > 1 GeV  + T > 3ns
    string hName6 = "lateR_ctbgT1" ;  // EB + Pt > 1 GeV  + T > 3ns + dt2 < 0.5 
    string hName6 = "lateR_ctbgT2" ;  // EB + Pt > 1 GeV  + T > 3ns + dt2 > 0.5 
    string hName7 = "sel_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60)
    string hName8 = "acc_ctbgT" ;    // EB + matched RECO + pass(HLT , Phot, JET, MET1 > 60, MET2 > 60) + T > 3ns
    */

    TFile* hfile[ nModel ] ;
    TH1D*  D_ctbgT[ nModel ] ;
    TH1D*  N_ctbgT[ nModel ] ;

    hfile[0]  = TFile::Open( fileName0 );
    hfile[1]  = TFile::Open( fileName1 );
    hfile[2]  = TFile::Open( fileName2 );
    hfile[3]  = TFile::Open( fileName3 );

    for ( int i=0 ; i< nModel; i++ ) { 
        D_ctbgT[i]    = (TH1D *) hfile[i]->Get( hNameD.c_str() )  ;
        N_ctbgT[i]    = (TH1D *) hfile[i]->Get( hNameN.c_str() )  ;
    }
    /*
    h_ctbgT[i]      = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
    Obs_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
    Late_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
    HLT_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
    Reco_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
    LRec_ctbgT[i]   = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
    Sel_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
    Acc_ctbgT[i]    = (TH1D *) hfile[i]->Get( hName8.c_str() )  ;
    */

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
    gStyle->SetLabelSize(0.04, "XYZ");
 
    // Plots
    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);

    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.05);
    c0->SetLogy();

    //gPad->SetGridx();
    //gPad->SetGridy();
    c0->cd();

    TGraphAsymmErrors* eff[nModel] ;
    leg1->Clear() ;
    for ( int i=0; i< nModel; i++ ) {

        eff[i]= new TGraphAsymmErrors();

        D_ctbgT[i]->Rebin( rbin ) ;
        N_ctbgT[i]->Rebin( rbin ) ;

        eff[i]->Divide( N_ctbgT[i], D_ctbgT[i] );    

        eff[i]->SetMarkerColor( color[i] );
        eff[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff[i], names[i]+" TeV" ,  "L");

        if ( i ==0 ) {
           c0->cd();
           c0->SetLogy(0);

           eff[i]->SetMaximum( ymax );
           eff[i]->SetMinimum( 0.0 );
           eff[i]->SetMarkerStyle(22);
           eff[i]->SetMarkerSize(1);
           eff[i]->SetLineWidth(2);

           eff[i]->GetXaxis()->SetTitleOffset(0.9);
           eff[i]->GetYaxis()->SetTitleOffset(1.25);
	   eff[i]->GetXaxis()->SetTitleSize(0.06);
	   eff[i]->GetYaxis()->SetTitleSize(0.06);
         
           eff[i]->GetXaxis()->SetTitle("Number of Vertices") ;
           eff[i]->GetYaxis()->SetTitle("Efficiency ") ;
           eff[i]->GetXaxis()->SetRangeUser(0, xmax ) ;
           eff[i]->Draw("AP");
        } else {
           eff[i]->Draw("SAMEPS");
        }
    }
    leg1->Draw("sames") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( hfolder + plotname );


    delete c0 ;
}

