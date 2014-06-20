# vim: noet
#
# makefile for UnitsC++ demo and tests

# If you're running under Windows, set the e variable to 'exe' to
# cause suitable executables to be built.  Leave it empty for
# UNIX-style systems.

e =

# C++ compiler
cxx = g++

# Compiler options
options = -Wall 

all: test_units$e test_constants$e demo$e glacier$e

demo$e: demo.o area.o units.h
	${cxx} -o $@ ${options} demo.o area.o

test_units$e: test_units.o 
	${cxx} -o $@ ${options} test_units.o

test_constants$e: test_constants.o 
	${cxx} -o $@ ${options} test_constants.o

glacier$e: glacier.o 
	${cxx} -o $@ ${options} glacier.o

will_not_compile:
	${cxx} -DWILLNOTCOMPILE test_units.cpp && false

test_units.h: unitscpp.py test_units.cfg
	python unitscpp.py test_units.cfg >$@

test_constants.h: unitscpp.py 
	python unitscpp.py -s >test_constants.cfg
	python unitscpp.py test_constants.cfg >$@
	rm -f test_constants.cfg

units.h: unitscpp.py demo.cfg
	python unitscpp.py demo.cfg >$@

glacier.h: unitscpp.py glacier.cfg
	python unitscpp.py glacier.cfg >$@

clean:
	rm -f demo.o area.o test_units.o test_constants.o 
	rm -f test_units$e test_constants$e demo$e
	rm -f units.h test_constants.h test_units.h glacier.h 

demo.o: demo.cpp units.h
area.o: area.cpp units.h
test_units.o:  test_units.cpp test_units.h
test_constants.o:  test_constants.cpp test_constants.h
glacier.o:  glacier.cpp glacier.h

%.o: %.cpp
	${cxx} -c ${options} $<

