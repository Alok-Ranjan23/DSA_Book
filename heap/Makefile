################################################################################
#                                                                              #
#                                  HEAP                                        #
#                                                                              #
################################################################################

CC := g++
CFLAGS := -std=c++17 -Wall

PROGRAMS := heap_implementation heap_sort heap_sort2 k_most_played top_songs_class top_songs_class_with_updates

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
