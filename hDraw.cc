#include "hDraw.h"
#include "MathTools.h"

hDraw::hDraw(){

  //Input  = new AnaInput( datacardfile );
  Input = AnaInput::Instance() ;

  Input->GetParameters("PlotType",      &plotType ) ;
  Input->GetParameters("Path",          &hfolder ) ;

  gSystem->mkdir( hfolder.c_str() );

  c1  = new TCanvas("c1","", 800, 600);
  c2  = new TCanvas("c2","", 800, 600);
  c3  = new TCanvas("c3","", 800, 600);

  //c1->SetLeftMargin(0.15);
  //c2->SetLeftMargin(0.15);
  //c3->SetLeftMargin(0.15);

  func1 = NULL ;
  StatBoxOn = true ;
}

hDraw::hDraw( string hfolder_ , string plotType_ ){

  hfolder  = hfolder_ ;
  plotType = plotType_ ;

  gSystem->mkdir( hfolder.c_str() );

  c1  = new TCanvas("c1","", 800, 600);
  c2  = new TCanvas("c2","", 800, 600);
  c3  = new TCanvas("c3","", 800, 600);

  func1 = NULL ;
  StatBoxOn = true ;

}

hDraw::~hDraw(){

  delete c1 ;
  delete c2 ;
  delete c3 ;
  //if ( Input != NULL ) delete Input ;
  cout<<" Draw ! "<<endl ;

}

void hDraw::Draw( TH1D* h1_, string plotName, string xTitle, string yTitle, string logY, float statY, int color, double scale_, TLegend* leg ) {

      //gStyle->SetOptStat("eoumi");
      //if ( !StatBoxOn ) gStyle->SetOptStat(kFALSE); 
      //if (  StatBoxOn ) gStyle->SetOptStat(kTRUE); 
      if ( h1_ == NULL ) return ;

      TH1D* h1 = (TH1D*)h1_->Clone() ;
      h1->Scale( scale_ ); 

      c1->Clear();
      c1->SetFillColor(10);
      c1->SetFillColor(10);
      c1->SetLogy(0);

      if ( strncasecmp( "logY", logY.c_str(), logY.size() ) ==0 && logY.size() > 0 ) c1->SetLogy() ;

      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );
      gStyle->SetStatTextColor( color );

      h1->GetXaxis()->SetTitle( xTitle.c_str() );
      h1->GetYaxis()->SetTitle( yTitle.c_str() );
      h1->GetYaxis()->SetTitleOffset(1.39);
      h1->SetLineColor( color ) ;
      h1_->SetLineColor( color ) ;

      c1->cd();
      h1->Draw() ;
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
         //if ( func1 != NULL ) func1 = NULL ;
      }

}

void hDraw::DrawAppend( TH1D* h1_, string plotName, float statY, int color, double scale_, TLegend* leg ) {

      if ( h1_ == NULL ) return ;

      TH1D* h1 = (TH1D*)h1_->Clone() ;
      h1->Scale( scale_ ); 

      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );

      h1->SetLineColor( color ) ;
      h1_->SetLineColor( color ) ;

      h1->DrawCopy("sames") ;
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
         //if ( func1 != NULL ) func1 = NULL ;
      }
}

void hDraw::Draw2D( TH2D* h2, string plotName, string xTitle, string yTitle, string logZ, int nColor, float titleFontSize, float statFontSize ) {

      if ( h2 == NULL ) return ;

      TCanvas* c4  = new TCanvas("c4","", 800, 600 );
      c4->SetFillColor(10);
      c4->SetFillColor(10);
      c4->SetLeftMargin(0.16);
      c4->SetBottomMargin(0.12);
      //c4->SetLogy(0);
      //if ( !StatBoxOn ) gStyle->SetOptStat(kFALSE); 
      //if (  StatBoxOn ) gStyle->SetOptStat(kTRUE); 

      if ( strncasecmp( "logZ", logZ.c_str(), logZ.size() ) ==0  && logZ.size() > 0 ) gPad->SetLogz(1) ;

      SetHistoAtt( h2 ) ;
      gStyle->SetPalette(1);
      gStyle->SetStatFontSize( statFontSize ) ;
      gStyle->SetTitleFontSize( titleFontSize ) ;
      gStyle->SetNumberContours( nColor );
      gStyle->SetStatX(0.9);

      h2->GetXaxis()->SetTitle( xTitle.c_str() );
      h2->GetYaxis()->SetTitle( yTitle.c_str() );
      h2->GetXaxis()->SetTitleOffset(1.5);
      h2->GetYaxis()->SetTitleOffset(1.4);

      c4->cd() ;
      h2->Draw("COLZ") ;
      c4->Update();

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c4->Print( plotname1 );
      }
      delete c4 ;
}

void hDraw::CreateNxM( string plotName , int N, int M ) {

      c2->Clear();
      c2->SetFillColor(10);
      c2->SetFillColor(10);
      c2->Divide(N, M) ;

      gStyle->SetOptStat("eroumi");

      plotname2 = hfolder + plotName + "."+plotType ;
}

void hDraw::DrawNxM( int id, TH1D* h1, string xTitle, string yTitle, string logY, int color, bool close  ) {

      c2->cd( id );

      if ( h1 == NULL ) return ;

      gPad->SetLogy(0) ;
      if ( strncasecmp( "logY", logY.c_str(), logY.size() ) ==0  && logY.size() > 0 ) gPad->SetLogy(1) ;

      //SetHistoAtt( h1 ) ;
      gStyle->SetStatTextColor( color );
      h1->SetLineColor( color ) ;

      h1->GetXaxis()->SetTitle( xTitle.c_str() );
      h1->GetYaxis()->SetTitle( yTitle.c_str() );

      h1->Draw() ;
      c2->Update();

      if ( close ) {
         c2->Print( plotname2 );
      }
}

void hDraw::DrawNxM( int id, TH2D* h2, string xTitle, string yTitle, string logZ, int nColor, float titleFontSize, float statFontSize, bool close  ) {

      c2->cd( id );

      gPad->SetLogy(0) ;
      if ( strncasecmp( "logZ", logZ.c_str(), logZ.size() ) ==0  && logZ.size() > 0 ) gPad->SetLogz(1) ;

      SetHistoAtt( h2 ) ;
      gStyle->SetStatFontSize( statFontSize ) ;
      gStyle->SetTitleFontSize( titleFontSize ) ;
      gStyle->SetNumberContours( nColor );

      h2->GetXaxis()->SetTitle( xTitle.c_str() );
      h2->GetYaxis()->SetTitle( yTitle.c_str() );

      h2->Draw("COLZ") ;
      c2->Update();

      if ( close ) {
         c2->Print( plotname2 );
      }
}

void hDraw::FitNDraw( TH1D* h1, TF1* ffn, string plotName, string xTitle, string yTitle, string logY, float statY, int color, TLegend* leg ) {

      // Plot the histogram
      c1->Clear();
      c1->SetFillColor(10);
      c1->SetFillColor(10);
      c1->SetLogy(0);

      //gStyle->SetOptStat("emio");
      if ( strncasecmp( "logY", logY.c_str(), logY.size() ) ==0 && logY.size() > 0 ) c1->SetLogy() ;

      gStyle->SetOptFit(0011);
      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );
      gStyle->SetStatFontSize( 0.015 ) ;

      if ( xTitle.size() > 0 ) h1->GetXaxis()->SetTitle( xTitle.c_str() );
      if ( yTitle.size() > 0 ) h1->GetYaxis()->SetTitle( yTitle.c_str() );
      h1->SetLineColor( color ) ;

      c1->cd();
      h1->Draw() ;
      c1->Update();

      // Define the fitting function and fit
      h1->Fit( ffn, "R", "sames" );
      //func1->Draw("same") ;
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
      }
}

void hDraw::FitNDraw( TH1D* h1, string plotName, string xTitle, string yTitle, string logY, float statY, int color, TLegend* leg ) {

      // Plot the histogram
      c1->Clear();
      c1->SetFillColor(10);
      c1->SetFillColor(10);
      c1->SetLogy(0);

      //gStyle->SetOptStat("emio");
      if ( strncasecmp( "logY", logY.c_str(), logY.size() ) ==0 && logY.size() > 0 ) c1->SetLogy() ;

      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );

      if ( xTitle.size() > 0 ) h1->GetXaxis()->SetTitle( xTitle.c_str() );
      if ( yTitle.size() > 0 ) h1->GetYaxis()->SetTitle( yTitle.c_str() );
      h1->SetLineColor( color ) ;

      c1->cd();
      h1->Draw() ;
      c1->Update();

      // Define the fitting function and fit
      h1->Fit( func1, "R", "sames" );
      //func1->Draw("same") ;
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
      }
}

void hDraw::FitNDrawAppend( TH1D* h1, string plotName, float statY, int color, TLegend* leg ) {

      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );

      h1->SetLineColor( color ) ;

      c1->cd();
      h1->DrawCopy("sames") ;
      c1->Update();

      h1->Fit( func1, "R", "sames" );
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
         if ( func1 != NULL ) func1 = NULL ;
      }
}

void hDraw::FitNDrawAppend( TH1D* h1, TF1* ffn, string plotName, float statY, int color, TLegend* leg ) {

      gStyle->SetOptFit(0011);
      gStyle->SetStatY( statY  );
      gStyle->SetStatTextColor( color );
      gStyle->SetStatFontSize( 0.012 ) ;

      h1->SetLineColor( color ) ;

      c1->cd();
      h1->DrawCopy("sames") ;
      c1->Update();

      h1->Fit( ffn, "R", "sames" );
      c1->Update();

      if ( leg != NULL ) leg->Draw("sames") ;

      if ( plotName.size() > 0 ) {
         TString plotname1 = hfolder + plotName + "."+plotType ;
         c1->Print( plotname1 );
         if ( func1 != NULL ) func1 = NULL ;
      }
}

void hDraw::SetFitParameter( string fitFunc_, double fitMin_, double fitMax_ , int nFitPara_,  double* initVals, int color ) {

   fitMin = fitMin_ ;
   fitMax = fitMax_ ;
   nFitPara = nFitPara_ ;

   gStyle->SetOptFit(111);

   if ( strncasecmp( "Gaus", fitFunc_.c_str(), fitFunc_.size() ) == 0  )  {
      func1 = new TF1("func1", &MathTools::fitGS, fitMin, fitMax, nFitPara );  
      func1->SetParameter( 0, initVals[0] );
      func1->SetParameter( 1, initVals[1] );
      func1->SetParameter( 2, initVals[2] );
      func1->SetLineColor( color );
   }
   if ( strncasecmp( "Exp", fitFunc_.c_str(), fitFunc_.size() ) == 0  )  {
      func1 = new TF1("func1", &MathTools::fExp , fitMin, fitMax, nFitPara );
      func1->SetParameter( 0, initVals[0] );
      func1->SetParameter( 1, initVals[1] );
      func1->SetLineColor( color );
   }

}

void hDraw::SetFitParameter( string fitFunc_, TH1D* h1, double fitMin_, double fitMax_ , int nFitPara_, int color ) {

   if ( fitMin_ != fitMax_ ) fitMin = fitMin_ ;
   if ( fitMin_ != fitMax_ ) fitMax = fitMax_ ;
   nFitPara = nFitPara_ ;

   gStyle->SetOptFit(111);

   if ( strncasecmp( "Gaus", fitFunc_.c_str(), fitFunc_.size() ) == 0  )  {
      double maxv = h1->GetMaximum() ;
      double mean = h1->GetMean() ;
      double rms  = h1->GetRMS() ;
      if ( fitMin_ == fitMax_ ) fitMin = mean - (2.*rms) ;
      if ( fitMin_ == fitMax_ ) fitMax = mean + (2.*rms) ;

      func1 = new TF1("func1", &MathTools::fitGS, fitMin, fitMax, nFitPara );  
      func1->SetParameter( 0, maxv );
      func1->SetParameter( 1, mean );
      func1->SetParameter( 2, rms  );
      func1->SetLineColor( color );
   }

}

// Drawing Efficiency Plot from two histograms    
void hDraw::EffPlot( TH1D* hCut, TH1D* hAll, string xlable, double minBinContent, int beginBin, int endBin, string graphName, TPaveText* ttex ) {

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
   double bW = hCut->GetBinWidth(1) ;
   cout<<" bin width = " << bW <<" end bin = "<< endBin << endl ;

   // Accumulate bin contain
   for ( int i= beginBin ; i<= endBin; i++ ) {
       double bc_ = hCut->GetBinContent(i) ;
       double ba_ = hAll->GetBinContent(i) ;
       double x_  = hAll->GetBinCenter(i) ;
       //printf("     (%d)_%.2f =  %.2f/%.2f \n", i, x_, bc_, ba_ ) ;
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
	     // sc's method to calculate error
	     pair<double,double> errs = MathTools::EffError( ba, bc ) ;
	     errH.push_back( errs.first ) ;
	     errL.push_back( errs.second ) ;
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
   int nbins = (int) xV.size() ;
   TH1D* hTop      = new TH1D("hTop", " ",  nbins,  0, nbins );
   TH1D* hBot      = new TH1D("hBot", " ",  nbins,  0, nbins );
   for ( int i=0; i< nbins ; i++ ) {
       hTop->SetBinContent( i+1 , bcV[i] ) ;
       hBot->SetBinContent( i+1 , baV[i] ) ;
   }
   TGraphAsymmErrors* gRatio = new TGraphAsymmErrors();
   gRatio->BayesDivide( hTop, hBot );

   const int sz = (int) xV.size() ;
   Double_t eYL[sz], eYH[sz], fX[sz], eX[sz];
   Double_t* fY = gRatio->GetY() ;
   Double_t yA[sz], eY_L[sz], eY_H[sz] ;  // for SC's method
   for ( Int_t i=0 ; i< sz ; i++) {
       fX[i]  = xV[i] ;
       eX[i]  = xW[i] ;
       eYL[i] = gRatio->GetErrorYlow(i) ;
       eYH[i] = gRatio->GetErrorYhigh(i) ;
       // for SC's method
       yA[i]   = bcV[i] / baV[i] ;
       eY_L[i] = errL[i] ;
       eY_H[i] = errH[i] ;
   }

   double xMin =  fX[0]    - eX[0]   ;
   double xMax =  fX[sz-1] + eX[sz-1] ;

   TGraphAsymmErrors* gr  = new TGraphAsymmErrors( sz, fX, fY, eX, eX, eYL, eYH );
   TGraphAsymmErrors* gr1 = new TGraphAsymmErrors( sz, fX, yA, eX, eX, eY_L, eY_H ); // SC's result !

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

   gr->SetMaximum( 1.1 );
   gr->SetMinimum( 0.0 );
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(1);
   gr->SetLineWidth(2);
   gStyle->SetTitleFontSize(0.04) ;
   gr->SetTitle(" CMS Preliminary #sqrt{s} = 8 TeV ") ;
   gr->GetXaxis()->SetTitleOffset(1.34);
   gr->GetYaxis()->SetTitleOffset(1.39);
   gr->GetXaxis()->SetTitleFont(42);
   gr->GetYaxis()->SetTitleFont(42);
   gr->GetXaxis()->SetTitleSize(0.04);
   gr->GetYaxis()->SetTitleSize(0.04);
   gr->GetXaxis()->SetTitle( xlable.c_str() ) ;
   gr->GetYaxis()->SetTitle(" Efficiency ") ;
   gr->GetXaxis()->SetLimits( xMin, xMax );
   gr->Draw("AP");
   c0->Update();
   //if ( ttex != NULL ) {
   //   ttex->Draw("same") ;
   //   c0->Update();
   //} 
   TString plotname = hfolder + graphName + "Asym."+plotType ;
   c0->Print( plotname );
   
   c0->cd();
   gr1->SetTitle(" CMS Preliminary #sqrt{s} = 8 TeV ") ;
   gr1->SetMaximum( 1.1 );
   gr1->SetMinimum( 0.0 );
   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(22);
   gr1->SetMarkerSize(1);
   gr1->SetLineWidth(2);
   gr1->GetXaxis()->SetTitleOffset(1.34);
   gr1->GetYaxis()->SetTitleOffset(1.39);
   gr1->GetXaxis()->SetTitle( xlable.c_str() ) ;
   gr1->GetYaxis()->SetTitle(" Efficiency ") ;
   gr1->GetXaxis()->SetLimits( xMin, xMax );
   gr1->Draw("AP");
   c0->Update();
   if ( ttex != NULL ) {
      ttex->Draw("same") ;
      c0->Update();
   } 

   plotname = hfolder + graphName + "Asym1."+plotType ;
   c0->Print( plotname );
   
   delete hTop ;
   delete hBot ;
   delete c0 ;
   delete gr ;
   delete gr1 ;
}


void hDraw::EffProbPlot( double N_all, string graphName ){

  cout<<" N_All = "<< N_all <<endl ;
  TF1* fn1 = new TF1("fn1", MathTools::BinomialErr, 0., 1., 3);

  fn1->SetParameter( 0, 1. ) ;

   TCanvas* c0 = new TCanvas("c0","", 800, 600);
   c0->SetFillColor(10);
   c0->SetFillColor(10);
   gPad->SetGridx();

   for ( int i = 0 ; i <= N_all; i++ ) {

      if ( N_all >= 50 && i%5 != 0 ) continue ;
      c0->cd();
      fn1->SetParameter( 1, N_all ) ;
      fn1->SetParameter( 2, i ) ;
      if ( i == 0 ) fn1->Draw() ;
      fn1->DrawCopy("sames") ;
      c0->Update() ;
      //double intP = fn1->Integral( 0, 1 ) ; 
      //cout<<" Int = "<< intP <<endl ; 
   }
   TString plotname = hfolder + graphName + "."+plotType ;
   c0->Print( plotname );

   delete fn1 ;
   delete c0 ;
}

void hDraw::SetHistoAtt( string axis, float labelSize, float tickLength, float titleSize, float titleOffset ){

     if ( axis == "x" || axis == "X" ) {
        labelSize_x   = labelSize ;
        tickLength_x  = tickLength ;
        titleSize_x   = titleSize ;
        titleOffset_x = titleOffset ;
        if ( labelSize   == (float)0 ) labelSize_x   = 0.05 ;
        if ( tickLength  == (float)0 ) tickLength_x  = 0.03 ;
        if ( titleSize   == (float)0 ) titleSize_x   = 0.04 ;
        if ( titleOffset == (float)0 ) titleOffset_x = 1.0 ;
     }
     if ( axis == "y" || axis == "Y" ) {
        labelSize_y   = labelSize ;
        tickLength_y  = tickLength ;
        titleSize_y   = titleSize ;
        titleOffset_y = titleOffset ;
        if ( labelSize   == (float)0 ) labelSize_y   = 0.05 ;
        if ( tickLength  == (float)0 ) tickLength_y  = 0.03 ;
        if ( titleSize   == (float)0 ) titleSize_y   = 0.04 ;
        if ( titleOffset == (float)0 ) titleOffset_y = 1.0 ;
     }
}

void hDraw::SetHistoAtt( TH1D* h1 ){

        h1->GetXaxis()->SetLabelSize( labelSize_x );
        h1->GetXaxis()->SetTickLength( tickLength_x );
        h1->GetXaxis()->SetTitleSize( titleSize_x );
        h1->GetXaxis()->SetTitleOffset( titleOffset_x );
        //h1->GetYaxis()->SetTitleFont(42);

        h1->GetYaxis()->SetLabelSize( labelSize_y );
        h1->GetYaxis()->SetTickLength( tickLength_y );
        h1->GetYaxis()->SetTitleSize( titleSize_y );
        h1->GetYaxis()->SetTitleOffset( titleOffset_y );
}

void hDraw::SetHistoAtt( TH2D* h2 ){

        h2->GetXaxis()->SetLabelSize( labelSize_x );
        h2->GetXaxis()->SetTickLength( tickLength_x );
        h2->GetXaxis()->SetTitleSize( titleSize_x );
        h2->GetXaxis()->SetTitleOffset( titleOffset_x );
        //h1->GetYaxis()->SetTitleFont(42);

        h2->GetYaxis()->SetLabelSize( labelSize_y );
        h2->GetYaxis()->SetTickLength( tickLength_y );
        h2->GetYaxis()->SetTitleSize( titleSize_y );
        h2->GetYaxis()->SetTitleOffset( titleOffset_y );
}

void hDraw::SetPlotStyle( bool StatBoxOn_, float tMargin, float bMargin, float lMargin, float rMargin ) {

     StatBoxOn = StatBoxOn_ ;
     gStyle->SetPadTopMargin( tMargin );
     gStyle->SetPadBottomMargin( bMargin );
     gStyle->SetPadLeftMargin( lMargin );
     gStyle->SetPadRightMargin( rMargin );

}


