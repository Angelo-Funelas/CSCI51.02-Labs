#include <iostream>
using namespace std;

// This function takes a name, then censors the characters of the name except the first character.
// This is done by taking an empty string, then concatenating only the first character, then adding
// hashtags (#) equal to the length of the remaining string.
string censorName(string name) {
    string censoredName = "";
    censoredName += name[0];
    for (int i=1; i<name.length(); i++) censoredName += "#";
    return censoredName;
}

int main() {
    string name;
    cout << "What is your name?\n  ";
    cin >> name; // Asks the user's name then passes it to 'name'

    cout << name << endl; // Print the name
    cout << censorName(name) << endl; // Print the censored name

    return 0;
}
