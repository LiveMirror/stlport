#include <cmath>

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)

namespace NS1 {

void f()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

}

namespace {

void g()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

}

void h()
{
  double d( 1.0 );

  d = sqrt( d );
  d = ::sqrt( d );
  d = std::sqrt( d );
};

struct sq
{
    sq()
      { }

    double sqroot( double x )
      {
        /*
         * gcc (3.4.2) fail to resolve correct namespace for sqrt in case:

         using namespace std;
         return sqrt(x);

         The key is 'using namespace std;'.
         The workaround is 'using std::sqrt;';

         There is no way to import one function from another namespace
         and add overloaded variants, due to following construction is ill-formed:

         namespace std {
         using double ::sqrt( double );
         float sqrt( float );
         long double sqrt( long double );
         };

         BTW, no 'using'---no problems (see functions f(), g(), h() above ).

           - ptr, 2005-03-04

         */

        // using namespace std;
        using std::sqrt;
        return sqrt(x);
      }
};

#endif


#if 0 // Do nothing, this should be compiled only

#include "cppunit/cppunit_proxy.h"

class ResolveNameTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(ResolveNameTest);
  CPPUNIT_TEST(cstyle);
  CPPUNIT_TEST_SUITE_END();

protected:
  void cstyle();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ResolveNameTest);

void ResolveNameTest::cstyle()
{
}

#endif
