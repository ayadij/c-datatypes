//	Lab01.c	2016/09/15 AYA DIJKWEL CS224-003

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "lab01.h"

unsigned long MCLK_HZ = 1050000;		// SMCLK frequency in Hz
unsigned long BPS = 9600;				// ASYNC serial baud rate

int main(void)
{
	lab01_init();

		//uncomment call to find_baud_rate to find MCLK_HZ
		//find_baud_rate();




TERMINAL("\n\n\n\r********************************** part 1 *");


	TERMINAL("\n\r*SIGNED CHAR*");
		signed char s_biggest_char, s_next_char, s_smallest_char;
		s_next_char = 1;
		s_biggest_char = 1;
	    while((s_next_char <<= 1) > 0)
	    {
	    	s_biggest_char = (s_biggest_char << 1) + 1;;
	    }
	    s_smallest_char = s_biggest_char + 1;

		TERMINAL2("largest  = %d (0x%2x)", s_biggest_char);
		TERMINAL2("smallest = %d (0x%2x)", s_smallest_char);


	TERMINAL("\n\r*SIGNED INT*");
	    signed int s_biggest_int, s_next_int, s_smallest_int;
	    s_next_int = 1;
	    s_biggest_int = 1;
	    while((s_next_int <<= 1) > 0)
	    {
	    	s_biggest_int = (s_biggest_int << 1) + 1;;
	    }
		TERMINAL2("largest  = %d (0x%2x)", s_biggest_int);
		s_smallest_int = s_biggest_int + 1;
		TERMINAL2("smallest = %d (0x%2x)", s_smallest_int);


	TERMINAL("\n\r*SIGNED LONG*");
	    signed long s_biggest_long, s_next_long, s_smallest_long;
	    s_next_long = 1;
	    s_biggest_long = 1;
	    while((s_next_long <<= 1) > 0)
	    {
	    	s_biggest_long = (s_biggest_long << 1) + 1;;
	    }
		TERMINAL2("largest  = %ld (0x%2x)", s_biggest_long);

		s_smallest_long = 1;
		signed long s_next_long2 = 1;
		while ((s_next_long2 <<= 1))
		{
			s_smallest_long = (s_smallest_long << 1);
		}
		TERMINAL2("smallest = %ld (0x%2x)", s_smallest_long);


	TERMINAL("\n\r*UNSIGNED*");
		unsigned char biggest_char, next_char;
		next_char = 1;
		biggest_char = 1;
		while((next_char <<= 1) > 0)
		{
			biggest_char = (biggest_char << 1) + 1;;
		}
		TERMINAL2("char = %u (0x%2x)", biggest_char);


		unsigned int biggest_int, next_int;
		next_int = 1;
		biggest_int = 1;
		while((next_int <<= 1) > 0)
		{
			biggest_int = (biggest_int << 1) + 1;;
		}
		TERMINAL2("int = %u (0x%2x)", biggest_int);


		unsigned long biggest_long, next_long;
		next_long = 1;
		biggest_long = 1;
		while((next_long <<= 1) > 0)
		{
			biggest_long = (biggest_long << 1) + 1;;
		}
		TERMINAL2("long = %lu (0x%2x)", biggest_long);




TERMINAL("\n\n\r********************************** part 2 *");


	TERMINAL("\n\r*OVERFLOW*");
		char ca, cc; ca = 255;
		cc = ca + 2;
		TERMINAL2("char 255 + 2 = %u (0x%2x)", cc);

		int ta, tb; ta = -32768; tb = ta - 2;
		TERMINAL2("int -32768 -2 = %d (0x%2x)", tb);

		long la, lb; la = 2147483647; lb = la + 2;
		TERMINAL2("long 2147483647 + 2 = %ld (0x%2x)", lb);




TERMINAL("\n\n\r********************************** part 3 *");


	TERMINAL("\n\r*Q16.16*");
		TERMINAL3("smallest = %f (0x%2x)", (((long)s_smallest_long)/65536.0), s_smallest_long);
		TERMINAL3("largest = %f (0x%2x)", (((long)s_biggest_long)/65536.0), s_biggest_long);




TERMINAL("\n\n\r********************************** part 4 *");


	TERMINAL("\n\r*FLOATING POINT ROUND OFF ERRORS*");
		float f01 = 0.0001; float f02 = 0.00;
		int i;
		for (i=0; i<20000; ++i) f02 += f01;
		TERMINAL2("result 1 = %f (0x%08lx)", f02);
		TERMINAL2("result 2 = %f (0x%08lx)", f01*20000);

		float f11 = 0.0005; float f12 = 0.00;
		for (i=0; i<10000; ++i) f12 += f11;
		TERMINAL2("result 1 = %f (0x%08lx)", f12);
		TERMINAL2("result 2 = %f (0x%08lx)", f11*10000);



TERMINAL("\n\n\r********************************** part 5 *");

/*
	TERMINAL("\n\r*ORDER OF OPERATIONS*");
		float f21 = 5.00; float f22 = 6.00; float f23 = 7.00;
		TERMINAL2("5.0 * 6.0 + 7.0 = %f (0x%08lx)", f21*f22+f23);
		TERMINAL2("5.0 * (6.0 + 7.0) = %f (0x%08lx)", f21*(f22+f23));

		float f31 = 9.2; float f32 = 6.6; float f33 = 7.4; float f34 = 8.0;
		TERMINAL2("9.2 * 6.6 + 7.4 * 8.0 = %f (0x%08lx)", (f31*f32)+(f33*f34));
		TERMINAL2("9.2 * (6.6 + 7.4 * 8.0) = %f (0x%08lx)", f31*(f32+f33*f34));
*/

	TERMINAL("\n\r*ORDER OF OPERATIONS*");
		int f21 = 5.00; int f22 = 6.00; int f23 = 7.00;
		TERMINAL2("5.0 * 6.0 + 7.0 = %d (0x%2x)", f21*f22+f23);
		TERMINAL2("5.0 * (6.0 + 7.0) = %d (0x%2x)", f21*(f22+f23));

		int f31 = 9.2; int f32 = 6.6; int f33 = 7.4; int f34 = 8.0;
		TERMINAL2("9.2 * 6.6 + 7.4 * 8.0 = %d (0x%2x)", (f31*f32)+(f33*f34));
		TERMINAL2("9.2 * (6.6 + 7.4 * 8.0) = %d (0x%2x)", f31*(f32+f33*f34));





TERMINAL("\n\n\r************************************* end *");


return 0;

}


