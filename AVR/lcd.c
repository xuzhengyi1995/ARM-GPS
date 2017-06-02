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
    LCD_write_onechar(0x08,0);    /*��ʾ�ر�*/
    LCD_write_onechar(0x01,0);    /*��ʾ����*/
	LCD_write_onechar(0x06,0);    /*��ʾ����ƶ�����*/
	Delayms(1);;  
    LCD_write_onechar(0x0C,0);    /*��ʾ�����������*/
}


void LCD_en_write(void)        
{
    LCD_EN_1;
    Delayus(300);  //E����������С150ns
    LCD_EN_0;
}


void wait_LCD_Ready(void)
{
	uchar temp1;
    LCD_DATA_PORT=0XFF;
    LCD_DATA_PIN;                  //D7��Ϊ���룬׼���ж�LCDæ��־ 
                                   //1Ϊæ  0Ϊ����
	LCD_RS_0;
    LCD_RW_1;                      //��
	LCD_EN_1;
	Delayus(2);
    while((temp1=PINC & 0X80));
	LCD_EN_0;
    LCD_RS_1;
	LCD_DATA_POUT;
}


void LCD_write_onechar(uchar COMM,uchar DAT)
{ 
	 //wait_LCD_Ready();         //�ȴ�LCD����
	 LCD_RW_0;                 //д
	 
	 //д����
	 if(COMM==0)
	 {
	    LCD_RS_1;  //RS�ߵ�ƽ��LCDд����
		LCD_DATA_PORT=DAT;
	 } 
	 //д����
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
    set_LCD_xy( X, Y );                //����LCD��ʾ����
	unsigned int x=0;
    while (x<sum) 
    {
      LCD_write_onechar(0,*string );
	  string ++;                       //ָ����һ��ʾ�ַ���ַ
	  x++;
    }
}


void set_LCD_xy(uchar x, uchar y )
{
    uchar DIS_address;
    if (y == 0) 
	   DIS_address = 0x80 + x;            //��һ��X��
    else 
       DIS_address = 0xc0 + x;
    LCD_write_onechar( DIS_address, 0 );  //�ڶ���X��
}

