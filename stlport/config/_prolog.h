
#if defined (_STLP_MSVC) || defined (__ICL)

#  if !(defined (_STLP_MSVC) && (_STLP_MSVC < 1200))
#    pragma warning(push)
#  endif
/* We are using a special memory alignment for the node_allocator
 * implementation.
 */
#  if !defined (_WIN64)
#    pragma pack(push, 8)
#  else
#    pragma pack(push, 16)
#  endif
#  include <config/_msvc_warnings_off.h>

#elif defined (__BORLANDC__)
#  pragma option -w-pck
#  if (__BORLANDC__ < 0x530)
#   pragma pack(push)
#  else
#   pragma option push 
#  endif
#  pragma option -Vx- -Ve- -a8 -b -pc
#  pragma option -w-aus     // -w-8004 'identifier' is assigned a value that is never used
#  pragma option -w-ccc	    // -w-8008 Condition is always true OR Condition is always false
//#  pragma option -w-csu   // -w-8012 Comparing signed and unsigned values
//#  pragma option -w-dup   // -w-8017 Redefinition of 'macro' is not identical
#  pragma option -w-inl     // -w-8027 Functions containing reserved words are not expanded inline
#  pragma option -w-ngu     // -w-8041 Negating unsigned value
#  pragma option -w-par     // -w-8057 Parameter 'parameter' is never used
#  pragma option -w-pow     // -w-8062 Previous options and warnings not restored
#  pragma option -w-rch	    // -w-8066 Unreachable code
#  pragma option -w-sig     // -w-8071 Conversion may lose significant digits 
#  pragma option -w-spa     // -w-8072 Suspicious pointer arithmetic
//#  pragma option -w-use   // -w-8080 'identifier' declared but never used

#elif defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)

#  pragma set woff 1209
#  pragma set woff 1174
#  pragma set woff 1375
// from iterator_base.h
#  pragma set woff 1183

#elif defined(__DECCXX)

#  ifdef __PRAGMA_ENVIRONMENT
#    pragma __environment __save
#    pragma __environment __header_defaults
#  endif

#elif defined(__IBMCPP__)
// supress EDC3130: A constant is being used as a conditional expression
#  pragma info(nocnd)

#elif defined (__HP_aCC)
/* _REENTRANT selects Posix 1c threads unless draft4 selected.
 *  * This usage is obsolescent, "-D_POSIX_C_SOURCE=199506" is preferred */
#  if 0 /* defined (_REENTRANT) && ! defined (_POSIX_C_SOURCE) */
#    define _POSIX_C_SOURCE 199506
#  endif
#elif defined (__WATCOMCPLUSPLUS__)
#  pragma warning 604 10 // must lookahead to determine...
#  pragma warning 594 10 // resolved as declaration/type
#  pragma warning 595 10 // resolved as an expression
#endif
