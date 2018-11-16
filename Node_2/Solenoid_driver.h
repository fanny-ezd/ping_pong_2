#ifndef _SOLENOID_
#define _SOLENOID_
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>

void solenoid_init();
void rise_sol();

#endif
