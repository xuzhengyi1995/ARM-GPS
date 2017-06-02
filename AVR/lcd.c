#include "lcd.h"
#include "delay.h"
void lcd_init(void)
{
    Delayms(15);
	LCD_DATA_POUT;     
    LCD_Control_OUT;
    LCD_write_onechar(0x38,0);
	Delayms(1);
    LCD_write_onechar(0x38,0);
	Delayms(1);
    LCD_write_onechar(0x38,0);
	Delayms(1);
    LCD_write_onechar(0x38,0);
    LCD_write_onechar(0x08,0);    /*显示关闭*/
    LCD_write_onechar(0x01,0);    /*显示清屏*/
	LCD_write_onechar(0x06,0);    /*显示光标移动设置*/
	Delayms(1);;  
    LCD_write_onechar(0x0C,0);    /*显示开及光标设置*/
}


void LCD_en_write(void)        
{
    LCD_EN_1;
    Delayus(300);  //E脉冲周期最小150ns
    LCD_EN_0;
}


void wait_LCD_Ready(void)
{
	uchar temp1;
    LCD_DATA_PORT=0XFF;
    LCD_DATA_PIN;                  //D7设为输入，准备判断LCD忙标志 
                                   //1为忙  0为空闲
	LCD_RS_0;
    LCD_RW_1;                      //读
	LCD_EN_1;
	Delayus(2);
    while((temp1=PINC & 0X80));
	LCD_EN_0;
    LCD_RS_1;
	LCD_DATA_POUT;
}


void LCD_write_onechar(uchar COMM,uchar DAT)
{ 
	 //wait_LCD_Ready();         //等待LCD空闲
	 LCD_RW_0;                 //写
	 
	 //写数据
	 if(COMM==0)
	 {
	    LCD_RS_1;  //RS高电平向LCD写数据
		LCD_DATA_PORT=DAT;
	 } 
	 //写命令
	 else
	 {
	    LCD_RS_0;
        LCD_DATA_PORT=COMM;
	 }
	 LCD_en_write(); 
	 Delayus(2);
	 LCD_RW_1;
	 LCD_RS_1;
}


void LCD_write_string(uchar X,uchar Y,uchar *string,unsigned int sum)
{
    set_LCD_xy( X, Y );                //设置LCD显示坐标
	unsigned int x=0;
    while (x<sum) 
    {
      LCD_write_onechar(0,*string );
	  string ++;                       //指向下一显示字符地址
	  x++;
    }
}


void set_LCD_xy(uchar x, uchar y )
{
    uchar DIS_address;
    if (y == 0) 
	   DIS_address = 0x80 + x;            //第一行X列
    else 
       DIS_address = 0xc0 + x;
    LCD_write_onechar( DIS_address, 0 );  //第二行X列
}

