#include <iostream>
#include "IntArray.h"
using namespace std;

void multiplyBy61(IntArray *p) {
    int n = p->size;
    for(int i=0; i < n; i++) {
        int multipliedElement = p->elements[i] * 61;
        p->elements[i] = multipliedElement;
    }
}