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

// This function takes a name, then replaces each character with the succeeding character in the alphabet.
// This is done by taking an empty string, then shifting each letter to the right based on its ASCII value.
// The case of 'z' and 'Z' needs to be handled separately, as the next character in ASCII does not loop back
// to 'a' and 'A'. For the case of non-letter characters, it is simply concatenated to the shifted name.
string shiftName1(string name) {
    string shiftedName = "";
    for (int i=0; i<name.length(); i++) { // Loop through every character of the input name
        char letter = name[i]; // Set the letter to the current character according to the index
        if ((letter >= 'a' && letter <= 'y')||(letter >= 'A' && letter <= 'Y')) shiftedName += letter + 1; // Shift letter to next position of alphabet
        else if (letter == 'z') shiftedName += 'a'; // Replace z with a
        else if (letter == 'Z') shiftedName += 'A'; // Replace Z with A
        else shiftedName += letter; // Accounting for non-letter characters
    }
    return shiftedName;
}

// ShiftName2 takes a char pointer as its parameter, with the char value within the pointer being shifted using
// the logic for shiftName1.
char shiftName2(char *namePointer) {
     if ((*namePointer >= 'a' && *namePointer <= 'y')||(*namePointer >= 'A' && *namePointer <= 'Y')) *namePointer = *namePointer + 1; // Shift letter to next position of alphabet
        else if (*namePointer == 'z') *namePointer = 'a'; // Replace z with a
        else if (*namePointer == 'Z') *namePointer = 'A'; // Replace Z with A
       
    return *namePointer;
}

int main() {
    string name;
    cout << "What is your name?\n  ";
    cin >> name; // Asks the user's name then passes it to 'name'

    cout << name << endl; // Print the name
    cout << censorName(name) << endl; // Print the censored name
    cout << shiftName1(name) << endl; // Print the censored name
   
    for (int i=0; i<name.length(); i++) {
       shiftName2(&name[i]); // Updates the value of each char in name
    }
    cout << name << endl;

    return 0;
}
