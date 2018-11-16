#include "Solenoid_driver.h"
volatile bool flag_r=false;
volatile bool flag_l=false;

void solenoid_init(){
  DDRC|=(1<<DDC0);
  PORTC&=(~(1<<PC0));
}

void rise_sol(){
  if(flag_r){
    flag_r=false;
    PORTC|=(1<<PC0);
    _delay_ms(100);
    PORTC&=(~(1<<PC0));
  }
}
