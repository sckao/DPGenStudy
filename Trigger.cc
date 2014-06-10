#include "Trigger.h"

Trigger::Trigger( string datacardfile ){

  //Input  = new AnaInput( datacardfile );
  Input = AnaInput::Instance() ;
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw() ;

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ;
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  
  //Input->GetParameters("RootFiles",     &rfolder ) ; 

  nX0    = 0 ;
  n2X0_g = 0 ;
  n1X0_g = 0 ;
  n0X0_g = 0 ;
}

Trigger::~Trigger() {

  cout<<" Output historams written ! "<<endl ;
  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  if ( isData == 0 ) printf(" nX0 = %d  di-Photon = %d single-photon = %d zero-Photon = %d \n", nX0, n2X0_g, n1X0_g, n0X0_g ) ;
  delete select ;
  //delete Input  ;
  delete h_draw ;
  cout<<" done ! "<<endl ;

}

// analysis template
void Trigger::ReadTree( string dataName ) { 

   gSystem->mkdir( hfolder.c_str() );
   TString Path_fName = hfolder + hfName + ".root" ;
   theFile = new TFile( Path_fName, "RECREATE" );
   theFile->cd() ;

   TTree* tr   = Input->GetTree( dataName, "DPAnalysis" );
   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nElectrons",  &nElectrons);
   tr->SetBranchAddress("triggered",   &triggered);
   tr->SetBranchAddress("L1a",         &L1a );
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("totalNVtx",   &totalNVtx);
   tr->SetBranchAddress("runId",       &runId);

   tr->SetBranchAddress("met0Px",      &metPx );
   tr->SetBranchAddress("met0Py",      &metPy );
   tr->SetBranchAddress("met0",        &metE );

   tr->SetBranchAddress("t_metPx",     &t_metPx );
   tr->SetBranchAddress("t_metPy",     &t_metPy );
   tr->SetBranchAddress("t_met",       &t_metE );
   tr->SetBranchAddress("t_metdR",     &t_metdR );
   tr->SetBranchAddress("t_phoPx",     &t_phoPx );
   tr->SetBranchAddress("t_phoPy",     &t_phoPy );
   tr->SetBranchAddress("t_phoPz",     &t_phoPz );
   tr->SetBranchAddress("t_phoE",      &t_phoE );
   tr->SetBranchAddress("t_phodR",     &t_phodR );

   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("pt_TrkPho",   pt_TrkPho );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("dtdPhi",      dtdPhi );
   tr->SetBranchAddress("dtdEta",      dtdEta );

   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("phoTrkIso",   phoTrkIso );
   tr->SetBranchAddress("phoEcalIso",  phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  phoHcalIso );
   // PFISO
   tr->SetBranchAddress("cHadIso",     cHadIso );
   tr->SetBranchAddress("nHadIso",     nHadIso );
   tr->SetBranchAddress("photIso",     photIso );
   tr->SetBranchAddress("phoHoverE",   phoHovE );

   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("nBC",         nBC );

   //tr->SetBranchAddress("vtxX",       vtxX );
   //tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   
   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );

   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genM",        genM );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );


   select->Init( tr1 ) ;
   //setRtupleAddresses( tr, rt );

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   //Raw Information
   h_gPt      = new TH1D("h_gPt",     "Leading Photon Pt   ", 42,  40, 250);
   h_trg_gPt  = new TH1D("h_trg_gPt", "hltPhoton65 Trigger Object Pt", 41,  45, 250);
   dR_TrgReco_Pho = new TH1D("dR_TrgReco_Pho", " dR( trg, Reco ) Photon", 50, 0., 1. );
   dR_TrgReco_Met = new TH1D("dR_TrgReco_Met", " dR( trg, Reco ) PFMET", 50, 0., 1. );

   // Efficiency 
   h_gPt_sel  = new TH1D("h_gPt_sel", "Selected Photon Pt  ", 42,  40, 250);
   h_gPt_trg  = new TH1D("h_gPt_trg", "Selected Photon Pt & trigger hltPhoton65Filter", 42,  40, 250);

   h_met      = new TH1D("h_met",     "PFMET distribution           ", 40,  0, 200);
   h_met_sel  = new TH1D("h_met_sel", "Selected PFMET distribution           ", 40,  0, 200);
   h_trg_met  = new TH1D("h_trg_met", "hltPFMET25 Trigger Object    ", 40,  0, 200);
   h_met_trg  = new TH1D("h_met_trg", "PFMET distribution passed hltPFMET25 ", 40,  0, 200);

   hEff_Sel   = new TH2D("hEff_Sel", " Selected  ", 42,  40, 250, 40,  0, 200 ) ;
   hEff_Trg   = new TH2D("hEff_Trg", " Triggered ", 42,  40, 250, 40,  0, 200 ) ;
   hEff_2D    = new TH2D("hEff_2D",  "2D Efficiency", 42,  40, 250, 40,  0, 200 ) ;

   hTime_sel  = new TH1D("hTime_sel", " Ecal Time", 100,  -5 , 5 );

   // 
   dR_Pho90 = new TH1D("dR_Pho90", " dR( trg, Reco ) Photon ( pt > 90 ) ", 50, 0., 5. );
   dR_Pho50 = new TH1D("dR_Pho50", " dR( trg, Reco ) Photon ( pt < 55 ) ", 50, 0., 5. );

   // Time Resolution

   for ( int i=0; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;

       // Raw Information
       TLorentzVector t_gP4 = TLorentzVector( t_phoPx, t_phoPy, t_phoPz, t_phoE ) ;
       if ( nPhotons > 0 ) {
          TLorentzVector gP4_ = TLorentzVector( phoPx[0], phoPy[0], phoPz[0], phoE[0] ) ;
          h_gPt->Fill( gP4_.Pt() ) ;
          //cout<<" t_pt : "<< t_gP4.Pt() <<endl ;
          h_trg_gPt->Fill( t_gP4.Pt() ) ;
       }
       // Gen Information 
       int nX = ( isData == 0 ) ? GenInfo() : -1 ;
       if ( isData == 0 && nX != 1 ) continue ; // only use for Signal MC  
      
       // MET information
       TLorentzVector t_met = TLorentzVector( t_metPx, t_metPy, 0., t_metE ) ;
       TLorentzVector met( metPx, metPy, 0, metE)  ;
       h_met->Fill( metE ) ;
       h_trg_met->Fill( t_metE ) ;
      
       // Trigger Matching dR 
       dR_TrgReco_Pho->Fill( t_phodR ) ;
       dR_TrgReco_Met->Fill( t_metdR ) ;

       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;

       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       uint32_t evtType = select->EventIdentification();
       //bool pass = ( (evtType >> 1) & 1  ) ;
       bool passTrig = select->HLTFilter() ;
       if ( !passTrig ) continue ;

       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;

       // Find matched reco photon
       if ( selectPho.size() < 1 || selectJets.size() < 1 ) continue;


       double match_dR ;
       int itr = TrigRecoMatch( t_gP4, selectPho, match_dR, 999.9 ) ;
       // Only use 1 photon events to evaluate photon trigger efficiency
       if ( nPhotons == 1 && selectPho.size() == 1 ) {
       //if ( selectPho.size() == 2 ) {

          if ( selectPho[0].second.Pt() > 90 ) dR_Pho90->Fill( match_dR ) ;
          if ( selectPho[0].second.Pt() < 50 ) dR_Pho50->Fill( match_dR ) ;

          if ( itr < 0 && match_dR < 0.5 ) cout<<" bad event "<< match_dR << endl ;
          if ( match_dR < 0.5  ) {
             //if ( itr < 0 ) itr = 0 ;
             h_gPt_sel->Fill( selectPho[0].second.Pt() )  ;
	     h_gPt_trg->Fill( selectPho[0].second.Pt() )  ;
	     //if ( selectPho[itr].second.Pt() < 50 ) {
	     //   printf("(%d) trg pt: %.1f , reco: pt: %.1f , dR : %.2f , nPho: %d  sel: %d \n"
	     //          , itr, t_gP4.Pt(), selectPho[itr].second.Pt(), t_phodR, nPhotons, selectPho.size() ) ;
	     //}
          } else {
             h_gPt_sel->Fill( selectPho[0].second.Pt() )  ;
          }
       }

       // Get event with better MET quality by requiring >= 1 jet events
       // Require events going through HLT_PFMET module 
       // Event without passing HLT_PFMET module does NOT mean it fails the HLT_PFMET
       if ( selectJets.size() > 0 && t_metE > 0.01 ) {
          h_met_sel->Fill( metE ) ;
          if (t_metE > 24.99 ) h_met_trg->Fill( metE ) ;
          if ( metE > 130. && t_metE < 25. )  {
             int kk = selectPho[0].first ;
             printf(" gPt : %.2f , eta: %.2f , T: %.2f t_metE= %.2f , nJ= %d \n", 
                    selectPho[0].second.Pt(), selectPho[0].second.Eta(), seedTime[kk], t_metE, selectJets.size() ) ;
             for ( int k=0 ; k < selectJets.size() ; k++ ) 
                 printf("  jPt : %.2f , eta: %.2f \n", selectJets[k].second.Pt(), selectJets[k].second.Eta() ) ;
          }
            
          // This is a biased bad measurement -> In single photon dataset, events with PFMET trigger information
          // are more likely to be triggered by DisplacedPhotonTrigger 
          if ( nPhotons == 1 && selectPho.size() == 1 ) {
             hEff_Sel->Fill( selectPho[0].second.Pt(), metE ) ;
             if (triggered == 3 && match_dR < 0.5 ) hEff_Trg->Fill( selectPho[0].second.Pt(), metE ) ;

	     //if (  selectPho[0].second.Pt() < 65. && metE > 60.) { 
	     //     printf(" triggered = %d (%d - %d ) , gPt = %.2f , trgPt = %.2f dR: %.2f \n", 
      	     // 	     triggered , nPhotons, selectPho.size(), selectPho[itr].second.Pt(), t_gP4.Pt(), match_dR ) ;
	     //}

          }
       }

       // Time Resolution
       int kk = selectPho[0].first ;
       bool isHalo   = (cscdPhi[kk] < 0.05) || (sMajPho[kk] > 0.8  && sMinPho[kk] < 0.2)  ;
       bool isCosmic =  (dtdEta[kk] < 0.1) && (dtdPhi[kk] < 0.1)  ;
       if ( !isHalo && !isCosmic )  hTime_sel->Fill( seedTime[kk] ) ;
      

   } // end of event looping

   // 2D Efficiency 
   for ( int i=1 ; i <=42; i++ ) {
       for ( int j=1 ; j <=40; j++ ) {
           double bA =  hEff_Sel->GetBinContent(i,j) ;
           double bC =  hEff_Trg->GetBinContent(i,j) ;
           double ef = ( bA > 0. ) ? bC/bA : 0. ;
           hEff_2D->SetBinContent(i,j, ef ) ;
       }
   }
   // Write the histograms into TFile
   HistoWrite( ) ;
}

void Trigger::Plot() {

   TLegend* leg1  = new TLegend(.55, .73, .95, .90 );
   leg1->Clear();
   TString IntStr0 = "Leading Photon Pt" ;
   TString IntStr1 = "HLT Photon Pt " ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_gPt,     IntStr0,  "L");
   leg1->AddEntry( h_trg_gPt, IntStr1,  "L");
 
   h_draw->Draw(       h_gPt, "", " Pt (GeV/c)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h_trg_gPt, "PhotonPt_Trig", 0.75, 4, 1,leg1 ) ;

   leg1->Clear();
   IntStr0 = "PFMET " ;
   IntStr1 = "hlt_PFMET" ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_met,     IntStr0,  "L");
   leg1->AddEntry( h_trg_met, IntStr1,  "L");
   h_draw->Draw(       h_met, "", " MET (GeV)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h_trg_met, "MET_Trig", 0.75, 4, 1, leg1 ) ;

   h_draw->EffPlot( h_gPt_trg, h_gPt_sel, "Photon P_{T} (GeV/c) ", 10, 1, -1,  "PhotonPtEff" );
   h_draw->EffPlot( h_met_trg, h_met_sel, "MET (GeV/c) ", 10, 1, -1,  "METEff" );
   // Efficiency
   /*
   TPaveText* tex = new TPaveText(0.50, 0.27, 0.87,0.39, "NDC"); // NDC sets coords
   tex->SetFillColor(0); // text is black on white
   tex->SetBorderSize(1);
   tex->SetTextSize(0.035);
   tex->SetTextAlign(12);
   tex->AddText("    65 GeV HLT Photon");
   
   tex->Clear() ;
   tex->AddText("25 GeV HLT PF MET ");
   h_draw->EffPlot( h_met_hlt, h_met, "PF MET (GeV) ",   minBinContent[1], 1, -1,  "PFMETEff", tex );
   */

   // dR(Trigger, Reco) 
   h_draw->CreateNxM( "TrgReco", 1,2 );
   h_draw->DrawNxM( 1, dR_TrgReco_Pho,   "",   "", "", 1, false );
   h_draw->DrawNxM( 2, dR_TrgReco_Met,   "",   "", "", 1, true );

   // dR(Trigger, Reco) 
   h_draw->CreateNxM( "TrgReco1", 1,2 );
   h_draw->DrawNxM( 1, dR_Pho90,   "",   "", "", 1, false );
   h_draw->DrawNxM( 2, dR_Pho50,   "",   "", "", 1, true );

   h_draw->Draw( hTime_sel, "hTime_sel", " Ecal Time (ns)", "", "", 0.95, 1 ) ;


   // 2D Efficiency 
   
   for ( int i=1 ; i <=42; i++ ) {
       for ( int j=1 ; j <=40; j++ ) {
           double bA =  hEff_Sel->GetBinContent(i,j) ;
           double bC =  hEff_Trg->GetBinContent(i,j) ;
           double ef = ( bA > 0. ) ? bC/bA : 0. ;
           hEff_2D->SetBinContent(i,j, ef ) ;
       }
   }
   hEff_2D->Write() ;
    
   TCanvas* c_0  = new TCanvas("c_0","", 800, 600 );
   c_0->SetFillColor(10);
   c_0->SetFillColor(10);
   c_0->SetLeftMargin(0.16);
   c_0->SetBottomMargin(0.12);
   gStyle->SetOptStat(kFALSE);
   gStyle->SetNumberContours( 10 );

   hEff_2D->GetXaxis()->SetTitle( "Photon Pt (GeV)" );
   hEff_2D->GetYaxis()->SetTitle( "MET (GeV)" );
   hEff_2D->GetXaxis()->SetTitleOffset(1.5);
   hEff_2D->GetYaxis()->SetTitleOffset(1.5);

   c_0->cd() ;
   hEff_2D->Draw("COLZ") ;
   c_0->Update();

   TString plotname_0 = hfolder + "Eff2D."+plotType ;
   c_0->Print( plotname_0 );
   delete c_0 ;


}  


//int Trigger::TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV, double match_dR ) { 
int Trigger::TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV, double& match_dR, double dR_cut ) { 

    if ( trgP4.E() < 0.001 ) {
       //cout<<" No Triggger Object in the event "<<endl ;
       match_dR = 99. ;
       return -1 ;
    }

    double mindR = 99. ;
    int matchID = -1 ;

    for ( size_t i=0; i< objV.size(); i++ ) {
        double dR = trgP4.DeltaR( objV[i].second ) ;
        if ( dR < mindR ) {
           mindR   = dR ;
           matchID = (int)(i) ;
        }
    }
    match_dR = mindR ;
    if ( mindR > dR_cut )  {
       //printf(" min dR = %.2f , matchID : %d \n", mindR , matchID ) ;
       matchID = -1  ;
    }
    return matchID ;
}

void Trigger::EventList( string dataFileName ) {

   string logfilePath = hfolder ;
   logfilePath += "eventList.txt" ;

   FILE* logfile = fopen( logfilePath.c_str() ,"a");

   TTree* tr   = Input->GetTree( dataFileName, "DPAnalysis" );
   cout<<" Get the tree ! "<<endl ;
   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   int runId, eventId ;

   tr->SetBranchAddress("runId",        &runId);
   tr->SetBranchAddress("eventId",      &eventId);

   select->Init( tr1 ) ;

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataFileName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   for ( int i=0; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );

       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       uint32_t evtType = select->EventIdentification();
       bool pass = ( (evtType >> 1) & 1  ) ;

       if ( !pass ) continue ;
       fprintf(logfile," %8d %16d \n", runId, eventId );

   }

   fclose( logfile ) ;
}

// Return number of neutralino which decays to photon 
// For non-Signal MC, it returns -1 
int Trigger::GenInfo() { 

    int nX0_(0) , nX0_g_(0) ;
    for (int j=0; j< nGen; j++ ) {
	if ( pdgId[j] == 1000022 ) {
	   nX0_++ ;
	}
	if ( pdgId[j] == 22 && momId[j] > -1 ) {
	   if ( pdgId[ momId[j] ] == 1000022 ) {
	      nX0_g_++ ;
           }
	}
    }
    
    if ( nX0_ > 0 )     nX0++ ;
    if ( nX0_g_ == 2 )  n2X0_g++ ;
    if ( nX0_g_ == 1 )  n1X0_g++ ;
    if ( nX0_g_ == 0 )  n0X0_g++ ;

    if ( nX0_ < 1 ) return -1 ;
    else            return nX0_g_ ;
}

void Trigger::HistoOpen() {

   
   TString Path_fName = hfolder + hfName + ".root" ;
   theFile = new TFile( Path_fName, "UPDATE" );
   //theFile = new TFile( Path_fName, "READ" );
   //createFile = true ;
   cout<<" file opened ! "<<endl ;
   
   h_gPt     = (TH1D*) theFile->Get("h_gPt") ;
   h_trg_gPt = (TH1D*) theFile->Get("h_trg_gPt")  ;
   dR_TrgReco_Pho = (TH1D*) theFile->Get("dR_TrgReco_Pho") ;
   dR_TrgReco_Met = (TH1D*) theFile->Get("dR_TrgReco_Met") ;
   dR_Pho90 = (TH1D*) theFile->Get("dR_Pho90") ;
   dR_Pho50 = (TH1D*) theFile->Get("dR_Pho50") ;

   h_gPt_sel = (TH1D*) theFile->Get("h_gPt_sel") ;
   h_gPt_trg = (TH1D*) theFile->Get("h_gPt_trg") ; 

   h_met     = (TH1D*) theFile->Get("h_met")     ;
   h_met_sel = (TH1D*) theFile->Get("h_met_sel") ;
   h_trg_met = (TH1D*) theFile->Get("h_trg_met") ;
   h_met_trg = (TH1D*) theFile->Get("h_met_trg") ;

   hEff_Sel = (TH2D*) theFile->Get("hEff_Sel") ;
   hEff_Trg = (TH2D*) theFile->Get("hEff_Trg") ;
   hEff_2D  = (TH2D*) theFile->Get("hEff_2D") ;

   hTime_sel = (TH1D*) theFile->Get("hTime_sel")  ;

   cout<<" histogram linked ! "<<endl ;
}

void Trigger::HistoWrite() {

   h_gPt->Write()  ;
   h_trg_gPt->Write()  ;
   dR_TrgReco_Pho->Write() ;
   dR_TrgReco_Met->Write() ;
   dR_Pho90->Write() ;
   dR_Pho50->Write() ;

   h_gPt_sel->Write() ;
   h_gPt_trg->Write() ; 

   h_met->Write()     ;
   h_met_sel->Write()     ;
   h_trg_met->Write() ;
   h_met_trg->Write() ;

   hEff_Sel->Write() ;
   hEff_Trg->Write() ;
   hEff_2D->Write() ;

   hTime_sel->Write() ;
   cout<<" histograms are written ! " <<endl ;
}

void Trigger::CutFlow( string dataFileName ) {

   string logfilePath = hfolder ;
   logfilePath += "eventList.txt" ;

   FILE* logfile = fopen( logfilePath.c_str() ,"a");

   TTree* tr   = Input->GetTree( dataFileName, "CutFlow" );
   cout<<" Get the tree ! "<<endl ;
   // clone the tree for event selection

   int counter[12] ;
   int ctr[12] = { 0 } ;

   tr->SetBranchAddress("counter",  counter);

   int totalN = tr->GetEntries();
   for ( int i=0; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );

       for (int j=0; j<12 ; j++ ) ctr[j] += counter[j] ;

   }
   fprintf(logfile,"|    All   |    HLT   | Vertex | Fiducial | Conversion | sMaj_sMin | dR(phot,trk) | LeadingPt | BeamHalo |   Jet  |   MET  |  Final |\n" );
   fprintf(logfile,"  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n",  
                     ctr[0], ctr[1], ctr[2], ctr[3], ctr[4], ctr[5], ctr[6], ctr[7], ctr[8], ctr[9], ctr[10], ctr[11] ) ;

   fclose( logfile ) ;
}

