TARGETS=conv-fit phe_sat

ROOTFLAGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --libs)

CXXFLAGS  = -Wall -O2 $(ROOTFLAGS)
CXXLIBS   = $(ROOTLIBS)

all: $(TARGETS)

conv-fit: conv-fit.o
	 g++ -o $@ conv-fit.o $(CXXLIBS)

phe_sat: phe_sat.o
	g++ -o $@ phe_sat.o $(CXXLIBS)

.cc.o:
	g++ -c $(CXXFLAGS) $<

clean:
	rm -f phe_sat.o phe_sat
	rm -f conv-fit.o conv-fit
