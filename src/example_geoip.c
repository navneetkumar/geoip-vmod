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


int main(int argc, char *argv[] ) {
	 const char *country = NULL;
	 GeoIPRecord *record = NULL;
	    GeoIP *gi = NULL;
        //char *ip="201.56.216.242";
       //char *ip="67.27.68.34";
       // char *ip="14.140.107.130";
        char *ip=argv[1];
	puts(ip);
	    gi =  GeoIP_open(GEOIP_CITY_DATA, GEOIP_MEMORY_CACHE);
	    if (gi) {
	      record = GeoIP_record_by_addr(gi,ip);
	    }
        if(record && record->region) {  
	puts(GeoIP_database_info(gi));
	printf("IP: %s country_code3: %s country_name: %s region: %s city: %s postal_code: %s latitude:%f longigute:%f ",ip,record->country_code3,record->country_name,record->region,record->city,record->postal_code,record->latitude,record->longitude);
	}	
return EXIT_SUCCESS;
}
