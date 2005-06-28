# -*- makefile -*- Time-stamp: 
# $Id: rules-exe-windows.mak

#!message build\Makefiles\borland\app\rules-exe-windows.mak

.AUTODEPEND

clean-prg :
		@if exist $(PRG) del $(PRG)

clean-prg-dbg :
		@if exist $(PRG_DBG) del $(PRG_DBG)

clean-prg-stldbg :
		@if exist $(PRG_STLDBG) del $(PRG_STLDBG)

clean-prga :
		@if exist $(PRG_A) del $(PRG_A)

clean-prga-dbg :
		@if exist $(PRG_A_DBG) del $(PRG_A_DBG)

clean-prga-stldbg :
		@if exist $(PRG_A_STLDBG) del $(PRG_A_STLDBG)

release-shared : clean-prg $(PRG) 

dbg-shared     : clean-prg-dbg $(PRG_DBG)

stldbg-shared  : clean-prg-stldbg $(PRG_STLDBG)

release-static : clean-prga $(PRG_A) 

dbg-static     : clean-prga-dbg $(PRG_A_DBG)

stldbg-static  : clean-prga-stldbg $(PRG_A_STLDBG)


$(PRG) : $(OBJ)
		@echo $(PRG) (release-shared)
		@if not exist $(USE_MAKE)\objs_srr.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME) not found.
!endif
        @if exist $(USE_MAKE)\objs_srr.inc $(LINK_cpp_REL) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_srr.inc,$(PRG),,$(LDLIBS),$(DEF_FILE),$(RES)
		@if exist $(OUTPUT_DIR)\*.tds del $(OUTPUT_DIR)\*.tds

$(PRG_DBG) : $(OBJ_DBG)
		@echo $(PRG_DBG) (dbg-shared)
		@if not exist $(USE_MAKE)\objs_sdr.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME_DBG) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME_DBG) not found.
!endif
        @if exist $(USE_MAKE)\objs_sdr.inc $(LINK_cpp_DBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdr.inc,$(PRG_DBG),,$(LDLIBS),$(DEF_FILE_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_DBG)\*.tds del $(OUTPUT_DIR_DBG)\*.tds

$(PRG_STLDBG) : $(OBJ_STLDBG) 
		@echo $(PRG_STLDBG) (stldbg-shared)
		@if not exist $(USE_MAKE)\objs_sdd.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME_STLDBG) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(LIB_NAME_STLDBG) not found.
!endif
        @if exist $(USE_MAKE)\objs_sdd.inc $(LINK_cpp_STLDBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_sdd.inc,$(PRG_STLDBG),,$(LDLIBS),$(DEF_FILE_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_STLDBG)\*.tds del $(OUTPUT_DIR_STLDBG)\*.tds

$(PRG_A) : $(OBJ_A)
		@echo $(PRG_A) (release-static)
		@if not exist $(USE_MAKE)\objs_arr.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME) not found.
!endif
        @if exist $(USE_MAKE)\objs_arr.inc $(LINK_cpp_STATIC) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_arr.inc,$(SRCROOT_EXT)\$(PRG_A),,$(LDLIBS_STATIC),$(DEF_FILE_A),$(RES)
		@if exist $(OUTPUT_DIR_A)\*.tds del $(OUTPUT_DIR_A)\*.tds

$(PRG_A_DBG) : $(OBJ_A_DBG)
		@echo $(PRG_A_DBG) (dbg-static)
		@if not exist $(USE_MAKE)\objs_adr.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME_DBG) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME_DBG) not found.
!endif
        @if exist $(USE_MAKE)\objs_adr.inc $(LINK_cpp_STATIC_DBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_adr.inc,$(SRCROOT_EXT)\$(PRG_A_DBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_DBG),$(RES_DBG)
		@if exist $(OUTPUT_DIR_A_DBG)\*.tds del $(OUTPUT_DIR_A_DBG)\*.tds

$(PRG_A_STLDBG) : $(OBJ_A_STLDBG)
		@echo $(PRG_A_STLDBG) (stldbg-static)
		@if not exist $(USE_MAKE)\objs_add.inc echo Please run 'make -f [makefile] depend'
!ifdef LIB_VERSION
		@if not exist $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME_STLDBG) echo WARNING: $(BC5ROOT_LIB_DIR)\$(LIB_VERSION)$(A_NAME_STLDBG) not found.
!endif
        @if exist $(USE_MAKE)\objs_add.inc $(LINK_cpp_STATIC_STLDBG) $(STARTUPCON) @$(SRCROOT_EXT)\$(USE_MAKE)\objs_add.inc,$(SRCROOT_EXT)\$(PRG_A_STLDBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_STLDBG),$(RES_STLDBG)
		@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del $(OUTPUT_DIR_A_STLDBG)\*.tds

