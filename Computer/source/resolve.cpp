#include "stdafx.h"
#include "resolve.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

resolve::resolve(char *_source)
{
	memset(source, '\0', 60);
	memset(utc_time, '\0', 9);
	gps_lati = 0;
	gps_long = 0;
	gps_speed = 0;
	check_sum = 0;
	strcpy(source, _source);
}

bool resolve::process()
{
	unsigned char check_sum_do = 0;
	int now_p = 0;
	int l = strlen(source);
	int i, temp_i;
	char temp[20];
	char temp_min[10];
	for (i = 0; i < l - 1; i++)
	{
		check_sum_do ^= source[i];
	}
	if (source[0] == '$')
	{
		if (source[1] == 'O')
		{
			_is_gps_ready = true;
			now_p = 2;
			while (source[now_p] != ',' && now_p < l)
			{
				++now_p;
			}
			++now_p;

			//utcÊ±¼ä
			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->utc_time[0] = temp[0];
			this->utc_time[1] = temp[1];
			this->utc_time[2] = ':';
			this->utc_time[3] = temp[2];
			this->utc_time[4] = temp[3];
			this->utc_time[5] = ':';
			this->utc_time[6] = temp[4];
			this->utc_time[7] = temp[5];

			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->gps_lati += (temp[0] - 48) * 10;
			this->gps_lati += (temp[1] - 48);
			for (i = 2; i < strlen(temp); i++)
			{
				temp_min[i - 2] = temp[i];
			}
			this->gps_lati += (atof(temp_min) / 60.0);

			this->gps_ns = source[now_p];
			now_p += 2;

			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->gps_long += (temp[0] - 48) * 100;
			this->gps_long += (temp[1] - 48) * 10;
			this->gps_long += (temp[2] - 48);
			for (i = 3; i < strlen(temp); i++)
			{
				temp_min[i - 3] = temp[i];
			}
			this->gps_long += (atof(temp_min) / 60.0);

			this->gps_ew = source[now_p];
			now_p += 2;

			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->gps_speed = atof(temp);

			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->t = atoi(temp);

			memset(temp, '\0', 20);
			temp_i = 0;
			while (source[now_p] != ',' && now_p < l)
			{
				temp[temp_i] = source[now_p];
				++temp_i;
				++now_p;
			}
			++now_p;
			this->h = atoi(temp);

			this->check_sum = source[now_p];

			if (check_sum == check_sum_do) return true; else return false;
		}
		else
		{
			if (source[1] == 'N')
			{
				now_p = 3;
				while (source[now_p] == ',' && now_p < l) ++now_p;

				memset(temp, 20, '\0');
				temp_i = 0;
				while (source[now_p] != ',' && now_p < l)
				{
					temp[temp_i] = source[now_p];
					++temp_i;
					++now_p;
				}
				++now_p;
				this->t = atoi(temp);

				memset(temp, 20, '\0');
				temp_i = 0;
				while (source[now_p] != ',' && now_p < l)
				{
					temp[temp_i] = source[now_p];
					++temp_i;
					++now_p;
				}
				++now_p;
				this->h = atoi(temp);

				this->check_sum = source[now_p];

				_is_gps_ready = false;

				if (check_sum == check_sum_do) return true; else return false;
			}
			else
				return false;
		}
	}
	else
		return false;
}

bool resolve::is_gps_ready()
{
	return _is_gps_ready;
}
		