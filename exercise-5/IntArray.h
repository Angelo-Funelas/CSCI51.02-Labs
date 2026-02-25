struct IntArray {
    int size = 0;
    int *elements = nullptr;

    // void add(int value) {
    //     size++; // increment size
    //     int *newElements = new int[size]; // make a new array
    //     for (int i=0; i<size; i++)  newElements[i] = elements[i]; // move old values to new array
    //     newElements[size-1] = value; // set last element to new value
    //     delete[] elements; // delete old array
    //     elements = newElements; // set elements to new array
    // }

    // int get(int i) {
    //     if (i >= 0 && i < size) return elements[i];
    //     return 0;
    // }

    // void set(int i, int value) {
    //     if (i >= 0 && i < size) elements[i] = value;
    // }

    // ~IntArray() {
    //     delete[] elements; // deallocate if deleted
    // }
};
