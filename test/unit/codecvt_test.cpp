#include <string>

#if !defined (STLPORT) || !defined (_STLP_USE_NO_IOSTREAMS)
#  include <fstream>
#  include <locale>

#  include "cppunit/cppunit_proxy.h"

#  if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#  endif

//
// TestCase class
//
class CodecvtTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(CodecvtTest);
  CPPUNIT_TEST(variable_encoding);
  CPPUNIT_TEST_SUITE_END();

protected:
  void variable_encoding();
};

CPPUNIT_TEST_SUITE_REGISTRATION(CodecvtTest);

#if defined (STLPORT)
#  define __NO_THROW _STLP_NOTHROW
#else
#  define __NO_THROW throw()
#endif


/* Codecvt facet eating some characters from the external buffer.
 * Transform '01' in 'a'
 */
struct eater_codecvt : codecvt<char, char, mbstate_t> {
    typedef codecvt<char,char,mbstate_t> base;

    explicit eater_codecvt(size_t refs = 0) : base(refs) {}

    // primitive conversion
    virtual base::result
    do_in(mbstate_t& mb,
          const char* ebegin, const char* eend, const char*& ecur,
          char* ibegin, char* iend, char*& icur) const __NO_THROW {
        ecur = ebegin;
        icur = ibegin;

        while (ecur != eend) {
            if (icur == iend)
                return partial;
            if (*ecur == '0' || mb == 1) {
              if (mb != 1) {
                ++ecur;
              }
              if (ecur == eend) {
                mb = 1;
                return ok;
              }

              if (*ecur == '1') {
                *icur = 'a';
              }
              else {
                *(icur++) = '0';
                if (icur == iend) {
                  if (mb != 1) {
                    --ecur;
                  }
                  return partial;
                }
                *icur = *ecur;
              }
            }
            else {
              *icur = *ecur;
            }

            mb = 0;
            ++icur;
            ++ecur;
        }

        return ok;
    }

    // claim it's not a null-conversion
    virtual bool do_always_noconv() const __NO_THROW
    { return false; }

    // claim it doesn't have a fixed-length encoding
    virtual int do_encoding() const __NO_THROW
    { return 0; }

    // implemented for consistency with do_in overload
    virtual int do_length(const mbstate_t &state,
                          const char *efrom, const char *eend, size_t m) const {
      char *ibegin = new char[m];
      const char *ecur = efrom;
      try {
        char *icur = ibegin;
        mbstate_t tmp = state;
        do_in(tmp, efrom, eend, ecur, ibegin, ibegin + m, icur);
      }
      catch (...) {
        delete[] ibegin;
        throw;
      }

      delete[] ibegin;
      return ecur - efrom;
    }

    virtual int do_max_length() const __NO_THROW
    { return 2; }
};

/* Codecvt facet generating more characters than the ones read from the
 * external buffer, transform '01' in 'abc'
 * This kind of facet do not allow systematical positionning in the external
 * buffer (tellg -> -1), when you just read a 'a' you are at an undefined
 * external buffer position.
 */
struct generator_codecvt : codecvt<char, char, mbstate_t>
{
    typedef codecvt<char,char,mbstate_t> base;

    explicit generator_codecvt(size_t refs = 0) : base(refs) {}

    // primitive conversion
    virtual base::result
    do_in(mbstate_t& mb,
          const char* ebegin, const char* eend, const char*& ecur,
          char* ibegin, char* iend, char*& icur) const __NO_THROW {
        ecur = ebegin;
        icur = ibegin;

        if (icur == iend) {
          return ok;
        }

        switch (mb) {
          case 2:
            *(icur++) = 'b';
            if (icur == iend) {
              mb = 3;
              return partial;
            }
          case 3:
            *(icur++) = 'c';
            mb = 0;
        }

        while (ecur != eend) {
            if (icur == iend)
                return ok;
            if (*ecur == '0' || mb == 1) {
              if (mb != 1) {
                ++ecur;
              }
              if (ecur == eend) {
                mb = 1;
                return ok;
              }

              if (*ecur == '1') {
                *(icur++) = 'a';
                if (icur == iend) {
                  mb = 2;
                  return partial;
                }
                *(icur++) = 'b';
                if (icur == iend) {
                  mb = 3;
                  return partial;
                }
                *icur = 'c';
              }
              else {
                *(icur++) = '0';
                if (icur == iend) {
                  if (mb != 1) {
                    --ecur;
                  }
                  return partial;
                }
                *icur = *ecur;
              }
            }
            else {
              *icur = *ecur;
            }

            mb = 0;
            ++icur;
            ++ecur;
        }

        return ok;
    }

    // claim it's not a null-conversion
    virtual bool do_always_noconv() const __NO_THROW
    { return false; }

    // claim it doesn't have a fixed-length encoding
    virtual int do_encoding() const __NO_THROW
    { return 0; }

    // implemented for consistency with do_in overload
    virtual int do_length(const mbstate_t &state,
                          const char *efrom, const char *eend, size_t m) const {
      char *ibegin = new char[m];
      const char *ecur = efrom;
      try {
        char *icur = ibegin;
        mbstate_t tmpState = state;
        do_in(tmpState, efrom, eend, ecur, ibegin, ibegin + m, icur);
        if (tmpState != 0) {
          switch (tmpState) {
            case 1:
              --ecur;
              break;
            case 2:
            case 3:
              //Undefined position, we return -1:
              ecur = efrom - 1;
              break;
          }
        }
        else {
          if (state != 0) {
            //We take into account the character that hasn't been counted yet in
            //the previous decoding step:
            ecur++;
          }
        }
      }
      catch (...) {
        delete[] ibegin;
        throw;
      }

      delete[] ibegin;
      return ecur - efrom;
    }

    virtual int do_max_length() const __NO_THROW
    { return 0; }
};

//
// tests implementation
//
void CodecvtTest::variable_encoding()
{
  //We first generate the file used for test:
  const char* fileName = "test_file.txt";
  {
    ofstream ostr(fileName);
    //Maybe we simply do not have write access to repository
    CPPUNIT_ASSERT( ostr.good() );
    for (int i = 0; i < 2048; ++i) {
      ostr << "0123456789";
    }
    CPPUNIT_ASSERT( ostr.good() );
  }

  {
    ifstream istr(fileName);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( !istr.eof() );

    eater_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( (int)istr.tellg() == 0 );

    int theoricalPos = 0;
    do {
      char c = istr.get();
      if (c == char_traits<char>::eof()) {
        break;
      }
      ++theoricalPos;
      if (c == 'a') {
        ++theoricalPos;
      }

      CPPUNIT_ASSERT( (int)istr.tellg() == theoricalPos );
    }
    while (!istr.eof());

    CPPUNIT_ASSERT( istr.eof() );
  }

#if 0
  {
    ifstream istr(fileName);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( !istr.eof() );

    generator_codecvt codec(1);
    locale loc(locale::classic(), &codec);

    istr.imbue(loc);
    CPPUNIT_ASSERT( istr.good() );
    CPPUNIT_ASSERT( (int)istr.tellg() == 0 );

    int theoricalPos = 0;
    int tellgExpectedResult;
    do {
      char c = istr.get();
      if (c == char_traits<char>::eof()) {
        break;
      }
      ++theoricalPos;
      switch (c) {
        case 'a':
        case 'b':
          --theoricalPos;
          tellgExpectedResult = -1;
          break;
        case 'c':
          ++theoricalPos;
        default:
          tellgExpectedResult = theoricalPos;
          break;
      }

      if ((int)istr.tellg() != tellgExpectedResult) {
        CPPUNIT_ASSERT( (int)istr.tellg() == tellgExpectedResult );
      }
    }
    while (!istr.eof());

    CPPUNIT_ASSERT( istr.eof() );
  }
#endif
}

#endif
