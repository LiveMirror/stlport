# -*- makefile -*- Time-stamp: <2011-03-23 18:32:10 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 6
LIBMINOR = 0

PRGNAME = stl_unit_test

SRC_CC = suite.cc test_suite.cc logger_stdio.cc

SRC_CPP = \
	msstring_test.cpp \
	stream_test.cpp \
        iter_test.cpp \
        ostmit_test.cpp \
        istmit_test.cpp \
        ioiter_test.cpp \
        codecvt_test.cpp \
        locale_test.cpp \
        shared_ptr_test.cpp \
        exception_test.cpp \
        errno_test.cpp \
	fstream_test.cpp
