#include "QCDStudy.h"
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

QCDStudy::QCDStudy( string datacardfile ) {

  Input  = new AnaInput( datacardfile );

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("PhotonCuts",    &photonCuts ) ; 
  Input->GetParameters("JetCuts",       &jetCuts ) ; 
  Input->GetParameters("HFileName",     &hfileName ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  createFile = false ;
 
}


QCDStudy::~QCDStudy(){

  if ( createFile ) {
     theFile->Close() ;
     cout<<" File closed ! "<<endl ;
  }

  delete Input ;
  cout<<" done ! "<<endl ;

}


void QCDStudy::Create( TFile* hFile ) {

     if ( hFile == NULL ) {
        TString Path_fName = hfolder + hfileName + ".root" ;
	theFile = new TFile( Path_fName, "RECREATE" );
	createFile = true ;
     } else {
        theFile = hFile ;
	createFile = false ;
     }
     theFile->cd() ;

     qcd_MET_Time_0J = new TH2D( "qcd_MET_Time_0J", "MET vs photon time for qcd 0J events" , 50, 0, 500, 160, -20, 20 ) ;
     qcd_MET_Time_1J = new TH2D( "qcd_MET_Time_1J", "MET vs photon time for qcd 1J events", 50, 0, 500, 160, -20, 20 ) ;
     qcd_MET_Time_2J = new TH2D( "qcd_MET_Time_2J", "MET vs photon time for qcd >=2J events", 50, 0, 500, 160, -20, 20 ) ;

     qcd_MET0_Time  = new TH2D( "qcd_MET0_Time", " MET vs photon time for QCD", 50, 0, 500, 160, -20, 20 ) ;
     qcd_MET1_Time  = new TH2D( "qcd_MET1_Time", " MET correction1 vs photon time for QCD ", 50, 0, 500, 160, -20, 20 ) ;
     qcd_MET2_Time  = new TH2D( "qcd_MET2_Time", " MET correction2 vs photon time for QCD ", 50, 0, 500, 160, -20, 20 ) ;
     qcd_cHadIso_Time = new TH2D( "qcd_cHadIso_Time", " Charged Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
     qcd_nHadIso_Time = new TH2D( "qcd_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
     qcd_photIso_Time = new TH2D( "qcd_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );

     qcd_dPhi_gMET_Time = new TH2D("qcd_dPhi_gMET_Time", " dPhi( photon, MET) vs Time", 64, 0, 3.2 , 120, -15, 15) ;

     qcd_Eta_Time  = new TH2D( "qcd_Eta_Time", " eta vs photon time for cosmic photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
     qcd_Phi_Time  = new TH2D( "qcd_Phi_Time", " phi vs photon time for cosmic photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
     qcd_Pt_Time   = new TH2D( "qcd_Pt_Time",  " Pt vs photon time for cosmic photon ",  50, 0, 500, 160, -20, 20 ) ;

     qcd_sMaj_sMin = new TH2D( "qcd_sMaj_sMin", "sMajor vs sMinor for cosmic photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
     qcd_Time      = new TH1D( "qcd_Time",   "Photon time from cosmic ", 160,  -14.5, 25.5 ) ;
     qcd_Time1     = new TH1D( "qcd_Time1",   "Photon time from cosmic ", 160,  -14.5, 25.5 ) ;
     qcd_nXtl      = new TH1D( "qcd_nXtl", " N crystals vs #eta", 50, 0, 50 ) ;
     qcd_tChi2 = new TH1D( "qcd_tChi2", " chi2 of time ", 100, 0, 10  ) ;

}

void QCDStudy::Open() {

     //Input->GetParameters("Path",      &hfolder ) ; 
     //hfolder += "backgrounds/" ;

     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<" for qcd-study " << endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     //hFile->cd() ;
     cout<<" root file opened ! "<<endl ;

     qcd_MET_Time_0J  = (TH2D*) theFile->Get("qcd_MET_Time_0J");
     qcd_MET_Time_1J  = (TH2D*) theFile->Get("qcd_MET_Time_1J");
     qcd_MET_Time_2J  = (TH2D*) theFile->Get("qcd_MET_Time_2J");
     qcd_MET0_Time = (TH2D*) theFile->Get("qcd_MET0_Time");
     qcd_MET1_Time = (TH2D*) theFile->Get("qcd_MET1_Time");
     qcd_MET2_Time = (TH2D*) theFile->Get("qcd_MET2_Time");
     qcd_dPhi_gMET_Time = (TH2D*) theFile->Get("qcd_dPhi_gMET_Time");

     qcd_photIso_Time = (TH2D*) theFile->Get("qcd_photIso_Time");
     qcd_nHadIso_Time = (TH2D*) theFile->Get("qcd_nHadIso_Time");
     qcd_cHadIso_Time = (TH2D*) theFile->Get("qcd_cHadIso_Time");

     qcd_tChi2 = (TH1D*) theFile->Get("qcd_tChi2");
     qcd_Eta_Time = (TH2D*) theFile->Get("qcd_Eta_Time");
     qcd_Phi_Time = (TH2D*) theFile->Get("qcd_Phi_Time");
     qcd_Pt_Time  = (TH2D*) theFile->Get("qcd_Pt_Time");
     qcd_sMaj_sMin    = (TH2D*) theFile->Get("qcd_sMaj_sMin");
     qcd_Time    = (TH1D*) theFile->Get("qcd_Time");
     qcd_Time1   = (TH1D*) theFile->Get("qcd_Time1");
     qcd_nXtl    = (TH1D*) theFile->Get("qcd_nXtl");

     cout<<" link all histograms  "<<endl ;
}

void QCDStudy::Write() {

     qcd_MET_Time_0J->Write() ;
     qcd_MET_Time_1J->Write() ;
     qcd_MET_Time_2J->Write() ;
     qcd_MET0_Time->Write() ;
     qcd_MET1_Time->Write() ;
     qcd_MET2_Time->Write() ;
     qcd_dPhi_gMET_Time->Write() ;

     qcd_photIso_Time->Write() ;
     qcd_nHadIso_Time->Write() ;
     qcd_cHadIso_Time->Write() ;

     qcd_Eta_Time->Write() ;
     qcd_Phi_Time->Write() ;
     qcd_Pt_Time->Write() ;
     qcd_sMaj_sMin->Write();
     qcd_Time->Write() ;
     qcd_Time1->Write() ;
     qcd_nXtl->Write() ;
     qcd_tChi2->Write() ;
     cout<<" Output historams written ! "<< endl ;

}

// analysis template
void QCDStudy::Run(  vector<objID>& selectPho, vector<objID>& selectJets, Rtuple& rt, double weight ) { 

       // MET Correction - take out-of-time photons into account
       TLorentzVector met( rt.metPx, rt.metPy, 0, rt.metE )  ;
       TLorentzVector newMET( rt.metPx, rt.metPy, 0, rt.metE )  ;
       TLorentzVector corrMET( rt.metPx, rt.metPy, 0, rt.metE )  ;
       for ( int k=0 ; k < rt.nPhotons ; k++ ) {

           TLorentzVector gP4_ = TLorentzVector( rt.phoPx[k], rt.phoPy[k], rt.phoPz[k], rt.phoE[k] ) ;
           if ( fabs( rt.seedTime[k]) > 3.0 && fabs( gP4_.Eta() ) < 1.47 ) {
              double newEx =  met.Px() - gP4_.Px()  ;
              double newEy =  met.Py() - gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              newMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }
           if ( fabs(rt.seedTime[k]) > 10.0 && fabs( gP4_.Eta() ) > 1.47 ) {
              double newEx =  met.Px() - gP4_.Px()  ;
              double newEy =  met.Py() - gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              newMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }

           bool isMIB = MIBTag( rt, k ) ;
           if (  isMIB && fabs( rt.seedTime[k]) < 3.0 && fabs( gP4_.Eta() ) < 1.47 ) {
              double newEx =  met.Px() + gP4_.Px()  ;
              double newEy =  met.Py() + gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              corrMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }
           if ( !isMIB && fabs( rt.seedTime[k]) > 3.0 && fabs( gP4_.Eta() ) < 1.47 ) {
              double newEx =  met.Px() - gP4_.Px()  ;
              double newEy =  met.Py() - gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              corrMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }
           if (  isMIB && fabs(rt.seedTime[k]) < 10.0 && fabs( gP4_.Eta() ) > 1.47 ) {
              double newEx =  met.Px() + gP4_.Px()  ;
              double newEy =  met.Py() + gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              corrMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }
           if ( !isMIB && fabs(rt.seedTime[k]) > 10.0 && fabs( gP4_.Eta() ) > 1.47 ) {
              double newEx =  met.Px() - gP4_.Px()  ;
              double newEy =  met.Py() - gP4_.Py()  ;
              double newE  = sqrt( newEx*newEx + newEy*newEy ) ;
              corrMET.SetPxPyPzE( newEx, newEy, 0., newE ) ;
           }
       }

       for ( size_t kk =0; kk < selectPho.size() ; kk++ ) {

           int k = selectPho[kk].first ;
           bool isMIB = MIBTag( rt, k ) ;
           if ( isMIB ) continue ;

	   TLorentzVector gP4_ = selectPho[kk].second ; 
   	   double phIso = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
           double nHIso = max( rt.nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
           double dPhi_gMET = fabs( gP4_.DeltaPhi( met ) ) ;

	   qcd_Pt_Time->Fill( gP4_.Pt() , rt.seedTime[k] , weight );

           if ( selectPho[0].second.Pt() < 80. && selectJets.size() > 0 ) {
	      qcd_MET0_Time->Fill(     met.E(), rt.seedTime[k] , weight ) ;
	      qcd_MET1_Time->Fill(  newMET.E(), rt.seedTime[k] , weight ) ;
	      qcd_MET2_Time->Fill( corrMET.E(), rt.seedTime[k] , weight ) ;
              qcd_dPhi_gMET_Time->Fill( dPhi_gMET, rt.seedTime[k] , weight );

              qcd_photIso_Time->Fill(         phIso, rt.seedTime[k] , weight ) ;
              qcd_nHadIso_Time->Fill(         nHIso, rt.seedTime[k] , weight ) ;
              qcd_cHadIso_Time->Fill( rt.cHadIso[k], rt.seedTime[k] , weight ) ;

	      qcd_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
	      qcd_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
	      qcd_Time->Fill( rt.seedTime[k] , weight ) ;
	      qcd_tChi2->Fill( rt.timeChi2[k] ,  weight );
	      qcd_nXtl->Fill( rt.nXtals[k] , weight ) ;
	      if ( fabs( rt.seedTime[k]) > 1.5 ) {
		 qcd_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k] , weight ) ;
              }

           }

           bool isPFIso = true ;
           if ( rt.cHadIso[k] >= 2.6 ) isPFIso = false ;  // chargedHadron
	   if ( rt.nHadIso[k] >= 3.5 + ( 0.04*gP4_.Pt()   ) ) isPFIso = false ;  // neutralHadron
	   if ( rt.photIso[k] >= 1.3 + ( 0.005*gP4_.Pt() ) )  isPFIso = false ;  // photon

           if ( selectPho[0].second.Pt() < 80. && !isPFIso ) {
              if ( selectJets.size() == 0 ) qcd_MET_Time_0J->Fill( met.E(), rt.seedTime[k] , weight ) ;
              if ( selectJets.size() == 1 ) qcd_MET_Time_1J->Fill( met.E(), rt.seedTime[k] , weight ) ;
              if ( selectJets.size() >= 2 ) qcd_MET_Time_2J->Fill( met.E(), rt.seedTime[k] , weight ) ;
	      if ( selectJets.size() >  0 ) qcd_Time1->Fill( rt.seedTime[k] , weight ) ;
           }

       } // end of photon looping 
 
}  

void QCDStudy::DrawHistograms( hDraw* h_draw ) {

   bool createDrawer = false;
   if ( h_draw == NULL ) {
      h_draw = new hDraw( hfolder, plotType ) ;
      createDrawer = true ;
      cout<<" create drawing class " << endl ;
   }

   hfolder += "qcd/" ;
   gSystem->mkdir( hfolder.c_str() );
   h_draw->SetPath( hfolder ) ;

   // Halo Studies
   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);

   h_draw->SetPlotStyle(false) ; // Turn off the stats box

   h_draw->Draw2D( qcd_MET_Time_0J, "qcd_MET_Time_0J", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_MET_Time_1J, "qcd_MET_Time_1J", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_MET_Time_2J, "qcd_MET_Time_2J", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_MET0_Time,   "qcd_MET0_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_MET1_Time,   "qcd_MET1_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_MET2_Time,   "qcd_MET2_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_dPhi_gMET_Time,"qcd_dPhi_MET_Time", "dPhi(#gamma,MET)", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_photIso_Time,  "qcd_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( qcd_nHadIso_Time,  "qcd_nHadIso_Time",   " Neutral Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( qcd_cHadIso_Time,  "qcd_cHadIso_Time",   " Charged Hadronic Iso", "EcalTime (ns)", "logZ" , 8 ) ;

   h_draw->Draw2D( qcd_Eta_Time,  "qcd_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_Phi_Time,  "qcd_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( qcd_Pt_Time,   "qcd_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw(   qcd_nXtl,      "qcd_nXtl",    "N crystals",       "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   qcd_Time,      "qcd_Time", " Ecal time ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   qcd_Time1,     "qcd_Time1", " Ecal time ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw(   qcd_tChi2,     "qcd_tChi2", " #chi^{2}_{T} ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( qcd_sMaj_sMin, "qcd_sMaj_sMin", " sMajor ", "sMinor", "") ;

   //h_draw->Draw(   qcd_Time,      "", " Ecal time ", "", "logY", 0.95, 2 ) ;
   //h_draw->DrawAppend( qcd_Time1, "qcd_Time1", 0.75, 8, 1 ) ;

   ABCD_Report() ;

   if ( createDrawer ) delete h_draw ;
}

bool QCDStudy::MIBTag( Rtuple& rt, int k ) {

     bool isMIB  = ( rt.cscdPhi[k] < 0.1 ) ? true : false  ;
     if ( rt.sMajPho[k]  > 0.8 || rt.sMinPho[k] < 0.15 ) isMIB = true ;
     if ( rt.nXtals[k] < 7 )                             isMIB = true ;
     if ( rt.dtdEta[k] < 0.1 && rt.dtdPhi[k] < 0.1 )     isMIB = true ;

     return isMIB ;
}

void QCDStudy::ABCD_Report( ) {

    // MET: ( 50, 0, 500)  Time: ( 160, -20, 20 )
    double nA0 = qcd_MET_Time_0J->Integral( 1, 6, 41,  67 );
    double nB0 = qcd_MET_Time_0J->Integral( 7,50, 41,  67 );
    double nC0 = qcd_MET_Time_0J->Integral( 1, 6, 93, 120 );
    double nD0 = qcd_MET_Time_0J->Integral( 7,50, 93, 120 );

    double nA1 = qcd_MET_Time_1J->Integral( 1, 6, 41,  67 );
    double nB1 = qcd_MET_Time_1J->Integral( 7,50, 41,  67 );
    double nC1 = qcd_MET_Time_1J->Integral( 1, 6, 93, 120 );
    double nD1 = qcd_MET_Time_1J->Integral( 7,50, 93, 120 );

    double nA2 = qcd_MET_Time_2J->Integral( 1, 6, 41,  67 );
    double nB2 = qcd_MET_Time_2J->Integral( 7,50, 41,  67 );
    double nC2 = qcd_MET_Time_2J->Integral( 1, 6, 93, 120 );
    double nD2 = qcd_MET_Time_2J->Integral( 7,50, 93, 120 );

    printf(" ============ QCD 0Jet ============\n") ;
    double rDC0 = ( nC0 < 0.0001 ) ? -1 : nD0/nC0 ;
    double rBA0 = ( nA0 < 0.0001 ) ? -1 : nB0/nA0 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.1f \n", nC0, nD0 , rDC0 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.1f \n", nA0, nB0 , rBA0 ) ;

    printf(" ============ QCD 1Jet ============\n") ;
    double rDC1 = ( nC1 < 0.0001 ) ? -1 : nD1/nC1 ;
    double rBA1 = ( nA1 < 0.0001 ) ? -1 : nB1/nA1 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.1f \n", nC1, nD1, rDC1 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.1f \n", nA1, nB1, rBA1 ) ;

    printf(" ============ QCD >= 2Jet ============\n") ;
    double rDC2 = ( nC2 < 0.0001 ) ? -1 : nD2/nC2 ;
    double rBA2 = ( nA2 < 0.0001 ) ? -1 : nB2/nA2 ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.1f \n", nC2, nD2, rDC2 ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.1f \n", nA2, nB2, rBA2 ) ;

    printf(" ============ QCD >= 1Jet ============\n") ;
    double rDC = ( (nC2 + nC1) < 0.0001 ) ? -1 : (nD2+nD1)/(nC2+nC1) ;
    double rBA = ( (nA2 + nA1) < 0.0001 ) ? -1 : (nB2+nB1)/(nA2+nA1) ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.1f \n", nC2+nC1, nD2+nD1, rDC ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.1f \n", nA2+nA1, nB2+nB1, rBA ) ;

    printf(" =====================================\n") ;

}
