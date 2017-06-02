#include "th.h"

unsigned char get_th(unsigned char *DHT_value)
{
	DATA_IN;
	DATA_SET;
	delay_us(10);
	DHT_read(DHT_value);
}

unsigned char DHT_byte(unsigned char *p)
{
	unsigned char j, time_flag, DHT_byte_value = 0, temp;
	for (j = 0; j < 8; j++)
	{
		time_flag = 2;
		while ((!(DATA_READ)) && time_flag++); 
		if (time_flag == 1) 
		{
			*p = 0x01;
			break;
		}
		delay_us(40);
		temp = 0;
		if (DATA_READ)temp = 1; 
		time_flag = 2;
		while ((DATA_READ) && time_flag++); 
		if (time_flag == 1) 
		{
			*p = 0x01;
			break;
		}
		DHT_byte_value <<= 1;
		DHT_byte_value |= temp;
	}
	return DHT_byte_value;
}

void DHT_read(unsigned char *p)
{
	unsigned char i, time_flag, DHT_v_temp[5], temp1 = 0;
	DATA_OUT;
	DATA_CLR;
	delay_ms(18);
	DATA_IN;
	DATA_SET;
	delay_us(40);
	if (DATA_READ) time_flag = 1;
	while (!(DATA_READ))
	{
		time_flag = 2;
		while ((!(DATA_READ)) && time_flag++);
		if (time_flag == 1) break;
		time_flag = 2;
		while ((DATA_READ) && time_flag++);
		if (time_flag == 1) break;
		for (i = 0; i < 5; i++)
		{
			DHT_v_temp[i] = DHT_byte(&time_flag); //读取数据;
			if (time_flag == 1)break;
			if (i < 4) temp1 += DHT_v_temp[i]; //校验和
		}
	}
	DATA_IN;
	DATA_SET;
	if (temp1 == DHT_v_temp[4])
	{
		for (i = 0; i < 5; i++)
		{
			*(p + i) = DHT_v_temp[i];
		}
	}
}

