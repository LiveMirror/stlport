#
#  Target directories
#
#

$(OUTDIR) :
	$(MKDIR) $(OUTDIR)
$(RELEASE_OBJDIR_dynamic) :
	$(MKDIR) $(RELEASE_OBJDIR_dynamic)
$(DEBUG_OBJDIR_dynamic) :
	$(MKDIR) $(DEBUG_OBJDIR_dynamic)
$(STLDEBUG_OBJDIR_dynamic) :
	$(MKDIR) $(STLDEBUG_OBJDIR_dynamic)
$(RELEASE_OBJDIR_static) :
	$(MKDIR) $(RELEASE_OBJDIR_static)
$(DEBUG_OBJDIR_static) :
	$(MKDIR) $(DEBUG_OBJDIR_static)
$(STLDEBUG_OBJDIR_static) :
	$(MKDIR) $(STLDEBUG_OBJDIR_static)
$(RELEASE_OBJDIR_staticx) :
	$(MKDIR) $(RELEASE_OBJDIR_staticx)
$(DEBUG_OBJDIR_staticx) :
	$(MKDIR) $(DEBUG_OBJDIR_staticx)
$(STLDEBUG_OBJDIR_staticx) :
	$(MKDIR) $(STLDEBUG_OBJDIR_staticx)

#create a compiler platform directory
platform: $(PREPARE_STEP)
	-@$(MKDIR) $(OUTDIR)
	-@$(MKDIR) $(OBJDIR_COMMON)
	-@$(MKDIR) $(OBJDIR)

prepare: $(PREPARE_STEP)
	@echo "STLport installation is prepared for use in-place. No iostreams are built yet !"
	@echo "To build and use STLport iostreams, please do : make -f <this makefile> all."
	@echo "To install STLport in a designated directory, please do : make -f <this makefile> install."

clean_all_obj:
	-$(RM) $(OUTDIR)$(PATH_SEP)obj

######   Targets ##################

all_static :   platform $(ALL_STATIC_LIBS)

all_dynamic :  platform $(ALL_DYNAMIC_LIBS)

all_staticx :	platform $(ALL_STATICX_LIBS) 

release_static :  platform $(OUTDIR)$(PATH_SEP)$(RELEASE_LIB)

debug_static :  platform $(OUTDIR)$(PATH_SEP)$(DEBUG_LIB)

stldebug_static :  platform $(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB)

release_staticx :  platform $(OUTDIR)$(PATH_SEP)$(RELEASEX_LIB)
 
debug_staticx :  platform $(OUTDIR)$(PATH_SEP)$(DEBUGX_LIB)

stldebug_staticx :  platform $(OUTDIR)$(PATH_SEP)$(STLDEBUGX_LIB)

release_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB)

debug_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB)

stldebug_dynamic :  platform $(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB)

install :  all $(INSTALL_STEP)

clean : $(CLEAN_SPECIFIC)
	-$(RM) $(RELEASE_OBJDIR_static) $(DEBUG_OBJDIR_static) $(STLDEBUG_OBJDIR_static) \
        $(RELEASE_OBJDIR_staticx) $(DEBUG_OBJDIR_staticx) $(STLDEBUG_OBJDIR_staticx) \
        $(RELEASE_OBJDIR_dynamic) $(DEBUG_OBJDIR_dynamic) $(STLDEBUG_OBJDIR_dynamic) \
        $(OUTDIR)$(PATH_SEP)SunWS_cache SunWS_cache $(OUTDIR)$(PATH_SEP)Templates.DB Templates.DB tempinc

clobber : clean clean_all_obj
	-$(RM) $(OUTDIR)$(PATH_SEP)$(DEBUG_NAME).* \
               $(OUTDIR)$(PATH_SEP)$(RELEASE_NAME).* $(OUTDIR)$(PATH_SEP)$(STLDEBUG_NAME).*

HEADER_DIRS1 = . using wrap_std old_hp 
HEADER_DIRS2 = config stl stl/debug stl/wrappers using/h  wrap_std/h classic_iostreams cpp_runtime cstd cstd_h

symbolic_links :
	$(RM) $(OUTDIR)/$(RELEASE_NAME).$(DYNEXT)
	$(RM) $(OUTDIR)/$(STLDEBUG_NAME).$(DYNEXT)
	$(RM) $(OUTDIR)/$(DEBUG_NAME).$(DYNEXT)
	ln -s $(RELEASE_DYNLIB) $(OUTDIR)/$(RELEASE_NAME).$(DYNEXT)
	-ln -s $(DEBUG_DYNLIB) $(OUTDIR)/$(DEBUG_NAME).$(DYNEXT)
	ln -s $(STLDEBUG_DYNLIB) $(OUTDIR)/$(STLDEBUG_NAME).$(DYNEXT)


$(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB) : $(OUTDIR) $(RELEASE_OBJDIR_dynamic) $(DEF_FILE) $(RELEASE_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(RELEASE_DYNLIB) $(LDFLAGS_RELEASE_dynamic) $(RELEASE_OBJECTS_dynamic) $(LDLIBS_RELEASE_dynamic) 

$(OUTDIR)$(PATH_SEP)$(RELEASE_LIB) : $(OUTDIR) $(RELEASE_OBJDIR_static) $(DEF_FILE) $(RELEASE_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(RELEASE_LIB) $(LDFLAGS_RELEASE_static) $(RELEASE_OBJECTS_static) $(LDLIBS_RELEASE_static)

$(OUTDIR)$(PATH_SEP)$(RELEASEX_LIB) : $(OUTDIR) $(RELEASE_OBJDIR_staticx) $(DEF_FILE) $(RELEASE_OBJECTS_staticx)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_EP)$(RELEASEX_LIB) $(LDFLAGS_RELEASE_static) $(RELEASE_OBJECTS_staticx) $(LDLIBS_RELEASE_static)

$(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB) : $(OUTDIR) $(DEBUG_OBJDIR_dynamic) $(DEF_FILE) $(DEBUG_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(DEBUG_DYNLIB) $(LDFLAGS_DEBUG_dynamic) $(DEBUG_OBJECTS_dynamic) $(LDLIBS_DEBUG_dynamic) 

$(OUTDIR)$(PATH_SEP)$(DEBUG_LIB) : $(OUTDIR) $(DEBUG_OBJDIR_static) $(DEF_FILE) $(DEBUG_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(DEBUG_LIB) $(LDLIBS_DEBUG_static) $(LDFLAGS_DEBUG_static) $(DEBUG_OBJECTS_static)  

$(OUTDIR)$(PATH_SEP)$(DEBUGX_LIB) : $(OUTDIR) $(DEBUG_OBJDIR_staticx) $(DEF_FILE) $(DEBUG_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(DEBUGX_LIB) $(LDLIBS_DEBUG_static) $(LDFLAGS_DEBUG_static) $(DEBUG_OBJECTS_staticx)

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB) : $(OUTDIR) $(STLDEBUG_OBJDIR_dynamic) $(DEF_FILE) $(STLDEBUG_OBJECTS_dynamic)
	$(DYN_LINK) $(DYNLINK_OUT)$(OUTDIR)$(PATH_SEP)$(STLDEBUG_DYNLIB) $(LDFLAGS_STLDEBUG_dynamic) $(STLDEBUG_OBJECTS_dynamic) $(LDLIBS_STLDEBUG_dynamic)

$(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB) : $(OUTDIR) $(STLDEBUG_OBJDIR_static) $(DEF_FILE) $(STLDEBUG_OBJECTS_static)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(STLDEBUG_LIB) $(LDFLAGS_STLDEBUG_static) $(STLDEBUG_OBJECTS_static)  $(LDLIBS_STLDEBUG_static)

$(OUTDIR)$(PATH_SEP)$(STLDEBUGX_LIB) : $(OUTDIR) $(STLDEBUG_OBJDIR_staticx) $(DEF_FILE) $(STLDEBUG_OBJECTS_staticx)
	$(LINK) $(LINK_OUT)$(OUTDIR)$(PATH_SEP)$(STLDEBUGX_LIB) $(LDFLAGS_STLDEBUG_static) $(STLDEBUG_OBJECTS_staticx)  $(LDLIBS_STLDEBUG_static)

#########################################
