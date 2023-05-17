#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "ArrayList.h"

ArrayList *initArrayList()
{

    ArrayList *AL = (ArrayList*)malloc(sizeof(ArrayList));

    AL->array = (char **)malloc(6 * sizeof(char *));

    AL->lastIndex = -1;
    AL->size = 6;

    return AL;
}

void addInArray(ArrayList *array, char* username)
{

    if (array->lastIndex == array->size - 1)
    {
        char** ptr=array->array;
        // for (int i = 0; i < array->size; i++)
        // {
        //     ptr[i]=array->array[i];
        //     /* code */
        // }
        array->array = realloc(array->array, 2 * sizeof(array->array) * sizeof(char *));
        for (int i = 0; i < array->size; i++)
        {
            array->array[i]=ptr[i];
            /* code */
        }
    }

    array->lastIndex++;
    array->array[array->lastIndex] = username;
}

void printArrayList(ArrayList *list)
{
    for (int i = 0; i <= list->lastIndex; i++)
    {
        printf("%s ", list->array[i]);
        /* code */
    }
}

int sizeAL(ArrayList *list)
{
    return list->lastIndex + 1;
}

char *getAL(ArrayList *list, int i)
{
    return list->array[i];
}

// int main(){
//     ArrayList *l=initArrayList();
//     addInArray(l,"dfgtf");
//     addInArray(l,"dfgtcds");
//     addInArray(l,"dfgfdsx");
//     addInArray(l,"ddvggfrhn");
//     printArrayList(l);
//     return 0;
// }