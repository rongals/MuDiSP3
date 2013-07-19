#
# INeSiS Makefile
#
##########################################
#  C++  COMPILER
CC = g++ -DTNT_NO_BOUNDS_CHECK -DUSERS=2

##########################################
# INeSis SIMULATOR PATH
MDSP3_SRC=/usr/local/mudisp3

##########################################
# USER PROJECT NAME (es. iir) 
USERPROJECT = cdma_verdu_awgn

##########################################
# USER SOURCES DIR (es. SRC SRC1 SRC2) 
USERDIRS = src src_blind 


##########################################
# USER SOURCES FILES
USERSRC = uservec.cpp \
	  bitsrc.cpp \
	  bitber.cpp \
	  awgn.cpp \
	  pulse.cpp \
	  corrblind.cpp 


##########################################
# DEBUG
DEBUG = true;

##########################################
# SIMULATOR LIBS
#
# add the following for LAPACK Support
# -lg2c \
# -llapack \
# -lblas \
# 
#
LIBS = 


##########################################
##########################################
# DO NOT MODIFY BELOW
#

USERSRC += system.cpp	\
	main.cpp

include $(MDSP3_SRC)/lib/Makefile.sim

##########################################
##########################################
# DEMO Targets 
#
demosim:
	rm -f ./results/*.dat 
	./launcher ./cdma_verdu_awgn params/cdma_blind_awgn_63c2u_00*
	./launcher ./cdma_verdu_awgn params/cdma_mf_awgn_63c2u_00*

demoplot:
	analyzer/2ublind.gnu

democlean: distclean
	rm -f cdma_verdu_awgn
