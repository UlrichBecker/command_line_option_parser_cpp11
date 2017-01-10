###############################################################################
##                                                                           ##
##  Makefile for test-program for using the command line option parser       ##
##  for C++11.                                                               ##
##                                                                           ##
## Demonstration for using initializer-lists with callback lambda-functions  ##
## and the overwritten callback function CLOP::OPTION_V::onGiven.            ##
##                                                                           ##
##---------------------------------------------------------------------------##
## File:   ~/example/test/makefile                                           ##
## Author: Ulrich Becker                                                     ##
## Date:   17.12.2016                                                        ##
###############################################################################
BASEDIR = ../../src
SOURCES = cmd_opt_test.cpp $(BASEDIR)/parse_opts.cpp
EXE_NAME = e1

VPATH= $(BASEDIR)
INCDIR = $(BASEDIR)
CXXFLAGS = -g -O0 -std=c++11

CXX ?= g++
CXXFLAGS += $(addprefix -I,$(INCDIR))

OBJDIR=.obj
LIBS = stdc++

OBJ = $(addprefix $(OBJDIR)/,$(addsuffix .opp,$(notdir $(basename $(SOURCES)))))

.PHONY: all 
all: $(EXE_NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.opp: %.cpp $(SOURCES) $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(EXE_NAME): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(addfrefix "-l",$(LIBS))

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.opp $(EXE_NAME) core
	rmdir $(OBJDIR)
	
#=================================== EOF ======================================
