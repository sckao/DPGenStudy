#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Eff_XPt_ctau() {

    gROOT->LoadMacro("CMS_lumi.C");

    TString hfolder  = "TCuts_GMSB_L180/" ;
    TString fileName = "TCuts_GMSB_L180/GMSB2J_180_" ;

    TString plotname4 = "Eff2D_xPt_ct" ;
    TString plotname5 = "pass_xPt_ct.png" ;
    TString plotname6 = "reco_xPt_ct.png" ;

    string hName0 = "reco_xPt_ctT" ;
    string hName1 = "sel_xPt_ctT" ;


    // Lambda 180
    double nGen[8]   = { 50000, 50000, 50000, 50000,  50000,  50000, 50000,   50000  } ;
    TString names[8] = { "185", "365", "730","1100", "2195", "3950", "5980", "10450" } ;
    int color[8]     = {     1,     2,     3,     4,      5,      6,      7,     8   } ;
    const int nModel = 8;


    TFile* hfile[ nModel ] ;

    TH2D*  sel_xPt_ct[ nModel ]  ;
    TH2D*  reco_xPt_ct[ nModel ] ;

    for ( int i=0 ; i< nModel ; i++ ) {
        hfile[i]  = TFile::Open( fileName+names[i]+".root" );

        reco_xPt_ct[i] = (TH2D *) hfile[i]->Get( hName0.c_str() )  ;
        sel_xPt_ct[i]  = (TH2D *) hfile[i]->Get( hName1.c_str() )  ;
    }

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
    gStyle->SetOptTitle(0);
    //gStyle->SetOptFit(111);
    //gStyle->SetTitleFontSize(0.05);

    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");
    //gPad->SetGridx();

    // Plot4
    TCanvas* c1 = new TCanvas("c1","", 800, 800);
    c1->SetFillColor(10);
    c1->SetFillColor(10);
    c1->SetTopMargin(0.05);
    //c1->SetBottomMargin(0.13);
    //c1->SetLeftMargin(0.16);
    //c1->SetRightMargin(0.12);

    c1->Divide(2, 3) ;
    // Legend
    TLatex latex ;
    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextSize(0.1);    
    latex.SetTextAlign(12); 
    latex.SetNDC() ;
		
    sel_xPt_ct[0]->RebinY(2);
    reco_xPt_ct[0]->RebinY(2);
    TH2D* sel_All = (TH2D*) sel_xPt_ct[0]->Clone("sel_All") ;
    TH2D* rec_All = (TH2D*) reco_xPt_ct[0]->Clone("rec_All") ;
    for ( int i=0; i< nModel; i++ ) {

        sel_xPt_ct[i]->RebinY(2);
        reco_xPt_ct[i]->RebinY(2);
        if ( i < 2 ) continue ; // do not plot short ctau cases

        sel_All->Add( sel_xPt_ct[i] );
        rec_All->Add( reco_xPt_ct[i] );

        TH2D* hEff = (TH2D*) sel_xPt_ct[i]->Clone("hEff") ;
        hEff->Divide( reco_xPt_ct[i] ) ;

        c1->cd(i-1);
        hEff->SetMaximum(0.4) ;
	hEff->GetXaxis()->SetTitleOffset(0.75);
	hEff->GetYaxis()->SetTitleOffset(0.6);
	hEff->GetXaxis()->SetTitleSize(0.07);
	hEff->GetYaxis()->SetTitleSize(0.07);
	hEff->GetXaxis()->SetTitle( "P_{T} of #chi^{0} (GeV)" ) ;
	hEff->GetYaxis()->SetTitle( "Transverse c#tau  (mm)" ) ;
        gStyle->SetNumberContours( 10 );
        hEff->Draw("COLZ") ;

        TString ct_str = "c#tau = " + names[i] + " mm";
        latex.DrawLatex( 0.5, 0.8,  ct_str );

	c1->Update();
    }
    //CMS_lumi( c1, 2, 11 ) ;
    //c0->Update();
    c1->Print( hfolder + plotname4 + ".png" );

    // Over all efficiency
    gStyle->SetLabelOffset(0.007, "XYZ");
    gStyle->SetLabelSize(0.05, "XYZ");

    TCanvas* c0 = new TCanvas("c0","", 800, 700);
    c0->SetFillColor(10);
    c0->SetFillColor(10);

    c0->SetTopMargin(0.05);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.12);
    c0->cd();
    //c0->SetLogy() ;
  
    TH2D* hEff_All = (TH2D*) sel_All->Clone("hEff_All") ;
    hEff_All->Sumw2() ;
    rec_All->Sumw2() ;
    hEff_All->Divide( rec_All ) ;
    c0->cd() ;

    hEff_All->GetXaxis()->SetTitleOffset(0.9);
    hEff_All->GetYaxis()->SetTitleOffset(1.25);
    hEff_All->GetXaxis()->SetTitleSize(0.06);
    hEff_All->GetYaxis()->SetTitleSize(0.06);
    hEff_All->GetXaxis()->SetTitle( "P_{T} of #chi^{0} (GeV)" ) ;
    hEff_All->GetYaxis()->SetTitle( "Transverse c#tau (mm)" ) ;

    hEff_All->SetMaximum(0.5) ;
    gStyle->SetNumberContours( 10 );
    hEff_All->Draw("COLZ");
    c0->Update() ;
    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();
    c0->Print( hfolder + plotname4 + "_all.png" ) ;

    //for ( int j= hEff_All->GetNbinsY(); j>=1; j-- ) {
    double aErr_u[300] = {0.} ;
    double aErr_d[300] = {0.} ;
    double Eff_a[300] = {0.} ;
    for ( int j= 1 ; j <= hEff_All->GetNbinsY();  j++ ) {
        for ( int i=1; i<= hEff_All->GetNbinsX(); i++ ) {
            if ( i == 16 ) printf("\n" ) ;
            if ( i >= 16 ) continue ;

            // error calculation
            double nA =  rec_All->GetBinContent(i,j)  ;
            double nP =  sel_All->GetBinContent(i,j)  ;
            //if ( i > 0) printf(" %.f/%.f=", nP,nA ) ;
            double errs_u =  EffError( nA, nP, true ) ;
            double errs_d =  EffError( nA, nP, false ) ;
            int k = ((j-1)*15) + (i-1) ;
            aErr_u[k] = errs_u ;
            aErr_d[k] = errs_d ;
            Eff_a[k] = hEff_All->GetBinContent(i,j) ;
            // Efficiency errors
            //if ( i > 0 ) printf(" %.5f,", errs ) ;
            //if ( i > 0 ) printf(" %.5f,", hEff_All->GetBinErrorLow(i,j) ) ;
            // Efficiency 
            if ( i > 0 ) printf(" %.5f,", hEff_All->GetBinContent(i,j) ) ;
        }
        for ( int i=1; i<= hEff_All->GetNbinsX(); i++ ) {
            if ( i == 16 && j == hEff_All->GetNbinsY() ) printf("\n" ) ;
            if ( i >= 16 ) continue ;

            if ( j== hEff_All->GetNbinsY() )  printf(" %7d ", i ) ;
            //if ( i== hEff_All->GetNbinsX() )  printf("\n" ) ;
        }
    }
    
    for ( int m=0; m< nModel; m++ ) {
        double sumErr_u = 0. ;
        double sumErr_d = 0. ;
        for ( int j= 1 ; j <= reco_xPt_ct[m]->GetNbinsY();  j++ ) {
            for ( int i=1; i<= reco_xPt_ct[m]->GetNbinsX(); i++ ) {
                if ( i >= 16 ) continue ;

                double ib = reco_xPt_ct[m]->GetBinContent(i,j) ;
                int k = ((j-1)*15) + (i-1) ;
                sumErr_u += ( (ib*aErr_u[k]*ib*aErr_u[k]) + (ib*Eff_a[k]*Eff_a[k]) ) ; 
                sumErr_d += ( (ib*aErr_d[k]*ib*aErr_d[k]) + (ib*Eff_a[k]*Eff_a[k]) ) ; 
            }
        }
        sumErr_u = sqrt( sumErr_u ) ;
        sumErr_d = sqrt( sumErr_d ) ;
        string model_name = names[m] ;
        printf(" model %s  +%.2f -%.2f \n", model_name.c_str(), sumErr_u, sumErr_d ) ;
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
    if ( eff0 > 1. || eff0 < 0. ) {
       return 0. ;
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

    bool skipR = false ;
    bool skipL = false ;
    Double_t pR = 0. ;
    Double_t pL = 0. ;
    while ( IntEff < 0.683)  {
        if ( !skipR && xR[0] < 1. ) {
           xR[0] +=  step ;
           pR = BinomialErr( xR, par ) ;
           IntEff += (pR*step*(N_all+1) ) ;
           //if ( pR == 0 ) cout<<" ("<< xR[0] <<") --> R : "<< IntEff <<"  pR = "<< pR <<" eff0 = "<< eff0 <<endl ;
        }
        if ( !skipL && xL[0] > 0. && xL[0] > step ) {
           xL[0] -=  step ;
           pL = BinomialErr( xL, par ) ;
           IntEff += (pL*step*(N_all+1) ) ;
           //if ( pL == 0 ) cout<<" ("<< xL[0] <<") <-- L : "<< IntEff <<"  pL = "<< pL <<endl;
        } else {
          //printf(" Int_eff = %.4f, pR = %.4f, pL = %.4f , xR=%.4f, xL=%.4f \n", IntEff, pR, pL, xR[0], xL[0] ) ;
          break ;
        }
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



