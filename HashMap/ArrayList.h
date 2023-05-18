typedef struct ArrayList {

    char** array;  
    int lastIndex;
    int size;
}ArrayList;
ArrayList* initArrayList() ;
void addInArray( ArrayList * arrayList, char* username ) ;
void printArrayList(ArrayList *list);
int sizeAL(ArrayList *list);
char* getAL(ArrayList *list,int i);
