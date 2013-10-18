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

   hS.seedTime_Chi2  = new TH2D("seedTime_Chi2", "Seed Time vs Chi2 ", 160,  -14.5, 25.5, 50, 0, 100);

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

   hS.h_HoverE  = new TH1D("h_HoverE", " H/E  ", 100,  0., 0.5 ) ;
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
   hS.h_nXtals     = new TH1D("h_nXtals", "N of crystals of the photon ", 50,  0, 50 );
   hS.h_nBC        = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   hS.h_sMin       = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

  
   hS.h_Eta      = new TH1D("h_Eta",  "#eta distribution ", 51,  -2.5, 2.5);
   hS.h_met      = new TH1D("h_met",  "MET distribution ", 50,  0, 500);
   hS.h_g1Pt     = new TH1D("h_g1Pt", "Leading Photon Pt ", 50,  0, 500);
   hS.h_gen1Pt     = new TH1D("h_gen1Pt", "Leading GenPhoton Pt ", 50,  0, 500);
   hS.h_genMET     = new TH1D("h_genMET", "gen MET(MET from gravitino)  ", 50,  0, 500);
   hS.h_METRes     = new TH1D("h_METRes", "gen MET - reco MET  ", 100,  -200, 200);
   hS.h_METdPhi    = new TH1D("h_METdPhi", "#Delta#Phi(gen MET,reco MET)  ", 64,  0., 3.2);
   hS.h_gen1RecoPt = new TH1D("h_gen1RecoPt", "Leading GenPhoton Reco Pt ", 50,  0, 500);

   hS.h_nVtx       = new TH1D("h_nVtx",    "N of vertices", 51,  -0.5, 50.5 );
   hS.h_nPhotons   = new TH1D("h_nPhotons", "N of Photons  ", 10,  -0.5, 9.5);
   hS.h_nGenPhotons = new TH1D("h_nGenPhotons", "N of GenPhotons  ", 10,  -0.5, 9.5);
   hS.h_nJets      = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   hS.h_nMuons     = new TH1D("h_nMuons", "N of Muons  ", 10,  -0.5, 9.5);
   hS.h_nElectrons = new TH1D("h_nElectrons", "N of Electrons  ", 10,  -0.5, 9.5);

   hS.Gh_rho_Time  = new TH2D( "Gh_rho_Time", " #rho vs Ecal time", 65, 0., 160.55, 200, -25, 25 ) ;
   hS.Gh_rho_dT    = new TH2D( "Gh_rho_dT",    " #rho vs dT ", 65, 0., 160.55, 200, -7.5, 7.5 ) ;
   hS.Gh_Phi_Time  = new TH2D( "Gh_Phi_Time", " #phi vs Ecal time", 63, -3.15, 3.15, 200, -25, 25 ) ;
   hS.Gh_Eta_Time  = new TH2D( "Gh_Eta_Time", " #eta vs Ecal time", 51, -2.5, 2.5, 200, -25, 25 ) ;
   hS.Gh_Eta_Time1 = new TH2D( "Gh_Eta_Time1", " #eta vs Ecal time", 51, -2.5, 2.5, 200, -25, 25 ) ;
   hS.h_Pt_Eta    = new TH2D( "h_Pt_Eta",  " Pt vs. #eta ", 50, 0., 500 , 51, -2.5, 2.5  ) ;
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

   hS.m_sigIeta_time = new TH2D("m_sigIeta_time", "#sigma_{i#eta} vs time", 80, 0, 0.08, 100, -5, 20 ) ;
   hS.m_sMaj_sMin    = new TH2D("m_sMaj_sMin",    "sMaj vs sMin", 100, 0, 2, 60, 0.1, 0.4 ) ;
   hS.m_sMaj_time    = new TH2D("m_sMaj_time",    "sMaj vs Ecal time", 100, 0, 2, 100, -5, 20 ) ;
   hS.m_sMin_time    = new TH2D("m_sMin_time",    "sMin vs. Ecal time ", 100, 0., 0.5 , 100, -5, 20  ) ;
   hS.m_cHadIso_time = new TH2D("m_cHadIso_time", "Charged Hadronic IsoDeposit vs time", 100, 0, 10., 100, -5, 20 );
   hS.m_nHadIso_time = new TH2D("m_nHadIso_time", "Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 100, -5, 20 );
   hS.m_photIso_time = new TH2D("m_photIso_time", "Photon IsoDeposit vs time",           100, 0, 10., 100, -5, 20 );
   hS.dR_GenReco     = new TH1D("dR_GenReco",    "dR(gen,Reco) ", 100, 0, 5 ) ;
   hS.dR_Time        = new TH2D("dR_Time",    "dR(gen,Reco), time", 100, 0, 5, 100, -5, 20  ) ;
   hS.dR_XTime       = new TH2D("dR_XTime",    "dR(gen,Reco), neutralino's lifetime", 100, 0, 5, 100, 0, 5000.  ) ;
   hS.dR_sigIeta     = new TH2D("dR_sigIeta", "dR(gen,Reco), sig_Ieta", 100, 0, 5, 80, 0, 0.08  ) ;
   hS.dR_sMaj        = new TH2D("dR_sMaj",    "dR(gen,Reco), sMajor", 100, 0, 5, 100, 0, 2. ) ;
   hS.dR_sMin        = new TH2D("dR_sMin",    "dR(gen,Reco), sMinor", 100, 0, 5, 100, 0, 0.5  ) ;
   hS.dR_photIso     = new TH2D("dR_photIso", "dR(gen,Reco), PhotonIso", 100, 0, 5, 100, 0, 10 ) ;
   hS.dR_nHadIso     = new TH2D("dR_nHadIso", "dR(gen,Reco), Neutral Hadronic Iso", 100, 0, 5, 100, 0, 10 ) ;
   hS.dR_cHadIso     = new TH2D("dR_cHadIso", "dR(gen,Reco), Charged Hadronic Iso", 100, 0, 5, 100, 0, 10 ) ;
   hS.sMaj_sMin      = new TH2D("sMaj_sMin",    "sMajor sMinor", 100, 0, 2., 60, 0.1, 0.4  ) ;
   hS.XTime_genTime  = new TH2D("XTime_genTime", " neutralino's lifetime vs. measured Photon time ", 100, 0., 5000, 100, -5, 20 ) ;

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

     h.seedTime_Chi2 = (TH2D*) hFile->Get("seedTime_Chi2")  ;
     h.Time_R = (TH2D*) hFile->Get("Time_R")  ;
     h.Time_Z = (TH2D*) hFile->Get("Time_Z")  ;

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
     h.h_nXtals = (TH1D*) hFile->Get("h_nXtals")    ;
     h.h_nBC = (TH1D*) hFile->Get("h_nBC")       ;
     h.h_sMin = (TH1D*) hFile->Get("h_sMin")      ;

     h.h_Eta = (TH1D*) hFile->Get("h_Eta")        ;
     h.h_met = (TH1D*) hFile->Get("h_met")        ;
     h.h_g1Pt = (TH1D*) hFile->Get("h_g1Pt")       ;
     h.h_gen1Pt = (TH1D*) hFile->Get("h_gen1Pt")     ;
     h.h_genMET = (TH1D*) hFile->Get("h_genMET")     ;
     h.h_METRes = (TH1D*) hFile->Get("h_METRes")     ;
     h.h_METdPhi = (TH1D*) hFile->Get("h_METdPhi")     ;
     h.h_gen1RecoPt = (TH1D*) hFile->Get("h_gen1RecoPt") ;

     h.h_nVtx        = (TH1D*) hFile->Get("h_nVtx")       ;
     h.h_nPhotons    = (TH1D*) hFile->Get("h_nPhotons")   ;
     h.h_nGenPhotons = (TH1D*) hFile->Get("h_nGenPhotons");
     h.h_nJets       = (TH1D*) hFile->Get("h_nJets")      ;
     h.h_nMuons      = (TH1D*) hFile->Get("h_nMuons")     ;
     h.h_nElectrons  = (TH1D*) hFile->Get("h_nElectrons") ;

     h.Gh_rho_Time  = (TH2D*) hFile->Get("Gh_rho_Time")  ;
     h.Gh_rho_dT    = (TH2D*) hFile->Get("Gh_rho_dT")  ;
     h.Gh_Phi_Time  = (TH2D*) hFile->Get("Gh_Phi_Time")  ;
     h.Gh_Eta_Time  = (TH2D*) hFile->Get("Gh_Eta_Time")  ;
     h.Gh_Eta_Time1  = (TH2D*) hFile->Get("Gh_Eta_Time1")  ;
     h.h_Pt_Eta    = (TH2D*) hFile->Get("h_Pt_Eta")  ;
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

     h.m_sigIeta_time = (TH2D*) hFile->Get("m_sigIeta_time")  ;
     h.m_sMaj_sMin    = (TH2D*) hFile->Get("m_sMaj_sMin")  ;
     h.m_sMaj_time    = (TH2D*) hFile->Get("m_sMaj_time")  ;
     h.m_sMin_time    = (TH2D*) hFile->Get("m_sMin_time") ;
     h.m_cHadIso_time = (TH2D*) hFile->Get("m_cHadIso_time")  ;
     h.m_nHadIso_time = (TH2D*) hFile->Get("m_nHadIso_time") ;
     h.m_photIso_time = (TH2D*) hFile->Get("m_photIso_time") ;
     h.dR_GenReco     = (TH1D*) hFile->Get("dR_GenReco")     ;
     h.dR_Time        = (TH2D*) hFile->Get("dR_Time")     ;
     h.dR_XTime       = (TH2D*) hFile->Get("dR_XTime")     ;
     h.dR_sigIeta      = (TH2D*) hFile->Get("dR_sigIeta")     ;
     h.dR_sMaj         = (TH2D*) hFile->Get("dR_sMaj")     ;
     h.dR_sMin         = (TH2D*) hFile->Get("dR_sMin")     ;
     h.dR_photIso      = (TH2D*) hFile->Get("dR_photIso")     ;
     h.dR_nHadIso      = (TH2D*) hFile->Get("dR_nHadIso")     ;
     h.dR_cHadIso      = (TH2D*) hFile->Get("dR_cHadIso")     ;
     h.sMaj_sMin       = (TH2D*) hFile->Get("sMaj_sMin")     ;
     h.XTime_genTime   = (TH2D*) hFile->Get("XTime_genTime") ;
 
     cout<<" link all histograms  "<<endl ;
}

void Histogram::Write( string theFolder , TFile* file  ) {

     if ( theFolder.size() > 0 ) file->cd( theFolder.c_str() );

     h.obsTime->Write()     ;
     h.aveObsTime->Write() ;
     h.aveObsTime1->Write() ;
     h.aveObsTime2->Write() ;

     h.seedTime_Chi2->Write()  ;
     h.Time_R->Write()  ;
     h.Time_Z->Write()  ;

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
     h.h_nXtals->Write()    ;
     h.h_nBC->Write()       ;
     h.h_sMin->Write()      ;

     h.h_Eta->Write()        ;
     h.h_met->Write()        ;
     h.h_g1Pt->Write()       ;
     h.h_gen1Pt->Write()     ;
     h.h_genMET->Write()     ;
     h.h_METRes->Write()     ;
     h.h_METdPhi->Write()     ;
     h.h_gen1RecoPt->Write() ;

     h.h_nVtx->Write()       ;
     h.h_nPhotons->Write()   ;
     h.h_nGenPhotons->Write();
     h.h_nJets->Write()      ;
     h.h_nMuons->Write()     ;
     h.h_nElectrons->Write() ;

     h.Gh_rho_Time->Write() ;
     h.Gh_rho_dT->Write() ;
     h.Gh_Phi_Time->Write() ;
     h.Gh_Eta_Time->Write() ;
     h.Gh_Eta_Time1->Write() ;
     h.h_Pt_Eta->Write() ;
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

     h.m_sigIeta_time->Write() ;
     h.m_sMaj_time->Write() ;
     h.m_sMaj_sMin->Write() ;
     h.m_sMin_time->Write() ;
     h.m_nHadIso_time->Write() ;
     h.m_cHadIso_time->Write() ;
     h.m_photIso_time->Write() ;
     h.dR_GenReco->Write() ; 
     h.dR_Time->Write() ; 
     h.dR_XTime->Write() ; 
     h.dR_sigIeta->Write() ; 
     h.dR_sMaj->Write() ; 
     h.dR_sMin->Write() ; 
     h.dR_photIso->Write() ; 
     h.dR_nHadIso->Write() ; 
     h.dR_cHadIso->Write() ; 
     h.sMaj_sMin->Write() ; 
     h.XTime_genTime->Write() ;
    
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

         gStyle->SetOptStat("ermuoi");
	 h_draw->Draw(       h.h_genMET,  "genMET", "MET from Gravitino", "", "logY", 0.95, 1 ) ;
	 h_draw->Draw(       h.h_METRes,  "METRes", "gen MET - reco MET", "", "", 0.95, 1 ) ;
	 h_draw->Draw(       h.h_METdPhi, "METdPhi", "#Delta#phi (gen MET , reco MET)", "", "", 0.95, 1 ) ;
	 // matching stuff
	 h_draw->Draw(       h.h_matchRecoTime, "", "Matched Photon Time (ns)", "", "logY", 0.95, 2 ) ;
	 h_draw->DrawAppend( h.h_matchGenTime,  "",           0.75, 4 ) ;
	 //h_draw->DrawAppend( h.h_genTime,       "",           0.55, 6 ) ;
	 h_draw->DrawAppend( h.h_matchTime,     "MatchTime",  0.35, 1 ) ;

	 h_draw->EffPlot( h.h_matchTime, h.h_matchGenTime, " EcalTime (ns) ", 16, 51, -1, "matchTimeEff" );  
	 h_draw->EffPlot( h.h_matchTime, h.h_genTime,      " EcalTime (ns) ", 16, 51, -1, "recoTimeEff" );  
         gStyle->SetOptStat("");
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
      h_draw->Draw2D( h.dR_Time, "dR_Time", " dR(Gen,Reco)", "EcalTime", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_XTime, "dR_XTime", " dR(Gen,Reco)", " #chi_{0} lifetime", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_sigIeta, "dR_sigIeta", " dR(Gen,Reco)", "#sigma_{i#eta}", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_sMaj, "dR_sMaj",       " dR(Gen,Reco)", "s_{Major}", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_sMin, "dR_sMin",       " dR(Gen,Reco)", "s_{Minor}", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_photIso, "dR_photIso", " dR(Gen,Reco)", "PF photIso", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_nHadIso, "dR_nHadIso", " dR(Gen,Reco)", "PF nHadIso", "logZ", 8 ) ;
      h_draw->Draw2D( h.dR_cHadIso, "dR_cHadIso", " dR(Gen,Reco)", "PF cHadIso", "logZ", 8 ) ;
      h_draw->Draw2D( h.XTime_genTime, "XTime_genTime", "  #chi_{0} life", "EcalTime", "logZ", 8 ) ;
      h_draw->Draw2D( h.sMaj_sMin, "sMaj_sMin",       " s_{Major}", "s_{Minor}", "logZ", 8 ) ;
      h_draw->Draw( h.dR_GenReco, "dR_GenReco", " dR(gen,reco)", "", "logY", 0.95, 1 ) ;
   }

   // some Pt/Et spectrums
   h_draw->Draw( h.h_g1Pt,   "PhotonPt",    " Pt (GeV/c) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_Eta,    "Eta",         " #eta ",       "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_met,    "MET",         " #slash{E_{T}} (GeV) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nChi2,  "TimeChi2",    " #chi^{2} / ndof", "",      "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEB, "maxSwissXEB", " max SwissCross value from EB", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_maxSwissEE, "maxSwissXEE", " max SwissCross value from EE", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_seedSwiss, "seedSwissX", " seed SwissCross value ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nXtals, "nXtals",      " N of xtals ", "",         "logY", 0.95, 1 ) ;
   h_draw->Draw( h.h_nBC,    "nBC",         " N of basic cluster ", "", "", 0.95, 1 ) ;
   h_draw->Draw( h.h_nVtx,   "NVertices",   " N of valid vertices ", "","", 0.95, 1 ) ;
   h_draw->Draw( h.h_sMin,   "sMinor",      " sMinor ", "",              "logY", 0.95, 1 ) ;

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
   h_draw->DrawNxM( 1, h.h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 2, h.h_HcalIsoR, "Hcal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 3, h.h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 4, true );

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
   h_draw->Draw2D( h.h_Pt_Eta,      "h_Pt_Eta",      "P_{T}", "#eta",  ""  ) ;
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

   h_draw->Draw2D( h.m_sigIeta_time,   "m_sigIeta_time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.m_sMaj_sMin,      "m_sMaj_sMin",   "sMaj", "sMin",  "logZ"  ) ;
   h_draw->Draw2D( h.m_sMaj_time,      "m_sMaj_time",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.m_sMin_time,      "m_sMin_time",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.m_cHadIso_time,   "m_cHadIso_time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.m_nHadIso_time,   "m_nHadIso_time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.m_photIso_time,   "m_photIso_time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h.Gh_Eta_Time1,   "Gh_Eta_Time1",    "#phi (cm)", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.Gh_Phi_Time,   "Gh_Phi_Time",    "#phi (cm)", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.Gh_rho_Time,   "Gh_rho_Time",    "#rho (cm)", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.Gh_rho_dT,   "Gh_rho_dT",      "#rho (cm)", " #Delta T (ns)",  "logZ"  ) ;

   TCanvas* c_1 = new TCanvas("c_1","", 800, 700);
   c_1->SetFillColor(10);
   c_1->SetLogz() ;

   h.Gh_Eta_Time->Draw("COLZ") ;
   c_1->Update() ;
   TF1 *f2 = new TF1("f2", Histogram::HaloFunction ,-1.4,1.4, 3 );
   f2->SetParameter(0,  1.4) ;
   f2->SetParameter(1,  1.5) ;
   f2->SetParameter(2,  -1.5) ;
   f2->SetLineColor(1) ;
   f2->Draw("sames") ;
   c_1->Update();

   TF1 *f3 = new TF1("f3", Histogram::HaloFunction ,-1.4,1.4, 3 );
   f3->SetParameter(0, 1.4) ;
   f3->SetParameter(1, 1.3)  ;
   f3->SetParameter(2, -1)  ;
   f3->SetLineColor(1) ;
   f3->Draw("sames") ;
   c_1->Update();

   TString plotname = hfolder + "HaloFunction."+plotType ;
   c_1->Print( plotname ) ;


   hFile->Close() ;
   cout<<" hfile closed ! "<<endl ;
}  

Double_t Histogram::HaloFunction( Double_t* eta, Double_t* par  ) {

     double c  = 30. ; // speed of light : 30 cm/ns
     double eta_func =  par[0]*eta[0] ;
     //double theta = 2.* atan( exp(-1*eta_ ) ) ;
     // rho /z = tan(theta) 
     double t0 =  129 / (-2*c) ;
     Double_t T  = t0 * exp( eta_func )*par[1]  + par[2]  ;

     return T ;
}

