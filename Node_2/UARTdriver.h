#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int);
int Usart_sending ( char data, FILE * _out);
int Usart_receive (FILE * _in);

#endif
