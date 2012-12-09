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
void printNode(Node *n){
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
void printTracks(Event *event){
	printf("%6s","");
	for(int j=0; j<event->nodes.length; j++){
		printf("%6d",j+1);
	}
	printf("\n");
	for(int i=0; i<event->nodes.length; i++){
		printf("%6d",i+1);
		for(int h=0; h<event->nodes.length; h++){
			int max = 0;
			if(event->nodeGraph[i][h]!=NULL){
				max = event->nodeGraph[i][h]->max_time;
			}
			printf("%5d%1s",max,"m");
		}
		printf("\n");
	}
}
void printCourses(Event *event){
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
void printEntrants(Event *event){
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		printf("Competitor number %d, %s on course %c\n", currentData->competitor_num, currentData->name, currentData->course->identifier);
		if(currentData->visited.length>0){
			int h = currentData->time/60;
			int m = currentData->time%60;
			printf("And they last hit a checkpoint at %d:%d and have visited these checkpoints: ",h,m);
			ListNode *c = currentData->visited.head;
			do{
				Node *n = c->data;
				printf("%d, ", n->identifier);
				c = c->next;
			}while(c!=NULL);
			printf("\n\n");
		}
		current = current->next;
	}while(current!=NULL);
}
void printStatus(Entrant *entrant){
	int h = entrant->time/60;
	int m = entrant->time%60;
	Node *last = entrant->visited.tail->data;
	printf("Entrant %s last checked in at %d:%d at checkpoint %d\n", entrant->name, h, m, last->identifier);
}

