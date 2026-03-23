#include "listHeap.h"

int max(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}


int isGreater(const void *a, const void *b){
    const int c = *(const int *)a;
    const int d = *(const int *)b;
    return c > d;
}


void heapify(int(*compare)(const void *, const void *), struct List *list){
    int current_node = list->current_size / 2 - 1;
    while(current_node >= 0){
        percolate_down(compare, list, current_node);
        --current_node;
    }

    return;
    
}

void percolate_down(int(*compare)(const void *, const void *), struct List *list, int node_index){
    int left_node = node_index * 2 + 1;
    int right_node = node_index * 2 + 2;
    if(right_node < list->current_size){
        if(compare(getAtIndex(list, left_node), getAtIndex(list, node_index)) || compare(getAtIndex(list, right_node), getAtIndex(list, node_index))){
            if(compare(getAtIndex(list, left_node), getAtIndex(list, right_node))){
                swapElements(list, left_node, node_index);
                percolate_down(compare, list, left_node);
            }
            else{
                swapElements(list, right_node, node_index);
                percolate_down(compare, list, right_node);
            }
        }
    
    }
    else if(left_node < list->current_size){
        if(compare(getAtIndex(list, left_node), getAtIndex(list, node_index))){
            swapElements(list, left_node, node_index);
            percolate_down(compare, list, left_node);
        }
    
    }
    else{
        return;
    }
}


void percolate_up(int(*compare)(const void *, const void *), struct List *list, int node_index){
    int parent_index = (node_index - 1) / 2;
    if(parent_index < 0){
        return;
    }
    if(compare(getAtIndex(list, node_index), getAtIndex(list,parent_index))){
        swapElements(list, node_index, parent_index);
        if(parent_index > 0){
            percolate_up(compare, list, parent_index);
        }
    }
}

void insertHeap(int(*compare)(const void *, const void *), struct List *list, void *value){
    push(list, value);
    if(list->current_size == 1){
        return;
    }
    percolate_up(compare, list, list->current_size - 1); 
}


// User need to provide mem location for the value being removed
void removeHeap(int(*compare)(const void *, const void *), struct List *list, void *return_val){
    memcpy(return_val, getAtIndex(list, 0), list->stride);
    swapElements(list, 0, list->current_size - 1);
    list->current_size--;
    percolate_down(compare, list, 0);
}

int stringCmpWrapper(const void *string1, const void *string2){
    return strcmp((const char *)string1, (const char *)string2) > 0 ? 1 : 0;
}


int main(){
    struct List list;
    #define heap_size 6
    const char *strs[heap_size] = {
        "abc",
        "xyz",
        "orca",
        "silva",
        "wario",
        "aest"
    
    };
    initList(&list, sizeof(char *), NULL, 0, 128);
    for(int i = 0; i < heap_size; ++i){
        printf("%s\n", strs[i]);
        push(&list, (void *)strs[i]);
    }
    heapify(stringCmpWrapper, &list);
    printf("orca\n");
    fflush(stdout);
    const char *val;
    while(list.current_size > 0){
        removeHeap(stringCmpWrapper, &list, (void *)&val);
        printf("%s\n", val);
    }
    return 0;
}
