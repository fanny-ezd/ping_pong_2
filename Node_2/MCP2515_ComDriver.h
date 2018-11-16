#ifndef MCP2515COM_H
#define MCP2515COM_H
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000
#include <avr/sleep.h>
#include "MCP2515_driver.h"
#include "TWI_Master.h"
#include <util/delay.h>
#include "Motor_driver.h"

typedef struct can_message {
  uint8_t AH;
  uint8_t AL;
  uint8_t length;
  char data[8];
}can_message;

void MCP2515_init();
void set_mode(uint8_t);
void send_something_loop(can_message);
void recieve_something_loop();


#endif
