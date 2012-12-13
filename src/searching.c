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
Track *find_track(int start_node, int end_node, LinkedList *tracks){
	/*
	 * Searches for a track with the specified start and
	 * end node in the list of tracks specified.
	 */
	ListNode *current = tracks->head;
	do{
		Track *currentData = current->data;
		if((currentData->start_node->identifier==start_node
				&&currentData->end_node->identifier==end_node)
				||(currentData->start_node->identifier==end_node
						&&currentData->end_node->identifier==start_node)){
			return currentData;
		}
		current = current->next;
	}while(current!=NULL);
	return NULL;
}
Track *find_track_from_event(Event *event, int start_node, int end_node){
	/*
	 * Returns the track in the node graph with the start and end node
	 */
	return event->node_graph[start_node-1][end_node-1];
}
Node *find_node(Event *event, int ident){
	/*
	 * Finds a node by identifier in in the event
	 */
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
Course *find_course(char identifier, Event *event){
	/*
	 * Finds a course in an event
	 */
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
Entrant *find_entrant(int competitor_num, Event *event){
	/*
	 * Finds an entrant by competitor number in an event
	 */
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
Entrant *find_entrant_by_name(char *name, Event *event){
	/*
	 * Finds an entrant by name in an event
	 */
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
	/*
	 * Returns the number of time checkpoints in a course
	 */
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
	/*
	 * Returns 1 if they have finished, 0 if they're on course,
	 * and -1 if they have not started.
	 */
	if((entrant->visited.length)>=checkpoints_in_course(entrant->course)){
		return 1;
	}else if(entrant->visited.length<=1){
		return -1;
	}
	return 0;
}
Track *current_track(Event *event, Entrant *entrant){
	/*
	 * Finds the current track an entrant should be on,
	 * assuming they're on time and went the correct direction.
	 */
	int i;
	int time_since_last_checkin = event->current_time-entrant->current_time;
	int time = 0;

	Node *last = entrant->visited.tail->data;
	if(has_finished(entrant)==0&&is_on_course(entrant)==1){
		for(i=0; i<entrant->course->num_tracks; i++){
			Track *t = entrant->course->tracks[i];
			if(t->start_node==last){
				break;
			}
		}
		for(;i<entrant->course->num_tracks; i++){
			Track *current = entrant->course->tracks[i];
			if((i+1)>entrant->course->num_tracks){
				return NULL;
			}
			time += current->max_time;
			if(time>time_since_last_checkin){
				return current;
			}
		}
	}
	return NULL;
}
int get_completion_time(Entrant *entrant){
	/*
	 * Returns the time in minutes it took the entrant
	 * to complete the course.
	 */
	int start_time = entrant->start_time;
	int time = entrant->current_time;
	int medical = entrant->medical;
	time = time - start_time - medical;
	return time;
}

