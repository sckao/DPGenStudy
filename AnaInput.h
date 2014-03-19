#ifndef AnaInput_H
#define AnaInput_H

#include "TObject.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <TMath.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TString.h>
#include <TSystem.h>
#include <TLorentzVector.h>
//#include "WFormat.h"

//#define MAXPHO 10
//#define MAXVTX 10
/*
#define MAXPHO 12
#define MAXVTX 30
#define MAXJET 15
#define MAXMU 5
#define MAXELE 5
#define MAXGEN 20
*/

using namespace std;
typedef pair<int, TLorentzVector> objID ;

// some definitions of global functions
bool badCrystal( double eta, double phi ) ;

class AnaInput : public TObject {

public:

   AnaInput( string datacardInput = "DataCard.txt" );     
   ~AnaInput();     

   void LinkForests( TString treeName ) ;

   void GetForest( string DataSet, TString treeName );

   TTree* TreeMap( string fileName ) ;

   TTree* GetTree( string fName, TString treeName, TFile* file = NULL );

   vector<double> NormalizeComponents( string cfgFile = "" );
   
   void GetParameters( string paraName, int* thePara, string cfgFile = "" );
   void GetParameters( string paraName, double* thePara, string cfgFile ="" );
   void GetParameters( string paraName, string* thePara, string cfgFile ="" );
   void GetParameters( string paraName, vector<double>* thePara, string cfgFile = "" );
   void GetParameters( string paraName, vector<string>* thePara, string cfgFile = "" );
   void GetParameters( string paraName, vector<int>* thePara, string cfgFile = "" );

private:

   string datacardfile ;

   vector<TTree*> forestData ;
   vector<TTree*> forestMC ;


   //ClassDef(AnaInput, 1);

};

//#if !defined(__CINT__)
//    ClassImp(AnaInput);

#endif

