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
        if(compare(getPtrToIndex(list, left_node), getPtrToIndex(list, node_index)) || compare(getPtrToIndex(list, right_node), getPtrToIndex(list, node_index))){
            if(compare(getPtrToIndex(list, left_node), getPtrToIndex(list, right_node))){
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
        if(compare(getPtrToIndex(list, left_node), getPtrToIndex(list, node_index))){
            swapElements(list, left_node, node_index);
            percolate_down(compare, list, left_node);
        }
    
    }
    else{
        return;
    }
}

/*
// User need to provide mem location for the value being removed
void *removeHeap(int(*compare)(const void *, const void *), struct List *list, void *return_val){
    memcpy(return_val, getAtIndex(list, 0), list->stride);
	swapElements(list, 0, list->current_size - 1);
    list->current_size--;
    percolate_down(compare, list, 0);
	return return_val;
}
*/

void percolate_up(int(*compare)(const void *, const void *), struct List *list, int node_index){
    int parent_index = (node_index - 1) / 2;
    if(parent_index < 0){
        return;
    }
    if(compare(getPtrToIndex(list, node_index), getPtrToIndex(list,parent_index))){
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


int stringCmpWrapper(const void *string1, const void *string2){
    return strcmp((const char *)string1, (const char *)string2) > 0 ? 1 : 0;
}

void removeHeap(int (*compare)(const void *, const void *), struct List *list, void *return_val)
{
	getValueAtIndex(list, 0, return_val);
	swapElements(list, 0, list->current_size - 1);
	list->current_size--;
	percolate_down(compare, list, 0);
	//printf("%s\n", (char *)return_val);
}

void removeHeapPointer(int (*compare)(const void *, const void *), struct List *list, void *return_val)
{
}
/*
	void *tmp = getPtrAtIndex(list, 0);
	//printf("rHP temp = %s\n", (char *)tmp);
	memcpy(return_val, &tmp, list->stride);
	printf("rHP return_val = %s\n", *(char**)return_val);
	swapElements(list, 0, list->current_size - 1);
	printf("rHP return_val = %s\n", *(char**)return_val);
	list->current_size--;
	percolate_down(compare, list, 0);
	printf("rHP return_val = %s\n", *(char**)return_val);
}*/

#define STR_TESTING
int main(){
    struct List list;
    #define heap_size 7
    const char *strs[heap_size] = {
        "zzzzzzzxyzasdlfjhaklsdghaljkshglakjhdfklajsdhflkajhsdfjklahdklfajhsdklfjh",
        "orca",
        "silva",
        "abc",
        "wario",
		"zzz",
        "aest"
    };
	uint64_t buf = 0xAAAAAAAA;
	uint64_t buf1 = 0xAAAAAAAA;
	uint64_t buf2 = 0xBBBBBBBB;
	uint64_t buf3 = 0xBBBBBBBB;

	const char *strs2[heap_size] = {
		"ccc",
		"ddd",
		"eee",
		"fff",
		"ggg",
		"hhh",
		"iii"
	};
	const uint64_t ints[heap_size] = {420, 6, 7, 8888, 14, 42, 9999};
	#ifdef STR_TESTING
    initList(&list, sizeof(char *), NULL, 0, 128);
    for(int i = 0; i < heap_size; ++i){
        push(&list, (void *)&strs[i]);
        push(&list, (void *)&strs2[i]);
    }
	heapify(stringCmpWrapper, &list);
    /*for(int i = 0; i < heap_size; ++i){
        printf("%s\n", (char *)pop(&list));
    }*/
    char *val;
    while(list.current_size > 0){
        removeHeap(stringCmpWrapper, &list, (void *)&val);
        printf("%s\n", val);
    }
    return 0;
	#else
	initList(&list, sizeof(uint64_t), NULL, 0, 128);
    for(int i = 0; i < heap_size; ++i){
        push(&list, (void *)&ints[i]);
    }
	heapify(isGreater, &list);
    int val;
    while(list.current_size > 0){
        removeHeap(isGreater, &list, (void *)&val);
        printf("%d\n", val);
    }
    return 0;
	#endif
}
