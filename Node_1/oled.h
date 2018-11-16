#ifndef OLED_H
#define OLED_H

#include <stdlib.h>
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#define F_CPU 4915200
#include <util/delay.h>
#include <stdbool.h>
#include "joystick.h"

typedef struct screen_shots{
	char num;
	const char* write;
	char line;
	bool C[8] ;
	struct screen_shots* next[8];
	struct screen_shots* prev;
	bool with_arrow;
}screen;


void clear();
//void clear_C();
void oled_init();
void go_to_column(char);
void go_to_line(char);
void oled_pos(char,char);
void write_letter(const char);
void oled_print(screen*);
// SCREENSHOTS
void write_arrow(char);
void clean_arrow(char);
//void select_line_joystick(char);
void screen_arrow(screen);
void interface(screen*);
char interface2(screen**);
//void Hello_world();
//void just_try();
//void I();
//void just_try2();



#endif
