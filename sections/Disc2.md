# CS61c Spring 2015 Discussion 2 – C Memory Management & MIPS
## 1. C Memory Management

1. In which memory sections (**C**ODE, S**T**ATIC, **H**EAP, **S**TACK) do the following reside?

```c
#define C 2
const int val = 16;
char arr[] = "foo";
void foo(int arg){
    char *str = (char *) malloc (C*val);
    char *ptr = arr;
}
```

`arg` [ S ] | `str` [ S ]
`arr` [ T ] | `*str` [ H ]
`val` [ T ] |  `C` [ C ] 

2. What is wrong with the C code below?

```c
int* ptr = malloc(4 * sizeof(int));
if(extra_large) ptr = malloc(10 * sizeof(int));
return ptr;
```
There's a memory leak. If `extra_large` is true, more space is allocated, but the previously allocated space is not freed, and the pointer to it is lost.
Also, `malloc()` returns `void*`, so it should be cast to `(int *)`.

3. Write code to prepend (add to the start) to a linked list, and to free/empty the entire list.

Note: list points to the first element of the list, or to NULL if the list is empty.

```c
struct ll_node { 
    struct ll_node* next; 
    int value; 
};

void free_ll(struct ll_node** list)  {
    struct ll_node *next, *this = *list;
    while(this != NULL) {
        next = this->next;
        free(this);
        this = next;
    }
}

void prepend(struct ll_node** list, int value) {
    struct ll_node *node = (struct ll_node *) malloc(sizeof(struct ll_node));
    node->value = value;
    node->next = *list;
    *list = node;
}
```

## 2. MIPS Intro
1. Assume we have an array in memory that contains `int* arr = {1,2,3,4,5,6,0}`. Let the value of `arr`
be a multiple of 4 and stored in register `$s0`. What do the following programs do?

a) 

```
lw $t0, 12($s0)    # Loads arr[3] (4); could also use lh, lb;
add $t1, $t0, $s0  # $t1 = $s0+4, i.e. arr[1] 
sw $t0, 4($t1)     # arr[2] =  4
```

b) 
```
addiu $s1, $s0, 27 # add 27 to the memory address in $s0
lh $t0, -3($s1)    # load 24($s0) to $t0; could also use lw, lb
```

c) 
```
addiu $s1, $s0, 24 # add 27 to the memory address in $s0
lh $t0$, -3($s1)   # register alignment error?
```

d) 
```
addiu $t0, $0, 12  # sets register $t0 to 12
sw $t0, 6($s0)     # register alignment error; 
```

e) 
```
addiu $t0, $0, 8   # sets register $t0 to 8
sw $t0, -4($s0)    # index out of bounds
```

f) 
```
addiu $s1, $s0, 10 # sets $s1 to the memory address at $s0 + 10
addiu $t0, $0, 6   # sets $t0 to 6
sw $t0, 2($s1)     # saves arr[3] = 6; could also use sh, sb;
```

2. In 1), what other instructions could be used in place of each load/store without alignment errors?


3. What are the instructions to branch to label: on each of the following conditions?

    - `$s0 < $s1` 

```
slt $t0, $s0, $s1       # $t0 = 1 if $s0 < $s1, else 0
bne $t0, $zero, label   # go to label if $t0 != 0
```

    - `$s0 <= $s1` 

```
slt $t0, $s1, $s0       # $t0 = 1 if $s0 > $s1
beq $t0, $zero, label   # go to label if $t0 == 0
```

    - `$s0 > 1` 

```
slti $t0, $s0, 1       # $t0 = 1 if <1
bne $t0, $zero, label
```

    - `$s0 >= 1`

```
slti $t0, $s0, 1       # $t0 = 1 if <1
beq $t0, $zero, label
```

## 3. Translating between C and MIPS
Translate between the C and MIPS code. You may want to use the MIPS Green Sheet as a reference. In all of
the C examples, we show you how the different variables map to registers – you don’t have to worry about the
stack or any memory-related issues.
### 1:C 
```c
// $s0 -> a, $s1 -> b
// $s2 -> c, $s3 -> z
int a = 4, b = 5, c = 6, z;
z = a + b + c + 10;
```

### 1:MIPS
```
addi $s0, $zero, 4  # a = 4
addi $s1, $zero, 5  # b = 5
addi $s2, $zero, 6  # c = 6
add $t0, $s0, $s1   # temp = a + b
add $t0, $t0, $s2   # temp += c
addi $s3, $t0, 10   # z = temp + 10
```

### 2:C
```c
// $s0 -> int * p = intArr;
// $s1 -> a;
*p = 0;
int a = 2;
p[1] = p[a] = a;
```

### 2:MIPS
```
sw $zero, 0($s0)    # *p = 0
addi $s1, $zero, 2  # a = 2
sw $s1, 4($s0)      # p[1] = a
sll $t0, $s1, 2     # get offset of a (2 * 4)
add $t1, $t0, $s0   # store the address of p[a] in $t1
sw $s1, 0($t1)      # p[a] = a
```

### 3:C
```c
// $s0 -> a, $s1 -> b
int a = 5, b = 10;
if(a + a == b) {
    a = 0;
} else {
    b = a - 1;
}
```

### 3:MIPS
```
    addi $s0, $zero, 5   # a = 5
    addi $s1, $zero, 10  # b = 10
    add $t0, $s0, $s0    # $t0 = a + a
    bne $t0, $s1, else   # go to else if (a+a != b)
    addi $s0, $zero, 0   # a = 0
    j exit
else:
    addi $s1, $s0, -1    # b = a - 1
exit:
```

### 4:C
```c
unsigned int a = 0, b = 1;
while (a != 30) {
    b += b;
    a++;
}
```

### 4:MIPS
```
    addiu $s0, $0, 0
    addiu $s1, $0, 1
    addiu $t0, $0, 30
loop:
    beq $s0, $t0, exit
    addu $s1, $s1, $s1
    addiu $s0, $s0, 1
    j loop
exit:
```

### 5:C
```c
// $a0 -> n, $v0 -> sum
int sum;
for(sum=0;n>0;sum+=n--);
```

### 5:MIPS
```
    addi $v0, $zero, 0
loop:
    slt $t0, $zero, $a0   # $t0 = 1 if n > 0
    beq $t0, $zero, exit  # exit if n <= 0
    add $v0, $v0, $a0     # sum = sum + n
    addi $a0, $a0, -1     # n = n - 1
    j loop
exit:
```
