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

/*!
  \file derandom.cc
*/

/*
 $Id: rndgen.cpp,v 1.1.1.1 2002/09/11 07:18:36 ronga Exp $ 
*/

#include "rndgen.h"


void SetSeed(int seed1, int seed2) 
{ 
  setall(seed1, seed2); 
}

// generic functions w/o initalizers 
double rndUniformDouble(double low, double high) 
{ 
  return genunf(low, high); 
}

long int rndUniformInt(long int low, long int high) 
{ 
  return ignuin(low, high); 
}

double rndExponential(double M) 
{ 
  return genexp(M); 
}

double rndGaussian(double M, double sigma) 
{ 
  return gennor(M, sigma); 
}

unsigned int rndGeometric0(double M)
{
  double p = M / (M + 1);        // Mean = p/(1-p)
  return (M > 0) ? (unsigned int)(floor(log(1.0 - ranf()) / log(p))) : 0;
}

unsigned int rndGeometric1(double M)
{
  double p = (M - 1) / M;        // Mean = 1/(1-p)
  return (M > 1) ? (unsigned int)(floor(log(1.0 - ranf()) / log(p))) + 1 : 1;
}

long int  NegativeBinomial(long r, float p)
{
  return ignnbn(r,p);
}

double rndPareto(double location, double shape)
{
  return location*pow(double(genunf(0,1)),-1./shape);
}

double rndWeibull(double location, double scale, double shape)
{
  return ( location + scale*pow(-log(double(genunf(0,1))), 1./shape) );
}


/*
$Log: rndgen.cpp,v $
Revision 1.1.1.1  2002/09/11 07:18:36  ronga


Revision 1.4  2002/07/26 13:24:34  pecos
Added Negative Binomial distribution

Revision 1.1  2002/07/26 13:20:32  pecos
*** empty log message ***

Revision 1.3  2000/10/22 19:47:49  pecos
no message

Revision 1.2  2000/02/24 08:36:21  pecos
no message

Revision 1.1.1.1  1999/05/24 15:59:57  inesis
INeSiS Project

Revision 1.1.1.1  1999/05/24 15:17:20  inesis
INeSiS Project

Revision 1.2  1999/01/26 11:24:23  pecos
*** empty log message ***

Revision 1.3  1998/10/04 16:24:46  nanni
*** empty log message ***

Revision 1.2  1998/09/29 18:56:38  nanni
*** empty log message ***

Revision 1.1  1998/09/15 15:20:24  ronga
Initial revision

*/

