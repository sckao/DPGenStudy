#include "SpikeStudy.h"
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

SpikeStudy::SpikeStudy( string datacardfile ) {

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


SpikeStudy::~SpikeStudy(){

  if ( createFile ) {
     theFile->Close() ;
     cout<<" File closed ! "<<endl ;
  }

  delete Input ;
  cout<<" done ! "<<endl ;

}


void SpikeStudy::Create( TFile* hFile ) {


  if ( hFile == NULL ) {
     TString Path_fName = hfolder + hfileName + ".root" ;
     theFile = new TFile( Path_fName, "RECREATE" );
     createFile = true ;
  } else {
     theFile = hFile ;
     createFile = false ;
  }
  theFile->cd() ;

  spike_tChi2  = new TH1D( "spike_tChi2", " chi2 of time ", 100, 0, 10  ) ;

  spikeCS_Eta_Time  = new TH2D( "spikeCS_Eta_Time", " #eta vs time for spikes CS",  51, -2.5, 2.5,   160, -20, 20 ) ;
  spikeCS_Eta_Time1 = new TH2D( "spikeCS_Eta_Time1", " #eta vs time after spikes tagging",  51, -2.5, 2.5,   160, -20, 20 ) ;
  spikeCS_Phi_Time  = new TH2D( "spikeCS_Phi_Time", " #phi vs time for spikes CS",  63, -3.15, 3.15, 160, -20, 20 ) ;
  spikeCS_sMaj_sMin = new TH2D( "spikeCS_sMaj_sMin", "sMaj vs sMin for spikes CS", 100,  0, 2, 50, 0.1, 0.4   ) ;
  spikeCS_nXtl      = new TH1D( "spikeCS_nXtl",      "N of xtals of spikes ", 50,  0, 50 );
  spikeCS_swissX    = new TH1D( "spikeCS_swissX",    " swiss-X for spike CS ", 110,  0, 1.1 );

  spike_Eta[0] = new TH1D( "spike_Eta0", "Eta before Spike-tagging", 6, 0., 1.68 ) ;
  spike_Eta[1] = new TH1D( "spike_Eta1", "Eta after Spike-tagging",  6, 0., 1.68 ) ;

  char nameStr3[25], nameStr4[25] ; 
  for ( int i=0; i< 7; i++) {
      sprintf( nameStr3, "nXtl_eta%d", i+1 ) ;
      sprintf( nameStr4, "nXtl_eta_topo%d", i+1 ) ;
      nXtl_eta[i]      =  new TH1D( nameStr3,  "N of Crystals ",  50, 0., 50 ) ;
      nXtl_eta_topo[i] =  new TH1D( nameStr4,  "N of Crystals ",  50, 0., 50 ) ;
  }

  spike_MET_Time_0J  = new TH2D("spike_MET_Time_0J", "MET vs photon time for 0-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;
  spike_MET_Time_1J  = new TH2D("spike_MET_Time_1J", "MET vs photon time for 1-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;
  spike_MET_Time_2J  = new TH2D("spike_MET_Time_2J", "MET vs photon time for 2-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;
  spike_MET2_Time_0J = new TH2D("spike_MET2_Time_0J", "MET2 vs photon time for 0-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;
  spike_MET2_Time_1J = new TH2D("spike_MET2_Time_1J", "MET2 vs photon time for 1-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;
  spike_MET2_Time_2J = new TH2D("spike_MET2_Time_2J", "MET2 vs photon time for 2-jet spike photon", 50, 0, 500, 160, -20, 20 ) ;

  spike_sigIeta   = new TH1D( "spike_sigIeta", " Sigma Ieta Ieta for spike photon ", 100,  0., 0.1 ) ;
  spike_Pt_Time   = new TH2D( "spike_Pt_Time",  " Pt vs photon time for spike photon ",  50, 0, 500, 160, -20, 20 ) ;
  spike_MET_Time  = new TH2D( "spike_MET_Time", " MET vs photon time for spike photon ", 50, 0, 500, 160, -20, 20 ) ;
  spike_Eta_Time  = new TH2D( "spike_Eta_Time", " eta vs photon time for spike photon ", 51, -2.5, 2.5,   160, -20, 20 ) ;
  spike_Phi_Time  = new TH2D( "spike_Phi_Time", " phi vs photon time for spike photon ", 63, -3.15, 3.15, 160, -20, 20 ) ;
  spike_sMaj_sMin = new TH2D( "spike_sMaj_sMin", " sMajor vs sMinor for spike photon ", 100, 0., 2., 50, 0.1, 0.4 ) ;
  spike_sMaj_Time = new TH2D( "spike_sMaj_Time",  "sMaj vs Ecal time for spike Photon", 100, 0, 2, 160, -20, 20 ) ;
  spike_sMin_Time = new TH2D( "spike_sMin_Time",  "sMin vs. Ecal time for spike photon", 100, 0., 0.5 , 160, -20, 20  ) ;
  spike_Time      = new TH1D( "spike_Time",   "Photon time w/ spike ", 160,  -14.5, 25.5 ) ;
  spike_photIso_Time = new TH2D("spike_photIso_Time", " Photon IsoDeposit vs time",           100, 0, 10., 120, -15, 15 );
  spike_nHadIso_Time = new TH2D("spike_nHadIso_Time", " Neutral Hadronic IsoDeposit vs time", 100, 0, 10., 120, -15, 15 );
  spike_sMaj_sigIeta = new TH2D( "spike_sMaj_sigIeta", " sMaj vs #sigma_{i#eta}", 100, 0, 2, 80, 0, 0.08 ) ;
  spike_sMin_sigIeta = new TH2D( "spike_sMin_sigIeta",  "sMin vs #sigma_{i#eta} ", 100, 0., 0.5 , 80, 0, 0.08 ) ;
  spike_T_dPhi_gMET_0J = new TH2D("spike_T_dPhi_gMET_0J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  spike_T_dPhi_gMET_1J = new TH2D("spike_T_dPhi_gMET_1J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;
  spike_T_dPhi_gMET_2J = new TH2D("spike_T_dPhi_gMET_2J", "time vs dPhi( photon, MET)", 120, -15, 15, 64, 0, 3.2 ) ;

  notSpike_nXtl   = new TH1D("notSpike_nXtl", "N of crystals for non-spike photon ", 50,  0, 50 );

}

void SpikeStudy::Open( TFile* hFile ) {

     if ( hFile == NULL ) {
        TString Path_fName = hfolder + hfileName + ".root" ;
        theFile = new TFile( Path_fName, "UPDATE" );
        createFile = true ;
        cout<<" file opened ! "<<endl ;
     } else {
        theFile = hFile ;
        createFile = false ;
     }

     /*
     TString Path_fName = hfolder + hfileName + ".root" ; 
     cout<<" Opening : "<< Path_fName <<" for spike-study "<<endl ;

     theFile = (TFile*) TFile::Open( Path_fName , "READ" );
     */

     spike_tChi2  = (TH1D*) theFile->Get("spike_tChi2");

     spikeCS_Eta_Time1 = (TH2D*) theFile->Get("spikeCS_Eta_Time1");
     spikeCS_Eta_Time  = (TH2D*) theFile->Get("spikeCS_Eta_Time");
     spikeCS_Phi_Time  = (TH2D*) theFile->Get("spikeCS_Phi_Time");
     spikeCS_sMaj_sMin = (TH2D*) theFile->Get("spikeCS_sMaj_sMin");
     spikeCS_nXtl   = (TH1D*) theFile->Get("spikeCS_nXtl");
     spikeCS_swissX = (TH1D*) theFile->Get("spikeCS_swissX");

     spike_Eta[0] = (TH1D*) theFile->Get("spike_Eta0");
     spike_Eta[1] = (TH1D*) theFile->Get("spike_Eta1");

     char nameStr3[25], nameStr4[25] ; 
     for ( int i=0; i< 7; i++) {
	 sprintf( nameStr3, "nXtl_eta%d", i+1 ) ;
	 sprintf( nameStr4, "nXtl_eta_topo%d", i+1 ) ;
         nXtl_eta[i]      = (TH1D*) theFile->Get( nameStr3 );
         nXtl_eta_topo[i] = (TH1D*) theFile->Get( nameStr4 );
     }

     spike_MET_Time_0J = (TH2D*) theFile->Get("spike_MET_Time_0J");
     spike_MET_Time_1J = (TH2D*) theFile->Get("spike_MET_Time_1J");
     spike_MET_Time_2J = (TH2D*) theFile->Get("spike_MET_Time_2J");
     spike_MET2_Time_0J = (TH2D*) theFile->Get("spike_MET2_Time_0J");
     spike_MET2_Time_1J = (TH2D*) theFile->Get("spike_MET2_Time_1J");
     spike_MET2_Time_2J = (TH2D*) theFile->Get("spike_MET2_Time_2J");

     spike_Eta_Time = (TH2D*) theFile->Get("spike_Eta_Time");
     spike_Phi_Time = (TH2D*) theFile->Get("spike_Phi_Time");
     spike_Pt_Time  = (TH2D*) theFile->Get("spike_Pt_Time");
     spike_MET_Time = (TH2D*) theFile->Get("spike_MET_Time");
     spike_sMaj_sMin = (TH2D*) theFile->Get("spike_sMaj_sMin");
     spike_sMaj_Time = (TH2D*) theFile->Get("spike_sMaj_Time");
     spike_sMin_Time = (TH2D*) theFile->Get("spike_sMin_Time");
     spike_photIso_Time = (TH2D*) theFile->Get("spike_photIso_Time");
     spike_nHadIso_Time = (TH2D*) theFile->Get("spike_nHadIso_Time");
     spike_sigIeta = (TH1D*) theFile->Get("spike_sigIeta");
     spike_Time = (TH1D*) theFile->Get("spike_Time");
     spike_sMaj_sigIeta = (TH2D*) theFile->Get("spike_sMaj_sigIeta");
     spike_sMin_sigIeta = (TH2D*) theFile->Get("spike_sMin_sigIeta");
     spike_T_dPhi_gMET_1J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_1J") ;
     spike_T_dPhi_gMET_2J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_2J") ;
     spike_T_dPhi_gMET_0J  = (TH2D*) theFile->Get("spike_T_dPhi_gMET_0J") ;

     notSpike_nXtl = (TH1D*) theFile->Get("notSpike_nXtl");

     cout<<" link all histograms  "<<endl ;
}

void SpikeStudy::Write() {

  theFile->cd() ;

  spikeCS_Eta_Time->Write() ;
  spikeCS_Eta_Time1->Write() ;
  spikeCS_Phi_Time->Write() ;
  spikeCS_sMaj_sMin->Write() ;
  spikeCS_nXtl->Write() ;
  spikeCS_swissX->Write() ;

  spike_tChi2->Write() ;

  spike_Eta[0]->Write();
  spike_Eta[1]->Write();

  for ( int i=0; i< 7; i++ ) {
      nXtl_eta[i]->Write() ;
      nXtl_eta_topo[i]->Write() ;
  }

  spike_MET_Time_0J->Write() ;
  spike_MET_Time_1J->Write() ;
  spike_MET_Time_2J->Write() ;
  spike_MET2_Time_0J->Write() ;
  spike_MET2_Time_1J->Write() ;
  spike_MET2_Time_2J->Write() ;

  spike_Eta_Time->Write() ;
  spike_Phi_Time->Write() ;
  spike_Pt_Time->Write() ;
  spike_MET_Time->Write() ;
  spike_sMaj_Time->Write() ;
  spike_sMin_Time->Write() ;
  spike_photIso_Time->Write() ;
  spike_nHadIso_Time->Write() ;
  spike_sMaj_sMin->Write();
  spike_Time->Write() ;
  spike_sigIeta->Write() ;
  spike_sMaj_sigIeta->Write() ;
  spike_sMin_sigIeta->Write() ;
  spike_T_dPhi_gMET_1J->Write() ;
  spike_T_dPhi_gMET_2J->Write() ;
  spike_T_dPhi_gMET_0J->Write() ;
  spike_tChi2->Write() ;

  cout<<" Output historams written ! "<< endl ;
}


// analysis template
void SpikeStudy::Run( vector<objID>& selectPho, vector<objID>& selectJets, Rtuple& rt, double weight ) { 

     TLorentzVector met( rt.metPx, rt.metPy, 0, rt.metE)  ;
 
     //double leadPt = 0 ;
     //for ( int k=0 ; k < rt.nPhotons ; k++ ) {
     //    TLorentzVector gP4_ = TLorentzVector( rt.phoPx[k], rt.phoPy[k], rt.phoPz[k], rt.phoE[k] ) ;
     //    if ( k ==0 ) leadPt = gP4_.Pt() ;
     for ( size_t kk =0; kk < selectPho.size() ; kk++) {
         int k = selectPho[kk].first ;
	 TLorentzVector gP4_ = selectPho[kk].second ;

         // Possible bad crystals 
         bool badApple = badCrystal( gP4_.Eta(), gP4_.Phi()  ) ;
         if ( badApple ) continue ;
	 //if ( gP4_.Eta() > -0.75 && gP4_.Eta() < -0.6 && gP4_.Phi() > -1.   && gP4_.Phi() < -0.8 ) continue ;
	 //if ( gP4_.Eta() > 0.80  && gP4_.Eta() < 0.95 && gP4_.Phi() > -1.95 && gP4_.Phi() < -1.8 ) continue ;

	 double dPhi_gMET = fabs( gP4_.DeltaPhi( met ) );
	 double phIso = max( rt.photIso[k] - (0.005*gP4_.Pt()) , 0. ) ;
	 double nHIso = max( rt.nHadIso[k] - (0.04*gP4_.Pt()) , 0. ) ;
         bool   spikeTag = SpikeTag( rt, k ) ;

         // ****************************
         //  Current Spike-Control Sample - for efficiency and fake rate study
         // ****************************
         if ( selectJets.size() < 3 && rt.seedTime[k]  < -3 &&  fabs( gP4_.Eta() ) < 1.4 &&
                 rt.cscdPhi[k] > 0.1 && fabs(gP4_.Phi()) > 0.2 && fabs( fabs(gP4_.Phi()) - 3.1416 ) > 0.2 ) {

                spikeCS_sMaj_sMin->Fill( rt.sMajPho[k] , rt.sMinPho[k] , weight ) ;
		spikeCS_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
		spikeCS_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
		spikeCS_nXtl->Fill( rt.nXtals[k] , weight ) ;
		spikeCS_swissX->Fill( rt.seedSwissX[k] , weight ) ;

		if ( fabs(gP4_.Eta()) < 0.28 )                            nXtl_eta[0]->Fill( rt.nXtals[k] , weight ) ;
		if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) nXtl_eta[1]->Fill( rt.nXtals[k] , weight ) ;
		if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) nXtl_eta[2]->Fill( rt.nXtals[k] , weight ) ;
		if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) nXtl_eta[3]->Fill( rt.nXtals[k] , weight ) ;
		if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) nXtl_eta[4]->Fill( rt.nXtals[k] , weight ) ;
		if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) nXtl_eta[5]->Fill( rt.nXtals[k] , weight ) ;
	        if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) nXtl_eta[6]->Fill( rt.nXtals[k] , weight ) ;

		if ( rt.sMajPho[k] < 0.6 && rt.sMinPho[k] < 0.17  ) {
                   if ( fabs(gP4_.Eta()) < 0.28 )                            nXtl_eta_topo[0]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 0.28 && fabs(gP4_.Eta()) < 0.56 ) nXtl_eta_topo[1]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 0.56 && fabs(gP4_.Eta()) < 0.84 ) nXtl_eta_topo[2]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 0.84 && fabs(gP4_.Eta()) < 1.12 ) nXtl_eta_topo[3]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 1.12 && fabs(gP4_.Eta()) < 1.40 ) nXtl_eta_topo[4]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 1.5  && fabs(gP4_.Eta()) < 2.0  ) nXtl_eta_topo[5]->Fill( rt.nXtals[k] , weight ) ;
		   if ( fabs(gP4_.Eta()) > 2.   && fabs(gP4_.Eta()) < 2.5  ) nXtl_eta_topo[6]->Fill( rt.nXtals[k] , weight ) ;
		}

		// Count efficiency in different eta slice 
		double SpikeEta = ( fabs(gP4_.Eta()) > 1.67 ) ? 1.67 : fabs( gP4_.Eta() ) ;
		spike_Eta[0]->Fill( SpikeEta, weight ) ;

		if ( spikeTag ) { 
                   spikeCS_Eta_Time1->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
                   spike_Eta[1]->Fill( SpikeEta, weight )  ;
                }
         }


         // ****************************
	 //  Information after applying spike-tagging 
	 // ****************************
         if ( selectPho[0].second.Pt() > 80. ) {
         //if ( leadPt > 80. ) {

            if ( spikeTag ) {
               spike_Eta_Time->Fill( gP4_.Eta() , rt.seedTime[k] , weight );
	       spike_Phi_Time->Fill( gP4_.Phi() , rt.seedTime[k] , weight );
	       spike_sMaj_Time->Fill( rt.sMajPho[k], rt.seedTime[k] , weight ) ;
	       spike_sMin_Time->Fill( rt.sMinPho[k], rt.seedTime[k] , weight ) ;
	       spike_Time->Fill( rt.seedTime[k] , weight ) ;
	       spike_photIso_Time->Fill( phIso, rt.seedTime[k] , weight ) ;
	       spike_nHadIso_Time->Fill( nHIso, rt.seedTime[k] , weight ) ;
	       spike_tChi2->Fill( rt.timeChi2[k] ,  weight );
	       if ( fabs( rt.seedTime[k]) > 1.5 ) {
	          spike_Pt_Time->Fill( gP4_.Pt(), rt.seedTime[k] , weight );
		  spike_MET_Time->Fill( met.E(), rt.seedTime[k] , weight );
		  spike_sMaj_sMin->Fill( rt.sMajPho[k], rt.sMinPho[k] , weight ) ;
		  spike_sigIeta->Fill( rt.sigmaIeta[k] , weight ) ;
		  spike_sMaj_sigIeta->Fill( rt.sMajPho[k], rt.sigmaIeta[k] , weight ) ;
		  spike_sMin_sigIeta->Fill( rt.sMinPho[k], rt.sigmaIeta[k] , weight ) ;
	       }
               //double dPhi_gMET = gP4_.DeltaPhi( met ) ;
	       if ( selectJets.size() == 0 ) spike_T_dPhi_gMET_0J->Fill( rt.seedTime[k] , dPhi_gMET ) ;
	       if ( selectJets.size() == 1 ) spike_T_dPhi_gMET_1J->Fill( rt.seedTime[k] , dPhi_gMET ) ;
	       if ( selectJets.size() >= 2 ) spike_T_dPhi_gMET_2J->Fill( rt.seedTime[k] , dPhi_gMET ) ;

               if ( noPhotMET.E() < 60 && rt.timeChi2[k] < 4. ) {
                  if ( selectJets.size() == 0 ) spike_MET_Time_0J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
		  if ( selectJets.size() == 1 ) spike_MET_Time_1J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
		  if ( selectJets.size() >= 2 ) spike_MET_Time_2J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
               }
               if ( noPhotMET.E() > 60 && rt.timeChi2[k] < 4. ) {
                  if ( selectJets.size() == 0 ) spike_MET2_Time_0J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
		  if ( selectJets.size() == 1 ) spike_MET2_Time_1J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
		  if ( selectJets.size() >= 2 ) spike_MET2_Time_2J->Fill( newMET.E(), rt.seedTime[k] , weight ) ; 
               }

            } else { 
               notSpike_nXtl->Fill( rt.nXtals[k] , weight );
            }
         }

       } // end of photon looping 
 

}  

void SpikeStudy::DrawHistograms( hDraw* h_draw ) {

   bool createDrawer = false;
   if ( h_draw == NULL ) {
      h_draw = new hDraw( hfolder, plotType ) ;
      createDrawer = true ;
      cout<<" create drawing class " << endl ;
   }

   hfolder += "spike/" ;
   gSystem->mkdir( hfolder.c_str() );
   h_draw->SetPath( hfolder );

   // Halo Studies
   h_draw->SetHistoAtt("X", 0, 0, 0, 0 ) ;
   h_draw->SetHistoAtt("Y", 0, 0, 0, 0 ) ;
   gStyle->SetOptStat("");
   gStyle->SetStatY(0.9);


   TLegend* leg2  = new TLegend(.62, .7, .85, .9 );
   leg2->Clear() ;

   h_draw->Draw2D( spikeCS_Eta_Time1, "spikeCS_Eta_Time1", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_Eta_Time,  "spikeCS_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spikeCS_Phi_Time,  "spikeCS_Phi_Time", "#phi", "EcalTime (ns)",  ""  ) ;
   h_draw->Draw2D( spikeCS_sMaj_sMin, "spikeCS_sMaj_sMin", "sMaj", "sMin (ns)",  ""  ) ;
   h_draw->Draw(   spikeCS_swissX,    "spikeCS_swissX",    " Swiss-X", "", "logY", 0.95, 1 ) ;

   /*
   leg2->Clear() ;
   spikeCS_nXtl->SetLineWidth(2) ;
   halo_nXtl->SetLineWidth(2) ;
   cs_nXtl->SetFillColor(7) ;
   cs_nXtl->SetLineWidth(2) ;
   leg2->AddEntry(    spikeCS_nXtl,  "Spike CS" , "L" ) ;
   leg2->AddEntry(    halo_nXtl,     "Halo ", "L" ) ;
   leg2->AddEntry(    cs_nXtl,       " |t| < 1 ns", "F" ) ;

   h_draw->Draw(            cs_nXtl,  "", "N of crystals", "", "", 0.95, 4, 100/ cs_nXtl->Integral() ) ;
   h_draw->DrawAppend(    halo_nXtl,  "",    0.85, 1,                       100/ halo_nXtl->Integral()  ) ;
   h_draw->DrawAppend( spikeCS_nXtl,  "spikeCS_nXtl",    0.85, 2,           100/ spikeCS_nXtl->Integral(), leg2 ) ;
   */

   h_draw->Draw2D( spike_sMaj_Time, "spike_sMaj_Time",  "sMaj", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMin_Time, "spike_sMin_Time",  "sMin", " EcalTime (ns) ",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMaj_sMin, "spike_sMaj_sMin", " sMajor ", "sMinor", "") ;
   h_draw->Draw2D( spike_Eta_Time,  "spike_Eta_Time", "#eta", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_Phi_Time,  "spike_Phi_Time", "#phi", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_Pt_Time,   "spike_Pt_Time",  "P_{T}", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw2D( spike_MET_Time,  "spike_MET_Time", "MET", "EcalTime (ns)",  "", 8 ) ;
   h_draw->Draw(   spike_sigIeta,   "spike_sigIeta", " Sigma_IetaIeta ", "", "logY", 0.95, 1 ) ;
   h_draw->Draw2D( spike_photIso_Time,"spike_photIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( spike_nHadIso_Time,"spike_nHadIso_Time",   " Photon Iso", "EcalTime (ns)", "logZ" , 8 ) ;
   h_draw->Draw2D( spike_sMaj_sigIeta,"spike_sMaj_sigIeta",   "sMaj", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( spike_sMin_sigIeta,"spike_sMin_sigIeta",   "sMin", "#sigma_{i#eta i#eta}",  "logZ"  ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_1J, "spike_T_dPhi_gMET_1J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_2J, "spike_T_dPhi_gMET_2J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;
   h_draw->Draw2D( spike_T_dPhi_gMET_0J, "spike_T_dPhi_gMET_0J", "EcalTime (ns)", "dPhi( photon, MET)", "logZ", 8 ) ;

   gPad->SetGridx() ;
   gStyle->SetOptStat("");

   gStyle->SetOptStat("");
   for (int i=0; i<5; i++) { 
       nXtl_eta[i]->SetLabelSize(0.1, "X") ;
       nXtl_eta[i]->SetLabelSize(0.1, "Y") ;
   }
   h_draw->CreateNxM( "nXtl_EtaSlice", 2,3 );
   h_draw->DrawNxM( 1, nXtl_eta[0] , "",          "", "logY", 1, false );
   h_draw->DrawNxM( 2, nXtl_eta[1] , "",          "", "logY", 2, false );
   h_draw->DrawNxM( 3, nXtl_eta[2] , "",          "", "logY", 4, false );
   h_draw->DrawNxM( 4, nXtl_eta[3] , "",          "", "logY", 6, false ) ;
   h_draw->DrawNxM( 5, nXtl_eta[4] , "N. of Xtals", "", "logY", 8, true ) ;

   gStyle->SetOptStat("");
   for (int i=0; i<5; i++) { 
       nXtl_eta_topo[i]->SetLabelSize(0.1, "X") ;
       nXtl_eta_topo[i]->SetLabelSize(0.1, "Y") ;
   }
   h_draw->CreateNxM( "nXtl_EtaSlice_topo", 2,3 );
   h_draw->DrawNxM( 1, nXtl_eta_topo[0] , "",          "", "logY", 1, false );
   h_draw->DrawNxM( 2, nXtl_eta_topo[1] , "",          "", "logY", 2, false );
   h_draw->DrawNxM( 3, nXtl_eta_topo[2] , "",          "", "logY", 4, false );
   h_draw->DrawNxM( 4, nXtl_eta_topo[3] , "",          "", "logY", 6, false ) ;
   h_draw->DrawNxM( 5, nXtl_eta_topo[4] , "N. of Xtals", "", "logY", 8, true ) ;
   /*
   TLegend* leg6  = new TLegend(.5, .7, .9, .9 );
   float nSp0  = notSpike_nXtl->Integral(1,8);
   float nSp   = notSpike_nXtl->Integral();
   char NStr[50] ;
   sprintf( NStr,  "%.1f / %.1f = %.4f ", nSp0, nSp, nSp0/nSp ) ;
   leg6->AddEntry( notSpike_nXtl, NStr , "L" ) ;
   */

   if ( isData == 1 ) {

      cout<<" ======= Spike Tagging Efficiency ====== "<<endl ;
      TCanvas* c_0 = new TCanvas("c_0","", 800, 700);
      c_0->SetFillColor(10);
      c_0->SetFillColor(10);
      c_0->SetLeftMargin(0.16);
      c_0->SetRightMargin(0.08);
      c_0->SetTopMargin(0.1);
      c_0->SetBottomMargin(0.12);

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
      TString plotname = hfolder + "Efficiency_Spike."+plotType ;
      c_0->Print( plotname ) ;
   }


   ABCD_Report() ;
   h_draw->Draw(   notSpike_nXtl, "notSpike_nXtl", "N of crystals ", "",  "logY", 0.95, 1, 1) ;

   if ( createDrawer ) delete h_draw ;

}

bool SpikeStudy::SpikeTag( Rtuple& rt, int k ) {

     TLorentzVector gP4_ = TLorentzVector( rt.phoPx[k], rt.phoPy[k], rt.phoPz[k], rt.phoE[k] ) ;

     bool spikeTag = ( rt.nXtals[k] < 7 || rt.seedSwissX[k] > 0.9 ) ? true : false  ;
     if ( rt.sMajPho[k] < 0.6 && rt.sMinPho[k] < 0.17 && fabs( gP4_.Eta() ) < 1.47 ) spikeTag = true;
     return spikeTag ;
}

void SpikeStudy::GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) {

     newMET    = newMET_ ;
     noPhotMET = noPhotMET_ ;
}

void SpikeStudy::ABCD_Report( ) {

    // MET: ( 50, 0, 500)  Time: ( 160, -20, 20 )
    double nA0 = spike_MET_Time_0J->Integral( 1, 6, 41,  67 );
    double nB0 = spike_MET_Time_0J->Integral( 7,50, 41,  67 );
    double nC0 = spike_MET_Time_0J->Integral( 1, 6, 93, 120 );
    double nD0 = spike_MET_Time_0J->Integral( 7,50, 93, 120 );

    double nA1 = spike_MET_Time_1J->Integral( 1, 6, 41,  67 );
    double nB1 = spike_MET_Time_1J->Integral( 7,50, 41,  67 );
    double nC1 = spike_MET_Time_1J->Integral( 1, 6, 93, 120 );
    double nD1 = spike_MET_Time_1J->Integral( 7,50, 93, 120 );

    double nA2 = spike_MET_Time_2J->Integral( 1, 6, 41,  67 );
    double nB2 = spike_MET_Time_2J->Integral( 7,50, 41,  67 );
    double nC2 = spike_MET_Time_2J->Integral( 1, 6, 93, 120 );
    double nD2 = spike_MET_Time_2J->Integral( 7,50, 93, 120 );

    printf(" ============ Spike 0Jet ============\n") ;
    double rDC0 = ( nC0 < 0.0001 ) ? -1 : nD0/nC0 ;
    double rBA0 = ( nA0 < 0.0001 ) ? -1 : nB0/nA0 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.2f \n", nC0, nD0 , rDC0 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.2f \n", nA0, nB0 , rBA0 ) ;

    printf(" ============ Spike 1Jet ============\n") ;
    double rDC1 = ( nC1 < 0.0001 ) ? -1 : nD1/nC1 ;
    double rBA1 = ( nA1 < 0.0001 ) ? -1 : nB1/nA1 ;
    printf(" | [C] %.1f  | [D] %.1f | [D/C] = %.2f \n", nC1, nD1, rDC1 ) ;
    printf(" | [A] %.1f  | [B] %.1f | [B/A] = %.2f \n", nA1, nB1, rBA1 ) ;

    printf(" ============ Spike >= 2Jet ============\n") ;
    double rDC2 = ( nC2 < 0.0001 ) ? -1 : nD2/nC2 ;
    double rBA2 = ( nA2 < 0.0001 ) ? -1 : nB2/nA2 ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.2f \n", nC2, nD2, rDC2 ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.2f \n", nA2, nB2, rBA2 ) ;

    printf(" ============ Spike >= 1Jet ============\n") ;
    double rDC = ( (nC2 + nC1) < 0.0001 ) ? -1 : (nD2+nD1)/(nC2+nC1) ;
    double rBA = ( (nA2 + nA1) < 0.0001 ) ? -1 : (nB2+nB1)/(nA2+nA1) ;
    printf(" | [C] %.1f | [D] %.1f | [D/C] = %.2f \n", nC2+nC1, nD2+nD1, rDC ) ;
    printf(" | [A] %.1f | [B] %.1f | [B/A] = %.2f \n", nA2+nA1, nB2+nB1, rBA ) ;

    printf(" =====================================\n") ;

}

