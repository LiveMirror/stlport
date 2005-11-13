# -*- makefile -*- Time-stamp: 
# $Id: rules-a.mak

#!message build\Makefiles\borland\lib\rules-a.mak

# static libraries tags

.AUTODEPEND
#.SILENT

clean-out-a :
		@if exist $(A_NAME_OUT) del $(A_NAME_OUT)

clean-out-a-dbg :
		@if exist $(A_NAME_OUT_DBG) del $(A_NAME_OUT_DBG)

clean-out-a-stldbg :
		@if exist $(A_NAME_OUT_STLDBG) del $(A_NAME_OUT_STLDBG)

allobjs_rel_message:
		@echo $(A_NAME_OUT) (release-static)
	@if not exist $(USE_MAKE)\objs_arr.inc echo Please run 'make -f $(COMPILER_NAME).mak depend'
	@if not exist $(USE_MAKE)\objs_arr.inc dir $(USE_MAKE)\objs_arr.inc > NUL

allobjs_dbg_message:
		@echo $(A_NAME_OUT_DBG) (dbg-static)
	@if not exist $(USE_MAKE)\objs_adr.inc echo Please run 'make -f $(COMPILER_NAME).mak depend'
	@if not exist $(USE_MAKE)\objs_adr.inc dir $(USE_MAKE)\objs_adr.inc > NUL

allobjs_stldbg_message:
		@echo $(A_NAME_OUT_STLDBG) (stldbg-static)
	@if not exist $(USE_MAKE)\objs_add.inc echo Please run 'make -f $(COMPILER_NAME).mak depend'
	@if not exist $(USE_MAKE)\objs_add.inc dir $(USE_MAKE)\objs_add.inc > NUL

release-static: allobjs_rel_message clean-out-a $(A_NAME_OUT)
	@echo.

dbg-static:     allobjs_dbg_message clean-out-a-dbg $(A_NAME_OUT_DBG)
	@echo.

stldbg-static:  allobjs_stldbg_message clean-out-a-stldbg $(A_NAME_OUT_STLDBG)
	@echo.

!ifdef TLIB_A

$(TLIB_A): 
	$(AR) $(OUTPUT_DIR_A)\$(A_NAME) $(AR_EXTR) +$(OUTPUT_DIR_A)\$&.obj

$(A_NAME_OUT) : $(OBJ_A) $(TLIB_A)

!endif

!ifdef TLIB_A_DBG

$(TLIB_A_DBG): 
	$(AR) $(OUTPUT_DIR_A_DBG)\$(A_NAME_DBG) $(AR_EXTR) +$(OUTPUT_DIR_A_DBG)\$&.obj

$(A_NAME_OUT_DBG) : $(OBJ_A_DBG) $(TLIB_A_DBG)

!endif

!ifdef TLIB_A_STLDBG

$(TLIB_A_STLDBG):
	$(AR) $(OUTPUT_DIR_A_STLDBG)\$(A_NAME_STLDBG) $(AR_EXTR) +$(OUTPUT_DIR_A_STLDBG)\$&.obj

$(A_NAME_OUT_STLDBG) : $(OBJ_A_STLDBG) $(TLIB_A_STLDBG)

!endif

.NOSILENT

.precious: allobjs_rel_message
.precious: allobjs_dbg_message
.precious: allobjs_stldbg_message
