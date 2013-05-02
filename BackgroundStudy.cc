#include "BackgroundStudy.h"
#include <TTree.h>
#include <algorithm>
#include <TCanvas.h>
#include <TStyle.h>
#include <TFrame.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphErrors.h>


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

  theFile->cd() ;
  if ( writeHist ) Write() ;

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
  h_EB_Time3->Write() ;
  h_EE_Time->Write() ;
  h_EE_Time0->Write() ;
  h_EE_Time1->Write() ;
  h_EE_Time2->Write() ;
  h_EE_Time3->Write() ;

  h_Eta_Time->Write() ;
  h_Phi_Time->Write() ;
  h_cscdPhi_Time->Write() ;
  h_sMaj_Time_EB->Write() ;
  h_sMaj_Time_EE->Write() ;
  h_sMin_Time_EB->Write() ;
  h_sMin_Time_EE->Write() ;
  h_sigIeta_Time_EB->Write() ;
  h_sigIeta_Time_EE->Write() ;
  h_Pt_Time_EB->Write() ;
  h_Pt_Time_EE->Write() ;
  h_MET_Time_EB->Write() ;
  h_MET_Time_EE->Write() ;
  h_cHadIso_Time->Write() ;
  h_nHadIso_Time->Write() ;
  h_photIso_Time->Write() ;

  h_sMaj_Eta->Write() ;
  h_sMaj_Phi->Write() ;
  h_sMaj_sMin->Write() ;
  h_sigEta_sMaj->Write() ;
  h_sigEta_sMaj_late->Write() ;
  h_nXtl_Eta->Write() ;
  h_nXtl_Pt->Write() ;

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
  sg_cHadIso_Time->Write() ;
  sg_nHadIso_Time->Write() ;
  sg_photIso_Time->Write() ;
  sg_photIso_sMaj->Write() ;
  sg_photIso_sMin->Write() ;
  sg_photIso_sigIeta->Write() ;
  //sg_gg_dR->Write() ; 

  sel_Time->Write();
  sel_sMaj_Time->Write() ;
  sel_sMaj_Eta->Write() ;
  sel_sMin_Time->Write() ;
  sel_sMin_Eta->Write() ;
  sel_Eta_Time->Write() ;
  sel_Phi_Time->Write() ;

  cs_Eta_Time->Write() ;
  cs_Phi_Time->Write() ;
  cs_sigIeta_Time->Write() ;
  cs_nXtl->Write() ;
  cs_nXtl_Eta->Write() ;
  cs_cscdPhi->Write() ;
  cs_cHadIso_Time->Write() ;
  cs_nHadIso_Time->Write() ;
  cs_photIso_Time->Write() ;

  sideband_photIso_cscdPhi->Write() ;
  sideband_sMaj_Time->Write() ;
  sideband_sMaj_Phi->Write() ;
  sideband_sMaj_sMin->Write() ;
  sideband_sMaj_Eta->Write() ;
  sideband_nXtl_Eta->Write() ;
  sideband_cscdPhi->Write() ;
  sideband_cscdPhi_a3->Write() ;
  sideband_cscdPhi_b3->Write() ;
  sideband_cscdPhi_c2->Write() ;
  sideband_nXtl->Write() ;
  sideband_sMaj->Write() ;
  bg_Eta_Time->Write() ;

  qcdCS_Time->Write() ;
  qcdCS_Eta_Time->Write() ;

  haloCS_nXtl_a3->Write() ;
  haloCS_nXtl_b3->Write() ;
  haloCS_nXtl_c2->Write() ;
  spikeCS_nXtl_a3->Write() ;
  spikeCS_nXtl_b3->Write() ;
  spikeCS_nXtl_c2->Write() ;

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

  halo_Eta_Time->Write() ;
  halo_Phi_Time->Write() ;
  halo_sMin_Time->Write() ;
  halo_sMaj_Time->Write() ;
  halo_photIso_Time->Write() ;
  halo_sMaj_sMin->Write();
  halo_Time->Write() ;
  halo_sigEta->Write() ;
  halo_sigIeta->Write() ;

  noHalo_Time->Write() ;
  noHalo_sigEta->Write() ;
  noHalo_sigIeta->Write() ;
  noHalo_Phi_Time->Write() ;
  noHalo_Eta_Time->Write() ;
  noHalo_sMaj_sMin->Write() ;
  noHalo_sMaj_Time->Write() ;
  noHalo_sMin_Time->Write() ;

  noHalo_nXtl_side->Write() ;
  noHalo_nXtl_center->Write() ;

  spike_Eta_Time->Write() ;
  spike_Phi_Time->Write() ;
  spike_sMaj_Time->Write() ;
  spike_sMin_Time->Write() ;
  spike_photIso_Time->Write() ;
  spike_sMaj_sMin->Write();
  spike_Time->Write() ;
  spike_sigEta->Write() ;
  spike_sigIeta->Write() ;

  noSpike_Phi_Time->Write() ;
  noSpike_Eta_Time->Write() ;
  noSpike_sMaj_Time->Write() ;
  noSpike_sMin_Time->Write() ;
  noSpike_sMaj_sMin->Write() ;
  noSpike_Time->Write() ;
  noSpike_sigEta->Write() ;
  noSpike_sigIeta->Write() ;

  pure_Time->Write() ;
  pure_Eta_Time->Write() ;
  pure_Phi_Time->Write() ;
  pure_sMaj_sMin->Write() ;

  nHL_Eta->Write() ;
  nSpk_Eta->Write() ;
  nCS_Eta->Write() ;
  notSpike_nXtl->Write()    ;

  hBg_sg->Write() ;
  hBg_m->Write() ;
  hBg_t->Write() ;
  hBg_mt->Write() ;

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
  h_EB_Time3  = new TH1D( "h_EB_Time3", " Ecal time from EB", 160, -20, 20 ) ;
  h_EE_Time   = new TH1D( "h_EE_Time", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time0  = new TH1D( "h_EE_Time0", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time1  = new TH1D( "h_EE_Time1", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time2  = new TH1D( "h_EE_Time2", " Ecal time from EE", 160, -20, 20 ) ;
  h_EE_Time3  = new TH1D( "h_EE_Time3", " Ecal time from EE", 160, -20, 20 ) ;

  // Raw information
  h_Eta_Time  = new TH2D( "h_Eta_Time", " eta vs Ecal time", 102, -2.5, 2.5, 160, -20, 20 ) ;
  h_Phi_Time  = new TH2D( "h_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  h_cscdPhi_Time  = new TH2D( "h_cscdPhi_Time", " d#Phi vs Ecal time", 64, 0, 3.2, 160, -20, 20 ) ;
  h_sigIeta_Time_EB  = new TH2D( "h_sigIeta_Time_EB", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sigIeta_Time_EE  = new TH2D( "h_sigIeta_Time_EE", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  h_sMaj_Time_EB = new TH2D( "h_sMaj_Time_EB", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMaj_Time_EE = new TH2D( "h_sMaj_Time_EE", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  h_sMin_Time_EB = new TH2D( "h_sMin_Time_EB",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  h_sMin_Time_EE = new TH2D( "h_sMin_Time_EE",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  h_Pt_Time_EB   = new TH2D( "h_Pt_Time_EB",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_Pt_Time_EE   = new TH2D( "h_Pt_Time_EE",  " Pt vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EB  = new TH2D( "h_MET_Time_EB",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_MET_Time_EE  = new TH2D( "h_MET_Time_EE",  " MET vs Ecal time", 50, 0, 500, 120, -15, 15 ) ;
  h_cHadIso_Time = new TH2D("h_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_nHadIso_Time = new TH2D("h_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  h_photIso_Time = new TH2D("h_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );

  h_sMaj_Eta  = new TH2D( "h_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  h_sMaj_Phi  = new TH2D( "h_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  h_sMaj_sMin = new TH2D( "h_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  h_nXtl_Eta  = new TH2D( "h_nXtl_Eta", "N crystals vs #eta ", 50, 0, 50 ,  51, -2.5, 2.5) ;
  h_nXtl_Pt   = new TH2D( "h_nXtl_Pt", "N crystals vs #eta ", 50, 0, 50 ,  50,  0. , 500. ) ;
  h_sigEta_sMaj   = new TH2D( "h_sigEta_sMaj", " sigma_iEta vs sMaj ", 80, 0, 0.08, 100, 0, 2 ) ;
  h_sigEta_sMaj_late = new TH2D( "h_sigEta_sMaj_late", " sigma_iEta vs sMaj for late photon", 80, 0, 0.08, 100, 0, 2 ) ;

  // Information from signal selection
  sg_nXtl      = new TH1D( "sg_nXtl", "N crystals ", 50, 0, 50 ) ;
  sg_cscdPhi   = new TH1D( "sg_cscdPhi", " d#Phi ", 64, 0, 3.2 ) ;
  sg_Time      = new TH1D( "sg_Time", "Photon Time from signal CS", 160,  -14.5, 25.5);
  sg_Time_halo = new TH1D( "sg_Time_halo", "Photon Time from signal but halo-tagged", 160,  -14.5, 25.5);
  sg_Time_spike= new TH1D( "sg_Time_spike", "Photon Time from signal but spike-tagged", 160,  -14.5, 25.5);
  sg_Eta_Time  = new TH2D( "sg_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sg_Eta_Time_halo  = new TH2D( "sg_Eta_Time_halo", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sg_Eta_Time_spike  = new TH2D( "sg_Eta_Time_spike", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sg_Phi_Time  = new TH2D( "sg_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  sg_nXtl_Eta  = new TH2D( "sg_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  sg_sigIeta_Time = new TH2D("sg_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  sg_cHadIso_Time = new TH2D("sg_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  sg_nHadIso_Time = new TH2D("sg_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  sg_photIso_Time = new TH2D("sg_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  sg_photIso_sMaj = new TH2D("sg_photIso_sMaj", " Photon IsoDeposit vs sMajor",         100, 0, 10., 100,  0., 2. );
  sg_photIso_sMin = new TH2D("sg_photIso_sMin", " Photon IsoDeposit vs sMinor",         100, 0, 10., 120,  0., 0.5 );
  sg_photIso_sigIeta = new TH2D("sg_photIso_sigIeta", " Photon IsoDeposit vs sigma_iEta",  100, 0, 10., 80,  0., 0.08 );
  sg_sMaj_Time   = new TH2D( "sg_sMaj_Time", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  sg_sMin_Time   = new TH2D( "sg_sMin_Time",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  sg_sMaj_Eta    = new TH2D( "sg_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2.0, 51, -2.5, 2.5 ) ;
  sg_sMin_Eta    = new TH2D( "sg_sMin_Eta", " sMin vs photon #eta", 100, 0, 0.5, 51, -2.5, 2.5 ) ;
  //sg_gg_dR       = new TH1D( "sg_gg_dR", " dR(g,g) " , 100, 0, 5. ) ;

  sel_Time      = new TH1D( "sel_Time", "Photon Time after sg selection & bg rejection", 160,  -14.5, 25.5);
  sel_Eta_Time  = new TH2D( "sel_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  sel_Phi_Time  = new TH2D( "sel_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  sel_sMaj_Time = new TH2D( "sel_sMaj_Time", " sMaj vs Ecal time", 100, 0, 2, 160, -20, 20 ) ;
  sel_sMin_Time = new TH2D( "sel_sMin_Time",  "sMin vs. Ecal time ", 100, 0., 0.5 , 160, -20, 20  ) ;
  sel_sMaj_Eta    = new TH2D( "sel_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2.0, 51, -2.5, 2.5 ) ;
  sel_sMin_Eta    = new TH2D( "sel_sMin_Eta", " sMin vs photon #eta", 100, 0, 0.5, 51, -2.5, 2.5 ) ;
  // Information from signal selection
  cs_Eta_Time  = new TH2D( "cs_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;
  cs_Phi_Time  = new TH2D( "cs_Phi_Time", " phi vs Ecal time", 63, -3.15, 3.15, 160, -20, 20 ) ;
  cs_sigIeta_Time = new TH2D( "cs_sigIeta_Time", " sigma_iEta vs Ecal time", 80, 0, 0.08, 120, -15, 15 ) ;
  cs_nXtl_Eta     = new TH2D( "cs_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  cs_nXtl      = new TH1D( "cs_nXtl", "N crystals ", 50, 0, 50 ) ;
  cs_cscdPhi   = new TH1D( "cs_cscdPhi", " d#Phi ", 64, 0, 3.2 ) ;
  cs_cHadIso_Time = new TH2D("cs_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_nHadIso_Time = new TH2D("cs_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  cs_photIso_Time = new TH2D("cs_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );

  sideband_photIso_cscdPhi = new TH2D("sideband_photIso_cscdPhi", " Photon IsoDeposit vs d#Phi" ,   100, 0, 10.,  64,  0., 3.2 );
  sideband_sMaj_Time  = new TH2D( "sideband_sMaj_Time", " sMaj vs photon time", 100, 0, 2, 160, -20, 20 ) ;
  sideband_sMaj_Phi   = new TH2D( "sideband_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  sideband_sMaj_sMin  = new TH2D( "sideband_sMaj_sMin", " sMaj vs sMin", 100, 0, 2, 50, 0.1, 0.4 ) ;
  sideband_sMaj_Eta   = new TH2D( "sideband_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  sideband_nXtl_Eta   = new TH2D( "sideband_nXtl_Eta", " N crystals vs #eta", 50, 0, 50 ,  51, -2.5, 2.5) ;
  sideband_cscdPhi    = new TH1D( "sideband_cscdPhi", " d#Phi ", 64, 0, 3.2 ) ;
  sideband_cscdPhi_a3 = new TH1D( "sideband_cscdPhi_a3", " #Delta#Phi(cscSegment, #gamma) ", 64, 0., 3.2 ) ;
  sideband_cscdPhi_b3 = new TH1D( "sideband_cscdPhi_b3", " #Delta#Phi(cscSegment, #gamma) ", 64, 0., 3.2 ) ;
  sideband_cscdPhi_c2 = new TH1D( "sideband_cscdPhi_c2", " #Delta#Phi(cscSegment, #gamma) ", 64, 0., 3.2 ) ;
  sideband_nXtl       = new TH1D( "sideband_nXtl", " N of crystals ", 50, 0, 50 ) ;
  sideband_sMaj       = new TH1D( "sideband_sMaj", " sMajor ", 100, 0., 2. ) ;

  bg_Eta_Time  = new TH2D( "bg_Eta_Time", " eta vs Ecal time", 51, -2.5, 2.5, 160, -20, 20 ) ;

  qcdCS_Time       = new TH1D( "qcdCS_Time", "Photon Time For QCD selection", 160,  -14.5, 25.5 );
  qcdCS_Eta_Time   = new TH2D( "qcdCS_Eta_Time", " #eta vs time for qcd CS",  51, -2.5, 2.5,   160, -20, 20 ) ;

  haloCS_nXtl_a3   = new TH1D( "haloCS_nXtl_a3", " N of Crystals ", 50, 0, 50 ) ;
  haloCS_nXtl_b3   = new TH1D( "haloCS_nXtl_b3", " N of Crystals ", 50, 0, 50 ) ;
  haloCS_nXtl_c2   = new TH1D( "haloCS_nXtl_c2", " N of Crystals ", 50, 0, 50 ) ;
  spikeCS_nXtl_a3  = new TH1D( "spikeCS_nXtl_a3", " N of Crystals ", 50, 0, 50 ) ;
  spikeCS_nXtl_b3  = new TH1D( "spikeCS_nXtl_b3", " N of Crystals ", 50, 0, 50 ) ;
  spikeCS_nXtl_c2  = new TH1D( "spikeCS_nXtl_c2", " N of Crystals ", 50, 0, 50 ) ;

  haloCS_sMaj_Eta  = new TH2D( "haloCS_sMaj_Eta", " sMaj vs photon #eta", 100, 0, 2, 51, -2.5, 2.5 ) ;
  haloCS_sMaj_Phi  = new TH2D( "haloCS_sMaj_Phi", " sMaj vs photon #phi", 100, 0, 2, 63, -3.15, 3.15 ) ;
  haloCS_Eta_Time  = new TH2D( "haloCS_Eta_Time", " eta vs photon time  ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  haloCS_Eta_Time1 = new TH2D( "haloCS_Eta_Time1", " eta vs photon time ", 51, -2.5, 2.5,   160, -20, 20 ) ;

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

  halo_Eta_Time  = new TH2D( "halo_Eta_Time", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  halo_Phi_Time  = new TH2D( "halo_Phi_Time", " phi vs photon time for halo photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  halo_sMin_Time = new TH2D( "halo_sMin_Time",  "sMin vs Ecal time for halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  halo_sMaj_Time = new TH2D( "halo_sMaj_Time",  "sMaj vs Ecal time for halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  halo_photIso_Time = new TH2D("halo_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  halo_sMaj_sMin = new TH2D( "halo_sMaj_sMin", "sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  halo_sigEta    = new TH1D( "halo_sigEta", " Sigma Eta Eta for Halo Photon ", 100,  0., 0.1 ) ;
  halo_sigIeta   = new TH1D( "halo_sigIeta", " Sigma Ieta Ieta for Halo Photon ", 100,  0., 0.1 ) ;
  halo_Time      = new TH1D( "halo_Time",   "Photon time w/ halo ", 160,  -14.5, 25.5 ) ;

  noHalo_Phi_Time  = new TH2D( "noHalo_Phi_Time", "#phi vs Non Halo Photon time ", 63, -3.15, 3.15, 160,  -20, 20 ) ;
  noHalo_Eta_Time  = new TH2D( "noHalo_Eta_Time", "#eta vs Non Halo Photon time ", 51, -2.5, 2.5, 160,  -20, 20 ) ;
  noHalo_sMaj_sMin = new TH2D( "noHalo_sMaj_sMin", "sMaj vs sMin for non halo photon",100, 0, 2, 50, 0.1, 0.4   ) ;
  noHalo_sMaj_Time = new TH2D( "noHalo_sMaj_Time",  "sMaj vs Ecal time for non halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  noHalo_sMin_Time = new TH2D( "noHalo_sMin_Time",  "sMin vs. Ecal time for non halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  noHalo_sigEta  = new TH1D( "noHalo_sigEta", " Sigma Eta Eta for non halo photon", 100,  0., 0.1 ) ;
  noHalo_sigIeta = new TH1D( "noHalo_sigIeta", " Sigma Ieta Ieta for non halo photon", 100,  0., 0.1 ) ;
  noHalo_Time    = new TH1D( "noHalo_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;

  noHalo_nXtl_side = new TH1D( "noHalo_nXtl_side", "N of xtals of non halo photon w/ |t| > 3ns",     50,  0, 50 );
  noHalo_nXtl_center = new TH1D( "noHalo_nXtl_center", "N of xtals of non halo photon w/ |t| < 3ns", 50,  0, 50 );

  spike_sigEta    = new TH1D( "spike_sigEta", " Sigma Eta Eta for spike photon ", 100,  0., 0.1 ) ;
  spike_sigIeta   = new TH1D( "spike_sigIeta", " Sigma Ieta Ieta for spike photon ", 100,  0., 0.1 ) ;
  spike_Time      = new TH1D( "spike_Time",   "Photon time w/ spike ", 160,  -14.5, 25.5 ) ;
  spike_Eta_Time  = new TH2D( "spike_Eta_Time", " eta vs photon time for spike photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  spike_Phi_Time  = new TH2D( "spike_Phi_Time", " phi vs photon time for spike photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  spike_sMaj_sMin = new TH2D( "spike_sMaj_sMin", " sMajor vs sMinor for spike photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  spike_sMaj_Time = new TH2D( "spike_sMaj_Time",  "sMaj vs Ecal time for spike Photon", 100, 0, 2, 160, -20, 20 ) ;
  spike_sMin_Time = new TH2D( "spike_sMin_Time",  "sMin vs. Ecal time for spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  spike_photIso_Time = new TH2D("spike_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );

  noSpike_sigEta  = new TH1D( "noSpike_sigEta", " Sigma Eta Eta for non spike photon", 100,  0., 0.1 ) ;
  noSpike_sigIeta = new TH1D( "noSpike_sigIeta", " Sigma Ieta Ieta for non spike photon", 100,  0., 0.1 ) ;
  noSpike_Time    = new TH1D( "noSpike_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;
  noSpike_Phi_Time = new TH2D( "noSpike_Phi_Time", "#phi vs Non Spike Photon time ", 63, -3.15, 3.15, 160,  -20, 20 ) ;
  noSpike_Eta_Time = new TH2D( "noSpike_Eta_Time", "#eta vs Non Spike Photon time ", 51, -2.5, 2.5, 160,  -20, 20 ) ;
  noSpike_sMaj_sMin = new TH2D( "noSpike_sMaj_sMin", "sMaj vs sMin for non spike photon",100, 0, 2, 50, 0.1, 0.4   ) ;
  noSpike_sMaj_Time = new TH2D( "noSpike_sMaj_Time",  "sMaj vs Ecal time for non spike Photon", 100, 0, 2, 160, -20, 20 ) ;
  noSpike_sMin_Time = new TH2D( "noSpike_sMin_Time",  "sMin vs. Ecal time for non spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;

  notSpike_nXtl   = new TH1D("notSpike_nXtl", "N of crystals for non-spike photon ", 50,  0, 50 );

  pure_Time      = new TH1D( "pure_Time", "  time for pure photon", 160, -14.5, 25.5 ) ;
  pure_Eta_Time  = new TH2D( "pure_Eta_Time", " #eta vs time for pure photon",  51, -2.5, 2.5,   160, -20, 20 ) ;
  pure_Phi_Time  = new TH2D( "pure_Phi_Time", " #phi vs time for pure photon",  63, -3.15, 3.15, 160, -20, 20 ) ;
  pure_sMaj_sMin = new TH2D( "pure_sMaj_sMin", "sMaj vs sMin for pure photon", 100,  0, 2, 50, 0.1, 0.4   ) ;

  nHL_Eta  = new TH1D( "nHL_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
  nSpk_Eta = new TH1D( "nSpk_Eta",  " N of Spike in |#eta|", 5, 0., 1.4 ) ;
  nCS_Eta  = new TH1D( "nCS_Eta",  " N of CS in |#eta|", 5, 0., 1.4 ) ;
 
  // x is eta region , each is 0.28 , y is different sample, 0:total, 1:halo, 2: spike
  hBg_sg = new TH2D( "hBg_sg", "Background in signal region",          5,  0., 5, 3, 0, 3 ) ;
  hBg_m  = new TH2D( "hBg_m",  "Background in MET > 60 GeV, t < -2ns", 5,  0., 5, 3, 0, 3 ) ;
  hBg_t  = new TH2D( "hBg_t",  "Background in MET < 60 GeV, t >  2ns", 5,  0., 5, 3, 0, 3 ) ;
  hBg_mt  = new TH2D( "hBg_mt","Background in MET < 60 GeV, t > -2ns", 5,  0., 5, 3, 0, 3 ) ;

  for (int i=0; i<5 ; i++) {
      // signal region
      s_Count[i] = 0 ;
      h_Count[i] = 0 ;
      B_Count[i] = 0 ;

      // low MET, t > 2ns 
      st_Count[i] = 0 ;
      ht_Count[i] = 0 ;
      Bt_Count[i] = 0 ;

      // pass MET cut, t < -2ns
      sm_Count[i] = 0 ;
      hm_Count[i] = 0 ;
      Bm_Count[i] = 0 ;

      // low MET, t < -2ns 
      sa_Count[i] = 0 ;
      ha_Count[i] = 0 ;
      Ba_Count[i] = 0 ;
  }

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
     h_EB_Time3 = (TH1D*) theFile->Get("h_EB_Time3");
     h_EE_Time  = (TH1D*) theFile->Get("h_EE_Time");
     h_EE_Time0 = (TH1D*) theFile->Get("h_EE_Time0");
     h_EE_Time1 = (TH1D*) theFile->Get("h_EE_Time1");
     h_EE_Time2 = (TH1D*) theFile->Get("h_EE_Time2");
     h_EE_Time3 = (TH1D*) theFile->Get("h_EE_Time3");

     h_Eta_Time  = (TH2D*) theFile->Get("h_Eta_Time");
     h_Phi_Time  = (TH2D*) theFile->Get("h_Phi_Time");
     h_cscdPhi_Time = (TH2D*) theFile->Get("h_cscdPhi_Time");
     h_sMaj_Time_EB = (TH2D*) theFile->Get("h_sMaj_Time_EB");
     h_sMaj_Time_EE = (TH2D*) theFile->Get("h_sMaj_Time_EE");
     h_sMin_Time_EB = (TH2D*) theFile->Get("h_sMin_Time_EB");
     h_sMin_Time_EE = (TH2D*) theFile->Get("h_sMin_Time_EE");
     h_sigIeta_Time_EB = (TH2D*) theFile->Get("h_sigIeta_Time_EB");
     h_sigIeta_Time_EE = (TH2D*) theFile->Get("h_sigIeta_Time_EE");
     h_Pt_Time_EB  = (TH2D*) theFile->Get("h_Pt_Time_EB");
     h_Pt_Time_EE  = (TH2D*) theFile->Get("h_Pt_Time_EE");
     h_MET_Time_EB = (TH2D*) theFile->Get("h_MET_Time_EB");
     h_MET_Time_EE = (TH2D*) theFile->Get("h_MET_Time_EE");
     h_cHadIso_Time = (TH2D*) theFile->Get("h_cHadIso_Time");
     h_nHadIso_Time = (TH2D*) theFile->Get("h_nHadIso_Time");
     h_photIso_Time = (TH2D*) theFile->Get("h_photIso_Time");

     h_sMaj_Eta  = (TH2D*) theFile->Get("h_sMaj_Eta");
     h_sMaj_Phi  = (TH2D*) theFile->Get("h_sMaj_Phi");
     h_sMaj_sMin = (TH2D*) theFile->Get("h_sMaj_sMin");
     h_sigEta_sMaj      = (TH2D*) theFile->Get("h_sigEta_sMaj");
     h_sigEta_sMaj_late = (TH2D*) theFile->Get("h_sigEta_sMaj_late");
     h_nXtl_Eta = (TH2D*) theFile->Get("h_nXtl_Eta");
     h_nXtl_Pt  = (TH2D*) theFile->Get("h_nXtl_Pt");

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
     sg_cHadIso_Time = (TH2D*) theFile->Get("sg_cHadIso_Time");
     sg_nHadIso_Time = (TH2D*) theFile->Get("sg_nHadIso_Time");
     sg_photIso_Time = (TH2D*) theFile->Get("sg_photIso_Time");
     sg_photIso_sMaj = (TH2D*) theFile->Get("sg_photIso_sMaj");
     sg_photIso_sMin = (TH2D*) theFile->Get("sg_photIso_sMin");
     sg_photIso_sigIeta = (TH2D*) theFile->Get("sg_photIso_sigIeta");
     sg_sMaj_Time = (TH2D*) theFile->Get("sg_sMaj_Time");
     sg_sMin_Time = (TH2D*) theFile->Get("sg_sMin_Time");
     sg_sMaj_Eta  = (TH2D*) theFile->Get("sg_sMaj_Eta");
     sg_sMin_Eta  = (TH2D*) theFile->Get("sg_sMin_Eta");
     //sg_gg_dR     = (TH1D*) theFile->Get("sg_gg_dR");

     sel_Time        = (TH1D*) theFile->Get("sel_Time");
     sel_Eta_Time = (TH2D*) theFile->Get("sel_Eta_Time");
     sel_Phi_Time = (TH2D*) theFile->Get("sel_Phi_Time");
     sel_sMaj_Time = (TH2D*) theFile->Get("sel_sMaj_Time");
     sel_sMin_Time = (TH2D*) theFile->Get("sel_sMin_Time");
     sel_sMaj_Eta  = (TH2D*) theFile->Get("sel_sMaj_Eta");
     sel_sMin_Eta  = (TH2D*) theFile->Get("sel_sMin_Eta");

     cs_Eta_Time = (TH2D*) theFile->Get("cs_Eta_Time");
     cs_Phi_Time = (TH2D*) theFile->Get("cs_Phi_Time");
     cs_sigIeta_Time = (TH2D*) theFile->Get("cs_sigIeta_Time");
     cs_cscdPhi      = (TH1D*) theFile->Get("cs_cscdPhi");
     cs_nXtl         = (TH1D*) theFile->Get("cs_nXtl");
     cs_nXtl_Eta     = (TH2D*) theFile->Get("cs_nXtl_Eta");
     cs_cHadIso_Time = (TH2D*) theFile->Get("cs_cHadIso_Time");
     cs_nHadIso_Time = (TH2D*) theFile->Get("cs_nHadIso_Time");
     cs_photIso_Time = (TH2D*) theFile->Get("cs_photIso_Time");

     sideband_photIso_cscdPhi = (TH2D*) theFile->Get("sideband_photIso_cscdPhi");
     sideband_sMaj_Time = (TH2D*) theFile->Get("sideband_sMaj_Time");
     sideband_sMaj_Phi  = (TH2D*) theFile->Get("sideband_sMaj_Phi");
     sideband_sMaj_sMin = (TH2D*) theFile->Get("sideband_sMaj_sMin");
     sideband_sMaj_Eta  = (TH2D*) theFile->Get("sideband_sMaj_Eta");
     sideband_nXtl_Eta  = (TH2D*) theFile->Get("sideband_nXtl_Eta");
     sideband_cscdPhi   = (TH1D*) theFile->Get("sideband_cscdPhi");
     sideband_cscdPhi_a3   = (TH1D*) theFile->Get("sideband_cscdPhi_a3");
     sideband_cscdPhi_b3   = (TH1D*) theFile->Get("sideband_cscdPhi_b3");
     sideband_cscdPhi_c2   = (TH1D*) theFile->Get("sideband_cscdPhi_c2");
     sideband_nXtl = (TH1D*) theFile->Get("sideband_nXtl");
     sideband_sMaj = (TH1D*) theFile->Get("sideband_sMaj");

     bg_Eta_Time = (TH2D*) theFile->Get("bg_Eta_Time");

     qcdCS_Time      = (TH1D*) theFile->Get("qcdCS_Time");
     qcdCS_Eta_Time  = (TH2D*) theFile->Get("qcdCS_Eta_Time");

     haloCS_nXtl_a3  = (TH1D*) theFile->Get("haloCS_nXtl_a3");
     haloCS_nXtl_b3  = (TH1D*) theFile->Get("haloCS_nXtl_b3");
     haloCS_nXtl_c2  = (TH1D*) theFile->Get("haloCS_nXtl_c2");
     spikeCS_nXtl_a3  = (TH1D*) theFile->Get("spikeCS_nXtl_a3");
     spikeCS_nXtl_b3  = (TH1D*) theFile->Get("spikeCS_nXtl_b3");
     spikeCS_nXtl_c2  = (TH1D*) theFile->Get("spikeCS_nXtl_c2");

     haloCS_sMaj_Eta  = (TH2D*) theFile->Get("haloCS_sMaj_Eta");
     haloCS_sMaj_Phi  = (TH2D*) theFile->Get("haloCS_sMaj_Phi");
     haloCS_Eta_Time  = (TH2D*) theFile->Get("haloCS_Eta_Time");
     haloCS_Eta_Time1 = (TH2D*) theFile->Get("haloCS_Eta_Time1");

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

     halo_Eta_Time = (TH2D*) theFile->Get("halo_Eta_Time");
     halo_Phi_Time = (TH2D*) theFile->Get("halo_Phi_Time");
     halo_sMin_Time = (TH2D*) theFile->Get("halo_sMin_Time");
     halo_sMaj_Time = (TH2D*) theFile->Get("halo_sMaj_Time");
     halo_photIso_Time = (TH2D*) theFile->Get("halo_photIso_Time");
     halo_sMaj_sMin    = (TH2D*) theFile->Get("halo_sMaj_sMin");
     halo_sigEta  = (TH1D*) theFile->Get("halo_sigEta");
     halo_sigIeta = (TH1D*) theFile->Get("halo_sigIeta");
     halo_Time    = (TH1D*) theFile->Get("halo_Time");

     noHalo_sigEta = (TH1D*) theFile->Get("noHalo_sigEta");
     noHalo_sigIeta = (TH1D*) theFile->Get("noHalo_sigIeta");
     noHalo_Time = (TH1D*) theFile->Get("noHalo_Time");
     noHalo_Phi_Time = (TH2D*) theFile->Get("noHalo_Phi_Time");
     noHalo_Eta_Time = (TH2D*) theFile->Get("noHalo_Eta_Time");
     noHalo_sMaj_sMin = (TH2D*) theFile->Get("noHalo_sMaj_sMin");
     noHalo_sMaj_Time = (TH2D*) theFile->Get("noHalo_sMaj_Time");
     noHalo_sMin_Time = (TH2D*) theFile->Get("noHalo_sMin_Time");

     noHalo_nXtl_side = (TH1D*) theFile->Get("noHalo_nXtl_side");
     noHalo_nXtl_center = (TH1D*) theFile->Get("noHalo_nXtl_center");

     spike_Eta_Time = (TH2D*) theFile->Get("spike_Eta_Time");
     spike_Phi_Time = (TH2D*) theFile->Get("spike_Phi_Time");
     spike_sMaj_sMin = (TH2D*) theFile->Get("spike_sMaj_sMin");
     spike_sMaj_Time = (TH2D*) theFile->Get("spike_sMaj_Time");
     spike_sMin_Time = (TH2D*) theFile->Get("spike_sMin_Time");
     spike_photIso_Time = (TH2D*) theFile->Get("spike_photIso_Time");
     spike_sigEta = (TH1D*) theFile->Get("spike_sigEta");
     spike_sigIeta = (TH1D*) theFile->Get("spike_sigIeta");
     spike_Time = (TH1D*) theFile->Get("spike_Time");

     noSpike_Phi_Time = (TH2D*) theFile->Get("noSpike_Phi_Time");
     noSpike_Eta_Time = (TH2D*) theFile->Get("noSpike_Eta_Time");
     noSpike_sMaj_sMin = (TH2D*) theFile->Get("noSpike_sMaj_sMin");
     noSpike_sMaj_Time = (TH2D*) theFile->Get("noSpike_sMaj_Time");
     noSpike_sMin_Time = (TH2D*) theFile->Get("noSpike_sMin_Time");
     noSpike_sigEta    = (TH1D*) theFile->Get("noSpike_sigEta");
     noSpike_sigIeta   = (TH1D*) theFile->Get("noSpike_sigIeta");
     noSpike_Time      = (TH1D*) theFile->Get("noSpike_Time");

     notSpike_nXtl = (TH1D*) theFile->Get("notSpike_nXtl");

     pure_Time = (TH1D*) theFile->Get("pure_Time");
     pure_Eta_Time  = (TH2D*) theFile->Get("pure_Eta_Time");
     pure_Phi_Time  = (TH2D*) theFile->Get("pure_Phi_Time");
     pure_sMaj_sMin = (TH2D*) theFile->Get("pure_sMaj_sMin");

     nHL_Eta  = (TH1D*) theFile->Get("nHL_Eta");
     nSpk_Eta = (TH1D*) theFile->Get("nSpk_Eta");
     nCS_Eta  = (TH1D*) theFile->Get("nCS_Eta");

     hBg_sg   = (TH2D*) theFile->Get("hBg_sg") ;
     hBg_m    = (TH2D*) theFile->Get("hBg_m") ;
     hBg_t    = (TH2D*) theFile->Get("hBg_t") ;
     hBg_mt   = (TH2D*) theFile->Get("hBg_mt") ;

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
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("totalNVtx",   &totalNVtx);
   
   tr->SetBranchAddress("nOutTimeHits", &nHaloHits ) ;
   tr->SetBranchAddress("nHaloTrack",   &nHaloTracks ) ;
   tr->SetBranchAddress("haloPhi",      &haloPhi ) ;
   tr->SetBranchAddress("haloRho",      &haloRho ) ;

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

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

       // testing for raw information - no cut applied
       for ( int g=0 ; g < nPhotons ; g++ ) {

	   TLorentzVector gP4_ = TLorentzVector( phoPx[g], phoPy[g], phoPz[g], phoE[g] ) ;
           //if ( fabs(gP4_.Eta()) > 1.47 ) continue ;
           if ( fabs(gP4_.Eta()) < 1.45 ) {
              if ( selectJets.size()  > 0 ) h_EB_Time->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 0 ) h_EB_Time0->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 1 ) h_EB_Time1->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 2 ) h_EB_Time2->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 3 ) h_EB_Time3->Fill( seedTime[g] , weight );
           } 
           if ( fabs(gP4_.Eta()) > 1.5 ) {
              if ( selectJets.size()  > 0 ) h_EE_Time->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 0 ) h_EE_Time0->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 1 ) h_EE_Time1->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 2 ) h_EE_Time2->Fill( seedTime[g] , weight );
              if ( selectJets.size() == 3 ) h_EE_Time3->Fill( seedTime[g] , weight );
           }

           h_Eta_Time->Fill( gP4_.Eta() , seedTime[g] , weight );
 	   h_Phi_Time->Fill( gP4_.Phi() , seedTime[g] , weight );
	   h_cscdPhi_Time->Fill( cscdPhi[g], seedTime[g] , weight  ) ;
           if ( fabs( gP4_.Eta() ) < 1.45 ) {
  	      h_sMin_Time_EB->Fill( sMinPho[g] , seedTime[g] , weight );
	      h_sMaj_Time_EB->Fill( sMajPho[g] , seedTime[g] , weight );
	      h_sigIeta_Time_EB->Fill( sigmaIeta[g], seedTime[g] , weight  ) ;
	      h_Pt_Time_EB->Fill( gP4_.Pt(), seedTime[g] , weight  ) ;
	      h_MET_Time_EB->Fill( metE, seedTime[g] , weight  ) ;
           }
           if ( fabs( gP4_.Eta() ) > 1.5 ) {
  	      h_sMin_Time_EE->Fill( sMinPho[g] , seedTime[g] , weight );
	      h_sMaj_Time_EE->Fill( sMajPho[g] , seedTime[g] , weight );
	      h_sigIeta_Time_EE->Fill( sigmaIeta[g], seedTime[g] , weight  ) ;
	      h_Pt_Time_EE->Fill( gP4_.Pt(), seedTime[g] , weight  ) ;
	      h_MET_Time_EE->Fill( metE, seedTime[g] , weight  ) ;
           }

	   h_sMaj_Eta->Fill( sMajPho[g] , gP4_.Eta() , weight ) ;
	   h_sMaj_sMin->Fill( sMajPho[g] , sMinPho[g] , weight );
	   h_nXtl_Eta->Fill( nXtals[g],  gP4_.Eta() , weight );
	   h_nXtl_Pt->Fill( nXtals[g],  gP4_.Pt() , weight );
	   h_sigEta_sMaj->Fill( sigmaEta[g], sMajPho[g] , weight  ) ;
	   if ( seedTime[g] > 2.99 ) h_sigEta_sMaj_late->Fill( sigmaEta[g], sMajPho[g] , weight  ) ;
	   if ( sMajPho[g] > 0.4 ) h_sMaj_Phi->Fill(sMajPho[g] , gP4_.Phi() , weight ) ;
	   double nHIso = max( nHadIso[g] - (0.04*gP4_.Pt()) , 0. ) ;
	   double phIso = max( photIso[g] - (0.005*gP4_.Pt()) , 0. ) ;
           h_cHadIso_Time->Fill( cHadIso[g] , seedTime[g] , weight ) ;
           h_nHadIso_Time->Fill( nHIso , seedTime[g] , weight ) ;
           h_photIso_Time->Fill( phIso , seedTime[g] , weight ) ;

       }

       // constrol sample - events fails MET cuts 
       if ( !pass ) continue ;
       nEvt++; 

	  //cout<<" EVT# : "<< nEvt <<endl ;
	  for ( size_t kk =0; kk < selectPho.size() ; kk++) {
              int k = selectPho[kk].first ;
	      TLorentzVector gP4_ = TLorentzVector( phoPx[k], phoPy[k], phoPz[k], phoE[k] ) ;

	      // Define the Tag and Check the efficiency 
	      bool haloTag  = ( cscdPhi[k] < 0.05 && fabs( gP4_.Eta() ) <= 0.75 ) ? true : false  ;
	      if ( sMajPho[k] > 0.7 && cscdPhi[k] < 0.1 && fabs( gP4_.Eta() ) > 0.75 && fabs(gP4_.Eta()) < 1.45 ) haloTag = true;

	      bool spikeTag = ( nXtals[k] < 7 && !haloTag ) ? true : false  ;
	      bool ghostTag = ( haloTag || spikeTag ) ? true : false ;

              // ******************
              //   Region A and B
              // ******************
              //if ( selectPho[0].second.Pt() < 80. && metE > jetCuts[4] && selectJets.size() > 0 ) {
              if ( selectPho[0].second.Pt() > 80. && metE < jetCuts[4] && selectJets.size() < 1 ) {

                 obsTime->Fill( seedTime[k], weight );
                 bg_Eta_Time->Fill( gP4_.Eta() , seedTime[k], weight ) ;

   	         double phIso = max( photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
		 // Look at the sideband of time spectrum 
		 if ( fabs( seedTime[k] ) > 3. ) {
     	            sideband_sMaj_sMin->Fill( sMajPho[k] , sMinPho[k] , weight );
		    sideband_sMaj_Phi->Fill( sMajPho[k] , gP4_.Phi() , weight );
		    sideband_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
		    sideband_sMaj_Eta->Fill( sMajPho[k] , gP4_.Eta() , weight );
		    sideband_nXtl_Eta->Fill( nXtals[k], gP4_.Eta() , weight );
		    sideband_photIso_cscdPhi->Fill( phIso , cscdPhi[k] , weight ) ;
		    sideband_cscdPhi->Fill( cscdPhi[k] , weight );
		    sideband_nXtl->Fill( nXtals[k] , weight );
		    sideband_sMaj->Fill( sMajPho[k] , weight ) ;
                 }
		 if ( seedTime[k] > 3. )       sideband_cscdPhi_a3->Fill( cscdPhi[k] , weight );
		 if ( seedTime[k] < -3. )      sideband_cscdPhi_b3->Fill( cscdPhi[k] , weight );
		 if ( fabs(seedTime[k]) < 2. ) sideband_cscdPhi_c2->Fill( cscdPhi[k] , weight );
              

                 // Region B
		 if ( seedTime[k] > 2. ) {
	  	    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;
		    Bt_Count[ ih ]++ ;
		    if ( haloTag  ) ht_Count[ ih ]++ ;
		    if ( spikeTag ) st_Count[ ih ]++ ;

		    hBg_t->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_t->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_t->Fill( ih, 2.5, weight );
                 }
                 // Region A
		 if ( seedTime[k] < -3. ) {
	  	    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;
		    Ba_Count[ ih ]++ ;
		    if ( haloTag  ) ha_Count[ ih ]++ ;
		    if ( spikeTag ) sa_Count[ ih ]++ ;

		    hBg_mt->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_mt->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_mt->Fill( ih, 2.5, weight );
                 }
            
                 // The result of halo tagging and spike tagging 
                 if ( haloTag ) {
                    halo_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    halo_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    halo_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    halo_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    halo_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		    halo_sigEta->Fill( sigmaEta[k] , weight ) ;
		    halo_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		    halo_Time->Fill( seedTime[k] , weight ) ;
		    halo_photIso_Time->Fill( phIso, seedTime[k] , weight ) ;

                 } else {
                    noHalo_Eta_Time->Fill( gP4_.Eta(), seedTime[k] , weight ) ;
                    noHalo_Phi_Time->Fill( gP4_.Phi(), seedTime[k] , weight ) ;
		    noHalo_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		    noHalo_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    noHalo_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    noHalo_sigEta->Fill( sigmaEta[k] , weight ) ;
		    noHalo_sigIeta->Fill( sigmaIeta[k] , weight ) ;
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
		    spike_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		    spike_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    spike_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    spike_sigEta->Fill( sigmaEta[k] , weight ) ;
		    spike_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		    spike_Time->Fill( seedTime[k] , weight ) ;
		    spike_photIso_Time->Fill( phIso, seedTime[k] , weight ) ;
                 } else {
                    noSpike_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    noSpike_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    noSpike_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		    noSpike_sMaj_Time->Fill( sMajPho[k], seedTime[k] , weight ) ;
		    noSpike_sMin_Time->Fill( sMinPho[k], seedTime[k] , weight ) ;
		    noSpike_sigEta->Fill( sigmaEta[k] , weight ) ;
		    noSpike_sigIeta->Fill( sigmaIeta[k] , weight ) ;
		    noSpike_Time->Fill( seedTime[k] , weight ) ;
                 }
                 if ( sMajPho[k] < 0.7 && cscdPhi[k] > 0.1 ) notSpike_nXtl->Fill( nXtals[k] , weight );
 
                 if ( !ghostTag ) {
                    pure_sMaj_sMin->Fill( sMajPho[k], sMinPho[k] , weight ) ;
		    pure_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    pure_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    pure_Time->Fill( seedTime[k] , weight );
		 }

		 // QCD Sample
		 if ( selectJets.size() > 0 && sMajPho[k] < 0.6 && sMinPho[k] > 0.2 && cscdPhi[k] > 0.1 ) {
                    qcdCS_Time->Fill( seedTime[k] , weight ) ;
   		    qcdCS_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
                 }
              }

              // Current Halo-Control Sample - for efficiency and fake rate study
              // **********************************************
              //   Region for Efficiency and fake rate study
              // **********************************************
              if ( selectPho[0].second.Pt() < 80. && metE < jetCuts[4] && selectJets.size() < 1 ) {

                 if ( fabs( gP4_.Phi() ) < 0.1 || fabs( fabs(gP4_.Phi()) - 3.14 ) < 0.1  ) {
                    if ( fabs( gP4_.Eta() ) < 1.4 &&  seedTime[k]  < -3 && nXtals[k] > 7 ) {
                       haloCS_sMaj_Eta->Fill(sMajPho[k] , gP4_.Eta() , weight ) ;
		       haloCS_sMaj_Phi->Fill( sMajPho[k] , gP4_.Phi() , weight );
		       haloCS_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );

		       // Count efficiency in different eta slice 
		       double haloEta = ( fabs(gP4_.Eta()) > 1.67 ) ? 1.67 : fabs(gP4_.Eta()) ;
		       halo_Eta[0]->Fill( haloEta, weight ) ;

	  	       if ( haloTag ) {
                          haloCS_Eta_Time1->Fill( gP4_.Eta() , seedTime[k] , weight );
			  halo_Eta[1]->Fill( haloEta, weight ) ;
		       }
                    }
                    // For DOE2013
                    if ( fabs( gP4_.Eta() ) < 1.4 && sMajPho[k] > 0.6 ) {   
                       if ( seedTime[k] > 3. )         haloCS_nXtl_a3->Fill( nXtals[k] , weight );
                       if ( seedTime[k] < -3. )        haloCS_nXtl_b3->Fill( nXtals[k] , weight );
                       if ( fabs(seedTime[k]) < 2.  )  haloCS_nXtl_c2->Fill( nXtals[k] , weight );
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
                 // For DOE2013 
                 if ( fabs( gP4_.Eta() ) < 1.4 && sMajPho[k] < 0.7 ) {
  		    if ( seedTime[k] >  3. )       spikeCS_nXtl_a3->Fill( nXtals[k] , weight );
  		    if ( seedTime[k] < -3. )       spikeCS_nXtl_b3->Fill( nXtals[k] , weight );
		    if ( fabs(seedTime[k]) < 2. )  spikeCS_nXtl_c2->Fill( nXtals[k] , weight );
                 }
              }

              // Check mis-tagging rate from real photon
              bool passCSSelect = false ;
              if ( fabs(seedTime[k]) < 2 && isData == 1 && selectJets.size()  > 0 && met.Et() < 60.) passCSSelect = true ;
              if (       seedTime[k] > 2 && isData == 0 ) passCSSelect = true ;

              if ( passCSSelect ) {

                 // For Halo
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

                 nCS_Eta->Fill( fabs(gP4_.Eta()) , weight )  ;
                 // For Halo
                 if ( haloTag ) nHL_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;
                 // For Spike -  need to exclude halo
                 if ( spikeTag ) nSpk_Eta->Fill( fabs(gP4_.Eta()) , weight ) ;

              }
 
              // ******************
              //   Region C and D
              // ******************
              // signal sample - require MET cut 
              //if ( pass && metE > jetCuts[4] ) {
              //if ( selectPho[0].second.Pt() > 80. && metE > jetCuts[4] && selectJets.size() > 1 ) {
              if ( selectPho[0].second.Pt() > 80. && metE > jetCuts[4] && selectJets.size() < 1 ) {
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
		 sg_cscdPhi->Fill( cscdPhi[k], weight  ) ;
		 double nHIso = max( nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
		 double phIso = max( photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
		 sg_cHadIso_Time->Fill( cHadIso[k] , seedTime[k] , weight ) ;
		 sg_nHadIso_Time->Fill( nHIso , seedTime[k] , weight ) ;
		 sg_photIso_Time->Fill( phIso , seedTime[k] , weight ) ;
		 sg_photIso_sMaj->Fill( phIso , sMajPho[k] , weight ) ;
		 sg_photIso_sMin->Fill( phIso , sMinPho[k] , weight ) ;
		 sg_photIso_sigIeta->Fill( phIso , sigmaIeta[k] , weight ) ;

		 /*
                 double dRgg = 5. ;
   	         for ( size_t jj =0; jj < selectPho.size() ; jj++) {
                     if (  kk == jj || kk < jj ) continue ;
		     int j = selectPho[jj].first ;
		     TLorentzVector gP4_b( phoPx[j], phoPy[j], phoPz[j], phoE[j] ) ;
		     double dRgg_ = ( gP4_.DeltaR( gP4_b ) > 5. ) ? 4.99  : gP4_.DeltaR( gP4_b ) ;
		     dRgg = ( dRgg_ < dRgg ) ? dRgg_ : dRgg ;
		     if ( dRgg_ < 0.1 ) printf(" t[%d] = %.2f and  t[%d] = %.2f \n ", (int)kk, seedTime[k], (int)jj, seedTime[j] ) ;
                 }
                 if ( selectPho.size() > 1 ) sg_gg_dR->Fill( dRgg ) ;
                 */

		 //if ( seedTime[k] > 2 && sigmaIeta[k] > 0.02 && phIso > 3. ) {
		 //   printf( "run:%d, lumi:%d, eventId: %d,  nPho: %d, nJet: %d \n"
		 //          , runId, lumiSection, eventId , nPhotons, nJets ) ;
		 //}

                 if ( !ghostTag ) {
	            sel_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    sel_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    sel_sMaj_Time->Fill( sMajPho[k] , seedTime[k] , weight );
		    sel_sMaj_Eta->Fill( sMajPho[k] , gP4_.Eta() , weight );
		    sel_sMin_Time->Fill( sMinPho[k] , seedTime[k] , weight );
		    sel_sMin_Eta->Fill( sMinPho[k] , gP4_.Eta() , weight );
		    sel_Time->Fill( seedTime[k] , weight ) ;
		 }
                 if ( haloTag  ) sg_Time_halo->Fill( seedTime[k] , weight ) ;
		 if ( haloTag  ) sg_Eta_Time_halo->Fill( gP4_.Eta() , seedTime[k] , weight );

		 if ( spikeTag ) sg_Time_spike->Fill( seedTime[k] , weight ) ;
		 if ( spikeTag ) sg_Eta_Time_spike->Fill( gP4_.Eta() , seedTime[k] , weight );

                 // Count the background estimation at MET > 60 GeV, t > 2ns Region
                 // Region D
                 if ( seedTime[k] > 2. ) {
                    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;
		    B_Count[ ih ]++ ;
		    if ( haloTag  ) h_Count[ ih ]++ ;
		    if ( spikeTag ) s_Count[ ih ]++ ;

                    hBg_sg->Fill( ih, 0.5, weight );
                    if ( haloTag  ) hBg_sg->Fill( ih, 1.5, weight );
                    if ( spikeTag ) hBg_sg->Fill( ih, 2.5, weight );
                 }
                 // Check the background estimation at MET > 60 GeV, t < -3ns Region
                 // Region C
                 if ( seedTime[k] < -3. ) {
                    int ih = ( fabs(gP4_.Eta()) >= 1.4 ) ? 4 :  ( fabs(gP4_.Eta()) / 0.28 ) ;
		    Bm_Count[ ih ]++ ;
		    if ( haloTag  ) hm_Count[ ih ]++ ;
		    if ( spikeTag ) sm_Count[ ih ]++ ;

		    hBg_m->Fill( ih, 0.5, weight );
		    if ( haloTag  ) hBg_m->Fill( ih, 1.5, weight );
		    if ( spikeTag ) hBg_m->Fill( ih, 2.5, weight );
                 }

                 // Good photon behavior
                 if ( seedTime[k] > -2. && seedTime[k] < 2. ) {
      		    cs_Eta_Time->Fill( gP4_.Eta() , seedTime[k] , weight );
		    cs_Phi_Time->Fill( gP4_.Phi() , seedTime[k] , weight );
		    cs_sigIeta_Time->Fill( sigmaIeta[k], seedTime[k] , weight ) ;
		    cs_nXtl->Fill( nXtals[k] , weight );
		    cs_nXtl_Eta->Fill( nXtals[k] , gP4_.Eta() , weight );
		    cs_cscdPhi->Fill( cscdPhi[k], weight  ) ;
		    cs_cHadIso_Time->Fill( cHadIso[k] , seedTime[k] , weight ) ;
		    cs_nHadIso_Time->Fill( nHIso , seedTime[k] , weight ) ;
		    cs_photIso_Time->Fill( phIso , seedTime[k] , weight ) ;
                 }
              }

          } // end of photon looping 
   } // end of event looping
 

   double totalB = 0 ;
   double Bg_m = 0 ; 
   double Bg_t = 0 ; 
   int Bg_exp = 0 ; 
   int Bg_m_exp = 0 ; 
   int Bg_t_exp = 0 ; 
   for ( int i=0; i< 5; i++ ) {
       vector<double> bgV = GetComponent( i, B_Count[i], h_Count[i], s_Count[i] ) ;
       totalB += bgV[0] ;
       totalB += bgV[1] ;
       Bg_exp += B_Count[i] ;
       printf(" eta(%d) : spike:%f , halo:%f , B+= %f  from %d \n ", i, bgV[0], bgV[1], totalB, B_Count[i] ) ;

       vector<double> bmV = GetComponent( i, Bm_Count[i], hm_Count[i], sm_Count[i] ) ;
       Bg_m += bmV[0] ;
       Bg_m += bmV[1] ;
       Bg_m_exp += Bm_Count[i] ;
       vector<double> btV = GetComponent( i, Bt_Count[i], ht_Count[i], st_Count[i] ) ;
       Bg_t += btV[0] ;
       Bg_t += btV[1] ;
       Bg_t_exp += Bt_Count[i] ;
   }
   printf(" B from MET > 60 GeV & T >  2ns :  %d -> %f \n ", Bg_exp,   totalB ) ;
   printf(" B from MET > 60 GeV & T < -3ns :  %d -> %f \n ", Bg_m_exp, Bg_m ) ;
   printf(" B from MET < 60 GeV & T >  2ns :  %d -> %f \n ", Bg_t_exp, Bg_t ) ;

   select->PrintCutFlow() ;
   writeHist = true ;
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
   h_draw->Draw(   h_EB_Time,      "h_EB_Time",     "Time from EB ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time0,     "h_EB_Time0",     "Time from EB for 0 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time1,     "h_EB_Time1",     "Time from EB for 1 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time2,     "h_EB_Time2",     "Time from EB for 2 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EB_Time3,     "h_EB_Time3",     "Time from EB for 3 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time,      "h_EE_Time",     "Time from EE ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time0,     "h_EE_Time0",     "Time from EE for 0 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time1,     "h_EE_Time1",     "Time from EE for 1 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time2,     "h_EE_Time2",     "Time from EE for 2 jet event", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   h_EE_Time3,     "h_EE_Time3",     "Time from EE for 3 jet event", "", "logY", 0.95, 1 ) ;

   if ( isData == 1 ) {
   h_draw->SetHistoInfo(2) ; // set histo lineWidth

   sideband_cscdPhi_b3->SetFillColor(5) ;
   sideband_cscdPhi_a3->SetLineWidth(2) ;
   sideband_cscdPhi_c2->SetLineWidth(2) ;
   TLegend* leg3  = new TLegend(.6, .7, .9, .9 );
   leg3->AddEntry( sideband_cscdPhi_b3, " t < -3 ns" , "F" ) ;
   leg3->AddEntry( sideband_cscdPhi_a3, " t >  3 ns" , "L" ) ;
   leg3->AddEntry( sideband_cscdPhi_c2, "|t| < 2 ns" , "L" ) ;
 
   sideband_cscdPhi_b3->SetTitle( "" ) ;
   h_draw->Draw(  sideband_cscdPhi_b3, "", "#Delta#Phi(cscSegment,#gamma) ", "", "logY", 0.95, 1, 1./ sideband_cscdPhi_b3->Integral() ) ;
   h_draw->DrawAppend( sideband_cscdPhi_a3, "",            0.75, 2 , 1./ sideband_cscdPhi_a3->Integral() ) ;
   h_draw->DrawAppend( sideband_cscdPhi_c2, "DOE_cscdPhi", 0.55, 4 , 1./ sideband_cscdPhi_c2->Integral(), leg3 ) ;

   leg3->Clear() ;
   haloCS_nXtl_b3->SetFillColor(5) ;
   haloCS_nXtl_a3->SetLineWidth(2) ;
   haloCS_nXtl_c2->SetLineWidth(2) ;
   leg3->AddEntry( haloCS_nXtl_b3, " t < -3 ns" , "F" ) ;
   leg3->AddEntry( haloCS_nXtl_a3, " t >  3 ns" , "L" ) ;
   leg3->AddEntry( haloCS_nXtl_c2, "|t| < 2 ns" , "L" ) ;
   haloCS_nXtl_b3->SetTitle( "" ) ;
   h_draw->Draw(       haloCS_nXtl_b3, "", " N of crystal (Halo CS)", "", "logY", 0.95, 1, 1./ haloCS_nXtl_b3->Integral() ) ;
   h_draw->DrawAppend( haloCS_nXtl_a3, "",               0.75, 2 , 1./ haloCS_nXtl_a3->Integral() ) ;
   h_draw->DrawAppend( haloCS_nXtl_c2, "DOE_halo_nXtl",  0.55, 4 , 1./ haloCS_nXtl_c2->Integral(), leg3 ) ;

   leg3->Clear() ;
   spikeCS_nXtl_b3->SetFillColor(5) ;
   spikeCS_nXtl_a3->SetLineWidth(2) ;
   spikeCS_nXtl_c2->SetLineWidth(2) ;
   leg3->AddEntry( spikeCS_nXtl_b3, " t < -3 ns" , "F" ) ;
   leg3->AddEntry( spikeCS_nXtl_a3, " t >  3 ns" , "L" ) ;
   leg3->AddEntry( spikeCS_nXtl_c2, "|t| < 2 ns" , "L" ) ;
   spikeCS_nXtl_b3->SetTitle( "" ) ;
   h_draw->Draw(       spikeCS_nXtl_b3, "", "N of crystal (Spike CS) ", "", "logY", 0.95, 1, 1./ spikeCS_nXtl_b3->Integral() ) ;
   h_draw->DrawAppend( spikeCS_nXtl_a3, "",                0.75, 2 , 1./ spikeCS_nXtl_a3->Integral() ) ;
   h_draw->DrawAppend( spikeCS_nXtl_c2, "DOE_spike_nXtl",  0.55, 4 , 1./ spikeCS_nXtl_c2->Integral(), leg3 ) ;
   } 

   h_draw->SetHistoInfo(1) ;

   h_draw->Draw2D( h_Eta_Time,    "h_Eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( h_Phi_Time,    "h_Phi_Time",    "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( h_cscdPhi_Time,"h_cscdPhi_Time","d#phi", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_cHadIso_Time,"h_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_nHadIso_Time,"h_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_photIso_Time,"h_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EB,   "h_sMaj_Time_EB",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EB,   "h_sMin_Time_EB",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EB,"h_sigIeta_Time_EB","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EB,     "h_Pt_Time_EB", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EB,    "h_MET_Time_EB", "MET", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_sMaj_Time_EE,   "h_sMaj_Time_EE",   "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sMin_Time_EE,   "h_sMin_Time_EE",   "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( h_sigIeta_Time_EE,"h_sigIeta_Time_EE","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_Pt_Time_EE,     "h_Pt_Time_EE", "P_T", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( h_MET_Time_EE,    "h_MET_Time_EE", "MET", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( h_sMaj_Eta,    "h_sMaj_Eta",    "sMaj", "#eta ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_Phi,    "h_sMaj_Phi",    "sMaj", "#phi ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sMaj_sMin,   "h_sMaj_sMin",   "sMaj", "sMin ",  "logZ", 8 ) ;
   h_draw->Draw2D( h_sigEta_sMaj, "h_sigEta_sMaj", "#sigma_{#eta #eta}", "s_{Maj}", "logZ" , 8 ) ;
   h_draw->Draw2D( h_sigEta_sMaj_late, "h_sigEta_sMaj_late", "#sigma_{#eta #eta}", "s_{Maj}", "logZ" , 8 ) ;
   h_draw->Draw2D( h_nXtl_Eta,    "h_nXtl_Eta",    "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw2D( h_nXtl_Pt,     "h_nXtl_Pt",     "N crystals", "P_{T}", "logZ", 8  ) ;

   h_draw->Draw2D( sg_Eta_Time,    "sg_Eta_Time",    "#eta", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sg_Phi_Time,    "sg_Phi_Time",    "#phi", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sg_sigIeta_Time,"sg_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_nXtl_Eta,    "sg_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw(   sg_nXtl,        "sg_nXtl",      "N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   sg_cscdPhi,     "sg_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( sg_cHadIso_Time,"sg_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_nHadIso_Time,"sg_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_photIso_Time,"sg_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_photIso_sMaj,"sg_photIso_sMaj",   " Photon Iso", "sMajor", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_photIso_sMin,"sg_photIso_sMin",   " Photon Iso", "sMinor", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_photIso_sigIeta,"sg_photIso_sigIeta",   " Photon Iso", "sigma_iEta", "logZ" , 8 ) ;
   h_draw->Draw2D( sg_sMaj_Time,   "sg_sMaj_Time",  "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMin_Time,   "sg_sMin_Time",  "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMaj_Eta,    "sg_sMaj_Eta",   "sMaj", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sg_sMin_Eta,    "sg_sMin_Eta",   "sMin", "#eta",  "logZ"  ) ;
   //h_draw->Draw(   sg_gg_dR,       "sg_gg_dR",      "dR(gg) ", "",  "", 0.95, 1 ) ;

   gPad->SetGridx() ;
   TLegend* leg2  = new TLegend(.6, .7, .9, .9 );
   leg2->Clear() ;
   leg2->AddEntry( sg_Time,  " MET > 60 GeV" , "L" ) ;
   leg2->AddEntry( sel_Time, " MET > 60 + NoHalo NoSpike" , "L" ) ;
   leg2->AddEntry( sg_Time,  " MET > 60 + HaloTagged" , "L" ) ;
   leg2->AddEntry( sg_Time,  " MET > 60 + SpikeTagged" , "L" ) ;
   h_draw->Draw(       sg_Time,       "",  "Ecal Time (ns) ", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( sel_Time,      "", 0.75, 2, 1  ) ;
   h_draw->DrawAppend( sg_Time_halo,  "", 0.55, 4, 1  ) ;
   h_draw->DrawAppend( sg_Time_spike, "sg_Time", 0.35, 6, 1 , leg2 ) ;
   gPad->SetGridx() ;

   h_draw->Draw2D( sel_Eta_Time,   "sel_Eta_Time",   "#eta", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sel_Phi_Time,   "sel_Phi_Time",   "#phi", "EcalTime (ns)",  "", 8  ) ;
   h_draw->Draw2D( sel_sMaj_Time,  "sel_sMaj_Time",  "sMaj", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMin_Time,  "sel_sMin_Time",  "sMin", "EcalTime (ns)",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMaj_Eta,   "sel_sMaj_Eta",   "sMaj", "#eta",  "logZ"  ) ;
   h_draw->Draw2D( sel_sMin_Eta,   "sel_sMin_Eta",   "sMin", "#eta",  "logZ"  ) ;

   h_draw->Draw2D( cs_Eta_Time,    "cs_Eta_Time",    "#eta", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( cs_Phi_Time,    "cs_Phi_Time",    "#phi", "EcalTime (ns)",  "logZ", 8 ) ;
   h_draw->Draw2D( cs_sigIeta_Time,"cs_sigIeta_Time","#sigma_{i#eta i#eta}", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_nXtl_Eta,    "cs_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw(   cs_nXtl,        "cs_nXtl",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   cs_cscdPhi,     "cs_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( cs_cHadIso_Time,"cs_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_nHadIso_Time,"cs_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cs_photIso_Time,"cs_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( sideband_photIso_cscdPhi,"sideband_photIso_cscdPhi",  " Photon Iso", "d#Phi", "logZ" , 8 ) ;
   h_draw->Draw2D( sideband_sMaj_Time, "sideband_sMaj_Time", "sMaj", "EcalTime (ns)",  "") ;
   h_draw->Draw2D( sideband_sMaj_Phi,  "sideband_sMaj_Phi",  "sMaj", " #phi",  ""  ) ;
   h_draw->Draw2D( sideband_sMaj_sMin, "sideband_sMaj_sMin", "sMaj", " sMin",  ""  ) ;
   h_draw->Draw2D( sideband_sMaj_Eta,  "sideband_sMaj_Eta",  "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( sideband_nXtl_Eta,  "sideband_nXtl_Eta",  "N crystals", "#eta", "logZ", 8  ) ;
   h_draw->Draw(   sideband_nXtl,      "sideband_nXtl",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   sideband_cscdPhi,   "sideband_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   sideband_sMaj,      "sideband_sMaj",    " sMajor ", "", "", 0.95, 1 ) ;

   h_draw->SetPlotStyle(true) ; // Turn off the stats box
   h_draw->Draw(   qcdCS_Time,       "qcdCS_Time",  "Ecal Time (ns) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( qcdCS_Eta_Time,   "qcdCS_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloCS_sMaj_Eta,  "haloCS_sMaj_Eta", "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( haloCS_sMaj_Phi,  "haloCS_sMaj_Phi", "sMaj", " #phi",  "", 8  ) ;
   h_draw->Draw2D( haloCS_Eta_Time,  "haloCS_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloCS_Eta_Time1, "haloCS_Eta_Time1", "#eta", "EcalTime (ns)",  "", 8 ) ;

   h_draw->Draw2D( spikeCS_Eta_Time1, "spikeCS_Eta_Time1", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_Eta_Time, "spikeCS_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_nXtl_Eta, "spikeCS_nXtl_Eta", "N of xtals", "#eta",  ""  ) ;
   h_draw->Draw2D( spikeCS_Phi_Time, "spikeCS_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( spikeCS_sMaj_sMin, "spikeCS_sMaj_sMin", "sMaj", "sMin (ns)",  ""  ) ;
   h_draw->Draw(   spikeCS_nXtl,     "spikeCS_nXtl",     " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( halo_sMaj_Time, "halo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMin_Time, "halo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMaj_sMin, "halo_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( halo_Eta_Time,  "halo_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Phi_Time,  "halo_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_photIso_Time,"halo_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw(   halo_sigEta,    "halo_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   halo_sigIeta,   "halo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( noHalo_Phi_Time, "noHalo_Phi_Time",  "#phi", " EcalTime (ns) ",  ""  ) ;
   h_draw->Draw2D( noHalo_Eta_Time, "noHalo_Eta_Time",  "#eta", " EcalTime (ns) ",  "", 8 ) ;
   h_draw->Draw2D( noHalo_sMaj_sMin, "noHalo_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;
   h_draw->Draw2D( noHalo_sMaj_Time, "noHalo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( noHalo_sMin_Time, "noHalo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw(   noHalo_sigEta,  "noHalo_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   noHalo_sigIeta, "noHalo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   noHalo_nXtl_side, "noHalo_nXtl_side",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   noHalo_nXtl_center, "noHalo_nXtl_center",  " N of crystals ", "",  "", 0.95, 1 ) ;

   h_draw->Draw2D( spike_sMaj_Time, "spike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMin_Time, "spike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMaj_sMin, "spike_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( spike_Eta_Time,  "spike_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_Phi_Time,  "spike_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_photIso_Time,"spike_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw(   spike_sigEta,    "spike_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   spike_sigIeta,   "spike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( noSpike_Eta_Time, "noSpike_Eta_Time",  "#eta", " EcalTime (ns) ",  "", 8 ) ;
   h_draw->Draw2D( noSpike_Phi_Time, "noSpike_Phi_Time",  "#phi", " EcalTime (ns) ",  "", 8 ) ;
   h_draw->Draw2D( noSpike_sMaj_sMin, "noSpike_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;
   h_draw->Draw2D( noSpike_sMaj_Time, "noSpike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( noSpike_sMin_Time, "noSpike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw(   noSpike_sigEta,  "noSpike_sigEta",  " Sigma_EtaEta ",   "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   noSpike_sigIeta, "noSpike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( pure_Phi_Time,  "pure_Phi_Time",  "#phi", " EcalTime (ns) ",  "", 8 ) ;
   h_draw->Draw2D( pure_Eta_Time,  "pure_Eta_Time",  "#eta", " EcalTime (ns) ",  "", 8 ) ;
   h_draw->Draw2D( pure_sMaj_sMin, "pure_sMaj_sMin",  "sMaj", " sMin ",  "logZ"  ) ;

   gPad->SetGridx() ;
   leg2->Clear() ;
   leg2->AddEntry( obsTime,  " MET < 60 GeV" , "L" ) ;
   leg2->AddEntry( pure_Time, " MET < 60 + NoHalo NoSpike" , "L" ) ;
   leg2->AddEntry( halo_Time,  " MET < 60 + HaloTagged" , "L" ) ;
   leg2->AddEntry( spike_Time,  " MET < 60 + SpikeTagged" , "L" ) ;
   h_draw->Draw(       obsTime,    "", "Ecal Time (ns)", "", "logY", 0.95, 1 ) ;
   h_draw->DrawAppend( pure_Time,  "", 0.75, 2, 1  ) ;
   h_draw->DrawAppend( halo_Time,  "", 0.55, 4, 1  ) ;
   h_draw->DrawAppend( spike_Time, "TimeForAll", 0.35, 6, 1, leg2  ) ;
   gPad->SetGridx() ;

   gStyle->SetOptStat("");
   //TString IntStrA[7] = { "" } ;
   TLegend* leg4  = new TLegend(.4, .6, .9, .9 );
   TLegend* leg5  = new TLegend(.4, .6, .9, .9 );
   Int_t nu0a, nu0 ;
   Float_t rate0 ;
   char RStr[30], RStr1[30], RStr2[60] ;
   float fEta = 0 ;
   for ( int k=0; k< 7; k++ ) {
       nu0a = sMaj_eta[k]->Integral();
       nu0  = sMaj_eta_csc[k]->Integral(28,100);
       rate0 = (float) nu0 / (float) nu0a ;
       sprintf( RStr,  "%.3f, %.2f<|#eta|<%.2f", rate0, fEta , fEta+0.28 ) ;
       sprintf( RStr1, "%d, %.2f<|#eta|<%.2f", nu0, fEta , fEta+0.28 ) ;
       sprintf( RStr2, "%d / %d = %s", nu0, nu0a , RStr ) ;
       fEta += 0.28 ;
       if ( k < 5 ) leg4->AddEntry( sMaj_eta[k], RStr2 , "L" ) ;
       if ( k < 5 ) leg5->AddEntry( sMaj_eta[k], RStr1 , "L" ) ;
   }

   sMaj_eta[0]->SetTitle("") ;
   h_draw->Draw(       sMaj_eta[0], "", " s_{Major} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( sMaj_eta[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[3], "",   0.9, 6, 1  ) ;
   h_draw->DrawAppend( sMaj_eta[4], "sMaj_EtaSlice", 0.9, 8, 1 , leg4 ) ;

   //h_draw->Draw(       sMaj_eta[5], "", " sMajor ", "", "logY", 0.95, 1 ) ;
   //h_draw->DrawAppend( sMaj_eta[6], "sMaj_EtaSlice_EE", 0.75, 2, 1  ) ;

   sMaj_eta_csc[0]->SetTitle("") ;
   h_draw->Draw(       sMaj_eta_csc[0], "", " s_{Major} ", "", "logY", 0.9, 1 ) ;
   h_draw->DrawAppend( sMaj_eta_csc[1], "",   0.9, 2, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[2], "",   0.9, 4, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[3], "",   0.9, 6, 1  ) ;
   h_draw->DrawAppend( sMaj_eta_csc[4], "sMaj_EtaSlice_CSC", 0.9, 8, 1, leg5 ) ;

   //h_draw->Draw(       sMaj_eta_csc[5], "", " sMajor ", "", "logY", 0.95, 1 ) ;
   //h_draw->DrawAppend( sMaj_eta_csc[6], "sMaj_EtaSlice_EECSC", 0.75, 2, 1  ) ;

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

      hMistag->SetMaximum( 0.03 );
      hMistag->SetMinimum( 0.0 );
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
   //GetQCDComponent( qcdCS_Time, obsTime ) ;
   //GetEstimation( hBg_sg ) ;
   //GetEstimation( hBg_m ) ;
   //GetEstimation( hBg_t ) ;
   //GetEstimation( hBg_mt ) ;

   ABCD( sel_Time, pure_Time ) ;
   ABCD( hBg_mt, hBg_t, hBg_m, hBg_sg ) ;
   GetQCDComponent( qcdCS_Time, sg_Time ) ;
}

void BackgroundStudy::ABCD( TH2D* hA, TH2D* hB, TH2D* hC, TH2D* hD ) {

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
   printf(" B/A = %f  ==> D/C = %f \n", rB/rA , rD/rC ) ;
   printf(" Observe :%f -> predict : %f \n", rD, predict ) ;

}

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

double BackgroundStudy::GetEstimation( TH2D* hCount ) {

   double totalB = 0 ;
   double Bg_exp = 0 ; 
   double residual = 0 ;
   for ( int i=0; i< 5; i++ ) {

       double nB = hCount->GetBinContent(i+1, 1) ;
       double nH = hCount->GetBinContent(i+1, 2) ;
       double nS = hCount->GetBinContent(i+1, 3) ;
       
       vector<double> bgV = GetComponent( i, nB, nH, nS ) ;
       totalB += bgV[0] ;
       totalB += bgV[1] ;
       Bg_exp += nB ;
       residual+= bgV[2] ;
       printf(" eta(%d) : spike:%f , halo:%f , B+= %f  from %f \n ", i, bgV[0], bgV[1], totalB, nB ) ;

   }

   printf(" Background :  %f -> %f \n ", Bg_exp, totalB ) ;

   return residual ;
}

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

// Return the background components in background control region ( MET < 60 GeV )
// Return [0]:spike , [1]:halo , [2]:QCD
// Input : number of event in background control region at t > 2 ns region 
// B12 : total background , h_B12 : halo-tagged events , s_B12 : spike tagged events
vector<double> BackgroundStudy::GetComponent( int eta_i, int B12, int h_B12, int s_B12 ) {

  vector<double> result = GetComponent( eta_i, (double)B12, (double)h_B12, (double)s_B12 ) ;
  return result ;

}

vector<double> BackgroundStudy::GetComponent( int eta_i, double B12, double h_B12, double s_B12 ) {

       // Tagging efficiency 
       double hEff[5] = { 0.89, 0.86, 0.97, 0.90, 0.89 } ; // halo
       double sEff[5] = { 0.94, 0.89, 0.77, 0.68, 0.56 } ; // spike
       
       for ( int i=0; i < 5; i++) {
           if ( haloEff == NULL || spikeEff == NULL )  break ;
           if ( haloEff[i] < 0. || spikeEff[i] < 0. )  continue ;
           hEff[i] = haloEff[i] ;
           sEff[i] = spikeEff[i] ;
           //cout<<" Updated Efficiency "<< endl ;
       }
       
       double h = hEff[ eta_i ] ;  // halo
       double s = sEff[ eta_i ] ;  // spike

       // Mis-tag rate
       double mA[5] = { 0.01349, 0.00629, 0.00154, 0.00088, 0.00038 } ;
       double nA[5] = { 0.02219, 0.02256, 0.01493, 0.00162, 0.00290 } ;

       for ( int i=0; i < 5; i++) {
           if ( haloMis == NULL || spikeMis == NULL )  break ;
           if ( haloMis[i] < 0. || spikeMis[i] < 0. )  continue ;
           mA[i] = haloMis[i] ;
           nA[i] = spikeMis[i] ;
           //cout<<" Updated Mistagging Rate "<< endl ;
       }
       
       double m = mA[ eta_i ] ;   // halo
       double n = nA[ eta_i ] ;   // spike

       // spike content
       double S12 = ( s_B12 - (n*B12) ) / ( s - n ) ;
       S12 = ( S12 < 0. ) ? 0 : S12 ;
       // halo content 
       double H12 = ( h_B12 - (m*B12) ) / ( h - m ) ;
       H12 = ( H12 < 0. ) ? 0 : H12 ;
       // QCD content 
       double Q12 = (double)(B12) - S12 - H12 ;
       Q12 = ( Q12 < 0. ) ? 0 : Q12 ;

       //printf("(%d) B12 %d = (S12: %.2f ) + ( H12: %.2f ) + ( Q12: %.2f )\n ", eta_i, B12, S12, H12, Q12 ) ;

       vector<double> C12 ;
       C12.push_back( S12 ) ;
       C12.push_back( H12 ) ;
       C12.push_back( Q12 ) ;
       return C12 ;
}

