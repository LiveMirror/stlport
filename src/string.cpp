#include "stlport_prefix.h"

#include <string>
#include <stl/_range_errors.h>

_STLP_BEGIN_NAMESPACE

#if defined (_STLP_MSVC_BINARY_COMPATIBILITY) 

#undef _String_base
void _STLP_CALL _String_base::_Xran(void)
{
  __stl_throw_out_of_range("basic_string"); 
}
void _STLP_CALL _String_base::_Xlen(void)
{
  __stl_throw_length_error("basic_string");
}

#define _String_base _String_val

#endif

#if defined(_STLP_USE_WIDE_INTERFACE)
_STLP_MOVE_TO_PRIV_NAMESPACE

wstring __ASCIIToWide(const char *ascii) {
    size_t size = strlen(ascii);
    wchar_t* buff = new wchar_t[size+1];
    mbstowcs(buff, ascii, size);
    buff[size] = 0x00;
    wstring ret(buff);
    delete[] buff;
    return ret;
}
string __WideToASCII(const wchar_t *wide) {
    size_t size = wcslen(wide);
    char* buff = new char[size+1];
    wcstombs(buff, wide, size);
    buff[size] = 0;
    string ret(buff);
    delete[] buff;
    return ret;
}
_STLP_MOVE_TO_STD_NAMESPACE
#endif

#if !defined (_STLP_NO_FORCE_INSTANTIATE)

template class _STLP_CLASS_DECLSPEC allocator<char>;
template class _STLP_CLASS_DECLSPEC _String_base<char, allocator<char> >;
template class _STLP_CLASS_DECLSPEC basic_string<char, char_traits<char>, allocator<char> >;

// template class _STLP_CLASS_DECLSPEC _STLP_alloc_proxy<char*, char, allocator<char> >;

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const basic_string<char, char_traits<char>, allocator<char> >& __x,
	    const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const char*__x,
	    const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( char __x,
	    const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const basic_string<char, char_traits<char>, allocator<char> >& __y, 
	    char __x);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const basic_string<char, char_traits<char>, allocator<char> >& __x,
	    const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const char*__x,
	    const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const basic_string<char, char_traits<char>, allocator<char> >& __y,
	    const char*__x );

template _STLP_DECLSPEC bool _STLP_CALL
operator<( const basic_string<char, char_traits<char>, allocator<char> >& __x,
	   const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator<( const char*__x,
	   const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator>( const basic_string<char, char_traits<char>, allocator<char> >& __x,
	   const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC basic_string<char, char_traits<char>, allocator<char> >  _STLP_CALL
operator+( const basic_string<char, char_traits<char>, allocator<char> >& __x,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC basic_string<char, char_traits<char>, allocator<char> > _STLP_CALL
operator+(const char* __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC basic_string<char, char_traits<char>, allocator<char> > _STLP_CALL
operator+(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, const char* __s);

template _STLP_DECLSPEC basic_string<char, char_traits<char>, allocator<char> > _STLP_CALL
operator+(char __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC basic_string<char, char_traits<char>, allocator<char> > _STLP_CALL
operator+(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, char __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(const char* __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, const char* __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(char __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, char __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(const char* __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, const char* __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(char __s,
          const basic_string<char, char_traits<char>, allocator<char> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(
          const basic_string<char, char_traits<char>, allocator<char> >& __y, char __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __x,
	    const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const wchar_t*__x,
	    const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y,
	    const wchar_t*__x );

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __x,
	    const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const wchar_t*__x,
	    const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y,
	    const wchar_t*__x );

template _STLP_DECLSPEC bool _STLP_CALL
operator<( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __x,
	   const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator<( const wchar_t*__x,
	   const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator<( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y,
	   const wchar_t*__x );

template _STLP_DECLSPEC bool _STLP_CALL
operator>( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __x,
	   const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator>( const wchar_t*__x,
	   const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator>( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y,
	   const wchar_t*__x );

template _STLP_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > _STLP_CALL
operator+( const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __x,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > _STLP_CALL
operator+(const wchar_t*  __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > _STLP_CALL
operator+(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, const wchar_t*  __s);

template _STLP_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > _STLP_CALL
operator+(wchar_t __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > _STLP_CALL
operator+(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, wchar_t __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(const wchar_t*  __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, const wchar_t*  __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(wchar_t __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator==(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, wchar_t __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(const wchar_t*  __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, const wchar_t*  __s);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(wchar_t __s,
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y);

template _STLP_DECLSPEC bool _STLP_CALL
operator!=(
          const basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >& __y, wchar_t __s);

#  if defined (_STLP_DEBUG) && !defined (__SUNPRO_CC) && !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#    define basic_string _STLP_NON_DBG_NAME(str)

template class _STLP_CLASS_DECLSPEC basic_string<char, char_traits<char>, allocator<char> >;
template class _STLP_CLASS_DECLSPEC __construct_checker<basic_string<char, char_traits<char>, allocator<char> > >;
#    undef basic_string
#  endif

#  if !defined (_STLP_NO_WCHAR_T)
template class _STLP_CLASS_DECLSPEC allocator<wchar_t>;

_STLP_MOVE_TO_PRIV_NAMESPACE

template class _STLP_CLASS_DECLSPEC _String_base<wchar_t, allocator<wchar_t> >;

#    if defined (_STLP_DEBUG) && !defined (__SUNPRO_CC) && !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#      define basic_string _STLP_NON_DBG_NAME(str)

template class _STLP_CLASS_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
template class _STLP_CLASS_DECLSPEC __construct_checker<basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> > >;

#      undef basic_string
#    endif

#    if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#      define basic_string _STLP_NO_MEM_T_NAME(str)
#    else
_STLP_MOVE_TO_STD_NAMESPACE
#    endif

template class _STLP_CLASS_DECLSPEC basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;

#    if defined (basic_string)
_STLP_MOVE_TO_STD_NAMESPACE
#      undef basic_string
#    endif
#  endif
#endif

_STLP_END_NAMESPACE
