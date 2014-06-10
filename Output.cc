#include "Output.h"
#include <TRandom3.h>
#include <TBranch.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TString.h>
#include <algorithm>


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
  Input->GetParameters("JetCuts",       &jetCuts) ;
  Input->GetParameters("PhotonCuts",    &photonCuts) ;
  Input->GetParameters("SystType",      &systType ) ;

  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  // Define time scope
  n_t_bin  = 28 ;
  t_low = 3. ;
  t_up  = 10. ;

  h_dataTimeAll= new TH1D("h_dataTimeAll",   "Photon Seed Time from data - Full Range",   80, -4.5, 15.5);
  h_sgTimeAll  = new TH1D("h_sgTimeAll",   "Photon Seed Time from signal MC - Full Range",   80, -4.5, 15.5);

  h_dataTime   = new TH1D("h_dataTime",  "Photon Seed Time from data",         n_t_bin, t_low, t_up);
  h_dataTimeA  = new TH1D("h_dataTimeA", "Photon Ave. Cluster Time from data", n_t_bin, t_low, t_up);
  h_MET        = new TH1D("h_MET",       " MET  ", 50,  30, 530);

  h_bgTime     = new TH1D("h_bgTime",  "Photon Seed Time of background ",         n_t_bin, t_low, t_up);
  h_bgTimeA    = new TH1D("h_bgTimeA", "Photon Ave. Cluster Time of background ", n_t_bin, t_low, t_up);
  h_bgMET      = new TH1D("h_bgMET",   "MET of background sample  ", 50,  30, 530);

  h_sgTime     = new TH1D("h_sgTime",  "Photon Seed Time of signal ",         n_t_bin, t_low, t_up);
  h_sgTimeA    = new TH1D("h_sgTimeA", "Photon Ave. Cluster Time of signal ", n_t_bin, t_low, t_up);
  h_sgMET      = new TH1D("h_sgMET",   "MET from signal MC ", 50,  30, 530);

  h_NJets      = new TH1D("h_NJets",   "N of Jets from Data",      10,  0, 10 );
  h_sgNJets    = new TH1D("h_sgNJets", "N of Jets from Signal MC", 10,  0, 10 );

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
  delete Input ;
  cout<<" done ! "<<endl ;
}

void Output::Produce() {

     string dataFileNames ;
     Input->GetParameters( "TheData", &dataFileNames );
     vector<string> mcFileNames ;
     Input->GetParameters( "TheMC",   &mcFileNames );

     RunData( dataFileNames ) ;
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) {
         RunMC( mcFileNames[i], normV[i] ) ;
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

       uint32_t evtType = select->EventIdentification();
       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       bool wanted = ( (evtType >> 1) & 1  ) ;
       if ( !wanted ) continue ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;

       nEvt++; 
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

           // Region E,F  |t| < 2 ns  
           if ( fabs( seedTime[k]) < 2. && passCollSelection ) {
              if ( noPhotMET.E() > jetCuts[4] ) hBg_F->Fill( ih, 0.5, nj );
              if ( noPhotMET.E() < jetCuts[4] ) hBg_E->Fill( ih, 0.5, nj );
           }

           // Background template
           // A and B region
           if ( seedTime[k] < -3. && seedTime[k] > -10. && passABCDSelection ) {

              if ( !ghostTag )  h_bgMET->Fill( metE ) ;
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
           if ( seedTime[k] >  3. && seedTime[k] < 10. && passABCDSelection ) {

              if ( !ghostTag ) h_MET->Fill( metE ) ;
              // Region C
              if ( noPhotMET.E() < jetCuts[4] ) {

                 hBg_C->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hBg_C->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hBg_C->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hBg_C->Fill( ih, 3.5, nj );
	         h_bgTime->Fill( seedTime[k] ) ; 
 	         h_bgTimeA->Fill( aveTime[k] ) ;
              }

              // Region D
              if ( noPhotMET.E() > jetCuts[4] ) {
                 hBg_D->Fill( ih, 0.5, nj );
                 if ( haloTag && !cosmicTag && !spikeTag )  hBg_D->Fill( ih, 1.5, nj );
                 if ( spikeTag && !cosmicTag )              hBg_D->Fill( ih, 2.5, nj );
                 if ( cosmicTag )                           hBg_D->Fill( ih, 3.5, nj );

                 // Signal template - D region
   	         h_dataTimeAll->Fill( seedTime[k] ) ;
   	         h_dataTime->Fill( seedTime[k] ) ;
	         h_dataTimeA->Fill( aveTime[k] ) ;
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
           if ( seedTime[k] < -3. && seedTime[k] > -10. && passCollSelection ) {
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
           if ( seedTime[k] > 3.0 && seedTime[k] < 10.0 && passCollSelection ) {
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

       h_NJets->Fill( (int) selectJets.size() ) ;

   } // end of event looping

   // Background estimation
   TH3D* ACols[] = { hCol_A, hCol_B, hCol_C, hCol_D, hCol_E, hCol_F } ;
   vector<TH3D*> hColls( ACols, ACols+6 ) ;
   TH3D* AMIBs[] = { hBg_A, hBg_B, hBg_C, hBg_D, hBg_E, hBg_F } ;
   vector<TH3D*> hMIBs( AMIBs, AMIBs+6 ) ;

   vector<double> predictBG = select->ABCD_ABCD( hColls, hMIBs ) ;

   double bgScale = (  h_bgTime->Integral() > 0. ) ? predictBG[0] / h_bgTime->Integral() : 1. ;
   h_bgTime->Scale( bgScale ) ; 
   h_bgTimeA->Scale( bgScale ) ; 

   rh_dataTime    = RebinHistogram( h_dataTime,    "rh_dataTime",    -1.*t_low , t_low ) ;
   rh_dataTimeA   = RebinHistogram( h_dataTimeA,   "rh_dataTimeA",   -1.*t_low , t_low ) ;
   rh_dataTimeAll = RebinHistogram( h_dataTimeAll, "rh_dataTimeAll", -1.*t_low , t_low ) ;

   rh_bgTime      = RebinHistogram( h_bgTime,     "rh_bgTime",  -1.*t_low , t_low ) ;
   rh_bgTimeA     = RebinHistogram( h_bgTimeA,    "rh_bgTimeA", -1.*t_low , t_low ) ;

   WriteDataHisto() ;
   cout<<" ======== CutFlow for Data ======== "<<endl ;
   select->PrintCutFlow() ;

}  

void Output::RunMC( string mcName, double weight ) { 

   string mcTag = mcName.substr( 8, mcName.size() - 8 ) ;
   char hName1[32] , hName2[32], hName3[32], hName4[32], hName5[32]   ;
   sprintf( hName1, "h_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( hName2, "h_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( hName3, "h_sgMET_%s",   mcTag.c_str() ) ;
   sprintf( hName4, "h_sgNJets_%s", mcTag.c_str() ) ;
   sprintf( hName5, "h_sgTimeAll_%s", mcTag.c_str() ) ;

   // Reset the histogram
   h_sgTime->SetName( hName1 ) ;
   h_sgTimeA->SetName( hName2 ) ;
   h_sgMET->SetName( hName3 ) ;
   h_sgNJets->SetName( hName4 ) ;
   h_sgTimeAll->SetName( hName5 ) ;

   h_sgTime->Reset() ;
   h_sgTimeA->Reset() ;
   h_sgMET->Reset() ;
   h_sgNJets->Reset() ;
   h_sgTimeAll->Reset() ;

   float phoPx[MAXPHO], phoPy[MAXPHO], phoPz[MAXPHO], phoE[MAXPHO] ;
   float cscdPhi[MAXPHO], sMinPho[MAXPHO], sMajPho[MAXPHO], dtdPhi[MAXPHO], dtdEta[MAXPHO] ;
   float seedTime[MAXPHO], aveTime[MAXPHO], aveTime1[MAXPHO], timeChi2[MAXPHO], seedSwissX[MAXPHO] ;
   int nXtals[MAXPHO]  ; 
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
       uint32_t evtType = select->EventIdentification();
       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       bool wanted = ( (evtType >> 1) & 1  ) ;
       if ( !wanted ) continue ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       nEvt++; 
       //cout<<" EVT# : "<< nEvt <<endl ;

       for ( size_t j =0 ; j < selectPho.size() ; j++ ) {
           int k = selectPho[j].first ;
           // Background Tagging
           bool haloTag   = select->HaloTag( cscdPhi[k] , sMajPho[k] , sMinPho[k] , selectPho[j].second.Eta() ) ;
	   bool spikeTag  = select->SpikeTag( nXtals[k] , sMajPho[k] , sMinPho[k], seedSwissX[k], selectPho[j].second.Eta() ) ;
           bool cosmicTag = select->CosmicTag( dtdEta[k] , dtdPhi[k] ) ;
           bool ghostTag = ( haloTag || spikeTag || cosmicTag ) ? true : false ;
           if ( ghostTag && j ==0 ) break ;
           if ( ghostTag ) continue ;

           bool passABCDSelection = ( newMET.E() > jetCuts[4] && noPhotMET.E() > jetCuts[4] 
                                     && selectPho[0].second.Pt() > photonCuts[8] ) ;
             
           if ( passABCDSelection && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
	      // timing correction : central shift = 0.1211 ,  sigma = 0.4
              float tRes    = ( systType == 7 ) ? timeCalib[1]*2. : timeCalib[1] ;
              float tShift  = ( systType == 9 ) ? timeCalib[0]*2. : timeCalib[0] ;
              if ( systType == 10 ) tShift = 0. ; 
              float tCorr = ( systType == 8 ) ? ( seedTime[k]- tShift ) : tRan->Gaus(seedTime[k], tRes ) - tShift ;
              
	      //float tCorr = seedTime[k] - 0.1211 ;
	      h_sgTimeAll->Fill( tCorr, weight ) ;
	      h_sgTime->Fill( tCorr, weight ) ;
              h_sgTimeA->Fill( aveTime[k], weight ) ;
	      h_sgMET->Fill( metE, weight ) ;
           }
       }
       h_sgNJets->Fill( (int) selectJets.size(), weight ) ;

   } // end of event looping
  
   char rhName1[32] , rhName2[32], rhName3[32], rhName4[32], rhName5[32]   ;
   sprintf( rhName1, "rh_sgTime_%s",  mcTag.c_str() ) ;
   sprintf( rhName2, "rh_sgTimeA_%s", mcTag.c_str() ) ;
   sprintf( rhName3, "rh_sgMET_%s",   mcTag.c_str() ) ;
   sprintf( rhName4, "rh_sgNJets_%s", mcTag.c_str() ) ;
   sprintf( rhName5, "rh_sgTimeAll_%s", mcTag.c_str() ) ;

   // rebin two tails
   rh_sgTime    = RebinHistogram( h_sgTime,   rhName1, -1.*t_low , t_low ) ;
   rh_sgTimeA   = RebinHistogram( h_sgTimeA,  rhName2, -1.*t_low , t_low ) ;
   rh_sgTimeAll = RebinHistogram( h_sgTimeAll,  rhName5, -1.*t_low , t_low ) ;

   WriteMcHisto() ;
   cout<<" ======== CutFlow for Signal MC ======== "<<endl ;
   select->PrintCutFlow() ;

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
     h_dataTimeAll->Write() ; 
     h_MET->Write() ;
     h_bgTime->Write() ;
     h_bgTimeA->Write() ;
     h_bgMET->Write() ;

     rh_dataTime->Write() ; 
     rh_dataTimeA->Write() ; 
     rh_dataTimeAll->Write() ; 
     //rh_MET->Write() ;
     rh_bgTime->Write() ;
     rh_bgTimeA->Write() ;
     //rh_bgMET->Write() ;
     //rh_NJets->Write() ;

     h_NJets->Write() ;

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
     h_sgTimeAll->Write() ;
     h_sgMET->Write() ;
     h_sgNJets->Write() ;

     rh_sgTime->Write() ;
     rh_sgTimeA->Write() ;
     rh_sgTimeAll->Write() ;
     //rh_sgMET->Write() ;
     //rh_sgNJets->Write() ;

}
