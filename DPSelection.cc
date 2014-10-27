#include "DPSelection.h"
#include "MathTools.h"

static bool PtDecreasing( objID s1, objID s2) { return ( s1.second.Pt() > s2.second.Pt() ); }

DPSelection::DPSelection( string datacardfile ){

  // SC's getParameters method
  // If you don't like to use the Datacard.txt , markout this section and use CMSSW method
  //Input = new AnaInput( datacardfile );
  Input = AnaInput::Instance() ;

  Input->GetParameters( "VertexCuts",   &vtxCuts );
  Input->GetParameters( "PhotonCuts",   &photonCuts );
  Input->GetParameters( "UsePFIso",     &usePFIso ) ;
  Input->GetParameters( "PhotonIso",    &photonIso );
  Input->GetParameters( "PhotonPFIso",  &photonPFIso ) ;
  Input->GetParameters( "ElectronCuts", &electronCuts );
  Input->GetParameters( "JetCuts",      &jetCuts );
  Input->GetParameters( "MuonCuts",     &muonCuts );
  Input->GetParameters( "IsData",       &isData );
  Input->GetParameters( "TriggerBits",  &trigBits );
  Input->GetParameters( "UseL1",        &UseL1 );
  Input->GetParameters( "SystType",     &systType ) ;

  /*
  // CMSSW getParameter method
  vtxCuts              = iConfig.getParameter<std::vector<double> >("vtxCuts");
  jetCuts              = iConfig.getParameter<std::vector<double> >("jetCuts");
  photonCuts           = iConfig.getParameter<std::vector<double> >("photonCuts");
  photonIso            = iConfig.getParameter<std::vector<double> >("photonIso");
  electronCuts         = iConfig.getParameter<std::vector<double> >("electronCuts");
  */
  for ( int i =0 ; i< 9 ; i++) {
      counter[i] = 0 ;
      gCounter[i] = 0 ;
  }

  passL1      = false ;
  passHLT     = false ;
  passTrigger = false ;
  passPho     = false ;
  passVtx     = false ;
  passJet     = false ;  
  passMET     = false ;  
  newMET    = TLorentzVector(0., 0., 0., 0.) ;
  noPhotMET = TLorentzVector(0., 0., 0., 0.) ;
  theMET    = TLorentzVector(0., 0., 0., 0.) ;

  metCorrX = 0 ;
  metCorrY = 0 ;
  met1x =0 ; met1y = 0 ; met1E = 0 ;
  met2x =0 ; met2y = 0 ; met2E = 0 ;
}

DPSelection::~DPSelection(){

  //delete Input;
  cout<<" done with selection ! "<<endl ;

}

void DPSelection::Init( TTree* tr ) { 

   tr->SetBranchAddress("eventId",    &eventId);
   tr->SetBranchAddress("triggered",  &triggered);
   tr->SetBranchAddress("L1a",        &L1a);
   tr->SetBranchAddress("nPhotons",   &nPhotons);
   tr->SetBranchAddress("nJets",      &nJets);
   tr->SetBranchAddress("nMuons",     &nMuons);
   tr->SetBranchAddress("nElectrons", &nElectrons);
   tr->SetBranchAddress("nVertices",  &nVertices );

   tr->SetBranchAddress("metPx",      &metPx );
   tr->SetBranchAddress("metPy",      &metPy );
   tr->SetBranchAddress("met",        &metE );
   tr->SetBranchAddress("met_dx1",    &met_dx1 );
   tr->SetBranchAddress("met_dy1",    &met_dy1 );
   tr->SetBranchAddress("met_dx2",    &met_dx2 );
   tr->SetBranchAddress("met_dy2",    &met_dy2 );
   tr->SetBranchAddress("met_dx3",    &met_dx3 );
   tr->SetBranchAddress("met_dy3",    &met_dy3 );

   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );
   tr->SetBranchAddress("jetPz",       jetPz );
   tr->SetBranchAddress("jetE",        jetE );
   tr->SetBranchAddress("jetNDau",     jetNDau );
   tr->SetBranchAddress("jetCM",       jetCM );
   tr->SetBranchAddress("jetCEF",      jetCEF );
   tr->SetBranchAddress("jetCHF",      jetCHF );
   tr->SetBranchAddress("jetNHF",      jetNHF );
   tr->SetBranchAddress("jetNEF",      jetNEF );
   tr->SetBranchAddress("jecUnc",      jecUnc );
   tr->SetBranchAddress("jerUnc",      jerUnc );
   tr->SetBranchAddress("jetTime",     jetTime );
   tr->SetBranchAddress("jetTimeErr",  jetTimeErr );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   tr->SetBranchAddress("cHadIso",     cHadIso );
   tr->SetBranchAddress("nHadIso",     nHadIso );
   tr->SetBranchAddress("photIso",     photIso );

   tr->SetBranchAddress("sigmaIeta",   sigmaIeta );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("phoHoverE",   phoHovE );
   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("timeChi2",    timeChi2 );
   tr->SetBranchAddress("seedSwissX",  seedSwissX );
   tr->SetBranchAddress("seedE",       seedE );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("cscRho",      cscRho );
   tr->SetBranchAddress("cscTime",     cscTime );
   tr->SetBranchAddress("dtdPhi",      dtdPhi );
   tr->SetBranchAddress("dtdEta",      dtdEta );
   tr->SetBranchAddress("nXtals",      nXtals );

   tr->SetBranchAddress("elePx",        elePx );
   tr->SetBranchAddress("elePy",        elePy );
   tr->SetBranchAddress("elePz",        elePz );
   tr->SetBranchAddress("eleE",         eleE );
   tr->SetBranchAddress("eleEcalIso",   eleEcalIso );
   tr->SetBranchAddress("eleHcalIso",   eleHcalIso );
   tr->SetBranchAddress("eleTrkIso",    eleTrkIso );
   tr->SetBranchAddress("eleNLostHits", eleNLostHits );

   tr->SetBranchAddress("muPx",        muPx );
   tr->SetBranchAddress("muPy",        muPy );
   tr->SetBranchAddress("muPz",        muPz );
   tr->SetBranchAddress("muE",         muE );
   //tr->SetBranchAddress("muEcalIso",   muEcalIso );
   //tr->SetBranchAddress("muHcalIso",   muHcalIso );
   //tr->SetBranchAddress("muTrkIso",    muTrkIso );

   //tr->SetBranchAddress("vtxX",       vtxX );
   //tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   tr->SetBranchAddress("vtxChi2",    vtxChi2 );
   tr->SetBranchAddress("vtxNdof",    vtxNdof );
}

void DPSelection::Init( Rtuple& rt ) { 

     SetArray( phoPx,  rt.phoPx, MAXPHO ) ;
     SetArray( phoPy,  rt.phoPy, MAXPHO ) ;
     SetArray( phoPz,  rt.phoPz, MAXPHO ) ;
     SetArray( phoE ,  rt.phoE, MAXPHO ) ;

     SetArray( seedTime , rt.seedTime , MAXPHO );
     SetArray( timeChi2 , rt.timeChi2 , MAXPHO );
     SetArray( seedSwissX , rt.seedSwissX , MAXPHO );
     SetArray( aveTime  , rt.aveTime , MAXPHO ) ; 
     SetArray( dR_TrkPho , rt.dR_TrkPho , MAXPHO ); 

     SetArray( phoHovE , rt.phoHovE , MAXPHO );
     SetArray( sMinPho , rt.sMinPho, MAXPHO ) ;
     SetArray( sMajPho , rt.sMajPho , MAXPHO ); 
     SetArray( sigmaIeta , rt.sigmaIeta , MAXPHO );
     SetArray( phoEcalIso , rt.phoEcalIso , MAXPHO ); 
     SetArray( phoHcalIso , rt.phoHcalIso , MAXPHO ); 
     SetArray( phoTrkIso  , rt.phoTrkIso , MAXPHO );
     SetArray( photIso    , rt.photIso , MAXPHO ); 
     SetArray( cHadIso    , rt.cHadIso , MAXPHO );  
     SetArray( nHadIso    , rt.nHadIso , MAXPHO ); 
     SetArray( seedE      , rt.seedE  , MAXPHO );
     SetArray( cscdPhi    , rt.cscdPhi, MAXPHO ) ;
     SetArray( cscRho     , rt.cscRho,  MAXPHO ) ;
     SetArray( cscTime    , rt.cscTime, MAXPHO ) ;
     SetArray( dtdPhi     , rt.dtdPhi , MAXPHO ); 
     SetArray( dtdEta     , rt.dtdEta , MAXPHO );
     SetArray( nXtals     , rt.nXtals , MAXPHO );

     SetArray( vtxZ , rt.vtxZ, MAXVTX ) ; 
     SetArray( vtxChi2 , rt.vtxChi2, MAXVTX )  ; 
     SetArray( vtxNdof  , rt.vtxNdof, MAXVTX )  ;

     SetArray( jetPx , rt.jetPx, MAXJET ) ;
     SetArray( jetPy , rt.jetPy , MAXJET ) ; 
     SetArray( jetPz , rt.jetPz , MAXJET ) ;
     SetArray( jetE  , rt.jetE , MAXJET ) ; 
 
     SetArray( jetNDau , rt.jetNDau , MAXJET ) ; 
     SetArray( jetCM   , rt.jetCM , MAXJET ) ;
     SetArray( jetCEF  , rt.jetCEF , MAXJET ) ; 
     SetArray( jetCHF  , rt.jetCHF , MAXJET ) ; 
     SetArray( jetNHF  , rt.jetNHF , MAXJET ) ; 
     SetArray( jetNEF  , rt.jetNEF , MAXJET ) ; 
     SetArray( jecUnc  , rt.jecUnc , MAXJET ) ;
     SetArray( jerUnc  , rt.jerUnc , MAXJET ) ;
     SetArray( jetTime , rt.jetTime , MAXJET ) ; 
     SetArray( jetTimeErr , rt.jetTimeErr , MAXJET ) ; 

     SetArray( muPx    , rt.muPx , MAXMU ) ;
     SetArray( muPy    , rt.muPy , MAXMU ) ; 
     SetArray( muPz    , rt.muPz , MAXMU ) ;
     SetArray( muE     , rt.muE , MAXMU ) ; 

     SetArray( elePx   , rt.elePx , MAXELE ) ;
     SetArray( elePy   , rt.elePy , MAXELE ); 
     SetArray( elePz   , rt.elePz , MAXELE ); 
     SetArray( eleE    , rt.eleE , MAXELE ); 
     SetArray( eleEcalIso  , rt.eleEcalIso , MAXELE ); 
     SetArray( eleHcalIso  , rt.eleHcalIso , MAXELE ); 
     SetArray( eleTrkIso   , rt.eleTrkIso , MAXELE ); 
     SetArray( eleNLostHits , rt.eleNLostHits , MAXELE ) ;

     metPx = rt.metPx ;
     metPy = rt.metPy ;
     metE  = rt.metE ;
     met_dx1 = rt.met_dx1 ;
     met_dy1 = rt.met_dy1 ;
     met_dx2 = rt.met_dx2 ;
     met_dy2 = rt.met_dy2 ;
     met_dx3 = rt.met_dx3 ;
     met_dy3 = rt.met_dy3 ;

     nJets = rt.nJets ; 
     nPhotons = rt.nPhotons ;
     nElectrons = rt.nElectrons ;
     nVertices = rt.nVertices ;
     nMuons = rt.nMuons ; 
     triggered = rt.triggered ;
     L1a     = rt.L1a ;
     eventId = rt.eventId;

}

// analysis template
bool DPSelection::HLTFilter( ) { 
    
     bool pass = false ;
     for ( size_t i=0; i < trigBits.size(); i++ )  {
        pass = ( triggered  == trigBits[i] ) ? true : false ; 
        //int pass_val = pass ? 1 : 0 ;
        //cout<<" trig : "<< trigBits[i] <<" pass : "<< pass_val <<endl;
        if ( pass ) break ;
     }
     return pass ;
}

bool DPSelection::L1Filter() { 

     bool pass = ( L1a == 1 ) ? true : false ;
     return pass ;
}


bool DPSelection::PhotonFilter() { 

       bool pass =  true ;
       int nG[9] = { 0 } ;

       // 0. photon cuts
       phoV.clear() ;
       double maxPt = 0 ;
       for ( int j=0 ; j< nPhotons; j++ ) {
           nG[0]++ ;
           TLorentzVector phoP4( phoPx[j], phoPy[j], phoPz[j], phoE[j] ) ;
	   bool badseed  = badCrystal( phoP4.Eta() , phoP4.Phi() ) ;

           double egScale = 1. ;
           if ( systType == 5 ) egScale = ( fabs(phoP4.Eta()) < 1.479 ) ? 1.006 : 1.015 ;
           if ( systType == 6 ) egScale = ( fabs(phoP4.Eta()) < 1.479 ) ? 0.994 : 0.985 ;
           // MET correction
           metCorrX += phoP4.Px() ;
           metCorrY += phoP4.Py() ;
           phoP4 = phoP4 * egScale ;
           metCorrX -= phoP4.Px() ;
           metCorrY -= phoP4.Py() ;

	   if ( badseed ) continue ; // reject bad crystals using orignal eta/phi

	   //bool isHalo   = HaloTag( cscdPhi[j], sMajPho[j], sMinPho[j], phoP4.Eta() ) ;
	   //bool isSpike  = SpikeTag( nXtals[j], sMajPho[j], sMinPho[j], seedSwissX[j], phoP4.Eta() ) ;
	   //bool isCosmic = CosmicTag( dtdEta[j] , dtdPhi[j]  ) ;
	   //bool ghostTag = ( isHalo || isSpike || isCosmic ) ? true : false ;


           // For MET2 calculation
	   if ( fabs( seedTime[j]) > 3.0 && fabs( phoP4.Eta() ) < 1.47 ) {
	         met2x -= phoP4.Px()  ;
		 met2y -= phoP4.Py()  ;
	   }
	   if ( fabs( seedTime[j]) > 10.0 && fabs( phoP4.Eta() ) > 1.47 ) {
		 met2x -= phoP4.Px()  ;
		 met2y -= phoP4.Py()  ;
	   }
           // For MET1 calculation
           //printf("   met1 corr -- x:%.2f , y:%.2f \n", met1x,  met1y ) ;
	   if ( fabs( seedTime[j]) < 3.0 && fabs( phoP4.Eta() ) < 1.47 ) {
		 met1x += phoP4.Px()  ;
		 met1y += phoP4.Py()  ;
	   }
	   if ( fabs( seedTime[j]) < 10.0 && fabs( phoP4.Eta() ) > 1.47 ) {
		 met1x += phoP4.Px()  ;
		 met1y += phoP4.Py()  ;
	   }

           if (        phoP4.Pt() < photonCuts[0] )          continue ;
           nG[1]++ ;
           if ( fabs(phoP4.Eta()) > photonCuts[1] )          continue ;
           nG[2]++ ;

           if ( phoHovE[j] > photonCuts[2] ) continue ;
           nG[3]++ ;
           if ( sMinPho[j] < photonCuts[5] || sMinPho[j] > photonCuts[6] ) continue ;
           nG[4]++ ;
           if ( dR_TrkPho[j] < photonCuts[7] ) continue; 
           nG[5]++ ;

           // PF Isolation
           if ( usePFIso == 1 ) {
	      if ( cHadIso[j] >= photonPFIso[0] ) continue ;  // chargedHadron
	      if ( nHadIso[j] >= photonPFIso[1] + ( 0.04*phoP4.Pt()   ) ) continue ;  // neutralHadron
	      if ( photIso[j] >= photonPFIso[2] + ( 0.005*phoP4.Pt() ) ) continue ;  // photon
           } 
           // Detector Iso
           if ( usePFIso == 2 ) {
              if ( phoTrkIso[j] / phoP4.Pt()  >= photonIso[0] )                                continue ;
              if ( phoEcalIso[j] >= photonIso[1] || phoEcalIso[j] / phoE[j] >= photonIso[2] )  continue ;
              if ( phoHcalIso[j] >= photonIso[3] || phoHcalIso[j] / phoE[j] >= photonIso[4] )  continue ;
           }
           if ( usePFIso == 3 ) {
	      if ( cHadIso[j] >= photonPFIso[0] ) continue ;  // chargedHadron
	      if ( nHadIso[j] >= photonPFIso[1] + ( 0.04*phoP4.Pt()   ) ) continue ;  // neutralHadron
           } 

           // check the isolation -- using dR_gj
           //double dR_gj = 999. ;
           //for ( size_t k=0 ; k< jetV.size() ; k++ ) {
           //    if ( phoP4.DeltaR( jetV[k].second ) < dR_gj )  dR_gj  = phoP4.DeltaR( jetV[k].second ) ;
           //}
           //if ( dR_gj < photonCuts[3] ) continue ;
           if ( timeChi2[j] > 4. ) continue; 
           nG[6]++ ;
           if ( sigmaIeta[j] > photonCuts[9] ) continue ;
           nG[7]++ ; 
           
           maxPt = ( maxPt < phoP4.Pt() ) ? phoP4.Pt() : maxPt ;

           phoV.push_back( make_pair( j , phoP4) );
       }
       if ( maxPt >= photonCuts[8] ) nG[8]++ ;


       // identify which photon cut kill the events
       for ( int i=0; i < 9; i++ ) { 
           if ( nG[i] == 0 ) { 
              photonCutFlow = i ;
              break ;
           }
       }

       if ( (int)phoV.size() < photonCuts[4] ) pass = false ;
       if ( (int)phoV.size() > photonCuts[3] ) pass = false ;
       if ( maxPt < photonCuts[8] ) pass = false ;
       if ( phoV.size() > 1 ) sort( phoV.begin(), phoV.end(), PtDecreasing );
       if ( pass ) photonCutFlow = 8 ;

       return pass ;
}

bool DPSelection::VertexFilter() { 

     bool pass =  true ;
     // 1. vertex cuts
     int nVtx = 0 ;
     for ( int j=0 ; j< nVertices; j++ ) {
         //double vtxRho = sqrt( (vtxX[j]*vtxX[j]) + (vtxY[j]*vtxY[j]) ); 
	 if ( nVertices < 1 )                continue ;
	 if ( vtxNdof[j]     < vtxCuts[0] )  continue ;
	 if ( fabs(vtxZ[j]) >= vtxCuts[1] )  continue ;
	 //if ( vtxRho        >= vtxCuts[2] )  continue ;
         nVtx++ ;
     }
     if ( nVtx < 1 ) pass = false ;
     return pass ;
}

// type 0: nominal , 1: JER up , 2: JER down, 3: JES up , 4: JES down , 5: Eg up , 6: Eg down
bool DPSelection::JetMETFilter( bool usePFJetClean ) { 

     bool pass =  true ;
     // 1. jet selection
     jetV.clear() ;
     for ( int j=0 ; j< nJets; j++ ) {
         TLorentzVector jp4( jetPx[j], jetPy[j], jetPz[j], jetE[j] ) ;
         double jCorr = 1. ;
         if ( systType == 1 ) jCorr = ( jp4.Pt() + jerUnc[j] ) / jp4.Pt() ;
         if ( systType == 2 ) jCorr = ( jp4.Pt() - jerUnc[j] ) / jp4.Pt() ;
         if ( systType == 3 ) jCorr = ( 1. + jecUnc[j] ) ;
         if ( systType == 4 ) jCorr = ( 1. - jecUnc[j] ) ;

	 metCorrX += jp4.Px() ;
	 metCorrY += jp4.Py() ;
	 jp4 = jp4*jCorr;
	 metCorrX -= jp4.Px() ;
	 metCorrY -= jp4.Py() ;

	 if ( jp4.Pt()        < jetCuts[0] ) continue ;
	 if ( fabs(jp4.Eta()) > jetCuts[1] ) continue ;
           
         // Jet ID cuts
         if ( usePFJetClean ) { 
            if ( jetNDau[j] < (double)   2 )  continue ;
	    if ( jetCEF[j] >= (double)0.99 )  continue ;
	    if ( jetNEF[j] >= (double)0.99 )  continue ;
	    if ( jetNHF[j] >= (double)0.99 )  continue ;
	    if ( fabs( jp4.Eta() ) < 2.4 && jetCM[j]  <= 0 ) continue ;
         }

	 double dR_gj = 999. ;
         for ( int k=0 ; k< nPhotons; k++ ) {
             TLorentzVector phoP4( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
             if ( phoP4.Pt() < photonCuts[0] ) continue ;
             if ( phoHovE[k] > photonCuts[2] ) continue ;
	     if ( cHadIso[k] >= photonPFIso[0] ) continue ;  // chargedHadron
	     if ( nHadIso[k] >= photonPFIso[1] + ( 0.04*phoP4.Pt()   ) ) continue ;  // neutralHadron
	     if ( phoP4.DeltaR( jp4 ) < dR_gj )  dR_gj  = phoP4.DeltaR( jp4 ) ;
         }

	 if ( dR_gj < jetCuts[5] ) continue ;
	 jetV.push_back( make_pair( j, jp4 ) );

     }
     int nu_Jets = (int)jetV.size() ;
     if ( nu_Jets < (int)jetCuts[2] || nu_Jets > (int)jetCuts[3] )  pass = false ;


     if ( jetV.size() > 1 ) sort( jetV.begin(), jetV.end(), PtDecreasing ) ;
 
     return pass ;
}

// Correct MET by taking late photon into account and systematic varies 
bool DPSelection::CorrectMET() { 

     bool pass = true ;

     //  set MET after sytematic variations
     metPx += metCorrX ;
     metPy += metCorrY ;
     double met_E  =  sqrt( (metPx*metPx) + (metPy*metPy) ) ;
     theMET.SetPxPyPzE( metPx, metPy, 0., met_E ) ;

     //  set MET2 - MET include late photons
     met2x = metPx + met2x  ;
     met2y = metPy + met2y  ;
     met2E  = sqrt( met2x*met2x + met2y*met2y ) ;
     newMET.SetPxPyPzE( met2x, met2y, 0., met2E ) ;

     //  set MET1 - MET without any photon
     met1x = metPx + met1x  ;
     met1y = metPy + met1y  ;
     met1E  = sqrt( met1x*met1x + met1y*met1y ) ;
     noPhotMET.SetPxPyPzE( met1x, met1y, 0., met1E ) ;

     if ( jetCuts[4] >= 0 &&  theMET.Et() < jetCuts[4] )         pass = false ;
     if ( jetCuts[4]  < 0 &&  theMET.Et() > fabs( jetCuts[4] ) ) pass = false ;

     return pass ;
}

bool DPSelection::ElectronFilter() { 

     bool pass =  true ;
     eleV.clear() ;
     for ( int j=0 ; j< nElectrons; j++ ) {
         TLorentzVector eP4( elePx[j], elePy[j], elePz[j], eleE[j] ) ;
	 if ( eP4.Pt() < electronCuts[0] )          continue ;
	 if ( fabs( eP4.Eta()) > electronCuts[1] )  continue ;

         double relIso   = (eleEcalIso[j] + eleHcalIso[j] + eleTrkIso[j] ) / eP4.Pt() ;

         if ( relIso > electronCuts[2] )            continue ;
         //if ( eleNLostHits[j] >= electronCuts[4]  ) continue ;

         double dR_ej = 999. ;
         for ( size_t k=0 ; k< jetV.size() ; k++ ) {
             if ( eP4.DeltaR( jetV[k].second ) < dR_ej )  dR_ej  = eP4.DeltaR( jetV[k].second ) ;
         }
         if ( dR_ej < electronCuts[3] ) continue ;

         eleV.push_back( make_pair( j, eP4 ) ) ;
     }
     if ( eleV.size() < 1 ) pass = false ;
     return pass = false ;
}


bool DPSelection::MuonFilter() { 

     bool pass =  true ;
     muV.clear() ;
     for ( int j=0 ; j< nMuons; j++ ) {
         TLorentzVector mP4( muPx[j], muPy[j], muPz[j], muE[j] ) ;
	 if ( mP4.Pt() < muonCuts[0] )          continue ;
	 if ( fabs( mP4.Eta()) > muonCuts[1] )  continue ;

         //double relIso   = (muEcalIso[j] + muHcalIso[j] + muTrkIso[j] ) / mP4.Pt() ;
         //if ( relIso > muonCuts[2] )            continue ;

         double dR_mj = 999. ;
         for ( size_t k=0 ; k< jetV.size() ; k++ ) {
             if ( mP4.DeltaR( jetV[k].second ) < dR_mj )  dR_mj  = mP4.DeltaR( jetV[k].second ) ;
         }
         if ( dR_mj < muonCuts[3] ) continue ;

         muV.push_back( make_pair( j, mP4 ) ) ;
     }
     if ( muV.size() < 1 ) pass = false ;
     return pass ;
}

// Catagorize events
// 1: Pass Datacard selection ; trigger, vertex, photon, jetMET 
// 2: Control sample, pass trigger+vertex and photon selection without leading photon pt requirement
// 4: Control sample + non-zero jet
// 8: Control sample + pass MET cut
// 0: Fail all above cases
uint32_t DPSelection::EventIdentification() {

       uint32_t eventType = 0 ;
       counter[0]++ ;
       // 1. Trigger Information
       passL1  =  L1Filter() ;
       passHLT  = HLTFilter();
       passTrigger = ( UseL1 == 1 ) ? passL1 : passHLT ;
       if ( passTrigger ) counter[1]++ ;

       // 2. Vertices Information
       passVtx  = VertexFilter();
       if ( passTrigger && passVtx ) counter[2]++ ;

       // 3. Photon Information  
       passPho = PhotonFilter();  // true for selecting Isolation 
       if ( passTrigger && passVtx ) {
          int photonStop = GetPhotonCutFlow() ;
          for ( int i=0; i< photonStop ; i++) { 
              gCounter[i]++ ;
          }
       }
       if ( passTrigger && passVtx && passPho ) counter[3]++ ;

       // JetMET information
       passJet = JetMETFilter();
       passMET = CorrectMET() ;

       // Define event types
       if ( passVtx  && passPho && passJet && passMET )          eventType |= (1 <<0) ;   // 0001
       if ( passVtx  && passPho                       )          eventType |= (1 <<1) ;   // 0010
       if ( passVtx  && phoV.size() > 0               )          eventType |= (1 <<2) ;   // 0100
       if ( passVtx  && passPho && passJet > 0        )          eventType |= (1 <<3) ;   // 1000
       if ( passTrigger && passVtx && passPho && passJet && passMET ) {
                                                                 eventType |= (1 <<4) ;  //10000
                                                                 counter[4]++ ;
       }
       if ( passHLT )                                            eventType |= (1 <<5) ; // 100000

       ResetCuts() ;  // reset cuts from Datacard
       return eventType ;      

}

bool DPSelection::SignalSelection( bool isTightPhoton ) {

       counter[0]++ ;

       passL1  =  L1Filter() ;
       passHLT  = HLTFilter();
       passTrigger = ( UseL1 == 1 ) ? passL1 : passHLT ;
       if ( passTrigger ) counter[1]++ ;

       passVtx  = VertexFilter();
       if ( passTrigger && passVtx ) counter[2]++ ;

       // reset cuts to tight photon selection
       if ( isTightPhoton ) {
          ResetCuts( "PhotonCuts", 0, 90. ) ;  // pt
	  ResetCuts( "PhotonCuts", 1, 1.4 ) ;   // eta
	  ResetCuts( "PhotonIso",  0, 0.1 ) ;   // Trk Iso
	  ResetCuts( "PhotonIso",  1, 2.4 ) ;   // Ecal Et 
	  ResetCuts( "PhotonIso",  2, 0.05 ) ;  // Ecal Ratio
	  ResetCuts( "PhotonIso",  3, 2.4 ) ;   // Hcal Et
	  ResetCuts( "PhotonIso",  4, 0.05 ) ;  // Hcal Ratio
	  //ResetCuts( "PhotonCuts", 7, -2. ) ;   // seed time
       }
       passPho = PhotonFilter();  // true for selecting Isolation 
       if ( passTrigger && passVtx ) {
          int photonStop = GetPhotonCutFlow() ;
          for ( int i=0; i< photonStop ; i++) { 
              gCounter[i]++ ;
          }
       }
       if ( passTrigger && passVtx && passPho ) counter[3]++ ;

       passJet = JetMETFilter();
       passMET = CorrectMET();
       if ( passTrigger && passVtx && passPho && passJet ) counter[4]++ ;

       ResetCuts() ;  // reset cuts from Datacard

       //bool isSignal = ( passHLT && passVtx  && passPho && passJet && !passGJets ) ? true : false ;
       bool isSignal = ( passTrigger && passVtx  && passPho && passJet && passMET ) ? true : false ;
      
       return isSignal ;

}


bool DPSelection::GetEventStat( string flagName ) {

     if ( flagName == "L1" )       return passL1 ;
     else if ( flagName == "HLT" )      return passHLT ;
     else if ( flagName == "Triggger" ) return passTrigger ;
     else if ( flagName == "Vertex" )   return passVtx ;
     else if ( flagName == "Photon" )   return passPho ;
     else if ( flagName == "Jet" )      return passJet ;
     else if ( flagName == "MET" )      return passMET ;
     else    return false ;
}


void DPSelection::PrintCutFlow() {

     printf(" Input: %d,  trig: %d,  vtx: %d,  photon: %d,  jetMET: %d \n"
           , counter[0], counter[1], counter[2], counter[3], counter[4]) ;
     printf(" Photon Input: %d,   Pt: %d ,  Eta: %d,    H/E: %d,     sMin: %d,  dR_trk: %d,    tChi2: %d, sigmaIeta: %d, maxPt: %d \n"
                 , gCounter[0], gCounter[1], gCounter[2], gCounter[3], gCounter[4], gCounter[5], gCounter[6],   gCounter[7], gCounter[8] );

}

void DPSelection::ResetCuts( string cutName, vector<int>& cutId, vector<double>& newValue ) {

     for ( size_t i=0; i< cutId.size() ; i++ ) {
         if ( cutName == "PhotonCuts" )   photonCuts[ cutId[i] ]   = newValue[i] ;
         if ( cutName == "PhotonIso" )    photonIso[ cutId[i] ]    = newValue[i] ;
         if ( cutName == "PhotonPFIso" )  photonPFIso[ cutId[i] ]  = newValue[i] ;
         if ( cutName == "VertexCuts" )   vtxCuts[ cutId[i] ]      = newValue[i] ;
         if ( cutName == "ElectronCuts" ) electronCuts[ cutId[i] ] = newValue[i] ;
         if ( cutName == "JetCuts" )      jetCuts[ cutId[i] ]      = newValue[i] ;
         if ( cutName == "MuonCuts" )     muonCuts[ cutId[i] ]     = newValue[i] ;
     }

}

void DPSelection::ResetCuts( string cutName, int cutId, double newValue ) {

         if ( cutName == "PhotonCuts" )   photonCuts[ cutId ]   = newValue ;
         if ( cutName == "PhotonIso" )    photonIso[ cutId ]    = newValue ;
         if ( cutName == "PhotonPFIso" )  photonPFIso[ cutId ]  = newValue ;
         if ( cutName == "VertexCuts" )   vtxCuts[ cutId ]      = newValue ;
         if ( cutName == "ElectronCuts" ) electronCuts[ cutId ] = newValue ;
         if ( cutName == "JetCuts" )      jetCuts[ cutId ]      = newValue ;
         if ( cutName == "MuonCuts" )     muonCuts[ cutId ]     = newValue ;

}

void DPSelection::ResetCuts( string cutName ) {

    if ( cutName == "VertexCuts"   || cutName == "All" ) Input->GetParameters( "VertexCuts",   &vtxCuts );
    if ( cutName == "PhotonCuts"   || cutName == "All" ) Input->GetParameters( "PhotonCuts",   &photonCuts );
    if ( cutName == "PhotonIso"    || cutName == "All" ) Input->GetParameters( "PhotonIso",    &photonIso );
    if ( cutName == "PhotonPFIso"  || cutName == "All" ) Input->GetParameters( "PhotonPFIso",  &photonPFIso );
    if ( cutName == "ElectronCuts" || cutName == "All" ) Input->GetParameters( "ElectronCuts", &electronCuts );
    if ( cutName == "JetCuts"      || cutName == "All" ) Input->GetParameters( "JetCuts",      &jetCuts );
    if ( cutName == "MuonCuts"     || cutName == "All" ) Input->GetParameters( "MuonCuts",     &muonCuts );

}

void DPSelection::ResetCollection( string cutName ) {

    metCorrX = 0 ;
    metCorrY = 0 ;
    met1x =0 ; met1y = 0 ; met1E = 0 ;
    met2x =0 ; met2y = 0 ; met2E = 0 ;

    if ( cutName == "Photon"   || cutName == "All" ) phoV.clear() ;
    if ( cutName == "Electron" || cutName == "All" ) eleV.clear() ;
    if ( cutName == "Jet"      || cutName == "All" ) jetV.clear() ;
    if ( cutName == "Muon"     || cutName == "All" ) muV.clear() ;

}

void DPSelection::GetCollection( string collName, vector<objID>& coll ) {

   if ( collName == "Photon" ) {
      for ( size_t i=0; i< phoV.size() ; i++ ) coll.push_back(  phoV[i] )  ;
   }
   else if ( collName == "Jet" ) {
      for ( size_t i=0; i< jetV.size() ; i++ ) coll.push_back( jetV[i] )  ;
   }
   else if ( collName == "Muon" ) {
      for ( size_t i=0; i< muV.size() ; i++ ) coll.push_back( muV[i] )  ;
   }
   else if ( collName == "Electron" ) {
      for ( size_t i=0; i< eleV.size() ; i++ ) coll.push_back( eleV[i] )  ;
   }
   else {
      cout <<" no collection matched ! " <<endl ;
   }

}

void DPSelection::ResetCounter() {
   for ( int i =0 ; i< 8 ; i++) {
       counter[i] = 0 ;
       gCounter[i] = 0 ;
   }
}

bool DPSelection::HaloTag( double cscdPhi, double sMaj, double sMin, double eta ) {

     bool haloTag  = ( cscdPhi < 0.05 ) ? true : false  ;
     //if ( sMaj > 0.7 && cscdPhi < 0.1 && fabs( eta ) > 0.75 && fabs( eta ) < 1.47 ) haloTag = true;
     //if ( sMaj > 0.8 && sMaj < 1.65 && sMin < 0.2 && fabs( eta ) < 1.47 ) haloTag = true;

     return haloTag ;
}


bool DPSelection::SpikeTag( int nXtl, double sMaj, double sMin, double swissX, double eta ) {

    //bool spikeTag = ( nXtl < 7 || swissX > 0.9 ) ? true : false ;
    bool spikeTag = ( swissX > 0.9 ) ? true : false ;
    if ( sMaj < 0.6 && sMin < 0.17 && fabs(eta) < 1.47 ) spikeTag = true;

    return spikeTag ;
}

bool DPSelection::CosmicTag( double dtdEta , double dtdPhi ) {

     bool cosmicTag = ( dtdEta < 0.1 && dtdPhi < 0.1  ) ? true : false ;
     return cosmicTag ;

}

// return background prediction, upward and downward uncertainty
vector<double> DPSelection::ABCD_ABCD( vector<TH3D*>& hColls, vector<TH3D*>& hMIBs ) {

     //printf("\n ####### MET2 < 60 ########## \n") ;
     //vector<double> abcdef_= ABCD( hCol_A,    hCol_B,    hCol_C,    hCol_D,    hCol_E,    hCol_F ) ;
     //vector<double> abcdef_  = ABCD( hColls[0], hColls[1], hColls[2], hColls[3], hColls[4], hColls[5] ) ;
     printf("\n ####### MET2 > 60 ########## \n") ;
     //vector<double> abcdef= ABCD( hBg_A,    hBg_B,    hBg_C,    hBg_D,    hBg_E,    hBg_F ) ;
     vector<double> abcdef  = ABCD( hMIBs[0], hMIBs[1], hMIBs[2], hMIBs[3], hMIBs[4], hMIBs[5] ) ;
     printf("\n ####### Q_D ########## \n") ;
     vector<double> colD    = ABCD_Collision( hColls[5], hMIBs[5], hColls[3], hMIBs[3] ) ;
     printf("\n ####### Q_B ########## \n") ;
     vector<double> colB    = ABCD_Collision( hColls[5], hMIBs[5], hColls[1], hMIBs[1] ) ;

     double predict = ( abcdef[1] > colB[0] || abcdef[0] < 0.0001 ) ? (abcdef[1] - colB[0])*(abcdef[2]/abcdef[0]) + colD[0] : colD[0] ;

     pair<double,double> errB     = MathTools::ErrApnB( abcdef[1] , colB[0] , -1, -1, colB[1], colB[2] ) ;
     pair<double,double> errCovA  = MathTools::ErrAovB( abcdef[2], abcdef[0]) ;
     pair<double,double> errBCovA = MathTools::ErrAxB( (abcdef[1] - colB[0]), (abcdef[2]/abcdef[0])
                                                     , errB.first, errB.second, errCovA.first, errCovA.second ) ;
     pair<double,double> errFinal = MathTools::ErrApnB( (abcdef[1] - colB[0])*(abcdef[2]/abcdef[0]), colD[0]
                                                     , errBCovA.first, errBCovA.second, colD[1], colD[2] ) ;

   printf("\n ================ Final Result =================== \n") ;
   printf(" Observe :%.2f -> Predict : %.4f + %.4f - %.4f \n", abcdef[3], predict, errFinal.first , errFinal.second ) ;

   vector<double> result ;
   result.push_back( predict ) ;
   result.push_back( errFinal.first ) ;
   result.push_back( errFinal.second ) ;
   return result ;
}


vector<double> DPSelection::ABCD_Collision( TH3D* hF_A, TH3D* hF_B, TH3D* hF_C, TH3D* hF_D ) {

   printf("\n  =========== ABCD Method for Collision ============= \n") ;
   cout<<" ===  A  === "<<endl ;
   double rA = GetEstimation( hF_A ) ;
   cout<<" ===  B  === "<<endl ;
   double rB = GetEstimation( hF_B ) ;
   cout<<" ===  C  === "<<endl ;
   double rC = GetEstimation( hF_C ) ;
   cout<<" ===  D  === "<<endl ;
   double rD = GetEstimation( hF_D ) ;

   pair<double,double> errAB = MathTools::ErrAovB( rA, rB ) ;
   double predict = ( rA > 0. ) ? rC * ( rB / rA ) : 0. ;

   double sBA_u = errAB.first ;
   double sBA_d = errAB.second ;

   double s2u = (sBA_u*sBA_u)*(rC*rC) + (rC*rB*rB)/(rA*rA) ;
   double s2d = (sBA_d*sBA_d)*(rC*rC) + (rC*rB*rB)/(rA*rA) ;

   printf(" Predicted Collision background : %.2f + %.2f - %.2f ", predict , sqrt(s2u) , sqrt(s2d) ) ;
   printf(" Observed = %.2f \n", rD ) ;

   vector<double> vals ;
   vals.push_back( predict );
   vals.push_back( sqrt(s2u) );
   vals.push_back( sqrt(s2d) );
   return vals ;
}


// x is eta region , each is 0.28 , y is different sample, 0:total, 1:halo, 2: spike 3: cosmic
vector<double> DPSelection::ABCD( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD, TH3D* hE, TH3D* hF ) {

   // Tagging efficiency 
   Input->GetParameters("UseInFlight",   &useInFlight ) ;
   if ( useInFlight == 0 || haloEff.size() < 5 || spikeEff.size() < 5 || haloMis.size() < 5 || spikeMis.size() < 5 ) {
      printf(" Get Efficiency and fake rate from Datacard !! \n") ;
      Input->GetParameters("HaloEff",    &haloEff ) ;
      Input->GetParameters("SpikeEff",   &spikeEff ) ;
      Input->GetParameters("CosmicEff",  &cosEff ) ;
      // Mis-tag rate
      Input->GetParameters("HaloFake",   &haloMis ) ;
      Input->GetParameters("SpikeFake",  &spikeMis ) ;
      Input->GetParameters("CosmicFake", &cosMis ) ;
   }

   //  GetEstimation returns QCD components
   cout<<" ===  E  === "<<endl ;
   double rE = GetEstimation( hE ) ;
   cout<<" ===  F  === "<<endl ;
   double rF = GetEstimation( hF ) ;
   //printf("=== D/F (%.2f/%.2f) = %.2f  + %.4f - %.4f \n", rF, rE, rF/rE, errEF.first, errEF.second ) ;
   cout<<" ===  A  === "<<endl ;
   double rA = GetEstimation( hA ) ;
   cout<<" ===  B  === "<<endl ;
   double rB = GetEstimation( hB ) ;
   cout<<" ===  C  === "<<endl ;
   double rC = GetEstimation( hC ) ;
   cout<<" ===  D  === "<<endl ;
   double rD = GetEstimation( hD ) ;

   pair<double,double> errAB = MathTools::ErrAovB( rB, rA ) ;
   pair<double,double> errCD = MathTools::ErrAovB( rD, rC ) ;
   pair<double,double> errFD = MathTools::ErrAovB( rD, rF ) ;
   double predict = ( rA > 0. ) ? rC * ( rB / rA ) : 0. ;

   if ( rA < 0.0001 ) { cout<<" Residual Background ABCD Fail ! " <<endl ;
   } else {
          printf(" B/A (%.2f/%.2f) = %.2f  + %.2f - %.2f \n", rB, rA, rB/rA, errAB.first , errAB.second ) ;
          printf(" D/C (%.2f/%.2f) = %.2f  + %.2f - %.2f \n", rD, rC, rD/rC, errCD.first , errCD.second ) ;
          printf(" D/F (%.2f/%.2f) = %.8f  + %.8f - %.8f \n", rD, rF, rD/rF, errFD.first , errFD.second ) ;
   }

   printf(" Observe :%.2f -> Predict : %.2f \n", rD, predict ) ;

   vector<double> vals ;
   vals.push_back( rA ) ;
   vals.push_back( rB ) ;
   vals.push_back( rC ) ;
   vals.push_back( rD ) ;
   vals.push_back( rE ) ;
   vals.push_back( rF ) ;
   return vals ;
}


// Return the sum of spike and halo component or QCD component of background
// xbin : 5 eta region ( 0 ~ 1.4 ) , bin width : 0.28
// ybin : [bin1]: Total count , [bin2]: Halo , [bin3]: Spike, [bin4]: Cosmic
double DPSelection::GetEstimation( TH3D* hCount, bool getQCD ) {

   double ghostB = 0 ;
   double Bg_exp = 0 ;
   double residual = 0 ;
   printf("| eta |   spike    |    halo    |   cosmic   |  QCD  |  Total  |\n" ) ;
   float sum[9] = {0.} ;
   // 5 eta bins
   for ( int i=0; i< 5; i++ ) {

       double nB = 0 ;
       double nH = 0 ;
       double nS = 0 ;
       double nC = 0 ;
       // 3 jet multiplicity
       for ( int j=0; j<3; j++ ) {

           if ( j < jetCuts[2] || j > jetCuts[3] ) continue ;
           nB += hCount->GetBinContent( i+1, 1, j+1 ) ; // total number in control region 
           nH += hCount->GetBinContent( i+1, 2, j+1 ) ; // number of halo tagged in control region
           nS += hCount->GetBinContent( i+1, 3, j+1 ) ; // number of spike tagged in control region
           nC += hCount->GetBinContent( i+1, 4, j+1 ) ; // number of cosmic tagged in control region
       }

       vector<double> bgV = GetComponent( i, nB, nH, nS, nC ) ;
       ghostB   += bgV[0] ;  // spike
       ghostB   += bgV[1] ;  // halo
       ghostB   += bgV[2] ; // cosmic
       residual += bgV[3] ; // qcd
       Bg_exp   += nB ;
       //printf(" eta(%d) : spike:%f , halo:%f , cosmic:%f , QCD:%f  from %f \n ", i, bgV[0], bgV[1], bgV[2], bgV[3], nB ) ;
       //printf(" eta  |  spike  |   halo   |  cosmic  |  QCD  |  from  |\n " ) ;
       printf("|  %d  | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f | %4.f |\n", i, bgV[0], nS, bgV[1], nH, bgV[2], nC, bgV[3], nB ) ;
       sum[0] += bgV[0] ;
       sum[1] +=     nS ;
       sum[2] += bgV[1] ;
       sum[3] +=     nH ;
       sum[4] += bgV[2] ;
       sum[5] +=     nC ;
       sum[6] += bgV[3] ;
       sum[7] += nB-nS-nH-nC ;
       sum[8] +=     nB ;
   }

   printf("| sum | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) |  %4.f |\n",
                        sum[0],sum[1], sum[2],sum[3], sum[4],sum[5], sum[6],sum[7], sum[8]  ) ;

   printf(" Background :  QCD:%f , Ghost:%f -> %f \n ", residual, ghostB, Bg_exp ) ;

   if ( getQCD ) return residual ;
   else          return Bg_exp ;
}


// Return the background components in background control region ( MET < 60 GeV )
// Return [0]:spike , [1]:halo , [2]:QCD
// Input : number of event in background control region at t > 2 ns region 
// B12 : total background , h_B12 : halo-tagged events , s_B12 : spike tagged events
vector<double> DPSelection::GetComponent( int eta_i, int B12, int h_B12, int s_B12, int c_B12 ) {

  vector<double> result = GetComponent( eta_i, (double)B12, (double)h_B12, (double)s_B12 , (double)c_B12 ) ;
  return result ;

}

// Get halo/spike/QCD component using tagging efficiency and mis-tagging rate 
vector<double> DPSelection::GetComponent( int eta_i, double B0 , double h_B, double s_B, double c_B ) {

       double h = haloEff[ eta_i ] ;  // halo
       double s = spikeEff[ eta_i ] ;  // spike
       double c = cosEff[ eta_i ] ;  // comsic

       double m = haloMis[ eta_i ] ;   // halo
       double n = spikeMis[ eta_i ] ;   // spike
       double o = cosMis[ eta_i ] ;   // cosmic

       // cosmic content 
       double C_ = (c_B - o*B0 ) / ( c - o ) ;
       C_ = ( C_ < 0. ) ? 0 : C_ ;
       // spike content
       double S_ = (s_B - n*B0 ) / ( s - n ) ;
       S_ = ( S_ < 0. ) ? 0 : S_ ;
       // halo content 
       double H_ = (h_B - m*B0 ) / ( h - m ) ;
       H_ = ( H_ < 0. ) ? 0 : H_ ;
       // QCD content 
       double Q_ = (double)(B0) - S_ - H_ - C_;
       Q_ = ( Q_ < 0. ) ? 0 : Q_ ;

       //printf("(%d) B12 %d = (S12: %.2f ) + ( H12: %.2f ) + ( Q12: %.2f )\n ", eta_i, B12, S12, H12, Q12 ) ;
       vector<double> BG12 ;
       BG12.push_back( S_ ) ;
       BG12.push_back( H_ ) ;
       BG12.push_back( C_ ) ;
       BG12.push_back( Q_ ) ;
       return BG12 ;
}

void DPSelection::SetArray( int a[], int b[], int size ) {
   for ( int i=0; i< size; i++ )   a[i] = b[i] ;
}

void DPSelection::SetArray( float a[], float b[], int size ) {
   for ( int i=0; i< size; i++ )   a[i] = b[i] ;
}


