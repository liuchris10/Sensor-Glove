#include "micro_setup.h"
#include "spi.h"
#include "uart.h"
#include "AD7147.h"
#include <string.h>

unsigned int single_sensor;
unsigned int second_sensor;
unsigned int device_ID;
unsigned int sensor_values[24] = {0};
unsigned int avail_sensors[24] = {0};
unsigned int cdc;
unsigned int on_off;
unsigned int num_sensors;
unsigned char indicator;
char state = RESET_STATE; //Initializing State to Reset State
unsigned int interrupt_values_cdc1[3] = {0}; //Possible Interrupt Values from CDC 1
unsigned int interrupt_values_cdc2[3] = {0}; //Possible Interrupt Values from CDC 2
unsigned int start_stop = 1; //Starting or stoping Contious Loop
unsigned char break_loop;
void interrupt high_priority ISR(void)
{
    //Check if the interrupt is caused by the pin RB0 (CDC 1)
    if(INTCONbits.INT0IF && INTCONbits.INT0IE)
    {
        read_cdc1(sensor_values);
        read_AD7147(interrupt_values_cdc1, STAGE_LOW_LIMIT_INT, 3, 1); //Registers 0x08 & 0x09 & 0x0A
        INTCONbits.INT0IF = 0; //Resetting the Interrupt Pin
    }
    if(INTCON3bits.INT1IF && INTCON3bits.INT1E)
    {
        read_cdc2(sensor_values);
        read_AD7147(interrupt_values_cdc2, STAGE_LOW_LIMIT_INT, 3, 2); //Registers 0x08 & 0x09 & 0x0A
        INTCON3bits.INT1IF = 0; //Resetting the Interrupt Pin
    }
    return;
}

void main(void) 
{
    delay_ms(500);
    setup_mcu();
    setup_spi();
    setup_AD7147(interrupt_values_cdc1, 1);
    //setup_AD7147(interrupt_values_cdc2, 2);
    //blink_LED(2);
    blink_LED(1);
    read_AD7147(interrupt_values_cdc1, STAGE_LOW_LIMIT_INT, 3, 1); //Registers 0x08 & 0x09 & 0x0A
    init_interrupts();
    while(1) 
    {   
        indicator = uart_read_char();
		switch (state)
		{
			case SINGLE:
                switch (indicator)
                {
                    case s_sensor:
                        single_sensor = uart_read_unsigned_int();
                        uart_write_unsigned_int(sensor_values[single_sensor]);
                        state = RESET_STATE;
                        break;
                    case led_blink:
                        cdc = uart_read_unsigned_int();
                        blink_LED(cdc);
                        state = RESET_STATE;
                        break;
                    case led_state:
                        cdc = uart_read_unsigned_int();
                        on_off = uart_read_unsigned_int();
                        switch_LED(cdc, on_off);
                        state = RESET_STATE;
                        break;
                    case id_sensor:
                        cdc = uart_read_unsigned_int(); //Either CDC 1 or CDC 2
                        device_ID = get_ID(cdc);
                        uart_write_unsigned_int(device_ID);
                        state = RESET_STATE;
                        break;
                }
                break;
                
            case CONTINOUS:
                switch (indicator)
                {
                    case c_sensor:
                        single_sensor = uart_read_unsigned_int();
                        read_sensor(sensor_values, single_sensor);
                        uart_write_unsigned_int(sensor_values[single_sensor]);
                        break;
                    case c_sensors:
                        while(start_stop == 1)
                        {
                            uart_write_char('s');
                            for(unsigned int i = 0; i<24; i++)
                            {
                                if(avail_sensors[i] == 1)
                                {
                                    uart_write_unsigned_int(sensor_values[i]);
                                }
                            }
                            break_loop = uart_read_indicator();
                            if(break_loop == 'z')
                            {
                                start_stop = 0;
                                state = RESET_STATE;
                            }
                        }
                        start_stop = 1;
                        break;
                    default:
                        state = RESET_STATE;
                        break;
                }
                break;
			
			case CDC_PARAMETERS:
                switch (indicator)
                {
                    case reset_sensors:
                        memset(avail_sensors, 0, 24*sizeof(avail_sensors[0])); //Reset Available Sensors
                        num_sensors = uart_read_unsigned_int(); //Getting the number of sensors
                        for(unsigned int k = 0; k < num_sensors; k++)
                        {
                            unsigned int index = uart_read_unsigned_int();
                            avail_sensors[index-1] = 1;
                        }
                        state = RESET_STATE;
                        break;
                    case 'e':
                        uart_write_char('e');
                        state = RESET_STATE;
                        break;
                    default:
                        break;
                }
                break;
                
			case RESET_STATE:
                switch (indicator)
                {
                    case SINGLE:
                        state = SINGLE;
                        break;
                    case CONTINOUS:
                        state = CONTINOUS;
                        break;
                    case CDC_PARAMETERS:
                        state = CDC_PARAMETERS;
                        break;
                    default:
                        state = RESET_STATE;
                        break;
                }
                break;
                
            default:
                break;
		}
    } 
    return;
}




