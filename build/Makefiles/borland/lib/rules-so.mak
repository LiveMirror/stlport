# -*- makefile -*- Time-stamp: 
# $Id: rules-so.mak

#!message build\Makefiles\borland\lib\rules-so.mak

.AUTODEPEND

# Shared libraries tags

clean-out :
		@if exist $(SO_NAME_OUT) del $(SO_NAME_OUT)
		@if exist $(LIB_NAME_OUT) del $(LIB_NAME_OUT)

clean-out-dbg :
		@if exist $(SO_NAME_OUT_DBG) del $(SO_NAME_OUT_DBG)
		@if exist $(LIB_NAME_OUT_DBG) del $(LIB_NAME_OUT_DBG)

clean-out-stldbg :
		@if exist $(SO_NAME_OUT_STLDBG) del $(SO_NAME_OUT_STLDBG)
		@if exist $(LIB_NAME_OUT_STLDBG) del $(LIB_NAME_OUT_STLDBG)

release-shared: clean-out $(SO_NAME_OUT)

dbg-shared:     clean-out-dbg $(SO_NAME_OUT_DBG)

stldbg-shared:  clean-out-stldbg $(SO_NAME_OUT_STLDBG)

$(SO_NAME_OUT): $(OBJ)
		@echo $(SO_NAME_OUT) (release-shared)
		@if not exist $(USE_MAKE)\objs_srr.inc echo Please run 'make -f [makefile] depend'
		@if exist $(USE_MAKE)\objs_srr.inc $(LINK_cpp_REL) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_srr.inc,$(SO_NAME_OUT),,$(LDLIBS),$(DEF_FILE),$(RES)
		@if exist $(OUTPUT_DIR)\*.tds del $(OUTPUT_DIR)\*.tds

$(SO_NAME_OUT_DBG): $(OBJ_DBG)
		@echo $(SO_NAME_OUT_DBG) (dbg-shared)
		@if not exist $(USE_MAKE)\objs_sdr.inc echo Please run 'make -f [makefile] depend'
		@if exist $(USE_MAKE)\objs_sdr.inc $(LINK_cpp_DBG) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdr.inc,$(SO_NAME_OUT_DBG),,$(LDLIBS),$(DEF_FILE_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_DBG)\*.tds del $(OUTPUT_DIR_DBG)\*.tds

$(SO_NAME_OUT_STLDBG): $(OBJ_STLDBG) 
		@echo $(SO_NAME_OUT_STLDBG) (stldbg-shared)
		@if not exist $(USE_MAKE)\objs_sdd.inc echo Please run 'make -f [makefile] depend'
		@if exist $(USE_MAKE)\objs_sdd.inc $(LINK_cpp_STLDBG) $(STARTUPDLL) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdd.inc,$(SO_NAME_OUT_STLDBG),,$(LDLIBS),$(DEF_FILE_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_STLDBG)\*.tds del $(OUTPUT_DIR_STLDBG)\*.tds

