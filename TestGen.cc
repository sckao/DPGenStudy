#include "TestGen.h"

TestGen::TestGen( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw( datacardfile ) ; 

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 
  Input->GetParameters("FitCtau",       &FitCtau) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  if ( isData == 0 ) Input->GetParameters("DecayR",  &decayR ) ; 

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

}

TestGen::~TestGen(){

  theFile->cd() ;
  HistoWrite( "", theFile ) ;
  cout<<" historams written ! "<<endl ;
  theFile->Close() ;

  delete select ;
  delete Input ;
  delete h_draw ;
  cout<<" done ! "<<endl ;

}

// analysis template
void TestGen::ReadTree( string dataName ) { 

   TTree* tr = Input->TreeMap( dataName );

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

   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );

   tr->SetBranchAddress("maxSwissX",   maxSwissX );
   tr->SetBranchAddress("seedSwissX",  seedSwissX );
   tr->SetBranchAddress("fSpike",      fSpike );
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

   select->Init( tr1 ) ;

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   obsTime     = new TH1D("obsTime", "Photon Time from seed", 160,  -14.5, 25.5);
   aveObsTime  = new TH1D("aveObsTime", "Photon Time from clusters", 160,  -14.5, 25.5);
   aveObsTime1 = new TH1D("aveObsTime1", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   aveObsTime2 = new TH1D("aveObsTime2", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   obsEBTimeErr  = new TH1D("obsEBTimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   obsEETimeErr  = new TH1D("obsEETimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   aveObsEBTimeErr  = new TH1D("aveObsEBTimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEETimeErr  = new TH1D("aveObsEETimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEBTimeErr1 = new TH1D("aveObsEBTimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEETimeErr1 = new TH1D("aveObsEETimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);

   seedTime_Chi2  = new TH2D("seedTime_Chi2", "Seed Time vs Chi2 ", 160,  -14.5, 25.5, 50, 0, 100);

   badPhoTime     = new TH1D("badPhoTime", "bad channel time", 102,  -25.5, 25.5);
   TimeLT3Jets    = new TH1D("TimeLT3Jets", "Ecal Time from  < 3 Jets Events", 160,  -14.5, 25.5);
   TimeGE3Jets    = new TH1D("TimeGE3Jets", "Ecal Time from >= 3 Jets Events", 160,  -14.5, 25.5);
   TimeLowMET     = new TH1D("TimeLowMET", "Ecal Time from  MET  < 60 GeV Events", 160,  -14.5, 25.5);
   TimeBigMET     = new TH1D("TimeBigMET", "Ecal Time from  MET >= 60 GeV Events", 160,  -14.5, 25.5);

   SpikeEtaP      = new TH1D("SpikeEtaP", "#eta distribution for spike like photon ( t > 10 )", 24, 0, 2.4);
   SpikeEtaN      = new TH1D("SpikeEtaN", "#eta distribution for spike like photon ( t < -10)", 24, 0, 2.4);
   Vz_P           = new TH1D("Vz_P", " z of vertices for events with photon ( t >  10)", 65, -32.5, 32.5);
   Vz_N           = new TH1D("Vz_N", " z of vertices for events with photon ( t < -10)", 65, -32.5, 32.5);

   h_matchRecoTime = new TH1D("h_matchRecoTime", "Matched Reco Photon Time", 160,  -14.5, 25.5);
   h_matchGenTime  = new TH1D("h_matchGenTime", "Matched Gen Photon Time", 160,  -14.5, 25.5);
   h_matchTime     = new TH1D("h_matchTime", "Time Matched Gen Photon Time", 160,  -14.5, 25.5);
   h_genTime       = new TH1D("h_genTime",   "Photon Time ", 160,  -14.5, 25.5);
   h_TimeRes1   = new TH1D("h_TimeRes1", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   h_TimeRes2   = new TH1D("h_TimeRes2", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   h_TimeRes3   = new TH1D("h_TimeRes3", "Seed Photon Time Resolution",  50,  -2.5, 2.5 );
   h_aTimeRes1   = new TH1D("h_aTimeRes1", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   h_aTimeRes2   = new TH1D("h_aTimeRes2", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   h_aTimeRes3   = new TH1D("h_aTimeRes3", "Weighted Ave. Photon Time Resolution",  50,  -2.5, 2.5 );
   h_PtRes     = new TH1D("h_PtRes",   " Photon Pt Resolution", 200,  -1., 1.);

   Time_R   = new TH2D("Time_R", "Gen Photon Time vs R ", 160,  -14.5, 25.5, 25, 0, 175);
   Time_Z   = new TH2D("Time_Z", "Gen Photon Time vs Z ", 160,  -14.5, 25.5, 30, 0, 390);

   h_Time    = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   h_nChi2   = new TH1D("h_nChi2", "normalized chi2 of seed xtals", 100,  0, 50.0);
   h_ctau    = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
   h_xbeta   = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
   h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );

   h_maxSwissEB = new TH1D("h_maxSwissEB", " max SwissCross value from seed EB BC ", 150,  0., 1.5 );
   h_maxSwissEE = new TH1D("h_maxSwissEE", " max SwissCross value from seed EE BC ", 150,  0., 1.5 );
   h_seedSwiss = new TH1D("h_seedSwiss", " seed SwissCross value ", 150,  0., 1.5 );
   h_fSpike   = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   h_nXtals   = new TH1D("h_nXtals", "N of crystals of the photon ", 100,  0, 100 );
   h_nBC      = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   h_sMin     = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

   h_met      = new TH1D("h_met",  "MET distribution ", 40,  0, 800);
   h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   h_gen1Pt     = new TH1D("h_gen1Pt", "Leading GenPhoton Pt ", 50,  0, 500);
   h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

   h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   h_nGenPhotons = new TH1D("h_nGenPhotons", "N of GenPhotons  ", 10,  -0.5, 9.5);
   h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);

   int nEvt = 0 ;
   int EscapedPhoton = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
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

       recoPho.clear() ; // used for matching
       recoTs.clear() ; // used for matching
       if ( pass ) {

          nEvt++; 
	  // multiplicity
	  h_nVtx->Fill( totalNVtx ) ;
	  h_nJets->Fill( nJets ) ;
	  h_nPhotons->Fill( nPhotons ) ;
	  h_nMuons->Fill( nMuons ) ;
	  h_nElectrons->Fill( nElectrons ) ;

	  // MET information
	  TLorentzVector met( metPx, metPy, 0, metE)  ;
	  h_met->Fill( met.Pt() );

	  //cout<<" EVT# : "<< nEvt <<endl ;
	  TLorentzVector g1P4(0,0,0,0)  ;
	  double max_gPt  = 0 ;
	  //for ( int k=0; k< nPhotons; k++) {
	  for ( size_t kk =0; kk < selectPho.size() ; kk++) {
              int k = selectPho[kk].first ;
              
	      TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
              //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
              if ( gP4_.Pt() > max_gPt ) {
                 max_gPt = gP4_.Pt() ;
                 g1P4 = gP4_ ;
              } 

              // collect good reco photons
	      recoPho.push_back( make_pair( k , gP4_) );
	      recoTs.push_back( seedTime[k] );

	      if ( fabs( gP4_.Eta()) <= 1.479 ) h_maxSwissEB->Fill( maxSwissX[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) h_maxSwissEE->Fill( maxSwissX[k] );
	      h_fSpike->Fill( fSpike[k] ) ;
	      h_sMin->Fill( sMinPho[k] ) ;

              // exclude spike-like photons
	      if ( fabs(fSpike[k]) > 0.001 ) badPhoTime->Fill( seedTime[k] ) ;
	      if ( fabs(fSpike[k]) > 0.001 ) continue ;
	      //if ( maxSwissX[k] > 0.95 ) continue ;
	      h_seedSwiss->Fill( seedSwissX[k] );
	      h_nXtals->Fill( nXtals[k] ) ;

	      obsTime->Fill( seedTime[k] );
	      if ( fabs( gP4_.Eta()) <= 1.479 ) obsEBTimeErr->Fill( seedTimeErr[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) obsEETimeErr->Fill( seedTimeErr[k] );

	      aveObsTime->Fill( aveTime[k] );
	      if ( fabs( gP4_.Eta()) <= 1.479 ) aveObsEBTimeErr->Fill( aveTimeErr[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) aveObsEETimeErr->Fill( aveTimeErr[k] );

              // timing in different kinematic features
              if ( selectJets.size()  < 3 ) TimeLT3Jets->Fill( seedTime[k] ) ;
              if ( selectJets.size() >= 3 ) TimeGE3Jets->Fill( seedTime[k] ) ;
              if ( met.Et() < 60.00001 )    TimeLowMET->Fill( seedTime[k] ) ;
              if ( met.Et() > 60.      )    TimeBigMET->Fill( seedTime[k] ) ;

              if ( aveTime1[k] >  10.5 ) SpikeEtaP->Fill( fabs( gP4_.Eta() ) );
              if ( aveTime1[k] < -10.5 ) SpikeEtaN->Fill( fabs( gP4_.Eta() ) );
              if ( fabs( aveTime1[k]) >  10.5 ) {
                 double maxVz = 0 ;
                 for (size_t iv =0; iv< MAXVTX ; iv++ ) { 
                     maxVz = (fabs(vtxZ[iv]) >  maxVz ) ? fabs(vtxZ[iv]) : maxVz ;
                 }
                 if ( aveTime1[k] >  10.5 ) Vz_P->Fill( maxVz ) ;
                 if ( aveTime1[k] < -10.5 ) Vz_N->Fill( maxVz ) ;
              }
              

	      if ( nXtals[k] < 3 ) continue ;
	      if ( timeChi2[k] < 5 )  aveObsTime1->Fill( aveTime1[k] );
	      if ( timeChi2[k] < 5 )  aveObsTime2->Fill( seedTime[k] );

	      if ( timeChi2[k] < 10 && fabs( gP4_.Eta()) <= 1.479 )  aveObsEBTimeErr1->Fill( aveTimeErr1[k] );
	      if ( timeChi2[k] < 10 && fabs( gP4_.Eta())  > 1.479 )  aveObsEETimeErr1->Fill( aveTimeErr1[k] );

              seedTime_Chi2->Fill( seedTime[k], timeChi2[k] ) ;

	      h_nChi2->Fill( timeChi2[k] ) ;
	      h_TrkIso->Fill( phoTrkIso[k] );
	      h_EcalIso->Fill( phoEcalIso[k] );
	      h_HcalIso->Fill( phoHcalIso[k] );
	      h_TrkIsoR->Fill( phoTrkIso[k] / gP4_.Pt() );
	      h_EcalIsoR->Fill( phoEcalIso[k] / gP4_.E() );
	      h_HcalIsoR->Fill( phoHcalIso[k] / gP4_.E() );
	      h_nBC->Fill( nBC[k] ) ;
          }
          h_g1Pt->Fill( max_gPt );
       }

       // look up gen information  
       //if ( nVertices > 0 ) cout<<" vtx  = ("<< vtxX[0] <<","<< vtxY[0] <<","<<vtxZ[0] <<")"<< endl;
       if ( isData == 1 ) continue ;

       genPho.clear() ; // used for matching
       genTs.clear() ; // used for matching
       double maxGenPt = 0. ;
       int nGenPho = 0;
       for ( int k=0; k< nGen ; k++) {
           if ( pdgId[k] != 22 ) continue ;
           TLorentzVector gP4 = TLorentzVector( genPx[k], genPy[k], genPz[k], genE[k] ) ;

           int mId = momId[k]  ;
           if ( mId < 0  ) continue ;
           TLorentzVector xP4 = TLorentzVector( genPx[mId], genPy[mId], genPz[mId], genE[mId] ) ;

           if ( gP4.Pt() > maxGenPt ) maxGenPt = gP4.Pt() ;
           nGenPho++ ;

           double EcalTime = genT[mId] ;  // tau*gamma
 
           // test my propagator
           /*
           double cbtg = genT[k] * 30  ;
           double ux = genVx[mId] ;
           double uy = genVy[mId] ;
           double uz = genVz[mId] ;
           double ut = 0 ; 
           Propagator( xP4, ux, uy, uz, ut, cbtg ) ;
           double EcalTime = cbtg  / ( 30* xP4.Beta() ) ;  // c*beta*tau*gamma
           cout<<"  --------------- "<<endl;
           cout<<" Propagate :     Vx:"<<    ux << "      Vy:"<< uy << "     Vz:"<< uz <<" r = "<<sqrt( (ux*ux) + (uy*uy) + (uz*uz) )<< endl;
           cout<<" FromSim   :  genVx:"<< genVx[k] << "  genVy:"<< genVy[k] << "  genVz:"<< genVz[k] ;
           cout<<" r = "<<sqrt( (genVx[k]*genVx[k]) + (genVy[k]*genVy[k]) + (genVz[k]*genVz[k])  ) <<endl;
           cout<<" my clock : "<<ut <<"  its clock:"<< EcalTime  <<"  its beta :"<< xP4.Beta() <<" ctbg = "<< cbtg <<", "<< cbtg*xP4.Beta() <<endl ;
           cout<<" dT = "<< ut - EcalTime  << endl;
           */
 
           double vx = genVx[k] ;
           double vy = genVy[k] ;
           double vz = genVz[k] ;
           if (  sqrt( (vx*vx) + (vy*vy)  ) < decayR ) continue ;
           if (  decayR < 0 && sqrt( (vx*vx) + (vy*vy)  ) > fabs(decayR) ) continue ;
           //if (  fabs(vz) < 160. ) continue ;
           Propagator( gP4, vx, vy, vz, EcalTime ) ;
           double d_x = vx - vtxX[0] ;
           double d_y = vy - vtxY[0] ;
           double d_z = vz - vtxZ[0] ;
           double d_r = sqrt( (d_x*d_x) + (d_y*d_y) + (d_z*d_z) ); 
           double t0  = d_r /30. ; // t0 -> ecaltime assuming photon is from original
           //double dT = ( EcalTime < -24.9 ) ? -4 : EcalTime  - t0 ;
           double dT = EcalTime  - t0 ;

           Time_R->Fill( dT, sqrt( (genVx[k]*genVx[k]) + ( genVy[k]*genVy[k]) ) );
           Time_Z->Fill( dT, fabs( genVz[k] )  );

           // build the P4 for gen photon from reconstruction point of view 
           // skip the escaped photon 
           TLorentzVector genRecoP4 = TLorentzVector( d_x, d_y, d_z, d_r ) ;
           genRecoP4 = genRecoP4 * ( gP4.E() / d_r ) ;
           if ( EcalTime > -20.0 ) { 
              genPho.push_back( make_pair( k, genRecoP4 ) ) ;
              genTs.push_back( dT ) ;
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
           }
           /*
           if ( dT < 0 && dT > -3 ) {
              cout<<"  Neutralino :  genVx:"<< genVx[mId] << " genVy:"<< genVy[mId] << " genVz:"<< genVz[mId] ;
              cout<<"  beta:"<< xP4.Beta()  <<endl;
              cout<<"      Photon :  genVx:"<< genVx[k] << "  genVy:"<< genVy[k] << "  genVz:"<< genVz[k] <<endl;
              cout<<"         FinalEcal Vx:"<< vx <<"     Vy:"<< vy <<"    Vz:"<< vz <<endl;
              cout<<" LifeTime : "<< genT[k] / xP4.Beta() << "  EcalTime :"<< EcalTime<<"  T0:"<< t0 <<endl ; 
           }
           */        
    
           h_Time->Fill( dT ) ;
          
           if ( dT > -3.999999 ) EscapedPhoton++ ;
           h_ctau->Fill( genT[mId]*300. /  xP4.Gamma()) ;
           h_xbeta->Fill( xP4.Beta() ) ;
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       }

       // check gen photon characters 
       double maxGen_RecoPt = 0 ;
       int    nGoodGenPho = 0 ;
       for ( size_t j = 0 ; j < genPho.size() ; j++ ) { 
           maxGen_RecoPt = ( genPho[j].second.Pt() > maxGen_RecoPt ) ? genPho[j].second.Pt() : maxGen_RecoPt ;
           bool pass1 = ( genPho[j].second.Pt() > photonCuts[0] + 10 && fabs(genPho[j].second.Eta()) < photonCuts[1] - 0.2 ) ;
           //if  ( !pass1 && (photonCuts[0] - genPho[j].second.Pt())  < 15. ) pass1 = true ;
           bool pass2 = true ;
           for ( size_t m =0; m< selectJets.size() ; m++ ) {
               double dR_ = selectJets[m].second.DeltaR( genPho[j].second ) ;
               if ( dR_ < photonCuts[3] ) pass2 = false ;
           }
           if ( pass1 && pass2 ) nGoodGenPho++ ;
       }

       bool genPass =  ( nGoodGenPho > 0 && maxGen_RecoPt >= photonCuts[8] + 10 ) ? true : false ;
       if ( genPass )  {
          h_gen1RecoPt->Fill( maxGen_RecoPt ) ;
          for ( size_t j=0; j< genTs.size() ; j++ ) h_genTime->Fill( genTs[j] ) ;
       }       

       h_gen1Pt->Fill( maxGenPt ) ;
       h_nGenPhotons->Fill( nGenPho ) ;

       // * Matching Process  *
       vector<iMatch> mlist = GlobalDRMatch( recoPho, genPho );
       for ( size_t k=0; k< mlist.size(); k++ ) {
           if ( mlist[k].dr > 0.5 || fabs(mlist[k].dPt) > 0.25 ) continue ;
           double recoTime  = seedTime[ mlist[k].ir ] ;
           double recoTime1 = aveTime1[ mlist[k].ir ] ;
           double genTime  = genTs[ mlist[k].idg ] ;
           h_matchRecoTime->Fill( recoTime ) ;
           h_matchGenTime->Fill( genTime ) ;
           if ( fabs( recoTime - genTime + 0.16 ) < 1. ) h_matchTime->Fill( genTime ) ;
           if ( genTime < 2                 ) h_TimeRes1->Fill( recoTime - genTime ) ;
           if ( genTime >=2  && genTime < 6 ) h_TimeRes2->Fill( recoTime - genTime ) ;
           if ( genTime >=6                 ) h_TimeRes3->Fill( recoTime - genTime ) ;
           if ( genTime < 2                 ) h_aTimeRes1->Fill( recoTime1 - genTime ) ;
           if ( genTime >=2  && genTime < 6 ) h_aTimeRes2->Fill( recoTime1 - genTime ) ;
           if ( genTime >=6                 ) h_aTimeRes3->Fill( recoTime1 - genTime ) ;
           h_PtRes->Fill( mlist[k].dPt ) ;
       }
       //for ( size_t k=0; k< mlist.size() ; k++ ) printf(" (%d) , dr: %f dPt: %f \n", (int)k , mlist[k].dr, mlist[k].dPt ) ;

   } // end of event looping

   select->PrintCutFlow() ;
   cout<<" EscapedPhoton = "<< EscapedPhoton << endl ;

}  

// propagator with backward propagation
// ECal Dimension : R:( 129 ~ 175 cm , Z : 317 ~390 )
bool TestGen::Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double taugamma ) {

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;

    if ( r >= 175. || fabs(z) >= 390. ) t = -25 ;

    bool insideEcal = ( r < 129. && fabs(z) < 317. ) ? true : false ;  // inner edge of ECAL
    bool alived     = true ;
    bool comeback   = false ;
    int     i = 0 ;
    double dl = 0. ;
    do {

       i++ ; 
       r0 = sqrt( (x*x) + (y*y ) ) ;
       z0 = z ;
       t = t + dt ;
       x = x + (bx*dt*30*v.Beta() ) ;
       y = y + (by*dt*30*v.Beta() ) ;
       z = z + (bz*dt*30*v.Beta() ) ;
       r = sqrt( (x*x) + (y*y) ) ;
       //double trace = sqrt( (x*x) + (y*y) + (z*z)  ) ; 

       alived     = ( t <  taugamma   ) ? true : false ;
       insideEcal = ( r < 129 && fabs(z) < 317 ) ? true : false ; // inner edge of ECAL
       if ( !insideEcal && !comeback )     alived = false ; // for those photons just hit the Ecal

       double dr = r - r0 ;
       double dz = fabs(z) - fabs(z0) ;
       //if ( insideEcal ) cout<<" r = "<< r <<" z : "<< z <<"  dr:"<<dr <<" dz:"<<dz<< endl;
       if (  r >= 175  || fabs(z) >= 390 ) alived = false ; // for those neutralino decay closed to Ecal outter edge
       if (  insideEcal &&  comeback )     alived = false ; // for those photons go back to tracker from Ecal
       if (  r < 175. && fabs(z) < 390. && alived ) {
	  if ( r >= 129 || fabs(z) >= 317 )           comeback = true ;
          if ( comeback  ) dl += sqrt( (dz*dz) + (dr*dr) ) ;
          // Ecal crystal length is 23 cm , 10 cm is a random choose for photon to be absorted insdie Ecal
          if ( dl > 10. ) { 
             comeback = false ; 
             alived   = false ;
          }
       }
       if ( !insideEcal && comeback ) insideEcal = true ; // keep loop running if neutralino decay inside Ecal
       //if ( comeback ) cout<<" r = "<< r <<" z : "<< z <<"  dr:"<<dr <<" dz:"<<dz<< endl;
    } while ( insideEcal && alived && t < 25 ) ;


    return insideEcal ;
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
    double minDR = 999 ; 
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
        double dr = sqrt( dr2 ) ;
        //cout<<" ) , dR = "<< dr << endl ;

        if ( dr < minDR ) {
             minDR = dr ;
             vMatch = vMatch0 ;
        }

    } while (  next_permutation( pool.begin() ,pool.end() ) ) ;
 
    return vMatch ;
}

void TestGen::HistoWrite( string theFolder , TFile* file  ) {

     if ( theFolder.size() > 0 ) file->cd( theFolder.c_str() );

     obsTime->Write()     ;
     aveObsTime->Write() ;
     aveObsTime1->Write() ;
     aveObsTime2->Write() ;
     obsEBTimeErr->Write()  ;
     obsEETimeErr->Write()  ;
     aveObsEBTimeErr->Write() ;
     aveObsEETimeErr->Write() ;
     aveObsEBTimeErr1->Write() ;
     aveObsEETimeErr1->Write() ;

     seedTime_Chi2->Write()  ;
     Time_R->Write()  ;
     Time_Z->Write()  ;

     badPhoTime->Write()     ;
     TimeLT3Jets->Write()    ;
     TimeGE3Jets->Write()    ;
     TimeLowMET->Write()     ;
     TimeBigMET->Write()     ;

     SpikeEtaP->Write()      ;
     SpikeEtaN->Write()      ;
     Vz_P->Write()           ;
     Vz_N->Write()           ;

     h_matchRecoTime->Write() ;
     h_matchGenTime->Write()  ;
     h_matchTime->Write()     ;
     h_genTime->Write()       ;
     h_TimeRes1->Write()      ;
     h_TimeRes2->Write()      ;
     h_TimeRes3->Write()      ;
     h_aTimeRes1->Write()     ;
     h_aTimeRes2->Write()     ;
     h_aTimeRes3->Write()     ;
     h_PtRes->Write()         ;

     h_Time->Write()   ;
     h_nChi2->Write()  ;
     h_ctau->Write()   ;
     h_xbeta->Write()  ;
     h_TrkIso->Write()   ;
     h_HcalIso->Write()  ;
     h_EcalIso->Write()  ;
     h_TrkIsoR->Write()  ;
     h_HcalIsoR->Write() ;
     h_EcalIsoR->Write() ;

     h_maxSwissEB->Write() ;
     h_maxSwissEE->Write() ;
     h_seedSwiss->Write()  ;
     h_fSpike->Write()    ;
     h_nXtals->Write()    ;
     h_nBC->Write()       ;
     h_sMin->Write()      ;

     h_met->Write()        ;
     h_g1Pt->Write()       ;
     h_gen1Pt->Write()     ;
     h_gen1RecoPt->Write() ;

     h_nVtx->Write()       ;
     h_nPhotons->Write()   ;
     h_nGenPhotons->Write();
     h_nJets->Write()      ;
     h_nMuons->Write()     ;
     h_nElectrons->Write() ;

}

