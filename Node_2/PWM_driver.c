#include "PWM_driver.h"

void var_PWM(uint8_t data){
  uint16_t pulse_width=1976+(data-38)*8;
  uint16_t aux=pulse_width<<8;
  uint8_t pulse_H=pulse_width>>8;
  uint8_t pulse_L=aux>>8;
  //printf("%04X %02X %02X\n\r",pulse_width, pulse_H, pulse_L );
  if((pulse_width>1800)&&(pulse_width<4200)){
    OCR1AH=pulse_H;
    OCR1AL=pulse_L;
  }
}
