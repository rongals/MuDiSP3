#
# MuDiSP Makefile: common
#


EXTRACPPFLAGS = -I$(MDSP3_SRC)/common \
                -I$(MDSP3_SRC)/common/randlib 

sources = randlib.cpp \
	  rndgen.cpp \
	  com.cpp \
	  linpack.cpp

install_include = rndgen.h \
                  randlib/randlib.h

target_name = libinesis

SUBDIRS = randlib


#######################################################################

include ../Makefile.lib

