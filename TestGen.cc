#include "TestGen.h"

TestGen::TestGen( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw( datacardfile ) ; 

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 
  Input->GetParameters("FitCtau",       &FitCtau) ; 

}

TestGen::~TestGen(){

  delete select ;
  delete Input ;
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

   tr->SetBranchAddress("maxSwissX",   maxSwissX );
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

   TH1D* obsTime     = new TH1D("obsTime", "observed Photon Time from seed", 160,  -14.5, 25.5);
   TH1D* aveObsTime  = new TH1D("aveObsTime", "observed Photon Time from clusters", 160,  -14.5, 25.5);
   TH1D* aveObsTime1 = new TH1D("aveObsTime1", "observed Photon Time from clusters", 160,  -14.5, 25.5);
   TH1D* obsTimeErr  = new TH1D("obsTimeErr", "observed Photon Time Error from seed", 100,  0, 2.0);
   TH1D* aveObsTimeErr  = new TH1D("aveObsTimeErr", "observed Photon Time Error from clusters", 100,  0, 2.0);
   TH1D* aveObsTimeErr1 = new TH1D("aveObsTimeErr1", "observed Photon Time Error from clusters", 100,  0, 2.0);

   TH1D* h_Time   = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   TH1D* h_nChi2  = new TH1D("h_nChi2", "normalized chi2 of seed xtals", 100,  0, 50.0);
   TH1D* h_ctau   = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
   TH1D* h_xbeta  = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   TH1D* h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   TH1D* h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   TH1D* h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
   TH1D* h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   TH1D* h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   TH1D* h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );

   TH1D* h_maxSwiss = new TH1D("h_maxSwiss", " max SwissCross value from seed BC ", 150,  0., 1.5 );
   TH1D* h_fSpike   = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   TH1D* h_nXtals   = new TH1D("h_nXtals", "N of crystals of the photon ", 100,  0, 100 );
   TH1D* h_nBC      = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   TH1D* h_sMin     = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

   TH1D* h_met      = new TH1D("h_met",  "MET distribution ", 40,  0, 800);
   TH1D* h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);

   TH1D* h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   TH1D* h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   TH1D* h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   TH1D* h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   TH1D* h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);


   int nEvt = 0 ;
   int EscapedPhoton = 0 ;
   for ( int i=0; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );

       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass = select->SignalSelection();
       if ( !pass ) continue ;

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
       for ( int k=0; k< nPhotons; k++) {
           TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
           //if ( nPhotons > 0 ) cout<<" photon"<<k <<" pt:"<<gP4_.Pt() <<endl;
           if ( gP4_.Pt() > max_gPt ) {
              max_gPt = gP4_.Pt() ;
              g1P4 = gP4_ ;
           } 

           h_maxSwiss->Fill( maxSwissX[k] );
           h_fSpike->Fill( fSpike[k] ) ;
           h_sMin->Fill( sMinPho[k] ) ;
           if ( fSpike[k] != 0 ) continue ;
           if ( nXtals[k] < 1 ) continue ;
           //if ( maxSwissX[k] > 0.95 ) continue ;

           obsTime->Fill( seedTime[k] );
           obsTimeErr->Fill( seedTimeErr[k] );
           //if (  aveTimeErr[k] < 0.4 )  aveObsTime->Fill( aveTime[k] );
           aveObsTime->Fill( aveTime[k] );
           aveObsTimeErr->Fill( aveTimeErr[k] );
           if ( timeChi2[k] < 10 )  aveObsTime1->Fill( aveTime1[k] );
           if ( timeChi2[k] < 10 )  aveObsTimeErr1->Fill( aveTimeErr1[k] );
           h_nChi2->Fill( timeChi2[k] ) ;
           h_TrkIso->Fill( phoTrkIso[k] );
           h_EcalIso->Fill( phoEcalIso[k] );
           h_HcalIso->Fill( phoHcalIso[k] );
           h_TrkIsoR->Fill( phoTrkIso[k] / gP4_.Pt() );
           h_EcalIsoR->Fill( phoEcalIso[k] / gP4_.E() );
           h_HcalIsoR->Fill( phoHcalIso[k] / gP4_.E() );
           h_nXtals->Fill( nXtals[k] ) ;
           h_nBC->Fill( nBC[k] ) ;
       }
       h_g1Pt->Fill( max_gPt );

       // look up gen information  
       //if ( nVertices > 0 ) cout<<" vtx  = ("<< vtxX[0] <<","<< vtxY[0] <<","<<vtxZ[0] <<")"<< endl;
       if ( isData == 1 ) continue ;
       for ( int k=0; k< nGen ; k++) {
           if ( pdgId[k] != 22 ) continue ;
           TLorentzVector gP4 = TLorentzVector( genPx[k], genPy[k], genPz[k], genE[k] ) ;

           int mId = momId[k]  ;
           if ( mId < 0  ) continue ;
           TLorentzVector xP4 = TLorentzVector( genPx[mId], genPy[mId], genPz[mId], genE[mId] ) ;
           //double EcalTime = genT[k] ;  // tau*gamma
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
           Propagator( gP4, vx, vy, vz, EcalTime ) ;
           double t0 = sqrt( (vx*vx) + (vy*vy) + (vz*vz) ) /30. ;
           double dT = ( EcalTime == -25. ) ? -4 : EcalTime - t0 ;
           /*
           if ( dT < 0 && dT > -3 ) {
              cout<<"  Neutralino :  genVx:"<< genVx[mId] << " genVy:"<< genVy[mId] << " genVz:"<< genVz[mId] <<endl;
              cout<<"      Photon :  genVx:"<< genVx[k] << "  genVy:"<< genVy[k] << "  genVz:"<< genVz[k] <<endl;
              cout<<"         FinalEcal Vx:"<< vx <<"     Vy:"<< vy <<"    Vz:"<< vz <<endl;
              cout<<" LifeTime : "<< genT[k] / xP4.Beta() << "  EcalTime :"<< EcalTime<<"  T0:"<< t0 <<endl ; 
           }
           */ 
           h_Time->Fill( dT ) ;
           if ( dT == -4 ) EscapedPhoton++ ;
           //h_ctau->Fill( genT[k]*300. /  xP4.Gamma()) ;
           h_ctau->Fill( genT[mId]*300. /  xP4.Gamma()) ;
           h_xbeta->Fill( xP4.Beta() ) ;
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       }
   } // end of event looping
   cout<<" EscapedPhoton = "<< EscapedPhoton << endl ;


   // ********************* 
   // *  Draw histograms  *
   // *********************
   
   TLegend* leg1  = new TLegend(.52, .7, .78, .9 );
   leg1->Clear();
   TString IntStr0 = "" ;
   TString IntStr1 = "" ;
   TString IntStr2 = "" ;
   TString IntStr3 = "" ;
   leg1->SetTextSize(0.032) ;

   // calculate the number events later than "TCut"
   int bin_tcut = static_cast<int>( (TCut + 14.5) / 0.25 ) ;
   /// gen time
   if ( isData == 0 ) {
      Int_t nu0  = h_Time->Integral(bin_tcut,160);
      Int_t nu0a = h_Time->Integral(43,160);      // ignore the photons outside ECAL ( t = -4 ns )
      IntStr0 += nu0 ;
      IntStr0 += " / " ;
      IntStr0 += nu0a ;
      IntStr0 += " gen T " ;
      leg1->AddEntry( h_Time, IntStr0,  "L");
   } 
   /// seed time
   Int_t nu1  = obsTime->Integral(bin_tcut,160);
   Int_t nu1a = obsTime->Integral(1,160);
   IntStr1 += nu1 ;
   IntStr1 += " / " ;
   IntStr1 += nu1a ;
   IntStr1 += " seed T " ;
   leg1->AddEntry( obsTime, IntStr1,  "L");
   /// altered cluster time
   Int_t nu2  = aveObsTime->Integral(bin_tcut,160);
   Int_t nu2a = aveObsTime->Integral(1,160);
   IntStr2 += nu2 ;
   IntStr2 += " / " ;
   IntStr2 += nu2a ;
   IntStr2 += " cl. ave.T " ;
   leg1->AddEntry( aveObsTime, IntStr2,  "L");
   /// original cluster time
   Int_t nu3  = aveObsTime1->Integral(bin_tcut,160);
   Int_t nu3a = aveObsTime1->Integral(1,160);
   IntStr3 += nu3 ;
   IntStr3 += " / " ;
   IntStr3 += nu3a ;
   IntStr3 += " ave.T " ;
   leg1->AddEntry( aveObsTime1, IntStr3,  "L");

   cout<<" nEvent >= "<< TCut <<" ns1 = "<<nu1 <<" ns2 = "<<nu2 <<" ns3 = "<<nu3 <<endl; 

   // Photon Time
   gStyle->SetOptStat("emri");
   if ( isData == 1 ) {

      ///double init_fval[3] = { 10000, -0.2, 1. } ;
      ///h_draw->SetFitParameter( "Gaus", -3 , 3., 3, init_fval , 8 );
      //h_draw->SetFitParameter( "Gaus", obsTime, 0, 0, 3, 8 );
      //h_draw->FitNDraw(       obsTime, "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->Draw(       obsTime, "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.55, 6, leg1 ) ;

      h_draw->Draw(       obsTimeErr, "", "Ecal Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsTimeErr1, "PhotonTimeErr", 0.55, 6 ) ;
   } else { 
      h_draw->Draw(       h_Time, "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( obsTime, "", 0.75, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "", 0.55, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.35, 6, leg1 ) ;

      h_draw->Draw(       obsTimeErr, "", "Ecal Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsTimeErr1, "PhotonTimeErr", 0.55, 6 ) ;

      // Efficiency in Time spectrum
      //h_draw->EffProbPlot( 2, "EffErrFunction2" ) ;
      h_draw->EffPlot( aveObsTime, h_Time, 100, 51, -1,  "timeEff" );  
   }

   if ( isData == 0 ) {
      // Beta distribution
      h_draw->Draw( h_xbeta, "Beta", " #{beta} ", "", "logY", 0.95, 2 ) ;

      // Gen CTau 
      double init_fval[2] = { 300, FitCtau } ;
      h_draw->SetFitParameter( "exp", 0., 4000., 2, init_fval , 2 );
      h_draw->FitNDraw( h_ctau, "GenCTau", " ctau (mm)", "", "logY", 0.95, 1 );
   }

   // some Pt/Et spectrums
   h_draw->Draw( h_g1Pt,   "PhotonPt",    " Pt (GeV/c) ", "",          "logY", 0.95, 1 ) ;
   h_draw->Draw( h_met,    "MET",         " #slash{E_{T}} (GeV) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_nChi2,  "TimeChi2",    " #chi^{2} / ndof", "",      "logY", 0.95, 1 ) ;
   h_draw->Draw( h_fSpike, "fSpike",      " fraction of spike xtal","","logY", 0.95, 1 ) ;
   h_draw->Draw( h_maxSwiss, "maxSwissX", " max SwissCross value", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_nXtals, "nXtals",      " N of xtals ", "",         "", 0.95, 1 ) ;
   h_draw->Draw( h_nBC,    "nBC",         " N of basic cluster ", "", "", 0.95, 1 ) ;
   h_draw->Draw( h_nVtx,   "NVertices",   " N of valid vertices ", "","", 0.95, 1 ) ;
   h_draw->Draw( h_sMin,   "sMinor",      " sMinor ", "",              "logY", 0.95, 1 ) ;

   // Multiplicity
   h_draw->CreateNxM( "Multiplicity", 2,2 );
   h_draw->DrawNxM( 1, h_nPhotons,   "N of Photons",   "", "logY", 1, false );
   h_draw->DrawNxM( 2, h_nJets,      "N of Jets",      "", "logY", 1, false );
   h_draw->DrawNxM( 3, h_nMuons,     "N of Muons",     "", "logY", 1, false );
   h_draw->DrawNxM( 4, h_nElectrons, "N of Electrons", "", "logY", 1, true );

   // Isolation
   h_draw->CreateNxM( "Isolations", 2,3 );
   h_draw->DrawNxM( 1, h_TrkIso,   "Track Isolation ",       "", "logY", 1, false );
   h_draw->DrawNxM( 2, h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 3, h_EcalIso,  "Ecal Isolation ",        "", "logY", 2, false );
   h_draw->DrawNxM( 4, h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 5, h_HcalIso,  "Hcal Isolation ",        "", "logY", 4, false );
   h_draw->DrawNxM( 6, h_HcalIsoR, "Hcal Isolation Ratio",   "", "logY", 4, true );

}  

bool TestGen::Propagator( TLorentzVector v, double& x, double& y, double& z, double& t, double taugamma ) {

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;

    bool insideEcal = ( r < 155. && fabs(z) < 341. ) ? true : false ;

    bool alived   = true ;
    bool comeback = false ;
    int i = 0 ;
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

       //alived     = ( trace < cbtaugamma  ) ? true : false ;
       alived     = ( t <  taugamma   ) ? true : false ;
       insideEcal = ( r < 155 && fabs(z) < 341 ) ? true : false ; // outer edge of ECAL

       double dr = r - r0 ;
       double dz = fabs(z) - fabs(z0) ;
       //if ( insideEcal ) cout<<" r = "<< r <<" z : "<< z <<"  dr:"<<dr <<" dz:"<<dz<< endl;
       if (  insideEcal && comeback ) alived = false ;
       if ( r >= 155  && dr < 0 && fabs(z)  < 341 )           comeback = true ;
       if ( r  < 155            && fabs(z) >= 341 && dz < 0 ) comeback = true ;
       if ( r >= 155  && dr < 0 && fabs(z) >= 341 && dz < 0 ) comeback = true ;

       if ( r >= 155  && dr < 0 && fabs(z) >= 341 && dz > 0 ) comeback = false ;
       if ( r >= 155  && dr > 0 && fabs(z) >= 341 && dz < 0 ) comeback = false ;
       if ( !insideEcal && comeback ) insideEcal = true ;
       //if ( comeback ) cout<<" r = "<< r <<" z : "<< z <<"  dr:"<<dr <<" dz:"<<dz<< endl;
    } while ( insideEcal && alived && t < 25 ) ;

    if ( !insideEcal && !comeback ) {
       //cout<<"  ==>  t:"<<  t << " r = "<< r <<" z : "<< z << endl;
       if ( r >= 157 || fabs(z) >= 343 ) t = -25 ;
       if ( r  < 157 && fabs(z)  < 343 && t > 24.5 ) t = 25 ;
    }  

    return insideEcal ;
}

// simple propagator without backward propagation
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

vector<int> GlobalDRMatch( vector<TLorentzVector> vr, vector<TLorentzVector> vg ) {

    vector<int> pool ;
    for (size_t i=0; i < vg.size(); i++) pool.push_back(i) ;

    vector<int> mlist ;
    double minDR = 999 ; 
    do {

        double dr = 0 ;
        int m = 0 ;
        for ( size_t j=0; j< pool.size() ; j++ ) {
            if ( j > vr.size() ) break ;
            dr += vr[j].DeltaR( vg[ pool[j] ] ) ;
            m++ ;
        }
        if ( m > 0 &&  dr < minDR ) {
             minDR = dr ;
             mlist = pool ;
        }

    } while (  next_permutation( pool.begin() ,pool.end() ) ) ;

    return mlist ;
}
 
