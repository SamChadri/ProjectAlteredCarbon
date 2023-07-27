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
	.comm	x,8,8
	movq	$7, %r8
	movq	$9, %r9
	cmpq	%r9, %r8
	setl	%r9b
	andq	$255, %r9
	movq	%r9, x(%rip)
	movq	x(%rip), %r8
	movq	%r8, %rdi
	call	printint
	movq	$10, %r9
	movq	$13, %r10
	cmpq	%r10, %r9
	setg	%r10b
	andq	$255, %r10
	movq	%r10, x(%rip)
	movq	x(%rip), %r9
	movq	%r9, %rdi
	call	printint
	movq	$7, %r10
	movq	$9, %r11
	cmpq	%r11, %r10
	setne	%r11b
	andq	$255, %r11
	movq	%r11, x(%rip)
	movq	x(%rip), %r10
	movq	%r10, %rdi
	call	printint
	movl	$0, %eax
	popq	%rbp
	ret
