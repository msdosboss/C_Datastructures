#include "list.h"


void initList(struct List *list, size_t stride, void *data, int data_size, int total_size){
    list->array = malloc(stride * total_size);
    list->stride = stride;
    list->current_size = 0;
    list->total_size = total_size;
    if(data != NULL){
        for(int i = 0; i < data_size; ++i){
            push(list, (data + i * stride));
        }
    }
    //Init an empty list with data_size elements
    else{
       memset(list->array, 0, data_size * stride); 
    }
}

void cleanList(struct List *list){
    free(list->array);
}

void resizeList(struct List *list){
    list->array = realloc(list->array, (list->total_size + 1) * 2 * list->stride);
}

void push(struct List *list, void *value){
    if(list->current_size == list->total_size){
        resizeList(list);
    }
    for(int i = 0; i < list->stride; ++i){
        *(uint8_t *)(list->array + list->current_size * list->stride + i) = *(uint8_t *)(value + i);
    }
    list->current_size++;
}

// It's going to return a pointer to the start of your value in the void array
// So when using it is requires a dereference and a cast e.g. int as type
// *(int *)(pop(list))
void *pop(struct List *list){
    if(list->current_size <= 0){
        printf("poping an empty list returning NULL");
        return NULL;
    }
    return (list->array + --list->current_size * list->stride);
}

//caller must allocate memory in val of sufficient size to store a single list element
void getValueAtIndex(struct List *list, int index, void *val){
    if(index >= list->current_size){
        fprintf(stderr, "tried to get value out of range. Tried %d when list->current_size = %d\n", index, list->current_size);
        return;
    }
	memcpy(val, list->array + index * list->stride, list->stride);
}

void *getPtrToIndex(struct List *list, int index){
    if(index >= list->current_size){
        printf("tried to get value out of range. Tried %d when list->current_size = %d\n", index, list->current_size);
        return NULL;
    }
	return list->array + index * list->stride;

}
void setAtIndex(struct List *list, int index, void *data){
    if(index >= list->current_size){
        printf("tried to set value out of range\n");
        return;
    }
    for(int i = 0; i < list->stride; ++i){
        *(uint8_t *)(list->array + index * list->stride + i) = *(uint8_t *)(data + i);
    }
}

void swapElements(struct List *list, int index_1, int index_2){
    if(index_1 >= list->current_size || index_2 >= list->current_size){
        printf("provided index to swapElements that was out of range\n");
        return;
    }
    void *tmp = malloc(list->stride);
    for(int i = 0; i < list->stride; ++i){
        *(uint8_t *)(tmp + i) = *(uint8_t *)(list->array + index_1 * list->stride + i);
    }
    for(int i = 0; i < list->stride; ++i){
        *(uint8_t *)(list->array + index_1 * list->stride + i) = *(uint8_t *)(list->array + index_2 * list->stride + i);
    }
    for(int i = 0; i < list->stride; ++i){
        *(uint8_t *)(list->array + index_2 * list->stride + i) = *(uint8_t *)(tmp + i);
    }
    free(tmp);
}
/*
int main(){
    struct List list;
    initList(&list, sizeof(int), NULL, 0,1024);

    int numbers[1024];
    for(int i = 0; i < 15; i++){
        numbers[i] = i;
        push(&list, (void *)&numbers[i]);
    }
    setAtIndex(&list, 0, (void *)&numbers[14]);
    swapElements(&list, 7, 8);
    for(int i = 0; i < 15; i++){
        printf("%d\n", *(int *)(pop(&list)));
    }

    cleanList(&list);
    return 0;
}
*/
