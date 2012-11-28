/*
 ============================================================================
 Name        : hello.c
 Author      : Navneet
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <GeoIP.h>
#include <GeoIPCity.h>

#ifndef GEOIP_CITY_DATA
#define GEOIP_CITY_DATA "/root/tmp/geoip-vmod/tmp/GeoIP_CITY_DB/GeoIPCitybr.dat"
#endif


int main(void) {
	 const char *country = NULL;
	 GeoIPRecord *record = NULL;
	    GeoIP *gi = NULL;
        char *ip="201.56.216.242";
	    gi =  GeoIP_open(GEOIP_CITY_DATA, GEOIP_MEMORY_CACHE);
	    if (gi) {
	      country = GeoIP_country_code_by_addr(gi,ip);
	      record = GeoIP_record_by_addr(gi,ip);
	    }
	puts(GeoIP_database_info(gi));
	printf("IP: %s country_code3: %s country_name: %s region: %s city: %s postal_code: %s latitude:%f longigute:%f ",ip,record->country_code3,record->country_name,record->region,record->city,record->postal_code,record->latitude,record->longitude);
	return EXIT_SUCCESS;
}
