#include "init.h"
void mcu_io_init(void)
{    
	 DDRF |=0X0E;           //LED�����������IO����Ϊ���
	 PORTF|=0X0E;             
	
	 DDRA=0XFF;             //LED IO����Ϊ���
	 PORTA=0XFF;
	 PORTF&=0xF7;           //�������ݹر�LED
	 
	 PORTA=0X00;
	 PORTF&=0XF8;           //�������ݹر������
	 
	 DDRB |=0X10;           //PB4��Ϊ���
	 PORTB|=0X10;           //�ر�PB4��ӵ�LED
     
	 LCD_DATA_PORT=0xff;
	 LCD_DATA_POUT;          //LCD���ݿ���Ϊ���
	
	 LCD_EN_1;
	 LCD_RW_1;
	 LCD_RS_1;
	 LCD_Control_IN;
}
