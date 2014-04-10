#include "CosmicStudy.h"
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

CosmicStudy::CosmicStudy( string datacardfile ) {

  Input  = new AnaInput( datacardfile );

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  createFile = false ;
 
}


CosmicStudy::~CosmicStudy(){

  if ( createFile ) {
     theFile->Close() ;
     cout<<" File closed ! "<<endl ;
  }

  delete Input ;
  cout<<" done ! "<<endl ;

}


void CosmicStudy::Create( TFile* hFile ) {


     if ( hFile == NULL ) {
        TString Path_fName = hfolder + hfileName + ".root" ;
	theFile = new TFile( Path_fName, "RECREATE" );
	createFile = true ;
     } else {
        theFile = hFile ;
	createFile = false ;
     }
     theFile->cd() ;

     cosmic_Eta_Time  = new TH2D( "cosmic_Eta_Time", " eta vs photon time for cosmic photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
     cosmic_Phi_Time  = new TH2D( "cosmic_Phi_Time", " phi vs photon time for cosmic photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
     cosmic_Pt_Time   = new TH2D( "cosmic_Pt_Time",  " Pt vs photon time for cosmic photon ",  50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET_Time  = new TH2D( "cosmic_MET_Time", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET_Time_0J = new TH2D( "cosmic_MET_Time_0J", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET_Time_1J = new TH2D( "cosmic_MET_Time_1J", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET_Time_2J = new TH2D( "cosmic_MET_Time_2J", " MET vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET2_Time_0J = new TH2D("cosmic_MET2_Time_0J", "MET2 vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET2_Time_1J = new TH2D("cosmic_MET2_Time_1J", "MET2 vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_MET2_Time_2J = new TH2D("cosmic_MET2_Time_2J", "MET2 vs photon time for cosmic photon ", 50, 0, 500, 160, -20, 20 ) ;
     cosmic_sMin_Time = new TH2D( "cosmic_sMin_Time",  "sMin vs Ecal time for cosmic photon", 100, 0., 0.5 , 160, -20, 20  ) ;
     cosmic_sMaj_Time = new TH2D( "cosmic_sMaj_Time",  "sMaj vs Ecal time for cosmic Photon", 100, 0, 2, 160, -20, 20 ) ;
     cosmic_sMaj_sMin = new TH2D( "cosmic_sMaj_sMin", "sMajor vs sMinor for cosmic photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
     cosmic_Time      = new TH1D( "cosmic_Time",   "Photon time from cosmic ", 160,  -14.5, 25.5 ) ;
     cosmic_photIso_Time = new TH2D("cosmic_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
     cosmic_nXtl      = new TH1D( "cosmic_nXtl", " N crystals vs #eta", 50, 0, 50 ) ;
     cosmic_tChi2 = new TH1D( "cosmic_tChi2", " chi2 of time ", 100, 0, 10  ) ;
     cosmic_seedE_photE = new TH2D("cosmic_seedE_photE", " seed E vs photon E",  100, 0, 500., 100, 0, 500. );

}

void CosmicStudy::Open( TFile* hFile) {

     if ( hFile == NULL ) {
        TString Path_fName = hfolder + hfileName + ".root" ;
        theFile = new TFile( Path_fName, "UPDATE" );
        createFile = true ;
        cout<<" root file opened ! "<<endl ;
     } else {
        theFile = hFile ;
        createFile = false ;
     }

     /*
     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<" for comsic-study " << endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     */

     cosmic_tChi2 = (TH1D*) theFile->Get("cosmic_tChi2");
     cosmic_Eta_Time = (TH2D*) theFile->Get("cosmic_Eta_Time");
     cosmic_Phi_Time = (TH2D*) theFile->Get("cosmic_Phi_Time");
     cosmic_Pt_Time  = (TH2D*) theFile->Get("cosmic_Pt_Time");
     cosmic_MET_Time = (TH2D*) theFile->Get("cosmic_MET_Time");
     cosmic_MET_Time_0J = (TH2D*) theFile->Get("cosmic_MET_Time_0J");
     cosmic_MET_Time_1J = (TH2D*) theFile->Get("cosmic_MET_Time_1J");
     cosmic_MET_Time_2J = (TH2D*) theFile->Get("cosmic_MET_Time_2J");
     cosmic_MET2_Time_0J = (TH2D*) theFile->Get("cosmic_MET2_Time_0J");
     cosmic_MET2_Time_1J = (TH2D*) theFile->Get("cosmic_MET2_Time_1J");
     cosmic_MET2_Time_2J = (TH2D*) theFile->Get("cosmic_MET2_Time_2J");
     cosmic_sMin_Time = (TH2D*) theFile->Get("cosmic_sMin_Time");
     cosmic_sMaj_Time = (TH2D*) theFile->Get("cosmic_sMaj_Time");
     cosmic_photIso_Time = (TH2D*) theFile->Get("cosmic_photIso_Time");
     cosmic_sMaj_sMin    = (TH2D*) theFile->Get("cosmic_sMaj_sMin");
     cosmic_Time    = (TH1D*) theFile->Get("cosmic_Time");
     cosmic_nXtl    = (TH1D*) theFile->Get("cosmic_nXtl");
     cosmic_seedE_photE = (TH2D*) theFile->Get("cosmic_seedE_photE");

     cout<<" link all histograms  "<<endl ;
}

void CosmicStudy::Write() {

     cosmic_Eta_Time->Write() ;
     cosmic_Phi_Time->Write() ;
     cosmic_Pt_Time->Write() ;
     cosmic_MET_Time->Write() ;
     cosmic_MET_Time_0J->Write() ;
     cosmic_MET_Time_1J->Write() ;
     cosmic_MET_Time_2J->Write() ;
     cosmic_MET2_Time_0J->Write() ;
     cosmic_MET2_Time_1J->Write() ;
     cosmic_MET2_Time_2J->Write() ;
     cosmic_sMin_Time->Write() ;
     cosmic_sMaj_Time->Write() ;
     cosmic_photIso_Time->Write() ;
     cosmic_sMaj_sMin->Write();
     cosmic_seedE_photE->Write();
     cosmic_Time->Write() ;
     cosmic_nXtl->Write() ;
     cosmic_tChi2->Write() ;
     cout<<" Output historams written ! "<< endl ;

}

// analysis template
void CosmicStudy::Run(  vector<objID>& selectPho, vector<objID>& selectJets, Rtuple& rt, double weight ) { 

       TLorentzVector met( rt.metPx, rt.metPy, 0, rt.metE)  ;

       for ( size_t kk =0; kk < selectPho.size() ; kk++) {
           int k = selectPho[kk].first ;
	   TLorentzVector gP4_ = selectPho[kk].second ; 
   	   double phIso = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
           bool cosmicTag = CosmicTag( rt, k ) ;

              if ( selectPho[0].second.Pt() > 80. ) {
                 if ( cosmicTag ) {
                    cosmic_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
		    cosmic_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
		    cosmic_Pt_Time->Fill( gP4_.Pt() , rt.seedTime[k] , weight );
		    cosmic_sMin_Time->Fill( rt.sMinPho[k], rt.seedTime[k] , weight ) ;
		    cosmic_sMaj_Time->Fill( rt.sMajPho[k], rt.seedTime[k] , weight ) ;
		    cosmic_Time->Fill( rt.seedTime[k] , weight ) ;
		    cosmic_tChi2->Fill( rt.timeChi2[k] ,  weight );
		    cosmic_seedE_photE->Fill( rt.seedE[k] , gP4_.E(),  weight );
                    if ( fabs( rt.seedTime[k]) > 1.5 ) {
		       cosmic_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k] , weight ) ;
		       cosmic_photIso_Time->Fill( phIso, rt.seedTime[k] , weight ) ;
		       cosmic_nXtl->Fill( rt.nXtals[k] , weight );
                    }
		    cosmic_MET_Time->Fill( met.E() , rt.seedTime[k] , weight );
                    if ( noPhotMET.E() < 60 && rt.timeChi2[k] < 4. ) {
                       if ( selectJets.size() == 0 ) cosmic_MET_Time_0J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
		       if ( selectJets.size() == 1 ) cosmic_MET_Time_1J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
		       if ( selectJets.size() >= 2 ) cosmic_MET_Time_2J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
                    }
                    if ( noPhotMET.E() > 60 && rt.timeChi2[k] < 4. ) {
                       if ( selectJets.size() == 0 ) cosmic_MET2_Time_0J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
		       if ( selectJets.size() == 1 ) cosmic_MET2_Time_1J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
		       if ( selectJets.size() >= 2 ) cosmic_MET2_Time_2J->Fill( newMET.E(), rt.seedTime[k] , weight ) ;
                    }
                 }
              }
       } // end of photon looping 
 
}  

void CosmicStudy::DrawHistograms( hDraw* h_draw ) {

   bool createDrawer = false;
   if ( h_draw == NULL ) {
      h_draw = new hDraw( hfolder, plotType ) ;
      createDrawer = true ;
      cout<<" create drawing class " << endl ;
   }

   hfolder += "cosmics/" ;
   gSystem->mkdir( hfolder.c_str() );
   h_draw->SetPath( hfolder ) ;

   // Halo Studies
   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);

   h_draw->SetPlotStyle(false) ; // Turn off the stats box

   h_draw->Draw2D( cosmic_sMaj_Time, "cosmic_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( cosmic_sMin_Time, "cosmic_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( cosmic_sMaj_sMin, "cosmic_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( cosmic_Eta_Time,  "cosmic_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_Phi_Time,  "cosmic_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_Pt_Time,   "cosmic_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_MET_Time,  "cosmic_MET_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( cosmic_photIso_Time,"cosmic_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( cosmic_seedE_photE, "cosmic_seedE_photE",   " seedE (GeV)", " Photon E (GeV)", "logZ" , 8 ) ;
   h_draw->Draw(   cosmic_nXtl,      "cosmic_nXtl",    "N crystals",       "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   cosmic_Time,      "cosmic_Time", " Ecal time ", "", "logY", 0.95, 1 ) ;

   gPad->SetGridx() ;
   gStyle->SetOptStat("");
   ABCD_Report() ;

   if ( createDrawer ) delete h_draw ;
}

bool CosmicStudy::CosmicTag( Rtuple& rt, int k ) {

     bool cosmicTag = ( rt.dtdEta[k] < 0.1 && rt.dtdPhi[k] < 0.1 ) ? true : false ;
     return cosmicTag ;

}

void CosmicStudy::GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) {

     newMET    = newMET_ ;
     noPhotMET = noPhotMET_ ;
}

void CosmicStudy::ABCD_Report() {

    // MET: ( 50, 0, 500)  Time: ( 160, -20, 20 )
    double nA0 = cosmic_MET_Time_0J->Integral( 1, 6, 41,  67 );
    double nB0 = cosmic_MET_Time_0J->Integral( 7,50, 41,  67 );
    double nC0 = cosmic_MET_Time_0J->Integral( 1, 6, 93, 120 );
    double nD0 = cosmic_MET_Time_0J->Integral( 7,50, 93, 120 );

    double nA1 = cosmic_MET_Time_1J->Integral( 1, 6, 41,  67 );
    double nB1 = cosmic_MET_Time_1J->Integral( 7,50, 41,  67 );
    double nC1 = cosmic_MET_Time_1J->Integral( 1, 6, 93, 120 );
    double nD1 = cosmic_MET_Time_1J->Integral( 7,50, 93, 120 );

    double nA2 = cosmic_MET_Time_2J->Integral( 1, 6, 41,  67 );
    double nB2 = cosmic_MET_Time_2J->Integral( 7,50, 41,  67 );
    double nC2 = cosmic_MET_Time_2J->Integral( 1, 6, 93, 120 );
    double nD2 = cosmic_MET_Time_2J->Integral( 7,50, 93, 120 );

    printf(" ============ Cosmics 0Jet ============\n") ;
    double rDC0 = ( nC0 < 0.0001 ) ? -1 : nD0/nC0 ;
    double rBA0 = ( nA0 < 0.0001 ) ? -1 : nB0/nA0 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.2f \n", nC0, nD0 , rDC0 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.2f \n", nA0, nB0 , rBA0 ) ;

    printf(" ============ Cosmics 1Jet ============\n") ;
    double rDC1 = ( nC1 < 0.0001 ) ? -1 : nD1/nC1 ;
    double rBA1 = ( nA1 < 0.0001 ) ? -1 : nB1/nA1 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.2f \n", nC1, nD1, rDC1 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.2f \n", nA1, nB1, rBA1 ) ;

    printf(" ============ Cosmics >= 2Jet ============\n") ;
    double rDC2 = ( nC2 < 0.0001 ) ? -1 : nD2/nC2 ;
    double rBA2 = ( nA2 < 0.0001 ) ? -1 : nB2/nA2 ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.2f \n", nC2, nD2, rDC2 ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.2f \n", nA2, nB2, rBA2 ) ;

    printf(" ============ Cosmics >= 1Jet ============\n") ;
    double rDC = ( (nC2 + nC1) < 0.0001 ) ? -1 : (nD2+nD1)/(nC2+nC1) ;
    double rBA = ( (nA2 + nA1) < 0.0001 ) ? -1 : (nB2+nB1)/(nA2+nA1) ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.2f \n", nC2+nC1, nD2+nD1, rDC ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.2f \n", nA2+nA1, nB2+nB1, rBA ) ;

    printf(" =====================================\n") ;

}

