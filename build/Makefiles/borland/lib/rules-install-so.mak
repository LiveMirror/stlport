# Time-stamp:
# $Id: rules-install-so.mak

#!message build\Makefiles\borland\lib\rules-install-so.mak

.AUTODEPEND
#.SILENT

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared 
!endif

install-release-shared: release-shared
	@if exist $(SO_NAME_OUT) echo $(INSTALL_SO) $(SO_NAME_OUT) $(INSTALL_DLL_DIR)
	@if exist $(LIB_NAME_OUT) echo $(INSTALL_SO) $(LIB_NAME_OUT) $(INSTALL_LIB_DIR)
	@if exist $(SO_NAME_OUT) $(INSTALL_SO) $(SO_NAME_OUT) $(INSTALL_DLL_DIR) > NUL
	@if exist $(LIB_NAME_OUT) $(INSTALL_SO) $(LIB_NAME_OUT) $(INSTALL_LIB_DIR) > NUL
	@echo.

install-dbg-shared: dbg-shared
	@if exist $(SO_NAME_OUT_DBG) echo $(INSTALL_SO) $(SO_NAME_OUT_DBG) $(INSTALL_DLL_DIR)
	@if exist $(LIB_NAME_OUT_DBG) echo $(INSTALL_SO) $(LIB_NAME_OUT_DBG) $(INSTALL_LIB_DIR)
	@if exist $(SO_NAME_OUT_DBG) $(INSTALL_SO) $(SO_NAME_OUT_DBG) $(INSTALL_DLL_DIR) > NUL
	@if exist $(LIB_NAME_OUT_DBG) $(INSTALL_SO) $(LIB_NAME_OUT_DBG) $(INSTALL_LIB_DIR) > NUL
	@echo.

install-stldbg-shared: stldbg-shared
	@if exist $(SO_NAME_OUT_STLDBG) echo $(INSTALL_SO) $(SO_NAME_OUT_STLDBG) $(INSTALL_DLL_DIR)
	@if exist $(LIB_NAME_OUT_STLDBG) echo $(INSTALL_SO) $(LIB_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR)
	@if exist $(SO_NAME_OUT_STLDBG) $(INSTALL_SO) $(SO_NAME_OUT_STLDBG) $(INSTALL_DLL_DIR) > NUL
	@if exist $(LIB_NAME_OUT_STLDBG) $(INSTALL_SO) $(LIB_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR) > NUL
	@echo.

.NOSILENT

.precious: install-release-shared
.precious: install-dbg-shared
.precious: install-stldbg-shared
