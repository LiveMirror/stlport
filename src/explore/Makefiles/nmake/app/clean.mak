# -*- makefile -*- Time-stamp: <03/10/26 16:17:03 ptr>
# $Id$

clobber:	clean
	@-del /F /Q $(PRG)
	@-del /F /Q $(PRG_DBG)
	@-del /F /Q $(PRG_STLDBG)
	@-del /F /Q $(PRG_A)
	@-del /F /Q $(PRG_A_DBG)
	@-del /F /Q $(PRG_A_STLDBG)

distclean:	clobber
	@-del /F /Q  $(INSTALL_BIN_DIR)\$(PRG_NAME)
	@-del /F /Q  $(INSTALL_BIN_DIR_DBG)\$(PRG_NAME_DBG)
	@-del /F /Q  $(INSTALL_BIN_DIR_STLDBG)\$(PRG_NAME_STLDBG)
	@-del /F /Q  $(INSTALL_BIN_DIR)\$(PRG_NAME_A)
	@-del /F /Q  $(INSTALL_BIN_DIR_DBG)\$(PRG_NAME_A_DBG)
	@-del /F /Q  $(INSTALL_BIN_DIR_STLDBG)\$(PRG_NAME_A_STLDBG)
