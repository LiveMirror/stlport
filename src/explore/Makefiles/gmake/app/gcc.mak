# -*- Makefile -*- Time-stamp: <04/07/30 08:22:41 ptr>
# $Id$

ifeq ($(OSNAME),linux)
START_OBJ := $(shell for o in crt{1,i,begin}.o; do ${CXX} -print-file-name=$$o; done)
LDFLAGS += -nostdlib
END_OBJ := $(shell for o in crt{end,n}.o; do ${CXX} -print-file-name=$$o; done)
STDLIBS := -lsupc++ -lgcc_s -lpthread -lc -lm
endif
