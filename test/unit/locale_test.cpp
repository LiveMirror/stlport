#include <memory>
#include <string>
#include <sstream>
#include <locale>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class LocaleTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(LocaleTest);
  CPPUNIT_TEST(num_put_get);
  CPPUNIT_TEST(money_put_get);
  CPPUNIT_TEST(time_put_get);
  CPPUNIT_TEST_SUITE_END();

public:
  void num_put_get();
  void money_put_get();
  void time_put_get();
};

CPPUNIT_TEST_SUITE_REGISTRATION(LocaleTest);

//
// tests implementation
//
void LocaleTest::num_put_get() {
  auto_ptr<locale> sploc;
  try {
    sploc.reset(new locale("french"));
  }
  catch (runtime_error const&) {
    /*
     * No locale support or bad locale identification, 
     * we do not test anything.
     */
    bool no_locale_support_or_wrong_locale_name = true;
    CPPUNIT_ASSERT ( ! no_locale_support_or_wrong_locale_name );
    return;
  }

  float val = 1234.56f;
  ostringstream ostr;
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1234.56" );

  numpunct<char> const& npct = use_facet<numpunct<char> >(*sploc);
  ostringstream fostr;
  fostr.imbue(*sploc);
  fostr << val;

  string ref = "1";
  ref += npct.thousands_sep();
  ref += "234";
  ref += npct.decimal_point();
  ref += "56";
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 12345678.9f;
  ostr.str("");
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1.23457e+07" );

  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == "1,23457e+07" );

  val = 1000000000.0f;
  ostr.str("");
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1e+09" );

  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == "1e+09" );
}

void LocaleTest::money_put_get() {
  auto_ptr<locale> floc;
  try {
    floc.reset(new locale("french"));
  }
  catch (runtime_error const&) {
    /*
     * No locale support or bad locale identification, 
     * we do not test anything.
     */
    bool no_locale_support_or_wrong_locale_name = true;
    CPPUNIT_ASSERT ( ! no_locale_support_or_wrong_locale_name );
    return;
  }

  money_put<char> const&fmp = use_facet<money_put<char> >(*floc);
  money_get<char> const&fmg = use_facet<money_get<char> >(*floc);
  moneypunct<char, true> const&intl_fmp = use_facet<moneypunct<char, true> >(*floc);

  ostringstream ostr;
  ostr.imbue(*floc);
  ostr << showbase;
  ostreambuf_iterator<char> res = fmp.put(ostr, true, ostr, ' ', 123456);

  CPPUNIT_ASSERT( !res.failed() );
  //The result is '1 234,56 EUR'
  string str_res = ostr.str();

  CPPUNIT_ASSERT( str_res[0] == '1' );
  CPPUNIT_ASSERT( str_res[1] == intl_fmp.thousands_sep() );
  CPPUNIT_ASSERT( str_res[2] == '2' );
  CPPUNIT_ASSERT( str_res[3] == '3' );
  CPPUNIT_ASSERT( str_res[4] == '4' );
  CPPUNIT_ASSERT( str_res[5] == intl_fmp.decimal_point() );
  CPPUNIT_ASSERT( str_res[6] == '5' );
  CPPUNIT_ASSERT( str_res[7] == '6' );
  CPPUNIT_ASSERT( str_res[8] == ' ' );
  CPPUNIT_ASSERT( str_res.substr(9, intl_fmp.curr_symbol().size()) == intl_fmp.curr_symbol() );
  CPPUNIT_ASSERT( str_res.size() == 9 + intl_fmp.curr_symbol().size() );

  ios_base::iostate err = ios_base::goodbit;
  string digits;

  istringstream istr(str_res);
  fmg.get(istr, istreambuf_iterator<char>(), true, ostr, err, digits);
  CPPUNIT_ASSERT( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
  CPPUNIT_ASSERT( digits == "123456" );

  ostr.str("");
  moneypunct<char, false> const&dom_fmp = use_facet<moneypunct<char, false> >(*floc);
  res = fmp.put(ostr, false, ostr, ' ', -123456);

  CPPUNIT_ASSERT( !res.failed() );
  //The result is '-1 234,56 E' E being the euro symbol
  str_res = ostr.str();

  size_t index = 0;
  CPPUNIT_ASSERT( str_res.substr(index, dom_fmp.negative_sign().size()) == dom_fmp.negative_sign() );
  index += dom_fmp.negative_sign().size();
  CPPUNIT_ASSERT( str_res[index++] == '1' );
  CPPUNIT_ASSERT( str_res[index++] == dom_fmp.thousands_sep() );
  CPPUNIT_ASSERT( str_res[index++] == '2' );
  CPPUNIT_ASSERT( str_res[index++] == '3' );
  CPPUNIT_ASSERT( str_res[index++] == '4' );
  CPPUNIT_ASSERT( str_res[index++] == dom_fmp.decimal_point() );
  CPPUNIT_ASSERT( str_res[index++] == '5' );
  CPPUNIT_ASSERT( str_res[index++] == '6' );
  CPPUNIT_ASSERT( str_res[index++] == ' ' );
  CPPUNIT_ASSERT( str_res.substr(index, dom_fmp.curr_symbol().size()) == dom_fmp.curr_symbol() );
  CPPUNIT_ASSERT( str_res.size() == index + dom_fmp.curr_symbol().size() );

  err = 0;
  _STLP_LONG_DOUBLE val;

  istr.str(str_res);
  fmg.get(istr, istreambuf_iterator<char>(), false, ostr, err, val);
  CPPUNIT_ASSERT( (err & (ios_base::failbit | ios_base::badbit)) == 0 );
  CPPUNIT_ASSERT( val == -123456 );
}

void LocaleTest::time_put_get() {
  auto_ptr<locale> floc;
  try {
    floc.reset(new locale("french"));
  }
  catch (runtime_error const&) {
    /*
     * No locale support or bad locale identification, 
     * we do not test anything.
     */
    bool no_locale_support_or_wrong_locale_name = true;
    CPPUNIT_ASSERT ( ! no_locale_support_or_wrong_locale_name );
    return;
  }

  time_put<char> const&tmp = use_facet<time_put<char> >(*floc);
  time_get<char> const&tmg = use_facet<time_get<char> >(*floc);

  struct tm xmas = { 0, 0, 12, 25, 11, 93 };
  ostringstream ostr;
  ostr.imbue(*floc);
  string format = "%a %d %b %y";

  time_put<char>::iter_type ret = tmp.put(ostr, ostr, ' ', &xmas, format.data(), format.data() + format.size());
  CPPUNIT_ASSERT( !ret.failed() );

  string str_ret = ostr.str();
}
