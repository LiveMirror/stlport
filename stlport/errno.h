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

#if !defined (_STLP_OUTERMOST_HEADER_ID)
#  define _STLP_OUTERMOST_HEADER_ID 0x205
#  include <stl/_prolog.h>
#elif (_STLP_OUTERMOST_HEADER_ID == 0x205) && !defined (_STLP_DONT_POP_HEADER_ID)
#  define _STLP_DONT_POP_HEADER_ID
#endif

#if defined (errno)
/* We are forced to undef errno otherwise the include of the native
 * errno.h file would fail with a message like:
 * unable to find file ../include/(errno_macro_replacement).h
 */
#  define _STLP_ERRNO_ALREADY_DEFINED
#  undef errno
#endif

#include _STLP_NATIVE_C_HEADER(errno.h)

#if defined (errno) || defined (_STLP_ERRNO_ALREADY_DEFINED)
#  if !defined (_STLP_ERRNO_ALREADY_DEFINED)
/* If errno was already defined it means that STLport errno.h
 * has already been included and __stlp_errno define. We do not 
 * redefine it as the errno macro might not have been redefine
 * in the case of a non reentrant native errno.h file (a common 
 * case).
 */
inline int* __stlp_errno() {
  return &(errno);
}
#  endif
#  undef errno
#  define errno (*__stlp_errno())
#else
_STLP_BEGIN_NAMESPACE
using ::errno;
_STLP_END_NAMESPACE
#endif

#if (_STLP_OUTERMOST_HEADER_ID == 0x205)
#  if ! defined (_STLP_DONT_POP_HEADER_ID)
#    include <stl/_epilog.h>
#    undef  _STLP_OUTERMOST_HEADER_ID
#  endif
#  undef  _STLP_DONT_POP_HEADER_ID
#endif

// Local Variables:
// mode:C++
// End:
