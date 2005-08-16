# -*- makefile -*- Time-stamp: 
# $Id: clean.mak

#!message build\Makefiles\borland\clean.mak

clean:

	@if exist $(USE_MAKE)\*.tmp del $(USE_MAKE)\*.tmp
	@if exist $(USE_MAKE)\objs_srr.inc del $(USE_MAKE)\objs_srr.inc
	@if exist $(USE_MAKE)\objs_sdr.inc del $(USE_MAKE)\objs_sdr.inc
	@if exist $(USE_MAKE)\objs_sdd.inc del $(USE_MAKE)\objs_sdd.inc
	@if exist $(USE_MAKE)\objs_arr.inc del $(USE_MAKE)\objs_arr.inc
	@if exist $(USE_MAKE)\objs_adr.inc del $(USE_MAKE)\objs_adr.inc
	@if exist $(USE_MAKE)\objs_add.inc del $(USE_MAKE)\objs_add.inc

	@if exist $(OUTPUT_DIR)\*.obj del $(OUTPUT_DIR)\*.obj
	@if exist $(OUTPUT_DIR)\*.tds del $(OUTPUT_DIR)\*.tds
	@if exist $(OUTPUT_DIR)\*.map del $(OUTPUT_DIR)\*.map

	@if exist $(OUTPUT_DIR_DBG)\*.obj del $(OUTPUT_DIR_DBG)\*.obj
	@if exist $(OUTPUT_DIR_DBG)\*.tds del $(OUTPUT_DIR_DBG)\*.tds
	@if exist $(OUTPUT_DIR_DBG)\*.map del $(OUTPUT_DIR_DBG)\*.map

	@if exist $(OUTPUT_DIR_STLDBG)\*.obj del $(OUTPUT_DIR_STLDBG)\*.obj
	@if exist $(OUTPUT_DIR_STLDBG)\*.tds del $(OUTPUT_DIR_STLDBG)\*.tds 
	@if exist $(OUTPUT_DIR_STLDBG)\*.map del $(OUTPUT_DIR_STLDBG)\*.map 

	@if exist $(OUTPUT_DIR_A)\*.obj del $(OUTPUT_DIR_A)\*.obj
	@if exist $(OUTPUT_DIR_A)\*.tds del $(OUTPUT_DIR_A)\*.tds
	@if exist $(OUTPUT_DIR_A)\*.bak del $(OUTPUT_DIR_A)\*.bak

	@if exist $(OUTPUT_DIR_A_DBG)\*.obj del $(OUTPUT_DIR_A_DBG)\*.obj
	@if exist $(OUTPUT_DIR_A_DBG)\*.tds del $(OUTPUT_DIR_A_DBG)\*.tds
	@if exist $(OUTPUT_DIR_A_DBG)\*.bak del $(OUTPUT_DIR_A_DBG)\*.bak

	@if exist $(OUTPUT_DIR_A_STLDBG)\*.obj del $(OUTPUT_DIR_A_STLDBG)\*.obj
	@if exist $(OUTPUT_DIR_A_STLDBG)\*.tds del $(OUTPUT_DIR_A_STLDBG)\*.tds
	@if exist $(OUTPUT_DIR_A_STLDBG)\*.bak del $(OUTPUT_DIR_A_STLDBG)\*.bak

!if "$(OS)" == "Windows_NT"
	@if exist .\$(USE_MAKE)\. echo. > .\$(USE_MAKE)\depends.inc
!else
	@if exist $(USE_MAKE).tmp echo. > depends.inc
	@if exist $(USE_MAKE).tmp copy depends.inc .\$(USE_MAKE)\depends.inc > NUL
	@if exist depends.inc del depends.inc
!endif

	@echo clean done.
