#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//Singly linked list
struct SLL_Node {
	struct SLL_Node *next;
	void *data;
};

struct SLL {
	struct SLL_Node *head;
	struct SLL_Node *tail;
	size_t length;
	size_t stride;
};

#endif
