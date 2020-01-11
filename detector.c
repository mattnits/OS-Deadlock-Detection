/*
detector.c

Student Name : Matthew Nitsopoulos
Student ID # : 170673880

TO FINISH: 4 5 6

FINISHED: 1 2 3
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 1000

/*
Any required standard libraries and your header files here
*/
#include "process.h"
#include "llist.h"
#include "pcs_llist.h"


void detector(FILE *fd){
    /*
        Your code here.
        You may edit the following code
    */
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    
    int n, m, num, cnt = 1;
	NODE *req_start = NULL, *req_rear = NULL, *alo_start = NULL, *alo_rear = NULL, *unalo_start = NULL, *unalo_rear = NULL;
	NODE *d_req_start = NULL, *d_req_rear = NULL, *d_alo_start = NULL, *d_alo_rear = NULL;
	PNODE *pcs_start = NULL, *pcs_rear = NULL;
	PNODE *d_pcs_start = NULL, *d_pcs_rear = NULL, *involved_start = NULL, *involved_rear = NULL;
    
	//Processs first line
    fgets(line_buffer, MAX_LINE_LENGTH, fd);
    sscanf(line_buffer, "%d %d",&n, &m);
	
	//printf("N = %d\n", n);
	//printf("M = %d\n", m);
    //Process remaining lines
    //Hint use template code from A1 to parse each line
	
	int i = 0, id_num = 1;
	int a[m];
	
	while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n') {
		
		token = strtok(line_buffer, " ");
		sscanf(token, "%d", &num);
		a[i] = num;
		i++;
		cnt++;
		
		token = strtok(NULL, " ");
		while ( token != NULL ){
			sscanf(token, "%d",&num);
			a[i] = num;
			token = strtok(NULL, " ");
			i++;
			cnt++;
		}
		i = 0;
		if (cnt <= ((m * n) + 1)) {
			insert_node(&req_start, &req_rear, a, m, id_num);
			pcs_insert_node(&pcs_start, &pcs_rear, (new_process(id_num, 0, 1)));
			
		}
		else if (cnt <= (((m * n) * 2) + 1)) {
			insert_node(&alo_start, &alo_rear, a, m, id_num);
		}
		else {
			insert_node(&unalo_start, &unalo_rear, a, m, id_num);
		}
		id_num++;
    }
	NODE *temp1 = req_start, *temp2 = alo_start, *temp3 = unalo_start, *temp1_back = NULL, *temp2_back = NULL;
	PNODE *temp_pcs = pcs_start, *temp_pcs_back = NULL;
	//int j = 0;
	
	/*printf("--------------REQUIRED------------------\n");
	while (temp1 != NULL) {
		for (j = 0; j < m; j++) {
			printf("%d ", temp1->a[j]);
		}
		printf("\n");
		temp1 = temp1->next;
	}
	j = 0;
	//printf("--------------ALLOCATED------------------\n");
	while (temp2 != NULL) {
		for (j = 0; j < m; j++) {
			printf("%d ", temp2->a[j]);
		}
		printf("\n");
		temp2 = temp2->next;
	}
	j = 0;
	//printf("--------------UNALLOCATED------------------\n");
	while (temp3 != NULL) {
		for (j = 0; j < m; j++) {
			printf("%d ", temp3->a[j]);
		}
		printf("\n");
		temp3 = temp3->next;
	}
	//printf("--------------PROCESSESS------------------\n");
	while (temp_pcs != NULL) {
		//printf("Process: %d, is %d\n", temp_pcs->p->pid, temp_pcs->p->process_bool);
		temp_pcs = temp_pcs->next;
	}*/
	
	//DECLARE VARIABLES FOR ALGO
	temp1 = req_start; 
	temp2 = alo_start;
	temp3 = unalo_rear;
	temp_pcs = pcs_start;
	PNODE *safe_start = NULL, *safe_rear = NULL, *del = NULL, *node_temp = NULL;
	
	//Set the total
	int total[m];
	for (i = 0; i < m; i++) {
		total[i] = temp3->a[i];
	}
	
	
	//Write algo
	int k = 0;
	int num_done = 0;
	int dlock = 1;
	int num_dlock = 0;
		
	//CHECK TO MAKE SURE THIS IS NOT EQUAL TO ZERO
	while (num_done < n) {
		while (temp_pcs->p->process_bool != 1) {
			for (k = 0; k < m; k++) {
				if (temp2->a[k] != 0) {
					temp_pcs->p->process_bool = 1;
					break;
				}
			}
			if (temp_pcs->p->process_bool != 1) {
				//MAYBE INSERT TO FINISH
				temp2 = temp2->next;
				temp_pcs = temp_pcs->next;
			}
		}
		
		while (num_done < n && dlock == 1) {
			//printf("----------------------------------\n");
			//printf("ID: %d\n", temp1->id);
			//printf("----------------------------------\n");
			
			for (k = 0; k < m; k++) {
				//printf("%d > %d \n", temp1->a[k], total[k]);
				if (temp1->a[k] > total[k]) {
					temp_pcs->p->deadlock = 0;
					
					node_temp = involved_start;
					while (node_temp != NULL && node_temp->p->pid != temp_pcs->p->pid) {
						node_temp = node_temp->next;
					}
					if (node_temp == NULL) {
						pcs_insert_node(&involved_start, &involved_rear, temp_pcs->p);
					}
					break;
				}
			}
			
			if (temp_pcs == pcs_rear && temp_pcs->p->deadlock == 0) {
				dlock = 0;
				num_dlock++;
				temp1 = req_start;
				temp2 = alo_start;
				temp_pcs = pcs_start;
			}
			else if (temp_pcs->p->deadlock == 0) {
				temp_pcs = temp_pcs->next;
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else {
				//CHECK IF ANY PROCESSES GO FIRST
				temp1_back = req_rear;
				temp2_back = alo_rear;
				temp_pcs_back = pcs_rear;
				
				//printf("-=-=-=-=-=CHECKING REAR-=-=-=-=-=\n");
				
				while (temp1_back->id != temp1->id) {
					//printf("----------------------------------\n");
					//printf("BACK-ID: %d\n", temp1_back->id);
					//printf("----------------------------------\n");
					
					for (k = 0; k < m; k++) {
						//printf("%d > %d \n", temp1_back->a[k], total[k]);
						if (temp1_back->a[k] > total[k]) {
							temp_pcs_back->p->deadlock = 0;
							break;
						}
					}
					if (temp_pcs_back->p->deadlock == 1) {
						break;
					}
					else {
						temp1_back = temp1_back->prev;
						temp2_back = temp2_back->prev;
						temp_pcs_back = temp_pcs_back->prev;
					}
				}	
				
				if (temp1_back->id == temp1->id) {
					//printf("---------------TOTAL FRONT--------------\n");
					for (k = 0; k < m; k++) {
						total[k] += temp2->a[k];
						//printf("%d ", total[k]);
					}
					//printf("\n----------------------------------\n");
					//printf("\n");
					del = pcs_delete_node(&pcs_start, &pcs_rear ,temp_pcs);
					
					pcs_insert_node(&safe_start, &safe_rear, del->p);
					delete_node(&req_start, &req_rear, temp1);
					delete_node(&alo_start, &alo_rear, temp2);
				}
				else {
					//printf("---------------TOTAL REAR--------------\n");
					for (k = 0; k < m; k++) {
						total[k] += temp2_back->a[k];
						//printf("%d ", total[k]);
					}
					//printf("\n----------------------------------\n");
					//printf("\n");
					del = pcs_delete_node(&pcs_start, &pcs_rear ,temp_pcs_back);
					
					pcs_insert_node(&safe_start, &safe_rear, del->p);
					delete_node(&req_start, &req_rear, temp1_back);
					delete_node(&alo_start, &alo_rear, temp2_back);
				}
				num_done++;
				
				temp_pcs = pcs_start;
				while (temp_pcs != NULL) {
					temp_pcs->p->deadlock = 1;
					temp_pcs = temp_pcs->next;
				}
				
				if (num_dlock == 0) {
					node_temp = involved_start;
					while (node_temp != NULL) {
						pcs_delete_node(&involved_start, &involved_rear, node_temp);
						node_temp = involved_start;
					}
				}
				
				temp1 = req_start;
				temp2 = alo_start;
				temp_pcs = pcs_start;
				
				//printf("REMOVED: R-> %d & A-> %d\n", delete_node(&req_start, &req_rear, temp1)->id, delete_node(&alo_start, &alo_rear, temp2)->id);
				//printf("temp1 %d\n", temp1->id);
				//printf("temp2 %d\n", temp2->id);
				//printf("process %d\n", temp_pcs->p->pid);
			}
		}
		while (dlock == 0) {
			temp1 = req_rear;
			temp2 = alo_rear;
			temp_pcs = pcs_rear;
			
			NODE *p1 = delete_node(&req_start, &req_rear, temp1);
			NODE *p2 = delete_node(&alo_start, &alo_rear, temp2);
			insert_node(&d_req_start, &d_req_rear, p1->a, m, p1->id);
			insert_node(&d_alo_start, &d_alo_rear, p2->a, m, p2->id);
			pcs_insert_node(&d_pcs_start, &d_pcs_rear, pcs_delete_node(&pcs_start, &pcs_rear, temp_pcs)->p);
			for (k = 0; k < m; k++) {
				total[k] += d_alo_rear->a[k];
			}
			//printf("====================================\n");
			//printf("PROCESS %d has been deleted!", d_pcs_rear->p->pid);
			//printf("\n====================================\n");
			
			temp_pcs = pcs_start;
			while (temp_pcs != NULL) {
				temp_pcs->p->deadlock = 1;
				temp_pcs = temp_pcs->next;
			}
			
			temp1 = req_start; 
			temp2 = alo_start;
			temp_pcs = pcs_start;
			dlock = 1;
			num_done++;
		}
		
		//DONE ALL WHILE LOOPS
	}
	//printf("FIN: %d\n", fin[0]);
	//printf("--------------FINISHED------------------\n");
	PNODE *finished = safe_start, *deleted = d_pcs_start, *involved = involved_start;
	
	if (deleted == NULL) {
		while (finished != NULL){
		printf("%d ", finished->p->pid);
		finished = finished->next;
		}
	}
	else {
		while (involved != NULL) {
			printf("%d ", involved->p->pid);
			involved = involved->next;
		}
		
		printf("\n");
		
		while (deleted != NULL) {
			printf("%d ", deleted->p->pid);
			deleted = deleted->next;
		}
		
		printf("\n");
		
		while (finished != NULL){
			printf("%d ", finished->p->pid);
			finished = finished->next;
		}
	}
	//THE END
}
