#include "llist.h"


void insert_node(NODE **startp, NODE **endp, int a[], int m, int id) {
	NODE* p = (NODE *) malloc(sizeof(NODE));
	p->next = NULL;
	p->prev = NULL;
	p->id = id;
	
	int i = 0;
	for (i = 0; i < m; i++) {
		p->a[i] = a[i];
	}
	
	if (*endp == NULL) {
		p->next = NULL;
		p->prev = NULL;
		*endp = p;
		*startp = p;
	}
	else {
		p->next = NULL;		
		(*endp)->next = p;
		p->prev = *endp;
		*endp = p;
	}	
}

NODE* delete_node(NODE **startp, NODE **endp, NODE *target) {
// your code
	NODE *ptr = *startp;
	NODE *last = NULL;
	
	while (ptr != NULL && ptr->id != target->id) {
		last = ptr;
		ptr = ptr->next;
	}
	
	if (ptr == NULL) {
		printf("ERROR IN LLIST REMOVE\n");
		return ptr;
	}
	else if (last == NULL && *startp != *endp) {
		last = ptr;
		ptr = ptr->next;
		*startp = ptr;
		ptr->prev = NULL;

		return last;
	}
	else if (last == NULL && *startp == *endp) {
		*startp = NULL;
		*endp = NULL;
		return ptr;
	}
	else if (ptr->id == (*endp)->id) {
		last->next = NULL;
		*endp = last;
		return ptr;
	}
	else {
		last->next = ptr->next;
		ptr->next->prev = last;
		return ptr;
	}
}
