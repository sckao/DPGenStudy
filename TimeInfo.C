#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the fitting function
void TimeInfo() {

    gROOT->LoadMacro("CMS_lumi.C");

    TString plotname0 = "Final2012/seedTime_Chi2.png" ;
    TString plotname0a = "Final2012/seedTime_Chi2_mc.png" ;
    TString plotname0b = "Final2012/InTime_Chi2_.png" ;
    TString plotname0c = "Final2012/OutTime_Chi2.png" ;
    TString plotname0c = "Final2012/OutTime_Chi2.png" ;
    TString plotname0d = "Final2012/ProbChi2.png" ;

    TString plotname1 = "Final2012/dt1_dt2_late.png" ;
    TString plotname2 = "Final2012/ECALTime.png" ;
    //TString plotname3 = "Final2012/SeedTime_data-mc.png" ;
    TString plotname3 = "Final2012/SeedTime_data-mc_Calib.png" ;
    TString plotname4 = "Final2012/Time_GMSB_Data.png" ;

    string hName0 = "seedTime_Chi2" ;
    string hName1 = "dt1_dt2_late" ;
    string hName2 = "obsTime1" ;
    string hName3 = "aveObsTime1" ;
    string hName4 = "isoTime" ;
    string hName5 = "isoTime1" ;
    
    //TFile *file2  = TFile::Open("MCQCD/test_gjets.root");
    TFile *file2  = TFile::Open("MCQCD/test_gjets_lowPt_norm.root");
    //TFile *file0  = TFile::Open("TCuts_RunBCD_new/testRun_0J.root");
    TFile *file0  = TFile::Open("TCuts_RunBCD_new/testRun_2J.root");
    TFile *file1  = TFile::Open("TCuts_GMSB_L180/GMSB2J_180_5980.root");

    TH2D* t_chi2     = (TH2D *) file0->Get( hName0.c_str() )  ;
    TH2D* t_chi2_mc  = (TH2D *) file1->Get( hName0.c_str() )  ;
    TH2D* dt1_dt2 = (TH2D *) file1->Get( hName1.c_str() )  ;

    TH1D* seedT  = (TH1D *) file0->Get( hName2.c_str() )  ;
    TH1D* aveT   = (TH1D *) file0->Get( hName3.c_str() )  ;
    TH1D* mc_T0  = (TH1D *) file1->Get( hName2.c_str() )  ;

    TH1D* data_T  = (TH1D *) file0->Get( hName4.c_str() )  ;
    //TH1D* mc_T    = (TH1D *) file2->Get( hName4.c_str() )  ;
    TH1D* mc_T    = (TH1D *) file2->Get( hName5.c_str() )  ;

   

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
    gStyle->SetLabelSize(0.05, "XYZ");

    TCanvas* c0 = new TCanvas("c0","", 800, 600);
    c0->SetFillColor(10);
    c0->SetFillColor(10);
    
    c0->SetTopMargin(0.08);
    c0->SetBottomMargin(0.13);
    c0->SetLeftMargin(0.16);
    c0->SetRightMargin(0.1);
    c0->SetLogz() ;

    //gPad->SetGridx();
    //gPad->SetGridy();
    c0->cd();

    // (0) Plot - seedTime vs Chi2
    //t_chi2->SetTitleFont(42);
    //t_chi2->SetTitle( hTitle.c_str() ) ;
    t_chi2->GetXaxis()->SetTitleOffset(0.9);
    t_chi2->GetYaxis()->SetTitleOffset(1.25);
    t_chi2->GetXaxis()->SetTitleSize(0.06);
    t_chi2->GetYaxis()->SetTitleSize(0.06);

    t_chi2->GetXaxis()->SetTitle( "ECAL Time (ns)" ) ;
    t_chi2->GetYaxis()->SetTitle( " #chi^{2}" ) ;
 
    gStyle->SetNumberContours( 10 );
    t_chi2->Draw("COLZ");
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname0 );

    // (0) Plot - seedTime vs Chi2 (MC)
    t_chi2_mc->GetXaxis()->SetTitleOffset(0.9);
    t_chi2_mc->GetYaxis()->SetTitleOffset(1.25);
    t_chi2_mc->GetXaxis()->SetTitleSize(0.06);
    t_chi2_mc->GetYaxis()->SetTitleSize(0.06);

    t_chi2_mc->GetXaxis()->SetTitle( "ECAL Time (ns)" ) ;
    t_chi2_mc->GetYaxis()->SetTitle( " #chi^{2}" ) ;
 
    gStyle->SetNumberContours( 10 );
    t_chi2_mc->Draw("COLZ");
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname0a );

    // Chi2 distribution
    TH1D* t_chi2_n = t_chi2->ProjectionY("t_chi2_n",  1,  68 ) ;
    TH1D* t_chi2_c = t_chi2->ProjectionY("t_chi2_c", 69,  91 ) ;
    TH1D* t_chi2_p = t_chi2->ProjectionY("t_chi2_p", 92, 160 ) ;
    TH1D* t_chi2_mc_n = t_chi2_mc->ProjectionY("t_chi2_mc_n",  1,  68 ) ;
    TH1D* t_chi2_mc_c = t_chi2_mc->ProjectionY("t_chi2_mc_c", 69,  91 ) ;
    TH1D* t_chi2_mc_p = t_chi2_mc->ProjectionY("t_chi2_mc_p", 92, 160 ) ;
        
    c0->SetLogy() ;
    t_chi2_c->Scale( 10000./ (float)t_chi2_c->Integral() ) ;
    t_chi2_c->GetXaxis()->SetTitle( " #chi^{2} of ECAL Time" ) ;
    t_chi2_c->GetYaxis()->SetTitle( " A.U. " ) ;
    t_chi2_c->GetXaxis()->SetTitleOffset(0.9);
    t_chi2_c->GetYaxis()->SetTitleOffset(1.25);
    t_chi2_c->GetXaxis()->SetTitleSize(0.06);
    t_chi2_c->GetYaxis()->SetTitleSize(0.06);
    t_chi2_c->Draw();
    c0->Update();
    t_chi2_mc_c->Scale( 10000./ (float)t_chi2_mc_c->Integral() ) ;
    t_chi2_mc_c->SetLineColor(2);
    t_chi2_mc_c->Draw("sames");
    c0->Update();
    
    TLegend* leg0  = new TLegend(.55, .72, .88, .9 );
    leg0->Clear();
    leg0->SetHeader( " ECAL Time (|t| < 3 ns)" );
    leg0->AddEntry( t_chi2_c,    "Data",  "L");
    leg0->AddEntry( t_chi2_mc_c, "GMSB MC",  "L");
    leg0->Draw("SAME") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();
    c0->Print( plotname0b );

    t_chi2_p->Scale( 10000./ (float)t_chi2_p->Integral() ) ;
    t_chi2_p->GetXaxis()->SetTitle( " #chi^{2} of ECAL Time" ) ;
    t_chi2_p->GetYaxis()->SetTitle( " A.U. " ) ;
    t_chi2_p->GetXaxis()->SetTitleOffset(0.9);
    t_chi2_p->GetYaxis()->SetTitleOffset(1.25);
    t_chi2_p->GetXaxis()->SetTitleSize(0.06);
    t_chi2_p->GetYaxis()->SetTitleSize(0.06);
    t_chi2_p->SetLineColor(2);
    t_chi2_p->Draw();
    c0->Update();
    t_chi2_n->Scale( 10000./ (float)t_chi2_n->Integral() ) ;
    t_chi2_n->SetLineColor(4);
    t_chi2_n->Draw("sames");
    c0->Update();
    t_chi2_mc_p->Scale( 10000./ (float)t_chi2_mc_p->Integral() ) ;
    t_chi2_mc_p->SetLineColor(8);
    t_chi2_mc_p->Draw("sames");
    c0->Update();
    
    leg0->Clear();
    leg0->SetHeader( " ECAL Time ( |t| > 3 ns)" );
    leg0->AddEntry( t_chi2_p,    "Data (t > 3 ns)",  "L");
    leg0->AddEntry( t_chi2_n,    "Data (t < -3 ns)",  "L");
    leg0->AddEntry( t_chi2_mc_p, "GMSB MC (t > 3 ns)",  "L");
    leg0->Draw("SAME") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();
    c0->Print( plotname0c );

    // (1) Plot dt1_dt2_late
    dt1_dt2->GetXaxis()->SetTitleOffset(0.9);
    dt1_dt2->GetYaxis()->SetTitleOffset(1.25);
    dt1_dt2->GetXaxis()->SetTitleSize(0.06);
    dt1_dt2->GetYaxis()->SetTitleSize(0.06);
    dt1_dt2->GetXaxis()->SetTitle( " #Delta t1 (ns)" ) ;
    dt1_dt2->GetYaxis()->SetTitle( " #Delta t2 (ns)" ) ;
 
    gStyle->SetNumberContours( 10 );
    dt1_dt2->Draw("COLZ");
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname1 );

    // (2) Plot ECALTime - seed and ave time comparison
    c0->SetRightMargin(0.05);
    c0->SetLogy() ;
    seedT->SetLineColor(1);
    seedT->SetLineWidth(2);
    seedT->GetXaxis()->SetTitleOffset(0.9);
    seedT->GetYaxis()->SetTitleOffset(1.25);
    seedT->GetXaxis()->SetTitleSize(0.06);
    seedT->GetYaxis()->SetTitleSize(0.06);
    seedT->GetXaxis()->SetTitle( "ECAL Time (ns)" ) ;
    seedT->GetYaxis()->SetTitle( "Entries / 0.25 ns " ) ;
    //seedT->GetXaxis()->SetLimits( xMin2, xMax2 );

    seedT->Fit("gaus","N","", -3, 3) ;
    double m_seed   = gaus->GetParameter(1) ;
    double sig_seed = gaus->GetParameter(2) ;
    seedT->Draw();
  
    c0->Update();

    aveT->SetLineColor(2);
    aveT->SetLineWidth(2);
    aveT->Fit("gaus","N","", -3, 3) ;
    double m_ave   = gaus->GetParameter(1) ;
    double sig_ave = gaus->GetParameter(2) ;
    aveT->Draw("sames");
    c0->Update();

    // Legend
    TLegend* leg1  = new TLegend(.61, .72, .95, .9 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[30], RStr1[30] ;
    sprintf( RStr0,  "Seed (%.3f #pm %.3f)", m_seed, sig_seed ) ;
    sprintf( RStr1,  "Average (%.3f #pm %.3f)", m_ave, sig_ave ) ;

    leg1->AddEntry( seedT, RStr0,  "L");
    leg1->AddEntry( aveT, RStr1,  "L");
    leg1->Draw("SAME") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname2 );

    // (3) Data-MC comparison
    double fitMin(-1.5) , fitMax(1.2) ;
    c0->SetRightMargin(0.05);
    c0->SetLogy() ;
    data_T->SetLineColor(4);
    data_T->SetLineWidth(2);
    data_T->GetXaxis()->SetTitleOffset(0.9);
    data_T->GetYaxis()->SetTitleOffset(1.25);
    data_T->GetXaxis()->SetTitleSize(0.06);
    data_T->GetYaxis()->SetTitleSize(0.06);
    data_T->GetXaxis()->SetTitle( "ECAL Time (ns)" ) ;
    data_T->GetYaxis()->SetTitle( "Entries / 0.25 ns " ) ;
    data_T->SetAxisRange( -10., 10. );
    double nMC = data_T->Integral() ;
    data_T->Scale( 10000. / nMC ) ;

    //data_T->Fit("gaus","RN","", -1.5, 1) ;
    data_T->Fit("gaus","RN","", fitMin, fitMax) ;
    double m_data   = gaus->GetParameter(1) ;
    double sig_data = gaus->GetParameter(2) ;
    data_T->Draw();
    c0->Update();

    gaus->SetLineWidth(2) ;
    gaus->SetLineColor(4) ;
    gaus->SetRange(fitMin, fitMax ) ;
    gaus->DrawCopy("SAME") ;
    c0->Update();

    mc_T->SetLineColor(2);
    mc_T->SetLineWidth(2);
    mc_T->SetAxisRange( -10., 10. );
    double nData = mc_T->Integral() ;
    mc_T->Scale( 10000. / nData ) ;

    //mc_T->Fit("gaus","RN","", -1.5, 1) ;
    mc_T->Fit("gaus","RN","", fitMin, fitMax) ;
    double m_mc   = gaus->GetParameter(1) ;
    double sig_mc = gaus->GetParameter(2) ;
    mc_T->Draw("SAME");
    c0->Update();

    gaus->SetLineWidth(2) ;
    gaus->SetLineColor(2) ;
    gaus->SetRange( fitMin, fitMax ) ;
    gaus->DrawCopy("SAME") ;
    c0->Update();

    // Legend
    TLegend* leg1  = new TLegend(.63, .75, .95, .90 );
    leg1->Clear();
    leg1->SetTextSize(0.03) ;

    char RStr0[40], RStr1[40] ;
    sprintf( RStr0,  "MC (%.3f #pm %.3f)", m_mc, sig_mc ) ;
    sprintf( RStr1,  "Data (%.3f #pm %.3f)", m_data, sig_data ) ;

    leg1->AddEntry( mc_T, RStr0,  "L");
    leg1->AddEntry( data_T, RStr1,  "L");
    leg1->Draw("SAME") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname3 );

    // (4) Plot ECALTime - Data and GMSB time comparison
    c0->SetRightMargin(0.05);
    c0->SetLogy() ;
    seedT->SetLineColor(1);
    seedT->SetLineWidth(2);
    seedT->GetXaxis()->SetTitleOffset(0.9);
    seedT->GetYaxis()->SetTitleOffset(1.25);
    seedT->GetXaxis()->SetTitleSize(0.06);
    seedT->GetYaxis()->SetTitleSize(0.06);
    seedT->GetXaxis()->SetTitle( "ECAL Time (ns)" ) ;
    seedT->GetYaxis()->SetTitle( "Entries / 0.25 ns " ) ;
    //seedT->GetXaxis()->SetLimits( xMin2, xMax2 );
    seedT->Scale( 4886. / seedT->Integral() );
    seedT->Draw();
  
    c0->Update();

    mc_T0->SetLineColor(2);
    mc_T0->SetLineWidth(2);
    mc_T0->Draw("sames");
    c0->Update();

    // Legend
    TLegend* leg2  = new TLegend(.67, .75, .95, .9 );
    leg2->Clear();
    leg2->SetTextSize(0.03) ;

    leg2->AddEntry( seedT, "Data",  "L");
    leg2->AddEntry( mc_T0, "GMSB MC (c#tau 6m)",  "L");
    leg2->Draw("SAME") ;
    c0->Update();

    CMS_lumi( c0, 2, 11 ) ;
    c0->Update();

    c0->Print( plotname4 );

    delete c0 ;
}


