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
   hS.aveObsTime2 = new TH1D("aveObsTime2", "Photon Time from seed with cluster chi2 < 5", 160,  -14.5, 25.5);
   hS.obsEBTimeErr  = new TH1D("obsEBTimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   hS.obsEETimeErr  = new TH1D("obsEETimeErr", "Photon Time Error from seed", 100,  0, 2.0);
   hS.aveObsEBTimeErr  = new TH1D("aveObsEBTimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEETimeErr  = new TH1D("aveObsEETimeErr", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEBTimeErr1 = new TH1D("aveObsEBTimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);
   hS.aveObsEETimeErr1 = new TH1D("aveObsEETimeErr1", "Photon Time Error from clusters", 100,  0, 2.0);

   hS.seedTime_Chi2  = new TH2D("seedTime_Chi2", "Seed Time vs Chi2 ", 160,  -14.5, 25.5, 50, 0, 100);

   hS.badPhoTime     = new TH1D("badPhoTime", "bad channel time", 102,  -25.5, 25.5);
   hS.TimeLT3Jets    = new TH1D("TimeLT3Jets", "Ecal Time from  0 Jets Events", 160,  -14.5, 25.5);
   hS.TimeGE3Jets    = new TH1D("TimeGE3Jets", "Ecal Time from  >= 1 Jets Events", 160,  -14.5, 25.5);
   hS.TimeLowMET     = new TH1D("TimeLowMET", "Ecal Time from  MET  < 60 GeV Events", 160,  -14.5, 25.5);
   hS.TimeBigMET     = new TH1D("TimeBigMET", "Ecal Time from  MET >= 60 GeV Events", 160,  -14.5, 25.5);

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

   hS.h_HoverE  = new TH1D("h_HoverE", " H/E  ", 80,  0., 0.8 ) ;
   hS.h_sigIeta = new TH1D("h_sigIeta", " Sigma Ieta Ieta ", 100,  0., 0.1 ) ;
   hS.h_Time    = new TH1D("h_Time", "Expected Photon Time", 160,  -14.5, 25.5);
   hS.h_nChi2   = new TH1D("h_nChi2", "normalized chi2 of seed xtals", 100,  0, 50.0);
   hS.h_ctau    = new TH1D("h_ctau", "gen #chi_{0} lifetime (ctau)", 80,  0, 4000);
   hS.h_xbeta   = new TH1D("h_xbeta", "Beta of Neutrlino ", 55,  0, 1.1);
   hS.h_TrkIsoR  = new TH1D("h_TrkIsoR", " Track Isolation Ratio", 110, 0, 1.1 );
   hS.h_HcalIsoR = new TH1D("h_HcalIsoR", " HCAL Isolation Ratio", 110, 0, 1.1 );
   hS.h_EcalIsoR = new TH1D("h_EcalIsoR", " ECAL Isolation Ratio", 110, 0, 1.1 );
   
   hS.h_cHadIso = new TH1D("h_cHadIso", " Charged Hadronic IsoDeposit ", 100, 0, 10. );
   hS.h_nHadIso = new TH1D("h_nHadIso", " Neutral Hadronic IsoDeposit ", 100, 0, 10. );
   hS.h_photIso = new TH1D("h_photIso", " Photon IsoDeposit ", 100, 0, 10. );
   hS.h_cHadIso_t = new TH2D("h_cHadIso_t", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
   hS.h_nHadIso_t = new TH2D("h_nHadIso_t", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
   hS.h_photIso_t = new TH2D("h_photIso_t", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );

   hS.h_maxSwissEB = new TH1D("h_maxSwissEB", " max SwissCross value from seed EB BC ", 150,  0., 1.5 );
   hS.h_maxSwissEE = new TH1D("h_maxSwissEE", " max SwissCross value from seed EE BC ", 150,  0., 1.5 );
   hS.h_seedSwiss  = new TH1D("h_seedSwiss", " seed SwissCross value ", 150,  0., 1.5 );
   hS.h_fSpike     = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   hS.h_nXtals     = new TH1D("h_nXtals", "N of crystals of the photon ", 50,  0, 50 );
   hS.h_nBC        = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   hS.h_sMin       = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

   hS.h_met      = new TH1D("h_met",  "MET distribution ", 50,  0, 500);
   hS.h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   hS.h_gen1Pt     = new TH1D("h_gen1Pt", "Leading GenPhoton Pt ", 50,  0, 500);
   hS.h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

   hS.h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   hS.h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   hS.h_nGenPhotons = new TH1D("h_nGenPhotons", "N of GenPhotons  ", 10,  -0.5, 9.5);
   hS.h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   hS.h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   hS.h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);

   hS.h_Eta_Time  = new TH2D( "h_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
   hS.h_Phi_Time  = new TH2D( "h_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.h_sMaj_Time = new TH2D( "h_sMaj_Time", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
   hS.h_sMin_Time = new TH2D( "h_sMin_Time",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
   hS.h_Pt_Time   = new TH2D( "h_Pt_Time",  " Pt vs. Ecal time ", 50, 0., 500 , 160, -20, 20  ) ;
   hS.h_cscdPhi_Time  = new TH2D( "h_cscdPhi_Time", " d#Phi vs Ecal time", 64, 0, 3.2, 160, -20, 20 ) ;
   hS.h_sigIeta_Time  = new TH2D( "h_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;

   hS.h_RhoPhi_Halo = new TH2D( "h_RhoPhi_Halo", " phi vs rho for halo tracks", 63, -3.15, 3.15, 50, 0, 500 ) ;
   hS.h_nHaloHits   = new TH1D( "h_nHaloHits",   " N of out of time CSC rechits", 50, 0, 50 ) ;
   hS.h_nHaloTracks = new TH1D( "h_nHaloTracks",   " N of CSC Halo Tracks", 10, 0, 10 ) ;

   hS.pureTime     = new TH1D("pureTime", "Photon Time after ghost cleaning", 160,  -14.5, 25.5);
   hS.ghostTime    = new TH1D("ghostTime", "Ghost Photon Time ", 160,  -14.5, 25.5);

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

     h.h_HoverE   = (TH1D*) hFile->Get("h_HoverE")   ;
     h.h_sigIeta  = (TH1D*) hFile->Get("h_sigIeta")   ;
     h.h_Time   = (TH1D*) hFile->Get("h_Time")   ;
     h.h_nChi2  = (TH1D*) hFile->Get("h_nChi2")  ;
     h.h_ctau   = (TH1D*) hFile->Get("h_ctau")   ;
     h.h_xbeta  = (TH1D*) hFile->Get("h_xbeta")  ;
     h.h_TrkIsoR = (TH1D*) hFile->Get("h_TrkIsoR")  ;
     h.h_HcalIsoR = (TH1D*) hFile->Get("h_HcalIsoR") ;
     h.h_EcalIsoR = (TH1D*) hFile->Get("h_EcalIsoR") ;

     h.h_cHadIso = (TH1D*) hFile->Get("h_cHadIso") ;
     h.h_nHadIso = (TH1D*) hFile->Get("h_nHadIso") ;
     h.h_photIso = (TH1D*) hFile->Get("h_photIso") ;
     h.h_cHadIso_t = (TH2D*) hFile->Get("h_cHadIso_t") ;
     h.h_nHadIso_t = (TH2D*) hFile->Get("h_nHadIso_t") ;
     h.h_photIso_t = (TH2D*) hFile->Get("h_photIso_t") ;

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
     h.h_nJets       = (TH1D*) hFile->Get("h_nJets")      ;
     h.h_nMuons      = (TH1D*) hFile->Get("h_nMuons")     ;
     h.h_nElectrons  = (TH1D*) hFile->Get("h_nElectrons") ;

     h.h_Pt_Time   = (TH2D*) hFile->Get("h_Pt_Time")  ;
     h.h_Eta_Time  = (TH2D*) hFile->Get("h_Eta_Time")  ;
     h.h_Phi_Time  = (TH2D*) hFile->Get("h_Phi_Time")  ;
     h.h_sMaj_Time = (TH2D*) hFile->Get("h_sMaj_Time")  ;
     h.h_sMin_Time = (TH2D*) hFile->Get("h_sMin_Time") ;
     h.h_cscdPhi_Time  = (TH2D*) hFile->Get("h_cscdPhi_Time")  ;
     h.h_sigIeta_Time  = (TH2D*) hFile->Get("h_sigIeta_Time")  ;

     h.h_RhoPhi_Halo = (TH2D*) hFile->Get("h_RhoPhi_Halo")  ;
     h.h_nHaloHits   = (TH1D*) hFile->Get("h_nHaloHits")  ;
     h.h_nHaloTracks = (TH1D*) hFile->Get("h_nHaloTracks")  ;

     h.pureTime      = (TH1D*) hFile->Get("pureTime")     ;
     h.ghostTime     = (TH1D*) hFile->Get("ghostTime")     ;
     cout<<" link all histograms  "<<endl ;
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

     h.h_HoverE->Write()   ;
     h.h_sigIeta->Write()   ;
     h.h_Time->Write()   ;
     h.h_nChi2->Write()  ;
     h.h_ctau->Write()   ;
     h.h_xbeta->Write()  ;
     h.h_TrkIsoR->Write()  ;
     h.h_HcalIsoR->Write() ;
     h.h_EcalIsoR->Write() ;

     h.h_cHadIso->Write() ;
     h.h_nHadIso->Write() ;
     h.h_photIso->Write() ;
     h.h_cHadIso_t->Write() ;
     h.h_nHadIso_t->Write() ;
     h.h_photIso_t->Write() ;

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
     h.h_Pt_Time->Write() ;
     h.h_sMaj_Time->Write() ;
     h.h_sMin_Time->Write() ;
     h.h_cscdPhi_Time->Write() ;
     h.h_sigIeta_Time->Write() ;

     h.h_RhoPhi_Halo->Write() ;
     h.h_nHaloHits->Write() ;
     h.h_nHaloTracks->Write() ;

     h.pureTime->Write() ;
     h.ghostTime->Write() ;
}

void Histogram::DrawHistograms() {

   // link all exist histograms
   Open() ;

   cout<<" start drawig "<<endl ;
   // ********************* 
   // *  Draw histograms  *
   // *********************
   gStyle->SetOptStat("");
   //gStyle->SetOptStat("ermi");

   TLegend* leg1  = new TLegend(.5, .7, .77, .9 );
   leg1->Clear();
   leg1->SetTextSize(0.03) ;

   // calculate the number events later than "TCut"
   int bin_tcut = static_cast<int>( (TCut + 14.5) / 0.25 ) ;
   /// seed time
   Int_t nu1  = h.obsTime->Integral(bin_tcut,160);
   Int_t nu1a = h.obsTime->Integral(1,160);
   char legStr1[35] ;
   sprintf( legStr1,  "Seed: %d / %d", nu1, nu1a ) ;
   leg1->AddEntry( h.obsTime, legStr1,  "L");
   /// altered cluster time
   Int_t nu2  = h.aveObsTime->Integral(bin_tcut,160);
   Int_t nu2a = h.aveObsTime->Integral(1,160);
   char legStr2[35] ;
   sprintf( legStr2,  "Cluster: %d / %d", nu2, nu2a  ) ;
   leg1->AddEntry( h.aveObsTime, legStr2,  "L");

   /// original cluster time with Chi2 cut
   Int_t nu3  = h.aveObsTime1->Integral(bin_tcut,160);
   Int_t nu3a = h.aveObsTime1->Integral(1,160);
   char legStr3[35] ;
   sprintf( legStr3,  "Chi2: %d / %d", nu3, nu3a ) ;
   leg1->AddEntry( h.aveObsTime1, legStr3,  "L");

   /// gen time
   if ( isData == 0 ) {
      Int_t nu0  = h.h_genTime->Integral(bin_tcut,160);
      Int_t nu0a = h.h_genTime->Integral(43,160);      // ignore the photons outside ECAL ( t = -4 ns )
      char legStr0[35] ;
      sprintf( legStr0,  "Gen: %d / %d", nu0, nu0a ) ;
      leg1->AddEntry( h.h_genTime, legStr0,  "L");
      h_draw->Draw(    h.h_genTime,  "", "Ecal Time (ns)", "", "logY", 0.35, 6 ) ;
      h_draw->DrawAppend( h.obsTime, "",           0.95, 1, 1 ) ;
   } else {
      h_draw->Draw(    h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   }
   h_draw->DrawAppend( h.aveObsTime, "",           0.75, 2, 1 ) ;
   h_draw->DrawAppend( h.aveObsTime1,"ECALTime",           0.55, 4, 1, leg1 ) ;
   //cout<<" nEvent >= "<< TCut <<" ns1 = "<<nu1 <<" ns2 = "<<nu2 <<" ns3 = "<<nu3 <<endl; 

   h_draw->Draw(       h.obsEBTimeErr, "", "EB Time Error (ns)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h.aveObsEBTimeErr, "", 0.75, 4 ) ;
   h_draw->DrawAppend( h.aveObsEBTimeErr1, "EBPhotonTimeErr", 0.55, 6 ) ;

   h_draw->Draw(       h.obsEETimeErr, "", "EE Time Error (ns)", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( h.aveObsEETimeErr, "", 0.75, 4 ) ;
   h_draw->DrawAppend( h.aveObsEETimeErr1, "EEPhotonTimeErr", 0.55, 6 ) ;

   h_draw->Draw( h.h_sigIeta, "sigmaIeta", " sigma_IetaIeta", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_HoverE, "HoverE", " H/E", "", "logY", 0.95, 1 ) ;

   if ( isData == 0 ) {

      // Gen CTau 
      if ( FitCtau > 0 ) {
         double init_fval[2] = { 800, FitCtau } ;
         h_draw->SetFitParameter( "exp", 0., 4000., 2, init_fval , 2 );
         h_draw->FitNDraw( h.h_ctau, "GenCTau", " ctau (mm)", " ", "logY", 0.95, 1 );
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

	 h_draw->EffPlot( h.h_matchTime, h.h_matchGenTime, " EcalTime (ns) ", 16, 51, -1, "matchTimeEff" );  
	 h_draw->EffPlot( h.h_matchTime, h.h_genTime,      " EcalTime (ns) ", 16, 51, -1, "recoTimeEff" );  
      }

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
      h_draw->Draw2D( h.Time_R, "Time_R", "EcalTime (ns)", "  R (cm)", "logZ", 5 ) ;
      h_draw->Draw2D( h.Time_Z, "Time_Z", "EcalTime (ns)", "|Z| (cm)", "logZ", 5 ) ;
   }

   // some Pt/Et spectrums
   h_draw->Draw( h.h_g1Pt,   "PhotonPt",    " Pt (GeV/c) ", "",          "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_met,    "MET",         " #slash{E_{T}} (GeV) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nChi2,  "TimeChi2",    " #chi^{2} / ndof", "",      "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_fSpike, "fSpike",      " fraction of spike xtal","","logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEB, "maxSwissXEB", " max SwissCross value from EB", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEE, "maxSwissXEE", " max SwissCross value from EE", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_seedSwiss, "seedSwissX", " seed SwissCross value ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nXtals, "nXtals",      " N of xtals ", "",         "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nBC,    "nBC",         " N of basic cluster ", "", "", 0.95, 1 ) ;
   h_draw->Draw( h.h_nVtx,   "NVertices",   " N of valid vertices ", "","", 0.95, 1 ) ;
   h_draw->Draw( h.h_sMin,   "sMinor",      " sMinor ", "",              "logY", 0.95, 1 ) ;
   h_draw->Draw( h.badPhoTime, "badPhoTime", "Ecal Time (ns)", "", "logY", 0.95, 2 ) ;

   // control sample studies 
   gStyle->SetOptStat("");
   TLegend* leg3  = new TLegend(.5, .7, .77, .9 );
   leg3->AddEntry( h.TimeLT3Jets, "  0 Jet", "L" ) ;
   leg3->AddEntry( h.TimeGE3Jets, " > 0 Jet", "L" ) ;
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
   //cout<<" 0jet : "<< h.h_nJets->GetBinContent(1) <<endl ;;
   //cout<<" 1jet : "<< h.h_nJets->GetBinContent(2) <<endl ;;
   //cout<<" All : "<< h.h_nJets->Integral() <<endl ;;

   // Isolation
   h_draw->CreateNxM( "Isolations", 2,2 );
   h_draw->DrawNxM( 2, h.h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 4, h.h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 6, h.h_HcalIsoR, "Hcal Isolation Ratio",   "", "logY", 4, true );

   // PF Isolation
   h_draw->CreateNxM( "PFIsolations", 2,2 );
   h_draw->DrawNxM( 1, h.h_cHadIso,  "Charged Hadronic Isolation ",  "", "logY", 1, false );
   h_draw->DrawNxM( 2, h.h_nHadIso,  "Neutral Hadronic Isolation ",  "", "logY", 2, false );
   h_draw->DrawNxM( 3, h.h_photIso,  "Photon Isolation ",   "", "logY", 4, true );

   // Halo Studies
   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);
   h_draw->Draw2D( h.seedTime_Chi2, "seedTime_Chi2", "EcalTime (ns)", "Chi2",  ""  ) ;
   h_draw->Draw2D( h.h_Eta_Time,    "h_Eta_Time",    "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.h_Phi_Time,    "h_Phi_Time",    "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.h_Pt_Time,     "h_Pt_Time",     "P_{T}", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.h_sMaj_Time,   "h_sMaj_Time",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.h_sMin_Time,   "h_sMin_Time",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.h_cscdPhi_Time,"h_cscdPhi_Time","d#phi", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_sigIeta_Time,"h_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_cHadIso_t,   "h_cHadIso_t",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_nHadIso_t,   "h_nHadIso_t",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_photIso_t,   "h_photIso_t",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h.h_RhoPhi_Halo,   "h_RhoPhi_Halo", "#phi", " #rho",  ""  ) ;
   h_draw->Draw(   h.h_nHaloHits,     "h_nHaloHits",    " N of Halo csc rechits ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_nHaloTracks,   "h_nHaloTracks",  " N of Halo csc tracks  ", "",  "logY", 0.95, 1 ) ;

   h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.pureTime,   "", 0.75, 2, 1  ) ;
   h_draw->DrawAppend( h.ghostTime,  "h_TimeTag", 0.55, 4, 1  ) ;

   hFile->Close() ;
   cout<<" hfile closed ! "<<endl ;
}  

