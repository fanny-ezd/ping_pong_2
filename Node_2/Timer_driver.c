#include "Timer_driver.h"
#define MED 3000 // 0x0BB8
#define MIN 1800 // 0x07D0
#define MAX 4200 // 0x0FA0
extern uint16_t val_left;
extern uint16_t val_right;
bool flag_enc=false;
bool flag_timer=false;
// Partitions 0,0005 ms
uint8_t counter=0;
uint16_t encoder;
uint8_t aux;

void init_timer(){
  DDRB|=(1<<DDB5);
  TCCR1A|=(1<<COM1A1); //Non-invertin mode
  TCCR1A&=(~(1<<COM1A0)); //Non_invertin mode
  TCCR1A|=(1<<WGM11);//MODE
  TCCR1A&=(~(1<<WGM10));   //MODE
  TCCR1B|=(1<<WGM13)|(1<<WGM12);   //MODE 1110
  TCCR1B&=(~(1<<CS12))&(~(CS10)); // clk/8
  TCCR1B|=(1<<CS11); // clk/8
  ICR1H=0x9C;// TOP 40000
  ICR1L=0x40; //TOP 40000
  OCR1AH=0x0B; //MED
  OCR1AL=0xB8; //MED
  TIMSK1|=(1<<TOIE1); // Enable periodic interrupt

     //cli(); //Disable interrupts
     //sei() //Enable interrupts


}

ISR(TIMER1_OVF_vect){
  if(counter<5){
    counter++;
    flag_timer=true;
  }
  else{
    aux=read_encoder();
    if(aux<)
    flag_enc=true;
    //printf("HEy\n");
    //encoder=read_encoder();
    //printf("%04X\n\r", encoder);
    counter=0;
  }

  //printf("HEllo\n\r" );
}
