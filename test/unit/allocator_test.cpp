#include <memory>

#include "cppunit/cppunit_proxy.h"

#if !defined (STLPORT) || defined(_STLP_USE_NAMESPACES)
using namespace std;
#endif

//
// TestCase class
//
class AllocatorTest : public CPPUNIT_NS::TestCase
{
  CPPUNIT_TEST_SUITE(AllocatorTest);
#if !defined (_STLP_NO_EXCEPTIONS)
  CPPUNIT_TEST(bad_alloc_test);
#endif
  CPPUNIT_TEST_SUITE_END();

protected:
  void bad_alloc_test();
};

CPPUNIT_TEST_SUITE_REGISTRATION(AllocatorTest);

//
// tests implementation
//

#if !defined (_STLP_NO_EXCEPTIONS)

struct BigStruct 
{
  char _data[4096];
};

void AllocatorTest::bad_alloc_test()
{
  typedef allocator<BigStruct> BigStructAllocType;
  BigStructAllocType bigStructAlloc;

  try {
    //Lets try to allocate almost 4096 Go (on most of the platforms) of memory:
    BigStructAllocType::pointer pbigStruct = bigStructAlloc.allocate(1024 * 1024 * 1024);

    CPPUNIT_ASSERT( pbigStruct != 0 && "Allocation failed but no exception thrown" );
  }
  catch (bad_alloc const&) {
  }
  catch (...) {
    //We shouldn't be there:
    CPPUNIT_ASSERT( false && "Not bad_alloc exception thrown." );
  }
}
#endif
