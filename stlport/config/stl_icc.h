// STLport configuration file
// It is internal STLport header - DO NOT include it directly
// A list of Intel compiler for Linux portion of STLport settings.

# define _STLP_LONG_LONG long long

// Edit relative path below (or put full path) to get native
// compiler headers included. Default is "../include".
// C headers may reside in different directory, so separate macro is provided.
# if (__INTEL_COMPILER >= 800)
# define _STLP_NATIVE_INCLUDE_PATH ../include/c++
# define _STLP_NATIVE_C_INCLUDE_PATH ../include
# define _STLP_NATIVE_CPP_C_INCLUDE_PATH ../include
# endif /* __INTEL_COMPILER >= 800 */

# undef _STLP_WINCE

# ifndef __GNUC__ 
# define __GNUC__ 1
# endif

# define _STLP_NO_NATIVE_WIDE_FUNCTIONS 1
