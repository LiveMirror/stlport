# -*- makefile -*- Time-stamp: <03/10/26 15:42:12 ptr>
# $Id$

ALLOBJS = $(ALLOBJS:../../src/=)
ALLRESS = $(ALLRESS:../../src/=)

{../../src}.cpp{$(OUTPUT_DIR)}.o:
	$(COMPILE_cc_REL) $(OUTPUT_OPTION) $<

{../../src}.cpp{$(OUTPUT_DIR_DBG)}.o:
	$(COMPILE_cc_DBG) $(OUTPUT_OPTION_DBG) $<

{../../src}.cpp{$(OUTPUT_DIR_STLDBG)}.o:
	$(COMPILE_cc_STLDBG) $(OUTPUT_OPTION_STLDBG) $<

{../../src}.cpp{$(OUTPUT_DIR_A)}.o:
	$(COMPILE_cc_STATIC_REL) $(OUTPUT_OPTION) $<

{../../src}.cpp{$(OUTPUT_DIR_A_DBG)}.o:
	$(COMPILE_cc_STATIC_DBG) $(OUTPUT_OPTION_STATIC_DBG) $<

{../../src}.cpp{$(OUTPUT_DIR_A_STLDBG)}.o:
	$(COMPILE_cc_STATIC_STLDBG) $(OUTPUT_OPTION_STATIC_STLDBG) $<

