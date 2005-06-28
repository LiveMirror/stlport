# Time-stamp: <03/07/15 12:20:52 ptr>
# $Id$

!ifndef CFGSET
depend: 
	@echo STLport configuration error!
	@echo Please go to build\lib and run configure.bat
!else
depend: bld_sys_msg dirs DEP_INIT $(ALLBASE) DEP_END
	@echo depend done.

.precious: depend

DEP_INIT:
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@if exist dep_srr.tmp del dep_srr.tmp
	@if exist dep_sdr.tmp del dep_sdr.tmp
	@if exist dep_sdd.tmp del dep_sdd.tmp
	@if exist dep_arr.tmp del dep_arr.tmp
	@if exist dep_adr.tmp del dep_adr.tmp
	@if exist dep_add.tmp del dep_add.tmp
	@if exist objs_srr.inc del objs_srr.inc
	@if exist objs_sdr.inc del objs_sdr.inc
	@if exist objs_sdd.inc del objs_sdd.inc
	@if exist objs_arr.inc del objs_arr.inc
	@if exist objs_adr.inc del objs_adr.inc
	@if exist objs_add.inc del objs_add.inc
	@echo OBJ          = \ > dep_srr.tmp
	@echo OBJ_DBG      = \ > dep_sdr.tmp
	@echo OBJ_STLDBG   = \ > dep_sdd.tmp
	@echo OBJ_A        = \ > dep_arr.tmp
	@echo OBJ_A_DBG    = \ > dep_adr.tmp
	@echo OBJ_A_STLDBG = \ > dep_add.tmp
	@cd $(SRCROOT_EXT)

DEP_END:
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@echo. >> dep_srr.tmp
	@echo. >> dep_sdr.tmp
	@echo. >> dep_sdd.tmp
	@echo. >> dep_arr.tmp
	@echo. >> dep_adr.tmp
	@echo. >> dep_add.tmp
	@copy dep_srr.tmp + dep_sdr.tmp + dep_sdd.tmp + dep_arr.tmp + dep_adr.tmp + dep_add.tmp depends.inc > NUL
	@if exist dep_srr.tmp del dep_srr.tmp
	@if exist dep_sdr.tmp del dep_sdr.tmp
	@if exist dep_sdd.tmp del dep_sdd.tmp
	@if exist dep_arr.tmp del dep_arr.tmp
	@if exist dep_adr.tmp del dep_adr.tmp
	@if exist dep_add.tmp del dep_add.tmp
	@cd $(SRCROOT_EXT)

$(ALLBASE):
	@cd $(SRCROOT_EXT)\$(USE_MAKE)
	@echo $&.obj
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR)\$&.obj \ >> dep_srr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)\$&.obj \ >> dep_sdr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)\$&.obj \ >> dep_sdd.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR)\$&.obj + >> objs_srr.inc
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_DBG)\$&.obj + >> objs_sdr.inc
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_STLDBG)\$&.obj + >> objs_sdd.inc
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A)\$&.obj \ >> dep_arr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)\$&.obj \ >> dep_adr.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)\$&.obj \ >> dep_add.tmp
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A)\$&.obj + >> objs_arr.inc
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_DBG)\$&.obj + >> objs_adr.inc
	@echo $(SRCROOT_EXT)\$(OUTPUT_DIR_A_STLDBG)\$&.obj + >> objs_add.inc
	@cd $(SRCROOT_EXT)

!include $(DEPENDS_COLLECTION)

!endif
