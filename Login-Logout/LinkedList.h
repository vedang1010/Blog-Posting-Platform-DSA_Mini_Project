// #define size 100
// #define len 30

typedef struct node
{
    char *username;
    char  *password;
    struct node *next;

} node;
node *initialize_LL();
node *createNode(char *user,char*  password);
node* add(node* head,char* username,char* password);
void print(node* head);
int LLsize(node* head);
node** create_array_of_nodes(int size);
node* removeLL(node* head,int n);
node* getLL(node* head,int n);