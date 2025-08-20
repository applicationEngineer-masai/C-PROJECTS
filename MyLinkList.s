	.file	"MyLinkList.c"
	.text
	.globl	createDataType
	.type	createDataType, @function
createDataType:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$256, %rsp
	movq	%rdi, -248(%rbp)
	movl	%esi, -252(%rbp)
	movq	%rdx, -160(%rbp)
	movq	%rcx, -152(%rbp)
	movq	%r8, -144(%rbp)
	movq	%r9, -136(%rbp)
	testb	%al, %al
	je	.L2
	movaps	%xmm0, -128(%rbp)
	movaps	%xmm1, -112(%rbp)
	movaps	%xmm2, -96(%rbp)
	movaps	%xmm3, -80(%rbp)
	movaps	%xmm4, -64(%rbp)
	movaps	%xmm5, -48(%rbp)
	movaps	%xmm6, -32(%rbp)
	movaps	%xmm7, -16(%rbp)
.L2:
	movq	%fs:40, %rax
	movq	%rax, -184(%rbp)
	xorl	%eax, %eax
	movl	-252(%rbp), %eax
	movl	%eax, -240(%rbp)
	movl	$16, -208(%rbp)
	movl	$48, -204(%rbp)
	leaq	16(%rbp), %rax
	movq	%rax, -200(%rbp)
	leaq	-176(%rbp), %rax
	movq	%rax, -192(%rbp)
	cmpl	$16, -252(%rbp)
	ja	.L50
	movl	-252(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L5(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L5(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L5:
	.long	.L18-.L5
	.long	.L17-.L5
	.long	.L16-.L5
	.long	.L15-.L5
	.long	.L50-.L5
	.long	.L14-.L5
	.long	.L13-.L5
	.long	.L12-.L5
	.long	.L11-.L5
	.long	.L50-.L5
	.long	.L10-.L5
	.long	.L9-.L5
	.long	.L8-.L5
	.long	.L7-.L5
	.long	.L50-.L5
	.long	.L6-.L5
	.long	.L4-.L5
	.text
.L18:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L19
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L20
.L19:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L20:
	movl	(%rax), %eax
	movb	%al, -224(%rbp)
	jmp	.L21
.L17:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L22
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L23
.L22:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L23:
	movl	(%rax), %eax
	movw	%ax, -224(%rbp)
	jmp	.L21
.L16:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L24
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L25
.L24:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L25:
	movl	(%rax), %eax
	movl	%eax, -224(%rbp)
	jmp	.L21
.L15:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L26
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L27
.L26:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L27:
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	jmp	.L21
.L14:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L28
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L29
.L28:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L29:
	movl	(%rax), %eax
	movb	%al, -224(%rbp)
	jmp	.L21
.L13:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L30
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L31
.L30:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L31:
	movl	(%rax), %eax
	movw	%ax, -224(%rbp)
	jmp	.L21
.L12:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L32
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L33
.L32:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L33:
	movl	(%rax), %eax
	movl	%eax, -224(%rbp)
	jmp	.L21
.L11:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L34
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L35
.L34:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L35:
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	jmp	.L21
.L10:
	movl	-204(%rbp), %eax
	cmpl	$175, %eax
	ja	.L36
	movq	-192(%rbp), %rax
	movl	-204(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-204(%rbp), %edx
	addl	$16, %edx
	movl	%edx, -204(%rbp)
	jmp	.L37
.L36:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L37:
	movsd	(%rax), %xmm0
	cvtsd2ss	%xmm0, %xmm0
	movss	%xmm0, -224(%rbp)
	jmp	.L21
.L9:
	movl	-204(%rbp), %eax
	cmpl	$175, %eax
	ja	.L38
	movq	-192(%rbp), %rax
	movl	-204(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-204(%rbp), %edx
	addl	$16, %edx
	movl	%edx, -204(%rbp)
	jmp	.L39
.L38:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L39:
	movsd	(%rax), %xmm0
	movsd	%xmm0, -224(%rbp)
	jmp	.L21
.L8:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L40
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L41
.L40:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L41:
	movl	(%rax), %eax
	movb	%al, -224(%rbp)
	jmp	.L21
.L7:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L42
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L43
.L42:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L43:
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	jmp	.L21
.L6:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L44
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L45
.L44:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L45:
	movl	(%rax), %eax
	testl	%eax, %eax
	setne	%al
	movb	%al, -224(%rbp)
	jmp	.L21
.L4:
	movl	-208(%rbp), %eax
	cmpl	$47, %eax
	ja	.L46
	movq	-192(%rbp), %rax
	movl	-208(%rbp), %edx
	movl	%edx, %edx
	addq	%rdx, %rax
	movl	-208(%rbp), %edx
	addl	$8, %edx
	movl	%edx, -208(%rbp)
	jmp	.L47
.L46:
	movq	-200(%rbp), %rax
	leaq	8(%rax), %rdx
	movq	%rdx, -200(%rbp)
.L47:
	movq	(%rax), %rax
	movq	%rax, -224(%rbp)
	jmp	.L21
.L50:
	nop
.L21:
	movq	-248(%rbp), %rcx
	movq	-240(%rbp), %rax
	movq	-232(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-224(%rbp), %rax
	movq	-216(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	-184(%rbp), %rax
	subq	%fs:40, %rax
	je	.L49
	call	__stack_chk_fail@PLT
.L49:
	movq	-248(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	createDataType, .-createDataType
	.section	.rodata
	.align 8
.LC0:
	.string	"Memory allocation failed for new node"
	.text
	.globl	createNode
	.type	createNode, @function
createNode:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$48, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L52
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$0, %eax
	jmp	.L53
.L52:
	movq	-8(%rbp), %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	-8(%rbp), %rax
	movq	$0, 32(%rax)
	movq	-8(%rbp), %rax
.L53:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	createNode, .-createNode
	.globl	appendNode
	.type	appendNode, @function
appendNode:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	16(%rbp), %rax
	movq	24(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	call	createNode
	addq	$32, %rsp
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L60
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L57
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, (%rax)
	jmp	.L54
.L57:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, -16(%rbp)
	jmp	.L58
.L59:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
.L58:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	testq	%rax, %rax
	jne	.L59
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, 32(%rax)
	jmp	.L54
.L60:
	nop
.L54:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	appendNode, .-appendNode
	.section	.rodata
.LC1:
	.string	"%d"
.LC2:
	.string	"%lld"
.LC3:
	.string	"%u"
.LC4:
	.string	"%llu"
.LC5:
	.string	"%.6f"
.LC6:
	.string	"%.12lf"
.LC7:
	.string	"%c"
.LC8:
	.string	"(null)"
.LC9:
	.string	"%s"
.LC10:
	.string	"true"
.LC11:
	.string	"false"
.LC12:
	.string	"%p"
.LC13:
	.string	"(unknown type)"
	.text
	.globl	printData
	.type	printData, @function
printData:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$128, %edi
	call	malloc@PLT
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jne	.L62
	movl	$0, %eax
	jmp	.L63
.L62:
	movl	16(%rbp), %eax
	cmpl	$16, %eax
	ja	.L64
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	.L66(%rip), %rax
	movl	(%rdx,%rax), %eax
	cltq
	leaq	.L66(%rip), %rdx
	addq	%rdx, %rax
	notrack jmp	*%rax
	.section	.rodata
	.align 4
	.align 4
.L66:
	.long	.L81-.L66
	.long	.L80-.L66
	.long	.L79-.L66
	.long	.L78-.L66
	.long	.L77-.L66
	.long	.L76-.L66
	.long	.L75-.L66
	.long	.L74-.L66
	.long	.L73-.L66
	.long	.L72-.L66
	.long	.L71-.L66
	.long	.L70-.L66
	.long	.L69-.L66
	.long	.L68-.L66
	.long	.L64-.L66
	.long	.L67-.L66
	.long	.L65-.L66
	.text
.L81:
	movzbl	32(%rbp), %eax
	movsbl	%al, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC1(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L80:
	movzwl	32(%rbp), %eax
	movswl	%ax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC1(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L79:
	movl	32(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC1(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L78:
	movq	32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC2(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L77:
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC2(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L76:
	movzbl	32(%rbp), %eax
	movzbl	%al, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L75:
	movzwl	32(%rbp), %eax
	movzwl	%ax, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L74:
	movl	32(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC3(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L73:
	movq	32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC4(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L72:
	movq	32(%rbp), %rax
	movq	40(%rbp), %rdx
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC4(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L71:
	movss	32(%rbp), %xmm0
	pxor	%xmm1, %xmm1
	cvtss2sd	%xmm0, %xmm1
	movq	%xmm1, %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC5(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	snprintf@PLT
	jmp	.L82
.L70:
	movq	32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %xmm0
	leaq	.LC6(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	snprintf@PLT
	jmp	.L82
.L69:
	movzbl	32(%rbp), %eax
	movsbl	%al, %edx
	movq	-8(%rbp), %rax
	movl	%edx, %ecx
	leaq	.LC7(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L68:
	movq	32(%rbp), %rax
	testq	%rax, %rax
	je	.L83
	movq	32(%rbp), %rax
	jmp	.L84
.L83:
	leaq	.LC8(%rip), %rax
.L84:
	movq	-8(%rbp), %rdi
	movq	%rax, %rcx
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdx
	movl	$128, %esi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L67:
	movzbl	32(%rbp), %eax
	testb	%al, %al
	je	.L85
	leaq	.LC10(%rip), %rax
	jmp	.L86
.L85:
	leaq	.LC11(%rip), %rax
.L86:
	movq	-8(%rbp), %rdi
	movq	%rax, %rcx
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdx
	movl	$128, %esi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L65:
	movq	32(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rdx, %rcx
	leaq	.LC12(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	jmp	.L82
.L64:
	movq	-8(%rbp), %rax
	leaq	.LC13(%rip), %rdx
	movl	$128, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	snprintf@PLT
	nop
.L82:
	movq	-8(%rbp), %rax
.L63:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	printData, .-printData
	.section	.rodata
.LC14:
	.string	"NULL"
.LC15:
	.string	"[%s]"
.LC16:
	.string	"->"
.LC17:
	.string	"->NULL"
	.text
	.globl	printNode
	.type	printNode, @function
printNode:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L90
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	jmp	.L87
.L93:
	movq	-16(%rbp), %rcx
	subq	$32, %rsp
	movq	%rsp, %rsi
	movq	(%rcx), %rax
	movq	8(%rcx), %rdx
	movq	%rax, (%rsi)
	movq	%rdx, 8(%rsi)
	movq	16(%rcx), %rax
	movq	24(%rcx), %rdx
	movq	%rax, 16(%rsi)
	movq	%rdx, 24(%rsi)
	call	printData
	addq	$32, %rsp
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L91
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC15(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L91:
	movq	-16(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	je	.L90
	leaq	.LC16(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
.L90:
	cmpq	$0, -16(%rbp)
	jne	.L93
	leaq	.LC17(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L87:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	printNode, .-printNode
	.globl	free_linkedlist
	.type	free_linkedlist, @function
free_linkedlist:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	jmp	.L95
.L96:
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	32(%rax), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
.L95:
	cmpq	$0, -24(%rbp)
	jne	.L96
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	free_linkedlist, .-free_linkedlist
	.section	.rodata
.LC19:
	.string	"Hello World"
.LC20:
	.string	"Linked List contents: "
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$224, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movq	$0, -216(%rbp)
	leaq	-208(%rbp), %rax
	movl	$42, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-208(%rbp), %rax
	movq	-200(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-192(%rbp), %rax
	movq	-184(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	-176(%rbp), %rax
	movq	.LC18(%rip), %rdx
	movq	%rdx, %xmm0
	movl	$10, %esi
	movq	%rax, %rdi
	movl	$1, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-176(%rbp), %rax
	movq	-168(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-160(%rbp), %rax
	movq	-152(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	-144(%rbp), %rax
	movl	$65, %edx
	movl	$12, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-144(%rbp), %rax
	movq	-136(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-128(%rbp), %rax
	movq	-120(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	-112(%rbp), %rax
	leaq	.LC19(%rip), %rdx
	movl	$13, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-112(%rbp), %rax
	movq	-104(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-96(%rbp), %rax
	movq	-88(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	-80(%rbp), %rax
	movl	$1, %edx
	movl	$15, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-80(%rbp), %rax
	movq	-72(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-64(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	-48(%rbp), %rax
	movl	$0, %edx
	movl	$15, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	createDataType
	leaq	-216(%rbp), %rsi
	subq	$32, %rsp
	movq	%rsp, %rcx
	movq	-48(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, (%rcx)
	movq	%rdx, 8(%rcx)
	movq	-32(%rbp), %rax
	movq	-24(%rbp), %rdx
	movq	%rax, 16(%rcx)
	movq	%rdx, 24(%rcx)
	movq	%rsi, %rdi
	call	appendNode
	addq	$32, %rsp
	leaq	.LC20(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	printNode
	movq	-216(%rbp), %rax
	movq	%rax, %rdi
	call	free_linkedlist
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L99
	call	__stack_chk_fail@PLT
.L99:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC18:
	.long	1610612736
	.long	1074339512
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
