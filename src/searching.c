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

