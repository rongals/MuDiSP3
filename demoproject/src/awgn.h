//
// MuDiSP2
// Multirate Digital Signal Processor 2
// By Luca Simone Ronga (C) Apr 1999
// 
//

#ifndef __MUDISP2_AWGN_H 
#define __MUDISP2_AWGN_H

#include "mudisp.h"
#include "tnt.h"
#include "cmat.h"
#include <complex>

using namespace std;
using namespace TNT;


////////
////////   Here put your personal includes
////////


class AWGN : public Block {
private:

////////   Parameters instances

  FloatParam noisevar;

////////   Local Attributes

  unsigned int Nin;
  double noisestd;

public:

////////   InPorts and OutPorts

  InPort < Matrix <complex <double > > > *in;
  OutPort < Matrix <complex <double > > > vout1;  



  AWGN(int numin = 1 ):Block("AWGN")
    
////////  parameters initializazion
    ,Nin(numin)
    ,noisevar("Variance",0.5,"gaussian noise variance (linear)")

    {

//////// local parameter registration

      AddParameter(noisevar);

      in=new InPort < Matrix <complex <double > > >[numin];

    }

  ~AWGN() {
    delete [] in;
  }

  void Setup();
  void Run();


  
};

#endif /* __MUDISP_MYBLOCK_H  */

