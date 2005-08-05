# -*- Makefile -*- Time-stamp: 
# $Id: bc55.mak

#!message build\test\eh\bc55.mak

.AUTODEPEND

COMPILER_NAME = bc55

!ifndef BC5ROOT
! ifdef MAKEDIR
BC5ROOT   = $(MAKEDIR)\..
! else
BC5ROOT   = \BCC55
! endif
!endif

STLPORT_DIR   = $(BC5ROOT)\STLport-500-BC5-P1-edited
SRCROOT       = $(STLPORT_DIR)\build
SRCROOT_EXT   = $(SRCROOT)\test\eh
SRCDIR        = $(STLPORT_DIR)\test\eh

ALL_TAGS      = release-shared dbg-shared stldbg-shared release-static dbg-static stldbg-static

!include Makefile.inc

LIB_VERSION   = stlp$(LIBMAJOR)$(LIBMINOR)

INCLUDES      = -I$(SRCDIR);

DEFS          = 

#NOINIT_A = 1

!include $(SRCROOT)\Makefiles\borland\top.mak
