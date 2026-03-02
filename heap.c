#include "heap.h"

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


void heapify(int(*compare)(const void *, const void *), int *heap, int heap_size){
    int current_node = heap_size / 2 - 1;
    while(current_node >= 0){
        percolate_down(compare, heap, heap_size, current_node);
        --current_node;
    }

    return;
    
}

void percolate_down(int(*compare)(const void *, const void *), int *heap, int heap_size, int node_index){
    int left_node = node_index * 2 + 1;
    int right_node = node_index * 2 + 2;
    if(right_node < heap_size){
        if(compare((const void *)&heap[left_node], (const void *)&heap[node_index]) || compare((const void *)&heap[right_node], (const void *)&heap[node_index])){
            if(compare((const void *)&heap[left_node], (const void *)&heap[right_node])){
                int tmp = heap[left_node];
                heap[left_node] = heap[node_index];
                heap[node_index] = tmp;
                percolate_down(compare, heap, heap_size, left_node);
            }
            else{
                int tmp = heap[right_node];
                heap[right_node] = heap[node_index];
                heap[node_index] = tmp;
                percolate_down(compare, heap, heap_size, right_node);
            }
        }
    
    }
    else if(left_node < heap_size){
        if(compare((const void *)&heap[left_node], (const void *)&heap[node_index])){
            int tmp = heap[left_node];
            heap[left_node] = heap[node_index];
            heap[node_index] = tmp;
            percolate_down(compare, heap, heap_size, left_node);
        }
    
    }
    else{
        return;
    }
}


void percolate_up(int(*compare)(const void *, const void *), int *heap, int heap_size, int node_index){
    int parent_index = (node_index - 1) / 2;
    if(parent_index < 0){
        return;
    }
    if(compare((const void *)&heap[node_index], (const void *)&heap[parent_index])){
        int tmp = heap[node_index];
        heap[node_index] = heap[parent_index];
        heap[parent_index] = tmp;
        if(parent_index > 0){
            percolate_up(compare, heap, heap_size, parent_index);
        }
    }
}

void insertHeap(int(*compare)(const void *, const void *), int *heap, int *heap_size, int value){
    heap[*heap_size] = value;
    (*heap_size)++;
    if(*heap_size == 1){
        return;
    }
    percolate_up(compare, heap, *heap_size, *heap_size - 1); 
}


int removeHeap(int(*compare)(const void *, const void *), int *heap, int *heap_size){
    int return_val = heap[0];
    (*heap_size)--;
    heap[0] = heap[*heap_size];
    percolate_down(compare, heap, *heap_size, 0);
    return return_val;
}


int main(){
    int numbers[1024];
    /*int heap_size = 0;
    for(int i = 0; i < 10; ++i){
        //insertHeap(isGreater, numbers, &heap_size, i);
    }*/
    int heap_size = 10;
    for(int i = 0; i < heap_size; ++i){
        numbers[i] = i;
    }
    heapify(isGreater, numbers, heap_size);
    /*int numbers[] = {3,1,5,0,4,2,6};
    heapify(isGreater, numbers, 7);
    percolate_down(isGreater, numbers, 7, 0);*/
    while(heap_size > 0){
        printf("%d\n",removeHeap(isGreater, numbers, &heap_size));
    }
    return 0;
}
