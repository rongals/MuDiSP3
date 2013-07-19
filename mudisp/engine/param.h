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



#ifndef __MUDISP2_PARAM_HXX
#define __MUDISP2_PARAM_HXX

#define NAME_FIELD 40
#define VALUE_FIELD 15
#define MAXLINEL 255
#define MAXSTRINGL 128


#include "errors.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;


class GenericParam {

private:

  //
  // True if the parameter has been set by hand
  //
  bool isMuted;

  //
  // True if the parameter needs to read the file but does
  // not appear in the param file
  //
  bool isExported;

public:
  //
  // name of the parameter
  //
  string ParamName;

  //
  // description of the parameter
  //
  string ParamDesc;


  GenericParam(): isMuted(false), isExported(false) {}
  GenericParam(const char *name,const char *desc);
  
  virtual ~GenericParam(){}

  //
  // Default line dump in parameter file 
  //
  virtual void DumpString( ostream & , vector <string> base_name ){}
  virtual void Read( string filename , vector <string> base_name ){}
  virtual void Set(const int &val){} 
  virtual void Set(const double &val){} 
  virtual void Set(const char *val){}

  bool isMute(){ return isMuted; }
  void Mute() { isMuted=true; }
  bool Exported(){ return isExported; }
  void Export() { isExported=true; }

};


class IntParam : public GenericParam {
public:
  int Value;

  IntParam(){}
  IntParam(const char*, const int &, const char* desc="");
  ~IntParam(){}
  
  int operator()(){ return Value; }
  
  void DumpString( ostream & os ,   vector <string> base_name );
  void Read( string filename , vector <string> base_name );

  void Set(const int & val);

};

class FloatParam : public GenericParam {
public:
  double Value;

  FloatParam(){}
  FloatParam(const char*, const double &, const char* desc="");
  ~FloatParam();
  
  double operator()(){ return Value; }
  
  void DumpString( ostream & os ,   vector <string> base_name );
  void Read( string filename , vector <string> base_name );
  void Set(const double & val);


};

class StringParam : public GenericParam {
public:
  char Value[MAXSTRINGL];

  StringParam(){}
  StringParam(const char*, const char * , const char* desc="");
  ~StringParam();
  
  const char *operator()(){ return Value; }

  void DumpString( ostream & os , vector <string> base_name );
  void Read( string filename , vector <string> base_name );
  void Set( const char * val );


};


#endif /* __MUDISP_PARAM_HXX  */

