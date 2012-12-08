/*
 * searching.c
 *
 *  Created on: 8 Dec 2012
 *      Author: tim
 */
#include "data.h"
#include "functions.h"
#include <stdlib.h>
Track *findTrack(int start_node, int end_node, Track *tracks, int num_tracks){
	for(int i=0; i<num_tracks; i++){
		if((tracks[i].start_node->identifier==start_node&&tracks[i].end_node->identifier==end_node)
				||(tracks[i].start_node->identifier==end_node&&tracks[i].end_node->identifier==start_node)){
			return &tracks[i];
		}
	}
	return NULL;
}
Track *findTrackFromEvent(Event *event, int start_node, int end_node){
	return event->nodeGraph[start_node-1][end_node-1];
}
Node *findNode(Event *event, int ident){
	ListNode *current = event->nodes.head;
	do{
		Node *currentData = current->data;
		if(currentData->identifier==ident){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
	return NULL;
}
Course *findCourse(char identifier, Event *event){
	for(int i=0; i<event->num_courses; i++){
		if(event->courses[i].identifier==identifier){
			return &event->courses[i];
		}
	}
	return NULL;
}


