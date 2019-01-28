# BitVector Class - Starting Guide

## Description

BitVector is Hiventive's class to be used to represent and manipulate binary vectors with arbitrary bit width. It was designed for intuitive manipulation while remaining extremely performant in terms of speed and memory. This way, BitVector is suitable for handling intensive binary logic operations and manipulation. This high performance is achieved by leveraging as much as possible native number representation and hardware-implemented instructions.

## Accessing BitVector

BitVector class is declared in `bitvector.h` and is part of namespace `::hv::commmon`.

```cpp
#include "common/bitvector.h"
using namespace ::hv::common;
```

## A Basic How-To

This section develops a demonstration of BitVector syntax and manipulation.

### Initialization, copy and interoperability

Let's start with a few declarations and displays with the following code:

```cpp
// Declarations and initialization
BitVector bv1(12, 0);
BitVector bv2(18, 1748);
BitVector bv3("010101010101010101");

// Display
std::cout << "bv1 = " << bv1 << std::endl;
std::cout << "bv2 = " << bv2 << std::endl;
std::cout << "bv3 = " << bv3 << std::endl;
```

This code outputs:

```bash
# Console output
bv1 = 000000000000
bv2 = 000000011011010100
bv3 = 010101010101010101
```

`x` is a 12-bit BitVector worth 0, `y` is a 18-bit BitVector worth 1748 and `z` is an 18-bit BitVector worth 87381. Everytime a BitVector is created, its size and initial value must be specified, except when initiated from a `std::string` for which the size is implicitely set to the string's length.

BitVector's are set from `std::string` MSB (Most Significant Bit) first, and also displayed the same way.

<u>Note:</u> from this point, code used to display values won't be listed anymore for readability purpose.

Be careful, when initiating a BitVector the following way,

```cpp
// Dangerous initialization
BitVector bv4(12);
```

a BitVector of size 12 is __NOT__ created as you could have expected. If your host machine interprets 12 as an `int`, a 32-bit BitVector worth 12 is created as displayed below.

```bash
# Console output
bv4 = 00000000000000000000000000001100
```

If a BitVector is initiated from a negative integer, two's complement is used.

```cpp
// Initialization from negative number
BitVector bv5(18, -1843);
```

```bash
# Console output
bv5 = 111111100011001101
```

A BitVector can be created from another BitVector by copy the following way. If we have an 8-bit BitVector `x` 

```cpp
BitVector x(8, 0xF0);
```

and we want to create another 8-bit BitVector `y` taking the value of `x`, we can directly use the copy constructor:

```cpp
BitVector y(x);
```

```bash
# Console output
x = 11110000
y = 11110000
```

<u>Note:</u> Copy constructor must only be used with *pure* BitVector, and never using bit and sub-vector selection (see  [Bit and Sub-Vector Selection section](#Bit-And-Sub-Vector-Selection)).

A BitVector can be assigned from any native source (signed and unsigned integers from 8 to 64 bits), and also from any `std::string` containing only characters `0` and `1`.

```cpp
// Assignment from int
x = 0x55;

// Assignment from BitVector
y = x;

// Assignment from std::string
x = "00110011"; // or x.fromString("00110011");
```

```bash
# Console output
x = 01010101
y = 01010101
x = 00110011
```

It can also be implicitly transformed into any native type by construction or assignment.

```cpp
// unsigned char initialization from BitVector
hvuint8_t z1(x);

// signed int assignment from BitVector
hvint32_t z2;
z2 = x;
```

```bash
# Console output
z1 = 51
z2 = 51
```

For `std::string`, a string can be directly constructed by construction from a BitVector. However, assigning a `std::string` must be done explicitely. E.g:

```cpp
// std::string initialization from BitVector
std::string str1(x);

// std::string assignment from BitVector
std::string str2;
str2 = std::string(x); // or str2 = x.toString();
```

```bash
# Console output
str1 = 00110011
str2 = 00110011
```

It is advised to use BitVector assignment from (resp. cast to) `std::string` only for debugging or demonstration. Using native types is much faster.

### Bit and Sub-Vector Selection

BitVectors can be manipulated by bit position or by slice as left-value or right-value, to enable intuitive binary values manipulation as it would be in hardware design language such as VHDL.

Bits are ordered from 0 (LSB) to N-1 (MSB) where N is the size of the considered BitVector instance. 

Accessing the bit of significance `i` of BitVector `bv` is performed by the operation `x[i]`.

Accessing the slice containing all bits from `j`  to `k` is performed by the operation `x(j,k)` or `x(k,j)` (strictly equivalent).

Any operation available on a *pure* BitVector is also available on a single bit or a slice. Which is very cool. Really.

Let's take a look at simple bit/slice read/write operations. First, let's declare two BitVectors.

```cpp
// BitVector declarations
BitVector x(8, 0), y(12, 0xFFF);
```

```bash
# Console output
x = 00000000
y = 111111111111
```

We now want the bit of significance 2 of `x` to be set to the value of the bit of significant 5 of `y`, which is simply performed the following way:

```cpp
x[2] = y[5];
```

```bash
# Console output
x = 00000100
y = 111111111111
```

If we want to put a 3-bit slice of `x` in `y` we can do:

```cpp
y(3,0) = x(7,4);
// or y(3,0) = x(4,7);
// or y(0,3) = x(7,4);
// or y(0,3) = x(4,7);
```

```bash
# Console output
x = 00000100
y = 111111110000
```

You can notice that the order of the indexes does not matter on the result. To reverse a BitVector or a slice of BitVector, you can use `flip()` method:

```cpp
y(11,8) = x(3,0).flip();
```

```bash
# Console output
x = 00000100
y = 001011110000
```

__Note__: `flip()` method can't be a lvalue. Therefore you **can't** do something like:

```cpp
y(11,8).flip() = x(3,0);
```

It will compile but won't do anything to `y`'s value.

__Important notes:__

1. If you write a slice `x(.,.)` to another slice `y(.,.)` which is smaller, then `x(.,.)` will be truncated to its MSB side, and only the LSB that fit in `y(.,.)` will be written.

2. Inversely, if you write a slice `x(.,.)` to another slice `y(.,.)` which is larger, then `x(.,.)` will be set to the LSB side of `y(.,.)`, and the unreached MSB part will be filled with 0s.

3. **Never initialize a BitVector directly from a bit or slice selected from another BitVector using copy constructor.** This can lead to undefined behavior and memory leaks. E.g:

   ```cpp
   // Creating a BitVector of size 32
   BitVector x(32, 0x0F0F0F0F);
   // <!> Never use this syntax <!>
   BitVector y(x(11,0));
   // However, you can use this syntax
   BitVector z(12, x(11,0));
   ```

__Tips__:

1. You can chain slices/bit selection. E.g, `x(15,2)(8,3)[0]`, which is equivalent to `x[5]`. Guess which one is the most efficient?
2. You can create a reduced BitVector using `strip()` method. This method returns a potentially smaller BitVector (all 0s to the MSB are cut off), but comes with a non-negligible time-penalty. Use it only if you may potentially have huge BitVectors with a lot of 0s.

### Concatenation

You now know how to tear BitVectors into pieces, but you can also concatenate them. There is nothing easier, just use operator `+`. Let's take two simple BitVectors:

```cpp
// Declarations/instantiations
BitVector x(8, 0xF0);
BitVector y(8, 0x0F);
```

```bash
# Console output
x = 11110000
y = 00001111
```

Let's concatenate them and store them in a 16-bit BitVector.

```cpp
// Concatenation
BitVector z1(16, 0);
z1 = x + y;
```

```bash
# Console output
z1 = 1111000000001111
```

When using concatenation operator, the first operand is set as MSB part and the second one is set as LSB part (which is intuitive with the order in console output).

Of course, concatenation operator is interoperable with bit and slice selections. E.g:

```cpp
// Slices concatenation
BitVector z2(16, 0);
z2(9,2) = x(6,3) + y(4,1);
```

```bash
# Console output
z2 = 0000001110011100
```

__Important note:__

Concatenation is also interoperable with native types but should be used with caution (you may not know the size of the native types your are manipulating if you leave the choice to the compiler). 

### Bitwise operations

Now you know everything on BitVector instantiation, assignment, bit and slice selection and concatenation, you need to know how to use basic bitwise manipulation on them. And you are lucky, this is very simple. The first thing you need to know is that __everything is interoperable and should work as you expect__.

Indeed, all bitwise operations we are going to talk about can be applied to BitVectors, bit selections, slice selections and native types, without any explicit cast. Moreover, this interoperability comes with very slight to zero performance overhead compared to pure BitVector manipulation.

The main bitwise operations available for BitVector are bitwise negation (~), bitwise AND (&), bitwise OR (|) and bitwise XOR (^). The three last of this list also come with their associated assignment operator (&=, |= and ^=).

To make a demonstration of these operators, let's take the following base BitVectors:

```cpp
// Declarations/instantiations
BitVector a(32,0x00000000);
BitVector b(32,0xFFFFFFFF);
BitVector c(16,0xFF00);
BitVector d(8,0xF0);
```

```bash
# Console output
a = 00000000000000000000000000000000
b = 11111111111111111111111111111111
c = 1111111100000000
d = 11110000
```

Here is a short example of how to use negation operator:

```cpp
// Bitwise negation examples
BitVector e(16,0);
e = ~c;
b(7,0) = ~c(11,4);
```

```bash
#Console output
e = 0000000011111111
b = 11111111111111111111111100001111
```

Another example of how to use bitwise operators:

```cpp
// Bitwise AND, OR and XOR examples
d = a(12, 5) | c(10, 3);
b(23, 20) &= a(15, 12) | (d(5,2) ^ b(12, 9));
```

```bash
# Console output
d = 11100000
b = 11111111011111111111111100001111
```

And as said above, everything is interoperable. Therefore, things like this do work:

```cpp
// Declarations/instantiations
BitVector f(32, 0xF0F0F0F0);
BitVector g(16, 0xFF00);
hvuint16_t h(0x0FF0);
hvint16_t i(-1); // 0xFFFF
BitVector j(32, 0x55555555);
hvuint8_t k(160); // 0xA0

// A lot of operations in one single line
f(31, 16) |= ((g(14, 0) + f[6]) & ((h | (k + j(20, 5))) ^ i)).flip();
```

```bash
# Console output
f = 11111010111100001111000011110000
```

### Boolean tests

Boolean tests can also be performed on a combination of BitVectors, BitVectors selections, BitVectors:

- Non-zero test (operator !)
- Boolean AND (operator &&)
- Boolean OR (operator ||)

```cpp
// Declarations/instantiations
BitVector f(8, 0x00);
BitVector g(8, 0x0F);
hvuint8_t h(0);
hvuint8_t i(12);

// Some boolean tests
bool test1 = (f && g);
bool test2 = (!f && g);
bool test3 = (f || g);
bool test4 = (f || !g);
bool test5 = (h || g);
bool test6 = (g && !i);
bool test7 = (g(7,4) && i);
```

```bash
# Console output
test3 = true
test4 = false
test5 = true
test6 = false
test7 = false
```

Nothing special to be mentioned here. Just use it.

---

You are ready to go now. Be Hiventive!