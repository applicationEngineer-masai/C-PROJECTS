	.file	"dynamicMemoryAlloc.c"
	.text
	.section	.rodata
.LC0:
	.string	"%i\n"
.LC1:
	.string	"ptr[%d] = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$12, %edi
	call	malloc@PLT
	movq	%rax, -24(%rbp)
	movl	$4, %esi
	movl	$3, %edi
	call	calloc@PLT
	movq	%rax, -16(%rbp)
	movq	-24(%rbp), %rax
	movl	$44, (%rax)
	movq	-24(%rbp), %rax
	addq	$4, %rax
	movl	$55, (%rax)
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movl	$66, (%rax)
	movq	-16(%rbp), %rax
	movl	$88, (%rax)
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movl	$99, (%rax)
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movl	$109, (%rax)
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	addq	$4, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	addq	$8, %rax
	movl	(%rax), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-24(%rbp), %rax
	movl	$24, %esi
	movq	%rax, %rdi
	call	realloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L2
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	jmp	.L3
.L2:
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
.L3:
	movl	$3, -32(%rbp)
	jmp	.L4
.L5:
	movl	-32(%rbp), %eax
	leal	1(%rax), %edx
	movl	-32(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rcx
	movq	-24(%rbp), %rax
	addq	%rax, %rcx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, (%rcx)
	addl	$1, -32(%rbp)
.L4:
	cmpl	$5, -32(%rbp)
	jle	.L5
	movl	$0, -28(%rbp)
	jmp	.L6
.L7:
	movl	-28(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-28(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	addl	$1, -28(%rbp)
.L6:
	cmpl	$5, -28(%rbp)
	jle	.L7
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
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
