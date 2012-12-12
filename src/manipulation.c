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
	int time = h*60 + m;
	Node *at = find_node(event, node_ident);
	entrant->time = time;
	if(entrant->visited.length==0){
		entrant->start_time = time;
	}
	listadd(at, &entrant->visited);
	event->current_time = time;
}
void listadd(void *data, LinkedList *list){
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
	ListNode *previous = node->previous;
	ListNode *next = node->next;
	previous->next = next;
	next->previous = previous;
	free(node);
	list->length = list->length - 1;
}
void swapelements(ListNode *first, ListNode *second){
	void *data = first->data;
	first->data = second->data;
	second->data = data;

}
void sortentrants(LinkedList *list){
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



