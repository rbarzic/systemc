CXX=g++
CXX_OPTS?=-std=c++11

INC= -I. -I$(SYSTEMC_HOME)/include -I$(SYSTEMC_AMS_HOME)/include
LIBDIR = -L. -L$(SYSTEMC_HOME)/lib-linux64 -L$(SYSTEMC_AMS_HOME)/lib-linux64
LIBS= -lsystemc -lsystemc-ams -lpthread

LD_STUFF= LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64:$(SYSTEMC_AMS_HOME)/lib-linux64:

SOURCES = tb.cpp


comp:
	$(CXX) $(CXX_OPTS) $(INC) $(LIBDIR)  -o sim  $(SOURCES) $(LIBS)
run:
	$(LD_STUFF) ./sim


wave:
	gtkwave gtkwave.gtkw   &

all: comp run

check-syntax:
	clang -fsyntax-only -Wall -Wextra $(INC)  $(CHK_SOURCES)
