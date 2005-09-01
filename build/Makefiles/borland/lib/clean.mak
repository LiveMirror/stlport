# -*- makefile -*- Time-stamp: 
# $Id: clean.mak

#!message build\Makefiles\borland\lib\clean.mak

clobber:        clean

	@if exist $(SO_NAME_OUT)          del $(SO_NAME_OUT)
	@if exist $(SO_NAME_OUT_DBG)      del $(SO_NAME_OUT_DBG)
	@if exist $(SO_NAME_OUT_STLDBG)   del $(SO_NAME_OUT_STLDBG)
	@if exist $(LIB_NAME_OUT)         del $(LIB_NAME_OUT)
	@if exist $(LIB_NAME_OUT_DBG)     del $(LIB_NAME_OUT_DBG)
	@if exist $(LIB_NAME_OUT_STLDBG)  del $(LIB_NAME_OUT_STLDBG)
	@if exist $(A_NAME_OUT)           del $(A_NAME_OUT)
	@if exist $(A_NAME_OUT_DBG)       del $(A_NAME_OUT_DBG)
	@if exist $(A_NAME_OUT_STLDBG)    del $(A_NAME_OUT_STLDBG)

!if "$(OS)" == "Windows_NT"
	@if exist $(OUTPUT_DIR)          rmdir /S /Q $(OUTPUT_DIR)
	@if exist $(OUTPUT_DIR_DBG)      rmdir /S /Q $(OUTPUT_DIR_DBG)
	@if exist $(OUTPUT_DIR_STLDBG)   rmdir /S /Q $(OUTPUT_DIR_STLDBG)
	@if exist $(OUTPUT_DIR_A)        rmdir /S /Q $(OUTPUT_DIR_A)
	@if exist $(OUTPUT_DIR_A_DBG)    rmdir /S /Q $(OUTPUT_DIR_A_DBG)
	@if exist $(OUTPUT_DIR_A_STLDBG) rmdir /S /Q $(OUTPUT_DIR_A_STLDBG)

	@if exist obj\$(TARGET_NAME)$(COMPILER_NAME) rmdir /S /Q obj\$(TARGET_NAME)$(COMPILER_NAME)
	@if exist obj rmdir /S /Q obj
!else
	@if exist $(OUTPUT_DIR).tmp          rmdir $(OUTPUT_DIR)
	@if exist $(OUTPUT_DIR_DBG).tmp      rmdir $(OUTPUT_DIR_DBG)
	@if exist $(OUTPUT_DIR_STLDBG).tmp   rmdir $(OUTPUT_DIR_STLDBG)
	@if exist $(OUTPUT_DIR_A).tmp        rmdir $(OUTPUT_DIR_A)
	@if exist $(OUTPUT_DIR_A_DBG).tmp    rmdir $(OUTPUT_DIR_A_DBG)
	@if exist $(OUTPUT_DIR_A_STLDBG).tmp rmdir $(OUTPUT_DIR_A_STLDBG)

	@if exist $(OUTPUT_DIR).tmp          del $(OUTPUT_DIR).tmp
	@if exist $(OUTPUT_DIR_DBG).tmp      del $(OUTPUT_DIR_DBG).tmp
	@if exist $(OUTPUT_DIR_STLDBG).tmp   del $(OUTPUT_DIR_STLDBG).tmp
	@if exist $(OUTPUT_DIR_A).tmp        del $(OUTPUT_DIR_A).tmp
	@if exist $(OUTPUT_DIR_A_DBG).tmp    del $(OUTPUT_DIR_A_DBG).tmp
	@if exist $(OUTPUT_DIR_A_STLDBG).tmp del $(OUTPUT_DIR_A_STLDBG).tmp

	@if exist obj\$(TARGET_NAME)$(COMPILER_NAME).tmp rmdir obj\$(TARGET_NAME)$(COMPILER_NAME)
	@if exist obj\$(TARGET_NAME)$(COMPILER_NAME).tmp del obj\$(TARGET_NAME)$(COMPILER_NAME).tmp

	@if exist obj.tmp rmdir obj
	@if exist obj.tmp del obj.tmp

!endif
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
	
!if "$(OS)" == "Windows_NT"
	@if exist $(USE_MAKE)              rmdir /S /Q $(USE_MAKE)
	@if exist ..\test\unit\$(USE_MAKE) rmdir /S /Q ..\test\unit\$(USE_MAKE)
	@if exist ..\test\eh\$(USE_MAKE)   rmdir /S /Q ..\test\eh\$(USE_MAKE)
!else
	@if exist $(USE_MAKE).tmp              rmdir $(USE_MAKE)
	@if exist ..\test\unit\$(USE_MAKE).tmp rmdir ..\test\unit\$(USE_MAKE)
	@if exist ..\test\eh\$(USE_MAKE).tmp   rmdir ..\test\eh\$(USE_MAKE)

	@if exist $(USE_MAKE).tmp              del $(USE_MAKE).tmp
	@if exist ..\test\unit\$(USE_MAKE).tmp del ..\test\unit\$(USE_MAKE).tmp
	@if exist ..\test\eh\$(USE_MAKE).tmp   del ..\test\eh\$(USE_MAKE).tmp
!endif

	@if exist ..\Makefiles\config.mak  del ..\Makefiles\config.mak
	@echo SETUP_MSG = This file is required for setup. > ..\Makefiles\$(USE_MAKE)\depend.inc
	@echo SETUP_MSG = This file is required for setup. > ..\Makefiles\$(USE_MAKE)\sysid.inc
	
	@echo distclean done.
