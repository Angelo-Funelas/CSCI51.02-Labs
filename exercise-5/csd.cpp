#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

void CSD_getInstructions(vector<string>* instructions, int num) {
    instructions->push_back("    # Implemented with CSD algorithm\n");
    int csd_res = 0;
    int bitSize = sizeof(num) * CHAR_BIT;

    vector<int> carry(bitSize+1);
    vector<int> csd_digits(bitSize);
    
    for (int i = 0; i < bitSize; i++) {
        int bit = (num >> i) & 1;
        int bit_next = (num >> i+1) & 1;
        carry[i+1] = ((bit+bit_next+carry[i])>=2)?1:0;
        csd_digits[bitSize-i-1] = bit+carry[i]-(2*carry[i+1]);
    }
    cout << csd_digits.size() << endl;
    for (int i = 0; i < csd_digits.size(); i++) {
        cout << csd_digits[i] << " ";
    }
}

int main() {
    vector<string> instructions;
    CSD_getInstructions(&instructions, 61);
    return 0;
}


