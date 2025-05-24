.PHONY: all

DSNAME=bit_array

SRC=src/$(DSNAME).c
INCLUDE=include/$(DSNAME).h
TEST=test/$(DSNAME)_test.c

CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g
RELEASE=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -03
TARGET= fooer.out

all: output

output: $(DSNAME).o $(DSNAME)_test.o
	$(CC)$(CFLAG) -o $@ $^

$(DSNAME).o: $(DSNAME).c
	$(CC)$(CFLAG) -c $(DSNAME).c
	
$(DSNAME)_test.o: $(DSNAME)_test.c
	$(CC)$(CFLAG) -c $(DSNAME)_test.c


release: $(SRC) $(TEST)
	$(CC)$(REALSE) -o bit/release/$(DSNAME) $^

debug: 
	make --debug=b
	
vlg: main
	valgrind --leak-check=yes --track-origins=yes ./a.out


.PHONY: clean
clean:
	rm *.o fooer.out
