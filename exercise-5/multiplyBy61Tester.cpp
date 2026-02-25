#include <iostream>
#include "IntArray.h"
using namespace std;

extern void multiplyBy61(IntArray* p);

int main() {
    IntArray arr;
    arr.elements = new int[7]{6, 7, 4, 2, 0, 6, 9};
    arr.size = 7;
    
    cout << "[";
    for (int i = 0; i<arr.size; i++) {
        cout << arr.elements[i];
        if (i != arr.size-1) cout << ", ";
    }
    cout << "]" << endl;
    multiplyBy61(&arr);
    cout << "[";
    for (int i = 0; i<arr.size; i++) {
        cout << arr.elements[i];
        if (i != arr.size-1) cout << ", ";
    }
    cout << "]" << endl;
    return 0;
}