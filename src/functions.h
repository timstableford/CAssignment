#ifndef FUNCTIONS
#define FUNCTIONS
#include "data.h"
int loadFiles(char *folder_name, Event *event);
int loadEvent(char* file_name, Event *event);
int loadNodes(char* file_name, Event* e);
int loadTrack(char* file_name, Event* event);
int loadCourses(char* file_location, Event* event);
int loadEntrants(char* file_location, Event *event);
int loadTimes(char* file_location, Event *event);

Node *findNode(Event *event, int ident);
Track *findTrack(int start_node, int end_node, LinkedList *list);
Track *findTrackFromEvent(Event *event, int start_node, int end_node);
Course *findCourse(char identifier, Event *event);
Entrant *findEntrant(int competitor_num, Event *event);
Entrant *findEntrantByName(char *name, Event *event);

void listadd(void *data, LinkedList *list);
void listremove(LinkedList *list, ListNode *node);

void checkin(Event *event, int node_ident, Entrant *entrant, int h, int m);

void printNode(Node *n);
void printTracks(Event *event);
void printCourses(Event *event);
void printEntrants(Event *event);
void printStatus(Entrant *entrant);
void printNotStarted(Event *event);
void printStarted(Event *event);
void printFinished(Event *event);
void printOptions();
#endif
