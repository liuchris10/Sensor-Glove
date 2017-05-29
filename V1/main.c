#include "micro_setup.h"
#include "spi.h"
#include "uart.h"
#include "AD7147.h"

void main(void) 
{
    delay_ms(500);
    setup_mcu();
    setup_spi();
    //setup_AD7147();
   
    char indicator = 'i';
    unsigned int bb = 1020;
    while(1) 
    {   
        if (indicator == 'i')
        {
            uart_write_char('i');
            unsigned int device_ID = get_ID(1);
            uart_write_unsigned_int(device_ID);
        }
        if (indicator == 's')
        {
            uart_write_char('s');
            unsigned int sensor_0 = read_sensor(0);
            uart_write_unsigned_int(sensor_0);
        }  
        if (indicator == 'f')
        {
            uart_write_char('f');
            //setup_AD7147();
            uart_write_unsigned_int(bb);
        }
        delay_ms(500);
    } 
    return;
}