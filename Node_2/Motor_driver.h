#ifndef _MOTOR_
#define _MOTOR_

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdbool.h>

#include "TWI_Master.h"


void motor_init();
void calibrate_motor();
uint16_t read_encoder();
void sweep_direction(uint8_t);
void en_motor();
void stop_motor();


#endif
