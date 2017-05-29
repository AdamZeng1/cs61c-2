    .text
main:
    move $t0, $s0   # setup t0
    move $t1, $s1   # setup t1
    add $t2, $t0, $t1
    add $t3, $t1, $t2
    add $t4, $t2, $t3
    add $t5, $t3, $t4
    add $t6, $t4, $t5
    add $t7, $t5, $t6
finish:
    li $v0, 1      # print the result
    move $a0, $t7
    syscall
    li $v0, 10     # exit the program
    syscall

