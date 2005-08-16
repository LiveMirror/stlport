# -*- makefile -*- Time-stamp:
# $Id: clean.mak

clobber: clean

	@if exist $(PRG)          del $(PRG)
	@if exist $(PRG_DBG)      del $(PRG_DBG)
	@if exist $(PRG_STLDBG)   del $(PRG_STLDBG)
	@if exist $(PRG_A)        del $(PRG_A)
	@if exist $(PRG_A_DBG)    del $(PRG_A_DBG)
	@if exist $(PRG_A_STLDBG) del $(PRG_A_STLDBG)

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

	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME)        del $(INSTALL_BIN_DIR)\$(PRG_NAME)
	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME_DBG)    del $(INSTALL_BIN_DIR)\$(PRG_NAME_DBG)
	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME_STLDBG) del $(INSTALL_BIN_DIR)\$(PRG_NAME_STLDBG)

	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME_A)        del $(INSTALL_BIN_DIR)\$(PRG_NAME_A)
	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME_A_DBG)    del $(INSTALL_BIN_DIR)\$(PRG_NAME_A_DBG)
	@if exist $(INSTALL_BIN_DIR)\$(PRG_NAME_A_STLDBG) del $(INSTALL_BIN_DIR)\$(PRG_NAME_A_STLDBG)
	
!if "$(OS)" == "Windows_NT"
	@if not exist $(INSTALL_BIN_DIR)\*.exe if exist $(INSTALL_BIN_DIR) rmdir /S /Q $(INSTALL_BIN_DIR)
!else
	@if not exist $(INSTALL_BIN_DIR)\*.exe if exist $(INSTALL_BIN_DIR)\..\bin.tmp rmdir $(INSTALL_BIN_DIR)
	@if not exist $(INSTALL_BIN_DIR)\*.exe if exist $(INSTALL_BIN_DIR)\..\bin.tmp del $(INSTALL_BIN_DIR)\..\bin.tmp
!endif

	@echo distclean done.


