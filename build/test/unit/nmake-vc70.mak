# -*- Makefile -*- Time-stamp: <04/03/30 14:53:15 ptr>
# $Id$

COMPILER_NAME=vc70

INCLUDES=$(INCLUDES) /I "$(STLPORT_DIR)/src" /FI "vc_warning_disable.h"

!include nmake-vc-common.mak

