// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

#ifdef MAIN
#define ioiter_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int ioiter_test( int, char ** )
{
  cout << "Results of ioiter: " << endl;
  char c;
  char *pc;
  char *strorg = "abcd";
  std::string expected( "abcd" );
  std::string tmp;

  std::string objStr(strorg);

  std::istringstream objIStrStrm1(objStr);
  std::istringstream objIStrStrm2(objStr);
  std::istringstream objIStrStrm3(objStr);

  cout << "plain C-string postfix increment operator and indirection: ";
  pc = strorg;
  std::string::size_type sz = strlen(strorg);
  for ( std::string::size_type i = 0; i < sz; ++i ) {
    c = *pc++;
    tmp += c;
    std::cout << c;
  }
  std::cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << std::endl;

  cout << "postfix increment operator and indirection: ";

  std::istreambuf_iterator<char> objIStrmbIt1( objIStrStrm1.rdbuf() );
  std::istreambuf_iterator<char> end;

  // objIStrmbIt1 != end;

  tmp.clear();

  for ( std::string::size_type i = 0; i < sz /* objIStrmbIt1 != end */; ++i ) {
    c = *objIStrmbIt1++;
    tmp += c;
    std::cout << c;
  }
  std::cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << std::endl;

  cout << "indirection, then postfix increment operator: ";

  tmp.clear();

  std::istreambuf_iterator<char> objIStrmbIt2( objIStrStrm2.rdbuf() );
  for ( std::string::size_type i = 0; i < sz; ++i ) {
    c = *objIStrmbIt2;
    tmp += c;
    std::cout << c;
    objIStrmbIt2++;
  }
  std::cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << std::endl;

  tmp.clear();

  cout << "compare, then postfix increment operator and indirection: ";

  std::istreambuf_iterator<char> objIStrmbIt3( objIStrStrm3.rdbuf() );

  while ( objIStrmbIt3 != end ) {
    c = *objIStrmbIt3++;
    tmp += c;
    std::cout << c;
  }
  std::cout << " ... " << ( tmp == expected ? "pass" : "fail" ) << std::endl;

  return 0;
}
