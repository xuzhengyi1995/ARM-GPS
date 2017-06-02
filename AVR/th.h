#ifndef Include
#include <avr/io.h>
#include <macros.h>
#include "delay.h"
#define Include
#endif
#define DATA_IN DDRG &= ~(1 << PG0) /*��������*/
#define DATA_OUT DDRG |= (1 << PG0) /*�������*/
#define DATA_CLR PORTG &= ~(1 << PG0) /*�õ͵�ƽ*/
#define DATA_SET PORTG |= (1 << PG0) /*�øߵ�ƽ*/
#define DATA_READ PING & (1 <<PG0) /*�����ƽ*/

unsigned char get_th(unsigned char *DHT_value);
unsigned char DHT_byte(unsigned char *p);
void DHT_read(unsigned char *p);
