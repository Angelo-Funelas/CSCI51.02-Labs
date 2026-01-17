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

string shiftName1(string name) {
    string shiftedName = "";
    for (int i=0; i<name.length(); i++) {
        char letter = name[i];
        if ((letter >= 'a' && letter <= 'y')||(letter >= 'A' && letter <= 'Y')) shiftedName += letter + 1;
        else if (letter == 'z') shiftedName += 'a';
        else if (letter == 'Z') shiftedName += 'A';
        else shiftedName += letter;
    }
    return shiftedName;
}

string shiftName2(string name) {
    return " ";
}

int main() {
    string name;
    cout << "What is your name?\n  ";
    cin >> name; // Asks the user's name then passes it to 'name'

    cout << name << endl; // Print the name
    cout << censorName(name) << endl; // Print the censored name
    cout << shiftName1(name) << endl; // Print the censored name
    cout << shiftName2(name) << endl; // Print the censored name

    return 0;
}
