#include <string>
#include <sstream>
#include <locale>

#if defined(__unix) || defined(__unix__)
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <cstring>
# include <iostream>
#endif

#include <map>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif


class LColl {
  public:
    LColl( const char * );

    bool operator[]( const string& _s )
     { return _m[_s]; }

  private:
    map<string,bool> _m;
};

LColl::LColl( const char *loc_dir )
{
# if defined(__unix) || defined(__unix__)
  /* Iterate through catalog that contain catalogs with locale definitions, installed on system
   * (this is expected /usr/lib/locale for most linuxes and /usr/share/locale for *BSD).
   * The names of catalogs here will give supported locales.
   */
  string base( loc_dir );
  DIR *d = opendir( base.c_str() );
  struct dirent *ent;
  while ( (ent = readdir( d )) != 0 ) {
    if ( strcmp( ent->d_name, "." ) == 0 || strcmp( ent->d_name, ".." ) == 0 ) {
      continue;
    }
    string f = base;
    f += '/';
    f += ent->d_name;
    struct stat s;
    stat( f.c_str(), &s );
    if ( S_ISDIR( s.st_mode ) ) {
      _m[string(ent->d_name)] = true;
      // cout << ent->d_name << endl;
    }
  }
  closedir( d );
# endif
# ifdef WIN32
  // real list of installed locales should be here...
  _m[string("french")] = true;
# endif
}

# if defined(__FreeBSD__) || defined(__OpenBSD__)
static LColl loc_ent( "/usr/share/locale" );
# else
static LColl loc_ent( "/usr/lib/locale" );
# endif

struct ref_locale {
  const char *name;
  const char *decimal_point;
  const char *thousands_sep;
  const char *money_prefix;
  const char *money_suffix;
};

static ref_locale tested_locales[] = {
//{  name,         decimal_point, thousands_sep, money_prefix, money_suffix},
  { "french",      ",",           "\xa0",       "",           " EUR" },
  { "ru_RU.koi8r", ",",           " ",           "",           " RUR" },
  { "en_GB",       ".",           "'",           "GBP ",       "" },
  { "en_US",       ".",           "'",           "USD ",       "" }
};

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
private:
  void _num_put_get( const locale&, const ref_locale& );
  void _money_put_get( const locale&, const ref_locale& );
  void _time_put_get( const locale&, const ref_locale& );
};

CPPUNIT_TEST_SUITE_REGISTRATION(LocaleTest);

//
// tests implementation
//

void LocaleTest::_num_put_get( const locale& loc, const ref_locale& rl ) {
  float val = 1234.56f;
  ostringstream ostr;
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1234.56" );

  numpunct<char> const& npct = use_facet<numpunct<char> >(loc);

  CPPUNIT_ASSERT( npct.decimal_point() == *rl.decimal_point );
  CPPUNIT_ASSERT( npct.thousands_sep() == *rl.thousands_sep );


  ostringstream fostr;
  fostr.imbue(loc);
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

  ref = "1";
  ref += npct.decimal_point();
  ref += "23457e+07";
  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == ref );

  val = 1000000000.0f;
  ostr.str("");
  ostr << val;
  CPPUNIT_ASSERT( ostr.str() == "1e+09" );

  fostr.str("");
  fostr << val;
  CPPUNIT_ASSERT( fostr.str() == "1e+09" );
}

void LocaleTest::_money_put_get( const locale& loc, const ref_locale& rl )
{
  money_put<char> const& fmp = use_facet<money_put<char> >(loc);
  money_get<char> const& fmg = use_facet<money_get<char> >(loc);
  moneypunct<char, true> const& intl_fmp = use_facet<moneypunct<char, true> >(loc);

  ostringstream ostr;
  ostr.imbue(loc);
  ostr << showbase;
  ostreambuf_iterator<char> res = fmp.put(ostr, true, ostr, ' ', 123456);

  CPPUNIT_ASSERT( !res.failed() );
  //The result is '1 234,56 EUR'
  string str_res = ostr.str();

  // cout << "code " << hex << int(str_res[0]) << dec << ' ' << str_res << endl;
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
  moneypunct<char, false> const& dom_fmp = use_facet<moneypunct<char, false> >(loc);
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

void LocaleTest::_time_put_get( const locale& loc, const ref_locale& rl )
{
  time_put<char> const&tmp = use_facet<time_put<char> >(loc);
  time_get<char> const&tmg = use_facet<time_get<char> >(loc);

  struct tm xmas = { 0, 0, 12, 25, 11, 93 };
  ostringstream ostr;
  ostr.imbue(loc);
  string format = "%a %d %b %y";

  time_put<char>::iter_type ret = tmp.put(ostr, ostr, ' ', &xmas, format.data(), format.data() + format.size());
  CPPUNIT_ASSERT( !ret.failed() );

  string str_ret = ostr.str();
}

void LocaleTest::num_put_get() {
  int n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for ( int i = 0; i < n; ++i ) {
    if ( loc_ent[string( tested_locales[i].name )] ) {
      //cout << '\t' << tested_locales[i].name << endl;
      locale loc( tested_locales[i].name );
      _num_put_get( loc, tested_locales[i] );
    }
  }
}

void LocaleTest::money_put_get() {
  int n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for ( int i = 0; i < n; ++i ) {
    if ( loc_ent[string( tested_locales[i].name )] ) {
      //cout << '\t' << tested_locales[i].name << endl;
      locale loc( tested_locales[i].name );
      _money_put_get( loc, tested_locales[i] );
    }
  }
}

void LocaleTest::time_put_get() {
  int n = sizeof(tested_locales) / sizeof(tested_locales[0]);
  for ( int i = 0; i < n; ++i ) {
    if ( loc_ent[string( tested_locales[i].name )] ) {
      //cout << '\t' << tested_locales[i].name << endl;
      locale loc( tested_locales[i].name );
      _time_put_get( loc, tested_locales[i] );
    }
  }
}
