// -*- C++ -*-
//
// Package:    GenStudy
// Class:      GenStudy
// 
/**\class GenStudy GenStudy.cc EXO/GenStudy/src/GenStudy.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Shih-Chuan Kao
//         Created:  Thu Mar 15 12:51:07 CDT 2012
// $Id$
//
//

#include "GenStudy.h"
#include "Ntuple.h"

using namespace edm;

GenStudy::GenStudy(const edm::ParameterSet& iConfig) {
   //now do what ever initialization is needed
   genSrc         = iConfig.getParameter<edm::InputTag> ("genParticles"); 
   rootFileName   = iConfig.getUntrackedParameter<string> ("rootFileName");
   tau            = iConfig.getParameter<double> ("tau");

   theFile  = new TFile( rootFileName.c_str(), "RECREATE") ;
   theFile->cd () ;
   theTree  = new TTree ( "Gen","Gen" ) ;
   setBranches( theTree, leaves ) ;

   nEvt = 0 ;
   expPDF = new TRandom();
   expPDF->SetSeed( 123 );

}


GenStudy::~GenStudy() {
 
   theFile->cd () ;
   theTree->Write() ;
   theFile->Close() ;

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
}

//
// member functions
//

// ------------ method called for each event  ------------
void GenStudy::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

   Handle< std::vector<reco::GenParticle> > genParticles;
   iEvent.getByLabel( genSrc , genParticles );

   initializeBranches( theTree, leaves );

   //cout<<" fk1 "<<endl ;
   nEvt++;
   leaves.eventId = nEvt ;
   
   printf( " ======================================== \n ") ;
   int i = 0 ;
   int j = 0 ;
   for (std::vector<reco::GenParticle>::const_iterator it = genParticles->begin(); it != genParticles->end(); it++ ){

       if ( it->pdgId() == 1000022 && it->status() == 3 ) {
          leaves.neuPx[i] = it->p4().Px() ;
          leaves.neuPy[i] = it->p4().Py() ;
          leaves.neuPz[i] = it->p4().Pz() ;
          leaves.neuE[i]  = it->p4().E() ;
          leaves.neuM[i]  = it->mass() ;
          leaves.neuGamma[i]  = it->p4().E() / it->mass() ;
           
          double lifeTime = expPDF->Exp( tau ) ;
          //double beta  = it->p()/it->energy() ;
          double gamma = it->p4().E() / it->mass() ;
          leaves.neuctau[i] = lifeTime ;
  
          //cout<<" bz = "<< it->p4().Pz() /it->energy() <<"  b sin_theta = "<< beta*cos( it->theta() ) <<endl ;

          printf( " PID = %d ,  status: %d", it->pdgId(), it->status() ) ;
          printf( " M: %.2f  P: %.2f, E: %.2f gamma: %.2f \n", it->mass(), it->p(), it->energy(), it->energy()/it->mass() )  ;
          printf( "  Vtx=( %.2f, %.2f, %.2f ) \n" , it->vx(),  it->vy(), it->vz() ) ;
          double x1 = it->vx() ;
          double y1 = it->vy() ;
          double z1 = it->vz() ;
          double t1 = 0 ;
          bool insideEcal =  Propagator( it->p4(), x1, y1, z1, t1, lifeTime*gamma ) ;
          /*if ( insideEcal ) {
             cout<<"  ctau gamma : "<< lifeTime * gamma /10. <<" L = "<< sqrt( (x1*x1) + (y1*y1) + (z1*z1) ) <<endl; 
             cout<<"  ctau z = "<< lifeTime * gamma*cos(it->theta() ) <<"  Lz = "<< z1 <<endl ; 
             cout<<"  ctau x = "<< lifeTime * gamma*sin(it->theta())*cos(it->phi() ) <<"  Lx = "<< x1 <<endl ; 
             cout<<"  ctau y = "<< lifeTime * gamma*sin(it->theta())*sin(it->phi() ) <<"  Ly = "<< y1 <<endl ; 
             cout<<"  lifetime = "<< lifeTime * gamma /300 <<"   T = "<< t1 <<endl;
          }*/
          printf( "  beta: %.2f, ctau: %.3f, T: %.2f \n" , it->p()/it->energy(),  lifeTime, t1 ) ;
          if ( insideEcal ) cout<<" ** Still Inside Ecal ** "<<endl ;
          i++ ;

          for (size_t q=0; q< it->numberOfDaughters(); ++q) {
              const reco::Candidate *dau = it->daughter(q) ;
              if( abs(dau->pdgId()) != 22 ) continue;
              printf( "   pID = %d ,  status: %d  E: %.2f \n" , dau->pdgId(),  dau->status(), dau->energy() ) ;
              printf( "   vtx=( %.2f, %.2f, %.2f ) \n" , dau->vx(),  dau->vy(), dau->vz() ) ;
              leaves.phoPx[j] = dau->px() ;
              leaves.phoPy[j] = dau->py() ;
              leaves.phoPz[j] = dau->pz() ;
              leaves.phoE[j]  = dau->energy() ;
              leaves.phoVx[j] = dau->vx() ;
              leaves.phoVy[j] = dau->vy() ;
              leaves.phoVz[j] = dau->vz() ;
              leaves.phoMother[j]  = i ;
              Propagator( dau->p4(), x1, y1, z1, t1 ) ;
              double t0 = sqrt( (x1*x1) + (y1*y1) + (z1*z1) ) /30. ;
              printf( "   pos:( %.2f, %.2f, %.2f),  T: %.2f  T0: %.2f \n" , x1, y1, z1, t1, t0 ) ;
              double sTime = t1 - t0 ; 
              if ( !insideEcal ) sTime = -99 ;
              leaves.sTime[q] = sTime ;
              j++ ; 
          }
       }
   }
   leaves.nPhotons = j ;
   leaves.nNeu = i ;      
   theTree->Fill();

}

bool GenStudy::Propagator( LorentzVector v, double& x, double& y, double& z, double& t, double ctaugamma ) {

    double bx = v.Px() / v.E() ;
    double by = v.Py() / v.E() ;
    double bz = v.Pz() / v.E() ;

    double dt = 0.01 ;
    double r = sqrt( (x*x) + (y*y ) );
    bool insideEcal = true ;
    bool alived     = true ;
    do { 
       t = t + dt ;
       x = x + (bx*dt*30) ;
       y = y + (by*dt*30) ;
       z = z + (bz*dt*30) ;
       r = sqrt( (x*x) + (y*y ) ) ;
       //double trace = sqrt( (r*r) + (z*z ) ) ;
       //alived     = ( trace < (ctaugamma/10.)    ) ? true : false ;
       alived     = ( t < (ctaugamma/300.)     ) ? true : false ;
       insideEcal = ( r < 129 && fabs(z) < 293.5 ) ? true : false ;

    } while ( insideEcal && alived ) ;
 
    return insideEcal ;
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenStudy);
