#include "Tester.h"
#include "MathTools.h"

Tester::Tester( string datacardfile ){

  // Load the basic classes
  Input = AnaInput::Instance() ;
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw() ;

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ;
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ;
  Input->GetParameters("PhotonCuts",    &photonCuts ) ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  
  // Open a root file to write histograms
  gSystem->mkdir( hfolder.c_str() );
  TString Path_fName = hfolder + hfName + ".root" ;
  theFile = new TFile( Path_fName, "RECREATE" );
  cout<<" Histogram File opened ! "<<endl ;
  theFile->cd() ;

}

Tester::~Tester() {

  cout<<" Output historams written ! "<<endl ;
  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete h_draw ;
  cout<<" Done ! "<<endl ;

}

// analysis template
void Tester::ReadTree( string dataName ) { 

   // Link the data tree
   TTree* tr   = Input->GetTree( dataName, "DPAnalysis" );
   // Clone the tree for event selection
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
   tr->SetBranchAddress("seedSwissX",  seedSwissX );

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

   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genT",        genT );  // t*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );

   // Initialize tree for DPSelection class
   select->Init( tr1 ) ;

   // Define histograms
   HistoInit() ;

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;
 
   // Main event loop
   for ( int i=0; i< totalN ; i++ ) {

       // 0. Get event entry
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
       
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;

       uint32_t evtType = select->EventIdentification();
       bool    passTrig = select->HLTFilter() ;
       bool passOffline = ( (evtType >> 5) & 1 ) ;

       // 2. Get selected objects
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;
       
       // MET information
       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;
       TLorentzVector met( metPx, metPy, 0, metE)  ;
      

       // Method to Loop the selected objects
       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
           int k = selectPho[kk].first ;
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
           h_PhotPt->Fill( gP4_.Pt() ) ;

       }

       // Method to Loop all objects
       for ( int k=0 ; k < nPhotons ; k++ ) {
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
           h_AllPhotPt->Fill( gP4_.Pt() ) ;
       }

   } // end of event looping

   // Write the histograms into TFile
   HistoWrite() ;
   Plot() ;
}

void Tester::PlotOnly() {

   HistoOpen() ;
   Plot() ;

}

void Tester::Plot() {

   TLegend* leg1  = new TLegend(.55, .73, .95, .90 );
   leg1->Clear();
   TString IntStr0 = "All Photon Pt" ;
   TString IntStr1 = "Selected Photon Pt " ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_AllPhotPt,     IntStr0,  "L");
   leg1->AddEntry( h_PhotPt,        IntStr1,  "L");
 
   h_draw->Draw(       h_AllPhotPt, "", " Pt (GeV/c)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h_PhotPt,    "PhotonPt_Trig",     0.75, 4, 1,leg1 ) ;

   // Un-marked it if you want to plot in different style
   /*
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

   TString plotname_0 = hfolder + "YourPlotName."+plotType ;
   c_0->Print( plotname_0 );

   delete c_0 ;
   */

}  

int Tester::TrigRecoMatch(  TLorentzVector trgP4, vector<objID> objV, double& match_dR, double dR_cut ) { 

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

void Tester::HistoInit() {

   h_PhotPt     = new TH1D("h_PhotPt",     "Leading Photon Pt   ", 42,  40, 250);
   h_AllPhotPt  = new TH1D("h_AllPhotPt",     "Leading Photon Pt   ", 42,  40, 250);

   cout<<" Histograms are defined ! "<<endl ;
}

void Tester::HistoOpen() {
   
   //TString Path_fName = hfolder + hfName + ".root" ;
   //theFile = new TFile( Path_fName, "UPDATE" );
   //theFile = new TFile( Path_fName, "READ" );
   
   h_PhotPt     = (TH1D*) theFile->Get("h_PhotPt" ) ;
   h_AllPhotPt  = (TH1D*) theFile->Get("h_AllPhotPt" ) ;


   cout<<" Histograms are linked ! "<<endl ;
}

void Tester::HistoWrite() {

   h_PhotPt->Write()  ;
   h_AllPhotPt->Write()  ;

   cout<<" Histograms are written ! " <<endl ;
}

