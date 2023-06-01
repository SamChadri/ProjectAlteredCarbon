	.text
.LC0:
	.string	"%d\n"
printint:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	_printf
	nop
	leave
	ret

	.globl	_main
_main:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	$6, %r8
	movq	$2, %r9
	movq	%r8, %rax
	cqo
	idivq	%r9
	movq	%rax, %r8
	movq	%r8, %rdi
	call	printint
	movl	$0, %eax
	popq	%rbp
	ret
