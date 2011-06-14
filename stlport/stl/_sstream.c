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

#ifndef _STLP_SSTREAM_C
#define _STLP_SSTREAM_C

#ifndef _STLP_INTERNAL_SSTREAM
#  include <stl/_sstream.h>
#endif

#if defined ( _STLP_NESTED_TYPE_PARAM_BUG )
// no wint_t is supported for this mode
#  define __BSB_int_type__ int
#  define __BSB_pos_type__ streampos
#else
#  define __BSB_int_type__ _STLP_TYPENAME_ON_RETURN_TYPE basic_stringbuf<_CharT, _Traits, _Alloc>::int_type
#  define __BSB_pos_type__ _STLP_TYPENAME_ON_RETURN_TYPE basic_stringbuf<_CharT, _Traits, _Alloc>::pos_type
#endif

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Non-inline stringbuf member functions.

// Constructors.  Note that the base class constructor sets all of the
// get and area pointers to null.

template <class _CharT, class _Traits, class _Alloc>
basic_stringbuf<_CharT, _Traits, _Alloc>::basic_stringbuf(ios_base::openmode __mode)
    : basic_streambuf<_CharT, _Traits>(), _M_mode(__mode)
{
  _Init(0, 0, _Getstate(__mode));
}

template <class _CharT, class _Traits, class _Alloc>
basic_stringbuf<_CharT, _Traits, _Alloc>::basic_stringbuf(const basic_string<_CharT, _Traits, _Alloc>& __s, ios_base::openmode __mode)
  : basic_streambuf<_CharT, _Traits>(), _M_mode(__mode)
{
  _Init(__s.data(), __s.size(), _Getstate(__mode));
}

template <class _CharT, class _Traits, class _Alloc>
basic_stringbuf<_CharT, _Traits, _Alloc>::~basic_stringbuf()
{
  _Tidy();
}

template <class _CharT, class _Traits, class _Alloc>
basic_string<_CharT, _Traits, _Alloc>
basic_stringbuf<_CharT, _Traits, _Alloc>::str() const
{
  if (!(_M_mode & _ReadOnly) && this->pptr() != 0) {
    return _String(this->pbase(), (_M_ptr < this->pptr() ? this->pptr() : _M_ptr) - this->pbase());
  } else if (!(_M_mode & _WriteOnly) && this->gptr() != 0) {
    return _String(this->eback(), this->egptr() - this->eback());
  } else
    return _String();  
}

// Set the underlying string to a new value.
template <class _CharT, class _Traits, class _Alloc>
void
basic_stringbuf<_CharT, _Traits, _Alloc>::str(const basic_string<_CharT, _Traits, _Alloc>& __s)
{
  _Tidy();
  _Init(__s.c_str(), __s.size(), _M_mode);
}


// Precondition: gptr() >= egptr().  Returns a character, if one is available.
template <class _CharT, class _Traits, class _Alloc>
__BSB_int_type__
basic_stringbuf<_CharT, _Traits, _Alloc>::underflow() {
  if (this->gptr()) {
    if (this->gptr() < this->egptr())
      return (traits_type::to_int_type(*this->gptr()));
    else if ((!(_M_mode & _WriteOnly)) && this->pptr() > this->gptr() && _M_ptr > this->gptr())       {	
      if (_M_ptr < this->pptr())
        _M_ptr = this->pptr();
      this->setg(this->eback(), this->gptr(), _M_ptr);
      return (traits_type::to_int_type(*this->gptr()));
    }
  }
  return traits_type::eof();
}

template <class _CharT, class _Traits, class _Alloc>
__BSB_int_type__
basic_stringbuf<_CharT, _Traits, _Alloc>::pbackfail(int_type __c) {
  if (this->gptr() != this->eback()) {
    if (!traits_type::eq_int_type(__c, traits_type::eof())) {
      if (traits_type::eq(traits_type::to_char_type(__c), this->gptr()[-1])) {
        this->gbump(-1);
        return __c;
      }
      else if (_M_mode & ios_base::out) {
        this->gbump(-1);
        *this->gptr() = traits_type::to_char_type(__c);
        return __c;
      }
      else
        return traits_type::eof();
    }
    else {
      this->gbump(-1);
      return traits_type::not_eof(__c);
    }
  }
  else
    return traits_type::eof();
}

template <class _CharT, class _Traits, class _Alloc>
__BSB_int_type__ basic_stringbuf<_CharT, _Traits, _Alloc>::overflow(int_type __c)
{
  
  if (_M_mode & _ReadOnly)
    return traits_type::eof();
  
  if ( this->pptr() && this->pptr() < _M_ptr && (_M_mode & _AppendMode) )
    this->setp(this->pbase(), _M_ptr, this->epptr());
  
  if (traits_type::eq_int_type(traits_type::eof(), __c))
    return (traits_type::not_eof(__c));

  if (this->pptr() && this->pptr() < this->epptr()) {
    // there is room left in the buffer
    *this->_Pninc() = traits_type::to_char_type(__c);
    return __c;
  } 
  
  size_t __cursize = this->pptr() ? this->epptr() - this->eback() : 0;
  off_t  __nextoffset =0;
  _CharT *__ptr = 0;
  _CharT *__nextptr = 0;
  size_t __newsize = max((size_t)64, __cursize * 2); // double, for amortized constant time
 
  // reallocate storage and copy old contents over
  __ptr = _M_alloc.allocate(__newsize); 
  if (__cursize)
    traits_type::copy(__ptr, this->eback(), min(__newsize, __cursize));
  if (_M_mode & _OwnStorage)
    _M_alloc.deallocate(this->eback(), __cursize);
  _M_mode |= _OwnStorage;
  
  if (__cursize!=0) {
    // existing data in buffer
    _M_ptr = __ptr + (_M_ptr - this->eback());
    this->setp(__ptr + (this->pbase() - this->eback()), __ptr + (this->pptr() - this->eback()) , __ptr + __newsize);
    __nextoffset = this->gptr() - this->eback();
    __nextptr = this->pptr() + 1;
  }
  else {
    _M_ptr = __ptr;
    this->setp(__ptr, __ptr + __newsize);
    __nextptr = __ptr + 1;
  }

  if (_M_mode & _WriteOnly)
    this->setg(__ptr, 0, __ptr);
  else
    this->setg(__ptr, __ptr + __nextoffset, __nextptr);
  
  *this->_Pninc() = traits_type::to_char_type(__c);
  return __c;
}



template <class _CharT, class _Traits, class _Alloc>
__BSB_pos_type__
basic_stringbuf<_CharT, _Traits, _Alloc>::seekoff(off_type __off, ios_base::seekdir __dir, ios_base::openmode __mode) {
  bool __imode  = (__mode & ios_base::in) != 0;
  bool __omode = (__mode & ios_base::out) != 0;

  if (this->pptr() && _M_ptr < this->pptr())
    _M_ptr = this->pptr();

  if (__imode && this->gptr()) {
    if (__dir == ios_base::end)
      __off += (off_type)(_M_ptr - this->eback());
    else if (__dir == ios_base::cur && !__omode )
      __off += (off_type)(this->gptr() - this->eback());
    else if (__dir != ios_base::beg)
      __off = off_type(-1);
    
    if (__off >=0 && __off <= _M_ptr - this->eback()) {
      this->gbump((int)(this->eback() - this->gptr() + __off));
      if (__omode && this->pptr())
        this->setp(this->pbase(), this->gptr(), this->epptr());
    } else
      __off =-1;
  }
  else if (__omode && this->pptr()) {
    if (__dir == ios_base::end)
      __off += (off_type)(_M_ptr - this->eback());
    else if (__dir == ios_base::cur)
      __off += (off_type)(this->pptr() - this->eback());
    else if (__dir != ios_base::beg)
      __off = -1;
    
    if (__off >= 0 && __off <= _M_ptr - this->eback())
      this->pbump((int)(this->eback() - this->pptr() + __off));
    else
      __off = -1;
  }
  else
    __off = -1;
  return pos_type(__off);
}

template <class _CharT, class _Traits, class _Alloc>
__BSB_pos_type__
basic_stringbuf<_CharT, _Traits, _Alloc>::seekpos(pos_type __pos, ios_base::openmode __mode) {
  __mode &= _M_mode;
  const off_type __n = __pos - pos_type(off_type(0));
  return streampos(seekoff(__n, ios_base::beg, __mode));
}

template <class _CharT, class _Traits, class _Alloc>
void
basic_stringbuf<_CharT, _Traits, _Alloc>::_Init(const _CharT* __ptr, size_t __count, int __state)
{
  _M_ptr = 0;
  _M_mode = __state;
  
  if (__count != 0 && (__state & (_WriteOnly | _ReadOnly)) != (_WriteOnly | _ReadOnly)) {
    _CharT *__myptr = _M_alloc.allocate(__count);
    traits_type::copy(__myptr, __ptr, __count);
    _M_ptr = __myptr + __count;
    
    if (!(__state & _WriteOnly))
      this->setg(__myptr, __myptr, __myptr + __count);
    if (!(__state & _ReadOnly)) {
      this->setp(__myptr, (_M_mode & _AtendMode) ? __myptr + __count : __myptr, __myptr + __count);
      if (!this->gptr())
        this->setg(__myptr, 0, __myptr);
    }
    _M_mode |= _OwnStorage;
  }
}

template <class _CharT, class _Traits, class _Alloc>
void
basic_stringbuf<_CharT, _Traits, _Alloc>::_Tidy()
{
  if (_M_mode & _OwnStorage) {
    _CharT* __base(this->eback());
    _CharT* __eptr(this->pptr() ? this->epptr() : this->egptr());
    _M_alloc.deallocate(__base, __eptr - __base);
  }
  _M_ptr = 0; _M_mode = 0;
  this->setg(0, 0, 0);
  this->setp(0, 0);
}

template <class _CharT, class _Traits, class _Alloc>
int 
basic_stringbuf<_CharT, _Traits, _Alloc>::_Getstate(ios_base::openmode __mode)
{
  int __ret(0);
  if (!(__mode & ios_base::in))
    __ret |= _WriteOnly;
  if (!(__mode & ios_base::out))
    __ret |= _ReadOnly;
  if (__ret & ios_base::app)
    __ret |= _AppendMode;
  if (__mode & ios_base::ate)
    __ret |= _AtendMode;
  return __ret;
}

//----------------------------------------------------------------------
// Non-inline istringstream member functions.

template <class _CharT, class _Traits, class _Alloc>
basic_istringstream<_CharT, _Traits, _Alloc>::basic_istringstream(ios_base::openmode __mode):
  basic_istream<_CharT, _Traits>(0), _M_buf(__mode | ios_base::in) {
  this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_istringstream<_CharT, _Traits, _Alloc>::basic_istringstream(const _String& __str,ios_base::openmode __mode)
    : basic_istream<_CharT, _Traits>(0), _M_buf(__str, __mode | ios_base::in) {
  this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_istringstream<_CharT, _Traits, _Alloc>::~basic_istringstream()
{}

//----------------------------------------------------------------------
// Non-inline ostringstream member functions.

template <class _CharT, class _Traits, class _Alloc>
basic_ostringstream<_CharT, _Traits, _Alloc>::basic_ostringstream(ios_base::openmode __mode)
    : basic_ostream<_CharT, _Traits>(0), _M_buf(__mode | ios_base::out) {
  this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_ostringstream<_CharT, _Traits, _Alloc>::basic_ostringstream(const _String& __str, ios_base::openmode __mode)
    : basic_ostream<_CharT, _Traits>(0), _M_buf(__str, __mode | ios_base::out) {
  this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_ostringstream<_CharT, _Traits, _Alloc>::~basic_ostringstream()
{}

//----------------------------------------------------------------------
// Non-inline stringstream member functions.

template <class _CharT, class _Traits, class _Alloc>
basic_stringstream<_CharT, _Traits, _Alloc>::basic_stringstream(ios_base::openmode __mode)
    : basic_iostream<_CharT, _Traits>(0), _M_buf(__mode) {
   this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_stringstream<_CharT, _Traits, _Alloc>::basic_stringstream(const _String& __str, ios_base::openmode __mode)
    : basic_iostream<_CharT, _Traits>(0), _M_buf(__str, __mode) {
  this->init(&_M_buf);
}

template <class _CharT, class _Traits, class _Alloc>
basic_stringstream<_CharT, _Traits, _Alloc>::~basic_stringstream()
{}

_STLP_END_NAMESPACE

# undef __BSB_int_type__
# undef __BSB_pos_type__

#endif /* _STLP_SSTREAM_C */

// Local Variables:
// mode:C++
// End:
