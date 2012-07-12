#include "Trigger.h"

Trigger::Trigger( string datacardfile ){

  Input  = new AnaInput( datacardfile );
  select = new DPSelection( datacardfile ) ;
  drawer = new hDraw( datacardfile ) ;

  Input->GetParameters("PlotType",      &plotType ) ; 
  Input->GetParameters("Path",          &hfolder ) ; 
  Input->GetParameters("RootFiles",     &rfolder ) ; 
  Input->GetParameters("IsData",        &isData ) ; 
  Input->GetParameters("ProcessEvents", &ProcessEvents ) ; 
  Input->GetParameters("TCut",          &TCut ) ; 

}

Trigger::~Trigger() {

  delete select ;
  delete Input  ;
  delete drawer ;
  cout<<" done ! "<<endl ;

}

// analysis template
void Trigger::ReadTree( string dataName ) { 

   TTree* tr = Input->TreeMap( dataName );

   // clone the tree for event selection
   TChain* tr1 = (TChain*) tr->Clone() ;

   tr->SetBranchAddress("nGen",        &nGen);
   tr->SetBranchAddress("nPhotons",    &nPhotons);
   tr->SetBranchAddress("nJets",       &nJets);
   tr->SetBranchAddress("nMuons",      &nMuons);
   tr->SetBranchAddress("nElectrons",  &nElectrons);
   tr->SetBranchAddress("triggered",   &triggered);
   tr->SetBranchAddress("L1a",         &L1a );
   tr->SetBranchAddress("nVertices",   &nVertices);
   tr->SetBranchAddress("runId",       &runId);

   tr->SetBranchAddress("metPx",       &metPx );
   tr->SetBranchAddress("metPy",       &metPy );
   tr->SetBranchAddress("met",         &metE );

   tr->SetBranchAddress("muE",         muE );

   tr->SetBranchAddress("phoPx",       phoPx );
   tr->SetBranchAddress("phoPy",       phoPy );
   tr->SetBranchAddress("phoPz",       phoPz );
   tr->SetBranchAddress("phoE",        phoE );
   tr->SetBranchAddress("dR_TrkPho",   dR_TrkPho );
   tr->SetBranchAddress("pt_TrkPho",   pt_TrkPho );
   tr->SetBranchAddress("seedTime",    seedTime );
   tr->SetBranchAddress("aveTime",     aveTime );
   tr->SetBranchAddress("aveTime1",    aveTime1 );
   tr->SetBranchAddress("aveTimeErr",  aveTimeErr );
   tr->SetBranchAddress("aveTimeErr1", aveTimeErr1 );

   tr->SetBranchAddress("fSpike",      fSpike );
   tr->SetBranchAddress("nXtals",      nXtals );
   tr->SetBranchAddress("nBC",         nBC );

   tr->SetBranchAddress("vtxX",       vtxX );
   tr->SetBranchAddress("vtxY",       vtxY );
   tr->SetBranchAddress("vtxZ",       vtxZ );
   
   tr->SetBranchAddress("genPx",       genPx );
   tr->SetBranchAddress("genPy",       genPy );
   tr->SetBranchAddress("genPz",       genPz );
   tr->SetBranchAddress("genE",        genE );
   tr->SetBranchAddress("genM",        genM );
   tr->SetBranchAddress("genVx",       genVx );
   tr->SetBranchAddress("genVy",       genVy );
   tr->SetBranchAddress("genVz",       genVz );
   tr->SetBranchAddress("genT",        genT );  // tau*gamma*beta
   tr->SetBranchAddress("pdgId",       pdgId );
   tr->SetBranchAddress("momId",       momId );

   select->Init( tr1 ) ;

   int totalN = tr->GetEntries();
   cout<<" from  "<< dataName <<" total entries = "<< totalN <<" Process "<< ProcessEvents <<endl;

   TH1D* h_gPt      = new TH1D("h_gPt", "Leading Photon Pt passed L1", 40,  50, 250);
   TH1D* h_gPt_hlt  = new TH1D("h_gPt_hlt", "Leading Photon Pt passed HLT", 40,  50, 250);
   //TH1D* h_PtEff    = new TH1D("h_PtEff", "Leading Photon Pt Efficiency passed HLT", 40,  50, 250);
   TH1D* h_met      = new TH1D("h_met",     "MET distribution ", 40,  0, 200);
   TH1D* h_met_hlt  = new TH1D("h_met_hlt", "MET distribution pssed HLT ", 40,  0, 200);
   TH1D* h_nJets    = new TH1D("h_nJets", "N of Jets  ", 10,  -0.5, 9.5);
   TH1D* h_dRTrkPho = new TH1D("h_dRTrkPho", " mindR(track, photon )", 100,  0, 10);
   TH1D* h_ptTrkPho = new TH1D("h_ptTrkPho", " pt of track near photon ", 100,  0, 100 );

   for ( int i=0; i< totalN ; i++ ) {
       if ( ProcessEvents > 0 && i > ( ProcessEvents - 1 ) ) break;
       tr->GetEntry( i );
       tr1->GetEntry( i );

       // 0. Use the events with only 1 photon
       if ( nPhotons != 1 ) continue ; 

       // 1. Reset the cuts and collectors
       select->ResetCuts() ;
       select->ResetCollection() ;
       bool pass_hlt = select->HLTFilter();
       bool pass_pho = select->PhotonFilter( true );  // true for applying Isolation 
       //bool pass_jet = select->JetMETFilter();
       if ( !pass_hlt || !pass_pho ) continue ;
        
       // Photon and MET information
       TLorentzVector met( metPx, metPy, 0, metE)  ;
       TLorentzVector gP4 = TLorentzVector( phoPx[0], phoPy[0], phoPz[0], phoE[0] ) ;

       // min_dR( track, photon)
       h_dRTrkPho->Fill( dR_TrkPho[0] ) ;
       h_ptTrkPho->Fill( pt_TrkPho[0] ) ;

       // multiplicity
       h_nJets->Fill( nJets ) ;

       if ( pass_pho && gP4.Pt() > 85. ) {
          double theMET = ( met.Pt() > 199 ) ? 199.9 :  met.Pt() ;
          h_met->Fill( theMET );
	  if ( triggered == 3 ) h_met_hlt->Fill( theMET );
       }
       if ( pass_pho && met.Pt() > 55 ) {
	  double gammaPt = ( gP4.Pt() > 249 ) ? 249.9 : gP4.Pt() ;
	  h_gPt->Fill( gammaPt );
	  if ( triggered == 3 ) h_gPt_hlt->Fill( gammaPt );
       }

   } // end of event looping


   TCanvas*  c1 = new TCanvas("c1","", 800, 600);
   c1->SetFillColor(10);
   c1->SetFillColor(10);
   c1->SetLogy();
   gStyle->SetOptStat("0");

   // Photon Pt distribution
   c1->cd();
   c1->SetLogy();
   //gStyle->SetStatY(0.95);
   //gStyle->SetStatTextColor(2);
   h_gPt->SetMinimum(0.1) ;
   h_gPt->SetLineColor(2) ;
   h_gPt->Draw() ;
   c1->Update();

   c1->SetLogy();
   //gStyle->SetStatY(0.75);
   //gStyle->SetStatTextColor(4);
   h_gPt_hlt->SetLineColor(4) ;
   h_gPt_hlt->DrawCopy("sames") ;
   c1->Update();

   TLegend* leg1  = new TLegend(.55, .73, .95, .90 );
   leg1->Clear();
   TString IntStr0 = "HLT_IsoMu24    = " ;
   TString IntStr1 = "HLT_DP65_MET25 = " ;
   Int_t nL1A = h_gPt->Integral() ;
   Int_t nHLT = h_gPt_hlt->Integral() ;
   IntStr0 += nL1A ;
   IntStr1 += nHLT ;
   leg1->SetTextSize(0.030) ;

   leg1->AddEntry( h_gPt,     IntStr0,  "L");
   leg1->AddEntry( h_gPt_hlt, IntStr1,  "L");
 
   leg1->Draw("sames");

   TString plotname1 = hfolder + "PhotonPt." + plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);
   c1->SetGridx(0);

   // Efficiency
    
   c1->cd();
   //gStyle->SetStatY(0.95);
   TGraphAsymmErrors* h_PtEff = new TGraphAsymmErrors();
   h_PtEff->BayesDivide( h_gPt_hlt, h_gPt );
   h_PtEff->SetMarkerStyle(20);
   h_PtEff->SetMarkerSize(1.0);
   h_PtEff->SetMarkerColor(1);
   h_PtEff->SetLineWidth(2);
   h_PtEff->Draw("AP") ;
   c1->Update();
   plotname1 = hfolder + "PtEff." +plotType ;
   c1->Print( plotname1 );
 

   // MET distribution
   c1->cd();
   c1->SetLogy();
   gStyle->SetStatY(0.95);
   gStyle->SetStatTextColor(2) ;
   h_met->SetLineColor(2) ;
   h_met->Draw() ;
   c1->Update();

   c1->SetLogy();
   gStyle->SetStatY(0.7);
   gStyle->SetStatTextColor(4);
   h_met_hlt->SetLineColor(4) ;
   h_met_hlt->DrawCopy("sames") ;
   c1->Update();

   leg1->Clear();
   IntStr0 = "HLT_IsoMu24    = " ;
   IntStr1 = "HLT_DP65_MET25 = " ;
   nL1A = h_met->Integral() ;
   nHLT = h_met_hlt->Integral() ;
   IntStr0 += nL1A ;
   IntStr1 += nHLT ;
   leg1->AddEntry( h_met,     IntStr0,  "L");
   leg1->AddEntry( h_met_hlt, IntStr1,  "L");
   leg1->Draw("sames") ;

   plotname1 = hfolder + "MET." +plotType ;
   c1->Print( plotname1 );
   c1->SetLogy(0);

   // Efficiency Plots
   EffPlot( h_gPt_hlt, h_gPt, 20, "PhotonPtEff" ) ;
   EffPlot( h_met_hlt, h_met, 20, "METEff" ) ;

   // mindR(Track,photon)
   gStyle->SetOptStat("emriou");
   c1->cd();
   h_dRTrkPho->Draw();
   c1->Update();
   plotname1 = hfolder + "dR_TrkPho." +plotType ;
   c1->Print( plotname1 );

   c1->cd();
   h_ptTrkPho->Draw();
   c1->Update();
   plotname1 = hfolder + "Pt_TrkPho." +plotType ;
   c1->Print( plotname1 );

   //Jet Multiplicity
   c1->cd() ;
   h_nJets->Draw() ;
   c1->Update();  

   plotname1 = hfolder + "NJets." + plotType ;
   c1->Print( plotname1 );

   // test Efficiency Function
   //EffProbPlot( 7, 3 ) ;
   //drawer->EffError( 8, 4 ) ;

}  

// Drawing Efficiency Plot from two histograms    
void Trigger::EffPlot( TH1D* hCut, TH1D* hAll, double minBinContent, string graphName  ){

   int nbin = hAll->GetNbinsX();
   double ba = 0 ;
   double bc = 0 ;
   double x  = 0 ;
   double rbin = 0 ;
   vector<double> baV ;
   vector<double> bcV ;
   vector<double> xV ;
   vector<double> xW ;
   vector<double> errL;
   vector<double> errH;
   // Accumulate bin contain
   for ( int i=1 ; i<= nbin; i++ ) {
       double bc_ = hCut->GetBinContent(i) ;
       double ba_ = hAll->GetBinContent(i) ;
       double x_  = hAll->GetBinCenter(i) ;
       if ( ba < minBinContent ) {
          ba += ba_ ; 
          bc += bc_ ; 
          x  +=  x_ ;
          rbin++ ;
       }
       if ( ba >= minBinContent || i == nbin ) {
          bcV.push_back( bc ) ;
          baV.push_back( ba ) ;
          xV.push_back( x / rbin )  ;
          xW.push_back( rbin * 5. / 2.) ;
          // sc's method to calculate error
          pair<double,double> errs = drawer->EffError( ba, bc ) ;
          errH.push_back( errs.first ) ;
          errL.push_back( errs.second ) ;
          //cout<<" x: "<< x/rbin <<" rb: "<< rbin <<"  bc: "<< bc <<"  ba: "<< ba <<endl ;
          bc   = 0 ;
          ba   = 0 ;
          x    = 0 ;
          rbin = 0 ;
       } 
   }
   
   cout<<" nbins = "<< xV.size() <<endl ;

   // calculate proper error
   int nbins = (int) xV.size() ;
   TH1D* hTop      = new TH1D("hTop", " ", nbins,  0, nbins );
   TH1D* hBot      = new TH1D("hBot", " ", nbins,  0, nbins );
   for ( int i=0; i< nbins ; i++ ) {
       hTop->SetBinContent( i+1 , bcV[i] ) ;
       hBot->SetBinContent( i+1 , baV[i] ) ;
   }
   TGraphAsymmErrors* gRatio = new TGraphAsymmErrors();
   gRatio->BayesDivide( hTop, hBot );
   
   const int sz = (int) xV.size() ;
   Double_t eYL[sz], eYH[sz], fX[sz], eX[sz];
   Double_t* fY = gRatio->GetY() ;
   Double_t yA[sz], eY_L[sz], eY_H[sz] ;  // for SC's method
   for ( Int_t i=0 ; i< sz ; i++) {
       fX[i]  = xV[i] ;
       eX[i]  = xW[i] ;
       eYL[i] = gRatio->GetErrorYlow(i) ;
       eYH[i] = gRatio->GetErrorYhigh(i) ;
       // for SC's method
       yA[i]   = bcV[i] / baV[i] ;
       eY_L[i] = errL[i] ;
       eY_H[i] = errH[i] ;
   }

   cout<<" now drawing "<<endl ;
   TGraphAsymmErrors* gr  = new TGraphAsymmErrors( sz, fX, fY, eX, eX, eYL, eYH );
   TGraphAsymmErrors* gr1 = new TGraphAsymmErrors( sz, fX, yA, eX, eX, eY_L, eY_H ); // SC's result !

   TCanvas* c0 = new TCanvas("c0","", 800, 700);
   c0->SetFillColor(10);
   c0->SetFillColor(10);
   //gPad->SetGridx();
   //gPad->SetGridy();
   c0->SetLeftMargin(0.15);
   c0->SetRightMargin(0.12);
   c0->SetTopMargin(0.1);
   c0->SetBottomMargin(0.12);

   c0->cd();
   gStyle->SetOptStat(kTRUE);
   gStyle->SetOptFit(111);

   gr->SetMaximum( 1.1 );
   gr->SetMinimum( 0.0 );
   //gr->SetMarkerColor(4);
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(1);
   gr->SetLineWidth(2);
   gStyle->SetTitleFontSize(0.04) ;
   gr->SetTitle("CMS Preliminary 2012, #sqrt{s} = 8 TeV ") ;
   gr->GetXaxis()->SetTitleOffset(1.34);
   gr->GetYaxis()->SetTitleOffset(1.39);
   gr->GetXaxis()->SetTitleFont(42);
   gr->GetYaxis()->SetTitleFont(42);
   gr->GetXaxis()->SetTitleSize(0.04);
   gr->GetYaxis()->SetTitleSize(0.04);
   if ( minBinContent ==  64 ) gr->GetXaxis()->SetTitle(" Photon p_{T} (GeV/c)") ;
   if ( minBinContent == 100 ) gr->GetXaxis()->SetTitle(" Missing Energy (GeV)") ;
   gr->GetYaxis()->SetTitle(" Efficiency ") ;
   gr->Draw("AP");

   c0->Update();
   TString plotname = hfolder + graphName + "Asym."+plotType ;
   //TString plotname = hfolder + graphName + ".pdf";
   c0->Print( plotname );

   /*
   TLatex* tex = new TLatex();
   tex->SetTextColor(1);
   tex->SetTextSize(0.030);
   tex->SetLineWidth(2);
   tex->SetTextFont(42);
   if ( minBinContent ==  64 ) tex->DrawLatex( 170, 1.0, "Missing Energy > 55 GeV ");
   if ( minBinContent == 100 ) tex->DrawLatex( 150, 1.0, "Photon p_{T} > 85 GeV ");
   */

   // Drawing SC's result !
   c0->cd();
   gr1->SetMaximum( 1.1 );
   gr1->SetMinimum( 0.0 );
   gr1->SetMarkerColor(4);
   gr1->SetMarkerStyle(22);
   gr1->SetMarkerSize(1);
   gr1->SetLineWidth(2);
   gr1->Draw("AP");

   c0->Update();
   plotname = hfolder + graphName + "Asym1."+plotType ;
   c0->Print( plotname );

}

// return asymmetry errors <H,L>
/*
pair<double, double> Trigger::EffError( double N_all, double N_pass ) {

    double eff0 = N_pass / N_all ;
    pair<double,double> theErr ;
    if ( eff0 > 1 ) {
       theErr = make_pair( -1 , -1 );
       return theErr ; 
    } 
    //cout<<" N_All: "<<N_all <<"  N_pass: "<< N_pass << endl;
    int nStep = 1000 ;
    double step = 1. / nStep ;
    //cout<<" step = "<< step <<endl;
    Double_t par[3] = { 1, N_all, N_pass } ;
    Double_t xL[1] = { eff0 } ;
    Double_t xR[1] = { eff0 } ;
    double IntEff = (N_all+ 1) * step * BinomialErr( xR, par ) ;
    //cout<<" Eff 0th : "<< BinomialErr( xR, par ) << endl ;  

    bool skipR = false ;
    bool skipL = false ;
    Double_t pR = 0 ;
    Double_t pL = 0 ;
    while ( IntEff < 0.683)  {
        if ( !skipR && xR[0] < 1 ) {
           xR[0] +=  step ;
           pR = BinomialErr( xR, par ) ;
           IntEff += (pR*step*(N_all+1) ) ;
           //cout<<" ("<< xR[0] <<") --> R : "<< IntEff <<"  pR = "<< pR <<endl ;
        }
        if ( !skipL && xL[0] > 0 ) {
           xL[0] -=  step ;
           pL = BinomialErr( xL, par ) ;
           IntEff += (pL*step*(N_all+1) ) ;
           //cout<<" ("<< xL[0] <<") <-- L : "<< IntEff <<"  pL = "<< pL <<endl;
        }
        //cout<<" ------ "<<endl; 
        skipR = ( pL > pR ) ? true : false ;
        skipL = ( pL < pR ) ? true : false ;
        if ( pL == pR ) {
           skipR = false ;
           skipL = false ;
        }
    }
    //cout<<"  ["<< N_pass/N_all <<"] Prob = "<< IntEff <<endl ; 
    //cout<<"                 - "<< (N_pass/N_all) - xL[0] <<endl ;
    //cout<<"                 + "<< xR[0] - (N_pass/N_all) <<endl ;
    theErr 	= make_pair( xR[0] - eff0 , eff0 - xL[0] );
 
    return theErr ;
}


Double_t Trigger::BinomialErr( Double_t* x, Double_t* par ) {

  Double_t N_all = par[1] ;
  Double_t N_pass = par[2] ;

  Double_t Z = ( TMath::Gamma( N_pass + 1 ) * TMath::Gamma( N_all - N_pass + 1 ) ) / TMath::Gamma( N_all + 2 );


  Double_t Cnk = pow(x[0], N_pass ) * pow( (1-x[0]) , (N_all - N_pass) ) ;

  Double_t prob = par[0]*Cnk / ( Z * (N_all + 1) );
  //cout<<" x = "<< x[0] <<" p = "<< prob <<endl ;

  if ( x[0] < 0 || x[0] > 1 ) prob = 0 ;

  return prob ;
}
*/
void Trigger::EffProbPlot( double N_all, double N_pass ){

  cout<<" N_All = "<< N_all <<" N_pass = "<< N_pass <<endl ; 
  TF1* fn1 = new TF1("fn1", hDraw::BinomialErr, 0., 1., 3);

  fn1->SetParameter( 0, 1. ) ;

   TCanvas* c0 = new TCanvas("c0","", 800, 600);
   c0->SetFillColor(10);
   c0->SetFillColor(10);
   gPad->SetGridx();

   for ( int i = 0 ; i <= N_all; i++ ) {
      c0->cd();
      fn1->SetParameter( 1, N_all ) ;
      fn1->SetParameter( 2, i ) ;
      if ( i == 0 ) fn1->Draw() ;
      fn1->DrawCopy("sames") ;
      c0->Update() ;
      //double intP = fn1->Integral( 0, 1 ) ; 
      //cout<<" Int = "<< intP <<endl ; 
   }
   TString plotname = hfolder + "EffErrFunction."+plotType ;
   c0->Print( plotname );

   delete fn1 ;
   delete c0 ;
}
