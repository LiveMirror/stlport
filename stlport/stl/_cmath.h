/*
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

#ifndef _STLP_CMATH_H_HEADER
#define _STLP_CMATH_H_HEADER

#if 0

/* I try to comments this code do to following reasons:
 *
 * 1. This code used only for VC before VC 7 (_STLP_MSVC <= 1300)
 * 2. _STLP_DO_* macro not used below for (_STLP_MSVC <= 1300)
 * 3. From 1. and 2. I expect that _STLP_DO_* macro and _STL_math_proxy
 *    not required...
 *
 *          - ptr 2005-03-05
 */

#ifdef _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG

_STLP_BEGIN_NAMESPACE

// this proxy is needed for some compilers to resolve problems
// calling sqrt() from within sqrt(), etc.
template <class _Tp>
struct _STL_math_proxy {
  static inline _Tp _do_abs(const _Tp& __x)     { return _STLP_VENDOR_CSTD::fabs(__x); } 
  static inline _Tp _do_acos(const _Tp& __x)    { return _STLP_VENDOR_CSTD::acos(__x); } 
  static inline _Tp _do_asin(const _Tp& __x)    { return _STLP_VENDOR_CSTD::asin(__x); } 
  static inline _Tp _do_atan(const _Tp& __x)    { return _STLP_VENDOR_CSTD::atan(__x); } 
  static inline _Tp _do_atan2(const _Tp& __x, const _Tp& __y)  { return _STLP_VENDOR_CSTD::atan2(__x, __y); } 
  static inline _Tp _do_cos(const _Tp& __x)     { return _STLP_VENDOR_CSTD::cos(__x); } 
  static inline _Tp _do_cosh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::cosh(__x); } 
  static inline _Tp _do_floor(const _Tp& __x)    { return _STLP_VENDOR_CSTD::floor(__x); } 
  static inline _Tp _do_ceil(const _Tp& __x)    { return _STLP_VENDOR_CSTD::ceil(__x); } 
  static inline _Tp _do_fmod(const _Tp& __x, const _Tp& __y)    { return _STLP_VENDOR_CSTD::fmod(__x, __y); } 
  static inline _Tp _do_frexp(const _Tp& __x, int* __y)    { return _STLP_VENDOR_CSTD::frexp(__x, __y); } 
  static inline _Tp _do_ldexp(const _Tp& __x, int __y)    { return _STLP_VENDOR_CSTD::ldexp(__x, __y); } 
  static inline _Tp _do_modf(const _Tp& __x, double* __y) { return _STLP_VENDOR_CSTD::modf(__x, __y); }
  static inline _Tp _do_log(const _Tp& __x)     { return _STLP_VENDOR_CSTD::log(__x); } 
  static inline _Tp _do_log10(const _Tp& __x)   { return _STLP_VENDOR_CSTD::log10(__x); } 
  static inline _Tp _do_pow(const _Tp& __x, const _Tp& __y)    { return _STLP_VENDOR_CSTD::pow(__x, __y); } 
  static inline _Tp _do_pow(const _Tp& __x, int __y)    { return _STLP_VENDOR_CSTD::pow(__x, __y); } 
  static inline _Tp _do_sin(const _Tp& __x)     { return _STLP_VENDOR_CSTD::sin(__x); } 
  static inline _Tp _do_sinh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::sinh(__x); } 

  static inline _Tp _do_sqrt(const _Tp& __x)    { return _STLP_VENDOR_CSTD::sqrt(__x); } 
  static inline _Tp _do_tan(const _Tp& __x)     { return _STLP_VENDOR_CSTD::tan(__x); } 
  static inline _Tp _do_tanh(const _Tp& __x)    { return _STLP_VENDOR_CSTD::tanh(__x); } 
  static inline _Tp _do_exp(const _Tp& __x)     { return _STLP_VENDOR_CSTD::exp(__x); } 
#  ifdef _STLP_WCE
  static inline _Tp _do_hypot(const _Tp& __x, const _Tp& __y)   { return _STLP_VENDOR_CSTD::sqrt(__x * __x + __y * __y); } 
#  else // _STLP_WCE
  static inline _Tp _do_hypot(const _Tp& __x, const _Tp& __y)   { return _STLP_VENDOR_CSTD::hypot(__x, __y); } 
#  endif // _STLP_WCE
};

_STLP_END_NAMESPACE

# define _STLP_DO_ABS(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_abs
# define _STLP_DO_ABSF(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_abs
# define _STLP_DO_ACOS(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_acos
# define _STLP_DO_ASIN(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_asin
# define _STLP_DO_ATAN(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_atan
# define _STLP_DO_ATAN2(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_atan2
# define _STLP_DO_COS(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_cos
# define _STLP_DO_COSH(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_cosh
# define _STLP_DO_FLOOR(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_floor
# define _STLP_DO_CEIL(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_ceil
# define _STLP_DO_FMOD(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_fmod
# define _STLP_DO_FREXP(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_frexp
# define _STLP_DO_LDEXP(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_ldexp
# define _STLP_DO_MODF(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_modf
# define _STLP_DO_LOG(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_log
# define _STLP_DO_LOG10(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_log10
# define _STLP_DO_POW(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_pow
# define _STLP_DO_SIN(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_sin
# define _STLP_DO_SINH(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_sinh
# define _STLP_DO_SQRT(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_sqrt
# define _STLP_DO_TAN(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_tan
# define _STLP_DO_TANH(_Tp)  _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_tanh
# define _STLP_DO_EXP(_Tp)   _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_exp
# define _STLP_DO_HYPOT(_Tp) _STLP_STD_NAME::_STL_math_proxy<_Tp>::_do_hypot

#else /* _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG */

# define _STLP_DO_ABS(_Tp)   ::fabs
# define _STLP_DO_ABSF(_Tp)  ::fabsf
# define _STLP_DO_ACOS(_Tp)  ::acos
# define _STLP_DO_ASIN(_Tp)  ::asin
# define _STLP_DO_ATAN(_Tp)  ::atan
# define _STLP_DO_ATAN2(_Tp) ::atan2
# define _STLP_DO_COS(_Tp)   ::cos
# define _STLP_DO_COSH(_Tp)  ::cosh
# define _STLP_DO_FLOOR(_Tp) ::floor
# define _STLP_DO_CEIL(_Tp)  ::ceil
# define _STLP_DO_FMOD(_Tp)  ::fmod
# define _STLP_DO_FREXP(_Tp) _STLP_VENDOR_CSTD::frexp
# define _STLP_DO_LDEXP(_Tp) _STLP_VENDOR_CSTD::ldexp
# define _STLP_DO_MODF(_Tp) _STLP_VENDOR_CSTD::modf
# define _STLP_DO_LOG(_Tp)   _STLP_VENDOR_CSTD::log
# define _STLP_DO_LOG10(_Tp) _STLP_VENDOR_CSTD::log10
# define _STLP_DO_POW(_Tp)   _STLP_VENDOR_CSTD::pow
# define _STLP_DO_SIN(_Tp)   _STLP_VENDOR_CSTD::sin
# define _STLP_DO_SINH(_Tp)  _STLP_VENDOR_CSTD::sinh
# define _STLP_DO_SQRT(_Tp)  _STLP_VENDOR_CSTD::sqrt
# define _STLP_DO_TAN(_Tp)   _STLP_VENDOR_CSTD::tan
# define _STLP_DO_TANH(_Tp)  _STLP_VENDOR_CSTD::tanh
# define _STLP_DO_EXP(_Tp)   _STLP_VENDOR_CSTD::exp
//# if defined (__GNUC__) || defined ( __IBMCPP__ ) || defined (__SUNPRO_CC) || defined (__HP_aCC) || (_MSC_VER >= 1310)
# define _STLP_DO_HYPOT(_Tp) ::hypot
// # else
// #  define _STLP_DO_HYPOT(_Tp) _STLP_VENDOR_CSTD::hypot
// # endif

#endif /* _STLP_SAME_FUNCTION_NAME_RESOLUTION_BUG */

#endif // 0

#if !defined(_STLP_MSVC) || (_STLP_MSVC > 1300) || !defined(_MSC_EXTENSIONS) || defined(_STLP_WCE)
# define _STLP_MATH_INLINE(__type,func,cfunc) \
  inline __type func (__type x) { return ::cfunc(x); }
# define _STLP_MATH_INLINE2(__type1,__type2,func,cfunc) \
  inline __type1 func (__type1 x, __type2 y) { return ::cfunc(x,y); }
#else
# define _STLP_MATH_INLINE(float_type,func,cfunc) \
  inline float_type func (float_type x) { return (cfunc(x)); }
# define _STLP_MATH_INLINE2(float_type,type,func,cfunc) \
  inline float_type func (float_type x, type y) { return (cfunc(x,y)); }
#endif

#define _STLP_MATH_INLINEX(__type,func,cfunc) \
  inline __type func (__type x) { return __STATIC_CAST(__type,::cfunc((double)x)); }
#define _STLP_MATH_INLINE2X(__type1,__type2,func,cfunc) \
  inline __type1 func (__type1 x, __type2 y) { return __STATIC_CAST(__type1,::cfunc((double)x,y)); }
#define _STLP_MATH_INLINE2XX(__type1,func,cfunc) \
  inline __type1 func (__type1 x, __type1 y) { return __STATIC_CAST(__type1,::cfunc((double)x,(double)y)); }

#if !defined(_STLP_NO_LONG_DOUBLE) && !defined(_STLP_NO_VENDOR_MATH_L) && !defined(_STLP_NO_VENDOR_MATH_F) // && defined(_STLP_VENDOR_LONG_DOUBLE_MATH)
# define _STLP_DEF_MATH_INLINE(func,cf) \
  _STLP_MATH_INLINE(float,func,cf##f) \
  _STLP_MATH_INLINE(long double,func,cf##l)
# define _STLP_DEF_MATH_INLINE2(func,cf) \
  _STLP_MATH_INLINE2(float,float,func,cf##f) \
  _STLP_MATH_INLINE2(long double,long double,func,cf##l)
# define _STLP_DEF_MATH_INLINE2P(func,cf) \
  _STLP_MATH_INLINE2(float,float *,func,cf##f) \
  _STLP_MATH_INLINE2(long double,long double *,func,cf##l)
# define _STLP_DEF_MATH_INLINE2PI(func,cf) \
  _STLP_MATH_INLINE2(float,int *,func,cf##f) \
  _STLP_MATH_INLINE2(long double,int *,func,cf##l)
# define _STLP_DEF_MATH_INLINE2I(func,cf) \
  _STLP_MATH_INLINE2(float,int,func,cf##f) \
  _STLP_MATH_INLINE2(long double,int,func,cf##l)
#else // !_STLP_NO_LONG_DOUBLE
# ifndef _STLP_NO_VENDOR_MATH_F
#  define _STLP_DEF_MATH_INLINE(func,cf) \
    _STLP_MATH_INLINE(float,func,cf##f)
#  define _STLP_DEF_MATH_INLINE2(func,cf) \
    _STLP_MATH_INLINE2(float,float,func,cf##f)
#  define _STLP_DEF_MATH_INLINE2P(func,cf) \
    _STLP_MATH_INLINE2(float,float *,func,cf##f)
#  define _STLP_DEF_MATH_INLINE2PI(func,cf) \
    _STLP_MATH_INLINE2(float,int *,func,cf##f)
#  define _STLP_DEF_MATH_INLINE2I(func,cf) \
    _STLP_MATH_INLINE2(float,int,func,cf##f)
# else // _STLP_NO_VENDOR_MATH_F
#  define _STLP_DEF_MATH_INLINE(func,cf) \
    _STLP_MATH_INLINEX(float,func,cf)
#  define _STLP_DEF_MATH_INLINE2(func,cf) \
    _STLP_MATH_INLINE2XX(float,func,cf)
#  define _STLP_DEF_MATH_INLINE2P(func,cf) \
    _STLP_MATH_INLINE2X(float,float *,func,cf)
#  define _STLP_DEF_MATH_INLINE2PI(func,cf) \
    _STLP_MATH_INLINE2X(float,int *,func,cf)
#  define _STLP_DEF_MATH_INLINE2I(func,cf) \
    _STLP_MATH_INLINE2X(float,int,func,cf)
# endif // _STLP_NO_VENDOR_MATH_F
#endif // !_STLP_NO_LONG_DOUBLE

#if defined (_STLP_WCE) || \
   (defined(_STLP_MSVC) && (_STLP_MSVC <= 1300) && defined (_MSC_EXTENSIONS) /* && !defined(_STLP_WCE_NET) */)
/*
 * dums: VC6 has all the required C++ functions but only define them if
 * _MSC_EXTENSIONS is not defined (a bug?). STLport just do the same
 * thing also when _MSC_EXTENSIONS is defined.
 */
//We have to tell the compilers that abs, acos ... math functions are not intrinsic
//otherwise we have Internal Compiler Error in release mode...
#  pragma warning(push)
#  pragma warning(disable: 4162) // no function with C linkage found
#  pragma warning(disable: 4163) // not available as an intrinsic function
#  pragma function (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh)
#  if defined (_STLP_WCE)
#    pragma function (ceil, floor)
#  endif
#endif // _STLP_MSVC && _STLP_MSVC <= 1300 && !_STLP_WCE && _MSC_EXTENSIONS

inline double abs(double __x) { return ::fabs(__x); }
#ifndef __MVS__
_STLP_DEF_MATH_INLINE(abs,fabs)
#else // __MVS__ has native long double abs?
inline float abs(float __x) { return ::fabsf(__x); }
#endif
_STLP_DEF_MATH_INLINE(acos,acos)
_STLP_DEF_MATH_INLINE(asin,asin)
_STLP_DEF_MATH_INLINE(atan,atan)
_STLP_DEF_MATH_INLINE2(atan2,atan2)
_STLP_DEF_MATH_INLINE(ceil,ceil)
_STLP_DEF_MATH_INLINE(cos,cos)
_STLP_DEF_MATH_INLINE(cosh,cosh)
_STLP_DEF_MATH_INLINE(exp,exp)
_STLP_DEF_MATH_INLINE(fabs,fabs)
_STLP_DEF_MATH_INLINE(floor,floor)
_STLP_DEF_MATH_INLINE2(fmod,fmod)
_STLP_DEF_MATH_INLINE2PI(frexp,frexp)

#if defined(_STLP_MSVC)
_STLP_MATH_INLINE2XX(float,hypot,hypot)
_STLP_MATH_INLINE2XX(long double,hypot,hypot)
#else
# ifdef _STLP_USE_UCLIBC
inline double hypot(double x, double y) { return sqrt(x*x + y*y); }
# endif
_STLP_DEF_MATH_INLINE2(hypot,hypot)
#endif

_STLP_DEF_MATH_INLINE2I(ldexp,ldexp)
_STLP_DEF_MATH_INLINE(log,log)
_STLP_DEF_MATH_INLINE(log10,log10)
_STLP_DEF_MATH_INLINE2P(modf,modf)

#if 0 // Unknown OS, where float/long double modf missed
// fbp : float versions are not always available

// Context of define of _STLP_VENDOR_LONG_DOUBLE_MATH should be changed:
// many OS has *l math functions... -ptr

# if !defined(_STLP_VENDOR_LONG_DOUBLE_MATH)  //*ty 11/25/2001 - 
inline float modf (float __x, float* __y)     { 
  double __dd[2]; 
  double __res = ::modf((double)__x, __dd); 
  __y[0] = (float)__dd[0] ; __y[1] = (float)__dd[1]; 
  return (float)__res; 
}
#  else  //*ty 11/25/2001 - i.e. for apple SCpp
inline float modf (float __x, float* __y)     { 
  long double __dd[2]; 
  long double __res = ::modfl(__STATIC_CAST(long double,__x), __dd); 
  __y[0] = __STATIC_CAST(float,__dd[0]); __y[1] = __STATIC_CAST(float,__dd[1]); 
  return __STATIC_CAST(float,__res);
}
# endif  //*ty 11/25/2001 - 
// fbp : long double versions are not available
inline long double modf (long double __x, long double* __y) { 
  double __dd[2]; 
  double __res = ::modf((double)__x, __dd); 
  __y[0] = (long double)__dd[0] ; __y[1] = (long double)__dd[1]; 
  return (long double)__res; 
}
#endif // 0

_STLP_DEF_MATH_INLINE2(pow,pow)

#if !defined(_STLP_MSVC) /* || (_STLP_MSVC > 1300) */ || defined(_STLP_WCE) || !defined (_MSC_EXTENSIONS) /* && !defined(_STLP_WCE_NET) */
# ifndef _STLP_NO_VENDOR_MATH_F
inline float       pow(float __x, int __y)       { return ::powf(__x, __STATIC_CAST(float,__y)); }
# else
inline float       pow(float __x, int __y)       { return __STATIC_CAST(float,::pow(__x, __STATIC_CAST(float,__y))); }
# endif
inline double      pow(double __x, int __y)      { return ::pow(__x, __STATIC_CAST(double,__y)); }
# if !defined(_STLP_NO_VENDOR_MATH_L) && !defined(_STLP_NO_LONG_DOUBLE)
inline long double pow(long double __x, int __y) { return ::powl(__x, __STATIC_CAST(long double,__y)); }
# elif !defined(_STLP_NO_LONG_DOUBLE)
inline long double pow(long double __x, int __y) { return __STATIC_CAST(long double,::pow(__x, __STATIC_CAST(long double,__y))); }
# endif
#else
//The MS native pow version has a bugged overload so it is not imported
//in the STLport namespace.
//Here is the bugged version:
//inline double pow(int __x, int __y)            { return (_Pow_int(__x, __y)); }
inline double      pow(double __x, int __y)      { return (_Pow_int(__x, __y)); }
inline float       pow(float __x, int __y)       { return (_Pow_int(__x, __y)); }
inline long double pow(long double __x, int __y) { return (_Pow_int(__x, __y)); }
#endif

_STLP_DEF_MATH_INLINE(sin,sin)
_STLP_DEF_MATH_INLINE(sinh,sinh)
_STLP_DEF_MATH_INLINE(sqrt,sqrt)
_STLP_DEF_MATH_INLINE(tan,tan)
_STLP_DEF_MATH_INLINE(tanh,tanh)

#if defined (_STLP_WCE) || \
   (defined(_STLP_MSVC) && (_STLP_MSVC <= 1300) && defined (_MSC_EXTENSIONS) /* && !defined(_STLP_WCE_NET) */)
//restoration of the default intrinsic status of those functions:
#  pragma intrinsic (abs, acos, asin, atan, atan2, cos, cosh, exp, fabs, fmod, log, log10, sin, sinh, sqrt, tan, tanh)
#  if defined (_STLP_WCE)
#    pragma intrinsic (ceil, floor)
#  endif
#  pragma warning(pop)
#endif // _STLP_MSVC && _STLP_MSVC <= 1300 && !_STLP_WCE && _MSC_EXTENSIONS

_STLP_BEGIN_NAMESPACE
using ::abs;
using ::acos;
using ::asin;
using ::atan;
using ::atan2;
using ::ceil;
using ::cos;
using ::cosh;
using ::exp;
using ::fabs;
using ::floor;
using ::fmod;
using ::frexp;
using ::hypot;
using ::ldexp;
using ::log;
using ::log10;
using ::modf;
using ::pow;
using ::sin;
using ::sinh;
using ::sqrt;
using ::tan;
using ::tanh;
_STLP_END_NAMESPACE

#endif /* CMATH_H */

// Local Variables:
// mode:C++
// End:
