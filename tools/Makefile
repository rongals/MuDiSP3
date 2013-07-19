##########################################
#######  OK I take care of the rest ######
##########################################
comma:= ,
empty:=
space:= $(empty) $(empty)


all: param_exploder param_exploder_multi


#
# The Targets
#

.PHONY: clean distclean


param_exploder : param_exploder.o
	$(CXX) $(CFLAGS) -o param_exploder param_exploder.o

param_exploder_multi : param_exploder_multi.o
	$(CXX) $(CFLAGS) -o param_exploder_multi param_exploder_multi.o

clean:
	rm -f *.o *.d

distclean:
	rm -f *.o *.d *~ param_exploder param_exploder_multi

print:
	@echo vpath = $(VPATH)

install:
	mkdir -p $(INSTALLDIR)/tools ; \
	cp param_exploder param_exploder_multi changer $(INSTALLDIR)/tools ;


#
# The rules ...
#

%.o : %.cpp
ifdef DEBUG
	$(CXX) $(DEBUGFLAGS) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
else
	$(CXX) $(RELEASEFLAGS) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
endif

%.d : %.cpp
	$(CXX) -MM -c $(CFLAGS) $(CPPFLAGS) $< > $@
