#include "spi.h"
#include "micro_setup.h"

void setup_spi(void) 
{
    SSPSTATbits.SMP = 0;   //SPI Master Mode: Input data sampled at middle of data output time
    SSPSTATbits.CKE = 0;   //Transition occurs on rising edge
    
    SSPCON1bits.WCOL = 0;  //Collision Detection Bit, 0 = no collision
    SSPCON1bits.CKP = 1;   //Clock Polarity, Idle State: 1 = (3.3V), High
    
    SSPCON1bits.SSPM3 = 0; //SSPM3:0 SPI Master Mode, Clock = Fosc/64
    SSPCON1bits.SSPM2 = 0;
    SSPCON1bits.SSPM1 = 1;
    SSPCON1bits.SSPM0 = 0;
    
    PIE1bits.SSPIE = 0;    // Interrupt is disabled
    
    SSPCON1bits.SSPEN = 1; //Enables the ports for SSP
    
    //TRISC &= 0xDF;      // clearing TRISC<5> for SDO1
    //TRISC &= 0xF7;      // clearing TRISC<3> for SCK1
    // SDI is automatically controlled by the SPI module
}

void w32_spi(unsigned int address, unsigned int data)
{
    unsigned int address_low, address_high, data_low, data_high;

    address_low = address & 0xFF;
    address_high = (address >> 8) & 0xFF;
    
    data_low = data & 0xFF;
    data_high = (data >> 8) & 0xFF;
    
    SSPBUF = address_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    unsigned int p1 = SSPBUF;
    
    SSPBUF = address_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    unsigned int p2 = SSPBUF;
    
    SSPBUF = data_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    unsigned int p3 = SSPBUF;
    
    SSPBUF = data_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    unsigned int p4 = SSPBUF;
}

void w16_spi(unsigned int address)
{
    unsigned int address_low, address_high; 
    unsigned int p1, p2;
    
    address_low = address & 0xFF;
    address_high = (address >> 8) & 0xFF;
    
    SSPBUF = address_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p1 = SSPBUF;
    
    SSPBUF = address_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p2 = SSPBUF;
}

unsigned int r16_spi(void)
{
    unsigned int blank_low = 0x000;
    unsigned int blank_high = 0x000;
    unsigned int p1, p2, result;
    
    
    SSPBUF = blank_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p1 = SSPBUF;
    
    SSPBUF = blank_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p2 = SSPBUF;
    
    result = (p1 << 8) + p2;
    return result;    
}

unsigned int w16_r16_spi(unsigned int address)
{
    unsigned int address_low, address_high, result;
    unsigned int blank_low = 0x000;
    unsigned int blank_high = 0x000;
    unsigned int p1, p2, p3, p4;
    
    address_low = address & 0xFF;
    address_high = (address >> 8) & 0xFF;
  
    SSPBUF = address_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p1 = SSPBUF;
    
    SSPBUF = address_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p2 = SSPBUF;
    
    SSPBUF = blank_high;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p3 = SSPBUF;
    
    SSPBUF = blank_low;  // Command byte (write to pot 0)
    while(!SSPSTATbits.BF); // wait to complete 
    p4 = SSPBUF;
    
    result = (p3 << 8) + p4;
    return result; 
}

/*
void write_spi_register(unsigned int address[], unsigned int NumberOfRegisters, unsigned int data[])
{
    unsigned int address_low;
    unsigned int address_high;
    unsigned int data_low;
    unsigned int data_high;
    unsigned int p1, p2, p3, p4;
    
    for(int i=0; i<NumberOfRegisters; i++)
    {
        address_low = address[i] & 0xFF;
        address_high = (address[i] >> 8);
        data_low = data[i] & 0xFF;
        data_high = (data[i] >> 8); 
        
        SSP1BUF = address_high;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p1 = SSP1BUF;
    
        SSP1BUF = address_low;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p2 = SSP1BUF;
    
        SSP1BUF = data_high;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p3 = SSP1BUF;
    
        SSP1BUF = data_low;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p4 = SSP1BUF;    
    }
}

void w16_r16_spi_loop(unsigned int address[], unsigned int NumberOfRegisters, unsigned int sensor)
{
    //unsigned int address_low;
    //unsigned int address_high;
    unsigned int blank_low = 0x000;
    unsigned int blank_high = 0x000;
    unsigned int p1, p2, p3, p4;
    
    CS_CDC1 = 0;   //set CS to low (transmit data)
    for(int i=0; i<NumberOfRegisters; i++)
    {
        unsigned int address_low = address[i] & 0xFF;
        unsigned int address_high = (address[i] >> 8);
        
        SSP1BUF = address_high;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p1 = SSP1BUF;
    
        SSP1BUF = address_low;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p2 = SSP1BUF;
    
        SSP1BUF = blank_high;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p3 = SSP1BUF;
    
        SSP1BUF = blank_low;  // Command byte (write to pot 0)
        while(!SSP1STATbits.BF); // wait to complete 
        p4 = SSP1BUF;
        
        CDC_RESULT[sensor+1] = (p3 << 8) + p4;
    }
    CS_CDC1 = 1;   //set CS to low (transmit data)
}
*/
