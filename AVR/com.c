#include "com.h"
//if(UCSR0A&(1<<RXC0))   //������ջ�����������
//tmp=&_Receive();  //��������
//&_Transmit(tmp);  //��������


void USART1_Init( void )
{
     unsigned int tmp;     
     UBRR1L=51;                        /* ���ò�����*/    
     UCSR1B = (1<<RXEN1)|(1<<TXEN1);   /* �������뷢����ʹ��*/   
     UCSR1C = (1<<UCSZ10)|(1<<UCSZ11); /* ����֡��ʽ: 8 ������λ, 1��ֹͣλ*/
}


void computer_transmit( unsigned char data )
{
     /* �ȴ����ͻ�����Ϊ�� */
     while ( !( UCSR1A & (1<<UDRE1)) );
     /* �����ݷ��뻺�������������� */
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
     /* �ȴ���������*/
     while ( !(UCSR1A & (1<<RXC1)) );
     /* �ӻ������л�ȡ����������*/
     return UDR1;
} 


void USART0_Init( void )
{
     unsigned int tmp;     
     UBRR0L=51;                        /* ���ò�����*/    
     UCSR0B = (1<<RXEN0)|(1<<TXEN0);   /* �������뷢����ʹ��*/   
     UCSR0C = (1<<UCSZ00)|(1<<UCSZ01); /* ����֡��ʽ: 8 ������λ, 1��ֹͣλ*/
}


void gps_transmit( unsigned char data )
{
     /* �ȴ����ͻ�����Ϊ�� */
     while ( !( UCSR0A & (1<<UDRE0)) );
     /* �����ݷ��뻺�������������� */
     UDR0 = data;
} 


unsigned char gps_receive( void )
{
     /* �ȴ���������*/
     while ( !(UCSR0A & (1<<RXC0)) );
     /* �ӻ������л�ȡ����������*/
     return UDR0;
} 
