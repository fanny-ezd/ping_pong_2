#include "UARTdriver.h"
#include "MCP2515_ComDriver.h"
#define F_CPU 16000000
#include <util/delay.h>
//#include "Timer_driver.h"
#include "PWM_driver.h"
#include "IR_driver.h"
#include "TWI_Master.h"
#include "Motor_driver.h"
#include "Solenoid_driver.h"
volatile uint8_t var_motor;
volatile uint8_t var_servo;
//volatile uint8_t flag_l=0;


void main(){
  cli();
  var_motor=0x00;
  var_servo=0x00;
  USART_Init(MYUBRR);
  MCP2515_init();
  set_mode(MODE_NORMAL);
  MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);
  init_timer();
  IR_init();
  TWI_Master_Initialise();
  motor_init();
  solenoid_init();
  //cli();
  printf("Ola\n\r");
  //    _delay_ms(30000);
  sei();
  uint8_t aux;
  _delay_ms(1000);
  calibrate_motor();

  /*can_message test1;
  test1.AH=0b00000000; //IDjoystick a;
  test1.AL=0b10000000;  //ID
  test1.length=0b00000010;
  test1.data[0]='b';
  test1.data[1]='c';
*/

  while(1){
    //send_I2C(0x00);
    //printf("%04X\n\r",read_encoder());
    //sei();
  //  printf("%02X %02X\n\r", var_motor, var_servo );
    send_I2C(var_motor);
    sweep_direction(var_motor);
    var_PWM(var_servo);
    //rise_sol();
    read_encoder();
    //print_IR();
    //IR_check();
    //_delay_ms(50);

  //  sweep_direction(var_motor);
  //  printf("%02X\n\r",TWI_Get_State_Info() );
//  printf("%02X\n\r",var_motor );
  //  _delay_ms(100);
  //  printf("%02X\n\r",var_motor );
  //  read_encoder();
  //  printf("%02X\n\r",var_motor );
  //  _delay_ms(50);

    //printf("E\n\r" );
    //print_IR();
    //send_something_loop(test1);
  //  _delay_ms(50);
  }
//  uint8_t test=0x00;
    while(1){
printf("Hola\n\r" );/*
    var_PWM(test);
    test++;
    _delay_ms(100);
*/
  }



}
