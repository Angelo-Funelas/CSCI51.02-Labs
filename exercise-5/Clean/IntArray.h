#include <string>
using namespace std;
struct IntArray {
    int size = 0;
    int *elements = nullptr;

    string stringify() {
        string res = "";
        res += "[";
        for (int i = 0; i<size; i++) {
            res += to_string(elements[i]);
            if (i != size-1) res += ", ";
        }
        res += "]\n";
        return res;
    }

    ~IntArray() {
        delete[] elements; // deallocate if deleted
    }
};
