#include "micro_setup.h"
#include <xc.h>                 // PIC16F917 Configuration Bit Settings
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


unsigned int cdc_signal(char signal, int number)
{
    // 'c' = configuration (Reading)
    // 'r' = result from CDC (Writing)
    if(signal == 'c')
    {
        
        
    }
    if(signal == 'r')
    {
        
    }
   return signal; 
}

void uart_write_char(char data)
{ 
    while(!TXSTA1bits.TRMT);
    //while(!PIR1bits.TXIF);
    TXREG1 = data;
}

void uart_write_int(int number)
{ 
    while(!TXSTA1bits.TRMT);
    //while(!PIR1bits.TXIF);
    char temp = number + '0';
    TXREG1 = temp;
}

void uart_write_unsigned_int(unsigned int number)
{ 
    char char1 = number & 0xFF;
    char char2 = number >> 8;
    
    while(!TXSTA1bits.TRMT);
    TXREG1 = char1;
    while(!TXSTA1bits.TRMT);
    TXREG1 = char2;
}
void uart_write_32(unsigned int address, unsigned int data)
{ 
    unsigned int address_low, address_high, data_low, data_high;

    address_low = address & 0xFF;
    address_high = (address >> 8) & 0xFF;
    
    data_low = data & 0xFF;
    data_high = (data >> 8) & 0xFF;
    
    while(!TXSTA1bits.TRMT);
    TXREG1 = address_low;
    while(!TXSTA1bits.TRMT);
    TXREG1 = address_high;
    
    while(!TXSTA1bits.TRMT);
    TXREG1 = data_low;
    while(!TXSTA1bits.TRMT);
    TXREG1 = data_high;
}
char uart_int_to_string(int number)
{
    char temp = number + '0';
    return temp;
}

void uart_write_string(const char *text)
{
    for(int i=0; i <= strlen(text); i++)
    {
        uart_write_char(text[i]);
    }
}

char uart_tx_empty(void)
{
    return TXSTA1bits.TRMT;    
}


char uart_data_ready(void)
{
    return RC1IF;
}

char uart_read_char(void)
{
    while(PIR1bits.RC1IF == 0)
    {
        if(RCSTA1bits.OERR == 1)
        {
            RCSTA1bits.OERR = 0;
            RCSTA1bits.CREN = 0;
            RCSTA1bits.CREN = 1;
        }
    }
    return RCREG1;
}

void uart_read_text(char *Output, unsigned int length)
{
    for(int i=0; i<length; i++)
    {
        Output[i] = uart_read_char();
    }
}