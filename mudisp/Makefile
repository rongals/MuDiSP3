#
# MuDiSP3 Makefile: mudisp
#

SUBDIRS = engine

EXTRACPPFLAGS = -DMUDISP_VERBOSE  \
		-I$(MDSP3_SRC)/common \
                -I$(MDSP3_SRC)/common/randlib \
		-I$(MDSP3_SRC)/tnt \
		$(SUBDIRS:%=-I%)


sources = 	block.cpp \
		lcm.cpp \
		param.cpp \
		parlist.cpp \
		port.cpp 

install_include = engine/errors.h \
                  engine/block.h \
                  engine/lcm.h \
                  engine/mudisp.h \
                  engine/param.h \
                  engine/parlist.h \
                  engine/port.h

target_name = libmudisp


#######################################################################


include ../Makefile.lib

