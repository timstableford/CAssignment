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
	int current_node = 0;
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
		current_node++;
	}
	return 1;
}
int loadCourses(char* file_location, Event* event){
	//courses contain tracks
	int current_course = 0;
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	event->courses = malloc(0);
	char ident;
	int num_nodes;
	while(fscanf(file, " %c %d",&ident,&num_nodes)!=EOF){
		event->courses = realloc(event->courses, sizeof(Course)*(current_course+1));
		event->courses[current_course].identifier = ident;
		int last_node = -1;
		event->courses[current_course].num_tracks = num_nodes-1;
		event->courses[current_course].tracks = calloc(num_nodes-1,sizeof(Track*));
		for(int i=0; i<num_nodes; i++){
			int node_ident;
			fscanf(file, " %d",&node_ident);
			if(last_node>=0){
				event->courses[current_course].tracks[i-1] = findTrackFromEvent(event,last_node,node_ident);
			}
			last_node = node_ident;
		}
		current_course++;
	}
	event->num_courses = current_course;
	return 1;
}
int loadTrack(char* file_location, Event* event){
	//tracks are the time between 2 nodes
	FILE *file = fopen(file_location, "r");
	if(file==NULL){
		printf("File %s not found\n",file_location);
		return -1;
	}
	int current_track = 0;
	Track* tracks = malloc(0);
	int track_num;
	int start_node;
	int end_node;
	int max_time;
	//first we'll scan them in to a 1d array
	while(fscanf(file, " %d %d %d %d",&track_num,&start_node,&end_node,&max_time)!=EOF){
		tracks = realloc(tracks, sizeof(Track)*(current_track+1));
		tracks[current_track].track_num = track_num;
		tracks[current_track].start_node = findNode(event,start_node);
		tracks[current_track].end_node = findNode(event,end_node);
		tracks[current_track].max_time = max_time;
		current_track++;
	}
	//now we build out 2d array to represent the node graph
	event->nodeGraph = (Track***)calloc(event->nodes.length, sizeof(Track**));
	for(int h=0; h<event->nodes.length; h++){
		event->nodeGraph[h] = (Track**)calloc(event->nodes.length,sizeof(Track*));
	}
	for(int i=0; i<event->nodes.length; i++){
		for(int j=0; j<event->nodes.length; j++){
			event->nodeGraph[i][j] = findTrack(i+1,j+1,tracks, current_track);
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
	event->num_entrants = 0;
	event->entrants = malloc(sizeof(Entrant));
	char course;
	int competitor_num;
	char *name = malloc(sizeof(char)*50);
	while(fscanf(file, " %d %c %[^\n]",&competitor_num,&course,name)!=EOF){
		event->num_entrants = event->num_entrants + 1;
		event->entrants = realloc(event->entrants, sizeof(Entrant)*(event->num_entrants));
		event->entrants[event->num_entrants-1].course = findCourse(course, event);
		event->entrants[event->num_entrants-1].competitor_num = competitor_num;
		event->entrants[event->num_entrants-1].name = name;
	}
	return 1;
}
