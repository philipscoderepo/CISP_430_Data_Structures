#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into


struct node{
    int value;
    node *next;
};

void pop(node *&top){
    node *temp;
    if(top){
        temp = top;
        top = top->next;
        delete temp;
    }
}

void push(int value, node *&top){
    node *nn = new node;
    nn->value = value;
    nn->next = top;
    top = nn;
}

int evaluate(int l, int r, char oper){
    int result;

    if(oper=='+'){result = l + r;}
    else if(oper=='-'){result = l - r;}
    else if(oper=='*'){result = l * r;}
    else{result = l / r;}

    return result;
}

void display(node *n){
    cout << "Contents: " << endl;
    while(n){
        cout << n->value << endl;
        n = n->next;
    }
}

int main(){
    node *top=NULL;
    string s;
    //Read input into data
    in >> s;
    //While there is data
    for(char c : s){
        if(isdigit(c)){
            //Subtract 48 to get int value from char value
            push(c-48, top);
        }
        else if(c=='+'||c=='-'||c=='*'||c=='/'){
            //Get values to operate on
            int right = top->value;
            pop(top);
            int left = top->value;
            pop(top);
            //Evaluate and store the value
            int value;
            value = evaluate(left,right,c);
            //Add the value to the stack
            push(value, top);
        }
        //display(top);
    }
    //Display and pop
    cout << top->value << endl;
    pop(top);
}
