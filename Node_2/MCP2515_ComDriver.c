#include "MCP2515_ComDriver.h"
#include "PWM_driver.h"

extern uint8_t var_motor;
extern uint8_t var_servo;
extern bool flag_r;
extern bool flag_l;

void MCP2515_init(){

  uint8_t value;

   SPI_Init();
   MCP2515_Reset();
   //MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);

  /* MCP2515_read(MCP_CANSTAT,& value);
   if ((value & MODE_MASK)!=MODE_CONFIG){
     printf("MCP2513 is NOT in configuration mode after reset!\n");
     return 1;
   }*/
   // Interrupt
   DDRD&=(~(1<<DDD2));

   EIMSK|=(1<<INT2); // Enable interrupts in INT2
   EICRA|=(1<<ISC21);
   EICRA&=(~(1<<ISC20));

   MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);
   MCP2515_write(MCP_RXB0CTRL, MCP_RXB0CTRL|0x60); //Recieve everything in Buffer RXB0
//   MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX1IE, MCP_RX1IE);

  // cli() Disable interrupts
   //sei() Enable interrupts

}

void set_mode(uint8_t mode){
  MCP2515_Bit_Modify(MCP_CANCTRL, MODE_MASK, mode);
//  while((MCP2515_read(MCP_CANSTAT)&MODE_MASK)!=mode){}
}


void send_something_loop(can_message message){

  MCP2515_write(MCP_TXB0SIDH, message.AH);
  MCP2515_write(MCP_TXB0SIDL, message.AL);
  MCP2515_write(MCP_TXB0DLC, message.length);
  for(uint8_t i=0;i<message.length;i++){
    MCP2515_write(MCP_TXB0D0+i, (uint8_t)message.data[i]);
  }
MCP2515_Request_to_send(MCP_RTS_TX0);
}

void recieve_something_loop(){
  if(MCP2515_read(MCP_CANINTF)&MCP_RX0IF){
    MCP2515_Bit_Modify(MCP_CANINTF, MCP_RX0IF, 0x00);
    printf("%c\n\r", MCP2515_read(MCP_RXB0D0));
  }
}




ISR(INT2_vect) {
  //printf("Interrupt\n\r" );

  uint8_t length=(0x0F&MCP2515_read(MCP_RXB0DLC));
  if(length>0x08){
    length=0x08;
  }
  uint8_t auxH=MCP2515_read(MCP_RXB0SIDH);
  uint8_t auxL=MCP2515_read(MCP_RXB0SIDL);
  uint8_t result[8];
  MCP2515_Bit_Modify(MCP_CANINTF, MCP_RX0IF, ~MCP_RX0IF);
  for(uint8_t i=0; i<length;i++){
    result[i]=MCP2515_read(MCP_RXB0D0+i);
  }
  if((0x00==auxH)&&(0xE0==auxL)){
    /*for (uint8_t i=0; i<4;i++){
      result[2*i]=MCP2515_read(MCP_RXB0D0+2*i);
      result[2*i+1]=MCP2515_read(MCP_RXB0D0+2*i+1);
      printf("%02X %02X\n\r",result[2*i], result[2*i+1] );
      var_PWM(result[2*i]); // Change PWM with joystick
    }*/
    /*for(uint8_t i=0; i<length;i++){
      result[i]=MCP2515_read(MCP_RXB0D0+i);
    }*/
    //printf("%02X %02X\n\r",result[0], result[1] );
    //sweep_direction(result[0]);
    var_motor=result[0];
    var_servo=result[2];
    //send_I2C(result[0]);

  }
  /*else if((0x00==auxH)&&(0x80==auxL)){
    for (uint8_t i=0; i<8;i++){
      result[i]=MCP2515_read(MCP_RXB0D0+i);
      printf("%02X\n\r",result[i]);
      send_I2C(result[i]); // Change DAC form MAX510 with slider right
    }
  }*/
  else if((0x00==auxH)&&(0x20==auxL)){//if((0x00==auxH)&&(0xE0==auxL)){
    //length=(0x0F&MCP2515_read(MCP_RXB0DLC));
  /*  if(length>0x08){
      length=0x08;
    }
    for(uint8_t i=0;i<length;i++){
      result[i]=MCP2515_read(MCP_RXB0D0+i);
      //send_I2C(result[i]);
      var_motor=result[i];
      sweep_direction(var_motor);
      //printf("%02X\n\r", result[i]);
    }*/
   printf("left\n\r" );
    flag_l=true;
  }
  if((0x00==auxH)&&(0x40==auxL)){
    printf("rigth\n\r" );
    flag_r=true;
  }
}
