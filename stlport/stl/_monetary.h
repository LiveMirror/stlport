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
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef _STLP_INTERNAL_MONETARY_H
#define _STLP_INTERNAL_MONETARY_H

#ifndef _STLP_INTERNAL_OSTREAMBUF_ITERATOR_H
#  include <stl/_ostreambuf_iterator.h>
#endif

#ifndef _STLP_INTERNAL_ISTREAMBUF_ITERATOR_H
#  include <stl/_istreambuf_iterator.h>
#endif

#ifndef _STLP_FACETS_FWD_H
#  include <stl/_facets_fwd.h>
#endif

_STLP_BEGIN_NAMESPACE

class _STLP_CLASS_DECLSPEC money_base : public locale::facet {
public:
  enum part {none = 'x', space = ' ', symbol = '$', sign = '+', value = 'v'};
  struct pattern {
    char field[4];
  };
  money_base(size_t __refs) : locale::facet(__refs) {}
};

// moneypunct facets: forward declaration
template <class _charT, _STLP_DFL_NON_TYPE_PARAM(bool, _International, false) > class moneypunct {};

// money_get facets

template <class _CharT, class _InputIter>
class money_get : public locale::facet {
public:
  typedef _CharT               char_type;
  typedef _InputIter           iter_type;
  typedef basic_string<_CharT, char_traits<_CharT>, allocator<_CharT> > string_type;

  explicit money_get(size_t __refs = 0) : locale::facet(__refs) {}
  iter_type get(iter_type __s, iter_type  __end, bool __intl,
                ios_base&  __str, ios_base::iostate&  __err,
                _STLP_LONGEST_FLOAT_TYPE& __units) const
  { return do_get(__s,  __end, __intl,  __str,  __err, __units); }
  iter_type get(iter_type __s, iter_type  __end, bool __intl,
                ios_base&  __str, ios_base::iostate& __err,
                string_type& __digits) const
  { return do_get(__s,  __end, __intl,  __str,  __err, __digits); }

  static locale::id id;

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY

  explicit money_get(const _Locinfo& __i, size_t __refs = 0) : locale::facet(__refs) { _Init(__i); }

  static size_t _STLP_CALL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
				   ,const locale *__l = 0
#endif
				   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new money_get<char_type, iter_type>();
    return (locale::monetary);
  }

protected:
  void _Init(const _Locinfo&) {}

#endif

protected:
  ~money_get() {}
  virtual iter_type do_get(iter_type __s, iter_type  __end, bool  __intl,
                           ios_base&  __str, ios_base::iostate& __err,
                           _STLP_LONGEST_FLOAT_TYPE& __units) const;
  virtual iter_type do_get(iter_type __s, iter_type __end, bool __intl,
                           ios_base&  __str, ios_base::iostate& __err,
                           string_type& __digits) const;
};


template <class _CharT>
class _Mpunct : public money_base
{
public:
  typedef _CharT                                      char_type;
  typedef basic_string<_CharT, char_traits<_CharT> >  string_type;

  char        decimal_point() const { return do_decimal_point(); }
  char        thousands_sep() const { return do_thousands_sep(); }
  string      grouping()      const { return do_grouping(); }
  string_type curr_symbol()   const { return do_curr_symbol(); }
  string_type positive_sign() const { return do_positive_sign(); }
  string_type negative_sign() const { return do_negative_sign(); }
  int         frac_digits()   const { return do_frac_digits(); }
  pattern     pos_format()    const { return do_pos_format(); }
  pattern     neg_format()    const { return do_neg_format(); }

  explicit  _Mpunct(size_t __refs, bool __intl, bool __b = false) : money_base(__refs)
  { _M_init(__intl, __b); }

  void _M_init(bool __intl, bool __b) {
    // todo : hook up init 
  }

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY
  explicit _Mpunct(const _Locinfo& __i, size_t __refs, bool __intl, bool __b) : 
    money_base(__refs), _Intl(__intl) { _Init(__i, __b); }

protected:
  explicit _Mpunct(const char* __name, size_t __refs, bool __intl, bool __b = false) : 
    money_base(__refs), _Intl(__intl) { _Init(_Locinfo(__name), __b); }

  void _Init(const _Locinfo&, bool __b = false) {
    // TODO: implement
  }

#endif

 protected:

  virtual _CharT do_decimal_point() const
  {
    return (_M_decimal_point);
  }
  
  virtual _CharT do_thousands_sep() const
  {
    return (_M_separator);
  }
  
  virtual string  do_grouping() const
  {
    return (string(_M_grouping));
  }
  
  virtual string_type  do_curr_symbol() const
  {
    return (string_type(_M_curr_symbol));
  }
  
  virtual string_type  do_positive_sign() const
  {
    return (string_type(_M_plus_sign));
  }
  
  virtual string_type  do_negative_sign() const
  {
    return (string_type(_M_minus_sign));
  }
  
  virtual int  do_frac_digits() const
  {
    return (_M_frac_digits);
  }
  
  virtual pattern  do_pos_format() const
  {
    return (_M_pos_format);
  }
  
  virtual pattern  do_neg_format() const
  {
    return (_M_neg_format);
  }
  

  virtual  ~_Mpunct()
  {	// destroy the object
    _Tidy();
  }

private:
  void  _Makpat(pattern&, unsigned int,
		unsigned int, unsigned int)
  {
    // TODO: fill
  }
  
  void  _Tidy()
  {
    // TODO : fill
  }
 
protected:
  const char *_M_grouping;
  _CharT _M_decimal_point;
  _CharT _M_separator;
  const _CharT *_M_curr_symbol;
  const _CharT *_M_plus_sign;
  const _CharT *_M_minus_sign;
  int _M_frac_digits;
  pattern _M_pos_format;
  pattern _M_neg_format;
  bool _Intl;
};


// moneypunct facets: definition of specializations

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct<char, true> : public _Mpunct<char> {
public:
  typedef char                 char_type;
  typedef string               string_type;
  explicit moneypunct _STLP_PSPEC2(char, true) (size_t __refs = 0);


  static _STLP_STATIC_DECLSPEC locale::id id;
  _STLP_STATIC_CONSTANT(bool, intl = true);

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY

  explicit moneypunct(const _Locinfo& __i, size_t __refs = 0) : _Mpunct<char>(__refs, true) {}

  static size_t _STLP_CALL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
				   , const locale *__l = 0
#endif
				   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new moneypunct<char_type, true>();
    return (locale::monetary);
  }

 protected:
  explicit moneypunct(const char* __name, size_t __refs = 0) : _Mpunct<char>(__name, __refs, true) {}

#endif

protected:

  ~moneypunct _STLP_PSPEC2(char, true) ();

  virtual char        do_decimal_point() const;
  virtual char        do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string      do_curr_symbol()   const;

  virtual string      do_positive_sign() const;
  virtual string      do_negative_sign() const;
  virtual int         do_frac_digits()   const;
  virtual pattern     do_pos_format()    const;
  virtual pattern     do_neg_format()    const;
};

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct<char, false> : public _Mpunct<char> {
public:
  typedef char                 char_type;
  typedef string               string_type;

  explicit moneypunct _STLP_PSPEC2(char, false) (size_t __refs = 0);

  static _STLP_STATIC_DECLSPEC locale::id id;
  _STLP_STATIC_CONSTANT(bool, intl = false);

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY
  explicit moneypunct(const _Locinfo& __i, size_t __refs = 0) : _Mpunct<char>(__refs, false) {}
  static size_t __CLRCALL_OR_CDECL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
					   , const locale * = 0
#endif
					   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new moneypunct<char_type, false>();
    return (locale::monetary);
  }
 protected:
  explicit moneypunct(const char* __name, size_t __refs = 0) : _Mpunct<char>(__name, __refs, false) {}
  void _Init(const _Locinfo&) {}
#endif

protected:

  ~moneypunct _STLP_PSPEC2(char, false) ();

  virtual char        do_decimal_point() const;
  virtual char        do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string      do_curr_symbol()   const;

  virtual string      do_positive_sign() const;
  virtual string      do_negative_sign() const;
  virtual int         do_frac_digits()   const;
  virtual pattern     do_pos_format()    const;
  virtual pattern     do_neg_format()    const;
};


#ifndef _STLP_NO_WCHAR_T

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct<wchar_t, true> : public _Mpunct<wchar_t> {
public:
  typedef wchar_t                 char_type;
  typedef wstring                 string_type;
  explicit moneypunct _STLP_PSPEC2(wchar_t, true) (size_t __refs = 0);

  static _STLP_STATIC_DECLSPEC locale::id id;
  _STLP_STATIC_CONSTANT(bool, intl = true);

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY

  explicit moneypunct(const _Locinfo& __i, size_t __refs = 0) : _Mpunct<wchar_t>(__refs, true) {}

  static size_t _STLP_CALL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
				   ,const locale * = 0
#endif
				   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new moneypunct<char_type, true>();
    return (locale::monetary);
  }

 protected:
  void _Init(const _Locinfo&) {}
  explicit moneypunct(const char* __name, size_t __refs = 0) : _Mpunct<wchar_t>(__name, __refs, true) {}

#endif

protected:

  ~moneypunct _STLP_PSPEC2(wchar_t, true) ();

  virtual wchar_t     do_decimal_point() const;
  virtual wchar_t     do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;
  virtual pattern     do_pos_format()    const;
  virtual pattern     do_neg_format()    const;
};


_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct<wchar_t, false> : public _Mpunct<wchar_t> {
public:
  typedef wchar_t                 char_type;
  typedef wstring                 string_type;
  explicit moneypunct _STLP_PSPEC2(wchar_t, false) (size_t __refs = 0);

  static _STLP_STATIC_DECLSPEC locale::id id;
  _STLP_STATIC_CONSTANT(bool, intl = false);

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY
  explicit moneypunct(const _Locinfo& __i, size_t __refs = 0) : _Mpunct<wchar_t>(__refs, false) {}

  static size_t _STLP_CALL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
				   ,const locale *  = 0
#endif
				   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new moneypunct<char_type, false>();
    return (locale::monetary);
  }

 protected:
  explicit moneypunct(const char* __name, size_t __refs = 0) : _Mpunct<wchar_t>(__name, __refs, false) { }
  void _Init(const _Locinfo&) {}
#endif

protected:

  ~moneypunct _STLP_PSPEC2(wchar_t, false) ();

  virtual wchar_t     do_decimal_point() const;
  virtual wchar_t     do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;
  virtual pattern     do_pos_format()    const;
  virtual pattern     do_neg_format()    const;
};

# endif

template <class _charT, _STLP_DFL_NON_TYPE_PARAM(bool , _International , false) > class moneypunct_byname {};

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct_byname<char, true> : public moneypunct<char, true> {
  friend class locale::_Locimp;
public:
  typedef money_base::pattern   pattern;
  typedef char                  char_type;
  typedef string                string_type;

  explicit moneypunct_byname _STLP_PSPEC2(char, true) (const char * __name, size_t __refs = 0);

protected:
  ~moneypunct_byname _STLP_PSPEC2(char, true) ();
  virtual char        do_decimal_point() const;
  virtual char        do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;

private:
  moneypunct_byname _STLP_PSPEC2(char, true) (_Locale_monetary *__monetary);

  typedef moneypunct_byname<char, true> _Self;
  //explicitely defined as private to avoid warnings:
  moneypunct_byname(_Self const&);
  _Self& operator = (_Self const&);

  _Locale_monetary* _M_monetary;
};

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct_byname<char, false> : public moneypunct<char, false> {
  friend class locale::_Locimp;
public:
  typedef money_base::pattern   pattern;
  typedef char                  char_type;
  typedef string                string_type;

  explicit moneypunct_byname _STLP_PSPEC2(char, false) (const char * __name, size_t __refs = 0);

protected:
  ~moneypunct_byname _STLP_PSPEC2(char, false) ();
  virtual char        do_decimal_point() const;
  virtual char        do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;

private:
  moneypunct_byname _STLP_PSPEC2(char, false) (_Locale_monetary *__monetary);

  typedef moneypunct_byname<char, false> _Self;
  //explicitely defined as private to avoid warnings:
  moneypunct_byname(_Self const&);
  _Self& operator = (_Self const&);

  _Locale_monetary* _M_monetary;
};

#if !defined (_STLP_NO_WCHAR_T)
_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct_byname<wchar_t, true> : public moneypunct<wchar_t, true> {
  friend class locale::_Locimp;
public:
  typedef money_base::pattern   pattern;
  typedef wchar_t               char_type;
  typedef wstring               string_type;

  explicit moneypunct_byname _STLP_PSPEC2(wchar_t, true) (const char * __name, size_t __refs = 0);

protected:
  ~moneypunct_byname _STLP_PSPEC2(wchar_t, true) ();
  virtual wchar_t     do_decimal_point() const;
  virtual wchar_t     do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;

private:
  moneypunct_byname _STLP_PSPEC2(wchar_t, true) (_Locale_monetary *__monetary);

  typedef moneypunct_byname<wchar_t, true> _Self;
  //explicitely defined as private to avoid warnings:
  moneypunct_byname(_Self const&);
  _Self& operator = (_Self const&);

  _Locale_monetary* _M_monetary;
};

_STLP_TEMPLATE_NULL
class _STLP_CLASS_DECLSPEC moneypunct_byname<wchar_t, false> : public moneypunct<wchar_t, false> {
  friend class locale::_Locimp;
public:
  typedef money_base::pattern   pattern;
  typedef wchar_t               char_type;
  typedef wstring               string_type;

  explicit moneypunct_byname _STLP_PSPEC2(wchar_t, false) (const char * __name, size_t __refs = 0);

protected:
  ~moneypunct_byname _STLP_PSPEC2(wchar_t, false) ();
  virtual wchar_t     do_decimal_point() const;
  virtual wchar_t     do_thousands_sep() const;
  virtual string      do_grouping()      const;

  virtual string_type do_curr_symbol()   const;

  virtual string_type do_positive_sign() const;
  virtual string_type do_negative_sign() const;
  virtual int         do_frac_digits()   const;

private:
  moneypunct_byname _STLP_PSPEC2(wchar_t, false) (_Locale_monetary *__monetary);

  typedef moneypunct_byname<wchar_t, false> _Self;
  //explicitely defined as private to avoid warnings:
  moneypunct_byname(_Self const&);
  _Self& operator = (_Self const&);

  _Locale_monetary* _M_monetary;
};
#endif

//===== methods ======


// money_put facets

template <class _CharT, class _OutputIter>
class money_put : public locale::facet {
public:
  typedef _CharT               char_type;
  typedef _OutputIter          iter_type;
  typedef basic_string<_CharT, char_traits<_CharT>, allocator<_CharT> > string_type;

  explicit money_put(size_t __refs = 0) : locale::facet(__refs) {}
  iter_type put(iter_type __s, bool __intl, ios_base& __str,
                char_type  __fill, _STLP_LONGEST_FLOAT_TYPE __units) const
    { return do_put(__s, __intl, __str, __fill, __units); }
  iter_type put(iter_type __s, bool __intl, ios_base& __str,
                char_type  __fill,
                const string_type& __digits) const
    { return do_put(__s, __intl, __str, __fill, __digits); }

  static locale::id id;

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY
  void _Init(const _Locinfo&) {}

  explicit money_put(const _Locinfo& __i, size_t __refs = 0) : locale::facet(__refs) { _Init(__i); }

  static size_t _STLP_CALL _Getcat(const locale::facet **__f = 0
#if (_MSC_VER >= 1500)
				   ,const locale * = 0
#endif
				   )
  {	// return locale category mask and construct standard facet
    if (__f != 0 && *__f == 0)
      *__f = new money_put<char_type,iter_type>();
    return (locale::monetary);
  }
#endif

protected:
  ~money_put() {}
  virtual iter_type do_put(iter_type __s, bool  __intl, ios_base&  __str,
                           char_type __fill, _STLP_LONGEST_FLOAT_TYPE __units) const;
  virtual iter_type do_put(iter_type __s, bool  __intl, ios_base&  __str,
                           char_type __fill,
                           const string_type& __digits) const;
};

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS _Mpunct<char>;
_STLP_EXPORT_TEMPLATE_CLASS money_get<char, istreambuf_iterator<char, char_traits<char> > >;
_STLP_EXPORT_TEMPLATE_CLASS money_put<char, ostreambuf_iterator<char, char_traits<char> > >;
#  if ! defined (_STLP_NO_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS _Mpunct<wchar_t>;
_STLP_EXPORT_TEMPLATE_CLASS money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
_STLP_EXPORT_TEMPLATE_CLASS money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
#  endif
#endif

_STLP_END_NAMESPACE

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION)
#  include <stl/_monetary.c>
#endif

#endif /* _STLP_INTERNAL_MONETARY_H */

// Local Variables:
// mode:C++
// End:


