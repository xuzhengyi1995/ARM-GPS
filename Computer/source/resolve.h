#pragma once

class resolve
{
public:
	resolve(char *_source);
	bool process();
	bool is_gps_ready();
//private:
	char source[60];
	unsigned char utc_time[9];//utc ʱ��
	unsigned char check_sum;//xorУ���
	int t, h;//t�¶ȣ�h�ʶ�
	unsigned char gps_ns, gps_ew;//�ϱ�������
	double gps_lati, gps_long, gps_speed;//γ�ȣ����ȣ��ٶ�
	bool _is_gps_ready;
};
