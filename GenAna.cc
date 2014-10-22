#include "GenAna.h"

static bool PtDecreasing( objID s1, objID s2) { return ( s1.second.Pt() > s2.second.Pt() ); }

GenAna::GenAna( string datacardfile ) {

  Input = AnaInput::Instance() ;

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("TimeCalib",     &timeCalib ) ;
  Input->GetParameters("SystType",      &systType ) ;

  gSystem->mkdir( hfolder.c_str() );
  InitHisto();

}

GenAna::~GenAna(){


  cout<<" done ! "<<endl ;
}

void GenAna::InitHisto() {

  // initial histograms  
  h_ctbg   = new TH1D("h_ctbg", "(c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  h_ctbgT  = new TH1D("h_ctbgT", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  h_ctau   = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
  h_Time   = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
  selTime  = new TH1D("selTime", "Photon Time", 160,  -14.5, 25.5);
  h_Xbeta  = new TH1D("h_Xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
  h_XPt    = new TH1D("h_XPt", "Pt of Neutrlino", 50,  0, 500);
  h_XEta   = new TH1D("h_XEta", "#eta of Neutrlino", 51,  -2.55, 2.55);
  hTime_Xbeta = new TH2D("hTime_Xbeta", "Beta of Neutrlino vs Time", 55,  0, 1.1, 160,  -14.5, 25.5);
  hTime_ctbgT = new TH2D("hTime_ctbgT", "Transverse (c*t*beta*gamma) for #chi_{0} vs Time", 80,  0, 4000, 160,  -14.5, 25.5);
  xPt_ctbgT = new TH2D("xPt_ctbgT", "Pt of Neutralino vs decay length", 20,  0, 500, 40,  0, 4000);

  reco_ctbgT  = new TH1D("reco_ctbgT", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  acc_ctbgT  = new TH1D("acc_ctbgT", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  sel_XEta   = new TH1D("sel_XEta", "#eta of Neutrlino", 51,  -2.55, 2.55);
  sel_ctbgT  = new TH1D("sel_ctbgT", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  acc_ctbgT0  = new TH1D("acc_ctbgT0", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  acc_ctbgT1  = new TH1D("acc_ctbgT1", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  acc_ctbgT2  = new TH1D("acc_ctbgT2", "Transverse (c*t*beta*gamma) for #chi_{0}", 80,  0, 4000);
  xPt_T1    = new TH1D("xPt_T1", "Pt of Neutrlino", 50,  0, 500);
  xPt_T2    = new TH1D("xPt_T2", "Pt of Neutrlino", 50,  0, 500);
  xCtau_T1  = new TH1D("xCtau_T1", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
  xCtau_T2  = new TH1D("xCtau_T2", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
  xBeta_T1  = new TH1D("xBeta_T1", "Beta of Neutrlino ", 55,  0, 1.1);
  xBeta_T2  = new TH1D("xBeta_T2", "Beta of Neutrlino ", 55,  0, 1.1);

  h_lateXbeta = new TH1D("h_lateXbeta", "Beta of Neutrlino for late photon", 55,  0, 1.1);
  h_lateXctau = new TH1D("h_lateXctau", "ctau of Neutrlino for late photon", 80,  0, 4000);
  h_lateXctbgT = new TH1D("h_lateXctbgT", "Transverse (c*t*beta*gamma) for late photon ", 80,  0, 4000);
  h_lateXPt   = new TH1D("h_lateXPt", "Pt of Neutrlino for late photon", 50,  0, 500);

  dt1_dt2      = new TH2D("dt1_dt2", "dt1 vs dt2 ", 60, -2, 13, 60, -2, 13 ) ;
  dt1_dt2_late = new TH2D("dt1_dt2_late", "dt1 vs dt2 ", 60, -2, 13, 60, -2, 13 ) ;
  h_ctbg_RZ    = new TH2D("h_ctbg_RZ", "Decay length in R vs Z ",  100, -500, 500, 80, 0, 400 );

  h_GMET      = new TH1D("h_GMET",  "MET (MET from gravitino) distribution ", 50,  0, 500);
  h_genMET    = new TH1D("h_genMET", "gen MET ", 50,  0, 500);
  h_METRes    = new TH1D("h_METRes", "gen MET - Gravitino MET  ", 100,  -200, 200);
  h_METdPhi   = new TH1D("h_METdPhi", "#Delta#Phi(gen MET,Gravitino MET)  ", 64,  0., 3.2);

  h_gen1Pt     = new TH1D("h_gen1Pt",     "Leading Photon Pt ", 50,  0, 500);
  h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

  h_nJet     = new TH1D("h_nJet",     " N of Gen Jets ", 10,  0, 10.);
  h_j1Pt     = new TH1D("h_j1Pt",     "Leading jet Pt ", 50,  0, 500);
}

// analysis template
void GenAna::ReadTree( string dataName, double weight, string fNamePattern ) { 

   string dataFileNames ;
   if ( dataName.size() > 2 ) {
      dataFileNames = dataName ;   
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   printf(" Data File Names : %s \n", dataFileNames.c_str() ) ;
   
   // Open file for saving historms
   TString Path_fName = ( fNamePattern != "") ? hfolder + hfName + fNamePattern + ".root" : hfolder + hfName + ".root";
   theFile = new TFile( Path_fName, "RECREATE" );
   theFile->cd() ;
   printf(" Histo File name : %s%s \n", hfName.c_str(), fNamePattern.c_str() ) ;
   // Init histograms
   ResetHisto() ;
 

   TTree* tr   = Input->GetTree( dataFileNames, "DPGenAnalysis" );
   cout<<" Get the tree ! "<<endl ;

   // clone the tree for event selection

   tr->SetBranchAddress("evtId",       &eventId);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nGen",        &nGen);
   
   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("jetPx",       jetPx );
   tr->SetBranchAddress("jetPy",       jetPy );
   tr->SetBranchAddress("jetPz",       jetPz );
   tr->SetBranchAddress("jetE",        jetE );

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
   
   // Prepare a random number generator for gen Time smearing 
   TRandom3* tRan = new TRandom3();
   tRan->SetSeed( 0 );

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;
 
   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       if ( i % 10000 == 0 && i > 9999 ) printf(" ----- processed %8d Events \n", i ) ;
       nEvt++; 

       double maxGenPt = 0 ;
       double genMETP4[4] = {0,0,0,0};
       bool hasGravitino = false ;
       TLorentzVector met = TLorentzVector( metPx, metPy, 0., metE ) ;

       genPho.clear() ; 
       genXTs.clear() ; 
       v_time.clear() ; 
       v_ctbgT.clear() ;
   
       printf(" ============================== \n" ) ; 
       for ( int k=0; k< nGen ; k++) {
           //printf("===========%d============ \n", k ) ;
            
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
 
           // This is where the neutralino decays
           double vx = genVx[k] ;
           double vy = genVy[k] ;
           double vz = genVz[k] ;
           double ctbg  = sqrt( (vx*vx) + (vy*vy) + (vz*vz) ) ;
           double ctbgT = sqrt( (vx*vx) + (vy*vy)  ) ;
           double EcalTime = genT[mId] ;  // tau*gamma
           double vz0 = genVz[k] ;

           // time delay from slowness of neutralino 
           // has to be placed before Propagator
           double t1_c = ctbg / 30. ;
           double dt1  = EcalTime - t1_c ;   

           h_ctbg->Fill( ctbg*10. ) ;
           h_ctau->Fill( genT[mId]*300. / xP4.Gamma() ) ; // ctau in mm -> c = 300 mm / ns
           h_Xbeta->Fill( xP4.Beta() ) ;
           h_XPt->Fill( xP4.Pt() ) ;
           h_XEta->Fill( xP4.Eta() ) ;
           if ( fabs(vz) < 317. ) h_ctbgT->Fill( ctbgT*10. ) ;

           //double vrho = sqrt( (vx*vx) + (vy*vy) ) ;
           //printf("         v4( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           h_ctbg_RZ->Fill( vz0, ctbgT ) ; // where the neutralino decay

           // *************************************************************
           // * Main propagator - to make sure decay photon will hit ECAL *
           // *************************************************************
           bool hasEcalTime = Propagator( gP4, vx, vy, vz, EcalTime ) ;
           if ( !hasEcalTime ) continue ;

           // Construct 4 vector for generated photon
           //printf("           ( %.2f,%.2f,%.2f, rho: %.2f , t: %.2f ) \n", vx, vy, vz, vrho, EcalTime ) ;
           double d_x = vx - 0 ;
           double d_y = vy - 0 ;
           double d_z = vz - 0 ;
           double d_r = sqrt( (d_x*d_x) + (d_y*d_y) + (d_z*d_z) ); 
           double t0  = d_r /30. ; // t0 -> ecaltime assuming photon is from original
           // This is the measured ECAL time for gen photons
           //double dT = tRan->Gaus( EcalTime - t0 , timeCalib[1] ) - timeCalib[0] ;
           float tRes   = 0.4356 ;
           float tShift = 0.0322 ;
           if ( systType == 7 )  tRes   = sqrt( (0.4356*0.4356) + (timeCalib[1]*timeCalib[1]) )  ;
           if ( systType == 8 )  tRes   = sqrt( (0.4356*0.4356) - (timeCalib[1]*timeCalib[1]) ) ;
           if ( systType == 9 )  tShift = tShift + timeCalib[0] ;
           if ( systType == 10)  tShift = tShift - timeCalib[0] ;
           //printf(" syst = %d tRes = %.4f \n", systType, tRes) ;
           double dT = tRan->Gaus( EcalTime - t0 , tRes ) - tShift ;


           // Build the P4 for gen photon from reconstruction point of view 
           TLorentzVector genRecoP4 = TLorentzVector( d_x, d_y, d_z, d_r ) ;
           genRecoP4 = genRecoP4 * ( gP4.E() / d_r ) ;
           if ( genRecoP4.Pt() > maxGenPt ) maxGenPt = genRecoP4.Pt() ;
           //printf("    ---> p4( %.1f,%.1f,%.1f,%.1f) recoT:%.3f , dT: %.3f \n", 
           //                    genRecoP4.Px(),genRecoP4.Py(),genRecoP4.Pz(),genRecoP4.E(), t0, dT ) ;

           // Check the source of time delay
           double t2_c = EcalTime - genT[mId] ;
           double t3_c = sqrt( (vx*vx) + (vy*vy) + (vz*vz) ) / 30. ;
           double dt2 = t1_c + t2_c - t3_c ;  // time delay from deviation of photon path
           dt1_dt2->Fill( dt1, dt2 ) ;
           hTime_Xbeta->Fill( xP4.Beta(),  dT ) ;
           hTime_ctbgT->Fill( ctbgT*10. ,  dT ) ;

           // reweight sim to reco like 
           if (genRecoP4.Pt() > 1. && fabs( genRecoP4.Eta()) < 1.47 ) {
              xPt_ctbgT->Fill( xP4.Pt(), ctbgT*10./(xP4.Beta()*xP4.Gamma()) ) ;

              selTime->Fill( dT, Input->RecoWeight( xP4.Pt() , ctbgT*10./(xP4.Beta()*xP4.Gamma()) ) ) ;
           }

           if ( dT > 3. ) dt1_dt2_late->Fill( dt1, dt2 ) ;

           if ( genRecoP4.Pt() > 1. && fabs( genRecoP4.Eta()) < 1.47 ) {
	      reco_ctbgT->Fill( ctbgT*10. ) ; 
	      sel_XEta->Fill( xP4.Eta() ) ; 
	      if ( dT > 3.              ) acc_ctbgT0->Fill( ctbgT*10. ) ;         
	      if ( dT > 3. && dt2 < 0.5 ) acc_ctbgT1->Fill( ctbgT*10. ) ;         
	      if ( dT > 3. && dt2 > 0.5 ) acc_ctbgT2->Fill( ctbgT*10. ) ;         

	      if ( dT > 3. && dt2 < 0.5 ) xPt_T1->Fill( xP4.Pt() ) ;         
	      if ( dT > 3. && dt2 > 0.5 ) xPt_T2->Fill( xP4.Pt() ) ;         
	      if ( dT > 3. && dt2 < 0.5 ) xCtau_T1->Fill(  genT[mId]*300. / xP4.Gamma() ) ;         
	      if ( dT > 3. && dt2 > 0.5 ) xCtau_T2->Fill(  genT[mId]*300. / xP4.Gamma() ) ;         
	      if ( dT > 3. && dt2 < 0.5 ) xBeta_T1->Fill( xP4.Beta() ) ;         
	      if ( dT > 3. && dt2 > 0.5 ) xBeta_T2->Fill( xP4.Beta() ) ;         
           }

           h_Time->Fill( dT ) ;
           if ( genRecoP4.Pt() > 40. && fabs(genRecoP4.Eta()) < 1.47 ) {
              genPho.push_back( make_pair( k, genRecoP4 ) ) ;
	      genXTs.push_back( genT[mId]*300. / xP4.Gamma()  ) ;
	      v_time.push_back( dT ) ;
	      v_ctbgT.push_back( ctbgT*10. ) ;
           }

           if ( dT > 3. ) {
              h_lateXbeta->Fill( xP4.Beta() ) ;
              h_lateXctau->Fill( genT[mId]*300. / xP4.Gamma() ) ;
              h_lateXctbgT->Fill( ctbgT*10. ) ;
	      h_lateXPt->Fill( xP4.Pt() ) ;
           }
           //cout<<" PID:"<<pdgId[k] ;
           //cout<<" T_X: "<< genT[k] <<" EcalTime: "<<  EcalTime <<" dT = "<< dT << endl; 
       } 
       // End of gen particle loop

       int nPassJet = 0 ;
       double leadJetPt = 0 ;
       for ( int k=0 ; k < nJets; k++ ) {
           TLorentzVector jP4 = TLorentzVector( jetPx[k], jetPy[k], jetPz[k], jetE[k] ) ;
           if ( fabs( jP4.Eta()) > 2.4 ) continue ;
           if ( jP4.Pt() > 30. ) nPassJet++ ; 
           if ( jP4.Pt() > leadJetPt ) leadJetPt = jP4.Pt() ;
       }
       h_nJet->Fill( nPassJet ) ;
       if ( nPassJet > 0 ) h_j1Pt->Fill( leadJetPt ) ;

       // Check missing Et w.r.t to two Grabitino pt sum
       if ( hasGravitino ) {
          TLorentzVector G_P4 = TLorentzVector( genMETP4[0], genMETP4[1], genMETP4[2], genMETP4[3] ) ;
	  h_GMET->Fill( G_P4.Pt() ) ;
	  h_METRes->Fill( metE - G_P4.Pt() ) ;
	  h_METdPhi->Fill( fabs( G_P4.DeltaPhi( met ) ) ) ;
       }
       h_genMET->Fill( metE ) ;

       // sort the gen photon collection
       // check gen photon whether pass pt and eta cuts
       if ( genPho.size() > 1 ) sort( genPho.begin(), genPho.end(), PtDecreasing );
       if ( genPho.size() > 0 ) {
          h_gen1RecoPt->Fill( genPho[0].second.Pt() ) ;
          h_gen1Pt->Fill( maxGenPt ) ;
       }

       // Approximate the cuts on RECO
       if ( genPho[0].second.Pt() >= 80. &&  metE > 60. && nPassJet >= 2 ) {
          for ( size_t k=0; k< v_time.size(); k++ ) { 
              //selTime->Fill( v_time[k] ) ;
	      sel_ctbgT->Fill( v_ctbgT[k] ) ; 
	      if ( v_time[k] > 3. ) acc_ctbgT->Fill( v_ctbgT[k] ) ;         
          }
       }


   } // end of event looping


   theFile->cd() ;
   WriteHisto() ;
   cout<<" Output historams written ! "<<endl ;
   theFile->Close() ;
   cout<<" File closed ! "<<endl ;

}  

// propagator with backward propagation
// ECal Dimension : R:( 129 ~ 155 cm , Z(one-side) : 317 ~345 )
bool GenAna::Propagator( TLorentzVector& v, double& x, double& y, double& z, double& t, double taugamma ) {

    bool hasEcalTime = true ;

    double bx = v.Px() / v.P() ;
    double by = v.Py() / v.P() ;
    double bz = v.Pz() / v.P() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    double r0 = r ;
    double z0 = z ;
    double dL = 0. ;

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

void GenAna::WriteHisto() {

     h_ctbg->Write() ;
     h_ctbgT->Write() ;
     h_ctau->Write() ;
     h_Time->Write() ;
     selTime->Write() ;
     h_Xbeta->Write() ;
     h_XPt->Write() ;
     h_XEta->Write() ;
     hTime_Xbeta->Write() ;
     hTime_ctbgT->Write() ;
     xPt_ctbgT->Write() ;

     sel_XEta->Write() ;
     sel_ctbgT->Write() ;
     acc_ctbgT->Write() ;
     reco_ctbgT->Write() ;
     acc_ctbgT0->Write() ;
     acc_ctbgT1->Write() ;
     acc_ctbgT2->Write() ;
     xPt_T1->Write() ;
     xPt_T2->Write() ;
     xCtau_T1->Write() ;
     xCtau_T2->Write() ;
     xBeta_T1->Write() ;
     xBeta_T2->Write() ;

     h_ctbg_RZ->Write() ;
     dt1_dt2->Write() ;
     dt1_dt2_late->Write() ;

     h_lateXctau->Write() ;
     h_lateXctbgT->Write() ;
     h_lateXbeta->Write() ;
     h_lateXPt->Write() ;

     h_GMET->Write() ;
     h_genMET->Write() ;
     h_METRes->Write() ;
     h_METdPhi->Write() ;

     h_gen1RecoPt->Write() ;
     h_gen1Pt->Write() ;

     h_j1Pt->Write() ;
     h_nJet->Write() ;

 
}

void GenAna::OpenHisto() {

     h_ctbg  = (TH1D*) theFile->Get("h_ctbg")  ;
     h_ctbgT = (TH1D*) theFile->Get("h_ctbgT")  ;
     h_ctau  = (TH1D*) theFile->Get("h_Ctau")  ;
     h_Time  = (TH1D*) theFile->Get("h_Time")  ;
     selTime = (TH1D*) theFile->Get("selTime")  ;
     h_Xbeta = (TH1D*) theFile->Get("h_Xbeta")  ;
     h_XPt   = (TH1D*) theFile->Get("h_XPt")  ;
     h_XEta  = (TH1D*) theFile->Get("h_XEta")  ;
     hTime_Xbeta = (TH2D*) theFile->Get("hTime_Xbeta")  ;
     hTime_ctbgT = (TH2D*) theFile->Get("hTime_ctbgT")  ;
     xPt_ctbgT = (TH2D*) theFile->Get("xPt_ctbgT")  ;

     sel_XEta   = (TH1D*) theFile->Get("sel_XEta")  ;
     sel_ctbgT  = (TH1D*) theFile->Get("sel_ctbgT")  ;
     acc_ctbgT  = (TH1D*) theFile->Get("acc_ctbgT")  ;
     reco_ctbgT  = (TH1D*) theFile->Get("reco_ctbgT")  ;
     acc_ctbgT0  = (TH1D*) theFile->Get("acc_ctbgT0")  ;
     acc_ctbgT1  = (TH1D*) theFile->Get("acc_ctbgT1")  ;
     acc_ctbgT2  = (TH1D*) theFile->Get("acc_ctbgT2")  ;
     xPt_T1   = (TH1D*) theFile->Get("xPt_T1")  ;
     xPt_T2   = (TH1D*) theFile->Get("xPt_T2")  ;
     xCtau_T1   = (TH1D*) theFile->Get("xCtau_T1")  ;
     xCtau_T2   = (TH1D*) theFile->Get("xCtau_T2")  ;
     xBeta_T1   = (TH1D*) theFile->Get("xBeta_T1")  ;
     xBeta_T2   = (TH1D*) theFile->Get("xBeta_T2")  ;

     h_ctbg_RZ    = (TH2D*) theFile->Get("h_ctbg_RZ")  ;
     dt1_dt2      = (TH2D*) theFile->Get("dt1_dt2")  ;
     dt1_dt2_late = (TH2D*) theFile->Get("dt1_dt2_late")  ;

     h_lateXctau  = (TH1D*) theFile->Get("h_lateXctau")  ;
     h_lateXctbgT = (TH1D*) theFile->Get("h_lateXctbgT")  ;
     h_lateXbeta  = (TH1D*) theFile->Get("h_lateXbeta")  ;
     h_lateXPt    = (TH1D*) theFile->Get("h_lateXPt")  ;

     h_GMET    = (TH1D*) theFile->Get("h_GMET")  ;
     h_genMET  = (TH1D*) theFile->Get("h_genMET")  ;
     h_METRes  = (TH1D*) theFile->Get("h_METRes")  ;
     h_METdPhi = (TH1D*) theFile->Get("h_METdPhi")  ;

     h_gen1RecoPt = (TH1D*) theFile->Get("h_gen1RecoPt")  ;
     h_gen1Pt     = (TH1D*) theFile->Get("h_gen1Pt")  ;

     h_nJet     = (TH1D*) theFile->Get("h_nJet")  ;
     h_j1Pt     = (TH1D*) theFile->Get("h_j1Pt")  ;

}

void GenAna::ResetHisto() {

     h_ctbg->Reset()    ;
     h_ctbgT->Reset()   ;
     h_ctau->Reset()   ;
     h_Time->Reset()   ;
     selTime->Reset()  ;
     h_Xbeta->Reset()  ;
     h_XPt->Reset()    ;
     h_XEta->Reset()   ;
     hTime_Xbeta->Reset() ;
     hTime_ctbgT->Reset() ;
     xPt_ctbgT->Reset() ;

     sel_XEta->Reset()   ;
     sel_ctbgT->Reset()  ;
     acc_ctbgT->Reset()  ;
     reco_ctbgT->Reset() ;
     acc_ctbgT0->Reset() ;
     acc_ctbgT1->Reset() ;
     acc_ctbgT2->Reset() ;
     xPt_T1->Reset()     ;
     xPt_T2->Reset()     ;
     xCtau_T1->Reset()   ;
     xCtau_T2->Reset()   ;
     xBeta_T1->Reset()   ;
     xBeta_T2->Reset()   ;

     h_ctbg_RZ->Reset()    ;
     dt1_dt2->Reset()      ;
     dt1_dt2_late->Reset() ;

     h_lateXctau->Reset()  ;
     h_lateXctbgT->Reset() ;
     h_lateXbeta->Reset()  ;
     h_lateXPt->Reset()    ;

     h_GMET->Reset()     ;
     h_genMET->Reset()   ;
     h_METRes->Reset()   ;
     h_METdPhi->Reset()  ;

     h_gen1RecoPt->Reset() ;
     h_gen1Pt->Reset() ;    

     h_nJet->Reset()  ; 
     h_j1Pt->Reset()  ;  

} 
