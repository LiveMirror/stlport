# Time-stamp: 
# $Id: targetdirs.mak

#!message build\Makefiles\borland\targetdirs.mak

!ifndef BC5ROOT
BC5ROOT = $(MAKEDIR)\..
!endif

!ifdef TARGET_PROC
TARGET_NAME=$(TARGET_PROC)_
!else
TARGET_NAME=
!endif

!ifndef STLPORT_DIR
! error STLPORT_DIR is not defined.
!endif

OUTPUT_DIR          = obj\$(TARGET_NAME)$(COMPILER_NAME)\rel$(EXTRA_DIRS)
OUTPUT_DIR_DBG      = obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg$(EXTRA_DIRS)
OUTPUT_DIR_STLDBG   = obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg$(EXTRA_DIRS)
OUTPUT_DIR_A        = obj\$(TARGET_NAME)$(COMPILER_NAME)\static$(EXTRA_DIRS)
OUTPUT_DIR_A_DBG    = obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg$(EXTRA_DIRS)
OUTPUT_DIR_A_STLDBG = obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg$(EXTRA_DIRS)

DEPENDS_COLLECTION  = .\$(USE_MAKE)\depends.inc

INSTALL_LIB_DIR     = $(STLPORT_DIR)\lib

INSTALL_DLL_DIR     = $(STLPORT_DIR)\lib

INSTALL_BIN_DIR     = $(STLPORT_DIR)\bin

!ifdef ALL_TAGS
INSTALL_REL_TAGS    = $(ALL_TAGS:release=install-release)
INSTALL_DBG_TAGS    = $(INSTALL_REL_TAGS:dbg=install-dbg)
INSTALL_STLDBG_TAGS = $(INSTALL_DBG_TAGS:stlinstall-dbg=install-stldbg)
INSTALL_TAGS        = $(INSTALL_STLDBG_TAGS)
!endif

!ifndef INSTALL_TAGS
INSTALL_TAGS = install-release-shared install-dbg-shared install-stldbg-shared install-release-static install-dbg-static install-stldbg-static
!endif

SRR_TAGS = $(ALL_TAGS:release-shared=SRR)
SDD_TAGS = $(SRR_TAGS:stldbg-shared=SDD)
SDR_TAGS = $(SDD_TAGS:dbg-shared=SDR)
ARR_TAGS = $(SDR_TAGS:release-static=ARR)
ADD_TAGS = $(ARR_TAGS:stldbg-static=ADD)
ADR_TAGS = $(ADD_TAGS:dbg-static=ADR)
SET_TAGS = $(ADR_TAGS)

OUTPUT_DIRS = \
		$(OUTPUT_DIR) \
        $(OUTPUT_DIR_DBG) \
		$(OUTPUT_DIR_STLDBG) \
		$(OUTPUT_DIR_A) \
		$(OUTPUT_DIR_A_DBG) \
		$(OUTPUT_DIR_A_STLDBG) 

dirs : create_dirs $(OUTPUT_DIRS)

create_dirs :
!if "$(OS)" == "Windows_NT"
	@if not exist .\$(USE_MAKE) mkdir .\$(USE_MAKE)
	@if not exist $(STLPORT_DIR)\bin mkdir $(STLPORT_DIR)\bin
!else
	@if not exist .\$(USE_MAKE).tmp mkdir .\$(USE_MAKE) 
	@if not exist .\$(USE_MAKE).tmp echo. > .\$(USE_MAKE).tmp

	@if not exist $(STLPORT_DIR)\bin.tmp mkdir $(STLPORT_DIR)\bin
	@if not exist $(STLPORT_DIR)\bin.tmp echo. > $(STLPORT_DIR)\bin.tmp
!endif

delete_tags :
	@if exist .\$(USE_MAKE)\tag_srr.tmp del .\$(USE_MAKE)\tag_srr.tmp
	@if exist .\$(USE_MAKE)\tag_sdr.tmp del .\$(USE_MAKE)\tag_sdr.tmp
	@if exist .\$(USE_MAKE)\tag_sdd.tmp del .\$(USE_MAKE)\tag_sdd.tmp
	@if exist .\$(USE_MAKE)\tag_arr.tmp del .\$(USE_MAKE)\tag_arr.tmp
	@if exist .\$(USE_MAKE)\tag_adr.tmp del .\$(USE_MAKE)\tag_adr.tmp
	@if exist .\$(USE_MAKE)\tag_add.tmp del .\$(USE_MAKE)\tag_add.tmp

.precious: dirs
.precious: create_dirs
.precious: delete_tags

$(OUTPUT_DIRS) : delete_tags $(SET_TAGS)
!if "$(OS)" == "Windows_NT"

	@if not exist obj mkdir obj
	@if not exist obj\$(TARGET_NAME)$(COMPILER_NAME) mkdir obj\$(TARGET_NAME)$(COMPILER_NAME)

	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\rel if exist .\$(USE_MAKE)\tag_srr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\rel mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg if exist .\$(USE_MAKE)\tag_sdr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg if exist .\$(USE_MAKE)\tag_sdd.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static if exist .\$(USE_MAKE)\tag_arr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg if exist .\$(USE_MAKE)\tag_adr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg if exist .\$(USE_MAKE)\tag_add.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg mkdir $< 

!else

	@if not exist obj.tmp mkdir obj 
	@if not exist obj.tmp echo. > obj.tmp

	@if not exist obj\$(TARGET_NAME)$(COMPILER_NAME).tmp mkdir obj\$(TARGET_NAME)$(COMPILER_NAME) 
	@if not exist obj\$(TARGET_NAME)$(COMPILER_NAME).tmp echo. > obj\$(TARGET_NAME)$(COMPILER_NAME).tmp

	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\rel if exist .\$(USE_MAKE)\tag_srr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\rel.tmp mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg if exist .\$(USE_MAKE)\tag_sdr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg.tmp mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg if exist .\$(USE_MAKE)\tag_sdd.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg.tmp mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static if exist .\$(USE_MAKE)\tag_arr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static.tmp mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg if exist .\$(USE_MAKE)\tag_adr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg.tmp mkdir $< 
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg if exist .\$(USE_MAKE)\tag_add.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg.tmp mkdir $< 

	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\rel if exist .\$(USE_MAKE)\tag_srr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\rel.tmp echo. > $<.tmp
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg if exist .\$(USE_MAKE)\tag_sdr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\dbg.tmp echo. > $<.tmp
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg if exist .\$(USE_MAKE)\tag_sdd.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\stldbg.tmp echo. > $<.tmp
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static if exist .\$(USE_MAKE)\tag_arr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static.tmp echo. > $<.tmp
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg if exist .\$(USE_MAKE)\tag_adr.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_dbg.tmp echo. > $<.tmp
	@if $< == obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg if exist .\$(USE_MAKE)\tag_add.tmp if not exist obj\$(TARGET_NAME)$(COMPILER_NAME)\static_stldbg.tmp echo. > $<.tmp

!endif

$(SET_TAGS) :
    @if not $& == SRR if not $& == SDR if not $& == SDD if not $& == ARR if not $& == ADR if not $& == ADD echo bad tag: $&
	@if $& == SRR echo release-shared >> .\$(USE_MAKE)\tag_srr.tmp
	@if $& == SDR echo dbg-shared >> .\$(USE_MAKE)\tag_sdr.tmp
	@if $& == SDD echo stldbg-shared >> .\$(USE_MAKE)\tag_sdd.tmp
	@if $& == ARR echo release-static >> .\$(USE_MAKE)\tag_arr.tmp
	@if $& == ADR echo dbg-static >> .\$(USE_MAKE)\tag_adr.tmp
	@if $& == ADD echo stldbg-static >> .\$(USE_MAKE)\tag_add.tmp



