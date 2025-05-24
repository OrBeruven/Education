CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -Iinclude
RELEASE=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -Iinclude
TARGET= a.out

.PHONY: all
all: fsa

fsa: fsa.o fsa_test.o
	$(CC) $(CFLAGS) -o a.out $^

fsa.o: src/fsa.c include/fsa.h
	$(CC) $(CFLAGS) -c src/fsa.c
	
fsa_test.o: test/fsa_test.c include/fsa.h 
	$(CC) $(CFLAGS) -c test/fsa_test.c

fsa_release: fsa.o fsa_test.o
	$(CC) $(RELEASE) -o bin/release/fsa $^
	
	
fsa_compzip:
	mkdir -p fsa_or_review
	mkdir -p fsa_or_review/test
	mkdir -p fsa_or_review/src
	mkdir -p fsa_or_review/include

	cp test/fsa_test.c fsa_or_review/test/
	cp src/fsa.c fsa_or_review/src/
	cp include/fsa.h fsa_or_review/include/
	cp include/utilities.h fsa_or_review/include/
	cp makefile fsa_or_review/

	tar -czvf fsa_or_review.tar.gz fsa_or_review

	rm -r fsa_or_review

.PHONY: clean
clean:
	rm *.o
