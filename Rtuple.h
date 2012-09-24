#ifndef Rtuple_h
#define Rtuple_h

#include "TChain.h" 

struct Rtuple {

  int   nJets ;
  int   nPhotons ;

  float met;

  float g1Time;
  float g1Pt ;
  float g2Time;
  float g2Pt ;
  float bgTime ;

};

// ------------------------------------------------------------------------
//! branch addresses settings
void setRtupleAddresses(TTree* chain, Rtuple& treeVars);

//! create branches for a tree
void setRtupleBranches(TTree* chain, Rtuple& treeVars);

//! initialize branches
void initRtuple(TTree* chain, Rtuple& treeVars);



#endif
