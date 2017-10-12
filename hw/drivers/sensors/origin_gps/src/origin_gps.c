#include "origin_gps/origin_gps.h"

#include "console/console.h"

int origin_gps_init(struct os_dev * dev, void * arg)
{

    console_printf("--- Origin GPS init ---\n");
    return 1;
}

int origin_gps_config(struct origin_gps * dev, struct origin_gps_cfg * cfg)
{
    return 1;    
}