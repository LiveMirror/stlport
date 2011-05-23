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

#include <algorithm>
#include <ios>
#include <locale>
#include <ostream> // for __get_ostreambuf definition
#include <iomanip>

#include "aligned_buffer.h"

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// ios_base members

// class ios_base::failure, a subclass of exception.  It's used solely
// for reporting errors.

ios_base::failure::failure(const string& s)
  : runtime_error(s)
{}

ios_base::failure::~failure() _STLP_NOTHROW_INHERENTLY {}

#if !defined (_STLP_STATIC_CONST_INIT_BUG) && !defined (_STLP_NO_STATIC_CONST_DEFINITION)
// Definitions of ios_base's formatting flags.
const ios_base::fmtflags ios_base::left;
const ios_base::fmtflags ios_base::right;
const ios_base::fmtflags ios_base::internal;
const ios_base::fmtflags ios_base::dec;
const ios_base::fmtflags ios_base::hex;
const ios_base::fmtflags ios_base::oct;
const ios_base::fmtflags ios_base::fixed;
const ios_base::fmtflags ios_base::scientific;
const ios_base::fmtflags ios_base::boolalpha;
const ios_base::fmtflags ios_base::showbase;
const ios_base::fmtflags ios_base::showpoint;
const ios_base::fmtflags ios_base::showpos;
const ios_base::fmtflags ios_base::skipws;
const ios_base::fmtflags ios_base::unitbuf;
const ios_base::fmtflags ios_base::uppercase;
const ios_base::fmtflags ios_base::adjustfield;
const ios_base::fmtflags ios_base::basefield;
const ios_base::fmtflags ios_base::floatfield;

// Definitions of ios_base's state flags.
const ios_base::iostate ios_base::goodbit;
const ios_base::iostate ios_base::badbit;
const ios_base::iostate ios_base::eofbit;
const ios_base::iostate ios_base::failbit;

// Definitions of ios_base's openmode flags.
const ios_base::openmode ios_base::app;
const ios_base::openmode ios_base::ate;
const ios_base::openmode ios_base::binary;
const ios_base::openmode ios_base::in;
const ios_base::openmode ios_base::out;
const ios_base::openmode ios_base::trunc;

// Definitions of ios_base's seekdir flags.
const ios_base::seekdir ios_base::beg;
const ios_base::seekdir ios_base::cur;
const ios_base::seekdir ios_base::end;

#endif

locale ios_base::imbue(const locale& loc) {
  if (loc != *_M_locale) {
    locale previous = *_M_locale;
    *_M_locale = loc;
    _M_invoke_callbacks(imbue_event);
    return previous;
  }
  else {
    _M_invoke_callbacks(imbue_event);
    return *_M_locale;
  }
}

int _STLP_CALL ios_base::xalloc() {
#if defined (_STLP_THREADS) && \
    defined (_STLP_WIN32THREADS) && defined (_STLP_NEW_PLATFORM_SDK)
  static volatile __stl_atomic_t _S_index = 0;
  return _STLP_ATOMIC_INCREMENT(&_S_index);
#else
  static int _S_index = 0;
  static _STLP_STATIC_MUTEX __lock _STLP_MUTEX_INITIALIZER;
  _STLP_auto_lock sentry(__lock);
  return _S_index++;
#endif
}

long& ios_base::iword(int index) {
  static void* dummy = 0;
  _AuxStorageNode& ref = _Findarr(index);
  return ref._M_long;
}


void*& ios_base::pword(int index) {
  static void* dummy = 0;
  _AuxStorageNode& ref = _Findarr(index);
  return ref._M_ptr;
}

void ios_base::register_callback(event_callback __fn, int __idx) {
  _M_callbacks = new _CallbackNode(__idx, __fn, _M_callbacks);
}

// Invokes all currently registered callbacks for a particular event.
// Behaves correctly even if one of the callbacks adds a new callback.
void ios_base::_M_invoke_callbacks(event E) {
    for (_CallbackNode *p = _M_callbacks; p != 0; p = p->_M_next)
      (p->_M_cb)(E, *this, p->_M_index);
}

// This function is called if the state, rdstate(), has a bit set
// that is also set in the exception mask exceptions().
void ios_base::_M_throw_failure() {
  const char* arg ;
# if 0
  char buffer[256];
  char* ptr;
  strcpy(buffer, "ios failure: rdstate = 0x");
  ptr = __write_integer(buffer+strlen(buffer), ios_base::hex, __STATIC_CAST(unsigned long,_M_iostate));
  strcpy(ptr, " mask = 0x");
  ptr = __write_integer(buffer+strlen(buffer), ios_base::hex, __STATIC_CAST(unsigned long,_M_exception_mask));
  *ptr = 0;
  arg = buffer;
# else
  arg = "ios failure";
# endif

# ifndef _STLP_USE_EXCEPTIONS
  fputs(arg, stderr);
# else
  throw failure(arg);
# endif
}

// Copy x's state to *this.  This member function is used in the
// implementation of basic_ios::copyfmt.  Does not copy _M_exception_mask
// or _M_iostate.
void ios_base::_M_copy_state(const ios_base& x) {
  _M_fmtflags  = x._M_fmtflags; // Copy the flags, except for _M_iostate
  _M_precision = x._M_precision;
  _M_width     = x._M_width;
  *_M_locale    = *x._M_locale;

  if (x._M_callbacks) {
    for (_CallbackNode *cur = x._M_callbacks; cur; cur = cur->_M_next) {
      register_callback(cur->_M_cb, cur->_M_index);
    }
  }
  else {
    _M_setstate_nothrow(badbit);
    _M_check_exception_mask();
  }
  
  if (x._M_ipwords) {
    for (_AuxStorageNode *cur = x._M_ipwords; cur; cur = cur->_M_next) {
      if (cur->_M_long || cur->_M_ptr) {
	_AuxStorageNode& mynode = _Findarr(cur->_M_index);
	mynode._M_long = cur->_M_long;
	mynode._M_ptr = cur->_M_ptr;
      }
    }    
  }
  else {
    _M_setstate_nothrow(badbit);
    _M_check_exception_mask();
  }

}

// ios's (protected) default constructor.  The standard says that all
// fields have indeterminate values; we initialize them to zero for
// simplicity.  The only thing that really matters is that the arrays
// are all initially null pointers, and the array element counts are all
// initially zero.
ios_base::ios_base()
  : _M_std_stream(0), _M_fmtflags(0), _M_iostate(0), 
    _M_exception_mask(0),
    _M_precision(0), _M_width(0),
    _M_callbacks(0),
    _M_ipwords(0),
    _M_locale(new locale())
{}

// ios's destructor.
ios_base::~ios_base() {
  _Tidy();
}

void _STLP_CALL 
ios_base::_Addstd(ios_base * s)
{
  static int curr_stream= 0;
  s->_M_std_stream = ++curr_stream;
}

ios_base::_AuxStorageNode& 
ios_base::_Findarr(int idx)
{
   _AuxStorageNode *ret = 0;
   
   for (_AuxStorageNode *cur = _M_ipwords; cur; cur = cur->_M_next)
     if (cur->_M_index == idx)
       return (*cur);
     else if (cur->_M_long == 0 && cur->_M_ptr == 0)
       ret = cur;
   
   if (ret)  {
     ret->_M_index = idx;
   }
   else
     ret = _M_ipwords = new _AuxStorageNode(idx, _M_ipwords);
   return *ret;
}

void ios_base::_Tidy()
{
  _M_invoke_callbacks(ios_base::erase_event);

  for (_CallbackNode *cur = _M_callbacks; cur; ) {
    _CallbackNode * next = cur->_M_next;
    delete cur;
    cur = next;
  }

  for (_AuxStorageNode *cur = _M_ipwords; cur; ) {
    _AuxStorageNode *next = cur->_M_next;
    delete cur;
    cur = next;
  }

}

_STLP_DECLSPEC int _STLP_CALL _Ios_setbase(ios_base& __ios, int __n)
{  
  ios_base::fmtflags __base = __n == 8  ? ios_base::oct :
    __n == 10 ? ios_base::dec :
    __n == 16 ? ios_base::hex :
    ios_base::fmtflags(0);
  __ios.unsetf(ios_base::basefield);
  return  __ios.setf(__base );
}

_STLP_DECLSPEC int _STLP_CALL _Ios_setflags(ios_base& __ios, ios_base::fmtflags __f)
{
  return __ios.setf(__f);
}

_STLP_DECLSPEC int _STLP_CALL _Ios_unsetflags(ios_base& __ios, ios_base::fmtflags __f)
{
  __ios.unsetf(__f);
  return __f;
}

_STLP_DECLSPEC int _STLP_CALL _Ios_precision(ios_base& __ios, int __prec)
{
  return __ios.precision(__prec);
}

_STLP_DECLSPEC int _STLP_CALL _Ios_width(ios_base& __ios, int __w)
{
  return __ios.width(__w);
}

_Ios_Setf_Manip _STLP_CALL resetiosflags(ios_base::fmtflags __mask)
{ 
  _Smanip<streamsize>::__f_ptr_type __f = &_Ios_unsetflags;
  return  _Ios_Setf_Manip(__f, __mask); 
}
_Ios_Setf_Manip _STLP_CALL setiosflags(ios_base::fmtflags __mask)
{ 
  _Smanip<streamsize>::__f_ptr_type __f = &_Ios_setflags;
  return  _Ios_Setf_Manip(__f, __mask); 
}

_STLP_DECLSPEC _Smanip<streamsize> _STLP_CALL
setprecision(int __n) {
   _Smanip<streamsize>::__f_ptr_type __f = _Ios_precision;
  return  _Smanip<streamsize>(__f, __n);
}

_STLP_DECLSPEC _Smanip<streamsize>  _STLP_CALL
setw(int __n) {
   _Smanip<streamsize>::__f_ptr_type __f = _Ios_width;  
  return  _Smanip<streamsize>(__f, __n);
}

//----------------------------------------------------------------------
// Force instantiation of basic_ios
// For DLL exports, they are already instantiated.
#if !defined(_STLP_NO_FORCE_INSTANTIATE)
template class _STLP_CLASS_DECLSPEC basic_ios<char, char_traits<char> >;
#  if !defined (_STLP_NO_WCHAR_T)
template class _STLP_CLASS_DECLSPEC basic_ios<wchar_t, char_traits<wchar_t> >;
#  endif /* _STLP_NO_WCHAR_T */
#endif

_STLP_END_NAMESPACE

// Local Variables:
// mode:C++
// End:
