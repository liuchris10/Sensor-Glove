#ifndef AD7147_H
#define	AD7147_H
//---------------------------------
//Function prototypes
//---------------------------------
void setup_AD7147(unsigned int);
void write_AD7147(unsigned int RegisterAddress, unsigned int NumberOfRegisters, unsigned int DataBuffer[]);
unsigned int read_AD7147(unsigned int, unsigned int);
static int ServiceAD7147Isr(void);
unsigned int read_sensor(unsigned int);
unsigned int get_ID(unsigned int);
void read_sensors(void);
void switch_LED(unsigned int, unsigned int);
void blink_LED(unsigned int);
void get_CDC(unsigned int, unsigned int);
void sensor_cdc(unsigned int, unsigned int);
#endif	/* XC_HEADER_TEMPLATE_H */


