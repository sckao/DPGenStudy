#include "Rtuple.h"

void setRtupleAddresses(TTree* chain, Rtuple& treeVars) {

  chain -> SetBranchAddress("nJets",       &treeVars.nJets      );
  chain -> SetBranchAddress("nPhotons",    &treeVars.nPhotons   );

  chain -> SetBranchAddress("met",         &treeVars.met       );
  chain -> SetBranchAddress("g1Pt",        &treeVars.g1Pt     );
  chain -> SetBranchAddress("g2Pt",        &treeVars.g2Pt     );
  chain -> SetBranchAddress("g1Time",      &treeVars.g1Time   );
  chain -> SetBranchAddress("g2Time",      &treeVars.g2Time   );
  chain -> SetBranchAddress("bgTime",      &treeVars.bgTime   );

}


void setRtupleBranches(TTree* chain, Rtuple& treeVars) {

  chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nPhotons",    &treeVars.nPhotons,             "nPhotons/I");

  chain -> Branch("met",         &treeVars.met,                  "met/F");
  chain -> Branch("g1Pt",        &treeVars.g1Pt,                 "g1Pt/F");
  chain -> Branch("g2Pt",        &treeVars.g2Pt,                 "g2Pt/F");
  chain -> Branch("g1Time",      &treeVars.g1Time,               "g1Time/F");
  chain -> Branch("g2Time",      &treeVars.g2Time,               "g2Time/F");
  chain -> Branch("bgTime",      &treeVars.bgTime,               "bgTime/F");

}


void initRtuple(TTree* chain, Rtuple& treeVars) {
  
  treeVars.nJets      = 0 ; 
  treeVars.nPhotons   = 0 ; 

  treeVars.met     = 0 ;
  treeVars.g1Pt    = 0 ;
  treeVars.g2Pt    = 0 ;
  treeVars.g1Time  = -25 ;
  treeVars.g2Time  = -25 ;
  treeVars.bgTime  = -25 ;

}
