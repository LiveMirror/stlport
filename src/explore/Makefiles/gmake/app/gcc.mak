# -*- Makefile -*- Time-stamp: <04/08/23 23:07:09 ptr>
# $Id$

ifeq ($(OSNAME),linux)
START_OBJ := $(shell for o in crt{1,i,begin}.o; do ${CXX} -print-file-name=$$o; done)
LDFLAGS += -nostdlib
END_OBJ := $(shell for o in crt{end,n}.o; do ${CXX} -print-file-name=$$o; done)
ifeq ($(CXX_VERSION_MAJOR),3)
STDLIBS := -lsupc++ -lgcc_s -lpthread -lc -lm
else
# i.e. gcc before 3.x.x: 2.95, etc.
# gcc before 3.x don't had libsupc++.a and libgcc_s.so
# exceptions and operators new are in libgcc.a
STDLIBS := $(shell ${CXX} -print-file-name=libgcc.a) -lpthread -lc -lm
endif
endif
