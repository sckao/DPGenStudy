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
#include "Tester.h"
#include "GenAna.h"
//#include "mtest.h"

using namespace std; 

int main( int argc, const char* argv[] ) { 

  string datacardfile = ( argc > 1 ) ? argv[1] : "DataCard.txt";
  //AnaInput  *Input = new AnaInput( datacardfile );
  AnaInput  *Input = AnaInput::Instance() ;
  Input->SetDatacard( datacardfile ) ;
  
  // method to read root files
  string dataFileNames ;
  Input->GetParameters( "TheData", &dataFileNames );
  vector<string> mcFileNames ;
  Input->GetParameters( "TheMC",   &mcFileNames );

  int module = -1 ;
  Input->GetParameters( "Module", & module ) ;

  if ( module == 0 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     tgen->ReadTree( dataFileNames );
     delete tgen ;

     //Histogram *histo = new Histogram() ;
     //histo->DrawHistograms();
     //delete histo ;
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
     Histogram *histo = new Histogram() ;
     histo->DrawHistograms();
     delete histo ;
  }
  if ( module == 3 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     //vector<double >normV = Input->NormalizeComponents( datacardfile );

     vector<string> mcIdx ;
     Input->GetParameters( "mcIndex",   &mcIdx );
     
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) { 
         //if ( i!= 4 && i!= 5 && i!= 6 && i!=1 ) continue ;
         tgen->ReadTree( mcFileNames[i], 1., mcIdx[i] );
     }
     delete tgen ;

     //Histogram *histo = new Histogram( ) ;
     //histo->DrawHistograms();
     //delete histo ;
  }
  if ( module == 4 ) {
     Output* out = new Output( datacardfile ) ;
     out->Produce() ;
     delete out ;
  }
  if ( module == 5 ) {
     Output* out = new Output( datacardfile ) ;
     out->ReadHisto() ;
     delete out ;
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
  if ( module == 11 ) {
     Output* out = new Output( datacardfile ) ;
     out->ProduceMC() ;
     delete out ;
  }
  if ( module == 12 ) {
     Output* out = new Output( datacardfile ) ;
     out->ProduceGen() ;
     delete out ;
  }
  if ( module == 7 ||  module == 8 || module == 9  ) {
     
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
  if ( module == 10 ) {
     Systematic* syst  = new Systematic( datacardfile ) ;
     syst->McDataCompare() ;
     delete syst ;
  }
  if ( module == 13 ) {

     GenAna   *genA  = new GenAna( datacardfile ) ;
     genA->ReadTree( dataFileNames );

     /*
     vector<string> mcIdx ;
     Input->GetParameters( "mcIndex",   &mcIdx );
     
     for ( size_t i=0 ; i < mcFileNames.size() ; i++ ) { 
          genA->ReadTree( mcFileNames[i], 1., mcIdx[i] );
     }
     */
     delete genA ;
  }

  if ( module == 20 ) {
     Tester   *tt  = new Tester( datacardfile ) ;
     tt->ReadTree( dataFileNames );
     delete tt ;
  }
  if ( module == 21 ) {
     Tester   *tt  = new Tester( datacardfile ) ;
     tt->PlotOnly();
     delete tt ;
  }


  delete Input ;
  cout<<" Finished !!!"<<endl ;

  return 0;

}

bool badCrystal( double eta , double phi ) {

     bool badSeed = false ; 
     if ( eta > -0.75 && eta < -0.6 && phi > -1.   && phi < -0.8 ) badSeed = true  ;
     if ( eta > 0.80  && eta < 0.95 && phi > -1.95 && phi < -1.8 ) badSeed = true  ;

     return badSeed ;
}
