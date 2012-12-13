/*
 * manipulation.c
 *
 *  Created on: 9 Dec 2012
 *      Author: tim
 */
#include <stdlib.h>
#include "data.h"
#include "functions.h"
#include <stdio.h>
void checkin(Event *event, int node_ident, Entrant *entrant, int h, int m){
	/*
	 * Finds the node specified by a node ident
	 * and adds it to the visited list of the specified entrant
	 * also updating the time they last visited a node,
	 * and the time the Event was last updated.
	 */
	int time = h*60 + m;
	Node *at = find_node(event, node_ident);
	if(entrant->visited.length==0){
		entrant->start_time = time;
	}
	listadd(at, &entrant->visited);
	entrant->current_time = time;
	is_on_course(entrant);
	event->current_time = time;
}
void medical(Event *event, int node_ident, Entrant *entrant, int h, int m){
	int t = 60*h + m;
	Node *tail = entrant->visited.tail->data;
	if(entrant->visited.tail->previous!=NULL){
		Node *last = entrant->visited.tail->previous->data;
		if(last->type==MC&&tail->type==MC){
			entrant->medical = entrant->medical - (t-entrant->current_time);
		}
	}
	checkin(event, node_ident, entrant, h, m);
}
void listadd(void *data, LinkedList *list){
	/*
	 * Adds data to a linked list.
	 * If the length is 0 then sets the new node as head,
	 * if not sets the tails next node as the new node,
	 * then sets the tail node as the new node.
	 * Then finally increases the length.
	 */
	if(list->length==0){
		list->head = malloc(sizeof(ListNode));
		list->tail = list->head;
		list->head->previous = NULL;
	}else{
		list->tail->next = malloc(sizeof(ListNode));
		list->tail->next->previous = list->tail;
		list->tail = list->tail->next;
	}
	list->tail->data = data;
	list->length = list->length + 1;
}
void listremove(LinkedList *list, ListNode *node){
	/*
	 * This method isn't actually used, but is there anyway.
	 * Gets the nodes either side of the given node and links them,
	 * then deletes the list node and decreses the length.
	 */
	ListNode *previous = node->previous;
	ListNode *next = node->next;
	previous->next = next;
	next->previous = previous;
	free(node);
	list->length = list->length - 1;
}
void swapelements(ListNode *first, ListNode *second){
	/*
	 * Swaps the data inside of the 2 elements.
	 */
	void *data = first->data;
	first->data = second->data;
	second->data = data;

}
void sortentrants(LinkedList *list){
	/*
	 * Does a simple bubble sort on the list,
	 * ordering it from smallest time to largest.
	 */
	int num_changed = 1;
	ListNode *current = list->head;
	while(num_changed>0){
		current = list->head;
		num_changed = 0;
		for(int i=0; i<list->length-1; i++){
			Entrant *c = current->data;
			Entrant *n = current->next->data;
			if(get_completion_time(c)>get_completion_time(n)){
				swapelements(current,current->next);
				num_changed++;
			}
			current = current->next;
		}
	}
}
int is_on_course(Entrant *entrant){
	if(has_finished(entrant)){
		return 1;
	}
	LinkedList cps;
	cps.length = 0;
	for(int i=0; i<entrant->course->num_tracks; i++){
		Node *cp = entrant->course->tracks[i]->start_node;
		if(cp->type==CP||cp->type==MC){
			listadd(cp, &cps);
		}
	}
	Node *final = entrant->course->tracks[entrant->course->num_tracks-1]->end_node;
	if(final->type==CP||final->type==MC){
		listadd(final,&cps);
	}
	ListNode *current = cps.head;
	ListNode *visited = entrant->visited.head;
	while(visited!=NULL){
		Node *cD = current->data;
		Node *cVD = visited->data;
		if(cD->identifier!=cVD->identifier){
			entrant->excluded = OFFCOURSE;
			return 0;
		}
		current = current->next;
		visited = visited->next;
	}
	return 1;
}



