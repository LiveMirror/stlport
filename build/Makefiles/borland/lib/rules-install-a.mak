# Time-stamp: 
# $Id: rules-install-a.mak

#!message build\Makefiles\borland\lib\rules-install-a.mak

.AUTODEPEND
#.SILENT

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-static install-dbg-static install-stldbg-static
!endif

install-release-static: release-static
	@if exist $(A_NAME_OUT) echo $(INSTALL_A) $(A_NAME_OUT) $(INSTALL_LIB_DIR)
	@if exist $(A_NAME_OUT) $(INSTALL_A) $(A_NAME_OUT) $(INSTALL_LIB_DIR) > NUL
	@echo.

install-dbg-static: dbg-static
	@if exist $(A_NAME_OUT_DBG) echo $(INSTALL_A) $(A_NAME_OUT_DBG) $(INSTALL_LIB_DIR)
	@if exist $(A_NAME_OUT_DBG) $(INSTALL_A) $(A_NAME_OUT_DBG) $(INSTALL_LIB_DIR) > NUL
	@echo.

install-stldbg-static: stldbg-static
	@if exist $(A_NAME_OUT_STLDBG) echo $(INSTALL_A) $(A_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR)
	@if exist $(A_NAME_OUT_STLDBG) $(INSTALL_A) $(A_NAME_OUT_STLDBG) $(INSTALL_LIB_DIR) > NUL
	@echo.

.NOSILENT

.precious: install-release-static
.precious: install-dbg-static
.precious: install-stldbg-static
