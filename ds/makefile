.PHONY: all

DSNAME=
LIB=linked_list

LIB_SRC=src/$(LIB).c
SRC=src/$(DSNAME).c
INCLUDE=include/$(DSNAME).h
INCLUDE_TWO=include/$(LIB).h
TEST=test/$(DSNAME)_test.c
VALGRIND=bin/debug/$(DSNAME)

CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -Iinclude
RELEASE=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -Iinclude
TARGET= a.out

all: dhcp

$(DSNAME): $(DSNAME).o $(DSNAME)_test.o
	$(CC) $(CFLAGS) -o $(DSNAME) $^

$(DSNAME).o: $(SRC) $(INCLUDE)
	$(CC) $(CFLAGS) -c $(SRC)
	
$(DSNAME)_test.o: $(TEST) $(INCLUDE) 
	$(CC) $(CFLAGS) -c $(TEST)


#release: $(SRC) $(TEST)
	$(CC) $(RELEASE) -o bin/release/$(DSNAME) $^




#############################################################
#						SortedList							#
#############################################################

sorted_list: sorted_list.o sorted_list_test.o dll.o
	$(CC) $(CFLAGS) -o a.out $^

sorted_list.o: src/sorted_list.c include/sorted_list.h include/dll.h
	$(CC) $(CFLAGS) -c src/sorted_list.c src/dll.c
	
sorted_list_test.o: test/sorted_list_test.c include/sorted_list.h 
	$(CC) $(CFLAGS) -c test/sorted_list_test.c src/dll.c

#use the dll.o target

sorted_list_release: src/sorted_list.c test/sorted_list_test.c src/dll.c
	$(CC) $(RELEASE) -o bin/release/sorted_list $^
	
	
sorted_list_compzip:
	mkdir -p sorted_list_or_review
	mkdir -p sorted_list_or_review/test
	mkdir -p sorted_list_or_review/src
	mkdir -p sorted_list_or_review/include

	cp test/sorted_list_test.c sorted_list_or_review/test/
	cp src/sorted_list.c sorted_list_or_review/src/
	cp src/dll.c sorted_list_or_review/src/
	cp include/sorted_list.h sorted_list_or_review/include/
	cp include/dll.h sorted_list_or_review/include/
	cp include/utilities.h sorted_list_or_review/include/
	cp makefile sorted_list_or_review/

	tar -czvf sorted_list_or_review.tar.gz sorted_list_or_review

	rm -r sorted_list_or_review
	
	
	
	
#############################################################
#							DLL								#
#############################################################

dll: dll.o dll_test.o
	$(CC) $(CFLAGS) -o a.out $^

dll.o: src/dll.c include/dll.h
	$(CC) $(CFLAGS) -c src/dll.c
	
dll_test.o: test/dll_test.c include/dll.h 
	$(CC) $(CFLAGS) -c test/dll_test.c

dll_release: dll.o dll_test.o
	$(CC) $(RELEASE) -o bin/release/dll $^
	
	
dll_compzip:
	mkdir -p dll_or_review
	mkdir -p dll_or_review/test
	mkdir -p dll_or_review/src
	mkdir -p dll_or_review/include

	cp test/dll_test.c dll_or_review/test/
	cp src/dll.c dll_or_review/src/
	cp include/dll.h dll_or_review/include/
	cp makefile dll_or_review/

	tar -czvf dll_or_review.tar.gz dll_or_review

	rm -r dll_or_review




#############################################################
#						CircularBuffer						#
#############################################################

c_buffer: c_buffer.o c_buffer_test.o
	$(CC) $(CFLAGS) -o a.out $^

c_buffer.o: src/c_buffer.c include/c_buffer.h
	$(CC) $(CFLAGS) -c src/c_buffer.c
	
c_buffer_test.o: test/c_buffer_test.c include/c_buffer.h 
	$(CC) $(CFLAGS) -c test/c_buffer_test.c

c_buffer_release: c_buffer.o c_buffer_test.o
	$(CC) $(RELEASE) -o bin/release/c_buffer $^
	
	
c_buffer_compzip:
	mkdir -p c_buffer_or_review
	mkdir -p c_buffer_or_review/test
	mkdir -p c_buffer_or_review/src
	mkdir -p c_buffer_or_review/include

	cp test/c_buffer_test.c c_buffer_or_review/test/
	cp src/c_buffer.c c_buffer_or_review/src/
	cp include/c_buffer.h c_buffer_or_review/include/
	cp makefile c_buffer_or_review/

	tar -czvf c_buffer_or_review.tar.gz c_buffer_or_review

	rm -r c_buffer_or_review
	
	
	
	
#############################################################
#					Priority Queue	    					#
#############################################################

pq: pq.o pq_test.o sorted_list.o dll.o
	$(CC) $(CFLAGS) -o a.out $^

pq.o: src/pq.c include/pq.h
	$(CC) $(CFLAGS) -c src/pq.c
	
pq_test.o: test/pq_test.c include/pq.h 
	$(CC) $(CFLAGS) -c test/pq_test.c

pq_release: pq.o pq_test.o sorted_list.o dll.o
	$(CC) $(RELEASE) -o bin/release/pq $^
	
	
pq_compzip:
	mkdir -p pq_or_review
	mkdir -p pq_or_review/test
	mkdir -p pq_or_review/src
	mkdir -p pq_or_review/include

	cp test/pq_test.c pq_or_review/test/
	cp src/pq.c pq_or_review/src/
	cp src/dll.c pq_or_review/src/
	cp src/sorted_list.c pq_or_review/src/
	cp include/pq.h pq_or_review/include/
	cp include/dll.h pq_or_review/include/
	cp include/sorted_list.h pq_or_review/include/
	cp include/utilities.h pq_or_review/include/
	cp makefile pq_or_review/

	tar -czvf pq_or_review.tar.gz pq_or_review

	rm -r pq_or_review
	
	
#############################################################
#							Sorts		  					#
#############################################################

sort: sort.o sort_test.o
	$(CC) $(CFLAGS) -o a.out $^

sort.o: src/sort.c include/sort.h
	$(CC) $(CFLAGS) -c src/sort.c
	
sort_test.o: test/sort_test.c include/sort.h 
	$(CC) $(CFLAGS) -c test/sort_test.c

sort_release: sort.o sort_test.o sorted_list.o dll.o
	$(CC) $(RELEASE) -o bin/release/sort $^
	
	
sort_compzip:
	mkdir -p sort_or_review
	mkdir -p sort_or_review/test
	mkdir -p sort_or_review/src
	mkdir -p sort_or_review/include

	cp test/sort_test.c sort_or_review/test/
	cp src/sort.c sort_or_review/src/
	cp include/sort.h sort_or_review/include/
	cp include/utilitiestwo.h sort_or_review/include/
	cp makefile sort_or_review/

	tar -czvf sort_or_review.tar.gz sort_or_review

	rm -r sort_or_review	
	
	
#############################################################
#						Recursion		  					#
#############################################################

recursion: recursion.o recursion_test.o stack.o
	$(CC) $(CFLAGS) -o a.out $^

recursion.o: src/recursion.c include/recursion.h
	$(CC) $(CFLAGS) -c src/recursion.c
	
recursion_test.o: test/recursion_test.c include/recursion.h 
	$(CC) $(CFLAGS) -c test/recursion_test.c

stack.o: src/stack.c include/stack.h
	$(CC) $(CFLAGS) -c src/stack.c

recursion_release: recursion.o recursion_test.o recursioned_list.o dll.o
	$(CC) $(RELEASE) -o bin/release/recursion $^
	
	
recursion_compzip:
	mkdir -p recursion_or_review
	mkdir -p recursion_or_review/test
	mkdir -p recursion_or_review/src
	mkdir -p recursion_or_review/include

	cp test/recursion_test.c recursion_or_review/test/
	cp src/recursion.c recursion_or_review/src/
	cp include/recursion.h recursion_or_review/include/
	cp include/utilitiestwo.h recursion_or_review/include/
	cp makefile recursion_or_review/

	tar -czvf recursion_or_review.tar.gz recursion_or_review

	rm -r recursion_or_review	
	
#############################################################
#					Binary Search Tree	  					#
#############################################################

bst: bst.o bst_test.o
	$(CC) $(CFLAGS) -o a.out $^

bst.o: src/bst.c include/bst.h
	$(CC) $(CFLAGS) -c src/bst.c
	
bst_test.o: test/bst_test.c include/bst.h 
	$(CC) $(CFLAGS) -c test/bst_test.c

bst_release: bst.o bst_test.o
	$(CC) $(RELEASE) -o bin/release/bst $^
	
	
bst_compzip:
	mkdir -p bst_or_review
	mkdir -p bst_or_review/test
	mkdir -p bst_or_review/src
	mkdir -p bst_or_review/include

	cp test/bst_test.c bst_or_review/test/
	cp src/bst.c bst_or_review/src/
	cp include/bst.h bst_or_review/include/
	cp include/utilitiestwo.h bst_or_review/include/
	cp makefile bst_or_review/

	tar -czvf bst_or_review.tar.gz bst_or_review

	rm -r bst_or_review	
	
	
	
#############################################################
#				Binary Search Tree	AVL  					#
#############################################################

avl: avl.o avl_test.o
	$(CC) $(CFLAGS) -o a.out $^

avl.o: src/avl.c include/avl.h
	$(CC) $(CFLAGS) -c src/avl.c
	
avl_test.o: test/avl_test.c include/avl.h 
	$(CC) $(CFLAGS) -c test/avl_test.c

avl_release: avl.o avl_test.o
	$(CC) $(RELEASE) -o bin/release/avl $^
	
	
avl_compzip:
	mkdir -p avl_or_review
	mkdir -p avl_or_review/test
	mkdir -p avl_or_review/src
	mkdir -p avl_or_review/include

	cp test/avl_test.c avl_or_review/test/
	cp src/avl.c avl_or_review/src/
	cp include/avl.h avl_or_review/include/
	cp include/utilitiestwo.h avl_or_review/include/
	cp makefile avl_or_review/

	tar -czvf avl_or_review.tar.gz avl_or_review

	rm -r avl_or_review	



#############################################################
#						Hash Table      					#
#############################################################

hash: hash.o hash_test.o dll.o
	$(CC) $(CFLAGS) -o a.out $^ -lm

hash.o: src/hash.c include/hash.h
	$(CC) $(CFLAGS) -c src/hash.c
	
hash_test.o: test/hash_test.c include/hash.h 
	$(CC) $(CFLAGS) -c test/hash_test.c

hash_release: hash.o hash_test.o
	$(CC) $(RELEASE) -o bin/release/hash $^
	
	
hash_compzip:
	mkdir -p hash_or_review
	mkdir -p hash_or_review/test
	mkdir -p hash_or_review/src
	mkdir -p hash_or_review/include

	cp test/hash_test.c hash_or_review/test/
	cp src/hash.c hash_or_review/src/
	cp include/hash.h hash_or_review/include/
	cp include/utilitiestwo.h hash_or_review/include/
	cp makefile hash_or_review/

	tar -czvf hash_or_review.tar.gz hash_or_review

	rm -r hash_or_review	



#############################################################
#						Heap Table      					#
#############################################################

heap: heap.o heap_test.o vector.o
	$(CC) $(CFLAGS) -o a.out $^ 

heap.o: src/heap.c include/heap.h
	$(CC) $(CFLAGS) -c src/heap.c
	
heap_test.o: test/heap_test.c include/heap.h 
	$(CC) $(CFLAGS) -c test/heap_test.c

vector.o: src/vector.c include/vector.h
	$(CC) $(RELEASE) -c src/vector.c

heap_release: heap.o heap_test.o
	$(CC) $(RELEASE) -o bin/release/heap $^
	
	
heap_compzip:
	mkdir -p heap_or_review
	mkdir -p heap_or_review/test
	mkdir -p heap_or_review/src
	mkdir -p heap_or_review/include

	cp test/heap_test.c heap_or_review/test/
	cp src/heap.c heap_or_review/src/
	cp include/heap.h heap_or_review/include/
	cp include/utilitiestwo.h heap_or_review/include/
	cp makefile heap_or_review/

	tar -czvf heap_or_review.tar.gz heap_or_review

	rm -r heap_or_review	


#############################################################
#					Priority Queue_Heap    					#
#############################################################

pq_heap: pq_heap.o pq_test.o heap.o vector.o
	$(CC) $(CFLAGS) -o a.out $^

pq_heap.o: src/pq_heap.c include/pq_heap.h
	$(CC) $(CFLAGS) -c src/pq_heap.c

pq_heap_release: pq_heap.o pq_test.o heap.o vector.o
	$(CC) $(RELEASE) -o bin/release/pq $^
	
	
pq_heap_compzip:
	mkdir -p pq_heap_or_review
	mkdir -p pq_heap_or_review/test
	mkdir -p pq_heap_or_review/src
	mkdir -p pq_heap_or_review/include

	cp test/pq_heap_test.c pq_heap_or_review/test/
	cp src/pq_heap.c pq_heap_or_review/src/
	cp src/dll.c pq_heap_or_review/src/
	cp src/sorted_list.c pq_heap_or_review/src/
	cp include/pq.h pq_heap_or_review/include/
	cp include/dll.h pq_heap_or_review/include/
	cp include/sorted_list.h pq_heap_or_review/include/
	cp include/utilities.h pq_heap_or_review/include/
	cp makefile pq_heap_or_review/

	tar -czvf pq_heap_or_review.tar.gz pq_heap_or_review

	rm -r pq_heap_or_review
	
	
	
#############################################################
#					Knight Algorithm	   					#
#############################################################

knight: knight.o knight_test.o pq_heap.o heap.o vector.o
	$(CC) $(CFLAGS) -o a.out $^

knight.o: src/knight.c include/knight.h
	$(CC) $(CFLAGS) -c src/knight.c

knight_test.o: test/knight_test.c include/knight.h
	$(CC) $(CFLAGS) -c test/knight_test.c

knight_release: knight.o knight_test.o
	$(CC) $(RELEASE) -o bin/release/knight $^
	
	
knight_compzip:
	mkdir -p knight_or_review
	mkdir -p knight_or_review/test
	mkdir -p knight_or_review/src
	mkdir -p knight_or_review/include

	cp test/knight_test.c knight_or_review/test/
	cp src/knight.c knight_or_review/src/
	cp include/knight.h knight_or_review/include/
	cp include/utilitiestwo.h knight_or_review/include/
	cp makefile knight_or_review/

	tar -czvf knight_or_review.tar.gz knight_or_review

	rm -r knight_or_review


#############################################################
#					Trie Data Structure	   					#
#############################################################

trie: trie.o trie_test.o
	$(CC) $(CFLAGS) -o a.out $^ -lm

trie.o: src/trie.c include/trie.h
	$(CC) $(CFLAGS) -c src/trie.c

trie_test.o: test/trie_test.c include/trie.h
	$(CC) $(CFLAGS) -c test/trie_test.c

trie_release: trie.o trie_test.o
	$(CC) $(RELEASE) -o bin/release/trie $^
	
	
trie_compzip:
	mkdir -p trie_or_review
	mkdir -p trie_or_review/test
	mkdir -p trie_or_review/src
	mkdir -p trie_or_review/include

	cp test/trie_test.c trie_or_review/test/
	cp src/trie.c trie_or_review/src/
	cp include/trie.h trie_or_review/include/
	cp include/utilitiestwo.h trie_or_review/include/
	cp makefile trie_or_review/

	tar -czvf trie_or_review.tar.gz trie_or_review

	rm -r trie_or_review


#############################################################
#							DHCP  		   					#
#############################################################

dhcp: dhcp.o dhcp_test.o trie.o
	$(CC) $(CFLAGS) -o a.out $^ -lm

dhcp.o: src/dhcp.c include/dhcp.h
	$(CC) $(CFLAGS) -c src/dhcp.c

dhcp_test.o: test/dhcp_test.c include/dhcp.h
	$(CC) $(CFLAGS) -c test/dhcp_test.c

dhcp_release: dhcp.o dhcp_test.o
	$(CC) $(RELEASE) -o bin/release/dhcp $^
	
	
dhcp_compzip:
	mkdir -p dhcp_or_review
	mkdir -p dhcp_or_review/test
	mkdir -p dhcp_or_review/src
	mkdir -p dhcp_or_review/include

	cp test/dhcp_test.c dhcp_or_review/test/
	cp src/dhcp.c dhcp_or_review/src/
	cp include/dhcp.h dhcp_or_review/include/
	cp include/utilitiestwo.h dhcp_or_review/include/
	cp makefile dhcp_or_review/

	tar -czvf dhcp_or_review.tar.gz dhcp_or_review

	rm -r dhcp_or_review
###########################################################




vlg: $(VALGRIND)
	valgrind --leak-check=yes --track-origins=yes ./$(DSNAME)



.PHONY: clean
clean:
	rm *.o $(DSNAME)
	
.PHONY: compzip
compzip:
	mkdir -p $(DSNAME)_or_review
	mkdir -p $(DSNAME)_or_review/test
	mkdir -p $(DSNAME)_or_review/src
	mkdir -p $(DSNAME)_or_review/include

	cp test/$(DSNAME)_test.c $(DSNAME)_or_review/test/
	cp src/$(DSNAME).c $(DSNAME)_or_review/src/
	cp include/$(DSNAME).h $(DSNAME)_or_review/include/
	cp makefile $(DSNAME)_or_review/

	tar -czvf $(DSNAME)_or_review.tar.gz $(DSNAME)_or_review

	rm -r $(DSNAME)_or_review

