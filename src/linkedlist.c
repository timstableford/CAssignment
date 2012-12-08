/*
 * linkedlist.c
 *
 *  Created on: 8 Dec 2012
 *      Author: tim
 */
#include "data.h"
#include <stdlib.h>
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


