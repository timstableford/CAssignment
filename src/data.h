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

#define NONE 0
#define MEDICAL 1
#define OFFCOURSE 2

typedef struct ListNode{
	void *data;
	struct ListNode *next;
	struct ListNode *previous;
}ListNode;

typedef struct{
	ListNode *head;
	ListNode *tail;
	int length;
}LinkedList;

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
	Course *course;
	LinkedList visited;
	int start_time;
	int current_time;
	int excluded;
	int medical;
}Entrant;

typedef struct{
	char name[50];
	char date[50];
	int current_time;
	LinkedList nodes;
	LinkedList entrants;
	LinkedList courses;
	Track ***node_graph;
}Event;

#endif
