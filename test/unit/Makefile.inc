# -*- makefile -*- Time-stamp: <2010-12-08 15:28:00 ptr>

# this is the version number of needed STLport library for linking
LIBMAJOR = 6
LIBMINOR = 0

PRGNAME = stl_unit_test

SRC_CC = suite.cc test_suite.cc logger_stdio.cc

SRC_CPP = \
	msstring_test.cpp \
	stream_test.cpp

