# -*- Makefile -*- Time-stamp: 
# $Id: bc56.mak

#!message build\lib\bc56.mak

.AUTODEPEND

COMPILER_NAME = bc56

!ifndef BC5ROOT
BC5ROOT   = $(MAKEDIR)\..
!endif

STLPORT_DIR   = ..\..
SRCROOT       = $(STLPORT_DIR)\build
SRCDIR        = $(STLPORT_DIR)\src

ALL_TAGS     = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static

NOINIT_A      = 1

!include .\Makefile.inc

LIBNAME       = stlp$(MAJOR)$(MINOR)

INCLUDES      = 

DEFS          = __BUILDING_STLPORT=1;__BUILDING_STLPORT_LIBS

!include $(SRCROOT)\Makefiles\borland\top.mak
