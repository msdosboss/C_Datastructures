debug: src/list.c src/listHeap.c src/list.h src/listHeap.h
	gcc -g -o main src/list.c src/listHeap.c

all: obj/linkedList.o
	gcc -o main obj/linkedList.o

obj/linkedList.o: src/linkedList.c src/linkedList.h
	gcc -c -o obj/linkedList.o src/linkedList.c

obj/list.o: src/list.c
	gcc -c -o obj/list.o src/list.c

obj/listHeap.o: src/listHeap.c
	gcc -c -o obj/listHeap.o src/listHeap.c
