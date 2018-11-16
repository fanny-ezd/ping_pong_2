#define F_CPU 4915200

#include "UARTdriver.h"
#include <util/delay.h>
#include <stdio.h>
#include "latch.h"
#include "joystick.h"
#include "oled.h"
#include "MCP2515_ComDriver.h"




// cli() Disable interrupts
 //sei() Enable interrupts

void main()
{


    USART_Init(MYUBRR);
    en_eMem();
    oled_init();
    MCP2515_init();
    uint8_t result;
    set_mode(MODE_NORMAL);
    MCP2515_Bit_Modify(MCP_CANINTE, MCP_RX0IE, MCP_RX0IE);
    joystick_init();
  //  buttons_init();
    /*while(1){
    print_left_right();
  }*/
    slider test;
    can_message test1;
  //  _delay_ms(5000);
    buttons_init();
    sei();
    screen menu;
    menu.num=1;
    menu.write="---Main  menu---$Want to play?$     New game$     Resume game$     Exit";
    menu.with_arrow=true;
    screen submenu;
    submenu.num=2;
	  submenu.write="     Try$     Try$     Try";
    menu.next[2]=&submenu;
    menu.next[3]=&submenu;
    menu.next[4]=NULL;
    menu.prev=&menu;
    submenu.prev=&menu;
    submenu.with_arrow=true;
    screen ext_sub;
    ext_sub.num=2;
    ext_sub.write="$$Go to the rigth$  to continue  ";
    ext_sub.with_arrow=false;
    ext_sub.prev=&submenu;
    menu.next[4]=&ext_sub;
    screen zero;
    zero.write="$    @@@@@@@@    $    @      @    $    @      @    $    @      @    $    @      @    $    @@@@@@@@    ";
    zero.with_arrow=false;
  //  interface(&menu);
    screen *h=&menu;
    printf("%d\n\r",interface2(&h) );
   printf("Hello world\n\r" );

  //  MCP2515_write(MCP_TXB0SIDH, 0b10101010);
  //  printf("%02X\n\r", MCP2515_read(MCP_TXB0SIDH));
  //  MCP2515_Bit_Modify(MCP_TXB0SIDH, 0b00001111, 0);
    //printf("%02X\n\r", MCP2515_read(MCP_TXB0SIDH));;

/*while(1){
  test=return_pos_joystick();
  printf("%02X %02X\n\r", test.X,test.Y);
  _delay_ms(1000);
}*/

    test1.AH=0b00000000; //IDjoystick a;
    test1.AL=0b10000000;  //ID
    test1.length=0b00001000;
    for(int i=0; i<8; i++){
        test1.data[i]='a'+i;

      }


    while(1){
    //  printf("Hola\n\r" );
   send_joystick_slider();
   _delay_ms(10);
   send_button_right();
    //send_slider_TXB0();
  //  print_left_right();
    //_delay_ms(50);
     //send_something_loop(test1);
    // test=return_pos_joystick();
    // printf("%02X %02X\n\r",test.X,test.Y );
  //   print_x_y();

    send_button_left();

  //  SRAM_test()
  //test=return_pos_joystick();
  //printf("%d %d\n\r",test.X,test.Y );
   //print_x_y();
    //printf("Errors?\n\r");
    //  _delay_ms(1000);

    }


/*    SPI_Init();
while(1){
  SPI_read();
}*/

    /*while (1) {
      printf("%s\n\r", "Hello");
      _delay_ms(50);}
      /* code
    }*/


  //  joystick test;
  //  char line=1;
//while (1){
  //  just_try2();
  /*while(1){
    //joystick_init();
    //test=return_pos_joystick();
  //  printf("%d %d\n\r",test.X,test.Y );
print_x_y();
    _delay_ms(500);
  }*/

  /*  clear();
    just_try();
    clear();
    just_try2();*/
    //scroll_init(0,0,7);




  // setup_oled();


//    while(1){
//      printf("Hello world %d\n\r", 42);
//    }
/*(uint8_t *)
    //  p=(char *)0xFFFF;
      //*p=0xFF;
      //_delay_ms(1000);

    //  p=(char *)0xFF00;
    //  *p=0x00;
     _delay_ms(2000);
*/

//    char *a=(char *)0x12FF;



/*while(1){
    printing();
    printf("a");
//}
    //printing();

    //test=return_pos();
    //printf("(X = %d , Y = %d )\n\r",test.X,test.Y );
    //_delay_ms(500);
    //test1();
      //SRAM_test();
}
/*while (1){
p=0x1800;
*p=FF;
_delay_ms(2000);
p=0x1400;
*p=FF;
_delay_ms(2000);
}*/

/*MCP2515_init()
  while (1) {
    MCP2515_read(0b01);
    MCP2515_write(0b01);
    printf("");

*/
  /* code */
}
