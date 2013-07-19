// tryrand.h

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

void test1(int);
void test2(int);
void test3(int);
void test4(int);
void test5(int);
void test6(int);
void Histogram(Random*, int);          // draw histogram with n obsv

OstreamWithFormat operator<<( OstreamWithFormat, const ExtReal& );




// body file: tryrand1.cpp
// body file: tryrand2.cpp
// body file: tryrand3.cpp
// body file: tryrand4.cpp
// body file: tryrand5.cpp
// body file: tryrand6.cpp

