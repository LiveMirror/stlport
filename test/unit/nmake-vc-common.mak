# -*- Makefile -*- Time-stamp: <04/03/30 14:53:15 ptr>
# $Id$

SRCROOT=../../src/explore
STLPORT_DIR=../..

!include Makefile.inc

INCLUDES=$(INCLUDES) /I "$(STLPORT_INCLUDE_DIR)" /I "$(STLPORT_DIR)/src" /FI "vc_warning_disable.h"

!ifdef STLP_BUILD_BOOST_PATH
INCLUDES=$(INCLUDES) /I "$(STLP_BUILD_BOOST_PATH)"
!endif

DEFS = /D_STLP_NO_CUSTOM_IO /D_STLP_DONT_FORCE_MSVC_LIB_NAME /DCPPUNIT_MINI=1

LDSEARCH=$(LDSEARCH) /LIBPATH:$(STLPORT_LIB_DIR)

LDLIBS_REL=stlport_$(COMPILER_NAME).lib
LDLIBS_DBG=stlport_$(COMPILER_NAME)_debug.lib
LDLIBS_STLDBG=stlport_$(COMPILER_NAME)_stldebug.lib

LDLIBS_A_REL=stlport_$(COMPILER_NAME)_static.lib
LDLIBS_A_DBG=stlport_$(COMPILER_NAME)_debug_static.lib
LDLIBS_A_STLDBG=stlport_$(COMPILER_NAME)_stldebug_static.lib

!include $(SRCROOT)/Makefiles/nmake/top.mak
