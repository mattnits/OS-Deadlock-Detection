#ifndef PCS_LLIST
#define PCS_LLIST
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

typedef struct pnode {
    struct process *p;
    struct pnode *next;
	struct pnode *prev;
} PNODE;

void pcs_insert_node(PNODE **startp, PNODE **endp, PROCESS *p);
PNODE* pcs_delete_node(PNODE **startp, PNODE **endp, PNODE *target);

#endif