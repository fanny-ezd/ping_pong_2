 #include "oled.h"
#include "fonts.h"
#define COMMAND 0x1000
#define DATA 0x1200



volatile uint8_t *h = (uint8_t *)0x1000;
volatile uint8_t *q = (uint8_t *)0x1200;
volatile char go_to;
volatile char current_line=0;



void write_c(uint8_t x){
  *h=x;
}

void write_d(uint8_t x){
  *q=x;
}

void oled_init(){
    write_c(0xae);// display off
    write_c(0xa1);//segment remap
    write_c(0xda);//common pads hardware: alternative
    write_c(0x12);
    write_c(0xc8); //common output scan direction:com63~com0
    write_c(0xa8);//multiplex ration mode:63
    write_c(0x3f);
    write_c(0xd5); //display  divide ratio/osc. freq. mode
    write_c(0x80);
    write_c(0x81);//contrast contro
    write_c(0x50);
    write_c(0xd9);//set pre-charge period
    write_c(0x21);
    write_c(0x20); //Set Memory Addressing Mode
    write_c(0x02);
    write_c(0xdb); //VCOM deselect level mod
    write_c(0x30);
    write_c(0xad);//master configuration
    write_c(0xa4); //out follows RAM
    write_c(0xa6);//set normal display
    write_c(0xaf);// display on
  	write_c(0xb0);
  	write_c(0x00);
  	write_c(0x10);
    clear();
  //  clear_C();
}

void clear(){
//	for(char i=0; i<8;){
  for(char i=0;i<8;i++){
    oled_pos(i,0);
		for(uint8_t j=0; j<128;j++){
		write_d(0x00);
		}
	}
}

/*void clear_C(){
  for(int i=0;i<8;i++){
    C[i]=0;
  }
}*/

void go_to_column(char column){
    volatile uint8_t higher, lower;
    higher=((uint8_t)column)>>4;
    higher=higher+0x10;
    lower=((uint8_t)column)<<4;
    lower=lower>>4;
    write_c(higher);
    write_c(lower);
}

void go_to_line(char line){
    write_c(0xb0+(uint8_t)line);
}


void oled_pos(char row, char column){
    go_to_line(row);
    go_to_column(column);
}

void write_letter(const char letter){
    for(uint8_t i=0;i<8;i++){
      write_d(pgm_read_byte(&(font8[letter-' '][i])));
      }
}



/*void oled_print(const char *word, char current_line){
  int i=0;
  char k=0;
  clear_C();
  oled_pos(current_line,0);
  while(word[i]!='\0'){
      if(word[i]!='$'){
        write_letter(word[i]);
        if((word[i]!=' ')&&(word[i-1]==' ')&&(word[i-2])){
          C[current_line]=k;
        }
        k++;
        }
      else{
        current_line++;
        oled_pos(current_line,0);
        k=0;
        }
      i++;
  }
}

// SCREENSHOTS

void write_arrow(char line, char pos){
  oled_pos(line,pos);
  write_d(0b00011000);
  write_d(0b00011000);
  write_d(0b01111110);
  write_d(0b00111100);
  write_d(0b00011000);
}

void select_line_joystick(char line){
  write_arrow(line,  C[line]);
}*/

void oled_print(screen *data){  //const char *word, char current_line){
  clear();
  int i=0;
  char k=0;
  //clear_C();
  oled_pos(k,0);
  if(data->write[0]==' '){
	  data->C[0]=1;
  }
  while(data->write[i]!='\0'){
      if(data->write[i]!='$'){
        write_letter(data->write[i]);
        }
      else{
		      k++;
          oled_pos(k,0);
		      if((data->write[i+1]==' ')){
			        data->C[k]=true;
		          }
          else{
            data->C[k]=false;
          }
        }
      i++;
  }
}

// SCREENSHOTS

void write_arrow(char line){
  oled_pos(line,0);
  write_d(0b00011000);
  write_d(0b00011000);
  write_d(0b01111110);
  write_d(0b00111100);
  write_d(0b00011000);
}

void clean_arrow(char line){
	oled_pos(line, 0);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
	write_d(0b00000000);
}

/*void select_line_joystick(char line, screen data){
	if(data.C[line]==1){
		write_arrow(line);
	}
}*/

void screen_arrow(screen data){
  //char current_line;
//  char aux;
  if(data.with_arrow){
    for(current_line=0;current_line<8;current_line++){
      if(data.C[current_line]){
        write_arrow(current_line);
        break;
      }
    }
  }

  go_to=return_direction_joystick();
  while(go_to>1){
    //printf("%d\n\r",aux );
    if(data.with_arrow){
      if(go_to==3){
        clean_arrow(current_line);
        if(current_line<7){
          current_line++;
          if(data.C[current_line]){

          }
          else{
            while(!data.C[current_line]){
              if(current_line<7){
                current_line++;
              }
              else{
                current_line=0;
              }
            }

          }
            write_arrow(current_line);
        }
        else{
          current_line=0;
          if(data.C[current_line]){

          }
          else{
            while(!data.C[current_line]){
              if(current_line<7){
                current_line++;
              }
              else{
                current_line=0;
              }
            }

          }
            write_arrow(current_line);
        }
        _delay_ms(100);
        while(return_direction_joystick()==3){};
        _delay_ms(100);
      }
       else if(go_to==2){
    				clean_arrow(current_line);
    				if(current_line>0){
    					current_line--;
    					if(data.C[current_line]){

    					}
    					else{
    						while(!data.C[current_line]){
    							if(current_line>0){
    								current_line--;
    							}
    							else{
    								current_line=7;
    							}
    						}

    					}
              	write_arrow(current_line);

    				}
    				else{
    					current_line=7;
    					if(data.C[current_line]){

    					}
    					else{
    						while(!data.C[current_line]){
    							if(current_line>0){
    								current_line--;
    							}
    							else{
    								current_line=7;
    							}
    						}

    					}
              	write_arrow(current_line);

    				}
            _delay_ms(100);
            	while(return_direction_joystick()==2){};
              _delay_ms(100);
    			}
        }

        go_to=return_direction_joystick();
  		}


      //printf("%d %d \n\r",go_to, current_line );
      //return aux;

}

void interface(screen *data){
  oled_print(data);
//  go_to=screen_arrow(*data);
  if(go_to==1){
    if((data->next[current_line])!=NULL){
      interface(data->next[current_line]);
    }
    else{
      return;
    }
  }
  else if(go_to==0){
    if((data->prev)!=NULL){
        interface(data->prev);
    }
    else{
      return;
    }
  }
  return;
}

char interface2(screen **h){
  char num_screen;
  while(*h!=NULL){
    num_screen=(*h)->num;
    oled_print(*h);
    screen_arrow(**h);
    if(go_to==1){
      while(return_direction_joystick()==1){};
      *h=((*h)->next[current_line]);
    }
    else if(go_to==0){
      while(return_direction_joystick()==0)
      *h=((*h)->prev);
    }
  }
  return num_screen;
}
/*void Hello_world(){
	oled_pos(0,0);
 oled_print("Hello world$Hello world$Hello world$Hello world$Hello world$Hello world$Hello world$Hello world", 0);
}

void just_try(){
  oled_pos(0,0);
  oled_print("Hey what's up$I'm fine and yu?",0);
}

void I(){
  oled_pos(0,0);
  oled_print("I$I$I$I$I$I$I$I",0);
}

void just_try2(){
  oled_pos(0,0);
  oled_print("What do u do$   1.Start$   2.Quit$   3.Scape",0);
}*/
