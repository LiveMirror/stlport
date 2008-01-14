#ifndef __stl_config__hpux_h
#define __stl_config__hpux_h

#define _STLP_PLATFORM "HP Unix"

#ifdef __GNUC__
#  define _STLP_NO_WCHAR_T
#  define _STLP_NO_CWCHAR
#  define _STLP_NO_LONG_DOUBLE
#endif

#ifndef _POSIX_C_SOURCE
#  define _POSIX_C_SOURCE 199506
#endif

#endif /* __stl_config__hpux_h */
