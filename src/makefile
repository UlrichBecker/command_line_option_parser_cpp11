###############################################################################
##                                                                           ##
##    Optional makefile to crating a shared-library: libParseOptsCpp11.so    ##
##                                                                           ##
##---------------------------------------------------------------------------##
## File:      command_line_option_parser_cpp11/src/makefile                  ##
## Author:    Ulrich Becker                                                  ##
## Date:      13.06.2018                                                     ##
## Rervision:                                                                ##
###############################################################################
LIBNAME      ?= ParseOptsCpp11
LIB_VERSION  ?= 1
LIB_REVISION ?= 0

LIB_DIR     ?= /usr/lib64/
HEADDER_DIR ?= /usr/include/

SOURCE_NAME := parse_opts

CXX          ?= g++
CURRENT_DIR = $(PWD)

LIB_FILENAME = lib$(LIBNAME).so

.PHONY: all
all: $(LIB_FILENAME).$(LIB_VERSION).$(LIB_REVISION)

$(SOURCE_NAME).opp: $(SOURCE_NAME).cpp
	$(CXX) -Wall -fPIC -std=c++11 -c -I. $(CXXFLAGS) -o $@ $<

$(LIB_FILENAME).$(LIB_VERSION).$(LIB_REVISION): $(SOURCE_NAME).opp
	$(CXX) -shared -Wl,-soname,$(LIB_FILENAME).$(LIB_VERSION) -o $@  $<

.PHONY: install
install: all
	cp $(SOURCE_NAME).hpp $(HEADDER_DIR)
	cp $(LIB_FILENAME).$(LIB_VERSION).$(LIB_REVISION) $(LIB_DIR)
	cd $(LIB_DIR); \
	ln -sf $(LIB_FILENAME).$(LIB_VERSION).$(LIB_REVISION) $(LIB_FILENAME).$(LIB_VERSION); \
	ln -sf $(LIB_FILENAME).$(LIB_VERSION) $(LIB_FILENAME); \
	cd $(CURRENT_DIR)

.PHONY: uninstall
uninstall:
	rm $(LIB_DIR)$(LIB_FILENAME)*
	rm $(HEADDER_DIR)$(SOURCE_NAME).hpp

.PHONY: clean
clean:
	rm *.opp
	rm $(LIB_FILENAME).$(LIB_VERSION).$(LIB_REVISION)

#=================================== EOF ======================================
