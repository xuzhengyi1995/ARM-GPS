#ifndef Include
#include <avr/io.h>
#include <macros.h>
#define  LCD_DATA_PORT    PORTA        //����LCD��D0-D7���ڶ˿�
#define  LCD_DATA_POUT    DDRA=0xFF    //����LCD���ݶ˿�Ϊ���
#define  LCD_DATA_PIN     DDRA=0x00    //����LCD���ݶ˿�Ϊ����(�ڶ�LCD״̬ʱ�õ�)

#define  LCD_Control_PORT PORTB        //����LCD��EN RW RS���ڶ˿ڷ���������
#define  LCD_Control_OUT  DDRB|=(1<<DDB5)|(1<<DDB6)|(1<<DDB7)
#define  LCD_Control_IN   DDRB&=~((1<<DDB5)|(1<<DDB6)|(1<<DDB7))

#define  LCD_EN_1         PORTB|=1<<PD7
#define  LCD_EN_0         PORTB&=~(1<<PD7)
#define  LCD_RW_1         PORTB|=1<<PD6
#define  LCD_RW_0         PORTB&=~(1<<PD6)
#define  LCD_RS_1         PORTB|=1<<PD5
#define  LCD_RS_0         PORTB&=~(1<<PD5)
#define Include
#endif
void mcu_io_init(void);
