#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct List {
    void *array;
    size_t stride;
    int current_size;
    int total_size;
};

void initList(struct List *list, size_t stride, void *data, int data_size, int total_size);
void cleanList(struct List *list);
void push(struct List *list, void *value);
void *pop(struct List *list);
void insert(struct List *list, void *value, int index);
void *getAtIndex(struct List *list, int index);
void setAtIndex(struct List *list, int index, void *data);
void swapElements(struct List *list, int index_1, int index_2);

#endif
