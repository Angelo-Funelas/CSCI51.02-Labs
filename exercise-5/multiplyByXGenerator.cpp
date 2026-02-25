#include <iostream>
#include <cmath>
#include <string>
#include <climits>
#include <vector>
#include "IntArray.h"
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void binary_getInstructions(vector<string>* instructions, int num) {
    int bitSize = sizeof(num) * CHAR_BIT;
    int last_shift_i = 0;
    int shift_count = 0;
    for (int i = 0; i < bitSize; i++) {
        int bit = (num >> i) & 1;
        if (bit == 1) {
            string instruction = (shift_count == 0)? "movl":"addl";
            shift_count++;
            int shift_count = i-last_shift_i;
            if (shift_count < 4) {
                instructions->push_back("	leal	(, %ecx, " + to_string((int)(pow(2,shift_count))) + "), %ecx\n");
            } else {
                instructions->push_back("	sall	$" + to_string(shift_count) + ", %ecx\n");
            }
            instructions->push_back("	" + instruction + "	%ecx, %r8d\n");
            last_shift_i = i;
        }
    }
    if (shift_count>1) {
        instructions->push_back("    movl	%r8d, %ecx\n");
    } else {
        instructions->pop_back();
    }
}

int possible_factors[] = {9,8,6,5,4,3,2};
int max_depth = 3;
void factoring_getInstructions(vector<string>* instructions, int og_num, int num, int depth, int run_count) {
    if (depth>max_depth || run_count > 20) {
        instructions->clear();
        cout << "	# Falling back to binary solution" << endl;
        binary_getInstructions(instructions, og_num);
        return;
    };
    if (num <= 1) return;
    // instructions->push_back("    # iteration: " + to_string(num) + " " + to_string(isPrime(num)) + "\n");
    if (isPrime(num) && (num > 9 || num == 7)) {
        // instructions->push_back("    # prime found: " + to_string(num) + "\n");
        num--;
        string temp_register = "%r" + to_string(8+depth) + "d";
        instructions->push_back("    movl	%ecx, " + temp_register + "\n");
        factoring_getInstructions(instructions, og_num, num, depth+1, run_count+1);
        // instructions->push_back("    # +x: " + to_string(num) + "\n");
        instructions->push_back("	leal	(" + temp_register + ",%ecx,1), %ecx\n");
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
        if (!found_factor) {
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
    int num_len = floor(log10(num))+1;
    string label = "_Z" + to_string(10+num_len) + "multiplyBy" + to_string(num) + "P8IntArray";
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

    factoring_getInstructions(&factoring_instructions, num, num, 0, 0);
    binary_getInstructions(&binary_instructions, num);
    // Print instructions
    instructions = (factoring_instructions.size()<binary_instructions.size())? &factoring_instructions : &binary_instructions;
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