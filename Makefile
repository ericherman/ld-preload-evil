LIB=lib

CC=gcc
CFLAGS=-std=c89 -g -Wall -Wextra -Werror -Wpedantic

SHAREDFLAGS = -shared
SHAREDEXT = so
SHAREDFLAGS += -Wl,-soname,$(SO_NAME)

SO_NAME=$(LIB).$(SHAREDEXT)
SO_VER=1
SO_PATCH=0

default: main

$(LIB).o: $(LIB).c
	$(CC) $(CFLAGS) -c -fPIC \
		-o $(LIB).o $(LIB).c

test-$(LIB).o: test-$(LIB).c
	$(CC) $(CFLAGS) -c -fPIC \
		-o test-$(LIB).o test-$(LIB).c

$(SO_NAME): $(LIB).o
	$(CC) $(CFLAGS) -fPIC \
		$(SHAREDFLAGS) \
		-o $(SO_NAME).$(SO_VER).$(SO_PATCH) $(LIB).o
	ln -sf ./$(SO_NAME).$(SO_VER).$(SO_PATCH) ./$(SO_NAME).$(SO_VER)
	ln -sf ./$(SO_NAME).$(SO_VER).$(SO_PATCH) ./$(SO_NAME)

test-$(LIB): $(LIB).o test-$(LIB).o
	$(CC) $(CFLAGS) \
		-o test-$(LIB) test-$(LIB).o $(LIB).o

main: $(SO_NAME) test-$(LIB)
	$(CC) $(CFLAGS) \
		-o main main.c

test: test-$(LIB)
	./test-$(LIB)

check: main
	# sudo chown root:root ./main && sudo chmod 06777 ./main && ls -l main
	./main
	LD_PRELOAD=$(PWD)/$(SO_NAME).$(SO_VER).$(SO_PATCH) ./main

clean:
	# git clean -dxf
	rm -f *.o test-$(LIB) $(LIB).$(SHAREDEXT) $(LIB).$(SHAREDEXT).* main *~
