# -*- makefile -*- Time-stamp: <03/11/30 11:41:22 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

OPT += -fPIC

ifeq ($(OSNAME),hp-ux)
dbg-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic  -Wl,+h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic  -Wl,+h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-C20 -Wl,-dynamic -Wl,+h$(SO_NAMExx) ${LDSEARCH}
endif

ifeq ($(OSNAME),sunos)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

ifeq ($(OSNAME),linux)
dbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-h$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif

ifeq ($(OSNAME),cygwin)
OPT := 
dbg-shared:	LDFLAGS += -shared -Wl,--out-implib=${LIB_NAME_OUT_DBG},--export-all-symbols --disable-auto-import
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

ifeq ($(OSNAME),openbsd)
dbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_DBGxx) ${LDSEARCH}
stldbg-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAME_STLDBGxx) ${LDSEARCH}
release-shared:	LDFLAGS += -shared -Wl,-soname -Wl,$(SO_NAMExx) ${LDSEARCH}
dbg-static:	LDFLAGS += ${LDSEARCH}
stldbg-static:	LDFLAGS += ${LDSEARCH}
release-static:	LDFLAGS += ${LDSEARCH}
endif
