//
// MuDiSP2
// Multirate Digital Signal Processor 2
// By Luca Simone Ronga (C) Apr 1999
// 
//

#include "bitsrc.h"


void BitSource::Setup() {

//////// initialization of dynamic data structures


//////// rate declaration for ports



}


void BitSource::Run() {


//////// production of data
  int tmp = rndUniformInt();
  out1.DeliverDataObj( tmp );

}

