#ifndef FUNCTIONS
#define FUNCTIONS
#include "data.h"
int loadFiles(char *folder_name, Event *event);
int loadEvent(char* file_name, Event *event);
int loadNodes(char* file_name, Event* e);
int loadTrack(char* file_name, Event* event);
void printNode(Node *n);
int loadCourses(char* file_location, Event* event);
Node *findNode(Event *event, int ident);
Track *findTrack(int start_node, int end_node, Track *tracks, int num_tracks);
void printTracks(Event *event);
Track *findTrackFromEvent(Event *event, int start_node, int end_node);
void printCourses(Event *event);
Course *findCourse(char identifier, Event *event);
int loadEntrants(char* file_location, Event *event);
void listadd(void *data, LinkedList *list);
void listremove(LinkedList *list, ListNode *node);
#endif
