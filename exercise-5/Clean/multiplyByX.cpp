#include <iostream>
#include "IntArray.h"
using namespace std;

void multiplyByX(IntArray *p, int x) {
    int n = p->size;
    for(int i=0; i < n; i++) {
        int multipliedElement = p->elements[i] * x;
        p->elements[i] = multipliedElement;
    }
}