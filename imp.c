#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct Node {
//     int data;
//     struct GraphNode* graphNode;
//     struct Node* next;
// };

struct GraphNode
{
    char username[20];
    char password[20]; // Added password field
    // struct Node* head;
    struct GraphNode **friends;
    int numFriends;
};

struct Graph
{
    int size;
    struct GraphNode **nodes;
};

struct HashMapNode
{
    char username[20];
    char password[20];
    struct HashMapNode *next;
};

struct HashMap
{
    int capacity;
    struct HashMapNode **table;
};

struct HashMap *createHashMap(int capacity)
{
    struct HashMap *hashMap = (struct HashMap *)malloc(sizeof(struct HashMap));
    hashMap->capacity = capacity;
    hashMap->table = (struct HashMapNode **)malloc(capacity * sizeof(struct HashMapNode *));

    for (int i = 0; i < capacity; i++)
    {
        hashMap->table[i] = NULL;
    }

    return hashMap;
}

int hashFunction(struct HashMap *hashMap, const char *key)
{
    int sum = 0;
    int len = strlen(key);
    for (int i = 0; i < len; i++)
    {
        sum += key[i];
    }

    return sum % hashMap->capacity;
}

void insert(struct HashMap *hashMap, const char *key, const char *value)
{
    int index = hashFunction(hashMap, key);

    struct HashMapNode *newNode = (struct HashMapNode *)malloc(sizeof(struct HashMapNode));
    strcpy(newNode->username, key);
    strcpy(newNode->password, value);
    newNode->next = hashMap->table[index];
    hashMap->table[index] = newNode;
}

const char *get(struct HashMap *hashMap, const char *key)
{
    int index = hashFunction(hashMap, key);

    struct HashMapNode *current = hashMap->table[index];
    while (current != NULL)
    {
        if (strcmp(current->username, key) == 0)
        {
            return current->password;
        }
        current = current->next;
    }

    return NULL;
}

void createGraph(struct Graph *graph)
{
    graph->size = 0;
    graph->nodes = NULL;
}

void addGraphNode(struct Graph *graph, struct HashMap *hashMap, const char *username, char *password)
{
    int index = graph->size;
    graph->nodes = (struct GraphNode **)realloc(graph->nodes, (index + 1) * sizeof(struct GraphNode *));

    struct GraphNode *newNode = (struct GraphNode *)malloc(sizeof(struct GraphNode));
    strcpy(newNode->username, username);
    strcpy(newNode->password, "");
    // newNode->head = NULL;
    newNode->friends = NULL;
    newNode->numFriends = 0;

    graph->nodes[index] = newNode;
    graph->size++;

    // Add the username to the hash map without a password initially
    insert(hashMap, username, password);
}

// void addNode(struct GraphNode* graphNode, int data) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->data = data;
//     newNode->graphNode = graphNode;
//     newNode->next = NULL;

//     if (graphNode->head == NULL) {
//         graphNode->head = newNode;
//     } else {
//         struct Node* current = graphNode->head;
//         while (current->next != NULL) {
//             current = current->next;
//         }
//         current->next = newNode;
//     }
// }

void addFriend(struct GraphNode *graphNode, struct GraphNode *friendNode)
{
    graphNode->friends = (struct GraphNode **)realloc(graphNode->friends, (graphNode->numFriends + 1) * sizeof(struct GraphNode *));
    graphNode->friends[graphNode->numFriends] = friendNode;
    graphNode->numFriends++;
}

void displayGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        printf("Username for node %d: %s\n", i, graph->nodes[i]->username);

        // struct Node* current = graph->nodes[i]->head;
        // printf("Elements: ");
        // while (current != NULL) {
        //     printf("%d ", current->data);
        //     current = current->next;
        // }

        printf("\nFriends: ");
        for (int j = 0; j < graph->nodes[i]->numFriends; j++)
        {
            printf("%s ", graph->nodes[i]->friends[j]->username);
        }

        printf("\n\n");
    }
}

int searchGraphNode(struct Graph *graph, const char *username)
{
    for (int i = 0; i < graph->size; i++)
    {
        if (strcmp(graph->nodes[i]->username, username) == 0)
        {
            return i;
        }
    }

    return -1;
}

void showAvailableFriends(struct Graph *graph, const char *username)
{
    int index = searchGraphNode(graph, username);
    if (index == -1)
    {
        printf("Graph node '%s' does not exist.\n", username);
        return;
    }

    printf("Available friends for graph node '%s':\n", username);

    for (int i = 0; i < graph->size; i++)
    {
        if (i != index)
        {
            int alreadyFriend = 0;
            for (int j = 0; j < graph->nodes[index]->numFriends; j++)
            {
                if (graph->nodes[index]->friends[j] == graph->nodes[i])
                {
                    alreadyFriend = 1;
                    break;
                }
            }

            if (!alreadyFriend)
            {
                printf("- %s\n", graph->nodes[i]->username);
            }
        }
    }
}

void freeGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->size; i++)
    {
        // struct Node* current = graph->nodes[i]->head;
        // while (current != NULL) {
        //     struct Node* temp = current;
        //     current = current->next;
        //     free(temp);
        // }
        free(graph->nodes[i]->friends);
        free(graph->nodes[i]);
    }
    free(graph->nodes);
}

void freeHashMap(struct HashMap *hashMap)
{
    for (int i = 0; i < hashMap->capacity; i++)
    {
        struct HashMapNode *current = hashMap->table[i];
        while (current != NULL)
        {
            struct HashMapNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashMap->table);
    free(hashMap);
}

int main()
{
    struct Graph graph;
    struct HashMap *hashMap = createHashMap(100);

    createGraph(&graph);

    int choice;
    while (choice != 10)
    {
        printf("\n--- Graph Menu ---\n");
        printf("1. SignUp\n");
        printf("2. Login\n");
        printf("3. Search Index of Username\n");
        printf("4. Display Graph\n");
        printf("5. Exit\n");

        // printf("3. Add Friend to Graph Node\n");
        // printf("6. Show Available Friends\n");
        // printf("7. Set Password\n");
        // printf("9. Logout\n");

        // printf("2. Add Node to Graph\n");
        // printf("5. Search Graph Node\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int loggedIn = 0;
        switch (choice)
        {
        case 1:
        {
            char username[20];
            char password[20];
            printf("Enter the username for the graph node: ");
            scanf("%s", username);
            printf("Enter the password for the graph node: ");
            scanf("%s", password);

            addGraphNode(&graph, hashMap, username, password);

            printf("Graph node '%s' added successfully.\n", username);
            break;
        }
        
        case 2:
        {
            char username[20];
            printf("Enter your username: ");
            scanf("%s", username);

            const char *password = get(hashMap, username);
            if (password == NULL)
            {
                printf("User '%s' does not exist.\n", username);
                break;
            }

            char enteredPassword[20];
            printf("Enter your password: ");
            scanf("%s", enteredPassword);

            if (strcmp(password, enteredPassword) == 0)
            {
                printf("Login successful. Welcome, %s!\n", username);
                loggedIn = 1;
            }
            else
            {
                loggedIn = 0;
                printf("Invalid password. Login failed.\n");
            }
            while (loggedIn == 1)
            {
                int ch = 0;
                printf("1. Add Friend to Graph Node\n");
                printf("2. Show Available Friends\n");
                printf("3. Set Password\n");
                printf("4. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);
                switch (ch)
                {
                case 1:
                {
                    char username[20];
                    printf("Enter the username of the graph node: ");
                    scanf("%s", username);

                    int index = searchGraphNode(&graph, username);
                    if (index == -1)
                    {
                        printf("Graph node '%s' does not exist.\n", username);
                        break;
                    }

                    char friendUsername[20];
                    printf("Enter the username of the friend node: ");
                    scanf("%s", friendUsername);

                    int friendIndex = searchGraphNode(&graph, friendUsername);
                    if (friendIndex == -1)
                    {
                        printf("Friend node '%s' does not exist.\n", friendUsername);
                        break;
                    }

                    addFriend(graph.nodes[index], graph.nodes[friendIndex]);

                    printf("Friend '%s' added to graph node '%s' successfully.\n", friendUsername, username);
                    break;
                }
                case 2:
                {
                    char username[20];
                    printf("Enter the username to show available friends: ");
                    scanf("%s", username);

                    showAvailableFriends(&graph, username);
                    break;
                }
                case 3:
                {
                    char username[20];
                    printf("Enter the username to set password: ");
                    scanf("%s", username);

                    const char *existingPassword = get(hashMap, username);
                    if (existingPassword != NULL)
                    {
                        printf("User '%s' already has a password set.\n", username);
                        break;
                    }

                    char password[20];
                    printf("Enter the new password: ");
                    scanf("%s", password);

                    insert(hashMap, username, password);
                    printf("Password set successfully for user '%s'\n", username);
                    break;
                }
                case 4:
                {
                    loggedIn=0;
                    printf("Logout successful. Goodbye!\n");
                    break;
                }

                default:
                    break;
                }
                /* code */
            }

            // char username[20];
            // printf("Enter the username of the graph node: ");
            // scanf("%s", username);

            // int index = searchGraphNode(&graph, username);
            // if (index == -1) {
            //     printf("Graph node '%s' does not exist.\n", username);
            //     break;
            // }

            // int data;
            // printf("Enter the data for the node: ");
            // scanf("%d", &data);

            // addNode(graph.nodes[index], data);

            // printf("Node with data '%d' added to graph node '%s' successfully.\n", data, username);
            break;
        }
        
        case 3:
        {
            char username[20];
            printf("Enter the username to search: ");
            scanf("%s", username);

            int index = searchGraphNode(&graph, username);
            if (index != -1)
            {
                printf("Graph node '%s' found at index %d\n", username, index);
            }
            else
            {
                printf("Graph node '%s' not found\n", username);
            }
            break;
        }
        
        case 4:
        {
            printf("\n--- Graph ---\n");
            displayGraph(&graph);
            break;
        }
        
        case 5:
        {
            freeGraph(&graph);
            freeHashMap(hashMap);
            exit(0);
        }
      
        default:
        {
            printf("Invalid choice. Please try again.\n");
            break;
        }
        }
    }

    return 0;
}


// same username should not be taken
// improve case2->case3 to be able to change password
