#include "init.h"
#include "lcd.h"
#include "delay.h"
#include "com.h"
#include "th.h";
#include "gps.h"
#include<string.h>;
#define F_CPU 8000000UL
//lcd_init():!!!!!!clear the lcd
//LCD_write_string(x,y,unsigned char *text,uint):!!!!!!write character at y(0~1) x(0~15)
//Delayms(usigned int t):!!!!!!delay ms
//Delayus(unsigned int t):!!!!!!delay us
//Delay_10us(void)!!!!!!
//mcu_io_init():!!!!!init
//gps_transmit( unsigned char data );
//unsigned char gps_receive( void );
//computer_transmit( unsigned char data );
//unsigned char computer_receive( void );
//get_th(DHT_value):read t&h in DHT_value[5];
//void computer_transmit_string(unsigned char *data,unsigned int sum)

unsigned char DHT_value[5];
unsigned char digit[]={48,49,50,51,52,53,54,55,56,57};
unsigned char gps_utc[10],gps_lati[11],gps_lati_ns,gps_long[12],gps_long_ew,gps_staus,gps_sat_sum[3],gps_speed[7];


int main()
{
	mcu_io_init();
	lcd_init();
	delay_ms(1000);
	LCD_write_string(0,0,"Starting...",11);
	delay_ms(5000);
	lcd_init();
	USART0_Init();
	USART1_Init();

	DDRG &= ~(1 << PG0);
	DDRE |= (1 << PE7);			
	
	unsigned char r_computer=0,check_sum=0,send_computer[60];
	unsigned char gps_back=0;
	unsigned char gps_staus_disp[18],connect_staus_disp[18]="  Disconnected.  ";
	unsigned char disp_kawaru=0;
	unsigned char i,flag_pc=0;
	//unsigned char t_disp[3]={'\0','\0','\0'},h_disp[3]={'\0','\0','\0'};
	unsigned char gps_temp[2]={'\0','\0'};
	
	unsigned char hito=0; 
	unsigned char delay_gps=0;

	while (1)
	{
		memset(gps_staus_disp,18,'\0');
		memset(connect_staus_disp,18,'\0');
		memset(send_computer,60,'\0');

		//!!!!!!!!!!!!!!!!!!!!!!!!!!hito!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		if((PING & 0x01) == 0x00)
		{
			PORTE &= ~(1 << PE7);
			hito=0;
		}
		else
		{
			PORTE |= (1 << PE7);
			hito=1;
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!end hito!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		//get_th(DHT_value);

		//t_disp[0]=digit[DHT_value[2]/10];
		//t_disp[1]=digit[DHT_value[2]%10];

		//h_disp[0]=digit[DHT_value[0]/10];
		//h_disp[1]=digit[DHT_value[0]%10];

		memset(gps_utc,10,'\0');
		memset(gps_lati,11,'\0');
		memset(gps_long,12,'\0');
		memset(gps_sat_sum,3,'\0');
		memset(gps_speed,7,'\0');
		delay_ms(100);
		gps_back=get_gps_info(gps_utc,gps_lati,&gps_lati_ns,gps_long,&gps_long_ew,&gps_staus,gps_sat_sum,gps_speed);

		if (delay_gps == 0)
		{

			if (gps_back == 0)
			{
				strcpy(gps_staus_disp, "GPS is not ready!");
			}
			else
			{
				strcpy(gps_staus_disp, "GPS OK!Speed:");//13
				if (gps_speed[0] < '2')
				{
					strcat(gps_staus_disp, "0.00");
				}
				else
				{
					gps_staus_disp[13] = gps_speed[0];
					gps_staus_disp[14] = gps_speed[1];
					gps_staus_disp[15] = gps_speed[2];
					gps_staus_disp[16] = gps_speed[3];
				}
			}
			if (disp_kawaru < 3)
			{

				lcd_init();
				LCD_write_string(0, 0, gps_staus_disp, 17);

				if (hito == 0)
				{
					LCD_write_string(0, 1, "    Normal...   ", 16);
				}
				else
				{
					LCD_write_string(0, 1, "    Warning!    ", 16);
				}


				/*LCD_write_string(0,1,"  T:",4);
				LCD_write_string(4,1,t_disp,2);
				LCD_write_string(6,5,"C  H:",5);
				LCD_write_string(11,1,h_disp,2);
				LCD_write_string(13,15,"%  ",3);*/
			}
			else
			{
				LCD_write_string(0, 0, connect_staus_disp, 17);

				LCD_write_string(0, 1, "  Time:", 7);
				if (gps_back == 0)
				{
					LCD_write_string(7, 1, "0", 1);
					LCD_write_string(8, 1, "0", 1);
					LCD_write_string(9, 1, ":", 1);

					LCD_write_string(10, 1, "0", 1);
					LCD_write_string(11, 1, "0", 1);

					LCD_write_string(12, 1, ":", 1);

					LCD_write_string(13, 1, "0", 1);
					LCD_write_string(14, 1, "0", 1);

					LCD_write_string(15, 1, "  ", 2);
				}
				else
				{
					LCD_write_string(7, 1, &gps_utc[0], 1);
					LCD_write_string(8, 1, &gps_utc[1], 1);
					LCD_write_string(9, 1, ":", 1);

					LCD_write_string(10, 1, &gps_utc[2], 1);
					LCD_write_string(11, 1, &gps_utc[3], 1);

					LCD_write_string(12, 1, ":", 1);

					LCD_write_string(13, 1, &gps_utc[4], 1);
					LCD_write_string(14, 1, &gps_utc[5], 1);

					LCD_write_string(15, 1, "  ", 2);
				}
			}
			if (disp_kawaru > 7)
			{
				disp_kawaru = 0;
				if (flag_pc == 0) strcpy(connect_staus_disp, "  Disconnected.  ");
			}
			++disp_kawaru;
		}

		if(UCSR1A&(1 << RXC1)) r_computer = computer_receive();

		if(r_computer=='G')
		{
			flag_pc=1;
			r_computer=0;
			strcpy(connect_staus_disp," Connected to PC ");
			if(gps_back!=0)
			{
				strcpy(send_computer,"$OK,");
				strcat(send_computer,gps_utc);
				strcat(send_computer,",");
				strcat(send_computer,gps_lati);
				strcat(send_computer,",");
				gps_temp[0]=gps_lati_ns;
				strcat(send_computer,gps_temp);
				strcat(send_computer,",");
				strcat(send_computer,gps_long);
				strcat(send_computer,",");
				gps_temp[0]=gps_long_ew;
				strcat(send_computer,gps_temp);
				strcat(send_computer,",");
				strcat(send_computer,gps_speed);
				strcat(send_computer,",");
				if(hito==0)
				{
					strcat(send_computer,"A-");
				}
				else
				{
					strcat(send_computer,"A!");
				}
				strcat(send_computer,",");
				for(i=0;i<strlen(send_computer);i++)
					check_sum^=send_computer[i];
			}
			else
			{
				strcpy(send_computer,"$NO,");
				strcat(send_computer,",");
				strcat(send_computer,",");
				strcat(send_computer,",");
				strcat(send_computer,",");
				strcat(send_computer,",");
				strcat(send_computer,",");
				if(hito==0)
				{
					strcat(send_computer,"A-");
				}
				else
				{
					strcat(send_computer,"A!");
				}
				strcat(send_computer,",");
				for(i=0;i<strlen(send_computer);i++)
					check_sum^=send_computer[i];
			}
			computer_transmit_string(send_computer,strlen(send_computer));
			delay_ms(10);
			computer_transmit(check_sum);
			check_sum=0;
			delay_ms(100);
		}
		else
		{
			flag_pc=0;
		}
		
		delay_ms(500);
		if(delay_gps>=5)
		{
			delay_gps=0;
		}
		else
		{
			++delay_gps;
		}

		//delay_ms(1000);
	}
}
