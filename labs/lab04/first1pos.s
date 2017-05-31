.data
shouldben1:	.asciiz "Should be -1, and firstposshift and firstposmask returned: "
shouldbe0:	.asciiz "Should be 0 , and firstposshift and firstposmask returned: "
shouldbe16:	.asciiz "Should be 16, and firstposshift and firstposmask returned: "
shouldbe31:	.asciiz "Should be 31, and firstposshift and firstposmask returned: "

.text
main:
	la	$a0, shouldbe31
	jal	print_str
	lui	$a0, 0x8000	# should be 31
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	lui	$a0, 0x8000
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldbe16
	jal	print_str
	lui	$a0, 0x0001	# should be 16
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	lui	$a0, 0x0001
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldbe0
	jal	print_str
	li	$a0, 1		# should be 0
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	li	$a0, 1
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	la	$a0, shouldben1
	jal	print_str
	move	$a0, $0		# should be -1
	jal	first1posshift
	move	$a0, $v0
	jal	print_int
	jal	print_space

	move	$a0, $0
	jal	first1posmask
	move	$a0, $v0
	jal	print_int
	jal	print_newline

	li	$v0, 10
	syscall

first1posshift:
    # check zero
    beq $a0, $0, return_zero

	# prologue
    addiu $sp, $sp, -8
    sw $s0, 4($sp)
    sw $s1, 0($sp)

    # body
    addiu $s0, $zero, 31
    lui $s1, 0x8000
shift:
    bgeu $a0, $s1, return_shift
    sll $a0, $a0, 1
    addiu $s0, $s0, -1
    j shift

    # epilogue
return_shift:
    move $v0, $s0
    lw $s1, 0($sp)
    lw $s0, 4($sp)
    addiu $sp, $sp, 8
    jr $ra

first1posmask:
    # check zero
    beq $a0, $0, return_zero

	# prologue
    addiu $sp, $sp, -12
    sw $s0, 8($sp)
    sw $s1, 4($sp)
    sw $s2, 0($sp)

    # body
    addiu $s0, $zero, 31
    lui $s1, 0x8000
mask:
    and $s2, $a0, $s1
    bne $s2, $zero, return_mask
    srl $s1, $s1, 1
    addiu $s0, $s0, -1
    j mask

    # epilogue
return_mask:
    move $v0, $s0
    lw $s2, 0($sp)
    lw $s1, 4($sp)
    lw $s0, 8($sp)
    addiu $sp, $sp, 8
    jr $ra

return_zero:
    addiu $v0, $zero, -1
    jr $ra

print_int:
	move	$a0, $v0
	li	$v0, 1
	syscall
	jr	$ra

print_str:
	li	$v0, 4
	syscall
	jr	$ra

print_space:
	li	$a0, ' '
	li	$v0, 11
	syscall
	jr	$ra

print_newline:
	li	$a0, '\n'
	li	$v0, 11
	syscall
	jr	$ra
