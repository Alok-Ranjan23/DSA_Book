################################################################################
#
#                                  HEAP
#
################################################################################

CC:=g++
CFLAGS:=-std=c++17 -Wall

all: heap_implementation heap_sort heap_sort2

heap_implementation: heap_implementation.cc
	$(CC) $(CFLAGS) -o $@ $<

heap_sort: heap_sort.cc
	$(CC) $(CFLAGS) -o $@ $<

heap_sort2: heap_sort2.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf heap_implementation heap_sort heap_sort2
