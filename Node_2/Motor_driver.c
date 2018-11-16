#include "Motor_driver.h"
#define _OE PH5
#define DIR PH1
#define SEL PH3
#define _RST PH6
#define EN PH4
#define ABS(x) ((x)<0?(-(x)):(x))
extern bool flag_enc;
volatile uint16_t max_dec;
volatile uint16_t min_dec;
volatile uint16_t range;


void motor_init(){
  DDRH|=(1<<DDH1)|(1<<DDH3)|(1<<DDH4)|(1<<DDH5)|(1<<DDH6); //H1->DIR, H3->SEL, H4->EN, H5->!OE, H6->RST outputs for arduino
  DDRK=0b00000000; // All K pins are inputs from decoder
  PORTH|=(1<<EN); // Enable motor
  PORTH|=(1<<_RST); //Enable encoder counting



}

uint16_t read_encoder(){
  if(flag_enc){
    flag_enc=false;
    uint8_t auxL;
    uint8_t auxH;
    uint16_t aux;
    PORTH&=(~(1<<_OE)); // !OE high, output encoder Enable
    PORTH&=(~(1<<EN)); // SEL high, MSB
    _delay_us(20);
    auxH=PINK; // Read MSB
    PORTH|=(1<<EN); // SEL high, MSB
    _delay_us(20);
    auxL=PINK; //Read MSB
    PORTH|=(1<<_OE);
    aux=auxH;
    aux=aux<<8;
    aux+=auxL;
    printf("%04X\n\r",aux );
    return aux;
  }
}

void sweep_direction(uint8_t data){
  if(data<0x80){
    PORTH&=(~(1<<DIR)); //To the left
  }
  else{
    PORTH|=(1<<DIR); //To the right
  }
}

void calibrate_motor(){
  cli();
  PORTH&=(~(1<<_RST)); //Toggle Reset
  PORTH|=(1<<_RST);
  sweep_direction(0xC0);
  send_I2C(0xC0);
  _delay_ms(1700);
  send_I2C(0x80);
  _delay_ms(500);
  min_dec=read_encoder();
  sweep_direction(0x40);
  send_I2C(0x40);
  _delay_ms(3200);
  send_I2C(0x80);
  _delay_ms(500);
  max_dec=read_encoder();
  //printf("%04X %04X\n\r",min_dec,max_dec );
  range=max_dec-min_dec;
  sei();
}

void position_motor(){

}

void stop_motor(){  PORTH&=(~(1<<EN));}
void en_motor(){   PORTH|=(1<<EN);}
