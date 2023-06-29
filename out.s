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
	.comm	fred,8,8
	.comm	jim,8,8
	movq	$5, %r8
	movq	%r8, jim(%rip)
	movq	$12, %r9
	movq	%r9, fred(%rip)
	movq	fred(%rip), %r10
	movq	jim(%rip), %r11
	addq	%r10, %r11
	movq	%r11, %rdi
	call	printint
	movl	$0, %eax
	popq	%rbp
	ret
