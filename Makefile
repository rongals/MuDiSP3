#
# MuDiSP3 Makefile
# $Id: Makefile,v 1.2 2002/11/20 17:01:08 ronga Exp $
#
#################################################
#################################################

#
# Here is the source main path
#
MDSP3_SRC=/home/ronga/MuDiSP3/mudisp3

#
# The installation base dir
#
INSTALLDIR=/usr/local/mudisp3


#
# Here is the compiler path
#
#
CC = g++

#################################################
#################################################
#########   nothing else   ######################
#################################################

CXX = $(CC)

TNTDIR=$(MDSP3_SRC)/tnt

DEBUGFLAGS = -g
RELEASEFLAGS = -O3

CPPFLAGS = -I$(MDSP3_SRC)/include -Wall

SUBDIRS = mudisp \
	  common \
	  library \
	  tools \
	  newran03


export CC CXX MDSP3_SRC INSTALLDIR DEBUGFLAGS RELEASEFLAGS CPPFLAGS

default: build


#
# The Targets
#

.PHONY: clean all default distclean


build:
	for D in $(SUBDIRS) ; do \
	  $(MAKE) -C $$D ; \
	done


clean:
	for D in $(SUBDIRS) ; do \
	  $(MAKE) -C $$D clean ; \
	done ;


distclean:
	for D in $(SUBDIRS) ; do \
	  $(MAKE) -C $$D distclean ; \
	done ; \
	rm -f *~


tags:
	etags `find . -name \*.h -or -name \*.cpp`


install:
	for D in $(SUBDIRS) ; do	\
	  $(MAKE) -C $$D install ; \
	done ; \
	mkdir -p $(INSTALLDIR)/lib ; \
	mkdir -p $(INSTALLDIR)/doc ; \
	mkdir -p $(INSTALLDIR)/demoproject ; \
	mkdir -p $(INSTALLDIR)/tools ; \
	cp $(MDSP3_SRC)/README $(INSTALLDIR) ; \
	cp $(MDSP3_SRC)/COPYING $(INSTALLDIR) ; \
	cp $(MDSP3_SRC)/CHANGE $(INSTALLDIR) ; \
	cp $(MDSP3_SRC)/CONTACT $(INSTALLDIR) ; \
	cp $(MDSP3_SRC)/Makefile.sim $(INSTALLDIR)/lib ; \
	cp -r $(TNTDIR) $(INSTALLDIR)/include ; \
	cp -r $(MDSP3_SRC)/demoproject $(INSTALLDIR) ; \
	cp -r $(MDSP3_SRC)/doc $(INSTALLDIR) ;

