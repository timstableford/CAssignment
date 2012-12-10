/*
 * printing.c
 *
 *  Created on: 8 Dec 2012
 *      Author: tim
 */
#include "functions.h"
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
void print_node(Node *n){
	char *t;
	switch(n->type){
	case CP:
		t = "Checkpoint";
		break;
	case MC:
		t = "Medical Checkpoint";
		break;
	case JN:
		t = "Junction";
		break;
	}
	printf("Node identifier: %d Type: %s\n", n->identifier, t);
}
void print_courses(Event *event){
	printf("Printing %d courses\n",event->courses.length);
	ListNode *current = event->courses.head;
	do{
		Course *currentData = current->data;
		int time = 0;
		for(int track=0; track<currentData->num_tracks; track++){
			time = time + currentData->tracks[track]->max_time;
		}
		printf("Course %c has %d tracks and takes %d minutes\n", currentData->identifier, currentData->num_tracks, time);
		current = current->next;
	}while(current!=NULL);
}
void print_entrants(Event *event){
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		print_status(currentData);
		current = current->next;
	}while(current!=NULL);
}
void print_status(Entrant *entrant){
	int h = entrant->time/60;
	int m = entrant->time%60;
	printf("%s is on course %c and ",entrant->name, entrant->course->identifier);
	if(entrant->visited.length==0){
		printf(" has not checked in\n");
	}else{
		Node *last = entrant->visited.tail->data;
		printf("last checked in at %d:%d at checkpoint %d", h, m, last->identifier);
		switch(has_finished(entrant)){
		case -1:
			printf(" and has not started\n");
			break;
		case 0:
			printf(" and is on course\n");
			break;
		case 1:
			printf(" and has finished\n");
			break;
		}
	}
}
void print_not_started(Event *event){
	int num = 0;
	ListNode *current = event->entrants.head;
	printf("Entrants who have not started are: \n");
	do{
		Entrant *currentData = current->data;
		if(has_finished(currentData)==-1){
			printf("%s\n", currentData->name);
			num++;
		}
		current = current->next;
	}while(current!=NULL);
	printf("%d entrants have not started\n",num);
}
void print_started(Event *event){
	int num = 0;
	ListNode *current = event->entrants.head;
	printf("Entrants who are on the course are: \n");
	do{
		Entrant *currentData = current->data;
		if(has_finished(currentData)==0){
			printf("%s\n", currentData->name);
			num++;
		}
		current = current->next;
	}while(current!=NULL);
	printf("%d entrants have started\n", num);
}
void print_finished(Event *event){
	int num_fin = 0;
	ListNode *current = event->entrants.head;
	printf("Entrants who have finished are: \n");
	do{
		Entrant *currentData = current->data;
		if(has_finished(currentData)){
			printf("%s\n", currentData->name);
			num_fin++;
		}
		current = current->next;
	}while(current!=NULL);
	printf("%d have finished\n",num_fin);
}

