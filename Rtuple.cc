#include "Rtuple.h"

void setRtupleAddresses(TTree* tr, Rtuple& vr ) {

   tr->SetBranchAddress("eventId",    &vr.eventId);
   tr->SetBranchAddress("triggered",  &vr.triggered);
   tr->SetBranchAddress("L1a",        &vr.L1a);
   tr->SetBranchAddress("nPhotons",   &vr.nPhotons);
   tr->SetBranchAddress("nJets",      &vr.nJets);
   tr->SetBranchAddress("nMuons",     &vr.nMuons);
   tr->SetBranchAddress("nElectrons", &vr.nElectrons);
   tr->SetBranchAddress("nVertices",  &vr.nVertices );
   tr->SetBranchAddress("totalNVtx",  &vr.totalNVtx);

   tr->SetBranchAddress("t_metPx",    &vr.t_metPx );
   tr->SetBranchAddress("t_metPy",    &vr.t_metPy );
   tr->SetBranchAddress("t_met",      &vr.t_met );
   tr->SetBranchAddress("metPx",      &vr.metPx );
   tr->SetBranchAddress("metPy",      &vr.metPy );
   tr->SetBranchAddress("met",        &vr.metE );
   tr->SetBranchAddress("met_dx1",    &vr.met_dx1 );
   tr->SetBranchAddress("met_dy1",    &vr.met_dy1 );
   tr->SetBranchAddress("met_dx2",    &vr.met_dx2 );
   tr->SetBranchAddress("met_dy2",    &vr.met_dy2 );
   tr->SetBranchAddress("met_dx3",    &vr.met_dx3 );
   tr->SetBranchAddress("met_dy3",    &vr.met_dy3 );

   tr->SetBranchAddress("jetPx",       &vr.jetPx );
   tr->SetBranchAddress("jetPy",       &vr.jetPy );
   tr->SetBranchAddress("jetPz",       &vr.jetPz );
   tr->SetBranchAddress("jetE",        &vr.jetE );
   tr->SetBranchAddress("jetNDau",     &vr.jetNDau );
   tr->SetBranchAddress("jetCM",       &vr.jetCM );
   tr->SetBranchAddress("jetCEF",      &vr.jetCEF );
   tr->SetBranchAddress("jetCHF",      &vr.jetCHF );
   tr->SetBranchAddress("jetNHF",      &vr.jetNHF );
   tr->SetBranchAddress("jetNEF",      &vr.jetNEF );
   tr->SetBranchAddress("jecUnc",      &vr.jecUnc );
   tr->SetBranchAddress("jerUnc",      &vr.jerUnc );
   tr->SetBranchAddress("jetTime",     &vr.jetTime );
   tr->SetBranchAddress("jetTimeErr",  &vr.jetTimeErr );

   tr->SetBranchAddress("phoPx",       &vr.phoPx );
   tr->SetBranchAddress("phoPy",       &vr.phoPy );
   tr->SetBranchAddress("phoPz",       &vr.phoPz );
   tr->SetBranchAddress("phoE",        &vr.phoE );
   tr->SetBranchAddress("phoEcalIso",  &vr.phoEcalIso );
   tr->SetBranchAddress("phoHcalIso",  &vr.phoHcalIso );
   tr->SetBranchAddress("phoTrkIso",   &vr.phoTrkIso );
   tr->SetBranchAddress("cHadIso",     &vr.cHadIso );
   tr->SetBranchAddress("nHadIso",     &vr.nHadIso );
   tr->SetBranchAddress("photIso",     &vr.photIso );

   tr->SetBranchAddress("sigmaIeta",   &vr.sigmaIeta );
   tr->SetBranchAddress("dR_TrkPho",   &vr.dR_TrkPho );
   tr->SetBranchAddress("phoHoverE",   &vr.phoHovE );
   tr->SetBranchAddress("sMinPho",     &vr.sMinPho );
   tr->SetBranchAddress("sMajPho",     &vr.sMajPho );
   tr->SetBranchAddress("seedTime",    &vr.seedTime );
   tr->SetBranchAddress("aveTime",     &vr.aveTime );
   tr->SetBranchAddress("cscdPhi",     &vr.cscdPhi );
   tr->SetBranchAddress("cscRho",      &vr.cscRho );
   tr->SetBranchAddress("cscTime",     &vr.cscTime );
   tr->SetBranchAddress("dtdPhi",      &vr.dtdPhi );
   tr->SetBranchAddress("dtdEta",      &vr.dtdEta );
   tr->SetBranchAddress("nXtals",      &vr.nXtals );
   tr->SetBranchAddress("timeChi2",    &vr.timeChi2 );
   tr->SetBranchAddress("seedSwissX",  &vr.seedSwissX );
   tr->SetBranchAddress("seedE",       &vr.seedE );

   tr->SetBranchAddress("elePx",        &vr.elePx );
   tr->SetBranchAddress("elePy",        &vr.elePy );
   tr->SetBranchAddress("elePz",        &vr.elePz );
   tr->SetBranchAddress("eleE",         &vr.eleE );
   tr->SetBranchAddress("eleEcalIso",   &vr.eleEcalIso );
   tr->SetBranchAddress("eleHcalIso",   &vr.eleHcalIso );
   tr->SetBranchAddress("eleTrkIso",    &vr.eleTrkIso );
   tr->SetBranchAddress("eleNLostHits", &vr.eleNLostHits );

   tr->SetBranchAddress("muPx",        &vr.muPx );
   tr->SetBranchAddress("muPy",        &vr.muPy );
   tr->SetBranchAddress("muPz",        &vr.muPz );
   tr->SetBranchAddress("muE",         &vr.muE );
   //tr->SetBranchAddress("muEcalIso",   muEcalIso );
   //tr->SetBranchAddress("muHcalIso",   muHcalIso );
   //tr->SetBranchAddress("muTrkIso",    muTrkIso );

   //tr->SetBranchAddress("vtxX",       vtxX );
   //tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       &vr.vtxZ );
   tr->SetBranchAddress("vtxChi2",    &vr.vtxChi2 );
   tr->SetBranchAddress("vtxNdof",    &vr.vtxNdof );

}

/*
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
*/

