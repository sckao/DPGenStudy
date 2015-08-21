#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Limit_ctau() {

   gROOT->LoadMacro("CMS_lumi.C");

   string hfolder  = "Limit5/" ;

   string Lambda = "180" ;
   float Xsec = 0.0145*0.82818 ;
   string names[7] = {  "500", "1000", "2000", "3000", "4000", "6000", "10450"  } ;
   const int sz = 7 ;

   /*
   string Lambda = "260" ;
   float Xsec = 0.0019*0.79108 ;
   string names[5] = { "495", "995", "2960", "6000", "10450"  } ;
   const int sz = 5;

   string Lambda = "220" ;
   float Xsec = 0.0048*0.80434 ;
   string names[6] = { "500", "1000", "2000", "3000", "6000", "10450"  } ;
   const int sz = 6;

   string Lambda = "160" ;
   float Xsec = 0.0277*0.84638 ;
   string names[7] = { "500", "1000", "2000", "3000", "4000", "6000", "9815"  } ;
   const int sz = 7;

   string Lambda = "140" ;
   float Xsec = 0.0574*0.8711 ;
   string names[7] = {  "500", "800", "2000", "3000", "4000", "6000", "10450"  } ;
   const int sz = 7;

   string Lambda = "120" ;
   float Xsec = 0.133*0.90421 ;
   string names[7] = { "500", "1000", "2000", "3000", "4000", "6000", "9825"  } ;
   const int sz = 7;

   string Lambda = "100" ;
   float Xsec = 0.368*0.94444 ;
   string names[7] = { "500", "1000", "2000", "3000", "4000", "6000", "9330"  } ;
   const int sz = 7;

   */

   TString legTitle = "#tilde{#chi}^{0}_{1} #rightarrow #gamma #tilde{G},  #Lambda ="+ Lambda+ "TeV" ;
   string limitPlotName = "limit_"+ Lambda + ".png" ;

   float yMax = 50. * Xsec ;
   float yMin = 0.2. * Xsec ; 

   char s1[8],s2[8],s3[8],s4[8],s5[8],s6[8],s7[8] ;
   float f1,f2 ;
   int r1 ;
   float md[sz], u1[sz], u2[sz], d1[sz], d2[sz], ob[sz], x[sz], th[sz], tau[sz] ;
   float ex[sz] = { 0. } ;
   FILE* logf ; 

   // Get signal strength
   for (int i=0; i< sz; i++ ) {
       string fileName = hfolder +  "log_" + Lambda + "_" + names[i] + ".txt"  ;
       printf(" filename : %s \n", fileName.c_str() ) ;
       logf = fopen( fileName.c_str() ,"r");
       int model = atoi(  names[i].c_str() ) ;
       x[i] = (float) model/10. ;
       tau[i] = x[i] / 30. ;
       th[i] = Xsec ;

       for (int j=0; j< 6; j++ ) {
           r1 = fscanf( logf, "%s %s %s %f %s %f %s %s %s", s1,s2,s3,&f1,s4,&f2,s5,s6,s7  );
	   printf("[%.0f] %s %s %s %f %s %f %s %s %s \n", x[i], s1,s2,s3, f1, s4, f2, s5,s6,s7 ) ;
           if ( j == 0 ) ob[i] = f1 * Xsec ;
           if ( j == 1 ) u2[i] = f1 * Xsec ;
           if ( j == 2 ) u1[i] = f1 * Xsec ;
           if ( j == 3 ) md[i] = f1 * Xsec ;
           if ( j == 4 ) d1[i] = f1 * Xsec ;
           if ( j == 5 ) d2[i] = f1 * Xsec ;
       } 
       u2[i] = u2[i] - md[i] ;
       u1[i] = u1[i] - md[i] ;
       d1[i] = md[i] - d1[i] ;
       d2[i] = md[i] - d2[i] ;

       printf(" -- \n") ;
       fclose( logf ) ;

   }

   // Calculate lower and higher limit of ctau
   printf(" === observed === \n") ;
   pair<float,float> obs_limit = findLimit( sz, ob, x, Xsec ) ;
   printf(" === expected === \n") ;
   pair<float,float> exp_limit = findLimit( sz, md, x, Xsec ) ;

   string rfName = hfolder +  "limitResult.txt"  ; 
   FILE* resf = fopen( rfName.c_str() ,"a") ;
   fprintf(resf, "%s %.0f %.0f %.0f %.0f \n", Lambda.c_str(), obs_limit.first, obs_limit.second, exp_limit.first, exp_limit.second) ;
   fclose( resf ) ;


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
   c1a->Clear() ;
   //c1a->SetGridy() ;
   c1a->SetTopMargin(0.1);
   c1a->SetBottomMargin(0.13);
   c1a->SetLeftMargin(0.16);
   c1a->SetRightMargin(0.05);
   
   c1a->SetLogy() ;
   c1a->SetLogx() ;
   TMultiGraph *mg = new TMultiGraph();
   //gStyle->SetTitleW(0.85);

   // Change ctau (cm) to tau (ns) c = 30 cm / ns
   
   // SetFillStyle ref: http://root.cern.ch/root/html/TAttFill.html
   TGraphAsymmErrors* gbe = new TGraphAsymmErrors(sz, tau, md, ex, ex, d2, u2);
   gbe->SetFillStyle(1001);
   gbe->SetFillColor(kYellow);
   //gbe->GetXaxis()->SetLimits(240.,6100.) ;

   TGraphAsymmErrors* gae = new TGraphAsymmErrors(sz, tau, md, ex, ex, d1, u1);
   gae->SetFillStyle(1001);
   gae->SetFillColor(kGreen);
   //gae->SetFillColor(kSpring);
   //gae->GetXaxis()->SetRangeUser(1.,5.) ;
   //gae->GetXaxis()->SetLimits(1.,5.) ;

   mg->Add( gbe ) ;
   mg->Add( gae ) ;
   mg->Draw("a3") ;
   // this modify the x-axis range, must set after Draw() ...stupid ROOT 
   
   mg->GetXaxis()->SetLimits( tau[0]-0.1, tau[sz-1]+1 ) ;
   mg->SetMaximum( yMax );
   mg->SetMinimum( yMin );
   //mg->GetXaxis()->SetNdivisions( 20, kFALSE );
   mg->GetXaxis()->SetTitleOffset(1.3);
   mg->GetXaxis()->SetTitleFont(42);
   mg->GetXaxis()->SetTitleSize(0.04);
   mg->GetXaxis()->SetTitle( "Neutralino Lifetime (ns)"  ) ;
   mg->GetYaxis()->SetTitleOffset(1.45);
   mg->GetYaxis()->SetTitleFont(42);
   mg->GetYaxis()->SetTitleSize(0.04);
   mg->GetYaxis()->SetTitle("Upper Limit of #sigma#times BR (pb) at 95% CL") ;
   gPad->Modified();
   gPad->Update() ;
   

   // expected
   TGraph*  g1  = new TGraph(sz, tau, md ) ;
   g1->SetLineColor(2) ;
   g1->SetLineWidth(2) ;
   g1->SetLineStyle(7) ;
   //g1->GetXaxis()->SetLimits(1.,5.) ;
   g1->Draw("LP") ;
   c1a->Update() ;

   // observation
   TGraph*  g0  = new TGraph(sz, tau, ob ) ;
   g0->SetLineColor(1) ;
   g0->SetLineWidth(2) ;
   g0->SetLineStyle(1) ;
   //g0->GetXaxis()->SetLimits(1.,5.) ;
   //g0->SetMarkerStyle(20) ;
   g0->Draw("LP") ;
   c1a->Update() ;

   // theoratical suggestion
   TGraph*  gth = new TGraph(sz, tau, th ) ;
   gth->SetLineColor(4) ;
   gth->SetLineWidth(2) ;
   gth->SetLineStyle(1) ;
   //gth->GetXaxis()->SetLimits( x[0], x[sz-1] ) ;
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
   leg1->AddEntry( gth, "SPS8 Theory LO Cross-Section", "L");
   leg1->AddEntry( g0,  "Observed 95% CL upper limit" , "L");
   leg1->Draw("same") ;

   CMS_lumi( c1a, 2, 11 ) ;
   c1a->Update();

   TString gPlotname = hfolder +  limitPlotName  ;
   c1a->Print( gPlotname ) ;
   delete c1a ;

}

pair<float,float> findLimit( const int sz, float lm[], float x[], float& Theo  ) {


   float tLow, tHigh ;
   float xs1[2] = {0,0} ;
   float xs2[2] = {0,0} ;
   int k = -1 ; 

   if ( lm[0] < Theo ) {
      xs1[0] = lm[0] ;
      xs1[1] = lm[1] ;
      k  = 1 ;
      printf(" Extrapolote ") ;
   } else {
     for (int i=0; i< sz; i++ ) {
         if ( lm[i] > Theo ) xs1[0] = lm[i] ;
         if ( lm[i] < Theo ) { 
                             xs1[1] = lm[i] ;
                             k = i ;
                             printf(" Interpolate(%d,%d) ", i-1, i) ;
                             break ;
         }
     }
   }
 
   float m = (k < 0) ? -9999. : (x[k] - x[k-1])/(xs1[1] - xs1[0])  ;
   tLow = ( k < 0 ) ? -1 : (x[k-1] + m*(Theo - xs1[0])) ;
   printf(" lower ct limit : %.2f \n", tLow ) ;
   printf(" k(%d) m= %.6f , dCs = %.5f , x0 = %.0f \n", k, m, Theo - xs1[0] , x[0] ) ;
   

   if ( lm[sz-1] < Theo ) {
      printf(" Extrapolote ") ;
      xs2[0] = lm[sz-1] ;
      xs2[1] = lm[sz-2] ;
      k = sz-2 ;
   } else {
     for (int i = sz-1; i>= 0; i-- ) {
         if ( lm[i] > Theo ) xs2[0] = lm[i] ;
         if ( lm[i] < Theo ) { 
                             xs2[1] = lm[i] ;
                             k = i ;
                             printf(" Interpolate(%d,%d) ", i, i+1) ;
                             break ;
         }
     }
   }
   float m = (k < 0) ? -9999. : (x[k+1] - x[k])/(xs2[0] - xs2[1])  ;
   tHigh = ( xs2[1] == 0 ) ? -1 : x[k+1] + (m*(Theo - xs2[0])) ;
   printf(" higher lambda limit : %.2f \n", tHigh ) ;
   //if ( k >= 0 ) printf("   x[k+1] = %f -  x[k] = %f \n", x[k+1] , x[k] ) ;

   pair<float,float> tlimit = make_pair(tLow, tHigh) ;
   return tlimit ;
}

