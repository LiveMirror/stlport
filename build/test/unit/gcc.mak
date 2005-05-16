# -*- Makefile -*- Time-stamp: <05/05/14 14:04:12 ptr>
# $Id$

SRCROOT := ../..
COMPILER_NAME := gcc

ALL_TAGS := release-shared stldbg-shared
STLPORT_DIR := ../../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I${STLPORT_INCLUDE_DIR}
DEFS += -D_STLP_NO_CUSTOM_IO -D_STLP_LEAKS_PEDANTIC

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED 

ifeq ($(OSNAME), cygming)
release-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
dbg-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
stldbg-shared:	DEFS += -D_STLP_USE_DYNAMIC_LIB
endif

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

release-shared:	LDSEARCH = -L${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR}

ifndef TARGET_OS
ifneq ($(OSNAME), cygming)
release-shared:	LDSEARCH += -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH += -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH += -Wl,-R${STLPORT_LIB_DIR}
endif
endif

ifeq ($(OSNAME),cygming)
LIB_VERSION = ${LIBMAJOR}${LIBMINOR}
release-shared : LDLIBS = -lstlport_r${LIB_VERSION}
dbg-shared     : LDLIBS = -lstlport_d${LIB_VERSION}
stldbg-shared  : LDLIBS = -lstlport_stld${LIB_VERSION}
else
release-shared : LDLIBS = -lstlport
dbg-shared     : LDLIBS = -lstlportg
stldbg-shared  : LDLIBS = -lstlportstlg
endif

ifeq ($(OSNAME),sunos)
release-shared : LDLIBS = -lstlport -lrt
stldbg-shared  : LDLIBS = -lstlportstlg -lrt
dbg-shared     : LDLIBS = -lstlportg -lrt
endif

