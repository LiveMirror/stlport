# -*- makefile -*- Time-stamp: <04/08/23 23:07:35 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

OPT += -fPIC

ifeq ($(OSNAME),linux)
_USE_NOSTDLIB := 1
endif

ifeq ($(OSNAME),sunos)
#_USE_NOSTDLIB := 1
endif

ifdef _USE_NOSTDLIB
NOSTDLIB :=

ifeq ($(CXX_VERSION_MAJOR),3)

# gcc before 3.3 (i.e. 3.0.x, 3.1.x, 3.2.x) has buggy libsupc++, so we should link with libstdc++ to avoid one

ifneq ($(CXX_VERSION_MINOR),0)
ifneq ($(CXX_VERSION_MINOR),1)
ifneq ($(CXX_VERSION_MINOR),2)
ifeq ($(OSNAME),linux)
START_OBJ := $(shell for o in crt{i,beginS}.o; do ${CXX} -print-file-name=$$o; done)
#START_A_OBJ := $(shell for o in crt{i,beginT}.o; do ${CXX} -print-file-name=$$o; done)
END_OBJ := $(shell for o in crt{endS,n}.o; do ${CXX} -print-file-name=$$o; done)
endif
ifeq ($(OSNAME),sunos)
#START_OBJ := $(shell for o in crti.o crtbegin.o; do ${CXX} -print-file-name=$$o; done)
#END_OBJ := $(shell for o in crtend.o crtn.o; do ${CXX} -print-file-name=$$o; done)
endif
#END_A_OBJ := $(shell for o in crtn.o; do ${CXX} -print-file-name=$$o; done)
STDLIBS := -Wl,--whole-archive -lsupc++ -Wl,--no-whole-archive -lgcc_s -lpthread -lc -lm
NOSTDLIB := -nostdlib
endif
endif
endif

else
# i.e. gcc before 3.x.x: 2.95, etc.
# gcc before 3.x don't had libsupc++.a and libgcc_s.so
# exceptions and operators new are in libgcc.a
#  Unfortunatly gcc before 3.x has a buggy C++ language support outside stdc++, so line below is commented
#STDLIBS := $(shell ${CXX} -print-file-name=libgcc.a) -lpthread -lc -lm
endif
endif

ifeq ($(OSNAME),hp-ux)
dbg-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic  -Wl,+h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic  -Wl,+h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic -Wl,+h$(SO_NAMExx) ${LDSEARCH}
endif

ifeq ($(OSNAME),sunos)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH} ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH} ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH} ${NOSTDLIB}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

ifeq ($(OSNAME),linux)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH} ${NOSTDLIB}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH} ${NOSTDLIB}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH} ${NOSTDLIB}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

ifeq ($(OSNAME),cygming)
OPT := 
dbg-shared:	LDFLAGS += -shared -Wl,--out-implib=${LIB_NAME_OUT_DBG},--export-all-symbols,--disable-auto-import
stldbg-shared:	LDFLAGS += -shared -Wl,--out-implib=${LIB_NAME_OUT_STLDBG},--export-all-symbols
release-shared:	LDFLAGS += -shared -Wl,--out-implib=${LIB_NAME_OUT},--export-all-symbols
dbg-static:	LDFLAGS += -static ${LDSEARCH}
stldbg-static:	LDFLAGS += -static ${LDSEARCH}
release-static:	LDFLAGS += -static ${LDSEARCH}
endif

ifeq ($(OSNAME),freebsd)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

ifeq ($(OSNAME),darwin)
CURRENT_VERSION := ${MAJOR}.${MINOR}.${PATCH}
COMPATIBILITY_VERSION := $(CURRENT_VERSION)

dbg-shared:	LDFLAGS += -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAME_DBGxx) -Wl ${LDSEARCH}
stldbg-shared:	LDFLAGS += -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAME_STLDBGxx) -Wl ${LDSEARCH}
release-shared:	LDFLAGS += -dynamiclib -compatibility_version $(COMPATIBILITY_VERSION) -current_version $(CURRENT_VERSION) -install_name $(SO_NAMExx) -Wl ${LDSEARCH}
dbg-static:	LDFLAGS += -staticlib ${LDSEARCH}
stldbg-static:	LDFLAGS += -staticlib ${LDSEARCH}
release-static:	LDFLAGS += -staticlib ${LDSEARCH}
endif

ifeq ($(OSNAME),openbsd)
dbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif
