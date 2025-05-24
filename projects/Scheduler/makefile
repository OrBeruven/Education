TARGET = a.out
TARGET_LIB = libsched_utils.so
CC = gcc
SOURCE = ./src/sched.c ./src/uid.c ./src/task.c ./src/pq_heap.c ./src/heap.c ./src/vector.c
TEST = ./test/sched_test.c
CPPFLAGS = -I./include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -fPIC
LDFLAGS =-L. -Wl,-rpath=. -lsched_utils
OBJS =  uid.o task.o heap.o vector.o pq_heap.o sched.o 

all: $(TARGET_LIB) $(TARGET)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -shared -o $@ $^
	
$(TARGET): $(TEST) $(TARGET_LIB)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $< $(LDFLAGS)

$(OBJS): 
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE) 
	
debug: CFLAGS += -g
debug: $(TARGET_LIB) $(TARGET)

release: CFLAGS += -O3
release: $(TARGET_LIB) $(TARGET)

.PHONY: update
update:
	touch $(SOURCE) $(TEST)
	
.PHONY:  clean
clean:
	rm $(OBJS) $(TARGET_LIB) $(TARGET)
