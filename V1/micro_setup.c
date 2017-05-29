#include <stdio.h>
#include "micro_setup.h"

unsigned int* CDC_RESULT[] = {0,0,0,0,0,0,0,0,0,0,0,0};

void setup_mcu(void)
{
    setup_port();
    init_uart();
}

void setup_port(void)
{
    //TRISA = 0b00000000;         // Port A: Output: 0-7
    TRISB = 0b00000000;         // Port B: Output: 0-7
    TRISC = 0b10010000;         // Port C: Output: 0-3,5-6 Input: 4,7 
    CS_CDC1=1;
    CS_CDC2=1;
    CS_AG=1;
}                   

void init_uart(void)
{
    TXSTA1 = 0b00100000;         // Transmission Register
    // Bit 7=x, CSRC, Using UART (Asynchronous), Don't care about bit
    // Bit 6=0, TX9, 8-Bit transmission
    // Bit 5=1, TXEN, Transmit Enabled
    // Bit 4=0, SYNC, Asynchronous mode
    // Bit 3=-, -, Unimplemented
    // Bit 2=0, BRGH, Baud Rate Select Bit, 1 = High Speed
    // Bit 1=x, TRMT, Transmit Shift Register Status Bit
    // Bit 0=0, TX9D, No parity bit
    
    //x = ((_XTAL_FREQ/BAUDRATE)/64)-1;
    // 9600 Baud Rate, x = 12
    SPBRG1 = 12;          // Writing SPBRG Register
    
    BAUDCON1 = 0b00000000;
    // Bit 7=0
    // Bit 6=
    // Bit 5=0, unimplemented
    // Bit 4=
    // Bit 3=
    // Bit 2=
    // Bit 1=
    // Bit 0=
    //RCSTA2 = 0b10010000;         // Receive Register
    // Bit 7=1, SPEN, Serial Port Enabled
    // Bit 6=0, RX9, 8-Bit reception, RX9 = 0
    // Bit 5=x, SREN, Single Receive Enable Bit- Asynchronous Mode- Don't Care
    // Bit 4=1, CREN, Continuous Receive Enable Bit, Asynchronous mode, Receiver Enabled
    // Bit 3=x, ADDEN, Asynchronous mode 8-bit, RX9=0, Don't Care
    // Bit 2=0, FERR, Framing Error Bit, FERR, 0 = No Framing Error
    // Bit 1=0, OERR, Overrun Error Bit, 0 = No Overrun Error has Occurred
    // Bit 0=0, RX9D, Parity Bit, RX9D, 9th Bit of Received Data
    
    //RCSTA
    RCSTA1bits.SPEN=1;   //Serial port enabled
    RCSTA1bits.RX9=0;    //8 bit mode
    RCSTA1bits.CREN=1;   //Enable receive
    //RCSTA2bits.ADDEN=0;  //Disable address detection
    //Receive interrupt
    //RCIE=1;       // USART Transmit Interrupt Enable bit
    //PEIE=1;       // Must be set to enable any peripheral interrupt
} 

void delay_ms(int n)
{
    int j = n/10;
    while(j--)
    {
        __delay_ms(10);
    }
}