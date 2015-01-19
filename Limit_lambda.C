#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Limit_lambda() {

   gROOT->LoadMacro("CMS_lumi.C");

   string hfolder  = "Limit1/" ;

   string ctau = "2000" ;
   string names[4] = {  "1935", "2060", "1945", "2195"  } ;
   const int sz = 4;

   string ld_Str[4] = { "120", "140", "160", "180" } ;
   float x[4] = { 120, 140, 160, 180, } ;
   float Xsec[4] = { 0.133, 0.0574, 0.0277, 0.0145 }  ;

   /*
   string ctau = "6000" ;
   string names[6] = { "6000", "5985", "6000", "5875", "5980", "6000"  } ;
   const int sz = 6;

   string ld_Str[6] = { "100", "120", "140", "160", "180", "220" } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 0.368, 0.133, 0.0574, 0.0277, 0.0145, 0.0048}  ;

   string ctau = "1000" ;
   string names[4] = {  "1030", "975", "1100", "1000"  } ;
   const int sz = 4;

   string ld_Str[4] = { "140", "160", "180", "220" } ;
   float x[4] = { 140, 160, 180, 220 } ;
   float Xsec[4] = { 0.0574, 0.0277, 0.0145, 0.0048}  ;

   string ctau = "10000" ;
   string names[6] = { "10000", "10000", "10000", "10000", "10000", "10000" } ;
   const int sz = 6;

   string ld_Str[6] = { "100", "120", "140", "160", "180", "220" } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 0.368, 0.133, 0.0574, 0.0277, 0.0145, 0.0048}  ;

   string ctau = "500" ;
   string names[4] = { "425", "515", "490", "500" } ;
   const int sz = 4;

   string ld_Str[4] = { "100", "140", "160", "220" } ;
   float x[4] = { 100, 140, 160, 220 } ;
   float Xsec[4] = { 0.368, 0.0574, 0.0277, 0.0048}  ;
   */

   /*
   string Lambda = "160" ;
   float Xsec = 0.0277 ;
   string names[7] = { "490", "975", "1945", "2930", "3910", "5875", "10000"  } ;
   const int sz = 7;

   string Lambda = "180" ;
   float Xsec = 0.0145 ;
   string names[8] = { "185", "365", "730", "1100", "2195", "3950", "5980", "10000"  } ;
   const int sz = 8;

   string Lambda = "220" ;
   float Xsec = 0.0048 ;
   string names[5] = { "500", "1000", "3000", "6000", "10000"  } ;
   const int sz = 5;

   string Lambda = "100" ;
   float Xsec = 0.368 ;
   string names[7] = { "215", "425", "1700", "3400", "5100", "6000", "10000"  } ;
   const int sz = 7;

   string Lambda = "120" ;
   float Xsec = 0.133 ;
   string names[8] = { "325", "645", "1290", "1935", "2955", "3870", "5985", "10000"  } ;
   const int sz = 8;

   string Lambda = "140" ;
   float Xsec = 0.0574 ;
   string names[8] = { "130", "515", "1030", "2060", "2920", "3985", "6000", "10000"  } ;
   const int sz = 8;
   */

   TString legTitle = "#tilde{#chi}^{0}_{1} #rightarrow #gamma #tilde{G}, c#tau ="+ ctau + " mm" ;
   string limitPlotName = "limit_ct"+ ctau + ".png" ;

   float yMax = 30. * Xsec[0] ;
   float yMin = 0.1 * Xsec[sz-1] ; 

   char s1[8],s2[8],s3[8],s4[8],s5[8],s6[8],s7[8] ;
   float f1,f2 ;
   int r1 ;
   float md[sz], u1[sz], u2[sz], d1[sz], d2[sz], ob[sz], x[sz], th[sz] ;
   float ex[sz] = { 0. } ;
   FILE* logf ; 

   // Get signal strength
   for (int i=0; i< sz; i++ ) {
       string fileName = hfolder +  "log_" + ld_Str[i] + "_" + names[i] + ".txt"  ;
       printf(" filename : %s \n", fileName.c_str() ) ;
       logf = fopen( fileName.c_str() ,"r");
       th[i] = Xsec[i] ;

       for (int j=0; j< 6; j++ ) {
           r1 = fscanf( logf, "%s %s %s %f %s %f %s %s %s", s1,s2,s3,&f1,s4,&f2,s5,s6,s7  );
	   printf("[%.0f] %s %s %s %f %s %f %s %s %s \n", x[i], s1,s2,s3, f1, s4, f2, s5,s6,s7 ) ;
           if ( j == 0 ) ob[i] = f1 * Xsec[i] ;
           if ( j == 1 ) u2[i] = f1 * Xsec[i] ;
           if ( j == 2 ) u1[i] = f1 * Xsec[i] ;
           if ( j == 3 ) md[i] = f1 * Xsec[i] ;
           if ( j == 4 ) d1[i] = f1 * Xsec[i] ;
           if ( j == 5 ) d2[i] = f1 * Xsec[i] ;
       } 
       u2[i] = u2[i] - md[i] ;
       u1[i] = u1[i] - md[i] ;
       d1[i] = md[i] - d1[i] ;
       d2[i] = md[i] - d2[i] ;

       printf(" -- \n") ;
       fclose( logf ) ;
   }


   // For the frame:
   gStyle->SetFrameBorderMode(0);
   gStyle->SetFrameBorderSize(1);
   gStyle->SetFrameFillColor(0);
   gStyle->SetFrameFillStyle(0);
   gStyle->SetFrameLineColor(1);
   gStyle->SetFrameLineStyle(1);
   gStyle->SetFrameLineWidth(1);

   gStyle->SetLabelOffset(0.007, "XYZ");
   gStyle->SetLabelSize(0.04, "XYZ");

   TCanvas *c1a = new TCanvas("c1a","c1a" ,800,800);
   //c1a->SetGridy() ;
   c1a->SetTopMargin(0.1);
   c1a->SetBottomMargin(0.13);
   c1a->SetLeftMargin(0.16);
   c1a->SetRightMargin(0.05);

   c1a->SetLogy() ;
   TMultiGraph *mg = new TMultiGraph();
   //gStyle->SetTitleW(0.85);
   //mg->SetTitle( "   CMS 19.1 fb^{-1}                                                   #sqrt{s} = 8 TeV" );

   // SetFillStyle ref: http://root.cern.ch/root/html/TAttFill.html
   TGraphAsymmErrors* gbe = new TGraphAsymmErrors(sz, x, md, ex, ex, d2, u2);
   gbe->SetFillStyle(1001);
   gbe->SetFillColor(kYellow);
   //gbe->GetXaxis()->SetLimits(240.,6100.) ;

   TGraphAsymmErrors* gae = new TGraphAsymmErrors(sz, x, md, ex, ex, d1, u1);
   gae->SetFillStyle(1001);
   //gae->SetFillColor(kSpring);
   gae->SetFillColor(kGreen);
   //gae->GetXaxis()->SetRangeUser(1.,5.) ;
   //gae->GetXaxis()->SetLimits(1.,5.) ;

   mg->Add( gbe ) ;
   mg->Add( gae ) ;
   mg->Draw("a3") ;

   // this modify the x-axis range, must set after Draw() ...stupid ROOT 
   gPad->Modified();
   mg->GetXaxis()->SetLimits( x[0] - 1, x[sz-1]+1 ) ;
   mg->SetMaximum( yMax );
   mg->SetMinimum( yMin );
   mg->GetXaxis()->SetTitleOffset(1.1);
   mg->GetYaxis()->SetTitleOffset(1.3);
   mg->GetXaxis()->SetTitleFont(42);
   mg->GetYaxis()->SetTitleFont(42);
   mg->GetXaxis()->SetTitleSize(0.04);
   mg->GetYaxis()->SetTitleSize(0.04);
   mg->GetXaxis()->SetTitle( "SUSY breaking scale (TeV)"  ) ;
   //mg->GetXaxis()->SetTitle( "MET Cut (GeV)" ) ;
   mg->GetYaxis()->SetTitle(" #sigma_{Upper Limit} (pb) at 95% CL") ;

   // expected
   TGraph*  g1  = new TGraph(sz, x, md ) ;
   g1->SetLineColor(2) ;
   g1->SetLineWidth(2) ;
   g1->SetLineStyle(1) ;
   //g1->GetXaxis()->SetLimits(1.,5.) ;
   g1->Draw("LP") ;
   c1a->Update() ;

   // observation
   TGraph*  g0  = new TGraph(sz, x, ob ) ;
   g0->SetLineColor(1) ;
   g0->SetLineWidth(2) ;
   g0->SetLineStyle(1) ;
   //g0->GetXaxis()->SetLimits(1.,5.) ;
   //g0->SetMarkerStyle(20) ;
   g0->Draw("LP") ;
   c1a->Update() ;


   // theoratical suggestion
   TGraph*  gth = new TGraph(sz, x, th ) ;
   gth->SetLineColor(4) ;
   gth->SetLineWidth(2) ;
   gth->SetLineStyle(1) ;
   gth->GetXaxis()->SetLimits( x[0], x[sz-1] ) ;
   gth->Draw("L") ;
   
   TLegend* leg1  = new TLegend(.4, .6, .90, .88 );
   //TLegend* leg1  = new TLegend(.4, .15, .90, .40 );
   leg1->SetHeader( legTitle ); 
   leg1->SetFillStyle(0); 
   leg1->SetBorderSize(0);
   leg1->SetFillColor(0);
   leg1 ->SetTextFont(22);

   leg1->SetFillColor(10) ;
   leg1->SetTextSize(0.030) ;
   leg1->AddEntry( gbe, "#pm 2#sigma Expected" ,  "F");
   leg1->AddEntry( gae, "#pm 1#sigma Expected" ,  "F");
   leg1->AddEntry( g1,  "Expected 95% CL upper limit" , "L");
   leg1->AddEntry( gth, "Theoretical LO cross-section", "L");
   leg1->AddEntry( g0,  "Observed" , "L");
   leg1->Draw("same") ;

   CMS_lumi( c1a, 2, 11 ) ;
   c1a->Update();

   TString gPlotname = hfolder +  limitPlotName  ;
   c1a->Print( gPlotname ) ;
   delete c1a ;

   /*
    // *************************
    // ***  Drawing setup    ***
    // *************************
    gStyle->SetOptStat("");

    gStyle->SetOptStat(kFALSE);
    //gStyle->SetOptFit(111);
    gStyle->SetOptTitle(0);
    //gStyle->SetTitleFontSize(0.05);
 
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
    */
}

