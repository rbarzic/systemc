CXX=g++
comp:
	$(CXX) -I. -I$(SYSTEMC_HOME)/include -L. -L$(SYSTEMC_HOME)/lib-linux64 -o sim first_counter.cpp first_counter_tb.cpp  -lsystemc -lm
run:
	LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64 ./sim


wave:
	gtkwave counter.vcd &

all: comp run

check-syntax:
	clang -fsyntax-only -Wall -Wextra -I$(SYSTEMC_HOME)/include $(CHK_SOURCES)
