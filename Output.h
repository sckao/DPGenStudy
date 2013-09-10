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

#define MAXPHO 10
#define MAXVTX 10
#define MAXMU 5


class Output : public TObject {

public:

   Output( string datacardfile = "DataCard.txt");     
   ~Output();     
   
   void RunData( string dataName ) ;
   void RunMC( string mcName, double weight = -1 ) ;
   void Produce() ;
   TH1D* RebinHistogram( TH1D* h1, string newHistoName, pair<int, int> cw[] ) ;
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
   string systType ;

   vector<double> normV ;
   vector<double> timeCalib ;
   vector<double> jetCuts ;
   vector<double> photonCuts ;

   vector<objID> selectJets ;
   vector<objID> selectPho ;

   TH1D* h_dataTime  ;
   TH1D* h_dataTimeA  ;
   TH1D* h_dataTimeAll  ;
   TH1D* h_MET       ;
   TH1D* h_bgTime    ;
   TH1D* h_bgTimeA   ;
   TH1D* h_bgMET       ;
   TH1D* h_sgTime    ;
   TH1D* h_sgTimeA    ;
   TH1D* h_sgTimeAll  ;
   TH1D* h_sgMET       ;
   TH1D* h_NJets     ;
   TH1D* h_sgNJets     ;

   TH2D* hBg_A ;
   TH2D* hBg_B ;
   TH2D* hBg_C ;
   TH2D* hBg_D ;

   TH1D* rh_dataTime  ;
   TH1D* rh_dataTimeA  ;
   TH1D* rh_dataTimeAll  ;
   //TH1D* rh_MET       ;
   TH1D* rh_bgTime    ;
   TH1D* rh_bgTimeA   ;
   //TH1D* rh_bgMET       ;
   TH1D* rh_sgTime    ;
   TH1D* rh_sgTimeA    ;
   TH1D* rh_sgTimeAll  ;
   //TH1D* rh_sgMET       ;
   //TH1D* rh_NJets     ;
   //TH1D* rh_sgNJets     ;

   //ClassDef(Output, 1);
};

//#if !defined(__CINT__)
//    ClassImp(Output);
#endif

