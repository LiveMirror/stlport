# Time-stamp: 
# $Id: rules-install.mak

#!message build\Makefiles\borland\app\rules-install.mak

.AUTODEPEND
#.SILENT

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared install-release-static install-dbg-static install-stldbg-static
!endif

install-release-shared: release-shared
	@if exist $(PRG) echo $(INSTALL_EXE) $(PRG) $(INSTALL_BIN_DIR)
	@if exist $(PRG) $(INSTALL_EXE) $(PRG) $(INSTALL_BIN_DIR) > NUL
	@echo.

install-dbg-shared: dbg-shared
	@if exist $(PRG_DBG) echo $(INSTALL_EXE) $(PRG_DBG) $(INSTALL_BIN_DIR)
	@if exist $(PRG_DBG) $(INSTALL_EXE) $(PRG_DBG) $(INSTALL_BIN_DIR) > NUL
	@echo.

install-stldbg-shared: stldbg-shared
	@if exist $(PRG_STLDBG) echo $(INSTALL_EXE) $(PRG_STLDBG) $(INSTALL_BIN_DIR)
	@if exist $(PRG_STLDBG) $(INSTALL_EXE) $(PRG_STLDBG) $(INSTALL_BIN_DIR) > NUL
	@echo.

install-release-static: release-static
	@if exist $(PRG_A) echo $(INSTALL_EXE) $(PRG_A) $(INSTALL_BIN_DIR)
	@if exist $(PRG_A) $(INSTALL_EXE) $(PRG_A) $(INSTALL_BIN_DIR) > NUL
	@echo.

install-dbg-static: dbg-static
	@if exist $(PRG_A_DBG) echo $(INSTALL_EXE) $(PRG_A_DBG) $(INSTALL_BIN_DIR)
	@if exist $(PRG_A_DBG) $(INSTALL_EXE) $(PRG_A_DBG) $(INSTALL_BIN_DIR) > NUL
	@echo.

install-stldbg-static: stldbg-static
	@if exist $(PRG_A_STLDBG) echo $(INSTALL_EXE) $(PRG_A_STLDBG) $(INSTALL_BIN_DIR)
	@if exist $(PRG_A_STLDBG) $(INSTALL_EXE) $(PRG_A_STLDBG) $(INSTALL_BIN_DIR) > NUL
	@echo.

.NOSILENT

.precious: install-release-shared
.precious: install-dbg-shared
.precious: install-stldbg-shared
.precious: install-release-static
.precious: install-dbg-static
.precious: install-stldbg-static
