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
# include "stlport_prefix.h"


// Trigonometric and hyperbolic functions for complex<float>, 
// complex<double>, and complex<long double>


#include "complex_impl.h"

#include <cfloat>
#include <cmath>

#ifdef _STLP_NO_VENDOR_MATH_F
_STLP_MATH_INLINE2XX(float,atan2f,atan2)
_STLP_MATH_INLINEX(float,cosf,cos)
_STLP_MATH_INLINEX(float,coshf,cosh)
_STLP_MATH_INLINEX(float,expf,exp)
_STLP_MATH_INLINE2XX(float,hypotf,hypot)
_STLP_MATH_INLINEX(float,logf,log)
_STLP_MATH_INLINEX(float,log10f,log10)
_STLP_MATH_INLINEX(float,sinf,sin)
_STLP_MATH_INLINEX(float,sinhf,sinh)
#endif

_STLP_BEGIN_NAMESPACE


//----------------------------------------------------------------------
// helpers

#ifdef __sgi
  static const union { unsigned int i; float f; } float_ulimit = { 0x42b2d4fc };
  static const float float_limit = float_ulimit.f;
  static union {
    struct { unsigned int h; unsigned int l; } w;
    double d;
  } double_ulimit = { 0x408633ce, 0x8fb9f87d };
  static const double double_limit = double_ulimit.d;
  static union {
    struct { unsigned int h[2]; unsigned int l[2]; } w;
    long double ld;
  } ldouble_ulimit = {0x408633ce, 0x8fb9f87e, 0xbd23b659, 0x4e9bd8b1};
# ifndef _STLP_NO_LONG_DOUBLE
  static const long double ldouble_limit = ldouble_ulimit.ld;
# endif
#else
  static const float float_limit = ::logf(FLT_MAX);
  static const double double_limit = ::log(DBL_MAX);
# ifndef _STLP_NO_LONG_DOUBLE
  static const long double ldouble_limit = ::logl(LDBL_MAX);
# endif
#endif


//----------------------------------------------------------------------
// sin

_STLP_DECLSPEC complex<float>  _STLP_CALL sin(const complex<float>& z) {
  return complex<float>(::sinf(z._M_re) * ::coshf(z._M_im),
                        ::cosf(z._M_re) * ::sinhf(z._M_im));
}

_STLP_DECLSPEC complex<double> _STLP_CALL sin(const complex<double>& z) {
  return complex<double>(::sin(z._M_re) * ::cosh(z._M_im),
                         ::cos(z._M_re) * ::sinh(z._M_im));
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL sin(const complex<long double>& z) {
  return complex<long double>(::sinl(z._M_re) * ::coshl(z._M_im),
                              ::cosl(z._M_re) * ::sinhl(z._M_im));
}
#endif

//----------------------------------------------------------------------
// cos

_STLP_DECLSPEC complex<float> _STLP_CALL cos(const complex<float>& z) {
  return complex<float>(::cosf(z._M_re) * ::coshf(z._M_im),
                        -::sinf(z._M_re) * ::sinhf(z._M_im));
}

_STLP_DECLSPEC complex<double> _STLP_CALL cos(const complex<double>& z) {
  return complex<double>(::cos(z._M_re) * ::cosh(z._M_im),
                        -::sin(z._M_re) * ::sinh(z._M_im));
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL cos(const complex<long double>& z) {
  return complex<long double>(::cosl(z._M_re) * ::coshl(z._M_im),
                              -::sinl(z._M_re) * ::sinhl(z._M_im));
}
# endif

//----------------------------------------------------------------------
// tan

_STLP_DECLSPEC complex<float> _STLP_CALL tan(const complex<float>& z) {
  float re2 = 2.f * z._M_re;
  float im2 = 2.f * z._M_im;

  if (::fabsf(im2) > float_limit)
    return complex<float>(0.f, (im2 > 0 ? 1.f : -1.f));
  else {
    float den = ::cosf(re2) + ::coshf(im2);
    return complex<float>(::sinf(re2) / den, ::sinhf(im2) / den);
  }
}

_STLP_DECLSPEC complex<double> _STLP_CALL tan(const complex<double>& z) {
  double re2 = 2. * z._M_re;
  double im2 = 2. * z._M_im;

  if (fabs(float(im2)) > double_limit)
    return complex<double>(0., (im2 > 0 ? 1. : -1.));
  else {
    double den = ::cos(re2) + ::cosh(im2);
    return complex<double>(::sin(re2) / den, ::sinh(im2) / den);
  }
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL tan(const complex<long double>& z) {
  long double re2 = 2.l * z._M_re;
  long double im2 = 2.l * z._M_im;
  if (::fabsl(im2) > ldouble_limit)
    return complex<long double>(0.l, (im2 > 0 ? 1.l : -1.l));
  else {
    long double den = ::cosl(re2) + ::coshl(im2);
    return complex<long double>(::sinl(re2) / den, ::sinhl(im2) / den);
  }
}

# endif

//----------------------------------------------------------------------
// sinh

_STLP_DECLSPEC complex<float> _STLP_CALL sinh(const complex<float>& z) {
  return complex<float>(::sinhf(z._M_re) * ::cosf(z._M_im),
                        ::coshf(z._M_re) * ::sinf(z._M_im));
}

_STLP_DECLSPEC complex<double> _STLP_CALL sinh(const complex<double>& z) {
  return complex<double>(::sinh(z._M_re) * ::cos(z._M_im),
                         ::cosh(z._M_re) * ::sin(z._M_im));
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL sinh(const complex<long double>& z) {
  return complex<long double>(::sinhl(z._M_re) * ::cosl(z._M_im),
                              ::coshl(z._M_re) * ::sinl(z._M_im));
}
#endif

//----------------------------------------------------------------------
// cosh

_STLP_DECLSPEC complex<float> _STLP_CALL cosh(const complex<float>& z) {
  return complex<float>(::coshf(z._M_re) * ::cosf(z._M_im),
                        ::sinhf(z._M_re) * ::sinf(z._M_im));
}

_STLP_DECLSPEC complex<double> _STLP_CALL cosh(const complex<double>& z) {
  return complex<double>(::cosh(z._M_re) * ::cos(z._M_im),
                         ::sinh(z._M_re) * ::sin(z._M_im));
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL cosh(const complex<long double>& z) {
  return complex<long double>(::coshl(z._M_re) * ::cosl(z._M_im),
                              ::sinhl(z._M_re) * ::sinl(z._M_im));
}
#endif

//----------------------------------------------------------------------
// tanh

_STLP_DECLSPEC complex<float> _STLP_CALL tanh(const complex<float>& z) {
  float re2 = 2.f * z._M_re;
  float im2 = 2.f * z._M_im;
  if (::fabsf(re2) > float_limit)
    return complex<float>((re2 > 0 ? 1.f : -1.f), 0.f);
  else {
    float den = ::coshf(re2) + ::cosf(im2);
    return complex<float>(::sinhf(re2) / den, ::sinf(im2) / den);
  }
}

_STLP_DECLSPEC complex<double> _STLP_CALL tanh(const complex<double>& z) {
  double re2 = 2. * z._M_re;
  double im2 = 2. * z._M_im;  
  if (fabs(float(re2)) > double_limit)
    return complex<double>((re2 > 0 ? 1. : -1.), 0.);
  else {
    double den = ::cosh(re2) + ::cos(im2);
    return complex<double>(::sinh(re2) / den, ::sin(im2) / den);
  }
}

#ifndef _STLP_NO_LONG_DOUBLE
_STLP_DECLSPEC complex<long double> _STLP_CALL tanh(const complex<long double>& z) {
  long double re2 = 2.l * z._M_re;
  long double im2 = 2.l * z._M_im;
  if (::fabsl(re2) > ldouble_limit)
    return complex<long double>((re2 > 0 ? 1.l : -1.l), 0.l);
  else {
    long double den = ::coshl(re2) + ::cosl(im2);
    return complex<long double>(::sinhl(re2) / den, ::sinl(im2) / den);
  }
}
#endif
_STLP_END_NAMESPACE
