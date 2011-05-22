/*
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
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
 */

#ifndef _STLP_STRING_C
#define _STLP_STRING_C

#ifndef _STLP_INTERNAL_STRING_H
#  include <stl/_string.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_H
#  include <stl/_function.h>
#endif

#include <stl/_bstring_operators.h>

#ifndef _STLP_INTERNAL_CTRAITS_FUNCTIONS_H
#  include <stl/_ctraits_fns.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_H
#  include <stl/_function.h>
#endif

#if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#  define basic_string _STLP_NO_MEM_T_NAME(str)
#elif defined (_STLP_DEBUG)
#  define basic_string _STLP_NON_DBG_NAME(str)
#endif

#if defined (_STLP_NESTED_TYPE_PARAM_BUG)
#  define __size_type__ size_t
#  define size_type size_t
#  define iterator _CharT*
#else
#  define __size_type__ _STLP_TYPENAME_ON_RETURN_TYPE basic_string<_CharT,_Traits,_Alloc>::size_type
#endif

_STLP_BEGIN_NAMESPACE

_STLP_MOVE_TO_PRIV_NAMESPACE

// A helper class to use a char_traits as a function object.
template <class _Traits>
struct _Not_within_traits : public unary_function<typename _Traits::char_type, bool> {
  typedef typename _Traits::char_type _CharT;
  const _CharT* _M_first;
  const _CharT* _M_last;

  _Not_within_traits(const _CharT* __f, const _CharT* __l)
    : _M_first(__f), _M_last(__l) {}

  bool operator()(const _CharT& __x) const {
    return find_if(_M_first, _M_last,
                   _STLP_PRIV _Eq_char_bound<_Traits>(__x)) == _M_last;
  }
};

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_of_aux(_InputIter __first1, _InputIter __last1,
                                          const _CharT* __first2, const _CharT* __last2,
                                          _Traits*, const true_type& /* _STLportTraits */)
{ return __find_first_of(__first1, __last1, __first2, __last2); }

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_of_aux(_InputIter __first1, _InputIter __last1,
                                          const _CharT* __first2, const _CharT* __last2,
                                          _Traits*, const false_type& /* _STLportTraits */)
{ return __find_first_of(__first1, __last1, __first2, __last2, _STLP_PRIV _Eq_traits<_Traits>()); }

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_of(_InputIter __first1, _InputIter __last1,
                                      const _CharT* __first2, const _CharT* __last2,
                                      _Traits* __traits) {
#if !defined (__BORLANDC__)
  // typedef typename _IsSTLportClass<_Traits>::_Ret _STLportTraits;
#else
  // enum { _Is = _IsSTLportClass<_Traits>::_Is };
  // typedef typename __bool2type<_Is>::_Ret _STLportTraits;
#endif
  return __str_find_first_of_aux(__first1, __last1, __first2, __last2, __traits, true_type() /* _STLportTraits() */ );
}

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_not_of_aux3(_InputIter __first1, _InputIter __last1,
                                               const _CharT* __first2, const _CharT* __last2,
                                               _Traits* /* __traits */, const true_type& __useStrcspnLikeAlgo)
{ return __find_first_of_aux2(__first1, __last1, __first2, __last2, __first2, not1(_Identity<bool>()), __useStrcspnLikeAlgo); }

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_not_of_aux3(_InputIter __first1, _InputIter __last1,
                                               const _CharT* __first2, const _CharT* __last2,
                                               _Traits* /* __traits */, const false_type& /* _UseStrcspnLikeAlgo */)
{ return _STLP_STD::find_if(__first1, __last1, _STLP_PRIV _Not_within_traits<_Traits>(__first2, __last2)); }

template <class _InputIter, class _CharT, class _Tp, class _Traits>
inline _InputIter __str_find_first_not_of_aux2(_InputIter __first1, _InputIter __last1,
                                               const _CharT* __first2, const _CharT* __last2,
                                               _Tp* __pt, _Traits* __traits) {
  typedef typename integral_constant<bool, is_integral<_Tp>::value && _STLP_PRIV is_char<_CharT>::value>::type _UseStrcspnLikeAlgo;
  return __str_find_first_not_of_aux3(__first1, __last1, __first2, __last2, __traits, _UseStrcspnLikeAlgo());
}

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_not_of_aux1(_InputIter __first1, _InputIter __last1,
                                               const _CharT* __first2, const _CharT* __last2,
                                               _Traits* __traits, const true_type& /* _STLportTraits */)
{ return __str_find_first_not_of_aux2(__first1, __last1, __first2, __last2,
                                      _STLP_VALUE_TYPE(__first1, _InputIter), __traits); }

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_not_of_aux1(_InputIter __first1, _InputIter __last1,
                                               const _CharT* __first2, const _CharT* __last2,
                                               _Traits*, const false_type& /* _STLportTraits */)
{ return _STLP_STD::find_if(__first1, __last1, _STLP_PRIV _Not_within_traits<_Traits>(__first2, __last2)); }

template <class _InputIter, class _CharT, class _Traits>
inline _InputIter __str_find_first_not_of(_InputIter __first1, _InputIter __last1,
                                          const _CharT* __first2, const _CharT* __last2,
                                          _Traits* __traits) {
#if !defined (__BORLANDC__)
  // typedef typename _IsSTLportClass<_Traits>::_Ret _STLportTraits;
#else
  // enum { _Is = _IsSTLportClass<_Traits>::_Is };
  // typedef typename __bool2type<_Is>::_Ret _STLportTraits;
#endif
  return __str_find_first_not_of_aux1(__first1, __last1, __first2, __last2, __traits, true_type() /* _STLportTraits() */ );
}

_STLP_MOVE_TO_STD_NAMESPACE

// ------------------------------------------------------------
// Non-inline declarations.

// Change the string's capacity so that it is large enough to hold
//  at least __res_arg elements, plus the terminating _CharT().  Note that,
//  if __res_arg < capacity(), this member function may actually decrease
//  the string's capacity.
template <class _CharT, class _Traits, class _Alloc>
void basic_string<_CharT,_Traits,_Alloc>::reserve(size_type __res_arg) {
  if (__res_arg > max_size())
    this->_M_throw_length_error();

  size_type __n = (max)(__res_arg, size()) + 1;
  if (__n < this->_M_capacity())
    return;

  _M_reserve(__n);
}

template <class _CharT, class _Traits, class _Alloc>
void basic_string<_CharT,_Traits,_Alloc>::_M_reserve(size_type __n)
{
  pointer __new_start = this->_M_alloc.allocate(__n+1);
  _STLP_PRIV __ucopy(this->_M_Start(), this->_M_Finish(), __new_start);
  _M_deallocate_block();
  _M_buf._M_start = __new_start;
  _M_cap = __n;
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT,_Traits,_Alloc>&
basic_string<_CharT,_Traits,_Alloc>::append(size_type __n, _CharT __c) {
  if (__n > 0) {
    if (__n > max_size() - size())
      this->_M_throw_length_error();
    if (__n >= this->_M_rest())
      _M_reserve(_M_compute_next_size(__n));
    _STLP_PRIV __uninitialized_fill_n(this->_M_Finish(), __n, __c);
    _Eos(_M_size + __n);
  }
  return *this;
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT, _Traits, _Alloc>&
basic_string<_CharT, _Traits, _Alloc>::_M_append(const _CharT* __first, const _CharT* __last)
{
  if (__first < __last) {
    size_type __n = __STATIC_CAST(size_type, __last - __first);
    if (__n >= this->_M_rest()) {
      if (_M_size + __n >= _DEFAULT_SIZE)
	  {
	    size_type __len = _M_compute_next_size(__n);
	    _M_reserve(__len);
	  }
    }
    _STLP_PRIV __ucopy(__first, __last, this->_M_Finish());
    _Eos(_M_size + __n);  
  }
  return *this;
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT,_Traits,_Alloc>&
basic_string<_CharT,_Traits,_Alloc>::assign(size_type __n, _CharT __c) {
  if (__n <= size()) {
    _Traits::assign(this->_M_Start(), __n, __c);
    erase(begin() + __n, end());
  }
  else {
    if (__n < capacity()) {
      _Traits::assign(this->_M_Start(), size(), __c);
      append(__n - size(), __c);
    }
    else {
      _Self __str(__n, __c);
      this->swap(__str);
    }
  }
  return *this;
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT,_Traits,_Alloc>&
basic_string<_CharT,_Traits,_Alloc>::_M_assign(const _CharT* __f, const _CharT* __l) {
  ptrdiff_t __n = __l - __f;

  if (__n > (ptrdiff_t)capacity()) {
    size_t __newsize= _M_compute_next_size(__n-_M_size);
    _Grow(__newsize);
  }
  else {
    if (__n  < _DEFAULT_SIZE) {
      _Tidy(true);
    } 
  }
  _Traits::copy(this->_M_Start(), __f, __n);
  _Eos(__n);
  return *this;
}


template <class _CharT, class _Traits, class _Alloc>
void basic_string<_CharT,_Traits,_Alloc>::insert(const_iterator_param __pos, size_t __n, _CharT __c)
{
  if (__n != 0) {
    size_t __npos = &*__pos - _M_Start();

    if (this->_M_rest() < __n) {
	_Grow(__n - _M_rest());
    }    
    pointer __p = _M_Start()+__npos;    

    const size_type __elems_after = this->_M_Finish() - __p;
    pointer __old_finish = this->_M_Finish() + 1;
    if (__elems_after >= __n) {
      _STLP_PRIV __ucopy((this->_M_Finish() - __n) + 1, __old_finish, __old_finish);
      _Traits::move(__p + __n, __p, (__elems_after - __n) + 1);
      _Traits::assign(__p, __n, __c);
    } else {
      _STLP_PRIV __uninitialized_fill_n(__old_finish, __n - __elems_after - 1, __c);
      _STLP_PRIV __ucopy(__p, __old_finish, __old_finish + __n - __elems_after-1);
      _Traits::assign(__p, __elems_after + 1, __c);
    }
    _Eos(_M_size + __n);
  }
}

template <class _CharT, class _Traits, class _Alloc>
void basic_string<_CharT,_Traits,_Alloc>::_M_insert(const_iterator __pos,
                                                    const _CharT* __first, const _CharT* __last,
                                                    bool __self_ref)
{
  //this version has to take care about the auto referencing
  if (__first <  __last) {
    const size_t __n = __last - __first;
    // memorize position before grow
    size_t __npos = &*__pos - _M_Start();
 
    if (this->_M_rest() < __n) {
      if (__self_ref) {
	size_t __fpos = __first - _M_Start();	
	_Grow(__n - _M_rest());
	__first = _M_Start()+__fpos;
	__last  = __first + __n;
      } else {
	_Grow(__n - _M_rest());
      }
    }    
    pointer __p = _M_Start()+__npos;    
    
    const size_t __elems_after = this->_M_Finish() - __p;
    if (__elems_after >= __n) {
      _STLP_PRIV __ucopy((this->_M_Finish() - __n) + 1, this->_M_Finish() + 1, this->_M_Finish() + 1);
      _Traits::move(__p + __n, __p, (__elems_after - __n) + 1);
      if (!__self_ref || __last < __p) {
	_M_copy(__first, __last, __p);
      } else {
	//We have to check that the source buffer hasn't move
	if (__first >= __p) {
	  //The source buffer has move
	  __first += __n;
	  __last += __n;
	  _M_copy(__first, __last, __p);
	} else {
	  //The source buffer hasn't move, it has been duplicated
	  _M_move(__first, __last, __p);
	}
      }
    } else {
      pointer __old_finish = this->_M_Finish();
      const _CharT* __mid = __first + __elems_after + 1;
      _STLP_PRIV __ucopy(__mid, __last, __old_finish+1);
      _STLP_PRIV __ucopy(__p, __old_finish+1, __old_finish +__n - __elems_after);
      if (!__self_ref) {
	_M_copy(__first, __mid, __p);
      } else {
	_M_move(__first, __mid, __p);
      }
    }
    _Eos(_M_size + __n);
  }
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT,_Traits,_Alloc>&
basic_string<_CharT,_Traits,_Alloc> ::replace(const_iterator_param __first, 
					      const_iterator_param __last,
                                              size_type __n, _CharT __c) {
  size_type __len = (size_type)(__last - __first);
  pointer __f = const_cast<_CharT*>(&*__first);

  if (__len >= __n) {
    _Traits::assign(__f, __n, __c);
    erase(__first + __n, __last);
  }
  else {
    _Traits::assign(__f, __len, __c);
    insert(__last, __n - __len, __c);
  }
  return *this;
}


template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT,_Traits,_Alloc>&
basic_string<_CharT,_Traits,_Alloc> ::_M_replace(const_iterator_param __first, 
						 const_iterator_param __last,
                                                 const _CharT* __f, const _CharT* __l,
                                                 bool __self_ref) {
  const ptrdiff_t       __n = __l - __f;
  const difference_type __len = __last - __first;
  pointer __fst = const_cast<_CharT*>(&*__first);

  if (__len >= __n) {
    if (!__self_ref || __l < __fst || __f >= &*__last)
      _M_copy(__f, __l, __fst);
    else
      _M_move(__f, __l, __fst);
    erase(__first + __n, __last);
  } else if (!__self_ref || (__f >= &*__last) || (__l <= __fst)) { // no overlap
    const_pointer __m = __f + __len;
    _M_copy(__f, __m, __fst);
    _M_insert(__last, __m, __l, __self_ref );
  } else if (__f < __fst) { // we have to take care of overlaping
    const_pointer __m = __f + __len;
    // We have to deal with possible reallocation because we do insert first.
    const difference_type __off_dest = __first - this->begin();
    const difference_type __off_src = __f - this->_M_Start();
    _M_insert(__last, __m, __l, true);
    _Traits::move(this->_M_Start() + __off_dest, this->_M_Start() + __off_src, __len);
  } else {
    const_pointer __m = __f + __len;
    _Traits::move(__fst, __f, __len);
    _M_insert(&*__last, __m, __l, true);
  }
  return *this;
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__ basic_string<_CharT,_Traits,_Alloc>::find( const _CharT* __s, size_type __pos,
                                                         size_type __n) const
{
  const size_t __len = size();
  if (__pos >= __len || __pos + __n > __len) {
    if ( __n == 0 && __pos <= __len ) { // marginal case
      return __pos;
    }
    return npos;
  }

  const_pointer __result =
    _STLP_STD::search(this->_M_Start() + __pos, this->_M_Finish(),
                      __s, __s + __n, _STLP_PRIV _Eq_traits<_Traits>());
  return __result != this->_M_Finish() ? __result - this->_M_Start() : npos;
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__ basic_string<_CharT,_Traits,_Alloc>::find(_CharT __c, size_type __pos) const
{
  if (__pos >= size()) { /*__pos + 1 > size()*/
    return npos;
  }

  const_pointer __result =
    _STLP_STD::find_if(this->_M_Start() + __pos, this->_M_Finish(),
                       _STLP_PRIV _Eq_char_bound<_Traits>(__c));
  return __result != this->_M_Finish() ? __result - this->_M_Start() : npos;
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__ basic_string<_CharT,_Traits,_Alloc>::rfind(const _CharT* __s, size_type __pos,
                                                         size_type __n) const
{
  const size_type __len = size();
  if ( __len < __n ) {
    return npos;
  }
  const_pointer __last = this->_M_Start() + (min)( __len - __n, __pos) + __n;
  if ( __n == 0 ) { // marginal case
    return __last - this->_M_Start();
  }
  const_pointer __result = _STLP_STD::find_end(this->_M_Start(), __last,
                                               __s, __s + __n, _STLP_PRIV _Eq_traits<_Traits>());
  return __result != __last ? __result - this->_M_Start() : npos;
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__ basic_string<_CharT,_Traits,_Alloc>::rfind(_CharT __c, size_type __pos) const
{
  const size_type __len = size();
  if ( __len < 1 ) {
    return npos;
  }
  const_iterator __last = begin() + (min)(__len - 1, __pos) + 1;
  const_reverse_iterator __rresult =
    _STLP_STD::find_if(const_reverse_iterator(__last), rend(),
                       _STLP_PRIV _Eq_char_bound<_Traits>(__c));
  return __rresult != rend() ? (__rresult.base() - 1) - begin() : npos;
}

template <class _CharT, class _Traits, class _Alloc> __size_type__
basic_string<_CharT,_Traits,_Alloc> ::find_first_of(const _CharT* __s, size_type __pos,
                                                    size_type __n) const {
  if (__pos >= size()) /*__pos + 1 > size()*/
    return npos;
  else {
    const_iterator __result = _STLP_PRIV __str_find_first_of(begin() + __pos, end(),
                                                             __s, __s + __n,
                                                             __STATIC_CAST(_Traits*, 0));
    return __result != end() ? __result - begin() : npos;
  }
}

template <class _CharT, class _Traits, class _Alloc>
 __size_type__
basic_string<_CharT,_Traits,_Alloc> ::find_last_of(const _CharT* __s, size_type __pos,
                                                   size_type __n) const
{
  const size_type __len = size();
  if ( __len < 1 ) {
    return npos;
  }
  const const_iterator __last = begin() + (min)(__len - 1, __pos) + 1;
  const const_reverse_iterator __rresult =
    _STLP_PRIV __str_find_first_of(const_reverse_iterator(__last), rend(),
                                   __s, __s + __n,
                                   __STATIC_CAST(_Traits*, 0));
  return __rresult != rend() ? (__rresult.base() - 1) - begin() : npos;
}


template <class _CharT, class _Traits, class _Alloc> __size_type__
basic_string<_CharT,_Traits,_Alloc> ::find_first_not_of(const _CharT* __s, size_type __pos,
                                                        size_type __n) const {
  typedef typename _Traits::char_type _CharType;
  if (__pos >= size()) /*__pos + 1 >= size()*/
    return npos;
  else {
    const_pointer __result = _STLP_PRIV __str_find_first_not_of(this->_M_Start() + __pos, this->_M_Finish(),
                                                                __STATIC_CAST(const _CharType*, __s),
                                                                __STATIC_CAST(const _CharType*, __s) + __n,
                                                                __STATIC_CAST(_Traits*, 0));
    return __result != this->_M_Finish() ? __result - this->_M_Start() : npos;
  }
}

template <class _CharT, class _Traits, class _Alloc> __size_type__
basic_string<_CharT,_Traits,_Alloc> ::find_first_not_of(_CharT __c, size_type __pos) const {
  if (1 > size())
    return npos;
  else {
    const_pointer __result = _STLP_STD::find_if(this->_M_Start() + __pos, this->_M_Finish(),
                                                _STLP_PRIV _Neq_char_bound<_Traits>(__c));
    return __result != this->_M_Finish() ? __result - this->_M_Start() : npos;
  }
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__
basic_string<_CharT,_Traits,_Alloc>::find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const
{
  typedef typename _Traits::char_type _CharType;
  const size_type __len = size();
  if ( __len < 1 ) {
    return npos;
  }
  const_iterator __last = begin() + (min)(__len - 1, __pos) + 1;
  const_reverse_iterator __rlast = const_reverse_iterator(__last);
  const_reverse_iterator __rresult =
    _STLP_PRIV __str_find_first_not_of(__rlast, rend(),
                                       __STATIC_CAST(const _CharType*, __s),
                                       __STATIC_CAST(const _CharType*, __s) + __n,
                                       __STATIC_CAST(_Traits*, 0));
  return __rresult != rend() ? (__rresult.base() - 1) - begin() : npos;
}

template <class _CharT, class _Traits, class _Alloc>
__size_type__
basic_string<_CharT, _Traits, _Alloc>::find_last_not_of(_CharT __c, size_type __pos) const
{
  const size_type __len = size();
  if ( __len < 1 ) {
    return npos;
  }
  const_iterator __last = begin() + (min)(__len - 1, __pos) + 1;
  const_reverse_iterator __rlast = const_reverse_iterator(__last);
  const_reverse_iterator __rresult =
    _STLP_STD::find_if(__rlast, rend(),
                       _STLP_PRIV _Neq_char_bound<_Traits>(__c));
  return __rresult != rend() ? (__rresult.base() - 1) - begin() : npos;
}

template <class _CharT, class _Traits, class _Alloc>
void _STLP_CALL _S_string_copy(const basic_string<_CharT,_Traits,_Alloc>& __s,
                               _CharT* __buf, size_t __n) {
  if (__n > 0) {
    __n = (min) (__n - 1, __s.size());
    _STLP_STD::copy(__s.begin(), __s.begin() + __n, __buf);
    __buf[__n] = _CharT();
  }
}

_STLP_END_NAMESPACE

#include <stl/_range_errors.h>

_STLP_BEGIN_NAMESPACE

template <class _CharT, class _Traits, class _Alloc>
void basic_string<_CharT, _Traits, _Alloc>::_M_allocate_block(size_t __n) {
  if ((__n <= (max_size())) && (__n >= 0)) {
    if (__n >= _DEFAULT_SIZE) {
      this->_M_buf._M_start = this->_M_alloc.allocate(__n+1);
	  this->_M_cap = __n;
    } else
		this->_M_cap = _DEFAULT_SIZE-1;
    this->_M_size = 0;
   
  } else {
    this->_M_throw_length_error();
  }
}

#if !defined (_STLP_STATIC_CONST_INIT_BUG) && !defined (_STLP_NO_STATIC_CONST_DEFINITION)
template <class _CharT, class _Traits, class _Alloc>
const size_t basic_string<_CharT, _Traits, _Alloc>::npos;
#endif

_STLP_END_NAMESPACE

#undef __size_type__

#endif /*  _STLP_STRING_C */

// Local Variables:
// mode:C++
// End:
