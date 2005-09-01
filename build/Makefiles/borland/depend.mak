# Time-stamp: 
# $Id: depend.mak 

#!message build\Makefiles\borland\depend.mak

!include $(RULESBASE)\$(USE_MAKE)\depend.inc

depend: build_system_message dirs objs_inc_delete depend_tmp_init $(ALLBASE) depend_tmp_end depend_inc_create depend_tmp_delete 
	@echo SETUP_MSG = This file is required for setup. > $(RULESBASE)\$(USE_MAKE)\sysid.inc
	@if exist $(RULESBASE)\config.mak echo CFGSET = $(COMPILER_NAME) >> $(RULESBASE)\$(USE_MAKE)\sysid.inc
	@if exist %WINDIR%\system32\user.exe echo WINSYSDIR = %WINDIR%\system32 >> $(RULESBASE)\$(USE_MAKE)\sysid.inc
	@if exist %WINDIR%\system\user.exe echo WINSYSDIR = %WINDIR%\system >> $(RULESBASE)\$(USE_MAKE)\sysid.inc
	@echo SETUP_MSG = This file is required for setup. > $(RULESBASE)\$(USE_MAKE)\depend.inc
	@if exist $(STLPORT_DIR)\build\lib\$(USE_MAKE)\depends.inc       echo DEPEND_LIB  = $(COMPILER_NAME) >> $(RULESBASE)\$(USE_MAKE)\depend.inc
	@if exist $(STLPORT_DIR)\build\test\unit\$(USE_MAKE)\depends.inc echo DEPEND_UNIT = $(COMPILER_NAME) >> $(RULESBASE)\$(USE_MAKE)\depend.inc
	@if exist $(STLPORT_DIR)\build\test\eh\$(USE_MAKE)\depends.inc   echo DEPEND_EH   = $(COMPILER_NAME) >> $(RULESBASE)\$(USE_MAKE)\depend.inc
	@echo depend done.

depend_tmp_delete :
	@if exist .\$(USE_MAKE)\dep_srr.tmp del .\$(USE_MAKE)\dep_srr.tmp
	@if exist .\$(USE_MAKE)\dep_sdr.tmp del .\$(USE_MAKE)\dep_sdr.tmp
	@if exist .\$(USE_MAKE)\dep_sdd.tmp del .\$(USE_MAKE)\dep_sdd.tmp
	@if exist .\$(USE_MAKE)\dep_arr.tmp del .\$(USE_MAKE)\dep_arr.tmp
	@if exist .\$(USE_MAKE)\dep_adr.tmp del .\$(USE_MAKE)\dep_adr.tmp
	@if exist .\$(USE_MAKE)\dep_add.tmp del .\$(USE_MAKE)\dep_add.tmp

	@if exist .\$(USE_MAKE)\objs_arr.tmp del .\$(USE_MAKE)\objs_arr.tmp
	@if exist .\$(USE_MAKE)\objs_adr.tmp del .\$(USE_MAKE)\objs_adr.tmp
	@if exist .\$(USE_MAKE)\objs_add.tmp del .\$(USE_MAKE)\objs_add.tmp

depend_tmp_init:
	@echo OBJ          = \ > .\$(USE_MAKE)\dep_srr.tmp
	@echo OBJ_DBG      = \ > .\$(USE_MAKE)\dep_sdr.tmp
	@echo OBJ_STLDBG   = \ > .\$(USE_MAKE)\dep_sdd.tmp
	@echo OBJ_A        = \ > .\$(USE_MAKE)\dep_arr.tmp
	@echo OBJ_A_DBG    = \ > .\$(USE_MAKE)\dep_adr.tmp
	@echo OBJ_A_STLDBG = \ > .\$(USE_MAKE)\dep_add.tmp
	@echo TLIB_A        = \ > .\$(USE_MAKE)\objs_arr.tmp
	@echo TLIB_A_DBG    = \ > .\$(USE_MAKE)\objs_adr.tmp
	@echo TLIB_A_STLDBG = \ > .\$(USE_MAKE)\objs_add.tmp


depend_tmp_end :
	@echo. >> .\$(USE_MAKE)\dep_srr.tmp
	@echo. >> .\$(USE_MAKE)\dep_sdr.tmp
	@echo. >> .\$(USE_MAKE)\dep_sdd.tmp
	@echo. >> .\$(USE_MAKE)\dep_arr.tmp
	@echo. >> .\$(USE_MAKE)\dep_adr.tmp
	@echo. >> .\$(USE_MAKE)\dep_add.tmp
	@echo. >> .\$(USE_MAKE)\objs_arr.tmp
	@echo. >> .\$(USE_MAKE)\objs_adr.tmp
	@echo. >> .\$(USE_MAKE)\objs_add.tmp

depend_inc_create :
	@copy .\$(USE_MAKE)\dep_srr.tmp + \
          .\$(USE_MAKE)\dep_sdr.tmp + \
          .\$(USE_MAKE)\dep_sdd.tmp + \
          .\$(USE_MAKE)\dep_arr.tmp + \
          .\$(USE_MAKE)\dep_adr.tmp + \
          .\$(USE_MAKE)\dep_add.tmp + \
          .\$(USE_MAKE)\objs_arr.tmp + \
          .\$(USE_MAKE)\objs_adr.tmp + \
          .\$(USE_MAKE)\objs_add.tmp   \
          .\$(USE_MAKE)\depends.inc > NUL
	
objs_inc_delete :
	@if exist .\$(USE_MAKE)\objs_srr.inc del .\$(USE_MAKE)\objs_srr.inc
	@if exist .\$(USE_MAKE)\objs_sdr.inc del .\$(USE_MAKE)\objs_sdr.inc
	@if exist .\$(USE_MAKE)\objs_sdd.inc del .\$(USE_MAKE)\objs_sdd.inc
	@if exist .\$(USE_MAKE)\objs_arr.inc del .\$(USE_MAKE)\objs_arr.inc
	@if exist .\$(USE_MAKE)\objs_adr.inc del .\$(USE_MAKE)\objs_adr.inc
	@if exist .\$(USE_MAKE)\objs_add.inc del .\$(USE_MAKE)\objs_add.inc

.precious: depend
.precious: depend_tmp_delete
.precious: depend_tmp_init
.precious: depend_tmp_end
.precious: depend_inc_create
.precious: objs_inc_delete

$(ALLBASE):
	@echo $&.obj

	@echo .\$(OUTPUT_DIR)\$&.obj \ >> .\$(USE_MAKE)\dep_srr.tmp
	@echo .\$(OUTPUT_DIR_DBG)\$&.obj \ >> .\$(USE_MAKE)\dep_sdr.tmp
	@echo .\$(OUTPUT_DIR_STLDBG)\$&.obj \ >> .\$(USE_MAKE)\dep_sdd.tmp

	@echo .\$(OUTPUT_DIR)\$&.obj + >> .\$(USE_MAKE)\objs_srr.inc
	@echo .\$(OUTPUT_DIR_DBG)\$&.obj + >> .\$(USE_MAKE)\objs_sdr.inc
	@echo .\$(OUTPUT_DIR_STLDBG)\$&.obj + >> .\$(USE_MAKE)\objs_sdd.inc

	@echo .\$(OUTPUT_DIR_A)\$&.obj \ >> .\$(USE_MAKE)\dep_arr.tmp
	@echo .\$(OUTPUT_DIR_A_DBG)\$&.obj \ >> .\$(USE_MAKE)\dep_adr.tmp
	@echo .\$(OUTPUT_DIR_A_STLDBG)\$&.obj \ >> .\$(USE_MAKE)\dep_add.tmp

	@echo .\$(OUTPUT_DIR_A)\$&.obj + >> .\$(USE_MAKE)\objs_arr.inc
	@echo .\$(OUTPUT_DIR_A_DBG)\$&.obj + >> .\$(USE_MAKE)\objs_adr.inc
	@echo .\$(OUTPUT_DIR_A_STLDBG)\$&.obj + >> .\$(USE_MAKE)\objs_add.inc

	@echo static\$&.obj \ >> .\$(USE_MAKE)\objs_arr.tmp
	@echo static_dbg\$&.obj \ >> .\$(USE_MAKE)\objs_adr.tmp
	@echo static_stldbg\$&.obj \ >> .\$(USE_MAKE)\objs_add.tmp

!if $(LIBNAME) == stlp$(MAJOR)$(MINOR)
! ifdef DEPEND_LIB
!  include $(DEPENDS_COLLECTION)
!endif
!elif $(PRGNAME) == stl_unit_test
! ifdef DEPEND_UNIT
!  include $(DEPENDS_COLLECTION)
! endif
!elif $(PRGNAME) == eh_test
! ifdef DEPEND_EH
!  include $(DEPENDS_COLLECTION)
! endif
!endif

.NOSILENT
