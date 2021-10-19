#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct node{
    int item;
    node *next;
};

struct nodeQ{
    node *front;
    node *rear;
};

void enqueue(int item, node *&front, node *&rear){
    node *nn = new node;
    nn->item = item;
    nn->next = NULL;
    if(rear){
        rear->next = nn;
        rear = nn;
    }
    else{
        front = rear = nn;
    }
}

void dequeue(node *&front, node *&rear){
    node *temp;
    if(front){
        temp = front;
        front = front->next;
        delete temp;
        if(!front){
            rear=NULL;
        }
    }
}

void sort_ascending(int *data, int len){
    //Create queue
    nodeQ que[10];
    //Initialize que
    for(int i=0; i<10; i++){
        que[i].front = NULL;
        que[i].rear = NULL;
    }

    //find max
    int max = data[0];
    for(int i=0; i<len; i++){
        if(max < data[i]){
            max = data[i];
        }
    }

    //determine how many iterations the sort will need
    int temp = max,
    iter = 0;
    while(temp > 0){
        temp = temp / 10;
        iter += 1;
    }

    //load the queue and sort the data
    for(int i=0, j=1, m=10; i<iter; i++,j*=10,m*=10){
        for(int k=0; k<len; k++){
            int index = data[k] % m / j;
            enqueue(data[k], que[index].front, que[index].rear);
        }

        int index = 0;
        for(int k=0; k<10; k++){
            while(que[k].front){
                data[index] = que[k].front->item;
                dequeue(que[k].front, que[k].rear);
                index++;
            }
        }
    }
}

void sort_descending(int *data, int len){
    //Create queue
    nodeQ que[10];
    //Initialize que
    for(int i=0; i<10; i++){
        que[i].front = NULL;
        que[i].rear = NULL;
    }

    //find max
    int max = data[0];
    for(int i=0; i<len; i++){
        if(max < data[i]){
            max = data[i];
        }
    }

    //determine how many iterations the sort will need
    int temp = max,
    iter = 0;
    while(temp > 0){
        temp = temp / 10;
        iter += 1;
    }

    //load the queue and sort the data
    for(int i=0, j=1, m=10; i<iter; i++,j*=10,m*=10){
        for(int k=0; k<len; k++){
            int index = 9-data[k] % m / j;
            enqueue(data[k], que[index].front, que[index].rear);
        }

        int index = 0;
        for(int k=0; k<10; k++){
            while(que[k].front){
                data[index] = que[k].front->item;
                dequeue(que[k].front, que[k].rear);
                index++;
            }
        }
    }
}

int main(){

    srand (time(NULL));
    //Pick amount of numbers in data
    int len = 15,
    //Top limit of data numbers
    limit = 1000,
    data[len],
    copy_data[len];

    //Initialize data
    for(int i=0; i<len; i++){
        data[i] = rand() % limit + 1;
        copy_data[i] = data[i];
    }

    cout << "Unsorted data: " << endl;
    for(int i=0; i<len; i++){
        cout << data[i] << endl;
    }
    cout << "================" << endl;

    ///Sort ascending
    sort_ascending(copy_data, len);

    //display
    cout << "Ascending order: " << endl;
    for(int i=0; i<len; i++){
        cout << copy_data[i] << endl;
    }
    cout << "================" << endl;

    //Reset copy
    for(int i=0; i<len; i++){
        copy_data[i] = data[i];
    }

    ///Sort descending
    sort_descending(copy_data, len);

    //display
    cout << "Descending order: " << endl;
    for(int i=0; i<len; i++){
        cout << copy_data[i] << endl;
    }
    cout << "================" << endl;
}
