/*
 * Copyright (c) 1997-1999
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

#ifndef _STLP_STRING_HASH_H
#define _STLP_STRING_HASH_H

#ifndef _STLP_HASH_FUN_H
# include <stl/_hash_fun.h>
#endif

#ifndef _STLP_INTERNAL_STRING_H
# include <stl/_string.h>
#endif

#include <stdint.h>

_STLP_BEGIN_NAMESPACE

template <class _CharT, class _Traits, class _Alloc>
inline size_t
__stl_string_hash(const basic_string<_CharT,_Traits,_Alloc>& __s)
{
  uint32_t __h = 0;
  size_t __len = __s.size();
  const _CharT* __data = __s.data();
  while ( __len-- > 0 ) {
    __h += (__h << 5) + *(__data++); // __h = 33 * __h + __s[i]
  }

  return size_t(__h);
}

template <class _CharT, class _Traits, class _Alloc>
struct hash<basic_string<_CharT,_Traits,_Alloc> > {
  size_t operator()(const basic_string<_CharT,_Traits,_Alloc>& __s) const
    { return __stl_string_hash(__s); }
};

_STLP_END_NAMESPACE

#endif

// Local Variables:
// mode:C++
// End:
