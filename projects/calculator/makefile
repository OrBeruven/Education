.PHONY: all

CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -Iinclude -I../../ds/include 
RELEASE=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -Iinclude
TARGET= a.out

all: calc

calc: calc.o calc_test.o stack.o
	$(CC) $(CFLAGS) -o a.out $^ -lm

calc.o: src/calc.c include/calc.h
	$(CC) $(CFLAGS) -c src/calc.c
	
calc_test.o: test/calc_test.c include/calc.h 
	$(CC) $(CFLAGS) -c test/calc_test.c

stack.o: ../../ds/src/stack.c ../../ds/include/stack.h
	$(CC) $(CFLAGS) -c ../../ds/src/stack.c

calc_release: calc.o calc_test.o
	$(CC) $(RELEASE) -o bin/release/calc $^
	
	
calc_compzip:
	mkdir -p calc_or_review
	mkdir -p calc_or_review/test
	mkdir -p calc_or_review/src
	mkdir -p calc_or_review/include

	cp test/calc_test.c calc_or_review/test/
	cp src/calc.c calc_or_review/src/
	cp include/calc.h calc_or_review/include/
	cp makefile calc_or_review/

	tar -czvf calc_or_review.tar.gz calc_or_review

	rm -r calc_or_review	
