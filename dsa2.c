#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#define DT_REG 8
#define MAX_USERS 1000
#define MAX_FRIENDS 100
#define MAX_INTERESTS 120
// Structure to represent a Post
struct Post
{
    // char content[100];
    FILE *fp;
    struct Post *next;
};

// Structure to represent a User
struct User
{
    char username[20];
    char password[20];

    struct User **friends_list; // array of pointers of friends
    int num_friends;
    struct Post *posts_list;
    char **interests;
    int num_interests;
};

// Structure to represent the Social Network
struct SocialNetwork
{
    struct User **users_list;
    int num_users;
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

// Function to create a new social network
struct SocialNetwork *createSocialNetwork()
{
    struct SocialNetwork *network = (struct SocialNetwork *)malloc(sizeof(struct SocialNetwork));
    network->users_list = NULL;
    network->num_users = 0;
    return network;
}

// Hashmap functions:-

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
    // newNode->next = NULL;

    hashMap->table[index] = newNode;
}

char *get(struct HashMap *hashMap, const char *key)
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

int usernameExists(struct SocialNetwork *network, const char *username)
{
    for (int i = 0; i < network->num_users; i++)
    {
        if (strcmp(network->users_list[i]->username, username) == 0)
        {
            return 1; // Username already exists
        }
    }

    return 0; // Username does not exist
}

// Function to add a new user to the social network
void addUser(struct SocialNetwork *network, struct HashMap *map, char *username, char *password)
{
    if (network == NULL)
    {
        printf("Error: Social network not found.\n");
        return;
    }

    struct User *newUser = (struct User *)malloc(sizeof(struct User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->friends_list = NULL;
    newUser->num_friends = 0;
    newUser->posts_list = NULL;
    newUser->interests = NULL;
    newUser->num_interests = 0;

    network->users_list = (struct User **)realloc(network->users_list, (network->num_users + 1) * sizeof(struct User *));
    network->users_list[network->num_users] = newUser;
    network->num_users++;
    insert(map, username, password);
    // printf("User '%s' registered successfully.\n", username);
}

// Function to find a user by username
struct User *findUser(struct SocialNetwork *network, char *username)
{
    if (network == NULL)
    {
        printf("Error: Social network not found.\n");
        return NULL;
    }

    int i;
    for (i = 0; i < network->num_users; i++)
    {
        if (strcmp(network->users_list[i]->username, username) == 0)
        {
            return network->users_list[i];
        }
    }

    return NULL;
}

// Function to add a friend to the user's friend list
void addFriend(struct User *user, struct User *friend)
{
    if (user == NULL || friend == NULL)
    {
        printf("Error: Invalid user or friend.\n");
        return;
    }

    // Check if the friend already exists in the user's friend list
    int i;
    for (i = 0; i < user->num_friends; i++)
    {
        if (strcmp(user->friends_list[i]->username, friend->username) == 0)
        {
            printf("User '%s' is already a friend.\n", friend->username);
            return;
        }
    }

    // Add the friend to the user's friend list
    user->friends_list = (struct User **)realloc(user->friends_list, (user->num_friends + 1) * sizeof(struct User *));
    user->friends_list[user->num_friends] = friend;
    user->num_friends++;

    printf("User '%s' is now friends with '%s'.\n", user->username, friend->username);
}

// Function to add a post for the user
void addPost(struct User *user)
{
    const char post[200];
    printf("Write a post:\n");
    scanf(" %[^\n]s", post);
    // Generate the folder path for the user's posts
    char folderPath[100];
    snprintf(folderPath, sizeof(folderPath), "posts/%s", user->username);

// Create the user's posts folder if it doesn't exist
#ifdef _WIN32
    _mkdir("posts");
#else
    mkdir("posts", 0777);
#endif

// Create the user's folder if it doesn't exist
#ifdef _WIN32
    _mkdir(folderPath);
#else
    mkdir(folderPath, 0777);
#endif

    // Generate the file path for the new text post
    char postFilePath[100];
    snprintf(postFilePath, sizeof(postFilePath), "%s/%d.txt", folderPath, num_post(user->posts_list));

    // Open the file in write mode
    FILE *fp = fopen(postFilePath, "w+");
    if (fp == NULL)
    {
        printf("Error creating the text post file.\n");
        return;
    }

    // Write the post content to the file
    fprintf(fp, "%s", post);

    // Close the file
    fclose(fp);

    struct Post *newPost = (struct Post *)malloc(sizeof(struct Post));
    // strcpy(newPost->content, post);
    newPost->fp = fp;
    newPost->next = NULL;

    if (user->posts_list == NULL)
    {
        user->posts_list = newPost;
    }
    else
    {
        struct Post *temp = user->posts_list;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newPost;
    }

    printf("Post added successfully.\n");
}

// Function to show the posts of a user
void showPosts(struct User *user)
{
    if (user == NULL)
    {
        printf("Error: Invalid user.\n");
        return;
    }

    if (num_post(user->posts_list) == 0)
    {
        printf("No posts found for user %s\n", user->username);
    }

    printf("Showing posts of user '%s':\n", user->username);

    for (int i = 0; i < num_post(user->posts_list); i++)
    {
        char filePath[120];
        sprintf(filePath, "posts/%s/%d.txt", user->username, i);

        FILE *file = fopen(filePath, "r");
        if (file == NULL)
        {
            printf("Error accessing post %d for friend: %s\n", i + 1, user->username);
            continue;
        }

        printf("Post %d:\n", i + 1);
        char post[100];
        while (fgets(post, sizeof(post), file) != NULL)
        {
            printf("%s", post);
        }
        printf("\n");

        fclose(file);
    }
}

void resetPassword(struct HashMap *hashMap, const char *key, const char *newPassword)
{
    int index = hashFunction(hashMap, key);

    struct HashMapNode *currentNode = hashMap->table[index];
    while (currentNode != NULL)
    {
        if (strcmp(currentNode->username, key) == 0)
        {
            strcpy(currentNode->password, newPassword);
            printf("Password reset successful.\n");
            return;
        }
        currentNode = currentNode->next;
    }

    printf("Key not found in the hash map.\n");
}

// Add Interests
void addInterest(struct User *user, const char *interest)
{
    char **newInterests = realloc(user->interests, (user->num_interests + 1) * sizeof(char *));
    if (newInterests == NULL)
    {
        printf("Failed to allocate memory for interests.\n");
        return;
    }

    user->interests = newInterests;
    user->interests[user->num_interests] = malloc((strlen(interest) + 1) * sizeof(char));
    if (user->interests[user->num_interests] == NULL)
    {
        printf("Failed to allocate memory for interest string.\n");
        return;
    }

    strcpy(user->interests[user->num_interests], interest);
    user->num_interests++;

    printf("Interest added successfully.\n");
}

void recommendFriends(struct User *user, struct SocialNetwork *social_network)
{
    printf("Friend recommendations for %s based on interests:\n", user->username);

    for (int i = 0; i < social_network->num_users; i++)
    {
        if (strcmp(user->username, social_network->users_list[i]->username) == 0)
        {
            continue;
        }

        int commonInterests = 0;
        for (int j = 0; j < user->num_interests; j++)
        {
            for (int k = 0; k < social_network->users_list[i]->num_interests; k++)
            {
                if (strcmp(user->interests[j], social_network->users_list[i]->interests[k]) == 0)
                {
                    commonInterests++;
                    break;
                }
            }
        }

        if (commonInterests > 0)
        {
            printf("- %s (%d common interests)\n", social_network->users_list[i]->username, commonInterests);
        }
    }
}

void show_interests(struct User *user)
{
    for (int i = 0; i < user->num_interests; i++)
    {
        printf("%s, ", user->interests[i]);
    }
}

// Function to logout the user
void logout(struct User **currentUser)
{
    if (currentUser == NULL || *currentUser == NULL)
    {
        printf("Error: Invalid user.\n");
        return;
    }

    printf("User '%s' logged out successfully.\n", (*currentUser)->username);
    *currentUser = NULL;
}

int num_post(struct Post *head)
{
    struct Post *temp = head;
    if (temp == NULL)
    {
        return 0;
    }
    int count = 1;
    while (temp->next != NULL)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

void displayGraph(struct SocialNetwork *network)
{
    for (int i = 0; i < network->num_users; i++)
    {
        printf("Username for node %d: %s\n", i, network->users_list[i]->username);
        printf("Number of Posts for node %d: %d\n", i, num_post(network->users_list[i]->posts_list));

        printf("\nFriends: ");
        for (int j = 0; j < network->users_list[i]->num_friends; j++)
        {
            printf("%s ", network->users_list[i]->friends_list[j]->username);
        }

        printf("\nInterests: ");
        for (int j = 0; j < network->users_list[i]->num_interests; j++)
        {
            printf("%s ", network->users_list[i]->interests[j]);
        }

        printf("\n\n");
    }
}

struct User *createUser(const char *username, const char *password)
{
    struct User *user = (struct User *)malloc(sizeof(struct User));
    strcpy(user->username, username);
    strcpy(user->password, password);
    user->num_friends = 0;
    user->friends_list = NULL;
    user->num_interests = 0;
    user->interests = NULL;
    return user;
}

void addUserfromFile(struct SocialNetwork *network, struct HashMap *map, const char *username, const char *password)
{
    if (network->num_users >= MAX_USERS)
    {
        printf("Maximum number of users reached.\n");
        return;
    }
    addUser(network, map, username, password);
    // struct User *user = createUser(username, password);
    // network->users_list[network->num_users] = user;
    // network->num_users++;
}

void addFriendfromFile(struct User *user, struct User *friend)
{
    if (user->friends_list == NULL)
    {
        user->friends_list = (struct User **)malloc(sizeof(struct User *));
    }
    else
    {
        user->friends_list = (struct User **)realloc(user->friends_list, (user->num_friends + 1) * sizeof(struct User *));
    }

    user->friends_list[user->num_friends] = friend;
    user->num_friends++;
}

void addInterestfromFile(struct User *user, const char *interest)
{
    if (user->interests == NULL)
    {
        user->interests = (char **)malloc(sizeof(char *));
    }
    else
    {
        user->interests = (char **)realloc(user->interests, (user->num_interests + 1) * sizeof(char *));
    }

    user->interests[user->num_interests] = strdup(interest);
    user->num_interests++;
}

int getUserIndex(struct SocialNetwork *network, struct User *user)
{
    for (int i = 0; i < network->num_users; i++)
    {
        if (network->users_list[i] == user)
        {
            return i;
        }
    }
    return -1;
}

void readUsersFromCSV(const char *filename, struct SocialNetwork *network, struct HashMap *map)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file))
    {
        char username[20];
        char password[20];
        sscanf(line, "%[^,],%s", username, password);
        addUserfromFile(network, map, username, password);
    }

    fclose(file);
}

void readFriendsFromCSV(const char *filename, struct SocialNetwork *network)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file))
    {
        int userIndex, friendIndex;
        sscanf(line, "%d,%d", &userIndex, &friendIndex);

        if (userIndex < 0 || userIndex >= network->num_users ||
            friendIndex < 0 || friendIndex >= network->num_users)
        {
            printf("Invalid user index.\n");
            continue;
        }

        struct User *user = network->users_list[userIndex];
        struct User *friend = network->users_list[friendIndex];
        addFriendfromFile(user, friend);
    }

    fclose(file);
}

void readInterestsFromCSV(const char *filename, struct SocialNetwork *network)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip the header line

    while (fgets(line, sizeof(line), file))
    {
        int userIndex;
        char interest[20];
        sscanf(line, "%d,%s", &userIndex, interest);

        if (userIndex < 0 || userIndex >= network->num_users)
        {
            printf("Invalid user index.\n");
            continue;
        }

        struct User *user = network->users_list[userIndex];
        addInterestfromFile(user, interest);
    }

    fclose(file);
}

void writeUsersToCSV(const char *filename, struct SocialNetwork *network)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    fprintf(file, "Username,Password,numPost\n");
    for (int i = 0; i < network->num_users; i++)
    {
        struct User *user = network->users_list[i];
        fprintf(file, "%s,%s\n", user->username, user->password);
    }

    fclose(file);
}

void writeFriendsToCSV(const char *filename, struct SocialNetwork *network)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    fprintf(file, "User Index,Friend Index\n");
    for (int i = 0; i < network->num_users; i++)
    {
        struct User *user = network->users_list[i];
        for (int j = 0; j < user->num_friends; j++)
        {
            int friendIndex = getUserIndex(network, user->friends_list[j]);
            fprintf(file, "%d,%d\n", i, friendIndex);
        }
    }

    fclose(file);
}

void writeInterestsToCSV(const char *filename, struct SocialNetwork *network)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    fprintf(file, "User Index,Interest\n");
    for (int i = 0; i < network->num_users; i++)
    {
        struct User *user = network->users_list[i];
        for (int j = 0; j < user->num_interests; j++)
        {
            fprintf(file, "%d,%s\n", i, user->interests[j]);
        }
    }

    fclose(file);
}

// Function to add posts to a user from their folder
void addPosts_FromFolder(struct SocialNetwork *network){
    for (int i = 0; i < network->num_users; i++){
        addPostFromFolder(network->users_list[i],network->users_list[i]->username);
    }

}

void addPostFromFolder(struct User *user, const char *username)
{
    // Generate the folder path for the user's posts
    char folderPath[100];
    snprintf(folderPath, sizeof(folderPath), "posts/%s", username);

    // Open the user's folder
    DIR *dir = opendir(folderPath);
    if (dir == NULL)
    {
        // printf("Error: Unable to open folder for user '%s'.\n", username);
        return;
    }

    // Read posts from the user's folder and add them to the user's posts list
    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL)
    {
        if (ent->d_type == DT_REG)
        {
            // Generate the file path for the post
            char postFilePath[100];
            snprintf(postFilePath, sizeof(postFilePath), "%s/%s", folderPath, ent->d_name);

            // Open the file in read mode
            FILE *fp = fopen(postFilePath, "r");
            if (fp == NULL)
            {
                printf("Error opening post file '%s'.\n", postFilePath);
                continue;
            }

            // Create a new post node and add it to the user's posts list
            struct Post *newPost = (struct Post *)malloc(sizeof(struct Post));
            newPost->fp = fp;
            newPost->next = NULL;

            if (user->posts_list == NULL)
            {
                user->posts_list = newPost;
            }
            else
            {
                struct Post *temp = user->posts_list;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newPost;
            }
        }
    }

    // Close the user's folder
    closedir(dir);
}


int main()
{
    
    struct SocialNetwork *network = createSocialNetwork();
    struct HashMap *map = createHashMap(100);
    struct User *currentUser = NULL;
    readUsersFromCSV("users.csv", network, map);
    readFriendsFromCSV("friends.csv", network);
    readInterestsFromCSV("interests.csv", network);
    addPosts_FromFolder(network);

    int choice, ch, choose;

    // addUserFromFile(network,map,"user.txt");
    while (1)
    {
        printf("\n----- HOME MENU -----\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Show social_network\n");

        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char username[20];
            char password[20];
            printf("Enter username: ");
            scanf("%s", username);
            if (usernameExists(network, username))
            {
                printf("Username '%s' already exists.\n", username);
                break;
            }
            printf("Enter password: ");
            scanf("%s", password);

            addUser(network, map, username, password);
            writeUsersToCSV("users.csv", network);

            break;
        }
        case 2:
        {
            if (currentUser != NULL)
            {
                printf("Error: User '%s' is already logged in.\n", currentUser->username);
                break;
            }

            char username[20];
            // char password[20];
            printf("Enter username: ");
            scanf("%s", username);
            const char *password = get(map, username);
            if (password == NULL)
            {
                printf("User %s does not exist", username);
                break;
            }
            char Epassword[20];
            printf("Enter your password:");
            scanf("%s", Epassword);

            if (strcmp(password, Epassword) == 0)
            {
                printf("Login Succesful\n");
                printf("Welcome %s\n", username);
                currentUser = findUser(network, username);
            }

            // printf("Enter password: ");
            // scanf("%s", password);

            else
            {
                printf("Invalid  password.\n");
            }
            break;
        }
        case 3:
            printf("Showing social_network.\n");
            displayGraph(network);
            break;

            break;
        case 4:
            printf("Exiting the program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }

        while (currentUser != NULL)
        {
            printf("\n----- USER MENU -----\n");
            printf("1. Add Friend\n");
            printf("2. Add Post\n");
            printf("3. Show My Posts\n");
            printf("4. Show Friends\n");
            printf("5. Visit Friend\n");
            printf("6. Reset Password\n");
            printf("7. Add interest\n");
            printf("8. Recommended friends\n");
            printf("9. Show Interests\n");
            printf("10. Logout\n");

            printf("Enter your choice: ");
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
            {
                char friendName[20];
                printf("Enter friend's username: ");
                scanf("%s", friendName);

                struct User *friend = findUser(network, friendName);
                if (friend != NULL)
                {
                    addFriend(currentUser, friend);
                }
                else
                {
                    printf("User '%s' not found.\n", friendName);
                }
                writeFriendsToCSV("friends.csv", network);

                break;
            }
            case 2:
                addPost(currentUser);
                break;
            case 3:
                showPosts(currentUser);
                break;
            case 4:
            {
                printf("Showing friends of user '%s':\n", currentUser->username);
                int i;
                for (i = 0; i < currentUser->num_friends; i++)
                {
                    printf("Friend %d: %s\n", i + 1, currentUser->friends_list[i]->username);
                }
                if (currentUser->num_friends == 0)
                {
                    printf("No friends found.\n");
                }
                break;
            }

            case 5:
            {
                char friendName[20];
                printf("Enter friend's username: ");
                scanf("%s", friendName);

                struct User *friend = findUser(network, friendName);
                if (friend != NULL && friend->username != currentUser->username)
                {
                    while (choose != 4)
                    {
                        printf("\n----- VISIT FRIEND MENU -----\n");
                        printf("1. Show Friends\n");
                        printf("2. Show Posts\n");
                        printf("3.Show interests\n");
                        printf("4. Back\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choose);

                        switch (choose)
                        {
                        case 1:
                        {
                            printf("Showing friends of user '%s':\n", friend->username);
                            int i;
                            for (i = 0; i < friend->num_friends; i++)
                            {
                                printf("Friend %d: %s\n", i + 1, friend->friends_list[i]->username);
                            }
                            if (friend->num_friends == 0)
                            {
                                printf("No friends found.\n");
                            }
                            break;
                        }
                        case 2:
                            showPosts(friend);
                            break;

                        case 3:

                            show_interests(friend);
                            break;

                        case 4:
                            // choose=0;
                            break;

                        default:
                            // printf("Invalid choice. Please try again.\n");
                            break;
                        }
                    }
                    choose = 0;
                }

                else if (friend->username == currentUser->username)
                {
                    printf("Error! Enter Friend's Username");
                }

                else
                {
                    printf("User '%s' not found.\n ", friendName);
                }
                break;
            }

            case 6:
            {
                char newPassword[20];
                printf("Enter new password");
                scanf("%s", newPassword);
                resetPassword(map, currentUser->username, newPassword);
                break;
            }

            case 7:
            {
                printf("How many intersts do you want to add:\n");
                int num_interests = 0;
                scanf("%d", &num_interests);

                for (int i = 0; i < num_interests; i++)
                {
                    char interests[40];
                    printf("Enter your interests:");
                    scanf("%s", interests);
                    addInterest(currentUser, interests);
                }
                writeInterestsToCSV("interests.csv", network);

                break;
            }
            case 8:
            {
                recommendFriends(currentUser, network);
                break;
            }

            case 9:
            {
                show_interests(currentUser);
                break;
            }

            case 10:
                logout(&currentUser);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}
