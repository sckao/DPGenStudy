#include "TestGen.h"

TestGen::TestGen( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  Hist   = new Histogram( datacardfile ) ;

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 
  Input->GetParameters("FitCtau",       &FitCtau) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("TimeCalib",     &timeCalib ) ;

  //if ( isData == 0 ) Input->GetParameters("DecayR",  &decayR ) ; 

  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  // initial histograms  
  Hist->Init( h ) ;
}

TestGen::~TestGen(){

  theFile->cd() ;
  Hist->Write( "", theFile ) ;
  cout<<" Output historams written ! "<<endl ;
  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete Input ;
  delete Hist ;
  cout<<" done ! "<<endl ;
}

// analysis template
void TestGen::ReadTree( string dataName, double weight ) { 

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

   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nElectrons",  &nElectrons);
   tr->SetBranchAddress("triggered",   &triggered);
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("totalNVtx",   &totalNVtx);
   
   tr->SetBranchAddress("nOutTimeHits", &nHaloHits ) ;
   tr->SetBranchAddress("nHaloTrack",   &nHaloTracks ) ;
   tr->SetBranchAddress("haloPhi",      &haloPhi ) ;
   tr->SetBranchAddress("haloRho",      &haloRho ) ;

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );
   tr->SetBranchAddress("muE",         muE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("seedTimeErr", seedTimeErr );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("aveTimeErr",  aveTimeErr );
   tr->SetBranchAddress("aveTimeErr1", aveTimeErr1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );
   tr->SetBranchAddress("sigmaEta",    sigmaEta );
   tr->SetBranchAddress("sigmaIeta",   sigmaIeta );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("dtdPhi",      dtdPhi );
   tr->SetBranchAddress("dtdEta",      dtdEta );

   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("cHadIso",     cHadIso );
   tr->SetBranchAddress("nHadIso",     nHadIso );
   tr->SetBranchAddress("photIso",     photIso );
   tr->SetBranchAddress("phoHoverE",   phoHoverE );

   tr->SetBranchAddress("maxSwissX",   maxSwissX );
   tr->SetBranchAddress("seedSwissX",  seedSwissX );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("nBC",         nBC );

   tr->SetBranchAddress("vtxX",       vtxX );
   tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genM",        genM );
   tr->SetBranchAddress("genVx",       genVx );
   tr->SetBranchAddress("genVy",       genVy );
   tr->SetBranchAddress("genVz",       genVz );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );

   // initialize selection
   select->Init( tr1 ) ;

   // Prepare a random number generator for gen Time smearing 
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;
 
   int nEvt = 0 ;
   int EscapedPhoton = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
    
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       //bool pass = select->SignalSelection();
       bool pass = select->ControlSelection();
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       recoPho.clear() ; // used for matching
       recoTs.clear() ;  // used for matching
       // MET information
       TLorentzVector met( metPx, metPy, 0, metE)  ;

       if ( pass ) {

          nEvt++; 
	  // multiplicity
	  h.h_nVtx->Fill(  totalNVtx , weight ) ;
	  h.h_nJets->Fill( selectJets.size() , weight ) ;
	  h.h_nPhotons->Fill( selectPho.size() , weight ) ;
	  h.h_nMuons->Fill( nMuons , weight ) ;
	  h.h_nElectrons->Fill( nElectrons , weight ) ;

	  h.h_met->Fill( met.Pt() , weight );

	  //cout<<" EVT# : "<< nEvt <<endl ;
	  TLorentzVector g1P4(0,0,0,0)  ;
	  double max_gPt  = 0 ;
	  for ( size_t kk =0; kk < selectPho.size() ; kk++) {
              int k = selectPho[kk].first ;
              
	      TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
              //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
              if ( gP4_.Pt() > max_gPt ) {
                 max_gPt = gP4_.Pt() ;
                 g1P4 = gP4_ ;
              } 

              // Define the Tag 
              bool haloTag  = ( cscdPhi[k] < 0.05 ) ? true : false  ;
             // if ( sMajPho[k] > 0.7 && cscdPhi[k] < 0.1  && fabs( gP4_.Eta() ) > 0.75 && fabs(gP4_.Eta()) < 1.47 ) haloTag = true;
             // if ( sMajPho[k] > 0.8 && sMajPho[k] < 1.65 && sMinPho[k] < 0.2 && fabs( gP4_.Eta() ) < 1.47 ) haloTag = true;

              bool spikeTag = ( nXtals[k] < 7 && !haloTag ) ? true : false  ;
              if ( sMajPho[k] < 0.6 && sMinPho[k] < 0.17 && fabs( gP4_.Eta() ) < 1.47 ) spikeTag = true;

              bool cosmicTag = ( dtdEta[k] < 0.1 && dtdPhi[k] < 0.1 && !haloTag ) ? true : false ;
              bool ghostTag = ( haloTag || spikeTag || cosmicTag ) ? true : false ;

              h.h_Eta->Fill( gP4_.Eta(), weight ) ;
              h.h_Pt_Eta->Fill( gP4_.Pt(), gP4_.Eta(), weight ) ;

              // collect good reco photons
	      recoPho.push_back( make_pair( k , gP4_) );
	      recoTs.push_back( seedTime[k] );

	      if ( fabs( gP4_.Eta()) <= 1.479 ) h.h_maxSwissEB->Fill( maxSwissX[k] , weight );
	      if ( fabs( gP4_.Eta())  > 1.479 ) h.h_maxSwissEE->Fill( maxSwissX[k] , weight );
	      h.h_sMin->Fill( sMinPho[k] , weight ) ;

	      //if ( maxSwissX[k] > 0.95 ) continue ;
	      h.h_seedSwiss->Fill( seedSwissX[k] , weight );
	      h.h_nXtals->Fill( nXtals[k] , weight ) ;
	      if ( nXtals[k] < 3 ) continue ;

	      h.obsTime->Fill( seedTime[k], weight );

	      h.aveObsTime->Fill( aveTime[k], weight );

	      if ( timeChi2[k] < 5 )  h.aveObsTime1->Fill( aveTime1[k] , weight );
	      if ( timeChi2[k] < 5 )  h.aveObsTime2->Fill( seedTime[k] , weight );

              h.seedTime_Chi2->Fill( seedTime[k], timeChi2[k] , weight ) ;
	      h.h_nChi2->Fill( timeChi2[k] , weight ) ;
	      h.h_nBC->Fill( nBC[k] , weight ) ;
              // Detector Isolation properties          
	      h.h_TrkIsoR->Fill( phoTrkIso[k] / gP4_.Pt() , weight );
	      h.h_EcalIsoR->Fill( phoEcalIso[k] / gP4_.E() , weight );
	      h.h_HcalIsoR->Fill( phoHcalIso[k] / gP4_.E() , weight );
              // PF Iso 
              h.h_HoverE->Fill( phoHoverE[k] , weight ) ;
	      h.h_sigIeta->Fill( sigmaIeta[k] , weight ) ;
	      double nHIso = max( nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ; 
	      double phIso = max( photIso[k] - (0.005*gP4_.Pt()) , 0. ) ; 
	      h.h_cHadIso->Fill( cHadIso[k] , weight ) ;
	      h.h_nHadIso->Fill( nHIso , weight ) ;
	      h.h_photIso->Fill( phIso , weight ) ;
	      h.h_cHadIso_t->Fill( cHadIso[k] , seedTime[k] , weight ) ;
	      h.h_nHadIso_t->Fill( nHIso , seedTime[k] , weight ) ;
	      h.h_photIso_t->Fill( phIso , seedTime[k] , weight ) ;

              // Time correlations
              h.h_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
              h.h_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
              h.h_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
              h.h_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
	      h.h_sigIeta_Time->Fill( sigmaIeta[k], seedTime[k] , weight  ) ;
              h.h_cscdPhi_Time->Fill( cscdPhi[k], seedTime[k] , weight  ) ;
              h.h_Pt_Time->Fill( gP4_.Pt() , seedTime[k] , weight );


              // Using CMSSW CSC Halo Tagging
              if ( nHaloTracks > 0  && haloRho > 0 ) {
                 h.h_RhoPhi_Halo->Fill( haloPhi, haloRho , weight ) ;
                 h.h_nHaloTracks->Fill( nHaloTracks , weight ) ;
                 h.h_nHaloHits->Fill( nHaloHits , weight ) ;
                 //double dphi = fabs( haloPhi - gP4_.Phi() ) ;
                 //dphi = ( dphi > 3.1416 ) ? 6.2832 - dphi : dphi ;
                 //double drho = fabs( haloRho - gP4_.Rho() ) ;
              }

              // Check the efficiency 
	      if ( ghostTag ) h.ghostTime->Fill( seedTime[k], weight );
              else h.pureTime->Fill( seedTime[k], weight );

              // simulate the EE photon
              if ( fabs(seedTime[k]) < 2. ) {

                 for ( int g=-4; g < 5; g++ ) {
                     if ( g == 0 ) continue ;

		     double zS = 75.0 * g ;
		     double tS = 2.5*abs(g) ;
		     double theTime = 0;
		     double pos[3] = { vtxX[0], vtxY[0], vtxZ[0]+ zS };
		     bool hasEcalTime = Propagator( gP4_, pos[0], pos[1], pos[2], theTime ) ;
		     double mag = sqrt( pos[0]*pos[0]+ pos[1]*pos[1] + pos[2]*pos[2] ) ;
		     double t0 = mag / 30. ;
              
		     double theTimeP = tRan->Gaus( (theTime + tS - t0) , timeCalib[1] ) - timeCalib[0] ;
                     double theTimeN = tRan->Gaus( (theTime - tS - t0) , timeCalib[1] ) - timeCalib[0] ;

		     //double vtx0[4] = { vtxX[k], vtxY[k], vtxZ[k], 0 };
		     //Propagator( gP4_, vtx0[0], vtx0[1], vtx0[2], vtx0[3] ) ;
		     //theTime = theTime - vtx0[3] ;
		     TLorentzVector GhP4( pos[0], pos[1], pos[2], mag ) ;
                     double scale = gP4_.P() / mag ;
                     GhP4 = GhP4 * scale ;
                     if ( GhP4.Pt() < photonCuts[8] ) continue ;

		     h.Gh_Eta_Time->Fill( GhP4.Eta(),  theTimeP, weight ) ;
		     h.Gh_Eta_Time->Fill( GhP4.Eta(),  theTimeN, weight ) ;
		 }
              }

              if ( fabs( gP4_.Eta() ) >  1.6 ) {
                 double theTime = 0;
		 double pos[3] = { vtxX[0], vtxY[0], vtxZ[0] };
		 Propagator( gP4_, pos[0], pos[1], pos[2], theTime ) ;
		 double mag = sqrt( pos[0]*pos[0]+ pos[1]*pos[1] + pos[2]*pos[2] ) ;
		 double rho = sqrt( pos[0]*pos[0]+ pos[1]*pos[1] ) ;
		 double t0 = mag / 30. ;
                 theTime = theTime - t0 ;
                
                 h.Gh_rho_Time->Fill( rho, seedTime[k] ) ;
                 h.Gh_rho_dT->Fill( rho, seedTime[k] -theTime ) ;
                 if ( fabs( seedTime[k] ) > 3.  ) h.Gh_Phi_Time->Fill( gP4_.Phi(), seedTime[k] ) ;
              }
              if ( fabs( gP4_.Phi() ) >  0.2 && fabs( gP4_.Phi() ) < 3.12 && !haloTag ) {
                 h.Gh_Eta_Time1->Fill( gP4_.Eta() , seedTime[k] ) ;
              }


          }
          h.h_g1Pt->Fill( max_gPt , weight );
       }

       // look up gen information for signal MC  
       if ( isData == 1 ) continue ;

       genPho.clear() ; // used for matching
       genTs.clear() ;  // used for matching
       genXTs.clear() ;  // used for matching
       genPs.clear() ;  // used for matching
       double maxGenPt = 0. ;
       int nGenPho = 0;
       double genMETP4[4] = {0,0,0,0};
       bool hasGravitino = false ;
       //printf("======================== \n") ;
 
       for ( int k=0; k< nGen ; k++) {

           if ( pdgId[k] == 1000039 ) {
                genMETP4[0] += genPx[k] ;
                genMETP4[1] += genPy[k] ;
                genMETP4[2] += genPz[k] ;
                genMETP4[3] += genE[k] ;
                hasGravitino = true ;
           }

           if ( pdgId[k] != 22 ) continue ;
           TLorentzVector gP4 = TLorentzVector( genPx[k], genPy[k], genPz[k], genE[k] ) ;
           
           int mId = momId[k]  ;
           if ( mId < 0  ) continue ;
           TLorentzVector xP4 = TLorentzVector( genPx[mId], genPy[mId], genPz[mId], genE[mId] ) ;
           //printf(" phot[%d] p4( %.1f,%.1f,%.1f,%.1f) genT:%.3f \n", k, genPx[k], genPy[k], genPz[k], genE[k], genT[mId] ) ;

           if ( gP4.Pt() > maxGenPt ) maxGenPt = gP4.Pt() ;
           nGenPho++ ;

           double EcalTime = genT[mId] ;  // tau*gamma
 
           double vx = genVx[k] ;
           double vy = genVy[k] ;
           double vz = genVz[k] ;
           //double vrho = sqrt( (vx*vx) + (vy*vy) ) ;
           //printf("         v4( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           bool hasEcalTime = Propagator( gP4, vx, vy, vz, EcalTime ) ;
           if ( !hasEcalTime ) continue ;

           //vrho = sqrt( (vx*vx) + (vy*vy) ) ;
           //printf("           ( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           double d_x = vx - vtxX[0] ;
           double d_y = vy - vtxY[0] ;
           double d_z = vz - vtxZ[0] ;
           double d_r = sqrt( (d_x*d_x) + (d_y*d_y) + (d_z*d_z) ); 
           double t0  = d_r /30. ; // t0 -> ecaltime assuming photon is from original
          
           // This is the measured time for gen photons
           double dT = EcalTime  - t0 ; 

           h.Time_R->Fill( dT, sqrt( (genVx[k]*genVx[k]) + ( genVy[k]*genVy[k]) ) , weight );
           h.Time_Z->Fill( dT, fabs( genVz[k] ) , weight );

           // build the P4 for gen photon from reconstruction point of view 
           // skip the escaped photon 
           TLorentzVector genRecoP4 = TLorentzVector( d_x, d_y, d_z, d_r ) ;
           genRecoP4 = genRecoP4 * ( gP4.E() / d_r ) ;
           //printf("    ---> p4( %.1f,%.1f,%.1f,%.1f) recoT:%.3f , dT: %.3f \n", 
           //                    genRecoP4.Px(),genRecoP4.Py(),genRecoP4.Pz(),genRecoP4.E(), t0, dT ) ;

           genPho.push_back( make_pair( k, genRecoP4 ) ) ;
	   genTs.push_back( dT ) ;
	   genXTs.push_back( genT[mId]*300. / xP4.Gamma()  ) ;
	   genPs.push_back( gP4 ) ;
              /*
              if ( dT > 6. ) {
                 printf(" === Gen  Time: %f, GenPt: %.1f, RecoPt: %.1f, RecoEta: %.2f, vx: %.2f, vy: %.2f, vz: %.2f  \n", 
                              dT, gP4.Pt(), genRecoP4.Pt(), genRecoP4.Eta(), genVx[k], genVy[k], genVz[k] ) ;
                 for ( int j=0; j< nPhotons; j++) {
                     TLorentzVector gP4_ = TLorentzVector( phoPx[j], phoPy[j], phoPz[j], phoE[j] ) ;
                     printf(" (%d) SeedT: %f,  Pt: %.1f, Eta: %.2f,  sMin: %.2f, dR_trk: %.2f, seedSwissX: %.2f \n",
                            j, seedTime[j], gP4_.Pt(), gP4_.Eta(), sMinPho[j], dR_TrkPho[j], seedSwissX[j] ) ;
                 }
                 cout<<" --------------------------------------- "<<endl ;
              }
              */
           /*
           if ( dT < 0 && dT > -3 ) {
              cout<<"  Neutralino :  genVx:"<< genVx[mId] << " genVy:"<< genVy[mId] << " genVz:"<< genVz[mId] ;
              cout<<"  beta:"<< xP4.Beta()  <<endl;
              cout<<"      Photon :  genVx:"<< genVx[k] << "  genVy:"<< genVy[k] << "  genVz:"<< genVz[k] <<endl;
              cout<<"         FinalEcal Vx:"<< vx <<"     Vy:"<< vy <<"    Vz:"<< vz <<endl;
              cout<<" LifeTime : "<< genT[k] / xP4.Beta() << "  EcalTime :"<< EcalTime<<"  T0:"<< t0 <<endl ; 
           }
           */        
    
           h.h_Time->Fill( dT ) ;
          
           if ( dT > -3.999999 ) EscapedPhoton++ ;
           h.h_ctau->Fill( genT[mId]*300. / xP4.Gamma() ) ;
           h.h_xbeta->Fill( xP4.Beta() ) ;
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       }

       if ( hasGravitino ) {
          TLorentzVector G_P4 = TLorentzVector( genMETP4[0], genMETP4[1], genMETP4[2], genMETP4[3] ) ;
	  h.h_genMET->Fill( G_P4.Pt() ) ;
	  h.h_METRes->Fill( G_P4.Pt() - metE ) ;
	  h.h_METdPhi->Fill( fabs( G_P4.DeltaPhi( met ) ) ) ;
       }

       // check gen photon characters 
       double maxGen_RecoPt = 0 ;
       int    nGoodGenPho = 0 ;
       for ( size_t j = 0 ; j < genPho.size() ; j++ ) { 
           maxGen_RecoPt = ( genPho[j].second.Pt() > maxGen_RecoPt ) ? genPho[j].second.Pt() : maxGen_RecoPt ;
           bool pass1 = ( genPho[j].second.Pt() > photonCuts[0] && fabs(genPho[j].second.Eta()) < photonCuts[1]  ) ;
           //if  ( !pass1 && (photonCuts[0] - genPho[j].second.Pt())  < 15. ) pass1 = true ;
           bool pass2 = true ;
           for ( size_t m =0; m< selectJets.size() ; m++ ) {
               double dR_ = selectJets[m].second.DeltaR( genPho[j].second ) ;
               if ( dR_ < jetCuts[5] ) pass2 = false ;
           }
           if ( pass1 && pass2 ) nGoodGenPho++ ;
       }

       bool genPass =  ( nGoodGenPho > 0 && maxGen_RecoPt >= photonCuts[8] ) ? true : false ;
       if ( genPass )  {
          h.h_gen1RecoPt->Fill( maxGen_RecoPt ) ;
          for ( size_t j=0; j< genTs.size() ; j++ ) {
              // the smearing according to reconstruction resolution
              double genT_corr = tRan->Gaus( genTs[j] , timeCalib[1] ) - timeCalib[0] ;
              h.h_genTime->Fill( genT_corr, weight ) ;
          } 
       }       

       h.h_gen1Pt->Fill( maxGenPt ) ;
       h.h_nGenPhotons->Fill( nGenPho ) ;

       // * Matching Process  *
       vector<iMatch> mlist = GlobalDRMatch( recoPho, genPho );
       for ( size_t k=0; k< mlist.size(); k++ ) {
           if ( mlist[k].dr > 0.5 ) continue ;
           double recoTime  = seedTime[ mlist[k].ir ] ;
           double recoTime1 = aveTime1[ mlist[k].ir ] ;
           double genTime  = genTs[ mlist[k].idg ] ;

           if ( genTime > 2. ) {
              h.m_sigIeta_time->Fill( sigmaIeta[mlist[k].ir], recoTime );
	      h.m_sMaj_time->Fill( sMajPho[mlist[k].ir], recoTime );
	      h.m_sMin_time->Fill( sMinPho[mlist[k].ir], recoTime );
	      h.m_sMaj_sMin->Fill( sMajPho[mlist[k].ir], sMinPho[mlist[k].ir] );
	      h.m_cHadIso_time->Fill( cHadIso[mlist[k].ir], recoTime );
	      h.m_nHadIso_time->Fill( nHadIso[mlist[k].ir], recoTime );
	      h.m_photIso_time->Fill( photIso[mlist[k].ir], recoTime );
           }

           if ( fabs(mlist[k].dPt) > 0.25 ) continue ;
           h.h_matchRecoTime->Fill( recoTime ) ;
           h.h_matchGenTime->Fill( genTime ) ;
           if ( fabs( recoTime - genTime + timeCalib[0] ) < 1. ) h.h_matchTime->Fill( genTime ) ;
           if ( genTime < 2                 ) h.h_TimeRes1->Fill( recoTime - genTime ) ;
           if ( genTime >=2  && genTime < 5 ) h.h_TimeRes2->Fill( recoTime - genTime ) ;
           if ( genTime >=5                 ) h.h_TimeRes3->Fill( recoTime - genTime ) ;
           if ( genTime < 2                 ) h.h_aTimeRes1->Fill( recoTime1 - genTime ) ;
           if ( genTime >=2  && genTime < 5 ) h.h_aTimeRes2->Fill( recoTime1 - genTime ) ;
           if ( genTime >=5                 ) h.h_aTimeRes3->Fill( recoTime1 - genTime ) ;
           h.h_PtRes->Fill( mlist[k].dPt ) ;

           if ( genTime > 3. ) h.dR_GenReco->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) ) ;
           h.dR_Time->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , genTime ) ;
           h.dR_sMaj->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , sMajPho[mlist[k].ir] ) ;
           h.dR_sMin->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , sMinPho[mlist[k].ir] ) ;
           h.dR_photIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , photIso[mlist[k].ir] ) ;
           h.dR_nHadIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , nHadIso[mlist[k].ir] ) ;
           h.dR_cHadIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , cHadIso[mlist[k].ir] ) ;
           h.dR_sigIeta->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , sigmaIeta[mlist[k].ir] ) ;
           h.dR_XTime->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) ,  genXTs[mlist[k].idg]  ) ;
           h.XTime_genTime->Fill( genXTs[mlist[k].idg] , genTime);
           h.sMaj_sMin->Fill( sMajPho[mlist[k].ir] , sMinPho[mlist[k].ir] ) ;

       }
       //for ( size_t k=0; k< mlist.size() ; k++ ) printf(" (%d) , dr: %f dPt: %f \n", (int)k , mlist[k].dr, mlist[k].dPt ) ;

   } // end of event looping

   select->PrintCutFlow() ;
   cout<<" EscapedPhoton = "<< EscapedPhoton << endl ;

}  

// propagator with backward propagation
// ECal Dimension : R:( 129 ~ 155 cm , Z : 317 ~345 )
bool TestGen::Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double taugamma ) {

    bool hasEcalTime = true ;

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;

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
       }

    } while ( alived ) ;

    //printf( " .... N_Steps : %d , ( %4.2f %4.2f %4.2f )  \n", i, x, y, z ) ;
    return hasEcalTime ;
}

// simple propagator without backward propagation -- propagator for neutralino
bool TestGen::Propagator1( TLorentzVector v, double& x, double& y, double& z, double& t, double taugamma ) {

    double bx = v.Px() / v.E() ;
    double by = v.Py() / v.E() ;
    double bz = v.Pz() / v.E() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );

    bool insideEcal = ( r < 155. && fabs(z) < 341. ) ? true : false ;
    
    if ( !insideEcal ) {
       t = -25. ;
       //cout<<" r = "<< r <<" z : "<< z << endl;
       return insideEcal ;
    }

    bool alived   = true ;
    int i = 0 ;
    do {
       i++ ; 
       t = t + dt ;
       x = x + (bx*dt*30) ;
       y = y + (by*dt*30) ;
       z = z + (bz*dt*30) ;
       r = sqrt( (x*x) + (y*y ) ) ;

       alived     = ( t < ( taugamma )     ) ? true : false ;
       insideEcal = ( r < 155 && fabs(z) < 341 ) ? true : false ; // outer edge of ECAL


    } while ( insideEcal && alived ) ;

    return insideEcal ;
}


// return the matched list for the 2nd vector, vg
vector<iMatch> TestGen::GlobalDRMatch( vector<objID> vr, vector<objID> vg ) {

    vector<int> pool ;
    for (size_t i=0; i < vg.size(); i++) pool.push_back(i) ;
    //printf(" size of vr : %d and vg : %d \n", (int)vr.size(), (int)vg.size() ) ;
    if ( vr.size() > vg.size() ) {
       for ( size_t i=0 ; i< vr.size() - vg.size() ; i++ ) pool.push_back( -1 ) ;
    }
    //cout<<" pool size = "<< pool.size() <<endl ;

    vector<iMatch> vMatch ;
    vector<iMatch> vMatch0 ;
    iMatch iM0 ;
    double minDR = 999. ; 
    do {

        double dr2 = 0 ;
        vMatch0.clear() ;
        //cout<<" ( " ;
        for ( size_t j=0; j< vr.size() ; j++ ) {
            if ( pool[j] == -1 ) continue ;
            double dr_ = vr[j].second.DeltaR( vg[ pool[j] ].second ) ;
            iM0.idg  = pool[j] ;
            iM0.idr  = j ;
            iM0.ig  = vg[ pool[j] ].first ;
            iM0.ir  = vr[ j ].first ;
            iM0.dr  = dr_ ;
            iM0.dPt = ( vr[j].second.Pt() - vg[ pool[j] ].second.Pt() ) / vg[ pool[j] ].second.Pt()  ;
            vMatch0.push_back( iM0 ) ;
            dr2 += (dr_*dr_) ;
            //cout<< j <<", " ;
        }
        double dr = ( vMatch0.size() > 0. ) ? sqrt( dr2 ) : 999. ;
        //cout<<" ) , dR = "<< dr << endl ;

        if ( dr < minDR ) {
             minDR = dr ;
             vMatch = vMatch0 ;
        }

    } while (  next_permutation( pool.begin() ,pool.end() ) ) ;
 
    // Debug matching process 
    /*
    if ( vMatch.size() > 0 ) printf(" ======= min_dR: %.2f =======\n", minDR );
    for ( size_t i=0; i< vMatch.size(); i++ ) {
        printf("    dR(%d - %d) = %.3f , dPt = %.2f \n", vMatch[i].ig , vMatch[i].ir , vMatch[i].dr , vMatch[i].dPt ); 
    }
    */

    return vMatch ;
}

