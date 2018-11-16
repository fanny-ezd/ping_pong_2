#include "MCP2515_ComDriver.h"
#include "joystick.h"

volatile bool flag_r=false;
volatile bool flag_l=false;

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
   DDRE&=(~(1<<DDE0)); // The interrup is in E0

   GICR|=(1<<INT2);  // Enable INT2
   EMCUCR&=(~(1<<ISC2)); // Interrupt produced when falling edge
   //sei();
   MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);
   MCP2515_write(MCP_RXB0CTRL, MCP_RXB0CTRL|0x60); //Recieve everything in Buffer RXB0

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

void send_joystick_TXB0(){
  int i;
  joystick aux;
  MCP2515_write(MCP_TXB0SIDH, 0x00);
  MCP2515_write(MCP_TXB0SIDL, 0x20);
  MCP2515_write(MCP_TXB0DLC, 0x01);
  //for(i=0; i<4; i++){
    aux=return_pos_joystick();
    MCP2515_write(MCP_TXB0D0/*+2*i*/, aux.X);
    MCP2515_write(MCP_TXB0D0/*+2*i+*/+1, aux.Y);
  //}
  MCP2515_Request_to_send(MCP_RTS_TX0);
}

void send_slider_TXB0(){
  int i;
  slider aux;
  MCP2515_write(MCP_TXB0SIDH, 0x00);
  MCP2515_write(MCP_TXB0SIDL, 0x40);
  MCP2515_write(MCP_TXB0DLC, 0x01);
  //for(i=0; i<8; i++){
    aux=return_pos_slider();
    MCP2515_write(MCP_TXB0D0, aux.R);
    printf("%02X\n\r",aux.R );
//  }
  MCP2515_Request_to_send(MCP_RTS_TX0);
}

void send_joystick_slider(){
  joystick aux_j;
  slider aux_s;
  MCP2515_write(MCP_TXB0SIDH, 0x00);
  MCP2515_write(MCP_TXB0SIDL, 0xE0);
  MCP2515_write(MCP_TXB0DLC, 0x04);
  aux_j=return_pos_joystick();
  aux_s=return_pos_slider();
  MCP2515_write(MCP_TXB0D0, aux_j.X);
  MCP2515_write(MCP_TXB0D0+1, aux_j.Y);
  MCP2515_write(MCP_TXB0D0+2, aux_s.R);
  MCP2515_write(MCP_TXB0D0+3, aux_s.L);
  MCP2515_Request_to_send(MCP_RTS_TX0);
}

void send_button_right(){
  if(flag_r){
    flag_r=false;
    MCP2515_write(MCP_TXB0SIDH, 0x00);
    MCP2515_write(MCP_TXB0SIDL, 0x40);
    MCP2515_write(MCP_TXB0DLC, 0x01);
    MCP2515_write(MCP_TXB0D0, 0x00);
    MCP2515_Request_to_send(MCP_RTS_TX0);
    _delay_ms(10);
  }
}

void send_button_left(){
  if(flag_l){
    flag_l=false;
    MCP2515_write(MCP_TXB0SIDH, 0x00);
    MCP2515_write(MCP_TXB0SIDL, 0x20);
    MCP2515_write(MCP_TXB0DLC, 0x01);
    MCP2515_write(MCP_TXB0D0, 0x00);
    MCP2515_Request_to_send(MCP_RTS_TX0);
    _delay_ms(10);
  }
}






ISR(INT2_vect) {
  uint8_t length;
  MCP2515_Bit_Modify(MCP_CANINTF, MCP_RX0IF, ~MCP_RX0IF);
  uint8_t result[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  if((0x00==MCP2515_read(MCP_RXB0SIDH))&&(0x20&MCP2515_read(MCP_RXB0SIDL))){
    for (uint8_t i=0; i<4;i++){
      result[2*i]=MCP2515_read(MCP_RXB0D0+2*i);
      result[2*i+1]=MCP2515_read(MCP_RXB0D0+2*i+1);
      printf("%02X %02X\n\r",result[2*i], result[2*i+1] );
    }
  }
  else if((0x00==MCP2515_read(MCP_RXB0SIDH))&&(0x40&MCP2515_read(MCP_RXB0SIDL))){
    for (uint8_t i=0; i<8;i++){
      result[i]=MCP2515_read(MCP_RXB0D0+i);
      printf("%02X\n\r",result[i]);
      //send_I2C(result[i]); // Change DAC form MAX510 with slider right
    }
  }
  else{
    length=(0x0F&MCP2515_read(MCP_RXB0DLC));
    if(length>0x08){
      length=0x08;
    }
    for(uint8_t i=0;i<length;i++){
      result[i]=MCP2515_read(MCP_RXB0D0+i);
      printf("%c\n\r", result[i]);
    }
    printf("%d\n\r",length );
  }



}

/*0b1010101);
MCP2515_write(MCP_TXB0SIDL, (MCP_TXB0SIDL|0b10100000));
MCP2515_write(MCP_TXB0DLC, 0b00000001);
MCP2515_write(MCP_TXB0D0, (uint8_t)data);
*/
