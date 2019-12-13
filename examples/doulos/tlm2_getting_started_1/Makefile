CXX=g++
CXX_OPTS?=-std=c++11

SRC= tlm2_getting_started_1.cpp
comp:
	$(CXX) $(CXX_OPTS) -I. -I$(SYSTEMC_HOME)/include -L. -L$(SYSTEMC_HOME)/lib-linux64 -o sim $(SRC)  -lsystemc -lm
run:
	LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64 ./sim


wave:
	gtkwave counter.vcd &

all: comp run

check-syntax:
	clang -fsyntax-only -Wall -Wextra -I$(SYSTEMC_HOME)/include $(CHK_SOURCES)
