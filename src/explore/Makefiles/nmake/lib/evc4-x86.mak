# -*- makefile -*- Time-stamp: <04/03/31 08:10:47 ptr>
# $Id$

LDFLAGS_COMMON = commctrl.lib coredll.lib corelibc.lib ccrtrtti.lib /nologo /base:"0x00100000" /stack:0x10000,0x1000 /incremental:yes /nodefaultlib:"LIBC.lib" /subsystem:WINDOWSCE
LDFLAGS_COMMON = $(LDFLAGS_COMMON) $(CEx86Corelibc) /nodefaultlib:"OLDNAMES.lib" /MACHINE:IX86

!include evc-common.mak
