#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "functions.h"
int loadFiles(char* folder_name, Event *event){
	printf("%s\n", folder_name);
	int status;
	char *name;
	//load event
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_NAME);
	status = loadEvent(name, event);
	free(name);
	if(status<1){ return status; }
	//load nodes
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_NODES);
	status = loadNodes(name, event);
	free(name);
	if(status<1){ return status; }
	//load tracks
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_TRACKS);
	status = loadTrack(name,event);
	free(name);
	if(status<1){ return status; }

	//load courses
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_COURSES);
	status = loadCourses(name, event);
	free(name);
	if(status<1){ return status; }

	//load entrants
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_ENTRANTS);
	status = loadEntrants(name, event);
	free(name);
	if(status<1){ return status; }

	return 1;
}
int loadEvent(char* file_location, Event *event){
	FILE *file = fopen(file_location,"r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	fscanf(file, " %[^\n] %[^\n] %[^\n]",event->name,event->date,event->time);
	return 1;
}
int loadNodes(char* file_location, Event* event){
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	int ident;
	event->nodes.length = 0;
	char type[2];
	while(fscanf(file, " %d %s",&ident,type)!=EOF){
		Node *n = malloc(sizeof(Node));
		n->identifier = ident;
		if(strcmp("JN",type)==0){
			n->type = JN;
		}else if(strcmp("CP",type)==0){
			n->type = CP;
		}else if(strcmp("MC",type)==0){
			n->type = MC;
		}
		listadd(n, &event->nodes);
	}
	return 1;
}
int loadCourses(char* file_location, Event* event){
	//courses contain tracks
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	event->courses.length = 0;
	char ident;
	int num_nodes;
	while(fscanf(file, " %c %d",&ident,&num_nodes)!=EOF){
		Course *c = malloc(sizeof(Course));
		c->identifier = ident;
		int last_node = -1;
		c->num_tracks = num_nodes-1;
		c->tracks = calloc(num_nodes-1,sizeof(Track*));
		for(int i=0; i<num_nodes; i++){
			int node_ident;
			fscanf(file, " %d",&node_ident);
			if(last_node>=0){
				c->tracks[i-1] = findTrackFromEvent(event,last_node,node_ident);
			}
			last_node = node_ident;
		}
		listadd(c, &event->courses);
	}
	return 1;
}
int loadTrack(char* file_location, Event* event){
	//tracks are the time between 2 nodes
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	int track_num;
	int start_node;
	int end_node;
	int max_time;
	//first we'll scan them in to a linkedlist
	LinkedList list;
	list.length = 0;
	while(fscanf(file, " %d %d %d %d",&track_num,&start_node,&end_node,&max_time)!=EOF){
		Track *t = malloc(sizeof(Track));
		t->track_num = track_num;
		t->start_node = findNode(event,start_node);
		t->end_node = findNode(event,end_node);
		t->max_time = max_time;
		listadd(t, &list);
	}
	//now we build out 2d array to represent the node graph
	event->nodeGraph = (Track***)calloc(event->nodes.length, sizeof(Track**));
	for(int h=0; h<event->nodes.length; h++){
		event->nodeGraph[h] = (Track**)calloc(event->nodes.length,sizeof(Track*));
	}
	for(int i=0; i<event->nodes.length; i++){
		for(int j=0; j<event->nodes.length; j++){
			event->nodeGraph[i][j] = findTrack(i+1,j+1,&list);
		}
	}
	return 1;
}
int loadEntrants(char* file_location, Event *event){
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	event->entrants.length = 0;
	char course;
	Entrant *e = malloc(sizeof(Entrant));
	while(fscanf(file, " %d %c %[^\n]",&e->competitor_num,&course,e->name)!=EOF){
		e->course = findCourse(course, event);
		listadd(e, &event->entrants);
		e = malloc(sizeof(Entrant));
	}
	if(e->name==NULL){
		free(e);
	}
	return 1;
}
