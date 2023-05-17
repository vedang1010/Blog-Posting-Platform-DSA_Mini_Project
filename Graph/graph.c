#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000

typedef struct Graph {
    int vertices;
    graphNode** adjacencyMatrix;
} Graph;

typedef struct graphNode{
    char* username;
    int userCode;
    int followers;
    int following;
    
}graphNode;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyMatrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }

    return graph;
}

void addEdge(Graph* graph, int source, int destination) {
    if (source >= 0 && source < graph->vertices && destination >= 0 && destination < graph->vertices) {
        graph->adjacencyMatrix[source][destination] = 1;
        graph->adjacencyMatrix[destination][source] = 1;
    }
}

void displayGraph(Graph* graph) {
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int vertices = 10;
    Graph* graph = createGraph(vertices);

    // Adding edges to create a disconnected graph
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    displayGraph(graph);

    return 0;
}
