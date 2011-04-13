/*
 * Copyright (c) 1997-1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999-2011
 * Boris Fomitchev
 *
 * Copyright (c) 2003
 * Francois Dumont
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

#ifndef _STLP_BSTRING_H
#define _STLP_BSTRING_H

#include <cstdio>
#include <cstddef>

#if defined (_MSC_VER) && (_MSC_VER < 1500)
# define const_iterator_param iterator
# define _STLP_NO_CONT  ((void*)-2)
#else
# define _STLP_NO_CONT  ((void*)-4)
# define const_iterator_param const_iterator
#endif

_STLP_BEGIN_NAMESPACE

class _STLP_DECLSPEC _String_base
{
public:
 static void _STLP_CALL _Xran();
 static void _STLP_CALL _Xlen();

inline void _M_throw_length_error() const
  { _Xlen(); }

inline void _M_throw_out_of_range() const
  { _Xran(); }

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
  _String_val() : _M_alloc(allocator_type())
  { }

  _String_val(allocator_type __a) : _M_alloc(__a)
  { }
  
protected:

  allocator_type _M_alloc;
};

// ------------------------------------------------------------
// Class basic_string.

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


typedef void* _Cont_base_ptr;

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 

template <class _CharT,
	  class _Traits,
	  class _Alloc>
class _String_iterator;

template <class _CharT,
	  class _Traits,
	  class _Alloc>
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

  template <class _Tr, class _Al>
  _String_const_iterator(const _String_iterator<_CharT, _Tr, _Al>&);

  _Self& operator=(const  _Self& __rhs) {
    _M_container = __rhs._M_container;
    _M_ptr = __rhs._M_ptr;
    return *this;
  }

  const _CharT& operator*() const
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

template <class _CharT,
	  class _Traits,
	  class _Alloc>
inline bool operator == (const _String_const_iterator<_CharT, _Traits, _Alloc>& i1, const _String_const_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr == i2._M_ptr;
}

template <class _CharT,
	  class _Traits,
	  class _Alloc>
inline bool operator != (const _String_const_iterator<_CharT, _Traits, _Alloc>& i1, const _String_const_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr != i2._M_ptr;
}

template <class _CharT,
	  class _Traits,
	  class _Alloc>
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
  {
  }

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

template <class _CharT,
	  class _Traits,
	  class _Alloc>
template <class _Tr,
	  class _Al>
_String_const_iterator<_CharT, _Traits, _Alloc>::_String_const_iterator(const _String_iterator<_CharT, _Tr, _Al>& __rhs): 
  _M_container(__rhs._M_container), _M_ptr(__rhs._M_ptr)
{
}

template <class _CharT,
	  class _Traits,
	  class _Alloc>
inline bool operator == (const _String_iterator<_CharT, _Traits, _Alloc>& i1, const _String_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr == i2._M_ptr;
}

template <class _CharT,
	  class _Traits,
	  class _Alloc>
inline bool operator != (const _String_iterator<_CharT, _Traits, _Alloc>& i1, const _String_iterator<_CharT, _Traits, _Alloc>& i2)
{
  return i1._M_ptr != i2._M_ptr;
}

#endif /* BINARY_COMPATIBILITY */

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

  //dums: Some compiler(MSVC6) require it to be public not simply protected!
  enum {_DEFAULT_SIZE = 16 / sizeof(_CharT)};

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  // Iterators.
  typedef _String_const_iterator<_CharT, _Traits, _Alloc> const_iterator;
  typedef _String_iterator<_CharT, _Traits, _Alloc>             iterator;
  iterator begin() { return iterator(this->_M_Start()); }
  const_iterator begin() const { return const_iterator(this->_M_Start()); }
  iterator end() { return iterator(this->_M_Finish()); }
  const_iterator end() const { return const_iterator(this->_M_Finish()); }
#else
  typedef const value_type* const_iterator;
  typedef value_type*       iterator;
  iterator begin()             { return this->_M_Start(); }
  iterator end()               { return this->_M_Finish(); }
  const_iterator begin() const { return this->_M_Start(); }
  const_iterator end()   const { return this->_M_Finish(); }
#endif

  typedef _STLP_STD::reverse_iterator<iterator> reverse_iterator;
  typedef _STLP_STD::reverse_iterator<const_iterator> const_reverse_iterator;

  reverse_iterator rbegin()             { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend()               { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const   { return const_reverse_iterator(begin()); }

#include <stl/_string_npos.h>

  typedef _String_reserve_t _Reserve_t;

public:                         // Constructor, destructor, assignment.
  typedef typename _Base::allocator_type allocator_type;

  union _Buffers
  {
    _CharT*  _M_start;
    _CharT   _M_static_buf[_DEFAULT_SIZE];
  } _M_buf;
  
  size_type _M_size;
  size_type _M_cap;
  
protected:
  bool _M_using_static_buf() const { return _M_cap < _DEFAULT_SIZE; }
  const _CharT* _M_Start() const { return _M_using_static_buf() ? _M_buf._M_static_buf : _M_buf._M_start; }
  _CharT* _M_Start()             { return _M_using_static_buf() ? _M_buf._M_static_buf : _M_buf._M_start; }
  const _CharT* _M_End() const   { return _M_Start()+_M_cap; }
  _CharT* _M_End()               { return _M_Start()+_M_cap; }
  size_type _M_capacity() const { return _M_cap; }
  size_type _M_rest() const     { return  _M_cap - _M_size; }
  _CharT const* _M_Finish() const  { return _M_Start() + _M_size;}
  _CharT* _M_Finish()              { return _M_Start() + _M_size;}
  
  // Precondition: 0 < __n <= max_size().
  void _M_allocate_block(size_t __n = _DEFAULT_SIZE-1);
  void _M_deallocate_block()
  {
    if (!_M_using_static_buf()) {
      this->_M_alloc.deallocate(_M_buf._M_start, _M_cap);
      this->_M_cap = _DEFAULT_SIZE-1;
    }
  }

public:
  size_t max_size() const
  {
    const size_type __string_max_size = size_type(-1) / sizeof(_CharT);
    typename allocator_type::size_type __alloc_max_size = this->_M_alloc.max_size();
    return (min)(__alloc_max_size, __string_max_size) - 1;
  }

  basic_string(const allocator_type& __a, size_t __n) :
    _Base(__a)
  { _M_allocate_block(__n); _M_terminate_string();}
  
#if !defined (_STLP_NO_MOVE_SEMANTIC)
  basic_string(__move_source<_Self> src) :
    _Base(src.get().get_allocator())
  { _M_allocate_block(); _M_swap(src.get()); }
#endif

  ~basic_string()  {  _M_deallocate_block(); }

  void _M_swap( _Self& __s )
  {
	 if (this->_M_alloc == __s._M_alloc)
	 {	
       _STLP_STD::swap(_M_buf, __s._M_buf);
       _STLP_STD::swap(_M_size, __s._M_size);
	   _STLP_STD::swap(_M_cap, __s._M_cap);
	 }
	 else
	 {
		 _Self __tmp(__s);
		 __s = *this;
		 *this = __tmp;
	 }
 }

  allocator_type get_allocator() const
  { return this->_M_alloc; }

  basic_string():
    _Base(allocator_type())
  { _M_allocate_block(); _M_terminate_string(); }
  
  explicit basic_string(const allocator_type& __a)
    : _Base(__a)
  {  _M_allocate_block(); _M_terminate_string(); }

  basic_string(_Reserve_t, size_t __n)
    : _Base(allocator_type())
  { _M_allocate_block(__n); _M_terminate_string(); }

  basic_string(_Reserve_t, size_t __n, const allocator_type& __a)
    : _Base(__a)
  { _M_allocate_block(__n); _M_terminate_string(); }

  basic_string(const _Self& __s): _Base(__s.get_allocator())
  { _M_range_initialize(__s._M_Start(), __s._M_Finish()); }
  
  basic_string(const _Self& __s, size_type __pos)
    : _Base(allocator_type()) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos, __s._M_Finish());
  }
  basic_string(const _Self& __s, size_type __pos, size_type __n)
    : _Base(allocator_type()) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos,
                          __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }
  basic_string(const _Self& __s, size_type __pos, size_type __n,
               const allocator_type& __a): _Base(__a) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    else
      _M_range_initialize(__s._M_Start() + __pos,
                          __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }
  
  basic_string(const _CharT* __s, size_type __n) : _Base(allocator_type()) {
      _M_range_initialize(__s, __s + __n);
    }
  
  basic_string(const _CharT* __s, size_type __n, const allocator_type& __a)
    : _Base(__a) {
    _M_range_initialize(__s, __s + __n);
  }
 
 basic_string(_CharT const* __s): _Base(allocator_type()) {
    _M_range_initialize(__s, __s + traits_type::length(__s));
  }
 
  basic_string(const _CharT* __s, const allocator_type& __a)  :  _Base(__a) {
    _M_range_initialize(__s, __s + traits_type::length(__s));
  }

  basic_string(size_type __n, _CharT __c): _Base(allocator_type()) {
    _M_allocate_block(__n);
    _Traits::assign(this->_M_Start(), __n, __c);
    _Eos(__n);
  }
  basic_string(size_type __n, _CharT __c, const allocator_type& __a)
    : _Base(__a) {
    _Traits::assign(this->_M_Start(), __n, __c);
    _Eos(__n);
  }

  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l,
               const allocator_type & __a _STLP_ALLOCATOR_TYPE_DFL)
    : _Base(__a) {
    typedef typename is_integral<_InputIterator>::type _Integral;
    _M_initialize_dispatch(__f, __l, _Integral());
  }

_STLP_PRIVATE:
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
  void _M_range_initialize(_InputIter __f, _InputIter __l,
                           const input_iterator_tag &__tag) {
    this->_M_allocate_block();
    _M_terminate_string();
    _M_appendT(__f, __l, __tag);
  }

  template <class _ForwardIter>
  void _M_range_initialize(_ForwardIter __f, _ForwardIter __l,
                           const forward_iterator_tag &) {
    difference_type __n = _STLP_STD::distance(__f, __l);
    this->_M_allocate_block(__n);
    uninitialized_copy(__f, __l, this->_M_Start());
    this->_M_terminate_string();
  }

  template <class _InputIter>
  void _M_range_initializeT(_InputIter __f, _InputIter __l) {
    _M_range_initialize(__f, __l, _STLP_ITERATOR_CATEGORY(__f, _InputIter));
  }

  template <class _Integer>
  void _M_initialize_dispatch(_Integer __n, _Integer __x, const true_type& /*_Integral*/) {
    this->_M_allocate_block(__n);
    __uninitialized_fill_n(this->_M_Start(), __n, __x);
    this->_M_terminate_string();
  }

  template <class _InputIter>
  void _M_initialize_dispatch(_InputIter __f, _InputIter __l, const false_type& /*_Integral*/) {
    _M_range_initializeT(__f, __l);
  }

public:
  _Self& operator=(const _Self& __s) {
    if (&__s != this)
      _M_assign(__s._M_Start(), __s._M_Finish());
    return *this;
  }

  _Self& operator=(const _CharT* __s) {
    return _M_assign(__s, __s + traits_type::length(__s));
  }

  _Self& operator=(_CharT __c)
  { return assign(__STATIC_CAST(size_type,1), __c); }

private:
  static _CharT _STLP_CALL _M_null()
  { return _STLP_DEFAULT_CONSTRUCTED(_CharT); }

protected:                     // Helper functions used by constructors
                                   // and elsewhere.
  void _M_construct_null(pointer __s) const { _STLP_STD::_Construct(__s); }
  void _M_terminate_string()  { _M_construct_null(_M_Start()+_M_size); }

  _CharT* _Myptr() { return _M_Start(); }
  const _CharT* _Myptr() const { return _M_Start(); }

  void _Eos(size_type _NSize) 
  {
    _M_size=_NSize;
    _M_terminate_string();
  }

  void _Tidy(bool __dealloc, size_type __new_size = 0) {
    if (__dealloc && _M_cap >= _DEFAULT_SIZE)
      {
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

  bool _Grow(size_type __new_size, bool _Shrink = false)
  {
    if (_Shrink)
      {
	if (__new_size < _DEFAULT_SIZE) {
	  _Tidy(true, min(__new_size, _M_size));
	} 
      }   
    else
      if (_M_cap < __new_size)
	_Copy(__new_size, _M_size);
      else
	if (__new_size==0)
	  _Eos(0);

    return __new_size > 0; 
  }

  void _Copy(size_type __new_size, size_type __old_size)
  {  
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

public:                         // Iterators.

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

private:
  void _M_reserve(size_type);
public:
  void reserve(size_type = 0);

  size_type capacity() const
  { return this->_M_cap - 1; }

  void clear() {
    if (!empty()) {
      _Tidy(0);
    }
  }

  bool empty() const { return this->_M_size == 0; }

public:                         // Element access.

  const_reference operator[](size_type __n) const
  { return *(this->_M_Start() + __n); }
  reference operator[](size_type __n)
  { return *(this->_M_Start() + __n); }

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

public:                         // Append, operator+=, push_back.

  _Self& operator+=(const _Self& __s) { return append(__s); }
  _Self& operator+=(const _CharT* __s) { _STLP_FIX_LITERAL_BUG(__s) return append(__s); }
  _Self& operator+=(_CharT __c) { push_back(__c); return *this; }

private:
  _Self& _M_append(const _CharT* __first, const _CharT* __last);

  template <class _InputIter>
  _Self& _M_appendT(_InputIter __first, _InputIter __last,
                    const input_iterator_tag &) {
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
	if (__n >= _DEFAULT_SIZE)
	  {
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

public:
  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& append(_InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_append_dispatch(__first, __last, _Integral());
  }

public:
  _Self& append(const _Self& __s)
  { return _M_append(__s._M_Start(), __s._M_Finish()); }

  _Self& append(const _Self& __s,
                size_type __pos, size_type __n) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    return _M_append(__s._M_Start() + __pos,
                     __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }

  _Self& append(const _CharT* __s, size_type __n)
  { return _M_append(__s, __s+__n); }
  _Self& append(const _CharT* __s)
  { return _M_append(__s, __s + traits_type::length(__s)); }
  _Self& append(size_type __n, _CharT __c);

public:
  void push_back(_CharT __c) {
    if (this->_M_rest() <= 1 )
      _M_reserve(_M_compute_next_size(1));
    _Traits::assign(*(this->_M_Finish()), __c);
    _M_size++;
    _M_terminate_string();
  }

  void pop_back() {
    _Grow(_M_size-1, true);
    _Eos(_M_size);
  }

public:                         // Assign
  _Self& assign(const _Self& __s)
  { return _M_assign(__s._M_Start(), __s._M_Finish()); }

  _Self& assign(const _Self& __s,
                size_type __pos, size_type __n) {
    if (__pos > __s.size())
      this->_M_throw_out_of_range();
    return _M_assign(__s._M_Start() + __pos,
                     __s._M_Start() + __pos + (min) (__n, __s.size() - __pos));
  }

  _Self& assign(const _CharT* __s, size_type __n)
  { _STLP_FIX_LITERAL_BUG(__s) return _M_assign(__s, __s + __n); }

  _Self& assign(const _CharT* __s)
  { return _M_assign(__s, __s + _Traits::length(__s)); }

  _Self& assign(const _CharT* __s1, const _CharT* __s2)
  { return _M_assign(__s1, __s2); }

  _Self& assign(const_iterator __s1, const_iterator __s2)
  { return _M_assign(__s1._M_ptr, __s2._M_ptr); }

  _Self& assign(size_type __n, _CharT __c);

private:
  _Self& _M_assign(const _CharT* __f, const _CharT* __l);

  // Helper functions for assign.
  template <class _Integer>
  _Self& _M_assign_dispatch(_Integer __n, _Integer __x, const true_type& /*_Integral*/)
  { return assign((size_type) __n, (_CharT) __x); }

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

public:
  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& assign(_InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_assign_dispatch(__first, __last, _Integral());
  }

public:                         // Insert
  _Self& insert(size_type __pos, const _Self& __s) {
    if (__pos > size())
      this->_M_throw_out_of_range();
    if (__s.size() > max_size() - size())
      this->_M_throw_length_error();
    _M_insert(begin() + __pos, __s._M_Start(), __s._M_Finish(), &__s == this);
    return *this;
  }

  _Self& insert(size_type __pos, const _Self& __s,
                size_type __beg, size_type __n) {
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
    }
    else
      {
	size_t __pos(&*__p - _M_Start());
	insert(__pos, 1, __c);
	return _M_Start() + __pos;
      }
  }

  void insert(const_iterator_param __p, size_t __n, _CharT __c);

_STLP_PRIVATE:  // Helper functions for insert.
  void _M_insert(const_iterator __p, const _CharT* __first, const _CharT* __last, bool __self_ref);

  void _M_copy(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _Traits::copy(__res, __f, __l - __f);
  }

  void _M_move(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _Traits::move(__res, __f, __l - __f);
  }

  template <class _ForwardIter>
  void _M_insert_overflow( const_iterator __pos, _ForwardIter __first, _ForwardIter __last, size_type __n )
      {
	// TODO : complete impl
        size_type __len = _M_compute_next_size(__n);
        this->_Grow(__len);
        this->_Eos(__len);
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
                  const forward_iterator_tag &) {
    if (__first != __last) {
      size_type __n = _STLP_STD::distance(__first, __last);
      if (__n < this->_M_rest()) {
        const size_type __elems_after = this->end() - __pos;
        if (__elems_after >= __n) {
          uninitialized_copy((this->_M_Finish() - __n) + 1, this->_M_Finish() + 1, this->_M_Finish() + 1);
          this->_M_size += __n;
          _Traits::move((_CharT*)&*__pos + __n, &*__pos, (__elems_after - __n) + 1);
          _M_copyT(&*__first, &*__last, (_CharT*)&*__pos);
        }
        else {
          pointer __old_finish = this->_M_Finish();
          _ForwardIter __mid = __first;
          _STLP_STD::advance(__mid, __elems_after + 1);
          _STLP_STD::uninitialized_copy(__mid, __last, this->_M_Finish() + 1);
          this->_M_size += __n - __elems_after;
          uninitialized_copy(&*__pos, __old_finish + 1, this->_M_Finish());
          this->_M_size += __elems_after;
          _M_copyT(&*__first, &*__mid, (_CharT*)&*__pos);
        }
      }
      else {
        _M_insert_overflow(__pos, __first, __last, __n);
      }
    }
  }

  template <class _Integer>
  void _M_insert_dispatch(const_iterator __p, _Integer __n, _Integer __x,
                          const true_type& /*Integral*/)
  { insert(__p, (size_type) __n, (_CharT) __x); }

  template <class _InputIter>
  void _M_insert_dispatch(const_iterator __p, _InputIter __first, _InputIter __last,
                          const false_type& /*Integral*/) {
    _STLP_FIX_LITERAL_BUG(__p)
    /* We are forced to do a temporary string to avoid the self referencing issue. */
    _Self __self(__first, __last, get_allocator());
    _M_insertT(__p, __self.begin(), __self.end(), forward_iterator_tag());
  }

  template <class _InputIterator>
  void _M_copyT(_InputIterator __first, _InputIterator __last, pointer __result) {
    _STLP_FIX_LITERAL_BUG(__result)
    for ( ; __first != __last; ++__first, ++__result)
      _Traits::assign(*__result, *__first);
  }

  void _M_copyT(const _CharT* __f, const _CharT* __l, _CharT* __res) {
    _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
    _STLP_FIX_LITERAL_BUG(__res)
    _Traits::copy(__res, __f, __l - __f);
  }
public:
  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  void insert(const_iterator_param __p, _InputIter __first, _InputIter __last) {
    typedef typename is_integral<_InputIter>::type _Integral;
    _M_insert_dispatch(__p, __first, __last, _Integral());
  }

  void insert(const_iterator_param __p, const_iterator __first, const_iterator __last) {
    _M_insert(__p, &*__first, &*__last, _Inside(&*__first));
  }

public:                         // Erase.
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

public:                         // Replace.  (Conceptually equivalent
                                // to erase followed by insert.)
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

  _Self& replace(size_type __pos1, size_type __n1, const _Self& __s,
                 size_type __pos2, size_type __n2) {
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

  _Self& replace(size_type __pos, size_type __n1,
                 const _CharT* __s, size_type __n2) {
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
    _STLP_FIX_LITERAL_BUG(__s)
    return replace(__pos, __n1, __s, _Traits::length(__s));
  }

  _Self& replace(size_type __pos, size_type __n1,
                 size_type __n2, _CharT __c) {
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

  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 const _CharT* __s, size_type __n) {
    return _M_replace(__first, __last, __s, __s + __n, _Inside(__s));
  }

  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 const _CharT* __s) {
    return _M_replace(__first, __last, __s, __s + _Traits::length(__s), _Inside(__s));
  }

  _Self& replace(const_iterator_param __first, const_iterator_param __last, size_type __n, _CharT __c);

_STLP_PRIVATE:                        // Helper functions for replace.
  _Self& _M_replace(const_iterator_param __first, const_iterator_param __last,
                    const _CharT* __f, const _CharT* __l, bool __self_ref);

  template <class _Integer>
  _Self& _M_replace_dispatch(iterator __first, iterator __last,
                             _Integer __n, _Integer __x, const true_type& /*IsIntegral*/) {
    _STLP_FIX_LITERAL_BUG(__first) _STLP_FIX_LITERAL_BUG(__last)
    return replace(__first, __last, (size_type) __n, (_CharT) __x);
  }

  template <class _InputIter>
  _Self& _M_replace_dispatch(const_iterator __first, const_iterator __last,
                             _InputIter __f, _InputIter __l, const false_type& /*IsIntegral*/) {
    _STLP_FIX_LITERAL_BUG(__first) _STLP_FIX_LITERAL_BUG(__last)
    /* We are forced to do a temporary string to avoid the self referencing issue. */
    const _Self __self(__f, __l, get_allocator());
    return _M_replace(__first, __last, __self._M_Start(), __self._M_Finish(), false);
  }

public:
  // Check to see if _InputIter is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 _InputIter __f, _InputIter __l) {
    typedef typename is_integral<_InputIter>::type _Integral;
    return _M_replace_dispatch(__first, __last, __f, __l,  _Integral());
  }

public:

  _Self& replace(const_iterator_param __first, const_iterator_param __last,
                 const_iterator __f, const_iterator __l) {
    return _M_replace(&*__first, &*__last, &*__f, &*__l, _Inside(&*__f));
  }

public:                         // Other modifier member functions.

  size_type copy(_CharT* __s, size_type __n, size_type __pos = 0) const {
    _STLP_FIX_LITERAL_BUG(__s)
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

public:                         // Conversion to C string.

  const _CharT* c_str() const { return this->_M_Start(); }
  const _CharT* data()  const { return this->_M_Start(); }

public: // find.
  size_type find(const _Self& __s, size_type __pos = 0) const
  { return find(__s._M_Start(), __pos, __s.size()); }

  size_type find(const _CharT* __s, size_type __pos = 0) const
  { return find(__s, __pos, _Traits::length(__s)); }

  size_type find(const _CharT* __s, size_type __pos, size_type __n) const;

  // WIE: Versant schema compiler 5.2.2 ICE workaround
  size_type find(_CharT __c) const { return find(__c, 0); }
  size_type find(_CharT __c, size_type __pos /* = 0 */) const;

public: // rfind.
  size_type rfind(const _Self& __s, size_type __pos = npos) const
  { return rfind(__s._M_Start(), __pos, __s.size()); }

  size_type rfind(const _CharT* __s, size_type __pos = npos) const
  { return rfind(__s, __pos, _Traits::length(__s)); }

  size_type rfind(const _CharT* __s, size_type __pos, size_type __n) const;
  size_type rfind(_CharT __c, size_type __pos = npos) const;

public: // find_first_of
  size_type find_first_of(const _Self& __s, size_type __pos = 0) const
  { return find_first_of(__s._M_Start(), __pos, __s.size()); }

  size_type find_first_of(const _CharT* __s, size_type __pos = 0) const
  { return find_first_of(__s, __pos, _Traits::length(__s)); }

  size_type find_first_of(const _CharT* __s, size_type __pos, size_type __n) const;

  size_type find_first_of(_CharT __c, size_type __pos = 0) const
  { return find(__c, __pos); }

public: // find_last_of
  size_type find_last_of(const _Self& __s, size_type __pos = npos) const
  { return find_last_of(__s._M_Start(), __pos, __s.size()); }

  size_type find_last_of(const _CharT* __s, size_type __pos = npos) const
  { return find_last_of(__s, __pos, _Traits::length(__s)); }

  size_type find_last_of(const _CharT* __s, size_type __pos, size_type __n) const;

  size_type find_last_of(_CharT __c, size_type __pos = npos) const
  { return rfind(__c, __pos); }

public: // find_first_not_of
  size_type find_first_not_of(const _Self& __s, size_type __pos = 0) const
  { return find_first_not_of(__s._M_Start(), __pos, __s.size()); }

  size_type find_first_not_of(const _CharT* __s, size_type __pos = 0) const
  { return find_first_not_of(__s, __pos, _Traits::length(__s)); }

  size_type find_first_not_of(const _CharT* __s, size_type __pos, size_type __n) const;

  size_type find_first_not_of(_CharT __c, size_type __pos = 0) const;

public: // find_last_not_of
  size_type find_last_not_of(const _Self& __s, size_type __pos = npos) const
  { return find_last_not_of(__s._M_Start(), __pos, __s.size()); }

  size_type find_last_not_of(const _CharT* __s, size_type __pos = npos) const
  { return find_last_not_of(__s, __pos, _Traits::length(__s)); }

  size_type find_last_not_of(const _CharT* __s, size_type __pos, size_type __n) const;

  size_type find_last_not_of(_CharT __c, size_type __pos = npos) const;

public: // Substring.
  _Self substr(size_type __pos = 0, size_type __n = npos) const
  { return _Self(*this, __pos, __n, get_allocator()); }

public: // Compare
  int compare(const _Self& __s) const
  { return _M_compare(this->_M_Start(), this->_M_Finish(), __s._M_Start(), __s._M_Finish()); }

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
    _STLP_FIX_LITERAL_BUG(__s)
    return _M_compare(this->_M_Start(), this->_M_Finish(), __s, __s + _Traits::length(__s));
  }

  int compare(size_type __pos1, size_type __n1, const _CharT* __s) const {
    _STLP_FIX_LITERAL_BUG(__s)
    if (__pos1 > size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s, __s + _Traits::length(__s));
  }

  int compare(size_type __pos1, size_type __n1, const _CharT* __s, size_type __n2) const {
    _STLP_FIX_LITERAL_BUG(__s)
    if (__pos1 > size())
      this->_M_throw_out_of_range();
    return _M_compare(this->_M_Start() + __pos1,
                      this->_M_Start() + __pos1 + (min) (__n1, size() - __pos1),
                      __s, __s + __n2);
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

  if (__n > capacity()) {
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

#endif /* _STLP_BSTRING_H */

/*
 * Local Variables:
 * mode:C++
 * End:
 */
