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
	/*
	 * Prints a node in a readable format
	 */
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
	/*
	 * Prints all the courses in an event,
	 * and for each prints its identifier, number of tracks,
	 * and it's time.
	 */
	printf("Printing %d courses\n",event->courses.length);
	ListNode *current = event->courses.head;
	do{
		Course *currentData = current->data;
		int time = 0;
		for(int track=0; track<currentData->num_tracks; track++){
			time = time + currentData->tracks[track]->max_time;
		}
		printf("Course %c has %d tracks and takes %d minutes\n",
				currentData->identifier, currentData->num_tracks, time);
		current = current->next;
	}while(current!=NULL);
}
void print_entrants(Event *event){
	/*
	 * Calls print_status for each entrant in the event
	 */
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		print_status(event, currentData);
		current = current->next;
	}while(current!=NULL);
}
void print_status(Event *event, Entrant *entrant){
	/*
	 * Prints their name, course identifier,
	 * and then where they are: not started,
	 * on course, finished.
	 */
	int h = entrant->current_time/60;
	int m = entrant->current_time%60;
	Track *t;
	printf("%s is on course %c and ",entrant->name, entrant->course->identifier);
	if(entrant->visited.length==0){
		printf(" has not checked in\n");
	}else{
		Node *last = entrant->visited.tail->data;
		printf("last checked in at %dh %dm at checkpoint %d", h, m, last->identifier);
		switch(has_finished(entrant)){
		case -1:
			printf(" and has not started\n");
			break;
		case 0:
			t = current_track(event, entrant);
			is_on_course(entrant);
			switch(entrant->excluded){
			case NONE:
				printf(" and is currently on track %d\n", t->track_num);
				break;
			case OFFCOURSE:
				printf(" and is off course\n");
				break;
			case MEDICAL:
				printf(" and is excluded for medical reasons\n");
				break;
			}
			break;
		case 1:
			printf(" and has finished\n");
			break;
		}
	}
}
void print_not_started(Event *event){
	/*
	 * Prints the name of each of the entrants who have not started,
	 * and then prints the number of names listed.
	 */
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
	/*
	 * Prints the name of each of the entrants on course,
	 * and then prints the number of names listed.
	 */
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
	printf("%d entrants are on course\n", num);
}
void print_finished(Event *event){
	/*
	 * Prints the name of each of the entrants who have finished,
	 * and then prints the number of names listed.
	 */
	int num_fin = 0;
	ListNode *current = event->entrants.head;
	printf("Entrants who have finished are: \n");
	do{
		Entrant *currentData = current->data;
		if(has_finished(currentData)==1){
			printf("%s\n", currentData->name);
			num_fin++;
		}
		current = current->next;
	}while(current!=NULL);
	printf("%d have finished\n",num_fin);
}
void print_results(Event *event){
	/*
	 * Orders the list of entrants who have finished,
	 * then prints each in order of time taken,
	 * smallest to largest, in a readable format.
	 */
	LinkedList finished;
	finished.length = 0;
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		if(has_finished(currentData)==1){
			listadd(currentData, &finished);
		}
		current = current->next;
	}while(current!=NULL);
	sortentrants(&finished);
	ListNode *cf = finished.head;
	Entrant *ce = cf->data;
	do{
		printf("%s started at %dh %dm and finished at %dh %dm and took %dh %dm minutes",ce->name,
				ce->start_time/60, ce->start_time%60,
				ce->current_time/60, ce->current_time%60,
				get_completion_time(ce)/60,get_completion_time(ce)%60);
		if(ce->medical>0){
			 printf(" and %d minutes were removed for medical",ce->medical);
		}
		printf("\n");
		cf = cf->next;
		if(cf!=NULL){
			ce = cf->data;
		}
	}while(cf!=NULL&&ce!=NULL&&ce->current_time!=0);
}
void print_nodes(Event *event){
	ListNode *current = event->nodes.head;
	do{
		Node *n = current->data;
		print_node(n);
		current = current->next;
	}while(current!=NULL);
}
void print_excluded(Event *event, int reason){
	int num_excluded = 0;
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		if(currentData->excluded==reason){
			printf("%s\n", currentData->name);
			num_excluded++;
		}
		current = current->next;
	}while(current!=NULL);
	printf("%d excluded\n", num_excluded);
}

