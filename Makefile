CC = gcc
CFLAGS = -Wall -g

build:
	gcc -g -Wall queue.c list.c stack.c main.c -o tema2
run:
	valgrind ./tema2 in_file out_file
clean:
	rm tema2