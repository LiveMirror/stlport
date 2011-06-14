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
#ifndef _STLP_INTERNAL_STREAMBUF
#define _STLP_INTERNAL_STREAMBUF

#ifndef _STLP_IOS_BASE_H
#  include <stl/_ios_base.h>      // Needed for ios_base bitfield members.
#endif                            // <ios_base> includes <iosfwd>.

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// Class basic_streambuf<>, the base class of the streambuf hierarchy.

// A basic_streambuf<> manages an input (get) area and an output (put)
// area.  Each is described by three pointers: a beginning, an end, and a
// current position.  basic_streambuf<> contains some very simple member
// functions that manipulate those six pointers, but almost all of the real
// functionality gets delegated to protected virtual member functions.
// All of the public member functions are inline, and most of the protected
// member functions are virtual.

// Although basic_streambuf<> is not abstract, it is useful only as a base
// class.  Its virtual member functions have default definitions such that
// reading from a basic_streambuf<> will always yield EOF, and writing to a
// basic_streambuf<> will always fail.

// The second template parameter, _Traits, defaults to char_traits<_CharT>.
// The default is declared in header <iosfwd>, and it isn't declared here
// because C++ language rules do not allow it to be declared twice.

template <class _CharT, class _Traits>
class basic_streambuf {
  friend class basic_istream<_CharT, _Traits>;
  friend class basic_ostream<_CharT, _Traits>;

public:                         // Typedefs.
  typedef _CharT                     char_type;
  typedef typename _Traits::int_type int_type;
  typedef typename _Traits::pos_type pos_type;
  typedef typename _Traits::off_type off_type;
  typedef _Traits                    traits_type;

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
public:
  void _Lock() { _M_lock._M_acquire_lock(); }
  
  void _Unlock() { _M_lock._M_release_lock(); }
private:
  _STLP_mutex _M_lock;
#endif

private:      // Data members.
  char_type* _M_gbegin;            // Beginning of get area
  char_type* _M_pbegin;            // Beginning of put area
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  char_type** _M_p_gbegin;         // Pointer to beginning of get area
  char_type** _M_p_pbegin;         // Pointer to beginning of put area
#endif
  char_type* _M_gnext;          // Current position within the get area
  char_type* _M_pnext;          // Current position within the put area
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  char_type** _M_p_gnext;         // Pointer to beginning of get area
  char_type** _M_p_pnext;         // Pointer to beginning of put area
#endif
  int _M_gcount;           // End of get area
  int _M_pcount;           // End of put area
#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
  int* _M_p_gcount;           // End of get area
  int* _M_p_pcount;           // End of put area
#endif
  locale* _M_locale;             // The streambuf's locale object

public:                         // Destructor.
  virtual ~basic_streambuf();

protected:                      // The default constructor.
  basic_streambuf();

protected:                      // Protected interface to the get area.
  char_type* eback() const { return *_M_p_gbegin; } // Beginning
  char_type* gptr()  const { return *_M_p_gnext; }  // Current position
  char_type* egptr() const { return *_M_p_gnext + *_M_p_gcount; }   // End

  void gbump(int __n) { 
    *_M_p_gnext += __n; 
    *_M_p_gcount -= __n;
  }

  void setg(char_type* __gbegin, char_type* __gnext, char_type* __gend) {
    *_M_p_gbegin = __gbegin;
    *_M_p_gnext  = __gnext;
    *_M_p_gcount   = (int)(__gend - __gbegin);
  }
  streamsize _Pnavail() const { return *_M_p_pnext ? *_M_p_pcount : 0; }
  streamsize _Gnavail() const { return *_M_p_gnext ? *_M_p_gcount : 0; }
  char_type *_Gninc() { --*_M_p_gcount; return (*_M_p_gnext)++; }
  char_type *_Gnpreinc() { --*_M_p_gcount; return ++(*_M_p_gnext); }
  char_type *_Gndec()  { ++(*_M_p_gcount); return --(*_M_p_gnext); }
  char_type *_Pninc() { --*_M_p_pcount; return (*_M_p_pnext)++; }
  
public:
  // An alternate public interface to the above functions
  // which allows us to avoid using templated friends which
  // are not supported on some compilers.
  char_type* _M_gptr()  const { return gptr(); }
  char_type* _M_egptr() const { return egptr(); }
  void _M_gbump(int __n)      { gbump(__n); }


protected:                      // Protected interface to the put area

  char_type* pbase() const { return *_M_p_pbegin; } // Beginning
  char_type* pptr()  const { return *_M_p_pnext; }  // Current position
  char_type* epptr() const { return *_M_p_pnext + *_M_p_pcount; }   // End

  void pbump(int __n) {  
    *_M_p_pnext += __n; 
    *_M_p_pcount -= __n;
  }

  void setp(char_type* __pbegin, char_type* __pend) {
    *_M_p_pbegin = __pbegin;
    *_M_p_pnext  = __pbegin;
    *_M_p_pcount   = (int)(__pend-__pbegin);
  }

  void setp(char_type* __pbegin, char_type* __pnext, char_type* __pend) {
    *_M_p_pbegin = __pbegin;
    *_M_p_pnext  = __pnext;
    *_M_p_pcount   = (int)(__pend-__pbegin);
  }

protected:                      // Virtual buffer management functions.

  virtual basic_streambuf<_CharT, _Traits>* setbuf(char_type*, streamsize);

  // Alters the stream position, using an integer offset.  In this
  // class seekoff does nothing; subclasses are expected to override it.
  virtual pos_type seekoff(off_type, ios_base::seekdir,
                           ios_base::openmode = ios_base::in | ios_base::out);

  // Alters the stream position, using a previously obtained streampos.  In
  // this class seekpos does nothing; subclasses are expected to override it.
  virtual pos_type
  seekpos(pos_type, ios_base::openmode = ios_base::in | ios_base::out);

  // Synchronizes (i.e. flushes) the buffer.  All subclasses are expected to
  // override this virtual member function.
  virtual int sync();


public:                         // Buffer management.
  basic_streambuf<_CharT, _Traits>* pubsetbuf(char_type* __s, streamsize __n)   { return this->setbuf(__s, __n); }

  pos_type pubseekoff(off_type __offset, ios_base::seekdir __way,
		      ios_base::openmode __mod = ios_base::in | ios_base::out)
  { return this->seekoff(__offset, __way, __mod); }

  pos_type pubseekpos(pos_type __sp, ios_base::openmode __mod = ios_base::in | ios_base::out) 
  { return this->seekpos(__sp, __mod); }

  int pubsync() { return this->sync(); }

protected:                      // Virtual get area functions, as defined in
                                // 17.5.2.4.3 and 17.5.2.4.4 of the standard.
  // Returns a lower bound on the number of characters that we can read,
  // with underflow, before reaching end of file.  (-1 is a special value:
  // it means that underflow will fail.)  Most subclasses should probably
  // override this virtual member function.
  virtual streamsize showmanyc();

  // Reads up to __n characters.  Return value is the number of
  // characters read.
  virtual streamsize xsgetn(char_type* __s, streamsize __n);

  // Called when there is no read position, i.e. when gptr() is null
  // or when gptr() >= egptr().  Subclasses are expected to override
  // this virtual member function.
  virtual int_type underflow();

  // Similar to underflow(), but used for unbuffered input.  Most
  // subclasses should probably override this virtual member function.
  virtual int_type uflow();

  // Called when there is no putback position, i.e. when gptr() is null
  // or when gptr() == eback().  All subclasses are expected to override
  // this virtual member function.
  virtual int_type pbackfail(int_type = traits_type::eof());

protected:                      // Virtual put area functions, as defined in
                                // 27.5.2.4.5 of the standard.

  // Writes up to __n characters.  Return value is the number of characters
  // written.
  virtual streamsize xsputn(const char_type* __s, streamsize __n);

  // Extension: writes up to __n copies of __c.  Return value is the number
  // of characters written.
  virtual streamsize _M_xsputnc(char_type __c, streamsize __n);

  // Called when there is no write position.  All subclasses are expected to
  // override this virtual member function.
  virtual int_type overflow(int_type = traits_type::eof());

public:                         // Public members for writing characters.
  // Write a single character.
  int_type sputc(char_type __c) {
    return ( _Pnavail() ?  _Traits::to_int_type(*_Pninc() = __c) : this->overflow(_Traits::to_int_type(__c)));
  }

  // Write __n characters.
  streamsize sputn(const char_type* __s, streamsize __n) { return this->xsputn(__s, __n); }

  // Extension: write __n copies of __c.
  streamsize _M_sputnc(char_type __c, streamsize __n) { return this->_M_xsputnc(__c, __n); }

public:                         // Public members for reading characters.
  streamsize in_avail() {
    streamsize __ret(_Gnavail());
    return __ret > 0 ? __ret: this->showmanyc();
  }

  // Advance to the next character and return it.
  int_type snextc() {
    if ( _Gnavail() > 1 ) {
      return _Traits::to_int_type(*_Gnpreinc());
    } else {
      return _Traits::eq_int_type(sbumpc(), _Traits::eof()) ? _Traits::eof() : sgetc();
    }
  }
  
  // Return the current character and advance to the next.
  int_type sbumpc() {
    return _Gnavail() ? _Traits::to_int_type(*_Gninc()) : this->uflow();
  }
  
  // Return the current character without advancing to the next.
  int_type sgetc() {
    return _Gnavail() ? _Traits::to_int_type(**_M_p_gnext) : this->underflow();
  }

  streamsize sgetn(char_type* __s, streamsize __n) { return this->xsgetn(__s, __n); }
  
  
  int_type sputbackc(char_type __c) {
    return ((*_M_p_gbegin < *_M_p_gnext) && _Traits::eq(__c, *(*_M_p_gnext - 1))) ? _Traits::to_int_type(*_Gndec()) : this->pbackfail(_Traits::to_int_type(__c));
  }

  int_type sungetc() {
    return (gptr() != 0 && eback() < gptr()) ?  _Traits::to_int_type(*_Gndec()) : this->pbackfail();
  }

#ifdef _STLP_MSVC_BINARY_COMPATIBILITY 
protected:
  streamsize _Sgetn_s(char_type *__p, size_t __size, streamsize __n) {
    return _Xsgetn_s(__p, __size, __n);
  }
  virtual streamsize _Xsgetn_s(char_type *__p, size_t __size, streamsize __n);
  void _Init(char_type **__gbegin, char_type **__gnext, int *__gcount,
	     char_type **__pbegin, char_type **__pnext, int *__pcount) {
    _M_p_gbegin = __gbegin, _M_p_pbegin = __pbegin;
    _M_p_gnext = __gnext, _M_p_pnext = __pnext;
    _M_p_gcount = __gcount, _M_p_pcount = __pcount;
  }
#endif

protected:                      // Virtual locale functions.

  // This is a hook, called by pubimbue() just before pubimbue()
  // sets the streambuf's locale to __loc.  Note that imbue should
  // not (and cannot, since it has no access to streambuf's private
  // members) set the streambuf's locale itself.
  virtual void imbue(const locale&);

public:                         // Locale-related functions.
  locale pubimbue(const locale&);
  locale getloc() const { return *_M_locale; }

#if !defined (_STLP_NO_ANACHRONISMS)
  void stossc() { this->sbumpc(); }
#endif


};

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS basic_streambuf<char, char_traits<char> >;
#  if !defined (_STLP_NO_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS basic_streambuf<wchar_t, char_traits<wchar_t> >;
#  endif // _STLP_NO_WCHAR_T
#endif // _STLP_USE_TEMPLATE_EXPORT

_STLP_END_NAMESPACE

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION)
#  include <stl/_streambuf.c>
#endif

#endif

// Local Variables:
// mode:C++
// End:
