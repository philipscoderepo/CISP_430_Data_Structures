#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into

int parent(int i){
    return (i - 1) / 2;
}

int leftChild(int i){
    return ((2 * i) + 1);
}

int rightChild(int i){
    return ((2 * i) + 2);
}

void swap(int *&arr, int pos1, int pos2){
    int temp = *(arr + pos1);
    *(arr + pos1) = *(arr + pos2);
    *(arr + pos2) = temp;
}

void siftUp(int *&arr, int i){
    while(i > 0 && *(arr + parent(i)) > *(arr + i)){
        swap(arr, parent(i), i);
        i = parent(i);
    }
}

void siftDown(int *&arr, int i, int heapSize){
    int minIndex = i;

    int l = leftChild(i);

    if(l <= heapSize && *(arr + l) < *(arr + minIndex)){
        minIndex = l;
    }

    int r = rightChild(i);

    if(r <= heapSize && *(arr + r) < *(arr + minIndex)){
        minIndex = r;
    }

    if(i != minIndex){
        swap(arr, i, minIndex);
        siftDown(arr, minIndex, heapSize);
    }
}

void remove(int *&arr, int &heapSize){
    int *newArr = new int[heapSize + 1];
    int newHeapSize = heapSize - 1;

    //I swap the first item to the end
    swap(arr, 0, heapSize);
    //Then don't add it back into the new array
    for(int i = 0; i < heapSize; i++){
        *(newArr + i) = *(arr + i);
    }

    delete []arr;
    arr = newArr;
    heapSize = newHeapSize;
    siftDown(arr, 0, heapSize);
}

int getMin(int *&arr){
    return *arr;
}

void insert(int *&arr, int &heapSize, const int val){
    heapSize = heapSize + 1;
    *(arr + heapSize) = val;
    siftUp(arr, heapSize);
}

void printLevel(int *&arr, int heapSize){
    //Used to calculate the beginning index of each level
    int levelBeg = 1;
    //Once the level passes the size of the heap there are no longer values to display
    while(levelBeg <= heapSize + 1){
        //Loop through the current level (level - 1 to get the proper index)
        for(int i = levelBeg - 1; i < levelBeg * 2 - 1; i++){
            //Ensure that the loop doesn't iterate past the heapSize
            if(i <= heapSize){
                cout << *(arr + i) << " ";
            }
        }
        levelBeg = levelBeg * 2;
        cout << endl << endl;
    }
}

int main(){
    int *heap;
    //Heap size is the highest index populated in the heap
    int heapSize = -1;
    heap = new int[10];

    //Get the data
    int data;
    in >> data;
    //Keep track of loop iterations
    while(!in.eof()){
        insert(heap, heapSize, data);
        in >> data;
    }

    cout << "Before Removes: " << endl;
    cout << "************************" << endl;
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    cout << "Remove " << *(heap) << ":"<< endl;
    cout << "************************" << endl;
    remove(heap, heapSize);
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    cout << "Remove " << *(heap) << ":"<< endl;
    cout << "************************" << endl;
    remove(heap, heapSize);
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    cout << "Remove " << *(heap) << ":"<< endl;
    cout << "************************" << endl;
    remove(heap, heapSize);
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    cout << "Remove " << *(heap) << ":"<< endl;
    cout << "************************" << endl;
    remove(heap, heapSize);
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    cout << "Remove " << *(heap) << ":"<< endl;
    cout << "************************" << endl;
    remove(heap, heapSize);
    printLevel(heap, heapSize);
    cout << "Current Array: ";
    for(int i = 0; i < heapSize + 1; i++){
        cout << *(heap + i) << " ";
    }
    cout << endl << endl;

    delete []heap;
    return 0;
}
