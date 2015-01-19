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
     // Scale factor for background template
     /*
     double sf = 1033000./1838000. ;
     pair<double,double> err_sf = ErrAovB( 1033000, 1838000, -1, -1, -1, -1 ) ;
     printf("scaleFactor = %.5f err + %.5f,  - %.5f \n", sf, err_sf.first, err_sf.second ) ;
     // Toal - Scaled Background for |t| < 2ns
     double InT_Bg = 5062600*sf ;
     pair<double,double> err_b1 = ErrAxB( 5062600, sf , -1, -1, err_sf.first, err_sf.second ) ;
     printf("InTime Bg = %.5f err + %.5f,  - %.5f \n", InT_Bg, err_b1.first, err_b1.second ) ;

     double InT = 5195700 - InT_Bg ;
     pair<double,double> err_InT = ErrApnB( 5195700, InT_Bg, -1, -1, err_b1.first, err_b1.second ) ;
     printf("InTime Z - Bg = %.5f err + %.5f,  - %.5f \n", InT, err_InT.first, err_InT.second ) ;
     // Toal - Scaled Background for t > 3ns
     double OuT_Bg = 42*sf ;
     pair<double,double> err_b2 = ErrAxB( 42, sf , -1, -1, err_sf.first, err_sf.second ) ;
     printf("OuTime Bg = %.5f err + %.5f,  - %.5f \n", OuT_Bg, err_b2.first, err_b2.second ) ;

     double OuT = 54 - OuT_Bg ;
     pair<double,double> err_OuT = ErrApnB( 54, OuT_Bg, -1, -1, err_b2.first, err_b2.second ) ;
     printf("OuTime Z - Bg = %.5f err + %.5f,  - %.5f \n", OuT, err_OuT.first, err_OuT.second ) ;
     // Given ratio of |t|<2 / t > 3
     double r = OuT/InT ;
     pair<double,double> err_r = ErrAovB( OuT, InT, err_OuT.first, err_OuT.second , err_InT.first, err_InT.second ) ;
     printf("Ratio = %.8f err + %.8f,  - %.8f \n", r, err_r.first, err_r.second ) ;
     // Predict
     double final= 29702*r ;
     pair<double,double> err = ErrAxB( 29702, r , -1, -1, err_r.first, err_r.second ) ;
     printf("Predict = %.5f err + %.5f,  - %.5f \n", final, err.first, err.second ) ;
     */

     //  Closure Test
     /*
     double f = 34047 ;
     pair<double,double> err_f = StatErr1( f ) ; 
     double f_u = err_f.first ;
     double f_d = err_f.second ;
     printf("f = %.3f err + %.3f,  - %.3f \n", f, f_u , f_d ) ;

     double fp = 1383015 ;
     pair<double,double> err_fp = StatErr1( fp ) ; 
     double fp_u = err_fp.first ;
     double fp_d = err_fp.second ;
     printf("fp = %.3f err + %.3f,  - %.3f \n", fp, fp_u, fp_d  ) ;

     pair<double,double> err_f = ErrAovB( f, fp, -1, -1, -1, -1 ) ;
     printf("f/fp = %.5f err + %.5f,  - %.5f \n", f/fp, err_f.first, err_f.second ) ;

     double bp = 7. ;
     pair<double,double> err_bp = StatErr1( bp ) ; 
     double bp_u = err_bp.first ;
     double bp_d = err_bp.second ;
     printf("bp = %.3f err + %.3f,  - %.3f \n", bp, bp_u, bp_d  ) ;

     pair<double,double> err_Qb = ErrAxB( bp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qb = bp*f/fp ;
     printf("bp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qb, err_Qb.first, err_Qb.second ) ;

     double dp = 2. ;
     pair<double,double> err_dp = StatErr1( dp ) ; 
     double dp_u = err_dp.first ;
     double dp_d = err_dp.second ;
     printf("dp = %.3f err + %.3f,  - %.3f \n", dp, dp_u, dp_d  ) ;

     pair<double,double> err_Qd = ErrAxB( dp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qd = dp*f/fp ;
     printf("dp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qd, err_Qd.first, err_Qd.second ) ;

     double c = 359. ;
     pair<double,double> err_c = StatErr1( c ) ; 
     double c_u = err_c.first ;
     double c_d = err_c.second ;
     printf("c = %.3f err + %.3f,  - %.3f \n", c, c_u , c_d ) ;

     double a = 850. ;
     pair<double,double> err_a = StatErr1( a ) ; 
     double a_u = err_a.first ;
     double a_d = err_a.second ;
     printf("a = %.3f err + %.3f,  - %.3f \n", a, a_u, a_d  ) ;

     pair<double,double> err0 = ErrAovB( c, a, -1, -1, -1, -1 ) ;
     printf("c/a = %.5f err + %.5f,  - %.5f \n", c/a, err0.first, err0.second ) ;

     double b = 39. ;
     pair<double,double> err_b = StatErr1( b ) ; 
     double b_u = err_b.first ;
     double b_d = err_b.second ;
     printf("b = %.3f err + %.3f,  - %.3f \n", b, b_u, b_d  ) ;

     // Qb = 0.1176 +0.1138 -0.0694
     pair<double,double> err1 = ErrApnB( b, Qb, -1, -1, err_Qb.first, err_Qb.second ) ;
     printf("b - Qb = %.5f err + %.5f,  - %.5f \n", b -Qb, err1.first, err1.second ) ;

     pair<double,double> err2 = ErrAxB( b - Qb , c/a, err1.first, err1.second, err0.first, err0.second) ;
     printf("(b-Qb)x(c/a) = %.5f err + %.5f,  - %.5f \n", (b -Qb)*c/a, err2.first, err2.second ) ;
     double d1 = (b -Qb)*c/a ;

     // Qd = 0.0888 +0.0888 -0.0444
     pair<double,double> err3 = ErrApnB( d1, Qd, err2.first, err2.second, err_Qd.first, err_Qd.second) ;
     printf("\nfinal = %.5f err + %.5f,  - %.5f \n", d1+Qd , err3.first, err3.second ) ;
     */


     // 2J events
     
     double f = 29702 ;
     pair<double,double> err_f = StatErr1( f ) ; 
     double f_u = err_f.first ;
     double f_d = err_f.second ;
     printf("f = %.3f err + %.3f,  - %.3f \n", f, f_u , f_d ) ;

     double fp = 669013 ;
     pair<double,double> err_fp = StatErr1( fp ) ; 
     double fp_u = err_fp.first ;
     double fp_d = err_fp.second ;
     printf("fp = %.3f err + %.3f,  - %.3f \n", fp, fp_u, fp_d  ) ;

     pair<double,double> err_f = ErrAovB( f, fp, -1, -1, -1, -1 ) ;
     printf("f/fp = %.5f err + %.5f,  - %.5f \n", f/fp, err_f.first, err_f.second ) ;

     double bp = 4. ;
     pair<double,double> err_bp = StatErr1( bp ) ; 
     double bp_u = err_bp.first ;
     double bp_d = err_bp.second ;
     printf("bp = %.3f err + %.3f,  - %.3f \n", bp, bp_u, bp_d  ) ;

     pair<double,double> err_Qb = ErrAxB( bp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qb = bp*f/fp ;
     printf("bp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qb, err_Qb.first, err_Qb.second ) ;

     double dp = 2. ;
     pair<double,double> err_dp = StatErr1( dp ) ; 
     double dp_u = err_dp.first ;
     double dp_d = err_dp.second ;
     printf("dp = %.3f err + %.3f,  - %.3f \n", dp, dp_u, dp_d  ) ;

     pair<double,double> err_Qd = ErrAxB( dp , f/fp, -1, -1, err_f.first, err_f.second) ;
     double Qd = dp*f/fp ;
     printf("dp(f/fp) = %.5f err + %.5f,  - %.5f \n\n", Qd, err_Qd.first, err_Qd.second ) ;

     double c = 0. ;
     pair<double,double> err_c = StatErr1( c ) ; 
     double c_u = err_c.first ;
     double c_d = err_c.second ;
     printf("c = %.3f err + %.3f,  - %.3f \n", c, c_u , c_d ) ;

     double a = 5. ;
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

     // Qb = 0.1176 +0.1138 -0.0694
     pair<double,double> err1 = ErrApnB( b, Qb, -1, -1, err_Qb.first, err_Qb.second ) ;
     printf("b - Qb = %.5f err + %.5f,  - %.5f \n", b -Qb, err1.first, err1.second ) ;

     pair<double,double> err2 = ErrAxB( b - Qb , c/a, err1.first, err1.second, err0.first, err0.second) ;
     printf("(b-Qb)x(c/a) = %.5f err + %.5f,  - %.5f \n", (b -Qb)*c/a, err2.first, err2.second ) ;
     double d1 = (b -Qb)*c/a ;

     // Qd = 0.0888 +0.0888 -0.0444
     pair<double,double> err3 = ErrApnB( d1, Qd, err2.first, err2.second, err_Qd.first, err_Qd.second) ;
     printf("\nfinal = %.5f err + %.5f,  - %.5f \n", d1+Qd , err3.first, err3.second ) ;
     

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


