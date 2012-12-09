#include <stdio.h>
#include <stdlib.h>
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
	printTracks(&event);
	printCourses(&event);


	if(times_name==NULL){
		printf("Enter file name for event times: ");
		times_name = calloc(80,sizeof(char));
		scanf(" %s",times_name);
	}
	loadTimes(times_name, &event);
	printEntrants(&event);
	printOptions();
	char in = 'Q';
	do{
		printOptions();
		scanf(" %c",&in);
		switch(in){
		case '1':
			printf("Enter entrant name: ");
			char name[50];
			scanf(" %[^\n]", &name);
			Entrant *e = findEntrantByName(&name,&event);
			if(e==NULL){
				printf("Entrant not found\n");
				break;
			}
			printStatus(e);
			break;
		}
	}while(in!='Q');
}
void printOptions(){
	printf("Enter an option:\n");
	printf("1 - Query location of entrant\n");

	printf("Q - Quit\n");
}
