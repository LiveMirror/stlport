# -*- makefile -*- Time-stamp: <03/10/17 14:09:57 ptr>
# $Id$


# Oh, the commented below work for gmake 3.78.1 and above,
# but phrase without tag not work for it. Since gmake 3.79 
# tag with assignment fail, but work assignment for all tags
# (really that more correct).

LDFLAGS_REL = /LTCG

!include $(RULESBASE)/$(USE_MAKE)/lib/vc-common.mak

