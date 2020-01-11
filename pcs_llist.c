#include "pcs_llist.h"


void pcs_insert_node(PNODE **startp, PNODE **endp, PROCESS *p) {
	PNODE* ptr = (PNODE *) malloc(sizeof(PNODE));
	ptr->p = p;
	
	if (*endp == NULL) {
		ptr->next = NULL;
		ptr->prev = NULL;
		*endp = ptr;
		*startp = ptr;
	}
	else {
		ptr->next = NULL;		
		(*endp)->next = ptr;
		ptr->prev = *endp;
		*endp = ptr;
	}	
}

PNODE* pcs_delete_node(PNODE **startp, PNODE **endp, PNODE *target) {
// your code
	PNODE *ptr = *startp;
	PNODE *last = NULL;
	
	while (ptr != NULL && ptr->p->pid != target->p->pid) {
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
	else if (ptr->p->pid == (*endp)->p->pid) {
		//printf("testing\n");
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
