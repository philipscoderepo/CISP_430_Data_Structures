#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

ifstream in("input.txt");                 //input.txt is the file that we read from
ofstream out("output.txt");          //output.txt is the file that we write into

void resize(int *&arr, int& size){
    int newSize = size * 2;
    int* newArr = new int[newSize];
    for(int i=0; i<newSize; i++){
        newArr[i] = arr[i];
    }
    delete []arr;
    arr = newArr;
    size = newSize;
}


int main(){
    int *b;
    int a;
    int b_size = 1;

    b = new int[b_size];
    int temp;

    int index = 0;
    in >> temp;
    while(!in.eof()){
        cout << "inserting: " << temp << endl;
        cout << b_size << endl;
        if(index == b_size){
            cout << "resize" << endl;
            resize(b, b_size);
        }
        *(b + index) = temp;
        index++;
        in >> temp;
    }

    for(int i=0; i<index; i++){
        cout << *(b + i) << " ";
    }
    delete []b;
}
