#
# Note : this makefile is for gcc-2.95 and later !
#

#
# compiler
#
CC = gcc 
CXX = g++ -fexceptions

#
# Basename for libraries
#
LIB_BASENAME = libstlport_gcc

#
# guts for common stuff
#
#
LINK=ar cr
# 2.95 flag

#Does not work yet for EMX
#DYN_LINK=g++ -pthread -fexceptions -shared -o

OBJEXT=o
#DYNEXT=so
STEXT=a
RM=rm -rf
PATH_SEP=/
MKDIR=mkdir -p
COMP=GCC$(ARCH)
INSTALL_STEP = install_unix 

#all:  all_dynamic all_static symbolic_links 
all:  all_static 

include common_macros.mak

WARNING_FLAGS= -Wall -W -Wno-sign-compare -Wno-unused -Wno-uninitialized -ftemplate-depth-32

#EMX GCC3 defines "unix" - not a good idea
#EMX GCC < 3.x does not define OS2 by default
CXXFLAGS_COMMON = -I${STLPORT_DIR} ${WARNING_FLAGS} -U__unix -Uunix -DOS2 -D__OS2__ -Zmt

CXXFLAGS_RELEASE_static = $(CXXFLAGS_COMMON) -O2
CXXFLAGS_RELEASE_dynamic = $(CXXFLAGS_COMMON) -O2 -fPIC

CXXFLAGS_DEBUG_static = $(CXXFLAGS_COMMON) -O -g
CXXFLAGS_DEBUG_dynamic = $(CXXFLAGS_COMMON) -O -g -fPIC

CXXFLAGS_STLDEBUG_static = $(CXXFLAGS_DEBUG_static) -D_STLP_DEBUG
CXXFLAGS_STLDEBUG_dynamic = $(CXXFLAGS_DEBUG_dynamic) -D_STLP_DEBUG

include common_percent_rules.mak
include common_rules.mak


#install: all
#	cp -p $(LIB_TARGET) ${D_LIB_TARGET} ../lib

#%.s: %.cpp
#	$(CXX) $(CXXFLAGS) -O4 -S -pto $<  -o $@


