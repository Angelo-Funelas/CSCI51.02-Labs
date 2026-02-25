#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <vector>
#include "IntArray.h"
using namespace std;

// Check if a number is prime
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) { // iterate until the square root of n
        if (n % i == 0) return false; // false if any i before sqrt(n) divides n
    }
    return true;
}

// Uses Canonical Signed Digit Representation to determine instructions
void CSD_getInstructions(vector<string>* instructions, int num) {
    instructions->push_back("    # Implemented with CSD algorithm\n");
    int bitSize = sizeof(num) * CHAR_BIT;

    vector<int> carry(bitSize+1); // Carry array
    vector<int> csd_digits(bitSize); // Digits in CSD form 
    
    for (int i = 0; i < bitSize; i++) { // iterate through bits of num
        int bit = (num >> i) & 1;
        int bit_next = (num >> i+1) & 1;
        carry[i+1] = ((bit+bit_next+carry[i])>=2)?1:0; // calculate the next carry
        csd_digits[bitSize-i-1] = bit+carry[i]-(2*carry[i+1]); // calculate current digit
    }
    instructions->push_back("    movl	%ecx, %r8d\n"); // place num in a temporary register
    int last_power = 1; 
    bool first_instruction = true;
    for (int i = 0; i<csd_digits.size(); i++) {
        int digit = csd_digits[i];
        if (digit == 0) continue;
        int power = csd_digits.size() - i;
        if (last_power < power) {
            instructions->push_back("    sall	$" + to_string(power-last_power) + ", %r8d\n"); // shift left if going up
        } else {
            instructions->push_back("    sarl	$" + to_string(last_power-power) + ", %r8d\n"); // shift right if going down
        }
        if (first_instruction) {
            instructions->push_back("	movl	%r8d, %ecx\n"); // Set ecx register after first shift
            first_instruction = false;
        } else {
            string arith_instr = (digit==1)?"addl":"subl"; // Use CSD digits to determine if addition or subtraction
            instructions->push_back("	" + arith_instr + "	%r8d, %ecx\n"); // add/subtract shifted register from our result 
        }
        last_power = power;
    }
}

// Use sum of powers of 2 depending on the binary representation
void binary_getInstructions(vector<string>* instructions, int num) {
    instructions->push_back("    # Implemented with binary summation algorithm\n");
    int bitSize = sizeof(num) * CHAR_BIT;
    int last_shift_i = 0;
    int shift_count = 0;
    
    // Additive
    for (int i = 0; i < bitSize; i++) { // go through bits of num
        int bit = (num >> i) & 1;
        if (bit == 1) {// if 1, add current power of 2 to current sum
            string instruction = (shift_count == 0)? "movl":"addl";
            shift_count++;
            int shift_amount = i-last_shift_i;
            if (shift_amount < 4) {
                int mul_factor = (int)(pow(2,shift_amount));
                if (mul_factor>1) instructions->push_back("	leal	(, %ecx, " + to_string(mul_factor) + "), %ecx\n"); // if shift is small enough, prefer lea instruction
            } else {
                instructions->push_back("	sall	$" + to_string(shift_amount) + ", %ecx\n"); // Shift
            }
            instructions->push_back("	" + instruction + "	%ecx, %r8d\n"); // add to current sum
            last_shift_i = i;
        }
    }

    // Subtractive
    int sum_count = shift_count;
    int diff_count = last_shift_i+1-shift_count; // calculate number of zeroes
    int last_1 = last_shift_i;
    last_shift_i = 0;
    if (diff_count < shift_count) { // Do subtractive if number in binary has less zeroes
        instructions->clear();
        instructions->push_back("    # Implemented with binary difference algorithm\n");
        instructions->push_back("	movl	%ecx, %r8d\n");
        int overshoot = ceil(log2(num)); // get the first power of 2 higher than num 
        instructions->push_back("	sall	$" + to_string(overshoot) + ", %ecx\n"); // multiply num by the power of 2, overshooting

        for (int i = 0; i < last_1+1; i++) {
            int bit = (num-1 >> i) & 1;
            if (bit == 0) { // if bit is zero, subtract 2^i from the current result
                int shift_amount = i-last_shift_i;
                if (shift_amount < 4) {
                    int mul_factor = (int)(pow(2,shift_amount));
                    if (mul_factor>1) instructions->push_back("	leal	(, %r8d, " + to_string(mul_factor) + "), %r8d\n"); // if shift is small enough, prefer lea instruction
                } else {
                    instructions->push_back("	sall	$" + to_string(shift_amount) + ", %r8d\n");
                }
                instructions->push_back("	subl	%r8d, %ecx\n");
                last_shift_i = i;
            }
        }
    }

    if (sum_count>1) {
        if (diff_count >= sum_count) instructions->push_back("    movl	%r8d, %ecx\n"); // if not power of 2 and used additive solution, add final instruction to copy result to ecx
    } else {
        instructions->pop_back(); // if only 1 instruction was done, means num is a power of 2, remove extra instructions
    }
}

// Calculate instructions by getting factors, then multiply number to factors
int possible_factors[] = {9,8,6,5,4,3,2};
int max_depth = 7; // Given a limited number of registers, only go deep until we run out of usable registers
void factoring_getInstructions(vector<string>* instructions, int og_num, int num, int depth, int run_count) {
    if (run_count == 0) instructions->push_back("    # Implemented with factoring algorithm\n");
    if (depth>max_depth || run_count > 20) {
        instructions->clear();
        instructions->resize(99999); // Factoring failed
        return;
    };
    if (num <= 1) return;
    // instructions->push_back("    # iteration: " + to_string(num) + " " + to_string(isPrime(num)) + "\n");
    if (isPrime(num) && (num > 9 || num == 7)) {
        // instructions->push_back("    # prime found: " + to_string(num) + "\n");
        num--;
        string temp_register = "%r" + to_string(8+depth) + "d";
        instructions->push_back("    movl	%ecx, " + temp_register + "\n"); // store current x at recursion level
        factoring_getInstructions(instructions, og_num, num, depth+1, run_count+1);
        // instructions->push_back("    # +x: " + to_string(num) + "\n");
        instructions->push_back("	leal	(" + temp_register + ",%ecx,1), %ecx\n"); // add x to achieve prime number multiplication
    } else {
        bool found_factor = false;
        for (int factor : possible_factors) {
            if (num % factor != 0) continue;
            // instructions->push_back("    # found factor: " + to_string(factor) + "\n");
            if (factor == 2 || factor == 4 || factor == 8) {
                instructions->push_back("	leal	(,%ecx, " + to_string(factor) + "), %ecx\n");
            } else if (factor == 3 || factor == 5 || factor == 9) {
                instructions->push_back("	leal	(%ecx,%ecx, " + to_string(factor-1) + "), %ecx\n");
            } else if (factor == 6) {
                instructions->push_back("	leal	(%ecx,%ecx,2), %ecx\n");
                instructions->push_back("	leal	(,%ecx,2), %ecx\n");
            }
            num = floor(num/factor);
            found_factor = true;
            break;
        }
        if (!found_factor) { // if no factors found, treat the same as a prime number
            // instructions->push_back("    # no factors found: " + to_string(num) + "\n");
            num--;
            string temp_register = "%r" + to_string(8+depth) + "d";
            instructions->push_back("    movl	%ecx, " + temp_register + "\n");
            factoring_getInstructions(instructions, og_num, num, depth+1, run_count+1);
            // instructions->push_back("    # +x: " + to_string(num) + "\n");
            instructions->push_back("	leal	(" + temp_register + ",%ecx,1), %ecx\n");
        } else {
            factoring_getInstructions(instructions, og_num, num, depth, run_count+1);
        }
    }
}

int main(int argc, char* argv[]) {
    int num = atoi(argv[1]);
    if (num <= 0) {
        cout << "Constant must be a positive integer, dawg." << endl;
        return 1;
    }
    int num_len = floor(log10(num))+1; // get length of the number
    string label = "_Z" + to_string(10+num_len) + "multiplyBy" + to_string(num) + "P8IntArray"; // Create label based on length of the function name and number
    cout << "	.file	\"multiplyBy" << num << ".cpp\"\n";
    cout << "	.text\n";
    cout << "	.globl	" << label << "\n";
    cout << "	.type	" << label << ", @function\n";
    cout << label << ":\n";
    cout << ".LFB1812:\n";
    cout << "	.cfi_startproc\n";
    cout << "	endbr64\n";
    cout << "	movl	(%rdi), %esi\n";
    cout << "	testl	%esi, %esi\n";
    cout << "	jle	.L1\n";
    cout << "	movl	%esi, %esi\n";
    cout << "	salq	$2, %rsi\n";
    cout << "	movl	$0, %eax\n";
    cout << ".L3:\n";
    cout << "	movq	%rax, %rdx\n";
    cout << "	addq	8(%rdi), %rdx\n";
    cout << "    movl	(%rdx), %ecx\n";
    // cout << "	imull	$" << num << ", (%rdx), %ecx\n";

    vector<string>* instructions;
    vector<string> factoring_instructions;
    vector<string> binary_instructions;
    vector<string> csd_instructions;

    // Run all algorithms
    factoring_getInstructions(&factoring_instructions, num, num, 0, 0);
    binary_getInstructions(&binary_instructions, num);
    CSD_getInstructions(&csd_instructions, num);

    // Print instructions
    instructions = (factoring_instructions.size()/2<binary_instructions.size())? (factoring_instructions.size()/2<csd_instructions.size())? &factoring_instructions : &csd_instructions : &binary_instructions;
    // instructions = &csd_instructions;
    for (string instruction : *instructions) {
        cout << instruction;
    }

    cout << "	movl	%ecx, (%rdx)\n";
    cout << "	addq	$4, %rax\n";
    cout << "	cmpq	%rsi, %rax\n";
    cout << "	jne	.L3\n";
    cout << ".L1:\n";
    cout << "	ret\n";
    cout << "	.cfi_endproc\n";
    cout << ".LFE1812:\n";
    cout << "	.size	" << label << ", .-" << label << "\n"; 
    cout << "	.type	_GLOBAL__sub_I_" << label << ", @function\n";
    cout << "_GLOBAL__sub_I_" << label << ":\n";
    cout << ".LFB2294:\n";
    cout << "	.cfi_startproc\n";
    cout << "	endbr64\n";
    cout << "	pushq	%rbx\n";
    cout << "	.cfi_def_cfa_offset 16\n";
    cout << "	.cfi_offset 3, -16\n";
    cout << "	leaq	_ZStL8__ioinit(%rip), %rbx\n";
    cout << "	movq	%rbx, %rdi\n";
    cout << "	call	_ZNSt8ios_base4InitC1Ev@PLT\n";
    cout << "	leaq	__dso_handle(%rip), %rdx\n";
    cout << "	movq	%rbx, %rsi\n";
    cout << "	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi\n";
    cout << "	call	__cxa_atexit@PLT\n";
    cout << "	popq	%rbx\n";
    cout << "	.cfi_def_cfa_offset 8\n";
    cout << "	ret\n";
    cout << "	.cfi_endproc\n";
    cout << ".LFE2294:\n";
    cout << "	.size	_GLOBAL__sub_I_" << label << ", .-_GLOBAL__sub_I_" << label << "\n";
    cout << "	.section	.init_array,\"aw\"\n";
    cout << "	.align 8\n";
    cout << "	.quad	_GLOBAL__sub_I_" << label << "\n";
    cout << "	.local	_ZStL8__ioinit\n";
    cout << "	.comm	_ZStL8__ioinit,1,1\n";
    cout << "	.hidden	__dso_handle\n";
    cout << "	.ident	\"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0\"\n";
    cout << "	.section	.note.GNU-stack,\"\",@progbits\n";
    cout << "	.section	.note.gnu.property,\"a\"\n";
    cout << "	.align 8\n";
    cout << "	.long	1f - 0f\n";
    cout << "	.long	4f - 1f\n";
    cout << "	.long	5\n";
    cout << "0:\n";
    cout << "	.string	\"GNU\"\n";
    cout << "1:\n";
    cout << "	.align 8\n";
    cout << "	.long	0xc0000002\n";
    cout << "	.long	3f - 2f\n";
    cout << "2:\n";
    cout << "	.long	0x3\n";
    cout << "3:\n";
    cout << "	.align 8\n";
    cout << "4:\n";
}