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

#ifndef LOCALE_IMPL_H
#define LOCALE_IMPL_H

#include <clocale>             // C locale header file.
#include <vector>
#include <string>
#include <locale>
#include "c_locale.h"

_STLP_BEGIN_NAMESPACE

#if defined (_STLP_USE_TEMPLATE_EXPORT)
//Export of _Locimp facets container:
#  if !defined (_STLP_USE_PTR_SPECIALIZATIONS)
//If we are using pointer specialization, vector<locale::facet*> will use
//the already exported vector<void*> implementation.
_STLP_EXPORT_TEMPLATE_CLASS allocator<locale::facet*>;

_STLP_MOVE_TO_PRIV_NAMESPACE

_STLP_EXPORT_TEMPLATE_CLASS _STLP_alloc_proxy<locale::facet**, locale::facet*, allocator<locale::facet*> >;
_STLP_EXPORT_TEMPLATE_CLASS _Vector_base<locale::facet*, allocator<locale::facet*> >;

_STLP_MOVE_TO_STD_NAMESPACE
#  endif
#  if defined (_STLP_DEBUG)
_STLP_MOVE_TO_PRIV_NAMESPACE
#    define _STLP_NON_DBG_VECTOR _STLP_NON_DBG_NAME(vector)
_STLP_EXPORT_TEMPLATE_CLASS __construct_checker<_STLP_NON_DBG_VECTOR<locale::facet*, allocator<locale::facet*> > >;
_STLP_EXPORT_TEMPLATE_CLASS _STLP_NON_DBG_VECTOR<locale::facet*, allocator<locale::facet*> >;
#    undef _STLP_NON_DBG_VECTOR
_STLP_MOVE_TO_STD_NAMESPACE
#  endif

_STLP_EXPORT_TEMPLATE_CLASS vector<locale::facet*, allocator<locale::facet*> >;
#endif

//----------------------------------------------------------------------

void _STLP_CALL _release_Locimp( locale::_Locimp *& loc );

_STLP_END_NAMESPACE

#endif

// Local Variables:
// mode:C++
// End:
