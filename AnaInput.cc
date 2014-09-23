#include "AnaInput.h"

AnaInput* AnaInput::m_Instance = NULL ;

//AnaInput::AnaInput( string datacardInput ) {
AnaInput::AnaInput() {

  datacardfile = "DataCard.txt" ;

}

AnaInput::~AnaInput(){

   cout<<" close input "<<endl ;

}

AnaInput* AnaInput::Instance() {

    if (! m_Instance ) {
       m_Instance = new AnaInput( ) ;
    } 
       
    return m_Instance ;

}

void AnaInput::SetDatacard( string datacardInput ) {
 
     datacardfile = datacardInput ;
}

//vector<TTree*> forestData ;
//vector<TTree*> forestMC ;
void AnaInput::LinkForests( TString treeName ){

  cout<<" Linking all trees !!!"<<endl;

  vector<string> fNamesData ;
  GetParameters( "TheData", &fNamesData );
  for ( size_t i =0 ; i< fNamesData.size(); i++ ) {
      TTree* tr = GetTree( fNamesData[i], treeName ) ;
      forestData.push_back( tr );
  }

  vector<string> fNamesMC ;
  GetParameters( "TheMC", &fNamesMC );
  for ( size_t i =0 ; i< fNamesMC.size(); i++ ) {
      TTree* tr = GetTree( fNamesMC[i], treeName ) ;
      forestMC.push_back( tr );
  }

}

// GetForest , run first
void AnaInput::GetForest( string DataSet, TString treeName ) {

    cout<<"  =>>> getting a forest of "<< treeName <<endl ;
    vector<string> fileList;
    GetParameters( DataSet , &fileList );

    vector<TTree*> forest ;
    for ( size_t i =0 ; i< fileList.size(); i++ ) {
        TTree* tr = GetTree( fileList[i], treeName ) ;
        forestData.push_back( tr );
    }
}

TTree* AnaInput::TreeMap( string fileName ) {

    vector<string> f0Names ;
    GetParameters( "TheData", &f0Names );
    vector<string> f1Names ;
    GetParameters( "TheMC", &f1Names );

    TTree* theTr = 0;
    for ( size_t i=0; i< f0Names.size(); i++ ) {
        if ( f0Names[i] == fileName ) theTr = forestData[i] ;
    }
    for ( size_t i=0; i< f1Names.size(); i++ ) {
        if ( f1Names[i] == fileName ) theTr = forestMC[i] ;
    }


    return theTr ;
}

// get the tree from a specific file(s)
TTree* AnaInput::GetTree( string fName, TString treeName, TFile* file  ) {
  
  TTree* tr = 0;

  string filePath ;
  GetParameters( "RootFiles", &filePath );

  TString theFileName ;
  TChain* theChain = new TChain( treeName ) ;

  if ( fName[ fName.size()-1 ] == '+'  ) {
     string ChainName = fName.substr( 0, fName.size()-1 ) + "Chain"  ;
     vector<string> chainlist;
     GetParameters( ChainName, &chainlist );
     cout<<" * fileName+ = "<< ChainName <<endl;
     for ( size_t j=0; j< chainlist.size(); j++) {
         theFileName = filePath + chainlist[j]+".root" ;
         //cout<<" ** fileName = "<< theFileName <<endl;
         theChain->Add( theFileName );
     }
  } else {
    theFileName = filePath + fName+".root" ;
    cout<<" * fileName = "<< theFileName <<endl;
    theChain->Add( theFileName );
    //if ( file == NULL ) file = TFile::Open( theFileName );
    //tr = (TTree*) file->Get( treeName );

  }
  tr = theChain ;

  return tr ;
}


vector<double> AnaInput::NormalizeComponents( string cfgFile ){

  if ( cfgFile == "" ) cfgFile = datacardfile ;

  double lumi ;
  GetParameters("Lumi", &lumi, cfgFile );

  vector<double> nEvents ;
  GetParameters( "NEvents" , &nEvents, cfgFile );
  vector<double> xsec;
  GetParameters("XSection", &xsec, cfgFile );
  vector<double> Eff;
  GetParameters("Eff", &Eff, cfgFile )  ;

  vector<double> nSkim;
  GetParameters("NSkim", &nSkim, cfgFile )  ;

  vector<double> normV ;
  for ( size_t i=0; i < xsec.size(); i++ ) {

     double skimEff = ( nSkim.size() > 0 ) ? nSkim[i]/nEvents[i] : 1. ;
     double nBase = xsec[i]*Eff[i]*skimEff ;
     double Scal = (nBase*lumi) / nEvents[i] ;
     //printf(" N: %.1f , X: %.1f , Eff: %.1f , NSkim: %.1f = Scal : %.4f \n", nEvents[i], xsec[i], Eff[i], nSkim[i], Scal ) ;
     printf(" N: %.1f , X: %.1f , Eff: %.1f  = Scale : %.4f \n", nEvents[i], xsec[i], Eff[i],  Scal ) ;
     //cout<<" Normalization =  "<< Scal << endl;
     normV.push_back( Scal ) ;
  } 

  if ( normV.size() < 1) normV.push_back( 1. ) ;

  return normV ;
}

// Methods to read DataCard.txt
void AnaInput::GetParameters(string paraName, int* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );
     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     string  getValue;
     size_t  pos ;
     size_t  vpos ;

     bool gotIt = false ;
     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() + 2;
           if ( pos < line.npos ) {
              string str_end = line.substr(vpos-1, 1) ;
              if ( str_end == ' ' || str_end == '=') {
                 getName  = line.substr( pos, paraName.size() );
                 getValue = line.substr( vpos );
                 *thePara = atoi( getValue.c_str() );
                 //cout<< paraName <<" = "<< *thePara << endl;
                 gotIt = true;
              }
           }
           if ( gotIt ) break ;
     }
     paraFile.close();
}

void AnaInput::GetParameters(string paraName, double* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );
     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     string  getValue;
     size_t  pos ;
     size_t  vpos ;

     bool gotIt = false ;
     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() + 2;
           if ( pos < line.npos ) {
              string str_end = line.substr(vpos-1, 1) ;
              if ( str_end == ' ' || str_end == '=') {
                 getName  = line.substr( pos, paraName.size() );
                 getValue = line.substr( vpos );
                 *thePara = atof( getValue.c_str() );
                 //cout<< paraName <<" = "<< *thePara << endl;
                 gotIt = true ;
              }
           }
           if ( gotIt ) break ;
     }
     paraFile.close();
}

void AnaInput::GetParameters(string paraName, string* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );
     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     size_t  pos ;
     size_t  vpos ;

     bool gotIt = false ;
     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() + 2;

           if ( pos < line.npos ) {
              string str_end = line.substr(vpos-1, 1) ;
              if ( str_end == ' ' || str_end == '=') {
                 //cout<<" pos = "<< pos <<endl;
                 getName  = line.substr( pos, paraName.size() );
                 //*thePara = line.substr( vpos );
                 //cout<< paraName <<" = "<< *thePara << endl;
                 string strTmp = line.substr( vpos );
                 for (string::iterator it = strTmp.begin(); it< strTmp.end(); it++) {
                     if ( (*it) != ',' && (*it) != ' ' && (*it) != '(' && (*it) != ')' && (*it) != '=') thePara->push_back( *it );
                 }
                 gotIt = true ;
              }
           }
           if ( gotIt ) break;
     }
     paraFile.close();
}

void AnaInput::GetParameters(string paraName, vector<double>* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );
     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     string  getValue;
     size_t  pos ;
     size_t  vpos ;
     vector<double>  vvec;

     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() + 1;
           if ( pos < line.npos ) {
              getName  = line.substr( pos, paraName.size() );
              string arrVal = line.substr( vpos );
              if ( arrVal[0] != '=' && arrVal[0] != ' ' ) continue;
	      int vidx = 0;
	      string vtemp ;
	      //cout<< paraName <<" = ( " ;
              for (string::iterator it = arrVal.begin(); it< arrVal.end(); it++) {
                  if ( (*it) != ',' && (*it) != ' ' && (*it) != '(' && (*it) != ')' && (*it) != '=') vtemp.push_back( *it );
                  if ( (*it) == ',' || (*it) == ')' ) { 
                     if ( vtemp.size() > 0 ) vvec.push_back( atof( vtemp.c_str() ) ) ;
		     //cout<< vtemp << *it;
		     vidx++ ;
		     vtemp.clear() ;
                  }
              }
              *thePara = vvec ;
           }
     }
     paraFile.close();

} 

void AnaInput::GetParameters(string paraName, vector<string>* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );

     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     string  getValue;
     size_t  pos ;
     size_t  vpos ;
     vector<string>  vvec;

     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() ;
           if ( pos < line.npos ) {
              getName  = line.substr( pos, paraName.size() );
              string arrVal = line.substr( vpos );
              if ( arrVal[0] != '=' && arrVal[0] != ' ' ) continue;
	      int vidx = 0;
	      string vtemp ;
	      //cout<< paraName <<" = ( " ;
              for (string::iterator it = arrVal.begin(); it< arrVal.end(); it++) {
                  if ( (*it) != ',' && (*it) != ' ' && (*it) != '(' && (*it) != ')' && (*it) != '=') vtemp.push_back( *it );
                  if ( (*it) == ',' || (*it) == ')' ) { 
                     if ( vtemp.size() > 0 ) vvec.push_back( vtemp ) ;
		     //cout<< vtemp << *it;
		     vidx++ ;
		     vtemp.clear() ;
                  }
              }
              *thePara = vvec ;
           }
     }
     paraFile.close();

}
 
void AnaInput::GetParameters(string paraName, vector<int>* thePara, string cfgFile ){

     if ( cfgFile == "" ) cfgFile = datacardfile ;

     fstream paraFile( cfgFile.c_str() );
     if ( !paraFile.is_open() )  cout<<" file opened error => check file path and the folder "<<endl;
     string  line;
     string  getName;
     string  getValue;
     size_t  pos ;
     size_t  vpos ;
     vector<int>  vvec;

     while ( getline(paraFile, line) ) {
           if ( line[0] == '#' ) continue ;

           pos = line.find( paraName );
           vpos = pos + paraName.size() ;
           if ( pos < line.npos ) {
              getName  = line.substr( pos, paraName.size() );
              string arrVal = line.substr( vpos );
              if ( arrVal[0] != '=' && arrVal[0] != ' ' ) continue;
	      //int vidx = 0;
	      string vtemp ;
	      //cout<< paraName <<" = ( " ;
              for (string::iterator it = arrVal.begin(); it< arrVal.end(); it++) {
                  if ( (*it) != ',' && (*it) != ' ' && (*it) != '(' && (*it) != ')' && (*it) != '=') vtemp.push_back( *it );
                  if ( (*it) == ',' || (*it) == ')' ) { 
                     if ( vtemp.size() > 0 ) vvec.push_back( atoi( vtemp.c_str() ) ) ;
		     //cout<< vtemp << *it;
		     //vidx++ ;
		     vtemp.clear() ;
                  }
              }
              *thePara = vvec ;
           }
     }
     paraFile.close();

}

 
// Weighting for GEN-SIM format of GMSB Signal MC , pt is neutralino's pt, ct is its lifetime in the rest frame.
// pt bin is 25 GeV (from 0 ~ 500 GeV), ct bin is 200 mm ( 0 ~ 4000 mm)
// error = 0 : nominal 1: nominal+upward 2: nominal+downward 
double AnaInput::RecoWeight( double pT, double ct, int error  ) {

     int x = ( pT/25)  ;
     if ( x > 14 ) x = 14 ;
     int y = ( ct/200)  ;
     if ( y > 19 ) y = 19 ;
     int k = (y*15) + x ;

     double effA[300] = {
/*
 0.00831, 0.00117, 0.00007, 0.00012, 0.00005, 0.00000, 0.00005, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07426, 0.03268, 0.00842, 0.00331, 0.00117, 0.00123, 0.00124, 0.00000, 0.00057, 0.00021, 0.00023, 0.00134, 0.00000, 0.00000, 0.00000,
 0.06857, 0.06182, 0.03646, 0.01684, 0.00759, 0.00296, 0.00402, 0.00249, 0.00171, 0.00071, 0.00000, 0.00186, 0.00056, 0.00000, 0.00000,
 0.08642, 0.11157, 0.07107, 0.04533, 0.03301, 0.02243, 0.00923, 0.00373, 0.00660, 0.00369, 0.00407, 0.00487, 0.00180, 0.00000, 0.00256,
 0.15094, 0.12013, 0.10615, 0.08749, 0.04750, 0.04146, 0.01658, 0.01162, 0.01139, 0.00780, 0.00443, 0.00681, 0.00276, 0.00000, 0.00000,
 0.20513, 0.12346, 0.15984, 0.15035, 0.11660, 0.08622, 0.04307, 0.01515, 0.01089, 0.00582, 0.00138, 0.00181, 0.00000, 0.00000, 0.00000,
 0.17857, 0.17857, 0.16817, 0.19471, 0.14665, 0.10345, 0.06901, 0.03954, 0.01173, 0.00179, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20000, 0.14400, 0.15884, 0.16745, 0.18861, 0.14015, 0.10462, 0.04263, 0.01087, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.16667, 0.15455, 0.10599, 0.14198, 0.17063, 0.14286, 0.11158, 0.04658, 0.00429, 0.01754, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.10526, 0.19355, 0.13125, 0.14610, 0.20117, 0.16867, 0.11816, 0.05025, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.23077, 0.15556, 0.21212, 0.15909, 0.17407, 0.17176, 0.16749, 0.07792, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.06667, 0.24390, 0.19835, 0.14368, 0.11538, 0.11834, 0.08271, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.20930, 0.13043, 0.12057, 0.09655, 0.07576, 0.09375, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.21875, 0.21687, 0.16541, 0.12687, 0.07317, 0.50000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.30769, 0.12903, 0.12963, 0.06173, 0.05882, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.22222, 0.10417, 0.08696, 0.12698, 0.28571, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.07143, 0.12500, 0.12727, 0.12500, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.06250, 0.20513, 0.08108, 0.14286, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.25000, 0.33333, 0.16216, 0.02778, 0.20000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.10000, 0.11034, 0.13158, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000
*/

 0.00805, 0.00149, 0.00007, 0.00006, 0.00011, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07426, 0.03624, 0.01213, 0.00519, 0.00155, 0.00123, 0.00107, 0.00000, 0.00057, 0.00021, 0.00023, 0.00107, 0.00000, 0.00000, 0.00000,
 0.06286, 0.06182, 0.03960, 0.01684, 0.00831, 0.00461, 0.00278, 0.00343, 0.00136, 0.00106, 0.00000, 0.00186, 0.00113, 0.00000, 0.00000,
 0.08642, 0.10744, 0.07513, 0.04887, 0.03073, 0.02094, 0.00777, 0.00513, 0.00710, 0.00474, 0.00465, 0.00557, 0.00180, 0.00000, 0.00256,
 0.15094, 0.12662, 0.12000, 0.09257, 0.06083, 0.04646, 0.01339, 0.01420, 0.01206, 0.00546, 0.00443, 0.00568, 0.00276, 0.00000, 0.00000,
 0.20513, 0.13580, 0.17213, 0.15177, 0.12605, 0.08529, 0.04651, 0.01684, 0.01188, 0.00466, 0.00138, 0.00181, 0.00000, 0.00000, 0.00000,
 0.17857, 0.17857, 0.16817, 0.19471, 0.14385, 0.10226, 0.06780, 0.04337, 0.01173, 0.00358, 0.00263, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20000, 0.14400, 0.15884, 0.16745, 0.19217, 0.14453, 0.09846, 0.05151, 0.02391, 0.00333, 0.01010, 0.00000, 0.00000, 0.00000, 0.00000,
 0.16667, 0.15455, 0.10599, 0.13580, 0.17279, 0.15584, 0.12000, 0.06575, 0.04721, 0.01754, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.10526, 0.19355, 0.13125, 0.14610, 0.20117, 0.16867, 0.12680, 0.07538, 0.04000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.23077, 0.15556, 0.21212, 0.15909, 0.17407, 0.17176, 0.16749, 0.07792, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.06667, 0.24390, 0.19835, 0.14368, 0.11538, 0.11834, 0.08271, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.20930, 0.13043, 0.12057, 0.09655, 0.07576, 0.09375, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.21875, 0.21687, 0.16541, 0.12687, 0.07317, 0.50000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.30769, 0.12903, 0.12963, 0.06173, 0.05882, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.22222, 0.10417, 0.08696, 0.12698, 0.28571, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.07143, 0.12500, 0.12727, 0.12500, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.06250, 0.20513, 0.08108, 0.14286, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.25000, 0.33333, 0.16216, 0.02778, 0.20000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.10000, 0.11034, 0.13158, 0.25000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000

     } ;

     double err_u[300] = {
 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.01400, 0.00500, 0.00200, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.02000, 0.00800, 0.00500, 0.00300, 0.00200, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100, 0.00100, 0.00000, 0.00000,
 0.03400, 0.01400, 0.00800, 0.00600, 0.00400, 0.00300, 0.00200, 0.00200, 0.00200, 0.00200, 0.00200, 0.00200, 0.00100, 0.00000, 0.00200,
 0.05300, 0.01900, 0.01300, 0.00900, 0.00700, 0.00600, 0.00300, 0.00300, 0.00300, 0.00200, 0.00200, 0.00300, 0.00200, 0.00100, 0.00200,
 0.06800, 0.02200, 0.01700, 0.01400, 0.01100, 0.00900, 0.00600, 0.00400, 0.00300, 0.00200, 0.00200, 0.00200, 0.00200, 0.00400, 0.01100,
 0.07800, 0.03000, 0.02100, 0.01700, 0.01300, 0.01000, 0.00900, 0.00700, 0.00400, 0.00300, 0.00300, 0.00400, 0.01500, 0.20400, 0.00000,
 0.09500, 0.03300, 0.02200, 0.01800, 0.01700, 0.01300, 0.01200, 0.00900, 0.00800, 0.00400, 0.01400, 0.11800, 0.00000, 0.00000, 0.00000,
 0.08300, 0.03600, 0.02200, 0.02000, 0.01800, 0.01700, 0.01500, 0.01300, 0.01500, 0.02400, 0.21200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.08300, 0.05300, 0.02800, 0.02100, 0.02200, 0.02100, 0.01800, 0.02000, 0.03500, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.12200, 0.05800, 0.03600, 0.02500, 0.02400, 0.02400, 0.02700, 0.03400, 0.31700, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.08400, 0.06900, 0.03800, 0.02800, 0.02200, 0.02600, 0.02500, 0.15600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.09800, 0.06500, 0.03700, 0.02900, 0.02600, 0.02500, 0.05900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.11800, 0.07600, 0.04700, 0.03400, 0.03000, 0.03200, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.15000, 0.09200, 0.04600, 0.03400, 0.03000, 0.05000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.31700, 0.08400, 0.04900, 0.04700, 0.04500, 0.16800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20400, 0.09000, 0.05200, 0.04900, 0.04800, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.20400, 0.08000, 0.06800, 0.05200, 0.15300, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.21200, 0.18200, 0.06500, 0.03800, 0.18900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07700, 0.03600, 0.02700, 0.04200, 0.21200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000

     } ;

     double err_d[300] = {
 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.01200, 0.00400, 0.00200, 0.00100, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.01600, 0.00800, 0.00400, 0.00200, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100, 0.00100, 0.00000, 0.00000,
 0.02800, 0.01400, 0.00800, 0.00500, 0.00400, 0.00300, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00100, 0.00000, 0.00100,
 0.04400, 0.01800, 0.01200, 0.00900, 0.00600, 0.00500, 0.00200, 0.00300, 0.00200, 0.00200, 0.00200, 0.00200, 0.00200, 0.00000, 0.00000,
 0.05800, 0.02100, 0.01700, 0.01300, 0.01000, 0.00800, 0.00600, 0.00300, 0.00300, 0.00200, 0.00100, 0.00100, 0.00000, 0.00000, 0.00000,
 0.06300, 0.02800, 0.01900, 0.01700, 0.01300, 0.01000, 0.00800, 0.00700, 0.00400, 0.00200, 0.00200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.07700, 0.02900, 0.02100, 0.01800, 0.01600, 0.01300, 0.01100, 0.00900, 0.00600, 0.00300, 0.00800, 0.00000, 0.00000, 0.00000, 0.00000,
 0.06500, 0.03200, 0.01900, 0.01800, 0.01700, 0.01600, 0.01400, 0.01200, 0.01200, 0.01300, 0.15200, 0.00000, 0.00000, 0.00000, 0.00000,
 0.05600, 0.04600, 0.02500, 0.01900, 0.02100, 0.02000, 0.01700, 0.01700, 0.02200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.09800, 0.04800, 0.03400, 0.02400, 0.02200, 0.02200, 0.02500, 0.02700, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.04700, 0.06200, 0.03400, 0.02500, 0.01900, 0.02300, 0.02200, 0.12200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.05600, 0.03200, 0.02500, 0.02300, 0.02100, 0.04300, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.06600, 0.04200, 0.03000, 0.02700, 0.02500, 0.24800, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.08300, 0.03800, 0.03000, 0.02300, 0.03200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.07100, 0.03800, 0.03600, 0.03800, 0.13600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.05000, 0.04200, 0.04000, 0.03900, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.04400, 0.05800, 0.03700, 0.09400, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.15200, 0.15300, 0.05400, 0.02000, 0.12600, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000,
 0.00000, 0.03000, 0.02400, 0.03500, 0.15200, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000
     } ;

     double weight = effA[k] ;
     if ( error == 1 ) weight += err_u[k] ; // upward fluctuation 
     if ( error == 2 ) weight -= err_d[k] ; // downward fluctuation 
     if ( weight < 0.  ) weight = 0. ;

     return weight ;
}
