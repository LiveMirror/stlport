!ifndef MSVC_DIR
MSVC_DIR = c:\Program Files\Microsoft Visual Studio\VC98
!endif

CFLAGS_COMMON = /nologo /W3 /GR /GX
CXXFLAGS_COMMON = /nologo /W3 /GR /GX

!include $(RULESBASE)/$(USE_MAKE)/vc-common.mak

