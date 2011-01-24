// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2008, 2009
 * Petr Ovtchenkov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#include <exam/suite.h>

// #include <misc/opts.h>
#include <string>
#include <sstream>

#include "string_test.h"
// #include "exception_test.h"
// #include "locale_test.h"

int main( int argc, const char** argv )
{
# if 0
  Opts opts;

  opts.description( "test suite for 'sockios' framework" );
  opts.usage( "[options]" );

  opts << option<void>( "print this help message", 'h', "help" )
       << option<void>( "list all test cases", 'l', "list" )
       << option<std::string>( "run tests by number", 'r', "run" )["0"]
       << option<void>( "print status of tests within test suite", 'v', "verbose" )
       << option<void>(  "trace checks", 't', "trace" );

  try {
    opts.parse( argc, argv );
  }
  catch (...) {
    opts.help( std::cerr );
    return 1;
  }

  if ( opts.is_set( 'h' ) ) {
    opts.help( std::cerr );
    return 0;
  }
#endif

  std::string test_s("Size test");
  std::string myar[2];
  myar[0]=test_s;
  myar[1]=test_s;
  std::string::const_iterator cit;

  printf ("sizeof(test_s): %d, s1==s2:%d\n", sizeof(test_s), myar[0]==myar[1]);
  printf ("sizeof(cit): %d\n", sizeof(cit));

  exam::test_suite t( "STLport test" );
  //   vector_test vec_test;

  exam::test_suite::test_case_type vec_tc[16];

  string_test str_test;

  str_test.constructor(&t);
  str_test.trivial_char_compare(&t);

  str_test.reserve(&t); // 
str_test.assign(&t); // "assign" );
str_test.erase(&t); // "erase" );
str_test.data(&t); // "data" );
str_test.c_str(&t); // "c_str" );
	  str_test.null_char(&t); // "null_char" );
	  str_test.insert(&t); // "insert" );
	  str_test.replace(&t); // "replace" );
	  str_test.resize(&t); // "resize" );
	  str_test.short_string(&t); // "short_string" );
	  str_test.find(&t); // "find" );
	  str_test.bogus_edge_find(&t); // "bogus_edge_find" );
	  str_test.rfind(&t); // "rfind" );
	  str_test.find_last_of(&t); // "find_last_of" );
	  str_test.find_last_not_of(&t); // "find_last_not_of" );
	  str_test.copy(&t); // "copy" );
	  str_test.mt(&t); // "mt" );
	  str_test.short_string_optim_bug(&t); // "short_string_optim_bug" );
	  str_test.compare(&t); // "compare" );
	  str_test.template_expression(&t); // "template_expression" );
	  str_test.te_tmp(&t); // "te_tmp" );
	  str_test.oper_tmp(&t); // "oper_tmp" );
	  str_test.template_wexpression(&t); // "template_wexpression" );
//	  str_test.io(&t); // "io" );

	  str_test.capacity(&t); // "capacity" );
	  str_test.concat24(&t); // "concat24" );
	  str_test.assign_from_char(&t); // "string assign from char buf" );

#if 0
  cstring_test cst_test;

  t.add( &cstring_test::import_checks, cst_test, "import_checks" );

  iostream_test strm_test;

  t.add( &iostream_test::manipulators, strm_test, "manipulators" );
  t.add( &iostream_test::in_avail, strm_test, "in_avail in std streams" );

  sstream_test sstrm_test;

  t.add( &sstream_test::output, sstrm_test, "sstream output" );
  t.add( &sstream_test::input, sstrm_test, "sstream input" );
  t.add( &sstream_test::input_char, sstrm_test, "sstream input_char" );
  t.add( &sstream_test::io, sstrm_test, "sstream io" );
  t.add( &sstream_test::err, sstrm_test, "sstream err" );
  t.add( &sstream_test::err_long, sstrm_test, "sstream err_long" );
  t.add( &sstream_test::maxint, sstrm_test, "sstream maxint" );
  t.add( &sstream_test::init_in, sstrm_test, "sstream init_in" );
  t.add( &sstream_test::init_out, sstrm_test, "sstream init_out" );
  t.add( &sstream_test::init_in_str, sstrm_test, "sstream str( \"foo\" )" );
  t.add( &sstream_test::buf, sstrm_test, "sstream buf" );
  t.add( &sstream_test::rdbuf, sstrm_test, "sstream rdbuf" );
  t.add( &sstream_test::streambuf_output, sstrm_test, "sstream streambuf_output" );
  t.add( &sstream_test::seek, sstrm_test, "sstream seek" );
  t.add( &sstream_test::seekp, sstrm_test, "sstream seekp" );
  t.add( &sstream_test::seek_gp, sstrm_test, "sstream seek_gp" );
  t.add( &sstream_test::tellp, sstrm_test, "sstream tellp" );
  t.add( &sstream_test::extra0_bug_id_2728232, sstrm_test, "extra 0; bug ID: 2728232" );
  t.add( &sstream_test::negative, sstrm_test, "sstream negative" );

  fstream_test fstrm_test;
  exam::test_suite::test_case_type fstream_tc[10];

  fstream_tc[0] = t.add( &fstream_test::err, fstrm_test, "fstream err",
    t.add( &fstream_test::io, fstrm_test, "fstream io",
      t.add( &fstream_test::input_char, fstrm_test, "fstream input_char",
        t.add( &fstream_test::input, fstrm_test, "fstream input",
          t.add( &fstream_test::output, fstrm_test, "fstream output" ) ) ) ) );

  t.add( &fstream_test::tell_binary_wce, fstrm_test, "fstream tellg binary WCE workaround",
    t.add( &fstream_test::tellg, fstrm_test, "fstream tellg", fstream_tc[0] ) );
  t.add( &fstream_test::tellp, fstrm_test, "fstream tellp", fstream_tc[0] );

  t.add( &fstream_test::seek_wide_stream, fstrm_test, "wfstream seek",
    fstream_tc[1] = t.add( &fstream_test::seek_text, fstrm_test, "fstream seek in text",
      t.add( &fstream_test::seek_binary, fstrm_test, "fstream seek in binary", fstream_tc[0] ) ) );
  t.add( &fstream_test::buf, fstrm_test, "fstream buf", fstream_tc[0] );

  t.add( &fstream_test::rdbuf, fstrm_test, "fstream rdbuf",
    t.add( &fstream_test::streambuf_output, fstrm_test, "fstream streambuf_output", fstream_tc[0] ) );
  t.add( &fstream_test::win32_file_format, fstrm_test, "fstream win32_file_format", fstream_tc[0] );
  t.add( &fstream_test::null_stream, fstrm_test, "fstream null_stream", fstream_tc[0] );
  t.add( &fstream_test::null_buf, fstrm_test, "fstream null_buf", fstream_tc[0] );
  t.add( &fstream_test::offset, fstrm_test, "fstream offset", fstream_tc[0] );
  t.add( &fstream_test::big_file, fstrm_test, "fstream big_file", fstream_tc[0] );
  fstream_tc[2] = t.add( &fstream_test::custom_facet, fstrm_test, "fstream custom_facet", fstream_tc[0] );

  t.add( &fstream_test::rewind, fstrm_test, "fstream write after read fail", fstream_tc[1] );
 
  istream_iterator_test isit_test;

  t.add( &istream_iterator_test::istmit1, isit_test, "istmit1" );
  t.add( &istream_iterator_test::copy_n_test, isit_test, "copy_n_test" );

  ostream_iterator_test osit_test;

  t.add( &ostream_iterator_test::ostmit0, osit_test, "ostmit0" );

  ioiter_test ioit_test;

  t.add( &ioiter_test::ioiterat_test, ioit_test, "ioiterat_test" );
  t.add( &ioiter_test::assign_test, ioit_test, "assign_test" );
  t.add( &ioiter_test::assign2_test, ioit_test, "assign2_test" );

  t.add( &limits_test::limits, lt_test, "limits_test::limits" );

  t.add( &limits_test::qNaN<float>, lt_test, "numeric_limits<float>::quiet_NaN()" );
  t.add( &limits_test::qNaN<double>, lt_test, "numeric_limits<double>::quiet_NaN()" );
#if !defined ( _STLP_NO_LONG_DOUBLE )
  t.add( &limits_test::qNaN<long double>, lt_test, "numeric_limits<long double>::quiet_NaN()" );
#endif
  t.add( &limits_test::sNaN<float>, lt_test, "numeric_limits<float>::signaling_NaN()" );
  t.add( &limits_test::sNaN<double>, lt_test, "numeric_limits<double>::signaling_NaN()" );
#if !defined ( _STLP_NO_LONG_DOUBLE )
  t.add( &limits_test::sNaN<long double>, lt_test, "numeric_limits<long double>::signaling_NaN()" );
#endif

  exception_test exc_test;

  t.add( &exception_test::what, exc_test, "exception_test::what" );
  t.add( &exception_test::unexpected_except, exc_test, "exception_test::unexpected_except" );
  t.add( &exception_test::uncaught_except, exc_test, "exception_test::uncaught_except" );
  t.add( &exception_test::exception_emission, exc_test, "exception_test::exception_emission" );

  errno_test err_test;
  t.add( &errno_test::check, err_test, "errno_test::check" );

  num_put_get_test nmg_test;

  // t.add( &num_put_get_test::scientific_precision, nmg_test, "scientific precision",
  t.add( &num_put_get_test::num_put_float, nmg_test, "num_put_float" ); // );
  t.add( &num_put_get_test::num_put_integer, nmg_test, "num_put_integer" );
  t.add( &num_put_get_test::num_get_float, nmg_test, "num_get_float" );
  t.add( &num_put_get_test::num_get_integer, nmg_test, "num_get_integer" );
  t.add( &num_put_get_test::inhex, nmg_test, "inhex" );
  t.add( &num_put_get_test::pointer, nmg_test, "pointer" );
  t.add( &num_put_get_test::fix_float_long, nmg_test, "fix_float_long" );
  t.add( &num_put_get_test::custom_numpunct, nmg_test, "custom_numpunct" );

  codecvt_test cvt_test;

  t.add( &codecvt_test::variable_encoding, cvt_test, "variable_encoding", fstream_tc[2] );
  t.add( &codecvt_test::in_out_test, cvt_test, "in_out_test" );
  t.add( &codecvt_test::length_test, cvt_test, "length_test" );
  t.add( &codecvt_test::imbue_while_reading, cvt_test, "imbue_while_reading" );
  t.add( &codecvt_test::special_encodings, cvt_test, "special_encodings" );

  shared_ptr_test shp_test;
  t.add( &shared_ptr_test::shared_from_this, shp_test, "shared_from_this" );

  ref_wrapper_test ref_test;

  t.add( &ref_wrapper_test::ref, ref_test, "ref" );
  t.add( &ref_wrapper_test::cref, ref_test, "cref" );

  locale_test ltest;

  t.add( &locale_test::locale_by_name, ltest, "locale_by_name" );
  t.add( &locale_test::moneypunct_by_name, ltest, "moneypunct_by_name" );
  t.add( &locale_test::time_by_name, ltest, "time_by_name" );
  t.add( &locale_test::numpunct_by_name, ltest, "numpunct_by_name" );
  t.add( &locale_test::ctype_by_name, ltest, "ctype_by_name" );
  t.add( &locale_test::collate_by_name, ltest, "collate_by_name" );
  t.add( &locale_test::messages_by_name, ltest, "messages_by_name" );

  t.add( &locale_test::loc_has_facet, ltest, "loc_has_facet" );
  t.add( &locale_test::num_put_get, ltest, "num_put_get" );
  t.add( &locale_test::money_put_get, ltest, "money_put_get" );
  t.add( &locale_test::money_put_X_bug, ltest, "money_put_X_bug" );
  t.add( &locale_test::time_put_get, ltest, "time_put_get" );
  t.add( &locale_test::collate_facet, ltest, "collate_facet" );
  t.add( &locale_test::ctype_facet, ltest, "ctype_facet" );
  t.add( &locale_test::locale_init_problem, ltest, "locale_init_problem" );

  t.add( &locale_test::default_locale, ltest, "default_locale" );
  t.add( &locale_test::combine, ltest, "combine" );
#endif

#if 0
  if ( opts.is_set( 'l' ) ) {
    t.print_graph( std::cout );
    return 0;
  }

  if ( opts.is_set( 'v' ) ) {
    t.flags( t.flags() | exam::base_logger::verbose );
  }

  if ( opts.is_set( 't' ) ) {
    t.flags( t.flags() | exam::base_logger::trace );
  }

  if ( opts.is_set( 'r' ) ) {
    std::stringstream ss( opts.get<std::string>( 'r' ) );
    int n;
    int res = 0;
    while ( ss >> n ) {
      res |= t.single( n );
    }

    return res;
  }
# endif

//  return t.girdle();
}
