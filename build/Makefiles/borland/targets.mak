# Time-stamp:
# $Id: targets.mak

#!message build\Makefiles\borland\targets.mak

ALLORIG	= $(SRC_CPP) $(SRC_CC) $(SRC_C)

!if $(LIBNAME) == stlp$(MAJOR)$(MINOR)
ALLBASE = $(ALLORIG:../../src/=)
!endif

!if $(PRGNAME) == stl_unit_test
ALLBAS0 = $(ALLORIG:../../../test/unit/=)
ALLBASE = $(ALLBAS0:/=\)
!endif

!if $(PRGNAME) == eh_test
ALLBAS0 = $(ALLORIG:../../../test/eh/=)
ALLBASE = $(ALLBAS0:/=\)
!endif

.precious: $(ALLORIG)
.precious: $(ALLBASE)

ALLOBJ3 = $(SRC_CPP:.cpp=.obj) $(SRC_CC:.cc=.obj) $(SRC_C:.c=.obj)
ALLOBJ2 = $(ALLOBJ3:../../src/=)
ALLOBJ1 = $(ALLOBJ2:../../../test/unit/=)
ALLOBJ0 = $(ALLOBJ1:cppunit/=)
ALLOBJS = $(ALLOBJ0:../../../test/eh/=)
ALLOBJS_A = $(ALLOBJS:.obj=.obj +-) 

#ALLRESS = $(SRC_RC)
ALLRESS  =

!ifdef $(SRC_RC) 
.precious: $(ALLRESS)
!endif

OBJ          = $(OBJ)
OBJ_DBG      = $(OBJ_DBG)
OBJ_STLDBG   = $(OBJ_STLDBG)

OBJ_A        = $(OBJ_A)
OBJ_A_DBG    = $(OBJ_A_DBG)
OBJ_A_STLDBG = $(OBJ_A_STLDBG)

RES          = $(ALLRESS) 
RES_DBG      = $(ALLRESS) 
RES_STLDBG   = $(ALLRESS) 

!ifdef NOINIT_SO
DEF_FILE        = $(RULESBASE)\$(USE_MAKE)\noinit.def
DEF_FILE_DBG    = $(RULESBASE)\$(USE_MAKE)\noinit.def
DEF_FILE_STLDBG = $(RULESBASE)\$(USE_MAKE)\noinit.def
!else
DEF_FILE        = 
DEF_FILE_DBG    = 
DEF_FILE_STLDBG = 
!endif

!ifdef NOINIT_A
DEF_FILE_A        = $(RULESBASE)\$(USE_MAKE)\noinit.def
DEF_FILE_A_DBG    = $(RULESBASE)\$(USE_MAKE)\noinit.def
DEF_FILE_A_STLDBG = $(RULESBASE)\$(USE_MAKE)\noinit.def
!else
DEF_FILE_A        = 
DEF_FILE_A_DBG    = 
DEF_FILE_A_STLDBG = 
!endif
