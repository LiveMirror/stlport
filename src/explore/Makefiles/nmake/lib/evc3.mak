# -*- makefile -*- Time-stamp: <04/05/01 00:34:42 ptr>
# $Id$

LDFLAGS_COMMON = commctrl.lib coredll.lib corelibc.lib /nologo /base:"0x00100000" /stack:0x10000,0x1000 /incremental:yes /nodefaultlib:"LIBC.lib" /subsystem:WINDOWSCE /align:"4096"
!if "$(TARGET_PROC)" == "arm"
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /MACHINE:ARM
!else
LDFLAGS_COMMON = $(LDFLAGS_COMMON) $(CEx86Corelibc) /nodefaultlib:"OLDNAMES.lib" /MACHINE:X86
!endif

!include evc-common.mak
