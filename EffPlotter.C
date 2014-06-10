#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void EffPlotter() {

    //TString plotname = "Photon_EffAsym.png" ;
    //tring xlable = "Photon P_{T} (GeV/c) " ;
    //string hName = "h_gPt_trg" ;
    //string AName = "h_gPt_sel" ;
    TString plotname = "PFMET_EffAsym.png" ;
    string xlable = "MET (GeV) " ;
    string hName = "h_met_trg" ;
    string AName = "h_met_sel" ;

    TFile *file0  = TFile::Open("TCuts_RunBCD_new/histo_trig_pho50.root");
    TFile *file1  = TFile::Open("TCuts_RunBCD_new/histo_trig_gmsb.root");
    TFile *file2  = TFile::Open("TCuts_RunBCD_new/histo_trig_gj.root");

    TH1D* h_data  = (TH1D *) file0->Get( hName.c_str() )  ;
    TH1D* h_gmsb  = (TH1D *) file1->Get( hName.c_str() )  ;
    TH1D* h_gjet  = (TH1D *) file2->Get( hName.c_str() )  ;

    TH1D* A_data  = (TH1D *) file0->Get( AName.c_str() )  ;
    TH1D* A_gmsb  = (TH1D *) file1->Get( AName.c_str() )  ;
    TH1D* A_gjet  = (TH1D *) file2->Get( AName.c_str() )  ;


    gStyle->SetOptStat("");
 
    
    double xMin, xMax, xMin1, xMax1, xMin2, xMax2 ;
    TGraphAsymmErrors* eff_data = EffPlot( h_data, A_data , 25., 1, -1, xMin, xMax );
    TGraphAsymmErrors* eff_gmsb = EffPlot( h_gmsb, A_gmsb , 25., 1, -1, xMin1, xMax1 );
    TGraphAsymmErrors* eff_gjet = EffPlot( h_gjet, A_gjet , 25., 1, -1, xMin2, xMax2 );

    // Plot

    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    gPad->SetGridx();
    gPad->SetGridy();
    c0->SetLeftMargin(0.15);
    c0->SetRightMargin(0.12);
    c0->SetTopMargin(0.1);
    c0->SetBottomMargin(0.12);

    c0->cd();
    gStyle->SetOptStat(kTRUE);
    gStyle->SetOptFit(111);

    eff_gjet->SetTitle(" CMS Preliminary #sqrt{s} = 8 TeV ") ;
    eff_gjet->SetMaximum( 1.1 );
    eff_gjet->SetMinimum( 0.0 );
    eff_gjet->SetMarkerColor(1);
    eff_gjet->SetMarkerStyle(22);
    eff_gjet->SetMarkerSize(1);
    eff_gjet->SetLineColor(1);
    eff_gjet->SetLineWidth(2);
    eff_gjet->GetXaxis()->SetTitleOffset(1.34);
    eff_gjet->GetYaxis()->SetTitleOffset(1.39);

    eff_gjet->GetXaxis()->SetTitle( xlable.c_str() ) ;
    eff_gjet->GetYaxis()->SetTitle(" Efficiency ") ;
    eff_gjet->GetXaxis()->SetLimits( xMin2, xMax2 );
    
    eff_gjet->Draw("AP");
    c0->Update();
    
    eff_gmsb->SetMarkerColor(2);
    eff_gmsb->SetMarkerStyle(21);
    eff_gmsb->SetMarkerSize(1);
    eff_gmsb->SetLineColor(2);
    eff_gmsb->SetLineWidth(2);
    eff_gmsb->Draw("SAMEP");
    c0->Update();

    eff_data->SetMarkerColor(4);
    eff_data->SetMarkerStyle(20);
    eff_data->SetMarkerSize(1);
    eff_data->SetLineColor(4);
    eff_data->SetLineWidth(2);
    eff_data->Draw("SAMEP");
    c0->Update();

    // Legend
    TLegend* leg1  = new TLegend(.65, .5, .85, .7 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30], RStr2[30] ;
    sprintf( RStr0,  "Data" ) ;
    sprintf( RStr1,  "GMSB" ) ;
    sprintf( RStr2,  "G+Jets") ;

    leg1->AddEntry( eff_data, RStr0,  "P");
    leg1->AddEntry( eff_gmsb, RStr1,  "P");
    leg1->AddEntry( eff_gjet, RStr2,  "P");
    
    leg1->Draw("SAME") ;    
    c0->Update();

    c0->Print( plotname );

    delete c0 ;
}

// Drawing Efficiency Plot from two histograms    
TGraphAsymmErrors* EffPlot( TH1D* hCut, TH1D* hAll, double minBinContent, int beginBin, int endBin, double& xMin, double& xMax ) {

   endBin = ( endBin == -1 ) ? hAll->GetNbinsX() : endBin ;

   double ba = 0 ;
   double bc = 0 ;
   double x  = 0 ;
   double rbin  = 0 ;
   double rbin_ = 0 ;
   vector<double> baV ;
   vector<double> bcV ;
   vector<double> xV ;
   vector<double> xW ;
   vector<double> errL;
   vector<double> errH;
   /*
   xV.clear() ;
   xW.clear() ;
   yV.clear() ;
   errL.clear() ;
   errH.clear() ;
   */
   double bW = hCut->GetBinWidth(1) ;
   cout<<" bin width = " << bW <<" end bin = "<< endBin << endl ;

   // Accumulate bin contain
   for ( int i= beginBin ; i<= endBin; i++ ) {
       double bc_ = hCut->GetBinContent(i) ;
       double ba_ = hAll->GetBinContent(i) ;
       double x_  = hAll->GetBinCenter(i) ;
       printf("\n     (%d)_%.2f =  %.2f/%.2f ", i, x_, bc_, ba_ ) ;
       if ( bc_ ==0 && ba_ ==0 ) continue ;
       // rebin the histogram in order to have consistence statistic for each bin
       if ( ba < minBinContent || ba < bc || rbin < rbin_ ) {
          ba += ba_ ;
          bc += bc_ ;
          x  +=  x_ ;
          rbin++ ;
          if ( i == endBin || (ba >= minBinContent && ba >= bc && rbin >= rbin_) ) {
             bcV.push_back( bc ) ;
             baV.push_back( ba ) ;
             xV.push_back( x / rbin )  ;
             xW.push_back( rbin * bW / 2.) ;
             //yV.push_back( bc/ba ) ;
             // sc's method to calculate error
             pair<double,double> errs = EffError( ba, bc ) ;
             errH.push_back( errs.first ) ;
             errL.push_back( errs.second ) ;
             printf(" + ( %.2f) - (%.2f ) ", errs.first, errs.second ) ;
             rbin_ = rbin ;
             //cout<<" x: "<< x/rbin <<" rb: "<< rbin <<" bW:"<< (rbin*bW) / 2. << "  bc: "<< bc <<"  ba: "<< ba ;
             //cout<<" eff:"<< bc/ba <<" + "<< errs.first <<" - "<< errs.second << endl ;
             //printf(" x[%d]:%.2f , %.2f  \n", (int)xV.size(), x/rbin, (rbin*bW/2.) ) ;
             bc   = 0 ;
             ba   = 0 ;
             x    = 0 ;
             rbin = 0 ;
             rbin_ = 0 ;
          }
       }
   }
   cout<<" nbins = "<< xV.size() <<endl ;

   // calculate proper error
   int sz = (int) xV.size() ;
   
   // static const int sz = (int) xV.size() ;
   Double_t fX[50], eX[50];
   Double_t yA[50], eY_L[50], eY_H[50] ;  // for SC's method
   for ( int i=0 ; i< 50 ; i++) {
       fX[i]   = 0. ;
       eX[i]   = 0. ;
       yA[i]   = 0. ;
       eY_L[i] = 0. ;
       eY_H[i] = 0. ;
   }
   for ( int i=0 ; i< sz ; i++) {
       fX[i]  = xV[i] ;
       eX[i]  = xW[i] ;
       yA[i]   = bcV[i] / baV[i] ;
       eY_L[i] = errL[i] ;
       eY_H[i] = errH[i] ;
   }

   xMin =  fX[0]    - eX[0]   ;
   xMax =  fX[sz-1] + eX[sz-1] ;

   TGraphAsymmErrors* gr = new TGraphAsymmErrors( 50, fX, yA, eX, eX, eY_L, eY_H ); // SC's result !
   
   return gr ;

}

pair<double, double> EffError( double N_all, double N_pass ) {

    if ( N_all < 0.0001 ) {
       pair<double,double> noErr  = make_pair( 0 , 0 );
       return noErr ;
    }

    double eff0 = N_pass / N_all ;
    if ( eff0 > 1 ) {
       pair<double,double> noErr = make_pair( 0 , 0 );
       return noErr ;
    }
    //cout<<" N_All: "<<N_all <<"  N_pass: "<< N_pass << endl;
    int nStep = 1000 ;
    double step = 1. / nStep ;
    //cout<<" step = "<< step <<endl;
    Double_t par[3] = { 1, N_all, N_pass } ;
    Double_t xL[1] = { eff0 } ;
    Double_t xR[1] = { eff0 } ;
    double IntEff = (N_all+ 1) * step * BinomialErr( xR, par ) ;
    //cout<<" Eff 0th : "<< BinomialErr( xR, par ) << endl ;  

    bool skipR = false ;
    bool skipL = false ;
    Double_t pR = 0. ;
    Double_t pL = 0. ;
    while ( IntEff < 0.683)  {
        if ( !skipR && xR[0] < 1. ) {
           xR[0] +=  step ;
           pR = BinomialErr( xR, par ) ;
           IntEff += (pR*step*(N_all+1) ) ;
           //cout<<" ("<< xR[0] <<") --> R : "<< IntEff <<"  pR = "<< pR <<endl ;
        }
        if ( !skipL && xL[0] > 0. ) {
           xL[0] -=  step ;
           pL = BinomialErr( xL, par ) ;
           IntEff += (pL*step*(N_all+1) ) ;
           //cout<<" ("<< xL[0] <<") <-- L : "<< IntEff <<"  pL = "<< pL <<endl;
        }
        //cout<<" ------ "<<endl; 
        skipR = ( pL > pR ) ? true : false ;
        skipL = ( pL < pR ) ? true : false ;
        if ( pL == pR ) {
           skipR = false ;
           skipL = false ;
        }
    }
    //cout<<"  ["<< N_pass/N_all <<"] Prob = "<< IntEff <<endl ; 
    //cout<<"                 - "<< (N_pass/N_all) - xL[0] <<endl ;
    //cout<<"                 + "<< xR[0] - (N_pass/N_all) <<endl ;
    double upErr = xR[0] - eff0  ;
    double dnErr = eff0 - xL[0] ;
    pair<double,double> theErr = make_pair( upErr, dnErr );

    return theErr ;
}

Double_t BinomialErr( Double_t* x, Double_t* par ) {

  Double_t N_all  = par[1] ;
  Double_t N_pass = par[2] ;

  //Double_t Bxy = TMath::Beta( ( N_pass + 1 ), ( N_all - N_pass + 1 ) ) ;
  //cout<< " Beta(x,y) = "<< Bxy <<endl ;
  //Double_t Cnk = pow(x[0], N_pass ) * pow( (1-x[0]) , (N_all - N_pass) ) ;
  //Double_t prob = par[0]*Cnk / ( Bxy * (N_all + 1. ) );

  double betaPDF = TMath::BetaDist( x[0],  (N_pass + 1) , (N_all - N_pass + 1) ) ;
  Double_t prob = (par[0] / (N_all + 1.) ) * betaPDF ;

  if ( x[0] < 0 || x[0] > 1 ) prob = 0 ;

  return prob ;

}

