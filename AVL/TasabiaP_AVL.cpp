#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into

struct node{
    int item;
    int height;
    node* left;
    node* right;
};

int getBalance(node* tree){
    //Get left height
    int leftHeight = -1;
    if(tree->left != NULL){
        leftHeight = tree->left->height;
    }
    //Get right height
    int rightHeight = -1;
    if(tree->right != NULL){
        rightHeight = tree->right->height;
    }
    //The difference is the balance
    return leftHeight - rightHeight;
}

void updateHeight(node* tree){
    //Get left height
    int leftHeight = -1;
    if(tree->left != NULL){
        leftHeight = tree->left->height;
    }
    //Get right height
    int rightHeight = -1;
    if(tree->right != NULL){
        rightHeight = tree->right->height;
    }
    //The max plus one is the height
    tree->height = max(leftHeight, rightHeight) + 1;
}

node* leftRotate(node* x){
    node *y = x->right;
    node *T2 = y->left;
    //Perform rotation
    y->left = x;
    x->right = T2;

    //update heights for x and y
    updateHeight(x);
    updateHeight(y);
    return y;
}

node* rightRotate(node* x){
    node *y = x->left;
    node *T2 = y->right;
    //Perform rotation
    y->right = x;
    x->left = T2;

    //update heights for x and y
    updateHeight(x);
    updateHeight(y);
    return y;
}

node* rebalance(node* tree){
    updateHeight(tree);
    int balance = getBalance(tree);

    //if the balance is positive then the tree is left heavy
    //rotate to the right
    //if the balance is negative then the tree is right heavy
    //rotate to the left

    //Do rotations as necessary
    if(balance > 1 || balance < -1){
        if(balance < -1){
            if(getBalance(tree->right) > 0){
                tree->right = rightRotate(tree->right);
                return leftRotate(tree);
            }else{
                return leftRotate(tree);
            }
        }
        if(balance > 1){
            if(getBalance(tree->left) < 0){
                tree->left = leftRotate(tree->left);
                return rightRotate(tree);
            }else{
                return rightRotate(tree);
            }
        }
    }

    return tree;
}

node* insert(node* tree, int key){
    //Recursive insert
    //at insert, set height to 0 for the node
    if(tree == NULL){
        node *newNode = new node;
        newNode->item = key;
        newNode->height = 0;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if(key < tree->item){
        tree->left = insert(tree->left, key);
    }else{
        tree->right = insert(tree->right, key);
    }

    tree = rebalance(tree);//update heights and re-balance
    return tree;
}

void displayAscending(node* tree){
    if(tree == NULL){
        return;
    }

    displayAscending(tree->left);
    cout << "Node: " << tree->item << endl;
    cout << "Height: " << tree->height << endl;
    cout << "Balance: " << getBalance(tree) << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    displayAscending(tree->right);
}

struct queueNode{
    node* item;
    queueNode* next;
};

void enqueue(node* item, queueNode* &front, queueNode* &rear){
    queueNode *newNode = new queueNode;

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

void dequeue(queueNode *& front, queueNode *& rear){
    queueNode *temp;

    if(front){
        temp = front;
        front = front->next;
        delete temp;
        if (!front){rear = NULL;}
    }
}

void printLevel(node* tree){
    queueNode *currentLevelF, *currentLevelR,
    *nextLevelF, *nextLevelR;

    currentLevelF = currentLevelR = NULL;
    nextLevelF = nextLevelR = NULL;

    //load the root
    enqueue(tree, currentLevelF, currentLevelR);
    int level = 0;
    while(currentLevelF){
        //Load the next level
        out << "Level: " << level << endl;
        out << "******************************" << endl;
        while(currentLevelF){
            if(currentLevelF->item->left){
                enqueue(currentLevelF->item->left, nextLevelF, nextLevelR);
            }
            if(currentLevelF->item->right){
                enqueue(currentLevelF->item->right, nextLevelF, nextLevelR);
            }
            //write current level
            out << "Node: " << currentLevelF->item->item << endl;
            out << "Height: " << currentLevelF->item->height << endl;
            out << "Balance: " << getBalance(currentLevelF->item) << endl;
            out << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            dequeue(currentLevelF, currentLevelR);
        }
        level++;
        out << endl;
        while(nextLevelF){
            //load the next level into the current level
            enqueue(nextLevelF->item, currentLevelF, currentLevelR);
            dequeue(nextLevelF, nextLevelR);
        }
    }
}

int main(){
    node *tree = NULL;
    int data;
    //Read input into data
    in >> data;
    while(!in.eof()){
        //cout << "Inserting: " << data << endl;
        tree = insert(tree, data);
        in >> data;
    }
    //cout << endl;
    out << endl << "Tree Balance: " << getBalance(tree) << endl
    << "Tree Height: " << tree->height << endl << endl;

    printLevel(tree);
    displayAscending(tree);

    return 0;
}
