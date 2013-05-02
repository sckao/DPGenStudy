#include "DPSelection.h"

static bool PtDecreasing( objID s1, objID s2) { return ( s1.second.Pt() > s2.second.Pt() ); }


DPSelection::DPSelection( string datacardfile ){

  // SC's getParameters method
  // If you don't like to use the Datacard.txt , markout this section and use CMSSW method
  Input = new AnaInput( datacardfile );
  
  Input->GetParameters( "VertexCuts",   &vtxCuts );
  Input->GetParameters( "PhotonCuts",   &photonCuts );
  Input->GetParameters( "UsePFIso",     &usePFIso ) ;
  Input->GetParameters( "PhotonIso",    &photonIso );
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
  passJetMET  = false ;  

  select_met = -1 ; 
}

DPSelection::~DPSelection(){

  delete Input;
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

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   // PFISO
   if ( usePFIso == 1 ) { 
      tr->SetBranchAddress("cHadIso",     cHadIso );
      tr->SetBranchAddress("nHadIso",     nHadIso );
      tr->SetBranchAddress("photIso",     photIso );
   }
   tr->SetBranchAddress("sigmaIeta",   sigmaIeta );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("phoHoverE",   phoHovE );
   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("fSpike",      fSpike );

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

   tr->SetBranchAddress("vtxX",       vtxX );
   tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   tr->SetBranchAddress("vtxChi2",    vtxChi2 );
   tr->SetBranchAddress("vtxNdof",    vtxNdof );
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
       int nG[9] = { 0. } ;

       // 0. photon cuts
       phoV.clear() ;
       double maxPt = 0 ;
       vector<bool> shadow( nPhotons ,false );
       vector<bool> skipPhoIso( nPhotons , false );
       
       for ( int j=0 ; j< nPhotons; j++ ) {
           nG[0]++ ;
           TLorentzVector phoP4( phoPx[j], phoPy[j], phoPz[j], phoE[j] ) ;
           double egScale = 1. ;
           if ( systType == 5 ) egScale = ( fabs(phoP4.Eta()) < 1.479 ) ? 1.006 : 1.015 ;
           if ( systType == 6 ) egScale = ( fabs(phoP4.Eta()) < 1.479 ) ? 0.994 : 0.985 ;
           phoP4 = phoP4 * egScale ;

           if ( shadow[j] ) continue ;

	   if ( fabs(fSpike[j]) > 0.001 ) continue ;
           if (        phoP4.Pt() < photonCuts[0] )          continue ;
           if ( fabs(phoP4.Eta()) > photonCuts[1] )          continue ;
           nG[1]++ ;

           //if ( ( phoHcalIso[j]/phoP4.Pt() + phoHovE[j] ) * phoE[j] >= photonCuts[2] )      continue ;
           if ( phoHovE[j] > photonCuts[2] ) continue ;
           nG[2]++ ;
           if ( sMinPho[j] < photonCuts[5] || sMinPho[j] > photonCuts[6] )                continue ;
           nG[3]++ ;
           if ( dR_TrkPho[j] < photonCuts[7] ) continue; 
           nG[4]++ ;

           // Reject nearby photon 
           /*
           for ( int k = 1 ; k < nPhotons ; k++ ) {
               if (  k == j || k < j ) continue ;
                  TLorentzVector phoP4_( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
                  phoP4_ = phoP4_ * egScale ;
                  if ( phoP4.DeltaR( phoP4_ ) < 0.2 )  { 
                     shadow[k]     = true ;
                     skipPhoIso[j] = true ;
                  }
           }
           */

           //if ( phoTime[j] < photonCuts[7] ) continue ; 
           // Isolation
           if ( usePFIso == 1 ) {
              Input->GetParameters( "PhotonPFIso",     &photonPFIso ) ;
	      if ( cHadIso[j] >= photonPFIso[0] ) continue ;  // photIso
	      if ( nHadIso[j] >= photonPFIso[1] + ( 0.04*phoP4.Pt()   ) ) continue ;  // chargedHadron
              if ( !skipPhoIso[j] ) {
	         if ( photIso[j] >= photonPFIso[2] + ( 0.005*phoP4.Pt() ) ) continue ;  // neutralHadron
              }
           } 
           if ( usePFIso == 2 ) {
              if ( phoTrkIso[j] / phoP4.Pt()  >= photonIso[0] )                                continue ;
              if ( phoEcalIso[j] >= photonIso[1] || phoEcalIso[j] / phoE[j] >= photonIso[2] )  continue ;
              if ( phoHcalIso[j] >= photonIso[3] || phoHcalIso[j] / phoE[j] >= photonIso[4] )  continue ;
           }
           nG[5]++ ;

           // check the isolation -- using dR_gj
           double dR_gj = 999. ;
           for ( size_t k=0 ; k< jetV.size() ; k++ ) {
               if ( phoP4.DeltaR( jetV[k].second ) < dR_gj )  dR_gj  = phoP4.DeltaR( jetV[k].second ) ;
           }
           if ( dR_gj < photonCuts[3] ) continue ;
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

       if ( (int)phoV.size() < photonCuts[4] || maxPt < photonCuts[8] ) pass = false ;
       if ( phoV.size() > 1 ) sort( phoV.begin(), phoV.end(), PtDecreasing );
       if ( pass ) photonCutFlow = 8 ;

       return pass ;
}

bool DPSelection::VertexFilter() { 

     bool pass =  true ;
     // 1. vertex cuts
     int nVtx = 0 ;
     for ( int j=0 ; j< nVertices; j++ ) {

         double vtxRho = sqrt( (vtxX[j]*vtxX[j]) + (vtxY[j]*vtxY[j]) ); 
	 if ( nVertices < 1 )                continue ;
	 if ( vtxNdof[j]     < vtxCuts[0] )  continue ;
	 if ( fabs(vtxZ[j]) >= vtxCuts[1] )  continue ;
	 if ( vtxRho        >= vtxCuts[2] )  continue ;
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
         double jer_up = ( jp4.Pt() + jerUnc[j] ) / jp4.Pt() ;
         double jer_dw = ( jp4.Pt() - jerUnc[j] ) / jp4.Pt() ;
         if ( systType == 1 ) jp4 = jp4 * jer_up ;
         if ( systType == 2 ) jp4 = jp4 * jer_dw ;
         if ( systType == 3 ) jp4 = jp4 * ( 1. + jecUnc[j] ) ;
         if ( systType == 4 ) jp4 = jp4 * ( 1. - jecUnc[j] ) ;

	 if ( jp4.Pt()        < jetCuts[0] ) continue ;
	 if ( fabs(jp4.Eta()) > jetCuts[1] ) continue ;
           
         // Jet ID cuts
         if ( usePFJetClean ) { 
            if ( jetNDau[j] < (double)   2 )  continue ;
	    if ( jetCEF[j] >= (double)0.99 )  continue ;
	    if ( jetNHF[j] >= (double)0.99 )  continue ;
	    if ( jetNEF[j] >= (double)0.99 )  continue ;
	    if ( fabs( jp4.Eta() ) < 2.4 && jetCM[j]  <= 0 ) continue ;
         }

	 //double dR_gj = 999. ;
	 //for ( size_t k=0; k< phoV.size() ; k++) {
	 //    if ( phoV[k].second.DeltaR( jp4 ) < dR_gj )  dR_gj  = phoV[k].second.DeltaR( jp4 ) ;
	 //}
	 //if ( dR_gj < photonCuts[3] ) continue ;
	 jetV.push_back( make_pair( j, jp4 ) );

     }
     int nu_Jets = (int)jetV.size() ;
     if ( nu_Jets < (int)jetCuts[2] || nu_Jets > (int)jetCuts[3] )      pass = false ;

     // 2. met selection
     double met_X(0) , met_Y(0) , met_E(0) ;
     if ( systType == 0 ) { 
          met_X = metPx ;
          met_Y = metPy ;
     } 
     if ( systType == 1 || systType == 2 ) { 
          double ud = ( systType == 1 ) ? 1 : -1 ;
          met_X =  metPx - ( ud * met_dx1 ) ;
	  met_Y =  metPy - ( ud * met_dy1 ) ;
     }             
     if ( systType == 3 || systType == 4 ) { 
          double ud = ( systType == 3 ) ? 1 : -1 ;
          met_X =  metPx - ( ud * met_dx2 ) ;
	  met_Y =  metPy - ( ud * met_dy2 ) ;
     }             
     if ( systType == 5 || systType == 6 ) { 
          double ud = ( systType == 5 ) ? 1 : -1 ;
          met_X =  metPx - ( ud * met_dx3 ) ;
	  met_Y =  metPy - ( ud * met_dy3 ) ;
     }             
     met_E  =  sqrt( (met_X*met_X) + (met_Y*met_Y) ) ;
     TLorentzVector metp4 = TLorentzVector( met_X, met_Y, 0., met_E ) ;
     select_met = metp4.Et() ;

     if ( jetCuts[4] >= 0 &&  metp4.Et() < jetCuts[4] )         pass = false ;
     if ( jetCuts[4]  < 0 &&  metp4.Et() > fabs( jetCuts[4] ) ) pass = false ;
     if ( jetV.size() > 1 ) sort( jetV.begin(), jetV.end(), PtDecreasing ) ;
 
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

         eleV.push_back( make_pair( j, eP4.Pt()) ) ;
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

         muV.push_back( make_pair( j, mP4.Pt() ) ) ;
     }
     if ( muV.size() < 1 ) pass = false ;
     return pass ;
}

bool DPSelection::GammaJetsBackground( ) {

    bool pass = true ;

    if ( jetV.size() < 1 ) return false ;
    if ( phoV.size() < 1 ) return false ;

    double dR   = phoV[0].second.DeltaR( jetV[0].second ) ;
    double ratio1 = jetV[0].second.Pt() / phoV[0].second.Pt() ;

    if ( dR <= (2*3.141593/3) )           pass = false ;
    if ( ratio1 >= 1.3 || ratio1 <= 0.7 ) pass = false ;

    if ( jetV.size() > 1 ) {
       double ratio2 = jetV[1].second.Pt() / phoV[0].second.Pt() ;
       if ( ratio2 >= 0.1 ) pass = false ;
    }

    return pass ;

}

bool DPSelection::GammaJetsControlSample( bool isTightPhoton ) {

       passHLT  = HLTFilter();
       passVtx  = VertexFilter();

       // reset cuts to tight photon selection
       if ( isTightPhoton ) {
          ResetCuts( "PhotonCuts", 0, 100. ) ;  // pt
	  ResetCuts( "PhotonCuts", 1, 1.4 ) ;   // eta
	  ResetCuts( "PhotonCuts", 7, -2. ) ;   // seed time
	  ResetCuts( "PhotonIso",  0, 0.1 ) ;   // Trk Iso
	  ResetCuts( "PhotonIso",  1, 2.4 ) ;   // Ecal Et 
	  ResetCuts( "PhotonIso",  2, 0.05 ) ;  // Ecal Ratio
	  ResetCuts( "PhotonIso",  3, 2.4 ) ;   // Hcal Et
	  ResetCuts( "PhotonIso",  4, 0.05 ) ;  // Hcal Ratio
       }
       passPho = PhotonFilter();

       ResetCuts( "JetCuts",  2, 1 ) ;  // Min Num of Jets
       ResetCuts( "JetCuts",  3, 2 ) ;  // Max Num of Jets
       passJet = JetMETFilter();

       //bool passGJets = GammaJetsBackground() ;
       bool passGJets = false ;

       ResetCuts() ;  // reset cuts from Datacard

       bool isGJet = ( passHLT && passVtx  && passPho && passJet && passGJets ) ? true : false ;
       return isGJet ;
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
          ResetCuts( "PhotonCuts", 0, 50. ) ;  // pt
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

       passJetMET = JetMETFilter();
       if ( passTrigger && passVtx && passPho && passJet ) counter[4]++ ;

       ResetCuts() ;  // reset cuts from Datacard

       //bool isSignal = ( passHLT && passVtx  && passPho && passJet && !passGJets ) ? true : false ;
       bool isSignal = ( passTrigger && passVtx  && passPho && passJetMET ) ? true : false ;
      
       return isSignal ;

}

bool DPSelection::ControlSelection() {

       counter[0]++ ;

       passL1  =  L1Filter() ;
       passHLT  = HLTFilter();
       passTrigger = ( UseL1 == 1 ) ? passL1 : passHLT ;
       passVtx  = VertexFilter();

       // JER (systType 1 and 2 ) are only varied for MC  
       if ( systType == 1 ||   systType == 2 )  systType = 0 ;

       passPho = PhotonFilter();  // true for selecting Isolation 
       if ( passTrigger && passVtx ) {
          int photonStop = GetPhotonCutFlow() ;
          for ( int i=0; i< photonStop ; i++) { 
              gCounter[i]++ ;
          }
       }
       JetMETFilter();

       ResetCuts() ;  // reset cuts from Datacard

       bool isSignal = ( passTrigger && passVtx  && passPho ) ? true : false ;
      
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
     else if ( flagName == "JetMET" )   return passJetMET ;
     else    return false ;
}

bool DPSelection::MCSignalSelection( bool isTightPhoton ) {

       counter[0]++ ;

       // Trigger Selection
       passL1  =  L1Filter() ;
       passTrigger = ( UseL1 == 1 ) ? passL1 : true ;
       if ( passTrigger ) counter[1]++ ;

       // Vertex Selection
       passVtx  = VertexFilter();
       if ( passTrigger && passVtx ) counter[2]++ ;

       // Set systematic setting 
       if ( systType != 1 ||   systType != 2 )  systType = 0 ;

       // reset cuts to tight photon selection
       if ( isTightPhoton ) {
          ResetCuts( "PhotonCuts", 0, 50. ) ;  // pt
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
       if ( passTrigger && passVtx && passPho && passJet ) counter[4]++ ;

       ResetCuts() ;  // reset cuts from Datacard

       //bool isSignal = ( passTrigger && passVtx  && passPho && passJet ) ? true : false ;
       bool isSignal = ( passTrigger && passVtx  && passPho ) ? true : false ;
      
       // Reset systematic setting after MC selection
       Input->GetParameters( "SystType",     &systType ) ;

       return isSignal ;

}

void DPSelection::PrintCutFlow() {

     printf(" Input: %d,  trig: %d,  vtx: %d,  photon: %d,  jetMET: %d \n"
           , counter[0], counter[1], counter[2], counter[3], counter[4]) ;
     printf(" Photon Input: %d, PtEta: %d, H/E: %d, sMin: %d, dR_trk: %d, Iso: %d, dR_jet: %d, MaxPt: %d, sigmaIeta: %d \n"
      , gCounter[0], gCounter[1], gCounter[2], gCounter[3], gCounter[4], gCounter[5], gCounter[6], gCounter[7], gCounter[8] );

}

bool DPSelection::QCDControlSample() {

       passHLT  = HLTFilter();
       passVtx  = VertexFilter();
       // reset cuts to tight photon selection
       ResetCuts( "PhotonCuts", 0, 100. ) ;  // pt
       ResetCuts( "PhotonCuts", 1, 1.4 ) ;   // eta
       ResetCuts( "PhotonCuts", 7, -2. ) ;   // seed time
       ResetCuts( "PhotonIso",  0, 0.1 ) ;   // Trk Iso
       ResetCuts( "PhotonIso",  1, 2.4 ) ;   // Ecal Et 
       ResetCuts( "PhotonIso",  2, 0.05 ) ;  // Ecal Ratio
       ResetCuts( "PhotonIso",  3, 2.4 ) ;   // Hcal Et
       ResetCuts( "PhotonIso",  4, 0.05 ) ;  // Hcal Ratio
       bool passTight = PhotonFilter();
 
       ResetCuts( "PhotonCuts", 0, 100. ) ; // pt
       ResetCuts( "PhotonCuts", 1, 1.4 ) ;  // eta
       ResetCuts( "PhotonIso",  0, 0.2 ) ;  // Trk Iso
       ResetCuts( "PhotonIso",  1, 4.5 ) ;  // Ecal Et 
       ResetCuts( "PhotonIso",  2, 0.1 ) ;  // Ecal Ratio
       ResetCuts( "PhotonIso",  3, 4.0 ) ;  // Hcal Et
       ResetCuts( "PhotonIso",  4, 0.1 ) ;  // Hcal Ratio
       passPho = PhotonFilter();

       ResetCuts( "JetCuts",  2, 3 ) ;  // Min Num of Jets
       passJet = JetMETFilter();

       //bool passGJets = GammaJetsBackground() ;

       ResetCuts() ;  // reset cuts from Datacard

       bool isQCD = ( passHLT && passVtx  && passPho && passJet && !passTight ) ? true : false ;

       return isQCD ;
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

    if ( cutName == "Photon"   || cutName == "All" ) phoV.clear() ;
    if ( cutName == "Electron" || cutName == "All" ) eleV.clear() ;
    if ( cutName == "Jet"      || cutName == "All" ) jetV.clear() ;
    if ( cutName == "Muon"     || cutName == "All" ) muV.clear() ;
    if ( cutName == "MET"      || cutName == "All" ) select_met = -1 ;

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

