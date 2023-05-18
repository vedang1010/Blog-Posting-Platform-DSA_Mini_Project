#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"
// #include "ArrayList.c"
// #include "LinkedList.c"

int n;
// typedef struct HashMap
// {
//     node **buckets;
//     int N;
// } HashMap;
// int hashFuntion(HashMap *map, char *username);
// int searchInLL(HashMap *map, char *username, int bi);
// void rehash(HashMap *map);
// HashMap *put(HashMap *map, char *username, char *password);
// char *get(HashMap *map, char *username);
// bool containsKey(HashMap *map, char *username);
// char *removeHM(HashMap *map, char *username);
// HashMap *init_HashMap();
// ArrayList *keySet(HashMap *map);

HashMap *init_HashMap()
{
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    map->N = 6;
    map->buckets = create_array_of_nodes(map->N);
    for (int i = 0; i < map->N; i++)
    {
        map->buckets[i] = initialize_LL();
    }
    return map;
}

int hashCode(char *str)
{
    int hashCode = 5381;
    int c;

    while (c = *str++)
        hashCode = ((hashCode << 5) + hashCode) + c; /* hash * 33 + c */

    return hashCode;
}
// int get_hash(const char *s, const int n)
// {
//     long long p = 31, m = 1e9 + 7;
//     long long hash = 0;
//     long long p_pow = 1;
//     for (int i = 0; i < n; i++)
//     {
//         hash = (hash + (s[i] - 'a' + 1) * p_pow) % m;
//         p_pow = (p_pow * p) % m;
//     }
//     return hash;
// }

// int hashCode(char *str)
// {
//     return get_hash(str, strlen(str));
// }

int hashFuntion(HashMap *map, char *username)
{
    int bi = hashCode(username);
    bi = abs(bi) % map->N;
    return bi;
}

// try again
int searchInLL(HashMap *map, char *username, int bi)
{
    // node *ll = initialize_LL();
    // LinkedList<Node>
    node *ll = map->buckets[bi];
    for (int i = 0; i < LLsize(ll); i++)
    {
        // if (ll.get(i)->username == username)
        if (getLL(ll, i)->username == username)
        {
            return i; // di
        }
    }
    return -1;
}

void rehash(HashMap *map)
{
    int a = map->N;
    map->N = map->N * 2; // might be wrong
    node **oldbuckets = map->buckets;
    // node *oldbuckets[] = buckets;
    // LinkedList<Node> oldBucket[] = buckets;
    // buckets = node* new[N * 2];
    free(map->buckets);
    map->buckets = create_array_of_nodes(map->N); // might be wrong
    for (int i = 0; i < map->N; i++)              // might be wrong
    {
        map->buckets[i] = initialize_LL();
    }
    for (int i = 0; i < a /*size of array of node old buckets*/; i++)
    {
        node *ll = oldbuckets[i];
        for (int j = 0; j < LLsize(ll); j++)
        {
            node *node = getLL(ll, j);
            map = put(map, node->username, node->password);
        }
    }
}

HashMap *put(HashMap *map, char *username, char *password)
{
    int bi = hashFuntion(map, username);
    int di = searchInLL(map, username, bi);

    if (di == -1)
    {
        // key doesnt exist
        map->buckets[bi] = add(map->buckets[bi], username, password);
        // buckets[bi].add(new Node(key, value));
        // printf("%d\n", 1);
        n++;
        // printf("%d\n", 2);
    }
    // else
    // {
        // key exist
        // node *node = buckets[bi].get(di);
        // printf("%d\n", 1);
        // node *node = getLL(map->buckets[bi], di);
        // node->password = password;
        // printf("%d\n", 2);
    // }

    double lambda = (double)n / map->N;
    if (lambda > 2.0)
    {
        // printf("%d\n", 1);

        // rehashing
        rehash(map);
        // printf("%d\n", 2);
    }
    return map;
}

char *get(HashMap *map, char *username)
{
    int bi = hashFuntion(map, username);
    int di = searchInLL(map, username, bi);
    if (di == -1)
    {
        // key doesnt exist
        // buckets[bi].add(new Node(key, value));
        return NULL;
    }
    else
    {
        // key exist
        node *node = getLL(map->buckets[bi], di);
        return node->password;
    }
}

bool containsKey(HashMap *map, char *username)
{
    int bi = hashFuntion(map, username);
    int di = searchInLL(map, username, bi);

    if (di == -1)
    {

        return false;
    }
    else
    {
        // node *node = getLL(buckets[bi],di);
        return true;
    }
}

char *removeHM(HashMap *map, char *username)
{
    int bi = hashFuntion(map, username);
    int di = searchInLL(map, username, bi);

    if (di == -1)
    {

        return NULL;
    }
    else
    {
        // key exist
        // node *node = buckets[bi].remove(di);
        node *node = removeLL(map->buckets[bi], di);
        n--;
        return node->password;
    }
}

ArrayList *keySet(HashMap *map)
{
    ArrayList *keys = initArrayList();
    for (int i = 0; i < map->N; i++)
    {
        node *ll = map->buckets[i];
        for (int j = 1; j < LLsize(ll); j++)
        {
            node *node = getLL(ll, j);
            if (node->username!=NULL && node->password!=NULL)
            {
            addInArray(keys, node->username);
            }
        }
    }
    return keys;
}
