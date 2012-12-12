#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "functions.h"
int main(int argc, char *argv[]){
	Event event;
	int status;
	char *file_name = malloc(sizeof(char)*80);
	/* If a folder name is given thne load thd defaults in that folder,
	 * if not prompt for the locations of each of the inidivual files.
	 */
	if(argc>1){
		file_name = argv[1];
		load_files(file_name, &event);
	}else{
		printf("Enter main file for event: ");
		scanf(" %s",file_name);
		status = load_event(file_name, &event);
		if(status<0){ return status; }

		printf("Enter file containing nodes: ");
		scanf(" %s", file_name);
		status = load_nodes(file_name, &event);
		if(status<0){ return status; }

		printf("Enter file containing tracks: ");
		scanf(" %s", file_name);
		status = load_track(file_name, &event);
		if(status<0){ return status; }

		printf("Enter file containing courses: ");
		scanf(" %s", file_name);
		status = load_courses(file_name, &event);
		if(status<0){ return status; }

		printf("Enter file containing entrants: ");
		scanf(" %s", file_name);
		status = load_entrants(file_name, &event);
		if(status<0){ return status; }
	}
	int in = 0;
	Entrant *e;
	/*
	 * When everything is loaded print the menu, wait for input,
	 * process, and the loop unless input is 0.
	 */
	do{
		print_options();
		scanf(" %d",&in);
		switch(in){
		case 1:
			printf("Enter entrant name: ");
			scanf(" %[^\n]", file_name);
			e = find_entrant_by_name(file_name,&event);
			if(e==NULL){
				printf("Entrant not found\n");
				break;
			}
			print_status(&event, e);
			break;
		case 2:
			print_not_started(&event);
			break;
		case 3:
			print_started(&event);
			break;
		case 4:
			print_finished(&event);
			break;
		case 5:
			print_entrants(&event);
			break;
		case 6:
			printf("Enter competitor name: ");
			scanf(" %[^\n]",file_name);
			printf("Enter time (HH:MM): ");
			int hour; int min;
			scanf(" %d:%d", &hour, &min);
			printf("Enter checkpoint number: ");
			int checkpoint;
			scanf(" %d", &checkpoint);
			e = find_entrant_by_name(file_name, &event);
			if(e==NULL){
				printf("Entrant not found\n");
			}else{
				checkin(&event, checkpoint, e, hour, min);
			}
			break;
		case 7:
			printf("Enter file name for event times: ");
			scanf(" %s",file_name);
			load_times(file_name, &event);
			break;
		case 8:
			print_courses(&event);
			break;
		case 9:
			print_results(&event);
			break;
		}
	}while(in!=0);
}
void print_options(){
	printf("Enter an option:\n");
	printf("1 - Query location of entrant\n");
	printf("2 - Print competitors who have not started\n");
	printf("3 - Print competitors who are on courses\n");
	printf("4 - Print finished\n");
	printf("5 - Print all competitors\n");
	printf("6 - Enter time checkpoint\n");
	printf("7 - Load times from file\n");
	printf("8 - Print Courses\n");
	printf("9 - Print results list\n");
	printf("0 - Quit\n");
}
