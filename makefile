debug: list.c listHeap.c list.h listHeap.h
	gcc -g -o main list.c listHeap.c

all: list.o listHeap.o
	gcc -o main list.o listHeap.o

list.o: list.c
	gcc -c -o list.o list.c

listHeap.o: listHeap.c
	gcc -c -o listHeap.o listHeap.c
