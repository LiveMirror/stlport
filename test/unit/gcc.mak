# -*- Makefile -*- Time-stamp: <04/03/14 23:50:57 ptr>
# $Id$

SRCROOT := ../../src/explore
COMPILER_NAME := gcc

ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I${STLPORT_INCLUDE_DIR}
DEFS += -D_STLP_NO_CUSTOM_IO -DCPPUNIT_MINI=1

ifeq ($(OSNAME), cygwin)
release-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
dbg-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
stldbg-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
endif

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

release-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}

ifeq ($(OSNAME),cygwin)
release-shared : LDLIBS = -lstlport_gcc_r50
dbg-shared     : LDLIBS = -lstlport_gcc_d50
stldbg-shared  : LDLIBS = -lstlport_gcc_stld50
else
release-shared : LDLIBS = -lstlport_gcc
dbg-shared     : LDLIBS = -lstlport_gcc_debug
stldbg-shared  : LDLIBS = -lstlport_gcc_stldebug
endif

ifeq ($(OSNAME),sunos)
release-shared : LDLIBS += -lrt
stldbg-shared  : LDLIBS += -lrt
dbg-shared     : LDLIBS += -lrt
endif

