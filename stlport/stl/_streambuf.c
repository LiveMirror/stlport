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
#ifndef _STLP_STREAMBUF_C
#define _STLP_STREAMBUF_C

#ifndef _STLP_INTERNAL_STREAMBUF
#  include <stl/_streambuf.h>
#endif

_STLP_BEGIN_NAMESPACE
//----------------------------------------------------------------------
// Non-inline basic_streambuf<> member functions.


template <class _CharT, class _Traits>
basic_streambuf<_CharT, _Traits>::basic_streambuf()
  : _M_gbegin(0), _M_pbegin(0),
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
    _M_p_gbegin(&_M_gbegin), _M_p_pbegin(&_M_pbegin),
#endif
    _M_gnext(0), _M_pnext(0),
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
    _M_p_gnext(&_M_gnext), _M_p_pnext(&_M_pnext),
#endif
    _M_gcount(0), _M_pcount(0),
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
    _M_p_gcount(&_M_gcount), _M_p_pcount(&_M_pcount),
#endif
    _M_locale(new locale()) {
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
    _M_lock._M_initialize();
#endif
}

template <class _CharT, class _Traits>
basic_streambuf<_CharT, _Traits>::~basic_streambuf()  { delete _M_locale; }

template <class _CharT, class _Traits>
locale basic_streambuf<_CharT, _Traits>::pubimbue(const locale& __loc) 
{
  this->imbue(__loc);
  locale __tmp = *_M_locale;
  *_M_locale = __loc;
  return __tmp;
}

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
template <class _CharT, class _Traits>
streamsize basic_streambuf<_CharT, _Traits>::_Xsgetn_s(_CharT* __s, size_t __size, streamsize __n) 
{
  streamsize __minsize = std::min((streamsize)__size, __n);
  return xsgetn(__s, __minsize);
}
#endif

template <class _CharT, class _Traits>
streamsize basic_streambuf<_CharT, _Traits>::xsgetn(_CharT* __s, streamsize __n) 
{
  streamsize __result = 0;
  const int_type __eof = traits_type::eof();

  while (__result < __n) {
    if (*_M_p_gcount > 0) {
      size_t __chunk = (min) (__STATIC_CAST(size_t,*_M_p_gcount),
                              __STATIC_CAST(size_t,__n - __result));
      traits_type::copy(__s, *_M_p_gnext, __chunk);
      __result += __chunk;
      __s += __chunk;
      gbump((int)__chunk);
    } else {
      int_type __c = this->sbumpc();
      if (!traits_type::eq_int_type(__c, __eof)) {
        *__s = traits_type::to_char_type(__c);
        ++__result;
        ++__s;
      }
      else
        break;
    }
  }
  return __result;
}

template <class _CharT, class _Traits>
streamsize basic_streambuf<_CharT, _Traits>::xsputn(const _CharT* __s, streamsize __n)
{
  streamsize __result = 0;
  const int_type __eof = traits_type::eof();

  while (__result < __n) {
    streamsize __avail(_Pnavail());
    if (__avail > 0) {
      size_t __chunk = (min) (__STATIC_CAST(size_t, __avail), __STATIC_CAST(size_t,__n - __result));
      traits_type::copy(*_M_p_pnext, __s, __chunk);
      __result += __chunk;
      __s += __chunk;
      pbump(__chunk);
    } else if (!traits_type::eq_int_type(this->overflow(traits_type::to_int_type(*__s)), __eof)) {
      ++__result;
      ++__s;
    }
    else
      break;
  }
  return __result;
}

template <class _CharT, class _Traits> 
streamsize basic_streambuf<_CharT, _Traits>::_M_xsputnc(_CharT __c, streamsize __n)
{
  streamsize __result = 0;
  const int_type __eof = traits_type::eof();

  while (__result < __n) {
    if (*_M_p_pcount > 0) {
      size_t __chunk = (min) (__STATIC_CAST(size_t,*_M_p_pcount), __STATIC_CAST(size_t,__n - __result));
      traits_type::assign(*_M_p_pnext, __chunk, __c);
      __result += __chunk;
      *_M_p_pnext += __chunk;
    } else if (!traits_type::eq_int_type(this->overflow(traits_type::to_int_type(__c)), __eof))
      ++__result;
    else
      break;
  }
  return __result;
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::int_type
basic_streambuf<_CharT, _Traits>::pbackfail(int_type) { return traits_type::eof(); }

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::int_type
basic_streambuf<_CharT, _Traits>::overflow(int_type) { return traits_type::eof(); }

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::int_type
basic_streambuf<_CharT, _Traits>::uflow() {
    return ( traits_type::eq_int_type(this->underflow(),traits_type::eof()) ?
             traits_type::eof() :
             traits_type::to_int_type(*_Gninc()));
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::int_type
basic_streambuf<_CharT, _Traits>::underflow() { return traits_type::eof(); }

template <class _CharT, class _Traits> streamsize basic_streambuf<_CharT, _Traits>::showmanyc() { return 0; }

template <class _CharT, class _Traits> void basic_streambuf<_CharT, _Traits>::imbue(const locale&) {}

template <class _CharT, class _Traits> int basic_streambuf<_CharT, _Traits>::sync() { return 0; }

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::pos_type
basic_streambuf<_CharT, _Traits>::seekpos(pos_type, ios_base::openmode) { return pos_type(-1); }

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_streambuf<_CharT, _Traits>::pos_type
basic_streambuf<_CharT, _Traits>::seekoff(off_type, ios_base::seekdir, ios_base::openmode) { return pos_type(-1); }

template <class _CharT, class _Traits>
basic_streambuf<_CharT, _Traits>* basic_streambuf<_CharT, _Traits>:: setbuf(char_type*, streamsize) { return this; }

_STLP_END_NAMESPACE

#endif

// Local Variables:
// mode:C++
// End:
