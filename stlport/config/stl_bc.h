// STLport configuration file
// It is internal STLport header - DO NOT include it directly

/* ==========================================================================*/
/* General */
#ifdef __BUILDING_STLPORT
# pragma message "_STLPORT_VERSION" = _STLPORT_VERSION  "__BORLANDC__" = __BORLANDC__
#endif

# ifdef __BUILDING_STLPORT
#  define _STLP_CALL __cdecl __export
# else
#  if __BORLANDC__ < 0x540
#  define  _STLP_CALL __cdecl __import
#else
#  define  _STLP_CALL __cdecl
#endif
# endif

#define _STLP_USE_OWN_MBSTATE_T
# define _STLP_VENDOR_UNEXPECTED_STD 1
# define _STLP_STATIC_CONST_INIT_BUG 1
# define _STLP_HAS_SPECIFIC_PROLOG_EPILOG 1

# ifdef __BUILDING_STLPORT
#  define _BC5_EXCLUDE_STLP_LIBS 1
# endif

// used for locale subsystem
# ifndef _BC5_STARTUP_LEVEL
#  define _BC5_STARTUP_LEVEL 1
static volatile int startup_level = 0;
   void startup_level_32() {
#  pragma startup startup_level_32 32
    startup_level = 32;
   }
   void startup_level_33() {
#  pragma startup startup_level_33 33
    startup_level = 33;
   }
# endif

# define _STLP_NO_VENDOR_STDLIB_L 1

// math, complex, limits
# define __MINMAX_DEFINED 1
# define _STLP_NO_LONG_DOUBLE 1 // crash on startup in complex_trig.cpp
# define _STLP_NO_IEC559_SUPPORT 1 // debugging limits_test, hash_test, qnan problem
# define _STLP_NO_VENDOR_MATH_F 1 // compile error in _cmath.h

// threads
# define NOWINBASEINTERLOCK  // winbase.h error
# if ! defined(__MT__) && ! defined(__BUILDING_STLPORT)
#  error - STLport single thread not supported!
# endif

// headers
# define _STLP_NO_NEW_NEW_HEADER 1

/* ==========================================================================*/
// Borland options
// These options have been tested.  
// Other options may work, but may not have been been tested.

#if __BORLANDC__ >= 0x550
// 80486 protected mode compatible (on)
#pragma checkoption -4
// use Borland keywords and extensions (on)
#pragma checkoption -AT
// 8 byte data alignment (on)
#pragma checkoption -a8
// enums always integer size (on)
#pragma checkoption -b
// enable nested comments (off)
#pragma checkoption -C-
// enable fast floating point (on)
#pragma checkoption -ff
// generate and use precompiled headers (off)
#pragma checkoption -H-
// enable precompiled headers with external file types (off)
#pragma checkoption -He-
// enable smart cached precompiled headers (off)
#pragma checkoption -Hs-
// generate definitions for all template instances and merge duplicates (on)
#pragma checkoption -Jgd
// set default character type to unsigned (on)
//#pragma checkoption -K
#ifndef __cplusplus
// perform C++ compile regardless of source extension (on)
# pragma checkoption -P
#endif
// use C calling convention (on)
#pragma checkoption -pc
// enable runtime type information (on)
#pragma checkoption -RT
// enable register variables (off)
#pragma checkoption -r-
// generate underscores on symbol names (on)
#pragma checkoption -u
// use smart c++ virtual tables (on)
#pragma checkoption -V
// do not mangle calling convention in symbol names (off)
#pragma checkoption -VC-
// use old c++ for-statement scoping rules (off)
#pragma checkoption -Vd-
// zero length empty base class (off)
#pragma checkoption -Ve-
// place no restrictions on where member pointers can point (on)
#pragma checkoption -Vmv
// zero length empty class member functions (off)
#pragma checkoption -Vx-
// compiler autodependency output (off)
#pragma checkoption -X-
// enable exception handling (on)
#pragma checkoption -x
// enable destructor cleanup (on)
#pragma checkoption -xd
// enable exception location information (on)
#pragma checkoption -xp
// enable fast exception prologs (off)
#pragma checkoption -xf-

# ifdef __BUILDING_STLPORT_LIBS
#  if defined (_RTLDLL)
#   ifndef _DEBUG
// project is a dynamic link library (on)
#    pragma checkoption -tWD
#   endif
#else
// project is a console application (on)
#   pragma checkoption -tWC
#  endif
#endif

#if defined (_MT)
// 32-bit multithreaded project (on)
# pragma checkoption -tWM
#else
// 32-bit multithreaded project (off)
# pragma checkoption -tWM-
#endif

# if defined (__MT__) && ! defined (_MT)
#  define _MT
# elif defined (_MT) && ! defined (__MT__)
#  define __MT__
# elif ! defined (_MT) && ! defined (__MT__)
#  error - singlethead not supported, please enable multithread (-tWM)
# endif

#if defined (_DEBUG) || defined (__DEBUG) || defined (_STLP_DEBUG)
// disable all optimizations (on)
# if __BORLANDC__ > 0x550
#  pragma checkoption -Od
# endif
// stack frames (on)
# pragma checkoption -k
// include browser information in generated object files (on)
# pragma checkoption -R
// source debugging (on)
# pragma checkoption -v
// enable inline function expansion (off)
# pragma checkoption -vi-
// debug line numbers (on)
# pragma checkoption -y
#endif

// linker flags
// specify warnings (on)
# pragma checkoption /l-w
// public symbol [symbol] defined in both [module1] and [module2] (off)
# pragma checkoption /l-w-dup

#endif // check options

// ============================================================================
#if __BORLANDC__ >= 0x550


# define _STLP_USE_OWN_BAD_ALLOC 1
# define _RWSTD_BAD_ALLOC_DEFINED 1

#  ifndef _STLP_OWN_IOSTREAMS
#   define _STLP_NO_OWN_IOSTREAMS
#  endif

#  define _STLP_BROKEN_EXCEPTION_CLASS 1
//#  define _STLP_NO_EXCEPTION_HEADER 1
#  define _STLP_USE_STDIO_IO 1
#  define _STLP_LONG_LONG  __int64 
#  define _STLP_NON_TYPE_TMPL_PARAM_BUG 1
#  define _STLP_USE_DECLSPEC 1

#  ifdef __CODEGUARD__
#   if ! defined( _STLP_USE_NEWALLOC ) && ! defined ( _STLP_USE_MALLOC )
#    define   _STLP_USE_NEWALLOC 1
#   endif
#   define _STLP_LEAKS_PEDANTIC // optional, for codeguard memory leaks
#  endif

#  define __STD_RWCOMPILER_H__ // exclude native stdcomp.h
#  define STARTWRAP // error in native stddefs.h
#  define ENDWRAP // error in native stddefs.h
#  define _RWSTD_THROW_SPEC_NULL throw() // error in native new.h

// streams
#  define _STLP_OWN_IOSTREAMS
#  define _STLP_USE_STDIO_IO 1 // __pioinfo error in 'fstream.cpp'
#  define _STLP_USE_NEW_IOSTREAMS 1 // for eh_test
#  ifdef _STLP_OWN_IOSTREAMS // oldstl header gurards
#   define __STD_FSTREAM__
#   define __STD_IOS__
#   define __STD_IOSFWD__
#   define __STD_ISTREAM__
#   define __STD_OSTREAM__
#   define __STD_STREAMBUF__
#   define __STD_STRSTREAM__
#  endif
#  define _RW_STD_IOSTREAM // exclude native iostream defs

// memory
#  define _STLP_NEW_DONT_THROW_BAD_ALLOC 1 // stl/_new.h (don't import native bad_alloc)
#  define _USE_OLD_RW_STL 1 // native new.h (operator new, operator delete)
#  undef __TURBOC__  // native oldstl/new.h (avoid duplicate exception class)
#  define _RWSTD_BAD_ALLOC_DEFINED 1 // native oldstl/new.h (avoid duplicate exception class)

// exception
#  define __STD_EXCEPTION 1 // native oldstl/exceptio.h (header guard)
#  define __EXCEPT_H 1 // native except.h (header guard)
#  define _STLP_BROKEN_EXCEPTION_CLASS 1 // use STLport exception class
#  if defined _STLP_BROKEN_EXCEPTION_CLASS && defined (_STLP_VENDOR_GLOBAL_EXCEPT_STD)
#   error inconsistent exception class specifications!
#endif

// strings
#  define __STRING_STL // exclude native string.stl
#  define __STD_STRING // exclude native string.stl

// locale
#  define __LOCALE_H  // exclude native _loc.h, except in stlport/clocale
#  define __USELOCALES__  // native _loc.h (use native setlocale)
#  define __LOCALE_H_USING_LIST // native _loc.h (disable native 'using std::setlocale')

// wchar_t
#  ifndef _STLP_NO_WCHAR_T
#   define _STLP_HAS_WCHAR_T 1
#   define _UNICODE 1
#   define _MBCS 1
#  else
typedef char mbstate_t;
#endif

// templates
#  define _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS 1
#  define _STLP_USE_PTR_SPECIALIZATIONS 1
#  define _STLP_STATIC_TEMPLATE_DATA 1
#  ifdef __BUILDING_STLPORT
#   define _STLP_USE_DECLSPEC 1
#endif

// namespaces
#  define _STLP_USING_NAMESPACE_BUG

// compiler
#  define _STLP_NO_FORCE_INSTANTIATE 1

// linker
#  define _STLP_USE_ALT_LIBNAMES 1

# endif

// ============================================================================

#if ( __BORLANDC__ < 0x540 )

#  error - Support for Borland compilers below version 5.4 to be implemented.

#endif

// auto enable thread safety and exceptions:
#ifndef _CPPUNWIND
#  define _STLP_HAS_NO_EXCEPTIONS
#endif

#if defined ( __MT__ ) && !defined (_NOTHREADS) && !defined (_REENTRANT)
#  define _REENTRANT 1
#endif

#if defined ( __DEBUG ) && ( __DEBUG > 1 )
#  define _STLP_DEBUG
#endif

// Note: If _STLP_USE_TEMPLATE_EXPORT is defined when building STLport, it should 
// also be defined when building STLport applications.  Offsets to class members 
// (e.g., _M_streambuf) may change when _STLP_USE_TEMPLATE_EXPORT is defined.
#  ifdef _STLP_USE_TEMPLATE_EXPORT
#   pragma message "Warning: _STLP_USE_TEMPLATE_EXPORT will increase size of obj and lib files."
#  endif

#  ifndef _STLP_USE_ALT_LIBNAMES
#   define _STLP_LIB_BASENAME stlpmt
#  else
#   if __BORLANDC__ >= 0x600 && __BORLANDC__ < 0x700
#    define _STLP_LIB_BASENAME stlp50_bc60
#   elif __BORLANDC__ >= 0x560 && __BORLANDC__ < 0x600 
#    define _STLP_LIB_BASENAME stlp50_bc56
#   elif __BORLANDC__ >= 0x550 && __BORLANDC__ < 0x560 
#    define _STLP_LIB_BASENAME stlp50_bc55
#   elif __BORLANDC__ >= 0x540 && __BORLANDC__ < 0x550
#    define _STLP_LIB_BASENAME stlp50_bc54
#   else
#    error - Support for Borland compilers below version 5.4 to be implemented.
#   endif
#  endif

#  ifndef _STLP_USE_ALT_LIBNAMES
#   ifdef _RTLDLL
#    define _LIB_SHARED_KEY i
#   else
#    define _LIB_SHARED_KEY
#   endif

#   if ! defined(_DEBUG) && ! defined (__DEBUG) && ! defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY   // release
#   elif (defined(_DEBUG) || __DEBUG < 2) && ! defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY _dbg  // debug
#   elif (defined(_DEBUG) || __DEBUG > 1) && defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY _stldbg  // stldebug
#   else
#    error - check debug configuration!
#   endif

#  else

// _STLP_USE_ALT_LIBNAMES
//  LIBRARY SUFFIX KEY:
//                          MULTITHREAD
//                   RELEASE |  DEBUG  | STLDEBUG
// DLL, IMPORT LIB     SRR       SDR       SDD
// STATIC LIB          ARR       ADR       ADD

#   ifdef _RTLDLL
// Using 's' and 'a' for consistency with rules-*.mak in *nix.
#    define _LIB_SHARED_KEY _s  // shared
#   else
#    define _LIB_SHARED_KEY _a  // archive
#  endif

#   if ! defined(_DEBUG) && ! defined (__DEBUG) && ! defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY rr  // release
#   elif (defined(_DEBUG) || __DEBUG < 2) && ! defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY dr  // debug
#   elif (defined(_DEBUG) || __DEBUG > 1) && defined (_STLP_DEBUG)
#    define _LIB_DEBUG_KEY dd  // stldebug
#   else
#    error - check debug configuration!
#   endif
#  endif /* _STLP_USE_ALT_LIBNAMES */


# define _LIB_ALT_KEY(key) key
# define _LIB_COMBINE_KEYS(base,shared,debug) base ## shared ## debug
# define _STLP_ALT_LIBNAME _LIB_COMBINE_KEYS(_LIB_ALT_KEY(_STLP_LIB_BASENAME),_LIB_ALT_KEY(_LIB_SHARED_KEY),_LIB_ALT_KEY(_LIB_DEBUG_KEY)) ## .lib
# define _STLP_ALT_EXENAME _LIB_COMBINE_KEYS(_LIB_ALT_KEY(_STLP_LIB_BASENAME),_LIB_ALT_KEY(_LIB_SHARED_KEY),_LIB_ALT_KEY(_LIB_DEBUG_KEY))

//# ifdef _STLP_USE_ALT_LIBNAMES
#  ifndef __BUILDING_STLPORT_EXECUTABLE
#   pragma message STLport lib: _STLP_ALT_LIBNAME
#else
#   ifndef _BC5_EXCLUDE_STLP_LIBS
#    define _BC5_EXCLUDE_STLP_LIBS 1
#   endif
#   pragma message STLport [ _STLP_ALT_EXENAME ] .exe
#  endif
//# endif

// ============================================================================
# if (__BORLANDC__ < 0x540)

#  error - Support for Borland compilers below version 5.4 to be implemented.

// ============================================================================
# else /* (__BORLANDC__ >= 0x540) */

#  define _STLP_EXPORT_DECLSPEC __declspec(dllexport)
#  define _STLP_IMPORT_DECLSPEC __declspec(dllimport)

#  define _STLP_CLASS_EXPORT_DECLSPEC __declspec(dllexport)
#  define _STLP_CLASS_IMPORT_DECLSPEC __declspec(dllimport)

#  if !defined (_STLP_NO_OWN_IOSTREAMS)

#   if ( defined (__DLL) || defined (_DLL) || defined (_WINDLL) || defined (_RTLDLL) \
      || defined(_AFXDLL) || defined (_STLP_USE_DYNAMIC_LIB) )
#    undef  _STLP_USE_DECLSPEC
#    define _STLP_USE_DECLSPEC 1
#  endif

#  ifndef _STLP_IMPORT_TEMPLATE_KEYWORD
#    define _STLP_IMPORT_TEMPLATE_KEYWORD __declspec(dllimport)
#  endif

#  define _STLP_EXPORT_TEMPLATE_KEYWORD __declspec(dllexport)

#  if (__BORLANDC__ >= 0x560) && !defined (_STLP_OWN_IOSTREAMS)
#      define _STLP_NATIVE_INCLUDE_PATH ../include/oldstl
#    define _STLP_NATIVE_CPP_C_INCLUDE_PATH ../include/oldstl
#    define _STLP_NATIVE_C_INCLUDE_PATH ../include/oldstl
#    define _STLP_NATIVE_CPP_RUNTIME_PATH ../include/oldstl
#  endif

#   ifdef _STLP_USE_ALT_LIBNAMES
#    if (__BORLANDC__ >= 0x560)
#     ifndef __BUILDING_STLPORT
#      ifdef _STLP_DEBUG
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_sdd.lib")
#         endif
#        else // NOT _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_add.lib")
#         endif
#        endif
#       endif
#      elif (__DEBUG == 1)
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_sdr.lib")
#endif
#        else // NOT _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_adr.lib")
#         endif
#        endif
#       endif
#      else // NOT __DEBUG
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_srr.lib")
#         endif
#        else
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc56_arr.lib")
#         endif
#        endif
#       endif // _MT
#      endif // _STLP_DEBUG
#     endif // __BUILDING_STLPORT
#    elif __BORLANDC__ >= 0x550 && __BORLANDC__ < 0x560
#     ifndef __BUILDING_STLPORT
#      ifdef _STLP_DEBUG
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_sdd.lib")
#         endif
#        else // NOT _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_add.lib")
#         endif
#         ifdef __DLL__
#         else
#         endif
#        endif
#       endif
#      elif (__DEBUG == 1)
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_sdr.lib")
#         endif
#        else // NOT _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_adr.lib")
#         endif
#        endif
#       endif
#      else // NOT __DEBUG
#       ifdef _MT
#        ifdef _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_srr.lib")
#         endif
#        else // NOT _RTLDLL
#         ifndef _BC5_EXCLUDE_STLP_LIBS
#          pragma comment(lib,"stlp50_bc55_arr.lib")
#         endif
#         ifdef __DLL__
#         else
#         endif
#        endif
#       endif // _MT
#      endif // _STLP_DEBUG
#     endif // __BUILDING_STLPORT
#    else /* __BORLANDC__ */
#     error - configure!
#    endif
#   else /* _STLP_USE_ALT_LIBNAMES */
#    ifndef __BUILDING_STLPORT
#     ifdef _STLP_DEBUG
#      ifdef _MT
#       ifdef _RTLDLL
#        pragma comment(lib,"stlpmti_stldbg.lib")
#       else
#        pragma comment(lib,"stlpmt_stldbg.lib")
#       endif
#      endif
#     elif (__DEBUG == 1)
#      ifdef _MT
#       ifdef _RTLDLL
#        pragma comment(lib,"stlpmti_dbg.lib")
#       else
#        pragma comment(lib,"stlpmt_dbg.lib")
#       endif
#      endif
#     else 
#      ifdef _MT
#       ifdef _RTLDLL
#        pragma comment(lib,"stlpmti.lib")
#       else
#        pragma comment(lib,"stlpmt.lib")
#       endif
#      endif
#     endif // _STLP_DEBUG
#    endif // __BUILDING_STLPORT
#   endif /* _STLP_USE_ALT_LIBNAMES */
#  endif /* _STLP_NO_OWN_IOSTREAMS */
# endif /* (__BORLANDC__ >= 0x540) */

