#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <TFile.h>
#include <TMath.h>
#include <iostream>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>


// define the generator's information across different ctau models
void Eff_Calculator() {

     // Z mass 
     // |t| < 2 ns  Z 
     double InT = 2349187.0 - 996803.6 ;
     pair<double,double> err_InT = ErrApnB( 2349187.0 , 996803.6 , -1, -1, -1, -1 ) ;
     printf("InTime Z  = %.5f err + %.5f,  - %.5f \n", InT, err_InT.first, err_InT.second ) ;

     // t > 3 ns Z
     double posT = 38.0 - 8.6  ;
     pair<double,double> err_posT = ErrApnB( 38, 8.6, -1, -1, -1, -1 ) ;
     printf("T > 3 Z = %.5f err + %.5f,  - %.5f \n", posT, err_posT.first, err_posT.second ) ;

     // t < 3 ns Z
     double negT = 378.0 - 329.0 ;
     pair<double,double> err_negT = ErrApnB( 378, 329, -1, -1, -1, -1 ) ;
     printf("T < 3 Z = %.5f err + %.5f,  - %.5f \n", negT, err_negT.first, err_negT.second ) ;

     // 2Jet events - total 28246
     double f = 28208 ; // 1 phot event in F 
     double f2 =   38 ;  // 2 phot event in F
     // Closure test events - total 35271
     //double f = 35097 ;
     //double f2 = 174  ;

     pair<double,double> err_f = StatErr1( f ) ; 
     double f_u = err_f.first ;
     double f_d = err_f.second ;
     pair<double,double> err_f2 = StatErr1( f2 ) ; 
     printf("f  = %.3f err + %.3f,  - %.3f \n", f, f_u , f_d ) ;
     printf("f2 = %.3f err + %.3f,  - %.3f \n", f2, err_f2.first , err_f2.second ) ;

     // Given ratio of t> 3 / |t|<2 for 1 photon events
     double r = posT/(2*InT) ;
     pair<double,double> err_r = ErrAovB( posT, 2*InT, err_posT.first, err_posT.second , 2*err_InT.first, 2*err_InT.second ) ;
     printf("Ratio(t1 or t2 >3)  = %.8f err + %.8f,  - %.8f \n", r, err_r.first, err_r.second ) ;
  
     double n2 = 3 ;
     double r2 = 3/InT ;
     pair<double,double> err_r2 = ErrAovB( n2 , InT,  -1, -1 , err_InT.first, err_InT.second ) ;
     printf("Ratio(t1 and t2 >3) = %.8f err + %.8f,  - %.8f \n", r2, err_r2.first, err_r2.second ) ;
     

     // Predict
     double Qd = (f*r) + (f2*2*r) + (f2*r2) + (f*r2);
     pair<double,double> err_Qd1 = ErrAxB( f, r , -1, -1, err_r.first, err_r.second ) ;
     pair<double,double> err_Qd2 = ErrAxB( 2*f2, r , -1, -1, err_r.first,   err_r.second ) ;
     pair<double,double> err_Qd3 = ErrAxB( f2, r2 , -1, -1, err_r2.first,  err_r2.second ) ;
     pair<double,double> err_Qd4 = ErrAxB(  f, r2 , -1, -1, err_r2.first,  err_r2.second ) ;
     pair<double,double> err_Qd5 = ErrApnB( f*r, f2*2*r ,  err_Qd1.first, err_Qd1.second, err_Qd2.first, err_Qd2.second ) ;
     pair<double,double> err_Qd6 = ErrApnB( (f*r)+(f2*2*r) , f2*r2,  err_Qd5.first, err_Qd5.second, err_Qd3.first, err_Qd3.second ) ;
     pair<double,double> err_Qd  = ErrApnB( (f*r)+(f2*2*r)+(f2*r2), f*r2 , err_Qd6.first, err_Qd6.second, err_Qd4.first, err_Qd4.second ) ;
     printf("Qd = %.5f err + %.5f,  - %.5f \n", Qd, err_Qd.first, err_Qd.second ) ;

     printf(" ==================== \n") ;

     // Given ratio of  t < -3 / |t|<2 
     double rB = negT/(2*InT) ;
     pair<double,double> err_rB = ErrAovB( negT, 2*InT, err_negT.first, err_negT.second , 2*err_InT.first, 2*err_InT.second ) ;
     printf("Ratio(t<3) = %.8f err + %.8f,  - %.8f \n", rB, err_rB.first, err_rB.second ) ;

     // Predict
     double Qb = f*rB + f2*2*rB ;
     pair<double,double> err_Qb1 = ErrAxB(  f,   rB , -1, -1, err_rB.first, err_rB.second ) ;
     pair<double,double> err_Qb2 = ErrAxB( f2, 2*rB , -1, -1, 2*err_rB.first, 2*err_rB.second ) ;
     pair<double,double> err_Qb = ErrApnB( f*rB, f2*2*rB , err_Qb1.first, err_Qb1.second, err_Qb2.first, err_Qb2.second ) ;
     printf("Qb = %.5f err + %.5f,  - %.5f \n", Qb, err_Qb.first, err_Qb.second ) ;

     printf(" ==================== \n\n") ;

     //  Closure Test
     // ABCD method for collision background
     /*    
     double f1 = 35271 ;
     pair<double,double> err_f1 = StatErr1( f1 ) ; 
     double f1_u = err_f1.first ;
     double f1_d = err_f1.second ;
     printf("f1 = %.3f err + %.3f,  - %.3f \n", f1, f1_u , f1_d ) ;
     double fp = 1445254 ;
     pair<double,double> err_fp = StatErr1( fp ) ; 
     double fp_u = err_fp.first ;
     double fp_d = err_fp.second ;
     printf("fp = %.3f err + %.3f,  - %.3f \n", fp, fp_u, fp_d  ) ;

     pair<double,double> err_f = ErrAovB( f, fp, -1, -1, -1, -1 ) ;
     printf("f1/fp = %.5f err + %.5f,  - %.5f \n", f/fp, err_f.first, err_f.second ) ;

     double bp = 8. ;
     pair<double,double> err_bp = StatErr1( bp ) ; 
     double bp_u = err_bp.first ;
     double bp_d = err_bp.second ;
     printf("bp = %.3f err + %.3f,  - %.3f \n", bp, bp_u, bp_d  ) ;

     pair<double,double> err_Qb = ErrAxB( bp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qb = bp*f/fp ;
     printf("Qb -> bp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qb, err_Qb.first, err_Qb.second ) ;
     printf(" ==================== \n") ;

     double dp = 2. ;
     pair<double,double> err_dp = StatErr1( dp ) ; 
     double dp_u = err_dp.first ;
     double dp_d = err_dp.second ;
     printf("dp = %.3f err + %.3f,  - %.3f \n", dp, dp_u, dp_d  ) ;

     pair<double,double> err_Qd7 = ErrAxB( dp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qd7 = dp*f/fp ;
     printf("Qd -> dp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qd7, err_Qd7.first, err_Qd7.second ) ;
     printf(" ==================== \n") ;


     double c = 359. ;
     pair<double,double> err_c = StatErr1( c ) ; 
     double c_u = err_c.first ;
     double c_d = err_c.second ;
     printf("c = %.3f err + %.3f,  - %.3f \n", c, c_u , c_d ) ;
  
     double a = 851. ;
     pair<double,double> err_a = StatErr1( a ) ; 
     double a_u = err_a.first ;
     double a_d = err_a.second ;
     printf("a = %.3f err + %.3f,  - %.3f \n", a, a_u, a_d  ) ;

     pair<double,double> err0 = ErrAovB( c, a, -1, -1, -1, -1 ) ;
     printf("c/a = %.5f err + %.5f,  - %.5f \n", c/a, err0.first, err0.second ) ;

     double b = 38. ;
     pair<double,double> err_b = StatErr1( b ) ; 
     double b_u = err_b.first ;
     double b_d = err_b.second ;
     printf("b = %.3f err + %.3f,  - %.3f \n", b, b_u, b_d  ) ;

     pair<double,double> err1 = ErrApnB( b, Qb, -1, -1, err_Qb.first, err_Qb.second ) ;
     printf("b - Qb = %.5f err + %.5f,  - %.5f \n", b -Qb, err1.first, err1.second ) ;

     pair<double,double> err2 = ErrAxB( b - Qb , c/a, err1.first, err1.second, err0.first, err0.second) ;
     printf("(b-Qb)x(c/a) = %.5f err + %.5f,  - %.5f \n", (b -Qb)*c/a, err2.first, err2.second ) ;
     double d1 = (b -Qb)*c/a ;

     pair<double,double> err3 = ErrApnB( d1, Qd, err2.first, err2.second, err_Qd.first, err_Qd.second) ;
     printf("\nfinal = %.5f err + %.5f,  - %.5f \n", d1+Qd , err3.first, err3.second ) ;
     */         

     // 2J events
     
     // ABCD method for collision background
     double f1 = 28246 ;
     pair<double,double> err_f1 = StatErr1( f1 ) ; 
     double f1_u = err_f1.first ;
     double f1_d = err_f1.second ;
     printf("f1 = %.3f err + %.3f,  - %.3f \n", f1, f1_u , f1_d ) ;
     double fp = 604958 ;
     pair<double,double> err_fp = StatErr1( fp ) ; 
     double fp_u = err_fp.first ;
     double fp_d = err_fp.second ;
     printf("fp = %.3f err + %.3f,  - %.3f \n", fp, fp_u, fp_d  ) ;

     pair<double,double> err_f = ErrAovB( f, fp, -1, -1, -1, -1 ) ;
     printf("f1/fp = %.5f err + %.5f,  - %.5f \n", f/fp, err_f.first, err_f.second ) ;

     double bp = 3. ;
     pair<double,double> err_bp = StatErr1( bp ) ; 
     double bp_u = err_bp.first ;
     double bp_d = err_bp.second ;
     printf("bp = %.3f err + %.3f,  - %.3f \n", bp, bp_u, bp_d  ) ;

     pair<double,double> err_Qb5 = ErrAxB( bp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qb5 = bp*f/fp ;
     printf("Qb -> bp(f/fp) = %.5f err + %.5f,  - %.5f \n", Qb5, err_Qb5.first, err_Qb5.second ) ;
     printf(" ==================== \n") ;

     double dp = 2. ;
     pair<double,double> err_dp = StatErr1( dp ) ; 
     double dp_u = err_dp.first ;
     double dp_d = err_dp.second ;
     printf("dp = %.3f err + %.3f,  - %.3f \n", dp, dp_u, dp_d  ) ;

     pair<double,double> err_Qd7 = ErrAxB( dp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qd7 = dp*f/fp ;
     printf("Qd -> dp(f/fp) = %.5f err + %.5f,  - %.5f \n", Qd7, err_Qd7.first, err_Qd7.second ) ;
     printf(" ==================== \n") ;

     
     double c = 0. ;
     pair<double,double> err_c = StatErr1( c ) ; 
     double c_u = err_c.first ;
     double c_d = err_c.second ;
     printf("c = %.3f err + %.3f,  - %.3f \n", c, c_u , c_d ) ;

     double a = 3. ;
     pair<double,double> err_a = StatErr1( a ) ; 
     double a_u = err_a.first ;
     double a_d = err_a.second ;
     printf("a = %.3f err + %.3f,  - %.3f \n", a, a_u, a_d  ) ;

     pair<double,double> err0 = ErrAovB( c, a, -1, -1, -1, -1 ) ;
     printf("c/a = %.5f err + %.5f,  - %.5f \n", c/a, err0.first, err0.second ) ;

     double b = 1. ;
     pair<double,double> err_b = StatErr1( b ) ; 
     double b_u = err_b.first ;
     double b_d = err_b.second ;
     printf("b = %.3f err + %.3f,  - %.3f \n", b, b_u, b_d  ) ;

     pair<double,double> err1 = ErrAxB( b , c/a, err_b.first, err_b.second, err0.first, err0.second) ;
     printf("(b)x(c/a) = %.5f err + %.5f,  - %.5f \n", b*c/a, err1.first, err1.second ) ;
     double d1 = b*c/a ;

     pair<double,double> err2 = ErrAxB( Qb , c/a, err_Qb.first, err_Qb.second, err0.first, err0.second) ;
     printf("(Qb)x(c/a) = %.5f err + %.5f,  - %.5f \n", Qb*c/a, err2.first, err2.second ) ;
     double d2 = Qb*c/a ;

     pair<double,double> err3 = ErrApnB( d1, d2, err1.first, err1.second, err2.first, err2.second ) ;
     printf("D  = %.5f err + %.5f,  - %.5f \n", d1 - d2, err3.first, err3.second ) ;
     double d3 = ( d1 > d2 ) ? d1 -d2 : 0. ;

     printf("\n === Result from ABCD + Zee =====\n");
     pair<double,double> err4 = ErrApnB( d3, Qd, err3.first, err3.second, err_Qd.first, err_Qd.second) ;
     printf("final = %.5f err + %.5f,  - %.5f, (+%f  -%f)  \n", d3+Qd , err4.first, err4.second, 
                                                      (d3+Qd+err4.first)/(d3+Qd), (d3+Qd-err4.second)/(d3+Qd) ) ;
     printf("  ==================================\n\n");
          

     pair<double,double> err2_ = ErrAxB( Qb5 , c/a, err_Qb5.first, err_Qb5.second, err0.first, err0.second) ;
     printf("(Qb)x(c/a) = %.5f err + %.5f,  - %.5f \n", Qb*c/a, err2_.first, err2_.second ) ;
     d2 = Qb5*c/a ;

     pair<double,double> err3_ = ErrApnB( d1, d2, err1.first, err1.second, err2_.first, err2_.second ) ;
     printf("D  = %.5f err + %.5f,  - %.5f \n", d1 - d2, err3_.first, err3_.second ) ;
     d3 = ( d1 > d2 ) ? d1 -d2 : 0. ;

     printf("\n === Result from ABCD + ABCD =====\n");
     pair<double,double> err4_ = ErrApnB( d3, Qd7, err3_.first, err3_.second, err_Qd7.first, err_Qd7.second) ;
     printf("final = %.5f err + %.5f,  - %.5f, (+%f  -%f) \n", d3+Qd7 , err4_.first, err4_.second,
                                                      (d3+Qd7+err4_.first)/(d3+Qd7), (d3+Qd7-err4_.second)/(d3+Qd7) ) ;
     printf("  ==================================\n\n");
     printf("  ==================================\n");
     
        
}

//pair<double, double> EffError( double N_all, double N_pass ) {
double EffError( double N_all, double N_pass, bool isUp ) {

    if ( N_all < 0.0001 ) {
       return 0. ;
    }

    double eff0 = N_pass / N_all ;
    if ( eff0 > 1. || eff0 < 0. ) {
       return 0. ;
    }
    //cout<<" N_All: "<<N_all <<"  N_pass: "<< N_pass << endl;
    int nStep = 1000 ;
    double step = 1. / (double)nStep ;
    //cout<<" step = "<< step <<endl;
    Double_t par[3] = { 1, N_all, N_pass } ;
    Double_t xL[1] = { eff0 } ;
    Double_t xR[1] = { eff0 } ;
    double IntEff = (N_all+ 1) * step * BinomialErr( xR, par ) ;
    //cout<<" Eff 0th : "<< BinomialErr( xR, par ) << endl ;  

    bool skipR = false ;
    bool skipL = false ;
    Double_t pR = 0. ;
    Double_t pL = 0. ;
    while ( IntEff < 0.683)  {
        if ( !skipR && xR[0] < 1. ) {
           xR[0] +=  step ;
           pR = BinomialErr( xR, par ) ;
           IntEff += (pR*step*(N_all+1) ) ;
           //if ( pR == 0 ) cout<<" ("<< xR[0] <<") --> R : "<< IntEff <<"  pR = "<< pR <<" eff0 = "<< eff0 <<endl ;
        }
        if ( !skipL && xL[0] > 0. && xL[0] > step ) {
           xL[0] -=  step ;
           pL = BinomialErr( xL, par ) ;
           IntEff += (pL*step*(N_all+1) ) ;
           //if ( pL == 0 ) cout<<" ("<< xL[0] <<") <-- L : "<< IntEff <<"  pL = "<< pL <<endl;
        } else {
          //printf(" Int_eff = %.4f, pR = %.4f, pL = %.4f , xR=%.4f, xL=%.4f \n", IntEff, pR, pL, xR[0], xL[0] ) ;
          break ;
        }
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
    double upErr = xR[0] - eff0  ;
    double dnErr = eff0 - xL[0] ;
    //pair<double,double> theErr = make_pair( upErr, dnErr );
    //return theErr ;
    if ( isUp ) return upErr ;
    else        return dnErr ;

}

Double_t BinomialErr( Double_t* x, Double_t* par ) {

  Double_t N_all  = par[1] ;
  Double_t N_pass = par[2] ;

  //Double_t Bxy = TMath::Beta( ( N_pass + 1 ), ( N_all - N_pass + 1 ) ) ;
  //cout<< " Beta(x,y) = "<< Bxy <<endl ;
  //Double_t Cnk = pow(x[0], N_pass ) * pow( (1-x[0]) , (N_all - N_pass) ) ;
  //Double_t prob = par[0]*Cnk / ( Bxy * (N_all + 1. ) );
  double betaPDF = TMath::BetaDist( x[0],  (N_pass + 1) , (N_all - N_pass + 1) ) ;
  Double_t prob = (par[0] / (N_all + 1.) ) * betaPDF ;

  if ( x[0] < 0. || x[0] > 1. ) prob = 0. ;

  return prob ;

}

// Not a correct method if m  < 25
Double_t StatErr( double m, bool upWard ){

  //pair<double,double> pErr ;
  double pErr ;
  double step = 0.01 ;
  // if m < 0.15 , the poisson probablilty will be out of precision 
  if ( m <= 0.15  && upWard ) {
     pErr = 1.;
  }
  else if ( m <= 0.15 && !upWard  ) {
     pErr = m ;
  }
  else if ( m > 100. ) {
     pErr = sqrt(m) ;
  }
  else {

     // -34%
     double k = m ;
     double lm = 0. ;
     double pp = 0. ;
     if ( !upWard ) { 
        while (lm <= 0.34 && k > 0 ) {
              k = k - step ;
              pp = TMath::PoissonI( k, m );
              lm = lm + (pp*step) ;
              //cout<<" k = "<< k <<" , p = "<< pp <<" int_P = "<< lm <<endl;
        }
     } 
     // +34%
     double j = m ;
     double hm = 0 ;
     double hp = 0 ;
     if ( upWard ) { 
        while ( hm <=0.34 && j > 0 ) {
              j = j + step ;
              hp = TMath::Poisson( j, m );
              hm = hm + (hp*step) ;
              if ( hp < 0.00001) { 
                 cout<<" j = "<< j <<" , p = "<< hp <<" int_P = "<< hm <<endl;
                 break ;
              }
        }
     }
     if ( upWard ) pErr = j - m ;
     else          pErr = m - k ;

  }
  return pErr ;

}


pair<double, double> ErrAxB( double A, double B, double u_A, double d_A, double u_B, double d_B ){

    pair<double,double> errA = StatErr1( A ) ;
    pair<double,double> errB = StatErr1( B ) ;

    // Upward fluctuation 
    double sAu = errA.first  ;
    double sBu = errB.first  ;
    double sAp = (u_A != -1 ) ? u_A : sAu ;
    double sBp = (u_B != -1 ) ? u_B : sBu ;

    // Downward fluctuation 
    double sAd = errA.second ;
    double sBd = errB.second ;
    double sAn = (d_A != -1 ) ? d_A : sAd ;
    double sBn = (d_B != -1 ) ? d_B : sBd ;

    //double f = A * B ;
    double s_fp = sqrt( B*B*sAp*sAp + A*A*sBp*sBp ) ;
    double s_fn = sqrt( B*B*sAn*sAn + A*A*sBn*sBn ) ;

    pair<double,double> sf = make_pair( s_fp, s_fn ) ;
     
    return sf ;
}


pair<double, double> ErrAovB( double A, double B, double u_A, double d_A, double u_B, double d_B ){

    pair<double,double> errA = StatErr1( A ) ;
    pair<double,double> errB = StatErr1( B ) ;
    double sAu = errA.first ;
    double sBu = errB.first ;
    double sAd = errA.second ;
    double sBd = errB.second ;

    double sAp = (u_A != -1 ) ? u_A : sAu ;
    double sBp = (u_B != -1 ) ? u_B : sBu ;

    double sAn = (d_A != -1 ) ? d_A : sAd ;
    double sBn = (d_B != -1 ) ? d_B : sBd ;

    double f = A / B ;
    double s_fp = sqrt( (sAp*sAp) + (f*f*sBp*sBp) ) / B ;
    double s_fn = sqrt( (sAn*sAn) + (f*f*sBn*sBn) ) / B ;

    //double sf = (  upWard ) ? s_fp: s_fn ;
    pair<double,double> sf = make_pair( s_fp, s_fn ) ;
    return sf ;

}

pair<double, double> ErrApnB( double A, double B, double u_A, double d_A, double u_B, double d_B ){

    pair<double,double> errA = StatErr1( A ) ;
    pair<double,double> errB = StatErr1( B ) ;
    double sAu = errA.first ;
    double sBu = errB.first ;
    double sAd = errA.second ;
    double sBd = errB.second ;

    double sAp = (u_A != -1 ) ? u_A : sAu  ;
    double sBp = (u_B != -1 ) ? u_B : sBu  ;

    double sAn = (d_A != -1 ) ? d_A : sAd  ;
    double sBn = (d_B != -1 ) ? d_B : sBd  ;

    // f = a+b or a-b
    double s_fp =  sqrt( (sAp*sAp) + (sBp*sBp) ) ;
    double s_fn =  sqrt( (sAn*sAn) + (sBn*sBn) ) ;

    pair<double,double> sf = make_pair( s_fp, s_fn ) ;
    return sf ;
}


// Better(correct) statistic error for poisson statistic 
// This is Pearson's Chi-square Interval 
pair<double, double> StatErr1( double n ) {

    double dm = ( n > 100) ? 0.01 : 0.001 ;
    double m1 = n  ;
    double m2 = ( n > 0. ) ? n : dm ;
    double x1(0.), x2(0.) ;
    double p1(0.), p2(0.) ;

    bool search = true ;
    do {
          
          if ( x1 <= 1. &&  m1 > 0. ) {
             x1 = (n - m1)*(n - m1) / m1 ;
             m1 -= dm ;
             p1 += TMath::PoissonI( n , m1 );
          }
          if ( x2 <= 1. ) {
             x2 = (n - m2)*(n - m2) / m2 ;
             m2 += dm ;
             p2 += TMath::PoissonI( n , m2 );
          }
          if ( m1 == 0 ) p1 += TMath::PoissonI( n , m1 );

          // Since the loop stop at x1 > 1 and x2 > 1 , move one step backward to get the range for x1 < 1 and x2 < 1
          if ( x1 > 1. && x2 > 1. ) {
             search = false ;
       	     m1 += dm ;
	     m2 -= dm ;
          }
          if ( m1 <= 0 && x2 > 1. ) {
             search = false ;
	     m2 -= dm ;
          }
	  //printf(" m1: %.3f, x1: %.3f  m2: %.3f x2: %.3f\n", m1, x1, m2, x2) ;
          

    } while ( search ) ;

    //printf(" m1: %.3f, m= %.3f , m2: %.3f , coverage : %.3f\n", m1, n, m2, (p1+p2)*dm ) ;
    std::pair<double,double> err = make_pair( m2 - n, n - m1 ) ;
    return err ;

}


