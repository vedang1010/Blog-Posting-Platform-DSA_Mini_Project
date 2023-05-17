#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a node in the linked list
typedef struct Node {
    char username[50];
    char password[50];
    struct Node* next;
} Node;

// Function to create a new node with the given username and password
Node* createNode(char* username, char* password) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    newNode->next = NULL;
    return newNode;
}

// Function to add a new node to the end of the linked list
void addNode(Node** head, char* username, char* password) {
    Node* newNode = createNode(username, password);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to check if a given username already exists in the linked list
int usernameExists(Node* head, char* username) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Function to create a new user account by adding a node to the linked list
void createUserAccount(Node** head) {
    char username[50];
    char password[50];
    printf("Enter a username: ");
    scanf("%s", username);
    if (usernameExists(*head, username)) {
        printf("Username already exists. Please try again.\n");
        return;
    }
    printf("Enter a password: ");
    scanf("%s", password);
    addNode(head, username, password);
    printf("Account created successfully!\n");
}

// Function to print all nodes in the linked list
void printList(Node* head) {
    Node* current = head;
    printf("User accounts:\n");
    while (current != NULL) {
        printf("Username: %s\n", current->username);
        printf("Password: %s\n", current->password);
        printf("\n");
        current = current->next;
    }
}

// Main function to test the linked list
int main() {
    Node* head = NULL;
    int choice = 0;
    while (choice != 3) {
        printf("1. Create user account\n");
        printf("2. View user accounts\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                createUserAccount(&head);
                break;
            case 2:
                printList(head);
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

