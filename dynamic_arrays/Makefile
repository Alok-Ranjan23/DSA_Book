################################################################################
#                                                                              #
#                             Dynamic Arrays                                   #
#                                                                              #
################################################################################

CC := g++
CFLAGS := -std=c++17 -Wall

PROGRAMS := dynamic_arrays1 dynamic_arrays2

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
