# -*- makefile -*- Time-stamp: <04/03/31 08:08:12 ptr>
# $Id$

LDFLAGS_COMMON = commctrl.lib coredll.lib $(CEx86Corelibc) corelibc.lib ccrtrtti.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:yes /nodefaultlib:"OLDNAMES.lib" /nodefaultlib:"libc.lib" /subsystem:WINDOWSCE
LDFLAGS_COMMON = $(LDFLAGS_COMMON) /align:"4096" /MACHINE:ARM

!include evc-common.mak
