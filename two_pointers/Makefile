################################################################################
#                                                                              #
#                               Two Pointers                                   #
#                                                                              #
################################################################################

CC := g++
CFLAGS := -std=c++17 -Wall

# Automatically find all .cc files and create program names
PROGRAMS := $(basename $(wildcard *.cc)) 

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
