# Time-stamp: <03/10/27 18:42:41 ptr>
# $Id$

# shared library:
SO  := dll
LIB := dll.a
EXP := exp

# executable:
EXE := .exe

# static library extention:
ARCH := a

AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@

INSTALL := install

INSTALL_SO := ${INSTALL} -m 0755
INSTALL_A := ${INSTALL} -m 0644
INSTALL_EXE := ${INSTALL} -m 0755

