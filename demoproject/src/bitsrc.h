//
// MuDiSP2
// Multirate Digital Signal Processor 2
// By Luca Simone Ronga (C) Apr 1999
// 
//


#ifndef __MUDISP2_BITSRC_H 
#define __MUDISP2_BITSRC_H

#include "mudisp.h"

////////
////////   Here put your personal includes
////////


class BitSource : public Block {
private:

////////   Parameters instances


////////   Local Attributes

public:

////////   InPorts and OutPorts

  OutPort <unsigned int> out1;  



  BitSource():Block("BitSource")
    
////////  parameters initializazion


    {

//////// local parameter registration


    }

  void Setup();
  void Run();
  
};

#endif /* __MUDISP_MYBLOCK_H  */

