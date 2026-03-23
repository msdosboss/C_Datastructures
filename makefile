debug: src/list.c src/listHeap.c src/list.h src/listHeap.h
	gcc -g -o main src/list.c src/listHeap.c

all: obj/list.o obj/listHeap.o
	gcc -o main obj/list.o obj/listHeap.o

obj/list.o: src/list.c
	gcc -c -o obj/list.o src/list.c

obj/listHeap.o: src/listHeap.c
	gcc -c -o obj/listHeap.o src/listHeap.c
