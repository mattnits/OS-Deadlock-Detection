#ifndef LLIST
#define LLIST
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int a[600];
	int id; 
	struct node *prev;
    struct node *next;
} NODE;

void insert_node(NODE **startp, NODE **endp, int a[], int m, int id);
NODE* delete_node(NODE **startp, NODE **endp, NODE *target);

#endif