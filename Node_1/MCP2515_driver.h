#ifndef MCP2515_H
#define MCP2515_H
#define F_CPU 4915200
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include "SPIdriver.h"
#include "MCP2515.h"

uint8_t MCP2515_read(uint8_t);
void MCP2515_write(uint8_t, uint8_t);
void MCP2515_Request_to_send(uint8_t);
uint8_t MCP2515_Read_Status();
void MCP2515_Bit_Modify(uint8_t, uint8_t, uint8_t);
void MCP2515_Reset();

#endif
