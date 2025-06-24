CC = gcc
CFLAGS = -Wall -g -pthread

all: buffer_simples buffer_simples_v1 buffer_simples_v2 buffer_simples_v3

buffer_simples: buffer_simples.c
	$(CC) $(CFLAGS) buffer_simples.c -o buffer_simples

buffer_simples_v1: buffer_simples_v1.c
	$(CC) $(CFLAGS) buffer_simples_v1.c -o buffer_simples_v1

buffer_simples_v2: buffer_simples_v2.c
	$(CC) $(CFLAGS) buffer_simples_v2.c -o buffer_simples_v2

buffer_simples_v3: buffer_simples_v3.c
	$(CC) $(CFLAGS) buffer_simples_v3.c -o buffer_simples_v3

clean:
	rm -f buffer_simples buffer_simples_v1 buffer_simples_v2 buffer_simples_v3