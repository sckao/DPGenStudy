#ifndef Output_H
#define Output_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TFile.h>
#include <TTree.h>
#include "TLorentzVector.h"

#include "AnaInput.h"
#include "DPSelection.h"

/*
#define MAXPHO 10
#define MAXVTX 10
#define MAXMU 5
*/

class Output : public TObject {

public:

   Output( string datacardfile = "DataCard.txt");     
   ~Output();     
 
   void CreateHisto() ;  
   void ReadHisto( TFile* hFile = NULL ) ;  
   void RunData( string dataName ) ;
   void RunMC( string mcName, string ctau_Id, double weight = -1 ) ;
   void RunGenOnly( string mcName, string ctau_Id, double weight = -1, double scale = 1. ) ;
   void Produce() ;
   void ProduceMC() ;
   void ProduceGen() ;
   bool Propagator( TLorentzVector& v, double& x, double& y, double& z, double& t, double ctaugamma = 99999999. ) ;

   TH1D* RebinHistogram( TH1D* h1, string newHistoName, double minBC ) ;
   TH1D* RebinHistogram( TH1D* h1, string newHistoName, double lowX, double upX ) ;

   void ShiftPeak( TH1D* h1, TH1D* h2 ) ;

   double ABCD( TH2D* hA, TH2D* hB, TH2D* hC, TH2D* hD ) ;
   double GetEstimation( TH2D* hCount, bool getQCD = true ) ;
   vector<double> GetComponent( int eta_i, double B12, double h_B12, double s_B12 ) ;

   void WriteDataHisto() ;
   void WriteMcHisto() ;

private:

   AnaInput*     Input;
   DPSelection*  select;

   string hfolder  ;
   int    ProcessEvents ;
   int    SkipEvents ;
   // Root File for Rootuple or histograms
   TFile *theFile ;
   string hfName ;
   int systType ;

   vector<double> normV ;
   vector<double> timeCalib ;
   vector<double> jetCuts ;
   vector<double> photonCuts ;
   vector<double> TCut ;
   vector<objID> selectJets ;
   vector<objID> selectPho ;

   TLorentzVector newMET ;
   TLorentzVector noPhotMET ;

   int    n_t_bin ;
   double t_low  ;
   double t_up   ;

   TH1D* h_dataTime  ;
   TH1D* h_dataTimeA  ;
   TH1D* h_dataTimeBFD  ;
   TH1D* h_dataTimeAEC  ;
   TH1D* h_bgTime    ;
   TH1D* h_bgTimeA   ;
   TH1D* h_sgTime    ;
   TH1D* h_sgTimeA    ;
   TH1D* h_sgTimeBFD  ;
   TH1D* h_sgTimeAEC  ;

   TH3D* hBg_A ;
   TH3D* hBg_B ;
   TH3D* hBg_C ;
   TH3D* hBg_D ;
   TH3D* hBg_E ;
   TH3D* hBg_F ;

   TH3D* hCol_A ;
   TH3D* hCol_B ;
   TH3D* hCol_C ;
   TH3D* hCol_D ;
   TH3D* hCol_E ;
   TH3D* hCol_F ;

   TH1D* rh_dataTime  ;
   TH1D* rh_dataTimeA  ;
   TH1D* rh_dataTimeBFD  ;
   TH1D* rh_dataTimeAEC  ;
   TH1D* rh_bgTime    ;
   TH1D* rh_bgTimeA   ;
   TH1D* rh_sgTime    ;
   TH1D* rh_sgTimeA    ;
   TH1D* rh_sgTimeBFD  ;
   TH1D* rh_sgTimeAEC  ;

   //ClassDef(Output, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Output);
#endif

