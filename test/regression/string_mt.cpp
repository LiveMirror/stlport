// -*- C++ -*- Time-stamp: <03/09/23 09:12:29 ptr>

#include <string>

#ifdef _PTHREADS
# include <pthread.h>
#endif

#ifdef MAIN
#define string_mt_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

string func( const string& par )
{
  string tmp( par );

  return tmp;
}

void *f( void * )
{
  string s( "qyweyuewunfkHBUKGYUGL,wehbYGUW^(@T@H!BALWD:h^&@#*@(#:JKHWJ:CND" );

  for ( int i = 0; i < 2000000; ++i ) {
    string sx = func( s );
  }

  return 0;
}

int string_mt_test( int, char * const * )
{
  const int nth = 2;
#ifdef _PTHREADS
  pthread_t t[nth];

  for ( int i = 0; i < nth; ++i ) {
    pthread_create( &t[i], 0, f, 0 );
  }

  for ( int i = 0; i < nth; ++i ) {
    pthread_join( t[i], 0 );
  }
#endif // _PTHREADS

  return 0;
}
