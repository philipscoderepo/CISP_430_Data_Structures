#include <iostream>
using namespace std;
//Singly linked list
struct node{
    int value;
    node* next;
};

node* add(int value){
    node *temp = new node;
    temp->value = value;
    return temp;
}

void remove(node *&head, int value){
    node *curr, *temp;
    if(head){
        //Check first value
        if(head->value==value){
            temp=head;
            head=head->next;
            delete temp;
        }
        else{
            curr=head;
            while(curr->next && curr->next->value != value){
                curr = curr->next;
            }
            if(curr->next){
                temp = curr->next;
                //If there is no node at next next then the next pointer of curr is set to null
                curr->next = curr->next->next;
                delete temp;
            }
        }
    }
}

int main(){
    node *head, *current;
    head=current=new node;
    current->value = 13;
    current->next = add(10);
    current = current->next;
    current->next = add(15);
    current = current->next;
    current->next = add(12);
    current = current->next;

    cout << "Before remove: ";
    node *temp = head;
    while(temp){
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;

    cout << "After remove: ";
    remove(head, 15);
    temp = head;
    while(temp){
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
 }
