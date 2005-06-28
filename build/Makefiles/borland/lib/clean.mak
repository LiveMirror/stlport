# -*- makefile -*- Time-stamp: 
# $Id: clean.mak

#!message build\Makefiles\borland\lib\clean.mak

clobber:        clean

	@cd $(SRCROOT_EXT)
	@if exist $(SO_NAME_OUT)          del $(SO_NAME_OUT)
	@if exist $(SO_NAME_OUT_DBG)      del $(SO_NAME_OUT_DBG)
	@if exist $(SO_NAME_OUT_STLDBG)   del $(SO_NAME_OUT_STLDBG)
	@if exist $(LIB_NAME_OUT)         del $(LIB_NAME_OUT)
	@if exist $(LIB_NAME_OUT_DBG)     del $(LIB_NAME_OUT_DBG)
	@if exist $(LIB_NAME_OUT_STLDBG)  del $(LIB_NAME_OUT_STLDBG)
	@if exist $(A_NAME_OUT)           del $(A_NAME_OUT)
	@if exist $(A_NAME_OUT_DBG)       del $(A_NAME_OUT_DBG)
	@if exist $(A_NAME_OUT_STLDBG)    del $(A_NAME_OUT_STLDBG)

	@if exist $(OUTPUT_DIR)          rd /S /Q $(OUTPUT_DIR)
	@if exist $(OUTPUT_DIR_DBG)      rd /S /Q $(OUTPUT_DIR_DBG)
	@if exist $(OUTPUT_DIR_STLDBG)   rd /S /Q $(OUTPUT_DIR_STLDBG)
	@if exist $(OUTPUT_DIR_A)        rd /S /Q $(OUTPUT_DIR_A)
	@if exist $(OUTPUT_DIR_A_DBG)    rd /S /Q $(OUTPUT_DIR_A_DBG)
	@if exist $(OUTPUT_DIR_A_STLDBG) rd /S /Q $(OUTPUT_DIR_A_STLDBG)

	@if exist obj\$(TARGET_NAME)$(COMPILER_NAME) rd /S /Q obj\$(TARGET_NAME)$(COMPILER_NAME)
	@if exist obj rd /S /Q obj

	@echo clobber done.

distclean:      clobber

	@if exist $(INSTALL_DLL_DIR)\$(SO_NAME)        del $(INSTALL_DLL_DIR)\$(SO_NAME)
	@if exist $(INSTALL_DLL_DIR)\$(SO_NAME_DBG)    del $(INSTALL_DLL_DIR)\$(SO_NAME_DBG)
	@if exist $(INSTALL_DLL_DIR)\$(SO_NAME_STLDBG) del $(INSTALL_DLL_DIR)\$(SO_NAME_STLDBG)

	@if exist $(INSTALL_LIB_DIR)\$(LIB_NAME)        del $(INSTALL_LIB_DIR)\$(LIB_NAME)
	@if exist $(INSTALL_LIB_DIR)\$(LIB_NAME_DBG)    del $(INSTALL_LIB_DIR)\$(LIB_NAME_DBG)
	@if exist $(INSTALL_LIB_DIR)\$(LIB_NAME_STLDBG) del $(INSTALL_LIB_DIR)\$(LIB_NAME_STLDBG)

	@if exist $(INSTALL_LIB_DIR)\$(A_NAME)        del $(INSTALL_LIB_DIR)\$(A_NAME)
	@if exist $(INSTALL_LIB_DIR)\$(A_NAME_DBG)    del $(INSTALL_LIB_DIR)\$(A_NAME_DBG)
	@if exist $(INSTALL_LIB_DIR)\$(A_NAME_STLDBG) del $(INSTALL_LIB_DIR)\$(A_NAME_STLDBG)
	
	@if exist $(USE_MAKE)\depends.inc              del $(USE_MAKE)\depends.inc
	@if exist ..\test\unit\$(USE_MAKE)\depends.inc del ..\test\unit\$(USE_MAKE)\depends.inc
	@if exist ..\test\eh\$(USE_MAKE)\depends.inc   del ..\test\eh\$(USE_MAKE)\depends.inc
	
	@if exist $(USE_MAKE)              rd /S /Q $(USE_MAKE)
	@if exist ..\test\unit\$(USE_MAKE) rd /S /Q ..\test\unit\$(USE_MAKE)
	@if exist ..\test\eh\$(USE_MAKE)   rd /S /Q ..\test\eh\$(USE_MAKE)

	@echo. > ..\Makefiles\config.mak
	
	@echo distclean done.
