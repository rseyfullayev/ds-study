#include "mylib.c"


typedef struct Node {
    int data;
    Node* next;

} Node;

typedef struct List {
    Node* head;
    int elementsCount;
} linkedList;


int main()
{

    greetings("earthman");
    return 0;
}