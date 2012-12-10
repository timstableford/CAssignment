#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "functions.h"
int main(int argc, char *argv[]){
	Event event;
	char *folder_name = NULL;
	for(int i=0; i<argc; i++){
		switch(i){
		case 1:
			folder_name = argv[i];
			break;
		default:
			printf("Argument given %s\n",argv[i]);
			break;
		}
	}
	if(folder_name==NULL){
		folder_name = malloc(80*sizeof(char));
		printf("Enter folder name for event: ");
		scanf(" %s",folder_name);
		printf("folder name is %s\n",folder_name);
	}
	if(load_files(folder_name, &event)<1){
		printf("Load failed, Terminating\n");
		return -1;
	}
	int in = 0;
	char name[80];
	Entrant *e;
	do{
		print_options();
		scanf(" %d",&in);
		switch(in){
		case 1:
			printf("Enter entrant name: ");
			scanf(" %[^\n]", name);
			e = find_entrant_by_name(name,&event);
			if(e==NULL){
				printf("Entrant not found\n");
				break;
			}
			print_status(e);
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
			scanf(" %[^\n]",name);
			printf("Enter time (HH:MM): ");
			int hour; int min;
			scanf(" %d:%d", &hour, &min);
			printf("Enter checkpoint number: ");
			int checkpoint;
			scanf(" %d", &checkpoint);
			e = find_entrant_by_name(name, &event);
			if(e==NULL){
				printf("Entrant not found\n");
			}else{
				checkin(&event, checkpoint, e, hour, min);
			}
			break;
		case 7:
			printf("Enter file name for event times: ");
			scanf(" %s",name);
			load_times(name, &event);
			break;
		case 8:
			print_courses(&event);
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
	printf("0 - Quit\n");
}
