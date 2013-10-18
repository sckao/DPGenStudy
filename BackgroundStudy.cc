#include "BackgroundStudy.h"
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

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  h_draw = new hDraw( datacardfile ) ;

  SkipEvents = 0 ;
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("SkipEvents",    &SkipEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 

  writeHist = false ;
}


BackgroundStudy::~BackgroundStudy(){

  theFile->Close() ;
  cout<<" File closed ! "<<endl ;

  delete select ;
  delete Input ;
  delete h_draw ;
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

  h_Eta_Time->Write() ;
  h_Phi_Time->Write() ;
  h_cscdPhi_Time->Write() ;
  h_cscdPhi_cscTime->Write() ;
  h_ecalT_cscT->Write() ;
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
  h_cHadIso_Time->Write() ;
  h_nHadIso_Time->Write() ;
  h_photIso_Time->Write() ;
  h_cscdPhi_rho->Write() ;
  h_Time_EB->Write() ;
  h_haloTime_EE->Write() ;
  h_Time_EE->Write() ;
  h_haloTime_EE->Write() ;

  h_Time_nZ0->Write() ;
  a_Z0->Write() ;
  b_Z0->Write() ;
  c_Z0->Write() ;
  d_Z0->Write() ;
  h_Z0->Write() ;

  a_nVtx->Write() ;
  b_nVtx->Write() ;
  c_nVtx->Write() ;
  d_nVtx->Write() ;
  l_nVtx->Write() ;
  h_nVtx->Write() ;

  h_sMaj_Eta->Write() ;
  h_sMaj_Phi->Write() ;
  h_sMaj_sMin_EB->Write() ;
  h_nXtl_Eta->Write() ;
  h_nXtl_Pt_EB->Write() ;

  sg_Eta_Time->Write() ;
  sg_Eta_Time_halo->Write() ;
  sg_Eta_Time_spike->Write() ;
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
  sg_sMaj_sigIeta->Write() ;
  sg_sMin_sigIeta->Write() ;
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
  cs_sMaj_sMin->Write() ;
  cs_cscdPhi->Write() ;
  cs_cHadIso_Time->Write() ;
  cs_nHadIso_Time->Write() ;
  cs_photIso_Time->Write() ;

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
  sideband_nXtl_u->Write() ;
  sideband_nXtl_d->Write() ;
  sideband_sMaj->Write() ;
  sideband_Pt_nJet->Write() ;
  sideband_nVtx_0J->Write() ;
  sideband_nVtx_1J->Write() ;
  sideband_nVtx_2J->Write() ;
  noG_nVtx_0J->Write() ;
  noG_nVtx_1J->Write() ;
  noG_nVtx_2J->Write() ;

  abcd_Pt_Time->Write() ;
  abcd_MET_Time->Write() ;
  abcd_NJet_Time->Write() ;

  ab_Pt_MET->Write() ;
  cd_Pt_MET->Write() ;
  ab_dPhi_gMET->Write() ;
  cd_dPhi_gMET->Write() ;

  haloTest_sMaj_sMin->Write() ;
  haloTest_cscdPhi->Write() ;

  haloAB_Pt_eta[0]->Write() ;
  haloAB_Pt_eta[1]->Write() ;
  haloAB_Pt_eta[2]->Write() ;
  haloAB_Pt_eta[3]->Write() ;

  haloCD_Pt_eta[0]->Write() ;
  haloCD_Pt_eta[1]->Write() ;
  haloCD_Pt_eta[2]->Write() ;
  haloCD_Pt_eta[3]->Write() ;

  haloAB_MET_eta[0]->Write() ;
  haloAB_MET_eta[1]->Write() ;
  haloAB_MET_eta[2]->Write() ;
  haloAB_MET_eta[3]->Write() ;

  haloCD_MET_eta[0]->Write() ;
  haloCD_MET_eta[1]->Write() ;
  haloCD_MET_eta[2]->Write() ;
  haloCD_MET_eta[3]->Write() ;

  haloCS_cscdPhi->Write() ;
  haloCS_cscdPhi1->Write() ;
  haloCS_sMaj_sMin->Write() ;
  haloCS_sMaj_Eta->Write() ;
  haloCS_sMaj_Phi->Write() ;
  haloCS_Eta_Time->Write() ;
  haloCS_Eta_Time1->Write() ;

  spikeCS_Eta_Time->Write() ;
  spikeCS_Eta_Time1->Write() ;
  spikeCS_nXtl_Eta->Write() ;
  spikeCS_Phi_Time->Write() ;
  spikeCS_sMaj_sMin->Write() ;
  spikeCS_nXtl->Write() ;

  halo_Eta[0]->Write();
  halo_Eta[1]->Write();
  spike_Eta[0]->Write();
  spike_Eta[1]->Write();

  sMaj_eta[0]->Write() ;
  sMaj_eta[1]->Write() ;
  sMaj_eta[2]->Write() ;
  sMaj_eta[3]->Write() ;
  sMaj_eta[4]->Write() ;
  sMaj_eta[5]->Write() ;
  sMaj_eta[6]->Write() ;

  sMaj_eta_csc[0]->Write() ;
  sMaj_eta_csc[1]->Write() ;
  sMaj_eta_csc[2]->Write() ;
  sMaj_eta_csc[3]->Write() ;
  sMaj_eta_csc[4]->Write() ;
  sMaj_eta_csc[5]->Write() ;
  sMaj_eta_csc[6]->Write() ;

  cosmic_Eta_Time->Write() ;
  cosmic_Phi_Time->Write() ;
  cosmic_Pt_Time->Write() ;
  cosmic_MET_Time->Write() ;
  cosmic_sMin_Time->Write() ;
  cosmic_sMaj_Time->Write() ;
  cosmic_photIso_Time->Write() ;
  cosmic_sMaj_sMin->Write();
  cosmic_Time->Write() ;
  cosmic_sigIeta->Write() ;
  cosmic_nXtl->Write() ;

  haloFN_Eta_Time->Write() ;
  haloFN_Phi_Time->Write() ;
  haloFN_Pt_Time->Write() ;
  haloFN_MET_Time->Write() ;
  haloFN_sMaj_sMin->Write() ;
  haloFN_cscdPhi->Write() ;

  halo_Eta_Time_0J->Write() ;
  halo_Eta_Time_1J->Write() ;
  halo_Eta_Time->Write() ;
  halo_Pt_Time->Write() ;
  halo_MET_Time->Write() ;
  halo_Phi_Time->Write() ;
  halo_sMin_Time->Write() ;
  halo_sMaj_Time->Write() ;
  halo_sMaj_sMin->Write();
  halo_Time->Write() ;
  halo_sigIeta->Write() ;
  halo_photIso_Time->Write() ;
  halo_sMaj_sigIeta->Write() ;
  halo_sMin_sigIeta->Write() ;
  halo_T_dPhi_gMET_1J->Write() ;
  halo_T_dPhi_gMET_2J->Write() ;
  halo_T_dPhi_gMET_0J->Write() ;
  halo_eta_rho->Write() ;
  halo_eta_sMaj->Write() ;
  halo_ecalT_rho->Write() ;
  halo_ecalT_cscT->Write() ;
  sideband_dPhi_MET_csc->Write() ;
  sideband_dPhi_MET_Jet1->Write() ;
  sideband_dPhi_MET_Jet2->Write() ;
  sideband_dPhi_MET_Jet3->Write() ;

  noHalo_Time->Write() ;
  noHalo_sMaj_Time->Write() ;
  noHalo_sMin_Time->Write() ;
  noHalo_nXtl_side->Write() ;
  noHalo_nXtl_center->Write() ;

  spike_Eta_Time->Write() ;
  spike_Phi_Time->Write() ;
  spike_Pt_Time->Write() ;
  spike_MET_Time->Write() ;
  spike_sMaj_Time->Write() ;
  spike_sMin_Time->Write() ;
  spike_photIso_Time->Write() ;
  spike_sMaj_sMin->Write();
  spike_Time->Write() ;
  spike_sigIeta->Write() ;
  spike_sMaj_sigIeta->Write() ;
  spike_sMin_sigIeta->Write() ;
  spike_T_dPhi_gMET_1J->Write() ;
  spike_T_dPhi_gMET_2J->Write() ;
  spike_T_dPhi_gMET_0J->Write() ;

  noSpike_sMaj_Time->Write() ;
  noSpike_sMin_Time->Write() ;
  noSpike_Time->Write() ;

  pure_Time->Write() ;

  nJets_center->Write() ;
  nJets_halo->Write() ;
  nJets_spike->Write() ;
  nJets_cosmic->Write() ;

  nHL_Eta->Write() ;
  nSpk_Eta->Write() ;
  nCS_Eta->Write() ;
  notSpike_nXtl->Write()    ;

  hBg_D->Write() ;
  hBg_C->Write() ;
  hBg_B->Write() ;
  hBg_A->Write() ;

  cout<<" Output historams written ! "<< endl ;
}

void BackgroundStudy::Create() {

  Input->GetParameters("Path",          &hfolder ) ; 
  hfolder += "halo/" ;
  gSystem->mkdir( hfolder.c_str() );

  TString Path_fName = hfolder + hfileName + ".root" ; 
  theFile = new TFile( Path_fName, "RECREATE" );
  theFile->cd() ;

  // initial histograms  
  obsTime     = new TH1D("obsTime", "Photon Time from seed", 160,  -14.5, 25.5);

  // DOE plots
  h_EB_Time   = new TH1D( "h_EB_Time", " Ecal time from EB", 160, -20, 20 ) ;
  h_EB_Time0  = new TH1D( "h_EB_Time0", " Ecal time from EB", 160, -20, 20 ) ;
  h_EB_Time1  = new TH1D( "h_EB_Time1", " Ecal time from EB", 160, -20, 20 ) ;
  h_EB_Time2  = new TH1D( "h_EB_Time2", " Ecal time from EB", 160, -20, 20 ) ;
  h_EE_Time   = new TH1D( "h_EE_Time", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time0  = new TH1D( "h_EE_Time0", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time1  = new TH1D( "h_EE_Time1", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time2  = new TH1D( "h_EE_Time2", " Ecal time from EE", 160, -20, 20 ) ;

  // Raw information
  h_Time_EB   = new TH1D( "h_Time_EB", " Ecal time from EB", 200, -25, 25 ) ;
  h_Time_EE   = new TH1D( "h_Time_EE", " Ecal time from EE", 200, -25, 25 ) ;
  h_haloTime_EE   = new TH1D( "h_haloTime_EE", " Halo Ecal time from EE", 200, -25, 25 ) ;
  h_Eta_Time  = new TH2D( "h_Eta_Time", " eta vs Ecal time", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Phi_Time  = new TH2D( "h_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  h_cscdPhi_Time  = new TH2D( "h_cscdPhi_Time", " d#Phi vs Ecal time", 65, 0, 3.25, 160, -20, 20 ) ;
  h_cscdPhi_cscTime  = new TH2D( "h_cscdPhi_cscTime", " d#Phi vs CSC time", 65, 0, 3.25, 300, -75, 75 ) ;
  h_ecalT_cscT       = new TH2D( "h_ecalT_cscT", " Ecal time vs CSC time", 200, -25, 25, 300, -75, 75 ) ;
  h_sigIeta_Time_EB  = new TH2D( "h_sigIeta_Time_EB", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sigIeta_Time_EE  = new TH2D( "h_sigIeta_Time_EE", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sMaj_Time_EB = new TH2D( "h_sMaj_Time_EB", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMaj_Time_EE = new TH2D( "h_sMaj_Time_EE", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMin_Time_EB = new TH2D( "h_sMin_Time_EB",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_sMin_Time_EE = new TH2D( "h_sMin_Time_EE",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_sMaj_sigIeta_EB = new TH2D( "h_sMaj_sigIeta_EB", " sMaj vs Ecal time", 100, 0, 2, 80, 0, 0.08 ) ;
  h_sMaj_sigIeta_EE = new TH2D( "h_sMaj_sigIeta_EE", " sMaj vs Ecal time", 100, 0, 2, 80, 0, 0.08 ) ;
  h_sMin_sigIeta_EB = new TH2D( "h_sMin_sigIeta_EB",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_sMin_sigIeta_EE = new TH2D( "h_sMin_sigIeta_EE",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  h_Pt_MET       = new TH2D( "h_Pt_MET",        " Leading Pt vs MET", 50, 0, 500, 50, 0, 500 ) ;

  h_Time_nZ0     = new TH2D( "h_Time_nZ0", "nTrackZ0 vs Time", 34, -170, 170 , 160, -20, 20 ) ;
  a_Z0     = new TH1D( "a_Z0", "nTrackZ0 vs Time", 34, -170, 170  ) ;
  b_Z0     = new TH1D( "b_Z0", "nTrackZ0 vs Time", 34, -170, 170  ) ;
  c_Z0     = new TH1D( "c_Z0", "nTrackZ0 vs Time", 34, -170, 170  ) ;
  d_Z0     = new TH1D( "d_Z0", "nTrackZ0 vs Time", 34, -170, 170  ) ;
  h_Z0     = new TH1D( "h_Z0", "nTrackZ0 vs Time", 34, -170, 170  ) ;

  a_nVtx     = new TH1D( "a_nVtx", "nVtx in a region", 41,-0.5,40.5  ) ;
  b_nVtx     = new TH1D( "b_nVtx", "nVtx in b region", 41,-0.5,40.5  ) ;
  c_nVtx     = new TH1D( "c_nVtx", "nVtx in c region", 41,-0.5,40.5  ) ;
  d_nVtx     = new TH1D( "d_nVtx", "nVtx in d region", 41,-0.5,40.5  ) ;
  h_nVtx     = new TH1D( "h_nVtx", "nVtx in good control region w/ MET > 60", 41,-0.5,40.5  ) ;
  l_nVtx     = new TH1D( "l_nVtx", "nVtx in good control region w/ MET < 60", 41,-0.5,40.5  ) ;

  h_Pt_Time_EB   = new TH2D( "h_Pt_Time_EB",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_Pt_Time_EE   = new TH2D( "h_Pt_Time_EE",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EB  = new TH2D( "h_MET_Time_EB",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EE  = new TH2D( "h_MET_Time_EE",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_cHadIso_Time = new TH2D( "h_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_nHadIso_Time = new TH2D( "h_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_photIso_Time = new TH2D( "h_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  h_cscdPhi_rho  = new TH2D( "h_cscdPhi_rho", " d#Phi vs rho", 65, 0, 3.25, 100, 100, 500. ) ;

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
  sg_Eta_Time_halo  = new TH2D( "sg_Eta_Time_halo", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sg_Eta_Time_spike  = new TH2D( "sg_Eta_Time_spike", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
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
  sg_sMaj_sigIeta = new TH2D( "sg_sMaj_sigIeta", " sMaj vs Ecal time", 100, 0, 2, 80, 0, 0.08 ) ;
  sg_sMin_sigIeta = new TH2D( "sg_sMin_sigIeta",  "sMin vs. Ecal time ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  //sg_gg_dR       = new TH1D( "sg_gg_dR", " dR(g,g) " , 100, 0, 5. ) ;

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
  cs_cscdPhi   = new TH1D( "cs_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  cs_cHadIso_Time = new TH2D("cs_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_nHadIso_Time = new TH2D("cs_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_photIso_Time = new TH2D("cs_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  cs_sigIeta_Time = new TH2D( "cs_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  cs_dtdPhidEta   = new TH2D( "cs_dtdPhidEta", " DT dPhi, dEta  ", 64, 0, 3.2, 50, 0, 1. ) ;

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
  sideband_dtdR       = new TH1D( "sideband_dtdR", " dR( DTSeg, #gamma) ", 50, 0, 1. ) ;
  sideband_nXtl_u     = new TH1D( "sideband_nXtl_u", " N of crystals ", 50, 0, 50 ) ;
  sideband_nXtl_d     = new TH1D( "sideband_nXtl_d", " N of crystals ", 50, 0, 50 ) ;
  sideband_sMaj       = new TH1D( "sideband_sMaj", " sMajor ", 100, 0., 2. ) ;
  sideband_Pt_nJet    = new TH2D( "sideband_Pt_nJet", " Pt vs nJet", 50, 0, 500 ,  10, -0.5, 9.5) ;
  sideband_nVtx_0J    = new TH1D( "sideband_nVtx_0J", " N of Vertex ", 50, -0.5, 49.5 ) ;
  sideband_nVtx_1J    = new TH1D( "sideband_nVtx_1J", " N of Vertex ", 50, -0.5, 49.5 ) ;
  sideband_nVtx_2J    = new TH1D( "sideband_nVtx_2J", " N of Vertex ", 50, -0.5, 49.5 ) ;
  noG_nVtx_0J         = new TH1D( "noG_nVtx_0J", " N of Vertex ", 50, -0.5, 49.5 ) ;
  noG_nVtx_1J         = new TH1D( "noG_nVtx_1J", " N of Vertex ", 50, -0.5, 49.5 ) ;
  noG_nVtx_2J         = new TH1D( "noG_nVtx_2J", " N of Vertex ", 50, -0.5, 49.5 ) ;

  abcd_Pt_Time   = new TH2D( "abcd_Pt_Time",  " Pt vs Ecal time", 50, 0, 500, 200, -25, 25 ) ;
  abcd_MET_Time  = new TH2D( "abcd_MET_Time",  " MET vs Ecal time", 50, 0, 500, 200, -25, 25 ) ;
  abcd_NJet_Time = new TH2D( "abcd_NJet_Time",  " NJet vs Ecal time", 10, 0, 10, 200, -25, 25 ) ;
  ab_dPhi_gMET   = new TH1D( "ab_dPhi_gMET",  "#Delta#Phi(photon, MET)", 64, 0, 3.2 ) ;
  cd_dPhi_gMET   = new TH1D( "cd_dPhi_gMET",  "#Delta#Phi(photon, MET)", 64, 0, 3.2 ) ;
  ab_Pt_MET      = new TH2D( "ab_Pt_MET",  " Pt vs MET", 50, 0, 500, 50, 0, 500 ) ;
  cd_Pt_MET      = new TH2D( "cd_Pt_MET",  " Pt vs MET", 50, 0, 500, 50, 0, 500 ) ;

  haloTest_cscdPhi   = new TH1D( "haloTest_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  haloTest_sMaj_sMin = new TH2D( "haloTest_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;


  haloAB_Pt_eta[0] = new TH1D( "haloAB_Pt_eta0", " Pt 0.00 < |#eta| < 0.37 ", 80, 0, 400 ) ;
  haloAB_Pt_eta[1] = new TH1D( "haloAB_Pt_eta1", " Pt 0.37 < |#eta| < 0.74 ", 80, 0, 400 ) ;
  haloAB_Pt_eta[2] = new TH1D( "haloAB_Pt_eta2", " Pt 0.74 < |#eta| < 1.11 ", 80, 0, 400 ) ;
  haloAB_Pt_eta[3] = new TH1D( "haloAB_Pt_eta3", " Pt 1.11 < |#eta| < 1.48 ", 80, 0, 400 ) ;

  haloCD_Pt_eta[0] = new TH1D( "haloCD_Pt_eta0", " Pt 0.00 < |#eta| < 0.37 ", 80, 0, 400 ) ;
  haloCD_Pt_eta[1] = new TH1D( "haloCD_Pt_eta1", " Pt 0.37 < |#eta| < 0.74 ", 80, 0, 400 ) ;
  haloCD_Pt_eta[2] = new TH1D( "haloCD_Pt_eta2", " Pt 0.74 < |#eta| < 1.11 ", 80, 0, 400 ) ;
  haloCD_Pt_eta[3] = new TH1D( "haloCD_Pt_eta3", " Pt 1.11 < |#eta| < 1.48 ", 80, 0, 400 ) ;

  haloAB_MET_eta[0] = new TH1D( "haloAB_MET_eta0", " MET 0.00 < |#eta| < 0.37 ", 80, 0, 400 ) ;
  haloAB_MET_eta[1] = new TH1D( "haloAB_MET_eta1", " MET 0.37 < |#eta| < 0.74 ", 80, 0, 400 ) ;
  haloAB_MET_eta[2] = new TH1D( "haloAB_MET_eta2", " MET 0.74 < |#eta| < 1.11 ", 80, 0, 400 ) ;
  haloAB_MET_eta[3] = new TH1D( "haloAB_MET_eta3", " MET 1.11 < |#eta| < 1.48 ", 80, 0, 400 ) ;

  haloCD_MET_eta[0] = new TH1D( "haloCD_MET_eta0", " MET 0.00 < |#eta| < 0.37 ", 80, 0, 400 ) ;
  haloCD_MET_eta[1] = new TH1D( "haloCD_MET_eta1", " MET 0.37 < |#eta| < 0.74 ", 80, 0, 400 ) ;
  haloCD_MET_eta[2] = new TH1D( "haloCD_MET_eta2", " MET 0.74 < |#eta| < 1.11 ", 80, 0, 400 ) ;
  haloCD_MET_eta[3] = new TH1D( "haloCD_MET_eta3", " MET 1.11 < |#eta| < 1.48 ", 80, 0, 400 ) ;

  haloCS_sMaj_Eta  = new TH2D( "haloCS_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  haloCS_sMaj_Phi  = new TH2D( "haloCS_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  haloCS_Eta_Time  = new TH2D( "haloCS_Eta_Time", " eta vs photon time  ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  haloCS_Eta_Time1 = new TH2D( "haloCS_Eta_Time1", " eta vs photon time ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  haloCS_sMaj_sMin = new TH2D( "haloCS_sMaj_sMin", " sMaj vs sMin of photon", 100, 0, 2, 50, 0.1, 0.4 ) ;
  haloCS_cscdPhi   = new TH1D( "haloCS_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  haloCS_cscdPhi1  = new TH1D( "haloCS_cscdPhi1", " d#Phi ", 65, 0, 3.25 ) ;

  spikeCS_Eta_Time  = new TH2D( "spikeCS_Eta_Time", " #eta vs time for spikes CS",  51, -2.5, 2.5,   160, -20, 20 ) ;
  spikeCS_Eta_Time1 = new TH2D( "spikeCS_Eta_Time1", " #eta vs time after spikes tagging",  51, -2.5, 2.5,   160, -20, 20 ) ;
  spikeCS_nXtl_Eta  = new TH2D( "spikeCS_nXtl_Eta", " N of Xtals for spikes CS vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  spikeCS_Phi_Time  = new TH2D( "spikeCS_Phi_Time", " #phi vs time for spikes CS",  63, -3.15, 3.15, 160, -20, 20 ) ;
  spikeCS_sMaj_sMin = new TH2D( "spikeCS_sMaj_sMin", "sMaj vs sMin for spikes CS", 100,  0, 2, 50, 0.1, 0.4   ) ;
  spikeCS_nXtl      = new TH1D( "spikeCS_nXtl",      "N of xtals of spikes ", 50,  0, 50 );

  halo_Eta[0]  = new TH1D( "halo_Eta0",  "Eta before Halo-tagging",  6, 0., 1.68 ) ;
  halo_Eta[1]  = new TH1D( "halo_Eta1",  "Eta after Halo-tagging",   6, 0., 1.68 ) ;
  spike_Eta[0] = new TH1D( "spike_Eta0", "Eta before Spike-tagging", 6, 0., 1.68 ) ;
  spike_Eta[1] = new TH1D( "spike_Eta1", "Eta after Spike-tagging",  6, 0., 1.68 ) ;

  sMaj_eta[0] = new TH1D( "sMaj_eta1",  "sMajor for 0.0  < |eta| < 0.28 ", 100, 0., 2.5 ) ;
  sMaj_eta[1] = new TH1D( "sMaj_eta2",  "sMajor for 0.28 < |eta| < 0.56 ", 100, 0., 2.5 ) ;
  sMaj_eta[2] = new TH1D( "sMaj_eta3",  "sMajor for 0.56 < |eta| < 0.84 ", 100, 0., 2.5 ) ;
  sMaj_eta[3] = new TH1D( "sMaj_eta4",  "sMajor for 0.84 < |eta| < 1.12 ", 100, 0., 2.5 ) ;
  sMaj_eta[4] = new TH1D( "sMaj_eta5",  "sMajor for 1.12 < |eta| < 1.40 ", 100, 0., 2.5 ) ;
  sMaj_eta[5] = new TH1D( "sMaj_eta6",  "sMajor for 1.5 < |eta| < 2.0 ", 100, 0., 2.5 ) ;
  sMaj_eta[6] = new TH1D( "sMaj_eta7",  "sMajor for 2.0 < |eta| < 2.5 ", 100, 0., 2.5 ) ;

  sMaj_eta_csc[0] = new TH1D( "sMaj_eta_csc1",  "sMajor for 0.0  < |eta| < 0.28 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[1] = new TH1D( "sMaj_eta_csc2",  "sMajor for 0.28 < |eta| < 0.56 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[2] = new TH1D( "sMaj_eta_csc3",  "sMajor for 0.56 < |eta| < 0.84 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[3] = new TH1D( "sMaj_eta_csc4",  "sMajor for 0.84 < |eta| < 1.12 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[4] = new TH1D( "sMaj_eta_csc5",  "sMajor for 1.12 < |eta| < 1.40 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[5] = new TH1D( "sMaj_eta_csc6",  "sMajor for 1.5 < |eta| < 2.0 ", 100, 0., 2.5 ) ;
  sMaj_eta_csc[6] = new TH1D( "sMaj_eta_csc7",  "sMajor for 2.0 < |eta| < 2.5 ", 100, 0., 2.5 ) ;

  cosmic_Eta_Time  = new TH2D( "cosmic_Eta_Time", " eta vs photon time for cosmic photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  cosmic_Phi_Time  = new TH2D( "cosmic_Phi_Time", " phi vs photon time for cosmic photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  cosmic_Pt_Time   = new TH2D( "cosmic_Pt_Time",  " Pt vs photon time for cosmic photon ",  50, 0, 500, 160, -20, 20 ) ;
  cosmic_MET_Time  = new TH2D( "cosmic_MET_Time", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
  cosmic_sMin_Time = new TH2D( "cosmic_sMin_Time",  "sMin vs Ecal time for cosmic photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  cosmic_sMaj_Time = new TH2D( "cosmic_sMaj_Time",  "sMaj vs Ecal time for cosmic Photon", 100, 0, 2, 160, -20, 20 ) ;
  cosmic_sMaj_sMin = new TH2D( "cosmic_sMaj_sMin", "sMajor vs sMinor for cosmic photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  cosmic_sigIeta   = new TH1D( "cosmic_sigIeta", " Sigma Ieta Ieta for cosmic Photon ", 100,  0., 0.1 ) ;
  cosmic_Time      = new TH1D( "cosmic_Time",   "Photon time from cosmic ", 160,  -14.5, 25.5 ) ;
  cosmic_photIso_Time = new TH2D("cosmic_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  cosmic_nXtl      = new TH1D( "cosmic_nXtl", " N crystals vs #eta", 50, 0, 50 ) ;

  haloFN_Eta_Time  = new TH2D( "haloFN_Eta_Time", " #eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  haloFN_Phi_Time  = new TH2D( "haloFN_Phi_Time", " #phi vs photon time for halo photon ", 63, -3.15, 3.15,   160, -20, 20 ) ;
  haloFN_Pt_Time   = new TH2D( "haloFN_Pt_Time",  " Pt vs photon time for halo photon ",  50, 0, 500, 160, -20, 20 ) ;
  haloFN_MET_Time  = new TH2D( "haloFN_MET_Time", " MET vs photon time for halo photon ", 50, 0, 500, 160, -20, 20 ) ;
  haloFN_sMaj_sMin = new TH2D( "haloFN_sMaj_sMin","sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  haloFN_cscdPhi   = new TH1D( "haloFN_cscdPhi",  " d#Phi ", 65, 0, 3.25 ) ;

  halo_Eta_Time_0J  = new TH2D( "halo_Eta_Time_0J", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  halo_Eta_Time_1J  = new TH2D( "halo_Eta_Time_1J", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  halo_Eta_Time  = new TH2D( "halo_Eta_Time", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  halo_Phi_Time  = new TH2D( "halo_Phi_Time", " phi vs photon time for halo photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  halo_Pt_Time   = new TH2D( "halo_Pt_Time",  " Pt vs photon time for halo photon ",  50, 0, 500, 160, -20, 20 ) ;
  halo_MET_Time  = new TH2D( "halo_MET_Time", " MET vs photon time for halo photon ", 50, 0, 500, 160, -20, 20 ) ;
  halo_sMin_Time = new TH2D( "halo_sMin_Time",  "sMin vs Ecal time for halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  halo_sMaj_Time = new TH2D( "halo_sMaj_Time",  "sMaj vs Ecal time for halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  halo_sMaj_sMin = new TH2D( "halo_sMaj_sMin", "sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  halo_sigIeta   = new TH1D( "halo_sigIeta", " Sigma Ieta Ieta for Halo Photon ", 100,  0., 0.1 ) ;
  halo_Time      = new TH1D( "halo_Time",   "Photon time w/ halo ", 160,  -14.5, 25.5 ) ;
  halo_photIso_Time = new TH2D("halo_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  halo_sMaj_sigIeta = new TH2D( "halo_sMaj_sigIeta", " sMaj vs #sigma_{i#eta}", 100, 0, 2, 80, 0, 0.08 ) ;
  halo_sMin_sigIeta = new TH2D( "halo_sMin_sigIeta",  "sMin vs #sigma_{i#eta}", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  halo_T_dPhi_gMET_0J = new TH2D("halo_T_dPhi_gMET_0J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_T_dPhi_gMET_1J = new TH2D("halo_T_dPhi_gMET_1J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_T_dPhi_gMET_2J = new TH2D("halo_T_dPhi_gMET_2J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_eta_rho        = new TH2D( "halo_eta_rho", " #eta vs rho", 51, -2.5, 2.5, 100, 100, 300. ) ;
  halo_eta_sMaj       = new TH2D( "halo_eta_sMaj", " #eta vs sMajor", 51, -2.5, 2.5, 100, 0, 2 ) ;
  halo_ecalT_rho      = new TH2D( "halo_ecalT_rho", " Ecal time vs rho", 160, -20, 20, 100, 100, 500. ) ;
  halo_ecalT_cscT     = new TH2D( "halo_ecalT_cscT", " Ecal time vs CSC time", 200, -25, 25, 300, -75, 75 ) ;

  sideband_dPhi_MET_csc = new TH2D("sideband_dPhi_MET_csc", "dPhi( photon, MET) vs dPhi(photon,csc)", 64, 0, 3.2, 64, 0, 3.2 ) ;
  sideband_dPhi_MET_Jet1 = new TH2D("sideband_dPhi_MET_Jet1", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;
  sideband_dPhi_MET_Jet2 = new TH2D("sideband_dPhi_MET_Jet2", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;
  sideband_dPhi_MET_Jet3 = new TH2D("sideband_dPhi_MET_Jet3", "dPhi(photon,MET) vs dPhi(photon,Jet)", 64, 0, 3.2, 68, -0.2, 3.2) ;

  noHalo_sMaj_Time = new TH2D( "noHalo_sMaj_Time",  "sMaj vs Ecal time for non halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  noHalo_sMin_Time = new TH2D( "noHalo_sMin_Time",  "sMin vs. Ecal time for non halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  noHalo_Time    = new TH1D( "noHalo_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;

  noHalo_nXtl_side = new TH1D( "noHalo_nXtl_side", "N of xtals of non halo photon w/ |t| > 3ns",     50,  0, 50 );
  noHalo_nXtl_center = new TH1D( "noHalo_nXtl_center", "N of xtals of non halo photon w/ |t| < 3ns", 50,  0, 50 );

  spike_sigIeta   = new TH1D( "spike_sigIeta", " Sigma Ieta Ieta for spike photon ", 100,  0., 0.1 ) ;
  spike_Pt_Time   = new TH2D( "spike_Pt_Time",  " Pt vs photon time for cosmic photon ",  50, 0, 500, 160, -20, 20 ) ;
  spike_MET_Time  = new TH2D( "spike_MET_Time", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
  spike_Eta_Time  = new TH2D( "spike_Eta_Time", " eta vs photon time for spike photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  spike_Phi_Time  = new TH2D( "spike_Phi_Time", " phi vs photon time for spike photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  spike_sMaj_sMin = new TH2D( "spike_sMaj_sMin", " sMajor vs sMinor for spike photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  spike_sMaj_Time = new TH2D( "spike_sMaj_Time",  "sMaj vs Ecal time for spike Photon", 100, 0, 2, 160, -20, 20 ) ;
  spike_sMin_Time = new TH2D( "spike_sMin_Time",  "sMin vs. Ecal time for spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  spike_Time      = new TH1D( "spike_Time",   "Photon time w/ spike ", 160,  -14.5, 25.5 ) ;
  spike_photIso_Time = new TH2D("spike_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  spike_sMaj_sigIeta = new TH2D( "spike_sMaj_sigIeta", " sMaj vs #sigma_{i#eta}", 100, 0, 2, 80, 0, 0.08 ) ;
  spike_sMin_sigIeta = new TH2D( "spike_sMin_sigIeta",  "sMin vs #sigma_{i#eta} ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  spike_T_dPhi_gMET_0J = new TH2D("spike_T_dPhi_gMET_0J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  spike_T_dPhi_gMET_1J = new TH2D("spike_T_dPhi_gMET_1J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  spike_T_dPhi_gMET_2J = new TH2D("spike_T_dPhi_gMET_2J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;

  noSpike_Time    = new TH1D( "noSpike_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;
  noSpike_sMaj_Time = new TH2D( "noSpike_sMaj_Time",  "sMaj vs Ecal time for non spike Photon", 100, 0, 2, 160, -20, 20 ) ;
  noSpike_sMin_Time = new TH2D( "noSpike_sMin_Time",  "sMin vs. Ecal time for non spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;

  notSpike_nXtl   = new TH1D("notSpike_nXtl", "N of crystals for non-spike photon ", 50,  0, 50 );
  pure_Time      = new TH1D( "pure_Time", "  time for pure photon", 160, -14.5, 25.5 ) ;

  nJets_center = new TH1D( "nJets_center",  "N of Jets for |t| < 2", 10, -0.5, 9.5 ) ;
  nJets_halo   = new TH1D( "nJets_halo",    "N of Jets for halo-tagged events", 10, -0.5, 9.5 ) ;
  nJets_spike  = new TH1D( "nJets_spike",   "N of Jets for spike-tagged events", 10, -0.5, 9.5 ) ;
  nJets_cosmic = new TH1D( "nJets_cosmic",  "N of Jets for cosmic-tagged events", 10, -0.5, 9.5 ) ;

  nHL_Eta  = new TH1D( "nHL_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
  nSpk_Eta = new TH1D( "nSpk_Eta",  " N of Spike in |#eta|", 5, 0., 1.4 ) ;
  nCS_Eta  = new TH1D( "nCS_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
 
  // x is eta region , each is 0.28 , y is different sample, 0:total, 1:halo, 2: spike, 3: cosmic
  hBg_D  = new TH2D( "hBg_D",  "Background in D (signal) region",   5,  0., 5, 4, 0, 4 ) ;
  hBg_C  = new TH2D( "hBg_C",  "Background in C ", 5,  0., 5, 4, 0, 4 ) ;
  hBg_B  = new TH2D( "hBg_B",  "Background in B ", 5,  0., 5, 4, 0, 4 ) ;
  hBg_A  = new TH2D( "hBg_A",  "Background in A ", 5,  0., 5, 4, 0, 4 ) ;

}

void BackgroundStudy::Open() {

     Input->GetParameters("Path",      &hfolder ) ; 
     hfolder += "halo/" ;

     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     //hFile->cd() ;
     cout<<" file opened ! "<<endl ;

     obsTime    = (TH1D*) theFile->Get("obsTime")     ;

     h_EB_Time  = (TH1D*) theFile->Get("h_EB_Time") ;
     h_EB_Time0 = (TH1D*) theFile->Get("h_EB_Time0");
     h_EB_Time1 = (TH1D*) theFile->Get("h_EB_Time1");
     h_EB_Time2 = (TH1D*) theFile->Get("h_EB_Time2");
     h_EE_Time  = (TH1D*) theFile->Get("h_EE_Time");
     h_EE_Time0 = (TH1D*) theFile->Get("h_EE_Time0");
     h_EE_Time1 = (TH1D*) theFile->Get("h_EE_Time1");
     h_EE_Time2 = (TH1D*) theFile->Get("h_EE_Time2");

     h_Time_EB = (TH1D*) theFile->Get("h_Time_EB");
     h_Time_EE = (TH1D*) theFile->Get("h_Time_EE");
     h_haloTime_EE = (TH1D*) theFile->Get("h_haloTime_EE");

     h_Eta_Time  = (TH2D*) theFile->Get("h_Eta_Time");
     h_Phi_Time  = (TH2D*) theFile->Get("h_Phi_Time");
     h_cscdPhi_Time = (TH2D*) theFile->Get("h_cscdPhi_Time");
     h_cscdPhi_cscTime = (TH2D*) theFile->Get("h_cscdPhi_cscTime");
     h_ecalT_cscT   = (TH2D*) theFile->Get("h_ecalT_cscT");
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
     h_cHadIso_Time = (TH2D*) theFile->Get("h_cHadIso_Time");
     h_nHadIso_Time = (TH2D*) theFile->Get("h_nHadIso_Time");
     h_photIso_Time = (TH2D*) theFile->Get("h_photIso_Time");

     h_sMaj_Eta  = (TH2D*) theFile->Get("h_sMaj_Eta");
     h_sMaj_Phi  = (TH2D*) theFile->Get("h_sMaj_Phi");
     h_sMaj_sMin_EB = (TH2D*) theFile->Get("h_sMaj_sMin_EB");
     h_nXtl_Eta    = (TH2D*) theFile->Get("h_nXtl_Eta");
     h_nXtl_Pt_EB  = (TH2D*) theFile->Get("h_nXtl_Pt_EB");
     h_cscdPhi_rho = (TH2D*) theFile->Get("h_cscdPhi_rho");
     h_Time_nZ0    = (TH2D*) theFile->Get("h_Time_nZ0");
     a_Z0    = (TH1D*) theFile->Get("a_Z0");
     b_Z0    = (TH1D*) theFile->Get("b_Z0");
     c_Z0    = (TH1D*) theFile->Get("c_Z0");
     d_Z0    = (TH1D*) theFile->Get("d_Z0");
     h_Z0    = (TH1D*) theFile->Get("h_Z0");

     a_nVtx    = (TH1D*) theFile->Get("a_nVtx");
     b_nVtx    = (TH1D*) theFile->Get("b_nVtx");
     c_nVtx    = (TH1D*) theFile->Get("c_nVtx");
     d_nVtx    = (TH1D*) theFile->Get("d_nVtx");
     h_nVtx    = (TH1D*) theFile->Get("h_nVtx");
     l_nVtx    = (TH1D*) theFile->Get("l_nVtx");

     sg_Eta_Time = (TH2D*) theFile->Get("sg_Eta_Time");
     sg_Eta_Time_halo  = (TH2D*) theFile->Get("sg_Eta_Time_halo");
     sg_Eta_Time_spike = (TH2D*) theFile->Get("sg_Eta_Time_spike");
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
     sg_sMaj_sigIeta = (TH2D*) theFile->Get("sg_sMaj_sigIeta");
     sg_sMin_sigIeta = (TH2D*) theFile->Get("sg_sMin_sigIeta");
     //sg_gg_dR     = (TH1D*) theFile->Get("sg_gg_dR");

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
     cs_sMaj_sMin     = (TH2D*) theFile->Get("cs_sMaj_sMin");
     cs_cHadIso_Time = (TH2D*) theFile->Get("cs_cHadIso_Time");
     cs_nHadIso_Time = (TH2D*) theFile->Get("cs_nHadIso_Time");
     cs_photIso_Time = (TH2D*) theFile->Get("cs_photIso_Time");
     cs_dtdPhidEta   = (TH2D*) theFile->Get("cs_dtdPhidEta");

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
     sideband_nXtl_u    = (TH1D*) theFile->Get("sideband_nXtl_u");
     sideband_nXtl_d    = (TH1D*) theFile->Get("sideband_nXtl_d");
     sideband_dtdR        = (TH1D*) theFile->Get("sideband_dtdR");
     sideband_dtdPhidEta  = (TH2D*) theFile->Get("sideband_dtdPhidEta");
     sideband_sMaj = (TH1D*) theFile->Get("sideband_sMaj");
     sideband_Pt_nJet   = (TH2D*) theFile->Get("sideband_Pt_nJet");

     sideband_nVtx_0J   = (TH1D*) theFile->Get("sideband_nVtx_0J");
     sideband_nVtx_1J   = (TH1D*) theFile->Get("sideband_nVtx_1J");
     sideband_nVtx_2J   = (TH1D*) theFile->Get("sideband_nVtx_2J");
     noG_nVtx_0J        = (TH1D*) theFile->Get("noG_nVtx_0J");
     noG_nVtx_1J        = (TH1D*) theFile->Get("noG_nVtx_1J");
     noG_nVtx_2J        = (TH1D*) theFile->Get("noG_nVtx_2J");

     abcd_Pt_Time = (TH2D*) theFile->Get("abcd_Pt_Time");
     abcd_MET_Time = (TH2D*) theFile->Get("abcd_MET_Time");
     abcd_NJet_Time = (TH2D*) theFile->Get("abcd_NJet_Time");
     ab_dPhi_gMET   = (TH1D*) theFile->Get("ab_dPhi_gMET");
     cd_dPhi_gMET   = (TH1D*) theFile->Get("cd_dPhi_gMET");
     ab_Pt_MET      = (TH2D*) theFile->Get("ab_Pt_MET");
     cd_Pt_MET      = (TH2D*) theFile->Get("cd_Pt_MET");
     haloTest_sMaj_sMin  = (TH2D*) theFile->Get("haloTest_sMaj_sMin");
     haloTest_cscdPhi    = (TH1D*) theFile->Get("haloTest_cscdPhi");

     haloCS_sMaj_sMin = (TH2D*) theFile->Get("haloCS_sMaj_sMin");
     haloCS_sMaj_Eta  = (TH2D*) theFile->Get("haloCS_sMaj_Eta");
     haloCS_sMaj_Phi  = (TH2D*) theFile->Get("haloCS_sMaj_Phi");
     haloCS_Eta_Time  = (TH2D*) theFile->Get("haloCS_Eta_Time");
     haloCS_Eta_Time1 = (TH2D*) theFile->Get("haloCS_Eta_Time1");
     haloCS_cscdPhi   = (TH1D*) theFile->Get("haloCS_cscdPhi");
     haloCS_cscdPhi1  = (TH1D*) theFile->Get("haloCS_cscdPhi1");

     haloAB_Pt_eta[0] = (TH1D*) theFile->Get("haloAB_Pt_eta0");
     haloAB_Pt_eta[1] = (TH1D*) theFile->Get("haloAB_Pt_eta1");
     haloAB_Pt_eta[2] = (TH1D*) theFile->Get("haloAB_Pt_eta2");
     haloAB_Pt_eta[3] = (TH1D*) theFile->Get("haloAB_Pt_eta3");

     haloCD_Pt_eta[0] = (TH1D*) theFile->Get("haloCD_Pt_eta0");
     haloCD_Pt_eta[1] = (TH1D*) theFile->Get("haloCD_Pt_eta1");
     haloCD_Pt_eta[2] = (TH1D*) theFile->Get("haloCD_Pt_eta2");
     haloCD_Pt_eta[3] = (TH1D*) theFile->Get("haloCD_Pt_eta3");

     haloAB_MET_eta[0] = (TH1D*) theFile->Get("haloAB_MET_eta0");
     haloAB_MET_eta[1] = (TH1D*) theFile->Get("haloAB_MET_eta1");
     haloAB_MET_eta[2] = (TH1D*) theFile->Get("haloAB_MET_eta2");
     haloAB_MET_eta[3] = (TH1D*) theFile->Get("haloAB_MET_eta3");

     haloCD_MET_eta[0] = (TH1D*) theFile->Get("haloCD_MET_eta0");
     haloCD_MET_eta[1] = (TH1D*) theFile->Get("haloCD_MET_eta1");
     haloCD_MET_eta[2] = (TH1D*) theFile->Get("haloCD_MET_eta2");
     haloCD_MET_eta[3] = (TH1D*) theFile->Get("haloCD_MET_eta3");

     spikeCS_Eta_Time1 = (TH2D*) theFile->Get("spikeCS_Eta_Time1");
     spikeCS_Eta_Time  = (TH2D*) theFile->Get("spikeCS_Eta_Time");
     spikeCS_nXtl_Eta  = (TH2D*) theFile->Get("spikeCS_nXtl_Eta");
     spikeCS_Phi_Time  = (TH2D*) theFile->Get("spikeCS_Phi_Time");
     spikeCS_sMaj_sMin = (TH2D*) theFile->Get("spikeCS_sMaj_sMin");
     spikeCS_nXtl = (TH1D*) theFile->Get("spikeCS_nXtl");

     halo_Eta[0]  = (TH1D*) theFile->Get("halo_Eta0");
     halo_Eta[1]  = (TH1D*) theFile->Get("halo_Eta1");
     spike_Eta[0] = (TH1D*) theFile->Get("spike_Eta0");
     spike_Eta[1] = (TH1D*) theFile->Get("spike_Eta1");

     sMaj_eta[0] = (TH1D*) theFile->Get("sMaj_eta1");
     sMaj_eta[1] = (TH1D*) theFile->Get("sMaj_eta2");
     sMaj_eta[2] = (TH1D*) theFile->Get("sMaj_eta3");
     sMaj_eta[3] = (TH1D*) theFile->Get("sMaj_eta4");
     sMaj_eta[4] = (TH1D*) theFile->Get("sMaj_eta5");
     sMaj_eta[5] = (TH1D*) theFile->Get("sMaj_eta6");
     sMaj_eta[6] = (TH1D*) theFile->Get("sMaj_eta7");
     sMaj_eta_csc[0] = (TH1D*) theFile->Get("sMaj_eta_csc1");
     sMaj_eta_csc[1] = (TH1D*) theFile->Get("sMaj_eta_csc2");
     sMaj_eta_csc[2] = (TH1D*) theFile->Get("sMaj_eta_csc3");
     sMaj_eta_csc[3] = (TH1D*) theFile->Get("sMaj_eta_csc4");
     sMaj_eta_csc[4] = (TH1D*) theFile->Get("sMaj_eta_csc5");
     sMaj_eta_csc[5] = (TH1D*) theFile->Get("sMaj_eta_csc6");
     sMaj_eta_csc[6] = (TH1D*) theFile->Get("sMaj_eta_csc7");

     cosmic_Eta_Time = (TH2D*) theFile->Get("cosmic_Eta_Time");
     cosmic_Phi_Time = (TH2D*) theFile->Get("cosmic_Phi_Time");
     cosmic_Pt_Time  = (TH2D*) theFile->Get("cosmic_Pt_Time");
     cosmic_MET_Time = (TH2D*) theFile->Get("cosmic_MET_Time");
     cosmic_sMin_Time = (TH2D*) theFile->Get("cosmic_sMin_Time");
     cosmic_sMaj_Time = (TH2D*) theFile->Get("cosmic_sMaj_Time");
     cosmic_photIso_Time = (TH2D*) theFile->Get("cosmic_photIso_Time");
     cosmic_sMaj_sMin    = (TH2D*) theFile->Get("cosmic_sMaj_sMin");
     cosmic_sigIeta = (TH1D*) theFile->Get("cosmic_sigIeta");
     cosmic_Time    = (TH1D*) theFile->Get("cosmic_Time");
     cosmic_nXtl    = (TH1D*) theFile->Get("cosmic_nXtl");

     haloFN_Eta_Time = (TH2D*) theFile->Get("haloFN_Eta_Time");
     haloFN_Phi_Time = (TH2D*) theFile->Get("haloFN_Phi_Time");
     haloFN_Pt_Time  = (TH2D*) theFile->Get("haloFN_Pt_Time");
     haloFN_MET_Time = (TH2D*) theFile->Get("haloFN_MET_Time");
     haloFN_sMaj_sMin= (TH2D*) theFile->Get("haloFN_sMaj_sMin");
     haloFN_cscdPhi  = (TH1D*) theFile->Get("haloFN_cscdPhi");

     halo_Eta_Time_0J = (TH2D*) theFile->Get("halo_Eta_Time_0J");
     halo_Eta_Time_1J = (TH2D*) theFile->Get("halo_Eta_Time_1J");
     halo_Eta_Time = (TH2D*) theFile->Get("halo_Eta_Time");
     halo_Phi_Time = (TH2D*) theFile->Get("halo_Phi_Time");
     halo_Pt_Time  = (TH2D*) theFile->Get("halo_Pt_Time");
     halo_MET_Time = (TH2D*) theFile->Get("halo_MET_Time");
     halo_sMin_Time = (TH2D*) theFile->Get("halo_sMin_Time");
     halo_sMaj_Time = (TH2D*) theFile->Get("halo_sMaj_Time");
     halo_photIso_Time = (TH2D*) theFile->Get("halo_photIso_Time");
     halo_sMaj_sMin    = (TH2D*) theFile->Get("halo_sMaj_sMin");
     halo_sigIeta = (TH1D*) theFile->Get("halo_sigIeta");
     halo_Time    = (TH1D*) theFile->Get("halo_Time");
     halo_sMaj_sigIeta = (TH2D*) theFile->Get("halo_sMaj_sigIeta");
     halo_sMin_sigIeta = (TH2D*) theFile->Get("halo_sMin_sigIeta");
     halo_T_dPhi_gMET_0J  = (TH2D*) theFile->Get("halo_T_dPhi_gMET_0J") ;
     halo_T_dPhi_gMET_1J  = (TH2D*) theFile->Get("halo_T_dPhi_gMET_1J") ;
     halo_T_dPhi_gMET_2J  = (TH2D*) theFile->Get("halo_T_dPhi_gMET_2J") ;
     halo_eta_rho         = (TH2D*) theFile->Get("halo_eta_rho");
     halo_eta_sMaj        = (TH2D*) theFile->Get("halo_eta_sMaj");
     halo_ecalT_rho       = (TH2D*) theFile->Get("halo_ecalT_rho");
     halo_ecalT_cscT      = (TH2D*) theFile->Get("halo_ecalT_cscT");
     sideband_dPhi_MET_csc = (TH2D*) theFile->Get("sideband_dPhi_MET_csc") ;
     sideband_dPhi_MET_Jet1 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet1") ;
     sideband_dPhi_MET_Jet2 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet2") ;
     sideband_dPhi_MET_Jet3 = (TH2D*) theFile->Get("sideband_dPhi_MET_Jet3") ;

     noHalo_Time = (TH1D*) theFile->Get("noHalo_Time");
     noHalo_sMaj_Time = (TH2D*) theFile->Get("noHalo_sMaj_Time");
     noHalo_sMin_Time = (TH2D*) theFile->Get("noHalo_sMin_Time");

     noHalo_nXtl_side = (TH1D*) theFile->Get("noHalo_nXtl_side");
     noHalo_nXtl_center = (TH1D*) theFile->Get("noHalo_nXtl_center");

     spike_Eta_Time = (TH2D*) theFile->Get("spike_Eta_Time");
     spike_Phi_Time = (TH2D*) theFile->Get("spike_Phi_Time");
     spike_Pt_Time  = (TH2D*) theFile->Get("spike_Pt_Time");
     spike_MET_Time = (TH2D*) theFile->Get("spike_MET_Time");
     spike_sMaj_sMin = (TH2D*) theFile->Get("spike_sMaj_sMin");
     spike_sMaj_Time = (TH2D*) theFile->Get("spike_sMaj_Time");
     spike_sMin_Time = (TH2D*) theFile->Get("spike_sMin_Time");
     spike_photIso_Time = (TH2D*) theFile->Get("spike_photIso_Time");
     spike_sigIeta = (TH1D*) theFile->Get("spike_sigIeta");
     spike_Time = (TH1D*) theFile->Get("spike_Time");
     spike_sMaj_sigIeta = (TH2D*) theFile->Get("spike_sMaj_sigIeta");
     spike_sMin_sigIeta = (TH2D*) theFile->Get("spike_sMin_sigIeta");
     spike_T_dPhi_gMET_1J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_1J") ;
     spike_T_dPhi_gMET_2J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_2J") ;
     spike_T_dPhi_gMET_0J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_0J") ;

     noSpike_sMaj_Time = (TH2D*) theFile->Get("noSpike_sMaj_Time");
     noSpike_sMin_Time = (TH2D*) theFile->Get("noSpike_sMin_Time");
     noSpike_Time      = (TH1D*) theFile->Get("noSpike_Time");

     notSpike_nXtl = (TH1D*) theFile->Get("notSpike_nXtl");

     pure_Time = (TH1D*) theFile->Get("pure_Time");

     nJets_center  = (TH1D*) theFile->Get("nJets_center");
     nJets_halo    = (TH1D*) theFile->Get("nJets_halo");
     nJets_spike   = (TH1D*) theFile->Get("nJets_spike");
     nJets_cosmic  = (TH1D*) theFile->Get("nJets_cosmic");

     nHL_Eta  = (TH1D*) theFile->Get("nHL_Eta");
     nSpk_Eta = (TH1D*) theFile->Get("nSpk_Eta");
     nCS_Eta  = (TH1D*) theFile->Get("nCS_Eta");

     hBg_D   = (TH2D*) theFile->Get("hBg_D") ;
     hBg_C    = (TH2D*) theFile->Get("hBg_C") ;
     hBg_B    = (TH2D*) theFile->Get("hBg_B") ;
     hBg_A   = (TH2D*) theFile->Get("hBg_A") ;

     cout<<" link all histograms  "<<endl ;
}

void BackgroundStudy::init( string dataName ) {

   //TTree* tr = Input->TreeMap( dataName );
   string dataFileNames ;
   if ( dataName.size() > 0 ) {
      dataFileNames = dataName ;
   } else {
      Input->GetParameters( "TheData", &dataFileNames );
   }
   tr   = Input->GetTree( dataFileNames, "DPAnalysis" );
   cout<<" Get the tree ! "<<endl ;
   // clone the tree for event selection
   tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("runId",        &runId);
   tr->SetBranchAddress("lumiSection",  &lumiSection);
   tr->SetBranchAddress("eventId",      &eventId);

   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("totalNVtx",   &totalNVtx);
   
   tr->SetBranchAddress("nOutTimeHits", &nHaloHits ) ;
   tr->SetBranchAddress("nHaloTrack",   &nHaloTracks ) ;
   tr->SetBranchAddress("haloPhi",      &haloPhi ) ;
   tr->SetBranchAddress("haloRho",      &haloRho ) ;

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );
   tr->SetBranchAddress("nTrkZ0",      &nTrkZ0 );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("timeChi2",    timeChi2 );
   tr->SetBranchAddress("sigmaEta",    sigmaEta );
   tr->SetBranchAddress("sigmaIeta",   sigmaIeta );
   tr->SetBranchAddress("cscdPhi",     cscdPhi );
   tr->SetBranchAddress("cscTime",     cscTime );
   tr->SetBranchAddress("cscRho",     cscRho );
   tr->SetBranchAddress("dtdPhi",     dtdPhi );
   tr->SetBranchAddress("dtdEta",     dtdEta );

   tr->SetBranchAddress("sMinPho",     sMinPho );
   tr->SetBranchAddress("sMajPho",     sMajPho );
   tr->SetBranchAddress("cHadIso",     cHadIso );
   tr->SetBranchAddress("nHadIso",     nHadIso );
   tr->SetBranchAddress("photIso",     photIso );
   tr->SetBranchAddress("phoHoverE",   phoHoverE );

   tr->SetBranchAddress("fSpike",      fSpike );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("nBC",         nBC );

   tr->SetBranchAddress("vtxX",       vtxX );
   tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   tr->SetBranchAddress("vtxDx",       vtxDx );
   tr->SetBranchAddress("vtxDy",       vtxDy );
   tr->SetBranchAddress("vtxDz",       vtxDz );
   
   // initialize selection
   select->Init( tr1 ) ;

   totalN = tr->GetEntries();
   cout<<" from  "<< dataFileNames  <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

}

// analysis template
//void BackgroundStudy::Run( string dataName, double weight ) { 
void BackgroundStudy::Run( double weight ) { 

   int nEvt = 0 ;
   int beginEvent = SkipEvents + 1 ;
   cout<<" Event start from : "<< beginEvent << endl ;

   //select->dR_Check() ;
   for ( int i= beginEvent ; i< totalN ; i++ ) {

       if ( ProcessEvents > 0 && i > ( ProcessEvents + beginEvent - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );
       if ( i % 100000 == 0 && i > 99999 ) printf(" ----- processed %8d Events \n", i ) ;
    
       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       // ControlSelection  - Events containing at least 1 photon 
       bool pass = select->ControlSelection();
       selectJets.clear() ;
       select->GetCollection("Jet", selectJets ) ;
       selectPho.clear() ;
       select->GetCollection("Photon", selectPho ) ;
 
       TLorentzVector met( metPx, metPy, 0, metE)  ;
       TLorentzVector ajet = JetVectorSum( selectJets ) ;
       double dPhi_jMET = ( selectJets.size() > 0 ) ? fabs( met.DeltaPhi( ajet ) ) : -0.1 ;

       //int totalTrk = 0 ;
       //for ( int v=0; v<34; v++) {
       //   totalTrk += nTrkZ0[v] ;
       //}

       // testing for raw information - no cut applied
       for ( int g=0 ; g < nPhotons ; g++ ) {

	   TLorentzVector gP4_ = TLorentzVector( phoPx[g], phoPy[g], phoPz[g], phoE[g] ) ;
           //if ( fabs(gP4_.Eta()) > 1.47 ) continue ;
	   bool haloTag  = ( cscdPhi[g] < 0.05 ) ? true : false  ;
	   //if ( sMajPho[g] > 0.7 && cscdPhi[g] < 0.1 && fabs( gP4_.Eta() ) > 0.75 && fabs(gP4_.Eta()) < 1.47 ) haloTag = true;
	   if ( sMajPho[g] > 0.8 && sMajPho[g] < 1.65 && sMinPho[g] < 0.2 && fabs( gP4_.Eta() ) < 1.47 ) haloTag = true;
	   double cscdPhi_ =  ( cscdPhi[g] > 9. ) ? 3.24 : cscdPhi[g] ;

           if ( fabs(gP4_.Eta()) < 1.47 ) {
              if ( selectJets.size() >= 0 ) h_EB_Time->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 0 ) h_EB_Time0->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 1 ) h_EB_Time1->Fill( seedTime[g] , weight );
              if ( selectJets.size() >= 2 ) h_EB_Time2->Fill( seedTime[g] , weight );
           } 
           if ( fabs(gP4_.Eta()) > 1.47 ) {
              if ( selectJets.size() >= 0 ) h_EE_Time->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 0 ) h_EE_Time0->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 1 ) h_EE_Time1->Fill( seedTime[g] , weight );
              if ( selectJets.size() >= 2 ) h_EE_Time2->Fill( seedTime[g] , weight );
           }

           //if ( selectJets.size() < 1 ) continue ;
	   if ( g ==0 ) h_Pt_MET->Fill( gP4_.Pt(), metE, weight  ) ;
           h_Eta_Time->Fill( gP4_.Eta() , seedTime[g] , weight );

           if ( !haloTag ) {
              for ( int v=0; v<34; v++) {
                double z0_ = (double)(-165 + v*10) ;
                h_Time_nZ0->Fill(  z0_ , seedTime[g] , (weight*nTrkZ0[v]) );
              }
           }

 	   if ( fabs(seedTime[g]) > 1.5 ) h_Phi_Time->Fill( gP4_.Phi() , seedTime[g] , weight );
	   h_cscdPhi_cscTime->Fill( cscdPhi_, cscTime[g] , weight  ) ;
	   h_cscdPhi_rho->Fill( cscdPhi_, cscRho[g], weight  ) ;
           if ( fabs( gP4_.Eta() ) < 1.45 ) {
   	      h_cscdPhi_Time->Fill( cscdPhi_, seedTime[g] , weight  ) ;
	      h_ecalT_cscT->Fill( seedTime[g], cscTime[g] , weight  ) ;
  	      h_sMin_Time_EB->Fill( sMinPho[g] , seedTime[g] , weight );
	      h_sMaj_Time_EB->Fill( sMajPho[g] , seedTime[g] , weight );
  	      h_sMin_sigIeta_EB->Fill( sMinPho[g] , sigmaIeta[g] , weight );
	      h_sMaj_sigIeta_EB->Fill( sMajPho[g] , sigmaIeta[g] , weight );
	      h_sigIeta_Time_EB->Fill( sigmaIeta[g], seedTime[g] , weight  ) ;
	      h_Pt_Time_EB->Fill( gP4_.Pt(), seedTime[g] , weight  ) ;
	      h_MET_Time_EB->Fill( metE, seedTime[g] , weight  ) ;
	      h_sMaj_sMin_EB->Fill( sMajPho[g] , sMinPho[g] , weight );
	      h_nXtl_Pt_EB->Fill( nXtals[g],  gP4_.Pt() , weight );
              if ( fabs(gP4_.Phi()) > 0.2 && fabs(gP4_.Phi()) < 3.12 && !haloTag)  {
                 h_Time_EB->Fill( seedTime[g] , weight ) ;
              }
           }
           if ( fabs( gP4_.Eta() ) > 1.5 ) {
  	      h_sMin_Time_EE->Fill( sMinPho[g] , seedTime[g] , weight );
	      h_sMaj_Time_EE->Fill( sMajPho[g] , seedTime[g] , weight );
  	      h_sMin_sigIeta_EE->Fill( sMinPho[g] , sigmaIeta[g] , weight );
	      h_sMaj_sigIeta_EE->Fill( sMajPho[g] , sigmaIeta[g] , weight );
	      h_sigIeta_Time_EE->Fill( sigmaIeta[g], seedTime[g] , weight  ) ;
	      h_Pt_Time_EE->Fill( gP4_.Pt(), seedTime[g] , weight  ) ;
	      h_MET_Time_EE->Fill( metE, seedTime[g] , weight  ) ;
              if ( haloTag ) h_haloTime_EE->Fill( seedTime[g] , weight ) ;
              // check ghost bunch collision
              if ( fabs(gP4_.Phi()) > 0.2 && fabs(gP4_.Phi()) < 3.12 )  {
                 h_Time_EE->Fill( seedTime[g] , weight ) ;
              }
           }

	   h_sMaj_Eta->Fill( sMajPho[g] , gP4_.Eta() , weight ) ;
	   h_nXtl_Eta->Fill( nXtals[g],  gP4_.Eta() , weight );
	   if ( sMajPho[g] > 0.4 ) h_sMaj_Phi->Fill(sMajPho[g] , gP4_.Phi() , weight ) ;
	   double nHIso = max( nHadIso[g] - (0.04*gP4_.Pt()) , 0. ) ;
	   double phIso = max( photIso[g] - (0.005*gP4_.Pt()) , 0. ) ;
           h_cHadIso_Time->Fill( cHadIso[g] , seedTime[g] , weight ) ;
           h_nHadIso_Time->Fill( nHIso , seedTime[g] , weight ) ;
           h_photIso_Time->Fill( phIso , seedTime[g] , weight ) ;

       }

       // constrol samples - At least 1 photon events  
       if ( !pass ) continue ;
       nEvt++; 

       //cout<<" EVT# : "<< nEvt <<endl ;
       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
              int k = selectPho[kk].first ;
	      //TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;
	      TLorentzVector gP4_ = selectPho[kk].second ; 
              double dPhi_gMET = fabs( gP4_.DeltaPhi( met ) );
	      double cscdPhi_ =  ( cscdPhi[k] > 9. ) ? 3.24 : cscdPhi[k] ;

              // Test Halo Stuff
              if ( fabs(gP4_.Eta()) < 1.47 ) {
                 if ( cscdPhi[k] < 0.05 ) haloTest_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight) ;
    	         if ( sMajPho[k] > 0.8 && sMajPho[k] < 1.65 && sMinPho[k] < 0.2 ) haloTest_cscdPhi->Fill( cscdPhi_ , weight ) ;
              }

	      // Define the Tag and Check the efficiency 
	      bool haloTag  = ( cscdPhi[k] < 0.05 ) ? true : false  ;
	      //if ( sMajPho[k] > 0.7 && cscdPhi[k] < 0.1  && fabs( gP4_.Eta() ) > 0.75 && fabs(gP4_.Eta()) < 1.47 ) haloTag = true;
	      if ( sMajPho[k] > 0.8 && sMajPho[k] < 1.65 && sMinPho[k] < 0.2 && fabs( gP4_.Eta() ) < 1.47 ) haloTag = true;

	      bool spikeTag = ( nXtals[k] < 7 && !haloTag ) ? true : false  ;
	      if ( sMajPho[k] < 0.6 && sMinPho[k] < 0.17 && fabs( gP4_.Eta() ) < 1.47 ) spikeTag = true;

              bool cosmicTag = ( dtdEta[k] < 0.1 && dtdPhi[k] < 0.1 && !haloTag ) ? true : false ;
	      bool ghostTag = ( haloTag || spikeTag || cosmicTag ) ? true : false ;

              // Test for ABCD region
              if ( !ghostTag ) {
                 if ( metE > jetCuts[4] && selectJets.size() >= jetCuts[2] )     abcd_Pt_Time->Fill( gP4_.Pt() , seedTime[k], weight ) ;
                 if ( selectPho[0].second.Pt() > 80. && selectJets.size() >= jetCuts[2] ) abcd_MET_Time->Fill( metE, seedTime[k], weight ) ;
                 if ( metE > jetCuts[4] && selectPho[0].second.Pt() > 80. ) abcd_NJet_Time->Fill( selectJets.size(), seedTime[k], weight ) ;
		 if ( seedTime[k] < -3 ) { 
                    ab_Pt_MET->Fill( gP4_.Pt(), metE ) ;
                    ab_dPhi_gMET->Fill( dPhi_gMET ) ;
                 }
		 if ( seedTime[k] >  3 ) { 
                    cd_Pt_MET->Fill( gP4_.Pt(), metE ) ;
                    cd_dPhi_gMET->Fill( dPhi_gMET ) ;
                 }
                 if ( fabs(seedTime[k]) < 2 && kk == 0) { // no double counting event
		    if ( selectJets.size() == 0 ) noG_nVtx_0J->Fill( totalNVtx, weight) ;
		    if ( selectJets.size() == 1 ) noG_nVtx_1J->Fill( totalNVtx, weight) ;
		    if ( selectJets.size() >= 2 ) noG_nVtx_2J->Fill( totalNVtx, weight) ;
                 }
              }

              if ( selectPho.size() < 2 ) {
                 int njets = ( selectJets.size() > 9 ) ? 9 : (int)selectJets.size() ;
                 if ( fabs(seedTime[k]) < 2. && ! ghostTag ) 
                                   nJets_center->Fill( njets , weight );
                 if ( haloTag    ) nJets_halo->Fill(   njets , weight );
                 if ( spikeTag   ) nJets_spike->Fill(  njets , weight );
                 if ( cosmicTag  ) nJets_cosmic->Fill( njets , weight );
              }

              // ******************
              //   Region A and B - Real Photon: -0.024 +/- 0.426
              // ******************
              if ( seedTime[k] < -3.00 && seedTime[k] > -10. && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
              //if ( seedTime[k] < -3.006 && metE > jetCuts[4] ) {
              //if ( seedTime[k] < -2.154 && metE > jetCuts[4] && selectJets.size() > 0 ) {

                 // Region B
		 if ( metE > jetCuts[4] ) {
		 //if ( selectJets.size() > 1) {
		 //if ( selectPho[0].second.Pt() > 80. ) {
	  	    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;

		    hBg_B->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_B->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_B->Fill( ih, 2.5, weight );
		    if ( cosmicTag ) hBg_B->Fill( ih, 3.5, weight );
                    if ( !ghostTag ) b_nVtx->Fill( totalNVtx, weight ) ;
                    for ( int v=0; v<34; v++) {
                        double z0_ = (double)(-165 + v*10) ;
                        if ( !ghostTag ) b_Z0->Fill(  z0_ ,  (weight*nTrkZ0[v]) );
                    }
                 }
                 // Region A
		 if ( metE < jetCuts[4] ) {
		 //if ( selectJets.size() == 1) {
		 //if ( selectPho[0].second.Pt() < 80. ) {
	  	    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;

		    hBg_A->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_A->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_A->Fill( ih, 2.5, weight );
		    if ( cosmicTag ) hBg_A->Fill( ih, 3.5, weight );
                    if ( !ghostTag ) a_nVtx->Fill( totalNVtx, weight ) ;
                    for ( int v=0; v<34; v++) {
                        double z0_ = (double)(-165 + v*10) ;
                        if ( !ghostTag ) a_Z0->Fill(  z0_ ,  (weight*nTrkZ0[v]) );
                    }
                 }
              }
              // ******************
              //   Region C and D
              // ******************
              //if ( selectPho[0].second.Pt() > 80. && metE > jetCuts[4] && selectJets.size() > 0 ) {
              if ( seedTime[k] > 3.0 && seedTime[k] < 10.0 && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
                 // Region D
		 if ( metE > jetCuts[4] ) {
                    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;

                    hBg_D->Fill( ih, 0.5, weight );
                    if ( haloTag  ) hBg_D->Fill( ih, 1.5, weight );
                    if ( spikeTag ) hBg_D->Fill( ih, 2.5, weight );
		    if ( cosmicTag ) hBg_D->Fill( ih, 3.5, weight );
                    if ( !ghostTag ) d_nVtx->Fill( totalNVtx, weight ) ;
                    for ( int v=0; v<34; v++) {
                        double z0_ = (double)(-165 + v*10) ;
                        if ( !ghostTag ) d_Z0->Fill(  z0_ ,  (weight*nTrkZ0[v]) );
                    }
                 }
                 // Check the background estimation at MET > 60 GeV, t < -3ns Region
                 // Region C
		 if ( metE < jetCuts[4] ) {
                    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;

		    hBg_C->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_C->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_C->Fill( ih, 2.5, weight );
		    if ( cosmicTag ) hBg_C->Fill( ih, 3.5, weight );
                    if ( !ghostTag ) c_nVtx->Fill( totalNVtx, weight ) ;
                    for ( int v=0; v<34; v++) {
                        double z0_ = (double)(-165 + v*10) ;
                        if ( !ghostTag ) c_Z0->Fill(  z0_ ,  (weight*nTrkZ0[v]) );
                    }
                 }
              }

              // ******************
              //   Region for normalizing ABCD
              // ******************
              if (seedTime[k] > -1.5 && seedTime[k] < 1.5 && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3] ) {
                 if ( !ghostTag && metE <= jetCuts[4]) l_nVtx->Fill( totalNVtx, weight ) ;
                 if ( !ghostTag && metE  > jetCuts[4]) h_nVtx->Fill( totalNVtx, weight ) ;
                 for ( int v=0; v<34; v++) {
                     double z0_ = (double)(-165 + v*10) ;
                     if ( !ghostTag ) h_Z0->Fill(  z0_ ,  (weight*nTrkZ0[v]) );
                 }
              }

              if ( selectPho[0].second.Pt() > 80. ) {
                 obsTime->Fill( seedTime[k], weight );

   	         double phIso = max( photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
		 // Look at the sideband of time spectrum 
		 if ( seedTime[k]  > 2. || seedTime[k] < -3 ) {
     	            sideband_Pt_nJet->Fill( gP4_.Pt() , selectJets.size() , weight );
     	            sideband_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight );
		    sideband_sMaj_Phi->Fill( sMajPho[k] , gP4_.Phi() , weight );
		    sideband_sMaj_Eta->Fill( sMajPho[k] , gP4_.Eta() , weight );
		    sideband_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
		    sideband_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
		    sideband_nXtl_Eta->Fill( nXtals[k], gP4_.Eta() , weight );
		    sideband_cscT_ecalT->Fill( cscTime[k] , seedTime[k] , weight );
		    sideband_photIso_cscdPhi->Fill( phIso , cscdPhi_ , weight ) ;
		    sideband_dtdPhidEta->Fill( dtdPhi[k] , dtdEta[k], weight );
                    double dtdR = sqrt( (dtdPhi[k]*dtdPhi[k]) + (dtdEta[k]*dtdEta[k]) ) ;
		    sideband_dtdR->Fill( dtdR , weight );
		    sideband_sMaj->Fill( sMajPho[k] , weight ) ;
		    sideband_dPhi_MET_csc->Fill( dPhi_gMET, cscdPhi_ ) ;
		    if ( seedTime[k] > 0 ) sideband_cscdPhi_u->Fill( cscdPhi_ , weight );
		    if ( seedTime[k] < 0 ) sideband_cscdPhi_d->Fill( cscdPhi_ , weight );
		    if ( seedTime[k] > 0 ) sideband_nXtl_u->Fill( nXtals[k] , weight );
		    if ( seedTime[k] < 0 ) sideband_nXtl_d->Fill( nXtals[k] , weight );

		    if ( selectJets.size() == 0 ) sideband_dPhi_MET_Jet1->Fill( dPhi_gMET, dPhi_jMET, weight ) ;
		    if ( selectJets.size() == 1 ) sideband_dPhi_MET_Jet2->Fill( dPhi_gMET, dPhi_jMET, weight ) ;
		    if ( selectJets.size() >= 2 ) sideband_dPhi_MET_Jet3->Fill( dPhi_gMET, dPhi_jMET, weight ) ;

		    if ( selectJets.size() == 0 && kk == 0 ) sideband_nVtx_0J->Fill( totalNVtx, weight) ;
		    if ( selectJets.size() == 1 && kk == 0 ) sideband_nVtx_1J->Fill( totalNVtx, weight) ;
		    if ( selectJets.size() >= 2 && kk == 0 ) sideband_nVtx_2J->Fill( totalNVtx, weight) ;
                 }

            
                 // The result of halo tagging and spike tagging 
                 if ( cosmicTag ) {
                    cosmic_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    cosmic_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    cosmic_Pt_Time->Fill( gP4_.Pt() , seedTime[k] , weight );
		    cosmic_MET_Time->Fill( metE , seedTime[k] , weight );
		    cosmic_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    cosmic_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    cosmic_Time->Fill( seedTime[k] , weight ) ;
                    if ( fabs(seedTime[k]) > 1.5 ) {
		       cosmic_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		       cosmic_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		       cosmic_photIso_Time->Fill( phIso, seedTime[k] , weight ) ;
		       cosmic_nXtl->Fill( nXtals[k] , weight );
                    }
                 }
                 if ( haloTag ) {
                    halo_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    halo_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    halo_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    halo_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    halo_Time->Fill( seedTime[k] , weight ) ;
		    halo_photIso_Time->Fill( phIso, seedTime[k] , weight ) ;
	            halo_ecalT_rho->Fill( seedTime[k], cscRho[k], weight  ) ;
	            halo_ecalT_cscT->Fill( seedTime[k], cscTime[k] , weight  ) ;
                    // Only check the out-of-time region
	            if ( fabs(seedTime[k]) > 1.5 ) {
		       halo_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		       halo_sMaj_sigIeta->Fill( sMajPho[k], sigmaIeta[k] , weight ) ;
		       halo_sMin_sigIeta->Fill( sMinPho[k], sigmaIeta[k] , weight ) ;
		       halo_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
                       halo_eta_rho->Fill( gP4_.Eta(), cscRho[k], weight  ) ;
		       halo_eta_sMaj->Fill( gP4_.Eta() , sMajPho[k], weight ) ;
		       halo_Pt_Time->Fill( gP4_.Pt() , seedTime[k] , weight );
		       halo_MET_Time->Fill( metE , seedTime[k] , weight );
                    }
		    if ( selectJets.size() == 0 ) halo_T_dPhi_gMET_0J->Fill( seedTime[k] , dPhi_gMET, weight ) ;
		    if ( selectJets.size() == 1 ) halo_T_dPhi_gMET_1J->Fill( seedTime[k] , dPhi_gMET, weight ) ;
		    if ( selectJets.size() >= 2 ) halo_T_dPhi_gMET_2J->Fill( seedTime[k] , dPhi_gMET, weight ) ;
		    if ( selectJets.size() == 0 ) halo_Eta_Time_0J->Fill( gP4_.Eta() , seedTime[k] , weight ) ;
		    if ( selectJets.size() == 1 ) halo_Eta_Time_1J->Fill( gP4_.Eta() , seedTime[k] , weight ) ;

                 } else {
		    noHalo_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    noHalo_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    noHalo_Time->Fill( seedTime[k] , weight ) ;

		    if ( fabs( seedTime[k] ) > 3. ) {
                       noHalo_nXtl_side->Fill( nXtals[k] , weight ) ;
                    } else  {
                       noHalo_nXtl_center->Fill( nXtals[k] , weight ) ;
                    }
                 }
                 
                 if ( spikeTag ) {
                    spike_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    spike_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    spike_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    spike_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    spike_Time->Fill( seedTime[k] , weight ) ;
		    spike_photIso_Time->Fill( phIso, seedTime[k] , weight ) ;
	            if ( fabs(seedTime[k]) > 1.5 ) {
		       spike_Pt_Time->Fill( gP4_.Pt() , seedTime[k] , weight );
		       spike_MET_Time->Fill( metE , seedTime[k] , weight );
		       spike_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		       spike_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		       spike_sMaj_sigIeta->Fill( sMajPho[k], sigmaIeta[k] , weight ) ;
		       spike_sMin_sigIeta->Fill( sMinPho[k], sigmaIeta[k] , weight ) ;
                    }
		    //double dPhi_gMET = gP4_.DeltaPhi( met ) ;
		    if ( selectJets.size() == 0 ) spike_T_dPhi_gMET_0J->Fill( seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() == 1 ) spike_T_dPhi_gMET_1J->Fill( seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() >= 2 ) spike_T_dPhi_gMET_2J->Fill( seedTime[k] , dPhi_gMET ) ;
                 } else {
		    noSpike_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    noSpike_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    noSpike_Time->Fill( seedTime[k] , weight ) ;
                 }
                 if ( sMajPho[k] < 0.7 && cscdPhi[k] > 0.1 ) notSpike_nXtl->Fill( nXtals[k] , weight );
 
                 if ( !ghostTag ) pure_Time->Fill( seedTime[k] , weight );

                 // 
                 if ( fabs( gP4_.Eta() ) < 1.3 && seedTime[k] < -1.) {
                     Double_t parLU[3] = { 1.4, 1.3, -1.0 } ;
		     Double_t parLD[3] = { 1.4, 1.5, -1.5 } ;
		     Double_t parRU[3] = { -1.4, 1.3, -1.0 } ;
		     Double_t parRD[3] = { -1.4, 1.5, -1.5 } ;
		     Double_t etaA[1]  = { gP4_.Eta() } ;
		     Double_t Cut_LU =  HaloFunction( etaA, parLU ) ;
		     Double_t Cut_LD =  HaloFunction( etaA, parLD ) ;
		     Double_t Cut_RU =  HaloFunction( etaA, parRU ) ;
		     Double_t Cut_RD =  HaloFunction( etaA, parRD ) ;
		     //cout<<" eta: "<< gP4_.Eta() <<" T : "<< seedTime[k] <<endl ;
		     //cout<<" LU: "<< Cut_LU <<" LD: "<< Cut_LD << endl ; 
		     //cout<<" RU: "<< Cut_RU <<" LD: "<< Cut_RD << endl ; 
		     bool fromL = ( seedTime[k] > Cut_LD && seedTime[k] < Cut_LU ) ;
                     bool fromR = ( seedTime[k] > Cut_RD && seedTime[k] < Cut_RU ) ;
                     if ( fromL || fromR ) {
                        haloFN_Eta_Time->Fill( gP4_.Eta(), seedTime[k] , weight ) ;
                        haloFN_Phi_Time->Fill( gP4_.Phi(), seedTime[k] , weight ) ;
			haloFN_Pt_Time->Fill( gP4_.Pt(), seedTime[k] , weight ) ;
			haloFN_MET_Time->Fill( metE, seedTime[k] , weight ) ;
			haloFN_sMaj_sMin->Fill( sMajPho[k], sMinPho[k],  weight ) ;
			haloFN_cscdPhi->Fill( cscdPhi_ ,  weight ) ;
                     }
                 }

              }
              // Current Halo-Control Sample - for efficiency and fake rate study
              // **********************************************
              //   Region for Efficiency and fake rate study
              // **********************************************
              if ( fabs( gP4_.Phi() ) < 0.2 || fabs( fabs(gP4_.Phi()) - 3.14 ) < 0.2  ) {
                 if ( selectJets.size() < 2 && seedTime[k] > 3 ) {
                    if ( fabs(gP4_.Eta())  < 0.37                            ) haloCD_Pt_eta[0]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloCD_Pt_eta[1]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloCD_Pt_eta[2]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloCD_Pt_eta[3]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta())  < 0.37                            ) haloCD_MET_eta[0]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloCD_MET_eta[1]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloCD_MET_eta[2]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloCD_MET_eta[3]->Fill( metE , weight);
                 }
                 if ( selectJets.size() < 2 && seedTime[k] < -3 ) {
                    if ( fabs(gP4_.Eta())  < 0.37                            ) haloAB_Pt_eta[0]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloAB_Pt_eta[1]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloAB_Pt_eta[2]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloAB_Pt_eta[3]->Fill( gP4_.Pt() , weight);
                    if ( fabs(gP4_.Eta())  < 0.37                            ) haloAB_MET_eta[0]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloAB_MET_eta[1]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloAB_MET_eta[2]->Fill( metE , weight);
                    if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloAB_MET_eta[3]->Fill( metE , weight);
                 }
              }

              if ( metE < jetCuts[4] && selectJets.size() < 1 ) {

                 // Halo-Control Sample
                 if ( fabs( gP4_.Phi() ) < 0.1 || fabs( fabs(gP4_.Phi()) - 3.14 ) < 0.1  ) {
                    if ( fabs( gP4_.Eta() ) < 1.4 &&  seedTime[k]  < -3 && nXtals[k] > 7 ) {
                       haloCS_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight ) ;
                       haloCS_sMaj_Eta->Fill( sMajPho[k] , gP4_.Eta() , weight ) ;
		       haloCS_sMaj_Phi->Fill( sMajPho[k] , gP4_.Phi() , weight );
		       haloCS_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
                       double cscdPhi_ =  ( cscdPhi[k] > 9. ) ? 3.24 : cscdPhi[k] ;
                       haloCS_cscdPhi->Fill( cscdPhi_ , weight ) ;
	               if ( sMajPho[k] > 0.8 && sMajPho[k] < 1.65 && sMinPho[k] < 0.2 ) haloCS_cscdPhi1->Fill( cscdPhi_ , weight ) ;

		       // Count efficiency in different eta slice 
		       double haloEta = ( fabs(gP4_.Eta()) > 1.67 ) ? 1.67 : fabs(gP4_.Eta()) ;
		       halo_Eta[0]->Fill( haloEta, weight ) ;

	  	       if ( haloTag ) {
                          haloCS_Eta_Time1->Fill( gP4_.Eta() , seedTime[k] , weight );
			  halo_Eta[1]->Fill( haloEta, weight ) ;
		       }
                    }
 
                    // Check on sMajor for halo in different eta
                    if ( fabs(gP4_.Eta()) < 0.28 )                            sMaj_eta[0]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) sMaj_eta[1]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) sMaj_eta[2]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) sMaj_eta[3]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) sMaj_eta[4]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) sMaj_eta[5]->Fill( sMajPho[k] , weight ) ;
		    if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) sMaj_eta[6]->Fill( sMajPho[k] , weight ) ;

                    if ( cscdPhi[k] < 0.05 ) {
                       if ( fabs(gP4_.Eta()) < 0.28 )                            sMaj_eta_csc[0]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) sMaj_eta_csc[1]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) sMaj_eta_csc[2]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) sMaj_eta_csc[3]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) sMaj_eta_csc[4]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) sMaj_eta_csc[5]->Fill( sMajPho[k] , weight ) ;
		       if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) sMaj_eta_csc[6]->Fill( sMajPho[k] , weight ) ;
                    }

                 }

                 // Current Spike-Control sample
                 if ( fabs( gP4_.Eta() ) < 1.4 &&  seedTime[k]  < -3 && sMajPho[k] < 0.7 && cscdPhi[k] > 0.1 && metE < jetCuts[4] ) {
                    spikeCS_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight ) ;
		    spikeCS_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    spikeCS_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    spikeCS_nXtl_Eta->Fill( nXtals[k], gP4_.Eta() , weight ) ;
		    spikeCS_nXtl->Fill( nXtals[k] , weight ) ;

		    // Count efficiency in different eta slice 
		    double SpikeEta = ( fabs(gP4_.Eta()) > 1.67 ) ? 1.67 : fabs(gP4_.Eta()) ;
		    spike_Eta[0]->Fill( SpikeEta, weight ) ;

		    if ( spikeTag ) { 
                       spikeCS_Eta_Time1->Fill( gP4_.Eta() , seedTime[k] , weight );
                       spike_Eta[1]->Fill( SpikeEta, weight )  ;
                    }
                 }
              }

 
              // signal sample - require MET cut 
              //if ( pass && metE > jetCuts[4] ) {
              if ( selectPho[0].second.Pt() > 80. && metE > jetCuts[4] && selectJets.size() >= jetCuts[2] && selectJets.size() < jetCuts[3]  ) {
              //if ( selectPho[0].second.Pt() > 80. && metE > jetCuts[4] && selectJets.size() < 1 ) {
		 double dPhi_gMET = gP4_.DeltaPhi( met ) ;
		 double nHIso = max( nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
		 double phIso = max( photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;

		 sg_Time->Fill( seedTime[k], weight );
	         sg_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		 sg_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		 sg_sigIeta_Time->Fill( sigmaIeta[k], seedTime[k] , weight ) ;
		 sg_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
		 sg_sMaj_Eta->Fill(  sMajPho[k] , gP4_.Eta() , weight );
		 sg_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
		 sg_sMin_Eta->Fill(  sMinPho[k] , gP4_.Eta() , weight );
		 sg_nXtl->Fill( nXtals[k] , weight );
		 sg_nXtl_Eta->Fill( nXtals[k] , gP4_.Eta(), weight );
		 sg_cscdPhi->Fill( cscdPhi_, weight  ) ;
		 sg_dPhi_MET_csc->Fill( dPhi_gMET, cscdPhi_ ) ;
	         sg_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight );
		 if ( selectJets.size() == 1 ) sg_dPhi_MET_Jet1->Fill( dPhi_gMET, dPhi_jMET ) ;
		 if ( selectJets.size() == 2 ) sg_dPhi_MET_Jet2->Fill( dPhi_gMET, dPhi_jMET ) ;
		 if ( selectJets.size() >= 3 ) sg_dPhi_MET_Jet3->Fill( dPhi_gMET, dPhi_jMET ) ;
                 if ( fabs( seedTime[k]) < 2. ) {
   		    sg_sMaj_sigIeta->Fill( sMajPho[k], sigmaIeta[k] , weight ) ;
		    sg_sMin_sigIeta->Fill( sMinPho[k], sigmaIeta[k] , weight ) ;
                 }
                 if ( !ghostTag ) {
		    sel_cHadIso_Time->Fill( cHadIso[k] , seedTime[k] , weight ) ;
		    sel_nHadIso_Time->Fill( nHIso , seedTime[k] , weight ) ;
		    sel_photIso_Time->Fill( phIso , seedTime[k] , weight ) ;
		    sel_photIso_sMaj->Fill( phIso , sMajPho[k] , weight ) ;
		    sel_photIso_sMin->Fill( phIso , sMinPho[k] , weight ) ;
		    sel_photIso_sigIeta->Fill( phIso , sigmaIeta[k] , weight ) ;
	            sel_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    sel_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    sel_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
		    sel_sMaj_Eta->Fill( sMajPho[k] , gP4_.Eta() , weight );
		    sel_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
		    sel_sMin_Eta->Fill( sMinPho[k] , gP4_.Eta() , weight );
		    sel_Time->Fill( seedTime[k] , weight ) ;
                    if ( fabs( seedTime[k] ) > 1.5 ) sel_weirdXtl->Fill( gP4_.Eta(), gP4_.Phi()  ) ;
		    if ( selectJets.size() == 1 ) sel_T_dPhi_gMET_1J->Fill( seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() == 2 ) sel_T_dPhi_gMET_2J->Fill( seedTime[k] , dPhi_gMET ) ;
		    if ( selectJets.size() >= 3 ) sel_T_dPhi_gMET_3J->Fill( seedTime[k] , dPhi_gMET ) ;
		 }
                 if ( haloTag  ) sg_Time_halo->Fill( seedTime[k] , weight ) ;
		 if ( haloTag  ) sg_Eta_Time_halo->Fill( gP4_.Eta() , seedTime[k] , weight );

		 if ( spikeTag ) sg_Time_spike->Fill( seedTime[k] , weight ) ;
		 if ( spikeTag ) sg_Eta_Time_spike->Fill( gP4_.Eta() , seedTime[k] , weight );

                 if ( cosmicTag ) sg_Time_cosmic->Fill( seedTime[k] , weight ) ;

                 // Good photon behavior
		 bool passCSSelect = false ;
		 if ( fabs(seedTime[k]) < 1. && isData == 1 && selectJets.size()  > 1 ) passCSSelect = true ;
		 if (       seedTime[k] > 1.7 && isData == 0 ) passCSSelect = true ;
                 //if ( seedTime[k] > -1. && seedTime[k] < 2. && fabs( gP4_.Phi()) > 0.2 && fabs( fabs(gP4_.Phi()) - 3.14) > 0.2 ) {
                 if ( passCSSelect ) {
                    
		    cs_dtdPhidEta->Fill( dtdPhi[k] , dtdEta[k], weight );
      		    cs_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    cs_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    cs_sigIeta_Time->Fill( sigmaIeta[k], seedTime[k] , weight ) ;
		    cs_nXtl->Fill( nXtals[k] , weight );
		    cs_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight );
		    cs_cscdPhi->Fill( cscdPhi_, weight  ) ;
		    cs_cHadIso_Time->Fill( cHadIso[k] , seedTime[k] , weight ) ;
		    cs_nHadIso_Time->Fill( nHIso , seedTime[k] , weight ) ;
		    cs_photIso_Time->Fill( phIso , seedTime[k] , weight ) ;
                    // Check mis-tagging rate from real photon
                    nCS_Eta->Fill( fabs(gP4_.Eta()) , weight )  ;
                    // For Halo
                    if ( haloTag ) nHL_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;
                    // For Spike -  need to exclude halo
                    if ( spikeTag ) nSpk_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;

                 }

              }

       } // end of photon looping 
   } // end of event looping
 

   select->PrintCutFlow() ;
   writeHist = true ;
   theFile->cd() ;
   if ( writeHist ) Write() ;
}  

void BackgroundStudy::DrawHistograms() {

   //gSystem->cd( hfolder.c_str() ) ;
   //gSystem->mkdir("plots") ;
   //gSystem->cd("../") ;
   //hfolder += "plots/" ;

   h_draw->SetPath( hfolder );

   // Halo Studies
   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);

   // DOE Plots
   h_draw->SetPlotStyle(false) ; // Turn off the stats box
   /*
   h_draw->Draw(   h_EB_Time,      "h_EB_Time",     "Time from EB ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time0,     "h_EB_Time0",     "Time from EB for 0 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time1,     "h_EB_Time1",     "Time from EB for 1 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time2,     "h_EB_Time2",     "Time from EB for 2 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time,      "h_EE_Time",     "Time from EE ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time0,     "h_EE_Time0",     "Time from EE for 0 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time1,     "h_EE_Time1",     "Time from EE for 1 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time2,     "h_EE_Time2",     "Time from EE for 2 jet event", "", "logY", 0.95, 1 ) ;
   */
   h_draw->Draw(        h_EB_Time, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time, "h_EB_Time", 0.75, 4 , 100./ max( 100., h_EE_Time->Integral() ) ) ;
   h_draw->Draw(        h_EB_Time0, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time0->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time0, "h_EB_Time0", 0.75, 4 , 100./ max( 100., h_EE_Time0->Integral() ) ) ;
   h_draw->Draw(        h_EB_Time1, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time1->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time1, "h_EB_Time1", 0.75, 4 , 100./ max( 100., h_EE_Time1->Integral() ) ) ;
   h_draw->Draw(        h_EB_Time2, "",     "Time from EB ", "", "logY", 0.95, 2, 100./max( 100., h_EB_Time2->Integral()) ) ;
   h_draw->DrawAppend(  h_EE_Time2, "h_EB_Time2", 0.75, 4 , 100./ max( 100., h_EE_Time2->Integral() ) ) ;

   if ( isData == 1 ) {
   h_draw->SetHistoInfo(2) ; // set histo lineWidth

   TLegend* leg3  = new TLegend(.6, .7, .9, .9 );
   leg3->AddEntry( h_Time_EB, " EB" , "L" ) ;
   leg3->AddEntry( h_Time_EE, " EE" , "L" ) ;
   leg3->AddEntry( h_haloTime_EE, " EE" , "L" ) ;
   //h_Time_EB->SetTitle( "" ) ;
   h_draw->Draw(       h_Time_EB, "",             " Ecal Time (ns)", "", "logY", 0.95, 2 );
   h_draw->DrawAppend( h_Time_EE, "",  0.8, 4 , 1. ) ;
   h_draw->DrawAppend( h_haloTime_EE, "h_Time_EB_EE",  0.65, 6 , 1.,  leg3  ) ;
   } 

   h_draw->SetHistoInfo(1) ;

   h_draw->Draw2D( h_Eta_Time,    "h_Eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Phi_Time,    "h_Phi_Time",    "#phi", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_cscdPhi_Time,"h_cscdPhi_Time","d#phi", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cscdPhi_cscTime,"h_cscdPhi_cscTime","d#phi", "CSC Time (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_ecalT_cscT,   "h_ecalT_cscT","Ecal Time(ns)", "CSC Time (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cHadIso_Time, "h_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_nHadIso_Time, "h_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_photIso_Time, "h_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EB,   "h_sMaj_Time_EB",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EB,   "h_sMin_Time_EB",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMaj_sigIeta_EB,"h_sMaj_sigIeta_EB",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_sigIeta_EB,"h_sMin_sigIeta_EB",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EB,"h_sigIeta_Time_EB","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EB,     "h_Pt_Time_EB", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EB,    "h_MET_Time_EB", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cscdPhi_rho,    "h_cscdPhi_rho", "#Delta#Phi( cscSeg, #gamma) ", "#rho", "logZ", 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EE,   "h_sMaj_Time_EE",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EE,   "h_sMin_Time_EE",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMaj_sigIeta_EE,   "h_sMaj_sigIeta_EE",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_sigIeta_EE,   "h_sMin_sigIeta_EE",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EE,"h_sigIeta_Time_EE","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EE,     "h_Pt_Time_EE", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EE,    "h_MET_Time_EE", "MET", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_Pt_MET,      "h_Pt_MET", "P_T", " MET", "logZ" , 8 ) ;
   h_draw->Draw2D( h_sMaj_Eta,    "h_sMaj_Eta",    "sMaj", "#eta ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_Phi,    "h_sMaj_Phi",    "sMaj", "#phi ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_sMin_EB,"h_sMaj_sMin_EB",   "sMaj", "sMin ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_nXtl_Eta,    "h_nXtl_Eta",    "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw2D( h_nXtl_Pt_EB,  "h_nXtl_Pt_EB",     "N crystals", "P_{T}", "logZ", 8  ) ;

   h_draw->Draw2D( h_Time_nZ0,     "h_Time_nZ0", "nTracks in Z0", "EcalTime (ns)",  "logZ" , 8 ) ;

   h_draw->Draw2D( abcd_Pt_Time,   "abcd_Pt_Time", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_MET_Time,  "abcd_MET_Time", "MET", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( abcd_NJet_Time, "abcd_NJet_Time", "NJet", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( ab_Pt_MET,      "ab_Pt_MET", "P_T", "MET", "logZ" , 8 ) ;
   h_draw->Draw2D( cd_Pt_MET,      "cd_Pt_MET", "P_T", "MET", "logZ" , 8 ) ;
   h_draw->Draw(   ab_dPhi_gMET,   "ab_dPhi_gMET", "#Delta#Phi(#gamma, MET) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   cd_dPhi_gMET,   "cd_dPhi_gMET", "#Delta#Phi(#gamma, MET) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( haloTest_sMaj_sMin,   "haloTest_sMaj_sMin",  "sMaj", "sMin ",  "logZ", 8 ) ;
   h_draw->Draw(   haloTest_cscdPhi,     "haloTest_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;

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
   h_draw->Draw2D( sg_sMaj_sigIeta,"sg_sMaj_sigIeta",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMin_sigIeta,"sg_sMin_sigIeta",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( sg_dPhi_MET_csc, "sg_dPhi_MET_csc",  "dPhi( photon, MET)", " dPhi( photon, cscseg)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet1, "sg_dPhi_MET_Jet1",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet2, "sg_dPhi_MET_Jet2",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_dPhi_MET_Jet3, "sg_dPhi_MET_Jet3",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sg_sMaj_sMin,   "sg_sMaj_sMin",  "sMaj", "sMin ",  "logZ", 8 ) ;

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

   //gStyle->SetOptStat("e");
   gPad->SetGridx() ;
   leg2->Clear() ;
   leg2->AddEntry( obsTime,     "All" , "L" ) ;
   leg2->AddEntry( pure_Time,   "NoBackgroud" , "L" ) ;
   leg2->AddEntry( halo_Time,   "HaloTagged" , "L" ) ;
   leg2->AddEntry( spike_Time,  "SpikeTagged" , "L" ) ;
   leg2->AddEntry( cosmic_Time, "CosmicTagged" , "L" ) ;
   h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( pure_Time,  "", 0.85, 2, 1  ) ;
   h_draw->DrawAppend( halo_Time,  "", 0.75, 4, 1  ) ;
   h_draw->DrawAppend( spike_Time,  "", 0.65, 6, 1  ) ;
   h_draw->DrawAppend( cosmic_Time, "TimeForAll", 0.55, 8, 1, leg2  ) ;

   leg2->Clear() ;
   leg2->AddEntry( nJets_center, "RealPhotons" , "L" ) ;
   leg2->AddEntry( nJets_halo,   "HaloTagged" , "L" ) ;
   leg2->AddEntry( nJets_spike,  "SpikeTagged" , "L" ) ;
   leg2->AddEntry( nJets_cosmic, "CosmicTagged" , "L" ) ;
   h_draw->Draw(       nJets_center, "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( nJets_halo,   "", 0.85, 2, 1  ) ;
   h_draw->DrawAppend( nJets_spike,   "", 0.75, 4, 1  ) ;
   h_draw->DrawAppend( nJets_cosmic, "NJets_All", 0.6, 8, 1, leg2  ) ;

   leg2->Clear() ;
   double a_o = a_Z0->Integral(1,15) + a_Z0->Integral(20,34) ;
   double a_i = a_Z0->Integral(16,19) ;
   double b_o = b_Z0->Integral(1,15) + b_Z0->Integral(20,34) ;
   double b_i = b_Z0->Integral(16,19) ;
   double c_o = c_Z0->Integral(1,15) + c_Z0->Integral(20,34) ;
   double c_i = c_Z0->Integral(16,19) ;
   double d_o = d_Z0->Integral(1,15) + d_Z0->Integral(20,34) ;
   double d_i = d_Z0->Integral(16,19) ;
   double h_o = h_Z0->Integral(1,15) + h_Z0->Integral(20,34) ;
   double h_i = h_Z0->Integral(16,19) ;
   printf(" a_o/a_i = (%.2f/%.2f) = %f \n", a_o, a_i, a_o/a_i ) ;
   printf(" b_o/b_i = (%.2f/%.2f) = %f \n", b_o, b_i, b_o/b_i ) ;
   printf(" c_o/c_i = (%.2f/%.2f) = %f \n", c_o, c_i, c_o/c_i ) ;
   printf(" d_o/d_i = (%.2f/%.2f) = %f \n", d_o, d_i, d_o/d_i ) ;
   printf(" h_o/h_i = (%.2f/%.2f) = %f \n", h_o, h_i, h_o/h_i ) ;
   printf(" b/a = %f \n", (b_o*a_i)/(a_o*b_i) ) ;
   printf(" d/c = %f \n", (d_o*c_i)/(c_o*d_i) ) ;
   leg2->AddEntry( h_Z0, "Normal" , "L" ) ;
   leg2->AddEntry( a_Z0, "A" , "L" ) ;
   leg2->AddEntry( b_Z0, "B" , "L" ) ;
   leg2->AddEntry( c_Z0, "C" , "L" ) ;
   leg2->AddEntry( d_Z0, "D" , "L" ) ;
   h_draw->Draw(       h_Z0,     "", "nTracks in Z0", "",  "logY" , 0.95, 1 ) ;
   h_draw->DrawAppend( a_Z0,     "", 0.9, 2, 1 ) ;
   h_draw->DrawAppend( b_Z0,     "", 0.85, 4, 1 ) ;
   h_draw->DrawAppend( c_Z0,     "", 0.8, 6, 1 ) ;
   h_draw->DrawAppend( d_Z0,     "abcd_Z0", 0.75,  8, 1, leg2 ) ;


   leg2->Clear() ;
   leg2->AddEntry( l_nVtx, "MET < 60" , "L" ) ;
   leg2->AddEntry( h_nVtx, "MET > 60" , "L" ) ;
   h_draw->Draw(       l_nVtx,     "", "nTracks in nVtx", "",  "logY" , 0.95, 1 ) ;
   h_draw->DrawAppend( h_nVtx,     "hl_nVtx", 0.75,  8, 1, leg2 ) ;

   leg2->Clear() ;
   leg2->AddEntry( a_nVtx, "A" , "L" ) ;
   leg2->AddEntry( b_nVtx, "B" , "L" ) ;
   leg2->AddEntry( c_nVtx, "C" , "L" ) ;
   leg2->AddEntry( d_nVtx, "D" , "L" ) ;

   h_draw->Draw(       a_nVtx,     "", "nTracks in nVtx", "",  "logY" , 0.95, 1 ) ;
   h_draw->DrawAppend( b_nVtx,     "", 0.85, 4, 1 ) ;
   h_draw->DrawAppend( c_nVtx,     "", 0.8, 6, 1 ) ;
   h_draw->DrawAppend( d_nVtx,     "abcd_nVtx", 0.75,  8, 1, leg2 ) ;

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
   h_draw->Draw2D( sideband_dtdPhidEta,"sideband_dtdPhidEta", "#Delta#eta", "#Delta#phi", "logZ", 8  ) ;
   h_draw->Draw2D( sideband_dPhi_MET_csc, "sideband_dPhi_MET_csc",  "dPhi( photon, MET)", " dPhi( photon, cscseg)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet1, "sideband_dPhi_MET_Jet1",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet2, "sideband_dPhi_MET_Jet2",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;
   h_draw->Draw2D( sideband_dPhi_MET_Jet3, "sideband_dPhi_MET_Jet3",  "dPhi( photon, MET)", " dPhi( photon, Jet)", "logZ", 8 ) ;

   delete leg2 ;
   leg2  = new TLegend(.62, .7, .85, .9 );
   leg2->Clear() ;
   cs_nXtl->SetLineWidth(2) ;
   sideband_nXtl_u->SetLineWidth(2) ;
   sideband_nXtl_d->SetLineWidth(2) ;
   leg2->AddEntry( cs_nXtl,       "Nominal" , "L" ) ;
   leg2->AddEntry( sideband_nXtl_u, "Late-timing" , "L" ) ;
   leg2->AddEntry( sideband_nXtl_d, "Early-timing" , "L" ) ;

   h_draw->Draw(       cs_nXtl,        "",  " N of crystals ", "",  "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( sideband_nXtl_u, "",               0.85, 4 ) ;
   h_draw->DrawAppend( sideband_nXtl_d, "cs_side_nXtl",   0.8 , 6, 1, leg2 ) ;

   leg2->Clear() ;
   cs_cscdPhi->SetLineWidth(2) ;
   sideband_cscdPhi_u->SetLineWidth(2) ;
   sideband_cscdPhi_d->SetLineWidth(2) ;
   leg2->AddEntry( cs_cscdPhi,       "Nominal" , "L" ) ;
   leg2->AddEntry( sideband_cscdPhi_u, "Late-timing" , "L" ) ;
   leg2->AddEntry( sideband_cscdPhi_d, "Early-timing" , "L" ) ;

   h_draw->Draw(       sideband_cscdPhi_u,  "", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 4 ) ;
   h_draw->DrawAppend( sideband_cscdPhi_d,  "",  0.9, 6 ) ;
   h_draw->DrawAppend( cs_cscdPhi,          "cs_side_cscdPhi",  0.85, 2, 1, leg2 ) ;

   leg2->Clear() ;
   leg2->AddEntry( sideband_nVtx_0J, "0 Jet" , "L" ) ;
   leg2->AddEntry( sideband_nVtx_1J, "1 Jet" , "L" ) ;
   leg2->AddEntry( sideband_nVtx_2J, ">= 2 Jet" , "L" ) ;
   h_draw->Draw(       sideband_nVtx_0J,  "", "N of vertex ", "", "logY", 0.95, 2 ) ;
   h_draw->DrawAppend( sideband_nVtx_2J,  "",  0.9, 6 ) ;
   h_draw->DrawAppend( sideband_nVtx_1J,  "sideband_nVtx",  0.85, 4, 1, leg2 ) ;

   leg2->Clear() ;
   leg2->AddEntry( noG_nVtx_0J, "0 Jet" , "L" ) ;
   leg2->AddEntry( noG_nVtx_1J, "1 Jet" , "L" ) ;
   leg2->AddEntry( noG_nVtx_2J, ">= 2 Jet" , "L" ) ;
   h_draw->Draw(       noG_nVtx_1J,  "", "N of vertex ", "", "logY", 0.95, 4 ) ;
   h_draw->DrawAppend( noG_nVtx_2J,  "",  0.9, 6 ) ;
   h_draw->DrawAppend( noG_nVtx_0J,  "noG_nVtx",  0.85, 2, 1, leg2 ) ;

   h_draw->SetPlotStyle(true) ; // Turn off the stats box
   h_draw->Draw2D( haloCS_sMaj_sMin, "haloCS_sMaj_sMin", "sMaj", "sMin",  "", 8  ) ;
   h_draw->Draw2D( haloCS_sMaj_Eta,  "haloCS_sMaj_Eta",  "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( haloCS_sMaj_Phi,  "haloCS_sMaj_Phi",  "sMaj", " #phi",  "", 8  ) ;
   h_draw->Draw2D( haloCS_Eta_Time,  "haloCS_Eta_Time",  "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloCS_Eta_Time1, "haloCS_Eta_Time1", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw(   haloCS_cscdPhi,   "haloCS_cscdPhi",  " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   haloCS_cscdPhi1,  "haloCS_cscdPhi1", " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( spikeCS_Eta_Time1, "spikeCS_Eta_Time1", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_Eta_Time, "spikeCS_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_nXtl_Eta, "spikeCS_nXtl_Eta", "N of xtals", "#eta",  ""  ) ;
   h_draw->Draw2D( spikeCS_Phi_Time, "spikeCS_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( spikeCS_sMaj_sMin, "spikeCS_sMaj_sMin", "sMaj", "sMin (ns)",  ""  ) ;
   h_draw->Draw(   spikeCS_nXtl,     "spikeCS_nXtl",     " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( cosmic_sMaj_Time, "cosmic_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( cosmic_sMin_Time, "cosmic_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( cosmic_sMaj_sMin, "cosmic_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( cosmic_Eta_Time,  "cosmic_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_Phi_Time,  "cosmic_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_Pt_Time,   "cosmic_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_MET_Time,  "cosmic_MET_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_photIso_Time,"cosmic_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw(   cosmic_nXtl,      "cosmic_nXtl",    "N crystals",       "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   cosmic_sigIeta,   "cosmic_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   cosmic_Time,      "cosmic_Time", " Ecal time ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( haloFN_Eta_Time,  "haloFN_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_Phi_Time,  "haloFN_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_Pt_Time,   "haloFN_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_MET_Time,  "haloFN_MET_Time", "MET",  "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_sMaj_sMin, "haloFN_sMaj_sMin", "s_{Major}", "s_{Minor}",  "", 8 ) ;
   h_draw->Draw(   haloFN_cscdPhi,   "haloFN_cscdPhi",  " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( halo_sMaj_Time, "halo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMin_Time, "halo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMaj_sMin, "halo_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( halo_Eta_Time_0J, "halo_Eta_Time_0J", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Eta_Time_1J, "halo_Eta_Time_1J", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Eta_Time,  "halo_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Phi_Time,  "halo_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Pt_Time,   "halo_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_MET_Time,  "halo_MET_Time", "MET",  "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_photIso_Time,"halo_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw(   halo_sigIeta,   "halo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( halo_sMaj_sigIeta,"halo_sMaj_sigIeta",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMin_sigIeta,"halo_sMin_sigIeta",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_1J, "halo_T_dPhi_gMET_1J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_2J, "halo_T_dPhi_gMET_2J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_0J, "halo_T_dPhi_gMET_0J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_eta_rho,     "halo_eta_rho",    "#eta ", "#rho", "logZ", 8 ) ;
   h_draw->Draw2D( halo_eta_sMaj,    "halo_eta_sMaj",    "#eta ", "s_{Major}", "logZ", 8 ) ;
   h_draw->Draw2D( halo_ecalT_rho,   "halo_ecalT_rho",    "Ecal time ", "#rho", "logZ", 8 ) ;
   h_draw->Draw2D( halo_ecalT_cscT,  "halo_ecalT_cscT","Ecal Time(ns)", "CSC Time (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( noHalo_sMaj_Time, "noHalo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( noHalo_sMin_Time, "noHalo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw(   noHalo_nXtl_side, "noHalo_nXtl_side",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   noHalo_nXtl_center, "noHalo_nXtl_center",  " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( spike_sMaj_Time, "spike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMin_Time, "spike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMaj_sMin, "spike_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( spike_Eta_Time,  "spike_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_Phi_Time,  "spike_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_Pt_Time,   "spike_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_MET_Time,  "spike_MET_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw(   spike_sigIeta,   "spike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( spike_photIso_Time,"spike_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( spike_sMaj_sigIeta,"spike_sMaj_sigIeta",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMin_sigIeta,"spike_sMin_sigIeta",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_1J, "spike_T_dPhi_gMET_1J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_2J, "spike_T_dPhi_gMET_2J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_0J, "spike_T_dPhi_gMET_0J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;

   h_draw->Draw2D( noSpike_sMaj_Time, "noSpike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( noSpike_sMin_Time, "noSpike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;

   gPad->SetGridx() ;
   gStyle->SetOptStat("");
   //TString IntStrA[7] = { "" } ;
   TLegend* leg4  = new TLegend(.52, .72, .99, .99 );
   TLegend* leg5  = new TLegend(.52, .72, .99, .99 );
   Int_t nu0a, nu0 , nu1a, nu1;
   Float_t rate0 , rate1 ;
   char RStr[30], RStr1[60], RStr2[60] ;
   float fEta = 0 ;
   //for ( int k=0; k< 7; k++ ) {
   for ( int k=0; k< 5; k++ ) {
       nu0a = sMaj_eta[k]->Integral();
       nu0  = sMaj_eta[k]->Integral(28,100);
       nu1a = sMaj_eta_csc[k]->Integral();
       nu1  = sMaj_eta_csc[k]->Integral(28,100);
       rate0 = (float) nu0 / (float) nu0a ;
       rate1 = (float) nu1 / (float) nu1a ;
       sprintf( RStr,  "%.3f, %.2f<|#eta|<%.2f", rate0, fEta , fEta+0.28 ) ;
       sprintf( RStr2, "%d / %d = %s", nu0, nu0a , RStr ) ;
       sprintf( RStr1, "%d/%d = %.3f, %.2f<|#eta|<%.2f", nu1, nu1a, rate1, fEta, fEta+0.28 ) ;
       fEta += 0.28 ;
       if ( k < 5 ) leg4->AddEntry( sMaj_eta[k], RStr2 , "L" ) ;
       if ( k < 5 ) leg5->AddEntry( sMaj_eta_csc[k], RStr1 , "L" ) ;
   }

   sMaj_eta[0]->SetTitle("") ;
   h_draw->Draw(       sMaj_eta[0], "", " s_{Major} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( sMaj_eta[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[3], "",   0.9, 6, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[4], "sMaj_EtaSlice", 0.9, 8, 1 , leg4 ) ;

   //h_draw->Draw(       sMaj_eta[5], "", " sMajor ", "", "logY", 0.95, 1 ) ;
   //h_draw->DrawAppend( sMaj_eta[6], "sMaj_EtaSlice_EE", 0.75, 2, 1  ) ;

   sMaj_eta_csc[3]->SetTitle("") ;
   h_draw->Draw(       sMaj_eta_csc[3], "", " s_{Major} ", "", "logY", 0.9, 6 ) ;
   h_draw->DrawAppend( sMaj_eta_csc[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[0], "",   0.9, 1, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[4], "sMaj_EtaSlice_CSC", 0.9, 8, 1, leg5 ) ;

   leg4->Clear() ;
   leg4->AddEntry( haloAB_Pt_eta[0], " 0 <|#eta|< 0.37" , "L" ) ;
   leg4->AddEntry( haloAB_Pt_eta[1], " 0.37 <|#eta|< 0.74" , "L" ) ;
   leg4->AddEntry( haloAB_Pt_eta[2], " 0.74 <|#eta|< 1.11" , "L" ) ;
   leg4->AddEntry( haloAB_Pt_eta[3], " 1.11 <|#eta|< 1.48" , "L" ) ;
   haloAB_Pt_eta[0]->SetTitle("") ;
   h_draw->Draw(       haloAB_Pt_eta[2], "", " P_{T} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( haloAB_Pt_eta[3], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( haloAB_Pt_eta[1], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( haloAB_Pt_eta[0], "haloAB_Pt",   0.9, 6, 1 , leg4 ) ;

   leg4->Clear() ;
   leg4->AddEntry( haloAB_MET_eta[0], " 0 <|#eta|< 0.37" , "L" ) ;
   leg4->AddEntry( haloAB_MET_eta[1], " 0.37 <|#eta|< 0.74" , "L" ) ;
   leg4->AddEntry( haloAB_MET_eta[2], " 0.74 <|#eta|< 1.11" , "L" ) ;
   leg4->AddEntry( haloAB_MET_eta[3], " 1.11 <|#eta|< 1.48" , "L" ) ;
   haloAB_MET_eta[0]->SetTitle("") ;
   h_draw->Draw(       haloAB_MET_eta[2], "", " MET ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( haloAB_MET_eta[3], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( haloAB_MET_eta[1], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( haloAB_MET_eta[0], "haloAB_MET",   0.9, 6, 1 , leg4 ) ;

   leg4->Clear() ;
   leg4->AddEntry( haloCD_Pt_eta[0], " 0 <|#eta|< 0.37" , "L" ) ;
   leg4->AddEntry( haloCD_Pt_eta[1], " 0.37 <|#eta|< 0.74" , "L" ) ;
   leg4->AddEntry( haloCD_Pt_eta[2], " 0.74 <|#eta|< 1.11" , "L" ) ;
   leg4->AddEntry( haloCD_Pt_eta[3], " 1.11 <|#eta|< 1.48" , "L" ) ;
   haloCD_Pt_eta[0]->SetTitle("") ;
   h_draw->Draw(       haloCD_Pt_eta[2], "", " P_{T} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( haloCD_Pt_eta[3], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( haloCD_Pt_eta[1], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( haloCD_Pt_eta[0], "haloCD_Pt",   0.9, 6, 1 , leg4 ) ;

   leg4->Clear() ;
   leg4->AddEntry( haloCD_MET_eta[0], " 0 <|#eta|< 0.37" , "L" ) ;
   leg4->AddEntry( haloCD_MET_eta[1], " 0.37 <|#eta|< 0.74" , "L" ) ;
   leg4->AddEntry( haloCD_MET_eta[2], " 0.74 <|#eta|< 1.11" , "L" ) ;
   leg4->AddEntry( haloCD_MET_eta[3], " 1.11 <|#eta|< 1.48" , "L" ) ;
   haloCD_MET_eta[0]->SetTitle("") ;
   h_draw->Draw(       haloCD_MET_eta[2], "", " MET ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( haloCD_MET_eta[3], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( haloCD_MET_eta[1], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( haloCD_MET_eta[0], "haloCD_MET",   0.9, 6, 1 , leg4 ) ;

   TLegend* leg6  = new TLegend(.5, .7, .9, .9 );
   float nSp0  = notSpike_nXtl->Integral(1,8);
   float nSp   = notSpike_nXtl->Integral();
   char NStr[50] ;
   sprintf( NStr,  "%.1f / %.1f = %.4f ", nSp0, nSp, nSp0/nSp ) ;
   leg6->AddEntry( notSpike_nXtl, NStr , "L" ) ;
   h_draw->Draw(   notSpike_nXtl, "notSpike_nXtl", "N of crystals ", "",  "logY", 0.95, 1, 1, leg6 ) ;

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
      spikeMis = sMistag->GetY() ;
      for (int i=0; i< 5 ; i++ ) {
              printf(" (%d)  = %.5f \n", i, spikeMis[i] ) ;
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
      haloMis  = hMistag->GetY() ;
      for (int i=0; i< 5 ; i++ ) {
              printf(" (%d)  = %.5f \n", i, haloMis[i] ) ;
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

      if ( isData == 1 ) {
      cout<<" ======= Halo Tagging Efficiency ====== "<<endl ;
      c_0->Clear() ;
      TGraphAsymmErrors* halo_Eff = new TGraphAsymmErrors();
      halo_Eff->Divide( halo_Eta[1], halo_Eta[0] );

      haloEff  = halo_Eff->GetY() ;
      for (int i=0; i< 6 ; i++ ) {
          if ( haloEff == NULL ) break ;
          printf(" (%d)  = %.5f \n", i, haloEff[i] ) ;
      }

      halo_Eff->SetMaximum( 1.1 );
      halo_Eff->SetMinimum( 0.0 );
      halo_Eff->SetMarkerStyle(22);
      halo_Eff->SetMarkerColor(4);
      halo_Eff->SetLineWidth(2);
      halo_Eff->GetYaxis()->SetTitleOffset(1.9);
      halo_Eff->GetXaxis()->SetTitle( "|#eta|" ) ;
      halo_Eff->GetYaxis()->SetTitle(" Efficiency ") ;
      halo_Eff->Draw("AP");
      c_0->Update();
      plotname = hfolder + "Efficiency_Halo."+plotType ;
      c_0->Print( plotname ) ;

      cout<<" ======= Spike Tagging Efficiency ====== "<<endl ;
      c_0->Clear() ;
      TGraphAsymmErrors* spike_Eff = new TGraphAsymmErrors();
      spike_Eff->Divide( spike_Eta[1], spike_Eta[0] );

      spikeEff  = spike_Eff->GetY() ;
      for (int i=0; i< 6 ; i++ ) {
          if ( spikeEff == NULL ) break ;
          printf(" (%d)  = %.5f \n", i, spikeEff[i] ) ;
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
   }

   // Get Background estimation 
   //GetEstimation( hBg_D ) ;
   //GetEstimation( hBg_C ) ;
   //GetEstimation( hBg_B ) ;
   //GetEstimation( hBg_A ) ;

   ABCD( hBg_A, hBg_B, hBg_C, hBg_D ) ;

   TCanvas* c_1 = new TCanvas("c_1","", 800, 700);
   c_1->SetFillColor(10);
   c_1->SetLogz() ;

   h_Eta_Time->Draw("COLZ") ;
   c_1->Update() ;
   TF1 *f2 = new TF1("f2", BackgroundStudy::HaloFunction ,-1.4,1.4, 3 );
   f2->SetParameter(0,  1.4) ;
   f2->SetParameter(1,  1.5) ;
   f2->SetParameter(2,  -1.5) ;
   f2->Draw("sames") ;
   c_1->Update();

   TF1 *f3 = new TF1("f3", BackgroundStudy::HaloFunction ,-1.4,1.4, 3 );
   f3->SetParameter(0, 1.4) ;
   f3->SetParameter(1, 1.3)  ;
   f3->SetParameter(2, -1)  ;
   f3->Draw("sames") ;
   c_1->Update();

   TString plotname = hfolder + "HaloFunction."+plotType ;
   c_1->Print( plotname ) ;

}

 // x is eta region , each is 0.28 , y is different sample, 0:total, 1:halo, 2: spike 3: cosmic
void BackgroundStudy::ABCD( TH2D* hA, TH2D* hB, TH2D* hC, TH2D* hD ) {

   //  GetEstimation returns QCD components
   cout<<" ===  A  === "<<endl ;
   double rA = GetEstimation( hA ) ;
   cout<<" ===  B  === "<<endl ;
   double rB = GetEstimation( hB ) ;
   cout<<" ===  C  === "<<endl ;
   double rC = GetEstimation( hC ) ;
   cout<<" ===  D  === "<<endl ;
   double rD = GetEstimation( hD ) ;

   double predict = ( rA > 0. ) ? rC * ( rB / rA ) : 0. ; 

   if ( rA < 0.0001 ) cout<<" Residual Background ABCD Fail ! " <<endl ;
   else               printf(" B/A (%.2f/%.2f) = %.2f  ==> D/C (%.2f/%.2f) = %.2f \n", rB, rA, rB/rA , rD, rC, rD/rC ) ;

   printf(" Observe :%f -> Predict : %f \n", rD, predict ) ;

}

// Return the sum of spike and halo component or QCD component of background
// xbin : 5 eta region ( 0 ~ 1.4 ) , bin width : 0.28
// ybin : [bin1]: Total count , [bin2]: Halo , [bin3]: Spike, [bin4]: Cosmic
double BackgroundStudy::GetEstimation( TH2D* hCount, bool getQCD ) {

   double ghostB = 0 ;
   double Bg_exp = 0 ; 
   double residual = 0 ;
   printf("| eta |    spike    |     halo    |   cosmic   |  QCD  |  Total  |\n" ) ;
   for ( int i=0; i< 5; i++ ) {

       double nB = hCount->GetBinContent(i+1, 1) ; // total number in control region 
       double nH = hCount->GetBinContent(i+1, 2) ; // number of halo tagged in control region
       double nS = hCount->GetBinContent(i+1, 3) ; // number of spike tagged in control region
       double nC = hCount->GetBinContent(i+1, 4) ; // number of cosmic tagged in control region
       
       vector<double> bgV = GetComponent( i, nB, nH, nS, nC ) ;
       ghostB   += bgV[0] ;  // spike
       ghostB   += bgV[1] ;  // halo
       ghostB   += bgV[2] ; // cosmic
       residual += bgV[3] ; // qcd
       Bg_exp   += nB ;
       //printf(" eta(%d) : spike:%f , halo:%f , cosmic:%f , QCD:%f  from %f \n ", i, bgV[0], bgV[1], bgV[2], bgV[3], nB ) ;
       //printf(" eta  |  spike  |   halo   |  cosmic  |  QCD  |  from  |\n " ) ;
       printf("|  %d  | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f (%4.f) | %4.2f | %4.f |\n", i, bgV[0], nS, bgV[1], nH, bgV[2], nC, bgV[3], nB ) ;

   }

   printf(" Background :  QCD:%f , Ghost:%f -> %f \n ", residual, ghostB, Bg_exp ) ;

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
vector<double> BackgroundStudy::GetComponent( int eta_i, double B12, double h_B12, double s_B12, double c_B12 ) {

       // Tagging efficiency 
       double hEff[5] = { 0.89, 0.86, 0.97, 0.90, 0.89 } ; // halo
       double sEff[5] = { 0.94, 0.89, 0.77, 0.68, 0.56 } ; // spike
       //double cEff[5] = { 1.0,  1.0,  1.0,  1.0,  1.0 } ; // cosmic
       
       // get the update efficiency for halo/spike/comsic
       for ( int i=0; i < 5; i++) {
           if ( haloEff == NULL || spikeEff == NULL )  break ;
           if ( haloEff[i] < 0. || spikeEff[i] < 0. )  continue ;
           hEff[i] = haloEff[i] ;
           sEff[i] = spikeEff[i] ;
           //cout<<" Updated Efficiency "<< endl ;
       }
       
       double h = hEff[ eta_i ] ;  // halo
       double s = sEff[ eta_i ] ;  // spike
       //double c = cEff[ eta_i ] ;  // comsic

       // Mis-tag rate
       double mA[5] = { 0.01349, 0.00629, 0.00154, 0.00088, 0.00038 } ;
       double nA[5] = { 0.02219, 0.02256, 0.01493, 0.00162, 0.00290 } ;
       //double oA[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 } ;

       for ( int i=0; i < 5; i++) {
           if ( haloMis == NULL || spikeMis == NULL )  break ;
           if ( haloMis[i] < 0. || spikeMis[i] < 0. )  continue ;
           mA[i] = haloMis[i] ;
           nA[i] = spikeMis[i] ;
           //cout<<" Updated Mistagging Rate "<< endl ;
       }
       
       double m = mA[ eta_i ] ;   // halo
       double n = nA[ eta_i ] ;   // spike
       //double o = oA[ eta_i ] ;   // cosmic

       // cosmic content 
       double C12 = c_B12 ;
       double B12_noC = B12 - C12 ;
       // spike content
       double S12 = ( s_B12 - (n*B12_noC) ) / ( s - n ) ;
       S12 = ( S12 < 0. ) ? 0 : S12 ;
       // halo content 
       double H12 = ( h_B12 - (m*B12_noC) ) / ( h - m ) ;
       H12 = ( H12 < 0. ) ? 0 : H12 ;
       // QCD content 
       double Q12 = (double)(B12) - S12 - H12 - C12;
       Q12 = ( Q12 < 0. ) ? 0 : Q12 ;

       //printf("(%d) B12 %d = (S12: %.2f ) + ( H12: %.2f ) + ( Q12: %.2f )\n ", eta_i, B12, S12, H12, Q12 ) ;

       vector<double> BG12 ;
       BG12.push_back( S12 ) ;
       BG12.push_back( H12 ) ;
       BG12.push_back( C12 ) ;
       BG12.push_back( Q12 ) ;
       return BG12 ;
}

// Obsolete old naive method
double BackgroundStudy::ABCD( TH1D* h_sg, TH1D* h_cs, double lowT, double upT ) {

     int bin0    = h_cs->FindBin( lowT ) ;
     int bin1    = h_cs->FindBin( upT ) ;
     int lastBin = h_cs->GetNbinsX() ;

     double nA = h_cs->Integral(    1, bin0 );
     double nB = h_cs->Integral( bin1, lastBin );

     double nC = h_sg->Integral( 1, bin0 ) ;
     double nX = h_sg->Integral( bin1, lastBin );

     double nD = ( nA > 0 ) ? (nC * nB / nA) : 0. ;

     if ( nA < 0.0001 ) cout<<" ABCD Fail ! " <<endl ;
     printf(" B/A = %f  ==> D/C = %f \n", nB/nA , nX/nC ) ;
     printf(" Observe :%f -> predict : %f \n", nX, nD ) ;

     return nD ;

}

// Get the QCD component by scaling the shape from QCD sample (h_qcd) to signal sample (h_sg)
// Scaling factor is driven from background control region in both histograms which is defined by lowX and upX
double BackgroundStudy::GetQCDComponent( TH1D* h_qcd, TH1D* h_sg, double lowX, double upX ) {

     int bin0 = h_qcd->FindBin( lowX ) ;
     int bin1 = h_qcd->FindBin( upX ) ;

     double int_qcd = h_qcd->Integral( bin0, bin1 );
     double int_sg  = h_sg->Integral( bin0, bin1 );

     double sc = int_sg / int_qcd ;

     TH1D* h_qcd_sg = (TH1D*) h_qcd->Clone() ;   
     h_qcd_sg->Scale( sc ) ;

     int lastBin = h_qcd_sg->GetNbinsX() ;
     double predict = h_qcd_sg->Integral( bin1, lastBin ) ;

     printf(" scale factor :%f -> QCD componenet : %f \n ", sc, predict ) ;
     return predict ;
}


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


