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
	char visited;
}Node;

typedef struct{
	char identifier;
	int num_nodes;
	Node *nodes;
}Course;

typedef struct{
	int track_num;
	int start_node;
	int end_node;
	int max_time;
	Course course;
}Track;

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
	Track *track;
	Entrant *entrant;
	Course *courses;
	int num_courses;
}Event;

#endif
