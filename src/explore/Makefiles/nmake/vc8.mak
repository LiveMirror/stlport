!ifndef MSVC_DIR
MSVC_DIR = c:\Program Files\Microsoft Visual Studio 8\VC
!endif

#CFLAGS_COMMON = /nologo /Tc /W3 
CFLAGS_COMMON = /nologo /W3 /GR /EHsc
CXXFLAGS_COMMON = /nologo /W3 /GR /EHsc

OPT_REL = $(OPT_REL) /GL

!include $(RULESBASE)/$(USE_MAKE)/vc-common.mak

