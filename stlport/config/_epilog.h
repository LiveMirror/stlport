#if defined (_STLP_MSVC) || defined (__ICL) || defined (__BORLANDC__)

# if defined (__BORLANDC__)
#  if (__BORLANDC__ < 0x530)
#   pragma pack(pop)
#   pragma nopackwarning
#  else
#  pragma option pop
#  endif
#  pragma option -w.ccc	    // -w-8008 Condition is always true OR Condition is always false
#  pragma option -w.inl     // -w-8027 Functions containing reserved words are not expanded inline
#  pragma option -w.ngu     // -w-8041 Negating unsigned value
#  pragma option -w.par     // -w-8057 Parameter 'parameter' is never used
#  pragma option -w.rch	    // -w-8066 Unreachable code
#  pragma option -w.spa     // -w-8072 Suspicious pointer arithmetic
#  pragma option -w-pow     // -w-8062 Previous options and warnings not restored 
#  pragma option -w-pck     // -w-8059 Structure packing size has changed
# else
#  if !(defined (_STLP_MSVC) && (_STLP_MSVC < 1200))
#   pragma warning (pop)
#  endif
#  pragma pack (pop)
# endif

#elif defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)

# pragma reset woff 1174
# pragma reset woff 1375
# pragma reset woff 1209
// from iterator_base.h
# pragma reset woff 1183

#elif defined(__DECCXX)

# ifdef __PRAGMA_ENVIRONMENT
#  pragma __environment __restore
# endif

#elif defined(__IBMCPP__)

#pragma info(restore)

#endif

