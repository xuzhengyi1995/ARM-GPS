#include "gps.h"
void gps_init()
{
	USART0_Init();
}

unsigned char get_gps_info(unsigned char *gps_utc, unsigned char *gps_lati, unsigned char *gps_lati_ns, unsigned char *gps_long, unsigned char *gps_long_ew, unsigned char *gps_staus, unsigned char *gps_sat_sum, unsigned char *gps_speed)
{
	unsigned char r_temp;
	unsigned char flag = 0;
	unsigned char i = 0;
	unsigned int s=0,s_com=0;
	i = 0;
	flag = 0;
	while (flag == 0 && s<25)
	{
		++s;
		while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
		if(s_com>=1000) return 0; else s_com=0;
		r_temp = gps_receive();
		while (r_temp != '$')
		{
			while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
			if(s_com>=1000) return 0; else s_com=0;
			r_temp = gps_receive();

		}
		while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
		if(s_com>=1000) return 0; else s_com=0;
		r_temp = gps_receive();
		if (r_temp == 'G')
		{
			while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
			if(s_com>=1000) return 0; else s_com=0;
			r_temp = gps_receive();
			if (r_temp == 'P')
			{
				while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
				if(s_com>=1000) return 0; else s_com=0;
				r_temp = gps_receive();
				if (r_temp == 'G')
				{
					while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
					if(s_com>=1000) return 0; else s_com=0;
					r_temp = gps_receive();
					if (r_temp == 'G')
					{
						while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
						if(s_com>=1000) return 0; else s_com=0;
						r_temp = gps_receive();
						if (r_temp == 'A')
						{
							while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
							if(s_com>=1000) return 0; else s_com=0;
							r_temp = gps_receive();
							if (r_temp == ',')
							{
								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (r_temp != ',')
								{
									gps_utc[i] = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (r_temp != ',')
								{
									gps_lati[i] = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while ((r_temp != ',') && (i < 1))
								{
									*gps_lati_ns = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (r_temp != ',')
								{
									gps_long[i] = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while ((r_temp != ',') && (i < 1))
								{
									*gps_long_ew = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								{
									*gps_staus = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (r_temp != ',')
								{
									gps_sat_sum[i] = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}
								flag = 1;
							}
						}
					}
				}
			}
		}



		while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
		if(s_com>=1000) return 0; else s_com=0;
		r_temp = gps_receive();
		while (r_temp != '$')
		{
			while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
			if(s_com>=1000) return 0; else s_com=0;
			r_temp = gps_receive();

		}
		while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
		if(s_com>=1000) return 0; else s_com=0;
		r_temp = gps_receive();
		if (r_temp == 'G')
		{
			while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
			if(s_com>=1000) return 0; else s_com=0;
			r_temp = gps_receive();
			if (r_temp == 'P')
			{
				while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
				if(s_com>=1000) return 0; else s_com=0;
				r_temp = gps_receive();
				if (r_temp == 'V')
				{
					while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
					if(s_com>=1000) return 0; else s_com=0;
					r_temp = gps_receive();
					if (r_temp == 'T')
					{
						while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
						if(s_com>=1000) return 0; else s_com=0;
						r_temp = gps_receive();
						if (r_temp == 'G')
						{
							while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
							if(s_com>=1000) return 0; else s_com=0;
							r_temp = gps_receive();
							if (r_temp == ',')
							{
								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}

								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								while (r_temp != ',')
								{
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}
								while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
								if(s_com>=1000) return 0; else s_com=0;
								r_temp = gps_receive();
								i = 0;
								while (r_temp != ',')
								{
									gps_speed[i] = r_temp;
									++i;
									while (!(UCSR0A&(1 << RXC0)) && s_com<1000) {s_com++;delay_us(800);}
									if(s_com>=1000) return 0; else s_com=0;
									r_temp = gps_receive();
								}
								//flag = 1;
							}
						}
					}
				}
			}
		}
	}
	if (*gps_staus == '0' || s>=25)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
