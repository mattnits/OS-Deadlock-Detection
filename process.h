#ifndef PROCESS_H
#define PROCESS_H
//TAKEN FROM CP264 AND MODIFIED

#include <stdio.h>
#include <malloc.h>

typedef struct process {
	int pid;
	int process_bool;
	int deadlock;
	
} PROCESS;

PROCESS* new_process(int process_id, int process_bool, int deadlock);

#endif