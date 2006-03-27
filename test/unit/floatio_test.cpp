#include <limits>

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#include <iomanip>
#include <string>
#include <sstream>

// #include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class FloatIOTest : public CPPUNIT_NS::TestCase
{
    CPPUNIT_TEST_SUITE(FloatIOTest);
    CPPUNIT_TEST(float_output_test);
    CPPUNIT_TEST(float_input_test);
    CPPUNIT_TEST(fix_float_long);
    CPPUNIT_TEST_SUITE_END();

  protected:
    void float_output_test();
    void float_input_test();
    void fix_float_long();

    static bool check_float (float val, float ref)
      {
        float epsilon = numeric_limits<float>::epsilon();
        return val <= ref + epsilon && val >= ref - epsilon;
      }

    static bool check_float (double val, double ref)
      {
        double epsilon = numeric_limits<double>::epsilon();
        return val <= ref + epsilon && val >= ref - epsilon;
      }

#ifndef _STLP_NO_LONG_DOUBLE
    static bool check_float (long double val, long double ref)
      {
        long double epsilon = numeric_limits<long double>::epsilon();
        return val <= ref + epsilon && val >= ref - epsilon;
      }
#endif

    static string reset_stream (ostringstream &ostr)
      {
        string tmp = ostr.str();
        ostr.str("");
        return tmp;
      }
};

CPPUNIT_TEST_SUITE_REGISTRATION(FloatIOTest);

//
// tests implementation
//
void FloatIOTest::float_output_test()
{
  ostringstream ostr;
  string output;

  ostr.precision(6);
  float test_val = (float)1.23457e+17;

  ostr << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "1.23457e+17");

  ostr << fixed << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 25);
  CPPUNIT_ASSERT(output.substr(0, 5) == "12345");
  CPPUNIT_ASSERT(output.substr(18) == ".000000");

  ostr << showpos << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 26);
  CPPUNIT_ASSERT(output.substr(0, 6) == "+12345");
  CPPUNIT_ASSERT(output.substr(19) == ".000000");

  ostr << setprecision(100) << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output.size() == 120);
  CPPUNIT_ASSERT(output.substr(0, 6) == "+12345");
  CPPUNIT_ASSERT(output.substr(19) == ".0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000" );

  ostr << noshowpos << scientific;
  CPPUNIT_ASSERT(ostr.good());

  test_val = 0.12345678f;
  ostr << setprecision(8) << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "1.2345678e-01");

  ostr << setw(30) << fixed << setfill('0') << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "000000000000000000000.12345678");

  ostr << setw(30) << showpos << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "0000000000000000000+0.12345678");

  ostr << setw(30) << left << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "+0.123456780000000000000000000");

  ostr << setw(30) << internal << test_val;
  CPPUNIT_ASSERT(ostr.good());
  output = reset_stream(ostr);
  CPPUNIT_ASSERT(output == "+00000000000000000000.12345678");
}

void FloatIOTest::float_input_test()
{
  float in_val;

  istringstream istr;

  istr.str("1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(!istr.fail());
  CPPUNIT_ASSERT(istr.eof());
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("-1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(!istr.fail());
  CPPUNIT_ASSERT(istr.eof());
  CPPUNIT_ASSERT(check_float(in_val, -1.2345f));
  istr.clear();

  istr.str("+1.2345");
  istr >> in_val;
  CPPUNIT_ASSERT(!istr.fail());
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("000000000000001.234500000000");
  istr >> in_val;
  CPPUNIT_ASSERT(!istr.fail());
  CPPUNIT_ASSERT(istr.eof());
  CPPUNIT_ASSERT(check_float(in_val, 1.2345f));
  istr.clear();

  istr.str("1.2345e+04");
  istr >> in_val;
  CPPUNIT_ASSERT(!istr.fail());
  CPPUNIT_ASSERT(istr.eof());
  CPPUNIT_ASSERT(check_float(in_val, 12345.0f));
  istr.clear();

  double in_val_d;
  {
    stringstream str;

    str << "1E+" << numeric_limits<double>::max_exponent10;

    str >> in_val_d;
    CPPUNIT_ASSERT(!str.fail());
    CPPUNIT_ASSERT(str.eof());
    CPPUNIT_ASSERT( in_val_d != numeric_limits<double>::infinity() );
    // CPPUNIT_ASSERT(in_val_d != 1E+308);
    str.clear();
  }
  {
    stringstream str;

    str << "1E+" << (numeric_limits<double>::max_exponent10 + 1);

    str >> in_val_d;
    CPPUNIT_ASSERT(!str.fail());
    CPPUNIT_ASSERT(str.eof());
    CPPUNIT_ASSERT( in_val_d == numeric_limits<double>::infinity() );
    // CPPUNIT_ASSERT(in_val_d == 1E+308);
    str.clear();
  }
}

void FloatIOTest::fix_float_long()
{
  ostringstream str;

  str.setf(ios::fixed, ios::floatfield);
  str << 1.0e+5;
  CPPUNIT_CHECK( str.str() == "100000.000000" );

  reset_stream(str);
  str.precision(0);
  str << 1.0e+5;
  CPPUNIT_CHECK( str.str() == "100000" );

  reset_stream(str);
  str.precision(4);
  str << 1.0e+5;
  CPPUNIT_CHECK( str.str() == "100000.0000" );

  reset_stream(str);
  str.precision(0);
  str << 1.0e+83;
  {
    istringstream istr( str.str() );
    double f;
    istr >> f;
    CPPUNIT_CHECK( !istr.fail() );
    if ( int(numeric_limits<double>::digits10) < 83 ) {
      double delta = 1.0;
      for ( int ee = 83 - int(numeric_limits<double>::digits10); ee > 0; --ee ) {
        delta *= 10.0;
      }
      // we may loss some digits here, but not more than mantissa:
      CPPUNIT_CHECK( (f > (1.0e+83 - delta)) && (f < (1.0e+83 + delta)) );
    } else {
      CPPUNIT_CHECK( check_float(f, 1.0e+83) );
    }
  }

#if 0 // #ifndef _STLP_NO_LONG_DOUBLE
  reset_stream(str);
  str.precision(0);
  str << 1.0e+83l;
  {
    istringstream istr( str.str() );
    long double f;
    istr >> f;
    CPPUNIT_CHECK( !istr.fail() );
    if ( int(numeric_limits<long double>::digits10) < 83 ) {
      long double delta = 1.0l;
      for ( int ee = 83 - int(numeric_limits<long double>::digits10); ee > 0; --ee ) {
        delta *= 10.0l;
      }
      // we may loss some digits here, but not more than mantissa:
      cerr << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789" << endl;
      cerr << str.str() << endl;
      cerr << delta << endl;
      cerr << f << endl;
      CPPUNIT_CHECK( (f > (1.0e+83l - delta)) && (f < (1.0e+83l + delta)) );
    } else {
      CPPUNIT_CHECK( check_float(f, 1.0e+83l) );
    }
  }
#endif

  reset_stream(str);
  str.precision(0);
  str << numeric_limits<double>::max();
  {
    istringstream istr( str.str() );
    double f;
    istr >> f;
    CPPUNIT_CHECK( !istr.fail() );
    if ( int(numeric_limits<double>::digits10) < int(numeric_limits<double>::max_exponent10) ) {
      double delta = 9.0;
      for ( int ee = int(numeric_limits<double>::max_exponent10) - int(numeric_limits<double>::digits10); ee > 0; --ee ) {
        delta *= 10.0;
      }
      // we may loss some digits here, but not more than mantissa:
      CPPUNIT_CHECK( (f > (numeric_limits<double>::max() - delta)) );
    }
  }

#if 0 // #ifndef _STLP_NO_LONG_DOUBLE
  reset_stream(str);
  str.precision(0);
  str << numeric_limits<long double>::max();
  {
    istringstream istr( str.str() );
    long double f;
    istr >> f;
    CPPUNIT_CHECK( !istr.fail() );
    if ( int(numeric_limits<long double>::digits10) < int(numeric_limits<long double>::max_exponent10) ) {
      long double delta = 1.0l;
      for ( int ee = int(numeric_limits<long double>::max_exponent10) - int(numeric_limits<long double>::digits10); ee > 0; --ee ) {
        delta *= 10.0l;
      }
      // we may loss some digits here, but not more than mantissa:
      CPPUNIT_CHECK( (f > (numeric_limits<long double>::max() - delta)) );
    }
  }
#endif
}


/*
int main (int argc, char *argv[]) {
  FloatIOTest test;
  test.float_output_test();
  test.float_input_test();
  return 0;
}
*/

#endif // NO_IOSTREAMS
