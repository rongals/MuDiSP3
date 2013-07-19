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



#ifndef __MUDISP2_BLOCK_HXX
#define __MUDISP2_BLOCK_HXX

#include <cstdlib>
#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <map>
#include <deque>

#include <algorithm>


#include "parlist.h"
#include "port.h"
#include "lcm.h"

#define NAMELEN 255

class Block;

//
// Link Class
//
class Link {
public:
  Block &a, &b;
  Port &ap, &bp;

  Link();
  Link(Block & aa, Port & aapp, 
       Block  & bb, Port & bbpp):
    a(aa),b(bb),ap(aapp),bp(bbpp){}

};

//
// TLink Class
//
class TLink {
public:
  Block &a;
  Port &ap, &tp;

  TLink();
  TLink(Block & aa, Port & aapp, 
       Port & ttpp):
    a(aa),ap(aapp),tp(ttpp){}

};


//
// block class declaration
//
class Block {

public:

  //
  // Identity Attributes
  //
  string ClassName;
  unsigned int InstID;
  string BlockName;

  //
  // this map holds the newly generated class types derived from
  // Block
  //
  static map < string , unsigned int> class_names;

  //
  // Runtime Related Attributes
  //
  // the following attributes are manipulated by
  // AddToRunSequence() method

  // run sequence express the order of execution 
  // for the blocks linked to this one
  // each block may be present more than once
  deque < Block * > run_seq;

  // block_map express the list of blocks linked
  // to this one, with the clock rate relative to
  // Run() clock
  map < Block *, unsigned int > block_map;

  // link_list stores the mapping of the registered links
  // along with the rates of the related ports
  //
  deque < Link > link_list;

  // tlink_list stores the mapping of the registered links
  // between the outports and inports and the trans-ports
  //
  deque < TLink > tlink_list;
 
  //
  // Parameters related attributes
  //
  ParamList param_list;


  //
  // Constructors and Methods
  //
  Block();
  Block( const char * );

  virtual ~Block();

  //
  // Runtime
  //
  virtual void Build();
  virtual void _ReadParameters( string filename,
		        vector <string> base_name);
  virtual void _DumpParameters(ostream &os, 
		        vector <string> base_name);
  virtual void _ReadParameters(string filename);
  virtual void _DumpParameters(ostream &os);
  virtual void Setup();
  virtual void Run();
  virtual void Finish();

  //private:

  //
  // Run Sequence Builder
  //
  void AddToRunSequence(Block& blk , int N=1);
  
  template <class DATATYPE> void Connect(Block &b1, 
					 OutPort <DATATYPE> &b1p,
					 Block &b2,
					 InPort <DATATYPE> &b2p){
    
    // blocks registration
    block_map[&b1]=1;
    block_map[&b2]=1;
    
    // link registration
    Link newlink( b1,b1p, b2,b2p);    
    link_list.push_back( newlink );
    
    // do the connection
    b1p.ConnectTo( b2p );

  }
  
  template <class DATATYPE> void Connect(Block &b1, 
					 OutPort <DATATYPE> &b1p,
       					 TransPort <DATATYPE> &tp1){
    
    // blocks registration
    block_map[&b1]=1;
    
    
    // link registration
    TLink newlink( b1,b1p,tp1);    
    tlink_list.push_back( newlink );
    
    // do the connection
    b1p.ConnectTo( tp1 );
  }
  
  template <class DATATYPE> void Connect(TransPort <DATATYPE> &tp1,
					 Block &b1,
					 InPort <DATATYPE> &b1p) {
    
    // blocks registration
    block_map[&b1]=1;
    
    
    // link registration
    TLink newlink(b1,b1p,tp1);
    tlink_list.push_back( newlink );
    
    // do the connection
    tp1.ConnectTo( b1p );
  }
  
  template <class DATATYPE> void DConnect(Block &b1, 
					  OutPort <DATATYPE> &b1p,
					  Block &b2,
					  InPort <DATATYPE> &b2p,
					  DATATYPE init=DATATYPE(0)){
    
    // blocks registration
    block_map[&b1]=1;
    block_map[&b2]=1;
    
    // link registration is not performed for Delayed Links
    
    // do the connection
    b1p.DelayConnectTo( b2p,init );
  }
  
  //
  // Sequence Finder
  //
  void SequenceFinder();

  //
  // Parameters related method
  //

  // add the parameter to the list.
  void AddParameter( GenericParam &par );

  // set statically the param value
  template <class PType > void SetParameter( string pName, 
					    PType  val ){
    param_list.Set(pName,val);
  }

  // the parameter is exported to the container block
  void ExportParameter( string pName );


private:

  //
  // Executer Unary Function
  //
  struct executer : public unary_function<Block *, void>
  {
    void operator()(Block *to_exe) { to_exe->Run(); }
  };

  //
  // MapReset
  //
  void ResetClassNames();

};

#endif /* __MUDISP_BLOCK_HXX */


