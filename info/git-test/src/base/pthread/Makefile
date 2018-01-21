CC=gcc
CFLAGS=-g -Wall -lpthread

all: create_join mutex_lock 

create_join: create_join.o
	$(CC) $(CFLAGS) $^ -o $@
mutex_lock: mutex_lock.o
	$(CC) $(CFLAGS) $^ -o $@
	
	
%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f *.o create_join mutex_lock