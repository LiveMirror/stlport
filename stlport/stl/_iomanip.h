/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
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

#ifndef _STLP_INTERNAL_IOMANIP
#define _STLP_INTERNAL_IOMANIP

#ifndef _STLP_INTERNAL_ISTREAM
#  include <stl/_istream.h>              // Includes <ostream> and <ios>
#endif

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Machinery for defining manipulators.

// Class that calls one of ios_base's single-argument member functions.
template <class _Arg>
struct _Smanip {
  typedef _Arg (_STLP_CALL *__f_ptr_type)(ios_base&, _Arg);

  _Smanip(__f_ptr_type __f, const _Arg& __arg)
    : _M_f(__f), _M_arg(__arg) {}

  void operator()(ios_base& __ios) const
  { (*_M_f)(__ios, _M_arg); }

  __f_ptr_type _M_f;
  _Arg _M_arg;
};

typedef _Smanip<ios_base::fmtflags> _Ios_Setf_Manip;

template <class _CharT, class _Traits, class _Arg>
inline basic_istream<_CharT, _Traits>& _STLP_CALL
operator>>(basic_istream<_CharT, _Traits>& __istr,
           const  _Smanip<_Arg>& __f) {
  __f(__istr);
  return __istr;
}

template <class _CharT, class _Traits, class _Arg>
inline basic_ostream<_CharT, _Traits>& _STLP_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const  _Smanip<_Arg>& __f) {
  __f(__os);
  return __os;
}

template <class _CharT, class _Traits>
inline basic_istream<_CharT, _Traits>& _STLP_CALL
operator>>(basic_istream<_CharT, _Traits>& __istr,
           const  _Ios_Setf_Manip& __f) {
  __f(__istr);
  return __istr;
}

template <class _CharT, class _Traits>
inline basic_ostream<_CharT, _Traits>& _STLP_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const  _Ios_Setf_Manip& __f) {
  __f(__os);
  return __os;
}

//----------------------------------------------------------------------
// The ios_base manipulators.
_STLP_DECLSPEC _Ios_Setf_Manip _STLP_CALL resetiosflags(ios_base::fmtflags __mask);

_STLP_DECLSPEC _Ios_Setf_Manip _STLP_CALL setiosflags(ios_base::fmtflags __flag);

_STLP_DECLSPEC _Ios_Setf_Manip _STLP_CALL setbase(int __n);

_STLP_DECLSPEC _Smanip<streamsize> _STLP_CALL setprecision(int __n);

_STLP_DECLSPEC _Smanip<streamsize>  _STLP_CALL setw(int __n);

//----------------------------------------------------------------------
// setfill, a manipulator that operates on basic_ios<> instead of ios_base.

template <class _CharT>
struct _Fillobj {
  _Fillobj(_CharT __c) : _M_c(__c) {}
  _CharT _M_c;
};

template <class _CharT, class _CharT2, class _Traits>
inline basic_ostream<_CharT, _Traits>& _STLP_CALL
operator<<(basic_ostream<_CharT, _Traits>& __os,
           const  _Fillobj<_CharT2>& __m) {
  __os.fill(__m._M_c);
  return __os;
}

template <class _CharT, class _CharT2, class _Traits>
inline basic_istream<_CharT, _Traits>& _STLP_CALL
operator>>(basic_istream<_CharT, _Traits>& __is,
           const  _Fillobj<_CharT2>& __m) {
  __is.fill(__m._M_c);
  return __is;
}

template <class _CharT>
inline _Fillobj<_CharT> _STLP_CALL setfill(_CharT __c)
{ return _Fillobj<_CharT>(__c); }

_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_IOMANIP */
