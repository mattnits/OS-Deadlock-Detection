#include "process.h"
//TAKEN FROM CP264 AND MODIFIED

PROCESS* new_process(int process_id, int process_bool, int deadlock) {
	PROCESS *pcs = (PROCESS*) malloc(sizeof(PROCESS));
	pcs->pid = process_id;
	pcs->process_bool = process_bool;
	pcs->deadlock = deadlock;
	
	return pcs;
}