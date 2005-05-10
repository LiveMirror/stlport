# -*- makefile -*- Time-stamp: <05/05/06 17:33:54 ptr>
# $Id$

LDFLAGS += -type generic -w off -nostdlib -msgstyle gcc

STDLIBS = -L"$(MWCW_NOVELL_SDK_BASE)/imports" \
          -L"$(MWCW_NOVELL_R)/Libraries/Runtime/Output/CLib" \
          -L"$(MWCW_NOVELL_SDK_BASE)/../libc/imports" \
          -lclib.imp -lthreads.imp -lmwcrtl.lib -lnlmlib.imp -llibc.imp
