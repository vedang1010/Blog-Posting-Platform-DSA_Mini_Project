#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "LinkedList.h"


node *initialize_LL()
{
    node *head = (node*)malloc(sizeof(node));
    head->username=(char*)malloc(sizeof(char)*20);
    head->password=(char*)malloc(sizeof(char)*20);

    head->next=NULL;
    // head->next=NUll;
    // ll=&head;
    return head;
}

node *createNode(char* user, char* password)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->username = user;
    newNode->password = password;
    newNode->next = NULL;

    return newNode;
}

node* getLL(node* head,int n){
    node* temp=head;
    for (int i = 0; i < n; i++)
    {
        temp=temp->next;
        /* code */
    }
    return temp;
}

node* add(node *head, char* username, char* password)
{
    if (head == NULL)
    {
        head = createNode(username, password);
        head->next = NULL;
        return head;
    }
    else
    {
        node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = createNode(username, password);
        return head; 
    }
}

void print(node *head)
{
    node *temp = head->next;
    while (temp != NULL)
    {
        printf("%s ", temp->username);
        temp = temp->next;
        /* code */
    }
}

int LLsize(node* head){
    int n=0;
    node *temp=head;
    while (temp!=NULL)
    {
        n++;
        temp=temp->next;
        /* code */
    }
    return n;
    
}

node* removeLL(node* head,int n){
    node* temp=head;
    node* ptr=NULL;
    if (n==0)
    {
        ptr=head;
        head=temp->next;
        // return ret;
        /* code */
    }
    else if (n==1)
    {
        ptr=temp->next;
        temp->next=ptr->next;
        /* code */
    }
    
    else{
        for (int i = 0; i < n-1; i++)
        {
            temp=temp->next;
            /* code */
        }
        ptr=temp->next;
        temp->next=ptr->next;
    }
    return ptr;
}

node** create_array_of_nodes(int size){
    node** array=(node**)malloc(sizeof(node*)*size);
    // node** array=(node**)malloc(sizeof(node*)*size);
    return array;
}


// int size_of_array_of_ll(node* array[]){
//     int n=sizeof(&array)/sizeof(array[0]);
//     return n;
// }

// // int size_of_node_list(node buckets[])
// // {
// //     int n=sizeof(buckets)/sizeof(node);
// //     return n;
// // }
// int main()
// {
//     int *arr=(int*)malloc(sizeof(int)*5);
//     // printf("%ld ",sizeof(&arr)/sizeof(node*));
//     node** ll = create_array_of_nodes(4);
//     for (int i = 0; i < 4; i++)
//     {
//         ll[i]=initialize_LL();
//         /* code */
//     }
//     ll[0]=add(ll[0],"fcdx","dffgg");
//     ll[0]=add(ll[0],"vtf","bvgcf");
//     ll[0]=add(ll[0],"vtf","bvgcf");
//     ll[0]=add(ll[0],"gvf","frgf5frf");

//     ll[1]=add(ll[1],"fcdx","dffgg");
//     ll[1]=add(ll[1],"fcdx","dffgg");
//     ll[1]=add(ll[1],"vtf","bvgcf");
//     ll[1]=add(ll[1],"gvf","frgf5frf");
    
//     // ll=add(ll, "vedamf", "dcdsx");
//     // ll=add(ll, "vedamlkjhgf", "dcdsx");
//     // ll=add(ll, "jhgfddamf", "dcdsx");
//     // printf("\n%d",LLsize(ll[0]));
//     print(ll[0]);
//     printf("\n");
//     print(ll[1]);
   
//     return 0;
// }

// // // node *remove(node* head)
