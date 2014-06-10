#include "TFileMerger.h"

void hMerge( TString outName ) {

 //std::vector<TString> fNameV = { "timehisto_1", "timehisto_2" } ;
 std::vector<TString> fNameV ;
 fNameV.push_back( "timehisto_1" ) ;
 fNameV.push_back( "timehisto_2" ) ;

 TString path = "Results/" ;
 TString mergeName = path + outName+".root" ; 

 TFileMerger *fileMerger = new TFileMerger();

 // Loop all files to be merged 
 for ( size_t i=0 ; i < fNameV.size(); i++) {

     TString subfile = path + fNameV[i] + ".root" ;
     cout<<"  Merge file"<<i<<" "<< subfile <<endl;
     fileMerger->AddFile(subfile);	
 }
 
 fileMerger->OutputFile(mergeName);
 bool work = fileMerger->Merge();

 //TDCacheFile* dcFile = new TDCacheFile( mergeName_a.c_str(), "RECREATE" ) ;
 //dcFile->SaveAs( mergeName ) ;

 if (work) {
    cout<<"  *** Merge Successful *** " <<endl;
 } else {
    cout<<"  !!! Fuck ! Merge Fail !!! " <<endl;
 }

}

