#ifndef FUNCTIONS
#define FUNCTIONS
int loadFiles(char *folder_name);
int loadEvent(char* file_name, Event *event);
int loadNodes(char* file_name, Event* e);
int loadTrack(char* file_name, Event* event);
void printNode(Node *n);
int loadCourses(char* file_location, Event* event);
Node findNode(Event *event, int ident);
#endif
