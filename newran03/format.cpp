

#define WANT_STREAM
#define WANT_MATH

#include <string.h>     // for strlen

#include "include.h"
#include "str.h"
#include "format.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif


#ifdef use_namespace

OstreamWithFormat& endl(OstreamWithFormat& osf)
   { osf.os << ::endl; return osf; }

OstreamWithFormat& ends(OstreamWithFormat& osf)
   { osf.os << ::ends; return osf; }

OstreamWithFormat& flush(OstreamWithFormat& osf)
   { osf.os << ::flush; return osf; }

#else

OstreamWithFormat& endl(OstreamWithFormat& osf)
   { osf.os << endl; return osf; }

OstreamWithFormat& ends(OstreamWithFormat& osf)
   { osf.os << ends; return osf; }

OstreamWithFormat& flush(OstreamWithFormat& osf)
   { osf.os << flush; return osf; }

#endif


OstreamWithFormat& OstreamWithFormat::operator<<(const char* value)
   { f.StringPrint(os, value, strlen(value)); return *this; }


void Format::FormatOut(ostream& os, double value) const
{
   os << prefix;
   switch (format_type)
   {
      case Format::SIG_FIGS:
         SigFig(os, value, precision);
         break;

      case Format::DEC_FIGS:
         DecFig(os, value, precision);
         break;

      case Format::SCIENTIFIC:
         Scientific(os, value, precision);
         break;

      case Format::INTEGER:
         DecFig(os, value, 0);
         break;
   }
   os << suffix;
}

void Format::IntegerPrint(ostream& os, double value) const
   { os << prefix; DecFig(os, value, 0); os << suffix; }


void Format::StringPrint(ostream& os, const char* value, int size) const
{
   int i;

   // prefix
   os << prefix;

   // will it fit
   if (size > max_width) { ErrorOut(os); return; }

   // padding
   int spaces;
   if (size < min_width) spaces = min_width - size;  else spaces = 0;
   int s1, s2;                                // leading and following spaces
   if (alignment == Format::LEFT) { s1 = 0; s2 = spaces; }
   else if (alignment == Format::RIGHT) { s1 = spaces; s2 = 0; }
   else { s1 = spaces / 2; s2 = spaces - s1; }

   // leading spaces
   for (i = 0; i < s1; i++) os << ' ';

   // the string
   for (i = 0; i < size; i++) os << value[i];

   // trailing blanks
   for (i = 0; i < s2; i++) os << ' ';

   // suffix
   os << suffix;
}

void Format::SigFig(ostream& os, double value, int nsig) const
{
   double v = value;
   if (v == 0.0) { DecFig(os, v, nsig-1); return; }

   // sign
   bool neg;
   if (v < 0) { v = -v; neg = true; }
   else neg = false;

   // exponent - first try
   int ndec = nsig - (int)floor(log10(v)) - 1;    // number of decimals

   // round
   double p = pow(10.0, ndec);                    // 10**ndec
   double rv = floor(v * p + 0.5);                // rounded value

   // exponent - adjust
   if (rv >= pow(10.0, nsig)) { ndec--; p /= 10; rv = floor(v * p + 0.5); }

   // make rounded value
   v = rv / p;
   if (neg) v = -v;

   // width for decimal format
   int w = nsig;
   if (ndec > 0)
   {
      w++;                                        // for decimal
      if (ndec > nsig) w += (ndec - nsig + 1);    // for additional zeros
   }
   else { w -= ndec; ndec = 0; }                  // additional zeros
   if (neg || positive != Format::NX) w++;        // for sign

   // use scientific or decimal format
   // use Scientific
   //    if number is large and won't fit
   //    number is small and won't fit and underflow policy is to use sci.
   if (w > max_width && (underflow_policy == Format::E || ndec == 0))
       Scientific(os, v, nsig);
   else DecFig(os, v, ndec, true);
}

void Format::DecFig(ostream& os, double value, int ndec,
   bool force_decimal) const
{
   int i;
   double v = value;

   // sign
   bool neg;
   if (v < 0) { v = -v; neg = true; } else neg = false;

   // round and break into integer and decimal bits
   double p = pow(10.0,ndec);                     // 10 ** ndec
   double iv; v = modf(v, &iv);                   // integer and decimal parts
   v = floor(v * p + 0.5);                        // rounded decimal part
   if (v >= p) { iv += 1.0; v -= p; }             // decimal part over 1

   // check for underflow
   if (iv == 0 && value != 0.0 && underflow_policy == Format::E
      && !force_decimal)
      { Scientific(os, value, ndec+1); return; }

   // space available for integer part
   int li = max_width - ndec;                     // max space for integer part
   int lj = min_width - ndec;                     // min space for integer part
   if (ndec > 0) { li--; lj--; }                  // space for decimal
   if (neg || positive != Format::NX) { li--; lj--; }
                                                  // space for sign

   if (li < 1) { DecFig(os, value, ndec+li-1, force_decimal); return; }

   String si(li, ' ');
   int nchar = 0;
   for (i = li-1; i >= 0; i--)
   {
      if (iv < 0.5) break;
      nchar++;                                    // chars in integer part
      double x; x = modf(iv/10, &iv);
      si[i] = (char)('0' + (int)floor(x * 10 + 0.5));
   }
   if (iv > 0.5 || li == 0)                       // won't fit
   {
      if (overflow_policy == Format::HASH) ErrorOut(os);
      else  Scientific(os, value, max_width-4);   // maybe do precision better
      return;
   }
   if (nchar == 0) { nchar = 1; si[li-1] = '0'; } // integer part is zero

   int spaces = lj - nchar;                       // number of spaces
   if (spaces < 0) spaces = 0;
   int s1, s2;                                    // leading and following sp
   if (alignment == Format::LEFT) { s1 = 0; s2 = spaces; }
   else if (alignment == Format::RIGHT) { s1 = spaces; s2 = 0; }
   else { s1 = spaces / 2; s2 = spaces - s1; }

   // leading spaces
   for (i = 0; i < s1; i++) os << ' ';

   // sign
   if (neg) os << '-';
   else if (positive == Format::SPACE) os << ' ';
   else if (positive == Format::PLUS) os << '+';

   // integer part
   for (i = 0; i < nchar; i++) os << si[li - nchar + i];

   // decimal part
   if (ndec > 0)
   {
      os << '.';
      String sv(ndec, '0');
      for (i = ndec-1;  i >= 0; i--)
      {
         double x; x = modf(v/10, &v);
         sv[i] = (char)('0' + (int)floor(x * 10 + 0.5));
      }
      for (i = 0; i < ndec; i++) os << sv[i];
   }

   // trailing blanks
   for (i = 0; i < s2; i++) os << ' ';

}

void Format::Scientific(ostream& os, double value, int nsig) const
{
   int i;
   double v = value;

   // check nsig >= 0
   if (nsig < 0) { ErrorOut(os); return; }

   // sign
   bool neg;
   if (v < 0) { v = -v; neg = true; }
   else neg = false;

   // exponent - first try
   int lv;
   if (v == 0.0) lv = 0;
   else lv = (int)floor(log10(v));           // power of 10 - first try
   v /= pow(10.0,lv);                        // normalise by power of 10

   // round
   double p = pow(10.0,nsig-1);              // aiming at nsig-1 decimal places
   double rv = floor(v * p + 0.5);           // rounded value * p

   // exponent - adjust
   if (rv >= 10.0 * p)
      { lv++; v /= 10.0; rv = floor(v * p + 0.5); }

   // will it fit
   int w = nsig;
   if (nsig > 1) w++;                      // for decimal
   if (neg || positive != Format::NX) w++; // for sign
   int np;                                 // decimals in power part
   if (lv >=100 || lv <= -100)
      { if (lv >=1000 || lv <= -1000) np = 4; else np = 3; }
   else np = 2;
   w += np + 2;                            // +2 is for e and sign
   if (w > max_width)
   {
      if (overflow_policy == Format::HASH) { ErrorOut(os); return; }
      nsig -= (w - max_width);               // how many decimals
      if (nsig < 0) { ErrorOut(os); return; }  // can't print
      if (nsig == 0) nsig = 1;               // don't need decimal
      Scientific(os, value, nsig);           // try again with reduced nsig
      return;
   }

   // spaces
   int spaces = min_width - w;
   if (spaces < 0) spaces = 0;
   int s1, s2;                                    // leading and following sp
   if (alignment == Format::LEFT) { s1 = 0; s2 = spaces; }
   else if (alignment == Format::RIGHT) { s1 = spaces; s2 = 0; }
   else { s1 = spaces / 2; s2 = spaces - s1; }

   // leading spaces
   for (i = 0; i < s1; i++) os << ' ';

   // sign
   if (neg) os << '-';
   else if (positive == Format::SPACE) os << ' ';
   else if (positive == Format::PLUS) os << '+';

   // decimal part
   String sv; sv.resize(nsig);
   for (i = nsig-1;  i >= 0; i--)
   {
      double x; x = modf(rv/10, &rv);
      sv[i] = (char)('0' + (int)floor(x * 10 + 0.5));
   }
   os << sv[0];                            // first digit
   if (nsig > 1)                           // need decimal
      { os << '.'; for (int i = 1; i < nsig; i++) os << sv[i]; }

   // power part
   os << 'e';
   if (lv >= 0) os << '+'; else { os << '-'; lv = -lv; }
   sv.resize(np);
   for (i = np-1; i >= 0; i--)
   {
      int lv1 = lv / 10; int x = lv - lv1 * 10; lv = lv1;
      sv[i] = (char)('0' + x);
   }
   for (i = 0; i < np; i++) os << sv[i];

   // trailing blanks
   for (i = 0; i < s2; i++) os << ' ';
}

void Format::ErrorOut(ostream& os) const
{
   if (min_width == 0) os << '#';
   else { for (int i = 0; i < min_width; i++) os << '#'; }
}


#ifdef use_namespace
}
#endif

