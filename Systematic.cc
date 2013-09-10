#include "Systematic.h"

Systematic::Systematic( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw( datacardfile ) ;

  //normV = Input->NormalizeComponents( datacardfile );

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 

  Input->GetParameters("TimeCalib",     &timeCalib ) ; 

  gSystem->mkdir( hfolder.c_str() );

  //Input->GetParameters("HFileName",     &hfName ) ; 
  //TString Path_fName = hfolder + hfName + ".root" ; 
  //theFile = new TFile( Path_fName, "RECREATE" );
  //theFile->cd() ;

  h_dataTime   = new TH1D("h_dataTime", " Photon Seed Time from data", 100,  -4.5, 5.5);
  h_dataTimeA  = new TH1D("h_dataTimeA"," Photon Ave. Cluster Time from data", 100,  -4.5, 5.5);
  h_dataMET    = new TH1D("h_dataMET",  " MET from data ", 50,  0, 500);

  h_mcTime     = new TH1D("h_mcTime",  " Photon Seed Time from mc", 100,  -4.5, 5.5);
  h_mcTimeC    = new TH1D("h_mcTimeC", " Photon Seed Time from mc after calibration", 100,  -4.5, 5.5);
  h_mcTimeA    = new TH1D("h_mcTimeA", " Photon Ave. Cluster Time from mc", 100,  -4.5, 5.5);
  h_mcMET      = new TH1D("h_mcMET",   " MET from mc ", 50,  0, 500);

  //theFile->cd() ;
}


Systematic::~Systematic(){

  //theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete Input ;
  delete h_draw ;
  cout<<" done ! "<<endl ;

}

// Produce Data and Background histogram for statistical test
void Systematic::RunData( string dataName, int nSample ) { 

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float metE ;
   int   nPhotons, nJets ;

   //TTree* tr = Input->TreeMap( dataName );
   string dataFileNames ;
   if ( dataName != "0" ) {
      dataFileNames = dataName ;
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   TTree* tr   = Input->GetTree( dataFileNames, "DPAnalysis" );

   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );

   // initialize selection
   select->Init( tr1 ) ;
   select->ResetCounter() ;

   int totalN = tr->GetEntries();
   cout<<" **** from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       if ( i % 10000 == 0 && i > 9999 ) printf(" ----- processed %8d Events \n", i ) ;
       tr->GetEntry( i );
       tr1->GetEntry( i );
        
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass = select->SignalSelection();
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       if ( !pass )  continue ;

       //cout<<" EVT# : "<< nEvt <<endl ;

       if ( selectJets.size() > 0 && selectJets.size() < 3 ) { 
          int k = selectPho[0].first ;
	  h_dataTime->Fill( seedTime[k] ) ;
	  h_dataMET->Fill( metE ) ;
          if ( timeChi2[k] < 5 ) {
             h_dataTimeA->Fill( aveTime[k] ) ;
          } 
          else if ( selectPho.size() > 1  ) {
             int m = selectPho[1].first ;
             if ( timeChi2[m] < 5 ) h_dataTimeA->Fill( aveTime[m] ) ;
          }
          nEvt++; 
          //if ( nSample > 0 && nEvt >= nSample) break ;
       }


   } // end of event looping

   //WriteDataHisto() ;
   //select->PrintCutFlow() ;

}  

void Systematic::RunMC( string mcName, int nSample, double weight ) { 

   //string mcTag = mcName.substr( 4, mcName.size() - 4 ) ;
   /*
   string mcTag = "gjet" ;
   printf("MC Tag = %s", mcTag.c_str() ) ;
   char hName1[20] , hName2[20], hName3[20] ;
   sprintf( hName1, "h_mcTime_%s",  mcTag.c_str() ) ;
   sprintf( hName2, "h_mcTimeA_%s", mcTag.c_str() ) ;
   sprintf( hName3, "h_mcMET_%s",   mcTag.c_str() ) ;

   // Reset the histogram
   h_mcTime->SetName( hName1 ) ;
   h_mcTimeA->SetName( hName2 ) ;
   h_mcMET->SetName( hName3 ) ;

   h_mcTime->Reset() ;
   h_mcTimeA->Reset() ;
   h_mcMET->Reset() ;
   */

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float metE ;
   int   nPhotons, nJets ;

   TTree* tr   = Input->GetTree( mcName, "DPAnalysis" );
   // clone the tree for event selection
   TChain* tr1   = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );

   // initialize selection
   select->Init( tr1 ) ;
   select->ResetCounter() ;

   int totalN = tr->GetEntries();
   cout<<" **** from  "<< mcName <<" total entries = "<< totalN <<" Process "<< nSample <<endl;
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       //if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       if ( nSample > 0 && i > ( nSample + beginEvent - 1 ) ) break;
       if ( i % 10000 == 0 && i > 9999 ) printf(" ----- processed %8d Events \n", i ) ;
       tr->GetEntry( i );
       tr1->GetEntry( i );
        
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass = select->SignalSelection();
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       if ( !pass ) continue ;

       if ( selectJets.size() > 0 ) { 
          int k = selectPho[0].first ;
          float tCorr = tRan->Gaus( seedTime[k] , timeCalib[1] ) - timeCalib[0] ;
	  h_mcTime->Fill( seedTime[k], weight ) ;
	  h_mcTimeC->Fill( tCorr, weight ) ;
	  h_mcMET->Fill( metE, weight ) ;
          if ( timeChi2[k] < 5 ) {
             h_mcTimeA->Fill( aveTime[k], weight ) ;
          } 
          else if ( selectPho.size() > 1  ) {
             int m = selectPho[1].first ;
             if ( timeChi2[m] < 5 ) h_mcTimeA->Fill( aveTime[m], weight ) ;
          }
       }

   } // end of event looping
  
   // Make sure RunData() first 
   //ShiftPeak( h_mcTime,  h_dataTime ) ;
   //ShiftPeak( h_mcTimeA, h_dataTimeA ) ;

   //WriteMcHisto() ;
   //select->PrintCutFlow() ;

}

void Systematic::McDataCompare() {


     // 1. Get the distribution from data and MC
     string dataFileNames ;
     Input->GetParameters( "TheData", &dataFileNames );
     vector<string> mcFileNames ;
     Input->GetParameters( "TheMC",   &mcFileNames );
     vector<double> xSec ;
     Input->GetParameters( "XSection", &xSec );
     double totalXsec = 0 ; 
     for ( size_t i=0; i< xSec.size(); i++ ) {
         totalXsec += xSec[i] ;
     }

     int nSample = 0 ;
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {  
         nSample = ProcessEvents * xSec[i] / totalXsec  ;
         
         RunMC( mcFileNames[i], nSample , 1. ) ;
     }
     RunData( dataFileNames, -1 ) ;

     TH1D* hData = (TH1D*) h_dataTime->Clone() ;
     TH1D* hMC   = (TH1D*) h_mcTime->Clone() ;
     TH1D* hMCC  = (TH1D*) h_mcTimeC->Clone() ;

     hData->Scale( 1. / hData->Integral() ) ; 
     hMC->Scale( 1. / hMC->Integral() ) ; 
     hMCC->Scale( 1. / hMCC->Integral() ) ; 

     ComparePlot( hData , hMC, "SeedTime_data-mc" ) ;   
     ComparePlot( hData , hMCC, "SeedTime_data-mc_Calib" ) ;   

}

void Systematic::ComparePlot( TH1D* hData, TH1D* hMC, string plotName ) {

     // 0. Set up Canvas for drawing
     TCanvas* c_a  = new TCanvas( "c_a","", 800, 600);
     c_a->SetFillColor(10);
     c_a->SetFillColor(10);
     //c_a->SetLogy();

     c_a->cd();
     gStyle->SetOptStat("");
     gStyle->SetOptFit(0011);
     gStyle->SetStatFontSize( 0.01 ) ;

     // 2. Fit and Draw the results
     TLegend* leg1  = new TLegend(.75, .3, .9, .5 ) ;
     leg1->Clear();
     TString legStr0 = "Data    " ;
     TString legStr1 = "GJets MC" ;
     leg1->SetTextSize(0.030) ;

     leg1->AddEntry( hData,  legStr0,  "L");
     leg1->AddEntry( hMC,    legStr1,  "L");

     TF1* ffn2 = new TF1("ffn2", &hDraw::fitGS, -1.5, 1.5, 3 );
     ffn2->SetParameter( 0, hMC->GetBinContent( hMC->GetMaximumBin() ) );
     ffn2->SetParameter( 1,  0.  );
     ffn2->SetParameter( 2,  0.5 );
     ffn2->SetLineColor( 4 );
     //h_draw->FitNDrawAppend( hMC, ffn2, "SeedTime_data-mc", 0.7, 4, leg1 ) ;
     gStyle->SetStatY( 0.70  );
     gStyle->SetStatTextColor(4);

     double yMax = 1.2*hMC->GetBinContent( hMC->GetMaximumBin() ) ;
     hMC->SetMaximum( yMax ) ;
     hMC->SetTitle(" Ecal Time from Seed Crystal ") ;

     hMC->SetLineColor(4) ;
     hMC->SetLineWidth(2) ;
     hMC->Draw() ;
     c_a->Update() ;
     hMC->Fit( "ffn2", "R", "sames" );
     c_a->Update();

     TF1* ffn1 = new TF1("ffn1", &hDraw::fitGS, -1.5, 1.5, 3 );
     ffn1->SetParameter( 0,  hData->GetBinContent(hData->GetMaximumBin()) );
     ffn1->SetParameter( 1,  0.  );
     ffn1->SetParameter( 2,  0.5 );
     ffn1->SetLineColor( 2 );
     //h_draw->FitNDraw( hData, ffn1, "", " Ecal Time (ns) ", "", "logY", 0.95, 2 ) ;
     gStyle->SetStatY( 0.90  );
     gStyle->SetStatTextColor(2);
     hData->SetLineColor(2) ;
     hData->SetLineWidth(2) ;
     hData->DrawCopy("SAME") ;
     c_a->Update() ;
     hData->Fit( "ffn1", "R", "sames" );
     c_a->Update();

     leg1->Draw("sames") ;
     c_a->Update();


     TString plotname_a = hfolder + plotName + "." + plotType ;
     c_a->Print( plotname_a );

     delete ffn1 ;
     delete ffn2 ;
     delete leg1 ;
     delete c_a ;

}

// Shift peak of h1 to the position of the peak of h2
void Systematic::ShiftPeak( TH1D* h1 , TH1D* h2 ) {

     // get the bin number of h2 peak
     int b2 = h2->GetMaximumBin() ;
     int nBin = h2->GetNbinsX() ; 

     // copy original h1 information  
     int b1 = h1->GetMaximumBin() ;
     TH1D* h1tmp = (TH1D*) h1->Clone() ;
     h1->Reset() ;
     
     // Refill h1
     int shift = b2 - b1 ;
     double binV = 0 ;
     double bin0V = 0 ;
     for ( int i=1; i<= nBin ; i++ ) {
         if ( i-shift > nBin ) binV = 0 ; 
         if ( i-shift < 1) { 
            bin0V += h1tmp->GetBinContent(i) ;
            continue ;
         }
         binV = h1tmp->GetBinContent( i - shift )  ;
         h1->SetBinContent( i, binV ) ;
     } 
     h1->SetBinContent( 0 , bin0V ) ;

} 

void Systematic::WriteDataHisto() { 

     h_dataTime->Write() ; 
     h_dataTimeA->Write() ; 
     h_dataMET->Write() ;
}

void Systematic::WriteMcHisto() { 

     h_mcTime->Write() ; 
     h_mcTimeC->Write() ; 
     h_mcTimeA->Write() ; 
     h_mcMET->Write() ;
}
