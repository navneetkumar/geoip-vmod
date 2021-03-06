/**/
#include <stdlib.h>
#include <GeoIP.h>
#include <GeoIPCity.h>
#include <string.h>

#include "vrt.h"
#include "bin/varnishd/cache.h"
#include "include/vct.h"
#include "vcc_if.h"

static const char *unknown= "Unknown";

char* trimwhitespace(char *str)
{
  char *end;
  while(isspace(*str)) str++;

  if(*str == 0) 
    return str;

  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;
  *(end+1) = 0;

  return str;
}

char* ip_at_index(char* ips, unsigned int index) {
        char **tokens = (char**)malloc(index * sizeof(char));
        unsigned int i = 0;
        for( tokens[i] = strtok_r( ips, ",", &ips); ++i <= index;
                        tokens[i] = strtok_r( NULL, ",", &ips ) ) {
        }
	char *result = strdup(tokens[index]);
	free(tokens);
        return trimwhitespace(result);
}

typedef struct geoIpConfig {
	char *db_path;
} config_t;

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
    return (0);
}

static config_t *
make_config(const char *db_path)
{
	config_t *cfg;

	cfg = malloc(sizeof(config_t));
	if(cfg == NULL)
		return NULL;

	cfg->db_path = strdup(db_path);
	return cfg;
}
 
void
vmod_init_database(struct sess *sp, struct vmod_priv *priv, const char *db_path)
{
	config_t *old_cfg = priv->priv;

	priv->priv = make_config(db_path);
	if(priv->priv && old_cfg) {
		free(old_cfg->db_path);
		free(old_cfg);
	}
}

const char *
vmod_country(struct sess *sp, const char *ip)
{
    const char *country = NULL;
    char *cp;
    GeoIP *gi = NULL;

    gi = GeoIP_new(GEOIP_STANDARD);
    if (gi) {
      country = GeoIP_country_code_by_addr(gi, ip);
    }
    if (!country) {
      country= unknown;
    }
    cp= WS_Dup(sp->wrk->ws, country);

    if (gi) {
      GeoIP_delete(gi);
    }
    return(cp);
}

const char *
vmod_record(struct sess *sp, struct vmod_priv *priv, const char *xforwarded_for, int index)
{
        char *formattedRecord [500];
        char *cp;
        char *region = NULL;
	GeoIPRecord *record = NULL;
	GeoIP *gi = NULL;
        config_t *cfg = priv->priv;
	char *ip = ip_at_index(xforwarded_for, index);

	gi =  GeoIP_open(cfg->db_path, GEOIP_MEMORY_CACHE);
	if (gi) {
		record = GeoIP_record_by_addr(gi,ip);
	}

	if (record && record->region) {
		sprintf(formattedRecord, "ip: %s, country_code: %s, region: %s, city: %s", ip ,record->country_code, record->region, record->city);
		GeoIPRecord_delete(record);
	} else {
		sprintf(formattedRecord, "ip: %s, country_code: unknown, region: unknown, city: unknown",ip);
	} 

	cp= WS_Dup(sp->wrk->ws, formattedRecord);
	GeoIP_delete(gi);

	return(cp);
}
