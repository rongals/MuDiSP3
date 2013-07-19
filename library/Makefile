#
# MuDiSP3 Makefile: library
#


# add any other block library directory here

SUBDIRS = base

EXTRACPPFLAGS = -DMUDISP_VERBOSE \
		-I$(MDSP3_SRC)/common \
                -I$(MDSP3_SRC)/common/randlib \
		-I$(MDSP3_SRC)/tnt \
		-I$(MDSP3_SRC)/mudisp/engine \
		$(SUBDIRS:%=-I%)

# add each source file

sources = 	write.cpp \
		filter.cpp

# add header path

install_include = base/write.h \
		  base/filter.h

target_name = libblocks


#######################################################################


include ../Makefile.lib

