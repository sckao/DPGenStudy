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

void Histogram::Init() {

   obsTime     = new TH1D("obsTime", "Photon Time from seed", 160,  -14.5, 25.5);
   aveObsTime  = new TH1D("aveObsTime", "Photon Time from clusters", 160,  -14.5, 25.5);
   aveObsTime1 = new TH1D("aveObsTime1", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   aveObsTime2 = new TH1D("aveObsTime2", "Photon Time from clusters chi2 < 5", 160,  -14.5, 25.5);
   obsEBTimeErr  = new TH1D("obsEBTimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   obsEETimeErr  = new TH1D("obsEETimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   aveObsEBTimeErr  = new TH1D("aveObsEBTimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEETimeErr  = new TH1D("aveObsEETimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEBTimeErr1 = new TH1D("aveObsEBTimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);
   aveObsEETimeErr1 = new TH1D("aveObsEETimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);

   seedTime_Chi2  = new TH2D("seedTime_Chi2", "Seed Time vs Chi2 ", 160,  -14.5, 25.5, 50, 0, 100);

   badPhoTime     = new TH1D("badPhoTime", "bad channel time", 102,  -25.5, 25.5);
   TimeLT3Jets    = new TH1D("TimeLT3Jets", "Ecal Time from  < 3 Jets Events", 160,  -14.5, 25.5);
   TimeGE3Jets    = new TH1D("TimeGE3Jets", "Ecal Time from >= 3 Jets Events", 160,  -14.5, 25.5);
   TimeLowMET     = new TH1D("TimeLowMET", "Ecal Time from  MET  < 60 GeV Events", 160,  -14.5, 25.5);
   TimeBigMET     = new TH1D("TimeBigMET", "Ecal Time from  MET >= 60 GeV Events", 160,  -14.5, 25.5);

   SpikeEtaP      = new TH1D("SpikeEtaP", "#eta distribution for spike like photon ( t > 10 )", 24, 0, 2.4);
   SpikeEtaN      = new TH1D("SpikeEtaN", "#eta distribution for spike like photon ( t < -10)", 24, 0, 2.4);
   Vz_P           = new TH1D("Vz_P", " z of vertices for events with photon ( t >  10)", 65, -32.5, 32.5);
   Vz_N           = new TH1D("Vz_N", " z of vertices for events with photon ( t < -10)", 65, -32.5, 32.5);

   h_matchRecoTime = new TH1D("h_matchRecoTime", "Matched Reco Photon Time", 160,  -14.5, 25.5);
   h_matchGenTime  = new TH1D("h_matchGenTime", "Matched Gen Photon Time", 160,  -14.5, 25.5);
   h_matchTime     = new TH1D("h_matchTime", "Time Matched Gen Photon Time", 160,  -14.5, 25.5);
   h_genTime       = new TH1D("h_genTime",   "Photon Time ", 160,  -14.5, 25.5);
   h_TimeRes1   = new TH1D("h_TimeRes1", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   h_TimeRes2   = new TH1D("h_TimeRes2", "Seed Photon Time Resolution", 100,  -2.5, 2.5 );
   h_TimeRes3   = new TH1D("h_TimeRes3", "Seed Photon Time Resolution",  50,  -2.5, 2.5 );
   h_aTimeRes1   = new TH1D("h_aTimeRes1", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   h_aTimeRes2   = new TH1D("h_aTimeRes2", "Weighted Ave. Photon Time Resolution", 100,  -2.5, 2.5 );
   h_aTimeRes3   = new TH1D("h_aTimeRes3", "Weighted Ave. Photon Time Resolution",  50,  -2.5, 2.5 );
   h_PtRes     = new TH1D("h_PtRes",   " Photon Pt Resolution", 200,  -1., 1.);

   Time_R   = new TH2D("Time_R", "Gen Photon Time vs R ", 160,  -14.5, 25.5, 25, 0, 175);
   Time_Z   = new TH2D("Time_Z", "Gen Photon Time vs Z ", 160,  -14.5, 25.5, 30, 0, 390);

   h_Time   = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   h_nChi2  = new TH1D("h_nChi2", "normalized chi2 of seed xtals", 100,  0, 50.0);
   h_ctau   = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
   h_xbeta  = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
   h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );

   h_maxSwissEB = new TH1D("h_maxSwissEB", " max SwissCross value from seed EB BC ", 150,  0., 1.5 );
   h_maxSwissEE = new TH1D("h_maxSwissEE", " max SwissCross value from seed EE BC ", 150,  0., 1.5 );
   h_seedSwiss = new TH1D("h_seedSwiss", " seed SwissCross value ", 150,  0., 1.5 );
   h_fSpike   = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   h_nXtals   = new TH1D("h_nXtals", "N of crystals of the photon ", 100,  0, 100 );
   h_nBC      = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   h_sMin     = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

   h_met      = new TH1D("h_met",  "MET distribution ", 40,  0, 800);
   h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   h_gen1Pt     = new TH1D("h_gen1Pt", "Leading GenPhoton Pt ", 50,  0, 500);
   h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

   h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   h_nGenPhotons = new TH1D("h_nGenPhotons", "N of GenPhotons  ", 10,  -0.5, 9.5);
   h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);

}

void Histogram::Open( ) {

     TString Path_fName = hfolder + hfName + ".root" ;

     string hfName_ = hfolder ;
     hfName_ += hfName ;
     hfName_ += ".root" ;

     cout<<" Opening : "<< hfName_ <<endl ;

     hFile = (TFile*) TFile::Open( hfName_.c_str() , "READ" );
     //hFile->cd() ;
     cout<<" file opened ! "<<endl ;

     obsTime     = (TH1D*) hFile->Get("obsTime")     ;
     aveObsTime  = (TH1D*) hFile->Get("aveObsTime") ;
     aveObsTime1 = (TH1D*) hFile->Get("aveObsTime1") ;
     aveObsTime2 = (TH1D*) hFile->Get("aveObsTime2") ;
     obsEBTimeErr = (TH1D*) hFile->Get("obsEBTimeErr")  ;
     obsEETimeErr = (TH1D*) hFile->Get("obsEETimeErr")  ;
     aveObsEBTimeErr = (TH1D*) hFile->Get("aveObsEBTimeErr") ;
     aveObsEETimeErr = (TH1D*) hFile->Get("aveObsEETimeErr") ;
     aveObsEBTimeErr1 = (TH1D*) hFile->Get("aveObsEBTimeErr1") ;
     aveObsEETimeErr1 = (TH1D*) hFile->Get("aveObsEETimeErr1") ;

     seedTime_Chi2 = (TH2D*) hFile->Get("seedTime_Chi2")  ;
     Time_R = (TH2D*) hFile->Get("Time_R")  ;
     Time_Z = (TH2D*) hFile->Get("Time_Z")  ;

     badPhoTime = (TH1D*) hFile->Get("badPhoTime")     ;
     TimeLT3Jets = (TH1D*) hFile->Get("TimeLT3Jets")   ;
     TimeGE3Jets = (TH1D*) hFile->Get("TimeGE3Jets")   ;
     TimeLowMET = (TH1D*) hFile->Get("TimeLowMET")     ;
     TimeBigMET = (TH1D*) hFile->Get("TimeBigMET")     ;

     SpikeEtaP = (TH1D*) hFile->Get("SpikeEtaP")      ;
     SpikeEtaN = (TH1D*) hFile->Get("SpikeEtaN")      ;
     Vz_P = (TH1D*) hFile->Get("Vz_P")           ;
     Vz_N = (TH1D*) hFile->Get("Vz_N")           ;

     h_matchRecoTime = (TH1D*) hFile->Get("h_matchRecoTime") ;
     h_matchGenTime = (TH1D*) hFile->Get("h_matchGenTime")  ;
     h_matchTime = (TH1D*) hFile->Get("h_matchTime")     ;
     h_genTime = (TH1D*) hFile->Get("h_genTime")       ;
     h_TimeRes1 = (TH1D*) hFile->Get("h_TimeRes1")      ;
     h_TimeRes2 = (TH1D*) hFile->Get("h_TimeRes2")      ;
     h_TimeRes3 = (TH1D*) hFile->Get("h_TimeRes3")      ;
     h_aTimeRes1 = (TH1D*) hFile->Get("h_aTimeRes1")     ;
     h_aTimeRes2 = (TH1D*) hFile->Get("h_aTimeRes2")     ;
     h_aTimeRes3 = (TH1D*) hFile->Get("h_aTimeRes3")     ;
     h_PtRes  = (TH1D*) hFile->Get("h_PtRes")         ;

     h_Time   = (TH1D*) hFile->Get("h_Time")   ;
     h_nChi2  = (TH1D*) hFile->Get("h_nChi2")  ;
     h_ctau   = (TH1D*) hFile->Get("h_cta")   ;
     h_xbeta  = (TH1D*) hFile->Get("h_xbeta")  ;
     h_TrkIso = (TH1D*) hFile->Get("h_TrkIso")   ;
     h_HcalIso = (TH1D*) hFile->Get("h_HcalIso")  ;
     h_EcalIso = (TH1D*) hFile->Get("h_EcalIso")  ;
     h_TrkIsoR = (TH1D*) hFile->Get("h_TrkIsoR")  ;
     h_HcalIsoR = (TH1D*) hFile->Get("h_HcalIsoR") ;
     h_EcalIsoR = (TH1D*) hFile->Get("h_EcalIsoR") ;

     h_maxSwissEB = (TH1D*) hFile->Get("h_maxSwissEB") ;
     h_maxSwissEE = (TH1D*) hFile->Get("h_maxSwissEE") ;
     h_seedSwiss = (TH1D*) hFile->Get("h_seedSwiss")  ;
     h_fSpike = (TH1D*) hFile->Get("h_fSpike")    ;
     h_nXtals = (TH1D*) hFile->Get("h_nXtals")    ;
     h_nBC = (TH1D*) hFile->Get("h_nBC")       ;
     h_sMin = (TH1D*) hFile->Get("h_sMin")      ;

     h_met = (TH1D*) hFile->Get("h_met")        ;
     h_g1Pt = (TH1D*) hFile->Get("h_g1Pt")       ;
     h_gen1Pt = (TH1D*) hFile->Get("h_gen1Pt")     ;
     h_gen1RecoPt = (TH1D*) hFile->Get("h_gen1RecoPt") ;

     h_nVtx        = (TH1D*) hFile->Get("h_nVtx")       ;
     h_nPhotons    = (TH1D*) hFile->Get("h_nPhotons")   ;
     h_nGenPhotons = (TH1D*) hFile->Get("h_nGenPhotons");
     h_nJets  = (TH1D*) hFile->Get("h_nJets")      ;
     h_nMuons = (TH1D*) hFile->Get("h_nMuons")     ;
     h_nElectrons = (TH1D*) hFile->Get("h_nElectrons") ;

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
      Int_t nu0  = h_genTime->Integral(bin_tcut,160);
      Int_t nu0a = h_genTime->Integral(43,160);      // ignore the photons outside ECAL ( t = -4 ns )
      IntStr0 += nu0 ;
      IntStr0 += " / " ;
      IntStr0 += nu0a ;
      IntStr0 += " Gen " ;
      leg1->AddEntry( h_genTime, IntStr0,  "L");
   } 
   /// seed time
   Int_t nu1  = obsTime->Integral(bin_tcut,160);
   Int_t nu1a = obsTime->Integral(1,160);
   IntStr1 += nu1 ;
   IntStr1 += " / " ;
   IntStr1 += nu1a ;
   IntStr1 += " Seed " ;
   leg1->AddEntry( obsTime, IntStr1,  "L");
   /// altered cluster time
   Int_t nu2  = aveObsTime->Integral(bin_tcut,160);
   Int_t nu2a = aveObsTime->Integral(1,160);
   IntStr2 += nu2 ;
   IntStr2 += " / " ;
   IntStr2 += nu2a ;
   IntStr2 += " Cluster " ;
   leg1->AddEntry( aveObsTime, IntStr2,  "L");
   /// original cluster time with Chi2 cut

   Int_t nu3  = aveObsTime1->Integral(bin_tcut,160);
   Int_t nu3a = aveObsTime1->Integral(1,160);
   IntStr3 += nu3 ;
   IntStr3 += " / " ;
   IntStr3 += nu3a ;
   IntStr3 += " Chi2 " ;
   leg1->AddEntry( aveObsTime1, IntStr3,  "L");

   cout<<" nEvent >= "<< TCut <<" ns1 = "<<nu1 <<" ns2 = "<<nu2 <<" ns3 = "<<nu3 <<endl; 

   // Photon Time
   gStyle->SetOptStat("ermi");
   if ( isData == 1 ) {

      ///double init_fval[3] = { 10000, -0.2, 1. } ;
      ///h_draw->SetFitParameter( "Gaus", -3 , 3., 3, init_fval , 8 );
      //h_draw->SetFitParameter( "Gaus", obsTime, 0, 0, 3, 8 );
      //h_draw->FitNDraw(       obsTime, "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;

      // for DOE
      h_draw->Draw(       obsTime, "SeedTime", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;

      TLegend* leg2  = new TLegend(.52, .72, .77, .9 );
      leg2->AddEntry( obsTime,    " Seed        ",     "L" ) ;
      leg2->AddEntry( aveObsTime, " Averaged    ", "L" ) ;
      h_draw->SetHistoInfo( obsTime,    " Data (Run2012B) ", 2 ) ;
      h_draw->SetHistoInfo( aveObsTime, "", 2 ) ;
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( aveObsTime, "PhotonTime", 0.75, 2, 1, leg2 ) ;
      delete leg2 ;

      TLegend* leg3  = new TLegend(.45, .72, .77, .9 );
      leg3->AddEntry( obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( aveObsTime1, "Averaged + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( aveObsTime1, "", 2 ) ;
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;

      leg3->Clear();
      leg3->AddEntry( obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( aveObsTime2, "Seed + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( aveObsTime2, "", 2 ) ;
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( aveObsTime2, "SeedPhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;
      delete leg3 ;

      /*
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "",  0.72, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.49, 6, 1, leg1 ) ;
     */
      h_draw->Draw(       obsEBTimeErr, "", "EB Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsEBTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsEBTimeErr1, "EBPhotonTimeErr", 0.55, 6 ) ;

      h_draw->Draw(       obsEETimeErr, "", "EE Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsEETimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsEETimeErr1, "EEPhotonTimeErr", 0.55, 6 ) ;

   } else { 

      // for DOE
      gStyle->SetOptStat("");
      h_draw->Draw(       obsTime, "SeedTime", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;

      TLegend* leg2  = new TLegend(.52, .72, .77, .9 );
      leg2->AddEntry( obsTime,    " Seed        ", "L" ) ;
      leg2->AddEntry( aveObsTime, " Averaged    ", "L" ) ;
      h_draw->SetHistoInfo( obsTime,    " MC (GMSB) ", 2 ) ;
      h_draw->SetHistoInfo( aveObsTime, "", 2 ) ;
      h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( aveObsTime, "PhotonTime", 0.75, 2, 1, leg2 ) ;

      TLegend* leg3  = new TLegend(.45, .72, .77, .9 );
      leg3->AddEntry( obsTime,     "Seed",     "L" ) ;
      leg3->AddEntry( aveObsTime1, "Averaged + #chi^{2}/ndof < 5", "L" ) ;
      h_draw->SetHistoInfo( aveObsTime1, "", 2 ) ;
      h_draw->Draw(       obsTime,     "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime_Chi2Cut", 0.75, 2, 1, leg3 ) ;
      delete leg3 ;
      
      /*
      h_draw->Draw(     h_genTime, "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
      h_draw->DrawAppend( obsTime, "", 0.75, 2 ) ;
      h_draw->DrawAppend( aveObsTime, "", 0.55, 4 ) ;
      h_draw->DrawAppend( aveObsTime1, "PhotonTime", 0.35, 6, 1,  leg1 ) ;
      */

      h_draw->Draw(       obsEBTimeErr, "", "EB Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsEBTimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsEBTimeErr1, "EBPhotonTimeErr", 0.55, 6 ) ;

      h_draw->Draw(       obsEETimeErr, "", "EE Time Error (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( aveObsEETimeErr, "", 0.75, 4 ) ;
      h_draw->DrawAppend( aveObsEETimeErr1, "EEPhotonTimeErr", 0.55, 6 ) ;
      // Efficiency in Time spectrum
      //h_draw->EffProbPlot( 2, "EffErrFunction2" ) ;
      //h_draw->EffPlot( obsTime, h_Time, " EcalTime (ns) ", 100, 51, -1,  "timeEff" );  
   }

   if ( isData == 0 ) {

      // Gen CTau 
      double init_fval[2] = { 300, FitCtau } ;
      h_draw->SetFitParameter( "exp", 0., 4000., 2, init_fval , 2 );
      h_draw->FitNDraw( h_ctau, "GenCTau", " ctau (mm)", "", "logY", 0.95, 1 );

      // more gen information
      h_draw->CreateNxM( "GenInfo", 2,2 );
      h_draw->DrawNxM( 1, h_gen1Pt,        "Leading GenPhoton Pt (GeV/c)",      "", "logY", 1, false );
      h_draw->DrawNxM( 2, h_gen1RecoPt,    "Leading GenPhoton Reco Pt (GeV/c)", "", "logY", 1, false );
      h_draw->DrawNxM( 3, h_nGenPhotons,   "N of GenPhotons",   "", "logY", 1, false );
      h_draw->DrawNxM( 4, h_xbeta,         " #{beta} ",         "", "logY", 1, true ) ;

      // matching stuff
      h_draw->Draw(       h_matchRecoTime, "", "Matched Photon Time (ns)", "", "logY", 0.95, 2 ) ;
      h_draw->DrawAppend( h_matchGenTime,  "",           0.75, 4 ) ;
      h_draw->DrawAppend( h_genTime,       "",           0.55, 6 ) ;
      h_draw->DrawAppend( h_matchTime,     "MatchTime",  0.35, 1 ) ;

      h_draw->EffPlot( h_matchTime, h_matchGenTime, " EcalTime (ns) ", 16, 51, -1,  "matchTimeEff" );  
      h_draw->EffPlot( h_matchTime, h_genTime,      " EcalTime (ns) ", 16, 51, -1,  "recoTimeEff" );  

      h_draw->Draw( h_PtRes, "PhoPtResolution", "Photon Pt Resolution", "", "", 0.95, 1 ) ;

      gStyle->SetOptStat("em");
      gStyle->SetStatW(0.25);
      gStyle->SetStatH(0.2);
      gStyle->SetTextSize(0.075);
      h_draw->SetFitParameter( "Gaus", h_TimeRes1, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_TimeRes1, "TimeResolution1", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h_TimeRes2, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_TimeRes2, "TimeResolution2", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h_TimeRes3, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_TimeRes3, "TimeResolution3", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;

      h_draw->SetFitParameter( "Gaus", h_aTimeRes1, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_aTimeRes1, "AveTimeResolution1", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h_aTimeRes2, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_aTimeRes2, "AveTimeResolution2", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;
      h_draw->SetFitParameter( "Gaus", h_aTimeRes3, 0, 0, 3, 4 );
      h_draw->FitNDraw( h_aTimeRes3, "AveTimeResolution3", "Reco - Gen Photon Time (ns)", "", "", 0.95, 1 ) ;

      h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
      h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
      h_draw->Draw2D( Time_R, "Time_R", "EcalTime (ns)", "  R (cm)", "", 5 ) ;
      h_draw->Draw2D( Time_Z, "Time_Z", "EcalTime (ns)", "|Z| (cm)", "", 5 ) ;
   }

   // some Pt/Et spectrums
   h_draw->Draw( h_g1Pt,   "PhotonPt",    " Pt (GeV/c) ", "",          "logY", 0.95, 1 ) ;
   h_draw->Draw( h_met,    "MET",         " #slash{E_{T}} (GeV) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_nChi2,  "TimeChi2",    " #chi^{2} / ndof", "",      "logY", 0.95, 1 ) ;
   h_draw->Draw( h_fSpike, "fSpike",      " fraction of spike xtal","","logY", 0.95, 1 ) ;
   h_draw->Draw( h_maxSwissEB, "maxSwissXEB", " max SwissCross value from EB", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_maxSwissEE, "maxSwissXEE", " max SwissCross value from EE", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_seedSwiss, "seedSwissX", " seed SwissCross value ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h_nXtals, "nXtals",      " N of xtals ", "",         "", 0.95, 1 ) ;
   h_draw->Draw( h_nBC,    "nBC",         " N of basic cluster ", "", "", 0.95, 1 ) ;
   h_draw->Draw( h_nVtx,   "NVertices",   " N of valid vertices ", "","", 0.95, 1 ) ;
   h_draw->Draw( h_sMin,   "sMinor",      " sMinor ", "",              "logY", 0.95, 1 ) ;
   h_draw->Draw( badPhoTime, "badPhoTime", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;
   h_draw->Draw( SpikeEtaP, "SpikeEtaP",    " | #eta |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( SpikeEtaN, "SpikeEtaN",    " | #eta |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( Vz_P,      "VtxZ_P",    " | vxt_z |    ", "",      "", 0.95, 1 ) ;
   h_draw->Draw( Vz_N,      "VtxZ_N",    " | vxt_z |    ", "",      "", 0.95, 1 ) ;

   // control sample studies 
   gStyle->SetOptStat("");
   TLegend* leg3  = new TLegend(.5, .7, .77, .9 );
   leg3->AddEntry( TimeLT3Jets, "  < 3Jets", "L" ) ;
   leg3->AddEntry( TimeGE3Jets, " >= 3Jets", "L" ) ;
   h_draw->Draw(       TimeLT3Jets, "", "Ecal Time (ns)", "", "logY", 0.95, 2, 1./TimeLT3Jets->Integral()  ) ;
   h_draw->DrawAppend( TimeGE3Jets, "TimeInJet", 0.7, 4, 1./TimeGE3Jets->Integral(), leg3 ) ;

   leg3->Clear();
   leg3->AddEntry( TimeLowMET, " MET  < 60", "L" ) ;
   leg3->AddEntry( TimeBigMET, " MET >= 60", "L" ) ;
   h_draw->Draw(       TimeLowMET, "", "Ecal Time (ns)", "", "logY", 0.95, 2, 1./TimeLowMET->Integral() ) ;
   h_draw->DrawAppend( TimeBigMET, "TimeInMET", 0.7, 4, 1./TimeBigMET->Integral(), leg3 ) ;

   // Multiplicity
   gStyle->SetOptStat("emuo");
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

   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   h_draw->Draw2D( seedTime_Chi2, "seedTime_Chi2", "EcalTime (ns)", "Chi2",  ""  ) ;

   hFile->Close() ;
   cout<<" hfile closed ! "<<endl ;
}  

void Histogram::Write( string theFolder , TFile* file  ) {

     if ( theFolder.size() > 0 ) file->cd( theFolder.c_str() );

     obsTime->Write()     ;
     aveObsTime->Write() ;
     aveObsTime1->Write() ;
     aveObsTime2->Write() ;
     obsEBTimeErr->Write()  ;
     obsEETimeErr->Write()  ;
     aveObsEBTimeErr->Write() ;
     aveObsEETimeErr->Write() ;
     aveObsEBTimeErr1->Write() ;
     aveObsEETimeErr1->Write() ;

     seedTime_Chi2->Write()  ;
     Time_R->Write()  ;
     Time_Z->Write()  ;

     badPhoTime->Write()     ;
     TimeLT3Jets->Write()    ;
     TimeGE3Jets->Write()    ;
     TimeLowMET->Write()     ;
     TimeBigMET->Write()     ;

     SpikeEtaP->Write()      ;
     SpikeEtaN->Write()      ;
     Vz_P->Write()           ;
     Vz_N->Write()           ;

     h_matchRecoTime->Write() ;
     h_matchGenTime->Write()  ;
     h_matchTime->Write()     ;
     h_genTime->Write()       ;
     h_TimeRes1->Write()      ;
     h_TimeRes2->Write()      ;
     h_TimeRes3->Write()      ;
     h_aTimeRes1->Write()     ;
     h_aTimeRes2->Write()     ;
     h_aTimeRes3->Write()     ;
     h_PtRes->Write()         ;

     h_Time->Write()   ;
     h_nChi2->Write()  ;
     h_ctau->Write()   ;
     h_xbeta->Write()  ;
     h_TrkIso->Write()   ;
     h_HcalIso->Write()  ;
     h_EcalIso->Write()  ;
     h_TrkIsoR->Write()  ;
     h_HcalIsoR->Write() ;
     h_EcalIsoR->Write() ;

     h_maxSwissEB->Write() ;
     h_maxSwissEE->Write() ;
     h_seedSwiss->Write()  ;
     h_fSpike->Write()    ;
     h_nXtals->Write()    ;
     h_nBC->Write()       ;
     h_sMin->Write()      ;

     h_met->Write()        ;
     h_g1Pt->Write()       ;
     h_gen1Pt->Write()     ;
     h_gen1RecoPt->Write() ;

     h_nVtx->Write()       ;
     h_nPhotons->Write()   ;
     h_nGenPhotons->Write();
     h_nJets->Write()      ;
     h_nMuons->Write()     ;
     h_nElectrons->Write() ;

}

