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

#if defined  (__SUNPPRO_CC)  && !defined (_STLP_NO_NEW_C_HEADERS)
#  include <time.h>
// For sunpro, it chokes if time.h is included through stat.h
#endif

#include <fstream>

#ifdef __CYGWIN__
#  define __int64 long long
#endif

#include <cstdio>
#if !defined(__ISCPP__)
extern "C" {
#  include <sys/stat.h>
}
#endif

#if defined( __MSL__ )
#  include <unix.h>
#endif

#if defined(__ISCPP__)
#  include <c_locale_is/filestat.h>
#endif

#if defined(__BEOS__) && defined(__INTEL__)
#  include <fcntl.h>
#  include <sys/stat.h>         // For _fstat
#endif

#if defined (_STLP_MSVC) || defined (__MINGW32__)
#  include <fcntl.h>

#  define S_IREAD _S_IREAD
#  define S_IWRITE _S_IWRITE
#  define S_IFREG _S_IFREG
     // map permission masks
#  ifndef S_IRUSR
#    define S_IRUSR _S_IREAD
#    define S_IWUSR _S_IWRITE
#  endif
#  ifndef S_IRGRP
#    define S_IRGRP _S_IREAD
#    define S_IWGRP _S_IWRITE
#  endif
#  ifndef S_IROTH
#    define S_IROTH _S_IREAD
#    define S_IWOTH _S_IWRITE
#  endif

#  ifndef O_RDONLY
#    define O_RDONLY _O_RDONLY
#    define O_WRONLY _O_WRONLY
#    define O_RDWR   _O_RDWR
#    define O_APPEND _O_APPEND
#    define O_CREAT  _O_CREAT
#    define O_TRUNC  _O_TRUNC
#    define O_TEXT   _O_TEXT
#    define O_BINARY _O_BINARY
#  endif

#  ifndef O_ACCMODE
#    define O_ACCMODE (O_RDONLY|O_WRONLY|O_RDWR)
#  endif
#endif

const int INVALID_STLP_FD = -1;


#  ifdef __MSL__
#    define _O_TEXT 0x0
#    if !defined( O_TEXT )
#      define O_TEXT _O_TEXT
#    endif
#    define _S_IFREG S_IFREG
#    define S_IREAD        S_IRUSR
#    define S_IWRITE       S_IWUSR
#    define S_IEXEC        S_IXUSR
#    define _S_IWRITE S_IWRITE
#    define _S_IREAD S_IREAD
#    define _open open
#    define _close close
#    define _read read
#    define _write write
#  endif

_STLP_BEGIN_NAMESPACE

// Compare with streamoff definition in stl/char_traits.h!

#if defined (_STLP_USE_DEFAULT_FILE_OFFSET) || \
    (!defined(_LARGEFILE_SOURCE) && !defined(_LARGEFILE64_SOURCE))
#  define FOPEN fopen
#  define FSEEK fseek
#  define FSTAT fstat
#  define STAT  stat
#  define FTELL ftell
#else
#  define FOPEN fopen64
#  define FSEEK fseeko64
#  define FSTAT fstat64
#  define STAT  stat64
#  define FTELL ftello64
#endif

/*
bool _Filebuf_base::__regular_file() {
  struct STAT buf;
  return _M_should_close && (FSTAT(__get_fd(), &buf) == 0 && (buf.st_mode & S_IFREG) != 0);
}
*/



// Return the size of the file.  This is a wrapper for stat.
// Returns zero if the size cannot be determined or is ill-defined.
streamoff _Filebuf_base::_M_file_size()
{
  streamoff ret = 0;

  struct STAT buf;
  if (FSTAT(_fileno(_M_file), &buf) == 0 && (buf.st_mode & S_IFREG) != 0)
    ret = buf.st_size > 0 ? buf.st_size : 0;

  return ret;
}

bool _Filebuf_base::_M_open(const char* name, ios_base::openmode openmode,
                            int permission)
{

  if ( _M_file ) {
    return false;
  }

  // use FILE-based i/o
  const char* flags;

  switch (openmode & (~ios_base::ate)) {
    case ios_base::out:
    case ios_base::out | ios_base::trunc:
      flags = "w";
      break;

    case ios_base::out | ios_base::binary:
    case ios_base::out | ios_base::trunc | ios_base::binary:
      flags = "wb";
      break;

    case ios_base::out | ios_base::app:
      flags = "a";
      break;

    case ios_base::out | ios_base::app | ios_base::binary:
      flags = "ab";
      break;

    case ios_base::in:
      flags = "r";
      break;

    case ios_base::in | ios_base::binary:
      flags = "rb";
      break;

    case ios_base::in | ios_base::out:
      flags = "r+";
      break;

    case ios_base::in | ios_base::out | ios_base::binary:
      flags = "r+b";
      break;

    case ios_base::in | ios_base::out | ios_base::trunc:
      flags = "w+";
      break;

    case ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary:
      flags = "w+b";
      break;

    default:                      // The above are the only combinations of
      return false;               // flags allowed by the C++ standard.
  }

  // fbp : TODO : set permissions !
  (void)permission; // currently unused    //*TY 02/26/2000 - added to suppress warning message
  FILE* f = FOPEN(name, flags);

  return _M_open(f, openmode);
}



bool _Filebuf_base::_M_open(FILE* f, ios_base::openmode openmode)
{
  _M_file = f;

  if (!_M_file) {
    return false;
  }

  _M_should_close = true;

  if (openmode & ios_base::ate) {
    if (FSEEK(_M_file, 0, SEEK_END) != 0) {
      _M_should_close = false;
    }
  }

  return _M_should_close;
}


bool _Filebuf_base::_M_open(const char* name, ios_base::openmode openmode)
{
  // This doesn't really grant everyone in the world read/write
  // access.  On Unix, file-creation system calls always clear
  // bits that are set in the umask from the permissions flag.
  return this->_M_open(name, openmode, S_IRUSR | S_IWUSR | S_IRGRP |
                                       S_IWGRP | S_IROTH | S_IWOTH);
}

bool _Filebuf_base::_M_close()
{
  if (!_M_should_close) {
    return false;
  }

  fclose(_M_file);
  _M_file = 0;
  _M_should_close = false;

  return true;
}

// Read up to n characters into a buffer.  Return value is number of
// characters read.
ptrdiff_t _Filebuf_base::_M_read(char* buf, ptrdiff_t n) {
  return fread(buf, 1, n, _M_file);
}

// Write n characters from a buffer.  Return value: true if we managed
// to write the entire buffer, false if we didn't.
bool _Filebuf_base::_M_write(char* buf, ptrdiff_t n)
{
  for (;;) {
    ptrdiff_t written = fwrite(buf, 1, n, _M_file);

    if (n == written) {
      return true;
    }

    if (written > 0 && written < n) {
      n -= written;
      buf += written;
    } else {
      return false;
    }
  }
}

// Wrapper for lseek or the like.
streamoff _Filebuf_base::_M_seek(streamoff offset, ios_base::seekdir dir)
{
  int whence;

  switch ( dir ) {
    case ios_base::beg:
      if (offset < 0 /* || offset > _M_file_size() */ )
        return streamoff(-1);
      whence = SEEK_SET;
      break;
    case ios_base::cur:
      whence = SEEK_CUR;
      break;
    case ios_base::end:
      if (/* offset > 0 || */  -offset > _M_file_size() )
        return streamoff(-1);
      whence = SEEK_END;
      break;
    default:
      return streamoff(-1);
  }

  if ( FSEEK(_M_file, offset, whence) == 0 ) {
    return FTELL(_M_file);
  }

  return streamoff(-1);
}

_STLP_END_NAMESPACE
