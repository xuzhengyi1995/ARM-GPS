#pragma once

class resolve
{
public:
	resolve(char *_source);
	bool process();
	bool is_gps_ready();
//private:
	char source[60];
	unsigned char utc_time[9];//utc 时间
	unsigned char check_sum;//xor校验和
	int t, h;//t温度，h适度
	unsigned char gps_ns, gps_ew;//南北，东西
	double gps_lati, gps_long, gps_speed;//纬度，经度，速度
	bool _is_gps_ready;
};
