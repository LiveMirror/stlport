#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <slist>
#include <list>
#include <deque>
#include <iostream>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class MoveConstructorTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(MoveConstructorTest);
  CPPUNIT_TEST(move_construct_test);
  CPPUNIT_TEST(move_traits);
  CPPUNIT_TEST_SUITE_END();

protected:
  void move_construct_test();
  void move_traits();

  template <class _Container>
  void standard_test1(_Container const& ref_cont) {
    vector<_Container> vec_cont(1, ref_cont);
    typedef typename _Container::value_type value_type;
    value_type *pvalue = &(*vec_cont.front().begin());
    size_t cur_capacity= vec_cont.capacity();
    //force reallocation
    while (cur_capacity == vec_cont.capacity()) {
      vec_cont.push_back(ref_cont);
    }
    bool b=( (pvalue==(&(*vec_cont.front().begin()))) );
    CPPUNIT_ASSERT(b);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(MoveConstructorTest);

//
// tests implementation
//
void MoveConstructorTest::move_construct_test()
{
  //cout << "vector<vector<int>>";
  vector<int> const ref_vec(10, 0);
  vector<vector<int> > v_v_ints(1, ref_vec);

  int *pint = &(v_v_ints.front().front());

  size_t cur_capacity = v_v_ints.capacity();
  while (v_v_ints.capacity() <= cur_capacity) {
    v_v_ints.push_back(ref_vec);
  }

  //v_v_ints has been resized
  CPPUNIT_ASSERT((pint == &v_v_ints.front().front()));

  //cout << "vector<vector<int>>::erase";
  //We need at least 3 elements:
  while (v_v_ints.size() < 3) {
    v_v_ints.push_back(ref_vec);
  }

  //We erase the 2nd
  pint = &v_v_ints[2].front();
  v_v_ints.erase(v_v_ints.begin() + 1);
  CPPUNIT_ASSERT((pint == &v_v_ints[1].front()));

  //cout << "vector<string>";
  string const ref_str("ref string, big enough to be a dynamic one");
  vector<string> vec_strs(1, ref_str);

  char const* pstr = vec_strs.front().c_str();
  cur_capacity = vec_strs.capacity();
  while (vec_strs.capacity() <= cur_capacity) {
    vec_strs.push_back(ref_str);
  }

  //vec_str has been resized
  CPPUNIT_ASSERT((pstr == vec_strs.front().c_str()));

  //cout << "vector<string>::erase";
  //We need at least 3 elements:
  while (vec_strs.size() < 3) {
    vec_strs.push_back(ref_str);
  }

  //We erase the 2nd
  pstr = vec_strs[2].c_str();
  vec_strs.erase(vec_strs.begin() + 1);
  CPPUNIT_ASSERT((pstr == vec_strs[1].c_str()));

  //cout << "swap(vector<int>, vector<int>)";
  vector<int> elem1(10, 0), elem2(10, 0);
  int *p1 = &elem1.front();
  int *p2 = &elem2.front();
  swap(elem1, elem2);
  CPPUNIT_ASSERT(((p1 == &elem2.front()) && (p2 == &elem1.front())));

  {
    vector<bool> bit_vec(5, true);
    bit_vec.insert(bit_vec.end(), 5, false);
    vector<vector<bool> > v_v_bits(1, bit_vec);

    /*
     * This is a STLport specific test as we are using internal implementation
     * details to check that the move has been correctly handled. For other
     * STL implementation it is only a compile check.
     */
#ifdef STLPORT
#  if defined (_STLP_DEBUG)
    unsigned int *punit = v_v_bits.front().begin()._M_iterator._M_p;
#  else
    unsigned int *punit = v_v_bits.front().begin()._M_p;
#  endif
#endif

    size_t cur_capacity = v_v_bits.capacity();
    while (v_v_bits.capacity() <= cur_capacity) {
      v_v_bits.push_back(bit_vec);
    }

#ifdef STLPORT
    //v_v_bits has been resized
#  if defined (_STLP_DEBUG)
    CPPUNIT_ASSERT( punit == v_v_bits.front().begin()._M_iterator._M_p );
#  else
    CPPUNIT_ASSERT( punit == v_v_bits.front().begin()._M_p );
#  endif
#endif
  }

  // zero: don't like this kind of tests
  // because of template test function 
  // we should find another way to provide
  // move constructor testing...

/*
  standard_test1(list<int>(10));


  standard_test1(slist<int>(10));

  standard_test1(deque<int>(10));
*/

  /*
  int int_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  set<int> int_set(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_set);
  
  multiset<int> int_multiset(int_values, int_values + sizeof(in_values) / sizeof(int));
  standard_test1(int_multiset);
  */

  /*
  CheckFullMoveSupport(string());
  CheckFullMoveSupport(vector<int>());
  CheckFullMoveSupport(deque<int>());
  CheckFullMoveSupport(list<int>());
  CheckFullMoveSupport(slist<int>());
  */
}

#ifdef STLPORT
struct MovableStruct {
  MovableStruct() {
    ++nb_dft_construct_call;
  }
  MovableStruct(MovableStruct const&) {
    ++nb_cpy_construct_call;
  }
  MovableStruct(__move_source<MovableStruct>) {
    ++nb_mv_construct_call;
  }

  ~MovableStruct() {
    ++nb_destruct_call;
  }

  static unsigned int nb_dft_construct_call;
  static unsigned int nb_cpy_construct_call;
  static unsigned int nb_mv_construct_call;
  static unsigned int nb_destruct_call;
};

unsigned int MovableStruct::nb_dft_construct_call = 0;
unsigned int MovableStruct::nb_cpy_construct_call = 0;
unsigned int MovableStruct::nb_mv_construct_call = 0;
unsigned int MovableStruct::nb_destruct_call = 0;

namespace std {
  _STLP_TEMPLATE_NULL
  struct __move_traits<MovableStruct> {
    typedef __true_type implemented;
    typedef __false_type complete;
  };
}

struct CompleteMovableStruct {
  CompleteMovableStruct() {
    ++nb_dft_construct_call;
  }
  CompleteMovableStruct(CompleteMovableStruct const&) {
    ++nb_cpy_construct_call;
  }
  CompleteMovableStruct(__move_source<CompleteMovableStruct>) {
    ++nb_mv_construct_call;
  }

  ~CompleteMovableStruct() {
    ++nb_destruct_call;
  }

  static unsigned int nb_dft_construct_call;
  static unsigned int nb_cpy_construct_call;
  static unsigned int nb_mv_construct_call;
  static unsigned int nb_destruct_call;
};

unsigned int CompleteMovableStruct::nb_dft_construct_call = 0;
unsigned int CompleteMovableStruct::nb_cpy_construct_call = 0;
unsigned int CompleteMovableStruct::nb_mv_construct_call = 0;
unsigned int CompleteMovableStruct::nb_destruct_call = 0;

namespace std {
  _STLP_TEMPLATE_NULL
  struct __move_traits<CompleteMovableStruct> {
    typedef __true_type implemented;
    typedef __true_type complete;
  };
}
#endif //STLPORT

void MoveConstructorTest::move_traits()
{
  //Only relevant for an STLport test:
#ifdef STLPORT
  {
    {
      vector<MovableStruct> vect;
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());
      vect.push_back(MovableStruct());

      // vect contains 4 elements
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 3 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 7 );

      vect.insert(vect.begin() + 2, vect.begin(), vect.end());

      // vect contains 8 elements
      CPPUNIT_ASSERT( MovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( MovableStruct::nb_cpy_construct_call == 8 );
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 11 );

      vect.erase(vect.begin(), vect.begin() + 2 );

      // vect contains 6 elements
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 13 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 19 );

      vect.erase(vect.begin());

      // vect contains 5 elements
      CPPUNIT_ASSERT( MovableStruct::nb_mv_construct_call == 18 );
      CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 25 );
    }
    CPPUNIT_ASSERT( MovableStruct::nb_destruct_call == 30 );
  }

  {
    {
      vector<CompleteMovableStruct> vect;
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());
      vect.push_back(CompleteMovableStruct());

      // vect contains 4 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_cpy_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 3 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 4 );

      vect.insert(vect.begin() + 2, vect.begin(), vect.end());

      // vect contains 8 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_dft_construct_call == 4 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_cpy_construct_call == 8 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 7 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 4 );

      vect.erase(vect.begin(), vect.begin() + 2);

      // vect contains 6 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 13 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 6 );

      vect.erase(vect.begin());

      // vect contains 5 elements
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_mv_construct_call == 18 );
      CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 7 );
    }
    CPPUNIT_ASSERT( CompleteMovableStruct::nb_destruct_call == 12 );
  }
#endif //STLPORT
}
