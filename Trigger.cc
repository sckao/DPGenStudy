#include "Trigger.h"

Trigger::Trigger( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw( datacardfile ) ;

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 
  Input->GetParameters("ThresPhoMET",   &thresPhoMET ) ; 
  Input->GetParameters("MinBinContent", &minBinContent ) ; 

}

Trigger::~Trigger() {

  delete select ;
  delete Input  ;
  delete h_draw ;
  cout<<" done ! "<<endl ;

}

// analysis template
void Trigger::ReadTree( string dataName ) { 

   TTree* tr = Input->TreeMap( dataName );

   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nElectrons",  &nElectrons);
   tr->SetBranchAddress("triggered",   &triggered);
   tr->SetBranchAddress("L1a",         &L1a );
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("runId",       &runId);

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("muE",         muE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("pt_TrkPho",   pt_TrkPho );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("aveTimeErr",  aveTimeErr );
   tr->SetBranchAddress("aveTimeErr1", aveTimeErr1 );

   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );

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

   TH1D* h_gPt      = new TH1D("h_gPt",     "Leading Photon Pt           ", 40,  50, 250);
   TH1D* h_gPt_hlt  = new TH1D("h_gPt_hlt", "Leading Photon Pt passed HLT", 40,  50, 250);
   TH1D* h_met      = new TH1D("h_met",     "MET distribution           ", 40,  0, 200);
   TH1D* h_met_hlt  = new TH1D("h_met_hlt", "MET distribution pssed HLT ", 40,  0, 200);
   TH1D* h_dRTrkPho = new TH1D("h_dRTrkPho", " mindR(track, photon )", 100,  0, 10);
   TH1D* h_ptTrkPho = new TH1D("h_ptTrkPho", " pt of track near photon ", 100,  0, 100 );
   TH1D* h_nJets    = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);

   TH1D* h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   TH1D* h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   TH1D* h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
   TH1D* h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   TH1D* h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   TH1D* h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );


   for ( int i=0; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );

       // check isolation variables
       for ( int k=0; k< nPhotons; k++) {
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
           h_TrkIso->Fill( phoTrkIso[k] );
	   h_EcalIso->Fill( phoEcalIso[k] );
	   h_HcalIso->Fill( phoHcalIso[k] );
	   h_TrkIsoR->Fill( phoTrkIso[k] / gP4_.Pt() );
	   h_EcalIsoR->Fill( phoEcalIso[k] / gP4_.E() );
	   h_HcalIsoR->Fill( phoHcalIso[k] / gP4_.E() );
       }

       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass_vtx  = select->VertexFilter();
       bool pass_jet  = select->JetMETFilter();
       bool pass_pho = select->PhotonFilter( true );  // true for applying Isolation 
       bool pass_hlt = select->HLTFilter();
       //bool pass_mu  = select->MuonFilter();
       select->MuonFilter();
       if ( !pass_hlt || !pass_pho || !pass_vtx || !pass_jet ) continue ;
       // only look at 1 photon events
       phoV.clear() ;
       select->GetCollection( "Photon", phoV );
       if ( phoV.size() != 1 ) continue ; 
       muonV.clear() ;
       select->GetCollection( "Muon", muonV );
       jetV.clear() ;
       select->GetCollection( "Jet", jetV );
       //if ( jetV.size() == 0 && muonV.size() == 0 ) continue ; 
       
       // Photon and MET information
       TLorentzVector met( metPx, metPy, 0, metE)  ;
       //TLorentzVector gP4 = TLorentzVector( phoV[0], phoPy[0], phoPz[0], phoE[0] ) ;
       TLorentzVector gP4 = phoV[0].second ;
       // reject spike photons
       if ( fSpike[ phoV[0].first ] != 0 ) continue ;
       //if ( fSpike[ phoV[0].first ] > 0.1 || fSpike[ phoV[0].first ] < -0.1 ) continue ;



       // min_dR( track, photon)
       h_dRTrkPho->Fill( dR_TrkPho[0] ) ;
       h_ptTrkPho->Fill( pt_TrkPho[0] ) ;

       // jet multiplicity
       h_nJets->Fill( jetV.size() ) ;

       if ( gP4.Pt() > thresPhoMET[0] ) {
          double theMET = ( met.Pt() > 199 ) ? 199.9 :  met.Pt() ;
          h_met->Fill( theMET );
	  if ( triggered == 3 ) h_met_hlt->Fill( theMET );
       }
       // no actual jet requirement , only cut on MET
       if ( met.Et() > thresPhoMET[1] ) { 
	  double gammaPt = ( gP4.Pt() > 249 ) ? 249.9 : gP4.Pt() ;
	  h_gPt->Fill( gammaPt );
	  if ( triggered == 3 ) h_gPt_hlt->Fill( gammaPt );
       }

   } // end of event looping


   TLegend* leg1  = new TLegend(.55, .73, .95, .90 );
   leg1->Clear();
   TString IntStr0 = "HLT_PFMET150   = " ;
   TString IntStr1 = "HLT_DP65_MET25 = " ;
   Int_t nL1A = h_gPt->Integral() ;
   Int_t nHLT = h_gPt_hlt->Integral() ;
   IntStr0 += nL1A ;
   IntStr1 += nHLT ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_gPt,     IntStr0,  "L");
   leg1->AddEntry( h_gPt_hlt, IntStr1,  "L");
 
   h_draw->Draw(       h_gPt, "", " Pt (GeV/c)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h_gPt_hlt, "PhotonPt", 0.75, 4, 1,leg1 ) ;

   leg1->Clear();
   IntStr0 = "HLT_Photon150  = " ;
   IntStr1 = "HLT_DP65_MET25 = " ;
   nL1A = h_met->Integral() ;
   nHLT = h_met_hlt->Integral() ;
   IntStr0 += nL1A ;
   IntStr1 += nHLT ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_met,     IntStr0,  "L");
   leg1->AddEntry( h_met_hlt, IntStr1,  "L");
   h_draw->Draw(       h_met, "", " MET (GeV)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h_met_hlt, " MET", 0.75, 4, 1, leg1 ) ;

   // Efficiency
   h_draw->EffPlot( h_gPt_hlt, h_gPt, "Photon Pt (GeV/c) ", minBinContent[0], 1, -1,  "PhotonPtEff" );
   h_draw->EffPlot( h_met_hlt, h_met, "MET (GeV)    ",      minBinContent[1], 1, -1,  "PFMETEff" );

   // mindR(Track,photon)
   h_draw->CreateNxM( "TrkPho", 1,2 );
   h_draw->DrawNxM( 1, h_dRTrkPho,   "",   "", "", 1, false );
   h_draw->DrawNxM( 2, h_ptTrkPho,   "",   "", "", 1, true );

   // Isolation
   h_draw->CreateNxM( "Isolations", 2,3 );
   h_draw->DrawNxM( 1, h_TrkIso,   "Track Isolation ",       "", "logY", 1, false );
   h_draw->DrawNxM( 2, h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 3, h_EcalIso,  "Ecal Isolation ",        "", "logY", 2, false );
   h_draw->DrawNxM( 4, h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 5, h_HcalIso,  "Hcal Isolation ",        "", "logY", 4, false );
   h_draw->DrawNxM( 6, h_HcalIsoR, "Hcal Isolation Ratio",   "", "logY", 4, true );

   // jet multiplicity
   h_draw->Draw( h_nJets, "nJets", " Number of Jets ", "", "logY", 0.95, 1 ) ;
}  


