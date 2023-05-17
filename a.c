#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int privateVar;
} MyClass;

MyClass* createMyClass() {
    MyClass* obj = (MyClass*)malloc(sizeof(MyClass));
    obj->privateVar = 0;
    return obj;
}

void setPrivateVar(MyClass* obj, int value) {
    obj->privateVar = value;
}

int getPrivateVar(MyClass* obj) {
    return obj->privateVar;
}

int main() {
    MyClass* obj = createMyClass();
    setPrivateVar(obj, 42);
    printf("%d\n", getPrivateVar(obj));

    free(obj);

    return 0;
}
