#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"hashMap.h"
int main()
{
    HashMap *map = init_HashMap();
    map = put(map, "hfdv", "bgvf");
    map = put(map, "bvfcr", "fdx");
    map = put(map, "bfcr", "fdx");
    map = put(map, "bvfr", "fdx");
    map = put(map, "bvfc", "fdx");
    map = put(map, "bvf[pkjv", "fdx");
    map = put(map, "frtb5", "rvcxe");
    map = put(map, "fgvvc", "rvcxe");

    // char* s=get(map, "hfdv");
    // printf("%s",s);
    // keys = initArrayList();
    ArrayList* keys = keySet(map);
    for (int i = 0; i < keys->lastIndex; i++)
    {
        // int a=i;
        // printf("%d ",i);
        printf("%s ,\t %s\n",getAL(keys, i),  get(map, getAL(keys, i)));
    }
    // removeHM(map, "frtb5");
    // printf("%s" ,get(map,"frtb5"));
    return 0;
}
