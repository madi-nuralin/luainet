###########
# Makefile
###########

CC = gcc
CFLAGS = -Wall -fpic -shared -o

all:
	$(CC) $(CFLAGS) lib/linetlib.so -I/usr/include/lua5.3  src/linetlib.* src/_to.* src/_atoip.*

clean:
	rm lib/*.so
