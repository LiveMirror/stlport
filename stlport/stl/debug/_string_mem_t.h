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

#ifndef _STLP_DBG_STRING_MEM_T_H
#define _STLP_DBG_STRING_MEM_T_H

# define _STLP_NON_DBG_STRING_BASE _STLP_NON_DBG_NAME(str)<_CharT, _Traits, _Alloc>

_STLP_BEGIN_NAMESPACE

template <class _CharT, class _Traits, class _Alloc> 
class basic_string : private __range_checker_mem_t,
                     public _STLP_NON_DBG_STRING_BASE {
private:
  typedef _STLP_NON_DBG_STRING_BASE _Base;
  typedef basic_string<_CharT, _Traits, _Alloc> _Self;
  typedef __range_checker_mem_t _CheckRange;
  typedef typename _Base::_DbgBase _DbgBase;

public:
  __IMPORT_WITH_REVERSE_ITERATORS(_DbgBase)

  typedef typename _DbgBase::_Iterator_category _Iterator_category;
  typedef typename _DbgBase::traits_type traits_type;
  typedef typename _DbgBase::_Reserve_t _Reserve_t;

#  ifdef _STLP_USE_NATIVE_STRING
  // this typedef is being used for conversions
  typedef typename _DbgBase::__std_string __std_string;
#  endif

public:                         // Constructor, destructor, assignment.
  typedef typename _Base::_Reserve_t _Reserve_t;

public:
  basic_string() :
    _STLP_NON_DBG_STRING_BASE() {}
  
  explicit basic_string(const allocator_type& __a) :
    _STLP_NON_DBG_STRING_BASE(__a) {}

  basic_string(_Reserve_t __r, size_t __n,
               const allocator_type& __a = allocator_type()) :
    _STLP_NON_DBG_STRING_BASE(__r, __n, __a) {}

  basic_string(const _Self& __s) :
    _CheckRange(__s), _STLP_NON_DBG_STRING_BASE(__s) {}

  basic_string(const _Self& __s, size_type __pos, size_type __n = _Base::npos,
               const allocator_type& __a = allocator_type()) :
    _STLP_NON_DBG_STRING_BASE(__s, __pos, __n, __a) {}

  basic_string(const _CharT* __s, size_type __n,
               const allocator_type& __a = allocator_type()) :
    _STLP_NON_DBG_STRING_BASE(__s, __n, __a) {}

  basic_string(const _CharT* __s,
               const allocator_type& __a = allocator_type()):
    _STLP_NON_DBG_STRING_BASE(__s, __a) {}

  basic_string(size_type __n, _CharT __c,
               const allocator_type& __a = allocator_type()):
    _STLP_NON_DBG_STRING_BASE(__n, __c, __a) {}

  basic_string(__move_source<_Self> src):
    _STLP_NON_DBG_STRING_BASE(__move_source<_Base>(src.get())) {}

#if !(defined(__MRC__)||defined(__SC__))
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l,
               const allocator_type & __a _STLP_ALLOCATOR_TYPE_DFL) :
    _CheckRange(__f, __l), 
    _STLP_NON_DBG_STRING_BASE(__f, __l, __a) {
  }
#  ifdef _STLP_NEEDS_EXTRA_TEMPLATE_CONSTRUCTORS
  template <class _InputIterator>
  basic_string(_InputIterator __f, _InputIterator __l) :
    _CheckRange(__f, __l), 
    _STLP_NON_DBG_STRING_BASE(__f, __l) {
  }
#  endif
#endif

#if defined (_STLP_USE_NATIVE_STRING)
  // these conversion operations still needed for
  // strstream, etc.
  basic_string (const __std_string& __x)
    : _STLP_NON_DBG_STRING_BASE(__x.begin(), __x.end()) {}
  operator __std_string() const { return __std_string(this->data(), this->size()); }
#endif

  // constructor from non-debug version
  basic_string (const _Base& __x)
    : _STLP_NON_DBG_STRING_BASE(__x) {}

  _Self& operator=(const _Self& __s) {
    _Base::operator=(__s);
    return *this;
  }

  _Self& operator=(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::operator=(__s);
    return *this;
  }

  _Self& operator=(_CharT __c) {
    _Base::operator=(__c);
    return *this;
  }

public:                         // Append, operator+=, push_back.

  _Self& operator+=(const _Self& __s) {
    _Base::operator+=(__s);
    return *this;
  }
  _Self& operator+=(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::operator+=(__s);
    return *this;
  }
  _Self& operator+=(_CharT __c) {
    _Base::operator+=(__c);
    return *this;
  }

  _Self& append(const _Self& __s) {
    _Base::append(__s);
    return *this;
  }

  _Self& append(const _Self& __s, size_type __pos, size_type __n) {
    _Base::append(__s, __pos, __n);
    return *this;
  }

  _Self& append(const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::append(__s, __n);
    return *this;
  }

  _Self& append(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::append(__s);
    return *this;
  }

  _Self& append(size_type __n, _CharT __c) {
    _Base::append(__n, __c);
    return *this;
  }

  // Check to see if _InputIterator is an integer type.  If so, then
  // it can't be an iterator.
  template <class _InputIter>
  _Self& append(_InputIter __first, _InputIter __last) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    size_type __old_capacity = this->capacity();
    _Base::append(__first, __last);
    _Compare_Capacity(__old_capacity);
    return *this;
  }

/*#ifdef _STLP_MSVC
// specialization for append
 template <>
 inline _Self& append(iterator __f, iterator __l) {
   _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
   _STLP_DEBUG_CHECK(__check_range(__f, __l))
    size_type __old_capacity = this->capacity();
   _Base::append(__f._M_iterator, __l._M_iterator);
    _Compare_Capacity(__old_capacity);
   return *this;
 }
#endif*/

public:                         // Assign
  
  _Self& assign(const _Self& __s) {
    _Base::assign(__s); 
    return *this; 
  }

  _Self& assign(const _Self& __s, size_type __pos, size_type __n) {
    _Base::assign(__s, __pos, __n);
    return *this;
  }

  _Self& assign(const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::assign(__s, __n);
    return *this;
  }

  _Self& assign(const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _Base::assign(__s);
    return *this;
  }

  _Self& assign(size_type __n, _CharT __c) {
    _Base::assign(__n, __c);
    return *this;    
  }

  template <class _InputIter>
  inline _Self& assign(_InputIter __first, _InputIter __last) {
    _STLP_FIX_LITERAL_BUG(__first) _STLP_FIX_LITERAL_BUG(__last)
    _STLP_DEBUG_CHECK(__check_range(__first, __last))
    _Base::assign(__first, __last);
    return *this;    
  }

  /*
#ifdef _STLP_MSVC
// partial specialization for assign
template <>
inline _Self& assign(iterator __f, iterator __l) {
  _STLP_FIX_LITERAL_BUG(__f) _STLP_FIX_LITERAL_BUG(__l)
  _STLP_DEBUG_CHECK(__check_range(__f, __l))
  _Base::assign(__f._M_iterator, __l._M_iterator);
  return *this;
  }
#endif
  */
    
public:                         // Insert

  _Self& insert(size_type __pos, const _Self& __s) {
    _DbgBase::insert(__pos, __s);
    return *this;
  }

  _Self& insert(size_type __pos, const _Self& __s, size_type __beg, size_type __n) {
    _DbgBase::insert(__pos, __s, __beg, __n);
    return *this;
  }

  _Self& insert(size_type __pos, const _CharT* __s, size_type __n) {
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::insert(__pos, __s, __n);
    return *this;
  }

  _Self& insert(size_type __pos, const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::insert(__pos, __s);
    return *this;
  }
    
  _Self& insert(size_type __pos, size_type __n, _CharT __c) {
    _DbgBase::insert(__pos, __n, __c);
    return *this;
  }

  iterator insert(iterator __p, _CharT __c) {
    return _DbgBase::insert(__p, __c);
  }

  void insert(iterator __p, size_t __n, _CharT __c) {
    _DbgBase::insert(__p, __n, __c);
  }

  template <class _InputIter>
  void insert(iterator __p, _InputIter __first, _InputIter __last) {
    _STLP_DEBUG_CHECK(__check_if_owner(&this->_M_iter_list,__p))
    _STLP_DEBUG_CHECK(__check_range(__first,__last))

    typedef typename _AreSameTypes<_InputIter, iterator>::_Ret _IsNonConstIterator;
    typedef typename _AreSameTypes<_InputIter, const_iterator>::_Ret _IsConstIterator;
    typedef typename _Lor2<_IsNonConstIterator, _IsConstIterator>::_Ret _IsIterator;

    size_type __old_capacity = this->capacity();
    _M_insert_aux(__p, __first, __last, _IsIterator());
    _Compare_Capacity(__old_capacity);
  }

private:
  template <class _RandomIter>
  void _M_insert_aux (iterator __p, _RandomIter __first, _RandomIter __last,
                      const __true_type& /*_IsIterator*/) {
    _Base::insert(__p._M_iterator, __first._M_iterator, __last._M_iterator);
  }
  
  template<class _InputIter>
  void _M_insert_aux (iterator __p, _InputIter __first, _InputIter __last,
                      const __false_type& /*_IsIterator*/) {
    _Base::insert(__p._M_iterator, __first, __last);
  }



public:                         // Erase.
  _Self& erase(size_type __pos = 0, size_type __n = _Base::npos) {
    _DbgBase::erase(__pos, __n);
    return *this;
  }
  iterator erase(iterator __pos) {
    return _DbgBase::erase(__pos);
  }
  iterator erase(iterator __first, iterator __last) {
    return _DbgBase::erase(__first, __last);
  }

public:                         // Substring.
  _Self substr(size_type __pos = 0, size_type __n = _Base::npos) const {
    return _Base::substr(__pos, __n);
  }

public:                         // Replace.  (Conceptually equivalent
                                // to erase followed by insert.)
  _Self& replace(size_type __pos, size_type __n, const _Self& __s) {
    _DbgBase::replace(__pos, __n, __s);
    return *this;
  }

  _Self& replace(size_type __pos1, size_type __n1, const _Self& __s,
                 size_type __pos2, size_type __n2) {
    _DbgBase::replace(__pos1, __n1, __s, __pos2, __n2);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1, const _CharT* __s, size_type __n2) {    
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::replace(__pos, __n1, __s, __n2);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1, const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::replace(__pos, __n1, __s);
    return *this;
  }

  _Self& replace(size_type __pos, size_type __n1, size_type __n2, _CharT __c) {
    _DbgBase::replace(__pos, __n1, __n2, __c);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, const _Self& __s) {
    _DbgBase::replace(__first, __last, __s);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, const _CharT* __s, size_type __n) { 
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::replace(__first, __last, __s, __n);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, const _CharT* __s) {
    _STLP_FIX_LITERAL_BUG(__s)
    _DbgBase::replace(__first, __last, __s);
    return *this;
  }

  _Self& replace(iterator __first, iterator __last, size_type __n, _CharT __c) {
    _DbgBase::replace(__first, __last, __n, __c);
    return *this;
  }

  template <class _InputIter>
  _Self& replace(iterator __first, iterator __last,
                 _InputIter __f, _InputIter __l) {
    _STLP_DEBUG_CHECK(__check_range(__first, __last, this->begin(), this->end()))
    _STLP_DEBUG_CHECK(__check_range(__f, __l))

    typedef typename _AreSameTypes<_InputIter, iterator>::_Ret _IsNonConstIterator;
    typedef typename _AreSameTypes<_InputIter, const_iterator>::_Ret _IsConstIterator;
    typedef typename _Lor2<_IsNonConstIterator, _IsConstIterator>::_Ret _IsIterator;

    size_type __old_capacity = this->capacity();
    _M_replace_aux(__first, __last, __f, __l, _IsIterator());
    _Compare_Capacity(__old_capacity);
    return *this;
  }
 
private:
  template <class _RandomIter>
  void _M_replace_aux(iterator __first, iterator __last,
                      _RandomIter __f, _RandomIter __l, __true_type const& /*_IsIterator*/) {
    _Base::replace(__first._M_iterator, __last._M_iterator, __f._M_iterator, __l._M_iterator);
  }
  
  template <class _InputIter>
  void _M_replace_aux(iterator __first, iterator __last,
                      _InputIter __f, _InputIter __l, __false_type const& /*_IsIterator*/) {
    _Base::replace(__first._M_iterator, __last._M_iterator, __f, __l);
  }  

public:                         // Other modifier member functions.

  void swap(_Self& __s) {
    this->_M_iter_list._Swap_owners(__s._M_iter_list);
    _Base::swap(__s);
  }
};

_STLP_END_NAMESPACE

#undef basic_string
#undef _STLP_NON_DBG_STRING_BASE


#endif /* _STLP_DBG_STRING_MEM_T_H */

// Local Variables:
// mode:C++
// End:
