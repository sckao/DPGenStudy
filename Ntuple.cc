#include "Ntuple.h"

void setBranchAddresses(TTree* chain, Ntuple& treeVars)
{
  chain -> SetBranchAddress("runId",       &treeVars.runId);
  chain -> SetBranchAddress("lumiSection", &treeVars.lumiSection);
  chain -> SetBranchAddress("orbit",       &treeVars.orbit);
  chain -> SetBranchAddress("bx",          &treeVars.bx);
  chain -> SetBranchAddress("eventId",     &treeVars.eventId);
  chain -> SetBranchAddress("triggered",   &treeVars.triggered);
  chain -> SetBranchAddress("L1a",         &treeVars.L1a );
  
  // PAT VARIABLES
  chain -> SetBranchAddress("nMuons",      &treeVars.nMuons     );
  chain -> SetBranchAddress("nElectrons",  &treeVars.nElectrons );
  chain -> SetBranchAddress("nJets",       &treeVars.nJets      );
  chain -> SetBranchAddress("nPhotons",    &treeVars.nPhotons   );
  chain -> SetBranchAddress("nVertices",   &treeVars.nVertices  );
  chain -> SetBranchAddress("totalNVtx",   &treeVars.totalNVtx  );
  chain -> SetBranchAddress("nGen",        &treeVars.nGen       );

  chain -> SetBranchAddress("metPx",       &treeVars.metPx     );
  chain -> SetBranchAddress("metPy",       &treeVars.metPy     );
  chain -> SetBranchAddress("met",         &treeVars.met       );

  // vertex variables
  chain -> SetBranchAddress("vtxNTracks", treeVars.vtxNTracks);
  chain -> SetBranchAddress("vtxChi2",    treeVars.vtxChi2   );
  chain -> SetBranchAddress("vtxNdof",    treeVars.vtxNdof   );
  chain -> SetBranchAddress("vtxX",       treeVars.vtxX      );
  chain -> SetBranchAddress("vtxY",       treeVars.vtxY      );
  chain -> SetBranchAddress("vtxZ",       treeVars.vtxZ      );
  chain -> SetBranchAddress("vtxDx",      treeVars.vtxDx     );
  chain -> SetBranchAddress("vtxDy",      treeVars.vtxDy     );
  chain -> SetBranchAddress("vtxDz",      treeVars.vtxDz     );

  chain -> SetBranchAddress("muPx",        treeVars.muPx       );
  chain -> SetBranchAddress("muPy",        treeVars.muPy       );
  chain -> SetBranchAddress("muPz",        treeVars.muPz       );
  chain -> SetBranchAddress("muE",         treeVars.muE        );
  
  chain -> SetBranchAddress("elePx",        treeVars.elePx     );
  chain -> SetBranchAddress("elePy",        treeVars.elePy     );
  chain -> SetBranchAddress("elePz",        treeVars.elePz     );
  chain -> SetBranchAddress("eleE",         treeVars.eleE      );
  chain -> SetBranchAddress("eleNLostHits", treeVars.eleNLostHits );
  chain -> SetBranchAddress("eleEcalIso",   treeVars.eleEcalIso ) ;
  chain -> SetBranchAddress("eleHcalIso",   treeVars.eleHcalIso ) ;
  chain -> SetBranchAddress("eleTrkIso",    treeVars.eleTrkIso ) ;
  
  chain -> SetBranchAddress("jetPx",        treeVars.jetPx     );
  chain -> SetBranchAddress("jetPy",        treeVars.jetPy     );
  chain -> SetBranchAddress("jetPz",        treeVars.jetPz     );
  chain -> SetBranchAddress("jetE",         treeVars.jetE      );
  chain -> SetBranchAddress("jetNDau",      treeVars.jetNDau   );
  chain -> SetBranchAddress("jetCM",        treeVars.jetCM     );
  chain -> SetBranchAddress("jetCEF",       treeVars.jetCEF    );
  chain -> SetBranchAddress("jetCHF",       treeVars.jetCHF    );
  chain -> SetBranchAddress("jetNHF",       treeVars.jetNHF    );
  chain -> SetBranchAddress("jetNEF",       treeVars.jetNEF    );
  
  chain -> SetBranchAddress("phoPx",        treeVars.phoPx     );
  chain -> SetBranchAddress("phoPy",        treeVars.phoPy     );
  chain -> SetBranchAddress("phoPz",        treeVars.phoPz     );
  chain -> SetBranchAddress("phoE",         treeVars.phoE      );
  chain -> SetBranchAddress("phoEcalIso",   treeVars.phoEcalIso ) ;
  chain -> SetBranchAddress("phoHcalIso",   treeVars.phoHcalIso ) ;
  chain -> SetBranchAddress("phoTrkIso",    treeVars.phoTrkIso ) ;
  chain -> SetBranchAddress("dR_TrkPho",    treeVars.dR_TrkPho ) ;
  chain -> SetBranchAddress("pt_TrkPho",    treeVars.pt_TrkPho ) ;
  chain -> SetBranchAddress("phoHoverE",    treeVars.phoHoverE ) ;
  chain -> SetBranchAddress("sMinPho",      treeVars.sMinPho ) ;
  chain -> SetBranchAddress("sMajPho",      treeVars.sMajPho ) ;
  chain -> SetBranchAddress("seedTime",     treeVars.seedTime ) ;
  chain -> SetBranchAddress("seedTimeErr",  treeVars.seedTimeErr ) ;
  chain -> SetBranchAddress("aveTime",      treeVars.aveTime ) ;
  chain -> SetBranchAddress("aveTimeErr",   treeVars.aveTimeErr ) ;
  chain -> SetBranchAddress("aveTime1",     treeVars.aveTime1 ) ;
  chain -> SetBranchAddress("aveTimeErr1",  treeVars.aveTimeErr1 ) ;
  chain -> SetBranchAddress("timeChi2",     treeVars.timeChi2 ) ;
  chain -> SetBranchAddress("nXtals",       treeVars.nXtals ) ;
  chain -> SetBranchAddress("fSpike",       treeVars.fSpike ) ;
  chain -> SetBranchAddress("seedSwissX",   treeVars.seedSwissX ) ;
  chain -> SetBranchAddress("nBC",          treeVars.nBC ) ;

  chain -> SetBranchAddress("genPx",        treeVars.genPx       );
  chain -> SetBranchAddress("genPy",        treeVars.genPy       );
  chain -> SetBranchAddress("genPz",        treeVars.genPz       );
  chain -> SetBranchAddress("genE",         treeVars.genE        );
  chain -> SetBranchAddress("genM",         treeVars.genM        );
  chain -> SetBranchAddress("genVx",        treeVars.genVx       );
  chain -> SetBranchAddress("genVy",        treeVars.genVy       );
  chain -> SetBranchAddress("genVz",        treeVars.genVz       );
  chain -> SetBranchAddress("genT",         treeVars.genT        );
  chain -> SetBranchAddress("pdgId",        treeVars.pdgId       );
  chain -> SetBranchAddress("momId",        treeVars.momId       );
  
}


void setBranches(TTree* chain, Ntuple& treeVars)
{
  chain -> Branch("runId",         &treeVars.runId,                "runId/i");
  chain -> Branch("lumiSection",   &treeVars.lumiSection,    "lumiSection/i");
  chain -> Branch("orbit",         &treeVars.orbit,                "orbit/i");
  chain -> Branch("bx",            &treeVars.bx,                      "bx/i");
  chain -> Branch("eventId",       &treeVars.eventId,            "eventId/i");
  chain -> Branch("triggered",     &treeVars.triggered,        "triggered/I");
  chain -> Branch("L1a",           &treeVars.L1a,              "L1a/I");
  
  // RECO VARIABLES
  chain -> Branch("nMuons",      &treeVars.nMuons,               "nMuons/I");
  chain -> Branch("nElectrons",  &treeVars.nElectrons,           "nElectrons/I");
  chain -> Branch("nJets",       &treeVars.nJets,                "nJets/I");
  chain -> Branch("nPhotons",    &treeVars.nPhotons,             "nPhotons/I");
  chain -> Branch("nVertices",   &treeVars.nVertices,            "nVertices/I");
  chain -> Branch("totalNVtx",   &treeVars.totalNVtx,            "totalNVtx/I");
  chain -> Branch("nGen",        &treeVars.nGen,                 "nGen/I");

  chain -> Branch("metPx",       &treeVars.metPx,                "metPx/F");
  chain -> Branch("metPy",       &treeVars.metPy,                "metPy/F");
  chain -> Branch("met",         &treeVars.met,                  "met/F");

  chain -> Branch("muPx",        treeVars.muPx,                 "muPx[nMuons]/F");
  chain -> Branch("muPy",        treeVars.muPy,                 "muPy[nMuons]/F");
  chain -> Branch("muPz",        treeVars.muPz,                 "muPz[nMuons]/F");
  chain -> Branch("muE",         treeVars.muE,                  "muE[nMuons]/F");
  
  chain -> Branch("elePx",        treeVars.elePx,                 "elePx[nElectrons]/F");
  chain -> Branch("elePy",        treeVars.elePy,                 "elePy[nElectrons]/F");
  chain -> Branch("elePz",        treeVars.elePz,                 "elePz[nElectrons]/F");
  chain -> Branch("eleE",         treeVars.eleE,                  "eleE[nElectrons]/F");
  chain -> Branch("eleNLostHits", treeVars.eleNLostHits,          "eleNLostHits[nElectrons]/I" );
  chain -> Branch("eleEcalIso",   treeVars.eleEcalIso,            "eleEcalIso[nElectrons]/F") ;
  chain -> Branch("eleHcalIso",   treeVars.eleHcalIso,            "eleHcalIso[nElectrons]/F") ;
  chain -> Branch("eleTrkIso",    treeVars.eleTrkIso,             "eleTrkIso[nElectrons]/F" ) ;
  
  chain -> Branch("jetPx",        treeVars.jetPx,                 "jetPx[nJets]/F");
  chain -> Branch("jetPy",        treeVars.jetPy,                 "jetPy[nJets]/F");
  chain -> Branch("jetPz",        treeVars.jetPz,                 "jetPz[nJets]/F");
  chain -> Branch("jetE",         treeVars.jetE,                  "jetE[nJets]/F");
  chain -> Branch("jetNDau",      treeVars.jetNDau,               "jetNDau[nJets]/I");
  chain -> Branch("jetCM",        treeVars.jetCM,                 "jetCM[nJets]/I"  );
  chain -> Branch("jetCEF",       treeVars.jetCEF,                "jetCEF[nJets]/F" );
  chain -> Branch("jetCHF",       treeVars.jetCHF,                "jetCHF[nJets]/F" );
  chain -> Branch("jetNHF",       treeVars.jetNHF,                "jetNHF[nJets]/F" );
  chain -> Branch("jetNEF",       treeVars.jetNEF,                "jetNEF[nJets]/F" );
  
  chain -> Branch("phoPx",        treeVars.phoPx,                 "phoPx[nPhotons]/F");
  chain -> Branch("phoPy",        treeVars.phoPy,                 "phoPy[nPhotons]/F");
  chain -> Branch("phoPz",        treeVars.phoPz,                 "phoPz[nPhotons]/F");
  chain -> Branch("phoE",         treeVars.phoE,                  "phoE[nPhotons]/F");
  chain -> Branch("phoEcalIso",   treeVars.phoEcalIso,            "phoEcalIso[nPhotons]/F") ;
  chain -> Branch("phoHcalIso",   treeVars.phoHcalIso,            "phoHcalIso[nPhotons]/F") ;
  chain -> Branch("phoTrkIso",    treeVars.phoTrkIso,             "phoTrkIso[nPhotons]/F") ;
  chain -> Branch("dR_TrkPho",    treeVars.dR_TrkPho,             "dR_TrkPho[nPhotons]/F") ;
  chain -> Branch("pt_TrkPho",    treeVars.pt_TrkPho,             "pt_TrkPho[nPhotons]/F") ;
  chain -> Branch("phoHoverE",    treeVars.phoHoverE,             "phoHoverE[nPhotons]/F") ;
  chain -> Branch("sMinPho",      treeVars.sMinPho,               "sMinPho[nPhotons]/F") ;
  chain -> Branch("sMajPho",      treeVars.sMajPho,               "sMajPho[nPhotons]/F") ;
  chain -> Branch("seedTime",     treeVars.seedTime,              "seedTime[nPhotons]/F") ;
  chain -> Branch("seedTimeErr",  treeVars.seedTimeErr,           "seedTimeErr[nPhotons]/F") ;
  chain -> Branch("aveTime",      treeVars.aveTime,               "aveTime[nPhotons]/F") ;
  chain -> Branch("aveTimeErr",   treeVars.aveTimeErr,            "aveTimeErr[nPhotons]/F") ;
  chain -> Branch("aveTime1",     treeVars.aveTime1,              "aveTime1[nPhotons]/F") ;
  chain -> Branch("aveTimeErr1",  treeVars.aveTimeErr1,           "aveTimeErr1[nPhotons]/F") ;
  chain -> Branch("timeChi2",     treeVars.timeChi2,              "timeChi2[nPhotons]/F") ;
  chain -> Branch("fSpike",       treeVars.fSpike,                "fSpike[nPhotons]/F"  ) ;
  chain -> Branch("seedSwissX",   treeVars.seedSwissX,            "seedSwissX[nPhotons]/F"  ) ;
  chain -> Branch("nXtals",       treeVars.nXtals,                "nXtals[nPhotons]/I"  ) ;
  chain -> Branch("nBC",          treeVars.nBC,                   "nBC[nPhotons]/I"  ) ;
 
  chain -> Branch("vtxNTracks",       treeVars.vtxNTracks,   "vtxNTracks[nVertices]/I");
  chain -> Branch("vtxChi2",          treeVars.vtxChi2,      "vtxChi2[nVertices]/F");
  chain -> Branch("vtxNdof",          treeVars.vtxNdof,      "vtxNdof[nVertices]/F");
  chain -> Branch("vtxX",             treeVars.vtxX,         "vtxX[nVertices]/F");
  chain -> Branch("vtxY",             treeVars.vtxY,         "vtxY[nVertices]/F");
  chain -> Branch("vtxZ",             treeVars.vtxZ,         "vtxZ[nVertices]/F");
  chain -> Branch("vtxDx",            treeVars.vtxDx,        "vtxDx[nVertices]/F");
  chain -> Branch("vtxDy",            treeVars.vtxDy,        "vtxDy[nVertices]/F");
  chain -> Branch("vtxDz",            treeVars.vtxDz,        "vtxDz[nVertices]/F");
  
  chain -> Branch("pdgId",        treeVars.pdgId,                 "pdgId[nGen]/I");
  chain -> Branch("momId",        treeVars.momId,                 "momId[nGen]/I");
  chain -> Branch("genPx",        treeVars.genPx,                 "genPx[nGen]/F");
  chain -> Branch("genPy",        treeVars.genPy,                 "genPy[nGen]/F");
  chain -> Branch("genPz",        treeVars.genPz,                 "genPz[nGen]/F");
  chain -> Branch("genE",         treeVars.genE,                  "genE[nGen]/F");
  chain -> Branch("genM",         treeVars.genM,                  "genM[nGen]/F");
  chain -> Branch("genVx",        treeVars.genVx,                 "genVx[nGen]/F");
  chain -> Branch("genVy",        treeVars.genVy,                 "genVy[nGen]/F");
  chain -> Branch("genVz",        treeVars.genVz,                 "genVz[nGen]/F");
  chain -> Branch("genT",         treeVars.genT,                  "genT[nGen]/F");
  
}


void initializeBranches(TTree* chain, Ntuple& treeVars)
{
  treeVars.runId = 0;
  treeVars.lumiSection = 0;
  treeVars.orbit = 0;
  treeVars.bx = 0;
  treeVars.eventId = 0; 
  treeVars.triggered = 0; 
  treeVars.L1a = 0; 
  
  treeVars.nJets      = 0 ; 
  treeVars.nElectrons = 0 ; 
  treeVars.nMuons     = 0 ; 
  treeVars.nPhotons   = 0 ; 
  treeVars.nVertices  = 0 ;
  treeVars.totalNVtx  = 0 ;
  treeVars.nGen       = 0 ; 

  treeVars.metPx = 0 ;
  treeVars.metPy = 0 ;
  treeVars.met   = 0 ;

  for ( int i=0; i< MAXJET; i++) {
      treeVars.jetPx[i] = 0 ;
      treeVars.jetPy[i] = 0 ;
      treeVars.jetPz[i] = 0 ;
      treeVars.jetE[i] = 0 ;
      treeVars.jetNDau[i] = 0 ;
      treeVars.jetCM[i] = 0 ;
      treeVars.jetCEF[i] = 0 ;
      treeVars.jetCHF[i] = 0 ;
      treeVars.jetNHF[i] = 0 ;
      treeVars.jetNEF[i] = 0 ;
  }

  for ( int i=0; i< MAXELE; i++) {
      treeVars.elePx[i] = 0 ;
      treeVars.elePy[i] = 0 ;
      treeVars.elePz[i] = 0 ;
      treeVars.eleE[i] = 0 ;
      treeVars.eleEcalIso[i] = -1 ;
      treeVars.eleHcalIso[i] = -1 ;
      treeVars.eleTrkIso[i]  = -1 ;
      treeVars.eleNLostHits[i]  = -1 ;

      treeVars.muPx[i] = 0 ;
      treeVars.muPy[i] = 0 ;
      treeVars.muPz[i] = 0 ;
      treeVars.muE[i] = 0 ;
  } 
  for ( int i=0; i< MAXPHO; i++) {
      treeVars.phoPx[i] = 0 ;
      treeVars.phoPy[i] = 0 ;
      treeVars.phoPz[i] = 0 ;
      treeVars.phoE[i] = 0 ;
      treeVars.phoEcalIso[i] = -1 ;
      treeVars.phoHcalIso[i] = -1 ;
      treeVars.phoTrkIso[i]  = -1 ;
      treeVars.dR_TrkPho[i]  = -1 ;
      treeVars.pt_TrkPho[i]  = -1 ;
      treeVars.phoHoverE[i]  = -1 ;
      treeVars.sMinPho[i]    = -1 ;
      treeVars.sMajPho[i]    = -1 ;
      treeVars.seedTime[i]   = -25 ;
      treeVars.seedTimeErr[i] = -25 ;
      treeVars.aveTime[i]     = -25 ;
      treeVars.aveTimeErr[i]  = -25 ;
      treeVars.aveTime1[i]    = -25 ;
      treeVars.aveTimeErr1[i] = -25 ;
      treeVars.timeChi2[i]    = -1 ;
      treeVars.fSpike[i]      = -1 ;
      treeVars.seedSwissX[i]  = 0 ;
      treeVars.nXtals[i]      = 0 ;
      treeVars.nBC[i]         = 0 ;
  }
  for(int i=0; i<MAXVTX; i++) {
      treeVars.vtxNTracks[i]=0;
      treeVars.vtxChi2[i]=0;
      treeVars.vtxNdof[i]=0;
      treeVars.vtxX[i]=0;
      treeVars.vtxY[i]=0;
      treeVars.vtxZ[i]=0;
      treeVars.vtxDx[i]=0;
      treeVars.vtxDy[i]=0;
      treeVars.vtxDz[i]=0;
  }
  for ( int i=0; i< MAXGEN; i++) {
      treeVars.pdgId[i] = 0 ;
      treeVars.momId[i] = 0 ;
      treeVars.genPx[i] = 0 ;
      treeVars.genPy[i] = 0 ;
      treeVars.genPz[i] = 0 ;
      treeVars.genE[i] = 0 ;
      treeVars.genM[i] = 0 ;
      treeVars.genVx[i] = 0 ;
      treeVars.genVy[i] = 0 ;
      treeVars.genVz[i] = 0 ;
      treeVars.genT[i] = 0 ;
  }
}
