#include <iostream>
#include "IntArray.h"
using namespace std;
extern void multiplyBy256(IntArray *p);
int main() {
    IntArray* arr = new IntArray();
    arr->elements = new int[7]{6, 7, 4, 2, 0, 6, 9};
    arr->size = 7;
    cout << arr->stringify();
    multiplyBy256(arr);
    cout << arr->stringify();
    delete arr;
    arr = nullptr;
    return 0;
}
