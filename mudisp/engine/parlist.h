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



#ifndef __MUDISP2_PARLIST_HXX
#define __MUDISP2_PARLIST_HXX

#include "param.h"
#include <string>
#include <map>
#include <list>
#include <iostream>
#include <vector>

class ParamList {

private:
  list < GenericParam * > plist;
  map < string , GenericParam *> pmap; 

public:
  ParamList(){}

  void AddParameter( GenericParam & toadd );
  void ReadAllParameters( string filename , vector <string> base_name);
  void DumpAllParameters( ostream & os, vector <string> base_name);
  bool empty();

  template <class PType> void Set(string pName, PType val){

    if (pmap.find(pName)!=pmap.end()) {
      //
      // parameter name found !
      //
      
      GenericParam *t;
      t=pmap[pName];
      
      t->Set(val);
    } 
    else {
      cerr << "Error using SetParamter, " << pName 
	   << " not found." << endl;
    }
  }

  //
  // if found, the parameter is muted and will not appear in the 
  // parameter file
  //
  void ExportParam(string pName);



};

#endif /* __MUDISP_PARLIST_HXX  */
