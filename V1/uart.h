#ifndef UART_H
#define	UART_H

#include <xc.h>

unsigned int cdc_signal(char, int);

void uart_write_char(char);

void uart_write_int(int);

void uart_write_unsigned_int(unsigned int);

void uart_write_32(unsigned int, unsigned int);

char uart_tx_empty(void);

void uart_write_string(const char *text);

char uart_int_to_string(unsigned int);

char uart_data_ready(void);

unsigned char uart_read_char(void);

unsigned char uart_read_indicator(void);

//void uart_read_text(char *Output, unsigned int length);

void uart_send_sensors(unsigned int*, unsigned int*, unsigned int);

unsigned int uart_read_unsigned_int(void);

#endif	/* UART_H */
