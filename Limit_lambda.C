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

   string hfolder  = "Limit5/" ;

   /*
   string ctau = "6000" ;
   const int sz = 6;
   string ld_Str[6] = { "100", "120", "140", "160", "180", "220" } ;
   string names[6] = { "6000", "6000", "6000", "6000", "6000", "6000"  } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 368*0.94444 , 133*0.90421, 57.4*0.8711, 27.7*0.84638, 14.5*0.82818, 4.8*0.80434 }  ;

   string ctau = "3000" ;
   const int sz = 6;
   string ld_Str[6] = { "100",  "120",  "140",  "160",  "180",  "220" } ;
   string names[6] = {  "3000", "3000", "3000", "3000", "3000", "3000"  } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 368*0.94444 , 133*0.90421, 57.4*0.8711, 27.7*0.84638, 14.5*0.82818, 4.8*0.80434 }  ;

   string ctau = "2000" ;
   const int sz = 6;
   string ld_Str[6] = { "100", "120", "140", "160", "180", "220" } ;
   string names[6] = {  "2000", "2000", "2000", "2000", "2000", "2000"  } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 0.368*0.94444,  0.133*0.90421, 0.0574*0.8711, 0.0277*0.84638, 0.0145*0.82818, 0.0048*0.80434  }  ;

   string ctau = "1000" ;
   const int sz = 5;
   string ld_Str[5] = { "100", "120", "160", "180", "220" } ;
   string names[5] = {  "1000", "1000", "1000", "1000", "1000"  } ;
   float x[5] = { 100, 120, 160, 180, 220 } ;
   float Xsec[5] = { 368*0.94444, 133.*0.90421, 27.7*0.84638 , 14.5*0.82818, 4.8*0.80434 }  ;

   string ctau = "10000" ;
   const int sz = 6;
   string ld_Str[6] = { "100", "120", "140", "160", "180", "220" } ;
   string names[6] = { "9330", "9825", "10450", "9815", "10450", "10450" } ;
   float x[6] = { 100, 120, 140, 160, 180, 220 } ;
   float Xsec[6] = { 0.368, 0.133, 0.0574, 0.0277, 0.0145, 0.0048}  ;

   string ctau = "500" ;
   const int sz = 4;
   string ld_Str[4] = { "100", "140", "160", "220" } ;
   string names[4] = { "500", "500", "500", "500" } ;
   float x[4] = { 100, 140, 160, 220 } ;
   float Xsec[4] = { 0.368, 0.0574, 0.0277, 0.0048}  ;

   */

   TString legTitle = "#tilde{#chi}^{0}_{1} #rightarrow #gamma #tilde{G}, c#tau ="+ ctau + " mm" ;
   string limitPlotName = "limit_ct"+ ctau + ".png" ;

   float yMax = 30. * Xsec[0] ;
   float yMin = 0.2 * Xsec[sz-1] ; 

   char s1[8],s2[8],s3[8],s4[8],s5[8],s6[8],s7[8] ;
   float f1,f2 ;
   int r1 ;
   float md[sz], u1[sz], u2[sz], d1[sz], d2[sz], ob[sz], x[sz], th[sz], m[sz] ;
   float ex[sz] = { 0. } ;
   FILE* logf ; 

   // Get signal strength
   for (int i=0; i< sz; i++ ) {
       string fileName = hfolder +  "log_" + ld_Str[i] + "_" + names[i] + ".txt"  ;
       printf(" filename : %s \n", fileName.c_str() ) ;
       logf = fopen( fileName.c_str() ,"r");
       th[i] = Xsec[i] ;
       m[i] = (x[i]*1.45) - 5 ;
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

   // Calculate lower and higher limit of ctau
   string rfName = hfolder +  "limitResult.txt"  ;
   FILE* resf = fopen( rfName.c_str() ,"a") ;

   printf(" === observed === \n") ;
   float obs_limit = findLimit( sz, ob, x, Xsec ) ;
   printf(" === expected === \n") ;
   float exp_limit = findLimit( sz, md, x, Xsec ) ;

   fprintf(resf, "%.2f %.2f %s \n", obs_limit, exp_limit, ctau.c_str() ) ;
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

   TCanvas *c2a = new TCanvas("c2a","c2a" ,800,800);
   //c2a->SetGridy() ;
   c2a->SetTopMargin(0.1);
   c2a->SetBottomMargin(0.13);
   c2a->SetLeftMargin(0.16);
   c2a->SetRightMargin(0.05);

   c2a->SetLogy() ;
   TMultiGraph *mg = new TMultiGraph();
   //gStyle->SetTitleW(0.85);
   //mg->SetTitle( "   CMS 19.1 fb^{-1}                                                   #sqrt{s} = 8 TeV" );

   // SetFillStyle ref: http://root.cern.ch/root/html/TAttFill.html
   TGraphAsymmErrors* gbe = new TGraphAsymmErrors(sz, m, md, ex, ex, d2, u2);
   gbe->SetFillStyle(1001);
   gbe->SetFillColor(kYellow);
   //gbe->GetXaxis()->SetLimits(240.,6100.) ;

   TGraphAsymmErrors* gae = new TGraphAsymmErrors(sz, m, md, ex, ex, d1, u1);
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
   mg->GetXaxis()->SetLimits( m[0] - 1, m[sz-1]+1 ) ;
   mg->SetMaximum( yMax );
   mg->SetMinimum( yMin );
   mg->GetXaxis()->SetTitleOffset(1.2);
   mg->GetYaxis()->SetTitleOffset(1.5);
   mg->GetXaxis()->SetTitleFont(42);
   mg->GetYaxis()->SetTitleFont(42);
   mg->GetXaxis()->SetTitleSize(0.04);
   mg->GetYaxis()->SetTitleSize(0.04);
   mg->GetXaxis()->SetTitle( "Neutralino Mass (GeV)"  ) ;
   //mg->GetXaxis()->SetTitle( "MET Cut (GeV)" ) ;
   mg->GetYaxis()->SetTitle("Upper Limit of #sigma#times BR (pb) at 95% CL") ;

   // expected
   TGraph*  g1  = new TGraph(sz, m, md ) ;
   g1->SetLineColor(2) ;
   g1->SetLineWidth(2) ;
   g1->SetLineStyle(7) ;
   g1->Draw("LP") ;
   c2a->Update() ;

   // observation
   TGraph*  g0  = new TGraph(sz, m, ob ) ;
   g0->SetLineColor(1) ;
   g0->SetLineWidth(2) ;
   g0->SetLineStyle(1) ;
   //g0->SetMarkerStyle(20) ;
   g0->Draw("LP") ;
   c2a->Update() ;


   // theoratical suggestion
   TGraph*  gth = new TGraph(sz, m, th ) ;
   gth->SetLineColor(4) ;
   gth->SetLineWidth(2) ;
   gth->SetLineStyle(1) ;
   gth->GetXaxis()->SetLimits( m[0], m[sz-1] ) ;
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
   leg1->AddEntry( gth, "SPS8 Theory LO cross-section", "L");
   leg1->AddEntry( g0,  "Observed 95% CL upper limit" , "L");
   leg1->Draw("same") ;

   TGaxis *lAxis = new TGaxis(154.5, 0.004, 299.5, 0.004,110, 210, 5,"+L");
   lAxis->SetTitle("SUSY #Lambda [TeV]");
   lAxis->SetLabelSize(0.04);
   lAxis->SetTitleSize(0.04);
   //lAxis->SetTitleFont(42);
   lAxis->SetTitleOffset(1.2);
   lAxis->Draw("sames");

   gPad->RedrawAxis();
   


   CMS_lumi( c2a, 2, 11 ) ;
   c2a->Update();

   TString gPlotname = hfolder +  limitPlotName  ;
   c2a->Print( gPlotname ) ;
   delete c2a ;

}

float findLimit( const int sz, float lm[], float x[], float Theo[]  ) {

   float xs1[2] = {0,0} ;
   float xs2[2] = {0,0} ;
   int k = -1 ;

   if ( lm[sz-1] < Theo[sz-1] ) {
      printf(" Extrapolote ") ;
      xs2[0] = lm[sz-1] ;
      xs2[1] = lm[sz-2] ;
      k = sz-2 ;
   } else {
     for (int i = sz-1; i>= 0; i-- ) {
         if ( lm[i] > Theo[i] ) xs2[0] = lm[i] ;
         if ( lm[i] < Theo[i] ) {
                             xs2[1] = lm[i] ;
                             k = i ;
                             printf(" Interpolate(%d,%d) \n", i, i+1) ;
                             break ;
         }
     }
   }
    
   if ( k <  0 ) return -999. ;
   // m = d_Lambda / d_Limit 
   float m = (x[k+1] - x[k])/(xs2[0] - xs2[1])  ;
   float b = x[k] -  (m*xs2[1] ) ;
   float n = (x[k+1] - x[k])/(Theo[k+1] - Theo[k])  ;
   float a = x[k] -  (n*Theo[k] ) ;

   float lambda0 = ( (n*b) - (m*a) )/(n-m) ;
   float limit0  =  (a-b)/(m-n) ;

   printf(" k = %d , m = %.3f b =%.3f m[%.5f ~ %.5f] in [%.1f ~ %.1f] \n", k, m ,b,  xs2[1], xs2[0], x[k] , x[k+1] )  ;
   printf("         n = %.3f a =%.3f n[%.5f ~ %.5f] \n", n, a, Theo[k] , Theo[k+1] ) ;
   printf(" higher lambda limit : %.2f at %.2f TeV ( %.2f GeV ) \n", limit0, lambda0, (lambda0*1.45) -5 ) ;

   float Lambda_Limit = (lambda0*1.45) -5 ;
   return Lambda_Limit ;
}

