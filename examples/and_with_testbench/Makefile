CXX=g++
comp:
	$(CXX) -I. -I$(SYSTEMC_HOME)/include -L. -L$(SYSTEMC_HOME)/lib-linux64 -o sim main.cpp  -lsystemc -lm
run:
	LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64 ./sim


wave:
	gtkwave and2.vcd &

all: comp run

# For Emacs flymake-mode
check-syntax:
	clang -fsyntax-only -Wall -Wextra -I$(SYSTEMC_HOME)/include $(CHK_SOURCES)
