
CXX = icl
CC = icl
LINK = xilink

CFLAGS_COMMON = /nologo /W4 /GR /GX
CXXFLAGS_COMMON = /nologo /W4 /GR /GX

OPT_REL = $(OPT_REL) /GL

!include $(RULESBASE)/$(USE_MAKE)/vc-common.mak

