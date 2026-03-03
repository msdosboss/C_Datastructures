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
    list->stride = stride;
    list->current_size = 0;
    list->total_size = total_size;
}

void append(struct List *list, void *value){
    if(list->current_size == list->total_size){
        // Will replace return call with resize function
        return;
    }

}
