# Configurations
# --------------

# compiler
CXX ?= g++
CXXFLAGS = -Wall -std=c++11
CXXFLAGS += -fPIC

# Contents
# --------

BINARIES = code_bdtaunu test_DataCoder test_TableCache test_AssignmentCsvWriter

# Dependencies
# ------------

# meta data encoder
META_ENCODER_LIBNAME = -lMetaEncoder
META_ENCODER_INC_PATH = ../../
META_ENCODER_LIB_PATH = ../../lib
INCFLAGS += -I $(META_ENCODER_INC_PATH)
LDFLAGS += -L $(META_ENCODER_LIB_PATH) $(META_ENCODER_LIBNAME)

# cern root
INCFLAGS += $(shell root-config --cflags)
LDFLAGS += $(shell root-config --libs)

# custom cpp utilities
CUSTOM_CPP_UTIL_ROOT = /Users/dchao/bdtaunu/custom_cpp_utilities
INCFLAGS += -I$(CUSTOM_CPP_UTIL_ROOT)
LDFLAGS += -L$(CUSTOM_CPP_UTIL_ROOT)/lib \
					 -lCustomCPPUtils \
					 -Wl,-rpath,$(CUSTOM_CPP_UTIL_ROOT)/lib

# Build Rules
# -----------

.PHONY: all debug clean 

$@ : $@.cc
	$(CXX) $(CXXFLAGS) $< -o $%

all : CXXFLAGS += -O3
all : $(BINARIES)

debug : CXX += -DDEBUG -g
debug : $(BINARIES)

$(BINARIES) : % : %.cc
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) -Wl,-rpath,$(META_ENCODER_LIB_PATH) -o $@ $<

clean:
	rm -f *~ *.o *.out $(BINARIES)
