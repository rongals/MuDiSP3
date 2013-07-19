//
// MuDiSP2
// Multirate Digital Signal Processor 2
// By Luca Simone Ronga (C) Apr 1999
// 
//


#include "awgn.h"


void AWGN::Setup() {

//////// initialization of dynamic data structures

  noisestd = sqrt( noisevar() );

//////// rate declaration for ports


}


void AWGN::Run() {

//////// fetch data objects

  Matrix <complex <double > > tmp =  in[0].GetDataObj();

  for (int i = 1; i< Nin; i++) {
     Matrix <complex <double > > obj =  in[i].GetDataObj();
     tmp =  Matrix <complex <double > >(obj + tmp);
  }



  for (int i=0; i< tmp.num_rows(); i++)
    for (int j=0; j< tmp.num_cols(); j++) {
      complex <double> n( rndGaussian(0.0, noisestd),
			  rndGaussian(0.0, noisestd));
      tmp[i][j] += n;
    }
  
//////// production of data

  vout1.DeliverDataObj( tmp );

}

