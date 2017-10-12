#ifndef _ORIGIN_GPS_H_
#define _ORIGIN_GPS_H_

#include <os/os.h>
#include "os/os_dev.h"
#include "sensor/sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

struct origin_gps_cfg {
    int8_t GPS_UART_TX_PIN;
    int8_t GPS_UART_RX_PIN;
};

struct origin_gps {
    struct os_dev dev;
    struct sensor sensor;
    struct origin_gps_cfg cfg;
    os_time_t last_read_time;
};


int origin_gps_init(struct os_dev * dev, void * arg);

int origin_gps_config(struct origin_gps * dev, struct origin_gps_cfg * cfg);



#ifdef __cplusplus
}
#endif
#endif