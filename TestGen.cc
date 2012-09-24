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
  Input->GetParameters("UnBinned",       &unBinned ) ;
  if ( isData == 0 ) Input->GetParameters("DecayR",  &decayR ) ; 

  TString Path_fName = hfolder + hfName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  Rtree = new TTree( "DP", "DP" ) ;
  setRtupleBranches( Rtree, Rleaves );
}


TestGen::~TestGen(){

  theFile->cd() ;
  if ( unBinned == 1 ) Rtree->Write() ;
  cout<<" RTree written ! "<<endl ;
  if ( unBinned == 0 ) Hist->Write( "", theFile ) ;
  cout<<" Output historams written ! "<<endl ;
  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete Input ;
  delete Hist ;
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

   // initialize selection
   select->Init( tr1 ) ;

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;
 
   // initial histograms  
   Hist->Init( h ) ;

   int nEvt = 0 ;
   int EscapedPhoton = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
        
       // init Rtuple for RooStats
       initRtuple( Rtree, Rleaves ) ;
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
	  h.h_nVtx->Fill( totalNVtx ) ;
	  h.h_nJets->Fill( selectJets.size() ) ;
	  h.h_nPhotons->Fill( selectPho.size() ) ;
	  h.h_nMuons->Fill( nMuons ) ;
	  h.h_nElectrons->Fill( nElectrons ) ;

	  // MET information
	  TLorentzVector met( metPx, metPy, 0, metE)  ;
	  h.h_met->Fill( met.Pt() );

	  //cout<<" EVT# : "<< nEvt <<endl ;
	  TLorentzVector g1P4(0,0,0,0)  ;
	  double max_gPt  = 0 ;
          int ik = 0 ;
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

	      if ( fabs( gP4_.Eta()) <= 1.479 ) h.h_maxSwissEB->Fill( maxSwissX[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) h.h_maxSwissEE->Fill( maxSwissX[k] );
	      h.h_fSpike->Fill( fSpike[k] ) ;
	      h.h_sMin->Fill( sMinPho[k] ) ;

              // exclude spike-like photons
	      if ( fabs(fSpike[k]) > 0.001 ) h.badPhoTime->Fill( seedTime[k] ) ;
	      if ( fabs(fSpike[k]) > 0.001 ) continue ;
	      //if ( maxSwissX[k] > 0.95 ) continue ;
	      h.h_seedSwiss->Fill( seedSwissX[k] );
	      h.h_nXtals->Fill( nXtals[k] ) ;
	      if ( nXtals[k] < 3 ) continue ;

	      h.obsTime->Fill( seedTime[k] );
	      if ( fabs( gP4_.Eta()) <= 1.479 ) h.obsEBTimeErr->Fill( seedTimeErr[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) h.obsEETimeErr->Fill( seedTimeErr[k] );

	      h.aveObsTime->Fill( aveTime[k] );
	      if ( fabs( gP4_.Eta()) <= 1.479 ) h.aveObsEBTimeErr->Fill( aveTimeErr[k] );
	      if ( fabs( gP4_.Eta())  > 1.479 ) h.aveObsEETimeErr->Fill( aveTimeErr[k] );

              // timing in different kinematic features
              if ( selectJets.size()  < 3 ) h.TimeLT3Jets->Fill( seedTime[k] ) ;
              if ( selectJets.size() >= 3 ) h.TimeGE3Jets->Fill( seedTime[k] ) ;
              if ( met.Et() < 60.00001 )    h.TimeLowMET->Fill( seedTime[k] ) ;
              if ( met.Et() > 60.      )    h.TimeBigMET->Fill( seedTime[k] ) ;

              if ( aveTime1[k] >  10.5 ) h.SpikeEtaP->Fill( fabs( gP4_.Eta() ) );
              if ( aveTime1[k] < -10.5 ) h.SpikeEtaN->Fill( fabs( gP4_.Eta() ) );
              if ( fabs( aveTime1[k]) >  10.5 ) {
                 double maxVz = 0 ;
                 for (size_t iv =0; iv< MAXVTX ; iv++ ) { 
                     maxVz = (fabs(vtxZ[iv]) >  maxVz ) ? fabs(vtxZ[iv]) : maxVz ;
                 }
                 if ( aveTime1[k] >  10.5 ) h.Vz_P->Fill( maxVz ) ;
                 if ( aveTime1[k] < -10.5 ) h.Vz_N->Fill( maxVz ) ;
              }
              

	      if ( timeChi2[k] < 5 )  h.aveObsTime1->Fill( aveTime1[k] );
	      if ( timeChi2[k] < 5 )  h.aveObsTime2->Fill( seedTime[k] );

	      if ( timeChi2[k] < 10 && fabs( gP4_.Eta()) <= 1.479 )  h.aveObsEBTimeErr1->Fill( aveTimeErr1[k] );
	      if ( timeChi2[k] < 10 && fabs( gP4_.Eta())  > 1.479 )  h.aveObsEETimeErr1->Fill( aveTimeErr1[k] );

              h.seedTime_Chi2->Fill( seedTime[k], timeChi2[k] ) ;

	      h.h_nChi2->Fill( timeChi2[k] ) ;
	      h.h_TrkIso->Fill( phoTrkIso[k] );
	      h.h_EcalIso->Fill( phoEcalIso[k] );
	      h.h_HcalIso->Fill( phoHcalIso[k] );
	      h.h_TrkIsoR->Fill( phoTrkIso[k] / gP4_.Pt() );
	      h.h_EcalIsoR->Fill( phoEcalIso[k] / gP4_.E() );
	      h.h_HcalIsoR->Fill( phoHcalIso[k] / gP4_.E() );
	      h.h_nBC->Fill( nBC[k] ) ;
              h.h_Eta_Time->Fill( gP4_.Eta() , seedTime[k] );
              h.h_Phi_Time->Fill( gP4_.Phi() , seedTime[k] );

              bool haloPhoton = false ;
              if ( nHaloTracks > 0  && haloRho > 0 ) {
                 h.h_RhoPhi_Halo->Fill( haloPhi, haloRho ) ;
                 h.h_nHaloTracks->Fill( nHaloTracks ) ;
                 h.h_nHaloHits->Fill( nHaloHits ) ;
                 double dphi = fabs( haloPhi - gP4_.Phi() ) ;
                 dphi = ( dphi > 3.1416 ) ? 6.2832 - dphi : dphi ;
                 //double drho = fabs( haloRho - gP4_.Rho() ) ;
                 if (  dphi < 0.5  ) {   
                    h.h_PhiTimeHalo->Fill( gP4_.Phi(), seedTime[k] ) ;
                    h.h_EtaTimeHalo->Fill( gP4_.Eta(), seedTime[k] ) ;
                    haloPhoton = true ;
                    h.h_SigEtaHalo->Fill( sigmaEta[k] ) ;
                    h.h_SigIetaHalo->Fill( sigmaIeta[k] ) ;
                 }
              }
              if (  !haloPhoton ) {
                 h.h_TimeNoHalo->Fill( seedTime[k] ) ;
                 h.h_EtaTimeNoHalo->Fill( gP4_.Eta(), seedTime[k] ) ;
		 h.h_SigEta->Fill( sigmaEta[k] ) ;
		 h.h_SigIeta->Fill( sigmaIeta[k] ) ;
              }

              if ( seedTime[k] <  -5. )  h.h_Phi_Time1->Fill( gP4_.Phi() , seedTime[k] );

	      if ( ik == 0 ) Rleaves.g1Pt   = gP4_.Pt() ;
	      if ( ik == 0 ) Rleaves.g1Time = seedTime[k] ;
	      if ( ik == 1 ) Rleaves.g2Pt   = gP4_.Pt() ;
	      if ( ik == 1 ) Rleaves.g2Time = seedTime[k] ;

              ik++ ;
          }
          h.h_g1Pt->Fill( max_gPt );

          Rleaves.nJets    = (int)( selectJets.size() );
          Rleaves.nPhotons = ik  ;
          Rleaves.met      = met.Et() ;
          if ( selectJets.size() > 0 && selectJets.size() < 3 ) Rleaves.bgTime = seedTime[ selectPho[0].first ] ;
       }

       if ( Rleaves.nPhotons > 0 ) Rtree->Fill() ;

       // look up gen information  
       //if ( nVertices > 0 ) cout<<" vtx  = ("<< vtxX[0] <<","<< vtxY[0] <<","<<vtxZ[0] <<")"<< endl;
       if ( isData == 1 ) continue ;

       genPho.clear() ; // used for matching
       genTs.clear() ;  // used for matching
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

           h.Time_R->Fill( dT, sqrt( (genVx[k]*genVx[k]) + ( genVy[k]*genVy[k]) ) );
           h.Time_Z->Fill( dT, fabs( genVz[k] )  );

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
    
           h.h_Time->Fill( dT ) ;
          
           if ( dT > -3.999999 ) EscapedPhoton++ ;
           h.h_ctau->Fill( genT[mId]*300. /  xP4.Gamma()) ;
           h.h_xbeta->Fill( xP4.Beta() ) ;
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
          h.h_gen1RecoPt->Fill( maxGen_RecoPt ) ;
          for ( size_t j=0; j< genTs.size() ; j++ ) h.h_genTime->Fill( genTs[j] ) ;
       }       

       h.h_gen1Pt->Fill( maxGenPt ) ;
       h.h_nGenPhotons->Fill( nGenPho ) ;

       // * Matching Process  *
       vector<iMatch> mlist = GlobalDRMatch( recoPho, genPho );
       for ( size_t k=0; k< mlist.size(); k++ ) {
           if ( mlist[k].dr > 0.5 || fabs(mlist[k].dPt) > 0.25 ) continue ;
           double recoTime  = seedTime[ mlist[k].ir ] ;
           double recoTime1 = aveTime1[ mlist[k].ir ] ;
           double genTime  = genTs[ mlist[k].idg ] ;
           h.h_matchRecoTime->Fill( recoTime ) ;
           h.h_matchGenTime->Fill( genTime ) ;
           if ( fabs( recoTime - genTime + 0.16 ) < 1. ) h.h_matchTime->Fill( genTime ) ;
           if ( genTime < 2                 ) h.h_TimeRes1->Fill( recoTime - genTime ) ;
           if ( genTime >=2  && genTime < 6 ) h.h_TimeRes2->Fill( recoTime - genTime ) ;
           if ( genTime >=6                 ) h.h_TimeRes3->Fill( recoTime - genTime ) ;
           if ( genTime < 2                 ) h.h_aTimeRes1->Fill( recoTime1 - genTime ) ;
           if ( genTime >=2  && genTime < 6 ) h.h_aTimeRes2->Fill( recoTime1 - genTime ) ;
           if ( genTime >=6                 ) h.h_aTimeRes3->Fill( recoTime1 - genTime ) ;
           h.h_PtRes->Fill( mlist[k].dPt ) ;
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

