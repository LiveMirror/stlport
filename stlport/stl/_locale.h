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


#ifndef _STLP_INTERNAL_LOCALE_H
#define _STLP_INTERNAL_LOCALE_H

#ifndef _STLP_INTERNAL_CSTDLIB
#  include <stl/_cstdlib.h>
#endif

#ifndef _STLP_INTERNAL_CWCHAR
#  include <stl/_cwchar.h>
#endif

#ifndef _STLP_INTERNAL_THREADS_H
#  include <stl/_threads.h>
#endif

#include <vector>

#ifndef _STLP_STRING_H
#  include <stl/_string.h>
#endif

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
#include <stl/_locinfo.h>
#endif

#include <stl/_facets_fwd.h>

struct _Locale_name_hint;

_STLP_BEGIN_NAMESPACE

class _Locinfo;
class locale;

template <class _CharT, class _Traits, class _Alloc>
bool __locale_do_operator_call(const locale& __loc,
                               const basic_string<_CharT, _Traits, _Alloc>& __x,
                               const basic_string<_CharT, _Traits, _Alloc>& __y);


_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _Facet>
bool _HasFacet(const locale& __loc, const _Facet* facet) _STLP_NOTHROW;

template <class _Facet>
_Facet* _UseFacet(const locale& __loc, const _Facet* __facet);

template <class _Facet>
void _InsertFacet(locale& __loc, _Facet* __facet);

_STLP_MOVE_TO_STD_NAMESPACE

#if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND) || \
    defined (_STLP_SIGNAL_RUNTIME_COMPATIBILITY) || defined (_STLP_CHECK_RUNTIME_COMPATIBILITY)
#  define locale _STLP_NO_MEM_T_NAME(loc)
#endif

class _STLP_CLASS_DECLSPEC locale {
public:

  class _Locimp; 
  friend class _Locimp;

  // types:
  class _STLP_CLASS_DECLSPEC facet : public _Refcount_Base {
  protected:
    /* Here we filter __init_count user value to 0 or 1 because __init_count is a
     * size_t instance and _Refcount_Base use __stl_atomic_t instances that might
     * have lower sizeof and generate roll issues. 1 is enough to keep the facet
     * alive when required. */
    explicit facet(size_t __init_count = 0);
    friend class locale;
    friend class _Locimp;
    friend facet * _STLP_CALL _get_facet( facet * );
    friend void _STLP_CALL _release_facet( facet *& );
#if defined (_MSC_VER) && (_MSC_VER < 1500)
 public:
#endif
    virtual ~facet();
  private:                        // Invalidate assignment and copying.
    facet(const facet& ) /* : _Refcount_Base(1) {} */;
    void operator=(const facet&);
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  public:
    void  _Incref() {
      _M_incr();
    }
    facet * _Decref() {
      return (_M_decr() ? this : 0);
    }
    void _Register() {
      facet_Register(this);
    }

    static size_t _STLP_CALL _Getcat(const facet **
#if (_MSC_VER >= 1500)
				     , const locale *
#endif
				     );
  private:
    static void _STLP_CALL facet_Register(facet *);
#endif
  };

#if defined (__MVS__) || defined (__OS400__)
  struct
#else
  class
#endif
  _STLP_CLASS_DECLSPEC id {
  public:
    id() {}
    id(size_t __id) : _M_index(__id) {}
    size_t _M_index;
    static size_t _S_max;
    operator size_t() { return _M_index; };
  };

  typedef int category;
  _STLP_STATIC_CONSTANT(category, none = 0x000);
  _STLP_STATIC_CONSTANT(category, collate = 0x010);
  _STLP_STATIC_CONSTANT(category, ctype = 0x020);
  _STLP_STATIC_CONSTANT(category, monetary = 0x040);
  _STLP_STATIC_CONSTANT(category, numeric = 0x100);
  _STLP_STATIC_CONSTANT(category, time = 0x200);
  _STLP_STATIC_CONSTANT(category, messages = 0x400);
  _STLP_STATIC_CONSTANT(category, all = collate | ctype | monetary | numeric | time | messages);

  // construct/copy/destroy:
  locale() _STLP_NOTHROW;
  locale(const locale&) _STLP_NOTHROW;
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  explicit locale(const char*,  category = all);
  locale (_Uninitialized);
  const facet * _Getfacet(size_t __id) const
  {
    return _M_get_facet(__id);
  }

#else
  explicit locale(const char *);
#endif
  locale(const locale&, const char*, category);

#if !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
  template <class _Facet>
  locale(const locale& __loc, _Facet* __f);
#endif

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
private:
  static _Locimp *__cdecl _Getgloballocale();
  static _Locimp *__cdecl _Init();
  static void __cdecl _Setgloballocale(void *);
#endif

private:
  // those are for internal use
  locale(_Locimp*);
  static const string _Nameless;

public:
  locale(const locale&, const locale&, category);
  locale& operator=(const locale&) _STLP_NOTHROW;

  ~locale() _STLP_NOTHROW;

public:
#if !defined (_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS) && \
   !defined(_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
  template <class _Facet>
  locale combine(const locale& __loc) const {
    _Facet *__facet = 0;
    if (!_STLP_PRIV _HasFacet(__loc, __facet))
      _M_throw_on_combine_error(__loc.name());

    return locale(*this, _STLP_PRIV _UseFacet(__loc, __facet));
  }
#endif

  // locale operations:
  string name() const;

  bool operator==(const locale& __L) const  {
    return this->_M_impl == __L._M_impl ||
      (this->name() == __L.name() && this->name() != _Nameless);
  }
  bool operator!=(const locale& __L) const {
    return !(*this == __L);
  }
  
#if defined (_STLP_INLINE_MEMBER_TEMPLATES)
  bool operator()(const string& __x, const string& __y) const;
#  ifndef _STLP_NO_WCHAR_T
  bool operator()(const wstring& __x, const wstring& __y) const;
#  endif
#elif !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
  template <class _CharT, class _Traits, class _Alloc>
  bool operator()(const basic_string<_CharT, _Traits, _Alloc>& __x,
                  const basic_string<_CharT, _Traits, _Alloc>& __y) const
  { return __locale_do_operator_call(*this, __x, __y); }
#endif

  // global locale objects:
#if !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
  static locale _STLP_CALL global(const locale&);
#else
  static _Locimp* _STLP_CALL global(const locale&);
#endif
  static const locale& _STLP_CALL classic();

//protected:                         // Helper functions for locale globals.
  facet* _M_get_facet(const id&) const;
  // same, but throws
  facet* _M_use_facet(const id&) const;
  static void _STLP_FUNCTION_THROWS _STLP_CALL _M_throw_on_combine_error(const string& name);
  static void _STLP_FUNCTION_THROWS _STLP_CALL _M_throw_on_null_name();
  static void _STLP_FUNCTION_THROWS _STLP_CALL _M_throw_on_creation_failure(int __err_code,
                                                                            const char* name, const char* facet);

//protected:                        // More helper functions.
  void _M_insert(facet* __f, id& __id);

  // Class _Locimp
  class _STLP_CLASS_DECLSPEC _Locimp : public facet {

  private:
    _Locimp(const char* s);
    _Locimp(const _Locimp&);
    _Locimp(size_t n, const char* s);

  protected:
    ~_Locimp();
    
  public:
    size_t size() const { return facets_vec.size(); }
    
    basic_string<char, char_traits<char>, allocator<char> > name;
    
    static void _STLP_FUNCTION_THROWS _STLP_CALL _M_throw_bad_cast();
    
  private:
    void _STLP_CALL operator=(const _Locimp&);
    
  public:
    class _STLP_CLASS_DECLSPEC Init {
    public:
      Init();
      ~Init();
    private:
      _Refcount_Base& _M_count() const;
    };
    
    static void _STLP_CALL _S_initialize();
    static void _STLP_CALL _S_uninitialize();
    
    static void make_classic_locale();
    static void free_classic_locale();
    
    friend class Init;

  public:
    // void remove(size_t index);
    void insert_from(locale::_Locimp* __from, size_t __n);
    void insert(locale::facet* __f, locale::id __id);

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  private:
    void _Addfac(locale::facet*, size_t, size_t);
    static _Locimp*  _STLP_CALL  _Makeloc(const _Locinfo&, category, _Locimp*, const locale*);
    static _Locimp*&  _STLP_CALL _Clocptr_func();
    // #ifndef _STLP_NO_WCHAR_T
    static void  _STLP_CALL _Makewloc(const _Locinfo&, category, _Locimp *, const locale*);
    static void _STLP_CALL _Makeushloc(const _Locinfo&, category, _Locimp *, const locale *);
    // #endif /* _NATIVE_WCHAR_T_DEFINED */
    static void _Makexloc(const _Locinfo&, category, _Locimp *, const locale *);
    _Locimp(bool);
#endif
  public:
    // Helper functions for byname construction of locales.
    _Locale_name_hint* insert_ctype_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    _Locale_name_hint* insert_numeric_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    _Locale_name_hint* insert_time_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    _Locale_name_hint* insert_collate_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    _Locale_name_hint* insert_monetary_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    _Locale_name_hint* insert_messages_facets(const char* &name, char *buf, _Locale_name_hint* hint);
    
    bool operator != (const locale& __loc) const { return __loc._M_impl != this; }
    
  private:
    static _Locimp *_C_locale_ptr;
    vector<locale::facet*> facets_vec;

  private:
    static void _STLP_CALL _Locimp_dtor(_Locimp *);
    static void _Locimp_ctor(_Locimp *,const _Locimp&);
    static void _STLP_CALL _Locimp_Addfac(locale::_Locimp* from, locale::facet*, size_t n);

    void _Addfac(locale::facet*, size_t n);

    friend _STLP_DECLSPEC locale::_Locimp * _STLP_CALL _copy_Nameless_Locimp( locale::_Locimp * );
    friend _STLP_DECLSPEC void _STLP_CALL _release_Locimp( locale::_Locimp *& loc );
#if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND) || \
    defined (_STLP_SIGNAL_RUNTIME_COMPATIBILITY) || defined (_STLP_CHECK_RUNTIME_COMPATIBILITY)
    friend class _STLP_NO_MEM_T_NAME(loc);
#else
    friend class locale;
#endif
  };

  // friends:
  friend class _Locimp;

protected:                        // Data members
  _Locimp* _M_impl;
  _Locimp* _M_get_impl() const { return _M_impl; }
};


_STLP_DECLSPEC locale::_Locimp * _STLP_CALL _get_Locimp( locale::_Locimp *locimpl );
_STLP_DECLSPEC locale::_Locimp * _STLP_CALL _copy_Nameless_Locimp( locale::_Locimp *locimpl );

template <class _Facet>
locale::locale(const locale& __loc, _Facet* __f) 
  : _M_impl(__f != 0 ? _copy_Nameless_Locimp(__loc._M_impl) : __loc._M_impl) {
  if ( __f != 0 ) {
    _STLP_PRIV _InsertFacet(*this, __f);
  }
}


//----------------------------------------------------------------------
// locale globals

template <class _Facet>
inline const _Facet&
#ifdef _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS
_Use_facet<_Facet>::operator *() const
#else
use_facet(const locale& __loc)
#endif
{
  _Facet *__facet = 0;
  return *(_STLP_PRIV _UseFacet(__loc, __facet));
}

template <class _Facet>
#ifdef _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS
struct has_facet {
  const locale& __loc;
  has_facet(const locale& __p_loc) : __loc(__p_loc) {}
  operator bool() const _STLP_NOTHROW
#else
inline bool has_facet(const locale& __loc) _STLP_NOTHROW
#endif
{
  _Facet *__facet = 0;
  return _STLP_PRIV _HasFacet(__loc, __facet);
}

#ifdef _STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS
}; // close class definition
#endif

_STLP_MOVE_TO_PRIV_NAMESPACE

/* _GetFacetId is a helper function that allow delaying access to
 * facet id static instance in the library source code to avoid
 * the other static instances that many compilers are generating
 * in all dynamic library or executable when instanciating facet
 * template class.
 */
template <class _Facet>
inline locale::id& _GetFacetId(const _Facet*)
{ return _Facet::id; }

_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_get<char, istreambuf_iterator<char, char_traits<char> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_put<char, ostreambuf_iterator<char, char_traits<char> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_get<char, istreambuf_iterator<char, char_traits<char> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_put<char, ostreambuf_iterator<char, char_traits<char> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_get<char, istreambuf_iterator<char, char_traits<char> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_put<char, ostreambuf_iterator<char, char_traits<char> > >*);

#ifndef _STLP_NO_WCHAR_T
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*);
#endif

template <class _Facet>
inline bool _HasFacet(const locale& __loc, const _Facet* __facet) _STLP_NOTHROW
{ return (__loc._M_get_facet(_GetFacetId(__facet)) != 0); }

template <class _Facet>
inline _Facet* _UseFacet(const locale& __loc, const _Facet* __facet)
{ return __STATIC_CAST(_Facet*, __loc._M_use_facet(_GetFacetId(__facet))); }

template <class _Facet>
inline void _InsertFacet(locale& __loc, _Facet* __facet)
{ __loc._M_insert(__facet, _GetFacetId(__facet)); }

_STLP_MOVE_TO_STD_NAMESPACE

_STLP_END_NAMESPACE

#endif /* _STLP_INTERNAL_LOCALE_H */

// Local Variables:
// mode:C++
// End:

