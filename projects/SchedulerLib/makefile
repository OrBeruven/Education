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

all: pq


#############################################################
#						SortedList							#
#############################################################

sorted_list: sorted_list.o sorted_list_test.o dll.o
	$(CC) $(CFLAGS) -o a.out $^

sorted_list.o: src/sorted_list.c include/sorted_list.h include/dll.h
	$(CC) $(CFLAGS) -c -fpic src/sorted_list.c src/dll.c
	
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
	$(CC) $(CFLAGS) -c -fpic src/dll.c
	
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
	$(CC) $(CFLAGS) -c -fpic src/c_buffer.c
	
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
	$(CC) $(CFLAGS) -c -fpic src/pq.c
	
pq_test.o: test/pq_test.c include/pq.h 
	$(CC) $(CFLAGS) -c test/pq_test.c

pq_release: pq.o pq_test.o
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
#				Scheduler Project - UID	    				#
#############################################################

uid: uid.o uid_test.o pq.o sorted_list.o dll.o
	$(CC) $(CFLAGS) -o uid $^

uid.o: src/uid.c include/uid.h
	$(CC) $(CFLAGS) -c -fpic src/uid.c
	
uid_test.o: test/uid_test.c include/uid.h 
	$(CC) $(CFLAGS) -c test/uid_test.c
	
	
	
#############################################################
#				Scheduler Project - Task	    			#
#############################################################

task: task.o task_test.o uid.o pq.o sorted_list.o dll.o
	$(CC) $(CFLAGS) -o bin/release/task $^
	rm *o

task.o: src/task.c include/task.h
	$(CC) $(CFLAGS) -c -fpic src/task.c
	
task_test.o: test/task_test.c include/task.h 
	$(CC) $(CFLAGS) -c test/task_test.c
	
task_compzip:
	mkdir -p task_or_review
	mkdir -p task_or_review/test
	mkdir -p task_or_review/src
	mkdir -p task_or_review/include

	cp test/task_test.c task_or_review/test/
	cp test/uid_test.c task_or_review/test/
	cp src/task.c task_or_review/src/
	cp src/uid.c task_or_review/src/
	cp include/task.h task_or_review/include/
	cp include/uid.h task_or_review/include/
	cp include/utilities.h task_or_review/include/
	cp makefile task_or_review/

	tar -czvf task_or_review.tar.gz task_or_review

	rm -r task_or_review



#############################################################
#				Scheduler Project - Scheduler    			#
#############################################################

sched: sched.o sched_test.o task.o uid.o pq.o sorted_list.o dll.o
	$(CC) $(CFLAGS) -o bin/release/sched $^


sched.o: src/sched.c include/sched.h
	$(CC) $(CFLAGS) -c -fpic src/sched.c
	
sched_test.o: test/sched_test.c include/sched.h 
	$(CC) $(CFLAGS) -c test/sched_test.c
	
sched_compzip:
	mkdir -p sched_or_review
	mkdir -p sched_or_review/test
	mkdir -p sched_or_review/src
	mkdir -p sched_or_review/include

	cp test/sched_test.c sched_or_review/test/
	cp test/task_test.c sched_or_review/test/
	cp test/uid_test.c sched_or_review/test/
	
	cp src/sched.c sched_or_review/src/
	cp src/task.c sched_or_review/src/
	cp src/uid.c sched_or_review/src/
	cp src/pq.c sched_or_review/src/
	cp src/sorted_list.c sched_or_review/src/
	cp src/dll.c sched_or_review/src/
	
	
	cp include/sched.h sched_or_review/include/
	cp include/task.h sched_or_review/include/
	cp include/uid.h sched_or_review/include/
	cp include/sorted_list.h sched_or_review/include/
	cp include/pq.h sched_or_review/include/
	cp include/dll.h sched_or_review/include/
	
	cp include/utilities.h sched_or_review/include/
	cp makefile sched_or_review/

	tar -czvf sched_or_review.tar.gz sched_or_review

	rm -r sched_or_review

 
	

###########################################################

libsched_utils.so: sched.o task.o uid.o pq.o sorted_list.o dll.o
	$(CC) $(CFLAGS) -shared -o libsched_utils.so $^
	$(CC) $(CFLAGS) test/sched_test.c -Wl,-rpath=//home/beru/BeruEnv/or.beruven/projects/Scheduler
	

libuid_utils.so: uid.o
	$(CC) $(CFLAGS) -shared -o libuid_utils.so $^




vlg: $(VALGRIND)
	valgrind --leak-check=yes --track-origins=yes ./$(DSNAME)



.PHONY: clean
clean:
	rm *.o $(DSNAME)
	
.PHONY: clean_all
clean_all: clean
	rm *.out
	rm *.so
	
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

