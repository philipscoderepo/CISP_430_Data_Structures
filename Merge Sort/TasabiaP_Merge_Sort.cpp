
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

void split(node* head, node* &a, node* &b){
    //Get the size of the stack
    int stackLength = 0;
    node *curr = head;
    while(curr){
        stackLength++;
        curr = curr->next;
    }
    //Split the stack
    curr = head;
    int midPoint = stackLength / 2;
    //Insert values for stack a
    for(int i=0; i<midPoint; i++){
        append(curr->value, a);
        curr = curr->next;
    }
    //Insert values for stack b
    for(int i=midPoint; i<stackLength; i++){
        append(curr->value, b);
        curr = curr->next;
    }
}

node* merge(node* a, node* b){
    node *merged = NULL;
    //Find where b is less than a
    node *curr_a = a, *curr_b = b;
    while(curr_a && curr_b){
        if(curr_a->value < curr_b->value){
            append(curr_a->value, merged);
            curr_a = curr_a->next;
        }else{
            append(curr_b->value, merged);
            curr_b = curr_b->next;
        }
    }
    if(curr_a){
        while(curr_a){
            append(curr_a->value, merged);
            curr_a = curr_a->next;
        }
    }
    if(curr_b){
        while(curr_b){
            append(curr_b->value, merged);
            curr_b = curr_b->next;
        }
    }

    return merged;
}

node* mergeSort(node* head){
    //Node a will point to the left partition
    node *a = NULL,
    //Node b will point to the right partition
    *b  = NULL,
    //Node c will point to the newly merged stack
    *c  = NULL;

    if(head==NULL){
        return NULL;
    }
    if(head->next==NULL){
        return head;
    }

    split(head, a, b);

    a=mergeSort(a);
    b=mergeSort(b);
    c=merge(a,b);
    return c;
}

int main(){
    int data[] = {22, 133, 515, 1, 20, 55, 9, 46, 333, 891, 100, 100};
    node *head = NULL;

    for(int n : data){
        append(n, head);
    }
    cout << "Unsorted data: ";
    display(head);
    cout << endl;

    head = mergeSort(head);
    cout << "Sorted data: ";
    display(head);
    cout << endl;

    return 0;
}
