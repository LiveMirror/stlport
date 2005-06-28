# Time-stamp:
# $Id: sysid.mak

#!message build\Makefiles\borland\sysid.mak

OSNAME = windows
M_ARCH = i386
P_ARCH = i386

!ifndef OSREL
OSREL = $(OSNAME)
!endif

!ifndef OS
OS =
!endif

!ifndef TARGET_OS
! ifdef PROCESSOR_ARCHITECTURE
TARGET_OS = $(PROCESSOR_ARCHITECTURE)
! else
TARGET_OS = x86
! endif
!endif

!ifdef USERNAME
USER = $(USERNAME)
!else
USER = 
!endif

!ifndef BUILD_DATE
BUILD_DATE =
!endif

BUILD_SYSTEM = $(OSREL) $(M_ARCH) $(USER)

bld_sys_msg:
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)

info: 
	@echo BUILD_DATE = $(BUILD_DATE)
	@echo M_ARCH = $(M_ARCH)
	@echo OSREL = $(OSREL)
	@echo USER = $(USER)
	@echo BUILD_SYSTEM = $(BUILD_SYSTEM)
	@echo WINSYSDIR = $(WINSYSDIR)
	@echo BC5ROOT = $(BC5ROOT)
	@echo STLPORT_DIR = $(STLPORT_DIR)
