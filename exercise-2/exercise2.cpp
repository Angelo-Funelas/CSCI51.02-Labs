#include <iostream>
using namespace std;

// This function goes through a string, per character, and checks if it is a digit.
// If it encounters at least one that isn't a digit, it will return false.
// Else if it doesn't enounter a non-digit, it will return true.
bool isNumber(string s) {
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

int main() {
    int N; // Initialize N
    cin >> N; // Read the first piece of data, load it into N
    for (int i=0; i<N; i++) { // Iterate through N lines
        int x; int y; string data; // Initialize variables
        cin >> x >> y; // Read x and y using cin
        cin.ignore(); // Throw away the extra space between y and data 
        getline(cin, data); // Read the entire line and pass it into data 
        cout << "Agent #" << i+1 << " is at ("  << x << ", " << y << ")" << endl; // Format output to show position of agent
        if (isNumber(data)) { // If the data is a number, an agent holds a number up
            cout << "Agent #" << i+1 << " holds up the number: " << data << endl; // Format output to show number held up by agent
            continue; // Skip and go to next agent
        }
        cout << "Agent #" << i+1 << " yells: \"" << data << "\"" << endl; // If the data is not a number, format output to show agent's message 
    }
    return 0;
}
