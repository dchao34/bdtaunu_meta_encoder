CXX ?= g++
CXXFLAGS = -Wall -std=c++11 
ROOTINCFLAGS = $(shell root-config --cflags)
ROOTLDFLAGS = $(shell root-config --libs)
INCFLAGS = $(shell root-config --cflags) -Icustom_cpp_utilities
LDFLAGS = $(shell root-config --libs) -Lcustom_cpp_utilities/lib -lCustomCPPUtils 

SHARED = -Wl,-rpath,custom_cpp_utilities/lib

BINARIES = code_bdtaunu

all : $(BINARIES)

% : %.cc
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(SHARED) $(LDFLAGS) $< -o $@

clean: 
	@rm -f *~ *.o $(BINARIES)
