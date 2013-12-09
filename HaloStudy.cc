#include "HaloStudy.h"
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

HaloStudy::HaloStudy( string datacardfile ) {

  Input  = new AnaInput( datacardfile );

  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  createFile = false ;

}


HaloStudy::~HaloStudy(){

  if ( createFile ) {
     theFile->Close() ;
     cout<<" File closed ! "<<endl ;
  }

  delete Input ;
  cout<<" done ! "<<endl ;

}


void HaloStudy::Create( TFile* hFile ) {


  if ( hFile == NULL ) {
     TString Path_fName = hfolder + hfileName + ".root" ; 
     theFile = new TFile( Path_fName, "RECREATE" );
     createFile = true ;
  } else {
     theFile = hFile ;
     createFile = false ;
     cout<<" write to an existing file ! "<< endl ;
  }
  theFile->cd() ;

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
  haloCS_sMaj_sMin = new TH2D( "haloCS_sMaj_sMin", " sMaj vs sMin of photon", 100, 0, 2, 50, 0.1, 0.4 ) ;
  haloCS_cscdPhi   = new TH1D( "haloCS_cscdPhi", " d#Phi ", 65, 0, 3.25 ) ;
  haloCS_cscdPhi1  = new TH1D( "haloCS_cscdPhi1", " d#Phi ", 65, 0, 3.25 ) ;

  halo_Eta[0]  = new TH1D( "halo_Eta0",  "Eta before Halo-tagging",  6, 0., 1.68 ) ;
  halo_Eta[1]  = new TH1D( "halo_Eta1",  "Eta after Halo-tagging",   6, 0., 1.68 ) ;

  char nameStr1[25], nameStr2[25]  ; 
  for ( int i=0; i< 7; i++) {
      sprintf( nameStr1, "sMaj_eta%d", i+1 ) ;
      sprintf( nameStr2, "sMaj_eta_csc%d", i+1 ) ;
      sMaj_eta[i]      =  new TH1D( nameStr1,  "sMajor ", 100, 0., 2.5 ) ;
      sMaj_eta_csc[i]  =  new TH1D( nameStr2,  "sMajor ", 100, 0., 2.5 ) ;
  }

  haloFN_Eta_Time  = new TH2D( "haloFN_Eta_Time", " #eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  haloFN_Phi_Time  = new TH2D( "haloFN_Phi_Time", " #phi vs photon time for halo photon ", 63, -3.15, 3.15,   160, -20, 20 ) ;
  haloFN_Pt_Time   = new TH2D( "haloFN_Pt_Time",  " Pt vs photon time for halo photon ",  50, 0, 500, 160, -20, 20 ) ;
  haloFN_MET_Time  = new TH2D( "haloFN_MET_Time", " MET vs photon time for halo photon ", 50, 0, 500, 160, -20, 20 ) ;
  haloFN_sMaj_sMin = new TH2D( "haloFN_sMaj_sMin","sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  haloFN_cscdPhi   = new TH1D( "haloFN_cscdPhi",  " d#Phi ", 65, 0, 3.25 ) ;

  halo_Eta_Time  = new TH2D( "halo_Eta_Time", " eta vs photon time for halo photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  halo_Phi_Time  = new TH2D( "halo_Phi_Time", " phi vs photon time for halo photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  halo_Pt_Time   = new TH2D( "halo_Pt_Time",  " Pt vs photon time for halo photon ",  50, 0, 500, 160, -20, 20 ) ;
  halo_MET_Time  = new TH2D( "halo_MET_Time", " MET vs photon time for halo photon ", 50, 0, 500, 160, -20, 20 ) ;
  halo_MET_Time_0J  = new TH2D( "halo_MET_Time_0J", "MET vs photon time for halo photon", 50, 0, 500, 160, -20, 20 ) ;
  halo_MET_Time_1J  = new TH2D( "halo_MET_Time_1J", "MET vs photon time for halo photon", 50, 0, 500, 160, -20, 20 ) ;
  halo_MET_Time_2J  = new TH2D( "halo_MET_Time_2J", "MET vs photon time for halo photon", 50, 0, 500, 160, -20, 20 ) ;
  halo_sMin_Time = new TH2D( "halo_sMin_Time",  "sMin vs Ecal time for halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  halo_sMaj_Time = new TH2D( "halo_sMaj_Time",  "sMaj vs Ecal time for halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  halo_sMaj_sMin = new TH2D( "halo_sMaj_sMin", "sMajor vs sMinor for halo photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  halo_sigIeta   = new TH1D( "halo_sigIeta", " Sigma Ieta Ieta for Halo Photon ", 100,  0., 0.1 ) ;
  halo_Time      = new TH1D( "halo_Time",   "Photon time w/ halo ", 160,  -14.5, 25.5 ) ;
  halo_photIso_Time = new TH2D( "halo_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  halo_nHadIso_Time = new TH2D( "halo_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  halo_sMaj_sigIeta = new TH2D( "halo_sMaj_sigIeta", " sMaj vs #sigma_{i#eta}", 100, 0, 2, 80, 0, 0.08 ) ;
  halo_sMin_sigIeta = new TH2D( "halo_sMin_sigIeta",  "sMin vs #sigma_{i#eta}", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  halo_T_dPhi_gMET_0J = new TH2D("halo_T_dPhi_gMET_0J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_T_dPhi_gMET_1J = new TH2D("halo_T_dPhi_gMET_1J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_T_dPhi_gMET_2J = new TH2D("halo_T_dPhi_gMET_2J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  halo_eta_rho        = new TH2D( "halo_eta_rho", " #eta vs rho", 51, -2.5, 2.5, 100, 100, 300. ) ;
  halo_eta_sMaj       = new TH2D( "halo_eta_sMaj", " #eta vs sMajor", 51, -2.5, 2.5, 100, 0, 2 ) ;
  halo_ecalT_rho      = new TH2D( "halo_ecalT_rho", " Ecal time vs rho", 160, -20, 20, 100, 100, 500. ) ;
  halo_nXtl     = new TH1D( "halo_nXtl", " N of crystals ", 50, 0, 50 ) ;
  halo_tChi2   = new TH1D( "halo_tChi2", " chi2 of time ", 100, 0, 10  ) ;
  noHalo_tChi2   = new TH1D( "noHalo_tChi2", " chi2 of time ", 100, 0, 10  ) ;

  noHalo_sMaj_Time = new TH2D( "noHalo_sMaj_Time",  "sMaj vs Ecal time for non halo Photon", 100, 0, 2, 160, -20, 20 ) ;
  noHalo_sMin_Time = new TH2D( "noHalo_sMin_Time",  "sMin vs. Ecal time for non halo photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  noHalo_Time    = new TH1D( "noHalo_Time", "Photon time w/o halo ", 160,  -14.5, 25.5 ) ;

  noHalo_nXtl_side = new TH1D( "noHalo_nXtl_side", "N of xtals of non halo photon w/ |t| > 3ns",     50,  0, 50 );
  noHalo_nXtl_center = new TH1D( "noHalo_nXtl_center", "N of xtals of non halo photon w/ |t| < 3ns", 50,  0, 50 );

}

void HaloStudy::Open() {

     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<" for halo-study"<<endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     //hFile->cd() ;
     cout<<" file opened ! "<<endl ;

     haloTest_sMaj_sMin  = (TH2D*) theFile->Get("haloTest_sMaj_sMin");
     haloTest_cscdPhi    = (TH1D*) theFile->Get("haloTest_cscdPhi");

     haloCS_sMaj_sMin = (TH2D*) theFile->Get("haloCS_sMaj_sMin");
     haloCS_sMaj_Eta  = (TH2D*) theFile->Get("haloCS_sMaj_Eta");
     haloCS_sMaj_Phi  = (TH2D*) theFile->Get("haloCS_sMaj_Phi");
     haloCS_Eta_Time  = (TH2D*) theFile->Get("haloCS_Eta_Time");
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

     halo_Eta[0]  = (TH1D*) theFile->Get("halo_Eta0");
     halo_Eta[1]  = (TH1D*) theFile->Get("halo_Eta1");

     char nameStr1[25], nameStr2[25] ; 
     for ( int i=0; i< 7; i++) {
         sprintf( nameStr1, "sMaj_eta%d", i+1 ) ;
         sprintf( nameStr2, "sMaj_eta_csc%d", i+1 ) ;
         sMaj_eta[i]      = (TH1D*) theFile->Get( nameStr1 );
         sMaj_eta_csc[i]  = (TH1D*) theFile->Get( nameStr2 );
     }

     haloFN_Eta_Time = (TH2D*) theFile->Get("haloFN_Eta_Time");
     haloFN_Phi_Time = (TH2D*) theFile->Get("haloFN_Phi_Time");
     haloFN_Pt_Time  = (TH2D*) theFile->Get("haloFN_Pt_Time");
     haloFN_MET_Time = (TH2D*) theFile->Get("haloFN_MET_Time");
     haloFN_sMaj_sMin= (TH2D*) theFile->Get("haloFN_sMaj_sMin");
     haloFN_cscdPhi  = (TH1D*) theFile->Get("haloFN_cscdPhi");

     halo_MET_Time_0J = (TH2D*) theFile->Get("halo_MET_Time_0J");
     halo_MET_Time_1J = (TH2D*) theFile->Get("halo_MET_Time_1J");
     halo_MET_Time_2J = (TH2D*) theFile->Get("halo_MET_Time_2J");

     halo_Eta_Time = (TH2D*) theFile->Get("halo_Eta_Time");
     halo_Phi_Time = (TH2D*) theFile->Get("halo_Phi_Time");
     halo_Pt_Time  = (TH2D*) theFile->Get("halo_Pt_Time");
     halo_MET_Time = (TH2D*) theFile->Get("halo_MET_Time");
     halo_sMin_Time = (TH2D*) theFile->Get("halo_sMin_Time");
     halo_sMaj_Time = (TH2D*) theFile->Get("halo_sMaj_Time");
     halo_photIso_Time = (TH2D*) theFile->Get("halo_photIso_Time");
     halo_nHadIso_Time = (TH2D*) theFile->Get("halo_nHadtIso_Time");
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
     halo_nXtl            = (TH1D*) theFile->Get("halo_nXtl");

     noHalo_Time = (TH1D*) theFile->Get("noHalo_Time");
     noHalo_sMaj_Time = (TH2D*) theFile->Get("noHalo_sMaj_Time");
     noHalo_sMin_Time = (TH2D*) theFile->Get("noHalo_sMin_Time");
     noHalo_nXtl_side = (TH1D*) theFile->Get("noHalo_nXtl_side");
     noHalo_nXtl_center = (TH1D*) theFile->Get("noHalo_nXtl_center");

     cout<<" link all histograms  "<<endl ;
}

void HaloStudy::Write( ) {

  theFile->cd() ;

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

  halo_Eta[0]->Write();
  halo_Eta[1]->Write();

  for ( int i=0; i< 7; i++ ) {
      sMaj_eta[i]->Write() ;
      sMaj_eta_csc[i]->Write() ;
  }

  haloFN_Eta_Time->Write() ;
  haloFN_Phi_Time->Write() ;
  haloFN_Pt_Time->Write() ;
  haloFN_MET_Time->Write() ;
  haloFN_sMaj_sMin->Write() ;
  haloFN_cscdPhi->Write() ;

  halo_MET_Time_0J->Write() ;
  halo_MET_Time_1J->Write() ;
  halo_MET_Time_2J->Write() ;

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
  halo_nHadIso_Time->Write() ;
  halo_sMaj_sigIeta->Write() ;
  halo_sMin_sigIeta->Write() ;
  halo_T_dPhi_gMET_1J->Write() ;
  halo_T_dPhi_gMET_2J->Write() ;
  halo_T_dPhi_gMET_0J->Write() ;
  halo_eta_rho->Write() ;
  halo_eta_sMaj->Write() ;
  halo_ecalT_rho->Write() ;
  halo_nXtl->Write() ;
  halo_tChi2->Write() ;

  noHalo_Time->Write() ;
  noHalo_sMaj_Time->Write() ;
  noHalo_sMin_Time->Write() ;
  noHalo_nXtl_side->Write() ;
  noHalo_nXtl_center->Write() ;
  noHalo_tChi2->Write() ;

  cout<<" Output historams written ! "<< endl ;
}

// analysis template
void HaloStudy::Run( vector<objID>& selectPho, vector<objID>& selectJets, Rtuple& rt, double weight ) { 

       TLorentzVector met( rt.metPx, rt.metPy, 0, rt.metE )  ;
       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
           int k = selectPho[kk].first ;
	   TLorentzVector gP4_ = selectPho[kk].second ; 
	   double dPhi_gMET    = fabs( gP4_.DeltaPhi( met ) );
	   double cscdPhi_     = ( rt.cscdPhi[k] > 9. ) ? 3.24 : rt.cscdPhi[k] ;
           double nHIso = max( rt.nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
           double phIso = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;          
	   bool haloTag  = HaloTag( rt, k ) ;


	   // Test Halo Stuff - cross -check
	   if ( fabs(gP4_.Eta()) < 1.47 ) {
              if ( rt.cscdPhi[k] < 0.05 ) haloTest_sMaj_sMin->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight) ;
    	      if ( rt.sMajPho[k] > 0.8 && rt.sMajPho[k] < 1.65 && rt.sMinPho[k] < 0.2 ) haloTest_cscdPhi->Fill( cscdPhi_ , weight ) ;
           }

           // **********************************************
           //   Current Halo-Control Sample - for efficiency and fake rate study
	   // **********************************************
           bool haloCtrl1 = ( fabs( gP4_.Phi() ) < 0.2 || fabs( fabs(gP4_.Phi()) - 3.1416 ) < 0.2  )  ;
           bool haloCtrl2 = ( selectJets.size() < 1 && rt.seedTime[k]  < -2. && dPhi_gMET > 2.6 ) ;
           bool haloCtrl3 = ( fabs( gP4_.Eta() ) < 1.4 && rt.nXtals[k] > 7 ) ;

	   if ( haloCtrl1 ) {
              if ( selectJets.size() < 2 && rt.seedTime[k] > 3 ) {
                 if ( fabs(gP4_.Eta())  < 0.37                            ) haloCD_Pt_eta[0]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloCD_Pt_eta[1]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloCD_Pt_eta[2]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloCD_Pt_eta[3]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta())  < 0.37                            ) haloCD_MET_eta[0]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloCD_MET_eta[1]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloCD_MET_eta[2]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloCD_MET_eta[3]->Fill( met.E() , weight);
              }
              if ( selectJets.size() < 2 && rt.seedTime[k] < -3 ) {
                 if ( fabs(gP4_.Eta())  < 0.37                            ) haloAB_Pt_eta[0]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloAB_Pt_eta[1]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloAB_Pt_eta[2]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloAB_Pt_eta[3]->Fill( gP4_.Pt() , weight);
		 if ( fabs(gP4_.Eta())  < 0.37                            ) haloAB_MET_eta[0]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.37 && fabs(gP4_.Eta()) < 0.74 ) haloAB_MET_eta[1]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 0.74 && fabs(gP4_.Eta()) < 1.11 ) haloAB_MET_eta[2]->Fill( met.E() , weight);
		 if ( fabs(gP4_.Eta()) >= 1.11 && fabs(gP4_.Eta()) < 1.48 ) haloAB_MET_eta[3]->Fill( met.E() , weight);
              }
           }

           if ( haloCtrl1 && haloCtrl2 && haloCtrl3 ) {

              haloCS_sMaj_sMin->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight ) ;
	      haloCS_sMaj_Eta->Fill( rt.sMajPho[k] , gP4_.Eta() , weight ) ;
	      haloCS_sMaj_Phi->Fill( rt.sMajPho[k] , gP4_.Phi() , weight );
	      haloCS_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
	      haloCS_cscdPhi->Fill( cscdPhi_ , weight ) ;
	      if ( rt.sMajPho[k] > 0.8 && rt.sMajPho[k] < 1.65 && rt.sMinPho[k] < 0.2 ) haloCS_cscdPhi1->Fill( cscdPhi_ , weight ) ;
	      // Count efficiency in different eta slice 
	      double haloEta = ( fabs(gP4_.Eta()) > 1.67 ) ? 1.67 : fabs(gP4_.Eta()) ;
	      halo_Eta[0]->Fill( haloEta, weight ) ;
	      if ( haloTag )   halo_Eta[1]->Fill( haloEta, weight ) ;

	      // Check on sMajor for halo in different eta
	      if ( fabs(gP4_.Eta()) < 0.28 )                            sMaj_eta[0]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) sMaj_eta[1]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) sMaj_eta[2]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) sMaj_eta[3]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) sMaj_eta[4]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) sMaj_eta[5]->Fill( rt.sMajPho[k] , weight ) ;
	      if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) sMaj_eta[6]->Fill( rt.sMajPho[k] , weight ) ;

	      if ( rt.cscdPhi[k] < 0.05 ) {
                 if ( fabs(gP4_.Eta()) < 0.28 )                            sMaj_eta_csc[0]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) sMaj_eta_csc[1]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) sMaj_eta_csc[2]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) sMaj_eta_csc[3]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) sMaj_eta_csc[4]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) sMaj_eta_csc[5]->Fill( rt.sMajPho[k] , weight ) ;
		 if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) sMaj_eta_csc[6]->Fill( rt.sMajPho[k] , weight ) ;
              }
           }

           // **************************
           //   Information after applying halo tagging
           // **************************
	   if ( selectPho[0].second.Pt() > 80. ) {

              if ( haloTag ) {
                 halo_Eta_Time->Fill(  gP4_.Eta() ,   rt.seedTime[k] , weight );
		 halo_Phi_Time->Fill(  gP4_.Phi() ,   rt.seedTime[k] , weight );
		 halo_sMin_Time->Fill( rt.sMinPho[k], rt.seedTime[k] , weight ) ;
		 halo_sMaj_Time->Fill( rt.sMajPho[k], rt.seedTime[k] , weight ) ;
		 halo_Time->Fill(  rt.seedTime[k] , weight ) ;
		 halo_photIso_Time->Fill( phIso, rt.seedTime[k] , weight ) ;
		 halo_nHadIso_Time->Fill( nHIso, rt.seedTime[k] , weight ) ;
		 halo_ecalT_rho->Fill( rt.seedTime[k], rt.cscRho[k], weight  ) ;
		 halo_tChi2->Fill( rt.timeChi2[k] ,  weight );
		 // Only check the out-of-time region
	         if ( fabs( rt.seedTime[k]) > 1.5 ) {
		       halo_sigIeta->Fill( rt.sigmaIeta[k] , weight ) ;
		       halo_sMaj_sigIeta->Fill( rt.sMajPho[k], rt.sigmaIeta[k] , weight ) ;
		       halo_sMin_sigIeta->Fill( rt.sMinPho[k], rt.sigmaIeta[k] , weight ) ;
		       halo_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k] , weight ) ;
                       halo_eta_rho->Fill( gP4_.Eta(),  rt.cscRho[k], weight  ) ;
		       halo_eta_sMaj->Fill( gP4_.Eta(), rt.sMajPho[k], weight ) ;
		       halo_Pt_Time->Fill( gP4_.Pt(),   rt.seedTime[k] , weight );
		       halo_MET_Time->Fill( met.E(),    rt.seedTime[k] , weight );
		       halo_nXtl->Fill( rt.nXtals[k] , weight );
                 }
		 if ( selectJets.size() == 0 ) halo_T_dPhi_gMET_0J->Fill( rt.seedTime[k] , dPhi_gMET, weight ) ;
		 if ( selectJets.size() == 1 ) halo_T_dPhi_gMET_1J->Fill( rt.seedTime[k] , dPhi_gMET, weight ) ;
		 if ( selectJets.size() >= 2 ) halo_T_dPhi_gMET_2J->Fill( rt.seedTime[k] , dPhi_gMET, weight ) ;
               
		 if ( selectJets.size() == 0 ) halo_MET_Time_0J->Fill( met.E(),  rt.seedTime[k] , weight );
		 if ( selectJets.size() == 1 ) halo_MET_Time_1J->Fill( met.E(),  rt.seedTime[k] , weight );
		 if ( selectJets.size() >= 2 ) halo_MET_Time_2J->Fill( met.E(),  rt.seedTime[k] , weight );

              } else {
		    noHalo_sMaj_Time->Fill( rt.sMajPho[k], rt.seedTime[k] , weight ) ;
		    noHalo_sMin_Time->Fill( rt.sMinPho[k], rt.seedTime[k] , weight ) ;
		    noHalo_Time->Fill( rt.seedTime[k] , weight ) ;
		    noHalo_tChi2->Fill( rt.timeChi2[k] ,  weight );

		    if ( fabs( rt.seedTime[k] ) > 3. ) {
                       noHalo_nXtl_side->Fill( rt.nXtals[k] , weight ) ;
                    } else  {
                       noHalo_nXtl_center->Fill( rt.nXtals[k] , weight ) ;
                    }
              }
                 
              // Another way to define halo-control sample
              if ( fabs( gP4_.Eta() ) < 1.3 && rt.seedTime[k] < -1.) {
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
		 bool fromL = ( rt.seedTime[k] > Cut_LD && rt.seedTime[k] < Cut_LU ) ;
		 bool fromR = ( rt.seedTime[k] > Cut_RD && rt.seedTime[k] < Cut_RU ) ;
		 if ( fromL || fromR ) {
                    haloFN_Eta_Time->Fill( gP4_.Eta(), rt.seedTime[k] , weight ) ;
		    haloFN_Phi_Time->Fill( gP4_.Phi(), rt.seedTime[k] , weight ) ;
		    haloFN_Pt_Time->Fill( gP4_.Pt(), rt.seedTime[k] , weight ) ;
		    haloFN_MET_Time->Fill( met.E(), rt.seedTime[k] , weight ) ;
		    haloFN_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k],  weight ) ;
		    haloFN_cscdPhi->Fill( cscdPhi_ ,  weight ) ;
                 }
              }

           }


       } // end of photon looping 

}  

void HaloStudy::DrawHistograms( hDraw* h_draw ) {

   bool createDrawer = false ;
   if ( h_draw == NULL ) {
      h_draw = new hDraw( hfolder, plotType ) ;
      createDrawer = true ;
      cout<<" create drawing class " << endl ;
   }

   hfolder += "halo/" ;
   gSystem->mkdir( hfolder.c_str() );
   h_draw->SetPath( hfolder ) ;

   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);
   h_draw->SetPlotStyle(false) ; // Turn off the stats box

   h_draw->Draw(   haloTest_cscdPhi,     "haloTest_cscdPhi", "#Delta#Phi( cscSeg, #gamma) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( haloTest_sMaj_sMin,   "haloTest_sMaj_sMin",  "sMaj", "sMin ",  "logZ", 8 ) ;

   h_draw->Draw2D( haloFN_Eta_Time,  "haloFN_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_Phi_Time,  "haloFN_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_Pt_Time,   "haloFN_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_MET_Time,  "haloFN_MET_Time", "MET",  "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( haloFN_sMaj_sMin, "haloFN_sMaj_sMin", "s_{Major}", "s_{Minor}",  "", 8 ) ;
   h_draw->Draw(   haloFN_cscdPhi,   "haloFN_cscdPhi",  " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;

   h_draw->SetPlotStyle(true) ; // Turn off the stats box
   h_draw->Draw2D( haloCS_sMaj_sMin, "haloCS_sMaj_sMin", "sMaj", "sMin",  "", 8  ) ;
   h_draw->Draw2D( haloCS_sMaj_Eta,  "haloCS_sMaj_Eta",  "sMaj", " #eta",  "", 8  ) ;
   h_draw->Draw2D( haloCS_sMaj_Phi,  "haloCS_sMaj_Phi",  "sMaj", " #phi",  "", 8  ) ;
   h_draw->Draw2D( haloCS_Eta_Time,  "haloCS_Eta_Time",  "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw(   haloCS_cscdPhi,   "haloCS_cscdPhi",  " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   haloCS_cscdPhi1,  "haloCS_cscdPhi1", " #Delta#phiE( csc, photon) ", "", "logY", 0.95, 1 ) ;

   h_draw->Draw2D( halo_sMaj_Time, "halo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMin_Time, "halo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMaj_sMin, "halo_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( halo_Eta_Time,  "halo_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Phi_Time,  "halo_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_Pt_Time,   "halo_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_MET_Time,  "halo_MET_Time", "MET",  "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( halo_photIso_Time,"halo_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( halo_nHadIso_Time,"halo_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw(   halo_sigIeta,   "halo_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( halo_sMaj_sigIeta,"halo_sMaj_sigIeta",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( halo_sMin_sigIeta,"halo_sMin_sigIeta",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_1J, "halo_T_dPhi_gMET_1J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_2J, "halo_T_dPhi_gMET_2J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_T_dPhi_gMET_0J, "halo_T_dPhi_gMET_0J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( halo_eta_rho,     "halo_eta_rho",    "#eta ", "#rho", "logZ", 8 ) ;
   h_draw->Draw2D( halo_eta_sMaj,    "halo_eta_sMaj",    "#eta ", "s_{Major}", "logZ", 8 ) ;
   h_draw->Draw2D( halo_ecalT_rho,   "halo_ecalT_rho",    "Ecal time ", "#rho", "logZ", 8 ) ;

   h_draw->Draw2D( noHalo_sMaj_Time, "noHalo_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( noHalo_sMin_Time, "noHalo_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw(   noHalo_nXtl_side, "noHalo_nXtl_side",  " N of crystals ", "",  "", 0.95, 1 ) ;
   h_draw->Draw(   noHalo_nXtl_center, "noHalo_nXtl_center",  " N of crystals ", "",  "", 0.95, 1 ) ;

   gPad->SetGridx() ;
   gStyle->SetOptStat("");

   // sMaj_eta[0]->SetTitle("") ;
   gStyle->SetOptStat("");
   for (int i=0; i<5; i++) { 
       sMaj_eta[i]->SetLabelSize(0.1, "X") ;
       sMaj_eta[i]->SetLabelSize(0.1, "Y") ;
   }
   h_draw->CreateNxM( "sMaj_EtaSlice", 1,5 );
   h_draw->DrawNxM( 1, sMaj_eta[0] , "",          "", "logY", 1, false );
   h_draw->DrawNxM( 2, sMaj_eta[1] , "",          "", "logY", 2, false );
   h_draw->DrawNxM( 3, sMaj_eta[2] , "",          "", "logY", 4, false );
   h_draw->DrawNxM( 4, sMaj_eta[3] , "",          "", "logY", 6, false ) ;
   h_draw->DrawNxM( 5, sMaj_eta[4] , "s_{Major}", "", "logY", 8, true ) ;

   h_draw->CreateNxM( "sMaj_EtaSlice_CSC", 1,5 );
   for (int i=0; i<5; i++) { 
       sMaj_eta_csc[i]->SetLabelSize(0.1, "X") ;
       sMaj_eta_csc[i]->SetLabelSize(0.1, "Y") ;
   }
   h_draw->DrawNxM( 1, sMaj_eta_csc[0] , "",          "", "logY", 1, false );
   h_draw->DrawNxM( 2, sMaj_eta_csc[1] , "",          "", "logY", 2, false );
   h_draw->DrawNxM( 3, sMaj_eta_csc[2] , "",          "", "logY", 4, false );
   h_draw->DrawNxM( 4, sMaj_eta_csc[3] , "",          "", "logY", 6, false ) ;
   h_draw->DrawNxM( 5, sMaj_eta_csc[4] , "s_{Major}", "", "logY", 8, true ) ;

   
   TLegend* leg4  = new TLegend(.52, .72, .99, .99 );
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

   gStyle->SetOptStat("");
   TCanvas* c_1 = new TCanvas("c_1","", 800, 700);
   c_1->SetFillColor(10);
   c_1->SetLeftMargin(0.16);
   c_1->SetRightMargin(0.08);
   c_1->SetTopMargin(0.1);
   c_1->SetBottomMargin(0.12);
   c_1->SetLogz() ;

   halo_Eta_Time->Draw("COLZ") ;
   c_1->Update() ;
   TF1 *f2 = new TF1("f2", HaloStudy::HaloFunction ,-1.4,1.4, 3 );
   f2->SetParameter(0,  1.4) ;
   f2->SetParameter(1,  1.5) ;
   f2->SetParameter(2,  -1.5) ;
   f2->Draw("sames") ;
   c_1->Update();

   TF1 *f3 = new TF1("f3", HaloStudy::HaloFunction ,-1.4,1.4, 3 );
   f3->SetParameter(0, 1.4) ;
   f3->SetParameter(1, 1.3)  ;
   f3->SetParameter(2, -1)  ;
   f3->Draw("sames") ;
   c_1->Update();

   TString plotname = hfolder + "HaloFunction."+plotType ;
   c_1->Print( plotname ) ;

   TCanvas* c_0 = new TCanvas("c_0","", 800, 700);
   c_0->SetFillColor(10);
   c_0->SetFillColor(10);
   c_0->SetLeftMargin(0.16);
   c_0->SetRightMargin(0.08);
   c_0->SetTopMargin(0.1);
   c_0->SetBottomMargin(0.12);

   if ( isData == 1 ) {

      cout<<" ======= Halo Tagging Efficiency ====== "<<endl ;
      c_0->Clear() ;
      TGraphAsymmErrors* halo_Eff = new TGraphAsymmErrors();
      halo_Eff->Divide( halo_Eta[1], halo_Eta[0] );
      double allHaloEff = halo_Eta[1]->Integral() /  halo_Eta[0]->Integral() ;
      printf(" All  = %.5f \n",  allHaloEff ) ;

      Double_t* halo_eA  = halo_Eff->GetY() ;
      haloEff.clear() ;
      for (int i=0; i< 5 ; i++ ) {
          if ( halo_eA == NULL ) break ;
          printf(" (%d)  = %.5f \n", i, halo_eA[i] ) ;
          haloEff.push_back( halo_eA[i] ) ;
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
   }

   ABCD_Report() ;

   if ( createDrawer ) delete h_draw ;

}

bool HaloStudy::HaloTag( Rtuple& rt, int k ) {

     TLorentzVector gP4_ = TLorentzVector( rt.phoPx[k], rt.phoPy[k], rt.phoPz[k], rt.phoE[k] ) ;
     bool haloTag  = ( rt.cscdPhi[k] < 0.05 ) ? true : false  ;
     if ( rt.sMajPho[k] > 0.8 && rt.sMajPho[k] < 1.65 && rt.sMinPho[k] < 0.2 && fabs( gP4_.Eta() ) < 1.47 ) haloTag = true;
     return haloTag ;
}

// eta = - ln ( tan theta/2 ) , theta = 2 atan( e ^ -eta )
// p0 : the falling rate, p1 : t scale,  p2: t shift
Double_t HaloStudy::HaloFunction( Double_t* eta, Double_t* par  ) {

     double c  = 30. ; // speed of light : 30 cm/ns
     double eta_func =  par[0]*eta[0] ;
     double t0 =  129 / (-2*c) ;
     Double_t T  = t0 * exp( eta_func )*par[1]  + par[2]  ; 

     return T ;
}

void HaloStudy::ABCD_Report( ) {

    // MET: ( 50, 0, 500)  Time: ( 160, -20, 20 )
    double nA0 = halo_MET_Time_0J->Integral( 1, 6, 41,  67 );
    double nB0 = halo_MET_Time_0J->Integral( 7,50, 41,  67 );
    double nC0 = halo_MET_Time_0J->Integral( 1, 6, 93, 120 );
    double nD0 = halo_MET_Time_0J->Integral( 7,50, 93, 120 );

    double nA1 = halo_MET_Time_1J->Integral( 1, 6, 41,  67 );
    double nB1 = halo_MET_Time_1J->Integral( 7,50, 41,  67 );
    double nC1 = halo_MET_Time_1J->Integral( 1, 6, 93, 120 );
    double nD1 = halo_MET_Time_1J->Integral( 7,50, 93, 120 );

    double nA2 = halo_MET_Time_2J->Integral( 1, 6, 41,  67 );
    double nB2 = halo_MET_Time_2J->Integral( 7,50, 41,  67 );
    double nC2 = halo_MET_Time_2J->Integral( 1, 6, 93, 120 );
    double nD2 = halo_MET_Time_2J->Integral( 7,50, 93, 120 );

    printf(" ============ Halo 0Jet ============\n") ;
    double rDC0 = ( nC0 < 0.0001 ) ? -1 : nD0/nC0 ;
    double rBA0 = ( nA0 < 0.0001 ) ? -1 : nB0/nA0 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.1f \n", nC0, nD0 , rDC0 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.1f \n", nA0, nB0 , rBA0 ) ;

    printf(" ============ Halo 1Jet ============\n") ;
    double rDC1 = ( nC1 < 0.0001 ) ? -1 : nD1/nC1 ;
    double rBA1 = ( nA1 < 0.0001 ) ? -1 : nB1/nA1 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.1f \n", nC1, nD1, rDC1 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.1f \n", nA1, nB1, rBA1 ) ;

    printf(" ============ Halo >= 2Jet ============\n") ;
    double rDC2 = ( nC2 < 0.0001 ) ? -1 : nD2/nC2 ;
    double rBA2 = ( nA2 < 0.0001 ) ? -1 : nB2/nA2 ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.1f \n", nC2, nD2, rDC2 ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.1f \n", nA2, nB2, rBA2 ) ;

    printf(" ============ Halo >= 1Jet ============\n") ;
    double rDC = ( (nC2 + nC1) < 0.0001 ) ? -1 : (nD2+nD1)/(nC2+nC1) ;
    double rBA = ( (nA2 + nA1) < 0.0001 ) ? -1 : (nB2+nB1)/(nA2+nA1) ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.1f \n", nC2+nC1, nD2+nD1, rDC ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.1f \n", nA2+nA1, nB2+nB1, rBA ) ;

    printf(" =====================================\n") ;

}

