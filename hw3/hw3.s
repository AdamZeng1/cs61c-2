.data
hello:      .asciiz "Hello, World"

.text
main: 
    la      $a0, hello
    jal     string_print_while
    li      $a0, '\n'
    jal     print_char

    la      $a0, hello
    addiu   $a1, $zero, 12
    jal     string_print_for
    li      $a0, '\n'
    jal     print_char

    la      $a0, hello
    jal     string_print_do_while
    li      $a0, '\n'
    jal     print_char

    addiu   $a0, $zero, 12
    jal     fib
    move    $a0, $v0
    jal     print_int
    li      $a0, '\n'
    jal     print_char

    addiu   $s0, $zero, 20   # fib number
    move    $a0, $s0
    jal     make_empty_array
    move    $a0, $s0        # set up fib_memoized args
    move    $a1, $v0        # sp from make_empty_array
    jal     fib_memoized
    addiu   $s0, $s0, 1     # restore the stack
    sll     $s0, $s0, 2
    addu    $sp, $sp, $s0
    move    $a0, $v0        # print result
    jal     print_int
    li      $a0, '\n'
    jal     print_char

    # MARS doesn't like editing the text segment
    # jal     nextshort
    # move    $a0, $v0
    # jal     print_int
    # li      $a0, '\n'   # line break
    # jal     print_char

    addiu   $v0, $0, 10 # exit
    syscall

string_print_while:
    addiu   $sp, $sp, -4
    sw      $ra, 0($sp)

    move    $t0, $a0
while_loop:
    lb      $a0, 0($t0)
    beq     $a0, $zero, return
    jal     print_char
    addiu   $t0, $t0, 1
    j       while_loop
    

string_print_for:
    addiu   $sp, $sp, -8
    sw      $ra, 4($sp)
    sw      $s0, 0($sp)

    move    $t0, $a0        # save a0 to t0 for later reference
    xor     $s0, $s0, $s0   # i = 0
for_loop:
    ble     $a1, $s0, return_for
    addu    $t1, $s0, $t0   # t1 = print_me+i
    lb      $a0, 0($t1)     # print(*(print_me+i))
    jal     print_char
    addiu   $s0, $s0, 1     # i++
    j       for_loop

return_for:
    lw      $s0, 0($sp)
    lw      $ra, 4($sp)
    addiu   $sp, $sp, 8
    jr $ra

string_print_do_while:
    addiu   $sp, $sp, -4
    sw      $ra, 0($sp)

    move    $t0, $a0        # make a temp copy of a0
    lb      $a0, 0($t0)     # if (!(*print_me)) return
    beq     $a0, $zero, return

do_while:
    jal     print_char
    addiu   $t0, $t0, 1
    lb      $a0, 0($t0)
    bne     $a0, $zero, do_while
    # exit loop
    j       return

fib:
    beq     $a0, $zero, return0 # if (n==0)
    addiu   $t0, $zero, 2       # if (n==1)
    blt     $a0, $t0, return1
    
    # prologue
    addiu   $sp, $sp, -12
    sw      $s0, 8($sp)
    sw      $a0, 4($sp)
    sw      $ra, 0($sp)
    
    addiu   $a0, $a0, -1    # fib(n-1)
    jal     fib
    move    $s0, $v0
    
    lw      $a0, 4($sp)
    addiu   $a0, $a0, -2    # fib(n-2)
    jal     fib
    addu    $v0, $v0, $s0
    j       return_fib
    
return0:
    addiu   $v0, $zero, 0
    jr      $ra
return1:
    addiu   $v0, $zero, 1
    jr      $ra
return_fib:
    lw      $ra, 0($sp)
    lw      $a0, 4($sp)
    lw      $s0, 8($sp)
    addiu   $sp, $sp, 12
    jr      $ra

fib_memoized:
    beq     $a0, $zero, return_m_0 # if (n==0)
    addiu   $t0, $zero, 2       # if (n==1)
    blt     $a0, $t0, return_m_1
    sll     $t0, $a0, 2         # if (memolist[n]) 
    addu    $t0, $t0, $a1       # $t0 = memolist+n
    lw      $t0, 0($t0)         # $t0 = *memolist+n
    bne     $t0, $zero, return_memolist
    
    # prologue
    addiu   $sp, $sp, -12
    sw      $s0, 8($sp)
    sw      $a0, 4($sp)
    sw      $ra, 0($sp)
    
    addiu   $a0, $a0, -1    # fib(n-1)
    jal     fib_memoized
    move    $s0, $v0
    
    lw      $a0, 4($sp)
    addiu   $a0, $a0, -2    # fib(n-2)
    jal     fib_memoized
    
    # memoize results
    addu    $v0, $v0, $s0   # set return value
    lw      $t0, 4($sp)     # $t0 =  1st param
    sll     $t0, $t0, 2     # x 4
    addu    $t0, $t0, $a1   # $t0 = memolist+n
    sw      $v0, 0($t0)     # memolist[n] = $v0
    j       return_m_fib
    
return_m_0:
    addiu   $v0, $zero, 0
    jr      $ra
return_m_1:
    addiu   $v0, $zero, 1
    jr      $ra
return_m_fib:
    lw      $ra, 0($sp)
    lw      $a0, 4($sp)
    lw      $s0, 8($sp)
    addiu   $sp, $sp, 12
    jr      $ra
return_memolist:
    move    $v0, $t0
    jr      $ra

nextshort:
    la      $t0, nextshort  
    addiu   $t1, $zero, 0   # "local variable"
    addiu   $t1, $t1, 1     # increment
    addiu   $t2, $t2, 0xFFFF# max short
    bge     $t1, $t2, max_overflow
continue:
    addiu   $t0, $t0, 8     # get addiu instruction address
    sh      $t1, 2($t0)     # change addiu immediate value
    move    $v0, $t1        # return value
    jr      $ra
max_overflow:
    addiu   $t1, $zero, 0
    j       continue

return:
    lw $ra, 0($sp)
    addiu $sp, $sp, 4
    jr $ra

print_char: 
    addiu $v0, $zero, 11
    syscall
    jr $ra

print_int:
    addiu $v0, $zero, 1
    syscall
    jr $ra

make_empty_array:
    addiu   $t0, $a0, 1     # make some room on the stack
    sll     $t0, $t0, 2
    sub     $sp, $sp, $t0 
    xor     $t2, $t2, $t2   # t2 = 0
    addiu   $t0, $t0, -4
zero_vals:
    slt     $t1, $t0, $0    # while t0 >= 0
    beq     $t0, $0, return_arr
    addu    $t3, $sp, $t0   
    sw      $t2, 0($t3)
    addi    $t0, $t0, -4
    j       zero_vals
return_arr:
    move    $v0, $sp
    jr      $ra
