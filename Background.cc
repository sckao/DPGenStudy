#include "Background.h"

Background::Background( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  h_draw = new hDraw( datacardfile ) ; 

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("IsData",        &isData ) ; 

  OpenHistograms() ;
}

Background::~Background() {

        delete Input ;
        delete h_draw ;
        //hFile->Close() ;
        cout<<" exit histogram "<<endl ;
        /*
        delete obsTime     ;
        delete aveObsTime  ;
        delete aveObsTime1 ;
        delete aveObsTime2 ;

        delete TimeLT3Jets    ;
        delete TimeGE3Jets    ;
        delete TimeLowMET     ;
        delete TimeBigMET     ;
         */
}

void Background::OpenHistograms() {

     string hfName1 = hfolder ;
     hfName1 += "TimeHisto_EB_B.root" ;
     string hfName2 = hfolder ;
     hfName2 += "TimeHisto_PhoHad_B.root" ;


     hFile1 = (TFile*) TFile::Open( hfName1.c_str() , "READ" );
     hFile2 = (TFile*) TFile::Open( hfName2.c_str() , "READ" );
     //hFile->cd() ;
     cout<<" file opened ! "<<endl ;

     TimeLT3Jets1 = (TH1D*) hFile1->Get("TimeLT3Jets")   ;
     TimeLT3Jets2 = (TH1D*) hFile2->Get("TimeLT3Jets")   ;

     cout<<" link all histograms  "<<endl ;
}

void Background::KSTest( TH1D* h1, TH1D* h2, int minBin, int maxBin, double hminX, double binWidth ) {

     int nBin = maxBin - minBin + 1 ;
     double minX = hminX + (minBin*binWidth) ;
     double maxX = minX + (binWidth*nBin) ;
     TH1D* h1t = new TH1D("h1t", "KS Test 1" , nBin,  minX, maxX );
     TH1D* h2t = new TH1D("h2t", "KS Test 2" , nBin,  minX, maxX );
     for ( int i = 0 ; i < nBin ; i++) {
         h1t->SetBinContent( i+1 , h1->GetBinContent( minBin + i  ) ) ;
         h2t->SetBinContent( i+1 , h2->GetBinContent( minBin + i  ) ) ;
     }
     //h2t->Scale( h1t->Integral() / h2t->Integral() ) ;

     double ksVal = h1t->KolmogorovTest( h2t ) ;     
     //TLegend* leg3  = new TLegend(.5, .7, .77, .9 );
     //leg3->AddEntry( h1t, " 2012B ", "L" ) ;
     //leg3->AddEntry( h2t, " 2012C ", "L" ) ;

     h_draw->Draw(       h1t, "", "Ecal Time (ns)", "", "logY", 0.95, 2  ) ;
     h_draw->DrawAppend( h2t, "KsTest", 0.7, 4 ) ;

     printf(" KS Val : %f ", ksVal ) ;

}

void Background::SpikeShape() {
 
     KSTest( TimeLT3Jets1, TimeLT3Jets2 , 40, 75, -14.5, 0.25  ) ;

}
