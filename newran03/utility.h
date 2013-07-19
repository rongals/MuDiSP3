//file utility.h   -  some statistical special functions

// some miscellanous functions I need
// The small ones (square and cube) are compiled inline so I give their
// full details here.
// The large one(s) (invchi95) are compiled separately so I give just the
// definition and the actual code is in utility.cpp


// C and C++ don't provide the exponentiation operator (** in Fortran)
// so I provide a function for taking squares and cubes of numbers.

#ifndef UTILITY_H
#define UTILITY_H

#ifdef use_namespace
using namespace RBD_COMMON;
#endif


inline double square(double x) { return x*x; }     // return x times x

inline double cube(double x) { return x*x*x; }     // return x times x times x

inline long iround(double x) { return (long)floor(x + 0.5); }
                                                   // rounded version of x


// Calculate 95% point of chi-squared distribution

double invchi95(int N);


// Calculate 99% point of chi-squared distribution

double invchi99(int N);


// Calculate 99.9% point of chi-squared distribution

double invchi999(int N);


// inverse of chisquared distribution
Real invchi(Real p, int df, bool upper = false);


// cdf of normal distribution function
double cdfnml(double x);

// inverse cdf of normal distribution function
double invcdfnml(double p);


// chi-squared distribution function
double cdf_chisq(double x, int df, bool upper=false);


// upper tail probabilities for 2 sided Kolmogorov-Smirnov test
double KS_probabilities(double z);






#endif


// body file: utility.cpp


