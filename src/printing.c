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
	for(int j=0; j<event->num_nodes; j++){
		printf("%6d",j+1);
	}
	printf("\n");
	for(int i=0; i<event->num_nodes; i++){
		printf("%6d",i+1);
		for(int h=0; h<event->num_nodes; h++){
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
	printf("Printing %d courses\n",event->num_courses);
	for(int course=0; course<event->num_courses; course++){
		int time = 0;
		for(int track=0; track<event->courses[course].num_tracks; track++){
			time = time + event->courses[course].tracks[track]->max_time;
		}
		printf("Course %c has %d tracks and takes %d minutes\n", event->courses[course].identifier, event->courses[course].num_tracks, time);
	}
}

