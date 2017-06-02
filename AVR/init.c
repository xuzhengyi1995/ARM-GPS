#include "init.h"
void mcu_io_init(void)
{    
	 DDRF |=0X0E;           //LED及数码管锁存IO口设为输出
	 PORTF|=0X0E;             
	
	 DDRA=0XFF;             //LED IO口设为输出
	 PORTA=0XFF;
	 PORTF&=0xF7;           //锁存数据关闭LED
	 
	 PORTA=0X00;
	 PORTF&=0XF8;           //锁存数据关闭数码管
	 
	 DDRB |=0X10;           //PB4设为输出
	 PORTB|=0X10;           //关闭PB4外接的LED
     
	 LCD_DATA_PORT=0xff;
	 LCD_DATA_POUT;          //LCD数据口设为输出
	
	 LCD_EN_1;
	 LCD_RW_1;
	 LCD_RS_1;
	 LCD_Control_IN;
}
