CXX ?= g++
CXXFLAGS = -Wall -std=c++11 

# boost
#INCFLAGS += -I$(BOOST_ROOT)

# custom cpp utilities
CUSTOM_CPP_UTIL_ROOT = /Users/dchao/bdtaunu/custom_cpp_utilities
INCFLAGS += -I$(CUSTOM_CPP_UTIL_ROOT)
LDFLAGS += -L$(CUSTOM_CPP_UTIL_ROOT)/lib \
					 -lCustomCPPUtils \
					 -Wl,-rpath,$(CUSTOM_CPP_UTIL_ROOT)/lib

# cern root
INCFLAGS += $(shell root-config --cflags)
LDFLAGS += $(shell root-config --libs)

BINARIES = code_bdtaunu
OBJECTS = RootReader.o RandomNumbers.o DataCoder.o TableCache.o AssignmentCsvWriter.o

all : $(BINARIES)

$(BINARIES) : % : %.cc $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) $^ -o $@

$(OBJECTS) : %.o : %.cc %.h
	  $(CXX) $(CXXFLAGS) $(INCFLAGS) -c $< -o $@

#% : %.cc
#	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(SHARED) $(LDFLAGS) $< -o $@

clean: 
	@rm -f *~ $(BINARIES) $(OBJECTS)
