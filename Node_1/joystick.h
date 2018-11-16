#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include<string.h>
#include <stdbool.h>
#include <stdio.h>
#include <avr/interrupt.h>
#define F_CPU 4915200
#include <util/delay.h>

typedef struct joystick_position {
    uint8_t X;
    uint8_t Y;
} joystick;

typedef struct slider_position	{
  uint8_t L;
	uint8_t R;
}slider;

void joystick_init();
void buttons_init();
uint8_t read_adc();
void write_adc(uint8_t);
//void test1();
void print_x_y();
void print_left_right();
//void test4();
joystick return_pos_joystick();
slider return_pos_slider();
uint8_t return_direction_joystick();

#endif
