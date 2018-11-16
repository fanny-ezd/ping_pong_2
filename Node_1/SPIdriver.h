#ifndef SPI_H
#define SPI_H
#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

void SPI_Init();
void SPI_send(char);
char SPI_read();
//void SPI_SlaveInit();
//char SPI_SlaveReceive();


#endif
