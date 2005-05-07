# Time-stamp: <05/05/06 17:29:04 ptr>
# $Id$

SO := nlm

ARCH := lib
AR := mwldnlm -type library -msgstyle gcc -w off
AR_INS_R := 
AR_EXTR :=
AR_OUT = -o $@

INSTALL := /usr/bin/install

INSTALL_SO := ${INSTALL} -c -m 0755
INSTALL_A := ${INSTALL} -c -m 0644
INSTALL_EXE := ${INSTALL} -c -m 0755

EXE := .nlm
