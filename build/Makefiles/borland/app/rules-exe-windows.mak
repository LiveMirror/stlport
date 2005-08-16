# -*- makefile -*- Time-stamp: 
# $Id: rules-exe-windows.mak

#!message build\Makefiles\borland\app\rules-exe-windows.mak

.AUTODEPEND
#.SILENT

clean-prg :
		@if exist $(PRG) del $(PRG)

clean-prg-dbg :
		@if exist $(PRG_DBG) del $(PRG_DBG)

clean-prg-stldbg :
		@if exist $(PRG_STLDBG) del $(PRG_STLDBG)

clean-prg-a :
		@if exist $(PRG_A) del $(PRG_A)

clean-prg-a-dbg :
		@if exist $(PRG_A_DBG) del $(PRG_A_DBG)

clean-prg-a-stldbg :
		@if exist $(PRG_A_STLDBG) del $(PRG_A_STLDBG)

release-shared : clean-prg $(PRG) 

dbg-shared     : clean-prg-dbg $(PRG_DBG)

stldbg-shared  : clean-prg-stldbg $(PRG_STLDBG)

release-static : clean-prg-a $(PRG_A) 

dbg-static     : clean-prg-a-dbg $(PRG_A_DBG)

stldbg-static  : clean-prg-a-stldbg $(PRG_A_STLDBG)


$(PRG) : $(OBJ)
		@echo $(PRG) (release-shared)
		@if not exist $(USE_MAKE)\objs_srr.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_REL) $(STARTUPCON) @.\$(USE_MAKE)\objs_srr.inc,$(PRG),,$(LDLIBS),$(DEF_FILE),$(RES)
		@echo.

$(PRG_DBG) : $(OBJ_DBG)
		@echo $(PRG_DBG) (dbg-shared)
		@if not exist $(USE_MAKE)\objs_sdr.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_DBG) $(STARTUPCON) @.\$(USE_MAKE)\objs_sdr.inc,$(PRG_DBG),,$(LDLIBS),$(DEF_FILE_DBG),$(RES_DBG)
		@echo.

$(PRG_STLDBG) : $(OBJ_STLDBG) 
		@echo $(PRG_STLDBG) (stldbg-shared)
		@if not exist $(USE_MAKE)\objs_sdd.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_STLDBG) $(STARTUPCON) @.\$(USE_MAKE)\objs_sdd.inc,$(PRG_STLDBG),,$(LDLIBS),$(DEF_FILE_STLDBG),$(RES_STLDBG)
		@echo.

$(PRG_A) : $(OBJ_A)
		@echo $(PRG_A) (release-static)
		@if not exist $(USE_MAKE)\objs_arr.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_STATIC) $(STARTUPCON) @.\$(USE_MAKE)\objs_arr.inc,.\$(PRG_A),,$(LDLIBS_STATIC),$(DEF_FILE_A),$(RES)
		@echo.

$(PRG_A_DBG) : $(OBJ_A_DBG)
		@echo $(PRG_A_DBG) (dbg-static)
		@if not exist $(USE_MAKE)\objs_adr.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_STATIC_DBG) $(STARTUPCON) @.\$(USE_MAKE)\objs_adr.inc,.\$(PRG_A_DBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_DBG),$(RES_DBG)
		@echo.

$(PRG_A_STLDBG) : $(OBJ_A_STLDBG)
		@echo $(PRG_A_STLDBG) (stldbg-static)
		@if not exist $(USE_MAKE)\objs_add.inc echo Please run 'make -f [makefile] depend'
		$(LINK_cpp_STATIC_STLDBG) $(STARTUPCON) @.\$(USE_MAKE)\objs_add.inc,.\$(PRG_A_STLDBG),,$(LDLIBS_STATIC),$(DEF_FILE_A_STLDBG),$(RES_STLDBG)
		@echo.

.NOSILENT
