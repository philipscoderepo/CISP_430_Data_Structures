#include <iostream>

using namespace std;

struct node {
    int item;
    node *next;
};

void enqueue(int item, struct node *&front, struct node*&rear){
    struct node *newNode = new node;

    newNode->item = item;
    newNode->next = NULL;
    if (rear){
        rear->next = newNode;
        rear = newNode;
   }
   else{
        front = rear = newNode;
   }
}

void dequeue(struct node *& front, struct node *& rear){
    struct node *temp;

    if(front){
        temp = front;
        front = front->next;
        delete temp;
        if (!front){rear = NULL;}
    }
}

int main(){
    struct node * front, * rear;
    front = rear = NULL;
    enqueue(5, front, rear);
 dequeue(front, rear);
}

