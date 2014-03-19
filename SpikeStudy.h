#ifndef SpikeStudy_H
#define SpikeStudy_H

#include <TObject.h>
#include <TSystem.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TString.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "DPSelection.h"
#include "hDraw.h"
#include "Rtuple.h"

class SpikeStudy : public TObject {

public:

   SpikeStudy( string datacardfile = "DataCard.txt");     
   ~SpikeStudy();     
   
   void Create( TFile* hfile = NULL ) ;
   void Open( TFile* hfile = NULL ) ;
   void Write() ;
   void Run( vector<objID>& selectPho, vector<objID>& selectJets, Rtuple& rt, double weight = 1. ) ;
   void DrawHistograms( hDraw* h_draw = NULL ) ;
   void GetNewMET( TLorentzVector& newMET_, TLorentzVector& noPhotMET_ ) ;

   bool SpikeTag( Rtuple& rt, int k ) ;
   void ABCD_Report() ;
   // Histograms set
   TH1D* spike_tChi2 ;

   TH2D* spikeCS_Eta_Time1 ;
   TH2D* spikeCS_Eta_Time ;
   TH2D* spikeCS_Phi_Time ;
   TH2D* spikeCS_sMaj_sMin ;
   TH1D* spikeCS_nXtl ;
   TH1D* spikeCS_swissX ;

   TH1D* spike_Eta[2] ;
   TH1D* nXtl_eta[7] ;
   TH1D* nXtl_eta_topo[7] ;
   
   TH2D* spike_Eta_Time ;
   TH2D* spike_Phi_Time ;
   TH2D* spike_Pt_Time ;
   TH2D* spike_MET_Time ;
   TH2D* spike_MET_Time_0J ;
   TH2D* spike_MET_Time_1J ;
   TH2D* spike_MET_Time_2J ;
   TH2D* spike_MET2_Time_0J ;
   TH2D* spike_MET2_Time_1J ;
   TH2D* spike_MET2_Time_2J ;
   TH2D* spike_sMaj_sMin ;
   TH2D* spike_sMaj_Time ;
   TH2D* spike_sMin_Time ;
   TH2D* spike_photIso_Time ;
   TH2D* spike_nHadIso_Time ;
   TH1D* spike_sigIeta ;
   TH1D* spike_Time ;
   TH2D* spike_sMaj_sigIeta ;
   TH2D* spike_sMin_sigIeta ;
   TH1D* notSpike_nXtl ;

   TH2D* spike_T_dPhi_gMET_0J ;
   TH2D* spike_T_dPhi_gMET_1J ;
   TH2D* spike_T_dPhi_gMET_2J ;

private:

   AnaInput*     Input;

   string hfolder  ;
   string plotType ;
   string hfileName ;
   int ProcessEvents ;
   int isData ;

   vector<double> photonCuts ;
   vector<double> jetCuts ;
   vector<double> timeCalib ;
   vector<double> spikeEff ;

   // Root File for Rootuple or histograms
   TFile *theFile ;
   bool createFile ;

   Rtuple tp ;
   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

   //ClassDef(SpikeStudy, 1);
};

//#if !defined(__CINT__)
//    ClassImp(SpikeStudy);
#endif

