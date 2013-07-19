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



#include "write.h"

//
// WRITE_DOUBLE
//


void Write::Setup(){
  string fn( fname() );
  if (fn != "cout") {
    ofs.open( fname());
  if (! ofs ) {
    cerr << BlockName << ": error opening "
	 << fn << endl;
    exit(_ERROR_OPEN_FILE_);
  }
}
}


void Write::Run() {

  double a=in1.GetDataObj();
  string fn( fname() );
  
  if (fn == "cout")
	  cout <<  a << " " << endl;
  else
	  ofs <<  a << " " << endl;
}

void Write::Finish(){
  string fn( fname() );
  if (fn != "cout")
	  ofs.close();
}

//
// WRITE_COMPLEX
//

void WriteCx::Setup(){
  string fn( fname() );

  if (fn != "cout") {
  ofs.open( fname()); 

  if (! ofs ) {
    cerr << BlockName << ": error opening "
	 << fn << endl;
    exit(_ERROR_OPEN_FILE_);
  }
}
}


void WriteCx::Run() {

  complex<double> a=in1.GetDataObj();
  string fn( fname() );

  if (fn == "cout")
	  cout <<  a << " " << endl;
  else
	  ofs <<  a << " " << endl;

}

void WriteCx::Finish(){
  string fn( fname() );
  if (fn != "cout")
	  ofs.close();
}

