# Time-stamp:
# $Id: targets.mak

#!message build\Makefiles\borland\targets.mak

ALLORIG	= $(SRC_CPP) $(SRC_CC) $(SRC_C)

!if $(LIBNAME) == stlp$(MAJOR)$(MINOR)
ALLBASE = $(ALLORIG:../../src/=)
!endif

!if $(PRGNAME) == stl_unit_test
! ifdef EXCLUDE_TESTS
ALLBAS0 = $(ALLORIG_FILTERED)
! else
ALLBAS0 = $(ALLORIG:../../../test/unit/=)
! endif
ALLBASE = $(ALLBAS0:/=\)
!endif

!if $(PRGNAME) == eh_test
ALLBAS0 = $(ALLORIG:../../../test/eh/=)
ALLBASE = $(ALLBAS0:/=\)
!endif

.precious: $(ALLORIG)
.precious: $(ALLBASE)

ALLOBJS2 = $(SRC_CPP:.cpp=.obj) $(SRC_CC:.cc=.obj) $(SRC_C:.c=.obj)
ALLOBJS1 = $(ALLOBJS2: ../../src/=)
ALLOBJS0 = $(ALLOBJS1:../../src/=)
ALLOBJS  = $(ALLOBJS0:.obj =.obj)

ALLRES0 = $(SRC_RC:/=\) 
ALLRESS = #$(ALLRES0:.rc=.res) 

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
