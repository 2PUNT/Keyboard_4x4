#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := 

# header files in this project
HEADERS := IKeyboardListener.hpp Keyboard_4x4.hpp

# other places to look for files for this project
SEARCH  := 

# set REATIVE to the next higher directory 
# and defer to the Makefile.native there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
