#include "LinkedList.h"
#include "ArrayList.h"
#include <stdbool.h>

typedef struct HashMap
{
    node **buckets;
    int N;
} HashMap;
int hashFuntion(HashMap *map, char *username);
int searchInLL(HashMap *map, char *username, int bi);
void rehash(HashMap *map);
HashMap *put(HashMap *map, char *username, char *password);
char *get(HashMap *map, char *username);
bool containsKey(HashMap *map, char *username);
char *removeHM(HashMap *map, char *username);
HashMap *init_HashMap();
ArrayList *keySet(HashMap *map);
