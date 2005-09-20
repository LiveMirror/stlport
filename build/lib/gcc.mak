# -*- Makefile -*- Time-stamp: <03/10/12 20:35:49 ptr>
# $Id$

SRCROOT := ..
COMPILER_NAME := gcc

STLPORT_INCLUDE_DIR = ../../stlport
include Makefile.inc
include ${SRCROOT}/Makefiles/top.mak


INCLUDES += -I$(STLPORT_INCLUDE_DIR)

ifeq ($(OSNAME),linux)
DEFS += -D_STLP_REAL_LOCALE_IMPLEMENTED -D_GNU_SOURCE

# gcc 2.95 don't have cxa-at-exit feature; without it we can't clear locale
# support safely
ifneq ($(CXX_VERSION_MAJOR),2)
DEFS += -D_STLP_LEAKS_PEDANTIC
endif
endif

# options for build with boost support
ifdef STLP_BUILD_BOOST_PATH
INCLUDES += -I$(STLP_BUILD_BOOST_PATH)
endif

