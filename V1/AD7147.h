#ifndef AD7147_H
#define	AD7147_H
//---------------------------------
//Function prototypes
//---------------------------------
void setup_AD7147(unsigned int*, unsigned int);
void write_AD7147(unsigned int, unsigned int, unsigned int*, unsigned int, unsigned int);
void read_AD7147(unsigned int*, unsigned int, unsigned int, unsigned int);
static int ServiceAD7147Isr(void);
void read_sensor(unsigned int*, unsigned int);
void read_cdc1(unsigned int*);
void read_cdc2(unsigned int*);
unsigned int get_ID(unsigned int);
void read_sensors(unsigned int*, unsigned int*, unsigned int);
void switch_LED(unsigned int, unsigned int);
void blink_LED(unsigned int);
void get_CDC(unsigned int, unsigned int);
void sensor_CDC(unsigned int, unsigned int);
#endif	/* XC_HEADER_TEMPLATE_H */


