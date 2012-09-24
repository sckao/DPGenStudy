#include "TestGen.h"

Histogram::Histogram( string datacardfile ) {

  Input  = new AnaInput( datacardfile );
  h_draw = new hDraw( datacardfile ) ; 

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("HFileName",     &hfName ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 
  Input->GetParameters("FitCtau",       &FitCtau) ; 

}

void Histogram::Init( hSet& hS ) {

   hS.obsTime     = new TH1D("obsTime", "Photon Time from seed", 160,  -14.5, 25.5);
   hS.aveObsTime  = new TH1D("aveObsTime", "Photon Time from clusters", 160,  -14.5, 25.5);
   hS.aveObsTime1 = new TH1D("aveObsTime1", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   hS.aveObsTime2 = new TH1D("aveObsTime2", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   hS.obsEBTimeErr  = new TH1D("obsEBTimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   hS.obsEETimeErr  = new TH1D("obsEETimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   hS.aveObsEBTimeErr  = new TH1D("aveObsEBTimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEETimeErr  = new TH1D("aveObsEETimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEBTimeErr1 = new TH1D("aveObsEBTimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEETimeErr1 = new TH1D("aveObsEETimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);

   hS.seedTime_Chi2  = new TH2D("seedTime_Chi2", "Seed Time vs Chi2 ", 160,  -14.5, 25.5, 50, 0, 100);

   hS.badPhoTime     = new TH1D("badPhoTime", "bad channel time", 102,  -25.5, 25.5);
   hS.TimeLT3Jets    = new TH1D("TimeLT3Jets", "Ecal Time from  < 3 Jets Events", 160,  -14.5, 25.5);
   hS.TimeGE3Jets    = new TH1D("TimeGE3Jets", "Ecal Time from >= 3 Jets Events", 160,  -14.5, 25.5);
   hS.TimeLowMET     = new TH1D("TimeLowMET", "Ecal Time from  MET  < 60 GeV Events", 160,  -14.5, 25.5);
   hS.TimeBigMET     = new TH1D("TimeBigMET", "Ecal Time from  MET >= 60 GeV Events", 160,  -14.5, 25.5);

   hS.SpikeEtaP      = new TH1D("SpikeEtaP", "#eta distribution for spike like photon ( t > 10 )", 24, 0, 2.4);
   hS.SpikeEtaN      = new TH1D("SpikeEtaN", "#eta distribution for spike like photon ( t < -10)", 24, 0, 2.4);
   hS.Vz_P           = new TH1D("Vz_P", " z of vertices for events with photon ( t >  10)", 65, -32.5, 32.5);
   hS.Vz_N           = new TH1D("Vz_N", " z of vertices for events with photon ( t < -10)", 65, -32.5, 32.5);

   hS.h_matchRecoTime = new TH1D("h_matchRecoTime", "Matched Reco Photon Time", 160,  -14.5, 25.5);
   hS.h_matchGenTime  = new TH1D("h_matchGenTime", "Matched Gen Photon Time", 160,  -14.5, 25.5);
   hS.h_matchTime     = new TH1D("h_matchTime", "Time Matched Gen Photon Time", 160,  -14.5, 25.5);
   hS.h_genTime       = new TH1D("h_genTime",   "Photon Time ", 160,  -14.5, 25.5);
   hS.h_TimeRes1   = new TH1D("h_TimeRes1", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   hS.h_TimeRes2   = new TH1D("h_TimeRes2", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   hS.h_TimeRes3   = new TH1D("h_TimeRes3", "Seed Photon Time Resolution",  50,  -2.5, 2.5 );
   hS.h_aTimeRes1   = new TH1D("h_aTimeRes1", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   hS.h_aTimeRes2   = new TH1D("h_aTimeRes2", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   hS.h_aTimeRes3   = new TH1D("h_aTimeRes3", "Weighted Ave. Photon Time Resolution",  50,  -2.5, 2.5 );
   hS.h_PtRes     = new TH1D("h_PtRes",   " Photon Pt Resolution", 200,  -1., 1.);

   hS.Time_R   = new TH2D("Time_R", "Gen Photon Time vs R ", 160,  -14.5, 25.5, 25, 0, 175);
   hS.Time_Z   = new TH2D("Time_Z", "Gen Photon Time vs Z ", 160,  -14.5, 25.5, 30, 0, 390);

   hS.h_Time   = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   hS.h_nChi2  = new TH1D("h_nChi2", "normalized chi2 of seed xtals", 100,  0, 50.0);
   hS.h_ctau   = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
   hS.h_xbeta  = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   hS.h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   hS.h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   hS.h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
   hS.h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   hS.h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   hS.h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );

   hS.h_maxSwissEB = new TH1D("h_maxSwissEB", " max SwissCross value from seed EB BC ", 150,  0., 1.5 );
   hS.h_maxSwissEE = new TH1D("h_maxSwissEE", " max SwissCross value from seed EE BC ", 150,  0., 1.5 );
   hS.h_seedSwiss = new TH1D("h_seedSwiss", " seed SwissCross value ", 150,  0., 1.5 );
   hS.h_fSpike   = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   hS.h_nXtals   = new TH1D("h_nXtals", "N of crystals of the photon ", 100,  0, 100 );
   hS.h_nBC      = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   hS.h_sMin     = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

   hS.h_met      = new TH1D("h_met",  "MET distribution ", 40,  0, 800);
   hS.h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   hS.h_gen1Pt     = new TH1D("h_gen1Pt", "Leading GenPhoton Pt ", 50,  0, 500);
   hS.h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

   hS.h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   hS.h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   hS.h_nGenPhotons = new TH1D("h_nGenPhotons", "N of GenPhotons  ", 10,  -0.5, 9.5);
   hS.h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   hS.h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   hS.h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);

   hS.h_Eta_Time  = new TH2D( "h_Eta_Time", " eta vs photon time", 51, -2.5, 2.5, 160, -20, 20 ) ;
   hS.h_Phi_Time  = new TH2D( "h_Phi_Time", " phi vs photon time", 63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.h_Phi_Time1 = new TH2D( "h_Phi_Time1", " phi vs photon time for T < -5 ns", 63, -3.15, 3.15, 160, -20, 20 ) ;

   hS.h_RhoPhi_Halo = new TH2D( "h_RhoPhi_Halo", " phi vs rho for halo tracks", 63, -3.15, 3.15, 50, 0, 500 ) ;
   hS.h_nHaloHits   = new TH1D( "h_nHaloHits",   " N of out of time CSC rechits", 50, 0, 50 ) ;
   hS.h_nHaloTracks = new TH1D( "h_nHaloTracks",   " N of CSC Halo Tracks", 10, 0, 10 ) ;
   hS.h_PhiTimeHalo  = new TH2D( "h_PhiTimeHalo", "#phi vs Photon time for halo ", 63, -3.15, 3.15, 160,  -14.5, 25.5 ) ;
   hS.h_EtaTimeHalo  = new TH2D( "h_EtaTimeHalo", "#eta vs Halo Photon time ", 51, -2.5, 2.5, 160,  -14.5, 25.5 ) ;
   hS.h_EtaTimeNoHalo = new TH2D( "h_EtaTimeNoHalo", "#eta vs No Halo Photon time ", 51, -2.5, 2.5, 160,  -14.5, 25.5 ) ;
   hS.h_TimeNoHalo    = new TH1D( "h_TimeNoHalo", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;
   hS.h_SigEtaHalo    = new TH1D( "h_SigEtaHalo", " Sigma Eta Eta for Halo Photon ", 100,  0., 0.1 ) ;
   hS.h_SigIetaHalo   = new TH1D( "h_SigIetaHalo", " Sigma Ieta Ieta for Halo Photon ", 100,  0., 0.1 ) ;
   hS.h_SigEta    = new TH1D( "h_SigEta", " Sigma Eta Eta for Photon w/o Halo", 100,  0., 0.1 ) ;
   hS.h_SigIeta   = new TH1D( "h_SigIeta", " Sigma Ieta Ieta for Photon w/o Halo", 100,  0., 0.1 ) ;

   cout<<" init ... ";
   h = hS ;
   cout<<"  !!! "<<endl ;

}

void Histogram::Open() {

     TString Path_fName = hfolder + hfName + ".root" ;

     string hfName_ = hfolder ;
     hfName_ += hfName ;
     hfName_ += ".root" ;

     cout<<" Opening : "<< hfName_ <<endl ;

     hFile = (TFile*) TFile::Open( hfName_.c_str() , "READ" );
     //hFile->cd() ;
     cout<<" file opened ! "<<endl ;

     h.obsTime     = (TH1D*) hFile->Get("obsTime")     ;
     h.aveObsTime  = (TH1D*) hFile->Get("aveObsTime") ;
     h.aveObsTime1 = (TH1D*) hFile->Get("aveObsTime1") ;
     h.aveObsTime2 = (TH1D*) hFile->Get("aveObsTime2") ;
     h.obsEBTimeErr = (TH1D*) hFile->Get("obsEBTimeErr")  ;
     h.obsEETimeErr = (TH1D*) hFile->Get("obsEETimeErr")  ;
     h.aveObsEBTimeErr = (TH1D*) hFile->Get("aveObsEBTimeErr") ;
     h.aveObsEETimeErr = (TH1D*) hFile->Get("aveObsEETimeErr") ;
     h.aveObsEBTimeErr1 = (TH1D*) hFile->Get("aveObsEBTimeErr1") ;
     h.aveObsEETimeErr1 = (TH1D*) hFile->Get("aveObsEETimeErr1") ;

     h.seedTime_Chi2 = (TH2D*) hFile->Get("seedTime_Chi2")  ;
     h.Time_R = (TH2D*) hFile->Get("Time_R")  ;
     h.Time_Z = (TH2D*) hFile->Get("Time_Z")  ;

     h.badPhoTime = (TH1D*) hFile->Get("badPhoTime")     ;
     h.TimeLT3Jets = (TH1D*) hFile->Get("TimeLT3Jets")   ;
     h.TimeGE3Jets = (TH1D*) hFile->Get("TimeGE3Jets")   ;
     h.TimeLowMET = (TH1D*) hFile->Get("TimeLowMET")     ;
     h.TimeBigMET = (TH1D*) hFile->Get("TimeBigMET")     ;

     h.SpikeEtaP = (TH1D*) hFile->Get("SpikeEtaP")      ;
     h.SpikeEtaN = (TH1D*) hFile->Get("SpikeEtaN")      ;
     h.Vz_P = (TH1D*) hFile->Get("Vz_P")           ;
     h.Vz_N = (TH1D*) hFile->Get("Vz_N")           ;

     h.h_matchRecoTime = (TH1D*) hFile->Get("h_matchRecoTime") ;
     h.h_matchGenTime = (TH1D*) hFile->Get("h_matchGenTime")  ;
     h.h_matchTime = (TH1D*) hFile->Get("h_matchTime")     ;
     h.h_genTime = (TH1D*) hFile->Get("h_genTime")       ;
     h.h_TimeRes1 = (TH1D*) hFile->Get("h_TimeRes1")      ;
     h.h_TimeRes2 = (TH1D*) hFile->Get("h_TimeRes2")      ;
     h.h_TimeRes3 = (TH1D*) hFile->Get("h_TimeRes3")      ;
     h.h_aTimeRes1 = (TH1D*) hFile->Get("h_aTimeRes1")     ;
     h.h_aTimeRes2 = (TH1D*) hFile->Get("h_aTimeRes2")     ;
     h.h_aTimeRes3 = (TH1D*) hFile->Get("h_aTimeRes3")     ;
     h.h_PtRes  = (TH1D*) hFile->Get("h_PtRes")         ;

     h.h_Time   = (TH1D*) hFile->Get("h_Time")   ;
     h.h_nChi2  = (TH1D*) hFile->Get("h_nChi2")  ;
     h.h_ctau   = (TH1D*) hFile->Get("h_cta")   ;
     h.h_xbeta  = (TH1D*) hFile->Get("h_xbeta")  ;
     h.h_TrkIso = (TH1D*) hFile->Get("h_TrkIso")   ;
     h.h_HcalIso = (TH1D*) hFile->Get("h_HcalIso")  ;
     h.h_EcalIso = (TH1D*) hFile->Get("h_EcalIso")  ;
     h.h_TrkIsoR = (TH1D*) hFile->Get("h_TrkIsoR")  ;
     h.h_HcalIsoR = (TH1D*) hFile->Get("h_HcalIsoR") ;
     h.h_EcalIsoR = (TH1D*) hFile->Get("h_EcalIsoR") ;

     h.h_maxSwissEB = (TH1D*) hFile->Get("h_maxSwissEB") ;
     h.h_maxSwissEE = (TH1D*) hFile->Get("h_maxSwissEE") ;
     h.h_seedSwiss = (TH1D*) hFile->Get("h_seedSwiss")  ;
     h.h_fSpike = (TH1D*) hFile->Get("h_fSpike")    ;
     h.h_nXtals = (TH1D*) hFile->Get("h_nXtals")    ;
     h.h_nBC = (TH1D*) hFile->Get("h_nBC")       ;
     h.h_sMin = (TH1D*) hFile->Get("h_sMin")      ;

     h.h_met = (TH1D*) hFile->Get("h_met")        ;
     h.h_g1Pt = (TH1D*) hFile->Get("h_g1Pt")       ;
     h.h_gen1Pt = (TH1D*) hFile->Get("h_gen1Pt")     ;
     h.h_gen1RecoPt = (TH1D*) hFile->Get("h_gen1RecoPt") ;

     h.h_nVtx        = (TH1D*) hFile->Get("h_nVtx")       ;
     h.h_nPhotons    = (TH1D*) hFile->Get("h_nPhotons")   ;
     h.h_nGenPhotons = (TH1D*) hFile->Get("h_nGenPhotons");
     h.h_nJets  = (TH1D*) hFile->Get("h_nJets")      ;
     h.h_nMuons = (TH1D*) hFile->Get("h_nMuons")     ;
     h.h_nElectrons = (TH1D*) hFile->Get("h_nElectrons") ;

     h.h_Eta_Time = (TH2D*) hFile->Get("h_Eta_Time")  ;
     h.h_Phi_Time = (TH2D*) hFile->Get("h_Phi_Time")  ;
     h.h_Phi_Time1 = (TH2D*) hFile->Get("h_Phi_Time1")  ;

     h.h_RhoPhi_Halo = (TH2D*) hFile->Get("h_RhoPhi_Halo")  ;
     h.h_nHaloHits   = (TH1D*) hFile->Get("h_nHaloHits")  ;
     h.h_nHaloTracks = (TH1D*) hFile->Get("h_nHaloTracks")  ;
     h.h_PhiTimeHalo  = (TH2D*) hFile->Get("h_PhiTimeHalo")  ;
     h.h_EtaTimeHalo  = (TH2D*) hFile->Get("h_EtaTimeHalo")  ;
     h.h_EtaTimeNoHalo  = (TH2D*) hFile->Get("h_EtaTimeNoHalo")  ;
     h.h_TimeNoHalo  = (TH1D*) hFile->Get("h_TimeNoHalo")  ;
     h.h_SigEtaHalo    = (TH1D*) hFile->Get("h_SigEtaHalo") ;
     h.h_SigIetaHalo   = (TH1D*) hFile->Get("h_SigIetaHalo") ;
     h.h_SigEta    = (TH1D*) hFile->Get("h_SigEta") ;
     h.h_SigIeta   = (TH1D*) hFile->Get("h_SigIeta") ;


     cout<<" link all histograms  "<<endl ;
}

void Histogram::DrawHistograms() {

   // link all exist histograms
   Open() ;

   cout<<" start drawig "<<endl ;
   // ********************* 
   // *  Draw histograms  *
   // *********************
   TLegend* leg1  = new TLegend(.5, .7, .77, .9 );
   leg1->Clear();
   TString IntStr0 = "" ;
   TString IntStr1 = "" ;
   TString IntStr2 = "" ;
   TString IntStr3 = "" ;
   leg1->SetTextSize(0.03) ;

   // calculate the number events later than "TCut"
   int bin_tcut = static_cast<int>( (TCut + 14.5) / 0.25 ) ;
   /// gen time
   if ( isData == 0 ) {
      Int_t nu0  = h.h_genTime->Integral(bin_tcut,160);
      Int_t nu0a = h.h_genTime->Integral(43,160);      // ignore the photons outside ECAL ( t = -4 ns )
      IntStr0 += nu0 ;
      IntStr0 += " / " ;
      IntStr0 += nu0a ;
      IntStr0 += " Gen " ;
      leg1->AddEntry( h.h_genTime, IntStr0,  "L");
   } 
   /// seed time
   Int_t nu1  = h.obsTime->Integral(bin_tcut,160);
   Int_t nu1a = h.obsTime->Integral(1,160);
   IntStr1 += nu1 ;
   IntStr1 += " / " ;
   IntStr1 += nu1a ;
   IntStr1 += " Seed " ;
   leg1->AddEntry( h.obsTime, IntStr1,  "L");
   /// altered cluster time
   Int_t nu2  = h.aveObsTime->Integral(bin_tcut,160);
   Int_t nu2a = h.aveObsTime->Integral(1,160);
   IntStr2 += nu2 ;
   IntStr2 += " / " ;
   IntStr2 += nu2a ;
   IntStr2 += " Cluster " ;
   leg1->AddEntry( h.aveObsTime, IntStr2,  "L");
   /// original cluster time with Chi2 cut

   Int_t nu3  = h.aveObsTime1->Integral(bin_tcut,160);
   Int_t nu3a = h.aveObsTime1->Integral(1,160);
   IntStr3 += nu3 ;
   IntStr3 += " / " ;
   IntStr3 += nu3a ;
   IntStr3 += " Chi2 " ;
   leg1->AddEntry( h.aveObsTime1, IntStr3,  "L");

   cout<<" nEvent >= "<< TCut <<" ns1 = "<<nu1 <<" ns2 = "<<nu2 <<" ns3 = "<<nu3 <<endl; 

   // Photon Time
   gStyle->SetOptStat("ermi");
   if ( isData == 1 ) {

      ///double init_fval[3] = { 10000, -0.2, 1. } ;
      ///h_draw->SetFitParameter( "Gaus", -3 , 3., 3, init_fval , 8 );
      //h_draw->SetFitParameter( "Gaus", obsTime, 0, 0, 3, 8 );
      //h_draw->FitNDraw(       obsTime, "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;

      // for DOE
      h_draw->Draw(     h.obsTime, "SeedTime", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;

      TLegend* leg2  = new TLegend(.52, .72, .77, .9 );
      leg2->AddEntry( h.obsTime,    " Seed        ",     "L" ) ;
      leg2->AddEntry( h.aveObsTime, " Averaged    ", "L" ) ;
      h_draw->SetHistoInfo( h.obsTime,    " Data (Run2012B) ", 2 ) ;
      h_draw->SetHistoInfo( h.aveObsTime, "", 2 ) ;
      h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( h.aveObsTime, "PhotonTime", 0.75, 2, 1, leg2 ) ;
      delete leg2 ;

      TLegend* leg3  = new TLegend(.45, .72, .77, .9 );
      leg3->AddEntry( h.obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( h.aveObsTime1, "Averaged + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( h.aveObsTime1, "", 2 ) ;
      h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( h.aveObsTime1, "PhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;

      leg3->Clear();
      leg3->AddEntry( h.obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( h.aveObsTime2, "Seed + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( h.aveObsTime2, "", 2 ) ;
      h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( h.aveObsTime2, "SeedPhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;
      delete leg3 ;

      /*
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "",  0.72, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.49, 6, 1, leg1 ) ;
     */
      h_draw->Draw(       h.obsEBTimeErr, "", "EB Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h.aveObsEBTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( h.aveObsEBTimeErr1, "EBPhotonTimeErr", 0.55, 6 ) ;

      h_draw->Draw(       h.obsEETimeErr, "", "EE Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h.aveObsEETimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( h.aveObsEETimeErr1, "EEPhotonTimeErr", 0.55, 6 ) ;

   } else { 

      // for DOE
      gStyle->SetOptStat("");
      h_draw->Draw(      h.obsTime, "SeedTime", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;

      TLegend* leg2  = new TLegend(.52, .72, .77, .9 );
      leg2->AddEntry( h.obsTime,    " Seed        ", "L" ) ;
      leg2->AddEntry( h.aveObsTime, " Averaged    ", "L" ) ;
      h_draw->SetHistoInfo( h.obsTime,    " MC (GMSB) ", 2 ) ;
      h_draw->SetHistoInfo( h.aveObsTime, "", 2 ) ;
      h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( h.aveObsTime, "PhotonTime", 0.75, 2, 1, leg2 ) ;

      TLegend* leg3  = new TLegend(.45, .72, .77, .9 );
      leg3->AddEntry( h.obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( h.aveObsTime1, "Averaged + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( h.aveObsTime1, "", 2 ) ;
      h_draw->Draw(       h.obsTime,     "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( h.aveObsTime1, "PhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;
      delete leg3 ;
      
      /*
      h_draw->Draw(     h.h_genTime, "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( obsTime, "", 0.75, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "", 0.55, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.35, 6, 1,  leg1 ) ;
      */

      h_draw->Draw(       h.obsEBTimeErr, "", "EB Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h.aveObsEBTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( h.aveObsEBTimeErr1, "EBPhotonTimeErr", 0.55, 6 ) ;

      h_draw->Draw(       h.obsEETimeErr, "", "EE Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h.aveObsEETimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( h.aveObsEETimeErr1, "EEPhotonTimeErr", 0.55, 6 ) ;

      // Efficiency in Time spectrum
      //h_draw->EffProbPlot( 2, "EffErrFunction2" ) ;
      //h_draw->EffPlot( h.obsTime, h_Time, " EcalTime (ns) ", 100, 51, -1,  "timeEff" );  
   }

   if ( isData == 0 ) {

      // Gen CTau 
      double init_fval[2] = { 300, FitCtau } ;
      h_draw->SetFitParameter( "exp", 0., 4000., 2, init_fval , 2 );
      // Crash here--Broken , FIX IT !!!
      //h_draw->FitNDraw( h.h_ctau, "GenCTau", " ctau (mm)", " ", "logY", 0.95, 1 );

      // more gen information
      h_draw->CreateNxM( "GenInfo", 2,2 );
      h_draw->DrawNxM( 1, h.h_gen1Pt,        "Leading GenPhoton Pt (GeV/c)",      "", "logY", 1, false );
      h_draw->DrawNxM( 2, h.h_gen1RecoPt,    "Leading GenPhoton Reco Pt (GeV/c)", "", "logY", 1, false );
      h_draw->DrawNxM( 3, h.h_nGenPhotons,   "N of GenPhotons",   "", "logY", 1, false );
      h_draw->DrawNxM( 4, h.h_xbeta,         " #{beta} ",         "", "logY", 1, true ) ;

      // matching stuff
      h_draw->Draw(       h.h_matchRecoTime, "", "Matched Photon Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h.h_matchGenTime,  "",           0.75, 4 ) ;
      h_draw->DrawAppend( h.h_genTime,       "",           0.55, 6 ) ;
      h_draw->DrawAppend( h.h_matchTime,     "MatchTime",  0.35, 1 ) ;

      h_draw->EffPlot( h.h_matchTime, h.h_matchGenTime, " EcalTime (ns) ", 16, 51, -1,  "matchTimeEff" );  
      h_draw->EffPlot( h.h_matchTime, h.h_genTime,      " EcalTime (ns) ", 16, 51, -1,  "recoTimeEff" );  

      h_draw->Draw( h.h_PtRes, "PhoPtResolution", "Photon Pt Resolution", "", "", 0.95, 1 ) ;

      gStyle->SetOptStat("em");
      gStyle->SetStatW(0.25);
      gStyle->SetStatH(0.2);
      gStyle->SetTextSize(0.075);
      h_draw->SetFitParameter( "Gaus", h.h_TimeRes1, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_TimeRes1, "TimeResolution1", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h.h_TimeRes2, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_TimeRes2, "TimeResolution2", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h.h_TimeRes3, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_TimeRes3, "TimeResolution3", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;

      h_draw->SetFitParameter( "Gaus", h.h_aTimeRes1, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_aTimeRes1, "AveTimeResolution1", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h.h_aTimeRes2, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_aTimeRes2, "AveTimeResolution2", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h.h_aTimeRes3, 0, 0, 3, 4 );
      h_draw->FitNDraw( h.h_aTimeRes3, "AveTimeResolution3", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;

      h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
      h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
      h_draw->Draw2D( h.Time_R, "Time_R", "EcalTime (ns)", "  R (cm)", "", 5 ) ;
      h_draw->Draw2D( h.Time_Z, "Time_Z", "EcalTime (ns)", "|Z| (cm)", "", 5 ) ;
   }

   // some Pt/Et spectrums
   h_draw->Draw( h.h_g1Pt,   "PhotonPt",    " Pt (GeV/c) ", "",          "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_met,    "MET",         " #slash{E_{T}} (GeV) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nChi2,  "TimeChi2",    " #chi^{2} / ndof", "",      "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_fSpike, "fSpike",      " fraction of spike xtal","","logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEB, "maxSwissXEB", " max SwissCross value from EB", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEE, "maxSwissXEE", " max SwissCross value from EE", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_seedSwiss, "seedSwissX", " seed SwissCross value ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nXtals, "nXtals",      " N of xtals ", "",         "", 0.95, 1 ) ;
   h_draw->Draw( h.h_nBC,    "nBC",         " N of basic cluster ", "", "", 0.95, 1 ) ;
   h_draw->Draw( h.h_nVtx,   "NVertices",   " N of valid vertices ", "","", 0.95, 1 ) ;
   h_draw->Draw( h.h_sMin,   "sMinor",      " sMinor ", "",              "logY", 0.95, 1 ) ;
   h_draw->Draw( h.badPhoTime, "badPhoTime", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
   h_draw->Draw( h.SpikeEtaP, "SpikeEtaP",    " | #eta |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( h.SpikeEtaN, "SpikeEtaN",    " | #eta |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( h.Vz_P,      "VtxZ_P",    " | vxt_z |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( h.Vz_N,      "VtxZ_N",    " | vxt_z |    ", "",      "", 0.95, 1 ) ;

   // control sample studies 
   gStyle->SetOptStat("");
   TLegend* leg3  = new TLegend(.5, .7, .77, .9 );
   leg3->AddEntry( h.TimeLT3Jets, "  < 3Jets", "L" ) ;
   leg3->AddEntry( h.TimeGE3Jets, " >= 3Jets", "L" ) ;
   h_draw->Draw(       h.TimeLT3Jets, "", "Ecal Time (ns)", "", "logY", 0.95, 2, 1./ h.TimeLT3Jets->Integral()  ) ;
   h_draw->DrawAppend( h.TimeGE3Jets, "TimeInJet", 0.7, 4, 1./ h.TimeGE3Jets->Integral(), leg3 ) ;

   leg3->Clear();
   leg3->AddEntry( h.TimeLowMET, " MET  < 60", "L" ) ;
   leg3->AddEntry( h.TimeBigMET, " MET >= 60", "L" ) ;
   h_draw->Draw(       h.TimeLowMET, "", "Ecal Time (ns)", "", "logY", 0.95, 2, 1./h.TimeLowMET->Integral() ) ;
   h_draw->DrawAppend( h.TimeBigMET, "TimeInMET", 0.7, 4, 1./h.TimeBigMET->Integral(), leg3 ) ;

   // Multiplicity
   gStyle->SetOptStat("emuo");
   h_draw->CreateNxM( "Multiplicity", 2,2 );
   h_draw->DrawNxM( 1, h.h_nPhotons,   "N of Photons",   "", "logY", 1, false );
   h_draw->DrawNxM( 2, h.h_nJets,      "N of Jets",      "", "logY", 1, false );
   h_draw->DrawNxM( 3, h.h_nMuons,     "N of Muons",     "", "logY", 1, false );
   h_draw->DrawNxM( 4, h.h_nElectrons, "N of Electrons", "", "logY", 1, true );

   // Isolation
   h_draw->CreateNxM( "Isolations", 2,3 );
   h_draw->DrawNxM( 1, h.h_TrkIso,   "Track Isolation ",       "", "logY", 1, false );
   h_draw->DrawNxM( 2, h.h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 3, h.h_EcalIso,  "Ecal Isolation ",        "", "logY", 2, false );
   h_draw->DrawNxM( 4, h.h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 5, h.h_HcalIso,  "Hcal Isolation ",        "", "logY", 4, false );
   h_draw->DrawNxM( 6, h.h_HcalIsoR, "Hcal Isolation Ratio",   "", "logY", 4, true );

   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);
   h_draw->Draw2D( h.seedTime_Chi2, "seedTime_Chi2", "EcalTime (ns)", "Chi2",  ""  ) ;
   h_draw->Draw2D( h.h_Eta_Time, "h_Eta_Time",   "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.h_Phi_Time, "h_Phi_Time",   "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.h_Phi_Time1, "h_Phi_Time1", "#phi", "EcalTime (ns)",  ""  ) ;

   h_draw->Draw2D( h.h_RhoPhi_Halo, "h_RhoPhi_Halo", "#phi", " #rho",  ""  ) ;
   h_draw->Draw2D( h.h_PhiTimeHalo,  "h_PhiTimeHalo",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.h_EtaTimeHalo,  "h_EtaTimeHalo",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.h_EtaTimeNoHalo,  "h_EtaTimeNoHalo",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw(   h.h_nHaloHits,   "h_nHaloHits",    " N of Halo csc rechits ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_nHaloTracks, "h_nHaloTracks",  " N of Halo csc tracks  ", "",  "logY", 0.95, 1 ) ;

   //h_draw->Draw(   h.h_TimeNoHalo,  "h_TimeNoHalo",  " EcalTime (ns) ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.h_TimeNoHalo, "h_TimeNoHalo", 0.75, 2, 1  ) ;

   h_draw->Draw(   h.h_SigEtaHalo,  "h_SigEtaHalo",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_SigIetaHalo, "h_SigIetaHalo", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_SigEta,  "h_SigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_SigIeta, "h_SigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;

   hFile->Close() ;
   cout<<" hfile closed ! "<<endl ;
}  

void Histogram::Write( string theFolder , TFile* file  ) {

     if ( theFolder.size() > 0 ) file->cd( theFolder.c_str() );

     h.obsTime->Write()     ;
     h.aveObsTime->Write() ;
     h.aveObsTime1->Write() ;
     h.aveObsTime2->Write() ;
     h.obsEBTimeErr->Write()  ;
     h.obsEETimeErr->Write()  ;
     h.aveObsEBTimeErr->Write() ;
     h.aveObsEETimeErr->Write() ;
     h.aveObsEBTimeErr1->Write() ;
     h.aveObsEETimeErr1->Write() ;

     h.seedTime_Chi2->Write()  ;
     h.Time_R->Write()  ;
     h.Time_Z->Write()  ;

     h.badPhoTime->Write()     ;
     h.TimeLT3Jets->Write()    ;
     h.TimeGE3Jets->Write()    ;
     h.TimeLowMET->Write()     ;
     h.TimeBigMET->Write()     ;

     h.SpikeEtaP->Write()      ;
     h.SpikeEtaN->Write()      ;
     h.Vz_P->Write()           ;
     h.Vz_N->Write()           ;

     h.h_matchRecoTime->Write() ;
     h.h_matchGenTime->Write()  ;
     h.h_matchTime->Write()     ;
     h.h_genTime->Write()       ;
     h.h_TimeRes1->Write()      ;
     h.h_TimeRes2->Write()      ;
     h.h_TimeRes3->Write()      ;
     h.h_aTimeRes1->Write()     ;
     h.h_aTimeRes2->Write()     ;
     h.h_aTimeRes3->Write()     ;
     h.h_PtRes->Write()         ;

     h.h_Time->Write()   ;
     h.h_nChi2->Write()  ;
     h.h_ctau->Write()   ;
     h.h_xbeta->Write()  ;
     h.h_TrkIso->Write()   ;
     h.h_HcalIso->Write()  ;
     h.h_EcalIso->Write()  ;
     h.h_TrkIsoR->Write()  ;
     h.h_HcalIsoR->Write() ;
     h.h_EcalIsoR->Write() ;

     h.h_maxSwissEB->Write() ;
     h.h_maxSwissEE->Write() ;
     h.h_seedSwiss->Write()  ;
     h.h_fSpike->Write()    ;
     h.h_nXtals->Write()    ;
     h.h_nBC->Write()       ;
     h.h_sMin->Write()      ;

     h.h_met->Write()        ;
     h.h_g1Pt->Write()       ;
     h.h_gen1Pt->Write()     ;
     h.h_gen1RecoPt->Write() ;

     h.h_nVtx->Write()       ;
     h.h_nPhotons->Write()   ;
     h.h_nGenPhotons->Write();
     h.h_nJets->Write()      ;
     h.h_nMuons->Write()     ;
     h.h_nElectrons->Write() ;

     h.h_Eta_Time->Write() ;
     h.h_Phi_Time->Write() ;
     h.h_Phi_Time1->Write() ;

     h.h_RhoPhi_Halo->Write() ;
     h.h_nHaloHits->Write() ;
     h.h_nHaloTracks->Write() ;
     h.h_PhiTimeHalo->Write() ;
     h.h_EtaTimeHalo->Write() ;
     h.h_EtaTimeNoHalo->Write() ;
     h.h_TimeNoHalo->Write() ;
     h.h_SigEtaHalo->Write() ;
     h.h_SigIetaHalo->Write() ;
     h.h_SigEta->Write() ;
     h.h_SigIeta->Write() ;
}

