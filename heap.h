#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>

void percolate_down(int(*compare)(const void *, const void *), int *heap, int heap_size, int node_index);
void heapify(int(*compare)(const void *, const void *), int *heap, int heap_size);
int max(int a, int b);
int isGreater(const void *a, const void *b);
int removeHeap(int(*compare)(const void *, const void *), int *heap, int *heap_size);
void insertHeap(int(*compare)(const void *, const void *), int *heap, int *heap_size, int value);

#endif
