#include "Background.h"

Background::Background( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  h_draw = new hDraw( datacardfile ) ; 
  select = new DPSelection( datacardfile ) ;

  Input->GetParameters("ProcessEvents", &ProcessEvents ) ;
  Input->GetParameters("SkipEvents",    &SkipEvents ) ;
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("IsData",        &isData ) ; 

  //OpenHistograms() ;
}

Background::~Background() {

        delete select ;
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

void Background::RunEstimation( string dataName ) {

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], cscdPhi[MAXPHO], sMajPho[MAXPHO] ;
   int   nXtals[MAXPHO] ;
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

   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );

   // initialize selection
   select->Init( tr1 ) ;
   select->ResetCounter() ;

   int totalN = tr->GetEntries();
   cout<<" **** from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;

   // Background counter
   int O12[5]   = { 0 };
   int O34[5]   = { 0 };
   int B12[5]   = { 0 };
   int B34[5]   = { 0 };
   int h_B12[5] = { 0 };
   int s_B12[5] = { 0 };
   int h_B34[5] = { 0 };
   int s_B34[5] = { 0 };
   int h_O12[5] = { 0 };
   int s_O12[5] = { 0 };
   int h_O34[5] = { 0 };
   int s_O34[5] = { 0 };
   int Q_12  =  0 ; 
   int Q_34  =  0 ; 
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

       //cout<<" NJet : "<< selectJets.size() <<endl ;
       nEvt++;
       //cout<<" EVT# : "<< nEvt <<endl ;
       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
           int k = selectPho[kk].first ;
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;

	   bool haloTag  = ( sMajPho[k] > 0.7 && cscdPhi[k] < 0.05 && fabs( gP4_.Eta() ) < 1.4 ) ? true : false  ;
	   if ( fabs( gP4_.Eta() ) > 1.4 && cscdPhi[k] < 0.05 ) haloTag = true ;
	   bool spikeTag = ( nXtals[k] < 7 ) ? true : false  ;
	   //bool ghostTag = ( haloTag || spikeTag ) ? true : false ;

           int eta_i = (int) ( fabs( gP4_.Eta() ) / 0.28 )  ;

           // background control region 
           if ( selectJets.size() > 0 && selectJets.size() < 2 ) {
              if ( fabs(seedTime[k]) < 2. )  Q_12++ ;
              if ( seedTime[k] < -3 ) {
                 O12[eta_i]++ ;
                 if ( haloTag )  h_O12[eta_i]++ ;
                 if ( spikeTag ) s_O12[eta_i]++ ;
              }
              if ( seedTime[k] > 2 ) {
                 B12[eta_i]++ ;
                 if ( haloTag )  h_B12[eta_i]++ ;
                 if ( spikeTag ) s_B12[eta_i]++ ;
              }
           }
           // signal region
           if ( selectJets.size() > 1 ) {
              if ( fabs(seedTime[k]) < 2. )  Q_34++ ;
              if ( seedTime[k] < -3 ) {
                 O34[eta_i]++ ;
                 if ( haloTag )  h_O34[eta_i]++ ;
                 if ( spikeTag ) s_O34[eta_i]++ ;
              }
              if ( seedTime[k] > 2 ) {
                 B34[eta_i]++ ;
                 if ( haloTag )  h_B34[eta_i]++ ;
                 if ( spikeTag ) s_B34[eta_i]++ ;
              }
           }
       } // end of photon looping
       //cout<<" Q12 : "<< Q_12 <<" Q_34 : "<< Q_34 <<endl ;
       //for(int j=0; j<5; j++ )  cout<<"("<<j<<") O12: "<< O12[j] <<" O34: "<< O34[j] <<endl ;

   } // end of event looping

   // Get the scaling factor 
   vector<double> scV = GetScale( O34, h_O34, s_O34, O12,  h_O12, s_O12 ) ;
   double sc_Q = ( Q_12 < 1. ) ? 0 : Q_34/Q_12 ;
   printf(" scaling = S: %f , H: %f , Q: %f , Qpeak: %f \n", scV[0] , scV[1], scV[2], sc_Q ) ;

   for (int j=0; j< 5; j++ ) {
       // get background components from bg control region at t > 2 ns 
       vector<double> C12 = GetComponent( j , B12[j], h_B12[j], s_B12[j] ) ;

       //double sc_Q12 = ( Q_12[j] == 0 ) ? 0 : (double)Q34[j] / (double)Q12[j] ;
       //GetScale( h_O12, s_O12, h_O34, s_O34, C12[0], C12[1], C12[2], sc_Q12 ) ;
       double predict_B34 = (C12[0]*scV[0]) + (C12[1]*scV[1]) + (C12[2]*sc_Q) ;
       printf(" Real B34[%d] = %d, h_B34 = %d , s_B34 = %d ", j , B34[j], h_B34[j], s_B34[j] ) ;
       printf(" Predict B34 : %f \n",  predict_B34 ) ;
   }

}

// Return the background components in background control region ( MET < 60 GeV )
// Return [0]:spike , [1]:halo , [2]:QCD
// Input : number of event in background control region at t > 2 ns region 
// B12 : total background , h_B12 : halo-tagged events , s_B12 : spike tagged events
vector<double> Background::GetComponent( int eta_i, int B12, int h_B12, int s_B12 ) {

       // Tagging efficiency 
       double hEff[5] = { 0.88, 0.8, 0.8, 0.8, 0.8 } ; // halo
       double sEff[5] = { 0.79, 0.8, 0.8, 0.8, 0.8 } ; // spike
       double h = hEff[ eta_i ] ;   // halo
       double s = sEff[ eta_i ] ;   // spike

       // Mis-tag rate
       double mA[5] = { 0.00035, 0.00029, 0.00022, 0.00059, 0.00133 } ;
       double nA[5] = { 0.04144, 0.02231, 0.00456, 0.00101, 0.00020 } ;
       double m = mA[ eta_i ] ;   // halo
       double n = nA[ eta_i ] ;   // spike

       // spike content
       double S12 = ( s_B12 - (n*B12) ) / ( s - n ) ;
       S12 = ( S12 < 0. ) ? 0 : S12 ;
       // halo content 
       double H12 = ( h_B12 - (m*B12) ) / ( h - m ) ;
       H12 = ( H12 < 0. ) ? 0 : H12 ;
       // QCD content 
       double Q12 = (double)(B12) - S12 - H12 ;
       Q12 = ( Q12 < 0. ) ? 0 : Q12 ;

       printf("(%d) B12 %d = (S12: %.2f ) + ( H12: %.2f ) + ( Q12: %.2f )\n ", eta_i, B12, S12, H12, Q12 ) ;

       vector<double> C12 ;
       C12.push_back( S12 ) ;
       C12.push_back( H12 ) ;
       C12.push_back( Q12 ) ;
       return C12 ; 
}


// Using t < -3 ns area to find out the scaling factor for spikes and halo components
// O34 : total # of events at  t < -3ns in signal region 
// h_O34 : # of events in O34 are tagged as halo
// s_O34 : # of events in O34 are tagged as spike
vector<double> Background::GetScale( int* O34, int*  h_O34, int* s_O34, int* O12, int*  h_O12, int* s_O12) {

     double H34 = 0. ;
     double H12 = 0. ;
     double S34 = 0. ;
     double S12 = 0. ;
     double Q34 = 0. ;
     double Q12 = 0. ;
     for ( int j=0 ; j < 5 ; j++ ) {
         cout<<" O12: "<< O12[j] <<" O34: "<< O34[j] <<endl ;
         // get background components from bg control region at t < -3 ns 
         vector<double> n12 = GetComponent( j , O12[j], h_O12[j], s_O12[j] ) ;
         // get background components from sg control region at t < -3 ns 
         vector<double> n34 = GetComponent( j , O34[j], h_O34[j], s_O34[j] ) ;
	 H34 +=  n34[1] ;
	 H12 +=  n12[1] ;
	 S34 +=  n34[0] ;
	 S12 +=  n12[0] ;
         Q34 +=  n34[2] ;
         Q12 +=  n12[2] ;
     }
     double sc_H = ( H12  < 1. ) ? 0 : H34/H12 ;
     double sc_S = ( S12  < 1. ) ? 0 : S34/S12 ;
     double sc_Q = ( Q12  < 1. ) ? 0 : Q34/Q12 ;
 
     vector<double> scV ; 
     scV.push_back( sc_S );
     scV.push_back( sc_H );
     scV.push_back( sc_Q );

     return scV ;

}

void Background::GetScale( int h_O12, int s_O12, int h_O34, int s_O34, double S12, double H12, double Q12, double sc_Q ) {

       printf(" h_O34: %d , s_O34: %d , h_O12: %d  , s_O12: %d  \n ", h_O34, s_O34, h_O12, s_O12 ) ;

       double sc_S = ( s_O12 < 1 ) ? 0. : (1.0*s_O34) / (1.0*s_O12) ;
       double sc_H = ( h_O12 < 1 ) ? 0. : (1.0*h_O34) / (1.0*h_O12) ;
  
       printf(" scale_S = %.6f , scale_H = %.6f, scale_Q = %.4f \n", sc_S , sc_H, sc_Q ) ;
       double predict = (sc_S*S12) + (sc_H*H12) + (sc_Q*Q12) ;
       printf(" predict 3+ backgroud = %.6f \n", predict ) ;
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
