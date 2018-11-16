#include "SPIdriver.h"

void SPI_Init(){
  /* Set MOSI anjd SCK output, all others input */
  DDRB=(1<<DDB2)|(1<<DDB1)|(1<<DDB0)|(1<<DDB7);
  PORTB|=(1<<DDB7);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_send(char cData){
  /* Start transmission */
  SPDR=cData;
  /* Wait for transmission complete */
  while(!(SPSR&(1<<SPIF)));
}

char SPI_read(){
  /* Send a dummy byte */
  SPI_send(0);
  return SPDR;
}
