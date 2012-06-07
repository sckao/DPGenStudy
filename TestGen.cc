#include "TestGen.h"

TestGen::TestGen( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
 
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
   //tr->SetBranchAddress("nVertices",   &nVertices);

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   //tr->SetBranchAddress("phoTime",     phoTime );

   //tr->SetBranchAddress("vtxX",       vtxX );
   //tr->SetBranchAddress("vtxY",       vtxY );
   //tr->SetBranchAddress("vtxZ",       vtxZ );
   
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

   TH1D* obsTime  = new TH1D("obsTime", "observed Photon Time from seed", 160,  -14.5, 25.5);
   TH1D* aveObsTime  = new TH1D("aveObsTime", "observed Photon Time from clusters", 160,  -14.5, 25.5);
   TH1D* h_Time   = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   TH1D* h_ctau   = new TH1D("h_ctau", "gen Photon Time (ctau)", 80,  0, 8000);
   TH1D* h_g1Pt   = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   TH1D* h_met    = new TH1D("h_met",  "MET distribution ", 40,  0, 800);
   TH1D* h_xbeta  = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   TH1D* h_nPhotons = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   TH1D* h_nJets    = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
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
       h_nJets->Fill( nJets ) ;
       h_nPhotons->Fill( nPhotons ) ;

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

           obsTime->Fill( seedTime[k] );
           aveObsTime->Fill( aveTime[k] );
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
           double EcalTime = genT[k] / xP4.Beta() ;  // tau*gamma
 
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
           h_ctau->Fill( genT[k]*300. / (xP4.Beta() * xP4.Gamma()) ) ;
           h_xbeta->Fill( xP4.Beta() ) ;
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       }
   } // end of event looping
   cout<<" EscapedPhoton = "<< EscapedPhoton << endl ;

   TCanvas*  c1 = new TCanvas("c1","", 800, 600);
   c1->SetFillColor(10);
   c1->SetFillColor(10);
   gStyle->SetOptStat("emriou");
   //c1->SetLogy();

   // Photon Pt distribution
   c1->cd();
   c1->SetLogy();
   gStyle->SetStatY(0.95);
   gStyle->SetStatTextColor(1);
   h_g1Pt->SetLineColor(1) ;
   h_g1Pt->Draw() ;
   c1->Update();

   TString plotname1 = hfolder + "PhotonPt." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);

   // MET distribution
   c1->cd();
   c1->SetLogy();
   h_met->SetLineColor(1) ;
   h_met->Draw() ;
   c1->Update();

   plotname1 = hfolder + "MET." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);

   // Multiplicity
   c1->cd() ;
   c1->SetFillColor(10);
   c1->Divide(2,2) ;
   c1->cd(1);
   h_nPhotons->Draw() ;
   c1->Update();  

   c1->cd(2);
   h_nJets->Draw() ;
   c1->Update();  

   c1->cd(3);
   h_nElectrons->Draw() ;
   c1->Update();  

   c1->cd(4);
   h_nMuons->Draw() ;
   c1->Update();  

   plotname1 = hfolder + "Multiplicity." + plotType ;
   c1->Print( plotname1 );

   // Beta distribution
   c1->cd();
   c1->SetLogy();
   h_xbeta->SetLineColor(1) ;
   h_xbeta->Draw() ;
   c1->Update();

   plotname1 = hfolder + "Beta." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);

   // Photon Time
   c1->cd() ;
   c1->SetLogy();
   c1->SetGridx();

   //leg1->SetTextSize(0.032) ;
   if ( isData == 1 ) {
      gStyle->SetStatY(0.95);
      gStyle->SetStatTextColor(2);
      obsTime->SetLineColor(2) ;
      obsTime->Draw() ;
      c1->Update();
      gStyle->SetStatY(0.7);
      gStyle->SetStatTextColor(4);
      aveObsTime->SetLineColor(4) ;
      aveObsTime->DrawCopy("sames") ;
   } else { 
      h_Time->SetLineColor(1) ;
      h_Time->Draw() ;
      c1->Update();
      gStyle->SetStatY(0.7);
      gStyle->SetStatTextColor(2);
      obsTime->SetLineColor(2) ;
      obsTime->DrawCopy("sames") ;
      c1->Update();
      gStyle->SetStatY(0.45);
      gStyle->SetStatTextColor(4);
      aveObsTime->SetLineColor(4) ;
      aveObsTime->DrawCopy("sames") ;
   }
   c1->Update();

   TLegend* leg1  = new TLegend(.58, .75, .78, .9 );
   leg1->Clear();
   TString IntStr1 = "" ;
   TString IntStr2 = "" ;

   int bin_tcut = static_cast<int>( (TCut + 4.5) / 0.25 ) ;
   Int_t nu1  = obsTime->Integral(bin_tcut,120);
   Int_t nu1a = obsTime->Integral(1,120);
   IntStr1 += nu1 ;
   IntStr1 += " / " ;
   IntStr1 += nu1a ;
   leg1->AddEntry( obsTime, IntStr1,  "L");
   Int_t nu2  = aveObsTime->Integral(bin_tcut,120);
   Int_t nu2a = aveObsTime->Integral(1,120);
   IntStr2 += nu2 ;
   IntStr2 += " / " ;
   IntStr2 += nu2a ;
   leg1->AddEntry( aveObsTime, IntStr2,  "L");

   cout<<" nEvent >= "<< TCut <<" ns1 = "<<nu1 <<" ns2 = "<<nu2 <<endl; 
   leg1->Draw("sames");

   plotname1 = hfolder + "PhoTime." + plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);
   c1->SetGridx(0);

   // Gen Photon Time
   c1->cd() ;
   gStyle->SetStatY(0.95);
   gStyle->SetOptFit(111);
   TF1 *func = new TF1("func", &TestGen::fExp , 0., 10000., 2);
   func->SetParameter(0, 500);
   func->SetParameter(1, FitCtau );

   h_ctau->Draw() ;
   c1->Update();
   h_ctau->Fit( func, "R" );
   func->SetLineColor(2);
   func->Draw("same") ;
   c1->Update();  

   plotname1 = hfolder + "GenPhoTime." + plotType ;
   c1->Print( plotname1 );


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

Double_t TestGen::fExp(Double_t *v, Double_t *par) {
      Double_t arg = v[0] /par[1];

      Double_t fitval = par[0]*TMath::Exp( -1*arg);
      return fitval;
}
            
