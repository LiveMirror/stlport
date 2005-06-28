# -*- Makefile -*- Time-stamp: 
# $Id: bc56.mak

#!message build\lib\bc56.mak

.AUTODEPEND

COMPILER_NAME = bc56

!ifndef BC5ROOT
! ifdef MAKEDIR
BC5ROOT   = $(MAKEDIR)\..
! else
BC5ROOT   = \CBuilderX
! endif
!endif

STLPORT_DIR   = $(BC5ROOT)\STLport-500-BC5-edited
SRCROOT       = $(STLPORT_DIR)\build
SRCROOT_EXT   = $(SRCROOT)\lib
SRCDIR        = $(STLPORT_DIR)\src

ALL_TAGS     = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static

#NOINIT_SO    = 1
NOINIT_A      = 1

!include .\Makefile.inc

LIBNAME       = stlp$(MAJOR)$(MINOR)

INCLUDES      = 

DEFS          = -D__BUILDING_STLPORT=1;__BUILDING_STLPORT_LIBS

!include $(SRCROOT)\Makefiles\borland\top.mak
