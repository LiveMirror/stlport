# -*- Makefile -*- Time-stamp: 
# $Id: bc55.mak

#!message build\test\eh\bc55.mak

.AUTODEPEND

COMPILER_NAME = bc55

!ifndef BC5ROOT
BC5ROOT   = $(MAKEDIR)\..
!endif

STLPORT_DIR   = ..\..\..
SRCROOT       = $(STLPORT_DIR)\build
SRCDIR        = $(STLPORT_DIR)\test\eh

ALL_TAGS      = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static

!include Makefile.inc

LIB_VERSION   = stlp$(LIBMAJOR)$(LIBMINOR)

INCLUDES      = $(SRCDIR)

DEFS          = 

!include $(SRCROOT)\Makefiles\borland\top.mak
