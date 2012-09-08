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

#include "AnaInput.h"
#include "TestGen.h"
#include "Trigger.h"
#include "Histogram.h"
#include "Background.h"

using namespace std; 

int main( int argc, const char* argv[] ) { 

  string datacardfile = ( argc > 1 ) ? argv[1] : "DataCard.txt";
  AnaInput  *Input = new AnaInput( datacardfile );

  // method to read root files
  Input->LinkForests("DPAnalysis");
  string dataFileNames ;
  Input->GetParameters( "TheData", &dataFileNames );

  int module = -1 ;
  Input->GetParameters( "Module", & module ) ;

  if ( module == 0 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     tgen->ReadTree( dataFileNames);
     delete tgen ;
  }
  if ( module == 1 ) {
     Trigger   *trg   = new Trigger( datacardfile ) ;
     trg->ReadTree( dataFileNames);
     delete trg ;
  }
  if ( module == 2 ) {
     TestGen   *tgen  = new TestGen( datacardfile ) ;
     tgen->ReadTree( dataFileNames);
     delete tgen ;

     Histogram *histo = new Histogram( datacardfile ) ;
     histo->DrawHistograms();
     delete histo ;
  }
  if ( module == 3 ) {
     Background * bg = new Background( datacardfile ) ;
     bg->SpikeShape() ;
     delete bg ;
  }

  cout<<" finished "<<endl ;
  //for ( size_t i =0 ; i< dataFileNames.size(); i++ ) {
  //    tgen->ReadTree( dataFileNames[i] );
  //} 

  //delete histo ;
  delete Input ;

  return 0;

}


