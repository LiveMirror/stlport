#define _STLP_DO_IMPORT_CSTD_FUNCTIONS

#include <cmath>
//We also test math functions imported from stdlib.h or 
//defined in cstdlib
#include <cstdlib>

#include "cppunit/cppunit_proxy.h"

//This test purpose is to check the right import of math.h C symbols
//into the std namespace so we do not use the using namespace std
//specification

//
// TestCase class
//
class CMathTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(CMathTest);
  CPPUNIT_TEST(test);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CMathTest);

//
// tests implementation
//
void CMathTest::test()
{
  int int_val = -1;
  long long_val = -1l;
  float float_val = -1.0f;
  double double_val = -1.0;
#if !defined (_STLP_NO_LONG_DOUBLE)
  long double long_double_val = -1.0l;
#endif

  CPPUNIT_ASSERT( std::abs(int_val) == -int_val );
  CPPUNIT_ASSERT( std::abs(long_val) == -long_val );
  CPPUNIT_ASSERT( std::labs(long_val) == -long_val );
  CPPUNIT_ASSERT( std::abs(float_val) == -float_val );
  CPPUNIT_ASSERT( std::abs(double_val) == -double_val );
#if !defined (_STLP_NO_LONG_DOUBLE)
  CPPUNIT_ASSERT( std::abs(long_double_val) == -long_double_val );
#endif

  CPPUNIT_ASSERT( std::fabs(float_val) == -float_val );
  CPPUNIT_ASSERT( std::fabs(double_val) == -double_val );
#if !defined (_STLP_NO_LONG_DOUBLE)
  CPPUNIT_ASSERT( std::fabs(long_double_val) == -long_double_val );
#endif

  std::div_t div_res = std::div(3, 2);
  CPPUNIT_ASSERT( div_res.quot == 1 );
  CPPUNIT_ASSERT( div_res.rem == 1 );
  std::ldiv_t ldiv_res = std::ldiv(3l, 2l);
  CPPUNIT_ASSERT( ldiv_res.quot == 1l );
  CPPUNIT_ASSERT( ldiv_res.rem == 1l );
  ldiv_res = std::div(3l, 2l);
  CPPUNIT_ASSERT( ldiv_res.quot == 1l );
  CPPUNIT_ASSERT( ldiv_res.rem == 1l );

  std::srand(2);
  int rand_val = std::rand();
  CPPUNIT_ASSERT( rand_val >= 0 && rand_val <= RAND_MAX );

  CPPUNIT_ASSERT( std::floor(1.5f) == 1.0f );
  CPPUNIT_ASSERT( std::ceil(1.5f) == 2.0f );
  CPPUNIT_ASSERT( std::fmod(1.5f, 1.0f) == 0.5f );
  CPPUNIT_ASSERT( std::floor(1.5) == 1.0 );
  CPPUNIT_ASSERT( std::ceil(1.5) == 2.0 );
  CPPUNIT_ASSERT( std::fmod(1.5, 1.0) == 0.5 );
#if !defined (_STLP_NO_LONG_DOUBLE)
  CPPUNIT_ASSERT( std::floor(1.5l) == 1.0l );
  CPPUNIT_ASSERT( std::ceil(1.5l) == 2.0l );
  CPPUNIT_ASSERT( std::fmod(1.5l, 1.0l) == 0.5l );
#endif
}
