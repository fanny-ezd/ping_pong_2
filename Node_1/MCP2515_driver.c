#include "MCP2515_driver.h"



uint8_t MCP2515_read(uint8_t address){

  uint8_t result;

  PORTB &=~(1<<DDB4);
  SPI_send(MCP_READ);
  SPI_send(address);
  result = SPI_read();
  PORTB |= (1<<DDB4);
  return result;
}

void MCP2515_write(uint8_t address, uint8_t data){

  PORTB &=~(1<<DDB4);
  SPI_send(MCP_WRITE);
  SPI_send(address);
  SPI_send(data);
  PORTB |= (1<<DDB4);
}

void MCP2515_Request_to_send(uint8_t buffer){

  PORTB &=~(1<<DDB4);
  SPI_send(buffer);
  PORTB |= (1<<DDB4);
}

uint8_t MCP2515_Read_Status(){

  uint8_t result;
  PORTB &=~(1<<DDB4);
  SPI_send(MCP_READ_STATUS);
  result=SPI_read();
  PORTB |= (1<<DDB4);
  return result;
}

void MCP2515_Bit_Modify(uint8_t address, uint8_t mask, uint8_t data){  // Only use in MCP_CANINTF


  PORTB &=~(1<<DDB4);
  SPI_send(MCP_BITMOD);
  SPI_send(address);
  SPI_send(mask);
  SPI_send(data);
  PORTB |= (1<<DDB4);

}

void MCP2515_Reset(){

  PORTB &=~(1<<DDB4);
  SPI_send(MCP_RESET);
  PORTB |= (1<<DDB4);
}
