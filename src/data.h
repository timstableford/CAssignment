#ifndef DATA
#define DATA

#define E_NAME "name.txt"
#define E_COURSES "courses.txt"
#define E_TRACKS "tracks.txt"
#define E_ENTRANTS "entrants.txt"
#define E_NODES "nodes.txt"

#define CP 0
#define MC 1
#define JN 2
typedef int NodeType;
typedef struct{
	int identifier;
	NodeType type;
}Node;

typedef struct{
	int track_num;
	Node* start_node;
	Node* end_node;
	int max_time;
}Track;

typedef struct{
	char identifier;
	int num_tracks;
	Track **tracks;
}Course;

typedef struct{
	int competitor_num;
	char name[50];
	Course course;
}Entrant;

typedef struct{
	char name[50];
	char date[50];
	char time[50];
	Node *nodes;
	int num_nodes;
	Entrant *entrant;
	Course *courses;
	int num_courses;
	Track ***nodeGraph;
}Event;

#endif
