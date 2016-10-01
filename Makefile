LIB=lib

CC=gcc
CFLAGS=-std=c89 -g -Wall -Wextra -Werror -Wpedantic

SHAREDFLAGS = -shared
SHAREDEXT = so
SHAREDFLAGS += -Wl,-soname,$(SO_NAME)

SO_NAME=$(LIB).$(SHAREDEXT)

default: main

test-$(LIB): $(LIB).o test-$(LIB).o
	$(CC) $(CFLAGS) $(OBJS) -o test-$(LIB) test-$(LIB).o $(LIB).o

$(LIB).o: $(LIB).c
	$(CC) $(CFLAGS) -c -fPIC $(LIB).c -o $(LIB).o

test-$(LIB).o: test-$(LIB).c
	$(CC) $(CFLAGS) -c -fPIC test-$(LIB).c -o test-$(LIB).o

$(SO_NAME): $(LIB).o
	$(CC) $(CFLAGS) -fPIC $(SHAREDFLAGS) -o $(SO_NAME).1 $(LIB).o

main: $(SO_NAME) test-$(LIB)
	$(CC) $(CFLAGS) -o main main.c

test: test-$(LIB)
	./test-$(LIB)

check: main
	echo sudo chown root:root ./main
	echo sudo chmod 6777 ./main
	ls -l main
	./main
	LD_PRELOAD=./$(SO_NAME).1 ./main

clean:
	rm -f *.o test-$(LIB) $(LIB).$(SHAREDEXT).1 main *~
