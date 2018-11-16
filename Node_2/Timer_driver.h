#ifndef _TIMER_
#define _TIMER_
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "Motor_driver.h"
#include <stdbool.h>
#include "IR_driver.h"

void init_timer();

#endif
