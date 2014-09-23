#include "TestGen.h"

static bool PtDecreasing( objID s1, objID s2) { return ( s1.second.Pt() > s2.second.Pt() ); }

TestGen::TestGen( string datacardfile ) {

  Input = AnaInput::Instance() ;
  select = new DPSelection( datacardfile ) ;
  Hist   = new Histogram( ) ;

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
  //delete Input ;
  delete Hist ;
  cout<<" done ! "<<endl ;
}

// analysis template
void TestGen::ReadTree( string dataName, double weight ) { 

   string dataFileNames ;
   if ( dataName.size() < 2 ) {
      dataFileNames = dataName ;   
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   printf(" Data File Names : %s \n", dataFileNames.c_str() ) ;
   

   TTree* tr   = Input->GetTree( dataFileNames, "DPAnalysis" );
   cout<<" Get the tree ! "<<endl ;

   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nElectrons",  &nElectrons);
   tr->SetBranchAddress("triggered",   &triggered);
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("totalNVtx",   &totalNVtx);
   
   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("seedTimeErr", seedTimeErr );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
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

   tr->SetBranchAddress("seedSwissX",  seedSwissX );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("nBC",         nBC );

   //tr->SetBranchAddress("vtxX",       vtxX );
   //tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   
   tr->SetBranchAddress("nGen",        &nGen);
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
   // initialize selection
   select->Init( tr1 ) ;
   
   // Prepare a random number generator for gen Time smearing 
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;
 
   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   int nPass = 0 ;
   int nPassPhot = 0 ;
   int nPassGen  = 0 ;
   int nPassGenPhot = 0 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
       nEvt++; 
    
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;

       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       uint32_t evtType = select->EventIdentification();
       bool pass     = ( (evtType >> 0) & 1  ) ;
       bool pass_hlt = ( (evtType >> 5) & 1  ) ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       recoPho.clear() ; // used for matching

       // MET information
       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;
       bool passMET = newMET.E() > jetCuts[4] && noPhotMET.E() > jetCuts[4]  ;
       TLorentzVector met( metPx, metPy, 0, metE)  ;

       // raw multiplicity information
       h.h_nVtx->Fill(  totalNVtx , weight ) ;
       h.h_nJets->Fill( selectJets.size() , weight ) ;
       h.h_nPhotons->Fill( nPhotons , weight ) ;
       h.h_nMuons->Fill( nMuons , weight ) ;
       h.h_nElectrons->Fill( nElectrons , weight ) ;
       h.h_met->Fill( met.Pt() , weight );

       // use for efficiency estimation
       if ( pass_hlt ) {
          TLorentzVector gP4 = TLorentzVector( phoPx[0], phoPy[0], phoPz[0], phoE[0] ) ;
          h.h_Eta->Fill( gP4.Eta(), weight ) ;
          h.h_g1Pt->Fill( gP4.Pt() , weight );
          h.h_Pt_Eta->Fill( gP4.Pt(), gP4.Eta(), weight ) ;
       }

       // collect reco photons for matching
       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
           int k = selectPho[kk].first ;
	   TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
	   recoPho.push_back( make_pair( k , gP4_) );
       }

       int nNonGhost = (int)selectPho.size() ;
       bool eventPass = false ;
       if ( pass && pass_hlt ) {

	  double max_gPt  = 0 ;
	  for ( size_t kk =0; kk < selectPho.size() ; kk++) {
              int k = selectPho[kk].first ;
              
	      TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
              //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
              if ( gP4_.Pt() > max_gPt )   max_gPt = gP4_.Pt() ;
              
	      // Background Tagging
	      bool haloTag   = select->HaloTag( cscdPhi[k] , sMajPho[k] , sMinPho[k] , gP4_.Eta() ) ;
	      bool spikeTag  = select->SpikeTag( nXtals[k] , sMajPho[k] , sMinPho[k], seedSwissX[k], gP4_.Eta() ) ;
	      bool cosmicTag = select->CosmicTag( dtdEta[k] , dtdPhi[k] ) ;
	      bool ghostTag  = ( haloTag || spikeTag || cosmicTag ) ? true : false ;
              if ( ghostTag ) nNonGhost-- ;

              if ( passMET && seedTime[k] > 3. && seedTime[k] < 15. ) {
                 if ( !eventPass ) nPass++ ;
                 eventPass = true ;
                 nPassPhot++ ;
              }

              // collect good reco photons

	      h.h_sMin->Fill( sMinPho[k] , weight ) ;

	      h.h_seedSwiss->Fill( seedSwissX[k] , weight );
	      h.h_nXtals->Fill( nXtals[k] , weight ) ;

	      if ( passMET && !ghostTag ) h.obsTime->Fill( seedTime[k], weight );
	      if ( passMET && !ghostTag ) h.aveObsTime->Fill( aveTime[k], weight );

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
              h.h_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k], weight ) ;
	      if ( seedTime[k]  > 3. ) { 
                 h.h_sMaj_sMin_late->Fill( sMajPho[k] , sMinPho[k], weight ) ;
                 h.h_photIso_nXtl->Fill( phIso , nXtals[k] , weight ) ;
                 h.h_photIso_nBC->Fill( phIso ,  nBC[k] , weight ) ;
              }
              
              // Time correlations
              h.h_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
              h.h_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
              h.h_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
              h.h_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
	      h.h_sigIeta_Time->Fill( sigmaIeta[k], seedTime[k] , weight  ) ;
              h.h_cscdPhi_Time->Fill( cscdPhi[k], seedTime[k] , weight  ) ;
              h.h_Pt_Time->Fill( gP4_.Pt() , seedTime[k] , weight );

              // Check the efficiency 
	      if ( ghostTag ) h.ghostTime->Fill( seedTime[k], weight );
              else h.pureTime->Fill( seedTime[k], weight );

              // simulate the off-time QCD photon
              if ( fabs(seedTime[k]) < 2. ) {

                 for ( int g=-4; g < 5; g++ ) {
                     if ( g == 0 ) continue ;

		     double zS = 75.0 * g ;
		     double tS = 2.5*abs(g) ;
		     double theTime = 0;
		     //double pos[3] = { vtxX[0], vtxY[0], vtxZ[0]+ zS };
		     double pos[3] = { 0, 0, zS };
		     Propagator( gP4_, pos[0], pos[1], pos[2], theTime ) ;
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
              if ( fabs( gP4_.Phi() ) >  0.2 && fabs( gP4_.Phi() ) < 3.12 && !haloTag ) {
                 h.Gh_Eta_Time1->Fill( gP4_.Eta() , seedTime[k] ) ;
              }

          }
       }

       // look up gen information for signal MC  
       if ( isData == 1 ) continue ;

       genPho.clear() ;  // used for matching
       genTs.clear() ;   // used for matching
       genXTs.clear() ;  // used for matching
       genPs.clear() ;   // used for matching
       genXPs.clear() ;  // used for matching
       v_ctbgTs.clear();
       double maxGenPt = 0. ;
       int    nGenPho = 0;
       double genMETP4[4] = {0,0,0,0};
       bool   hasGravitino = false ;
 
       // Find the real photon from neutralino decay
       //printf(" nGen : %d \n", nGen ) ;
       eventPass = false ;
       int nX0(0), nX0_g(0), nX0_gb(0) ;
       for ( int k=0; k< nGen ; k++) {
           // printf("===========%d============ \n", k ) ;
           // Check BR
           if ( pdgId[k] == 1000022 ) nX0++ ;

           // check MET from gravitino
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

           nGenPho++ ;
           double vx = genVx[k] ;
           double vy = genVy[k] ;
           double vz = genVz[k] ;
           double ctbg  = sqrt( (vx*vx) + (vy*vy) + (vz*vz) ) ;
           double ctbgT = sqrt( (vx*vx) + (vy*vy)  ) ;
           double EcalTime = genT[mId] ;  // tau*gamma
           double vz0 = vz ;

           // time delay from slowness of neutralino 
           // has to be placed before Propagator
           double t1_c = ctbg / 30. ;
           double dt1  = EcalTime - t1_c ;   

           if ( fabs(vz) < 317. ) h.h_ctbgT->Fill( ctbgT*10. ) ;
           h.h_ctbg->Fill( ctbg*10. ) ;
           h.h_ctau->Fill( genT[mId]*300. / xP4.Gamma() ) ; // ctau in mm -> c = 300 mm / ns

           //double vrho = sqrt( (vx*vx) + (vy*vy) ) ;
           //printf("         v4( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           h.ctbg_RZ1->Fill( vz0, ctbgT ) ; // where the neutralino decay
           // **********************************************************
           //  Main propagator - to make sure decay photon will hit ECAL
           // **********************************************************
           bool hasEcalTime = Propagator( gP4, vx, vy, vz, EcalTime ) ;
           if ( !hasEcalTime ) continue ;

           h.ctbg_RZ0->Fill( vz0, ctbgT ) ;  // for those neutralino who are seen by ECAL

           // Construct 4 vector for generated photon
           // vrho = sqrt( (vx*vx) + (vy*vy) ) ;
           // printf("           ( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           double d_x = vx - 0. ;
           double d_y = vy - 0. ;
           double d_z = vz - vtxZ[0] ;
           double d_r = sqrt( (d_x*d_x) + (d_y*d_y) + (d_z*d_z) ); 
           double t0  = d_r /30. ; // t0 -> ecaltime assuming photon is from original
           // This is the measured ECAL time for gen photons including smearing
           double dT = tRan->Gaus( EcalTime - t0 , 0.354 ) - 0.162 ;

           // Build the P4 for gen photon from reconstruction point of view 
           TLorentzVector genRecoP4 = TLorentzVector( d_x, d_y, d_z, d_r ) ;
           genRecoP4 = genRecoP4 * ( gP4.E() / d_r ) ;
           if ( genRecoP4.Pt() > maxGenPt ) maxGenPt = genRecoP4.Pt() ;

           if ( genRecoP4.Pt() > 45. && fabs(genRecoP4.Eta()) < 1.46 ) nX0_gb++ ;

           if ( dT > 3. ) h.late_ctbgT->Fill( ctbgT*10. ) ;

           if (genRecoP4.Pt() > 1. && fabs( genRecoP4.Eta()) < 1.47 ) {
              h.reco_ctbgT->Fill( ctbgT*10. ) ;
              h.reco_xbeta->Fill( xP4.Beta() ) ;
              h.reco_xPt->Fill( xP4.Pt() ) ;
              h.reco_gPt->Fill( genRecoP4.Pt() ) ;
              h.h_Time->Fill( dT ) ;

              double ctT = ( ctbgT*10./(xP4.Beta()*xP4.Gamma()) >= 4000. ) ? 3999. : ctbgT*10./(xP4.Beta()*xP4.Gamma()) ;
              h.reco_xPt_ctbgT->Fill( xP4.Pt(), ctT ) ;
              h.simTime->Fill( dT , Input->RecoWeight( xP4.Pt() , ctbgT*10./(xP4.Beta()*xP4.Gamma()) ) ) ;
              if ( dT > 3. ) h.lateR_ctbgT->Fill( ctbgT*10. ) ;
           }

           // Collections for matching
           genPho.push_back( make_pair( k, genRecoP4 ) ) ;
	   genTs.push_back( dT ) ;
	   genXTs.push_back( genT[mId]*300. / xP4.Gamma()  ) ;
	   genPs.push_back( gP4 ) ;
	   genXPs.push_back( xP4 ) ;
           v_ctbgTs.push_back( ctbgT*10. );

           // Find any nearby reco photon
           bool found_Reco = false ;
           double match_recoTime = -5. ;
	   for ( size_t kk =0; kk < selectPho.size() ; kk++) {
	       TLorentzVector rP4 = selectPho[kk].second ;
               int kj = selectPho[kk].first ;
               double dR_gR = rP4.DeltaR( genRecoP4 ) ;
               if ( dR_gR < 0.3 ) {
                  found_Reco = true ;
                  match_recoTime = seedTime[ kj ] ;
               }
           }

           h.obs_ctbgT->Fill( ctbgT*10. ) ;
           if ( ctbgT  < 30. )                 h.xPhot_pt1->Fill( gP4.Pt() ) ;
           if ( ctbgT >= 30. && ctbgT < 60. )  h.xPhot_pt2->Fill( gP4.Pt() ) ;
           if ( ctbgT >= 60. && ctbgT < 90. )  h.xPhot_pt3->Fill( gP4.Pt() ) ;
           if ( ctbgT >= 90. )                 h.xPhot_pt4->Fill( gP4.Pt() ) ;

           // Check the source of time delay
           double t2_c = EcalTime - genT[mId] ;
           double t3_c = sqrt( (vx*vx) + (vy*vy) + (vz*vz) ) / 30. ;
           double dt2 = t1_c + t2_c - t3_c ;  // time delay from deviation of photon path
           h.dt1_dt2->Fill( dt1, dt2 ) ;
           if ( dT > 3. ) h.dt1_dt2_late->Fill( dt1, dt2 ) ;

           if ( pass && pass_hlt && nNonGhost > 0 && passMET && found_Reco ) {
              h.sel_ctbg->Fill(  ctbg*10. ) ;
	      h.sel_ctbgT->Fill( ctbgT*10. ) ;
	      h.sel_ctau->Fill( genT[mId]*300. / xP4.Gamma() ) ;
	      h.h_genTime->Fill( dT ) ;
	      h.sel_xbeta->Fill( xP4.Beta() ) ;
	      h.sel_xPt->Fill( xP4.Pt() ) ;
	      h.sel_gPt->Fill( genRecoP4.Pt() ) ;
              double ctT = ( ctbgT*10./(xP4.Beta()*xP4.Gamma()) >= 4000. ) ? 3999. : ctbgT*10./(xP4.Beta()*xP4.Gamma()) ;
              if ( match_recoTime > 3. )   h.sel_xPt_ctbgT->Fill( xP4.Pt(), ctT ) ;
           }

           double dPt = genRecoP4.Pt() - gP4.Pt() ;
           h.ctbgT_dPt->Fill( ctbgT*10, dPt ) ;

	   h.h_gPt_time->Fill( genRecoP4.Pt(), dT ) ;
           h.h_xbeta->Fill( xP4.Beta() ) ;
           h.h_XPt->Fill( xP4.Pt() ) ;
           if ( dT > 3. && found_Reco ) {
              h.h_lateXbeta->Fill( xP4.Beta() ) ;
              h.h_lateXctau->Fill( genT[mId]*300. / xP4.Gamma() ) ;
	      h.h_lateXPt->Fill( xP4.Pt() ) ;

	      if (  pass && pass_hlt && nNonGhost > 0 && passMET ) h.acc_ctbgT->Fill( ctbgT*10. ) ;
	      if (  pass && pass_hlt && nNonGhost > 0 && passMET ) h.acc_ctbg->Fill( ctbg*10. ) ;
	      if (  pass && pass_hlt && nNonGhost > 0 && passMET ) h.acc_ctau->Fill( genT[mId]*300. / xP4.Gamma() ) ;
              if (  pass && pass_hlt && nNonGhost > 0 && passMET ) {
                 if ( !eventPass ) nPassGen++ ;
                 eventPass = true ;
                 nPassGenPhot++ ;
              }
           }
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       } 
       // End of gen particle loop

       h.h_XBR->Fill( nX0, nX0_g ) ;
       // Check missing Et w.r.t to two Grabitino pt sum
       if ( hasGravitino ) {
          TLorentzVector G_P4 = TLorentzVector( genMETP4[0], genMETP4[1], genMETP4[2], genMETP4[3] ) ;
	  h.h_genMET->Fill( G_P4.Pt() ) ;
	  h.h_METRes->Fill( G_P4.Pt() - metE ) ;
	  h.h_METdPhi->Fill( fabs( G_P4.DeltaPhi( met ) ) ) ;
       }

       // sort the gen photon collection
       if ( genPho.size() > 0 && maxGenPt > 0. )  h.h_gen1RecoPt->Fill( maxGenPt ) ;
       h.h_nGenPhotons->Fill( nGenPho ) ;

       // *********************
       // * Matching Process  *
       // *********************
       vector<iMatch> mlist = GlobalDRMatch( recoPho, genPho );
       int m_gen(0) ;
       for ( size_t k=0; k< mlist.size(); k++ ) {
           h.dR_GenReco->Fill( mlist[k].dr ) ;
           if ( mlist[k].dr > 0.5 ) continue ;
           m_gen++ ;
           double recoTime = seedTime[ mlist[k].ir ] ;
           double genTime  = genTs[ mlist[k].idg ] ;

           TLorentzVector m_rp4 = TLorentzVector( phoPx[mlist[k].ir], phoPy[mlist[k].ir], phoPz[mlist[k].ir], phoE[mlist[k].ir] ) ;
           TLorentzVector m_gp4 = genPho[ mlist[k].idg ].second ;
           h.m_RecoPt->Fill( m_rp4.Pt() ) ;
           h.m_GenPt->Fill( m_gp4.Pt() ) ;
           h.h_matchRecoTime->Fill( recoTime ) ;
           h.h_matchGenTime->Fill( genTime ) ;
           /*
           TLorentzVector xP4 = genXPs[mlist[k].idg] ;
           if ( m_gp4.Pt() >  1. && fabs(m_gp4.Eta()) < 1.47) {
              h.reco_xPt_ctbgT->Fill( xP4.Pt(), v_ctbgTs[ mlist[k].idg ]/(xP4.Beta()*xP4.Gamma()) ) ;
           }
           */
           if ( pass && pass_hlt && nNonGhost > 0 && passMET ) {
              // h.sel_xPt_ctbgT->Fill( xP4.Pt(), v_ctbgTs[ mlist[k].idg ]/(xP4.Beta()*xP4.Gamma()) ) ;
              h.h_matchTime->Fill( genTime ) ;
           }
           if ( v_ctbgTs[ mlist[k].idg ] > 300. && v_ctbgTs[ mlist[k].idg ] < 1200. ) h.m_sMaj_sMin->Fill( sMajPho[mlist[k].ir], sMinPho[mlist[k].ir] );

           // time resolution
           if ( fabs(mlist[k].dPt) > 0.25 ) continue ;
           //if ( fabs( recoTime - genTime + timeCalib[0] ) < 1. ) h.h_matchTime->Fill( genTime ) ;
           if (  genTime > 3                  ) h.h_TimeRes1->Fill( recoTime - genTime ) ;
           if ( recoTime > 3. && genTime < 3. ) h.h_TimeRes2->Fill( recoTime - genTime ) ;
           if ( recoTime < 3. && genTime > 3. ) h.h_TimeRes3->Fill( recoTime - genTime ) ;
           h.h_PtRes->Fill( mlist[k].dPt ) ;

           h.dR_Time->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , genTime ) ;
           h.dR_sMaj->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , sMajPho[mlist[k].ir] ) ;
           h.dR_sMin->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , sMinPho[mlist[k].ir] ) ;
           h.dR_photIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , photIso[mlist[k].ir] ) ;
           h.dR_nHadIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , nHadIso[mlist[k].ir] ) ;
           h.dR_cHadIso->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) , cHadIso[mlist[k].ir] ) ;
           h.dR_XTime->Fill( recoPho[mlist[k].idr].second.DeltaR( genPs[ mlist[k].idg ] ) ,  v_ctbgTs[mlist[k].idg]  ) ;
           h.XTime_genTime->Fill( genXTs[mlist[k].idg] , genTime);
           h.sMaj_sMin->Fill( sMajPho[mlist[k].ir] , sMinPho[mlist[k].ir] ) ;

       }
       if ( pass && pass_hlt ) h.m_nPhot->Fill( (int)recoPho.size(), m_gen ) ; 
       if ( pass && pass_hlt && nX0_gb == 2 ) h.m2_nPhot->Fill( (int)recoPho.size(), m_gen ) ; 
       if ( pass && pass_hlt && nX0_gb == 1 ) h.m1_nPhot->Fill( (int)recoPho.size(), m_gen ) ; 
       if ( pass && pass_hlt && nX0_gb == 0 ) h.m0_nPhot->Fill( (int)recoPho.size(), m_gen ) ; 
       int n_rec = ( recoPho.size() >= 4 ) ? 4 : (int)recoPho.size() ;
       h.nPhot_g_r->Fill( (int)genPho.size(), n_rec ) ; 

       if ( genPho.size() > 0 && recoPho.size() < 1 ) {
          for ( size_t k=0; k< genPho.size(); k++ ) { 
              h.failGen_Pt->Fill(  genPho[k].second.Pt()  ) ;
              h.failGen_Eta->Fill(  genPho[k].second.Eta()  ) ;
          }
       }

   } // end of event looping

   select->PrintCutFlow() ;

   printf("     Event Eff : %f  Phot/nEvt = %f \n", (double)nPass/(double)nEvt, (double)nPassPhot/(double)nEvt ) ;
   printf(" Gen Event Eff : %f  Phot/nEvt = %f \n", (double)nPassGen/(double)nEvt, (double)nPassGenPhot/(double)nEvt ) ;

}  

// propagator with backward propagation
// ECal Dimension : R:( 129 ~ 155 cm , Z(one-side) : 317 ~345 )
bool TestGen::Propagator( TLorentzVector& v, double& x, double& y, double& z, double& t, double taugamma ) {

    bool hasEcalTime = true ;

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;
    double dL = 0 ;

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
            iM0.idg  = pool[j] ;             // the position in gen list (vg)
            iM0.idr  = j ;                   // the poistion in reco list (vr)
            iM0.ig  = vg[ pool[j] ].first ;  // the index of the gen photon in ntuple
            iM0.ir  = vr[ j ].first ;        // the index of the reco photon in ntuple
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

/*
double TestGen::RecoWeight( double ctbgT ) {

     int ibin = (ctbgT/100)  ;
     if ( ibin > 17 ) ibin = 17 ;

     double effA[18] =  { 0.208, 0.200, 0.210, 0.209, 0.210, 0.223, 0.232, 0.220, 0.208, 0.236,
                          0.216, 0.208, 0.201, 0.144, 0.048, 0.003, 0.069, 0.0    } ;

     if ( ibin > 17 || effA[ibin] > 0.3 ) printf(" ibin = %d , weight = %.3f \n ", ibin, effA[ibin] ) ;

     double weight = effA[ibin] ;
     return weight ;

}
*/
double TestGen::RecoWeight( double pT ) {

     int ibin = ( pT/20)  ;
     if ( ibin > 24 ) ibin = 24 ;

     double effA[25] = { 0.000, 0.003, 0.028, 0.049, 0.195, 0.225, 0.240, 0.259, 0.259, 0.275, 0.283, 0.261,
                         0.265, 0.277, 0.266, 0.257, 0.252, 0.283, 0.226, 0.295, 0.261, 0.222, 0.356, 0.200, 0.324 } ;

     if ( ibin > 24 || effA[ibin] > 0.4 ) printf(" ibin = %d , weight = %.3f \n ", ibin, effA[ibin] ) ;

     double weight = effA[ibin] ;
     return weight ;

}

