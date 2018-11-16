#ifndef _IR_DRIVER_
#define _IR_DRIVER_
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <avr/sleep.h>
#include <stdbool.h>

void IR_init();
uint16_t read_IR();
void print_IR();


#endif
