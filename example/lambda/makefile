###############################################################################
##                                                                           ##
##  Makefile for demonstration for using the command line option parser      ##
##  for C++11.                                                               ##
##                                                                           ##
##  Usage of initializer-list with lambda-functions and function-pointers.   ##                                                                  ##                                                                           ##
##---------------------------------------------------------------------------##
## File:   ~/example/lambda/makefile                                         ##
## Author: Ulrich Becker                                                     ##
## Date:   31.12.2016                                                        ##
###############################################################################
BASEDIR = ../../src
SOURCES = cmd_opt_lambda.cpp $(BASEDIR)/parse_opts.cpp
EXE_NAME = e2

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
