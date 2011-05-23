// -*- C++ -*- Time-stamp: <2011-03-23 19:27:27 ptr>

/*
 * Copyright (c) 2008-2010
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

#if 0
#include "type_traits_test.h"
#include "ratio_test.h"
#include "vector_test.h"
#include "deque_test.h"
#include "list_test.h"
#include "slist_test.h"
#endif

#include "string_test.h"
#include "stream_test.h"
#include "iter_test.h"
#include "codecvt_test.h"
#include "exception_test.h"
#include "locale_test.h"
#include "errno_test.h"
#include "shared_ptr_test.h"
// #include "reference_wrapper_test.h"
/// #include "num_put_get_test.h"

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
  std::string myar0;
  std::string myar1;
  myar0=test_s;
  std::string::const_iterator cit;

  printf ("sizeof(_String_base): %d, sizeof(_String_val): %d\n", sizeof(std::_String_base), sizeof(std::_String_val<char, std::allocator<char> > ));
  printf ("sizeof(test_s): %d, s1==s2:%d\n", sizeof(test_s), myar0==test_s);
  printf ("sizeof(cit): %d\n", sizeof(cit));

  exam::test_suite t( "STLport test" );

#if 0
  t.add( &type_traits_test::is_trivially_copyable, ttt, "is_trivially_copyable", tt_tc[0] );

  ratio_test ratio_tst;

  t.add( &ratio_test::ratio, ratio_tst, "ratio", tt_tc[0] );
#endif

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

#if 0
  str_test.mt(&t); // "mt" );
#endif

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
  
  //  cstring_test cst_test;
  
  //   t.add( &cstring_test::import_checks, cst_test, "import_checks" );

  iostream_test strm_test;
  //  t.add( &iostream_test::manipulators, strm_test, "manipulators" );
  //  t.add( &iostream_test::in_avail, strm_test, "in_avail in std streams" );
  t.add (&iostream_test::cout_out, strm_test, "hello world");
  //  t.add( &iostream_test::manipulators, strm_test, "manipulators" );


  fstream_test fstrm_test;
  exam::test_suite::test_case_type fstream_tc[10];

  t.add( &fstream_test::err, fstrm_test, "fstream err");
  t.add( &fstream_test::io, fstrm_test, "fstream io");
  t.add( &fstream_test::input_char, fstrm_test, "fstream input_char");
  t.add( &fstream_test::input, fstrm_test, "fstream input");
  t.add( &fstream_test::output, fstrm_test, "fstream output");
  
  t.add( &fstream_test::tell_binary_wce, fstrm_test, "fstream tellg binary WCE workaround");
  t.add( &fstream_test::tellg, fstrm_test, "fstream tellg");
  t.add( &fstream_test::tellp, fstrm_test, "fstream tellp");
  
  t.add( &fstream_test::seek_wide_stream, fstrm_test, "wfstream seek");
  t.add( &fstream_test::seek_text, fstrm_test, "fstream seek in text");
  t.add( &fstream_test::seek_binary, fstrm_test, "fstream seek in binary");
  t.add( &fstream_test::buf, fstrm_test, "fstream buf");

  // t.add( &fstream_test::rdbuf, fstrm_test, "fstream rdbuf", fstream_tc[0]);

  //   t.add( &fstream_test::streambuf_output, fstrm_test, "fstream streambuf_output", fstream_tc[0]);

  t.add( &fstream_test::win32_file_format, fstrm_test, "fstream win32_file_format");
  t.add( &fstream_test::null_stream, fstrm_test, "fstream null_stream");
  t.add( &fstream_test::null_buf, fstrm_test, "fstream null_buf");
  t.add( &fstream_test::offset, fstrm_test, "fstream offset");
  t.add( &fstream_test::rewind, fstrm_test, "fstream write after read fail" );

  //  t.add( &fstream_test::big_file, fstrm_test, "fstream big_file" );
  fstream_tc[2] = t.add( &fstream_test::custom_facet, fstrm_test, "fstream custom_facet");



#if 0

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
  //  t.add( &sstream_test::streambuf_output, sstrm_test, "sstream streambuf_output" );
  t.add( &sstream_test::fail_bit, sstrm_test, "sstream throw ios_base::failure exception for invalid seekg",
  t.add( &sstream_test::seek, sstrm_test, "sstream seek" ) );
  t.add( &sstream_test::seekp, sstrm_test, "sstream seekp" );
  t.add( &sstream_test::seek_gp, sstrm_test, "sstream seek_gp" );
  t.add( &sstream_test::tellp, sstrm_test, "sstream tellp" );
  t.add( &sstream_test::extra0_bug_id_2728232, sstrm_test, "extra 0; bug ID: 2728232" );
  t.add( &sstream_test::negative, sstrm_test, "sstream negative" );

  istream_iterator_test isit_test;

  t.add( &istream_iterator_test::istmit1, isit_test, "istmit1" );
  t.add( &istream_iterator_test::copy_n_test, isit_test, "copy_n_test" );

  ostream_iterator_test osit_test;

  t.add( &ostream_iterator_test::ostmit0, osit_test, "ostmit0" );

  ioiter_test ioit_test;

  t.add( &ioiter_test::ioiterat_test, ioit_test, "ioiterat_test" );
  t.add( &ioiter_test::assign_test, ioit_test, "assign_test" );
  t.add( &ioiter_test::assign2_test, ioit_test, "assign2_test" );
#endif

#if 0

  insert_iter_test ins_test;

  t.add( &insert_iter_test::insert1, ins_test, "insert1" );
  t.add( &insert_iter_test::insert2, ins_test, "insert2" );

  binsert_iter_test bins_test;

  t.add( &binsert_iter_test::binsert1, bins_test, "binsert1" );
  t.add( &binsert_iter_test::binsert2, bins_test, "binsert2" );

  finsert_iter_test fins_test;

  t.add( &finsert_iter_test::finsert1, fins_test, "finsert1" );
  t.add( &finsert_iter_test::finsert2, fins_test, "finsert2" );

  reviter_test rev_test;

  t.add( &reviter_test::reviter1, rev_test, "reviter1" );
  t.add( &reviter_test::reviter2, rev_test, "reviter2" );
  t.add( &reviter_test::revbit1, rev_test, "revbit1" );

  bind_test bn_test;

  t.add( &bind_test::bind1st1, bn_test, "bind1st1" );
  t.add( &bind_test::bind2nd1, bn_test, "bind2nd1" );
  t.add( &bind_test::bind2nd2, bn_test, "bind2nd2" );
  t.add( &bind_test::bind2nd3, bn_test, "bind2nd3" );
  t.add( &bind_test::bind_memfn, bn_test, "bind_memfn" );

  count_test cn_test;

  t.add( &count_test::count0, cn_test, "count0" );
  t.add( &count_test::count1, cn_test, "count1" );
  t.add( &count_test::countif1, cn_test, "countif1" );

  partial_test part_test;

  t.add( &partial_test::parsrt0, part_test, "parsrt0" );
  t.add( &partial_test::parsrt1, part_test, "parsrt1" );
  t.add( &partial_test::parsrt2, part_test, "parsrt2" );
  t.add( &partial_test::parsrtc0, part_test, "parsrtc0" );
  t.add( &partial_test::parsrtc1, part_test, "parsrtc1" );
  t.add( &partial_test::parsrtc2, part_test, "parsrtc2" );
  t.add( &partial_test::bad_predicate_detected, part_test, "bad_predicate_detected partial_test" );

  heap_test hp_test;

  t.add( &heap_test::mkheap1, hp_test, "mkheap1" );
  t.add( &heap_test::mkheap2, hp_test, "mkheap2" );
  t.add( &heap_test::pheap1, hp_test, "pheap1" );
  t.add( &heap_test::pheap2, hp_test, "pheap2" );

  bsearch_test bs_test;

  t.add( &bsearch_test::bsearch1, bs_test, "bsearch1" );
  t.add( &bsearch_test::bsearch2, bs_test, "bsearch2" );

  bcompose_test bcm_test;

  t.add( &bcompose_test::bcompose1, bcm_test, "bcompose1" );
  t.add( &bcompose_test::bcompose2, bcm_test, "bcompose2" );

  rotate_test rt_test;

  t.add( &rotate_test::rotate0, rt_test, "rotate0" );
  t.add( &rotate_test::rotate1, rt_test, "rotate1" );
  t.add( &rotate_test::rotcopy0, rt_test, "rotcopy0" );
  t.add( &rotate_test::rotcopy1, rt_test, "rotcopy1" );

  fill_test fl_test;

  t.add( &fill_test::fill1, fl_test, "fill1" );
  t.add( &fill_test::filln1, fl_test, "filln1" );
  
  unique_test un_test;

  t.add( &unique_test::unique1, un_test, "unique1" );
  t.add( &unique_test::unique2, un_test, "unique2" );
  t.add( &unique_test::uniqcpy1, un_test, "uniqcpy1" );
  t.add( &unique_test::uniqcpy2, un_test, "uniqcpy2" );

  transform_test tr_test;

  t.add( &transform_test::trnsfrm1, tr_test, "trnsfrm1" );
  t.add( &transform_test::trnsfrm2, tr_test, "trnsfrm2" );
  t.add( &transform_test::self_str, tr_test, "self_str" );

  neq_test nq_test;

  t.add( &neq_test::negate0, nq_test, "negate0" );
  t.add( &neq_test::nequal0, nq_test, "nequal0" );

  modulus_test mod_test;

  t.add( &modulus_test::modulus0, mod_test, "modulus0" );

  ptr2_test pt_test;

  t.add( &ptr2_test::ptrbin1, pt_test, "ptrbin1" );
  t.add( &ptr2_test::ptrbin2, pt_test, "ptrbin2" );
  t.add( &ptr2_test::ptrun1, pt_test, "ptrun1" );
  t.add( &ptr2_test::ptrun2, pt_test, "ptrun2" );

  mismatch_test mis_test;

  t.add( &mismatch_test::mismatch0, mis_test, "mismatch0" );
  t.add( &mismatch_test::mismatch1, mis_test, "mismatch1" );
  t.add( &mismatch_test::mismatch2, mis_test, "mismatch2" );

  utility_test pr_test;

  t.add( &utility_test::pair0, pr_test, "pair0" );
  t.add( &utility_test::init, pr_test, "init" );
  t.add( &utility_test::forward, pr_test, "forward<A>" );

  rnd_shuffle_test rnd_test;

  t.add( &rnd_shuffle_test::rndshuf0, rnd_test, "rndshuf0" );
  t.add( &rnd_shuffle_test::rndshuf1, rnd_test, "rndshuf1" );

  nth_elem_test nth_test;

  t.add( &nth_elem_test::nthelem0, nth_test, "nthelem0" );
  t.add( &nth_elem_test::nthelem1, nth_test, "nthelem1" );
  t.add( &nth_elem_test::nthelem2, nth_test, "nthelem2" );

  includes_test incl_test;

  t.add( &includes_test::incl0, incl_test, "incl0" );
  t.add( &includes_test::incl1, incl_test, "incl1" );
  t.add( &includes_test::incl2, incl_test, "incl2" );

  inplace_test inp_test;

  t.add( &inplace_test::inplmrg1, inp_test, "inplmrg1" );
  t.add( &inplace_test::inplmrg2, inp_test, "inplmrg2" );

  rope_test rp_test;

  t.add( &rope_test::io, rp_test, "io" );
  t.add( &rope_test::find1, rp_test, "find1" );
  t.add( &rope_test::find2, rp_test, "find2" );
  t.add( &rope_test::construct_from_char, rp_test, "construct_from_char" );
  t.add( &rope_test::bug_report, rp_test, "bug_report" );
  t.add( &rope_test::test_saved_rope_iterators, rp_test, "test_saved_rope_iterators" );

  unary_test uny_test;

  t.add( &unary_test::unegate1, uny_test, "unegate1" );
  t.add( &unary_test::unegate2, uny_test, "unegate2" );
  t.add( &unary_test::unegate3, uny_test, "unegate3" );
  t.add( &unary_test::ucompose1, uny_test, "ucompose1" );
  t.add( &unary_test::ucompose2, uny_test, "ucompose2" );

  swap_test sw_test;

  t.add( &swap_test::swap1, sw_test, "swap1" );
  t.add( &swap_test::swprnge1, sw_test, "swprnge1" );
  t.add( &swap_test::swap_container_non_spec, sw_test, "swap_container_non_spec" );
  t.add( &swap_test::swap_container_spec, sw_test, "swap_container_spec" );

  merge_test mr_test;

  t.add( &merge_test::merge0, mr_test, "merge0" );
  t.add( &merge_test::merge1, mr_test, "merge1" );
  t.add( &merge_test::merge2, mr_test, "merge2" );

  divide_test div_test;
  t.add( &divide_test::div, div_test, "div" );

  lexcmp_test lcm_test;

  t.add( &lexcmp_test::lexcmp1, lcm_test, "lexcmp1" );
  t.add( &lexcmp_test::lexcmp2, lcm_test, "lexcmp2" );

  allocator_test al_test;

  t.add( &allocator_test::zero_allocation, al_test, "zero_allocation" );
  t.add( &allocator_test::bad_alloc_test, al_test, "bad_alloc_test" );
  t.add( &allocator_test::per_thread_alloc, al_test, "per_thread_alloc" );

  memory_test mem_test;
  t.add( &memory_test::auto_ptr_test, mem_test, "memory_test::auto_ptr_test" );

  rawriter_test rw_test;
  t.add( &rawriter_test::rawiter1, rw_test, "rawiter1" );

  strstream_buffer_test strb_test;
  t.add( &strstream_buffer_test::read_from_buffer, strb_test, "read_from_buffer" );

# endif

//file stream_test.cpp with this test wasn't added to Makefile.inc
//  strstream_test strs_test;
//  t.add( &strstream_test::input, strs_test, "strstream_test::input" );

#if 0
  ptrspec_test pts_test;

  t.add( &ptrspec_test::ptr_specialization_test, pts_test, "ptr_specialization_test" );
  t.add( &ptrspec_test::function_pointer, pts_test, "function_pointer" );

  limits_test lt_test;
  exam::test_suite::test_case_type limits_tc[10];

  limits_tc[0] = t.add( &limits_test::limits, lt_test, "limits_test::limits" );

  t.add( &limits_test::l_float, lt_test, "float limits", limits_tc[0] );
  t.add( &limits_test::l_double, lt_test, "double limits", limits_tc[0] );
  t.add( &limits_test::l_long_double, lt_test, "long double limits", limits_tc[0] );

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

#endif

  exception_test exc_test;

  t.add( &exception_test::what, exc_test, "exception_test::what" );

#if 0
  t.add( &exception_test::unexpected_except, exc_test, "exception_test::unexpected_except" );
  t.add( &exception_test::uncaught_except, exc_test, "exception_test::uncaught_except" );
  t.add( &exception_test::exception_emission, exc_test, "exception_test::exception_emission" );
#endif

  errno_test err_test;
  t.add( &errno_test::check, err_test, "errno_test::check" );

#if 0
  num_put_get_test nmg_test;
  t.add( &num_put_get_test::num_put_integer, nmg_test, "num_put_integer" );
  t.add( &num_put_get_test::num_get_integer, nmg_test, "num_get_integer" );
  t.add( &num_put_get_test::inhex, nmg_test, "inhex" );
  t.add( &num_put_get_test::pointer, nmg_test, "pointer" );


  // t.add( &num_put_get_test::scientific_precision, nmg_test, "scientific precision",
  t.add( &num_put_get_test::num_put_float, nmg_test, "num_put_float" ); // );

  t.add( &num_put_get_test::num_get_float, nmg_test, "num_get_float" );
  t.add( &num_put_get_test::fix_float_long, nmg_test, "fix_float_long" );
  t.add( &num_put_get_test::custom_numpunct, nmg_test, "custom_numpunct" );


  codecvt_test cvt_test;
  exam::test_suite::test_case_type cvt_tc[10];

  t.add( &codecvt_test::variable_encoding, cvt_test, "variable_encoding", fstream_tc[2] );
  t.add( &codecvt_test::in_out_test, cvt_test, "in_out_test" );
  t.add( &codecvt_test::length_test, cvt_test, "length_test" );
  t.add( &codecvt_test::imbue_while_reading, cvt_test, "imbue_while_reading" );

  t.add( &codecvt_test::_936_to_wchar, cvt_test, "convert CP936 to wchar",
    cvt_tc[0] = t.add( &codecvt_test::eol, cvt_test, "convert \\0" ) );

  t.add( &codecvt_test::bad_utf8, cvt_test, "convert bad UTF-8 to wchar",
    cvt_tc[1] = t.add( &codecvt_test::utf8_to_wchar, cvt_test, "convert UTF-8 to wchar", cvt_tc[0] ) );
  t.add( &codecvt_test::partial_conversion, cvt_test, "codecvt partial conversion", cvt_tc[1] );


  shared_ptr_test shp_test;
  t.add( &shared_ptr_test::shared_from_this, shp_test, "shared_from_this" );

  //  ref_wrapper_test ref_test;
  //  t.add( &ref_wrapper_test::ref, ref_test, "ref" );
  //  t.add( &ref_wrapper_test::cref, ref_test, "cref" );


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

  int ret = t.girdle();
  printf("Test result: %d\n", ret);
  char c = getchar();
  return ret;
}
