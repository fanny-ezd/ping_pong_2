#include "IR_driver.h"
volatile count=0;
volatile uint16_t IR_val[5];
volatile uint16_t IR_average;
extern bool flag_timer;

void IR_init(){
  DDRF&=(~(1<<DDF0));
  ADCSRA|=(1<<ADEN); // ADC Enable
  ADMUX&=0b00000000;  //AVCC with external capacitor at AREF pin . Info to the right. input ADC08
//  ADMUX|=(1<<REFS0); //AVCC with external capacitor at AREF pin
//  ADMUX&=(~(1<<REF1)); //AVCC with external capacitor at AREF pin
  ADCSRB&=(~(1<<MUX5)); // Info from port ADC08
  //ADCSRA|=(1<<ADIF); // When ADIF low, finished with the conversion
  ADCSRA&=(~(1<<ADPS1)&(~(1<<ADPS0))); // Division Factor 32
  ADCSRA|=(1<<ADPS2);//|(1<<ADPS0);
}

uint16_t read_IR(){
  uint16_t a;
  ADCSRA|=(1<<ADSC);
  while(ADCSRA&(1<<ADSC)){};
  //ADCSRA|=(1<<ADIF);

  cli();
  a = ADC;
  sei();
  return a;
}

void print_IR(){
  printf("%04X\n\r", read_IR() );
}

void IR_check(){
  if(flag_timer){
    flag_timer=false;
    if(count<25){
      IR_val[count]=read_IR();
      IR_val[count]=(IR_val[count])<<16;
      IR_val[count]=(IR_val[count])>>16;
      IR_average+=IR_val[count];
      count++;
    }
    else{
      count=0;
      if(IR_average<=(0x003F*25)){
        //printf("HUeeee\n\r");
      }
      IR_average=0x0000;
      printf("hey\n\r" );
    }
  }
}
