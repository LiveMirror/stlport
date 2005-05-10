# -*- Makefile -*- Time-stamp: <05/03/10 17:51:53 ptr>
# $Id$

SRCROOT := ../..
COMPILER_NAME := mwccnlm

ALL_TAGS := release-shared dbg-shared stldbg-shared
STLPORT_DIR := ../../..
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak

INCLUDES += -I${STLPORT_INCLUDE_DIR}
DEFS += -D_STLP_NO_CUSTOM_IO -D_STLP_LEAKS_PEDANTIC

dbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED
stldbg-shared:	DEFS += -D_STLP_DEBUG_UNINITIALIZED

ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I${STLP_BUILD_BOOST_PATH}
endif

ifndef TARGET_OS
release-shared:	LDSEARCH = -L+${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR} -Wl,-R${STLPORT_LIB_DIR}
else
release-shared:	LDSEARCH = -Le:/STLport/netware-lib
dbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR}
stldbg-shared:	LDSEARCH = -L${STLPORT_LIB_DIR}
endif


LIB_VERSION = ${LIBMAJOR}${LIBMINOR}
release-shared : LDLIBS = e:/STLport/netware-lib/stlport_r${LIB_VERSION}_static.lib
dbg-shared     : LDLIBS = -lstlport_d${LIB_VERSION}
stldbg-shared  : LDLIBS = -lstlport_stld${LIB_VERSION}

LDFLAGS += -commandfile novelltest.def
