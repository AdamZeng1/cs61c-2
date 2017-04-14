# CS61C Spring 2015 Discussion 0 – Number Representation
This is a simplified document, containing only Q&As. The full set of explanations is [here](http://inst.eecs.berkeley.edu/~cs61c/sp15/disc/00/Disc0.pdf).

## 1 Unsigned Integers
1. Convert the following numbers from their initial radix into the other two common radices:

binary | hexadecimal | decimal
-------|-------------|--------
**0b10010011** | 0x93 | 147
0b1101001110101101 | **0xD3AD** | 54189
0b00111111 | 0x3F | **63**
**0b00100100** | 0x24 | 36
0b1011001100111111 | **0xB33F** | 45887
0b0 | 0x0 | **0**
0b00100111 | 0x27 | **39**
0b0111111011000100 | **0x7EC4** | 32452
0b000110110101 | 0x1B5 | **437**

2. Write the following numbers using IEC prefixes: 

power of 2 | IEC
-----------|----
2^16 | 64 Ki
2^34 | 16 Gi
2^27 | 128 Mi
2^61 | 2 Ei
2^43 | 8 Ti
2^47 | 128 Ti
2^36 | 64 Gi
2^58 | 256 Pi

3. Write the following numbers as powers of 2: 

IEC | power of 2 
----|-----------
2 Ki | 2^11
256 Pi | 2^58
512 Ki | 2^19
64 Gi | 2^36
16 Mi | 2^24
128 Ei | 2^67

## 2 Signed Integers
For the following questions assume an 8 bit integer. Answer each question for the case of a two’s complement
number and unsigned number.
1. What is the largest integer? The largest integer + 1?
    a. Signed: 0b01111111, 127. Unsigned: 0b11111111, 255.
    b. Signed: 0b10000001, -128. Unsigned: 0b00000000, 0.

2. How do you represent the numbers 0, 1, and -1?
    a. Signed: 0b00000000, 0b00000001, 0b11111111
    b. Unsigned: 0b00000000, 0b00000001, can't be done.

3. How do you represent 17, -17?
    a. Signed: 0b00010001, 0b11101111
    b. Unsigned: 0b00010001, can't be done.

4. What is the largest integer that can be represented by any encoding scheme that only uses 8 bits?
    256

5. Prove that the two’s complement inversion trick is valid (i.e. that x and x + 1 sum to 0).
        0b0001
    +0b1111
        10000 = 0b0000 = 0

6. Explain where each of the three radices shines and why it is preferred over other bases in a given context.
    Base 10 is clearly the most natural for human readability. Base 2 make the most sense for electronics and computers, and for representing data in memory. Base 16 is a more compact, human readable number than base 2, but is very easily converted between the two. 
    

## 3 Counting
1. If the value of a variable is 0, π or e, what is the minimum number of bits needed to represent it?
    0: 1 bit
    π: an infinite number of bits, if you want to represent pi accurately 
    e: I assume this is a char. The limit would be the number of different chars you'd like to represent. ASCII allows for 8 bits, or 256 chars. If you only wanted to represent a set of 1 char, "e", 1 bit would suffice. To represent the letters of the alphabet in upper and lower case, 6 bits would suffice.
2. If we need to address 3 TiB of memory and we want to address every byte of memory, how long does an address need to be?
    3,298,534,883,328
3. If the only value a variable can take on is e, how many bits are needed to represent it?
    1 bit
