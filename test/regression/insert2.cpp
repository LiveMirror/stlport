// STLport regression testsuite component.
// To compile as a separate example, please #define MAIN.

#include <iostream>
#include <deque>
#include <algorithm>

#ifdef MAIN 
#define insert2_test main
#endif

#if !defined (STLPORT) || defined(__STL_USE_NAMESPACES)
using namespace std;
#endif

int insert2_test(int, char**)
{
  cout<<"Results of insert2_test:"<<endl;
  char* array1 [] = { "laurie", "jennifer", "leisa" };
  char* array2 [] = { "amanda", "saskia", "carrie" };

  deque<char*> names(array1, array1 + 3);
  deque<char*>::iterator i = names.begin() + 2;
  copy(array2, array2 + 3, inserter(names, i));
  deque<char*>::iterator j;
  for(j = names.begin(); j != names.end(); j++)
    cout << *j << endl;
  return 0;
}
