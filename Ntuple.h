#ifndef Ntuple_h
#define Ntuple_h

#include "TChain.h" 

#define MAXJET 10
#define MAXPHO 5
#define MAXOBJ 5

struct Ntuple
{
  
  unsigned int eventId;
  
  /*
  int   nJets ;
  float jetPx[MAXJET];
  float jetPy[MAXJET];
  float jetPz[MAXJET];
  float jetE[MAXJET];
  */

  int   nPhotons ;
  float phoPx[MAXPHO];
  float phoPy[MAXPHO];
  float phoPz[MAXPHO];
  float phoE[MAXPHO];
  float phoVx[MAXPHO];
  float phoVy[MAXPHO];
  float phoVz[MAXPHO];
  float sTime[MAXPHO];
  float phoMother[MAXPHO];

  int   nNeu ;
  float neuPx[MAXOBJ];
  float neuPy[MAXOBJ];
  float neuPz[MAXOBJ];
  float neuE[MAXOBJ];
  float neuM[MAXOBJ];
  float neuGamma[MAXOBJ] ;
  float neuctau[MAXOBJ] ;

};



//typedef Ntuple EcalTimeTreeContent;


// ------------------------------------------------------------------------
//! branch addresses settings
void setBranchAddresses(TTree* chain, Ntuple& treeVars);
//! create branches for a tree
void setBranches(TTree* chain, Ntuple& treeVars);
//! initialize branches
void initializeBranches(TTree* chain, Ntuple& treeVars);

#endif
