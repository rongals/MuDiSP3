// tryurng.h

#ifdef use_namespace
using namespace NEWRAN;
using namespace RBD_STRING;
using namespace RBD_COMMON;
#endif


// print time between construction and destruction
class time_lapse
{
   double start_time;
public:
   time_lapse();
   ~time_lapse();
};

void test1(double);

OstreamWithFormat operator<<( OstreamWithFormat, const ExtReal& );

#ifdef NAMESPACE
}
#endif



// body file: tryurng.cpp
// body file: tryurng1.cpp

