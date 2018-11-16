#ifndef LATCH_H
#define LATCH_H

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#define F_CPU 4915200
//#include <stdio.h>



void en_eMem();
char* adress(char *);
void data(uint8_t, char *);
void SRAM_test();


#endif
