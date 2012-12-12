#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "functions.h"
int load_files(char* folder_name, Event *event){
	printf("%s\n", folder_name);
	int status;
	char *name;
	//load event
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_NAME);
	status = load_event(name, event);
	free(name);
	if(status<1){ return status; }
	//load nodes
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_NODES);
	status = load_nodes(name, event);
	free(name);
	if(status<1){ return status; }
	//load tracks
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_TRACKS);
	status = load_track(name,event);
	free(name);
	if(status<1){ return status; }

	//load courses
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_COURSES);
	status = load_courses(name, event);
	free(name);
	if(status<1){ return status; }

	//load entrants
	name = calloc(50,sizeof(char));
	strcat(name,folder_name);
	strcat(name,"/");
	strcat(name,E_ENTRANTS);
	status = load_entrants(name, event);
	free(name);
	if(status<1){ return status; }

	return 1;
}
int load_event(char* file_location, Event *event){
	FILE *file = fopen(file_location,"r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	int h;
	int m;
	fscanf(file, " %[^\n] %[^\n] %d:%d",event->name,event->date,&h,&m);
	fclose(file);
	event->current_time = h*60+m;
	return 1;
}
int load_nodes(char* file_location, Event* event){
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
	fclose(file);
	return 1;
}
int load_courses(char* file_location, Event* event){
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
				c->tracks[i-1] = find_track_from_event(event,last_node,node_ident);
			}
			last_node = node_ident;
		}
		listadd(c, &event->courses);
	}
	fclose(file);
	return 1;
}
int load_track(char* file_location, Event* event){
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
		t->start_node = find_node(event,start_node);
		t->end_node = find_node(event,end_node);
		t->max_time = max_time;
		listadd(t, &list);
	}
	//now we build out 2d array to represent the node graph
	event->node_graph = (Track***)calloc(event->nodes.length, sizeof(Track**));
	for(int h=0; h<event->nodes.length; h++){
		event->node_graph[h] = (Track**)calloc(event->nodes.length,sizeof(Track*));
	}
	for(int i=0; i<event->nodes.length; i++){
		for(int j=0; j<event->nodes.length; j++){
			event->node_graph[i][j] = find_track(i+1,j+1,&list);
		}
	}
	fclose(file);
	return 1;
}
int load_entrants(char* file_location, Event *event){
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	event->entrants.length = 0;
	char course;
	Entrant *e = malloc(sizeof(Entrant));
	while(fscanf(file, " %d %c %[^\n]",&e->competitor_num,&course,e->name)!=EOF){
		e->course = find_course(course, event);
		listadd(e, &event->entrants);
		e->visited.length = 0;
		e->current_time = 0;
		e = malloc(sizeof(Entrant));
	}
	if(e->name==NULL){
		free(e);
	}
	fclose(file);
	return 1;
}
int load_times(char* file_location, Event *event){
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	char type;
	int checkpoint;
	int competitor;
	int time_A;
	int time_B;
	while(fscanf(file, " %c %d %d %d:%d",&type,&checkpoint,&competitor,&time_A,&time_B)!=EOF){
		if(type=='T'){
			checkin(event, checkpoint, find_entrant(competitor, event), time_A, time_B);
		}
	}
	fclose(file);
	return 1;
}
