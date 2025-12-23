################################################################################
#                                                                              #
#                            String Manipulation                               #
#                                                                              #
################################################################################

CC := g++
CFLAGS := -std=c++17 -Wall

PROGRAMS := string_join string_matching string_split

all: $(PROGRAMS)

%: %.cc
	$(CC) $(CFLAGS) -o $@ $<

.PHONY:clean
clean:
	rm -rf $(PROGRAMS) 
