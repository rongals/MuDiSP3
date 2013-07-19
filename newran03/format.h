#ifndef FORMAT_LIB
#define FORMAT_LIB

#include "str.h"

#ifdef use_namespace
namespace RBD_STRING { using namespace RBD_COMMON; }
namespace RBD_LIBRARIES { using namespace RBD_STRING; }
namespace RBD_STRING {
#endif


class Format
{
public:
   enum OUF {E, HASH, ZERO};
   enum A {LEFT, RIGHT, CENTRE, CENTER};
   enum FT {SIG_FIGS, DEC_FIGS, SCIENTIFIC, INTEGER};
   enum POS {PLUS, SPACE, NX};
private:
   int min_width;
   int max_width;
   OUF overflow_policy;
   OUF underflow_policy;
   A alignment;
   FT format_type;
   int precision;
   POS positive;
   String prefix;
   String suffix;
   String separator;
public:
   Format() : min_width(0), max_width(12), overflow_policy(E),
      underflow_policy(ZERO), alignment(RIGHT),
      format_type(SIG_FIGS), precision(2), positive(NX),
      prefix(""), suffix(""), separator(",") {}
   int MinWidth() const { return min_width; }
   void MinWidth(int mw) { min_width = mw; }
   int MaxWidth() const { return max_width; }
   void MaxWidth(int mw) { max_width = mw; }
   void Width(int w) { max_width = min_width = w; }
   OUF OverFlowPolicy() const { return overflow_policy; }
   void OverFlowPolicy(OUF of) { overflow_policy = of; }
   OUF UnderFlowPolicy() const { return underflow_policy; }
   void UnderFlowPolicy(OUF uf) { underflow_policy = uf; }
   A Alignment() const { return alignment; }
   void Alignment (A a) { alignment = a; }
   FT FormatType() const { return format_type; }
   void FormatType (FT ft) { format_type = ft; }
   POS Positive() const { return positive; }
   void Positive(POS p) { positive = p; }
   int Precision() const { return precision; }
   void Precision(int p) { precision = p; }
   String Prefix() const { return prefix; }
   void Prefix(const String& p) { prefix = p; }
   String Suffix() const { return suffix; }
   void Suffix(const String& s) { suffix = s; }
   String Separator() const { return separator; }
   void Separator(const String& s) { separator = s; }
   friend class OstreamWithFormat;
private:
   void SigFig(ostream& os, double value, int nsig) const;
   void DecFig(ostream& os, double value, int ndec, bool force_decimal=false)
      const;
   void IntegerPrint(ostream& os, double value) const;
   void Scientific(ostream& os, double value, int nsig) const;

   void FormatOut(ostream& os, double value) const;

   void StringPrint(ostream& os, const char* value, int size) const;

   void ErrorOut(ostream& os) const;
};

class OstreamWithFormat
{
   ostream& os;
   const Format& f;
public:
   OstreamWithFormat(ostream& osx, const Format& fx)
      : os(osx), f(fx) {}

   OstreamWithFormat& operator<<(const char* value);

   OstreamWithFormat& operator<<(const String& value)
      { f.StringPrint(os, value.data(), value.size()); return *this; }

   OstreamWithFormat& operator<<(int value)
      { f.IntegerPrint(os, (double)value); return *this; }

   OstreamWithFormat& operator<<(unsigned int value)
      { f.IntegerPrint(os, (double)value); return *this; }

   OstreamWithFormat& operator<<(double value)
      { f.FormatOut(os, value); return *this; }

   OstreamWithFormat& operator<<(float value)
      { return operator<<((double)value); }

   OstreamWithFormat& operator<<(long value)
      { f.IntegerPrint(os, (double)value); return *this; }

   OstreamWithFormat& operator<<(unsigned long value)
      { f.IntegerPrint(os, (double)value); return *this; }

   OstreamWithFormat& operator<<(char value) { os << value; return *this; }

   OstreamWithFormat& operator<< (OstreamWithFormat& (*_f)(OstreamWithFormat&))
      { _f(*this); return *this; }

   friend OstreamWithFormat operator<<(ostream& osx, const Format& fx)
      { return OstreamWithFormat(osx, fx); }
   friend OstreamWithFormat operator<<(OstreamWithFormat& osx, const Format& fx)
      { return OstreamWithFormat(osx.os, fx); }

   friend OstreamWithFormat& endl(OstreamWithFormat&);
   friend OstreamWithFormat& ends(OstreamWithFormat&);
   friend OstreamWithFormat& flush(OstreamWithFormat&);
};

#ifdef use_namespace
}
#endif


#endif

// body file: format.cpp



