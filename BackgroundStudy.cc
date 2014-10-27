#include "BackgroundStudy.h"
#include "MathTools.h"
#include <TTree.h>
#include <algorithm>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TF2.h>

BackgroundStudy::BackgroundStudy( string datacardfile ) {

  //Input  = new AnaInput( datacardfile );
  Input = AnaInput::Instance() ;
  select = new DPSelection( datacardfile ) ;

  qcdS    = new QCDStudy( datacardfile ) ;
  haloS   = new HaloStudy( datacardfile ) ;
  spikeS  = new SpikeStudy( datacardfile ) ;
  cosmicS = new CosmicStudy( datacardfile ) ;

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("PhotonPFIso",   &photonPFIso ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("SystType",      &systType ) ;
  Input->GetParameters("TCut",          &TCut ) ;

  h_draw_ = new hDraw( hfolder, plotType ) ;
  newMET  = TLorentzVector( 0., 0., 0., 0. )  ;
}


BackgroundStudy::~BackgroundStudy(){

  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  //delete Input ;
  delete qcdS ;
  delete haloS ;
  delete spikeS ;
  delete cosmicS ;
  //delete h_draw_ ;
  cout<<" done ! "<<endl ;

}

void BackgroundStudy::Write() {

  obsTime->Write() ;

  h_EB_Time->Write() ;
  h_EB_Time0->Write() ;
  h_EB_Time1->Write() ;
  h_EB_Time2->Write() ;
  h_EE_Time->Write() ;
  h_EE_Time0->Write() ;
  h_EE_Time1->Write() ;
  h_EE_Time2->Write() ;
  h_EE_haloTime->Write() ;

  h_Eta_Phi->Write() ;
  h_Eta_Time->Write() ;
  h_Eta_Time1->Write() ;
  h_Eta_Time2->Write() ;
  h_Eta_Time3->Write() ;
  h_Eta_Time4->Write() ;

  h_Phi_Time->Write() ;
  h_cscdPhi_Time->Write() ;
  h_cscdPhi_cscTime->Write() ;
  h_sMaj_Time_EB->Write() ;
  h_sMaj_Time_EE->Write() ;
  h_sMin_Time_EB->Write() ;
  h_sMin_Time_EE->Write() ;
  h_sMaj_sigIeta_EB->Write() ;
  h_sMaj_sigIeta_EE->Write() ;
  h_sMin_sigIeta_EB->Write() ;
  h_sMin_sigIeta_EE->Write() ;
  h_sigIeta_Time_EB->Write() ;
  h_sigIeta_Time_EE->Write() ;
  h_Pt_MET->Write() ;
  h_Pt_Time_EB->Write() ;
  h_Pt_Time_EE->Write() ;
  h_MET_Time_EB->Write() ;
  h_MET_Time_EE->Write() ;
  h_hltMET_Time_EB->Write() ;
  h_hltMET_Time_EE->Write() ;
  h_cHadIso_Time->Write() ;
  h_nHadIso_Time->Write() ;
  h_photIso_Time->Write() ;
  h_seedE_Time->Write() ;
  h_cscdPhi_rho->Write() ;
  h_met_met1->Write() ;
  h_met_met2->Write() ;
  h_nPhoton->Write() ;
  h_jet_phot_Time->Write() ;
  h_jetTime->Write() ;
  h_jetTimeErr->Write() ;

  h_tChi2->Write() ;
  cs_tChi2->Write() ;

  h_nVtx->Write() ;
  h_nVtx_tChi2->Write() ;

  h_pfMET->Write() ;
  h_hltMET->Write() ;

  h_sMaj_Eta->Write() ;
  h_sMaj_Phi->Write() ;
  h_sMaj_sMin_EB->Write() ;
  h_nXtl_Eta->Write() ;
  h_nXtl_Pt_EB->Write() ;

  sg_Eta_Time->Write() ;
  sg_Phi_Time->Write() ;
  sg_sigIeta_Time->Write() ;
  sg_sMaj_Time->Write() ;
  sg_sMaj_Eta->Write() ;
  sg_sMin_Time->Write() ;
  sg_sMin_Eta->Write() ;
  sg_nXtl->Write() ;
  sg_nXtl_Eta->Write() ;
  sg_cscdPhi->Write() ;
  sg_Time->Write() ;
  sg_Time_halo->Write() ;
  sg_Time_spike->Write() ;
  sg_Time_cosmic->Write() ;
  sg_sMaj_sMin->Write() ;
  sg_dPhi_MET_csc->Write() ;
  sg_dPhi_MET_Jet1->Write() ;
  sg_dPhi_MET_Jet2->Write() ;
  sg_dPhi_MET_Jet3->Write() ;

  sel_cHadIso_Time->Write() ;
  sel_nHadIso_Time->Write() ;
  sel_photIso_Time->Write() ;
  sel_photIso_sMaj->Write() ;
  sel_photIso_sMin->Write() ;
  sel_photIso_sigIeta->Write() ;
  sel_Time->Write();
  sel_sMaj_Time->Write() ;
  sel_sMaj_Eta->Write() ;
  sel_sMin_Time->Write() ;
  sel_sMin_Eta->Write() ;
  sel_Eta_Time->Write() ;
  sel_Phi_Time->Write() ;
  sel_weirdXtl->Write() ;
  sel_T_dPhi_gMET_1J->Write() ;
  sel_T_dPhi_gMET_2J->Write() ;
  sel_T_dPhi_gMET_3J->Write() ;

  cs_dtdPhidEta->Write() ;
  cs_Eta_Time->Write() ;
  cs_Phi_Time->Write() ;
  cs_sigIeta_Time->Write() ;
  cs_nXtl->Write() ;
  cs_swissX->Write() ;
  cs_sMaj_sMin->Write() ;
  cs_cscdPhi->Write() ;
  cs_cHadIso_Time->Write() ;
  cs_nHadIso_Time->Write() ;
  cs_photIso_Time->Write() ;
  cs_seedE_photE->Write() ;

  sideband_photIso_cscdPhi->Write() ;
  sideband_sMin_Time->Write() ;
  sideband_sMaj_Time->Write() ;
  sideband_sMaj_Phi->Write() ;
  sideband_sMaj_sMin->Write() ;
  sideband_sMaj_Eta->Write() ;
  sideband_nXtl_Eta->Write() ;
  sideband_cscT_ecalT->Write() ;
  sideband_dtdPhidEta->Write() ;
  sideband_dtdR->Write() ;
  sideband_dtdPhidEta->Write() ;
  sideband_cscdPhi_u->Write() ;
  sideband_cscdPhi_d->Write() ;
  sideband_sMaj->Write() ;
  sideband_Pt_nJet->Write() ;

  abcd_Pt_Time->Write() ;
  abcd_MET_Time->Write() ;
  abcd_MET1_T_sMET2_1J->Write() ;
  abcd_MET1_T_bMET2_1J->Write() ;
  abcd_MET1_T_sMET2_2J->Write() ;
  abcd_MET1_T_bMET2_2J->Write() ;
  abcd_MET2_Time->Write() ;
  abcd_NJet_Time->Write() ;
  abcd_MET1_Time_closure1->Write() ;
  abcd_MET1_Time_closure2->Write() ;

  sideband_dPhi_MET_csc->Write() ;
  sideband_dPhi_MET_Jet1->Write() ;
  sideband_dPhi_MET_Jet2->Write() ;
  sideband_dPhi_MET_Jet3->Write() ;

  pure_Time->Write() ;

  nJets_center->Write() ;
  nJets_halo->Write() ;
  nJets_spike->Write() ;
  nJets_cosmic->Write() ;

  nHL_Eta->Write() ;
  nSpk_Eta->Write() ;
  nCS_Eta->Write() ;

  hBg_F->Write() ;
  hBg_E->Write() ;
  hBg_D->Write() ;
  hBg_C->Write() ;
  hBg_B->Write() ;
  hBg_A->Write() ;

  hCol_F->Write() ;
  hCol_E->Write() ;
  hCol_D->Write() ;
  hCol_C->Write() ;
  hCol_B->Write() ;
  hCol_A->Write() ;

  cout<<" Output historams written ! "<< endl ;
}

void BackgroundStudy::Create() {


  TString Path_fName = hfolder + hfileName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  // initial histograms  
  obsTime     = new TH1D("obsTime", "Photon Time from seed", 160,  -14.5, 25.5);

  // DOE plots
  h_EB_Time   = new TH1D( "h_EB_Time",  " Ecal time from EB", 200, -25, 25 ) ;
  h_EB_Time0  = new TH1D( "h_EB_Time0", " Ecal time from EB", 200, -25, 25 ) ;
  h_EB_Time1  = new TH1D( "h_EB_Time1", " Ecal time from EB", 200, -25, 25 ) ;
  h_EB_Time2  = new TH1D( "h_EB_Time2", " Ecal time from EB", 200, -25, 25 ) ;
  h_EE_Time   = new TH1D( "h_EE_Time",  " Ecal time from EE", 200, -25, 25 ) ;
  h_EE_Time0  = new TH1D( "h_EE_Time0", " Ecal time from EE", 200, -25, 25 ) ;
  h_EE_Time1  = new TH1D( "h_EE_Time1", " Ecal time from EE", 200, -25, 25 ) ;
  h_EE_Time2  = new TH1D( "h_EE_Time2", " Ecal time from EE", 200, -25, 25 ) ;
  h_EE_haloTime = new TH1D( "h_EE_haloTime", " Halo Ecal time from EE", 200, -25, 25 ) ;

  // Raw information
  h_Eta_Phi   = new TH2D( "h_Eta_Phi",  "#eta vs #phi", 102, -2.5, 2.5, 63, -3.15, 3.15 ) ;
  h_Eta_Time  = new TH2D( "h_Eta_Time", "#eta vs Ecal time", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Eta_Time1  = new TH2D( "h_Eta_Time1", "#eta vs Ecal time, newMET < pfMET", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Eta_Time2  = new TH2D( "h_Eta_Time2", "#eta vs Ecal time, newMET > pfMET", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Eta_Time3  = new TH2D( "h_Eta_Time3", "#eta vs Ecal time, noPhotMET < pfMET", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Eta_Time4  = new TH2D( "h_Eta_Time4", "#eta vs Ecal time, noPhotMET > pfMET", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Phi_Time  = new TH2D( "h_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  h_cscdPhi_Time  = new TH2D( "h_cscdPhi_Time", " d#Phi vs Ecal time", 65, 0, 3.25, 160, -20, 20 ) ;
  h_cscdPhi_cscTime  = new TH2D( "h_cscdPhi_cscTime", " d#Phi vs CSC time", 65, 0, 3.25, 300, -75, 75 ) ;
  h_sigIeta_Time_EB  = new TH2D( "h_sigIeta_Time_EB", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sigIeta_Time_EE  = new TH2D( "h_sigIeta_Time_EE", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sMaj_Time_EB = new TH2D( "h_sMaj_Time_EB", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMaj_Time_EE = new TH2D( "h_sMaj_Time_EE", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMin_Time_EB = new TH2D( "h_sMin_Time_EB",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20., 20. ) ;
  h_sMin_Time_EE = new TH2D( "h_sMin_Time_EE",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20., 20. ) ;
  h_sMaj_sigIeta_EB = new TH2D( "h_sMaj_sigIeta_EB", " sMaj vs Ecal time", 100, 0, 2, 80, 0, 0.08 ) ;
  h_sMaj_sigIeta_EE = new TH2D( "h_sMaj_sigIeta_EE", " sMaj vs Ecal time", 100, 0, 2, 80, 0, 0.08 ) ;
  h_sMin_sigIeta_EB = new TH2D( "h_sMin_sigIeta_EB",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_sMin_sigIeta_EE = new TH2D( "h_sMin_sigIeta_EE",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_Pt_MET       = new TH2D( "h_Pt_MET",        " Leading Pt vs MET", 50, 0, 500, 50, 0, 500 ) ;

  h_tChi2     = new TH1D( "h_tChi2", " chi2 of time ", 100, 0, 10  ) ;
  cs_tChi2    = new TH1D( "cs_tChi2", " chi2 of time ", 100, 0, 10  ) ;

  h_nVtx_tChi2 = new TH2D( "h_nVtx_tChi2", "nVtx vs #chi2_{t}", 41,-0.5,40.5, 100, 0, 10 ) ;
  h_nVtx       = new TH1D( "h_nVtx", "nVtx in good control region w/ MET > 60", 41,-0.5,40.5  ) ;
  h_pfMET        = new TH1D("h_pfMET", "PF MET ",   100, 0, 100 ) ;
  h_hltMET       = new TH1D("h_hltMET", "HLT MET ", 100, 0, 100 ) ;

  h_Pt_Time_EB   = new TH2D( "h_Pt_Time_EB",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_Pt_Time_EE   = new TH2D( "h_Pt_Time_EE",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EB  = new TH2D( "h_MET_Time_EB",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EE  = new TH2D( "h_MET_Time_EE",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_hltMET_Time_EB  = new TH2D( "h_hltMET_Time_EB",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_hltMET_Time_EE  = new TH2D( "h_hltMET_Time_EE",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_cHadIso_Time = new TH2D( "h_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_nHadIso_Time = new TH2D( "h_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_photIso_Time = new TH2D( "h_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  h_seedE_Time   = new TH2D( "h_seedE_Time", " seed E vs time", 100, 0, 500., 120, -15, 15 );
  h_cscdPhi_rho  = new TH2D( "h_cscdPhi_rho", " d#Phi vs rho", 65, 0, 3.25, 100, 100, 500. ) ;

  h_met_met1     = new TH2D( "h_met_met1",    " MET vs MET1", 50, 0, 500, 50, 0, 500 ) ;
  h_met_met2     = new TH2D( "h_met_met2",    " MET vs MET2", 50, 0, 500, 50, 0, 500 ) ;
  h_nPhoton      = new TH1D( "h_nPhoton", "N Photons", 11, -0.5, 10.5 ) ;
  h_jet_phot_Time = new TH2D( "h_jet_phot_Time", " jet time vs photon time", 80, -5., 5., 160, -20, 20 ) ;
  h_jetTime      = new TH1D( "h_jetTime", "Jet time", 160, -20., 20. ) ;
  h_jetTimeErr   = new TH1D( "h_jetTimeErr", "Jet time error", 100, 0., 5. ) ;

  h_sMaj_Eta  = new TH2D( "h_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  h_sMaj_Phi  = new TH2D( "h_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  h_sMaj_sMin_EB = new TH2D( "h_sMaj_sMin_EB", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  h_nXtl_Eta     = new TH2D( "h_nXtl_Eta", "N crystals vs #eta ", 50, 0, 50 ,  51, -2.5, 2.5) ;
  h_nXtl_Pt_EB   = new TH2D( "h_nXtl_Pt_EB", "N crystals vs Pt ", 50, 0, 50 ,  50,  0. , 500. ) ;

  // Information from signal selection
  sg_nXtl      = new TH1D( "sg_nXtl", "N crystals ", 50, 0, 50 ) ;
  sg_cscdPhi   = new TH1D( "sg_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  sg_Time       = new TH1D( "sg_Time", "Photon Time from signal CS", 160,  -14.5, 25.5);
  sg_Time_halo  = new TH1D( "sg_Time_halo", "Photon Time from signal but halo-tagged", 160,  -14.5, 25.5);
  sg_Time_spike = new TH1D( "sg_Time_spike", "Photon Time from signal but spike-tagged", 160,  -14.5, 25.5);
  sg_Time_cosmic= new TH1D( "sg_Time_cosmic", "Photon Time from signal but cosmic-tagged", 160,  -14.5, 25.5);
  sg_Eta_Time  = new TH2D( "sg_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sg_Phi_Time  = new TH2D( "sg_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  sg_nXtl_Eta  = new TH2D( "sg_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  sg_sigIeta_Time = new TH2D("sg_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;

  sel_cHadIso_Time = new TH2D("sel_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  sel_nHadIso_Time = new TH2D("sel_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  sel_photIso_Time = new TH2D("sel_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  sel_photIso_sMaj = new TH2D("sel_photIso_sMaj", " Photon IsoDeposit vs sMajor",         100, 0, 10., 100,  0., 2. );
  sel_photIso_sMin = new TH2D("sel_photIso_sMin", " Photon IsoDeposit vs sMinor",         100, 0, 10., 120,  0., 0.5 );
  sel_photIso_sigIeta = new TH2D("sel_photIso_sigIeta", " Photon IsoDeposit vs sigma_iEta",  100, 0, 10., 80,  0., 0.08 );
  sg_sMaj_sMin   = new TH2D( "sg_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  sg_sMaj_Time   = new TH2D( "sg_sMaj_Time", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  sg_sMin_Time   = new TH2D( "sg_sMin_Time",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  sg_sMaj_Eta    = new TH2D( "sg_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2.0, 51, -2.5, 2.5 ) ;
  sg_sMin_Eta    = new TH2D( "sg_sMin_Eta", " sMin vs photon #eta", 100, 0, 0.5, 51, -2.5, 2.5 ) ;

  sel_Time      = new TH1D( "sel_Time", "Photon Time after sg selection & bg rejection", 160,  -14.5, 25.5);
  sel_Eta_Time  = new TH2D( "sel_Eta_Time", " eta vs Ecal time", 153, -2.5, 2.5, 160, -20, 20 ) ;
  sel_Phi_Time  = new TH2D( "sel_Phi_Time", " phi vs Ecal time", 189, -3.15, 3.15, 160, -20, 20 ) ;
  sel_weirdXtl  = new TH2D( "sel_weridXtl", " eta vs phi ", 153, -2.5, 2.5, 189, -3.15, 3.15 ) ;
  sel_sMaj_Time = new TH2D( "sel_sMaj_Time", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  sel_sMin_Time = new TH2D( "sel_sMin_Time",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  sel_sMaj_Eta  = new TH2D( "sel_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2.0, 51, -2.5, 2.5 ) ;
  sel_sMin_Eta  = new TH2D( "sel_sMin_Eta", " sMin vs photon #eta", 100, 0, 0.5, 51, -2.5, 2.5 ) ;
  sel_T_dPhi_gMET_1J = new TH2D("sel_T_dPhi_gMET_1J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  sel_T_dPhi_gMET_2J = new TH2D("sel_T_dPhi_gMET_2J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  sel_T_dPhi_gMET_3J = new TH2D("sel_T_dPhi_gMET_3J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  sg_dPhi_MET_csc  = new TH2D("sg_dPhi_MET_csc", "dPhi( photon, MET) vs dPhi(photon,csc)", 64, 0, 3.2, 68, -0.2, 3.2 ) ;
  sg_dPhi_MET_Jet1 = new TH2D("sg_dPhi_MET_Jet1", "dPhi( photon, MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2 ) ;
  sg_dPhi_MET_Jet2 = new TH2D("sg_dPhi_MET_Jet2", "dPhi( photon, MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2 ) ;
  sg_dPhi_MET_Jet3 = new TH2D("sg_dPhi_MET_Jet3", "dPhi( photon, MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2 ) ;
  // Information from signal selection
  cs_Eta_Time  = new TH2D( "cs_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  cs_Phi_Time  = new TH2D( "cs_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  cs_sMaj_sMin  = new TH2D( "cs_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  cs_nXtl      = new TH1D( "cs_nXtl", "N crystals ", 50, 0, 50 ) ;
  cs_swissX    = new TH1D( "cs_swissX", "Swiss-X ", 110, 0, 1.1 ) ;
  cs_cscdPhi   = new TH1D( "cs_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  cs_cHadIso_Time = new TH2D("cs_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_nHadIso_Time = new TH2D("cs_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_photIso_Time = new TH2D("cs_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  cs_sigIeta_Time = new TH2D( "cs_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  cs_dtdPhidEta   = new TH2D( "cs_dtdPhidEta", " DT dPhi, dEta  ", 64, 0, 3.2, 50, 0, 1. ) ;
  cs_seedE_photE  = new TH2D( "cs_seedE_photE", " seed E vs phot E", 100, 0, 500, 100, 0, 500 ) ;

  sideband_photIso_cscdPhi = new TH2D("sideband_photIso_cscdPhi", " Photon IsoDeposit vs d#Phi" ,   100, 0, 10., 65, 0, 3.25 );
  sideband_sMin_Time  = new TH2D( "sideband_sMin_Time", " sMin vs photon time", 50, 0.1, 0.4, 160, -20, 20 ) ;
  sideband_sMaj_Time  = new TH2D( "sideband_sMaj_Time", " sMaj vs photon time", 100, 0, 2, 160, -20, 20 ) ;
  sideband_sMaj_Phi   = new TH2D( "sideband_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  sideband_sMaj_sMin  = new TH2D( "sideband_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  sideband_sMaj_Eta   = new TH2D( "sideband_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  sideband_nXtl_Eta   = new TH2D( "sideband_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  sideband_cscT_ecalT = new TH2D( "sideband_cscT_ecalT", " csc time vs Ecal time ", 300, -75, 75 , 120, -15, 15  ) ;
  sideband_cscdPhi_u  = new TH1D( "sideband_cscdPhi_u", " d#Phi ", 65, 0, 3.25 ) ;
  sideband_cscdPhi_d  = new TH1D( "sideband_cscdPhi_d", " d#Phi ", 65, 0, 3.25 ) ;
  sideband_dtdPhidEta = new TH2D( "sideband_dtdPhidEta", " DT dPhi, dEta  ", 64, 0, 3.2, 50, 0, 1. ) ;
  sideband_dtdR       = new TH1D( "sideband_dtdR", " dR( DTSeg, #gamma) ", 50, 0., 2.5 ) ;
  sideband_sMaj       = new TH1D( "sideband_sMaj", " sMajor ", 100, 0., 2. ) ;
  sideband_Pt_nJet    = new TH2D( "sideband_Pt_nJet", " Pt vs nJet", 50, 0, 500 ,  10, -0.5, 9.5) ;

  abcd_Pt_Time   = new TH2D( "abcd_Pt_Time",  " Pt vs Ecal time", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET_Time  = new TH2D( "abcd_MET_Time",  " MET vs Ecal time", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_T_sMET2_1J = new TH2D( "abcd_MET1_T_sMET2_1J", "MET1 vs Ecal time (MET2 < 60)", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_T_bMET2_1J = new TH2D( "abcd_MET1_T_bMET2_1J", "MET1 vs Ecal time (MET2 > 60)", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_T_sMET2_2J = new TH2D( "abcd_MET1_T_sMET2_2J", "MET1 vs Ecal time (MET2 < 60)", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_T_bMET2_2J = new TH2D( "abcd_MET1_T_bMET2_2J", "MET1 vs Ecal time (MET2 > 60)", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_Time_closure1 = new TH2D( "abcd_MET1_Time_closure1", "MET1 vs Ecal time,  1-jet closure", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET1_Time_closure2 = new TH2D( "abcd_MET1_Time_closure2", "MET1 vs Ecal time, >1-jet closure", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET2_Time  = new TH2D( "abcd_MET2_Time", "newMET vs Ecal time, newMET < MET for |t|>3", 50, 0, 500, 200, -25, 25 ) ;
  abcd_NJet_Time = new TH2D( "abcd_NJet_Time",  " NJet vs Ecal time", 10, 0, 10, 200, -25, 25 ) ;

  sideband_dPhi_MET_csc = new TH2D("sideband_dPhi_MET_csc", "dPhi( photon, MET) vs dPhi(photon,csc)", 64, 0, 3.2, 64, 0, 3.2 ) ;
  sideband_dPhi_MET_Jet1 = new TH2D("sideband_dPhi_MET_Jet1", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;
  sideband_dPhi_MET_Jet2 = new TH2D("sideband_dPhi_MET_Jet2", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;
  sideband_dPhi_MET_Jet3 = new TH2D("sideband_dPhi_MET_Jet3", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;

  pure_Time      = new TH1D( "pure_Time", "  time for pure photon", 160, -14.5, 25.5 ) ;

  nJets_center = new TH1D( "nJets_center",  "N of Jets for |t| < 2", 10, -0.5, 9.5 ) ;
  nJets_halo   = new TH1D( "nJets_halo",    "N of Jets for halo-tagged events", 10, -0.5, 9.5 ) ;
  nJets_spike  = new TH1D( "nJets_spike",   "N of Jets for spike-tagged events", 10, -0.5, 9.5 ) ;
  nJets_cosmic = new TH1D( "nJets_cosmic",  "N of Jets for cosmic-tagged events", 10, -0.5, 9.5 ) ;

  nHL_Eta  = new TH1D( "nHL_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
  nSpk_Eta = new TH1D( "nSpk_Eta",  " N of Spike in |#eta|", 5, 0., 1.4 ) ;
  nCS_Eta  = new TH1D( "nCS_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
 
  // x is eta region ,      each is 0.28  
  // y is different sample, 0:total, 1:halo, 2: spike, 3: cosmic
  // z is jet multiplicity  0, 1, >=2 
  hBg_F  = new TH3D( "hBg_F",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hBg_E  = new TH3D( "hBg_E",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hBg_D  = new TH3D( "hBg_D",  "Background in D (signal) region",  5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hBg_C  = new TH3D( "hBg_C",  "Background in C ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hBg_B  = new TH3D( "hBg_B",  "Background in B ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hBg_A  = new TH3D( "hBg_A",  "Background in A ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;

  hCol_F  = new TH3D( "hCol_F",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_E  = new TH3D( "hCol_E",  "Background in |t| < 2ns region",   5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_D  = new TH3D( "hCol_D",  "Background in D (signal) region",  5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_C  = new TH3D( "hCol_C",  "Background in C ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_B  = new TH3D( "hCol_B",  "Background in B ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
  hCol_A  = new TH3D( "hCol_A",  "Background in A ",                 5, 0, 5,  4, 0, 4,  3, 0, 3 ) ;
}

void BackgroundStudy::OpenAllHistograms() {

     TString Path_fName = hfolder + hfileName + ".root" ;
     TFile* hFile = new TFile( Path_fName, "UPDATE" );
     cout<<" file opened ! "<<endl ;

     qcdS->Open( hFile ) ;
     haloS->Open( hFile ) ;
     spikeS->Open( hFile ) ;
     cosmicS->Open( hFile ) ;
     Open( hFile ) ;
}

void BackgroundStudy::Open( TFile* hFile ) {

     if ( hFile == NULL ) {
        TString Path_fName = hfolder + hfileName + ".root" ;
        theFile = new TFile( Path_fName, "UPDATE" );
        //createFile = true ;
        cout<<" file opened ! "<<endl ;
     } else {
        theFile = hFile ;
        //createFile = false ;
     }

     /*
     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<endl ;
     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     //hFile->cd() ;
     */

     obsTime    = (TH1D*) theFile->Get("obsTime")     ;

     h_EB_Time  = (TH1D*) theFile->Get("h_EB_Time") ;
     h_EB_Time0 = (TH1D*) theFile->Get("h_EB_Time0");
     h_EB_Time1 = (TH1D*) theFile->Get("h_EB_Time1");
     h_EB_Time2 = (TH1D*) theFile->Get("h_EB_Time2");
     h_EE_Time  = (TH1D*) theFile->Get("h_EE_Time");
     h_EE_Time0 = (TH1D*) theFile->Get("h_EE_Time0");
     h_EE_Time1 = (TH1D*) theFile->Get("h_EE_Time1");
     h_EE_Time2 = (TH1D*) theFile->Get("h_EE_Time2");
     h_EE_haloTime = (TH1D*) theFile->Get("h_EE_haloTime");

     h_Eta_Phi   = (TH2D*) theFile->Get("h_Eta_Phi");
     h_Eta_Time  = (TH2D*) theFile->Get("h_Eta_Time");
     h_Eta_Time1  = (TH2D*) theFile->Get("h_Eta_Time1");
     h_Eta_Time2  = (TH2D*) theFile->Get("h_Eta_Time2");
     h_Eta_Time3  = (TH2D*) theFile->Get("h_Eta_Time3");
     h_Eta_Time4  = (TH2D*) theFile->Get("h_Eta_Time4");
     h_Phi_Time  = (TH2D*) theFile->Get("h_Phi_Time");
     h_cscdPhi_Time = (TH2D*) theFile->Get("h_cscdPhi_Time");
     h_cscdPhi_cscTime = (TH2D*) theFile->Get("h_cscdPhi_cscTime");
     h_sMaj_Time_EB = (TH2D*) theFile->Get("h_sMaj_Time_EB");
     h_sMaj_Time_EE = (TH2D*) theFile->Get("h_sMaj_Time_EE");
     h_sMin_Time_EB = (TH2D*) theFile->Get("h_sMin_Time_EB");
     h_sMin_Time_EE = (TH2D*) theFile->Get("h_sMin_Time_EE");
     h_sMaj_sigIeta_EB = (TH2D*) theFile->Get("h_sMaj_sigIeta_EB");
     h_sMaj_sigIeta_EE = (TH2D*) theFile->Get("h_sMaj_sigIeta_EE");
     h_sMin_sigIeta_EB = (TH2D*) theFile->Get("h_sMin_sigIeta_EB");
     h_sMin_sigIeta_EE = (TH2D*) theFile->Get("h_sMin_sigIeta_EE");
     h_sigIeta_Time_EB = (TH2D*) theFile->Get("h_sigIeta_Time_EB");
     h_sigIeta_Time_EE = (TH2D*) theFile->Get("h_sigIeta_Time_EE");
     h_Pt_MET      = (TH2D*) theFile->Get("h_Pt_MET");
     h_Pt_Time_EB  = (TH2D*) theFile->Get("h_Pt_Time_EB");
     h_Pt_Time_EE  = (TH2D*) theFile->Get("h_Pt_Time_EE");
     h_MET_Time_EB = (TH2D*) theFile->Get("h_MET_Time_EB");
     h_MET_Time_EE = (TH2D*) theFile->Get("h_MET_Time_EE");
     h_hltMET_Time_EB = (TH2D*) theFile->Get("h_hltMET_Time_EB");
     h_hltMET_Time_EE = (TH2D*) theFile->Get("h_hltMET_Time_EE");
     h_cHadIso_Time = (TH2D*) theFile->Get("h_cHadIso_Time");
     h_nHadIso_Time = (TH2D*) theFile->Get("h_nHadIso_Time");
     h_photIso_Time = (TH2D*) theFile->Get("h_photIso_Time");
     h_seedE_Time   = (TH2D*) theFile->Get("h_seedE_Time");
     h_jet_phot_Time = (TH2D*) theFile->Get("h_jet_phot_Time");
     h_jetTime      = (TH1D*) theFile->Get("h_jetTime");
     h_jetTimeErr   = (TH1D*) theFile->Get("h_jetTimeErr");

     h_met_met1     = (TH2D*) theFile->Get("h_met_met1");
     h_met_met2     = (TH2D*) theFile->Get("h_met_met2");
     h_nPhoton      = (TH1D*) theFile->Get("h_nPhoton");

     h_sMaj_Eta  = (TH2D*) theFile->Get("h_sMaj_Eta");
     h_sMaj_Phi  = (TH2D*) theFile->Get("h_sMaj_Phi");
     h_sMaj_sMin_EB = (TH2D*) theFile->Get("h_sMaj_sMin_EB");
     h_nXtl_Eta    = (TH2D*) theFile->Get("h_nXtl_Eta");
     h_nXtl_Pt_EB  = (TH2D*) theFile->Get("h_nXtl_Pt_EB");
     h_cscdPhi_rho = (TH2D*) theFile->Get("h_cscdPhi_rho");
     h_tChi2    = (TH1D*) theFile->Get("h_tChi2");
     cs_tChi2     = (TH1D*) theFile->Get("cs_tChi2");
     halo_tChi2   = (TH1D*) theFile->Get("halo_tChi2");
     spike_tChi2  = (TH1D*) theFile->Get("spike_tChi2");
     noHalo_tChi2  = (TH1D*) theFile->Get("noHalo_tChi2");
     cosmic_tChi2 = (TH1D*) theFile->Get("cosmic_tChi2");

     h_nVtx_tChi2 = (TH2D*) theFile->Get("h_nVtx_tChi2");
     h_nVtx    = (TH1D*) theFile->Get("h_nVtx");
     h_pfMET   = (TH1D*) theFile->Get("h_pfMET");
     h_hltMET  = (TH1D*) theFile->Get("h_hltMET");

     sg_Eta_Time = (TH2D*) theFile->Get("sg_Eta_Time");
     sg_Phi_Time = (TH2D*) theFile->Get("sg_Phi_Time");
     sg_sigIeta_Time = (TH2D*) theFile->Get("sg_sigIeta_Time");
     sg_nXtl_Eta     = (TH2D*) theFile->Get("sg_nXtl_Eta");
     sg_cscdPhi      = (TH1D*) theFile->Get("sg_cscdPhi");
     sg_nXtl         = (TH1D*) theFile->Get("sg_nXtl");
     sg_Time         = (TH1D*) theFile->Get("sg_Time");
     sg_Time_halo    = (TH1D*) theFile->Get("sg_Time_halo");
     sg_Time_spike   = (TH1D*) theFile->Get("sg_Time_spike");
     sg_Time_cosmic  = (TH1D*) theFile->Get("sg_Time_cosmic");
     sel_cHadIso_Time = (TH2D*) theFile->Get("sel_cHadIso_Time");
     sel_nHadIso_Time = (TH2D*) theFile->Get("sel_nHadIso_Time");
     sel_photIso_Time = (TH2D*) theFile->Get("sel_photIso_Time");
     sel_photIso_sMaj = (TH2D*) theFile->Get("sel_photIso_sMaj");
     sel_photIso_sMin = (TH2D*) theFile->Get("sel_photIso_sMin");
     sel_photIso_sigIeta = (TH2D*) theFile->Get("sel_photIso_sigIeta");
     sg_sMaj_Time = (TH2D*) theFile->Get("sg_sMaj_Time");
     sg_sMin_Time = (TH2D*) theFile->Get("sg_sMin_Time");
     sg_sMaj_Eta  = (TH2D*) theFile->Get("sg_sMaj_Eta");
     sg_sMaj_sMin = (TH2D*) theFile->Get("sg_sMaj_sMin");
     sg_sMin_Eta  = (TH2D*) theFile->Get("sg_sMin_Eta");

     sel_Time     = (TH1D*) theFile->Get("sel_Time");
     sel_weirdXtl = (TH2D*) theFile->Get("sel_weirdXtl");
     sel_Eta_Time = (TH2D*) theFile->Get("sel_Eta_Time");
     sel_Phi_Time = (TH2D*) theFile->Get("sel_Phi_Time");
     sel_sMaj_Time = (TH2D*) theFile->Get("sel_sMaj_Time");
     sel_sMin_Time = (TH2D*) theFile->Get("sel_sMin_Time");
     sel_sMaj_Eta  = (TH2D*) theFile->Get("sel_sMaj_Eta");
     sel_sMin_Eta  = (TH2D*) theFile->Get("sel_sMin_Eta");
     sel_T_dPhi_gMET_1J  = (TH2D*) theFile->Get("sel_T_dPhi_gMET_1J") ;
     sel_T_dPhi_gMET_2J  = (TH2D*) theFile->Get("sel_T_dPhi_gMET_2J") ;
     sel_T_dPhi_gMET_3J  = (TH2D*) theFile->Get("sel_T_dPhi_gMET_3J") ;
     sg_dPhi_MET_csc    = (TH2D*) theFile->Get("sg_dPhi_MET_csc") ;
     sg_dPhi_MET_Jet1    = (TH2D*) theFile->Get("sg_dPhi_MET_Jet1") ;
     sg_dPhi_MET_Jet2    = (TH2D*) theFile->Get("sg_dPhi_MET_Jet2") ;
     sg_dPhi_MET_Jet3    = (TH2D*) theFile->Get("sg_dPhi_MET_Jet3") ;

     cs_Eta_Time = (TH2D*) theFile->Get("cs_Eta_Time");
     cs_Phi_Time = (TH2D*) theFile->Get("cs_Phi_Time");
     cs_sigIeta_Time = (TH2D*) theFile->Get("cs_sigIeta_Time");
     cs_cscdPhi      = (TH1D*) theFile->Get("cs_cscdPhi");
     cs_nXtl         = (TH1D*) theFile->Get("cs_nXtl");
     cs_swissX       = (TH1D*) theFile->Get("cs_swissX");
     cs_sMaj_sMin     = (TH2D*) theFile->Get("cs_sMaj_sMin");
     cs_cHadIso_Time = (TH2D*) theFile->Get("cs_cHadIso_Time");
     cs_nHadIso_Time = (TH2D*) theFile->Get("cs_nHadIso_Time");
     cs_photIso_Time = (TH2D*) theFile->Get("cs_photIso_Time");
     cs_dtdPhidEta   = (TH2D*) theFile->Get("cs_dtdPhidEta");
     cs_seedE_photE  = (TH2D*) theFile->Get("cs_seedE_photE");

     sideband_photIso_cscdPhi = (TH2D*) theFile->Get("sideband_photIso_cscdPhi");
     sideband_sMin_Time = (TH2D*) theFile->Get("sideband_sMin_Time");
     sideband_sMaj_Time = (TH2D*) theFile->Get("sideband_sMaj_Time");
     sideband_sMaj_Phi  = (TH2D*) theFile->Get("sideband_sMaj_Phi");
     sideband_sMaj_sMin = (TH2D*) theFile->Get("sideband_sMaj_sMin");
     sideband_sMaj_Eta  = (TH2D*) theFile->Get("sideband_sMaj_Eta");
     sideband_nXtl_Eta  = (TH2D*) theFile->Get("sideband_nXtl_Eta");
     sideband_cscT_ecalT= (TH2D*) theFile->Get("sideband_cscT_ecalT");
     sideband_cscdPhi_u = (TH1D*) theFile->Get("sideband_cscdPhi_u");
     sideband_cscdPhi_d = (TH1D*) theFile->Get("sideband_cscdPhi_d");
     sideband_dtdR        = (TH1D*) theFile->Get("sideband_dtdR");
     sideband_dtdPhidEta  = (TH2D*) theFile->Get("sideband_dtdPhidEta");
     sideband_sMaj = (TH1D*) theFile->Get("sideband_sMaj");
     sideband_Pt_nJet   = (TH2D*) theFile->Get("sideband_Pt_nJet");

     abcd_Pt_Time = (TH2D*) theFile->Get("abcd_Pt_Time");
     abcd_MET_Time = (TH2D*) theFile->Get("abcd_MET_Time");
     abcd_MET1_T_sMET2_1J = (TH2D*) theFile->Get("abcd_MET1_T_sMET2_1J");
     abcd_MET1_T_bMET2_1J = (TH2D*) theFile->Get("abcd_MET1_T_bMET2_1J");
     abcd_MET1_T_sMET2_2J = (TH2D*) theFile->Get("abcd_MET1_T_sMET2_2J");
     abcd_MET1_T_bMET2_2J = (TH2D*) theFile->Get("abcd_MET1_T_bMET2_2J");
     abcd_MET1_Time_closure1 = (TH2D*) theFile->Get("abcd_MET1_Time_closure1");
     abcd_MET1_Time_closure2 = (TH2D*) theFile->Get("abcd_MET1_Time_closure2");
     abcd_MET2_Time = (TH2D*) theFile->Get("abcd_MET2_Time");
     abcd_NJet_Time = (TH2D*) theFile->Get("abcd_NJet_Time");

     sideband_dPhi_MET_csc = (TH2D*) theFile->Get("sideband_dPhi_MET_csc") ;
     sideband_dPhi_MET_Jet1 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet1") ;
     sideband_dPhi_MET_Jet2 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet2") ;
     sideband_dPhi_MET_Jet3 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet3") ;

     pure_Time = (TH1D*) theFile->Get("pure_Time");

     nJets_center  = (TH1D*) theFile->Get("nJets_center");
     nJets_halo    = (TH1D*) theFile->Get("nJets_halo");
     nJets_spike   = (TH1D*) theFile->Get("nJets_spike");
     nJets_cosmic  = (TH1D*) theFile->Get("nJets_cosmic");

     nHL_Eta  = (TH1D*) theFile->Get("nHL_Eta");
     nSpk_Eta = (TH1D*) theFile->Get("nSpk_Eta");
     nCS_Eta  = (TH1D*) theFile->Get("nCS_Eta");

     hBg_F   = (TH3D*) theFile->Get("hBg_F") ;
     hBg_E   = (TH3D*) theFile->Get("hBg_E") ;
     hBg_D   = (TH3D*) theFile->Get("hBg_D") ;
     hBg_C   = (TH3D*) theFile->Get("hBg_C") ;
     hBg_B   = (TH3D*) theFile->Get("hBg_B") ;
     hBg_A   = (TH3D*) theFile->Get("hBg_A") ;
     
     hCol_F   = (TH3D*) theFile->Get("hCol_F") ;
     hCol_E   = (TH3D*) theFile->Get("hCol_E") ;
     hCol_D   = (TH3D*) theFile->Get("hCol_D") ;
     hCol_C   = (TH3D*) theFile->Get("hCol_C") ;
     hCol_B   = (TH3D*) theFile->Get("hCol_B") ;
     hCol_A   = (TH3D*) theFile->Get("hCol_A") ;
      
     cout<<" link all histograms  "<<endl ;
}

void BackgroundStudy::CreateHistograms() {

   Create() ;
   qcdS->Create( theFile ) ;
   haloS->Create( theFile ) ;
   spikeS->Create( theFile ) ;
   cosmicS->Create( theFile ) ;

}

void BackgroundStudy::SimpleRun( string dataName, double weight ) { 

   // Open file and link the tree
   string dataFileNames ;
   if ( dataName.size() > 0 ) {
      dataFileNames = dataName ;
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   tr   = Input->GetTree( dataFileNames, "DPAnalysis" );
   totalN = tr->GetEntries();
   cout<<" Get the tree ! "<<endl ;
   setRtupleAddresses( tr, rt );
   cout<<" Link Tree variables ! "<<endl ;

   gSystem->mkdir( hfolder.c_str() );

   //TString Path_fName = hfolder + hfileName + ".root" ; 
   //theFile = new TFile( Path_fName, "RECREATE" );
   //theFile->cd() ;

   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;
   cout<<" from  "<< dataFileNames  <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   int nTrig[2] = { 0. , 0 } ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       select->Init( rt ) ;
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
    
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;

       // Trigger selection 
       //if ( rt.triggered != 1 && rt.triggered != 3 ) continue ;
       bool passTrigger = select->HLTFilter() ;
       if ( !passTrigger ) continue ;
       // 2. ControlSelection  - Events containing at least 1 photon 
       uint32_t evtType = select->EventIdentification();

       // 3. Get Selection Result
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;
       //// Trigger Efficiency 
       if ( selectPho.size() > 0 ) {
          if ( rt.triggered == 1 || rt.triggered == 3 ) nTrig[0]++ ;
          if ( rt.triggered == 3 ) nTrig[1]++ ;
       }
    
       //// Propagate the MET2 to others
       newMET    = select->newMET ;
       noPhotMET = select->noPhotMET ;
       //TLorentzVector met1 = select->noPhotMET ;
       //printf(" pf: %.2f, met1: %.2f , met2: %.2f \n", rt.metE, noPhotMET.E() , newMET.E() ) ;
       //printf(" njet : %d , nphot : %d \n", (int)selectJets.size() , (int)selectPho.size() ) ;

       haloS->GetNewMET( newMET, select->noPhotMET ) ;
       spikeS->GetNewMET( newMET, select->noPhotMET ) ;
       cosmicS->GetNewMET( newMET, select->noPhotMET ) ;
       qcdS->GetNewMET( newMET, select->noPhotMET ) ;

       // 4. Raw Information - without applying any cuts
       RawInfo( selectPho, selectJets, weight ) ;
       qcdS->Run(   selectPho, selectJets, rt, weight  )   ;
 
       // Type = 2 : Control sample , at least one photon pt > 45 GeV
       bool wanted = ( (evtType >> 1) & 1  ) ;
       if ( !wanted ) continue ;
       //cout<<" evt type: "<< evtType ;
       //cout<<" phot sz: "<< selectPho.size() <<" jet sz: "<< selectJets.size() << endl ;

       // 5. Study each components   
       ControlStudy( selectPho, selectJets, weight ) ;
       haloS->Run(   selectPho, selectJets, rt, weight  )   ;
       spikeS->Run(  selectPho, selectJets, rt, weight  )   ;
       cosmicS->Run( selectPho, selectJets, rt, weight  )   ;
     
   }
   printf( "MET Trigger Efficiency = %d / %d = %.2f \n\n", nTrig[1] , nTrig[0], (float)nTrig[1]/(float)nTrig[0] ) ;  

   // Display cut flow
   select->PrintCutFlow() ;

}

void BackgroundStudy::WriteDrawHistograms() {

   theFile->cd() ;
   Write() ;
   qcdS->Write() ;
   haloS->Write() ;
   spikeS->Write() ;
   cosmicS->Write() ;

   // Draw histograms
   qcdS->DrawHistograms( h_draw_ ) ;
   haloS->DrawHistograms( h_draw_ ) ;
   spikeS->DrawHistograms( h_draw_ ) ;
   cosmicS->DrawHistograms( h_draw_ ) ;
   DrawHistograms( h_draw_ ) ;
}

// The overview of the data, without applying any cuts
void BackgroundStudy::RawInfo( vector<objID>& selectPho, vector<objID>& selectJets, double weight ) {

       TLorentzVector met = select->theMET ;

       double pfMET_  = ( met.E() > 99.5  ) ? 99.5 : met.E() ;
       double hltMET_ = ( rt.t_met > 99.5 ) ? 99.5 : rt.t_met ;
       h_pfMET->Fill( pfMET_, weight ) ;
       h_hltMET->Fill( hltMET_, weight ) ;
       h_nPhoton->Fill( selectPho.size(), weight ) ;
       h_nVtx->Fill( rt.totalNVtx, weight ) ;

       for ( int k=0 ; k < rt.nPhotons ; k++ ) {

	   TLorentzVector gP4_ = TLorentzVector( rt.phoPx[k], rt.phoPy[k], rt.phoPz[k], rt.phoE[k] ) ;
           bool badseed   = badCrystal( gP4_.Eta() , gP4_.Phi() ) ;

           double egScale = 1. ;
           if ( systType == 5 ) egScale = ( fabs(gP4_.Eta()) < 1.479 ) ? 1.006 : 1.015 ;
           if ( systType == 6 ) egScale = ( fabs(gP4_.Eta()) < 1.479 ) ? 0.994 : 0.985 ;
           gP4_ = gP4_ * egScale ;

           if ( fabs(gP4_.Eta() ) < 1.47 ) h_Eta_Phi->Fill( gP4_.Eta() , gP4_.Phi() , weight );

           if ( badseed ) continue ;

	   bool haloTag   = haloS->HaloTag( rt , k) ;

	   double nHIso = max( rt.nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
	   double phIso = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
	   double cscdPhi_ =  ( rt.cscdPhi[k] > 9. ) ? 3.24 : rt.cscdPhi[k] ;

           h_nVtx_tChi2->Fill( rt.totalNVtx, rt.timeChi2[k], weight ) ;
           if ( met.E() - newMET.E() > 1. )    h_Eta_Time1->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
	   if ( newMET.E() - met.E() > 1. )    h_Eta_Time2->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
           
           if ( met.E() - noPhotMET.E() > 1. ) h_Eta_Time3->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
	   if ( noPhotMET.E() - met.E() > 1. ) h_Eta_Time4->Fill( gP4_.Eta() , rt.seedTime[k] , weight );

           if ( fabs(gP4_.Eta()) < 1.45 ) {
              if ( selectJets.size() >= 0 ) h_EB_Time->Fill(  rt.seedTime[k] , weight );
              if ( selectJets.size() == 0 ) h_EB_Time0->Fill( rt.seedTime[k] , weight );
              if ( selectJets.size() == 1 ) h_EB_Time1->Fill( rt.seedTime[k] , weight );
              if ( selectJets.size() >= 2 ) h_EB_Time2->Fill( rt.seedTime[k] , weight );
           } 
           if ( fabs(gP4_.Eta()) > 1.5 ) {
              if ( selectJets.size() >= 0 ) h_EE_Time->Fill(  rt.seedTime[k] , weight );
              if ( selectJets.size() == 0 ) h_EE_Time0->Fill( rt.seedTime[k] , weight );
              if ( selectJets.size() == 1 ) h_EE_Time1->Fill( rt.seedTime[k] , weight );
              if ( selectJets.size() >= 2 ) h_EE_Time2->Fill( rt.seedTime[k] , weight );
              if ( haloTag ) h_EE_haloTime->Fill( rt.seedTime[k] , weight ) ;
           }

	   if ( k ==0 ) h_Pt_MET->Fill( gP4_.Pt(), met.E(), weight  ) ;
           h_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );

 	   if ( fabs( rt.seedTime[k]) > 1.5 ) h_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
	   h_cscdPhi_cscTime->Fill( cscdPhi_, rt.cscTime[k] , weight  ) ;
	   h_cscdPhi_rho->Fill(     cscdPhi_, rt.cscRho[k] , weight  ) ;

           if ( fabs( gP4_.Eta() ) < 1.45 ) {
   	      h_cscdPhi_Time->Fill(    cscdPhi_ ,      rt.seedTime[k] , weight  ) ;
  	      h_sMin_Time_EB->Fill(    rt.sMinPho[k] , rt.seedTime[k] , weight ) ;
	      h_sMaj_Time_EB->Fill(    rt.sMajPho[k] , rt.seedTime[k] , weight ) ;
  	      h_sMin_sigIeta_EB->Fill( rt.sMinPho[k] , rt.sigmaIeta[k] , weight ) ;
	      h_sMaj_sigIeta_EB->Fill( rt.sMajPho[k] , rt.sigmaIeta[k] , weight ) ;
	      h_sigIeta_Time_EB->Fill( rt.sigmaIeta[k], rt.seedTime[k] , weight  ) ;
	      h_Pt_Time_EB->Fill(  gP4_.Pt(), rt.seedTime[k] , weight  ) ;
	      h_MET_Time_EB->Fill( met.E(),   rt.seedTime[k] , weight  ) ;
	      h_hltMET_Time_EB->Fill( rt.t_met,   rt.seedTime[k] , weight  ) ;
	      h_sMaj_sMin_EB->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight );
	      h_nXtl_Pt_EB->Fill( rt.nXtals[k],  gP4_.Pt() , weight );
           }
           if ( fabs( gP4_.Eta() ) > 1.5 ) {
  	      h_sMin_Time_EE->Fill( rt.sMinPho[k] , rt.seedTime[k] , weight );
	      h_sMaj_Time_EE->Fill( rt.sMajPho[k] , rt.seedTime[k] , weight );
  	      h_sMin_sigIeta_EE->Fill( rt.sMinPho[k] , rt.sigmaIeta[k] , weight );
	      h_sMaj_sigIeta_EE->Fill( rt.sMajPho[k] , rt.sigmaIeta[k] , weight );
	      h_sigIeta_Time_EE->Fill( rt.sigmaIeta[k], rt.seedTime[k] , weight  ) ;
	      h_Pt_Time_EE->Fill( gP4_.Pt(), rt.seedTime[k] , weight  ) ;
	      h_MET_Time_EE->Fill( met.E(), rt.seedTime[k] , weight  ) ;
	      h_hltMET_Time_EE->Fill( rt.t_met , rt.seedTime[k] , weight  ) ;
           }

	   h_sMaj_Eta->Fill( rt.sMajPho[k] , gP4_.Eta() , weight ) ;
	   h_nXtl_Eta->Fill( rt.nXtals[k],  gP4_.Eta() , weight );
	   if ( rt.sMajPho[k] > 0.4 ) h_sMaj_Phi->Fill( rt.sMajPho[k] , gP4_.Phi() , weight ) ;
           h_cHadIso_Time->Fill( rt.cHadIso[k] , rt.seedTime[k] , weight ) ;
           h_nHadIso_Time->Fill( nHIso , rt.seedTime[k] , weight ) ;
           h_photIso_Time->Fill( phIso , rt.seedTime[k] , weight ) ;
           h_seedE_Time->Fill( rt.seedE[k] , rt.seedTime[k] , weight ) ;

       }
}


void BackgroundStudy::ControlStudy( vector<objID>& selectPho, vector<objID>& selectJets, double weight ) {

       TLorentzVector met = select->theMET ;
       TLorentzVector ajet = JetVectorSum( selectJets ) ;
       double dPhi_jMET = ( selectJets.size() > 0 ) ? fabs( met.DeltaPhi( ajet ) ) : -0.1 ;

       for ( size_t kk =0; kk < selectPho.size() ; kk++) {

           int k = selectPho[kk].first ;
	   TLorentzVector gP4_ = selectPho[kk].second ; 
	   double dPhi_gMET = fabs( gP4_.DeltaPhi( met ) );
	   double cscdPhi_  = ( rt.cscdPhi[k] > 9. ) ? 3.24 : rt.cscdPhi[k] ;
	   double nHIso     = max( rt.nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
	   double phIso     = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;

	   // Define the Tag and Check the efficiency 
	   bool haloTag   = haloS->HaloTag( rt , k) ;
	   bool cosmicTag = cosmicS->CosmicTag(rt, k ) ;
	   bool spikeTag  = spikeS->SpikeTag(rt, k) ;
	   bool ghostTag  = ( haloTag || spikeTag || cosmicTag ) ? true : false ;
           
           // Test for ABCD region
           if ( !ghostTag && rt.timeChi2[k] < 4. && selectPho[0].second.Pt() > photonCuts[8] && selectJets.size() >= jetCuts[2] && selectJets.size() <= jetCuts[3]) {
                 abcd_MET_Time->Fill( met.E(), rt.seedTime[k], weight);
		 abcd_MET2_Time->Fill( newMET.E(), rt.seedTime[k], weight);
           }

           // ******************
	   //   Region A and B - Real Photon: -0.024 +/- 0.426
	   // ******************
           bool passABCDSelection = ( newMET.E() > jetCuts[4] && rt.timeChi2[k] < 4 && selectPho[0].second.Pt() > photonCuts[8] ) ; 
           bool passCollSelection = ( newMET.E() < jetCuts[4] && rt.timeChi2[k] < 4 && selectPho[0].second.Pt() > photonCuts[8] ) ; 
  	   int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 : ( fabs(gP4_.Eta()) / 0.28 ) ;
           int nj = ( selectJets.size() > 2 )   ? 2 : (int)selectJets.size() ;

           if ( !ghostTag ) {
	      if (passABCDSelection && selectJets.size() == 1) abcd_MET1_T_bMET2_1J->Fill( noPhotMET.E(), rt.seedTime[k], weight );
	      if (passCollSelection && selectJets.size() == 1) abcd_MET1_T_sMET2_1J->Fill( noPhotMET.E(), rt.seedTime[k], weight );
	      if (passABCDSelection && selectJets.size()  > 1) abcd_MET1_T_bMET2_2J->Fill( noPhotMET.E(), rt.seedTime[k], weight );
	      if (passCollSelection && selectJets.size()  > 1) abcd_MET1_T_sMET2_2J->Fill( noPhotMET.E(), rt.seedTime[k], weight );
	      if (passABCDSelection && selectJets.size() >= 1) abcd_Pt_Time->Fill( gP4_.Pt() , rt.seedTime[k], weight) ;
	      if ( passABCDSelection )  abcd_NJet_Time->Fill( selectJets.size(), rt.seedTime[k], weight);
           }
           // Another closure selection -- test of closure test !!!
           if ( newMET.E() > jetCuts[4] && rt.timeChi2[k] < 4 && selectPho[0].second.Pt() < photonCuts[8] ) {
              if ( selectJets.size() == 1 )  abcd_MET1_Time_closure1->Fill( noPhotMET.E(), rt.seedTime[k], weight ) ;
              if ( selectJets.size()  > 1 )  abcd_MET1_Time_closure2->Fill( noPhotMET.E(), rt.seedTime[k], weight ) ;
           } 

           // Region E , |t| < 2 ns  
           if ( fabs(rt.seedTime[k]) < 2. && passABCDSelection ) {
              if ( noPhotMET.E() > jetCuts[4] ) hBg_F->Fill( ih, 0.5, nj,  weight );
              if ( noPhotMET.E() < jetCuts[4] ) hBg_E->Fill( ih, 0.5, nj,  weight );
           }
	   if ( rt.seedTime[k] > TCut[0] && rt.seedTime[k] < TCut[1] && passABCDSelection ) {
              // Region B
              if ( noPhotMET.E() > jetCuts[4] ) {

   	         hBg_B->Fill( ih, 0.5, nj,  weight );
		 if ( haloTag  && !cosmicTag && !spikeTag )  hBg_B->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )               hBg_B->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                            hBg_B->Fill( ih, 3.5, nj, weight );
              }
	      // Region A
              if ( noPhotMET.E() < jetCuts[4] ) {

		    hBg_A->Fill( ih, 0.5, nj, weight );
		    if ( haloTag && !cosmicTag && !spikeTag )  hBg_A->Fill( ih, 1.5, nj, weight );
		    if ( spikeTag && !cosmicTag )              hBg_A->Fill( ih, 2.5, nj, weight );
		    if ( cosmicTag )                           hBg_A->Fill( ih, 3.5, nj, weight );
              }
           }
	   // ******************
	   //   Region C and D
	   // ******************
           if ( rt.seedTime[k] > TCut[2] && rt.seedTime[k] < TCut[3] && passABCDSelection ) {
              // Region D
              if ( noPhotMET.E() > jetCuts[4] ) {

		 hBg_D->Fill( ih, 0.5, nj, weight );
		 if ( haloTag && !cosmicTag && !spikeTag )  hBg_D->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )              hBg_D->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                           hBg_D->Fill( ih, 3.5, nj, weight );
              }
	      // Region C
              if ( noPhotMET.E() < jetCuts[4] ) {

		 hBg_C->Fill( ih, 0.5, nj, weight );
		 if ( haloTag && !cosmicTag && !spikeTag )  hBg_C->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )              hBg_C->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                           hBg_C->Fill( ih, 3.5, nj, weight );
              }
           }

           // Region E , |t| < 2 ns  
           if ( fabs(rt.seedTime[k]) < 2. && passCollSelection ) {
              if ( noPhotMET.E() > jetCuts[4] ) hCol_F->Fill( ih, 0.5, nj,  weight );
              if ( noPhotMET.E() < jetCuts[4] ) hCol_E->Fill( ih, 0.5, nj,  weight );
           }
	   if ( rt.seedTime[k] > TCut[0] && rt.seedTime[k] < TCut[1] && passCollSelection ) {
              // Region B
              if ( noPhotMET.E() > jetCuts[4] ) {

   	         hCol_B->Fill( ih, 0.5, nj,  weight );
		 if ( haloTag  && !cosmicTag && !spikeTag )  hCol_B->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )               hCol_B->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                            hCol_B->Fill( ih, 3.5, nj, weight );
              }
	      // Region A
              if ( noPhotMET.E() < jetCuts[4] ) {

		    hCol_A->Fill( ih, 0.5, nj, weight );
		    if ( haloTag && !cosmicTag && !spikeTag )  hCol_A->Fill( ih, 1.5, nj, weight );
		    if ( spikeTag && !cosmicTag )              hCol_A->Fill( ih, 2.5, nj, weight );
		    if ( cosmicTag )                           hCol_A->Fill( ih, 3.5, nj, weight );
              }
           }
	   // ******************
	   //   Region C and D
	   // ******************
           if ( rt.seedTime[k] > TCut[2] && rt.seedTime[k] < TCut[3] && passCollSelection ) {
              // Region D
              if ( noPhotMET.E() > jetCuts[4] ) {

		 hCol_D->Fill( ih, 0.5, nj, weight );
		 if ( haloTag && !cosmicTag && !spikeTag )  hCol_D->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )              hCol_D->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                           hCol_D->Fill( ih, 3.5, nj, weight );
              }
	      // Region C
              if ( noPhotMET.E() < jetCuts[4] ) {

		 hCol_C->Fill( ih, 0.5, nj, weight );
		 if ( haloTag && !cosmicTag && !spikeTag )  hCol_C->Fill( ih, 1.5, nj, weight );
		 if ( spikeTag && !cosmicTag )              hCol_C->Fill( ih, 2.5, nj, weight );
		 if ( cosmicTag )                           hCol_C->Fill( ih, 3.5, nj, weight );
              }
           }

           // ******************
	   //   vertex studies
	   // ******************
           if ( rt.seedTime[k] > -1.5 && rt.seedTime[k] < 1.5 && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
                 if ( !ghostTag ) h_tChi2->Fill( rt.timeChi2[k], weight ) ;
           }

           // ******************
	   //   Jet studies
	   // ******************
           if ( kk == 0 ) {
              int njets = ( selectJets.size() > 9 ) ? 9 : (int)selectJets.size() ;
              if ( fabs( rt.seedTime[k]) < 2. && ! ghostTag ) 
                                nJets_center->Fill( njets , weight );
              if ( haloTag    ) nJets_halo->Fill(   njets , weight );
	      if ( spikeTag   ) nJets_spike->Fill(  njets , weight );
	      if ( cosmicTag  ) nJets_cosmic->Fill( njets , weight );
           }
         
           double dt_jg = 99. ;
           int jk = -1 ;
           for ( size_t jj =0 ; jj< selectJets.size() ; jj++ ) {
               int j = selectJets[jj].first ;
               if ( kk == 0 ) { 
                  h_jetTime->Fill( rt.jetTime[j] ) ;
                  h_jetTimeErr->Fill( rt.jetTimeErr[j] ) ;
               }
               if ( rt.jetTimeErr[j] < 0.001 || rt.jetTimeErr[j] > 50. ) continue ;
               double dt_ = fabs( rt.jetTime[j] - rt.seedTime[k] ) ;
               if ( dt_ < dt_jg ) {
                  dt_jg = dt_ ;
                  jk = j ;
               }          
           }
           h_jet_phot_Time->Fill( rt.jetTime[jk], rt.seedTime[k] ) ;

           if ( selectPho[0].second.Pt() > 80. ) {

               // ******************
               //   Look at the sideband area
   	       // ******************
	       if ( rt.seedTime[k]  > 2. || rt.seedTime[k] < -3 ) {
     	            sideband_Pt_nJet->Fill( gP4_.Pt() , selectJets.size() , weight );
     	            sideband_sMaj_sMin->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight );
		    sideband_sMaj_Phi->Fill( rt.sMajPho[k] , gP4_.Phi() , weight );
		    sideband_sMaj_Eta->Fill( rt.sMajPho[k] , gP4_.Eta() , weight );
		    sideband_sMaj_Time->Fill( rt.sMajPho[k] , rt.seedTime[k] , weight );
		    sideband_sMin_Time->Fill( rt.sMinPho[k] , rt.seedTime[k] , weight );
		    sideband_nXtl_Eta->Fill( rt.nXtals[k], gP4_.Eta() , weight );
		    sideband_cscT_ecalT->Fill( rt.cscTime[k] , rt.seedTime[k] , weight );
		    sideband_photIso_cscdPhi->Fill( phIso , cscdPhi_ , weight ) ;
		    sideband_dtdPhidEta->Fill( rt.dtdPhi[k] , rt.dtdEta[k], weight );
                    double dtdR = sqrt( (rt.dtdPhi[k]*rt.dtdPhi[k]) + (rt.dtdEta[k]*rt.dtdEta[k]) ) ;
		    sideband_dtdR->Fill( dtdR , weight );
		    sideband_sMaj->Fill( rt.sMajPho[k] , weight ) ;
		    sideband_dPhi_MET_csc->Fill( dPhi_gMET, cscdPhi_ ) ;
		    if ( rt.seedTime[k] > 0 ) sideband_cscdPhi_u->Fill( cscdPhi_ , weight );
		    if ( rt.seedTime[k] < 0 ) sideband_cscdPhi_d->Fill( cscdPhi_ , weight );

		    if ( selectJets.size() == 0 ) sideband_dPhi_MET_Jet1->Fill( dPhi_gMET, dPhi_jMET, weight ) ;
		    if ( selectJets.size() == 1 ) sideband_dPhi_MET_Jet2->Fill( dPhi_gMET, dPhi_jMET, weight ) ;
		    if ( selectJets.size() >= 2 ) sideband_dPhi_MET_Jet3->Fill( dPhi_gMET, dPhi_jMET, weight ) ;
               }

               // The result of halo tagging and spike tagging 
               obsTime->Fill( rt.seedTime[k], weight );
               if ( !ghostTag ) pure_Time->Fill( rt.seedTime[k] , weight );

           }

           // ********************
           //   Signal sample - require Leading photon pt, Jet and MET cut 
           // ********************
           if ( selectPho[0].second.Pt() > 80. && met.E() > jetCuts[4] && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3]  ) {

		 sg_Time->Fill( rt.seedTime[k], weight );
                 if ( haloTag   ) sg_Time_halo->Fill( rt.seedTime[k] , weight ) ;
		 if ( spikeTag  ) sg_Time_spike->Fill( rt.seedTime[k] , weight ) ;
                 if ( cosmicTag ) sg_Time_cosmic->Fill( rt.seedTime[k] , weight ) ;

	         sg_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
		 sg_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
		 sg_sigIeta_Time->Fill( rt.sigmaIeta[k], rt.seedTime[k] , weight ) ;
		 sg_sMaj_Time->Fill( rt.sMajPho[k] , rt.seedTime[k] , weight );
		 sg_sMaj_Eta->Fill(  rt.sMajPho[k] ,     gP4_.Eta() , weight );
		 sg_sMin_Time->Fill( rt.sMinPho[k] , rt.seedTime[k] , weight );
		 sg_sMin_Eta->Fill(  rt.sMinPho[k] ,     gP4_.Eta() , weight );
		 sg_nXtl->Fill( rt.nXtals[k] , weight );
		 sg_nXtl_Eta->Fill( rt.nXtals[k] , gP4_.Eta(), weight );
		 sg_cscdPhi->Fill( cscdPhi_, weight  ) ;
		 sg_dPhi_MET_csc->Fill( dPhi_gMET, cscdPhi_ ) ;
	         sg_sMaj_sMin->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight );
		 if ( selectJets.size() == 1 ) sg_dPhi_MET_Jet1->Fill( dPhi_gMET, dPhi_jMET ) ;
		 if ( selectJets.size() == 2 ) sg_dPhi_MET_Jet2->Fill( dPhi_gMET, dPhi_jMET ) ;
		 if ( selectJets.size() >= 3 ) sg_dPhi_MET_Jet3->Fill( dPhi_gMET, dPhi_jMET ) ;
                 if ( !ghostTag ) {
		    sel_Time->Fill( rt.seedTime[k] , weight ) ;
		    sel_cHadIso_Time->Fill( rt.cHadIso[k] , rt.seedTime[k] , weight ) ;
		    sel_nHadIso_Time->Fill( nHIso , rt.seedTime[k] , weight ) ;
		    sel_photIso_Time->Fill( phIso , rt.seedTime[k] , weight ) ;
		    sel_photIso_sMaj->Fill( phIso , rt.sMajPho[k] , weight ) ;
		    sel_photIso_sMin->Fill( phIso , rt.sMinPho[k] , weight ) ;
		    sel_photIso_sigIeta->Fill( phIso , rt.sigmaIeta[k] , weight ) ;
	            sel_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
		    sel_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
		    sel_sMaj_Time->Fill( rt.sMajPho[k] , rt.seedTime[k] , weight );
		    sel_sMaj_Eta->Fill( rt.sMajPho[k] , gP4_.Eta() , weight );
		    sel_sMin_Time->Fill( rt.sMinPho[k] , rt.seedTime[k] , weight );
		    sel_sMin_Eta->Fill( rt.sMinPho[k] , gP4_.Eta() , weight );
                    if ( fabs( rt.seedTime[k] ) > 1.5 ) sel_weirdXtl->Fill( gP4_.Eta(), gP4_.Phi()  ) ;
		    if ( selectJets.size() == 1 ) sel_T_dPhi_gMET_1J->Fill( rt.seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() == 2 ) sel_T_dPhi_gMET_2J->Fill( rt.seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() >= 3 ) sel_T_dPhi_gMET_3J->Fill( rt.seedTime[k] , dPhi_gMET ) ;
		 }

           }

           // *******************
           //   Control samples - select pure photon sample
           //   -- check mistagging rate  
           // *******************
	   bool passCSSelect = false ;
	   if ( isData == 1 && fabs( rt.seedTime[k]) < 1. && rt.timeChi2[k] < 4 && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) passCSSelect = true ;
	   if ( isData == 0 && rt.seedTime[k] > 1.7 ) passCSSelect = true ;
	   if ( passCSSelect ) {
                  
                 cs_seedE_photE->Fill( rt.seedE[k] , gP4_.E(), weight ) ;   
                 cs_tChi2->Fill( rt.timeChi2[k] , weight ) ;
		 cs_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
		 cs_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
		 cs_dtdPhidEta->Fill( rt.dtdPhi[k] , rt.dtdEta[k], weight );
		 cs_sigIeta_Time->Fill( rt.sigmaIeta[k], rt.seedTime[k] , weight ) ;
		 cs_nXtl->Fill( rt.nXtals[k] , weight );
		 cs_swissX->Fill( rt.seedSwissX[k] , weight );
		 cs_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k] , weight );
		 cs_cscdPhi->Fill( cscdPhi_, weight  ) ;
		 cs_cHadIso_Time->Fill( rt.cHadIso[k] , rt.seedTime[k] , weight ) ;
		 cs_nHadIso_Time->Fill( nHIso , rt.seedTime[k] , weight ) ;
		 cs_photIso_Time->Fill( phIso , rt.seedTime[k] , weight ) ;
		 // Check mis-tagging rate from real photon
		 nCS_Eta->Fill( fabs(gP4_.Eta()) , weight )  ;
		 if ( haloTag ) nHL_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;
		 if ( spikeTag ) nSpk_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;
           }
       } // end of photon looping 
}


void BackgroundStudy::DrawAllHistograms() {

   qcdS->DrawHistograms( h_draw_ ) ;
   haloS->DrawHistograms( h_draw_ ) ;
   spikeS->DrawHistograms( h_draw_ ) ;
   cosmicS->DrawHistograms( h_draw_ ) ;
   DrawHistograms( h_draw_ ) ;

}

void BackgroundStudy::DrawHistograms( hDraw* h_draw ) {

   bool createDrawer = false ;
   if ( h_draw == NULL ) {
      h_draw = new hDraw( hfolder, plotType ) ;
      createDrawer = true ;
      cout<<" create drawing class " << endl ;
   }

   hfolder += "backgrounds/" ;
   gSystem->mkdir( hfolder.c_str() );
   h_draw->SetPath( hfolder ) ;

   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);

   h_draw->SetPlotStyle(false) ; // Turn off the stats box
   TLegend* leg3  = new TLegend(.6, .7, .9, .9 );
   leg3->AddEntry( h_EB_Time, " EB" , "L" ) ;
   leg3->AddEntry( h_EE_Time, " EE" , "L" ) ;
   leg3->AddEntry( h_EE_haloTime, "EE Halo-Tagged" , "L" ) ;
   h_draw->Draw(        h_EB_Time, "",  "Time from EB ", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend(  h_EE_Time, "",  0.85, 4 , 1 ) ;
   h_draw->DrawAppend(  h_EE_haloTime,  "h_EBEE_Time",  0.75, 6 , 1.,  leg3  ) ;

   h_draw->Draw(        h_EB_Time0, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time0->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time0, "h_EB_Time0", 0.75, 4 , 100./ max( 100., h_EE_Time0->Integral() ) ) ;
   h_draw->Draw(        h_EB_Time1, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time1->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time1, "h_EB_Time1", 0.75, 4 , 100./ max( 100., h_EE_Time1->Integral() ) ) ;
   h_draw->Draw(        h_EB_Time2, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time2->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time2, "h_EB_Time2", 0.75, 4 , 100./ max( 100., h_EE_Time2->Integral() ) ) ;

   // MET Efficiency 
   
   leg3->Clear() ;
   leg3->SetX1NDC(0.45) ;
   char leg_pf[50] , leg_hlt[50] ;
   double pf_H  = h_pfMET->Integral(25,100 ) ;
   double pf_A  = h_pfMET->Integral() ;
   double hlt_H = h_hltMET->Integral(25,100 ) ;
   double hlt_A = h_hltMET->Integral() ;
   sprintf( leg_pf,  " PF MET : %.1f/%.1f = %.2f ",  pf_H,  pf_A , pf_H/pf_A ) ;
   sprintf( leg_hlt, " HLT MET: %.1f/%.1f = %.2f ", hlt_H, hlt_A , hlt_H/hlt_A ) ;
   leg3->AddEntry( h_pfMET, leg_pf , "L" ) ;
   leg3->AddEntry( h_hltMET, leg_hlt , "L" ) ;
   h_draw->Draw(        h_hltMET, "",  " MET ", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend(  h_pfMET,  "h_MET",  0.75, 4 , 1.,  leg3  ) ;
   leg3->SetX1NDC(0.6) ;
   
   //h_draw->SetHistoInfo(1) ;

   gStyle->SetOptStat("e");
   h_draw->Draw2D( h_Eta_Phi,     "h_Eta_Phi",      "#eta", "#phi ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Eta_Time1,   "h_Eta_Time1",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Eta_Time2,   "h_Eta_Time2",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Eta_Time3,   "h_Eta_Time3",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Eta_Time4,   "h_Eta_Time4",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   gStyle->SetOptStat("");
   h_draw->Draw2D( h_Eta_Time,    "h_Eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Phi_Time,    "h_Phi_Time",    "#phi", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_cscdPhi_Time,"h_cscdPhi_Time","d#phi", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cscdPhi_cscTime,"h_cscdPhi_cscTime","d#phi", "CSC Time (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cHadIso_Time, "h_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_nHadIso_Time, "h_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_photIso_Time, "h_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_seedE_Time,   "h_seedE_Time",   " Seed Energy (GeV)", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EB,   "h_sMaj_Time_EB",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EB,   "h_sMin_Time_EB",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMaj_sigIeta_EB,"h_sMaj_sigIeta_EB",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_sigIeta_EB,"h_sMin_sigIeta_EB",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EB,"h_sigIeta_Time_EB","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EB,     "h_Pt_Time_EB", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EB,    "h_MET_Time_EB", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_hltMET_Time_EB, "h_hltMET_Time_EB", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cscdPhi_rho,    "h_cscdPhi_rho", "#Delta#Phi( cscSeg, #gamma) ", "#rho", "logZ", 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EE,   "h_sMaj_Time_EE",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EE,   "h_sMin_Time_EE",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMaj_sigIeta_EE,"h_sMaj_sigIeta_EE",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_sigIeta_EE,"h_sMin_sigIeta_EE",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EE,"h_sigIeta_Time_EE","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EE,     "h_Pt_Time_EE", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EE,    "h_MET_Time_EE", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_hltMET_Time_EE, "h_hltMET_Time_EE", "MET", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_Pt_MET,      "h_Pt_MET", "P_T", " MET", "logZ" , 8 ) ;
   h_draw->Draw2D( h_sMaj_Eta,    "h_sMaj_Eta",    "sMaj", "#eta ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_Phi,    "h_sMaj_Phi",    "sMaj", "#phi ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_sMin_EB,"h_sMaj_sMin_EB",   "sMaj", "sMin ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_nXtl_Eta,    "h_nXtl_Eta",    "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw2D( h_nXtl_Pt_EB,  "h_nXtl_Pt_EB",     "N crystals", "P_{T}", "logZ", 8  ) ;
   
   h_draw->Draw2D( h_jet_phot_Time, "h_jet_phot_Time", "jet time", "photon time", "logZ", 8  ) ;
   h_draw->Draw(   h_jetTime,      "h_jetTime",    " jet time ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_jetTime,      "h_jetTimeErr", " jet time error", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h_met_met1,     "h_met_met1",     "MET", "MET1", "logZ", 8  ) ;
   h_draw->Draw2D( h_met_met2,     "h_met_met2",     "MET", "MET2", "logZ", 8  ) ;
   h_draw->Draw(   h_nPhoton,      "h_nPhoton", " N Selected Photons ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_nVtx,         "h_nVtx",    " N of vertex ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( h_nVtx_tChi2,   "h_nVtx_tChi2", "N of vertex", "#chi2_{time}", "logZ", 8  ) ;

   h_draw->Draw2D( abcd_Pt_Time,   "abcd_Pt_Time", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET_Time,  "abcd_MET_Time", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_T_sMET2_1J,  "abcd_MET1_T_sMET2_1J", "MET1 ( MET2 < 60 )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_T_bMET2_1J,  "abcd_MET1_T_bMET2_1J", "MET1 ( MET2 > 60 )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_T_sMET2_2J,  "abcd_MET1_T_sMET2_2J", "MET1 ( MET2 < 60 )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_T_bMET2_2J,  "abcd_MET1_T_bMET2_2J", "MET1 ( MET2 > 60 )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_Time_closure1,  "abcd_MET1_Time_closure1", "MET1 ( 1-jet closure )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET1_Time_closure2,  "abcd_MET1_Time_closure2", "MET1 ( 2-jet closure )", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET2_Time,  "abcd_MET2_Time", "MET2", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_NJet_Time, "abcd_NJet_Time", "NJet", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( sg_Eta_Time,    "sg_Eta_Time",    "#eta", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sg_Phi_Time,    "sg_Phi_Time",    "#phi", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sg_sigIeta_Time,"sg_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_nXtl_Eta,    "sg_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw(   sg_nXtl,        "sg_nXtl",      "N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   sg_cscdPhi,     "sg_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( sg_sMaj_Time,   "sg_sMaj_Time",  "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMin_Time,   "sg_sMin_Time",  "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMaj_Eta,    "sg_sMaj_Eta",   "sMaj", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMin_Eta,    "sg_sMin_Eta",   "sMin", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sg_dPhi_MET_csc, "sg_dPhi_MET_csc",  "dPhi( photon, MET)", " dPhi( photon, cscseg)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet1, "sg_dPhi_MET_Jet1",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet2, "sg_dPhi_MET_Jet2",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet3, "sg_dPhi_MET_Jet3",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_sMaj_sMin,   "sg_sMaj_sMin",  "sMaj", "sMin ",  "logZ", 8 ) ;

   // ========================
   //   Comparison Plots for halo/spike/comsic/control/signal
   // ========================

   /// Timing plot for signal selection
   gPad->SetGridx() ;
   TLegend* leg2  = new TLegend(.65, .6, .9, .9 );
   leg2->Clear() ;
   leg2->AddEntry( sg_Time,        " Signal Selection" , "L" ) ;
   leg2->AddEntry( sel_Time,       " No background" , "L" ) ;
   leg2->AddEntry( sg_Time_halo,   " HaloTagged" , "L" ) ;
   leg2->AddEntry( sg_Time_spike,  " SpikeTagged" , "L" ) ;
   leg2->AddEntry( sg_Time_cosmic, " CosmicTagged" , "L" ) ;
   h_draw->Draw(       sg_Time,       "",  "Ecal Time (ns) ", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( sel_Time,      "", 0.8, 2, 1   ) ;
   h_draw->DrawAppend( sg_Time_halo,  "", 0.65, 4, 1  ) ;
   h_draw->DrawAppend( sg_Time_spike, "", 0.5, 6, 1   ) ;
   h_draw->DrawAppend( sg_Time_cosmic, "sg_Time", 0.35, 8, 1, leg2  ) ;
   gPad->SetGridx() ;

   /// Timing plot for no selection
   //gStyle->SetOptStat("e");
   gPad->SetGridx() ;
   leg2->Clear() ;
   leg2->AddEntry( obsTime,     "All" , "L" ) ;
   leg2->AddEntry( pure_Time,   "Final" , "L" ) ;
   leg2->AddEntry( haloS->halo_Time,   "TaggedHalo" , "L" ) ;
   leg2->AddEntry( spikeS->spike_Time,  "TaggedSpike" , "L" ) ;
   leg2->AddEntry( cosmicS->cosmic_Time, "TaggedCosmic" , "L" ) ;
   h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( pure_Time,  "", 0.85, 2, 1  ) ;
   h_draw->DrawAppend( haloS->halo_Time,  "", 0.75, 4, 1  ) ;
   h_draw->DrawAppend( spikeS->spike_Time,  "", 0.65, 6, 1  ) ;
   h_draw->DrawAppend( cosmicS->cosmic_Time, "TimeForAll", 0.55, 8, 1, leg2  ) ;

   /// Jet multiplicity 
   leg2->Clear() ;
   leg2->AddEntry( nJets_center, "RealPhotons" , "L" ) ;
   leg2->AddEntry( nJets_halo,   "HaloTagged" , "L" ) ;
   leg2->AddEntry( nJets_spike,  "SpikeTagged" , "L" ) ;
   leg2->AddEntry( nJets_cosmic, "CosmicTagged" , "L" ) ;
   h_draw->Draw(       nJets_center, "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( nJets_halo,   "", 0.85, 2, 1  ) ;
   h_draw->DrawAppend( nJets_spike,   "", 0.75, 4, 1  ) ;
   h_draw->DrawAppend( nJets_cosmic, "NJets_All", 0.6, 8, 1, leg2  ) ;

   /// Time Chi2
   /*
   leg2->Clear() ;
   leg2->AddEntry( h_tChi2,     "Normal" , "L" ) ;
   leg2->AddEntry( haloS->halo_tChi2,   "Halo"   , "L" ) ;
   leg2->AddEntry( haloS->noHalo_tChi2,  "Spike"  , "L" ) ;
   leg2->AddEntry( cosmicS->cosmic_tChi2, "Cosmic" , "L" ) ;
   h_draw->Draw(       h_tChi2,       "", "#Chi2 of ECAL time", "",  "logY" , 0.95, 1.  ) ;
   h_draw->DrawAppend( haloS->halo_tChi2,     "",       0.85, 2,  h_tChi2->Integral()/max(1., haloS->halo_tChi2->Integral()   )) ;
   h_draw->DrawAppend( haloS->noHalo_tChi2,   "",       0.75, 6,  h_tChi2->Integral()/max(1., haloS->noHalo_tChi2->Integral() )) ;
   h_draw->DrawAppend( cosmicS->cosmic_tChi2, "h_tChi2", 0.65, 8, h_tChi2->Integral()/max(1., cosmicS->cosmic_tChi2->Integral()), leg2) ;
   */
   

   /// Time from final selections
   gStyle->SetOptStat("e");
   gStyle->SetStatW(0.25);
   gStyle->SetStatH(0.2);
   gStyle->SetTextSize(0.075);
   TH1D* selTime = sel_Eta_Time->ProjectionY("selTime"  ) ;
   h_draw->SetFitParameter( "Gaus", selTime, -1.5, 1.5, 3, 4 );
   h_draw->FitNDraw( selTime, "selTime", "Photon Time (ns)", "", "logY", 0.95, 1 ) ;

   gStyle->SetOptStat("");
   h_draw->Draw2D( sel_weirdXtl,   "sel_weirdXtl",   "#eta", "Phi",  "", 8  ) ;
   h_draw->Draw2D( sel_Eta_Time,   "sel_Eta_Time",   "#eta", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sel_Phi_Time,   "sel_Phi_Time",   "#phi", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sel_sMaj_Time,  "sel_sMaj_Time",  "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMin_Time,  "sel_sMin_Time",  "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMaj_Eta,   "sel_sMaj_Eta",   "sMaj", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMin_Eta,   "sel_sMin_Eta",   "sMin", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sel_T_dPhi_gMET_1J, "sel_T_dPhi_gMET_1J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( sel_T_dPhi_gMET_2J, "sel_T_dPhi_gMET_2J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( sel_T_dPhi_gMET_3J, "sel_T_dPhi_gMET_3J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( sel_cHadIso_Time,"sel_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sel_nHadIso_Time,"sel_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sel_photIso_Time,"sel_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sel_photIso_sMaj,"sel_photIso_sMaj",   " Photon Iso", "sMajor", "logZ" , 8 ) ;
   h_draw->Draw2D( sel_photIso_sMin,"sel_photIso_sMin",   " Photon Iso", "sMinor", "logZ" , 8 ) ;
   h_draw->Draw2D( sel_photIso_sigIeta,"sel_photIso_sigIeta",   " Photon Iso", "sigma_iEta", "logZ" , 8 ) ;

   h_draw->Draw2D( cs_Eta_Time,    "cs_Eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( cs_Phi_Time,    "cs_Phi_Time",    "#phi", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( cs_sigIeta_Time,"cs_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_sMaj_sMin,    "cs_sMaj_sMin",  "s_{Major}", "s_{Minor}", "logZ", 8  ) ;
   h_draw->Draw2D( cs_cHadIso_Time,"cs_cHadIso_Time", " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_nHadIso_Time,"cs_nHadIso_Time", " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_photIso_Time,"cs_photIso_Time", " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_dtdPhidEta,  "cs_dtdPhidEta",   "#Delta#eta", "#Delta#phi", "logZ", 8  ) ;
   h_draw->Draw2D( cs_seedE_photE, "cs_seedE_photE",  "seed E (GeV)", " photon E (GeV)", "logZ", 8  ) ;
   h_draw->Draw(   cs_swissX,      "cs_swissX",       "Swiss-X ", "", "logY", 0.95, 1 ) ;

   gStyle->SetOptStat(kFALSE);
   h_draw->Draw2D( sideband_photIso_cscdPhi,"sideband_photIso_cscdPhi",  " Photon Iso", "d#Phi", "logZ" , 8 ) ;
   h_draw->Draw2D( sideband_sMin_Time, "sideband_sMin_Time", "sMin", "EcalTime (ns)",  "") ;
   h_draw->Draw2D( sideband_sMaj_Time, "sideband_sMaj_Time", "sMaj", "EcalTime (ns)",  "") ;
   h_draw->Draw2D( sideband_sMaj_Phi,  "sideband_sMaj_Phi",  "sMaj", " #phi",  ""  ) ;
   h_draw->Draw2D( sideband_sMaj_sMin, "sideband_sMaj_sMin", "sMaj", " sMin",  ""  ) ;
   h_draw->Draw2D( sideband_sMaj_Eta,  "sideband_sMaj_Eta",  "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( sideband_nXtl_Eta,  "sideband_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw2D( sideband_cscT_ecalT,"sideband_cscT_ecalT",  "CSC Time", "Ecal Time", "logZ", 8  ) ;
   h_draw->Draw(   sideband_sMaj,      "sideband_sMaj",    " sMajor ", "", "", 0.95, 1 ) ;
   h_draw->Draw(   sideband_dtdR,      "sideband_dtdR", "#Delta R( dtSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( sideband_Pt_nJet,   "sideband_Pt_nJet", "P_{T}", " N Jets", "logZ", 8  ) ;
   h_draw->Draw2D( sideband_dtdPhidEta,"sideband_dtdPhidEta", "#Delta#phi", "#Delta#eta", "logZ", 8  ) ;
   h_draw->Draw2D( sideband_dPhi_MET_csc, "sideband_dPhi_MET_csc",  "dPhi( photon, MET)", " dPhi( photon, cscseg)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet1, "sideband_dPhi_MET_Jet1",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet2, "sideband_dPhi_MET_Jet2",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet3, "sideband_dPhi_MET_Jet3",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   delete leg2 ;


   /// CSC dPhi Comparison - control and haloControl
   leg2  = new TLegend(.62, .7, .85, .9 );
   leg2->Clear() ;
   cs_cscdPhi->SetLineWidth(2) ;
   cs_cscdPhi->SetFillColor(7) ;
   haloS->haloCS_cscdPhi->SetLineWidth(2) ;
   //sideband_cscdPhi_u->SetLineWidth(2) ;
   //sideband_cscdPhi_d->SetLineWidth(2) ;

   leg2->AddEntry( cs_cscdPhi,              "Nominal" , "F" ) ;
   leg2->AddEntry( haloS->haloCS_cscdPhi,   "Halo CS" , "L" ) ;
   //leg2->AddEntry( sideband_cscdPhi_u, "Late-timing" , "L" ) ;
   //leg2->AddEntry( sideband_cscdPhi_d, "Early-timing" , "L" ) ;

   h_draw->Draw(        cs_cscdPhi,  "", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 4 ) ;
   //h_draw->DrawAppend( sideband_cscdPhi_d,  "",  0.9, 6 ) ;
   //h_draw->DrawAppend( sideband_cscdPhi_u,  "cs_side_cscdPhi",  0.85, 2, 1, leg2 ) ;
   h_draw->DrawAppend( haloS->haloCS_cscdPhi,  "cs_side_cscdPhi",  0.85, 2, 100, leg2 ) ;

 
   /// Number of good crystals   
   leg2->Clear() ;
   spikeS->spikeCS_nXtl->SetLineWidth(2) ;
   haloS->halo_nXtl->SetLineWidth(2) ;
   cs_nXtl->SetLineWidth(2) ;
   cs_nXtl->SetFillColor(7) ;

   leg2->AddEntry( spikeS->spikeCS_nXtl,  "Spike CS" , "L" ) ;
   leg2->AddEntry( haloS->halo_nXtl,      "Halo ", "L" ) ;
   leg2->AddEntry(          cs_nXtl,      "|t| < 1 ns", "F" ) ;

   h_draw->Draw(                cs_nXtl,  "", "N of crystals", "", "", 0.95, 4, 100/ cs_nXtl->Integral() ) ;
   h_draw->DrawAppend( haloS->halo_nXtl,  "",    0.85, 1,                       100/ haloS->halo_nXtl->Integral()  ) ;
   h_draw->DrawAppend( spikeS->spikeCS_nXtl,  "spikeCS_nXtl",    0.85, 2,       100/ spikeS->spikeCS_nXtl->Integral(), leg2 ) ;
   
   gPad->SetGridx() ;
   gStyle->SetOptStat("");

   // Final Ghost mis-tagging rate
   if ( nCS_Eta->Integral() > 5 ) {
      TCanvas* c_0 = new TCanvas("c_0","", 800, 700);
      c_0->SetFillColor(10);
      c_0->SetFillColor(10);
      c_0->SetLeftMargin(0.16);
      c_0->SetRightMargin(0.08);
      c_0->SetTopMargin(0.1);
      c_0->SetBottomMargin(0.12);

      c_0->cd() ;
      TGraphAsymmErrors* sMistag = new TGraphAsymmErrors();
      sMistag->Divide( nSpk_Eta, nCS_Eta );

      cout<<" ======= Spike MisTagging Rate ====== "<<endl ;
      double allSpkMis = nSpk_Eta->Integral() /  nCS_Eta->Integral() ;
      printf(" All  = %.5f \n",  allSpkMis ) ;
      Double_t* spike_mA = sMistag->GetY() ;
      spikeMis.clear() ;
      for (int i=0; i< 5 ; i++ ) {
          printf(" (%d)  = %.5f \n", i, spike_mA[i] ) ;
          spikeMis.push_back( spike_mA[i] ) ;    
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
      TString plotname = hfolder + "MisTagging_Spike."+plotType ;
      c_0->Print( plotname ) ;

      c_0->Clear() ;
      TGraphAsymmErrors* hMistag = new TGraphAsymmErrors();
      hMistag->Divide( nHL_Eta, nCS_Eta );

      cout<<" ======= Halo MisTagging Rate ====== "<<endl ;
      double allHaloMis = nHL_Eta->Integral() /  nCS_Eta->Integral() ;
      printf(" All  = %.5f \n",  allHaloMis ) ;
      Double_t* halo_mA  = hMistag->GetY() ;
      haloMis.clear() ;
      for (int i=0; i< 5 ; i++ ) {
          printf(" (%d)  = %.5f \n", i, halo_mA[i] ) ;
          haloMis.push_back( halo_mA[i] ) ;
      }

      hMistag->SetMaximum( 0.06 );
      hMistag->SetMinimum( 0.01 );
      hMistag->SetMarkerStyle(22);
      hMistag->SetMarkerColor(4);
      hMistag->SetLineWidth(2);
      hMistag->GetYaxis()->SetTitleOffset(1.9);
      hMistag->GetXaxis()->SetTitle( "|#eta|" ) ;
      hMistag->GetYaxis()->SetTitle(" Mis-Tagging Rate ") ;
      hMistag->Draw("AP");
      c_0->Update();
      plotname = hfolder + "MisTagging_Halo."+plotType ;
      c_0->Print( plotname ) ;

      /*
      if ( isData == 1 ) {

      cout<<" ======= Spike Tagging Efficiency ====== "<<endl ;
      c_0->Clear() ;
      TGraphAsymmErrors* spike_Eff = new TGraphAsymmErrors();
      spike_Eff->Divide( spike_Eta[1], spike_Eta[0] );
      double allSpkEff = spike_Eta[1]->Integral() /  spike_Eta[0]->Integral() ;
      printf(" All  = %.5f \n",  allSpkEff ) ;
      Double_t* spike_eA  = spike_Eff->GetY() ;
      spikeEff.clear() ;
      for (int i=0; i< 5 ; i++ ) {
          if ( spike_eA == NULL ) break ;
          printf(" (%d)  = %.5f \n", i, spike_eA[i] ) ;
          spikeEff.push_back( spike_eA[i] ) ;
      }

      spike_Eff->SetMaximum( 1.1 );
      spike_Eff->SetMinimum( 0.0 );
      spike_Eff->SetMarkerStyle(22);
      spike_Eff->SetMarkerColor(4);
      spike_Eff->SetLineWidth(2);
      spike_Eff->GetYaxis()->SetTitleOffset(1.9);
      spike_Eff->GetXaxis()->SetTitle( "|#eta|" ) ;
      spike_Eff->GetYaxis()->SetTitle(" Efficiency ") ;
      spike_Eff->Draw("AP");
      c_0->Update();
      plotname = hfolder + "Efficiency_Spike."+plotType ;
      c_0->Print( plotname ) ;
      }
   */
   }

   //ABCD( hBg_A, hBg_B, hBg_C, hBg_D, hBg_E, hBg_F ) ;
   TH3D* ACols[] = { hCol_A, hCol_B, hCol_C, hCol_D, hCol_E, hCol_F } ; 
   vector<TH3D*> hColls( ACols, ACols+6 ) ;

   TH3D* AMIBs[] = { hBg_A, hBg_B, hBg_C, hBg_D, hBg_E, hBg_F } ; 
   vector<TH3D*> hMIBs( AMIBs, AMIBs+6 ) ;
 
   select->ABCD_ABCD( hColls, hMIBs ) ;
   if ( createDrawer ) delete h_draw ;
}

// ABCD for collision , usually under MET1 > 60 GeV , using Time ( |t| < 2 , t > 3 ) and MET2 ( MET2 > 60 or MET2 < 60 )
// Estimate collision background in B or D region (MET2 > 60 && MET1 > 60 GeV )
//  t  > 3 -->  hF_C : MET2 < 60  , hF_D : MET2 > 60  	
// |t| < 2 -->  hF_A : MET2 < 60  , hF_B : MET2 > 60  	
/*
vector<double> BackgroundStudy::ABCD_Collision( TH3D* hF_A, TH3D* hF_B, TH3D* hF_C, TH3D* hF_D ) {

   printf("\n  =========== ABCD Method for Collision ============= \n") ;
   cout<<" ===  A  === "<<endl ;
   double rA = GetEstimation( hF_A ) ;
   cout<<" ===  B  === "<<endl ;
   double rB = GetEstimation( hF_B ) ;
   cout<<" ===  C  === "<<endl ;
   double rC = GetEstimation( hF_C ) ;
   cout<<" ===  D  === "<<endl ;
   double rD = GetEstimation( hF_D ) ;

   pair<double,double> errAB = MathTools::ErrAovB( rA, rB ) ;
   double predict = ( rA > 0. ) ? rC * ( rB / rA ) : 0. ; 

   double sBA_u = errAB.first ;
   double sBA_d = errAB.second ;

   double s2u = (sBA_u*sBA_u)*(rC*rC) + (rC*rB*rB)/(rA*rA) ;
   double s2d = (sBA_d*sBA_d)*(rC*rC) + (rC*rB*rB)/(rA*rA) ;
   
   printf(" Predicted Collision background : %.2f + %.2f - %.2f ", predict , sqrt(s2u) , sqrt(s2d) ) ;
   printf(" Observed = %.2f \n", rD ) ;
 
   vector<double> vals ;
   vals.push_back( predict );
   vals.push_back( sqrt(s2u) );
   vals.push_back( sqrt(s2d) );
   return vals ;
}

 // x is eta region , each is 0.28 , y is different sample, 0:total, 1:halo, 2: spike 3: cosmic
vector<double> BackgroundStudy::ABCD( TH3D* hA, TH3D* hB, TH3D* hC, TH3D* hD, TH3D* hE, TH3D* hF ) {

   // Tagging efficiency 
   Input->GetParameters("UseInFlight",   &useInFlight ) ;
   if ( useInFlight == 0 || haloEff.size() < 5 || spikeEff.size() < 5 || haloMis.size() < 5 || spikeMis.size() < 5 ) {
      printf(" Get Efficiency and fake rate from Datacard !! \n") ;
      Input->GetParameters("HaloEff",    &haloEff ) ;
      Input->GetParameters("SpikeEff",   &spikeEff ) ;
      Input->GetParameters("CosmicEff",  &cosEff ) ;
      // Mis-tag rate
      Input->GetParameters("HaloFake",   &haloMis ) ;
      Input->GetParameters("SpikeFake",  &spikeMis ) ;
      Input->GetParameters("CosmicFake", &cosMis ) ;
   }
 
   //  GetEstimation returns QCD components
   cout<<" ===  E  === "<<endl ;
   double rE = GetEstimation( hE ) ;
   cout<<" ===  F  === "<<endl ;
   double rF = GetEstimation( hF ) ;
   //printf("=== D/F (%.2f/%.2f) = %.2f  + %.4f - %.4f \n", rF, rE, rF/rE, errEF.first, errEF.second ) ;
   cout<<" ===  A  === "<<endl ;
   double rA = GetEstimation( hA ) ;
   cout<<" ===  B  === "<<endl ;
   double rB = GetEstimation( hB ) ;
   cout<<" ===  C  === "<<endl ;
   double rC = GetEstimation( hC ) ;
   cout<<" ===  D  === "<<endl ;
   double rD = GetEstimation( hD ) ;

   pair<double,double> errAB = MathTools::ErrAovB( rB, rA ) ;
   pair<double,double> errCD = MathTools::ErrAovB( rD, rC ) ;
   pair<double,double> errFD = MathTools::ErrAovB( rD, rF ) ;
   double predict = ( rA > 0. ) ? rC * ( rB / rA ) : 0. ; 

   if ( rA < 0.0001 ) { cout<<" Residual Background ABCD Fail ! " <<endl ;
   } else {
          printf(" B/A (%.2f/%.2f) = %.2f  + %.2f - %.2f \n", rB, rA, rB/rA, errAB.first , errAB.second ) ;
          printf(" D/C (%.2f/%.2f) = %.2f  + %.2f - %.2f \n", rD, rC, rD/rC, errCD.first , errCD.second ) ;
          printf(" D/F (%.2f/%.2f) = %.8f  + %.8f - %.8f \n", rD, rF, rD/rF, errFD.first , errFD.second ) ;
   }

   printf(" Observe :%.2f -> Predict : %.2f \n", rD, predict ) ;

   vector<double> vals ;
   vals.push_back( rA ) ;
   vals.push_back( rB ) ;
   vals.push_back( rC ) ;
   vals.push_back( rD ) ;
   vals.push_back( rE ) ;
   vals.push_back( rF ) ;
   return vals ;
}

void BackgroundStudy::ABCD_ABCD() {

     printf("\n ####### MET2 < 60 ########## \n") ;
     vector<double> abcdef_  = ABCD( hCol_A, hCol_B, hCol_C, hCol_D, hCol_E, hCol_F ) ;
     printf("\n ####### MET2 > 60 ########## \n") ;
     vector<double> abcdef  = ABCD( hBg_A, hBg_B, hBg_C, hBg_D, hBg_E, hBg_F ) ;
     printf("\n ####### Q_D ########## \n") ;
     vector<double> colD    = ABCD_Collision( hCol_F, hBg_F, hCol_D, hBg_D ) ;
     printf("\n ####### Q_B ########## \n") ;
     vector<double> colB    = ABCD_Collision( hCol_F, hBg_F, hCol_B, hBg_B ) ;

     double predict =  (abcdef[1] - colB[0])*(abcdef[2]/abcdef[0]) + colD[0] ;

     pair<double,double> errB     = MathTools::ErrApnB( abcdef[1] , colB[0] , -1, -1, colB[1], colB[2] ) ;
     pair<double,double> errCovA  = MathTools::ErrAovB( abcdef[2], abcdef[0]) ;
     pair<double,double> errBCovA = MathTools::ErrAxB( (abcdef[1] - colB[0]), (abcdef[2]/abcdef[0])
                                                     , errB.first, errB.second, errCovA.first, errCovA.second ) ;
     pair<double,double> errFinal = MathTools::ErrApnB( (abcdef[1] - colB[0])*(abcdef[2]/abcdef[0]), colD[0]
                                                     , errBCovA.first, errBCovA.second, colD[1], colD[2] ) ;

   printf("\n ================ Final Result =================== \n") ;
   printf(" Observe :%.2f -> Predict : %.4f + %.4f - %.4f \n", abcdef[3], predict, errFinal.first , errFinal.second ) ;
}

// Return the sum of spike and halo component or QCD component of background
// xbin : 5 eta region ( 0 ~ 1.4 ) , bin width : 0.28
// ybin : [bin1]: Total count , [bin2]: Halo , [bin3]: Spike, [bin4]: Cosmic
double BackgroundStudy::GetEstimation( TH3D* hCount, bool getQCD ) {

   double ghostB = 0 ;
   double Bg_exp = 0 ; 
   double residual = 0 ;

   printf("| eta |    spike    |     halo    |   cosmic    |  unkown  | Total |\n" ) ;
   // 5 different eta region
   float sum[9] = {0.} ;
   for ( int i=0; i< 5; i++ ) {
       // 3 jet multiplicity
       double nB = 0 ; 
       double nH = 0 ;
       double nS = 0 ;
       double nC = 0 ;
       for ( int j=1; j<4; j++ ) { 

           if ( j-1 < jetCuts[2] || j-1 > jetCuts[3] ) continue ;
           
	   nB += hCount->GetBinContent( i+1, 1, j ) ; // total number in control region 
	   nH += hCount->GetBinContent( i+1, 2, j ) ; // number of halo tagged in control region
	   nS += hCount->GetBinContent( i+1, 3, j ) ; // number of spike tagged in control region
	   nC += hCount->GetBinContent( i+1, 4, j ) ; // number of cosmic tagged in control region
       }

       //printf(" (%d) -> %.2f , %.2f , %.2f , %.2f \n", i, nB, nH, nS, nC ) ;

       vector<double> bgV = GetComponent( i, nB, nH, nS, nC ) ;
       ghostB   += bgV[0] ;  // spike
       ghostB   += bgV[1] ;  // halo
       ghostB   += bgV[2] ; // cosmic
       residual += bgV[3] ; // qcd
       Bg_exp   += nB ;
       printf("|  %d  | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) |  %4.f |\n", 
                   i,     bgV[0], nS,   bgV[1], nH,    bgV[2], nC,    bgV[3], nB-nS-nH-nC ,    nB ) ;

       sum[0] += bgV[0] ;
       sum[1] +=     nS ;
       sum[2] += bgV[1] ;
       sum[3] +=     nH ;
       sum[4] += bgV[2] ;
       sum[5] +=     nC ;
       sum[6] += bgV[3] ;
       sum[7] += nB-nS-nH-nC ;
       sum[8] +=     nB ;

   }
       printf("| sum | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) |  %4.f |\n", 
                        sum[0],sum[1], sum[2],sum[3], sum[4],sum[5], sum[6],sum[7], sum[8]  ) ;
  
   printf("|----------------------------------------------------------------------\n") ;
   printf("| Background :  Unknown:%.2f , halo+spike+cosmic = %.2f from total %.1f \n", residual, ghostB, Bg_exp ) ;
   printf("|----------------------------------------------------------------------\n") ;

   if ( getQCD ) return residual ;
   else          return Bg_exp ;
}

// Return the background components in background control region ( MET < 60 GeV )
// Return [0]:spike , [1]:halo , [2]:QCD
// Input : number of event in background control region at t > 2 ns region 
// B12 : total background , h_B12 : halo-tagged events , s_B12 : spike tagged events
vector<double> BackgroundStudy::GetComponent( int eta_i, int B12, int h_B12, int s_B12, int c_B12 ) {

  vector<double> result = GetComponent( eta_i, (double)B12, (double)h_B12, (double)s_B12 , (double)c_B12 ) ;
  return result ;

}

// Get halo/spike/QCD component using tagging efficiency and mis-tagging rate 
vector<double> BackgroundStudy::GetComponent( int eta_i, double B0 , double h_B, double s_B, double c_B ) {

       double h = haloEff[ eta_i ] ;  // halo
       double s = spikeEff[ eta_i ] ;  // spike
       double c = cosEff[ eta_i ] ;  // comsic
       
       double m = haloMis[ eta_i ] ;   // halo
       double n = spikeMis[ eta_i ] ;   // spike
       double o = cosMis[ eta_i ] ;   // cosmic

       // cosmic content 
       double C_ = (c_B - o*B0 ) / ( c - o ) ; 
       C_ = ( C_ < 0. ) ? 0 : C_ ;
       // spike content
       double S_ = (s_B - n*B0 ) / ( s - n ) ; 
       S_ = ( S_ < 0. ) ? 0 : S_ ;
       // halo content 
       double H_ = (h_B - m*B0 ) / ( h - m ) ; 
       H_ = ( H_ < 0. ) ? 0 : H_ ;
       // QCD content 
       double Q_ = (double)(B0) - S_ - H_ - C_;
       Q_ = ( Q_ < 0. ) ? 0 : Q_ ;

       //printf("(%d) B12 %d = (S12: %.2f ) + ( H12: %.2f ) + ( Q12: %.2f )\n ", eta_i, B12, S12, H12, Q12 ) ;

       vector<double> BG12 ;
       BG12.push_back( S_ ) ;
       BG12.push_back( H_ ) ;
       BG12.push_back( C_ ) ;
       BG12.push_back( Q_ ) ;
       return BG12 ;
}
*/


TLorentzVector BackgroundStudy::JetVectorSum( vector<objID>& jetV ) {

    double px(0.) , py(0.), pz(0.) , E(0.) ;
    for ( size_t i=0; i< jetV.size() ; i++ ) {
        px += jetV[i].second.Px() ;
        py += jetV[i].second.Py() ;
        pz += jetV[i].second.Pz() ;
         E += jetV[i].second.E() ;
    }
    TLorentzVector jet_sum( px, py, pz, E) ;
    return jet_sum ;
}

// eta = - ln ( tan theta/2 ) , theta = 2 atan( e ^ -eta )
// p0 : the falling rate, p1 : t scale,  p2: t shift
Double_t BackgroundStudy::HaloFunction( Double_t* eta, Double_t* par  ) {

     double c  = 30. ; // speed of light : 30 cm/ns
     double eta_func =  par[0]*eta[0] ;
     double t0 =  129 / (-2*c) ;
     Double_t T  = t0 * exp( eta_func )*par[1]  + par[2]  ; 

     return T ;
}

