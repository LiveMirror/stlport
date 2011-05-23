/*
 * Copyright (c) 1996,1997
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
#ifndef _STLP_FSTREAM_STDIO_C
#define _STLP_FSTREAM_STDIO_C

#include <limits>

_STLP_BEGIN_NAMESPACE

template<class _CharT>
struct _FileAccessor
{
  static inline bool getc(_CharT& _Ch, FILE *__fd) { return (fread(&_Ch, sizeof (_CharT), 1, __fd) == 1); }
  static inline bool putc(_CharT __buf, FILE *__fd) { return fwrite(&__buf, 1, sizeof (_CharT), __fd) == sizeof (_CharT); }
  static inline bool ungetc(const _CharT& __buf, FILE *__fd) { return false; }
};


template<> struct _FileAccessor<char>
{
  static inline bool getc(char& __dest, FILE *__fd)	{
    int __c = fgetc(__fd);
    if (__c != EOF) {
      __dest = (char)__c;
      return true;
    }
    return false;  
  }
  static inline bool ungetc(const char& __buf, FILE *__fd) { return ::ungetc((unsigned char)__buf, __fd) != EOF; }
  static inline bool putc(char __buf, FILE *__fd) { return fputc(__buf, __fd) != EOF; }
};

template<>  struct _FileAccessor<wchar_t>
{
  static inline bool getc(wchar_t& __dest, FILE *__fd) {
    wint_t __c = ::fgetwc(__fd);
    if (__c != WEOF) {
      __dest = (wchar_t)__c;
      return true;
    }
    return false;
  } 
  static inline bool ungetc(const wchar_t& __buf, FILE *__fd) {    return ::ungetwc(__buf, __fd) != WEOF; }
  static inline bool putc(wchar_t __buf, FILE *__fd) { return ::fputwc(__buf, __fd) != WEOF; }
};
  

//----------------------------------------------------------------------
// Public basic_filebuf<> member functions

template <class _CharT, class _Traits>
basic_filebuf<_CharT, _Traits>::basic_filebuf() : basic_streambuf<_CharT, _Traits>(), _M_base(), _M_codecvt(0)
{
  this->imbue(locale());
}

template <class _CharT, class _Traits>
basic_filebuf<_CharT, _Traits>::~basic_filebuf()
{
  this->close();
}

template <class _CharT, class _Traits>
void basic_filebuf<_CharT, _Traits>::_Init(FILE *_F, _Initfl _M_reason)
{
  _M_base._M_file = _F;
  _M_base._M_should_close = (_M_reason == _InitReasonOpen  && _F);
  _M_dirty_buf = 0;
  _M_codecvt = 0;
  _M_state = _State_type();
  if (_M_base._M_file && sizeof(_CharT) == 1) {
    _Base::_Init((char_type**)&_F->_IOBASE, (char_type**)&_F->_IOPTR, &_F->_IORCNT, 
		 (char_type**)&_F->_IOBASE, (char_type**)&_F->_IOPTR, &_F->_IOWCNT);
  }
}



template <class _CharT, class _Traits>
bool basic_filebuf<_CharT, _Traits>::_Endwrite()
{
  if (_M_dirty_buf && _M_codecvt) {
      char *__dst;
      size_t __count;
      if (traits_type::eq_int_type(traits_type::eof(), overflow()))
        return (false);
      
      char __cvtbuf[32];
      while (true) {	
        int __cvtres = _M_codecvt->unshift(_M_state,
                                           __cvtbuf, __cvtbuf+32, __dst);
        switch (__cvtres) {
        case codecvt_base::ok:
          _M_dirty_buf = false;
        case codecvt_base::partial:
          __count = __dst - __cvtbuf;
          if (__count) {
            if (fwrite(__cvtbuf, 1, __count, _M_base._M_file) != __count)
              return false;
          } else
            return false;
          if (!_M_dirty_buf)
            return (true);
          break;
        case codecvt_base::noconv:
          return true;
          
        default:
          return false;
        }
      }
  }   
  return true;
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::int_type
basic_filebuf<_CharT, _Traits>::underflow() {
  _CharT* __gptr = this->gptr();
  if ( __gptr && __gptr < this->egptr())
    return (traits_type::to_int_type(*__gptr));
  else {
    int_type __u = uflow();
    if (traits_type::eq_int_type(__u, traits_type::eof()))
      return (__u);
    else {
      pbackfail(__u);
      return (__u);
    }
  }
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::int_type
basic_filebuf<_CharT, _Traits>::uflow() {
  _CharT* __gptr = this->gptr();
  if ( __gptr && __gptr < this->egptr())
    return traits_type::to_int_type(*this->_Gninc());
  _CharT __buf;

  if (__is_open()) {
    if (!_M_codecvt) {
      if (_FileAccessor<_CharT>::getc(__buf, _M_base._M_file))
	return traits_type::to_int_type(__buf);
    } else {
      char __cvtbuf[32];
      while (true) {	
	  _CharT *__dst;
	  _CharT __buf;
	  const char *__src;

	  int __tmp = fgetc(_M_base._M_file);
	  
	  if (__tmp == EOF)
	    return (traits_type::eof());
	  
	  __cvtbuf[0] = __tmp;
	  __cvtbuf[1] = 0;
	  int __res = _M_codecvt->in(_M_state,
				     __cvtbuf, __cvtbuf + 32, __src,
				     &__buf, &__buf, __dst);
	  switch (__res) {
	  case codecvt_base::partial:
	  case codecvt_base::ok:
	    if (__dst != &__buf) {
	      for (ptrdiff_t __i = __cvtbuf + 32 - __src; __i; )
		ungetc(__src[--__i], _M_base._M_file);
	      return (traits_type::to_int_type(__buf));
	    } else {
	      // TODO : shift ? , discard first chars  ?
	    }
	    break;
	      
	    case codecvt_base::noconv:
	      return (traits_type::to_int_type(__cvtbuf[0]));
	      
	    default:
	      return (traits_type::eof());
	    }
      }      
    }
  }
  return  traits_type::eof();
}

template <class _CharT, class _Traits>
basic_filebuf<_CharT, _Traits>*
basic_filebuf<_CharT, _Traits>::close()
{
  // We close our stream in any case
  bool __ok = _M_base._M_close();
  __ok == __ok && this->is_open();
  _Init(0, _InitReasonClose);
  return __ok ? this : 0;
}

//----------------------------------------------------------------------
// basic_filebuf<> overridden protected virtual member functions

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::int_type
basic_filebuf<_CharT, _Traits>::overflow(int_type __c)
{
  const _CharT *__src;
  char *__dst;
  size_t __count;
  
  char __cvtbuf[32];

  if (traits_type::eq_int_type(traits_type::eof(), __c))
    return (traits_type::not_eof(__c));
  if (!__is_open())
    return (traits_type::eof());
  
  const _CharT __buf = traits_type::to_char_type(__c);
  if (this->pptr() && this->pptr() < this->epptr()) {
    *this->_Pninc() = traits_type::to_char_type(__c);
    return __c;
  }
  else if (_M_codecvt == 0)
    return (_FileAccessor<_CharT>::putc(traits_type::to_char_type(__c), _M_base._M_file) ? __c : traits_type::eof());
  
  while (true) {
    int __cvtres = _M_codecvt->out(_M_state,
                                   &__buf, &__buf + 1, __src,
                                   &__cvtbuf[0], __cvtbuf + sizeof(__cvtbuf), __dst);   
    switch (__cvtres) {
    case codecvt_base::noconv:
      return (fwrite(&__c, 1, sizeof(_CharT), _M_base._M_file) == sizeof(_CharT) ? 
              __c : traits_type::eof());
      
    case codecvt_base::ok:
    case codecvt_base::partial:
      __count = __dst - __cvtbuf;
      if (__count) {
        if (fwrite(__cvtbuf, 1, __count, _M_base._M_file) != __count)
          return traits_type::eof();
        
        _M_dirty_buf = true;
        if (__src != &__buf)
          return __c;
      } else
        return traits_type::eof();
      break;      
    default:
      return traits_type::eof();
    }
  } // while
  
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::int_type
basic_filebuf<_CharT, _Traits>::pbackfail(int_type __c)
{
  const int_type __eof = traits_type::eof();

  if (this->gptr() && this->eback() < this->gptr()
      && (traits_type::eq_int_type(traits_type::eof(), __c) 
	  || traits_type::eq_int_type(traits_type::to_int_type(this->gptr()[-1]), __c))) {
    this->_Gndec();
    return (traits_type::not_eof(__c));
  } else if (_M_base._M_file == 0 || traits_type::eq_int_type(traits_type::eof(), __c))
    return __eof;
  else if (_M_codecvt == 0 && _FileAccessor<_CharT>::ungetc(traits_type::to_char_type(__c), _M_base._M_file))
    return __c;
  else if (sizeof (_CharT) > 1 && this->gptr() != &_M_pback_buf) {
    _M_pback_buf = traits_type::to_char_type(__c);
    this->setg(&_M_pback_buf, &_M_pback_buf, &_M_pback_buf + 1);
    return __c;
  }
  return __eof;
}


template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::pos_type
basic_filebuf<_CharT, _Traits>::seekoff(off_type __off,  ios_base::seekdir __whence, ios_base::openmode /* dummy */) 
{
  if (!this->is_open() || !_Endwrite())
    return pos_type(-1);

  fpos_t __pos (-1);

  // specil case : we are in putback mode an searh is relative
  if (__whence == ios_base::cur && _M_codecvt == 0 && this->gptr() == &_M_pback_buf)
    __off -= off_type(sizeof (_CharT));
  
  if (__whence != ios_base::cur || __off != 0) {
    __pos = _M_base._M_seek((long)__off, __whence);
  } else 
    if (fgetpos(_M_base._M_file, &__pos) != 0)
      return  pos_type(-1);
  
  if (this->gptr() == &_M_pback_buf)
    this->setg(&_M_pback_buf, &_M_pback_buf + 1,
		&_M_pback_buf + 1);
  
  return pos_type(_M_state, __pos);
}

template <class _CharT, class _Traits>
basic_streambuf<_CharT, _Traits>*
basic_filebuf<_CharT, _Traits>::setbuf(_CharT* __buf, streamsize __size) {
  if (_M_base._M_file == 0 || setvbuf(_M_base._M_file, (char *)__buf,
			      __buf == 0 && __size == 0 ? _IONBF : _IOFBF,
			      __size * sizeof (_CharT)) != 0)
    return 0;
  else {
    _Init(_M_base._M_file, _InitReasonOpen);
    return this;
  }
}

template <class _CharT, class _Traits>
_STLP_TYPENAME_ON_RETURN_TYPE basic_filebuf<_CharT, _Traits>::pos_type
basic_filebuf<_CharT, _Traits>::seekpos(pos_type __pos,
					ios_base::openmode /* dummy */) {
      fpos_t __fpos = __pos.seekpos();
      off_type __off = (off_type)__pos - __fpos;
      
      if (!this->is_open() || !_Endwrite())
	return pos_type(-1);
      
      if (fsetpos(_M_base._M_file, &__fpos)!=0)
	return pos_type(-1);
      
      if (this->gptr() == &_M_pback_buf)
	this->setg(&_M_pback_buf, &_M_pback_buf + 1,
		    &_M_pback_buf + 1);
      
      if (__off == 0 || (fseek(_M_base._M_file, (long)__off, SEEK_CUR) == 0
			 && fgetpos(_M_base._M_file, &__fpos) == 0)) {
	_M_state = __pos.state();
	return pos_type(_M_state, __fpos);
      }
      return pos_type(-1);
}
    
    
template <class _CharT, class _Traits>
int basic_filebuf<_CharT, _Traits>::sync()
{
  if (__is_open()) {
    int_type __o_res = overflow();
    if (traits_type::eq_int_type(__o_res, traits_type::eof()))
      return 0;
    return fflush(_M_base._M_file) >= 0 ? 0 : -1;
  }
  return 0; 
}

// Change the filebuf's locale.  This member function has no effect
// unless it is called before any I/O is performed on the stream.
template <class _CharT, class _Traits>
void basic_filebuf<_CharT, _Traits>::imbue(const locale& __loc)
{
    _M_codecvt = 0;
    if (has_facet<_Codecvt>(__loc)) {
      _Initcvt(const_cast< _Codecvt*>(&use_facet<_Codecvt>(__loc))) ;
    } 
}

template <class _CharT, class _Traits>
void basic_filebuf<_CharT, _Traits>::_Initcvt(_Codecvt* __c)
{
  if (__c && __c->always_noconv())
    _M_codecvt = 0;
  else
    _M_codecvt = __c;
}


inline _Filebuf_base::_Filebuf_base(): _M_should_close(false), _M_file(0)
{}

inline void _Filebuf_base::_S_initialize()
{}

_STLP_END_NAMESPACE

#endif /* _STLP_FSTREAM_C */

// Local Variables:
// mode:C++
// End:
