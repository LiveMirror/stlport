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

#ifndef _STLP_INTERNAL_STRING_H
#define _STLP_INTERNAL_STRING_H

#ifndef _STLP_INTERNAL_ALLOC_H
#  include <stl/_alloc.h>
#endif

#ifndef _STLP_STRING_FWD_H
#  include <stl/_string_fwd.h>
#endif

#ifndef _STLP_INTERNAL_FUNCTION_BASE_H
#  include <stl/_function_base.h>
#endif

#ifndef _STLP_INTERNAL_ALGOBASE_H
#  include <stl/_algobase.h>
#endif

#ifndef _STLP_INTERNAL_ITERATOR_H
#  include <stl/_iterator.h>
#endif

#ifndef _STLP_INTERNAL_UNINITIALIZED_H
#  include <stl/_uninitialized.h>
#endif

#if defined (_STLP_USE_TEMPLATE_EXPRESSION)
#  include <stl/_string_sum.h>
#endif /* _STLP_USE_TEMPLATE_EXPRESSION */

#include <cstdio>
#include <cstddef>

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
# include <stl/_string_iterator.h>
#endif

_STLP_BEGIN_NAMESPACE


// Class invariants:
// (1) [start, finish) is a valid range.
// (2) Each iterator in [start, finish) points to a valid object
//     of type value_type.
// (3) *finish is a valid object of type value_type; when
//     value_type is not a POD it is value_type().
// (4) [finish + 1, end_of_storage) is a valid range.
// (5) Each iterator in [finish + 1, end_of_storage) points to
//     unininitialized memory.

// Note one important consequence: a string of length n must manage
// a block of memory whose size is at least n + 1.

#if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#  define basic_string _STLP_NO_MEM_T_NAME(str)
#elif defined (_STLP_DEBUG)
#  define basic_string _STLP_NON_DBG_NAME(str)
#endif

#if defined (basic_string)
_STLP_MOVE_TO_PRIV_NAMESPACE
#endif

struct _String_reserve_t {};

#if defined (__DMC__)
#  define _STLP_PRIVATE public
#elif defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#  define _STLP_PRIVATE protected
#else
#  define _STLP_PRIVATE private
#endif

# define const_iterator_param const_iterator

class _STLP_DECLSPEC _String_base
{
public:
 static void _STLP_CALL _Xran();
 static void _STLP_CALL _Xlen();
 inline void _M_throw_length_error() const { _Xlen(); }
 inline void _M_throw_out_of_range() const { _Xran(); }
};

template <class _Tp, class _Alloc>
class _String_val : public _String_base
{
  typedef _String_val<_Tp, _Alloc> _Self;
  public:
  //This is needed by the full move framework
  typedef _Alloc allocator_type;
  typedef size_t size_type;

protected:  
  _String_val() : _M_alloc(allocator_type()) {}
  _String_val(allocator_type __a) : _M_alloc(__a) {}
  allocator_type _M_alloc;
};

// ------------------------------------------------------------
// Class basic_string.

template <class _CharT, class _Traits, class _Alloc>
class basic_string : public _String_val<_CharT,_Alloc>
{
  typedef _String_val<_CharT,_Alloc> _Base;
  typedef basic_string<_CharT, _Traits, _Alloc> _Self;

public:
  typedef _CharT value_type;
  typedef _Traits traits_type;

  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef typename _Base::size_type size_type;
  typedef ptrdiff_t difference_type;
  typedef random_access_iterator_tag _Iterator_category;
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  // Iterators.
  typedef _String_const_iterator<_CharT, _Traits, _Alloc> const_iterator;
  typedef _String_iterator<_CharT, _Traits, _Alloc>             iterator;
#else
  typedef const value_type* const_iterator;
  typedef value_type*       iterator;
#endif  
  typedef _STLP_STD::reverse_iterator<iterator> reverse_iterator;
  typedef _STLP_STD::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename _Base::allocator_type allocator_type;
  
  iterator begin() { return iterator(this->_M_Start()); }
  const_iterator begin() const { return const_iterator(this->_M_Start()); }
  iterator end() { return iterator(this->_M_Finish()); }
  const_iterator end() const { return const_iterator(this->_M_Finish()); }  
  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }
  typedef _String_reserve_t _Reserve_t;

public:                         // Constructor, destructor, assignment.
  basic_string(const allocator_type& __a, size_t __n) : _Base(__a) { _M_allocate_block(__n); _M_terminate_string(); }
#if !defined (_STLP_NO_MOVE_SEMANTIC)
  basic_string(__move_source<_Self> src) : _Base(src.get().get_allocator()) { _M_allocate_block(); _M_swap(src.get()); }
#endif
  ~basic_string()  {  _M_deallocate_block(); }
  basic_string(): _Base(allocator_type()) { _M_allocate_block(); _M_terminate_string(); }
  explicit basic_string(const allocator_type& __a) : _Base(__a) { _M_allocate_block(); _M_terminate_string(); }
  basic_string(_Reserve_t, size_t __n) : _Base(allocator_type()) { _M_allocate_block(__n); _M_terminate_string(); }
  basic_string(_Reserve_t, size_t __n, const allocator_type& __a) : _Base(__a) { _M_allocate_block(__n); _M_terminate_string(); }
  basic_string(const _Self& __s): _Base(__s.get_allocator()) { _M_range_initialize(__s._M_Start(), __s._M_Finish()); }  
  basic_string(const _Self& __s, size_type __pos) : _Base(allocator_type()) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos, __s._M_Finish());
  }
  basic_string(const _Self& __s, size_type __pos, size_type __n) : _Base(allocator_type()) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos,
                          __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }
  basic_string(const _Self& __s, size_type __pos, size_type __n, const allocator_type& __a): _Base(__a) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos,
                          __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }
  basic_string(const _CharT* __s, size_type __n) : _Base(allocator_type()) { _M_range_initialize(__s, __s + __n); }
  basic_string(const _CharT* __s, size_type __n, const allocator_type& __a) : _Base(__a) {    _M_range_initialize(__s, __s + __n); }
  basic_string(_CharT const* __s): _Base(allocator_type()) { _M_range_initialize(__s, __s + traits_type::length(__s)); }
  basic_string(const _CharT* __s, const allocator_type& __a)  :  _Base(__a) { _M_range_initialize(__s, __s + traits_type::length(__s)); }
  basic_string(size_type __n, _CharT __c): _Base(allocator_type()) {
    _M_allocate_block(__n);
    _Traits::assign(this->_M_Start(), __n, __c);
    _Eos(__n);
  }
  basic_string(size_type __n, _CharT __c, const allocator_type& __a)    : _Base(__a) {
    _Traits::assign(this->_M_Start(), __n, __c);
    _Eos(__n);
  }
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l, const allocator_type & __a _STLP_ALLOCATOR_TYPE_DFL) : _Base(__a) {
    typedef typename is_integral<_InputIterator>::type _Integral;
    _M_initialize_dispatch(__f, __l, _Integral());
  }
  _Self& operator=(const _Self& __s) {
    if (&__s != this)
      _M_assign(__s._M_Start(), __s._M_Finish());
    return *this;
  }
  _Self& operator=(const _CharT* __s) { return _M_assign(__s, __s + traits_type::length(__s)); }
  _Self& operator=(_CharT __c) {  return assign(__STATIC_CAST(size_type,1), __c); }
  allocator_type get_allocator() const { return this->_M_alloc; }
  
public:                         // Size, capacity, etc.
  size_type size() const     { return _M_size; }
  size_type length() const   { return _M_size; }
  void resize(size_type __n, _CharT __c) {
    if (__n <= size())
      erase(begin() + __n, end());
    else
      append(__n - size(), __c);
  }
  void resize(size_type __n) { resize(__n, _M_null()); }
  size_t max_size() const {
    const size_type __string_max_size = size_type(-1) / sizeof(_CharT);
    typename allocator_type::size_type __alloc_max_size = this->_M_alloc.max_size();
    return (min)(__alloc_max_size, __string_max_size) - 1;
  }
  void reserve(size_type = 0);
  size_type capacity() const  { return this->_M_cap - 1; }
  void clear() { if (!empty()) _Tidy(0); }
  bool empty() const { return this->_M_size == 0; }

public:                         // Element access.
  const_reference operator[](size_type __n) const  { return *(this->_M_Start() + __n); }
  reference operator[](size_type __n) { return *(this->_M_Start() + __n); }  
  const_reference at(size_type __n) const {
    if (__n >= size())
      this->_M_throw_out_of_range();
    return *(this->_M_Start() + __n);
  }
  reference at(size_type __n) {
    if (__n >= size())
      this->_M_throw_out_of_range();
    return *(this->_M_Start() + __n);
  }

  template <class _InputIter>
  _Self& append(_InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_append_dispatch(__first, __last, _Integral());
  }
  _Self& append(const _Self& __s) { return _M_append(__s._M_Start(), __s._M_Finish()); }
  _Self& append(const _Self& __s, size_type __pos, size_type __n) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    return _M_append(__s._M_Start() + __pos,
                     __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }
  _Self& append(const _CharT* __s, size_type __n) { return _M_append(__s, __s+__n); }
  _Self& append(const _CharT* __s) { return _M_append(__s, __s + traits_type::length(__s)); }
  _Self& append(size_type __n, _CharT __c);

  void push_back(_CharT __c) {
    if (this->_M_rest() <= 1 )
      _M_reserve(_M_compute_next_size(1));
    _Traits::assign(*(this->_M_Finish()), __c);
    _M_size++;
    _M_terminate_string();
  }
  void pop_back() {    _Grow(_M_size-1, true); _Eos(_M_size); }

  _Self& assign(const _Self& __s) { return _M_assign(__s._M_Start(), __s._M_Finish()); }
  _Self& assign(const _Self& __s, size_type __pos, size_type __n) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    return _M_assign(__s._M_Start() + __pos,
                     __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }  
  _Self& assign(const _CharT* __s, size_type __n) { return _M_assign(__s, __s + __n); }
  _Self& assign(const _CharT* __s) { return _M_assign(__s, __s + _Traits::length(__s)); }
  _Self& assign(const _CharT* __s1, const _CharT* __s2) { return _M_assign(__s1, __s2); }
  _Self& assign(const_iterator __s1, const_iterator __s2) { return _M_assign(__s1._M_ptr, __s2._M_ptr); }
  _Self& assign(size_type __n, _CharT __c);
  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& assign(_InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_assign_dispatch(__first, __last, _Integral());
  }

  _Self& insert(size_type __pos, const _Self& __s) {
    if (__pos > size())
      this->_M_throw_out_of_range();
    if (__s.size() > max_size() - size())
      this->_M_throw_length_error();
    _M_insert(begin() + __pos, __s._M_Start(), __s._M_Finish(), &__s == this);
    return *this;
  }
  _Self& insert(size_type __pos, const _Self& __s, size_type __beg, size_type __n) {
    if (__pos > size() || __beg > __s.size())
      this->_M_throw_out_of_range();
    size_type __len = (min) (__n, __s.size() - __beg);
    if (__len > max_size() - size())
      this->_M_throw_length_error();
    _M_insert(begin() + __pos,
              __s._M_Start() + __beg, __s._M_Start() + __beg + __len, &__s == this);
    return *this;
  }
  _Self& insert(size_type __pos, const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    if (__pos > size())
      this->_M_throw_out_of_range();
    if (__n > max_size() - size())
      this->_M_throw_length_error();
    _M_insert(begin() + __pos, __s, __s + __n, _Inside(__s));
    return *this;
  }
  _Self& insert(size_type __pos, const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    if (__pos > size())
      this->_M_throw_out_of_range();
    size_type __len = _Traits::length(__s);
    if (__len > max_size() - size())
      this->_M_throw_length_error();
    _M_insert(this->_M_Start() + __pos, __s, __s + __len, _Inside(__s));
    return *this;
  }
  _Self& insert(size_type __pos, size_type __n, _CharT __c) {
    if (__pos > size())
      this->_M_throw_out_of_range();
    if (__n > max_size() - size())
      this->_M_throw_length_error();
    insert(begin() + __pos, __n, __c);
    return *this;
  }
  iterator insert(const_iterator_param __p, _CharT __c) {
    if (&*__p == this->_M_Finish()) {
      push_back(__c);
      return this->_M_Finish() - 1;
    } else {
      size_t __pos(&*__p - _M_Start());
      insert(__pos, 1, __c);
      return _M_Start() + __pos;
    }
  }
  void insert(const_iterator_param __p, size_t __n, _CharT __c);
  void insert(const_iterator_param __p, const_iterator __first, const_iterator __last) {
    _M_insert(__p, &*__first, &*__last, _Inside(&*__first));
  }
  template <class _InputIter>
  void insert(const_iterator_param __p, _InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    _M_insert_dispatch(__p, __first, __last, _Integral());
  }

  _Self& erase(size_type __pos = 0, size_type __n = npos) {
    if (__pos > size())
      this->_M_throw_out_of_range();
    erase(begin() + __pos, begin() + __pos + (min) (__n, size() - __pos));
    return *this;
  }
  iterator erase(const_iterator_param __pos) {
    pointer __p(const_cast<_CharT*>(&*__pos));
    // The move includes the terminating _CharT().
    _Traits::move(__p, 
		  &*__pos + 1, this->_M_Finish() - &*__pos);
    _M_size--;
    return __p;
  }
  iterator erase(const_iterator_param __first, const_iterator_param __last) {
    pointer __f(const_cast<_CharT*>(&*__first));
    if (__first != __last) {
      // The move includes the terminating _CharT().
      traits_type::move(__f,
			&*__last, (this->_M_Finish() - &*__last) + 1);
      _M_size -= (__last - __first);
    }
    return __f;
  }

  _Self& replace(size_type __pos, size_type __n, const _Self& __s) {
    const size_type __size = size();
    if (__pos > __size)
      this->_M_throw_out_of_range();
    const size_type __len = (min) (__n, __size - __pos);
    if (__s.size() > max_size() - (__size - __len))
      this->_M_throw_length_error();
    return _M_replace(begin() + __pos, begin() + __pos + __len,
                      __s._M_Start(), __s._M_Finish(), &__s == this);
  }
  _Self& replace(size_type __pos1, size_type __n1, const _Self& __s, size_type __pos2, size_type __n2) {
    const size_type __size1 = size();
    const size_type __size2 = __s.size();
    if (__pos1 > __size1 || __pos2 > __size2)
      this->_M_throw_out_of_range();
    const size_type __len1 = (min) (__n1, __size1 - __pos1);
    const size_type __len2 = (min) (__n2, __size2 - __pos2);
    if (__len2 > max_size() - (__size1 - __len1))
      this->_M_throw_length_error();
    return _M_replace(begin() + __pos1, begin() + __pos1 + __len1,
                      __s._M_Start() + __pos2, __s._M_Start() + __pos2 + __len2, &__s == this);
  }
  _Self& replace(size_type __pos, size_type __n1, const _CharT* __s, size_type __n2) {
    _STLP_FIX_LITERAL_BUG(__s)
    const size_type __size = size();
    if (__pos > __size)
      this->_M_throw_out_of_range();
    const size_type __len = (min) (__n1, __size - __pos);
    if (__n2 > max_size() - (__size - __len))
      this->_M_throw_length_error();
    return _M_replace(begin() + __pos, begin() + __pos + __len,
                      __s, __s + __n2, _Inside(__s));
  }
  _Self& replace(size_type __pos, size_type __n1, const _CharT* __s) {
    return replace(__pos, __n1, __s, _Traits::length(__s));
  }
  _Self& replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c) {
    const size_type __size = size();
    if (__pos > __size)
      this->_M_throw_out_of_range();
    const size_type __len = (min) (__n1, __size - __pos);
    if (__n2 > max_size() - (__size - __len))
      this->_M_throw_length_error();
    return replace(begin() + __pos, begin() + __pos + __len, __n2, __c);
  }
  _Self& replace(const_iterator_param __first, const_iterator_param __last, const _Self& __s) {
    return _M_replace(__first, __last, __s._M_Start(), __s._M_Finish(), &__s == this);
  }
  _Self& replace(const_iterator_param __first, const_iterator_param __last, const _CharT* __s, size_type __n) {
    return _M_replace(__first, __last, __s, __s + __n, _Inside(__s));
  }
  _Self& replace(const_iterator_param __first, const_iterator_param __last, const _CharT* __s) {
    return _M_replace(__first, __last, __s, __s + _Traits::length(__s), _Inside(__s));
  }
  _Self& replace(const_iterator_param __first, const_iterator_param __last, size_type __n, _CharT __c);
  template <class _InputIter>
  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 _InputIter __f, _InputIter __l) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_replace_dispatch(__first, __last, __f, __l,  _Integral());
  }
  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 const_iterator __f, const_iterator __l) {
    return _M_replace(&*__first, &*__last, &*__f, &*__l, _Inside(&*__f));
  }
  
  _Self& operator+=(const _Self& __s) { return append(__s); }
  _Self& operator+=(const _CharT* __s) { return append(__s); }
  _Self& operator+=(_CharT __c) { push_back(__c); return *this; }

  size_type copy(_CharT* __s, size_type __n, size_type __pos = 0) const {
    if (__pos > size())
      this->_M_throw_out_of_range();
    const size_type __len = (min) (__n, size() - __pos);
    _Traits::copy(__s, this->_M_Start() + __pos, __len);
    return __len;
  }

  void swap(_Self& __s) { if (this!=&__s) this->_M_swap(__s); }

#if defined (_STLP_USE_PARTIAL_SPEC_WORKAROUND) && !defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
  void _M_swap_workaround(_Self& __x) { swap(__x); }
#endif

  const _CharT* c_str() const { return this->_M_Start(); }
  const _CharT* data()  const { return this->_M_Start(); }

  size_type find(const _Self& __s, size_type __pos = 0) const { return find(__s._M_Start(), __pos, __s.size()); }
  size_type find(const _CharT* __s, size_type __pos = 0) const { return find(__s, __pos, _Traits::length(__s)); }
  size_type find(const _CharT* __s, size_type __pos, size_type __n) const;

  // WIE: Versant schema compiler 5.2.2 ICE workaround
  size_type find(_CharT __c) const { return find(__c, 0); }
  size_type find(_CharT __c, size_type __pos /* = 0 */) const;

  size_type rfind(const _Self& __s, size_type __pos = npos) const  { return rfind(__s._M_Start(), __pos, __s.size()); }
  size_type rfind(const _CharT* __s, size_type __pos = npos) const { return rfind(__s, __pos, _Traits::length(__s)); }
  size_type rfind(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type rfind(_CharT __c, size_type __pos = npos) const;

  size_type find_first_of(const _Self& __s, size_type __pos = 0) const  { return find_first_of(__s._M_Start(), __pos, __s.size()); }
  size_type find_first_of(const _CharT* __s, size_type __pos = 0) const { return find_first_of(__s, __pos, _Traits::length(__s)); }
  size_type find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type find_first_of(_CharT __c, size_type __pos = 0) const { return find(__c, __pos); }

  size_type find_last_of(const _Self& __s, size_type __pos = npos) const { return find_last_of(__s._M_Start(), __pos, __s.size()); }
  size_type find_last_of(const _CharT* __s, size_type __pos = npos) const { return find_last_of(__s, __pos, _Traits::length(__s)); }
  size_type find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type find_last_of(_CharT __c, size_type __pos = npos) const { return rfind(__c, __pos); }

  size_type find_first_not_of(const _Self& __s, size_type __pos = 0) const { return find_first_not_of(__s._M_Start(), __pos, __s.size()); }
  size_type find_first_not_of(const _CharT* __s, size_type __pos = 0) const { return find_first_not_of(__s, __pos, _Traits::length(__s)); }
  size_type find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type find_first_not_of(_CharT __c, size_type __pos = 0) const;

  size_type find_last_not_of(const _Self& __s, size_type __pos = npos) const { return find_last_not_of(__s._M_Start(), __pos, __s.size()); }
  size_type find_last_not_of(const _CharT* __s, size_type __pos = npos) const  { return find_last_not_of(__s, __pos, _Traits::length(__s)); }
  size_type find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type find_last_not_of(_CharT __c, size_type __pos = npos) const;

  _Self substr(size_type __pos = 0, size_type __n = npos) const { return _Self(*this, __pos, __n, get_allocator()); }

  int compare(const _Self& __s) const { return _M_compare(this->_M_Start(), this->_M_Finish(), __s._M_Start(), __s._M_Finish()); }
  int compare(size_type __pos1, size_type __n1, const _Self& __s) const {
    if (__pos1 > size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s._M_Start(), __s._M_Finish());
  }
  int compare(size_type __pos1, size_type __n1, const _Self& __s,
              size_type __pos2, size_type __n2) const {
    if (__pos1 > size() || __pos2 > __s.size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s._M_Start() + __pos2,
                      __s._M_Start() + __pos2 + (min) (__n2, __s.size() - __pos2));
  }
  int compare(const _CharT* __s) const {
    return _M_compare(this->_M_Start(), this->_M_Finish(), __s, __s + _Traits::length(__s));
  }
  int compare(size_type __pos1, size_type __n1, const _CharT* __s) const {
    if (__pos1 > size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s, __s + _Traits::length(__s));
  }
  int compare(size_type __pos1, size_type __n1, const _CharT* __s, size_type __n2) const {
    if (__pos1 > size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s, __s + __n2);
  }
  
#include <stl/_string_npos.h>
  
_STLP_PRIVATE:
protected:
  enum {_DEFAULT_SIZE = 16 / sizeof(_CharT)};
  union _Buffers
  {
    _CharT*  _M_start;
    _CharT   _M_static_buf[_DEFAULT_SIZE];
  } _M_buf;
  
  size_type _M_size;
  size_type _M_cap;
  
  bool _M_using_static_buf() const { return _M_cap < _DEFAULT_SIZE; }
  const _CharT* _M_Start() const   { return _M_using_static_buf() ? _M_buf._M_static_buf : _M_buf._M_start; }
  _CharT* _M_Start()               { return _M_using_static_buf() ? _M_buf._M_static_buf : _M_buf._M_start; }
  const _CharT* _M_End() const     { return _M_Start()+_M_cap; }
  _CharT* _M_End()                 { return _M_Start()+_M_cap; }
  size_type _M_capacity() const    { return _M_cap; }
  size_type _M_rest() const        { return  _M_cap - _M_size; }
  _CharT const* _M_Finish() const  { return _M_Start() + _M_size;}
  _CharT* _M_Finish()              { return _M_Start() + _M_size;}
  
  // Precondition: 0 < __n <= max_size().
  void _M_allocate_block(size_t __n = _DEFAULT_SIZE-1);
  void _M_deallocate_block() {
    if (!_M_using_static_buf()) {
      this->_M_alloc.deallocate(_M_buf._M_start, _M_cap);
      this->_M_cap = _DEFAULT_SIZE-1;
    }
  }
  void _M_swap( _Self& __s ) {
	 if (this->_M_alloc == __s._M_alloc) {	
       _STLP_STD::swap(_M_buf, __s._M_buf);
       _STLP_STD::swap(_M_size, __s._M_size);
	   _STLP_STD::swap(_M_cap, __s._M_cap);
	 }
	 else {
       _Self __tmp(__s);
       __s = *this;
       *this = __tmp;
	 }
  }
  size_type _M_compute_next_size(size_type __n) {
    const size_type __size = size();
    if (__n > max_size() - __size)
      this->_M_throw_length_error();
    size_type __len = __size + (max)(__n, __size);
    if (__len > max_size() || __len < __size)
      __len = max_size(); // overflow
    return __len;
  }
  template <class _InputIter>
  void _M_range_initialize(_InputIter __f, _InputIter __l, const input_iterator_tag &__tag) {
    this->_M_allocate_block();
    _M_terminate_string();
    _M_appendT(__f, __l, __tag);
  }
  template <class _ForwardIter>
  void _M_range_initialize(_ForwardIter __f, _ForwardIter __l, const forward_iterator_tag &) {
    difference_type __n = _STLP_STD::distance(__f, __l);
    this->_M_allocate_block(__n);
    uninitialized_copy(__f, __l, this->_M_Start());
    this->_Eos(__n);
  }
  template <class _Integer>
  void _M_initialize_dispatch(_Integer __n, _Integer __x, const true_type& /*_Integral*/) {
    this->_M_allocate_block(__n);
    __uninitialized_fill_n(this->_M_Start(), __n, __x);
    this->_Eos(__n);
  }
  template <class _InputIter>
  void _M_initialize_dispatch(_InputIter __f, _InputIter __l, const false_type& /*_Integral*/) {
    _M_range_initialize(__f, __l, _STLP_ITERATOR_CATEGORY(__f, _InputIter));
  }

protected:
  void _M_construct_null(pointer __s) const { _STLP_STD::_Construct(__s); }
  void _M_terminate_string()  { _M_construct_null(_M_Start()+_M_size); }
  _CharT* _Myptr() { return _M_Start(); }
  const _CharT* _Myptr() const { return _M_Start(); }
  void _Eos(size_type _NSize)  {
    _M_size=_NSize;
    _M_terminate_string();
  }
  void _Tidy(bool __dealloc, size_type __new_size = 0) {
    if (__dealloc && _M_cap >= _DEFAULT_SIZE) {
      _CharT* __beg = _M_buf._M_start;
      if (__new_size > 0 )
        _Traits::_Copy_s(_M_buf._M_static_buf, _DEFAULT_SIZE, __beg, __new_size);
      this->_M_alloc.deallocate(__beg, _M_cap);
    } 
    _M_cap = _DEFAULT_SIZE - 1;
    _Eos(__new_size);
  }
  bool _Inside(const _CharT* __s) const {
    ptrdiff_t __n = __s - this->_M_Start();
    return __n >=0 && __n < (ptrdiff_t)_M_size;
  }
  bool _Grow(size_type __new_size, bool _Shrink = false) {
    if (_Shrink) {
      if (__new_size < _DEFAULT_SIZE) {
        _Tidy(true, min(__new_size, _M_size));
      } 
    }   else {
      if (_M_cap < __new_size)
        _Copy(__new_size, _M_size);
      else
        if (__new_size==0)
          _Eos(0);
    }
    return __new_size > 0; 
  }
  // this function has a prereq to be only called for non-small strings
  void _Copy(size_type __new_size, size_type __old_size) {  
    _CharT *__ptr = this->_M_alloc.allocate(__new_size+1);
    _Traits::_Copy_s(__ptr, __new_size + 1, _M_Start(), __old_size);
    _Tidy(true);
    _M_buf._M_start = __ptr;
    _M_cap = __new_size;
    _Eos(__old_size);
  }
  void _M_range_initialize(const _CharT* __f, const _CharT* __l) {
    ptrdiff_t __n = __l - __f;
    this->_M_allocate_block(__n);
    _Traits::copy(this->_M_Start(), __f, __n);
    _Eos(__n);
  }

  static _CharT _STLP_CALL _M_null() { return _STLP_DEFAULT_CONSTRUCTED(_CharT); }
  void _M_reserve(size_type);
  _Self& _M_append(const _CharT* __first, const _CharT* __last);
  template <class _InputIter>
  _Self& _M_appendT(_InputIter __first, _InputIter __last, const input_iterator_tag &) {
    for ( ; __first != __last ; ++__first)
      push_back(*__first);
    return *this;
  }  
  template <class _ForwardIter>
  _Self& _M_appendT( _ForwardIter __first, _ForwardIter __last, const forward_iterator_tag& )
  {
    if (__first != __last) {
      size_type __n = __STATIC_CAST(size_type, _STLP_STD::distance(__first, __last));
      if (__n >= this->_M_rest()) {
        if (__n >= _DEFAULT_SIZE) {
          size_type __len = _M_compute_next_size(__n);
          _M_reserve(__len);
        }
      }     
      _Traits::assign(*this->_M_Finish(), *__first++);
      uninitialized_copy(__first, __last, this->_M_Finish() + 1);
      _Eos(_M_size + __n);  
    }
    return *this;
  }
  template <class _Integer>
  _Self& _M_append_dispatch(_Integer __n, _Integer __x, const true_type& /*Integral*/)
  { return append((size_type) __n, (_CharT) __x); }  
  template <class _InputIter>
  _Self& _M_append_dispatch(_InputIter __f, _InputIter __l, const false_type& /*Integral*/)
  { return _M_appendT(__f, __l, _STLP_ITERATOR_CATEGORY(__f, _InputIter)); }
  
  _Self& _M_assign(const _CharT* __f, const _CharT* __l);

  template <class _Integer>
  _Self& _M_assign_dispatch(_Integer __n, _Integer __x, const true_type& /*_Integral*/) { return assign((size_type) __n, (_CharT) __x); }
  template <class _InputIter>
  _Self& _M_assign_dispatch(_InputIter __f, _InputIter __l, const false_type& /*_Integral*/) {
    pointer __cur = this->_M_Start();
    while (__f != __l && __cur != this->_M_Finish()) {
      _Traits::assign(*__cur, *__f);
      ++__f;
      ++__cur;
    }
    if (__f == __l)
      erase(__cur, this->end());
    else
      _M_appendT(__f, __l, _STLP_ITERATOR_CATEGORY(__f, _InputIter));
    return *this;
  }
  void _M_insert(const_iterator __p, const _CharT* __first, const _CharT* __last, bool __self_ref);
  void _M_copy(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _Traits::copy(__res, __f, __l - __f);
  }
  void _M_move(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _Traits::move(__res, __f, __l - __f);
  }
  template <class _InputIter>
  void _M_insertT(const_iterator __p, _InputIter __first, _InputIter __last,
                  const input_iterator_tag &) {
    for ( ; __first != __last; ++__first) {
      __p = insert(__p, *__first);
      ++__p;
    }
  }
  template <class _ForwardIter>
  void _M_insertT(const_iterator __pos, _ForwardIter __first, _ForwardIter __last,
                  const forward_iterator_tag &) 
  {
    const _Self __self(__first, __last, get_allocator());
    _M_insert(__pos, &*__self.begin(), &*__self.end(), false);
  }
  template <class _Integer>
  void _M_insert_dispatch(const_iterator __p, _Integer __n, _Integer __x, const true_type& /*Integral*/) {
    insert(__p, (size_type) __n, (_CharT) __x);
  }  
  template <class _InputIter>
  void _M_insert_dispatch(const_iterator __p, _InputIter __first, _InputIter __last,
                          const false_type& /*Integral*/) {
    _M_insertT(__p, __first, __last, _STLP_ITERATOR_CATEGORY(__f, _InputIter));
  }
  template <class _InputIterator>
  void _M_copyT(_InputIterator __first, _InputIterator __last, pointer __result) {
    for ( ; __first != __last; ++__first, ++__result)
      _Traits::assign(*__result, *__first);
  }
  void _M_copyT(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _Traits::copy(__res, __f, __l - __f);
  }
  _Self& _M_replace(const_iterator_param __first, const_iterator_param __last,
                    const _CharT* __f, const _CharT* __l, bool __self_ref);
  template <class _Integer>
  _Self& _M_replace_dispatch(iterator __first, iterator __last,
                             _Integer __n, _Integer __x, const true_type& /*IsIntegral*/) {
    return replace(__first, __last, (size_type) __n, (_CharT) __x);
  }
  template <class _InputIter>
  _Self& _M_replace_dispatch(const_iterator_param __first, const_iterator_param __last,
                             _InputIter __f, _InputIter __l, const false_type& /*IsIntegral*/) {
    /* We are forced to do a temporary string to avoid the self referencing issue. */
    const _Self __self(__f, __l, get_allocator());
    return _M_replace(__first, __last, __self._M_Start(), __self._M_Finish(), false);
  }

public: // Helper functions for compare.
  static int _STLP_CALL _M_compare(const _CharT* __f1, const _CharT* __l1,
                                   const _CharT* __f2, const _CharT* __l2) {
    const ptrdiff_t __n1 = __l1 - __f1;
    const ptrdiff_t __n2 = __l2 - __f2;
    return (__n1 < __n2 ? -1 : (__n1 > __n2 ? 1 : _Traits::compare(__f1, __f2, (min) (__n1, __n2))));
  }
  
#if defined (_STLP_USE_TEMPLATE_EXPRESSION) && !defined (_STLP_DEBUG) && !defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#  define _STLP_STRING_SUM_BASE(__reserve, __size, __alloc) _STLP_PRIV _String_val<_CharT, _Alloc>(__alloc, __size + 1)
#  include <stl/_string_sum_methods.h>
#  undef _STLP_STRING_SUM_BASE
#endif
};


#undef _STLP_PRIVATE

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS  _String_val<char, allocator<char> >;
_STLP_EXPORT_TEMPLATE_CLASS basic_string<char, char_traits<char>, allocator<char> >;
#  if defined (_STLP_HAS_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >;
#  endif
#endif /* _STLP_USE_TEMPLATE_EXPORT */

#if defined (basic_string)
_STLP_MOVE_TO_STD_NAMESPACE
#  if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
_STLP_BEGIN_TR1_NAMESPACE

#    if !defined (_STLP_USE_SHORT_STRING_OPTIM)
template <class _CharT, class _Traits, class _Alloc>
struct __has_trivial_move<_STLP_PRIV basic_string<_CharT, _Traits, _Alloc> > :
  public integral_constant<bool, is_trivial<_Alloc>::value> /* true_type */
{ };
#    endif

template <class _CharT, class _Traits, class _Alloc>
struct __has_move_constructor<_STLP_PRIV basic_string<_CharT, _Traits, _Alloc> > :
    public true_type
{ };

_STLP_END_NAMESPACE

#  endif
#  undef basic_string

#else // basic_string

#  if defined (_STLP_CLASS_PARTIAL_SPECIALIZATION) && !defined (_STLP_NO_MOVE_SEMANTIC)
_STLP_BEGIN_TR1_NAMESPACE

#    if !defined (_STLP_USE_SHORT_STRING_OPTIM)
template <class _CharT, class _Traits, class _Alloc>
struct __has_trivial_move<basic_string<_CharT, _Traits, _Alloc> > :
  public integral_constant<bool, is_trivial<_Alloc>::value> /* true_type */
{ };
#    endif

template <class _CharT, class _Traits, class _Alloc>
struct __has_move_constructor<basic_string<_CharT, _Traits, _Alloc> > :
    public true_type
{ };

_STLP_END_NAMESPACE

#  endif
#endif // basic_string

_STLP_END_NAMESPACE

#if defined (_STLP_USE_MSVC6_MEM_T_BUG_WORKAROUND)
#  include <stl/_string_workaround.h>
#endif

#if defined (_STLP_DEBUG)
#  include <stl/debug/_string.h>
#endif

_STLP_BEGIN_NAMESPACE

// ------------------------------------------------------------
// Non-member functions.
// Swap.
#if defined (_STLP_FUNCTION_TMPL_PARTIAL_ORDER)
template <class _CharT, class _Traits, class _Alloc>
inline void _STLP_CALL
swap(basic_string<_CharT,_Traits,_Alloc>& __x,
     basic_string<_CharT,_Traits,_Alloc>& __y)
{ __x.swap(__y); }
#else
inline void _STLP_CALL swap(string& __x, string& __y)
{ __x.swap(__y); }
#  if defined (_STLP_HAS_WCHAR_T)
inline void _STLP_CALL swap(wstring& __x, wstring& __y)
{ __x.swap(__y); }
#  endif
#endif

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _CharT, class _Traits, class _Alloc>
void _STLP_CALL _S_string_copy(const basic_string<_CharT,_Traits,_Alloc>& __s,
                               _CharT* __buf, size_t __n);

#if defined(_STLP_USE_WIDE_INTERFACE)
// A couple of functions to transfer between ASCII/Unicode
wstring __ASCIIToWide(const char *ascii);
string __WideToASCII(const wchar_t *wide);
#endif

inline const char* _STLP_CALL
__get_c_string(const string& __str) { return __str.c_str(); }

_STLP_MOVE_TO_STD_NAMESPACE
_STLP_END_NAMESPACE

#ifndef _STLP_INTERNAL_CTRAITS_FUNCTIONS_H
#  include <stl/_ctraits_fns.h>
#endif

#include <stl/_string.c>

#endif /* _STLP_INTERNAL_STRING_H */

/*
 * Local Variables:
 * mode:C++
 * End:
 */
