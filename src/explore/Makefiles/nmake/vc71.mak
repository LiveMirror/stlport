!ifndef MSVC_DIR
MSVC_DIR = c:\Program Files\Microsoft Visual Studio .NET 2003\VC7
!endif

CFLAGS_COMMON = /nologo /W3 /GR /GX
CXXFLAGS_COMMON = /nologo /W3 /GR /GX

OPT_REL = $(OPT_REL) /GL

!include $(RULESBASE)/$(USE_MAKE)/vc-common.mak

