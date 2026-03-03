	.file	"main.c"
	.intel_syntax noprefix
	.text
	.globl	fill_array
	.type	fill_array, @function
fill_array:
.LFB6:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	mov	QWORD PTR -24[rbp], rdi
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L3:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	mov	rax, QWORD PTR -24[rbp]
	add	rax, rdx
	mov	edx, DWORD PTR -4[rbp]
	add	edx, 1
	mov	DWORD PTR [rax], edx
	add	DWORD PTR -4[rbp], 1
.L2:
	cmp	DWORD PTR -4[rbp], 4
	jle	.L3
	nop
	nop
	pop	rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	fill_array, .-fill_array
	.section	.rodata
.LC0:
	.string	"%d "
	.text
	.globl	print_array
	.type	print_array, @function
print_array:
.LFB7:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 32
	mov	QWORD PTR -24[rbp], rdi
	mov	DWORD PTR -4[rbp], 0
	jmp	.L5
.L6:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*4]
	mov	rax, QWORD PTR -24[rbp]
	add	rax, rdx
	mov	eax, DWORD PTR [rax]
	mov	esi, eax
	lea	rax, .LC0[rip]
	mov	rdi, rax
	mov	eax, 0
	call	printf@PLT
	add	DWORD PTR -4[rbp], 1
.L5:
	cmp	DWORD PTR -4[rbp], 4
	jle	.L6
	mov	edi, 10
	call	putchar@PLT
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	print_array, .-print_array
	.section	.rodata
.LC1:
	.string	"Failed : mmap"
.LC2:
	.string	"Before Fork"
.LC3:
	.string	"From Child"
.LC4:
	.string	"Child terminated"
.LC5:
	.string	"From Parent"
.LC6:
	.string	"Error"
	.text
	.globl	main
	.type	main, @function
main:
.LFB8:
	.cfi_startproc
	endbr64
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 16
	mov	r9d, 0
	mov	r8d, -1
	mov	ecx, 33
	mov	edx, 3
	mov	esi, 20
	mov	edi, 0
	call	mmap@PLT
	mov	QWORD PTR -8[rbp], rax
	cmp	QWORD PTR -8[rbp], -1
	jne	.L8
	lea	rax, .LC1[rip]
	mov	rdi, rax
	call	perror@PLT
	mov	edi, 1
	call	exit@PLT
.L8:
	mov	rax, QWORD PTR -8[rbp]
	mov	rdi, rax
	call	fill_array
	lea	rax, .LC2[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rax, QWORD PTR -8[rbp]
	mov	rdi, rax
	call	print_array
	call	fork@PLT
	mov	DWORD PTR -12[rbp], eax
	cmp	DWORD PTR -12[rbp], 0
	jne	.L9
	lea	rax, .LC3[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rax, QWORD PTR -8[rbp]
	add	rax, 8
	mov	DWORD PTR [rax], 8
	mov	rax, QWORD PTR -8[rbp]
	mov	rdi, rax
	call	print_array
	mov	edi, 0
	call	exit@PLT
.L9:
	cmp	DWORD PTR -12[rbp], 0
	jle	.L10
	mov	edi, 0
	call	wait@PLT
	lea	rax, .LC4[rip]
	mov	rdi, rax
	call	puts@PLT
	lea	rax, .LC5[rip]
	mov	rdi, rax
	call	puts@PLT
	mov	rax, QWORD PTR -8[rbp]
	add	rax, 12
	mov	DWORD PTR [rax], 9
	mov	rax, QWORD PTR -8[rbp]
	mov	rdi, rax
	call	print_array
	jmp	.L11
.L10:
	lea	rax, .LC6[rip]
	mov	rdi, rax
	call	puts@PLT
.L11:
	mov	rax, QWORD PTR -8[rbp]
	mov	esi, 20
	mov	rdi, rax
	call	munmap@PLT
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
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
