/*
**   Copyright 2016 Telenor Digital AS
**
**  Licensed under the Apache License, Version 2.0 (the "License");
**  you may not use this file except in compliance with the License.
**  You may obtain a copy of the License at
**
**      http://www.apache.org/licenses/LICENSE-2.0
**
**  Unless required by applicable law or agreed to in writing, software
**  distributed under the License is distributed on an "AS IS" BASIS,
**  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**  See the License for the specific language governing permissions and
**  limitations under the License.
*/

#include <string.h>
#include "origin_gps/origin_gps.h"
#include "hal/hal_uart.h"

#include "console/console.h"
#include "origin_gps/nmealib.h"
#include "origin_gps/gps_std.h"
#include "origin_gps/gps_cache.h"



#define MAX_NMEA_BUFFER 254

static uint8_t nmea_buffer[MAX_NMEA_BUFFER];
static uint8_t nmea_pos = 0;


static int rxData(void *arg, uint8_t data)
{
    console_printf("%c", data);
    nmea_buffer[nmea_pos++] = data;
    if (nmea_pos >= MAX_NMEA_BUFFER) {
        nmea_pos = 0;
        return -1;
    }

     if (data == '\n') {
            nmea_buffer[nmea_pos] = 0;
            nmea_sentence_t sentence;
            if (nmea_parse(nmea_buffer, &sentence)) {
                if (sentence.type[0] == 'G' && sentence.type[2] == 'A') {
                    if (sentence.type[1] == 'G') {
                        // a very convoluted way of saying 'GGA'
                        gps_gga_t gga;
                        nmea_decode_gga(&sentence, &gga);
                        gps_update_gga(&gga);
                    }
                    else if (sentence.type[1] == 'S') {
                        // a very convoluted way of saying 'GSA'
                        gps_gsa_t gsa;
                        nmea_decode_gsa(&sentence, &gsa);
                        gps_update_gsa(&gsa);
                    }
                }
            }
            nmea_pos = 0;
            memset(nmea_buffer, 0, MAX_NMEA_BUFFER);
        }
    return 0;
}

int origin_gps_init(struct os_dev * dev, void * arg)
{

    console_printf("--- Origin GPS init ---\n");

    int rc;
    // Parametriser UART #
    rc = hal_uart_init_cbs(0, NULL, NULL, rxData, NULL);
    if (rc) {
        return rc;
    }

    rc = hal_uart_config(0, 9600, 8, 1, HAL_UART_PARITY_NONE, HAL_UART_FLOW_CTL_NONE);
    if (rc) {
        return rc;
    }

    return 0;
}

int origin_gps_config(struct origin_gps * dev, struct origin_gps_cfg * cfg)
{
    console_printf("  Origin GPS Config\n");
/*
    int rc;
    uint8_t id;
    uint8_t mode;
    struct sensor_itf *itf;

    itf = SENSOR_GET_ITF(&(dev->sensor));
  */  
    return 0;    
}

