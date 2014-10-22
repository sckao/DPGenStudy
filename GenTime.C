#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void TimeAccept() {

    TString plotname0  = "TimeDist.png" ;
    TString plotname1 = "TimeAccept.png" ;
    TString plotname2 = "TimeEfficiency.png" ;
    TString plotname3 = "Time_PtDist.png" ;
    string xlable = "ECAL Time (ns) " ;
    string hName = "h_time" ;
    string hName1 = "h_latePt" ;

    TString fileName = "TCuts_RunBCD_new/histo_trig_gmsb_" ;
    TString names[7] = { "250","500","1000", "2000", "3000", "4000", "6000" } ;
    int color[7]     = {     1,    2,     4,      5,    6,      7,      8   } ;
     

    TFile* hfile[7] ;
    TH1D*  hTime[7] ;
    TH1D*  hPt[7] ;

    for ( int i=0 ; i< 7; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );
        hTime[i]  = (TH1D *) hfile[i]->Get( hName.c_str() )  ;
        hPt[i]    = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
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
    gStyle->SetOptStat(kTRUE);
    gStyle->SetOptFit(111);
    c0->SetLogy();

    TLegend* leg1  = new TLegend(.55, .68, .95, .90 );
    leg1->Clear();
    char legStr[100] ;

    double nGen[7] = { 50112, 50112, 50112, 50112, 50112, 46944, 50112 } ;
    double nReco[7] , nObs[7] ;
    double eff[7],  eff_u[7] , eff_d[7] ;
    double reff[7], reff_u[7] , reff_d[7] ;
    double ctau[7] = {250,500,1000,2000,3000,4000,6000} ;
    double errX[7] = {  0,  0,   0,   0,   0,   0,   0} ;
    for ( int i = 0; i < 7; i++ ) {
        // calculate the number 
        nReco[i] = hTime[i]->Integral() ;
        nObs[i]  = hTime[i]->Integral(32, 100) ;

        // Setup color and draw histogram
        hTime[i]->Rebin(2) ;
        hTime[i]->SetLineColor( color[i] ) ;
        if ( i ==0 )  hTime[i]->Draw() ;
        else          hTime[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f / %.0f = %.5f ", nObs[i],  nReco[i],  nObs[i]/ nReco[i] ) ;
        leg1->AddEntry( hTime[i], names[i] + legStr,  "L");
        c0->Update() ;  
        printf( " nObs:%.1f nReco:% 1.f  \n",  nObs[i],  nReco[i] ) ;
    }

    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( plotname0 );

    // Pt spectrum
    c0->cd();
    c0->SetLogy();
    leg1->Clear() ;
    for ( int i = 6; i >=0 ; i-- ) {
        // Setup color and draw histogram
        hPt[i]->Rebin(2) ;
        hPt[i]->SetLineColor( color[i] ) ;
        if ( i == 6 )  hPt[i]->Draw() ;
        else          hPt[i]->Draw("SAMES") ;
        sprintf( legStr,  ":  %.0f ", hPt[i]->Integral()  ) ;
        leg1->AddEntry( hPt[i], names[i] + legStr,  "L");
        c0->Update() ;  
    }
    leg1->Draw("sames") ;
    c0->Update() ;  
    c0->Print( plotname3 );

    // Efficiency Plots
    TH1D* hObs      = new TH1D("hObs", " ",  7,  0, 7 );
    TH1D* hRec      = new TH1D("hRec", " ",  7,  0, 7 );
    TH1D* hGen      = new TH1D("hGen", " ",  7,  0, 7 );
    for ( int i=0; i< 7 ; i++ ) {
        hObs->SetBinContent( i+1 , nObs[i]*10. ) ;
        hRec->SetBinContent( i+1 , nReco[i] ) ;
        hGen->SetBinContent( i+1 , nGen[i] ) ;
    }
    TGraphAsymmErrors* acc_x = new TGraphAsymmErrors();
    acc_x->BayesDivide( hObs, hGen );
    TGraphAsymmErrors* eff_x = new TGraphAsymmErrors();
    eff_x->BayesDivide( hRec, hGen );

    /*
    for ( int i = 0; i < 7; i++ ) {
        // calculate efficiency and errors 
        pair<double,double> errs = EffError( nGen, nObs[i]*10. ) ;
        eff[i]   = nObs[i] / nGen ;
        eff_u[i] = 100.*errs.first  ;
        eff_d[i] = 100.*errs.second  ;
        printf( " Final eff = %.3f , err_d: %.8f , err_u: %.8f \n", eff[i], eff_d[i], eff_u[i] ) ;

        pair<double,double> rerrs = EffError( nGen, nReco[i] ) ;
        reff[i]   = nReco[i] / nGen ;
        reff_u[i] = rerrs.first  ;
        reff_d[i] = rerrs.second  ;
        printf( " Reco eff = %.3f , err_d: %.8f , err_u: %.8f \n", reff[i], reff_d[i], rerrs.first ) ;
    }
    */
    
    //TGraphAsymmErrors* acc_x = new TGraphAsymmErrors( 50, ctau, eff, errX, errX, eff_d, eff_u ); // SC's result !

    c0->cd();
    c0->SetLogy(0);

    acc_x->SetTitle(" Acceptance (t > 3 ns) ") ;
    acc_x->SetMaximum( 0.15 );
    acc_x->SetMinimum( 0.0 );
    acc_x->SetMarkerColor(4);
    acc_x->SetMarkerStyle(22);
    acc_x->SetMarkerSize(1);
    acc_x->SetLineColor(1);
    acc_x->SetLineWidth(2);
    acc_x->GetXaxis()->SetTitleOffset(1.34);
    acc_x->GetYaxis()->SetTitleOffset(1.41);

    acc_x->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    acc_x->GetYaxis()->SetTitle(" Efficiency x 10 ") ;
    //acc_x->GetXaxis()->SetLimits( 200, 6500 );
    acc_x->Draw("AP");
    c0->Update();
    c0->Print( plotname1 );
    
    eff_x->SetTitle(" Reco Efficiency ( |t|< 25 ns) ") ;
    eff_x->SetMaximum( 0.15 );
    eff_x->SetMinimum( 0.0 );
    eff_x->SetMarkerColor(2);
    eff_x->SetMarkerStyle(22);
    eff_x->SetMarkerSize(1);
    eff_x->SetLineColor(1);
    eff_x->SetLineWidth(2);
    eff_x->GetXaxis()->SetTitleOffset(1.34);
    eff_x->GetYaxis()->SetTitleOffset(1.41);

    eff_x->GetXaxis()->SetTitle(" Neutralino c#tau (mm) " ) ;
    eff_x->GetYaxis()->SetTitle(" Reco Efficiency ") ;
    //eff_x->GetXaxis()->SetLimits( 200, 6500 );
    
    eff_x->Draw("AP");
    c0->Update();
    c0->Print( plotname2 );


    /*
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

    */
    delete c0 ;
}

pair<double, double> EffError( double N_all, double N_pass ) {

    if ( N_all < 0.0001 ) {
       pair<double,double> noErr  = make_pair( 0 , 0 );
       printf(" No Error !! \n" ) ;
       return noErr ;
    }

    double eff0 = N_pass / N_all ;
    if ( eff0 > 1 ) {
       pair<double,double> noErr = make_pair( 0 , 0 );
       printf(" No Error !! \n" ) ;
       return noErr ;
    }
    //cout<<" N_All: "<<N_all <<"  N_pass: "<< N_pass << endl;
    int nStep = 1000 ;
    double step = 1. / (double)nStep ;
    //cout<<" step = "<< step <<endl;
    Double_t par[3] = { 1, N_all, N_pass } ;
    Double_t xL[1] = { eff0 } ;
    Double_t xR[1] = { eff0 } ;
    double IntEff = (N_all+ 1) * step * BinomialErr( xR, par ) ;
    //cout<<" Eff 0th : "<< BinomialErr( xR, par ) << endl ;  
    //printf(" Eff 0th : %.5f \n",  eff0 ) ;   

    bool skipR = false ;
    bool skipL = false ;
    Double_t pR = 0. ;
    Double_t pL = 0. ;
    while ( IntEff < 0.683)  {
        if ( !skipR && xR[0] < 1. ) {
           xR[0] +=  step ;
           pR = BinomialErr( xR, par ) ;
           IntEff += (pR*step*(N_all+1) ) ;
           cout<<" ("<< xR[0] <<") --> R : "<< IntEff <<"  pR = "<< pR <<endl ;
        }
        if ( !skipL && xL[0] > 0. ) {
           xL[0] -=  step ;
           pL = BinomialErr( xL, par ) ;
           IntEff += (pL*step*(N_all+1) ) ;
           cout<<" ("<< xL[0] <<") <-- L : "<< IntEff <<"  pL = "<< pL <<endl;
        }
        cout<<" ------ "<<endl; 
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
  printf("     ( %f,%.1f,%.1f,%.1f ) = %f\n", x[0], par[0], par[1], par[2], betaPDF ) ;
  Double_t prob = (par[0] / (N_all + 1.) ) * betaPDF ;
  

  if ( x[0] < 0. || x[0] > 1. ) prob = 0. ;

  return prob ;

}

