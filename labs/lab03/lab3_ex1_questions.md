1. What do the `.data`, `.word`, `.text` directives mean (i.e. what do you use them for)?

    1. `.data`: Subsequent items tored in Data segment at next available address.
    2. `.word`: Store the listed value9s) as 32 bit words on word boundary.
    3. `.text`: Susequent items (instructions) stored in Text segment at next available address.

2. How do you set a breakpoint in MARS? Set a breakpoint on line 14 and run to it. What is the instruction address? Has line 14 executed yet?

In the execute tab, click on the checkbox on the l.h.s of the line of code. 
The instruction address is 0x00400020. If you set the breakpoint at line 14 it doesn't execute; it breaks after executing line 13. 

3. Once at a breakpoint, how do you continue to execute your code? How do you step through your code? Run the code to completion.

Run -> Go/Step/Backstep, etc. Or keyboard shortcuts, or the buttons in the top panel. 

4. Find the "Run I/O" window. What number did the program output? Which fib number is this?

34, fib #9

5. At what address is n stored in memory? Try finding this by (1) looking at the Data Segment and (2) looking at the machine code (Code column in the Text Segment).

`0x10010010`

6. Without using the "Edit" tab, have the program calculate the 13th fib number by manually modifying this memory location before execution. You may find it helpful to uncheck the "Hexadecimal Values" box at the bottom of the Data Segment.

233
-- program is finished running --

7. How do you view and modify the contents of a register? Reset the simulation (Run-->Reset or F12) and now calculate the 13th fib number by (1) breaking at a well-chosen spot, (2) modifying a single register, and then (3) unsetting the breakpoint.

Double click on the register value in the "Registers" window, then change the value. 

8. Lines 19 and 21 use the syscall instruction. What is it and how do you use it? (Hint: look in Help)

`syscall`: Issue a system call: Execute the system call specified by value in `$v0`. 

```
addi    $a0, $t0, 0 # loads $t0 into the argument value
li      $v0, 1		# service 1 is print integer
syscall			    # prints the value in $a0

li      $v0, 10		# service 10 is exit (terminate execution)
syscall		        # exit
```
