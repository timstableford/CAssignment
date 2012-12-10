/*
 * searching.c
 *
 *  Created on: 8 Dec 2012
 *      Author: tim
 */
#include "data.h"
#include "functions.h"
#include <stdlib.h>
#include <string.h>
Track *findTrack(int start_node, int end_node, LinkedList *tracks){
	ListNode *current = tracks->head;
	do{
		Track *currentData = current->data;
		if((currentData->start_node->identifier==start_node&&currentData->end_node->identifier==end_node)
				||(currentData->start_node->identifier==end_node&&currentData->end_node->identifier==start_node)){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
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
	ListNode *current = event->courses.head;
	do{
		Course *currentData = current->data;
		if(currentData->identifier==identifier){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
	return NULL;
}
Entrant *findEntrant(int competitor_num, Event *event){
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		if(currentData->competitor_num==competitor_num){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
	return NULL;
}
Entrant *findEntrantByName(char *name, Event *event){
	ListNode *current = event->entrants.head;
	do{
		Entrant *currentData = current->data;
		if(strcmp(name, currentData->name)==0){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
	return NULL;
}
int checkpoints_in_course(Course *course){
	int ret = 0;
	for(int i=0; i<course->num_tracks; i++){
		Track *t = course->tracks[i];
		if(t->start_node->type==CP){
			ret++;
		}
	}
	if(course->tracks[course->num_tracks-1]->end_node->type==CP){
		ret++;
	}
	return ret;
}
int has_finished(Entrant *entrant){
	//1 for finished, 0 for in progress, -1 for not started
	if((entrant->visited.length)>=checkpoints_in_course(entrant->course)){
		return 1;
	}else if(entrant->visited.length<=1){
		return -1;
	}
	return 0;
}

