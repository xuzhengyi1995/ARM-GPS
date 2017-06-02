#ifndef Include
#include <avr/io.h>
#include <macros.h>
#define Include
#endif
void USART1_Init( void );
void computer_transmit( unsigned char data );
unsigned char computer_receive( void );
void computer_transmit_string(unsigned char *data,unsigned int sum);

void USART0_Init( void );
void gps_transmit( unsigned char data );
unsigned char gps_receive( void );

