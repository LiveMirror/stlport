/*
 * Copyright (c) 1999-2011
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

#ifndef _STLP_STRING_ITERATOR_H
#define _STLP_STRING_ITERATOR_H

_STLP_BEGIN_NAMESPACE

typedef void* _Cont_base_ptr;

#undef const_iterator_param
#if defined (_MSC_VER) && (_MSC_VER < 1500)
# define const_iterator_param iterator
# define _STLP_NO_CONT  ((void*)-2)
#else
# define _STLP_NO_CONT  ((void*)-4)
# define const_iterator_param const_iterator
#endif

template <class _CharT,
	  class _Traits,
	  class _Alloc>
class _String_iterator;

template <class _CharT, class _Traits, class _Alloc>
class _String_const_iterator
{
public:
  typedef _CharT value_type;
  typedef const _CharT* pointer;
  typedef const _CharT& reference;
  typedef _String_const_iterator<_CharT, _Traits, _Alloc> _Self;
  typedef _String_iterator<_CharT, _Traits, _Alloc> _NonConstSelf;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_category;

  _Cont_base_ptr _M_container; 
  pointer _M_ptr;
  _String_const_iterator(const _CharT* p = 0, _Cont_base_ptr c = _STLP_NO_CONT):
    _M_container(c), _M_ptr(p)
  {
  }

  template <class _Tr, class _Al>
  _String_const_iterator(const _String_const_iterator<_CharT, _Tr, _Al>& __rhs):
    _M_container(_STLP_NO_CONT), _M_ptr(__rhs._M_ptr)
  {
  }

  _String_const_iterator(const _String_iterator<_CharT, _Traits, _Alloc>&);

  template <class _Tr, class _Al>
  _String_const_iterator(const _String_iterator<_CharT, _Tr, _Al>&);

  _Self& operator=(const  _Self& __rhs) {
    _M_container = __rhs._M_container;
    _M_ptr = __rhs._M_ptr;
    return *this;
  }

  const _CharT& operator*() const {
    return *_M_ptr;
  }

  _Self& operator++() {
    ++_M_ptr;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    ++_M_ptr;
    return __tmp;
  }
  _Self& operator--() {
    --_M_ptr;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    --_M_ptr;
    return __tmp;
  }
  _Self& operator+=(difference_type __n) {
    _M_ptr+=__n;
    return *this;
  }
  _Self& operator-=(difference_type __n) {
    _M_ptr-=__n;
    return *this;
  }

  difference_type operator-(const _Self & rhs) const {
    return _M_ptr - rhs._M_ptr;
  }
  difference_type operator-(const _NonConstSelf & rhs) const {
    return _M_ptr - rhs._M_ptr;
  }

  _Self operator+(difference_type __n) const {
    _Self __tmp(*this);
    __tmp +=__n;
    return __tmp;
  }
  _Self operator-(difference_type __n) const {
    _Self __tmp(*this);
    __tmp -= __n;
    return __tmp;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }
};

template <class _CharT,	class _Traits, class _Alloc>
inline bool operator == (const _String_const_iterator<_CharT, _Traits, _Alloc>& i1, const _String_const_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr == i2._M_ptr;
}

template <class _CharT,	class _Traits, class _Alloc>
inline bool operator != (const _String_const_iterator<_CharT, _Traits, _Alloc>& i1, const _String_const_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr != i2._M_ptr;
}

template <class _CharT,	class _Traits, class _Alloc>
class _String_iterator
{
public:
  typedef _CharT value_type;
  typedef _CharT* pointer;
  typedef _CharT& reference;
  typedef _String_iterator _Self;
  typedef _String_const_iterator<_CharT, _Traits, _Alloc> _ConstSelf;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag iterator_category;

  _Cont_base_ptr _M_container; 
  pointer _M_ptr;
  _String_iterator(_CharT* p = 0, _Cont_base_ptr c = _STLP_NO_CONT):
    _M_container(c), _M_ptr(p)
  {}

  _Self& operator=(const  _Self& __rhs) {
    _M_container = __rhs._M_container;
    _M_ptr = __rhs._M_ptr;
    return *this;
  }
  reference operator*() const
  {
    return *_M_ptr;
  }

  _Self& operator++() {
    ++_M_ptr;
    return *this;
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    ++_M_ptr;
    return __tmp;
  }
  _Self& operator--() {
    --_M_ptr;
    return *this;
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    --_M_ptr;
    return __tmp;
  }
  _Self& operator+=(difference_type __n) {
    _M_ptr+=__n;
    return *this;
  }
  _Self& operator-=(difference_type __n) {
    _M_ptr-=__n;
    return *this;
  }
  difference_type operator-(const _Self & rhs) const {
    return _M_ptr - rhs._M_ptr;
  }
  difference_type operator-(const _ConstSelf & rhs) const {
    return _M_ptr - rhs._M_ptr;
  }
  _Self operator+(difference_type __n) const {
    _Self __tmp(*this);
    __tmp +=__n;
    return __tmp;
  }
  _Self operator-(difference_type __n) const {
    _Self __tmp(*this);
    __tmp-=__n;
    return __tmp;
  }
  reference operator[](difference_type __n) const { return *(*this + __n); }
};

template <class _CharT,	class _Traits, class _Alloc>
_String_const_iterator<_CharT, _Traits, _Alloc>::_String_const_iterator(const _String_iterator<_CharT, _Traits, _Alloc>& __rhs): 
  _M_container(__rhs._M_container), _M_ptr(__rhs._M_ptr)
{
}

template <class _CharT, class _Traits, class _Alloc>
template <class _Tr, class _Al>
_String_const_iterator<_CharT, _Traits, _Alloc>::_String_const_iterator(const _String_iterator<_CharT, _Tr, _Al>& __rhs): 
  _M_container(__rhs._M_container), _M_ptr(__rhs._M_ptr)
{
}

template <class _CharT,	class _Traits, class _Alloc>
inline bool operator == (const _String_iterator<_CharT, _Traits, _Alloc>& i1, const _String_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr == i2._M_ptr;
}

template <class _CharT, class _Traits, class _Alloc>
inline bool operator != (const _String_iterator<_CharT, _Traits, _Alloc>& i1, const _String_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr != i2._M_ptr;
}

_STLP_END_NAMESPACE

#endif
