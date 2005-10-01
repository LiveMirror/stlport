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
# EXCLUDE_TESTS          = 1

!ifdef EXCLUDE_TESTS
ALLORIG                = $(SRC_CPP) $(SRC_CC) $(SRC_C)
EXCLUDE_BASE           = $(ALLORIG:../../../test/unit/=)

# Edit this section to temporarily exclude specific unit tests. 
# Each line excludes one source file. 
# All source files are listed in makefile.inc
# EXCLUDE_[excluded]   = $(EXCLUDE_[previous]: [excluded].cpp=)

EXCLUDE_type_traits_test = $(EXCLUDE_BASE: type_traits_test.cpp=)
ALLORIG_FILTERED         = $(EXCLUDE_type_traits_test)
!endif

!include $(SRCROOT)\Makefiles\borland\top.mak

