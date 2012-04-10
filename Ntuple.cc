#include "Ntuple.h"

void setBranches(TTree* chain, Ntuple& treeVars) {

  chain -> Branch("eventId",       &treeVars.eventId,            "eventId/i");
  
  //chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nPhotons",    &treeVars.nPhotons,             "nPhotons/I");
  chain -> Branch("nNeu",        &treeVars.nNeu,                 "nNeu/I");
  /*
  chain -> Branch("jetPx",        treeVars.jetPx,                 "jetPx[nJets]/F");
  chain -> Branch("jetPy",        treeVars.jetPy,                 "jetPy[nJets]/F");
  chain -> Branch("jetPz",        treeVars.jetPz,                 "jetPz[nJets]/F");
  chain -> Branch("jetE",         treeVars.jetE,                  "jetE[nJets]/F");
   */
  chain -> Branch("phoPx",        treeVars.phoPx,                 "phoPx[nPhotons]/F");
  chain -> Branch("phoPy",        treeVars.phoPy,                 "phoPy[nPhotons]/F");
  chain -> Branch("phoPz",        treeVars.phoPz,                 "phoPz[nPhotons]/F");
  chain -> Branch("phoE",         treeVars.phoE,                  "phoE[nPhotons]/F");
  chain -> Branch("phoVx",        treeVars.phoVx,                 "phoVx[nPhotons]/F");
  chain -> Branch("phoVy",        treeVars.phoVy,                 "phoVy[nPhotons]/F");
  chain -> Branch("phoVz",        treeVars.phoVz,                 "phoVz[nPhotons]/F");
  chain -> Branch("sTime",        treeVars.sTime,                 "sTime[nPhotons]/F");
  chain -> Branch("phoMother",    treeVars.phoMother,             "phoMother[nPhotons]/I");

  chain -> Branch("neuPx",        treeVars.neuPx,                 "neuPx[nNeu]/F");
  chain -> Branch("neuPy",        treeVars.neuPy,                 "neuPy[nNeu]/F");
  chain -> Branch("neuPz",        treeVars.neuPz,                 "neuPz[nNeu]/F");
  chain -> Branch("neuE",         treeVars.neuE,                  "neuE[nNeu]/F");
  chain -> Branch("neuM",         treeVars.neuM,                  "neuM[nNeu]/F");
  chain -> Branch("neuGamma",     treeVars.neuGamma,              "neuGamma[nNeu]/F");
  chain -> Branch("neuctau",      treeVars.neuctau,               "neuctau[nNeu]/F");

}


void initializeBranches(TTree* chain, Ntuple& treeVars) {

  treeVars.eventId = 0; 
  
  //treeVars.nJets      = 0 ; 
  treeVars.nPhotons   = 0 ; 
  treeVars.nNeu       = 0 ; 

  /*
  for ( int i=0; i< MAXJET; i++) {
      treeVars.jetPx[i] = 0 ;
      treeVars.jetPy[i] = 0 ;
      treeVars.jetPz[i] = 0 ;
      treeVars.jetE[i] = 0 ;
  }*/

  for ( int i=0; i< MAXPHO; i++) {
      treeVars.phoPx[i] = 0 ;
      treeVars.phoPy[i] = 0 ;
      treeVars.phoPz[i] = 0 ;
      treeVars.phoE[i] = 0 ;
      treeVars.phoVx[i] = 0 ;
      treeVars.phoVy[i] = 0 ;
      treeVars.phoVz[i] = 0 ;
      treeVars.sTime[i] = -99 ;
      treeVars.phoMother[i] = 0 ;
  }
  for ( int i=0; i< MAXOBJ; i++) {
      treeVars.neuPx[i] = 0 ;
      treeVars.neuPy[i] = 0 ;
      treeVars.neuPz[i] = 0 ;
      treeVars.neuE[i]  = 0 ;
      treeVars.neuM[i]  = 0 ;
      treeVars.neuGamma[i] = 0 ;
      treeVars.neuctau[i] = 0 ;
  }

}
