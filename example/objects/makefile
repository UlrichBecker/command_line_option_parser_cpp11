###############################################################################
##                                                                           ##
##  Makefile for demonstration of the usage of class CLOP::OPTION_V of the   ##
##  command-line-option-parser for C++11                                     ##
##                                                                           ##
##  Overwriting of the callback function CLOP::OPTION_V::onGiven             ##
##  Overwriting of the callback function CLOP::PARSER::onArgument            ##
##                                                                           ##
##---------------------------------------------------------------------------##
## File:   ~/example/objects/makefile                                        ##
## Author: Ulrich Becker                                                     ##
## Date:   01.01.2017                                                        ##
###############################################################################
BASEDIR = ../../src
SOURCES = cmd_opt_objects.cpp $(BASEDIR)/parse_opts.cpp
EXE_NAME = e3

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
