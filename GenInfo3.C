#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void GenInfo3() {

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TString fileName = "TCuts_GMSB_L180/GMSB180_2J_" ;

    TString plotname0 = "Eff_xbeta.png" ;
    TString plotname1 = "Eff_time.png" ;
    TString plotname2 = "Eff_xPt.png" ;
    TString plotname3 = "Eff_gPt.png" ;
    TString plotname4 = "Eff2D_xPt_ct" ;
    TString plotname5 = "pass_xPt_ct.png" ;
    TString plotname6 = "reco_xPt_ct.png" ;

    string hName0 = "reco_xbeta" ;
    string hName1 = "sel_xbeta" ;
    string hName2 = "h_Time" ;
    string hName3 = "h_genTime" ;
    string hName4 = "reco_xPt" ;
    string hName5 = "sel_xPt" ;
    string hName6 = "reco_gPt" ;
    string hName7 = "sel_gPt" ;
    string hName8 = "reco_xPt_ctbgT" ;
    string hName9 = "sel_xPt_ctbgT" ;

    /*
    double nGen[5] = { 50112, 50112, 50112, 50112, 50112 } ;
    TString names[5] = { "250","500", "2000", "4000", "6000" } ;
    int color[5]     = {     1,    2,      4,      6,     8  } ;
    const int nModel = 5;
    */
     
    double nGen[7]   = { 50112, 50112, 50112,  50112,  50112,  46944,  50112 } ;
    TString names[7] = { "250", "500","1000", "2000", "3000", "4000", "6000" } ;
    int color[7]     = {     1,     2,     4,      5,      6,      7,      8 } ;
    const int nModel = 7;
    

    TFile* hfile[ nModel ] ;

    TH1D*  sel_xbeta[ nModel ] ;
    TH1D*  reco_xbeta[ nModel ] ;
    TH1D*  h_Time[ nModel ] ;
    TH1D*  h_genTime[ nModel ] ;
    TH1D*  sel_xPt[ nModel ] ;
    TH1D*  reco_xPt[ nModel ] ;
    TH1D*  sel_gPt[ nModel ] ;
    TH1D*  reco_gPt[ nModel ] ;
    TH2D*  sel_xPt_ct[ nModel ] ;
    TH2D*  reco_xPt_ct[ nModel ] ;

    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );

        reco_xbeta[i]  = (TH1D *) hfile[i]->Get( hName0.c_str() )  ;
        sel_xbeta[i]   = (TH1D *) hfile[i]->Get( hName1.c_str() )  ;
        h_Time[i]      = (TH1D *) hfile[i]->Get( hName2.c_str() )  ;
        h_genTime[i]   = (TH1D *) hfile[i]->Get( hName3.c_str() )  ;
        reco_xPt[i]    = (TH1D *) hfile[i]->Get( hName4.c_str() )  ;
        sel_xPt[i]     = (TH1D *) hfile[i]->Get( hName5.c_str() )  ;
        reco_gPt[i]    = (TH1D *) hfile[i]->Get( hName6.c_str() )  ;
        sel_gPt[i]     = (TH1D *) hfile[i]->Get( hName7.c_str() )  ;
        reco_xPt_ct[i] = (TH2D *) hfile[i]->Get( hName8.c_str() )  ;
        sel_xPt_ct[i]  = (TH2D *) hfile[i]->Get( hName9.c_str() )  ;
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

    TLegend* leg1  = new TLegend(.80, .65, .95, .90 );
    leg1->Clear();
    char legStr[100] ;

    // Plot0 
    TGraphAsymmErrors* eff_xbeta[nModel] ;
    leg1->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_xbeta[i]= new TGraphAsymmErrors();

        eff_xbeta[i]->BayesDivide( sel_xbeta[i], reco_xbeta[i] );   
        eff_xbeta[i]->SetMarkerColor( color[i] );
        eff_xbeta[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_xbeta[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_xbeta[i]->SetTitle(" Efficiency") ;
           eff_xbeta[i]->SetMaximum( 0.4 );
           eff_xbeta[i]->SetMinimum( 0.0 );
           eff_xbeta[i]->SetMarkerStyle(22);
           eff_xbeta[i]->SetMarkerSize(1);
           eff_xbeta[i]->SetLineWidth(2);
           eff_xbeta[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_xbeta[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_xbeta[i]->GetXaxis()->SetTitle(" Neutralino #beta (mm) " ) ;
           eff_xbeta[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff_xbeta[i]->Draw("AP");
        } else {
           eff_xbeta[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname0 );


    // Plot1
    TGraphAsymmErrors* eff_time[nModel] ;
    leg1->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_time[i]= new TGraphAsymmErrors();

        h_genTime[i]->Rebin(4) ;
        h_Time[i]->Rebin(4) ;

        eff_time[i]->BayesDivide( h_genTime[i], h_Time[i] );   
        eff_time[i]->SetMarkerColor( color[i] );
        eff_time[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_time[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_time[i]->SetTitle(" Efficiency") ;
           eff_time[i]->SetMaximum( 0.4 );
           eff_time[i]->SetMinimum( 0.0 );
           eff_time[i]->SetMarkerStyle(22);
           eff_time[i]->SetMarkerSize(1);
           eff_time[i]->SetLineWidth(2);
           eff_time[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_time[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_time[i]->GetXaxis()->SetTitle(" ECAL Time (ns) " ) ;
           eff_time[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff_time[i]->Draw("AP");
        } else {
           eff_time[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname1 );

    // Plot2
    TGraphAsymmErrors* eff_xPt[nModel] ;
    leg1->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_xPt[i]= new TGraphAsymmErrors();

        reco_xPt[i]->Rebin(2) ;
        sel_xPt[i]->Rebin(2) ;

        eff_xPt[i]->BayesDivide( sel_xPt[i], reco_xPt[i] );   
        eff_xPt[i]->SetMarkerColor( color[i] );
        eff_xPt[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_xPt[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_xPt[i]->SetTitle(" Efficiency") ;
           eff_xPt[i]->SetMaximum( 0.4 );
           eff_xPt[i]->SetMinimum( 0.0 );
           eff_xPt[i]->SetMarkerStyle(22);
           eff_xPt[i]->SetMarkerSize(1);
           eff_xPt[i]->SetLineWidth(2);
           eff_xPt[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_xPt[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_xPt[i]->GetXaxis()->SetTitle(" P_{T} of neutralino (GeV/c) " ) ;
           eff_xPt[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff_xPt[i]->Draw("AP");
        } else {
           eff_xPt[i]->Draw("SAMEPS");
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname2 );

    // Plot3
    TGraphAsymmErrors* eff_gPt[nModel] ;
    leg1->Clear() ;
    for ( int i=1; i< nModel; i++ ) {
        eff_gPt[i]= new TGraphAsymmErrors();

        reco_gPt[i]->Rebin(2) ;
        sel_gPt[i]->Rebin(2) ;

        eff_gPt[i]->BayesDivide( sel_gPt[i], reco_gPt[i] );   
        eff_gPt[i]->SetMarkerColor( color[i] );
        eff_gPt[i]->SetLineColor( color[i] );
        leg1->AddEntry( eff_gPt[i], names[i]  ,  "L");

        if ( i ==1 ) {
           c0->cd();
           c0->SetLogy(0);

           eff_gPt[i]->SetTitle(" Efficiency") ;
           eff_gPt[i]->SetMaximum( 0.4 );
           eff_gPt[i]->SetMinimum( 0.0 );
           eff_gPt[i]->SetMarkerStyle(22);
           eff_gPt[i]->SetMarkerSize(1);
           eff_gPt[i]->SetLineWidth(2);
           eff_gPt[i]->GetXaxis()->SetTitleOffset(1.34);
           eff_gPt[i]->GetYaxis()->SetTitleOffset(1.41);

           eff_gPt[i]->GetXaxis()->SetTitle(" P_{T} of Photon (GeV/c) " ) ;
           eff_gPt[i]->GetYaxis()->SetTitle(" Reco_Efficiency ") ;
           eff_gPt[i]->Draw("AP");
        } else {
           eff_gPt[i]->Draw("SAMEPS");
        }
        if ( i == nModel -1 ) {
           double* val_y = eff_gPt[i]->GetY() ;
	   double* val_x = eff_gPt[i]->GetX() ;
           for ( int j= 0; j < eff_gPt[i]->GetN() ; j++ ) {
                printf(" (%d) x = %.1f , y = %.3f \n", j, val_x[j], val_y[j] ) ;
           }
        }

    }
    leg1->Draw("sames") ;
    c0->Update();
    c0->Print( hfolder + plotname3 );

    // Plot4
    TCanvas* c1 = new TCanvas("c1","", 800, 700);
    c1->SetFillColor(10);
    c1->SetFillColor(10);
    c1->Divide(2, 3) ;

    sel_xPt_ct[0]->RebinY(2);
    reco_xPt_ct[0]->RebinY(2);
    TH2D* sel_All = (TH2D*) sel_xPt_ct[0]->Clone("sel_All") ;
    TH2D* rec_All = (TH2D*) reco_xPt_ct[0]->Clone("rec_All") ;
    for ( int i=1; i< nModel; i++ ) {

        sel_xPt_ct[i]->RebinY(2);
        reco_xPt_ct[i]->RebinY(2);

        sel_All->Add( sel_xPt_ct[i] );
        rec_All->Add( reco_xPt_ct[i] );

        TH2D* hEff = (TH2D*) sel_xPt_ct[i]->Clone("hEff") ;
        hEff->Divide( reco_xPt_ct[i] ) ;

        c1->cd(i);
 
        hEff->SetMaximum(1.0) ;
        gStyle->SetNumberContours( 10 );
        hEff->Draw("COLZ") ;

	c1->Update();
    }
    c1->Print( hfolder + plotname4 + ".png" );


    // Over all efficiency
    TH2D* hEff_All = (TH2D*) sel_All->Clone("hEff_All") ;
    hEff_All->Divide( rec_All ) ;
    c0->cd() ;
    hEff_All->SetMaximum(0.5) ;
    gStyle->SetNumberContours( 10 );
    hEff_All->Draw("COLZ");
    c0->Update() ;
    c0->Print( hfolder + plotname4 + "_all.png" ) ;

    //for ( int j= hEff_All->GetNbinsY(); j>=1; j-- ) {
    for ( int j= 1 ; j <= hEff_All->GetNbinsY();  j++ ) {
        for ( int i=1; i<= hEff_All->GetNbinsX(); i++ ) {
            if ( i == 16 ) printf("\n" ) ;
            if ( i >= 16 ) continue ;

            // error calculation
            
            double nA =  rec_All->GetBinContent(i,j)  ;
            double nP =  sel_All->GetBinContent(i,j)  ;
            // if ( i > 0) printf(" %.f/%.f=", nP,nA ) ;
            double errs =  EffError( nA, nP, false ) ;
            if ( i > 0 ) printf(" %.5f,", errs ) ;
            
            // Efficiency 
            //if ( i > 0 ) printf(" %.5f,", hEff_All->GetBinContent(i,j) ) ;
        }
        for ( int i=1; i<= hEff_All->GetNbinsX(); i++ ) {
            if ( i == 16 && j == hEff_All->GetNbinsY() ) printf("\n" ) ;
            if ( i >= 16 ) continue ;

            if ( j== hEff_All->GetNbinsY() )  printf(" %7d ", i ) ;
            //if ( i== hEff_All->GetNbinsX() )  printf("\n" ) ;
        }
    }

    /*
    printf(" Error for Efficiency \n") ;
    for ( int j= 1 ; j <= hEff_All->GetNbinsY();  j++ ) {
        for ( int i=0; i<= hEff_All->GetNbinsX(); i++ ) {
            if ( i == 14 ) printf("\n" ) ;
            if ( i >= 14 ) continue ;
            
            // error calculation
            double nA =  rec_All->GetBinContent(i,j)  ;
            double nP =  sel_All->GetBinContent(i,j)  ;
            double errs =  EffError( nA, nP, false ) ;
            double errR = ( hEff_All->GetBinContent(i,j)  > 0. ) ? errs/hEff_All->GetBinContent(i,j) : 0. ;
            if ( i > 0 ) printf(" %.3f,", errR ) ;
            
        }
    }
    */

    // Plot5
    for ( int i=1; i< nModel; i++ ) {
        c1->cd(i) ;
        
        sel_xPt_ct[i]->Draw("COLZ") ;
        c1->Update();
    }
    c1->Print( hfolder + plotname5  );

    // Plot6
    c1->Clear() ;
    c1->Divide(2, 3) ;
    for ( int i=1; i< nModel; i++ ) {
        c1->cd(i) ;
        
        reco_xPt_ct[i]->Draw("COLZ") ;
        c1->Update();
    }
    c1->Print( hfolder + plotname6  );
 
    delete c0 ;
    delete c1 ;

}

//pair<double, double> EffError( double N_all, double N_pass ) {
double EffError( double N_all, double N_pass, bool isUp ) {

    if ( N_all < 0.0001 ) {
       return 0. ;
    }

    double eff0 = N_pass / N_all ;
    if ( eff0 > 1 ) {
       return 0. ;
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
    //pair<double,double> theErr = make_pair( upErr, dnErr );
    //return theErr ;
    if ( isUp ) return upErr ;
    else        return dnErr ;

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

  if ( x[0] < 0. || x[0] > 1. ) prob = 0. ;

  return prob ;

}

