#ifndef Include
#include <avr/io.h>
#include <macros.h>
#define Include
#endif
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
#define uchar unsigned char
#define uint  unsigned int
#define ulint unsigned long int

void lcd_init(void);
void LCD_en_write(void);
void wait_LCD_Ready(void);
void set_LCD_xy(uchar x, uchar y );
void LCD_write_onechar(uchar COMM,uchar DAT);
void LCD_write_string(uchar X,uchar Y,uchar *string,unsigned int x);
