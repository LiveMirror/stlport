# Time-stamp: 
# $Id: sys.mak

#!message build\Makefiles\borland\sys.mak

.AUTODEPEND

# library extension:
SO  = dll
LIB = lib

# executable extension:
EXE = exe

# static library utility:
ARCH     = lib
AR       = tlib
AR_INS_R = 
AR_EXTR  = /C /E /P128 /0
AR_OUT   = 

# install utility:
INSTALL = copy

INSTALL_SO  = $(INSTALL)
INSTALL_A   = $(INSTALL)
INSTALL_EXE = $(INSTALL)

# compiler options:
!include $(RULESBASE)\$(USE_MAKE)\$(COMPILER_NAME).mak
