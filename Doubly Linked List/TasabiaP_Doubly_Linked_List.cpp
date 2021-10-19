#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into

struct node {
    string name;
    node *next;
    node *prev;
};

int compare(string s1, string s2){

    int maxLen = 0, cmp = 0;
    if(s1.length() > s2.length()){
        maxLen = s1.length();
    }
    else{
        maxLen = s2.length();
    }

    bool isSame = false;
    for(int i=0; i<maxLen; i++){
        if(toupper(s1[i]) < toupper(s2[i])){return -1;}
        else if(toupper(s1[i]) > toupper(s2[i])){return 1;}
        if(toupper(s1[i]) == toupper(s2[i])){isSame = true;}
    }

    if(s1.length() == s2.length() && isSame){
        cmp = 0;
    }
    else if(s1.length() < s2.length() && isSame){
        cmp = -1;
    }
    else if(s1.length() > s2.length() && isSame){
        cmp = 1;
    }

    return cmp;

}

void insert(string newName, node *&head, node *&tail){
    node *newNode = new node;
    newNode->name = newName;
    newNode->prev = NULL;
    newNode->next = NULL;

    //If the head is null then the list is empty
    if(!head){
        //So make the new node the first item
        head = newNode;
        tail = newNode;
    }
    else if(compare(newName, head->name)<=0){
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
    }
    //If we need to update the tail
    else if(compare(newName, tail->name)>=0){
            newNode->next = NULL;
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
    }
    else{
        node *curr = head->next;
        while(curr && compare(newName, curr->name)>=0){
            curr = curr->next;
        }

        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }
}

void deleteNode(string name, node *&head, node *&tail){
    if(!head){
        //There is no data to delete
    }
    //Check the head
    else if(compare(name, head->name)==0){
            node *temp = head;
            head = head->next;
            head->prev = NULL;
            delete temp;
    }
    //Check the tail
    else if(compare(name, tail->name)==0){
            node *temp = tail;
            tail = tail->prev;
            tail->next = NULL;
            delete temp;
    }
    //Search the list for the name
    else{
        node *curr = head->next;
        while(curr && compare(name, curr->name)!=0){
            curr = curr->next;
        }

        node *temp = curr;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;

        delete temp;
    }
}

void outputNodesAscending(node *&head){
    node *curr = head;
    while(curr){
        out << curr->name << endl;
        curr = curr->next;
    }
}

void outputNodesDescending(node *&tail){
    node *curr = tail;
    while(curr){
        out << curr->name << endl;
        curr = curr->prev;
    }
}

int main(){
    node *head = NULL, *tail = NULL;

    string s;
    in >> s;
    while(in.good()){
        if(s == "delete"){
            in >> s;
            deleteNode(s, head, tail);
        }
        else{
            insert(s, head, tail);
        }
        in >> s;
    }

    outputNodesAscending(head);
    out << "====================" << endl;
    outputNodesDescending(tail);
    out.close();
}
