# -*- Makefile -*- Time-stamp: 
# $Id: bc56.mak

#!message build\test\unit\bc56.mak

.AUTODEPEND

COMPILER_NAME = bc56

!ifndef BC5ROOT
BC5ROOT   = $(MAKEDIR)\..
!endif

STLPORT_DIR   = ..\..\..
SRCROOT       = $(STLPORT_DIR)\build
SRCDIR        = $(STLPORT_DIR)\test\unit

ALL_TAGS      = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static
 
!include Makefile.inc
 
LIB_VERSION   = stlp$(LIBMAJOR)$(LIBMINOR)
 
INCLUDES      = $(SRCDIR);$(SRCDIR)\cppunit

DEFS          = CPPUNIT_MINI

# Macro to temporarily exclude specific unit tests.
EXCLUDE_TESTS          = 1

!ifdef EXCLUDE_TESTS
ALLORIG                = $(SRC_CPP) $(SRC_CC) $(SRC_C)
EXCLUDE_BASE           = $(ALLORIG:../../../test/unit/=)

# Edit this section to temporarily exclude specific unit tests. 
# Each line excludes one source file. 
# All source files are listed in makefile.inc
# EXCLUDE_[excluded]   = $(EXCLUDE_[previous]: [excluded].cpp=)

EXCLUDE_alg_test       = $(EXCLUDE_BASE: alg_test.cpp=)
EXCLUDE_cmath_test     = $(EXCLUDE_alg_test: cmath_test.cpp=)
EXCLUDE_deque_test     = $(EXCLUDE_cmath_test: deque_test.cpp=)
EXCLUDE_find_test      = $(EXCLUDE_deque_test: find_test.cpp=)
EXCLUDE_finsert_test   = $(EXCLUDE_find_test: finsert_test.cpp=)
EXCLUDE_floatio_test   = $(EXCLUDE_finsert_test: floatio_test.cpp=)
EXCLUDE_fstream_test   = $(EXCLUDE_floatio_test: fstream_test.cpp=)
EXCLUDE_hash_test      = $(EXCLUDE_fstream_test: hash_test.cpp=)
EXCLUDE_insert_test    = $(EXCLUDE_hash_test: insert_test.cpp=)
EXCLUDE_ioiter_test    = $(EXCLUDE_insert_test: ioiter_test.cpp=)
EXCLUDE_istmit_test    = $(EXCLUDE_ioiter_test: istmit_test.cpp=)
EXCLUDE_locale_test    = $(EXCLUDE_istmit_test: locale_test.cpp=)
EXCLUDE_mvctor_test    = $(EXCLUDE_locale_test: mvctor_test.cpp=)
EXCLUDE_ostmit_test    = $(EXCLUDE_mvctor_test: ostmit_test.cpp=)
EXCLUDE_ptrspec_test   = $(EXCLUDE_ostmit_test: ptrspec_test.cpp=)
EXCLUDE_queue_test     = $(EXCLUDE_ptrspec_test: queue_test.cpp=)
EXCLUDE_resolve_name   = $(EXCLUDE_queue_test: resolve_name.cpp=)
EXCLUDE_rope_test      = $(EXCLUDE_resolve_name: rope_test.cpp=)
EXCLUDE_setdiff_test   = $(EXCLUDE_rope_test: setdiff_test.cpp=)
EXCLUDE_setinter_test  = $(EXCLUDE_setdiff_test: setinter_test.cpp=)
EXCLUDE_setunion_test  = $(EXCLUDE_setinter_test: setunion_test.cpp=)
EXCLUDE_slist_test     = $(EXCLUDE_setunion_test: slist_test.cpp=)
EXCLUDE_sstream_test   = $(EXCLUDE_slist_test: sstream_test.cpp=)
EXCLUDE_stack_test     = $(EXCLUDE_sstream_test: stack_test.cpp=)
EXCLUDE_string_test    = $(EXCLUDE_stack_test: string_test.cpp=)
EXCLUDE_transform_test = $(EXCLUDE_string_test: transform_test.cpp=)
EXCLUDE_unordered_test = $(EXCLUDE_transform_test: unordered_test.cpp=)
EXCLUDE_vector_test    = $(EXCLUDE_unordered_test: vector_test.cpp=)
ALLORIG_FILTERED       = $(EXCLUDE_vector_test)
!endif

!include $(SRCROOT)\Makefiles\borland\top.mak

