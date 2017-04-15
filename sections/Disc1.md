# CS61c Spring 2015 Discussion 1 – C
## 2. Uncommented Code? Yuck!
The following functions work correctly (note: this does not mean intelligently), but have no comments. Document
the code to prevent it from causing further confusion.

1. foo
```c
/*
 * Sum all the elements in arr
 */
int foo(int *arr, size_t n) {
    return n ? arr[0] + foo(arr + 1, n - 1) : 0;
}
```

2. bar
```c
/*
 * Return a negated count of the occurences of 0 in arr.
 * Eg. bar({ 0, 0, 1, 2, 3}, 5) returns -2
 */
int bar(int *arr, size_t n) {
    int sum = 0, i;
    for (i = n; i > 0; i--) {
        sum += !arr[i - 1];
    }
    return ~sum + 1;
}
```

3. baz
```c
/*
 * Assign x's value to y, and y's value to x.
 * (Seems a bit pointless within the function's scope, mind you)
 */
void baz(int x, int y) {
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}
```

## 3. Programming with Pointers
Implement the following functions so that they perform as described in the comment.

1. Swaps the value of two ints outside of this function.
```c
/* Swaps the value of two ints outside of this function. */
void swap(int *x, int *y) {
    *x = *x ^ *y;
    *y = *x ^ *y;
    *x = *x ^ *y;
}
```

2. Increments the value of an int outside of this function by one. 
```c
/* Increments the value of an int outside of this function by one. */
void increment(int *x) {
    ++*x;
}
```

3. Returns the number of bytes in a string. Does not use strlen. 
```c
/* Returns the number of bytes in a string. Does not use strlen. */
int str_bytes(char *str) {
    int i, result = 0;
    for (i = 0; *(str+i) != '\0'; i++)
        result += sizeof(*(str+1));
    return result;
}
```

## 4. Problem?
The following code segments may contain logic and syntax errors. Find and correct them.

1. Returns the sum of all the elements in SUMMANDS. 
```c
/* Returns the sum of all the elements in SUMMANDS. */
int sum(int* summands, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += *(summands + i);
    return sum;
}
```

2. Increments all the letters in the string STRING
```c
/* Increments all the letters in the string STRING, held in an array of length N.
 * Does not modify any other memory which has been previously allocated. */
void increment(char* string, int n) {
    int i;
    for (i = 0; i < n; i++)
        *(string + i) += 1;
}
```

3. Copies the string SRC to DST. 
```c
/* Copies the string SRC to DST. */
void copy(char* src, char* dst) {
    int i = 0;
    while (src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}
```
