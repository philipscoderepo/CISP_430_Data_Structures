
#include <iostream>

using namespace std;

struct node{
    int value;
    node* next;
};

void append(int value, node* &head){
    node* newNode = new node;
    newNode->next = NULL;
    newNode->value = value;
    if(head==NULL){
        head = newNode;
    }else{
        node *curr = head;
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newNode;
    }
}

void display(node* &top){
    node *curr = top;
    while(curr){
        cout << curr->value << " ";
        curr = curr->next;
    }
}

int main(){
    int data[10] = {22, 133, 515, 1, 20, 55, 9, 46, 333, 891};
    node *head = NULL, *tail = NULL;

    for(int n : data){
        append(n, head);
    }
    int stackLength = 0;
    node *curr = head;
    while(curr){
        stackLength++;
        curr = curr->next;
    }
    cout << "Stack Length: " << stackLength << endl;
    cout << "Unsorted data: ";
    display(head);
    cout << endl;

    //head = mergeSort(head);
    cout << "Sorted data: ";
    display(head);
    cout << endl;

    return 0;
}
