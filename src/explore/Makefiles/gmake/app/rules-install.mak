# -*- makefile -*- Time-stamp: <04/07/25 17:58:50 ptr>
# $Id$

install:	install-release-shared install-dbg-shared install-stldbg-shared

install-release-shared: release-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG} $(INSTALL_BIN_DIR)

install-dbg-shared: dbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG_DBG} $(INSTALL_BIN_DIR)

install-stldbg-shared: stldbg-shared
	@if [ ! -d $(INSTALL_BIN_DIR) ] ; then \
	  mkdir -p $(INSTALL_BIN_DIR) ; \
	fi
	$(INSTALL_EXE) ${PRG_STLDBG} $(INSTALL_BIN_DIR)
