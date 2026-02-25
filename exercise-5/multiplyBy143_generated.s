	.file	"multiplyBy143.cpp"
	.text
	.globl	_Z13multiplyBy143P8IntArray
	.type	_Z13multiplyBy143P8IntArray, @function
_Z13multiplyBy143P8IntArray:
.LFB1812:
	.cfi_startproc
	endbr64
	movl	(%rdi), %esi
	testl	%esi, %esi
	jle	.L1
	movl	%esi, %esi
	salq	$2, %rsi
	movl	$0, %eax
.L3:
	movq	%rax, %rdx
	addq	8(%rdi), %rdx
    movl	(%rdx), %ecx
	# Falling back to binary solution
	leal	(, %ecx, 1), %ecx
	movl	%ecx, %r8d
	leal	(, %ecx, 2), %ecx
	addl	%ecx, %r8d
	leal	(, %ecx, 2), %ecx
	addl	%ecx, %r8d
	leal	(, %ecx, 2), %ecx
	addl	%ecx, %r8d
	sall	$4, %ecx
	addl	%ecx, %r8d
    movl	%r8d, %ecx
	movl	%ecx, (%rdx)
	addq	$4, %rax
	cmpq	%rsi, %rax
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE1812:
	.size	_Z13multiplyBy143P8IntArray, .-_Z13multiplyBy143P8IntArray
	.type	_GLOBAL__sub_I__Z13multiplyBy143P8IntArray, @function
_GLOBAL__sub_I__Z13multiplyBy143P8IntArray:
.LFB2294:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	leaq	_ZStL8__ioinit(%rip), %rbx
	movq	%rbx, %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	movq	%rbx, %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	call	__cxa_atexit@PLT
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2294:
	.size	_GLOBAL__sub_I__Z13multiplyBy143P8IntArray, .-_GLOBAL__sub_I__Z13multiplyBy143P8IntArray
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z13multiplyBy143P8IntArray
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04.2) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
