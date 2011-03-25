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


#include "stlport_prefix.h"

#include <typeinfo>

#include <stdexcept>
#include <locale>
#include <algorithm>


#include "c_locale.h"
#include "aligned_buffer.h"
#include "acquire_release.h"
#include "locale_impl.h"

_STLP_BEGIN_NAMESPACE

static const string _Nameless("*");

static inline bool is_C_locale_name (const char* name)
{ return ((name[0] == 'C') && (name[1] == 0)); }

locale::facet * _STLP_CALL _get_facet(locale::facet *f)
{
  if (f != 0)
    f->_M_incr();
  return f;
}

void _STLP_CALL _release_facet(locale::facet *&f)
{
  if ((f != 0) && (f->_M_decr() == 0)) {
    delete f;
    f = 0;
  }
}

size_t locale::id::_S_max = 27;

static void _Stl_loc_assign_ids();

static _Stl_aligned_buffer<locale::_Locimp::Init> __Loc_init_buf;

locale::_Locimp::Init::Init() {
  if (_M_count()._M_incr() == 1) {
    locale::_Locimp::_S_initialize();
  }
}

locale::_Locimp::Init::~Init() {
  if (_M_count()._M_decr() == 0) {
    locale::_Locimp::_S_uninitialize();
  }
}

_Refcount_Base& locale::_Locimp::Init::_M_count() const {
  static _Refcount_Base _S_count(0);
  return _S_count;
}

locale::_Locimp::_Locimp(const char* s)
  : locale::facet(0), name(s), facets_vec() {
  facets_vec.reserve( locale::id::_S_max );
  new (&__Loc_init_buf) Init();
}

locale::_Locimp::_Locimp( _Locimp const& locimpl )
  : locale::facet(0), name(locimpl.name), facets_vec() {
  for_each( locimpl.facets_vec.begin(), locimpl.facets_vec.end(), _get_facet);
  facets_vec = locimpl.facets_vec;
  new (&__Loc_init_buf) Init();
}

locale::_Locimp::_Locimp( size_t n, const char* s)
  : locale::facet(0), name(s), facets_vec(n, 0) {
  new (&__Loc_init_buf) Init();
}

locale::_Locimp::~_Locimp() {
  (&__Loc_init_buf)->~Init();
  for_each( facets_vec.begin(), facets_vec.end(), _release_facet);
}

// Initialization of the locale system.  This must be called before
// any locales are constructed.  (Meaning that it must be called when
// the I/O library itself is initialized.)
void _STLP_CALL locale::_Locimp::_S_initialize() {
  _Stl_loc_assign_ids();
  make_classic_locale();
}

// Release of the classic locale ressources. Has to be called after the last
// locale destruction and not only after the classic locale destruction as
// the facets can be shared between different facets.
void _STLP_CALL locale::_Locimp::_S_uninitialize() {
  //Not necessary anymore as classic facets are now 'normal' dynamically allocated
  //facets with a reference counter telling to _release_facet when the facet can be
  //deleted.
  //free_classic_locale();
}

// _Locimp non-inline member functions.
void _STLP_CALL locale::_Locimp::_M_throw_bad_cast() {
  _STLP_THROW(bad_cast());
}

void locale::_Locimp::insert_from(locale::_Locimp *from, size_t n) {
  if (n > 0 && n < from->size()) {
    _Locimp_Addfac(this, from->facets_vec[n], n);
  }
}

void locale::_Locimp::insert(locale::facet *f, locale::id n) {
  _Locimp_Addfac(this, f, n);
}


void locale::_Locimp::_Addfac(locale::facet *f, size_t n) {
  _Locimp_Addfac(this, f, n);
}

void _STLP_CALL locale::_Locimp::_Locimp_Addfac(locale::_Locimp* from, locale::facet* f, size_t n) {

  if (f == 0 || n == 0)
    return;

  if (n >= from->facets_vec.size()) {
    from->facets_vec.resize(n + 1);
  }

  if (f != from->facets_vec[n])
  {
    _release_facet(from->facets_vec[n]);
    from->facets_vec[n] = _get_facet(f);
  }
}

//
// <locale> content which is dependent on the name
//

/* Six functions, one for each category.  Each of them takes a
 * a name, constructs that appropriate category facets by name,
 * and inserts them into the locale. */
_Locale_name_hint* locale::_Locimp::insert_ctype_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_ctype_default(buf);

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    locale::_Locimp* i2 = locale::classic()._M_impl;
    this->insert(i2, std::ctype<char>::id);
    this->insert(i2, std::codecvt<char, char, mbstate_t>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2, std::ctype<wchar_t>::id);
    this->insert(i2, std::codecvt<wchar_t, char, mbstate_t>::id);
#endif
  } else {
    locale::facet*    ct  = 0;
    locale::facet*    cvt = 0;
#ifndef _STLP_NO_WCHAR_T
    locale::facet* wct    = 0;
    locale::facet* wcvt   = 0;
#endif
    int __err_code;
    _Locale_ctype *__lct = _STLP_PRIV __acquire_ctype(name, buf, hint, &__err_code);
    if (!__lct) {
      locale::_M_throw_on_creation_failure(__err_code, name, "ctype");
      return hint;
    }

    if (hint == 0) hint = _Locale_get_ctype_hint(__lct);

    _STLP_TRY {
      ct   = new ctype_byname<char>(__lct);
    }
    _STLP_UNWIND(_STLP_PRIV __release_ctype(__lct));

    _STLP_TRY {
      cvt  = new codecvt_byname<char, char, mbstate_t>(name);
    }
    _STLP_UNWIND(delete ct);

#ifndef _STLP_NO_WCHAR_T
    _STLP_TRY {
      _Locale_ctype *__lwct = _STLP_PRIV __acquire_ctype(name, buf, hint, &__err_code);
      if (!__lwct) {
        locale::_M_throw_on_creation_failure(__err_code, name, "ctype");
        return hint;
      }

      _STLP_TRY {
        wct  = new ctype_byname<wchar_t>(__lwct);
      }
      _STLP_UNWIND(_STLP_PRIV __release_ctype(__lwct));
      
      _Locale_codecvt *__lwcvt = _STLP_PRIV __acquire_codecvt(name, buf, hint, &__err_code);
      if (__lwcvt) {
        _STLP_TRY {
          wcvt = new codecvt_byname<wchar_t, char, mbstate_t>(__lwcvt);
        }
        _STLP_UNWIND(_STLP_PRIV __release_codecvt(__lwcvt); delete wct);
      }
    }
    _STLP_UNWIND(delete cvt; delete ct);
#endif

    this->insert(ct, std::ctype<char>::id);
    this->insert(cvt, std::codecvt<char, char, mbstate_t>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(wct, std::ctype<wchar_t>::id);
    if (wcvt) this->insert(wcvt, std::codecvt<wchar_t, char, mbstate_t>::id);
#endif
  }
  return hint;
}

_Locale_name_hint* locale::_Locimp::insert_numeric_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_numeric_default(buf);

  locale::_Locimp* i2 = locale::classic()._M_impl;

  // We first insert name independant facets taken from the classic locale instance:
  this->insert(i2,
               num_put<char, ostreambuf_iterator<char, char_traits<char> >  >::id);
  this->insert(i2,
               num_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
#ifndef _STLP_NO_WCHAR_T
  this->insert(i2,
               num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> >  >::id);
  this->insert(i2,
               num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
#endif

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    this->insert(i2, numpunct<char>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2, numpunct<wchar_t>::id);
#endif
  }
  else {
    locale::facet* punct  = 0;
#ifndef _STLP_NO_WCHAR_T
    locale::facet* wpunct = 0;
#endif

    int __err_code;
    _Locale_numeric *__lpunct = _STLP_PRIV __acquire_numeric(name, buf, hint, &__err_code);
    if (!__lpunct) {
      locale::_M_throw_on_creation_failure(__err_code, name, "numpunct");
      return hint;
    }

    if (hint == 0) hint = _Locale_get_numeric_hint(__lpunct);
    _STLP_TRY {
      punct = new numpunct_byname<char>(__lpunct);
    }
    _STLP_UNWIND(_STLP_PRIV __release_numeric(__lpunct));

#ifndef _STLP_NO_WCHAR_T
    _Locale_numeric *__lwpunct = _STLP_PRIV __acquire_numeric(name, buf, hint, &__err_code);
    if (!__lwpunct) {
      delete punct;
      locale::_M_throw_on_creation_failure(__err_code, name, "numpunct");
      return hint;
    }
    if (__lwpunct) {
      _STLP_TRY {
        wpunct  = new numpunct_byname<wchar_t>(__lwpunct);
      }
      _STLP_UNWIND(_STLP_PRIV __release_numeric(__lwpunct); delete punct);
    }
#endif

    this->insert(punct, numpunct<char>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(wpunct, numpunct<wchar_t>::id);
#endif
  }
  return hint;
}

_Locale_name_hint* locale::_Locimp::insert_time_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_time_default(buf);

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    locale::_Locimp* i2 = locale::classic()._M_impl;
    this->insert(i2,
                 time_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
    this->insert(i2,
                 time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2,
                 time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
    this->insert(i2,
                 time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
#endif
  } else {
    locale::facet *get = 0;
    locale::facet *put = 0;
#ifndef _STLP_NO_WCHAR_T
    locale::facet *wget = 0;
    locale::facet *wput = 0;
#endif

    int __err_code;
    _Locale_time *__time = _STLP_PRIV __acquire_time(name, buf, hint, &__err_code);
    if (!__time) {
      // time facets category is not mandatory for correct stream behavior so if platform
      // do not support it we do not generate a runtime_error exception.
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        _STLP_THROW_BAD_ALLOC;
      }
      return hint;
    }

    if (!hint) hint = _Locale_get_time_hint(__time);
    _STLP_TRY {
      get = new time_get_byname<char, istreambuf_iterator<char, char_traits<char> > >(__time);
      put = new time_put_byname<char, ostreambuf_iterator<char, char_traits<char> > >(__time);
#ifndef _STLP_NO_WCHAR_T
      wget = new time_get_byname<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(__time);
      wput = new time_put_byname<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(__time);
#endif
    }
#ifndef _STLP_NO_WCHAR_T
    _STLP_UNWIND(delete wget; delete put; delete get; _STLP_PRIV __release_time(__time));
#else
    _STLP_UNWIND(delete get; _STLP_PRIV __release_time(__time));
#endif

    _STLP_PRIV __release_time(__time);

    this->insert(get, time_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
    this->insert(put, time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(wget, time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
    this->insert(wput, time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
#endif
  }
  return hint;
}

_Locale_name_hint* locale::_Locimp::insert_collate_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_collate_default(buf);

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    locale::_Locimp* i2 = locale::classic()._M_impl;
    this->insert(i2, std::collate<char>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2, std::collate<wchar_t>::id);
#endif
  }
  else {
    locale::facet *col = 0;
#ifndef _STLP_NO_WCHAR_T
    locale::facet *wcol = 0;
#endif

    int __err_code;
    _Locale_collate *__coll = _STLP_PRIV __acquire_collate(name, buf, hint, &__err_code);
    if (!__coll) {
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        _STLP_THROW_BAD_ALLOC;
      }
      return hint;
    }

    if (hint == 0) hint = _Locale_get_collate_hint(__coll);
    _STLP_TRY {
      col = new collate_byname<char>(__coll);
    }
    _STLP_UNWIND(_STLP_PRIV __release_collate(__coll));

#ifndef _STLP_NO_WCHAR_T
    _Locale_collate *__wcoll = _STLP_PRIV __acquire_collate(name, buf, hint, &__err_code);
    if (!__wcoll) {
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        delete col;
        _STLP_THROW_BAD_ALLOC;
      }
    }
    if (__wcoll) {
      _STLP_TRY {
        wcol  = new collate_byname<wchar_t>(__wcoll);
      }
      _STLP_UNWIND(_STLP_PRIV __release_collate(__wcoll); delete col);
    }
#endif

    this->insert(col, std::collate<char>::id);
#ifndef _STLP_NO_WCHAR_T
    if (wcol) this->insert(wcol, std::collate<wchar_t>::id);
#endif
  }
  return hint;
}

_Locale_name_hint* locale::_Locimp::insert_monetary_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_monetary_default(buf);

  locale::_Locimp* i2 = locale::classic()._M_impl;

  // We first insert name independant facets taken from the classic locale instance:
  this->insert(i2, money_get<char, istreambuf_iterator<char, char_traits<char> > >::id);
  this->insert(i2, money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id);
#ifndef _STLP_NO_WCHAR_T
  this->insert(i2, money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
  this->insert(i2, money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id);
#endif

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    this->insert(i2, moneypunct<char, false>::id);
    this->insert(i2, moneypunct<char, true>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2, moneypunct<wchar_t, false>::id);
    this->insert(i2, moneypunct<wchar_t, true>::id);
#endif
  }
  else {
    locale::facet *punct   = 0;
    locale::facet *ipunct  = 0;

#ifndef _STLP_NO_WCHAR_T
    locale::facet* wpunct  = 0;
    locale::facet* wipunct = 0;
#endif

    int __err_code;
    _Locale_monetary *__mon = _STLP_PRIV __acquire_monetary(name, buf, hint, &__err_code);
    if (!__mon) {
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        _STLP_THROW_BAD_ALLOC;
      }
      return hint;
    }

    if (hint == 0) hint = _Locale_get_monetary_hint(__mon);

    _STLP_TRY {
      punct   = new moneypunct_byname<char, false>(__mon);
    }
    _STLP_UNWIND(_STLP_PRIV __release_monetary(__mon));

    _Locale_monetary *__imon = _STLP_PRIV __acquire_monetary(name, buf, hint, &__err_code);
    if (!__imon) {
      delete punct;
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        _STLP_THROW_BAD_ALLOC;
      }
      return hint;
    }

    _STLP_TRY {
      ipunct  = new moneypunct_byname<char, true>(__imon);
    }
    _STLP_UNWIND(_STLP_PRIV __release_monetary(__imon); delete punct);

#ifndef _STLP_NO_WCHAR_T
    _STLP_TRY {
      _Locale_monetary *__wmon = _STLP_PRIV __acquire_monetary(name, buf, hint, &__err_code);
      if (!__wmon) {
        if (__err_code == _STLP_LOC_NO_MEMORY) {
          _STLP_THROW_BAD_ALLOC;
        }
      }

      if (__wmon) {
        _STLP_TRY {
          wpunct  = new moneypunct_byname<wchar_t, false>(__wmon);
        }
        _STLP_UNWIND(_STLP_PRIV __release_monetary(__wmon));
      
        _Locale_monetary *__wimon = _STLP_PRIV __acquire_monetary(name, buf, hint, &__err_code);
        if (!__wimon) {
          delete wpunct;
          if (__err_code == _STLP_LOC_NO_MEMORY) {
            _STLP_THROW_BAD_ALLOC;
          }
          wpunct = 0;
        }
        else {
          _STLP_TRY {
            wipunct = new moneypunct_byname<wchar_t, true>(__wimon);
          }
          _STLP_UNWIND(_STLP_PRIV __release_monetary(__wimon); delete wpunct);
        }
      }
    }
    _STLP_UNWIND(delete ipunct; delete punct);
#endif

    this->insert(punct, moneypunct<char, false>::id);
    this->insert(ipunct, moneypunct<char, true>::id);
#ifndef _STLP_NO_WCHAR_T
    if (wpunct) this->insert(wpunct, moneypunct<wchar_t, false>::id);
    if (wipunct) this->insert(wipunct, moneypunct<wchar_t, true>::id);
#endif
  }
  return hint;
}

_Locale_name_hint* locale::_Locimp::insert_messages_facets(const char* &name, char *buf, _Locale_name_hint* hint) {
  if (name[0] == 0)
    name = _Locale_messages_default(buf);

  if (name == 0 || name[0] == 0 || is_C_locale_name(name)) {
    locale::_Locimp* i2 = locale::classic()._M_impl;
    this->insert(i2, std::messages<char>::id);
#ifndef _STLP_NO_WCHAR_T
    this->insert(i2, std::messages<wchar_t>::id);
#endif
  }
  else {
    locale::facet *msg  = 0;
#ifndef _STLP_NO_WCHAR_T
    locale::facet *wmsg = 0;
#endif

    int __err_code;
    _Locale_messages *__msg = _STLP_PRIV __acquire_messages(name, buf, hint, &__err_code);
    if (!__msg) {
      if (__err_code == _STLP_LOC_NO_MEMORY) {
        _STLP_THROW_BAD_ALLOC;
      }
      return hint;
    }

    _STLP_TRY {
      msg  = new messages_byname<char>(__msg);
    }
    _STLP_UNWIND(_STLP_PRIV __release_messages(__msg));

#ifndef _STLP_NO_WCHAR_T
    _STLP_TRY {
      _Locale_messages *__wmsg = _STLP_PRIV __acquire_messages(name, buf, hint, &__err_code);
      if (!__wmsg) {
        if (__err_code == _STLP_LOC_NO_MEMORY) {
          _STLP_THROW_BAD_ALLOC;
        }
      }

      if (__wmsg) {
        _STLP_TRY {
          wmsg = new messages_byname<wchar_t>(__wmsg);
        }
        _STLP_UNWIND(_STLP_PRIV __release_messages(__wmsg));
      }
    }
    _STLP_UNWIND(delete msg);
#endif

    this->insert(msg, std::messages<char>::id);
#ifndef _STLP_NO_WCHAR_T
    if (wmsg) this->insert(wmsg, std::messages<wchar_t>::id);
#endif
  }
  return hint;
}

static void _Stl_loc_assign_ids() {
  // This assigns ids to every facet that is a member of a category,
  // and also to money_get/put, num_get/put, and time_get/put
  // instantiated using ordinary pointers as the input/output
  // iterators.  (The default is [io]streambuf_iterator.)

  money_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index          = 8;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index          = 9;
  num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index            = 10;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index            = 11;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index           = 12;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index           = 13;

#ifndef _STLP_NO_WCHAR_T
  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index = 21;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index = 22;
  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index   = 23;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > ::id._M_index  = 24;
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index  = 25;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index  = 26;
#endif
  //  locale::id::_S_max                               = 27;
}

// To access those static instance use the getter below, they guaranty
// a correct initialization.
static locale *_Stl_classic_locale = 0;
static locale *_Stl_global_locale = 0;
locale::_Locimp* locale::_Locimp::_C_locale_ptr = 0;

locale* _Stl_get_classic_locale() {
  static locale::_Locimp::Init init;
  return _Stl_classic_locale;
}

locale* _Stl_get_global_locale() {
  static locale::_Locimp::Init init;
  return _Stl_global_locale;
}

#if defined (_STLP_MSVC) || defined (__ICL) || defined (__ISCPP__) || defined (__DMC__)
/*
 * The following static variable needs to be initialized before STLport
 * users static variable in order for him to be able to use Standard
 * streams in its variable initialization.
 * This variable is here because MSVC do not allow to change the initialization
 * segment in a given translation unit, iostream.cpp already contains an
 * initialization segment specification.
 */
#  pragma warning (disable : 4073)
#  pragma init_seg(lib)
#endif

static ios_base::Init _IosInit;
// The classic locale contains every facet that belongs to a category.
static _Stl_aligned_buffer<locale::_Locimp> _Locale_classic_impl_buf;

void locale::_Locimp::make_classic_locale() {
  // This funcion will be called once: during build classic locale::_Locimp

  locale::_Locimp *classic = new(&_Locale_classic_impl_buf) locale::_Locimp("C");

  _C_locale_ptr = classic;

  locale::facet* classic_facets[] = {
    0,
    new std::collate<char>(1),
    new std::ctype<char>(0, false, 1),
    new std::codecvt<char, char, mbstate_t>(1),
    new std::moneypunct<char, true>(1),
    new std::moneypunct<char, false>(1),
    new std::numpunct<char>(1),
    new std::messages<char>(1),
    new std::money_get<char, istreambuf_iterator<char, char_traits<char> > >(1),
    new std::money_put<char, ostreambuf_iterator<char, char_traits<char> > >(1),
    new std::num_get<char, istreambuf_iterator<char, char_traits<char> > >(1),
    new std::num_put<char, ostreambuf_iterator<char, char_traits<char> > >(1),
    new std::time_get<char, istreambuf_iterator<char, char_traits<char> > >(1),
    new std::time_put<char, ostreambuf_iterator<char, char_traits<char> > >(1),
#ifndef _STLP_NO_WCHAR_T
    new std::collate<wchar_t>(1),
    new std::ctype<wchar_t>(1),
    new std::codecvt<wchar_t, char, mbstate_t>(1),
    new std::moneypunct<wchar_t, true>(1),
    new std::moneypunct<wchar_t, false>(1),
    new std::numpunct<wchar_t>(1),
    new std::messages<wchar_t>(1),
    new std::money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
    new std::money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
    new std::num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
    new std::num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
    new std::time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
    new std::time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >(1),
#endif
    0
  };

  const size_t nb_classic_facets = sizeof(classic_facets) / sizeof(locale::facet *);
  classic->facets_vec.reserve(nb_classic_facets);
  classic->facets_vec.assign(&classic_facets[0], &classic_facets[0] + nb_classic_facets);

  static locale _Locale_classic(classic);
  _Stl_classic_locale = &_Locale_classic;

  static locale _Locale_global(classic);
  _Stl_global_locale = &_Locale_global;
}

// Declarations of (non-template) facets' static data members
// size_t locale::id::_S_max = 27; // made before

locale::id collate<char>::id = locale::id(1);
locale::id ctype<char>::id = locale::id(2);
locale::id codecvt<char, char, mbstate_t>::id = locale::id(3);
locale::id moneypunct<char, true>::id = locale::id(4);
locale::id moneypunct<char, false>::id = locale::id(5);
locale::id numpunct<char>::id = locale::id(6);
locale::id messages<char>::id = locale::id(7);

#ifndef _STLP_NO_WCHAR_T
locale::id collate<wchar_t>::id = locale::id( 14 );
locale::id ctype<wchar_t>::id = locale::id( 15 );
locale::id codecvt<wchar_t, char, mbstate_t>::id = locale::id( 16 );
locale::id moneypunct<wchar_t, true>::id = locale::id( 17 ) ;
locale::id moneypunct<wchar_t, false>::id = locale::id( 18 ) ;
locale::id numpunct<wchar_t>::id = locale::id( 19 );
locale::id messages<wchar_t>::id = locale::id( 20 );
#endif

_STLP_DECLSPEC locale::_Locimp* _STLP_CALL _get_Locimp(locale::_Locimp *loc)
{
  _STLP_ASSERT( loc != 0 );
  loc->_M_incr();
  return loc;
}

void _STLP_CALL _release_Locimp(locale::_Locimp *& loc)
{
  _STLP_ASSERT( loc != 0 );
  if (loc->_M_decr() == 0) {
    if (*loc != *_Stl_classic_locale)
      delete loc;
    else
      loc->~_Locimp();
    loc = 0;
  }
}

_STLP_DECLSPEC locale::_Locimp* _STLP_CALL _copy_Nameless_Locimp(locale::_Locimp *loc)
{
  _STLP_ASSERT( loc != 0 );
  locale::_Locimp *loc_new = new locale::_Locimp(*loc);
  loc_new->name = _Nameless;
  return loc_new;
}

/* _GetFacetId implementation have to be here in order to be in the same translation unit
 * as where id are initialize (in _Stl_loc_assign_ids) */
_STLP_MOVE_TO_PRIV_NAMESPACE

_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_get<char, istreambuf_iterator<char, char_traits<char> > >*)
{ return money_get<char, istreambuf_iterator<char, char_traits<char> > >::id; }
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_put<char, ostreambuf_iterator<char, char_traits<char> > >*)
{ return money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id; }
#ifndef _STLP_NO_WCHAR_T
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
#endif

_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_get<char, istreambuf_iterator<char, char_traits<char> > >*)
{ return num_get<char, istreambuf_iterator<char, char_traits<char> > >::id; }
#ifndef _STLP_NO_WCHAR_T
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
#endif

_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_put<char, ostreambuf_iterator<char, char_traits<char> > >*)
{ return num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id; }
#ifndef _STLP_NO_WCHAR_T
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
#endif

_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_get<char, istreambuf_iterator<char, char_traits<char> > >*)
{ return time_get<char, istreambuf_iterator<char, char_traits<char> > >::id; }
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_put<char, ostreambuf_iterator<char, char_traits<char> > >*)
{ return time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id; }
#ifndef _STLP_NO_WCHAR_T
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
_STLP_DECLSPEC locale::id& _STLP_CALL _GetFacetId(const time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >*)
{ return time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id; }
#endif

_STLP_MOVE_TO_STD_NAMESPACE

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 

///\todo : figure what the last parameter does
void locale::_Locimp::_Addfac(locale::facet *f, size_t n, size_t) {
  _Locimp_Addfac(this, f, n);
}

locale::_Locimp*  _STLP_CALL  locale::_Locimp::_Makeloc(const _Locinfo&, category, _Locimp* __l, const locale*)
{
  return __l;
}

void  _STLP_CALL locale::_Locimp::_Makewloc(const _Locinfo&, category, _Locimp *, const locale*)
{
}

locale::_Locimp*&  _STLP_CALL locale::_Locimp::_Clocptr_func()
{
  return _C_locale_ptr;
}

#ifndef _STLP_NO_WCHAR_T
void _STLP_CALL locale::_Locimp::_Makeushloc(const _Locinfo&, category, _Locimp *, const locale *)
{}
#endif /* _NATIVE_WCHAR_T_DEFINED */

void locale::_Locimp::_Makexloc(const _Locinfo&, category, _Locimp *, const locale *)
{
}

locale::_Locimp::_Locimp(bool)
{
}

locale::_Locimp * locale::_Getgloballocale()
{
  return _Stl_global_locale->_M_get_impl();
}

locale::_Locimp * locale::_Init()
{
  locale::_Locimp::_S_initialize();
  // lucky guess
  return _Getgloballocale();
}

void __cdecl locale::_Setgloballocale(void * g)
{
  _Stl_global_locale = (locale*)g;
}

void locale::facet::facet_Register(facet *)
{

}

size_t _STLP_CALL locale::facet::_Getcat(const facet **,
					 const locale *)
{
  return ((size_t)(-1));
}

_Lockit::_Lockit(): _Locktype(0)
{
  _Lockit_ctor(this);
}

_Lockit::_Lockit(int __par)
{
  _Lockit_ctor(this, __par);
}

_Lockit::~_Lockit()
{
  _Lockit_dtor(this);
}
  
void _STLP_CALL _Lockit::_Lockit_ctor(int)
{
  // TODO
}

void _STLP_CALL _Lockit::_Lockit_dtor(int)
{
  // TODO
}

void _STLP_CALL _Lockit::_Lockit_ctor(_Lockit* __that)
{
  _STLP_mutex_spin<0>::_M_do_lock((__stl_atomic_t*)&__that->_Locktype);
}

void _STLP_CALL _Lockit::_Lockit_ctor(_Lockit* __that, int __val)
{
  __that->_Locktype = __val;
}

void _STLP_CALL _Lockit::_Lockit_dtor(_Lockit* that)
{
  // asm(" stbar ");
    that->_Locktype = 0;
}


#endif

_STLP_END_NAMESPACE


#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
#include <xlocinfo>
namespace 
{
  std::_Locinfo dummy;
}
#endif
