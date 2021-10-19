#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into


struct node{
    int item;
    node *next;
};

void pop(node *&head){
    node *temp;
    if(head){
        temp = head;
        head = head->next;
        delete temp;
    }
}

void push(int item, node *&head){
    node *newNode = new node;
    newNode->item=item;
    newNode->next=head;
    head=newNode;
}

int evaluate(int a, int b, char oper){
    int result;

    if(oper=='+'){result = a + b;}
    else if(oper=='-'){result = a - b;}
    else if(oper=='*'){result = a * b;}
    else{result = a / b;}

    return result;
}

int main(){
    node *head=NULL;
    char *data = new char;
    //Read input into data
    in >> data;
    while(in.good()){
        data++;
        in >> data;
    }
    in.close();

    //While there is data
    while(*data != NULL){
        if(*data > '0' && *data < '10'){
            //Subtract 48 to get int value from char value
            push(*data-48, head);
        }
        else if(*data=='+'||*data=='-'||*data=='*'||*data=='/'){
            int a = head->item;
            pop(head);
            int b = head->item;
            pop(head);
            int value;
            value = evaluate(a,b,*data);
            push(value, head);
            cout << head->item << endl;
            pop(head);
        }
        data++;
    }

}
