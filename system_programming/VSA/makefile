CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -Iinclude
RELEASE=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -Iinclude 
TARGET= a.out

.PHONY: all
all: vsa

vsa: vsa.o vsa_test.o
	$(CC) $(CFLAGS) -o a.out $^

vsa.o: src/vsa.c include/vsa.h
	$(CC) $(CFLAGS) -c src/vsa.c
	
vsa_test.o: test/vsa_test.c include/vsa.h 
	$(CC) $(CFLAGS) -c test/vsa_test.c

vsa_release: vsa.o vsa_test.o
	$(CC) $(RELEASE) -o bin/release/vsa $^
	
	
vsa_compzip:
	mkdir -p vsa_or_review
	mkdir -p vsa_or_review/test
	mkdir -p vsa_or_review/src
	mkdir -p vsa_or_review/include

	cp test/vsa_test.c vsa_or_review/test/
	cp src/vsa.c vsa_or_review/src/
	cp include/vsa.h vsa_or_review/include/
	cp include/utilities.h vsa_or_review/include/
	cp makefile vsa_or_review/

	tar -czvf vsa_or_review.tar.gz vsa_or_review

	rm -r vsa_or_review

.PHONY: clean
clean:
	rm *.o
