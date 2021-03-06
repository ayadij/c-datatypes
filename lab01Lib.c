//	lab01Lib.c	09/18/2014
//
#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "lab01.h"

#if !defined(__MSP430_HAS_USCI__)
 #error "This code written for the msp430g2553"
#endif

extern unsigned long MCLK_HZ;			// SMCLK frequency in Hz
extern unsigned long BPS;				// ASYNC serial baud rate

volatile unsigned int WDT_Sec_Cnt;
volatile unsigned int tics;
unsigned long baud_rate_20_bits;		// Bit rate divisor
unsigned int count;
char buffer[64];

//------------------------------------------------------------------------------
int getchar(void)
{
    while(!(IFG2 & UCA0RXIFG));
    IFG2 &= ~UCA0RXIFG;
    return UCA0RXBUF;
}

//------------------------------------------------------------------------------
int putchar(int c)
{
    while(!(IFG2 & UCA0TXIFG));                  // wait for TX buffer to be empty
    UCA0TXBUF = c;
    return c;
}

//------------------------------------------------------------------------------
void print(const char *s)
{
    while(*s) putchar(*s++);
}

//------------------------------------------------------------------------------
void printx(const uint8_t c)
{
    static char hex_table[] = "0123456789abcdef";
    putchar(hex_table[(c & 0xF0) >> 4]); putchar(hex_table[c & 0x0F]);
}

//------------------------------------------------------------------------------
void lab01_init()
{
	// configure Watchdog
	WDTCTL = WDT_CTL;					// Set Watchdog interval
	WDT_Sec_Cnt = WDT_1SEC_CNT;			// set WD 1 second counter
	tics = 0;
	IE1 |= WDTIE;						// enable WDT interrupt

    // Configure P1.1 and P1.2 as UART controlled pins
    P1DIR &= ~(BIT1 | BIT2);                        // Revert to default to GPIO input
    P1SEL = BIT1 | BIT2;                            // P1.1=RXD, P1.2=TXD
    P1SEL2 = BIT1 | BIT2;                           // P1.1=RXD, P1.2=TXD

    // Configure USCI UART for 9600
    baud_rate_20_bits = (MCLK_HZ + (BPS >> 1)) / BPS;
    UCA0CTL1 = UCSWRST;                             // Hold USCI in reset to allow configuration
    UCA0CTL0 = UCSPB;                               // No parity, LSB first, 8 bits, one stop bit, UART (async)
    UCA0BR1 = (baud_rate_20_bits >> 12) & 0xFF;     // High byte of whole divisor
    UCA0BR0 = (baud_rate_20_bits >> 4) & 0xFF;      // Low byte of whole divisor
    UCA0MCTL = ((baud_rate_20_bits << 4) & 0xF0) | UCOS16; // Fractional divisor, over sampling mode
    UCA0CTL1 = UCSSEL_2;                            // Use SMCLK for bit rate generator, then release reset

    ADC10CTL1 = INCH_10 + ADC10DIV_3;         // Temp Sensor ADC10CLK/4
    ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE + REF2_5V;
    ADC10AE0 |= 0x20;                         // PA.1 ADC option select

	count = 1;
    P1DIR |= 0x01;
    return;
}

//------------------------------------------------------------------------------
#define MIN_MCLK_HZ	850000
#define MAX_MCLK_HZ	1250000

void find_baud_rate()
{
	volatile int delay;
	while (1)
	{
		for (MCLK_HZ = MIN_MCLK_HZ; MCLK_HZ < 1200000; MCLK_HZ += 5000)
		{
			for (delay = 0; delay < 20000; delay++);
			baud_rate_20_bits = (MCLK_HZ + (BPS >> 1)) / BPS;
			UCA0CTL1 = UCSWRST;                             // Hold USCI in reset to allow configuration
			UCA0CTL0 = UCSPB;                               // No parity, LSB first, 8 bits, one stop bit, UART (async)
			UCA0BR1 = (baud_rate_20_bits >> 12) & 0xFF;     // High byte of whole divisor
			UCA0BR0 = (baud_rate_20_bits >> 4) & 0xFF;      // Low byte of whole divisor
			UCA0MCTL = ((baud_rate_20_bits << 4) & 0xF0) | UCOS16; // Fractional divisor, over sampling mode
			UCA0CTL1 = UCSSEL_2;                            // Use SMCLK for bit rate generator, then release reset
			TERMINAL1("MCLK_HZ = %lu", MCLK_HZ);
		}
	}
}


//------------------------------------------------------------------------------
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

//------------------------------------------------------------------------------
// Watchdog Timer ISR ----------------------------------------------------------
#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
	if (--WDT_Sec_Cnt == 0)
	{
		WDT_Sec_Cnt = WDT_1SEC_CNT;		// reset counter
		++tics;
	}
} // end WDT_ISR(void)

