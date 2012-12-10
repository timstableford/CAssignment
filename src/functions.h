#ifndef FUNCTIONS
#define FUNCTIONS
#include "data.h"
int load_files(char *folder_name, Event *event);
int load_event(char* file_name, Event *event);
int load_nodes(char* file_name, Event* e);
int load_track(char* file_name, Event* event);
int load_courses(char* file_location, Event* event);
int load_entrants(char* file_location, Event *event);
int load_times(char* file_location, Event *event);

Node *find_node(Event *event, int ident);
Track *find_track(int start_node, int end_node, LinkedList *list);
Track *find_track_from_event(Event *event, int start_node, int end_node);
Course *find_course(char identifier, Event *event);
Entrant *find_entrant(int competitor_num, Event *event);
Entrant *find_entrant_by_name(char *name, Event *event);
int checkpoints_in_course(Course *course);
int has_finished(Entrant *entrant);

void listadd(void *data, LinkedList *list);
void listremove(LinkedList *list, ListNode *node);

void checkin(Event *event, int node_ident, Entrant *entrant, int h, int m);

void print_node(Node *n);
void print_courses(Event *event);
void print_entrants(Event *event);
void print_status(Entrant *entrant);
void print_not_started(Event *event);
void print_started(Event *event);
void print_finished(Event *event);
void print_options();
#endif
