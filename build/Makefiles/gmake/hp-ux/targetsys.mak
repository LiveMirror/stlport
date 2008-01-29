# Time-stamp: <05/09/09 21:05:18 ptr>

ifeq ($(M_ARCH),ia64)
SO := so
else
SO := sl
endif

ARCH := a
AR := ar
AR_INS_R := -rs
AR_EXTR := -x
AR_OUT = $@
