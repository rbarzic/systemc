CXX=g++
CXX_OPTS?=-std=c++11
comp:
	$(CXX) $(CXX_OPTS) -I. -I$(SYSTEMC_HOME)/include -L. -L$(SYSTEMC_HOME)/lib-linux64 -o sim main.cpp  -lsystemc -lm
run:
	LD_LIBRARY_PATH=$(SYSTEMC_HOME)/lib-linux64 ./sim


wave:
	gtkwave muller2.vcd &

all: comp run

# For Emacs flymake-mode
check-syntax:
	clang -fsyntax-only -Wall -Wextra -I$(SYSTEMC_HOME)/include $(CHK_SOURCES)
# For Emacs Irony mode (and company-mode/flycheck-irony) support
# run the Makefile as follow :
# make comp CXX='cc_args.py g++'
# to generate the local .clang_complete file
