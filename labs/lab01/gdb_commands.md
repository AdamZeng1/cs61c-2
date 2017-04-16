## More gdb commands
Learning these commands will prove useful for the rest of this lab, and your C programming career in general. Create a text file containing answers to the following questions:

1. How do you pass command line arguments to a program when using gdb?

```sh
(gdb) run arglist
```

2. How do you set a breakpoint which only occurs when a set of conditions is true (e.g. when certain variables are a certain value)?

```sh
(gdb) b [file:]line
Breakpoint 1 at 0x40059e: [file], line.
(gdb) cond 1 [expr]
```

3. How do you execute the next line of C code in the program after stopping at a breakpoint?

```sh
(gdb) n
```

4. If the next line of code is a function call, you'll execute the whole function call at once if you use your answer to #3. How do you tell GDB that you want to debug the code inside the function instead?

```sh
(gdb) s
```

5. How do you resume the program after stopping at a breakpoint?

```sh
(gdb) c
```

6. How can you see the value of a variable (or even an expression like 1+2) in gdb?

```sh
(gdb) p expr
```

7. How do you configure gdb so it prints the value of a variable after every step?

```sh
(gdb) display expr
```

8. How do you print a list of all variables and their values in the current function?

```sh
(gdb) info locals
```

9. How do you exit out of gdb?

```sh
(gdb) quit
```

