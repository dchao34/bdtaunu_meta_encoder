# Configurations
# --------------

# compiler
CXX ?= g++
CXXFLAGS = -Wall -std=c++11
CXXFLAGS += -fPIC

# Contents
# --------

BINARIES = code_bdtaunu

# Dependencies
# ------------

# meta data encoder
META_ENCODER_LIBNAME = -lMetaEncoder
META_ENCODER_INC_PATH = ../
META_ENCODER_LIB_PATH = ../lib
INCFLAGS += -I $(META_ENCODER_INC_PATH)
LDFLAGS += -L $(META_ENCODER_LIB_PATH) $(META_ENCODER_LIBNAME)

# cern root
INCFLAGS += $(shell root-config --cflags)
LDFLAGS += $(shell root-config --libs)

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
	rm -f *~ *.o $(BINARIES)
