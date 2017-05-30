# CS61C Spring 2015 Discussion 4 – MIPS Procedures & CALL
## 1 MIPS Control Flow
There are only two instructions necessary for creating and calling functions: jal and jr. If you follow register conventions when calling functions, you will be able to write much simpler and cleaner MIPS code.

## 2 Conventions
1. How should $sp be used? When do we add or subtract from $sp?

    1. To grow the stack, subtract from `$sp`; adding to `$sp` pops items from the stack. 

2. Which registers need to be saved or restored before using jr to return from a function?

    1. The callee must preserve saved registers (`$s0`-`$s7`), so they must be restored before using `jr`.
    2. The `$sp` should be restored, after pushed values above have been popped. 

3. Which registers need to be saved before using jal?

    1. The caller must preserve `$a0`-`$a3`, `$ra`, and any temporary registers (`$t0`-`$t9`) that it may need after the procedure it's about to call is returned. 

4. How do we pass arguments into functions?

    1. With the argument registers, `$a0`-`$a3`. 

5. What do we do if there are more than four arguments to a function?

    1. Push additional arguments to the stack.

6. How are values returned by functions?

    1. With the return value register/s, `$v0` and `$v1`.

When calling a function in MIPS, who needs to save the following registers to the stack? Answer “caller” for the procedure making a function call, “callee” for the function being called, or “N/A” for neither.

$0 | $v\* | $a\* | $t\* | $s\* | $sp | $ra 
---|---|---|---|---|---|---|---
n/a | caller | caller | caller | callee | n/a | caller | 

Now assume a function foo (which may be called from a main fucntion) calls another function bar, which is known to call some other functions. foo takes one argument and will modify and use $t0 and $s0. bar takes two arguments, returns an integer, and uses $t0-$t2 and $s0-$s1. In the boxes below, draw a possible ordering of the stack just before bar calls a function. The top left box is the address of $sp when foo is first called, and the stack goes downwards, continuing at each next column. Add ‘(f)’ if the register is stored by foo and ‘(b)’ if the register is stored by bar. The first one is written in for you.

### Stack, just before bar calls a function:
1. $ra (f)
2. $s0 (f)
3. $t0 (f)
4. $a0 (f)
5. $ra (b)
6. $s0 (b)
7. $s1 (b)
8. $a0 (b)
9. $a1 (b)
10. ... 

## 3 A Guide to Writing Functions

```
FunctionFoo: # PROLOGUE
# begin by reserving space on the stack
addiu $sp, $sp, -FrameSize

# now, store needed registers
sw $ra, 0($sp)
sw $s0, 4($sp)
...
# BODY
...
# EPILOGUE
# restore registers
lw $s0 4($sp)
lw $ra 0($sp)

# release stack spaces
addiu $sp, $sp, FrameSize

# return to normal execution
jr $ra
```

## 4 C to MIPS
1. Assuming $a0 and $a1 hold integer pointers, swap the values they point to via the stack and return control.

```c
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

```
swap:
    addiu $sp, $sp, -4
    lw $t0, 0($a0)  # load the value $a0 points to 
    sw $t0, 0($sp)  # tmp = *a
    lw $t0, 0($a1)  # load the value $a1 points to
    sw $t0, 0($a0)  # *a = *b
    lw $t0, 0($sp)  # fetch $a0's value back from the stack
    sw $t0, 0($a1)  # *b = tmp
    addiu $sp, $sp, 4
    jr $ra
```

Without using the stack:
```
swap: 
    lw $t0, 0($a0)  # load *a
    lw $t1, 0($a1)  # load *b
    sw $t1, 0($a0)  # *a = *b
    sw $t0, 0($a1)  # *b = tmp
    jr $ra
```

2. Translate the following algorithm that finds the sum of the numbers from 0 to N to MIPS assembly. Assume $s0 holds N, $s1 holds sum, and that N is greater than or equal to 0.

```c
int sum = 0;

if (N==0) return 0;

while (N != 0) {
    sum += N;
    N--;
}
return sum;
```

```
sum: 
    # I assume that $s0 (N) is already holding a value >= 0
    xor $s1, $s1, $s1  # sum = 0
loop:
    beq $s0, $zero, finish
    add $s0, $s0, $s1
    subi $s0, $s0, 1
    j loop
finish:
    move $v0, $s1
    jr $ra
```

3. What must be done to make the adding algorithm from the previous part into a callable MIPS function?

    1. Add a label. If it needs to be callable from other modules, add the assembler directive `.globl sum`.
    2. Push and pop the `$s*` & `$ra` registers to/from the stack.


## 5 Compile, Assemble, Link, Load, and Go!

### 5.2 Exercises
1. What is the Stored Program concept and what does it enable us to do?

    1. It's the paradigm in which programming is done in memory (software), rather than hardware. It allows any program to be stored as data; a series of 1's and 0's. 

2. How many passes through the code does the Assembler have to make? Why?

    1. Two. The first pass finds the labels in the code so that symbolic names and the addresses they correspond to are known. This is important because assembly labels may be used before they are defined (forward references). The second pass translates instructions to machine language, and outputs an object file. 

3. What are the different parts of the object files output by the Assembler?

    1. Header
    2. Text segment
    3. Data segment
    4. Relocation Information
    5. Symbol table
    6. Debugging information

4. Which step in CALL resolves relative addressing? Absolute addressing?

    1. Relative addressing: The assembler
    2. Absolute addressing: The linker

5. What step in CALL may make use of the $at register?
    
    1. The assembler

6. What does RISC stand for? How is this related to pseudoinstructions?

    1. Reduced Instruction Set Computer. The basic idea is to minimize the instruction set to make hardward design easier, and processors faster. The pseudoinstructions are more human friendly instructions that are understood by the Assembler, but don't have any real hardware instructions. The Assembler translates pseudoinstructions into real instructions.

