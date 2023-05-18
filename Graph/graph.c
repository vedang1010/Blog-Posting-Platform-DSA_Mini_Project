#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"



// Function to create the graph
void createGraph(Graph *graph)
{
    graph->size = 0;
    graph->nodes = NULL;
}

// Function to add a graph node to the array
void addGraphNode(Graph *graph, const char *username)
{
    int index = graph->size;
    graph->nodes = (GraphNode **)realloc(graph->nodes, (index + 1) * sizeof(GraphNode *));

    // Create a new graph node
    GraphNode *newNode = (GraphNode *)malloc(sizeof(GraphNode));
    strcpy(newNode->username, username);
    newNode->head = NULL;
    newNode->friends = friends(newNode->head);
    newNode->fp = NULL;

    // Add the new graph node to the array
    graph->nodes[index] = newNode;
    graph->size++;
}

// Function to add a node to the linked list of a graph node
void addNode(GraphNode *graphNode, int data)
{
    // Create a new node
    NodeLL *newNode = (NodeLL *)malloc(sizeof(NodeLL));
    newNode->data = data;
    newNode->graphNode = graphNode;
    newNode->next = NULL;

    // Set the head pointer if it's the first node
    if (graphNode->head == NULL)
    {
        graphNode->head = newNode;
    }
    else
    {
        NodeLL *current = graphNode->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display the graph
void displayGraph(Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        printf("Username for node %d: %s\n", i, graph->nodes[i]->username);

        // Print the linked list elements
        NodeLL *current = graph->nodes[i]->head;
        printf("Elements: ");
        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

// Function to search for a graph node in the graph
int searchGraphNode(Graph *graph, const char *username)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (strcmp(graph->nodes[i]->username, username) == 0)
        {
            return i; // Node found, return its index
        }
    }

    return -1; // Node not found
}
int friends(NodeLL *head)
{
    int n = 0;
    NodeLL *temp = head;
    if (temp == NULL)
    {
        return 0;
        /* code */
    }

    while (temp != NULL)
    {
        n++;
        temp = temp->next;
        /* code */
    }
    return n;
}

int main()
{
    Graph *graph;

    createGraph(graph);

    int option;
    do
    {
        printf("\n1. Add a graph node\n");
        printf("2. Add a node to a graph node\n");
        printf("3. Display the graph\n");
        printf("4. Search for a graph node\n");
        printf("5. See no. of friends\n");
        printf("0. Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            char username[20];
            printf("Enter the username for the graph node: ");
            scanf("%s", username);
            addGraphNode(graph, username);
            break;
        }
        case 2:
        {
            if (graph->size == 0)
            {
                printf("No graph nodes available. Please add a graph node first.\n");
            }
            else
            {
                int nodeIndex;
                printf("Enter the index of the graph node: ");
                scanf("%d", &nodeIndex);
                if (nodeIndex < 0 || nodeIndex >= graph->size)
                {
                    printf("Invalid graph node index.\n");
                }
                else
                {
                    int data;
                    printf("Enter the number to add to the graph node: ");
                    scanf("%d", &data);
                    addNode(graph->nodes[nodeIndex], data);
                }
            }
            break;
        }
        case 3:
        {
            displayGraph(graph);
            break;
        }
        case 4:
        {
            char searchUsername[20];
            printf("Enter the username to search: ");
            scanf("%s", searchUsername);

            int nodeIndex = searchGraphNode(graph, searchUsername);
            if (nodeIndex != -1)
            {
                printf("Node with username '%s' found at index %d\n", searchUsername, nodeIndex);
            }
            else
            {
                printf("Node with username '%s' not found\n", searchUsername);
            }
            break;
        }
        case 5:
        {
            if (graph->size == 0)
            {
                printf("No graph nodes available. Please add a graph node first.\n");
            }
            else
            {
                int nodeIndex;
                printf("Enter the index of the graph node: ");
                scanf("%d", &nodeIndex);
                if (nodeIndex < 0 || nodeIndex >= graph->size)
                {
                    printf("Invalid graph node index.\n");
                }
                else
                {
                    int friend = friends(graph->nodes[nodeIndex]->head);
                    printf("He has %d friends\n", friend);
                    // printf("Enter the number to add to the graph node: ");
                    // scanf("%d", &data);
                    // addNode(graph->nodes[nodeIndex], data);
                }
            }
            break;
        }
        case 0:
        {
            printf("Exiting...\n");
            break;
        }
        default:
        {
            printf("Invalid option. Please try again.\n");
            break;
        }
        }
    } while (option != 0);

    // Free the memory allocated for the graph
    for (int i = 0; i < graph->size; i++)
    {
        NodeLL *current = graph->nodes[i]->head;
        while (current != NULL)
        {
            NodeLL *temp = current;
            current = current->next;
            free(temp);
        }
        free(graph->nodes[i]);
    }
    free(graph->nodes);

    return 0;
}
