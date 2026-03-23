#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void percolate_down(int(*compare)(const void *, const void *), struct List *list, int node_index);
void heapify(int(*compare)(const void *, const void *), struct List *list);
int max(int a, int b);
int isGreater(const void *a, const void *b);
void removeHeap(int(*compare)(const void *, const void *), struct List *list, void *return_val);
void removeHeapPointer(int(*compare)(const void *, const void *), struct List *list, void *return_val);
void insertHeap(int(*compare)(const void *, const void *), struct List *list, void *value);

#endif
