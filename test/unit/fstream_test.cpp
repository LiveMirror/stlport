#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class FstreamTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(FstreamTest);
  CPPUNIT_TEST(output);
  CPPUNIT_TEST(input);
  CPPUNIT_TEST(io);
  CPPUNIT_TEST(err);
  CPPUNIT_TEST(tellg);
  CPPUNIT_TEST(buf);
  CPPUNIT_TEST(rdbuf);
  CPPUNIT_TEST(eofloop);
  CPPUNIT_TEST_SUITE_END();

  protected:
    void output();
    void input();
    void io();
    void err();
    void tellg();
    void buf();
    void rdbuf();
    void eofloop();
};

CPPUNIT_TEST_SUITE_REGISTRATION(FstreamTest);

//
// tests implementation
//
void FstreamTest::output()
{
  ofstream f( "test_file.txt" );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";
  CPPUNIT_ASSERT (f.good());
  // CPPUNIT_ASSERT( s.str() == "1\n2\nabcd\nghk lm\nabcd ef" );
}

void FstreamTest::input()
{
  ifstream f( "test_file.txt" );
  int i = 0;
  f >> i;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  f >> d;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( d == 2.0 );
  string str;
  f >> str;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( str == "abcd" );
  char c = f.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( f, str );
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( str == "ghk lm" );
  getline( f, str );
  CPPUNIT_ASSERT( f.eof() );
  CPPUNIT_ASSERT( str == "abcd ef" );
}

void FstreamTest::io()
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  CPPUNIT_ASSERT( f.is_open() );

  f << 1 << '\n' << 2.0 << '\n' << "abcd\n" << "ghk lm\n" << "abcd ef";

  // f.flush();
  f.seekg( 0, ios_base::beg );

  int i = 0;
  f >> i;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( i == 1 );
  double d = 0.0;
  f >> d;
  CPPUNIT_ASSERT( d == 2.0 );
  string s;
  f >> s;
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( s == "abcd" );
  char c = f.get(); // extract newline, that not extracted by operator >>
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( c == '\n' );
  getline( f, s );
  CPPUNIT_ASSERT( f.good() );
  CPPUNIT_ASSERT( s == "ghk lm" );
  getline( f, s );
  CPPUNIT_ASSERT( !f.fail() );
  CPPUNIT_ASSERT( s == "abcd ef" );
  CPPUNIT_ASSERT( f.eof() );
}

void FstreamTest::err()
{
  basic_fstream<char,char_traits<char> > f( "test_file.txt", ios_base::in | ios_base::out | ios_base::trunc );

  CPPUNIT_ASSERT( f.is_open() );

  int i = 9;
  f << i;
  CPPUNIT_ASSERT( f.good() );
  i = 0;
  f.seekg( 0, ios_base::beg );
  f >> i;
  CPPUNIT_ASSERT( !f.fail() );
  CPPUNIT_ASSERT( i == 9 );
  f >> i;
  CPPUNIT_ASSERT( f.fail() );
  CPPUNIT_ASSERT( f.eof() );
  CPPUNIT_ASSERT( i == 9 );
}

void FstreamTest::tellg()
{
  // bogus ios_base::binary is for Wins
  ofstream of( "test_file.txt", ios_base::out | ios_base::binary | ios_base::trunc );
  CPPUNIT_ASSERT( of.is_open() );
  int i;

  for ( i = 0; i < 50; ++i ) {
    of << "line " << setiosflags(ios_base::right) << setfill('0') << setw(2) << i << "\n";
  }
  of.close();
  // bogus ios_base::binary is for Wins
  ifstream is( "test_file.txt", ios_base::in | ios_base::binary );
  CPPUNIT_ASSERT( is.is_open() );
  string line;
  char buf[64];

  // CPPUNIT_ASSERT( is.tellg() == 0 );
  ifstream::streampos p = 0;
  for ( i = 0; i < 50; ++i ) {
    CPPUNIT_ASSERT( is.tellg() == p );
    // getline( is, line, '\n' );
    is.read( buf, 8 );
    CPPUNIT_ASSERT( !is.fail() );
    p += 8;
  }
}

void FstreamTest::buf()
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );
  char buf[10];
  buf[7] = 'x';
  ss.get( buf, 10 );
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( buf[0] == '1' );
  CPPUNIT_ASSERT( buf[1] == '2' );
  CPPUNIT_ASSERT( buf[2] == '3' );
  CPPUNIT_ASSERT( buf[3] == '4' );
  CPPUNIT_ASSERT( buf[4] == '5' );
  CPPUNIT_ASSERT( buf[5] == '6' );
  CPPUNIT_ASSERT( buf[6] == '7' ); // 27.6.1.3 paragraph 10, paragraph 7
  CPPUNIT_ASSERT( buf[7] == 0 ); // 27.6.1.3 paragraph 8
  char c;
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 10, paragraph 7
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '8' );
}

void FstreamTest::rdbuf()
{
  fstream ss( "test_file.txt", ios_base::in | ios_base::out | ios_base::binary | ios_base::trunc );

  ss << "1234567\n89\n";
  ss.seekg( 0, ios_base::beg );

  ostringstream os;
  ss.get( *os.rdbuf(), '\n' );
  CPPUNIT_ASSERT( !ss.fail() );
  char c;
  c = ss.get();
  CPPUNIT_ASSERT( !ss.fail() );
  CPPUNIT_ASSERT( c == '\n' ); // 27.6.1.3 paragraph 12
  CPPUNIT_ASSERT( os.str() == "1234567" );
}

/* a streambuffer that always returns EOF when written to, this seems to be all that is needed to show the problem. */

class full_streambuf :
    public std::streambuf
{
  public:
    typedef std::streambuf::int_type int_type;
    typedef std::streambuf::traits_type traits_type;
    
    full_streambuf()
    {}

  protected:
    int_type overflow(int_type c)
    {
      return traits_type::eof();
    }
};

void FstreamTest::eofloop()
{
  ofstream of( "test_file.txt", ios_base::out | ios_base::binary | ios_base::trunc );
  // write zeroes into of
  of.write( "\0\0\0\0", 4 );
  of.close();

  ifstream in( "test_file.txt", ios_base::in | ios_base::binary );
  full_streambuf *sb = new full_streambuf;
  {
    ostream out( sb );
    out << in.rdbuf() << flush;
  }
  delete sb;
}

