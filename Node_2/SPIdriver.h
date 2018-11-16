#ifndef SPI_H
#define SPI_H
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <avr/sleep.h>
#include "MCP2515.h"

void SPI_Init();
void SPI_send(char);
char SPI_read();
//void SPI_SlaveInit();
//char SPI_SlaveReceive();


#endif
