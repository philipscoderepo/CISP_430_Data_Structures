#include <iostream>

using namespace std;

struct node {
    int value;
    node *next;
    node *prev;
};

void insert(int value, node *&head, node *&tail){
    node *newNode = new node;
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    //If the head is null then the list is empty
    if(!head){
        //So make the new node the first item
        head = newNode;
        tail = newNode;
    }
    else if(value < head->value){
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
    }
    //If we need to update the tail
    else if(value > tail->value){
            newNode->next = NULL;
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
    }
    else{
        node *curr = head->next;
        while(curr && value > curr->value){
            curr = curr->next;
        }

        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

void remove(int value, node *&head, node *&tail){
    if(!head){
        //There is no data to delete
    }
    //Check the head
    else if(value == head->value){
            node *temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
    }
    //Check the tail
    else if(value == tail->value){
            node *temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
    }
    //Search the list for the name
    else{
        node *curr = head->next;
        while(curr && value != curr->value){
            curr = curr->next;
        }

        node *temp = curr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete temp;
    }
}

void display(node *&head){
    node *curr = head;
    while(curr){
        cout << curr->value << endl;
        curr = curr->next;
    }
}

int main(){
    int data[10] = {22, 133, 515, 1, 20, 55, 9, 46, 333, 891};
    node *head = NULL, *tail = NULL;

    for(int n : data){
        insert(n, head, tail);
    }

    display(head);
    //mergeSort(head);
    return 0;
}
