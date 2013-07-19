/*!
  \file rndgen.h
*/

/*
 $Id: rndgen.h,v 1.1.1.1 2002/09/11 07:18:36 ronga Exp $ 
*/

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


#include <stdlib.h>
#include <math.h>

#include "randlib.h"

#ifndef ___RNDGEN_H___
#define ___RNDGEN_H___


void SetSeed(int seed1, int seed2);

////////////////////////////////////////////////////////////////////////////////
// generic functions w/o initalizers 
double rndUniformDouble(double low=0.0, double high=1.0);

long int rndUniformInt(long int low=0, long int high=1);

double rndExponential(double M);

double rndGaussian(double M, double sigma);

unsigned int rndGeometric0(double M);

unsigned int rndGeometric1(double M);


/***********************************************************************
*                                                                      *
*   Negative Binomial distribution                                     *       *                                                                      *
*                                                                      *
*     p(k) = (k + r -1 ) * p^r * (1-p)^k                               *
*            (    k    )                                               *
*                                                                      *
*     mean     = r*(1-p)/p                                             *
*     variance = r*(1-p)/p^2                                           *
*                                                                      *
***********************************************************************/
long int NegativeBinomial(long r, float p);


/***********************************************************************
*                                                                      *
*   Pareto distribution                                                *
*                                                                      *
*     p(x) = (shape * location^shape)/(x^(shape+1))                    *
*     P(x) = 1 - (location/x)^shape                                    *
*     mean     = location * shape / (shape - 1)                        *
*     variance = location^2 * shape / ( (shape -2) * (shape - 1)^2 )   *
*                                                                      *
***********************************************************************/
double rndPareto(double location, double shape);
	

/**************************************************************************
*                                                                         *
*   Weibull distribution                                                  *
*                                                                         *
*        l = location, sh = shape, sc = scale, Gamma() = Gamma function   *
*     p(x) = sh/sc * ((x-l)/sc)^(sh-1) * e^(-((x-l)/sc)^sh)               *
*     P(x) = 1 - e^(-((x-l)/sc)^sh)                                       *
*     mean     = l + sc*Gamma((sh+1)/sh)                                  *
*     variance = sc^2 * ( Gamma((sh+2)/sh) - Gamma^2((sh+1)/sh) )         *
*                                                                         *
**************************************************************************/
double rndWeibull(double location, double scale, double shape);


////////////////////////////////////////////////////////////////////////////////
//
class UniformDoubleRndGen
{
protected:
  double low, high;

public:
  UniformDoubleRndGen(double _low=0, double _high=1) : low(_low), high(_high) {};
  double get() { return genunf(low, high); };
};

////////////////////////////////////////////////////////////////////////////////
//
class UniformIntRndGen
{
protected:
  long int low, high;

public:
  UniformIntRndGen(long int _low=0, long int _high=1) : low(_low), high(_high) {};
  long int get() { return ignuin(low, high); };
};

////////////////////////////////////////////////////////////////////////////////
//
class ExponentialRndGen
{
protected:
  double mean;

public:
  ExponentialRndGen(double _mean=0) : mean(_mean) {};
  double get() { return genexp(mean); };
};

////////////////////////////////////////////////////////////////////////////////
//
class GaussianRndGen
{
protected:
  double mean, sigma;

public:
  GaussianRndGen(double _mean=0, double _sigma=0) : mean(_mean), sigma(_sigma) {};
  double get() { return gennor(mean, sigma); };
};

////////////////////////////////////////////////////////////////////////////////
//
class Geometric0RndGen
{
protected:
  double mean;
  double log_mean;

public:
  Geometric0RndGen(double _mean=0) 
    : mean(_mean)
  {
    if( _mean > 0 )
      log_mean = log(_mean / (_mean + 1));
  };

  unsigned long int get() 
  { 
    return ((mean > 0) ? (unsigned long int)(floor(log(1.0 - ranf()) / log_mean)) : 0);
  };
};

////////////////////////////////////////////////////////////////////////////////
//
class Geometric1RndGen
{
protected:
  double mean;
  double log_mean;

public:
  Geometric1RndGen(double _mean=1) 
    : mean(_mean)
  {
    if( _mean > 1 )
      log_mean = log((_mean -1) / _mean);
  };

  unsigned long int get() 
  { 
    return ((mean > 1) ? (unsigned long int)(floor(log(1.0 - ranf()) / log_mean)) + 1 : 1 );
  };
};

////////////////////////////////////////////////////////////////////////////////
//
class ParetoRndGen
{
protected:
  double location;
  double shape;

public:
  ParetoRndGen(double _location=1, double _shape=1) 
    : location(_location), shape(_shape)
  {};

  double get() 
  { 
    return rndPareto(location, shape);
  };
};

////////////////////////////////////////////////////////////////////////////////
//
class WeibullRndGen
{
protected:
  double location;
  double scale;
  double shape;

public:
  WeibullRndGen(double _location=1, double _scale=1, double _shape=1) 
    : location(_location), scale(_scale), shape(_shape)
  {};

  double get() 
  { 
    return rndWeibull(location, scale, shape);
  };
};

#endif


/*
$Log: rndgen.h,v $
Revision 1.1.1.1  2002/09/11 07:18:36  ronga


Revision 1.6  2002/07/26 13:24:34  pecos
Added Negative Binomial distribution

Revision 1.1  2002/07/26 13:20:33  pecos
*** empty log message ***

Revision 1.5  2001/03/17 09:47:56  pecos
Added default params for Pareto and Weibull

Revision 1.4  2000/02/24 08:36:21  pecos
no message

Revision 1.3  1999/09/11 09:14:13  pecos
*** empty log message ***

Revision 1.2  1999/05/28 23:54:48  pecos
no message

Revision 1.1.1.1  1999/05/24 15:59:57  inesis
INeSiS Project

Revision 1.1.1.1  1999/05/24 15:17:20  inesis
INeSiS Project

Revision 1.2  1999/01/26 11:24:23  pecos
*** empty log message ***

Revision 1.2  1998/09/29 18:56:53  nanni
*** empty log message ***

Revision 1.1  1998/09/15 15:20:24  ronga
Initial revision

*/

