#include "com.h"
//if(UCSR0A&(1<<RXC0))   //如果接收缓存区有数据
//tmp=&_Receive();  //接收数据
//&_Transmit(tmp);  //发送数据


void USART1_Init( void )
{
     unsigned int tmp;     
     UBRR1L=51;                        /* 设置波特率*/    
     UCSR1B = (1<<RXEN1)|(1<<TXEN1);   /* 接收器与发送器使能*/   
     UCSR1C = (1<<UCSZ10)|(1<<UCSZ11); /* 设置帧格式: 8 个数据位, 1个停止位*/
}


void computer_transmit( unsigned char data )
{
     /* 等待发送缓冲器为空 */
     while ( !( UCSR1A & (1<<UDRE1)) );
     /* 将数据放入缓冲器，发送数据 */
     UDR1 = data;
} 

void computer_transmit_string(unsigned char *data,unsigned int sum)
{
	unsigned int i;
	for(i=0;i<sum;i++)
	{
		computer_transmit(data[i]);
	}
}


unsigned char computer_receive( void )
{
     /* 等待接收数据*/
     while ( !(UCSR1A & (1<<RXC1)) );
     /* 从缓冲器中获取并返回数据*/
     return UDR1;
} 


void USART0_Init( void )
{
     unsigned int tmp;     
     UBRR0L=51;                        /* 设置波特率*/    
     UCSR0B = (1<<RXEN0)|(1<<TXEN0);   /* 接收器与发送器使能*/   
     UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); /* 设置帧格式: 8 个数据位, 1个停止位*/
}


void gps_transmit( unsigned char data )
{
     /* 等待发送缓冲器为空 */
     while ( !( UCSR0A & (1<<UDRE0)) );
     /* 将数据放入缓冲器，发送数据 */
     UDR0 = data;
} 


unsigned char gps_receive( void )
{
     /* 等待接收数据*/
     while ( !(UCSR0A & (1<<RXC0)) );
     /* 从缓冲器中获取并返回数据*/
     return UDR0;
} 
