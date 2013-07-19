//
// MuDiSP3 (Multirate Digital Signal Processor 3)
// Copyright 1999,2005 Luca Simone Ronga
//
// Contributor: Simone Menci
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
//
//
//
//

#ifndef __FILTRO_H
#define __FILTRO_H

#include <iostream>
#include <fstream> 
#include <stdlib.h> 
#include <complex>

using namespace std;

//
// FILTER_DOUBLE
//

class Filter {
  public:
    Filter() {};
    virtual double filtra(const double &s)=0;
    virtual ~Filter(){};

  protected:
    double *coeff_b, *coeff_a;
    double *mem_b, *mem_a;
};


class IIR : public Filter {
  private:
	int lb, la;

  public:
	IIR();
	IIR(double *b, double *a, const int lb, const int la );
	IIR(const char *bfname, const char *afname);
	double filtra(const double &val);
	~IIR();
};


class FIR : public Filter {
  private:
	int lb;

  public:
	FIR();
	FIR(double *b, const int b_length);
	FIR(const char *bfname);
	double filtra(const double &val);
	~FIR();
};


//
// FILTER_COMPLEX
//

class FilterCx {
  public:
    FilterCx() {};
    virtual complex < double > filtracx(const complex < double > &s)=0;
    virtual ~FilterCx(){};

  protected:
	double *coeff_b, *coeff_a;
	complex < double > *mem_bx, *mem_ax;
};


class IIRCx : public FilterCx {
  private:
	int lb, la;

  public:
	IIRCx(){};
	IIRCx(double *b, double *a, const int lb, const int la );
	IIRCx(const char *bfname, const char *afname);
	complex < double > filtracx(const complex < double > &val);
	~IIRCx();
};


class FIRCx : public FilterCx {
  private:
	int lb;

  public:
	FIRCx(){};
	FIRCx(double *b, const int b_length);
	FIRCx(const char *bfname);
    complex < double > filtracx(const complex < double > &val);
	~FIRCx();
};


#endif //  __FILTRO_H
