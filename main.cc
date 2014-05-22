#include <iostream> 
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <TString.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TMinuit.h>

//#include <pthread.h>
//#include <unistd.h>
//#include "TThread.h"

#include "AnaInput.h"
#include "TestGen.h"
#include "Trigger.h"
#include "Histogram.h"
#include "Background.h"
#include "BackgroundStudy.h"
#include "Systematic.h"
#include "Output.h"
//#include "mtest.h"

using namespace std; 

int main( int argc, const char* argv[] ) { 

  string datacardfile = ( argc > 1 ) ? argv[1] : "DataCard.txt";
  AnaInput  *Input = new AnaInput( datacardfile );

  // method to read root files
  string dataFileNames ;
  Input->GetParameters( "TheData", &dataFileNames );
  vector<string> mcFileNames ;
  Input->GetParameters( "TheMC",   &mcFileNames );

  int module = -1 ;
  Input->GetParameters( "Module", & module ) ;

  if ( module == 0 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     tgen->ReadTree( dataFileNames);
     delete tgen ;

     Histogram *histo = new Histogram( datacardfile ) ;
     histo->DrawHistograms();
     delete histo ;
  }
  if ( module == 1 ) {
     Trigger   *trg   = new Trigger( datacardfile ) ;
     trg->ReadTree( dataFileNames);
     trg->Plot() ;
     delete trg ;
     //trg->EventList( dataFileNames ) ;
     //trg->CutFlow( dataFileNames ) ;
  }
  if ( module == 2 ) {
     Histogram *histo = new Histogram( datacardfile ) ;
     histo->DrawHistograms();
     delete histo ;
  }
  if ( module == 3 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     vector<double >normV = Input->NormalizeComponents( datacardfile );

     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) { 
         tgen->ReadTree( mcFileNames[i] , normV[i] );
     }
     delete tgen ;

     Histogram *histo = new Histogram( datacardfile ) ;
     histo->DrawHistograms();
     delete histo ;
  }
  if ( module == 4 ) {

     Output* out = new Output( datacardfile ) ;
     out->Produce() ;

     delete out ;
  }
  if ( module == 5 ) {
     Systematic* syst  = new Systematic( datacardfile ) ;
     syst->McDataCompare() ;
     delete syst ;
  }
  if ( module == 6 ) {
     //Background * bg = new Background( datacardfile ) ;
     //bg->RunEstimation( dataFileNames ) ;
     //bg->SpikeShape() ;
     //delete bg ;
     Trigger   *trg   = new Trigger( datacardfile ) ;
     trg->HistoOpen( );
     trg->Plot() ;
     delete trg ;
  }
  if ( module == 7 ||  module == 8 || module == 9 || module == 10 ) {
     
     BackgroundStudy * bgS = new BackgroundStudy( datacardfile ) ;
     if ( module == 7 ) {
        bgS->CreateHistograms() ;
        bgS->SimpleRun() ;
        bgS->WriteDrawHistograms() ;
     }
      
     if ( module == 8 ) {
        vector<double >normV = Input->NormalizeComponents( datacardfile );
        bgS->CreateHistograms() ;
        for ( size_t i = 0 ; i < mcFileNames.size() ; i++ ) { 
            cout<<" Runing MC : "<< mcFileNames[i] << endl ;
            bgS->SimpleRun( mcFileNames[i], normV[i] ) ;
            //bgS->Run( normV[i] ) ;
        } 
        bgS->WriteDrawHistograms() ;
     } 
     

     if ( module == 9 ) {
     //if ( isData == 0 ) bgS->Run( mcFileNames[0] ) ;
         bgS->OpenAllHistograms() ;
         bgS->DrawAllHistograms() ;
     }

     delete bgS ;
  }

  cout<<" Finished !!!"<<endl ;

  return 0;

}

bool badCrystal( double eta , double phi ) {

     bool badSeed = false ; 
     if ( eta > -0.75 && eta < -0.6 && phi > -1.   && phi < -0.8 ) badSeed = true  ;
     if ( eta > 0.80  && eta < 0.95 && phi > -1.95 && phi < -1.8 ) badSeed = true  ;

     return badSeed ;
}
