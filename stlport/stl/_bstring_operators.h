/*
 * Copyright (c) 2003
 * Francois Dumont
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

#ifndef _STLP_BSTRING_OPERATORS_H
#define _STLP_BSTRING_OPERATORS_H

_STLP_BEGIN_NAMESPACE

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  typedef basic_string<_CharT,_Traits,_Alloc> _Str;
  typedef typename _Str::_Reserve_t _Reserve_t;
#  if defined (_STLP_INIT_AMBIGUITY)
  // gcc counts this as a function
  _Str __result  = _Str(_Reserve_t(), __s.size() + __y.size(), __s.get_allocator());
#  else
  _Str __result(_Reserve_t(), __s.size() + __y.size(), __s.get_allocator());
#  endif
  __result.append(__s);
  __result.append(__y);
  return __result;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  typedef basic_string<_CharT,_Traits,_Alloc> _Str;
  typedef typename _Str::_Reserve_t _Reserve_t;
  const size_t __n = _Traits::length(__s);
#  if defined (_STLP_INIT_AMBIGUITY)
  _Str __result = _Str(_Reserve_t(), __n + __y.size(), __y.get_allocator());
#  else
  _Str __result(_Reserve_t(), __n + __y.size(), __y.get_allocator());
#  endif
  __result.append(__s, __s + __n);
  __result.append(__y);
  return __result;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(_CharT __c,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  typedef basic_string<_CharT,_Traits,_Alloc> _Str;
  typedef typename _Str::_Reserve_t _Reserve_t;
#  if defined (_STLP_INIT_AMBIGUITY)
  _Str __result = _Str(_Reserve_t(), 1 + __y.size(), __y.get_allocator());
#  else
  _Str __result(_Reserve_t(), 1 + __y.size(), __y.get_allocator());
#  endif
  __result.push_back(__c);
  __result.append(__y);
  return __result;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  typedef basic_string<_CharT,_Traits,_Alloc> _Str;
  typedef typename _Str::_Reserve_t _Reserve_t;
  const size_t __n = _Traits::length(__s);
#  if defined (_STLP_INIT_AMBIGUITY)
  _Str __result = _Str(_Reserve_t(), __x.size() + __n, __x.get_allocator());
#  else
  _Str __result(_Reserve_t(), __x.size() + __n, __x.get_allocator());
#  endif
  __result.append(__x);
  __result.append(__s, __s + __n);
  return __result;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC basic_string<_CharT,_Traits,_Alloc> _STLP_CALL
operator+(const basic_string<_CharT,_Traits,_Alloc>& __x,
          _CharT __c) {
  typedef basic_string<_CharT,_Traits,_Alloc> _Str;
  typedef typename _Str::_Reserve_t _Reserve_t;
#  if defined (_STLP_INIT_AMBIGUITY)
  _Str __result = _Str(_Reserve_t(), __x.size() + 1, __x.get_allocator());
#  else
  _Str __result(_Reserve_t(), __x.size() + 1, __x.get_allocator());
#  endif
  __result.append(__x);
  __result.push_back(__c);
  return __result;
}

#  undef _STLP_INIT_AMBIGUITY

// Operator== and operator!=

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
 operator==(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return __x.size() == __y.size() && _Traits::compare(__x.data(), __y.data(), __x.size()) == 0;
}


template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
 operator==(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  size_t __n = _Traits::length(__s);
  return __n == __y.size() && _Traits::compare(__s, __y.data(), __n) == 0;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator==(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  size_t __n = _Traits::length(__s);
  return __x.size() == __n && _Traits::compare(__x.data(), __s, __n) == 0;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
 operator==(_CharT __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return __y.size() == 1 && _Traits::compare(&__s, __y.data(), 1) == 0;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
  operator==( const basic_string<_CharT,_Traits,_Alloc>& __y, _CharT __s) {
  return __y.size() == 1 && _Traits::compare(&__s, __y.data(), 1) == 0;
}

// Operator< (and also >, <=, and >=).

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return basic_string<_CharT,_Traits,_Alloc> ::_M_compare(__x.data(), __x.data()+__x.size(),
                                                          __y.data(), __y.data()+__y.size()) < 0;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  size_t __n = _Traits::length(__s);
  return basic_string<_CharT,_Traits,_Alloc> ::_M_compare(__s, __s + __n,
                                                          __y.data(), __y.data()+__y.size()) < 0;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  size_t __n = _Traits::length(__s);
  return basic_string<_CharT,_Traits,_Alloc> ::_M_compare(__x.data(), __x.data()+__x.size(),
                                                          __s, __s + __n) < 0;
}

/* Only defined if _STLP_USE_SEPARATE_RELOPS_NAMESPACE is defined otherwise
 * it might introduce ambiguity with pure template relational operators
 * from rel_ops namespace.
 */
template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator!=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y)
{ return !(__x == __y); }

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const basic_string<_CharT,_Traits,_Alloc>& __y)
{ return __y < __x; }

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y)
{ return !(__y < __x); }

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const basic_string<_CharT,_Traits,_Alloc>& __y)
{ return !(__x < __y); }

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator!=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return !(__s == __y);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator!=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  return !(__x == __s);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
  operator!=(const basic_string<_CharT,_Traits,_Alloc>& __y, _CharT __s) {
  return !(__s == __y);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
  operator!=(_CharT __s, const basic_string<_CharT,_Traits,_Alloc>& __y) {
  return !(__s == __y);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>(const _CharT* __s,
          const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return __y < __s;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>(const basic_string<_CharT,_Traits,_Alloc>& __x,
          const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return __s < __x;
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__y < __s);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator<=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__s < __x);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>=(const _CharT* __s,
           const basic_string<_CharT,_Traits,_Alloc>& __y) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__s < __y);
}

template <class _CharT, class _Traits, class _Alloc>
_STLP_DECLSPEC bool _STLP_CALL
operator>=(const basic_string<_CharT,_Traits,_Alloc>& __x,
           const _CharT* __s) {
  _STLP_FIX_LITERAL_BUG(__s)
  return !(__x < __s);
}

_STLP_END_NAMESPACE

#endif /* _STLP_BSTRING_OPERATORS_H */

