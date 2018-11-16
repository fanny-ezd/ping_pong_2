#include "latch.h"
#include <util/delay.h>


void en_eMem(){
  MCUCR |= (1<<SRE);
  SFIOR|=(1<<XMM2);
}

//void mask_out()

char* adress(char *a){
  char *p=a;
  return p;
}

void data(uint8_t b, char *p){
  *p=b;
}

void SRAM_test(){
  volatile char *ext_ram=(char *)0x1800;
  uint16_t ext_ram_size=0x800;
  uint16_t write_errors=0;
  uint16_t retrieval_errors=0;
  printf("Starting SRAM test...\n\r");
  _delay_ms(50);
  uint16_t seed=rand();
  srand(seed);
  for(uint16_t i=0;i<ext_ram_size;i++){
    uint8_t some_value = rand();
    ext_ram[i] = some_value;
    uint8_t retreived_value = ext_ram[i];
    if (retreived_value != some_value) {
      printf("Write phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value,some_value);
      write_errors++;
      _delay_ms(50);
  }
}

  srand (seed);
  for(uint16_t i = 0; i < ext_ram_size; i++) {
    uint8_t some_value = rand();
    uint8_t retreived_value = ext_ram[i];
    if (retreived_value != some_value) {
      printf("Retrieval phase error: ext_ram[%4d] = %02X (should be %02X)\n\r", i, retreived_value, some_value);
      retrieval_errors++;
      _delay_ms(50);
    }
  }
  printf("SRAM test completed with \n\r%4d errors in write phase and \n\r%4d errors in retrival phase\r\n\r\n", write_errors, retrieval_errors);
  _delay_ms(50);
}
