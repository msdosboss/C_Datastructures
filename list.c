#include <stdlib.h>
#include <stdio.h>

struct List {
    void *array;
    size_t stride;
    int current_size;
    int total_size;
};

void initList(struct List *list, size_t stride, int total_size){
    list->array = malloc(stride * total_size);


}
