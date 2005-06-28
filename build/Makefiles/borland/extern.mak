# Time-stamp: 
# $Id: extern.mak

#!message build\Makefiles\borland\extern.mak

.AUTODEPEND

!ifndef BC5ROOT
BC5ROOT = $(MAKEDIR)\..
!endif

!ifndef BC5ROOT_LIB_DIR
BC5ROOT_LIB_DIR = $(BC5ROOT)\lib
!endif

!ifndef BC5ROOT_INCLUDE_DIR
BC5ROOT_INCLUDE_DIR = $(BC5ROOT)\include
!endif

!ifndef STLPORT_DIR
STLPORT_DIR = $(BC5ROOT)\STLport-500
!endif

# This file reflect versions of third-party libraries that
# used in projects

# STLport library
!ifndef STLPORT_LIB_DIR
STLPORT_LIB_DIR = $(STLPORT_DIR)\lib
!endif

!ifndef STLPORT_INCLUDE_DIR
STLPORT_INCLUDE_DIR = $(STLPORT_DIR)\stlport
!endif

!ifndef STLPORT_VER
STLPORT_VER = 5.0.0
!endif

