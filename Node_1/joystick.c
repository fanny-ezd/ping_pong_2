#include "joystick.h"
#define ABS(x) ((x)<0?(-(x)):(x))

volatile uint8_t *p=(uint8_t *)0x1400;
volatile joystick calibration;
volatile joystick reference;
volatile uint8_t countx=0;
volatile uint8_t county=0;
volatile uint8_t resume=0; // To stop the game
//volatile uint8_t calINT1=0;
//volatile uint8_t calINT0=0;
extern bool flag_r;
extern bool flag_l;
uint8_t read_adc(){
	return *p;
}

void write_adc(uint8_t data){
	*p=data;
}



void joystick_init(){
	calibration.X=0x80;
	calibration.Y=0x80;
	reference.X=0x80;
	reference.Y=0x80;
	uint8_t aux1,aux2;



	//printf("%d %d\n\r", calibration.X, calibration.Y);
	//char a, b;
	//a=calibration.X;
	//b=calibration.Y;
//	printf("%d %d\n\r",a,b );
	/*while(calibration.X<0x80){
		write_adc(0x04);
		_delay_us(40);
		aux1=read_adc();
		if(ABS(calibration.X-aux1)<100){
			calibration.X=aux1;
		}
		_delay_us(40);
		//	printf("%02X %02X\n\r", calibration.X, calibration.Y);
	}
	while(calibration.Y<0x80){
		write_adc(0x05);
		_delay_us(40);
		aux2=read_adc();
		if(ABS(calibration.Y-aux2)<100){
			calibration.Y=aux2;
		}
		_delay_us(40);
			//printf("%02X %02X\n\r", calibration.X, calibration.Y);
	}
	reference.X=calibration.X;
	reference.Y=calibration.Y;
	printf("Calibrated correctly\n\r");*/
}


/*void test1(){
    volatile char *p=(char *)0x1400;
    uint8_t val;
    val=*p;
}*/

void buttons_init(){ // To use the buttons over the sliders
	DDRD&=(~(DDD2))&(~(DDD3)); // D2 and D3 as outputs
	GICR|=(1<<INT0)|(1<<INT1);  // Enable interrupts
	MCUCR|=(1<<ISC01)|(1<<ISC00);
	MCUCR|=(1<<ISC11)|(1<<ISC10); // Interrupt activates whith rising edge (LEFT)
//	EMCUCR|=(1<<ISC01)|(1<<ISC00); // Interruts activates with rising edge  (RIGHT)
}

void print_x_y(){
    joystick a;
    write_adc(0x04);
    _delay_us(100);
    a.X=read_adc();
    _delay_us(100);
    write_adc(0x05);
    _delay_us(100);
    a.Y=read_adc();
    _delay_us(100);
    printf("( %02d , %02d )\n\r", a.X, a.Y);
}

void print_left_right(){
    slider a;
    write_adc(0x06);
    _delay_us(100);
    a.R=read_adc();
    _delay_us(100);
    write_adc(0x07);
    _delay_us(100);
    a.L=read_adc();
    _delay_us(40);
    printf("( %02X , %02X )\n\r", a.L, a.R);
}

/*void test4(){
    volatile char *p=(char *)0x1400;
    uint8_t valleft,valright,valleft_Voltage,valright_Voltage;
    *p=0x06;
    _delay_us(200);
    valleft=*p-0xFF;
    valleft_Voltage= valleft*5/255;
    _delay_us(200);
    *p=0x07;
    _delay_us(200);
    valright=*p-0xFF;
    valright_Voltage=valright*5/255;
    _delay_us(200);
    printf("( %02d , %02d )\n\r", valleft_Voltage, valright_Voltage);
}*/

joystick return_pos_joystick(){
		uint8_t aux1,aux2;
		joystick servo;
		servo.X=0x80;
    write_adc(0x04);
		_delay_us(40);
		aux1=read_adc();
		if(ABS(calibration.X-aux1)<100){
			calibration.X=aux1;
		}
		else{
				calibration.X=reference.X;
		}
		write_adc(0x05);
		_delay_us(40);
		aux2=read_adc();
		if(ABS(calibration.Y-aux2)<100){
			calibration.Y=aux2;
		}
		else{
				calibration.Y=reference.Y;
		}
		_delay_us(40);
		if((calibration.X>0x7D)&&(calibration.X<0x84)){ // For the servo not to be affected by noise when joystick idle
			servo.Y=calibration.Y;
			return servo;
		}
		else{
    return calibration;
		}
}

slider return_pos_slider(){
	slider a;
    write_adc(0x06);
    _delay_us(40);
    a.R=read_adc();
    _delay_us(40);
    write_adc(0x07);
    _delay_us(40);
    a.L=read_adc();
    _delay_us(40);
	return a;
}//Scroll


uint8_t return_direction_joystick(){
	joystick a;
	a=return_pos_joystick();
	if((a.X>250)||(a.Y>250)){
		if(a.X>a.Y){
			return 1; //RIGHT
		}
		else if(a.X<a.Y){
			return 2; //UP
		}
	}
	else if((a.X<5)||(a.Y<5)){
		if(a.X<a.Y){
			return 0; //LEFT
		}
		else if(a.X>a.Y){
			return 3; //DOWN
		}
	}
	else{
		return 4; //NEUTRAL
	}
}


ISR(INT1_vect){
	//if(calINT1>2){
		printf("Left\n\r" );
		flag_l=true;
	//}
	//else{
	//	calINT1++;
	//}


}

ISR(INT0_vect){
	//if(calINT0>2){
		printf("Right\n\r" );
		flag_r=true;
		//_delay_ms(1000);
	//}
	//else{
	//	calINT0++;
	//}
}
