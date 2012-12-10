#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "functions.h"
int main(int argc, char *argv[]){
	Event event;
	char *folder_name = NULL;
	char *times_name = NULL;
	for(int i=0; i<argc; i++){
		switch(i){
		case 1:
			folder_name = argv[i];
			break;
		case 2:
			times_name = argv[i];
			break;
		default:
			printf("Argument given %s\n",argv[i]);
			break;
		}
	}
	if(folder_name==NULL){
		printf("Enter folder name for event: ");
		folder_name = calloc(80,sizeof(char));
		scanf(" %s",folder_name);
	}
	printf("folder name is %s\n",folder_name);
	if(loadFiles(folder_name, &event)<1){
		printf("Load failed, Terminating\n");
		return -1;
	}
	//printTracks(&event);
	//printCourses(&event);


	if(times_name==NULL){
		printf("Enter file name for event times: ");
		times_name = calloc(80,sizeof(char));
		scanf(" %s",times_name);
	}
	loadTimes(times_name, &event);
	//printEntrants(&event);
	char in = 'Q';
	char name[50];
	Entrant *e;
	do{
		printOptions();
		scanf(" %c",&in);
		switch(in){
		case '1':
			printf("Enter entrant name: ");
			scanf(" %[^\n]", name);
			e = findEntrantByName(name,&event);
			if(e==NULL){
				printf("Entrant not found\n");
				break;
			}
			printStatus(e);
			break;
		case '2':
			printNotStarted(&event);
			break;
		case '3':
			printStarted(&event);
			break;
		case '4':
			printFinished(&event);
			break;
		case '5':
			printf("Enter competitor name: ");
			scanf(" %[^\n]",name);
			int h;
			int m;
			printf("Enter time (HH:MM): ");
			scanf(" %d:%d", &h, &m);
			printf("Enter checkpoint number: ");
			int checkpoint;
			scanf(" %d", &checkpoint);
			e = findEntrantByName(name, &event);
			if(e==NULL){
				printf("Entrant not found\n");
				break;
			}
			checkin(&event, checkpoint, findEntrantByName(name, &event), h, m);
			break;
		case '6':
			printf("Enter file name for event times: ");
			times_name = calloc(80,sizeof(char));
			scanf(" %s",times_name);
			loadTimes(times_name, &event);
			break;
		}
	}while(in!='Q');
}
void printOptions(){
	printf("Enter an option:\n");
	printf("1 - Query location of entrant\n");
	printf("2 - Print competitors who have not started\n");
	printf("3 - Print competitors who are on courses\n");
	printf("4 - Print finished\n");
	printf("5 - Enter time checkpoint\n");
	printf("6 - Load times from file\n");
	printf("Q - Quit\n");
}
