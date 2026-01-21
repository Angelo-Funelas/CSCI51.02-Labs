#include <iostream>
using namespace std;

// This function goes through a string, per character, and checks if it is a digit.
// If it encounters at least one that isn't a digit, it will return false
// If it doesn't enounter a non-digit, it will return true
bool isNumber(string s) {
    for (char c : s) if (!isdigit(c)) return false;
    return true;
}

int main() {
    int N; // Initialize N
    cin >> N; // read the first piece of data, load into N
    for (int i=0; i<N; i++) { // Iterate through N lines
        int x; int y; string data; // initialize variables
        cin >> x >> y; // read x and y using cin
        cin.ignore(); // throw away the extra space between y and data 
        getline(cin, data); // read the entire line and pass it into data 
        cout << "Agent #" << i+1 << " is at ("  << x << ", " << y << ")" << endl; // format output to show position of agent
        if (isNumber(data)) { // if the data is a number, not a message
            cout << "Agent #" << i+1 << " holds up the number: " << data << endl; // format output to say that the agent holds up a number
            continue; // skip and go to next agent
        }
        cout << "Agent #" << i+1 << " yells: \"" << data << "\"" << endl; // if data is not a number, format output to say that the agent yells out a message 
    }
    return 0;
}
