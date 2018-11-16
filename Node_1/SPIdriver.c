#include "SPIdriver.h"

void SPI_Init(){
  /* Set MOSI anjd SCK output, all others input */
  DDRB=(1<<DDB5)|(1<<DDB7)|(1<<DDB4);
  /* Enable SPI, Master, set clock rate fck/16 */
  SPCR=(1<<SPE)|(1<<MSTR)|(SPR0);
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


/*void SPI_SlaveInit(void){

// Set MiSO output, all others input
DDRB = (1<<DDB6);
//Enable SPI
SPCR = (1<<SPE);
}

char SPI_SlaveReceive (void)
{
// Wait for reception complete
while(!(SPSR &(1<<SPIF)));

//Return data register

return SPDR;

}*/
