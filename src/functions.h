#ifndef FUNCTIONS
#define FUNCTIONS
int loadFiles(char *folder_name);
int loadEvent(char* file_name, Event *event);
int loadNodes(char* file_name, Event* e);
int loadTrack(char* file_name, Event* event);
void printNode(Node *n);
int loadCourses(char* file_location, Event* event);
Node *findNode(Event *event, int ident);
Track *findTrack(int start_node, int end_node, Track *tracks, int num_tracks);
void printTracks(Event *event);
#endif
