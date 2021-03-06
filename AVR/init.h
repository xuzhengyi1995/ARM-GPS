#ifndef Include
#include <avr/io.h>
#include <macros.h>
#define  LCD_DATA_PORT    PORTA        //定义LCD的D0-D7所在端口
#define  LCD_DATA_POUT    DDRA=0xFF    //定义LCD数据端口为输出
#define  LCD_DATA_PIN     DDRA=0x00    //定义LCD数据端口为输入(在读LCD状态时用到)

#define  LCD_Control_PORT PORTB        //定义LCD的EN RW RS所在端口方便后面操作
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
