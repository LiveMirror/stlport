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
#  define _STLP_OUTERMOST_HEADER_ID 0x219
#  include <stl/_prolog.h>
#elif (_STLP_OUTERMOST_HEADER_ID == 0x219) && ! defined (_STLP_DONT_POP_HEADER_ID)
#  define _STLP_DONT_POP_HEADER_ID
#endif

#include _STLP_NATIVE_C_HEADER(ctype.h)

// Undef convenience interfaces
#undef isspace
#undef isprint
#undef iscntrl
#undef isupper
#undef islower
#undef isalpha
#undef isdigit
#undef ispunct
#undef isxdigit
#undef isalnum
#undef isgraph
#undef toupper
#undef tolower

#if defined(UNDER_CE)
#  if (_WIN32_WCE < 300)                  // Only wide chars for older versions
#    define _isctype iswctype
#  endif

inline int (isalpha)(int c) { return _isctype(c, _ALPHA); }
inline int (isupper)(int c) { return _isctype(c, _UPPER); }
inline int (islower)(int c) { return _isctype(c, _LOWER); }
inline int (isdigit)(int c) { return _isctype(c, _DIGIT); }
inline int (isxdigit)(int c) { return _isctype(c, _HEX); }
inline int (isspace)(int c) { return _isctype(c, _SPACE); }
inline int (ispunct)(int c) { return _isctype(c, _PUNCT); }
inline int (isalnum)(int c) { return _isctype(c, _ALPHA|_DIGIT); }
inline int (isprint)(int c) { return _isctype(c, _BLANK|_PUNCT|_ALPHA|_DIGIT); }
inline int (isgraph)(int c) { return _isctype(c, _PUNCT|_ALPHA|_DIGIT); }
inline int (iscntrl)(int c) { return _isctype(c, _CONTROL); }
inline int (isascii)(int c) { return ((unsigned)(c) < 0x80); }

#undef _isctype

inline int (iswalpha)(int c) { return iswctype(c, _ALPHA); }
inline int (iswupper)(int c) { return iswctype(c, _UPPER); }
inline int (iswlower)(int c) { return iswctype(c, _LOWER); }
inline int (iswdigit)(int c) { return iswctype(c, _DIGIT); }
inline int (iswxdigit)(int c) { return iswctype(c, _HEX); }
inline int (iswspace)(int c) { return iswctype(c, _SPACE); }
inline int (iswpunct)(int c) { return iswctype(c, _PUNCT); }
inline int (iswalnum)(int c) { return iswctype(c, _ALPHA|_DIGIT); }
inline int (iswprint)(int c) { return iswctype(c, _BLANK|_PUNCT|_ALPHA|_DIGIT); }
inline int (iswgraph)(int c) { return iswctype(c, _PUNCT|_ALPHA|_DIGIT); }
inline int (iswcntrl)(int c) { return iswctype(c, _CONTROL); }
inline int (iswascii)(int c) { return ((unsigned)(c) < 0x80); }

#endif

#if (_STLP_OUTERMOST_HEADER_ID == 0x219)
#  if ! defined (_STLP_DONT_POP_HEADER_ID)
#    include <stl/_epilog.h>
#    undef  _STLP_OUTERMOST_HEADER_ID
#  endif
#  undef  _STLP_DONT_POP_HEADER_ID
#endif

// Local Variables:
// mode:C++
// End:
