#include "UARTdriver.h"

void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char) ubrr;
/*
Enable receiver and transmitter
 */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/*
Set frame format: 8data, 2stop bit
 */
UCSR0C = (1<<USBS0)|(3<<UCSZ00);

fdevopen(Usart_sending, Usart_receive);

}

int Usart_sending ( char data, FILE * _out)
{
  (void)(_out);

    while ( ! ( UCSR0A & (1<<UDRE0)));
    UDR0 = data;

    return 0;
}

int Usart_receive (FILE * _in)
{
  (void)(_in);

    while ( ! ( UCSR0A & (1<<RXC0)));
    return UDR0;

}
