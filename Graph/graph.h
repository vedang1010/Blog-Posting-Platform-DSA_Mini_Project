// Structure definition for a node in the linked list
#include <stdio.h>

typedef struct NodeLL {
    int data;
    char username[20];
    struct GraphNode* graphNode;
    struct NodeLL* next;
}NodeLL;
// Structure definition for a graph
typedef struct Graph
{
    int size;
    struct GraphNode **nodes;
} Graph;
// Structure definition for a graph node
typedef struct GraphNode {
    char username[20];
    int friends;
    FILE **fp;
    struct NodeLL* head;
}GraphNode;
int friends(NodeLL *head);
void addGraphNode(Graph *graph, const char *username);
void addNode(GraphNode *graphNode, int data);
void displayGraph(Graph *graph);
int searchGraphNode(Graph *graph, const char *username);
int friends(NodeLL *head);
