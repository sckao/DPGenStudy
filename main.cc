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
#include "mtest.h"

using namespace std; 

/*
class BackgroundStudy ;
class mtest ;

void *thread_F1( void *thread_arg ) {

    cout<<" === tread1 :" <<endl ;
    BackgroundStudy* bgS  =  static_cast<BackgroundStudy*>(thread_arg) ;
    bgS->Run() ;

    cout<<" ====================== "<<endl ;
    //pthread_exit(NULL);
    return 0 ;
}

void *thread_F2( void *thread_arg ) {

    cout<<" *** tread2 :" <<endl ;
    string datacardfile  = *( static_cast<string*>(thread_arg) );
   
    TThread::Lock() ;
    mtest *mt = new mtest( datacardfile ) ;
    mt->init() ;

    mt->RunData();
    TThread::UnLock() ;

    cout<<" ********************** "<<endl ;
    //pthread_exit(NULL);
    return 0 ;
}

void *thread_F3( void *thread_arg ) {

    cout<<" *** tread3 :" <<endl ;
    for ( int i=0 ; i < 35 ; i++) {
        sleep(3) ;
        cout<<"   ( "<<i*3 <<" ) " <<endl ;
    }
    cout<<" ********************** "<<endl ;
    //pthread_exit(NULL);
    return 0 ;
    
}

void *thread_Func1( void *thread_arg ) {

    string datacardfile  = *( static_cast<string*>(thread_arg) );

    cout<<" === tread1 :" << datacardfile <<endl ;

    BackgroundStudy *bgS  = new BackgroundStudy( datacardfile ) ;
    bgS->Run() ;

    cout<<" ====================== "<<endl ;
    //pthread_exit(NULL);
    return 0 ;
}

void *thread_Func2( void *thread_arg ) {

    string datacardfile  = *( static_cast<string*>(thread_arg) );

    cout<<" *** tread2 :" << datacardfile <<endl ;

    TestGen   *tgen  = new TestGen( datacardfile ) ;
    tgen->ReadTree();

    cout<<" ********************** "<<endl ;
    //pthread_exit(NULL);
    return 0 ;
}
*/

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
  }
  if ( module == 1 ) {
     Trigger   *trg   = new Trigger( datacardfile ) ;
     trg->ReadTree( dataFileNames);
     delete trg ;
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
     Background * bg = new Background( datacardfile ) ;
     bg->RunEstimation( dataFileNames ) ;
     //bg->SpikeShape() ;
     delete bg ;
  }
  if ( module == 7 ||  module == 8 || module == 9 ) {
     
     BackgroundStudy * bgS = new BackgroundStudy( datacardfile ) ;
     if ( module == 7 ) {
        bgS->Create() ;
        bgS->init() ;
        bgS->Run() ;
        bgS->DrawHistograms() ;
     } 
     if ( module == 8 ) {
        vector<double >normV = Input->NormalizeComponents( datacardfile );
        bgS->Create() ;
        for ( size_t i = 0 ; i < mcFileNames.size() ; i++ ) { 
            cout<<" Runing MC : "<< mcFileNames[i] << endl ;
            bgS->init( mcFileNames[i] ) ;
            bgS->Run( normV[i] ) ;
        } 
        bgS->DrawHistograms() ;
     } 
     if ( module == 9 ) {
     //if ( isData == 0 ) bgS->Run( mcFileNames[0] ) ;
         bgS->Open() ;
         bgS->DrawHistograms() ;
     }

     delete bgS ;
  }

  /*
  if ( module == 8 ) {
     pthread_t t1, t2 ; // declare 2 threads.

     string mcDataCard = "DataCard1.txt" ;

     pthread_create( &t1, NULL, thread_F2 ,  static_cast<void*>(&datacardfile) ); // create a thread running function1
     pthread_create( &t2, NULL, thread_F2 ,  static_cast<void*>(&mcDataCard) ); // create a thread running function1
     //pthread_create( &t2, NULL, &tgen->ReadTree( dataFileNames) ,NULL);
     pthread_join( t1, NULL ) ;
     pthread_join( t2, NULL ) ;

  }

  if ( module == 9 ) {
     pthread_t t1, t2 ; // declare 2 threads.

     string mcDataCard = "DataCard1.txt" ;
     //BackgroundStudy * bgS1 = new BackgroundStudy( datacardfile ) ;
     //bgS1->init() ;
     mtest           * mt   = new mtest( datacardfile ) ;
     mt->init() ;
     mtest           * mt2   = new mtest( mcDataCard ) ;
     mt2->init() ;
     //BackgroundStudy * bgS2 = new BackgroundStudy( mcDataCard ) ;

     //pthread_create( &t1, NULL, thread_F1 ,  static_cast<void*>(bgS1) ); // create a thread running function1
     pthread_create( &t1, NULL, thread_F2 ,  static_cast<void*>(mt2) ); // create a thread running function1
     //pthread_create( &t2, NULL, thread_F2 ,  static_cast<void*>(bgS2) ); // create a thread running function1
     pthread_create( &t2, NULL, thread_F2 ,  static_cast<void*>(mt) ); // create a thread running function1
     //pthread_create( &t2, NULL, &tgen->ReadTree( dataFileNames) ,NULL);
     pthread_join( t1, NULL ) ;
     pthread_join( t2, NULL ) ;

  }
  */

  cout<<" Finished !!!"<<endl ;
  //for ( size_t i =0 ; i< dataFileNames.size(); i++ ) {
  //    tgen->ReadTree( dataFileNames[i] );
  //} 

  //delete Input ;

  return 0;

}


