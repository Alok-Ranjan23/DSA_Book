################################################################################
#
#                                 SORTING
#
################################################################################

CC:=g++
CFLAGS:= -Wall -std=c++20

# Automatically find all .cc files and create program names
PROGRAMS := $(basename $(wildcard *.cc))

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
