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
   hS.h_TrkIso  = new TH1D("h_TrkIso", " Track Isolation ", 100, 0, 10. );
   hS.h_HcalIso = new TH1D("h_HcalIso", " HCAL Isolation ", 100, 0, 10. );
   hS.h_EcalIso = new TH1D("h_EcalIso", " ECAL Isolation ", 100, 0, 10. );
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
   hS.h_seedSwiss = new TH1D("h_seedSwiss", " seed SwissCross value ", 150,  0., 1.5 );
   hS.h_fSpike   = new TH1D("h_fSpike", "fraction of spike crystals in seed cluster ", 220,  -1.1, 1.1 );
   hS.h_nXtals   = new TH1D("h_nXtals", "N of crystals of the photon ", 50,  0, 50 );
   hS.h_nBC      = new TH1D("h_nBC",    "N of basic cluster of the photon ", 12,  0, 12 );
   hS.h_sMin     = new TH1D("h_sMin",    " sMinor distribution ", 105,  -0.05, 1 );

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
   hS.h_sMaj_Eta  = new TH2D( "h_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
   hS.h_sMaj_Phi  = new TH2D( "h_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
   hS.h_sMaj_sMin = new TH2D( "h_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
   hS.h_nXtl_Eta  = new TH2D( "h_nXtl_Eta", "N crystals vs #eta ", 50, 0, 50 ,  51, -2.5, 2.5) ;
   hS.h_nXtl_Pt   = new TH2D( "h_nXtl_Pt", "N crystals vs #eta ", 50, 0, 50 ,  50,  0. , 500. ) ;
   hS.h_cscdPhi_Time  = new TH2D( "h_cscdPhi_Time", " d#Phi vs Ecal time", 64, 0, 3.2, 160, -20, 20 ) ;
   hS.h_sigIeta_Time  = new TH2D( "h_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
   hS.h_sigIeta_Time1 = new TH2D( "h_sigIeta_Time1", " sigma_iEta vs Ecal time after cuts", 80, 0, 0.08, 120, -15, 15 ) ;
   hS.h_sigEta_sMaj   = new TH2D( "h_sigEta_sMaj", " sigma_iEta vs sMaj ", 80, 0, 0.08, 100, 0, 2 ) ;
   hS.h_sigEta_sMaj_late = new TH2D( "h_sigEta_sMaj_late", " sigma_iEta vs sMaj for late photon", 80, 0, 0.08, 100, 0, 2 ) ;
   hS.h_HoverE_Time   = new TH2D( "h_HoverE_Time",  " H/E vs Ecal time", 100, 0, 1, 120, -15, 15 ) ;

   hS.h_RhoPhi_Halo = new TH2D( "h_RhoPhi_Halo", " phi vs rho for halo tracks", 63, -3.15, 3.15, 50, 0, 500 ) ;
   hS.h_nHaloHits   = new TH1D( "h_nHaloHits",   " N of out of time CSC rechits", 50, 0, 50 ) ;
   hS.h_nHaloTracks = new TH1D( "h_nHaloTracks",   " N of CSC Halo Tracks", 10, 0, 10 ) ;

   hS.halo_sigEta    = new TH1D( "halo_sigEta", " Sigma Eta Eta for Halo Photon ", 100,  0., 0.1 ) ;
   hS.halo_sigIeta   = new TH1D( "halo_sigIeta", " Sigma Ieta Ieta for Halo Photon ", 100,  0., 0.1 ) ;
   hS.halo_Time      = new TH1D( "halo_Time",   "Photon time w/ halo ", 160,  -14.5, 25.5 ) ;
   hS.halo_Eta_Time  = new TH2D( "halo_Eta_Time", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.halo_Phi_Time  = new TH2D( "halo_Phi_Time", " phi vs photon time for halo photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.halo_sMaj_sMin = new TH2D( "halo_sMaj_sMin", "sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
   hS.halo_sMaj_Time = new TH2D( "halo_sMaj_Time",  "sMaj vs Ecal time for halo Photon", 100, 0, 2, 160, -20, 20 ) ;
   hS.halo_sMin_Time = new TH2D( "halo_sMin_Time",  "sMin vs Ecal time for halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;

   hS.noHalo_sigEta  = new TH1D( "noHalo_sigEta", " Sigma Eta Eta for non halo photon", 100,  0., 0.1 ) ;
   hS.noHalo_sigIeta = new TH1D( "noHalo_sigIeta", " Sigma Ieta Ieta for non halo photon", 100,  0., 0.1 ) ;
   hS.noHalo_Time    = new TH1D( "noHalo_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;
   hS.noHalo_Phi_Time = new TH2D( "noHalo_Phi_Time", "#phi vs Non Halo Photon time ", 63, -3.15, 3.15, 160,  -20, 20 ) ;
   hS.noHalo_Eta_Time = new TH2D( "noHalo_Eta_Time", "#eta vs Non Halo Photon time ", 51, -2.5, 2.5, 160,  -20, 20 ) ;
   hS.noHalo_sMaj_sMin = new TH2D( "noHalo_sMaj_sMin", "sMaj vs sMin for non halo photon",100, 0, 2, 50, 0.1, 0.4   ) ;
   hS.noHalo_sMaj_Time = new TH2D( "noHalo_sMaj_Time",  "sMaj vs Ecal time for non halo Photon", 100, 0, 2, 160, -20, 20 ) ;
   hS.noHalo_sMin_Time = new TH2D( "noHalo_sMin_Time",  "sMin vs. Ecal time for non halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;

   hS.noHalo_nXtl_side = new TH1D( "noHalo_nXtl_side", "N of xtals of non halo photon w/ |t| > 3ns",     50,  0, 50 );
   hS.noHalo_nXtl_center = new TH1D( "noHalo_nXtl_center", "N of xtals of non halo photon w/ |t| < 3ns", 50,  0, 50 );

   hS.spike_sigEta    = new TH1D( "spike_sigEta", " Sigma Eta Eta for spike photon ", 100,  0., 0.1 ) ;
   hS.spike_sigIeta   = new TH1D( "spike_sigIeta", " Sigma Ieta Ieta for spike photon ", 100,  0., 0.1 ) ;
   hS.spike_Time      = new TH1D( "spike_Time",   "Photon time w/ spike ", 160,  -14.5, 25.5 ) ;
   hS.spike_Eta_Time  = new TH2D( "spike_Eta_Time", " eta vs photon time for spike photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.spike_Phi_Time  = new TH2D( "spike_Phi_Time", " phi vs photon time for spike photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.spike_sMaj_sMin = new TH2D( "spike_sMaj_sMin", " sMajor vs sMinor for spike photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
   hS.spike_sMaj_Time = new TH2D( "spike_sMaj_Time",  "sMaj vs Ecal time for spike Photon", 100, 0, 2, 160, -20, 20 ) ;
   hS.spike_sMin_Time = new TH2D( "spike_sMin_Time",  "sMin vs. Ecal time for spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;

   hS.noSpike_sigEta  = new TH1D( "noSpike_sigEta", " Sigma Eta Eta for non spike photon", 100,  0., 0.1 ) ;
   hS.noSpike_sigIeta = new TH1D( "noSpike_sigIeta", " Sigma Ieta Ieta for non spike photon", 100,  0., 0.1 ) ;
   hS.noSpike_Time    = new TH1D( "noSpike_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;
   hS.noSpike_Phi_Time = new TH2D( "noSpike_Phi_Time", "#phi vs Non Spike Photon time ", 63, -3.15, 3.15, 160,  -20, 20 ) ;
   hS.noSpike_Eta_Time = new TH2D( "noSpike_Eta_Time", "#eta vs Non Spike Photon time ", 51, -2.5, 2.5, 160,  -20, 20 ) ;
   hS.noSpike_sMaj_sMin = new TH2D( "noSpike_sMaj_sMin", "sMaj vs sMin for non spike photon",100, 0, 2, 50, 0.1, 0.4   ) ;
   hS.noSpike_sMaj_Time = new TH2D( "noSpike_sMaj_Time",  "sMaj vs Ecal time for non spike Photon", 100, 0, 2, 160, -20, 20 ) ;
   hS.noSpike_sMin_Time = new TH2D( "noSpike_sMin_Time",  "sMin vs. Ecal time for non spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;

   hS.sideband_cscdPhi_EB = new TH1D( "sideband_cscdPhi_EB", "EB #Delta#Phi(cscSeg, #gamma) for |t| > 3", 64,  0., 3.2 ) ;
   hS.sideband_sMaj_EB    = new TH1D( "sideband_sMaj_EB",    "EB sMajor ", 100, 0., 2. ) ;
   hS.sideband_cscdPhi_EE = new TH1D( "sideband_cscdPhi_EE", "EE #Delta#Phi(cscSeg, #gamma) for |t| > 3", 64,  0., 3.2 ) ;
   hS.sideband_sMaj_EE    = new TH1D( "sideband_sMaj_EE",    "EE sMajor ", 100, 0., 2. ) ;
   hS.sideband_sMaj_Time  = new TH2D( "sideband_sMaj_Time", " sMaj vs photon time", 100, 0, 2, 160, -20, 20 ) ;
   hS.sideband_sMaj_Phi   = new TH2D( "sideband_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
   hS.sideband_sMaj_sMin  = new TH2D( "sideband_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
   hS.sideband_sMaj_Eta   = new TH2D( "sideband_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
   hS.sideband_nXtl_Eta   = new TH2D( "sideband_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
   hS.sideband_nXtl       = new TH1D( "sideband_nXtl", " N crystals ", 50, 0, 50 ) ;

   hS.gjCS_sMaj_Eta   = new TH2D( "gjCS_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
   hS.gjCS_nXtl_Eta   = new TH2D( "gjCS_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;

   hS.haloCS_cscdPhi   = new TH1D( "haloCS_cscdPhi", " #Delta#Phi(cscSeg, #gamma) ", 64,  0., 3.2 ) ;
   hS.haloCS_sMaj_Eta  = new TH2D( "haloCS_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
   hS.haloCS_sMaj_Phi  = new TH2D( "haloCS_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
   hS.haloCS_Eta_Time  = new TH2D( "haloCS_Eta_Time", " eta vs photon time  ", 51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.haloCS_Eta_Time1 = new TH2D( "haloCS_Eta_Time1", " eta vs photon time ", 51, -2.5, 2.5,   160, -20, 20 ) ;

   hS.spikeCS_Eta_Time  = new TH2D( "spikeCS_Eta_Time", " #eta vs time for spikes CS",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.spikeCS_Eta_Time1 = new TH2D( "spikeCS_Eta_Time1", " #eta vs time after spikes tagging",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.spikeCS_nXtl_Eta  = new TH2D( "spikeCS_nXtl_Eta", " N of Xtals for spikes CS vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
   hS.spikeCS_Phi_Time  = new TH2D( "spikeCS_Phi_Time", " #phi vs time for spikes CS",  63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.spikeCS_sMaj_sMin = new TH2D( "spikeCS_sMaj_sMin", "sMaj vs sMin for spikes CS", 100,  0, 2, 50, 0.1, 0.4   ) ;
   hS.spikeCS_nXtl      = new TH1D( "spikeCS_nXtl",      "N of xtals of spikes ", 50,  0, 50 );

   hS.notSpike_nXtl   = new TH1D("notSpike_nXtl", "N of crystals for non-spike photon ", 50,  0, 50 );

   hS.ghostCS_Eta_Time  = new TH2D( "ghostCS_Eta_Time", " #eta vs time for ghosts CS",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.ghostCS_Eta_Time1 = new TH2D( "ghostCS_Eta_Time1", " #eta vs time after ghosts tagging",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.ghostCS_Phi_Time  = new TH2D( "ghostCS_Phi_Time", " #phi vs time for ghosts CS",  63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.ghostCS_sMaj_sMin = new TH2D( "ghostCS_sMaj_sMin", "sMaj vs sMin for ghosts CS", 100,  0, 2, 50, 0.1, 0.4   ) ;
   hS.ghostCS_sMaj_Eta  = new TH2D( "ghostCS_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;

   hS.ghost_Time      = new TH1D( "ghost_Time", " time for ghost", 160, -20, 20 ) ;
   hS.ghost_Eta_Time  = new TH2D( "ghost_Eta_Time", " #eta vs time for ghost",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.ghost_Phi_Time  = new TH2D( "ghost_Phi_Time", " #phi vs time for ghost ",  63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.ghost_sMaj_sMin = new TH2D( "ghost_sMaj_sMin", "sMaj vs sMin for ghost ", 100,  0, 2, 50, 0.1, 0.4   ) ;
   hS.pure_Time      = new TH1D( "pure_Time", "  time for pure photon", 160, -20, 20 ) ;
   hS.pure_Eta_Time  = new TH2D( "pure_Eta_Time", " #eta vs time for pure photon",  51, -2.5, 2.5,   160, -20, 20 ) ;
   hS.pure_Phi_Time  = new TH2D( "pure_Phi_Time", " #phi vs time for pure photon",  63, -3.15, 3.15, 160, -20, 20 ) ;
   hS.pure_sMaj_sMin = new TH2D( "pure_sMaj_sMin", "sMaj vs sMin for pure photon", 100,  0, 2, 50, 0.1, 0.4   ) ;

   hS.sMaj_eta[0] = new TH1D( "sMaj_eta1",  "sMajor for 0.0  < |eta| < 0.28 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta[1] = new TH1D( "sMaj_eta2",  "sMajor for 0.28 < |eta| < 0.56 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta[2] = new TH1D( "sMaj_eta3",  "sMajor for 0.56 < |eta| < 0.84 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta[3] = new TH1D( "sMaj_eta4",  "sMajor for 0.84 < |eta| < 1.12 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta[4] = new TH1D( "sMaj_eta5",  "sMajor for 1.12 < |eta| < 1.40 ", 100, 0., 2.5 ) ;

   hS.sMaj_eta[5] = new TH1D( "sMaj_eta6",  "sMajor for 1.5 < |eta| < 2.0 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta[6] = new TH1D( "sMaj_eta7",  "sMajor for 2.0 < |eta| < 2.5 ", 100, 0., 2.5 ) ;

   hS.sMaj_eta_csc[0] = new TH1D( "sMaj_eta_csc1",  "sMajor for 0.0  < |eta| < 0.28 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta_csc[1] = new TH1D( "sMaj_eta_csc2",  "sMajor for 0.28 < |eta| < 0.56 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta_csc[2] = new TH1D( "sMaj_eta_csc3",  "sMajor for 0.56 < |eta| < 0.84 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta_csc[3] = new TH1D( "sMaj_eta_csc4",  "sMajor for 0.84 < |eta| < 1.12 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta_csc[4] = new TH1D( "sMaj_eta_csc5",  "sMajor for 1.12 < |eta| < 1.40 ", 100, 0., 2.5 ) ;

   hS.sMaj_eta_csc[5] = new TH1D( "sMaj_eta_csc6",  "sMajor for 1.5 < |eta| < 2.0 ", 100, 0., 2.5 ) ;
   hS.sMaj_eta_csc[6] = new TH1D( "sMaj_eta_csc7",  "sMajor for 2.0 < |eta| < 2.5 ", 100, 0., 2.5 ) ;

   hS.nHL_Eta = new TH1D( "nHL_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
   hS.nSpk_Eta = new TH1D( "nSpk_Eta",  " N of Spike in |#eta|", 5, 0., 1.4 ) ;

   hS.nCS_Eta = new TH1D( "nCS_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
   hS.nGhS_Eta = new TH1D( "nGhS_Eta",  " N of Ghost in |#eta|", 5, 0., 1.4 ) ;

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
     h.h_TrkIso = (TH1D*) hFile->Get("h_TrkIso")   ;
     h.h_HcalIso = (TH1D*) hFile->Get("h_HcalIso")  ;
     h.h_EcalIso = (TH1D*) hFile->Get("h_EcalIso")  ;
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

     h.h_Eta_Time  = (TH2D*) hFile->Get("h_Eta_Time")  ;
     h.h_nXtl_Eta  = (TH2D*) hFile->Get("h_nXtl_Eta")  ;
     h.h_nXtl_Pt   = (TH2D*) hFile->Get("h_nXtl_Pt")  ;
     h.h_Phi_Time  = (TH2D*) hFile->Get("h_Phi_Time")  ;
     h.h_sMaj_Time = (TH2D*) hFile->Get("h_sMaj_Time")  ;
     h.h_sMin_Time = (TH2D*) hFile->Get("h_sMin_Time") ;
     h.h_sMaj_Eta  = (TH2D*) hFile->Get("h_sMaj_Eta") ;
     h.h_sMaj_Phi  = (TH2D*) hFile->Get("h_sMaj_Phi") ;
     h.h_sMaj_sMin = (TH2D*) hFile->Get("h_sMaj_sMin")  ;
     h.h_cscdPhi_Time  = (TH2D*) hFile->Get("h_cscdPhi_Time")  ;
     h.h_sigIeta_Time  = (TH2D*) hFile->Get("h_sigIeta_Time")  ;
     h.h_sigIeta_Time1 = (TH2D*) hFile->Get("h_sigIeta_Time1")  ;
     h.h_sigEta_sMaj   = (TH2D*) hFile->Get("h_sigEta_sMaj")  ;
     h.h_sigEta_sMaj_late  = (TH2D*) hFile->Get("h_sigEta_sMaj_late")  ;
     h.h_HoverE_Time   = (TH2D*) hFile->Get("h_HoverE_Time")  ;

     h.h_RhoPhi_Halo = (TH2D*) hFile->Get("h_RhoPhi_Halo")  ;
     h.h_nHaloHits   = (TH1D*) hFile->Get("h_nHaloHits")  ;
     h.h_nHaloTracks = (TH1D*) hFile->Get("h_nHaloTracks")  ;

     h.spike_Time      = (TH1D*) hFile->Get("spike_Time")  ;
     h.spike_sigEta    = (TH1D*) hFile->Get("spike_sigEta") ;
     h.spike_sigIeta   = (TH1D*) hFile->Get("spike_sigIeta") ;
     h.spike_Eta_Time  = (TH2D*) hFile->Get("spike_Eta_Time") ;
     h.spike_Phi_Time  = (TH2D*) hFile->Get("spike_Phi_Time")  ;
     h.spike_sMaj_sMin = (TH2D*) hFile->Get("spike_sMaj_sMin") ;
     h.spike_sMaj_Time = (TH2D*) hFile->Get("spike_sMaj_Time")  ;
     h.spike_sMin_Time = (TH2D*) hFile->Get("spike_sMin_Time")  ;

     h.noSpike_Time      = (TH1D*) hFile->Get("noSpike_Time")  ;
     h.noSpike_sigEta    = (TH1D*) hFile->Get("noSpike_sigEta") ;
     h.noSpike_sigIeta   = (TH1D*) hFile->Get("noSpike_sigIeta") ;
     h.noSpike_Eta_Time  = (TH2D*) hFile->Get("noSpike_Eta_Time")  ;
     h.noSpike_Phi_Time  = (TH2D*) hFile->Get("noSpike_Phi_Time")  ;
     h.noSpike_sMaj_sMin = (TH2D*) hFile->Get("noSpike_sMaj_sMin")  ;
     h.noSpike_sMaj_Time = (TH2D*) hFile->Get("noSpike_sMaj_Time")  ;
     h.noSpike_sMin_Time = (TH2D*) hFile->Get("noSpike_sMin_Time")  ;

     h.halo_Time      = (TH1D*) hFile->Get("halo_Time")  ;
     h.halo_sigEta    = (TH1D*) hFile->Get("halo_sigEta") ;
     h.halo_sigIeta   = (TH1D*) hFile->Get("halo_sigIeta") ;
     h.halo_Eta_Time  = (TH2D*) hFile->Get("halo_Eta_Time") ;
     h.halo_Phi_Time  = (TH2D*) hFile->Get("halo_Phi_Time")  ;
     h.halo_sMaj_sMin = (TH2D*) hFile->Get("halo_sMaj_sMin") ;
     h.halo_sMaj_Time = (TH2D*) hFile->Get("halo_sMaj_Time")  ;
     h.halo_sMin_Time = (TH2D*) hFile->Get("halo_sMin_Time")  ;

     h.noHalo_Time      = (TH1D*) hFile->Get("noHalo_Time")  ;
     h.noHalo_sigEta    = (TH1D*) hFile->Get("noHalo_sigEta") ;
     h.noHalo_sigIeta   = (TH1D*) hFile->Get("noHalo_sigIeta") ;
     h.noHalo_Eta_Time  = (TH2D*) hFile->Get("noHalo_Eta_Time")  ;
     h.noHalo_Phi_Time  = (TH2D*) hFile->Get("noHalo_Phi_Time")  ;
     h.noHalo_sMaj_sMin = (TH2D*) hFile->Get("noHalo_sMaj_sMin")  ;
     h.noHalo_sMaj_Time = (TH2D*) hFile->Get("noHalo_sMaj_Time")  ;
     h.noHalo_sMin_Time = (TH2D*) hFile->Get("noHalo_sMin_Time")  ;

     h.noHalo_nXtl_side = (TH1D*) hFile->Get("noHalo_nXtl_side")  ;
     h.noHalo_nXtl_center = (TH1D*) hFile->Get("noHalo_nXtl_center")  ;

     h.spikeCS_Eta_Time  = (TH2D*) hFile->Get("spikeCS_Eta_Time") ;
     h.spikeCS_Eta_Time1 = (TH2D*) hFile->Get("spikeCS_Eta_Time1") ;
     h.spikeCS_nXtl_Eta  = (TH2D*) hFile->Get("spikeCS_nXtl_Eta") ;
     h.spikeCS_Phi_Time  = (TH2D*) hFile->Get("spikeCS_Phi_Time")  ;
     h.spikeCS_sMaj_sMin = (TH2D*) hFile->Get("spikeCS_sMaj_sMin")  ;
     h.spikeCS_nXtl      = (TH1D*) hFile->Get("spikeCS_nXtl")  ;

     h.ghost_Time      = (TH1D*) hFile->Get("ghost_Time") ;
     h.ghost_Eta_Time  = (TH2D*) hFile->Get("ghost_Eta_Time") ;
     h.ghost_Phi_Time  = (TH2D*) hFile->Get("ghost_Phi_Time")  ;
     h.ghost_sMaj_sMin = (TH2D*) hFile->Get("ghost_sMaj_sMin")  ;
     h.pure_Time      = (TH1D*) hFile->Get("pure_Time") ;
     h.pure_Eta_Time  = (TH2D*) hFile->Get("pure_Eta_Time") ;
     h.pure_Phi_Time  = (TH2D*) hFile->Get("pure_Phi_Time")  ;
     h.pure_sMaj_sMin = (TH2D*) hFile->Get("pure_sMaj_sMin")  ;

     h.notSpike_nXtl = (TH1D*) hFile->Get("notSpike_nXtl")    ;
     h.sMaj_eta[0]  = (TH1D*) hFile->Get("sMaj_eta1") ;
     h.sMaj_eta[1]  = (TH1D*) hFile->Get("sMaj_eta2") ;
     h.sMaj_eta[2]  = (TH1D*) hFile->Get("sMaj_eta3") ;
     h.sMaj_eta[3]  = (TH1D*) hFile->Get("sMaj_eta4") ;
     h.sMaj_eta[4]  = (TH1D*) hFile->Get("sMaj_eta5") ;
     h.sMaj_eta[5]  = (TH1D*) hFile->Get("sMaj_eta6") ;
     h.sMaj_eta[6]  = (TH1D*) hFile->Get("sMaj_eta7") ;

     h.sMaj_eta_csc[0]  = (TH1D*) hFile->Get("sMaj_eta_csc1") ;
     h.sMaj_eta_csc[1]  = (TH1D*) hFile->Get("sMaj_eta_csc2") ;
     h.sMaj_eta_csc[2]  = (TH1D*) hFile->Get("sMaj_eta_csc3") ;
     h.sMaj_eta_csc[3]  = (TH1D*) hFile->Get("sMaj_eta_csc4") ;
     h.sMaj_eta_csc[4]  = (TH1D*) hFile->Get("sMaj_eta_csc5") ;
     h.sMaj_eta_csc[5]  = (TH1D*) hFile->Get("sMaj_eta_csc6") ;
     h.sMaj_eta_csc[6]  = (TH1D*) hFile->Get("sMaj_eta_csc7") ;

     h.sideband_cscdPhi_EB = (TH1D*) hFile->Get("sideband_cscdPhi_EB") ; 
     h.sideband_sMaj_EB    = (TH1D*) hFile->Get("sideband_sMaj_EB") ;
     h.sideband_cscdPhi_EE = (TH1D*) hFile->Get("sideband_cscdPhi_EE") ; 
     h.sideband_sMaj_EE    = (TH1D*) hFile->Get("sideband_sMaj_EE") ;
     h.sideband_sMaj_Time  = (TH2D*) hFile->Get("sideband_sMaj_Time")  ;
     h.sideband_sMaj_Phi   = (TH2D*) hFile->Get("sideband_sMaj_Phi")  ;
     h.sideband_sMaj_sMin  = (TH2D*) hFile->Get("sideband_sMaj_sMin")  ;
     h.sideband_sMaj_Eta   = (TH2D*) hFile->Get("sideband_sMaj_Eta")  ;
     h.sideband_nXtl_Eta   = (TH2D*) hFile->Get("sideband_nXtl_Eta")  ;
     h.sideband_nXtl       = (TH1D*) hFile->Get("sideband_nXtl")  ;

     h.gjCS_sMaj_Eta   = (TH2D*) hFile->Get("gjCS_sMaj_Eta")  ;
     h.gjCS_nXtl_Eta   = (TH2D*) hFile->Get("gjCS_nXtl_Eta")  ;

     h.haloCS_cscdPhi   = (TH1D*) hFile->Get("haloCS_cscdPhi") ; 
     h.haloCS_sMaj_Eta  = (TH2D*) hFile->Get("haloCS_sMaj_Eta")  ;
     h.haloCS_sMaj_Phi  = (TH2D*) hFile->Get("haloCS_sMaj_Phi")  ;
     h.haloCS_Eta_Time  = (TH2D*) hFile->Get("haloCS_Eta_Time") ;
     h.haloCS_Eta_Time1 = (TH2D*) hFile->Get("haloCS_Eta_Time1") ;

     h.ghostCS_sMaj_Eta  = (TH2D*) hFile->Get("ghostCS_sMaj_Eta")  ;
     h.ghostCS_sMaj_sMin = (TH2D*) hFile->Get("ghostCS_sMaj_sMin")  ;
     h.ghostCS_Phi_Time  = (TH2D*) hFile->Get("ghostCS_Phi_Time") ;
     h.ghostCS_Eta_Time  = (TH2D*) hFile->Get("ghostCS_Eta_Time") ;
     h.ghostCS_Eta_Time1 = (TH2D*) hFile->Get("ghostCS_Eta_Time1") ;

     h.nHL_Eta  = (TH1D*) hFile->Get("nHL_Eta") ;
     h.nSpk_Eta = (TH1D*) hFile->Get("nSpk_Eta") ;

     h.nCS_Eta  = (TH1D*) hFile->Get("nCS_Eta") ;
     h.nGhS_Eta = (TH1D*) hFile->Get("nGhS_Eta") ;

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
     h.h_TrkIso->Write()   ;
     h.h_HcalIso->Write()  ;
     h.h_EcalIso->Write()  ;
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
     h.h_nXtl_Eta->Write() ;
     h.h_nXtl_Pt->Write() ;
     h.h_Phi_Time->Write() ;
     h.h_sMaj_Time->Write() ;
     h.h_sMin_Time->Write() ;
     h.h_sMaj_Eta->Write() ;
     h.h_sMaj_Phi->Write() ;
     h.h_sMaj_sMin->Write() ;
     h.h_cscdPhi_Time->Write() ;
     h.h_sigIeta_Time->Write() ;
     h.h_sigIeta_Time1->Write() ;
     h.h_sigEta_sMaj->Write() ;
     h.h_sigEta_sMaj_late->Write() ;
     h.h_HoverE_Time->Write() ;

     h.haloCS_cscdPhi->Write();
     h.haloCS_sMaj_Eta->Write() ;
     h.haloCS_sMaj_Phi->Write() ;
     h.haloCS_Eta_Time->Write() ;
     h.haloCS_Eta_Time1->Write() ;

     h.notSpike_nXtl->Write()    ;
     h.sMaj_eta[0]->Write() ;
     h.sMaj_eta[1]->Write() ;
     h.sMaj_eta[2]->Write() ;
     h.sMaj_eta[3]->Write() ;
     h.sMaj_eta[4]->Write() ;
     h.sMaj_eta[5]->Write() ;
     h.sMaj_eta[6]->Write() ;

     h.sMaj_eta_csc[0]->Write() ;
     h.sMaj_eta_csc[1]->Write() ;
     h.sMaj_eta_csc[2]->Write() ;
     h.sMaj_eta_csc[3]->Write() ;
     h.sMaj_eta_csc[4]->Write() ;
     h.sMaj_eta_csc[5]->Write() ;
     h.sMaj_eta_csc[6]->Write() ;

     h.h_RhoPhi_Halo->Write() ;
     h.h_nHaloHits->Write() ;
     h.h_nHaloTracks->Write() ;

     h.spike_Time->Write() ;
     h.spike_sigEta->Write() ;
     h.spike_sigIeta->Write() ;
     h.spike_Eta_Time->Write() ;
     h.spike_Phi_Time->Write() ;
     h.spike_sMaj_Time->Write() ;
     h.spike_sMin_Time->Write() ;
     h.spike_sMaj_sMin->Write();

     h.noSpike_Time->Write() ;
     h.noSpike_sigEta->Write() ;
     h.noSpike_sigIeta->Write() ;
     h.noSpike_Phi_Time->Write() ;
     h.noSpike_Eta_Time->Write() ;
     h.noSpike_sMaj_sMin->Write() ;
     h.noSpike_sMaj_Time->Write() ;
     h.noSpike_sMin_Time->Write() ;

     h.halo_Time->Write() ;
     h.halo_sigEta->Write() ;
     h.halo_sigIeta->Write() ;
     h.halo_Eta_Time->Write() ;
     h.halo_Phi_Time->Write() ;
     h.halo_sMaj_Time->Write() ;
     h.halo_sMin_Time->Write() ;
     h.halo_sMaj_sMin->Write();

     h.noHalo_Time->Write() ;
     h.noHalo_sigEta->Write() ;
     h.noHalo_sigIeta->Write() ;
     h.noHalo_Phi_Time->Write() ;
     h.noHalo_Eta_Time->Write() ;
     h.noHalo_sMaj_sMin->Write() ;
     h.noHalo_sMaj_Time->Write() ;
     h.noHalo_sMin_Time->Write() ;

     h.noHalo_nXtl_side->Write() ;
     h.noHalo_nXtl_center->Write() ;

     h.spikeCS_Eta_Time->Write() ;
     h.spikeCS_Eta_Time1->Write() ;
     h.spikeCS_nXtl_Eta->Write() ;
     h.spikeCS_Phi_Time->Write() ;
     h.spikeCS_sMaj_sMin->Write() ;
     h.spikeCS_nXtl->Write() ;

     h.ghostCS_Eta_Time->Write() ;
     h.ghostCS_Eta_Time1->Write() ;
     h.ghostCS_Phi_Time->Write() ;
     h.ghostCS_sMaj_sMin->Write() ;
     h.ghostCS_sMaj_Eta->Write() ;

     h.ghost_Time->Write() ;
     h.ghost_Eta_Time->Write() ;
     h.ghost_Phi_Time->Write() ;
     h.ghost_sMaj_sMin->Write() ;
     h.pure_Time->Write() ;
     h.pure_Eta_Time->Write() ;
     h.pure_Phi_Time->Write() ;
     h.pure_sMaj_sMin->Write() ;

     h.sideband_cscdPhi_EB->Write() ;
     h.sideband_sMaj_EB->Write() ;
     h.sideband_cscdPhi_EE->Write() ;
     h.sideband_sMaj_EE->Write() ;
     h.sideband_sMaj_Time->Write() ;
     h.sideband_sMaj_Phi->Write() ;
     h.sideband_sMaj_sMin->Write() ;
     h.sideband_sMaj_Eta->Write() ;
     h.sideband_nXtl_Eta->Write() ;
     h.sideband_nXtl->Write() ;

     h.gjCS_sMaj_Eta->Write() ;
     h.gjCS_nXtl_Eta->Write() ;

     h.nHL_Eta->Write() ;
     h.nSpk_Eta->Write() ;

     h.nCS_Eta->Write() ;
     h.nGhS_Eta->Write() ;
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

   // Isolation
   h_draw->CreateNxM( "Isolations", 2,3 );
   h_draw->DrawNxM( 1, h.h_TrkIso,   "Track Isolation ",       "", "logY", 1, false );
   h_draw->DrawNxM( 2, h.h_TrkIsoR,  "Track Isolation Ratio",  "", "logY", 1, false );
   h_draw->DrawNxM( 3, h.h_EcalIso,  "Ecal Isolation ",        "", "logY", 2, false );
   h_draw->DrawNxM( 4, h.h_EcalIsoR, "Ecal Isolation Ratio",   "", "logY", 2, false );
   h_draw->DrawNxM( 5, h.h_HcalIso,  "Hcal Isolation ",        "", "logY", 4, false );
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
   h_draw->Draw2D( h.h_sMaj_Time,   "h_sMaj_Time",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.h_sMin_Time,   "h_sMin_Time",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h.h_nXtl_Eta,    "h_nXtl_Eta",    "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw2D( h.h_nXtl_Pt,     "h_nXtl_Pt",     "N crystals", "P_{T}", "logZ", 8  ) ;
   h_draw->Draw2D( h.h_sMaj_Eta,    "h_sMaj_Eta",    "sMaj", "#eta ",  "logZ", 8 ) ;
   h_draw->Draw2D( h.h_sMaj_Phi,    "h_sMaj_Phi",    "sMaj", "#phi ",  "logZ", 8 ) ;
   h_draw->Draw2D( h.h_sMaj_sMin,   "h_sMaj_sMin",   "sMaj", "sMin ",  "logZ", 8 ) ;
   h_draw->Draw2D( h.h_cscdPhi_Time,"h_cscdPhi_Time","d#phi", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_sigIeta_Time,"h_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_sigIeta_Time1,"h_sigIeta_Time1","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_sigEta_sMaj, "h_sigEta_sMaj", "#sigma_{#eta #eta}", "s_{Maj}", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_sigEta_sMaj_late, "h_sigEta_sMaj_late", "#sigma_{#eta #eta}", "s_{Maj}", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_HoverE_Time, "h_HoverE_Time", "H/E", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_cHadIso_t,   "h_cHadIso_t",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_nHadIso_t,   "h_nHadIso_t",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h.h_photIso_t,   "h_photIso_t",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h.h_RhoPhi_Halo,   "h_RhoPhi_Halo", "#phi", " #rho",  ""  ) ;
   h_draw->Draw(   h.h_nHaloHits,     "h_nHaloHits",    " N of Halo csc rechits ", "",  "logY", 0.95, 1 ) ;
   h_draw->Draw(   h.h_nHaloTracks,   "h_nHaloTracks",  " N of Halo csc tracks  ", "",  "logY", 0.95, 1 ) ;

   h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.pure_Time, "", 0.95, 2, 1  ) ;
   h_draw->DrawAppend( h.ghost_Time, "h_TimeTag", 0.7, 4, 1  ) ;
   //h_draw->DrawAppend( h.noHalo_Time, "", 0.95, 2, 1  ) ;

   h_draw->Draw(       h.obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.halo_Time,  "", 0.7, 2, 1  ) ;
   h_draw->DrawAppend( h.spike_Time, "ghost_Time", 0.5, 4, 1  ) ;

   h_draw->Draw( h.halo_sigEta,  "halo_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.halo_sigIeta, "halo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h.halo_sMaj_Time, "halo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.halo_sMin_Time, "halo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.halo_sMaj_sMin, "halo_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( h.halo_Eta_Time, "halo_Eta_Time", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.halo_Phi_Time, "halo_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;

   h_draw->Draw( h.noHalo_sigEta,  "noHalo_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.noHalo_sigIeta, "noHalo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h.noHalo_Phi_Time, "noHalo_Phi_Time",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.noHalo_Eta_Time, "noHalo_Eta_Time",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.noHalo_sMaj_sMin, "noHalo_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;
   h_draw->Draw2D( h.noHalo_sMaj_Time, "noHalo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.noHalo_sMin_Time, "noHalo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;

   h_draw->Draw( h.spike_sigEta,  "spike_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.spike_sigIeta, "spike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h.spike_sMaj_Time, "spike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.spike_sMin_Time, "spike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.spike_sMaj_sMin, "spike_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( h.spike_Eta_Time, "spike_Eta_Time", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.spike_Phi_Time, "spike_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;

   h_draw->Draw( h.noSpike_sigEta,  "noSpike_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.noSpike_sigIeta, "noSpike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h.noSpike_Phi_Time, "noSpike_Phi_Time",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.noSpike_Eta_Time, "noSpike_Eta_Time",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.noSpike_sMaj_sMin, "noSpike_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;
   h_draw->Draw2D( h.noSpike_sMaj_Time, "noSpike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( h.noSpike_sMin_Time, "noSpike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;

   h_draw->Draw(   h.noHalo_nXtl_side, "noHalo_nXtl_side",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   h.noHalo_nXtl_center, "noHalo_nXtl_center",  " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw( h.haloCS_cscdPhi, "haloCS_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h.haloCS_sMaj_Eta,  "haloCS_sMaj_Eta", "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( h.haloCS_sMaj_Phi,  "haloCS_sMaj_Phi", "sMaj", " #phi",  "", 8  ) ;
   h_draw->Draw2D( h.haloCS_Eta_Time, "haloCS_Eta_Time", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.haloCS_Eta_Time1, "haloCS_Eta_Time1", "#eta", "EcalTime (ns)",  ""  ) ;

   h_draw->Draw2D( h.sideband_sMaj_Time, "sideband_sMaj_Time", "sMaj", "EcalTime (ns)",  "") ;
   h_draw->Draw2D( h.sideband_sMaj_Phi,  "sideband_sMaj_Phi",  "sMaj", " #phi",  ""  ) ;
   h_draw->Draw2D( h.sideband_sMaj_sMin, "sideband_sMaj_sMin", "sMaj", " sMin",  ""  ) ;
   h_draw->Draw2D( h.sideband_sMaj_Eta,  "sideband_sMaj_Eta",  "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( h.sideband_nXtl_Eta,  "sideband_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw(   h.sideband_nXtl,      "sideband_nXtl",  " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( h.gjCS_sMaj_Eta,  "gjCS_sMaj_Eta",  "sMaj", " #eta",  "logZ", 8  ) ;
   h_draw->Draw2D( h.gjCS_nXtl_Eta,  "gjCS_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;

   //h_draw->Draw( h.sideband_cscdPhi_EB, "", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   //h_draw->DrawAppend( h.sideband_cscdPhi_EE, "sideband_cscdPhi", 0.7, 2, 1  ) ;
   //h_draw->Draw( h.sideband_sMaj_EB,    "", " sMajor ", "", "", 0.95, 1 ) ;
   //h_draw->DrawAppend( h.sideband_sMaj_EE, "sideband_sMaj", 0.7, 2, 1  ) ;

   h_draw->Draw( h.sideband_cscdPhi_EB, "sideband_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw( h.sideband_sMaj_EB,    "sideband_sMaj",    " sMajor ", "", "", 0.95, 1 ) ;

   h_draw->Draw2D( h.spikeCS_sMaj_sMin, "spikeCS_sMaj_sMin", "sMaj", "sMin (ns)",  ""  ) ;
   h_draw->Draw2D( h.spikeCS_Eta_Time, "spikeCS_Eta_Time", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.spikeCS_Eta_Time1, "spikeCS_Eta_Time1", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.spikeCS_nXtl_Eta, "spikeCS_nXtl_Eta", "N of xtals", "#eta",  ""  ) ;
   h_draw->Draw2D( h.spikeCS_Phi_Time, "spikeCS_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw(   h.spikeCS_nXtl,     "spikeCS_nXtl",     " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( h.ghostCS_sMaj_Eta,  "ghostCS_sMaj_Eta", "sMaj", "#eta",  ""  ) ;
   h_draw->Draw2D( h.ghostCS_sMaj_sMin, "ghostCS_sMaj_sMin", "sMaj", "sMin (ns)",  ""  ) ;
   h_draw->Draw2D( h.ghostCS_Eta_Time,  "ghostCS_Eta_Time", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.ghostCS_Eta_Time1, "ghostCS_Eta_Time1", "#eta", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( h.ghostCS_Phi_Time,  "ghostCS_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;

   h_draw->Draw2D( h.ghost_Phi_Time, "ghost_Phi_Time",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.ghost_Eta_Time, "ghost_Eta_Time",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.ghost_sMaj_sMin, "ghost_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;
   h_draw->Draw2D( h.pure_Phi_Time,  "pure_Phi_Time",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.pure_Eta_Time,  "pure_Eta_Time",  "#eta", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( h.pure_sMaj_sMin, "pure_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;

   gStyle->SetOptStat("");
   //TString IntStrA[7] = { "" } ;
   TLegend* leg4  = new TLegend(.4, .6, .9, .9 );
   TLegend* leg5  = new TLegend(.4, .6, .9, .9 );
   Int_t nu0a, nu0 ;
   Float_t rate0 ;
   char RStr[30], RStr1[30], RStr2[60] ;
   float fEta = 0 ;
   for ( int k=0; k< 7; k++ ) {
       nu0a = h.sMaj_eta[k]->Integral();
       nu0  = h.sMaj_eta_csc[k]->Integral(28,100);   
       rate0 = (float) nu0 / (float) nu0a ;
       sprintf( RStr,  "%.3f, %.2f<|#eta|<%.2f", rate0, fEta , fEta+0.28 ) ;
       sprintf( RStr1, "%d, %.2f<|#eta|<%.2f", nu0, fEta , fEta+0.28 ) ;
       sprintf( RStr2, "%d / %d = %s", nu0, nu0a , RStr ) ;
       fEta += 0.28 ;
       //IntStrA[k] += nu0 ;
       //IntStrA[k] += " / " ;
       //IntStrA[k] += nu0a ;
       //IntStrA[k] += " = " ;
       //IntStrA[k] += RStr ;
       //if ( k < 5 ) leg4->AddEntry( h.sMaj_eta[k], IntStrA[k] , "L" ) ;
       if ( k < 5 ) leg4->AddEntry( h.sMaj_eta[k], RStr2 , "L" ) ;
       if ( k < 5 ) leg5->AddEntry( h.sMaj_eta[k], RStr1 , "L" ) ;
   }

   h.sMaj_eta[0]->SetTitle("") ;
   h_draw->Draw(       h.sMaj_eta[0], "", " s_{Major} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( h.sMaj_eta[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta[3], "",   0.9, 6, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta[4], "sMaj_EtaSlice_EB", 0.9, 8, 1 , leg4 ) ;

   h_draw->Draw(       h.sMaj_eta[5], "", " sMajor ", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.sMaj_eta[6], "sMaj_EtaSlice_EE", 0.75, 2, 1  ) ;

   h.sMaj_eta_csc[0]->SetTitle("") ;
   h_draw->Draw(       h.sMaj_eta_csc[0], "", " s_{Major} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( h.sMaj_eta_csc[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta_csc[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta_csc[3], "",   0.9, 6, 1  ) ;
   h_draw->DrawAppend( h.sMaj_eta_csc[4], "sMaj_EtaSlice_EBCSC", 0.9, 8, 1, leg5 ) ;

   h_draw->Draw(       h.sMaj_eta_csc[5], "", " sMajor ", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( h.sMaj_eta_csc[6], "sMaj_EtaSlice_EECSC", 0.75, 2, 1  ) ;

   TLegend* leg6  = new TLegend(.5, .7, .9, .9 );
   float nSp0  = h.notSpike_nXtl->Integral(1,8);   
   float nSp   = h.notSpike_nXtl->Integral();   
   char NStr[30] ;
   sprintf( NStr,  "%.1f / %.1f = %.4f ", nSp0, nSp, nSp0/nSp ) ;
   leg6->AddEntry( h.notSpike_nXtl, NStr , "L" ) ;
   h_draw->Draw(   h.notSpike_nXtl, "notSpike_nXtl", "N of crystals ", "",  "logY", 0.95, 1, 1, leg6 ) ;

   // Final Ghost mis-tagging rate
   if ( h.nCS_Eta->Integral() > 5 ) {
      TCanvas* c_0 = new TCanvas("c_0","", 800, 700);
      c_0->SetFillColor(10);
      c_0->SetFillColor(10);
      c_0->SetLeftMargin(0.16);
      c_0->SetRightMargin(0.08);
      c_0->SetTopMargin(0.1);
      c_0->SetBottomMargin(0.12);

      c_0->cd() ;

      TGraphAsymmErrors* gMistag = new TGraphAsymmErrors();
      gMistag->Divide( h.nGhS_Eta, h.nCS_Eta );

      gMistag->SetMaximum( 0.2 );
      gMistag->SetMinimum( 0.0 );
      gMistag->SetMarkerStyle(22);
      gMistag->SetMarkerSize(1);
      gMistag->SetMarkerColor(4);
      gMistag->SetLineWidth(2);
      gMistag->GetYaxis()->SetTitleOffset(1.39);
      gMistag->GetXaxis()->SetTitle( "|#eta|" ) ;
      gMistag->GetYaxis()->SetTitle(" Mis-Tagging Rate") ;
      gMistag->Draw("AP");
      c_0->Update();
      TString plotname = hfolder +  "MisTagging_Ghost."+plotType ;
      c_0->Print( plotname ) ;

      c_0->Clear() ;
      TGraphAsymmErrors* sMistag = new TGraphAsymmErrors();
      sMistag->Divide( h.nSpk_Eta, h.nCS_Eta );

      Double_t* sMA = sMistag->GetY() ;
      for (int i=0; i< 5 ; i++ ) { 
	      printf(" (%d)  = %.5f \n", i, sMA[i] ) ;
      }

      sMistag->SetMaximum( 0.08 );
      sMistag->SetMinimum( 0.0 );
      sMistag->SetMarkerStyle(22);
      sMistag->SetMarkerColor(4);
      sMistag->SetLineWidth(2);
      sMistag->GetYaxis()->SetTitleOffset(1.39);
      sMistag->GetXaxis()->SetTitle( "|#eta|" ) ;
      sMistag->GetYaxis()->SetTitle(" Mis-Tagging Rate ") ;
      sMistag->Draw("AP");
      c_0->Update();
      plotname = hfolder +  "MisTagging_Spike."+plotType ;
      c_0->Print( plotname ) ;

      c_0->Clear() ;
      TGraphAsymmErrors* hMistag = new TGraphAsymmErrors();
      hMistag->Divide( h.nHL_Eta, h.nCS_Eta );

      Double_t* hMA  = hMistag->GetY() ;
      for (int i=0; i< 5 ; i++ ) { 
	      printf(" (%d)  = %.5f \n", i, hMA[i] ) ;
      }

      hMistag->SetMaximum( 0.002 );
      hMistag->SetMinimum( 0.0 );
      hMistag->SetMarkerStyle(22);
      hMistag->SetMarkerColor(4);
      hMistag->SetLineWidth(2);
      hMistag->GetYaxis()->SetTitleOffset(1.9);
      hMistag->GetXaxis()->SetTitle( "|#eta|" ) ;
      hMistag->GetYaxis()->SetTitle(" Mis-Tagging Rate ") ;
      hMistag->Draw("AP");
      c_0->Update();
      plotname = hfolder +  "MisTagging_Halo."+plotType ;
      c_0->Print( plotname ) ;

   }


   hFile->Close() ;
   cout<<" hfile closed ! "<<endl ;
}  

