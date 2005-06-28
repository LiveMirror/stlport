# -*- makefile -*- Time-stamp: 
# $Id: rules-a.mak

#!message build\Makefiles\borland\lib\rules-a.mak

# static libraries tags

.AUTODEPEND

clean-outa :
		@if exist $(A_NAME_OUT) del $(A_NAME_OUT)
		@if exist $(OUTPUT_DIR_A)\stlp500.obj del $(OUTPUT_DIR_A)\stlp500.obj

clean-outa-dbg :
		@if exist $(A_NAME_OUT_DBG) del $(A_NAME_OUT_DBG)
		@if exist $(OUTPUT_DIR_A_DBG)\stlp500.obj del $(OUTPUT_DIR_A_DBG)\stlp500.obj

clean-outa-stldbg :
		@if exist $(A_NAME_OUT_STLDBG) del $(A_NAME_OUT_STLDBG)
		@if exist $(OUTPUT_DIR_A_STLDBG)\stlp500.obj del $(OUTPUT_DIR_A_STLDBG)\stlp500.obj

release-static: clean-outa $(A_NAME_OUT)

dbg-static:     clean-outa-dbg $(A_NAME_OUT_DBG)

stldbg-static:  clean-outa-stldbg $(A_NAME_OUT_STLDBG)

$(A_NAME_OUT) : $(OBJ_A)  
		@echo $(A_NAME_OUT) (release-static)
		$(AR) 0
		@if exist 0.lib del 0.lib
		@cd $(OUTPUT_DIR_A)
		$(AR) $(A_NAME) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_arr.tmp
		@if exist $(SRCROOT_EXT)\$(USE_MAKE)\tlib_arr.tmp echo See $(USE_MAKE)\tlib_arr.tmp for build output.
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A)\*.tds del $(OUTPUT_DIR_A)\*.tds

$(A_NAME_OUT_DBG) : $(OBJ_A_DBG) 
		@echo $(A_NAME_OUT_DBG) (dbg-static)
		$(AR) 0
		@if exist 0.lib del 0.lib
		@cd $(OUTPUT_DIR_A_DBG)
		$(AR) $(A_NAME_DBG) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_adr.tmp
		@if exist $(SRCROOT_EXT)\$(USE_MAKE)\tlib_adr.tmp echo See $(USE_MAKE)\tlib_adr.tmp for build output.
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A_DBG)\*.tds del $(OUTPUT_DIR_A_DBG)\*.tds

$(A_NAME_OUT_STLDBG) : $(OBJ_A_STLDBG) 
		@echo $(A_NAME_OUT_STLDBG) (stldbg-static)
		$(AR) 0
		@if exist 0.lib del 0.lib
		@cd $(OUTPUT_DIR_A_STLDBG)
		$(AR) $(A_NAME_STLDBG) $(AR_EXTR) +-$(ALLOBJS_A) > $(SRCROOT_EXT)\$(USE_MAKE)\tlib_add.tmp
		@if exist $(SRCROOT_EXT)\$(USE_MAKE)\tlib_add.tmp echo See $(USE_MAKE)\tlib_add.tmp for build output.
		@cd $(SRCROOT_EXT)
		@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del $(OUTPUT_DIR_A_STLDBG)\*.tds

