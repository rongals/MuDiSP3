//
// MuDiSP3 (Multirate Digital Signal Processor 3)
// Copyright 1999, Luca Simone Ronga
//
//
//  This file is part of MuDiSP3.
//
//  MuDiSP3 is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  MuDiSP3 is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with MuDiSP3; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
/////////////////////////////////////////////////////////



#ifndef __MUDISP2_PORT_HXX
#define __MUDISP2_PORT_HXX


#include <stack>
#include <list>
#include <queue>

using namespace std;

class Port {
protected:
  unsigned int rate;
public:
  Port(unsigned int rt):rate(rt){}

  unsigned int GetRate(){ return rate; };
  void SetRate( unsigned int rt ){ rate=rt; }
};

template <class DATATYPE> class InPort;

//
// OutPort objects store the data object 
// produced by blocks.
template <class DATATYPE> class OutPort : virtual public Port {
  
private:
  // 
  // Data Delivery List
  //
  list < InPort <DATATYPE> * > deliv_list;

public:
  //
  // contructors
  //
  OutPort(unsigned int rt=1 ):
    Port(rt){}

  //
  // Connection Builder
  //
  void ConnectTo( InPort <DATATYPE> & dest) {
    deliv_list.push_front( &dest );
  }
  
  //
  // Delayed Connection Builder
  //
  void DelayConnectTo( InPort <DATATYPE> & dest, 
		       DATATYPE init=DATATYPE(0) ) {
    deliv_list.push_front( &dest );
    dest.PutDataObj(init);
  }
  



  //
  // Data Access Functions
  // the block which owns the port put the data
  void DeliverDataObj( const DATATYPE & dt ) {
    typename list< InPort <DATATYPE> * >::iterator i = deliv_list.begin();
    for (unsigned int n=deliv_list.size();n>0;n--) {
      (*i++)->PutDataObj(dt);
    }
  }


}; 

//
// InPort objects store the data object 
// to be consumed. Data are pushed by the
// OutPorts
template <class DATATYPE> class InPort : virtual public Port {
  
private:
  //
  // Queue Data Repository
  //
  queue < DATATYPE > port_data_buffer;

public:
  //
  // contructors
  //
  InPort(unsigned int rt=1):
    Port(rt){}


    virtual ~InPort(){};
  
    //
    // Data Access Functions
    //
    // the block which owns the port put the data
    virtual void PutDataObj( const DATATYPE & data) {
      port_data_buffer.push(data);
    }
    
    // the receiving blocks access it
    DATATYPE GetDataObj(){
      DATATYPE data=port_data_buffer.front();
      port_data_buffer.pop();
      return data;
    }
    
}; 


template <class DATATYPE> class TransPort : public InPort <DATATYPE>,
  public OutPort <DATATYPE> {

  public:
  //
  // contructors
  //
  TransPort(unsigned int rt=1):
    Port(rt){}

  //
  // Data Access Functions
  // a transport forward the data to the connected sub-blocks
  //
  void PutDataObj( const DATATYPE & data) {
    DeliverDataObj( data );
  }
};


#endif /* __MUDISP_PORT_HXX */
