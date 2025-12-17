################################################################################
#
#                                  HEAP
#
################################################################################

CC := g++
CFLAGS := -std=c++17 -Wall

PROGRAMS := heap_implementation heap_sort heap_sort2

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
