#ifndef _FULL_STREAM_H
#define _FULL_STREAM_H

#include <streambuf>

/*
 * This full_streambuf purpose is to act like a full disk to check the right behavior
 * of the STLport code in such a case.
 */

class full_streambuf : public std::streambuf {
public:
  typedef std::streambuf::int_type int_type;
  typedef std::streambuf::traits_type traits_type;

  full_streambuf(size_t nb_output, bool do_throw = false)
    : _nb_output(nb_output), _do_throw(do_throw)
  {}

protected:
  int_type overflow(int_type c) {
    if (_nb_output == 0) {
#if !defined (_STLP_NO_EXCEPTIONS)
      if (_do_throw) {
        throw "streambuf full";
      }
#endif
      return traits_type::eof();
    }
    --_nb_output;
    return c;
  }

private:
  size_t _nb_output;
  bool _do_throw;
};

#endif //_FULL_STREAM_H
