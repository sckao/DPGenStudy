#include "Output.h"

Output::Output( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  normV = Input->NormalizeComponents( datacardfile );

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("TimeCalib",     &timeCalib) ;

  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  h_dataTime   = new TH1D("h_dataTime",  "Photon Seed Time from data", 80,  -4.5, 15.5);
  h_dataTimeA  = new TH1D("h_dataTimeA", "Photon Ave. Cluster Time from data", 80,  -4.5, 15.5);
  h_MET        = new TH1D("h_MET",       " MET  ", 50,  30, 530);

  h_bgTime     = new TH1D("h_bgTime",  "Photon Seed Time of background ", 80,  -4.5, 15.5);
  h_bgTimeA    = new TH1D("h_bgTimeA", "Photon Ave. Cluster Time of background ", 80,  -4.5, 15.5);
  h_bgMET      = new TH1D("h_bgMET",   "MET of background sample  ", 50,  30, 530);

  h_sgTime     = new TH1D("h_sgTime",  "Photon Seed Time of signal ", 80,  -4.5, 15.5);
  h_sgTimeA    = new TH1D("h_sgTimeA", "Photon Ave. Cluster Time of signal ", 80,  -4.5, 15.5);
  h_sgMET      = new TH1D("h_sgMET",   "MET from signal MC ", 50,  30, 530);

  h_NJets      = new TH1D("h_NJets",   "N of Jets from Data", 10,  0, 10);
  h_sgNJets    = new TH1D("h_sgNJets", "N of Jets from Signal MC", 10,  0, 10);

  theFile->cd() ;
}

Output::~Output(){

  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete Input ;
  cout<<" done ! "<<endl ;
}

// Produce Data and Background histogram for statistical test
void Output::RunData( string dataName ) { 

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float metE ;
   int   nPhotons, nJets ;

   TTree* tr = Input->TreeMap( dataName );
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
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
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

       nEvt++; 
       //cout<<" EVT# : "<< nEvt <<endl ;

       // Signal Region
       if ( selectJets.size() > 1 ) { 
          int k = selectPho[0].first ;
	  h_dataTime->Fill( seedTime[k] ) ;
	  h_MET->Fill( metE ) ;
          if ( timeChi2[k] < 5 ) {
             h_dataTimeA->Fill( aveTime[k] ) ;
          } 
          else if ( selectPho.size() > 1  ) {
             int m = selectPho[1].first ;
             if ( timeChi2[m] < 5 ) h_dataTimeA->Fill( aveTime[m] ) ;
          }
       }
       // Background Region
       if ( selectJets.size() > 0 && selectJets.size() < 2 ) { 
          int k = selectPho[0].first ;
	  h_bgTime->Fill( seedTime[k] ) ;
	  h_bgMET->Fill( metE ) ;
          if ( timeChi2[k] < 5 ) {
             h_bgTimeA->Fill( aveTime[k] ) ;
          } 
          else if ( selectPho.size() > 1  ) {
             int m = selectPho[1].first ;
             if ( timeChi2[m] < 5 ) h_bgTimeA->Fill( aveTime[m] ) ;
          }
       }
       h_NJets->Fill( (int) selectJets.size() ) ;

   } // end of event looping

   /*`
   pair<int, int> tRbin[3] = { make_pair(1,9), make_pair(9,1),  make_pair(27,54) };  ;
   rh_dataTime    = RebinHistogram( h_dataTime,   "rh_dataTime", tRbin ) ;
   rh_dataTimeA   = RebinHistogram( h_dataTimeA,  "rh_dataTimeA", tRbin ) ;
   rh_MET         = RebinHistogram( h_MET,        "rh_MET",   1 ) ;
   rh_bgTime      = RebinHistogram( h_bgTime,     "rh_bgTime", tRbin ) ;
   rh_bgTimeA     = RebinHistogram( h_bgTimeA,    "rh_bgTimeA", tRbin ) ;
   rh_bgMET       = RebinHistogram( h_bgMET,      "rh_bgMET",   1 ) ;
   rh_NJets       = RebinHistogram( h_NJets,      "rh_NJets",   1 ) ;
   */ 
   rh_dataTime    = RebinHistogram( h_dataTime,   "rh_dataTime",  -0.2, 1.5 ) ;
   rh_dataTimeA   = RebinHistogram( h_dataTimeA,  "rh_dataTimeA", -0.2, 1.5 ) ;
   //rh_MET         = RebinHistogram( h_MET,        "rh_MET",   1 ) ;

   rh_bgTime      = RebinHistogram( h_bgTime,     "rh_bgTime",  -0.2, 1.5 ) ;
   rh_bgTimeA     = RebinHistogram( h_bgTimeA,    "rh_bgTimeA", -0.2, 1.5 ) ;
   //rh_bgMET       = RebinHistogram( h_bgMET,      "rh_bgMET",   1 ) ;
   //rh_NJets       = RebinHistogram( h_NJets,      "rh_NJets",   1 ) ;

   WriteDataHisto() ;
   cout<<" ======== CutFlow for Data ======== "<<endl ;
   select->PrintCutFlow() ;

}  

void Output::RunMC( string mcName, double weight ) { 

   string mcTag = mcName.substr( 8, mcName.size() - 8 ) ;
   char hName1[32] , hName2[32], hName3[32], hName4[32]   ;
   sprintf( hName1, "h_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( hName2, "h_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( hName3, "h_sgMET_%s",   mcTag.c_str() ) ;
   sprintf( hName4, "h_sgNJets_%s", mcTag.c_str() ) ;

   // Reset the histogram
   h_sgTime->SetName( hName1 ) ;
   h_sgTimeA->SetName( hName2 ) ;
   h_sgMET->SetName( hName3 ) ;
   h_sgNJets->SetName( hName4 ) ;

   h_sgTime->Reset() ;
   h_sgTimeA->Reset() ;
   h_sgMET->Reset() ;
   h_sgNJets->Reset() ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float metE ;
   int   nPhotons, nJets ;

   //TTree* tr   = Input->TreeMap( mcName );
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
   cout<<" **** from  "<< mcName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   // Set up gaussian smearing for timing correction
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
        
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass = select->MCSignalSelection();
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       if ( !pass ) continue ;

       nEvt++; 
       //cout<<" EVT# : "<< nEvt <<endl ;

       if ( selectJets.size() > 2 ) { 
          int k = selectPho[0].first ;
          // timing correction : central shift = 0.1211 ,  sigma = 0.4
          float tCorr = ( timeCalib[1] > 0.001 ) ? tRan->Gaus(seedTime[k], timeCalib[1]) - timeCalib[0] : seedTime[k] - timeCalib[0] ;
          //float tCorr = seedTime[k] - 0.1211 ;
	  h_sgTime->Fill( tCorr, weight ) ;
	  h_sgMET->Fill( metE, weight ) ;
          if ( timeChi2[k] < 5 ) {
             h_sgTimeA->Fill( aveTime[k], weight ) ;
          } 
          else if ( selectPho.size() > 1  ) {
             int m = selectPho[1].first ;
             if ( timeChi2[m] < 5 ) h_sgTimeA->Fill( aveTime[m], weight ) ;
          }
       }
       h_sgNJets->Fill( (int) selectJets.size(), weight ) ;

   } // end of event looping
  
   // Make sure RunData() first 
   //ShiftPeak( h_sgTime,  h_dataTime ) ;
   //ShiftPeak( h_sgTimeA, h_dataTimeA ) ;

   char rhName1[32] , rhName2[32], rhName3[32], rhName4[32]   ;
   sprintf( rhName1, "rh_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( rhName2, "rh_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( rhName3, "rh_sgMET_%s",   mcTag.c_str() ) ;
   sprintf( rhName4, "rh_sgNJets_%s", mcTag.c_str() ) ;

   /*
   pair<int, int> tRbin[3] = { make_pair(1,9), make_pair(9,1),  make_pair(27,54) };  ;
   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, tRbin  ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, tRbin ) ;
   rh_sgMET     = RebinHistogram( h_sgMET,    rhName3, 1 ) ;
   rh_sgNJets   = RebinHistogram( h_sgNJets,  rhName4, 1 ) ;
   */
   /*
   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, 1 ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, 1 ) ;
   rh_sgMET     = RebinHistogram( h_sgMET,    rhName3, 1 ) ;
   rh_sgNJets   = RebinHistogram( h_sgNJets,  rhName4, 1 ) ;
   */

   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, -0.2, 1.5 ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, -0.2, 1.5 ) ;

   WriteMcHisto() ;
   cout<<" ======== CutFlow for Signal MC ======== "<<endl ;
   select->PrintCutFlow() ;

}

void Output::Produce() {

     string dataFileNames ;
     Input->GetParameters( "TheData", &dataFileNames );
     vector<string> mcFileNames ;
     Input->GetParameters( "TheMC",   &mcFileNames );

     RunData( dataFileNames ) ;
     //for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {
     //    RunMC( mcFileNames[i], normV[i] ) ;
     //}

}

// Shift peak of h1 to the position of the peak of h2
void Output::ShiftPeak( TH1D* h1 , TH1D* h2 ) {

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

// Rebin with 3 variable bin sizes
TH1D* Output::RebinHistogram( TH1D* h1, string newHistoName,  pair<int, int> cw[] ) {

   double b[3] = { cw[0].first,  cw[1].first,  cw[2].first } ;
   double r[3] = { cw[0].second, cw[1].second, cw[2].second } ;
   double c[4] , w[3] ; 
 
   // c: start bin, w: bin width
   c[0] = h1->GetBinCenter( b[0] ) - ( h1->GetBinWidth( b[0] )/2 ) ;
   w[0] = h1->GetBinWidth(  b[0] )*r[0]  ;

   c[1] = h1->GetBinCenter( b[1] ) - ( h1->GetBinWidth( b[1] )/2 ) ;
   w[1] = h1->GetBinWidth(  b[1] )*r[1] ;

   c[2] = h1->GetBinCenter( b[2] ) - ( h1->GetBinWidth( b[2] )/2 ) ;
   w[2] = h1->GetBinWidth(  b[2] )*r[2]  ;

   int lastBin = h1->GetNbinsX() ;
   c[3] = h1->GetBinCenter( lastBin ) - (h1->GetBinWidth( lastBin )/2) ;


   vector<double> cutV ;
   for ( int i=0 ; i < 3 ; i++) {
       printf(" c: %.2f  w: %.2f \n", c[i], w[i] ) ;
       int j = 0 ;
       bool fill = true ;
       while ( fill ) {
          double edge = c[i] + (w[i]*j);
          if ( edge < c[i+1] ) {
             cutV.push_back( edge )  ;
             printf( " edge %d-%d: %.2f \n", i, j, edge ) ;
          } else {
            fill = false ;
          }
          j++ ;
       }  ;
   }
   cutV.push_back( c[3] + h1->GetBinWidth( lastBin ) ) ;

   const int nBin = cutV.size() - 1 ;
   Double_t xbins[ nBin + 1 ] ;

   printf(" nbin: %d , size: %d \n", nBin, (int)cutV.size() ) ;
   for ( size_t i=0; i< cutV.size() ; i++ ) {
       xbins[i] = cutV[i] ;
       printf( " cut %d : %.2f \n", (int)i, cutV[i] ) ;
   }

   TH1D* h1_new = (TH1D*) h1->Rebin( nBin, newHistoName.c_str(), xbins );
   return h1_new ;
}

// rebin two-side tails
TH1D* Output::RebinHistogram( TH1D* h1, string newHistoName, double center, double width ) {

     int lowBound = h1->FindBin( center - width ) ;
     int  upBound = h1->FindBin( center + width ) ;

     double aveBC0 = 0 ;
     double sumBC0 = 0 ;
     double rbin0  = 0 ;
     double aveBC1 = 0 ;
     double sumBC1 = 0 ;
     double rbin1  = 0 ;
     for ( int i= 1 ; i<= h1->GetNbinsX() ; i++ ) {

         double bc_   = h1->GetBinContent(i) ;
         if ( i < lowBound ) {
            sumBC0 += bc_ ;
            rbin0 ++ ;
            aveBC0 = sumBC0 /rbin0 ;
         } 
         if ( i > upBound ) {
            sumBC1 += bc_ ;
            rbin1 ++ ;
            aveBC1 = sumBC1 /rbin1 ;
         } 
     }

     TH1D* h2 = (TH1D*) h1->Clone() ;
     h2->SetName( newHistoName.c_str() ) ;
     for ( int i= 1 ; i<= h1->GetNbinsX() ; i++ ) {
         // reset each bin
         h2->SetBinContent(i, 0 ) ;

         if ( i < lowBound ) {
            h2->SetBinContent( i, aveBC0 ) ;
         } else if ( i > upBound ) {
            h2->SetBinContent( i, aveBC1 ) ;
         } else {
            h2->SetBinContent( i, h1->GetBinContent(i) ) ;
         }
     }

     return h2 ;
}


// Automatic rebin
TH1D* Output::RebinHistogram( TH1D* h1, string newHistoName, double minBC ) {

     // accumuate bin information
     vector<double> xV ;
     vector<double> yV ;
     double aveBC = 0 ;
     double sumBC = 0 ;
     double rbin_ = 0 ;
     for ( int i= 1 ; i<= h1->GetNbinsX() ; i++ ) {

         double bc_   = h1->GetBinContent(i) ;
         double x_    = h1->GetBinCenter(i) ;
         double bc1_  = ( i == h1->GetNbinsX() ) ? minBC+1 : h1->GetBinContent(i+1) ;
         //cout<<" x: "<< x_ <<" y:"<< bc_   ;
         if ( aveBC < minBC ) {
            sumBC += bc_ ;
            rbin_ += 1. ;
            aveBC = sumBC / rbin_ ;
            if ( (aveBC >  minBC && bc1_ > minBC) || i == h1->GetNbinsX() ) {
               xV.push_back( x_ ) ;
               yV.push_back( aveBC ) ;
               //cout<<" aveBC: "<< aveBC<<"  from sum:"<< sumBC<<"/"<<rbin_   ;
               sumBC = 0 ;
               rbin_ = 0 ;
            }
            aveBC = 0 ;
         }
         //cout<<" "<<endl ; 
     }
     //cout<<" ====================== "<<endl ; 
     // refill the histogram 
     TH1D* h2 = (TH1D*) h1->Clone() ;
     h2->SetName( newHistoName.c_str() ) ;
     int ii = 0 ;
     for ( int i= 1 ; i<= h1->GetNbinsX() ; i++ ) {
         h2->SetBinContent(i, 0 ) ;
         for ( size_t j= ii ; j< xV.size(); j++ ) {
              double x_    = h2->GetBinCenter(i) ;
              if ( x_ <= xV[j] ) {
                 h2->SetBinContent(i, yV[j] ) ;
                 ii = j ;
                 //cout<<" x: "<< x_ <<" xB:"<< xV[j]<<" y: "<< yV[j] <<endl ;
                 break ;
              }
         }
     }
     return h2 ;
}

void Output::WriteDataHisto() { 

     h_dataTime->Write() ; 
     h_dataTimeA->Write() ; 
     h_MET->Write() ;
     h_bgTime->Write() ;
     h_bgTimeA->Write() ;
     h_bgMET->Write() ;

     rh_dataTime->Write() ; 
     rh_dataTimeA->Write() ; 
     //rh_MET->Write() ;
     rh_bgTime->Write() ;
     rh_bgTimeA->Write() ;
     //rh_bgMET->Write() ;
     //rh_NJets->Write() ;

     h_NJets->Write() ;
}

void Output::WriteMcHisto() { 

     h_sgTime->Write() ;
     h_sgTimeA->Write() ;
     h_sgMET->Write() ;
     h_sgNJets->Write() ;

     rh_sgTime->Write() ;
     rh_sgTimeA->Write() ;
     //rh_sgMET->Write() ;
     //rh_sgNJets->Write() ;

}
