# Datatypes
2016 BYU CS 224 Lab 1

### S01: Data Types
- Binary Digital System
- Integral Data Types
- Fractional Data Types
- ASCII Characters

### Explore:
- basic integral and floating point data types in a C program
- choose a correct data type according to the largest range of values needed
- explain problems associated with integral data type overflow
- choose the correct floating point operations when converting and comparing floating point numbers
- properly order associative arithmetic operations to minimize loose of data
- see the inaccuracies and limitations introduced by machine representations of number data types
- overflow 
- max values of integer data types (signed and unsigned)
- problems that arise when performing if statement logic with floats, etc

### Learn
Arithmetic problems begin with the choice of data types.
A number may be represented in a computer in many different binary forms call data types. For example, the decimal number 10 may be represented as 000010102 (8-bit integer), 101000002 (2 byte BCD), or 010000010010000000000000000000002 (32-bit float). Integral numbers (numbers without a fraction) are less of a problem for a computer because there is usually no loss of data with arithmetic operations and	most integer numbers are easily converted between data types.

Fractional numbers, however, are another story. The number π, for instance, is not representable in any finite number of digits, regardless of the data type. Even simple numbers can cause problems. For example, 0.1 (one tenth) cannot be represented exactly in floating point (0x3dcccccd float) data types. This means there is always a round-off error in conversions and arithmetic computations. There are two conventional ways to deal with round-off errors:

Conventional rounding rounds the result of a conversion or computation up or down to the nearest representable number.
Or, the result is chopped or truncated by just throwing away the excess information.
The error in chopping is twice that of rounding. IBM (and clones) mainframes use chopping. This means that calculations done on an IBM mainframe probably cannot be duplicated on any other computer! Even worse, some financial calculations like the coupon values of bonds, are required by convention, to be chopped while other calculations are rounded. Over the course of many calculations, someone is losing lots of money if the principals are large enough and there are enough transactions. Like banks, maybe?

Patriot Missile Failure
On February 25, 1991, during the Gulf War, an American Patriot Missile battery in Dharan, Saudi Arabia, failed to intercept an incoming Iraqi Scud missile. The Scud struck an American Army barracks and killed 28 soliders.

A report of the General Accounting office, GAO/IMTEC-92-26, entitled Patriot Missile Defense: Software Problem Led to System Failure at Dhahran, Saudi Arabia reported on the cause of the failure. It turns out that the cause was an inaccurate calculation of the time since boot due to computer arithmetic errors. Specifically, the time in tenths of second as measured by the system's internal clock was multiplied by 1/10 to produce the time in seconds. This calculation was performed using a 24 bit fixed point register. In particular, the value 1/10, which has a non-terminating binary expansion, was chopped at 24 bits after the radix point. The small chopping error, when multiplied by the large number giving the time in tenths of a second, lead to a significant error. Indeed, the Patriot battery had been up around 100 hours, and an easy calculation shows that the resulting time error due to the magnified chopping error was about 0.34 seconds.

Explosion of the Ariane 5
On June 4, 1996 an unmanned Ariane 5 rocket launched by the European Space Agency exploded just forty seconds after lift-off. The rocket was on its first voyage, after a decade of development costing $7 billion. The destroyed rocket and its cargo were valued at $500 million. A board of inquiry investigated the causes of the explosion and in two weeks issued a report. It turned out that the cause of the failure was a software error in the inertial reference system. Specifically a 64 bit floating point number relating to the horizontal velocity of the rocket with respect to the platform was converted to a 16 bit signed integer. The number was larger than 32,768, the largest integer storeable in a 16 bit signed integer, and thus the conversion failed.
