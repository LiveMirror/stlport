# -*- makefile -*- Time-stamp: <04/07/25 17:58:50 ptr>
# $Id$

install:	install-release install-dbg install-stldbg

install-release:	release-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG} $(INSTALL_BIN_DIR)

install-dbg:	dbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_DBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_DBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_DBG} $(INSTALL_BIN_DIR_DBG)

install-stldbg:	stldbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR_STLDBG) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR_STLDBG) ; \
	fi
	$(INSTALL_EXE) ${PRG_STLDBG} $(INSTALL_BIN_DIR_STLDBG)
