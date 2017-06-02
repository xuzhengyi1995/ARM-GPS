#ifndef Include
#include <avr/io.h>
#include <macros.h>
#define Include
#endif
#include "com.h"
#include "delay.h"
void gps_init();
//unsigned char gps_utc[10],gps_lati[11],gps_lati_ns,gps_long[12],gps_long_ew,gps_staus,gps_sat_sum[3],gps_speed[7];
unsigned char get_gps_info(unsigned char *gps_utc, unsigned char *gps_lati, unsigned char *gps_lati_ns, unsigned char *gps_long, unsigned char *gps_long_ew, unsigned char *gps_staus, unsigned char *gps_sat_sum, unsigned char *gps_speed);
