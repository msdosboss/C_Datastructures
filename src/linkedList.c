#include "linkedList.h"

//initializes head, tail, and length of a singly linked list
struct SLL SLL_init(size_t stride) {
	return (struct SLL) {
		.head = NULL,
		.tail = NULL,
		.length = 0,
		.stride = stride
	};
}

void SLL_Node_free(struct SLL_Node *n)
{
	free(n->data);
	free(n);
}

void SLL_free(struct SLL *list)
{
	struct SLL_Node *current = list->head;
	struct SLL_Node *tmp;
	while (current) {
		tmp = current->next;
		SLL_Node_free(current);
		current = tmp;
	}
}

struct SLL_Node *SLL_Node_init(void *data, size_t stride) {
	struct SLL_Node *node = malloc(sizeof(struct SLL_Node));
	node->data = malloc(sizeof(struct SLL_Node));
	memcpy(node->data, data, stride);
	node->next = NULL;
	return node;
}

void SLL_prepend(struct SLL *list, void *data)
{
	struct SLL_Node *node = SLL_Node_init(data, list->stride);
	if (list->head == NULL) {
		list->tail = node;
		list->head = node;
	} else {
		node->next = list->head;
		list->head = node;
	}
	list->length++;
	return;
}


void SLL_append(struct SLL *list, void *data)
{
	struct SLL_Node *node = SLL_Node_init(data, list->stride);
	if (list->head == NULL) {
		list->tail = node;
		list->head = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
	list->length++;
	return;
}

void SLL_insert_after(struct SLL *list, uint8_t (*cmp)(void *, void *), void *insert_after, void *data)
{
	struct SLL_Node *current_node = list->head;
	struct SLL_Node *new_node = SLL_Node_init(data, list->stride);
	if (list->head == NULL) {
		list->tail = new_node;
		list->head = new_node;
	}
	while (current_node != NULL) {
		if(cmp(current_node->data, data)){
			new_node->next = current_node->next;
			current_node->next = new_node;
			list->length++;
			return;
		}
		current_node = current_node->next;
	}
	list->tail->next = new_node;
	list->tail = new_node;
	list->length++;
	return;
}

uint8_t int_is_equ(void *a, void *b) { return (*(uint32_t *)a == *(uint32_t *)b) ? 1 : 0; }

void SLL_remove(struct SLL *list, uint8_t (*cmp)(void *, void *), void *remove_at)
{
	struct SLL_Node *current_node = list->head;
	struct SLL_Node *prev_node = NULL;
	if (list->head == NULL) {
		return;
	}
	while (current_node != NULL) {
		if(cmp(current_node->data, remove_at)){
			if (current_node == list->tail) {
				list->tail = prev_node;
			}
			if (prev_node == NULL) {
				list->head = current_node->next;
				SLL_Node_free(current_node);
			} else {
				prev_node->next = current_node->next;
				SLL_Node_free(current_node);
			}
			list->length--;
			return;
		}
		prev_node = current_node;
		current_node = current_node->next;
	}
}

uint8_t SLL_contains(struct SLL *list, uint8_t (*cmp)(void *, void *), void *data)
{
	struct SLL_Node *current_node = list->head;
	if (list->head == NULL) {
		return 0;
	}
	while (current_node != NULL) {
		if(cmp(current_node->data, data)){
			return 1;
		}
		current_node = current_node->next;
	}
	return 0;
}


void print_list(void *element)
{
	printf("%u\n", *(uint32_t *)element);
}

void SLL_print(struct SLL *list, void (*print_fn)(void *))
{
	struct SLL_Node *current_node = list->head;
	while (current_node != NULL) {
		print_fn(current_node->data);
		current_node = current_node->next;
	}
}

uint8_t SLL_is_empty(struct SLL *list)
{
	return (list->head == NULL) ? 1 : 0;
}

size_t SLL_get_length(struct SLL *list)
{
	return list->length;
}

int main()
{
	struct SLL a = SLL_init(sizeof(uint32_t));
	uint32_t big_data = 0xFFFFFFFF;
	uint32_t medium_data = 0x88888888;
	uint32_t small_data = 015;
	SLL_append(&a, (void *) &big_data);
	printf("big data %u\n", *(uint32_t *)a.head->data);
	SLL_append(&a, (void *) &small_data);
	printf("small data %d\n", *(uint32_t *)a.tail->data);

	SLL_prepend(&a, (void *) &medium_data);
	printf("medium data %u\n", *(uint32_t *)a.head->data);
	
	medium_data = 67;
	SLL_insert_after(&a, int_is_equ, (void *)&small_data, (void *)&medium_data);

	printf("special data %d\n", *(uint32_t *)a.head->next->next->next->data);
	SLL_print(&a, print_list);
	printf("REMOVING\n");
	SLL_remove(&a, int_is_equ, (void *)&big_data);
	SLL_print(&a, print_list);
	printf("%s\n", SLL_contains(&a, int_is_equ,(void *)&big_data) ? "Contains" : "does not contain");



	SLL_free(&a);
	return 0;
}
