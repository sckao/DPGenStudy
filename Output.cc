#include "Output.h"
#include <TRandom3.h>
#include <TBranch.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TString.h>
#include <algorithm>


Output::Output( string datacardfile ) {

  Input = AnaInput::Instance() ;

  select = new DPSelection( datacardfile ) ;
  normV = Input->NormalizeComponents( datacardfile );

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("TimeCalib",     &timeCalib) ;
  Input->GetParameters("JetCuts",       &jetCuts) ;
  Input->GetParameters("PhotonCuts",    &photonCuts) ;
  Input->GetParameters("SystType",      &systType ) ;
  Input->GetParameters("TCut",          &TCut ) ;

  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  // Define time scope
  n_t_bin  = 48 ;
  t_low = TCut[2] ;
  t_up  = TCut[3] ;

  h_dataTimeBFD= new TH1D("h_dataTimeBFD",   "Photon Seed Time from data - Full Range",   100, -9.5, 15.5);
  h_dataTimeAEC= new TH1D("h_dataTimeAEC",   "Photon Seed Time from data - Full Range",   100, -9.5, 15.5);
  h_sgTimeBFD  = new TH1D("h_sgTimeBFD",   "Photon Seed Time from signal MC - Full Range", 100, -9.5, 15.5);
  h_sgTimeAEC  = new TH1D("h_sgTimeAEC",   "Photon Seed Time from signal MC - Full Range", 100, -9.5, 15.5);

  h_dataTime   = new TH1D("h_dataTime",  "Photon Seed Time from data",         n_t_bin, t_low, t_up);
  h_dataTimeA  = new TH1D("h_dataTimeA", "Photon Ave. Cluster Time from data", n_t_bin, t_low, t_up);

  h_bgTime     = new TH1D("h_bgTime",  "Photon Seed Time of background ",         n_t_bin, t_low, t_up);
  h_bgTimeA    = new TH1D("h_bgTimeA", "Photon Ave. Cluster Time of background ", n_t_bin, t_low, t_up);

  h_sgTime     = new TH1D("h_sgTime",  "Photon Seed Time of signal ",         n_t_bin, t_low, t_up);
  h_sgTimeA    = new TH1D("h_sgTimeA", "Photon Ave. Cluster Time of signal ", n_t_bin, t_low, t_up);


  // ABCD use
  // x is eta region , each is 0.28 
  // y is different sample, 0:total, 1:halo, 2: spike, 3: cosmic
  // z is jet mulitplicity
  hBg_F  = new TH3D( "hBg_F", "Background in F region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;
  hBg_E  = new TH3D( "hBg_E", "Background in E region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;
  hBg_D  = new TH3D( "hBg_D", "Background in D region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;
  hBg_C  = new TH3D( "hBg_C", "Background in C region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;
  hBg_B  = new TH3D( "hBg_B", "Background in B region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;
  hBg_A  = new TH3D( "hBg_A", "Background in A region ",  5,  0., 5, 4, 0, 4, 3, 0, 3 ) ;

  hCol_F  = new TH3D( "hCol_F",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_E  = new TH3D( "hCol_E",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_D  = new TH3D( "hCol_D",  "Background in D (signal) region",  5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_C  = new TH3D( "hCol_C",  "Background in C ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_B  = new TH3D( "hCol_B",  "Background in B ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_A  = new TH3D( "hCol_A",  "Background in A ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;

  theFile->cd() ;
}

Output::~Output(){

  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  //delete Input ;
  cout<<" done ! "<<endl ;
}

void Output::Produce() {

     string dataFileNames ;
     Input->GetParameters( "TheData", &dataFileNames );
     //vector<string> mcFileNames ;
     //Input->GetParameters( "TheMC",   &mcFileNames );

     RunData( dataFileNames ) ;
     /*
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {
         RunMC( mcFileNames[i], normV[i] ) ;
     }
     */
}

void Output::ProduceMC() {

     vector<string> mcFileNames ;
     Input->GetParameters( "TheMC",   &mcFileNames );
     vector<string> mcIdx ;
     Input->GetParameters( "mcIndex",   &mcIdx );

     //string ctau_Id[7] = { "93", "185", "368", "733", "1076", "1444", "2161" } ;
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {
         RunMC( mcFileNames[i], mcIdx[i], normV[i] ) ;
     }
}

void Output::ProduceGen() {

     vector<string> mcFileNames ;
     Input->GetParameters( "TheMC",   &mcFileNames );
     // use official 6000 mm sample as base , normalize every sample to the number*scale factor
     //double n6k = 5.681 ;
     //double scale[6]   = { 0.412,  0.807,  1.004,  0.948,  0.721,  0.488 } ;
     string ctau_Id[6] = { "500", "1000", "2000", "3000", "6000", "12000" } ;

     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {
         RunGenOnly( mcFileNames[i], ctau_Id[i], normV[i], 1. ) ;
     }
}

// Produce Data and Background histogram for statistical test
void Output::RunData( string dataName ) { 

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float seedTime[MAXPHO], seedSwissX[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO] ;
   float metE ;
   int   nPhotons, nJets ;
   float cscdPhi[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   int nXtals[MAXPHO]  ; 

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
   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("seedSwissX",  seedSwissX );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("dtdPhi",     dtdPhi );
   tr->SetBranchAddress("dtdEta",     dtdEta );


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
       nEvt++; 

       uint32_t evtType = select->EventIdentification();
       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       bool wanted  = ( (evtType >> 4) & 1  ) ;
       bool passHLT = ( (evtType >> 5) & 1  ) ;     
       if ( !wanted || !passHLT ) continue ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;

       //cout<<" EVT# : "<< nEvt <<endl ;

       // Signal Region - Photon Pt > 80 
       for ( size_t j =0 ; j < selectPho.size() ; j++ ) {
           int k = selectPho[j].first ;
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;

           // Background Tagging
           bool haloTag   = select->HaloTag( cscdPhi[k] , sMajPho[k] , sMinPho[k] , gP4_.Eta() ) ;
	   bool spikeTag  = select->SpikeTag( nXtals[k] , sMajPho[k] , sMinPho[k], seedSwissX[k], gP4_.Eta() ) ;
           bool cosmicTag = select->CosmicTag( dtdEta[k] , dtdPhi[k] ) ;
           bool ghostTag  = ( haloTag || spikeTag || cosmicTag ) ? true : false ;

           int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;
           int nj = ( selectJets.size() > 2 ) ? 2 : (int)selectJets.size() ;

           // Seperation of collision and halo backgrounds
           bool passABCDSelection = ( newMET.E() > jetCuts[4] && timeChi2[k] < 4 && selectPho[0].second.Pt() > photonCuts[8] ) ;
           bool passCollSelection = ( newMET.E() < jetCuts[4] && timeChi2[k] < 4 && selectPho[0].second.Pt() > photonCuts[8] ) ;

           // *************************
           // * Halo-type Backgorunds *
           // *************************

           // Overall time shape - This is for validation
           if ( passABCDSelection && !ghostTag && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
              if ( noPhotMET.E() > jetCuts[4] ) h_dataTimeBFD->Fill( seedTime[k] ) ;
              if ( noPhotMET.E() < jetCuts[4] ) h_dataTimeAEC->Fill( seedTime[k] ) ;
           }

           // Region E,F  |t| < 2 ns  
           if ( fabs( seedTime[k]) < 2. && passCollSelection ) {
              if ( noPhotMET.E() > jetCuts[4] ) hBg_F->Fill( ih, 0.5, nj );
              if ( noPhotMET.E() < jetCuts[4] ) hBg_E->Fill( ih, 0.5, nj );
           }

           // Background template
           // A and B region
           if ( seedTime[k] > TCut[0] && seedTime[k] < TCut[1] && passABCDSelection ) {

              // Region A 
              if (  noPhotMET.E() < jetCuts[4] ) {
                 hBg_A->Fill( ih, 0.5, nj );
		 if ( haloTag && !cosmicTag && !spikeTag )  hBg_A->Fill( ih, 1.5, nj );
		 if ( spikeTag && !cosmicTag )              hBg_A->Fill( ih, 2.5, nj );
		 if ( cosmicTag )                           hBg_A->Fill( ih, 3.5, nj );
              }
              // Region B
              if (  noPhotMET.E() > jetCuts[4] ) {
                 hBg_B->Fill( ih, 0.5, nj );
                 if ( haloTag  && !cosmicTag && !spikeTag )  hBg_B->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )               hBg_B->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                            hBg_B->Fill( ih, 3.5, nj );
              }
           }
           // C and D region
           if ( seedTime[k] > t_low && seedTime[k] < t_up && passABCDSelection ) {

              // Region C
              if ( noPhotMET.E() < jetCuts[4] ) {

                 hBg_C->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hBg_C->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hBg_C->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hBg_C->Fill( ih, 3.5, nj );
 
                 // Background shape selection - C region
                 if ( !ghostTag && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
	            h_bgTime->Fill( seedTime[k] ) ; 
    	            h_bgTimeA->Fill( aveTime[k] ) ;
                 }
              }

              // Region D
              if ( noPhotMET.E() > jetCuts[4] ) {
                 hBg_D->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hBg_D->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hBg_D->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hBg_D->Fill( ih, 3.5, nj );

                 // Final signal sample - D region
                 if ( !ghostTag && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
      	            h_dataTime->Fill( seedTime[k] ) ;
 	            h_dataTimeA->Fill( aveTime[k] ) ;
                 }
              }
           }

           // ******************************
           // * Collision-type Backgorunds *
           // ******************************

           // Region E/F , |t| < 2 ns  
           if ( fabs(seedTime[k]) < 2. && passCollSelection ) {
              if ( noPhotMET.E() > jetCuts[4] ) hCol_F->Fill( ih, 0.5, nj );
              if ( noPhotMET.E() < jetCuts[4] ) hCol_E->Fill( ih, 0.5, nj );
           }
           if ( seedTime[k] > TCut[0] && seedTime[k] < TCut[1] && passABCDSelection ) {
              // Region B
              if ( noPhotMET.E() > jetCuts[4] ) {

                 hCol_B->Fill( ih, 0.5, nj );
                 if ( haloTag  && !cosmicTag && !spikeTag )  hCol_B->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )               hCol_B->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                            hCol_B->Fill( ih, 3.5, nj );
              }
              // Region A
              if ( noPhotMET.E() < jetCuts[4] ) {

                    hCol_A->Fill( ih, 0.5, nj );
                    if ( haloTag && !cosmicTag && !spikeTag )  hCol_A->Fill( ih, 1.5, nj );
                    if ( spikeTag && !cosmicTag )              hCol_A->Fill( ih, 2.5, nj );
                    if ( cosmicTag )                           hCol_A->Fill( ih, 3.5, nj );
              }
           }
           // ******************
           //   Region C and D
           // ******************
           if ( seedTime[k] > t_low && seedTime[k] < t_up && passCollSelection ) {
              // Region D
              if ( noPhotMET.E() > jetCuts[4] ) {

                 hCol_D->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hCol_D->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hCol_D->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hCol_D->Fill( ih, 3.5, nj );
              }
              // Region C
              if ( noPhotMET.E() < jetCuts[4] ) {

                 hCol_C->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hCol_C->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hCol_C->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hCol_C->Fill( ih, 3.5, nj );
              }
           }


       }

   } // end of event looping

   // Background estimation
   TH3D* ACols[] = { hCol_A, hCol_B, hCol_C, hCol_D, hCol_E, hCol_F } ;
   vector<TH3D*> hColls( ACols, ACols+6 ) ;
   TH3D* AMIBs[] = { hBg_A, hBg_B, hBg_C, hBg_D, hBg_E, hBg_F } ;
   vector<TH3D*> hMIBs( AMIBs, AMIBs+6 ) ;

   vector<double> predictBG = select->ABCD_ABCD( hColls, hMIBs ) ;

   double bgScale = (  h_bgTime->Integral() > 0. ) ? predictBG[0] / h_bgTime->Integral() : 1. ;
   if ( h_bgTime->Integral() == 0 ) {
      // if the predicted background == 0, use the upward 1-sigam as the background 
      // otherwise the background is set to be 1
      //double theCount = ( predictBG[0] > 0. ) ? predictBG[0] : predictBG[1] ; 
      //if ( theCount == 0 ) theCount = 1 ;

      // average the count in each bin
      double nbin = (double) h_bgTime->GetNbinsX() ;
      double c_bin = predictBG[0] / nbin  ;
      for ( int i =1 ; i <= h_bgTime->GetNbinsX() ; i++ ) {
          h_bgTime->SetBinContent( i , c_bin ) ;
          h_bgTime->SetBinError( i , predictBG[1]/sqrt( nbin ) ) ;
      }
   }

   h_bgTime->Scale( bgScale ) ; 
   h_bgTimeA->Scale( bgScale ) ; 

   rh_dataTime    = RebinHistogram( h_dataTime,    "rh_dataTime",    -1.*t_low , t_low ) ;
   rh_dataTimeA   = RebinHistogram( h_dataTimeA,   "rh_dataTimeA",   -1.*t_low , t_low ) ;
   rh_dataTimeBFD = RebinHistogram( h_dataTimeBFD, "rh_dataTimeBFD", -1.*t_low , t_low ) ;
   rh_dataTimeAEC = RebinHistogram( h_dataTimeAEC, "rh_dataTimeAEC", -1.*t_low , t_low ) ;

   rh_bgTime      = RebinHistogram( h_bgTime,     "rh_bgTime",  -1.*t_low , t_low ) ;
   rh_bgTimeA     = RebinHistogram( h_bgTimeA,    "rh_bgTimeA", -1.*t_low , t_low ) ;

   WriteDataHisto() ;
   cout<<" ======== CutFlow for Data ======== "<<endl ;
   select->PrintCutFlow() ;

}  

// This is for signal MC 
void Output::RunMC( string mcName, string ctau_Id, double weight ) { 

   // Efficiency log file
   string EffFileName = hfolder + hfName + "_eff.txt" ; 
   FILE* logfile = fopen( EffFileName.c_str() ,"a");
   fprintf(logfile," Efficinecy for %s ", ctau_Id.c_str() );

   //string mcTag = mcName.substr( 8, mcName.size() - 8 ) ;
   string mcTag = ctau_Id ;
   char hName1[32] , hName2[32], hName5[32], hName6[32]   ;
   sprintf( hName1, "h_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( hName2, "h_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( hName5, "h_sgTimeBFD_%s", mcTag.c_str() ) ;
   sprintf( hName6, "h_sgTimeAEC_%s", mcTag.c_str() ) ;

   // Reset the histogram
   h_sgTime->SetName( hName1 ) ;
   h_sgTimeA->SetName( hName2 ) ;
   h_sgTimeBFD->SetName( hName5 ) ;
   h_sgTimeAEC->SetName( hName6 ) ;

   h_sgTime->Reset() ;
   h_sgTimeA->Reset() ;
   h_sgTimeBFD->Reset() ;
   h_sgTimeAEC->Reset() ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float cscdPhi[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO], seedSwissX[MAXPHO] ;
   int nXtals[MAXPHO]  ; 
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
   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("dtdPhi",      dtdPhi );
   tr->SetBranchAddress("dtdEta",      dtdEta );

   // initialize selection
   select->Init( tr1 ) ;
   select->ResetCounter() ;

   int totalN = tr->GetEntries();
   cout<<" **** from  "<< mcName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   // Set up gaussian smearing for timing correction
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int nEvt  = 0 ;
   int nPass = 0 ;
   int nPassPhot = 0 ;
   int beginEvent = SkipEvents + 1 ;
   bool eventPass = false;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
        
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       nEvt++; 

       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       uint32_t evtType = select->EventIdentification();
       bool wanted  = ( (evtType >> 4) & 1  ) ;
       bool passHLT = ( (evtType >> 5) & 1  ) ;     
       if ( !wanted || !passHLT ) continue ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;

       //cout<<" EVT# : "<< nEvt <<endl ;
       bool passBasic = false ;
       for ( size_t j =0 ; j < selectPho.size() ; j++ ) {
           int k = selectPho[j].first ;
           // Background Tagging
           bool haloTag   = select->HaloTag( cscdPhi[k] , sMajPho[k] , sMinPho[k] , selectPho[j].second.Eta() ) ;
	   bool spikeTag  = select->SpikeTag( nXtals[k] , sMajPho[k] , sMinPho[k], seedSwissX[k], selectPho[j].second.Eta() ) ;
           bool cosmicTag = select->CosmicTag( dtdEta[k] , dtdPhi[k] ) ;
           bool ghostTag = ( haloTag || spikeTag || cosmicTag ) ? true : false ;
           if ( ghostTag && j ==0 && selectPho.size() < 2 ) break ;
           if ( ghostTag ) continue ;

           bool passABCDSelection = newMET.E() > jetCuts[4] && noPhotMET.E() > jetCuts[4]  ;
           passBasic = (selectPho[0].second.Pt() > photonCuts[8]) && (selectJets.size() >= jetCuts[2]) && (selectJets.size() < jetCuts[3] ) ;
	   // timing correction : central shift = 0.1211 ,  sigma = 0.4
           float tRes    = ( systType == 7 ) ? timeCalib[1]*2. : timeCalib[1] ;
	   float tShift  = ( systType == 9 ) ? timeCalib[0]*2. : timeCalib[0] ;
	   if ( systType == 10 ) tShift = 0. ; 
	   float tCorr = ( systType == 8 ) ? ( seedTime[k]- tShift ) : tRan->Gaus(seedTime[k], tRes ) - tShift ;

           if ( passABCDSelection && passBasic ) {
              
	      h_sgTimeBFD->Fill( tCorr, weight ) ;
              if ( tCorr > t_low && tCorr < t_up ) {
                 nPassPhot++ ;
                 if ( !eventPass ) nPass++ ;
                 eventPass = true ;
	         h_sgTime->Fill( tCorr, weight ) ;
                 h_sgTimeA->Fill( aveTime[k], weight ) ;
              }
           }
           if ( newMET.E() > jetCuts[4] && noPhotMET.E() < jetCuts[4]  && passBasic ) { 
	      h_sgTimeAEC->Fill( tCorr, weight ) ;
           }
       }

   } // end of event looping
  
   char rhName1[32] , rhName2[32], rhName5[32], rhName6[32]   ;
   sprintf( rhName1, "rh_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( rhName2, "rh_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( rhName5, "rh_sgTimeBFD_%s", mcTag.c_str() ) ;
   sprintf( rhName6, "rh_sgTimeAEC_%s", mcTag.c_str() ) ;

   // rebin two tails
   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, -1.*t_low , t_low ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, -1.*t_low , t_low ) ;
   rh_sgTimeBFD = RebinHistogram( h_sgTimeBFD,  rhName5, -1.*t_low , t_low ) ;
   rh_sgTimeAEC = RebinHistogram( h_sgTimeAEC,  rhName6, -1.*t_low , t_low ) ;

   printf(" [%s] Observe number = %.3f \n", ctau_Id.c_str(), rh_sgTime->Integral() ) ;

   WriteMcHisto() ;

   fprintf(logfile,"Observe: %f Event Eff: %f , nPhot/nEvt =  %f \n", 
                    rh_sgTime->Integral(), (double)nPass / (double)nEvt , (double)nPassPhot/(double)nEvt );
   fclose( logfile ) ;
   printf(" *** Event Efficiency : %f -> %f \n", (double)nPass / (double)nEvt , (double)nPassPhot / (double)nEvt ) ;
   cout<<" ======== CutFlow for Signal MC ======== "<<endl ;
   select->PrintCutFlow() ;

}

void Output::RunGenOnly( string mcName, string ctau_Id, double weight, double scale_ ) { 

   // Efficiency log file
   string EffFileName = hfolder + hfName + "_eff.txt" ; 
   FILE* logfile = fopen( EffFileName.c_str() ,"a");
   fprintf(logfile," Efficinecy for %s ", mcName.c_str() );

   string mcTag = ctau_Id ;
   //string mcTag = mcName.substr( 8, mcName.size() - 8 ) ;
   char hName1[32] , hName2[32], hName5[32], hName6[32]   ;
   sprintf( hName1, "h_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( hName2, "h_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( hName5, "h_sgTimeBFD_%s", mcTag.c_str() ) ;
   sprintf( hName6, "h_sgTimeAEC_%s", mcTag.c_str() ) ;

   // Reset the histogram
   h_sgTime->SetName( hName1 ) ;
   h_sgTimeA->SetName( hName2 ) ;
   h_sgTimeBFD->SetName( hName5 ) ;
   h_sgTimeAEC->SetName( hName6 ) ;

   h_sgTime->Reset() ;
   h_sgTimeA->Reset() ;
   h_sgTimeBFD->Reset() ;
   h_sgTimeAEC->Reset() ;

   float genPx[MAXGEN], genPy[MAXGEN], genPz[MAXGEN], genE[MAXGEN] ;
   float genVx[MAXGEN], genVy[MAXGEN], genVz[MAXGEN], genT[MAXGEN] ;
   int   pdgId[MAXGEN], momId[MAXGEN] ;

   float jetPx[10], jetPy[10], jetPz[10], jetE[10] ;

   float metPx, metPy, metE ;
   int   nGen, nJets ;

   TTree* tr   = Input->GetTree( mcName, "DPGenAnalysis" );

   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nGen",        &nGen);

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );
   tr->SetBranchAddress("jetPz",       jetPz );
   tr->SetBranchAddress("jetE",        jetE );

   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );
   tr->SetBranchAddress("genVx",       genVx );
   tr->SetBranchAddress("genVy",       genVy );
   tr->SetBranchAddress("genVz",       genVz );

   int totalN = tr->GetEntries();
   cout<<" **** from  "<< mcName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   // Set up gaussian smearing for timing correction
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   //int nEvt  = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;

   //vector<double> v_time ;
   //vector<TLorentzVector> v_p4 ;
   double finalCount = 0 ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       // Count number of jets
       int nPassJet = 0 ;
       for ( int k=0 ; k < nJets; k++ ) {
           TLorentzVector jP4 = TLorentzVector( jetPx[k], jetPy[k], jetPz[k], jetE[k] ) ;
           if ( fabs( jP4.Eta()) > jetCuts[1] ) continue ;
           if ( jP4.Pt() > jetCuts[0] ) nPassJet++ ;
       }
       // Gen MET
       TLorentzVector met = TLorentzVector( metPx, metPy, 0., metE ) ;
       noPhotMET = met ;

       // Photon signal
       //v_time.clear() ;
       //v_p4.clear() ;
       double maxPhoPt = 0 ;
       for ( int k=0; k< nGen ; k++) {

           if ( pdgId[k] != 22 ) continue ;
           TLorentzVector gP4 = TLorentzVector( genPx[k], genPy[k], genPz[k], genE[k] ) ;

           int mId = momId[k]  ;
           if ( mId < 0  ) continue ;
           TLorentzVector xP4 = TLorentzVector( genPx[mId], genPy[mId], genPz[mId], genE[mId] ) ;

           // This is where the neutralino decays
           double vx = genVx[k] ;
           double vy = genVy[k] ;
           double vz = genVz[k] ;
           double ctbgT = sqrt( (vx*vx) + (vy*vy)  ) ;
           double EcalTime = genT[mId] ;  // tau*gamma
           // *************************************************************
           // * Main propagator - to make sure decay photon will hit ECAL *
           // *************************************************************
           bool hasEcalTime = Propagator( gP4, vx, vy, vz, EcalTime ) ;
           if ( !hasEcalTime ) continue ;

           double d_x = vx - 0 ;
           double d_y = vy - 0 ;
           double d_z = vz - 0 ;
           double d_r = sqrt( (d_x*d_x) + (d_y*d_y) + (d_z*d_z) );
           double t0  = d_r /30. ; // t0 -> ecaltime assuming photon is from original

           // This is the measured ECAL time for gen photons
	   // timing correction : central shift = 0.162 ,  sigma = 0.354
           // Syst 7: tRes up , 8: tRes down , 9 : tShift up , 10: tShift down
           float tRes   = 0.4356 ;
           float tShift = 0.0322 ;
           if ( systType == 7 )  tRes   = tRes + timeCalib[1]  ;
           if ( systType == 8 )  tRes   = tRes - timeCalib[1]  ;
	   if ( systType == 9 )  tShift = tShift + timeCalib[0] ;
	   if ( systType == 10)  tShift = tShift - timeCalib[0] ;

           double dT = EcalTime - t0 ;
	   float tCorr = tRan->Gaus( dT, tRes ) - tShift ;

           // Build the P4 for gen photon from reconstruction point of view 
           TLorentzVector genRecoP4 = TLorentzVector( d_x, d_y, d_z, d_r ) ;
           genRecoP4 = genRecoP4 * ( gP4.E() / d_r ) ;
           noPhotMET += genRecoP4 ;
           if ( genRecoP4.Pt() < 1. ||  fabs(genRecoP4.Eta()) > photonCuts[1] ) continue ;

           if ( genRecoP4.Pt() > maxPhoPt ) maxPhoPt = genRecoP4.Pt() ;
           //v_time.push_back( tCorr ) ;
           //v_p4.push_back( genRecoP4 ) ;
           double scale_1 = Input->RecoWeight( xP4.Pt() , ctbgT*10./(xP4.Beta()*xP4.Gamma()) ) ;

           finalCount += (scale_1*weight) ;
           h_sgTime->Fill( tCorr, weight) ;
           h_sgTimeA->Fill( tCorr, weight ) ;
	   h_sgTimeBFD->Fill( tCorr, weight ) ;
	   h_sgTimeAEC->Fill( tCorr, weight ) ;
       }

       //bool passABCDSelection = (met.E() > jetCuts[4] && noPhotMET.E() > jetCuts[4] ) ;
       //bool passBasic  = (maxPhoPt > photonCuts[8]) && (nPassJet >= jetCuts[2]) && (nPassJet < jetCuts[3])  ;


   } // end of event looping
  
   char rhName1[64] , rhName2[64], rhName5[64], rhName6[64]   ;
   sprintf( rhName1, "rh_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( rhName2, "rh_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( rhName5, "rh_sgTimeBFD_%s", mcTag.c_str() ) ;
   sprintf( rhName6, "rh_sgTimeAEC_%s", mcTag.c_str() ) ;

   // rebin two tails
   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, -1.*t_low , t_low ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, -1.*t_low , t_low ) ;
   rh_sgTimeBFD = RebinHistogram( h_sgTimeBFD,  rhName5, -1.*t_low , t_low ) ;
   rh_sgTimeAEC = RebinHistogram( h_sgTimeAEC,  rhName6, -1.*t_low , t_low ) ;

   double scale_factor = finalCount / rh_sgTime->Integral() ;
   printf(" orignal: %.3f , scale factor = %.3f ", rh_sgTime->Integral() , scale_factor ) ;
   rh_sgTime->Scale( scale_factor ) ;
   rh_sgTimeA->Scale( scale_factor  ) ;
   rh_sgTimeBFD->Scale( scale_factor ) ;
   rh_sgTimeAEC->Scale( scale_factor ) ;

   h_sgTime->Scale( scale_factor ) ;
   h_sgTimeA->Scale( scale_factor  ) ;
   h_sgTimeBFD->Scale( scale_factor ) ;
   h_sgTimeAEC->Scale( scale_factor ) ;
   printf(" scaled N: %.3f , should be : %.3f \n", rh_sgTime->Integral(), scale_ ) ;

   WriteMcHisto() ;

   fprintf(logfile,"Observe: %f  \n",   rh_sgTime->Integral() );
   fclose( logfile ) ;
   //printf(" *** Event Efficiency : %f -> %f \n", (double)nPass / (double)nEvt , (double)nPassPhot / (double)nEvt ) ;
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

// Rebin two-side tails - Current used method
//TH1D* Output::RebinHistogram( TH1D* h1, string newHistoName, double center, double width ) {
TH1D* Output::RebinHistogram( TH1D* h1, string newHistoName, double lowX, double upX ) {

     int lowBound = h1->FindBin( lowX ) - 1;
     int  upBound = h1->FindBin( upX ) - 1;

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
     h_dataTimeBFD->Write() ; 
     h_dataTimeAEC->Write() ; 
     h_bgTime->Write() ;
     h_bgTimeA->Write() ;

     rh_dataTime->Write() ; 
     rh_dataTimeA->Write() ; 
     rh_dataTimeBFD->Write() ; 
     rh_dataTimeAEC->Write() ; 
     rh_bgTime->Write() ;
     rh_bgTimeA->Write() ;

     hBg_A->Write() ;
     hBg_B->Write() ;
     hBg_C->Write() ;
     hBg_D->Write() ;
     hBg_E->Write() ;
     hBg_F->Write() ;

     hCol_A->Write() ;
     hCol_B->Write() ;
     hCol_C->Write() ;
     hCol_D->Write() ;
     hCol_E->Write() ;
     hCol_F->Write() ;
}

void Output::WriteMcHisto() { 

     h_sgTime->Write() ;
     h_sgTimeA->Write() ;
     h_sgTimeBFD->Write() ;
     h_sgTimeAEC->Write() ;

     rh_sgTime->Write() ;
     rh_sgTimeA->Write() ;
     rh_sgTimeBFD->Write() ;
     rh_sgTimeAEC->Write() ;

}

// propagator with backward propagation
// ECal Dimension : R:( 129 ~ 155 cm , Z(one-side) : 317 ~345 )
bool Output::Propagator( TLorentzVector& v, double& x, double& y, double& z, double& t, double taugamma ) {

    bool hasEcalTime = true ;

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;
    double dL = 0. ;

    bool insideEcal =  ( r < 129. && fabs(z) < 317. ) ? true : false ;  // inner edge of ECAL
    bool outsideEcal = ( r > 155. || fabs(z) > 345. ) ? true : false ;  // outer edge of ECAL
    bool alived     = true ;

    //if ( r < 129. && fabs(z) < 317. )  cout<<"   Inside ECAL  " ;
    //if ( r > 155. || fabs(z) > 345. )  cout<<"   Outside ECAL " ;
    //if ( !insideEcal && !outsideEcal ) cout<<"   In ECAL      " ; 

    int     i = 0 ;
    do {

       i++ ;
       r0 = sqrt( (x*x) + (y*y ) ) ;
       z0 = z ;
       t = t + dt ;
       x = x + (bx*dt*30 ) ;
       y = y + (by*dt*30 ) ;
       z = z + (bz*dt*30 ) ;
       r = sqrt( (x*x) + (y*y) ) ;

       alived      = ( t < taugamma ) ? true : false ;
       if ( t > taugamma )  hasEcalTime = false ;

       insideEcal  = ( r < 129 && fabs(z) < 317 ) ? true : false ; // inner surface of ECAL
       outsideEcal = ( r > 155 || fabs(z) > 345 ) ? true : false ; // outer surface of ECAL
       if ( !insideEcal && !outsideEcal )     alived = false ; // for those photons just hit the Ecal

       double dr = r - r0 ;
       double dz = fabs(z) - fabs(z0) ;
       if ( outsideEcal && alived ) {
          if ( dr > 0 && dz > 0            ) alived = false ;
          if ( dr < 0 && r < 155 && dz > 0 ) alived = false ;
          if ( dz < 0 && z < 345 && dr > 0 ) alived = false ;
          if ( !alived ) hasEcalTime = false ;
          // simulate the energy loss from HCAL , radiation length = 1.5 cm
          dL += sqrt( (dr*dr) + (dz*dz) ) ;
          if ( dL > 1.5 ) {
             v = v*0.63 ;
             dL = 0. ;
          }
       }

    } while ( alived ) ;

    //printf( " .... N_Steps : %d , ( %4.2f %4.2f %4.2f )  \n", i, x, y, z ) ;
    return hasEcalTime ;
}

