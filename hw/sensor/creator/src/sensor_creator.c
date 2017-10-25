
#include "console/console.h"
#include "origin_gps/origin_gps.h"
#include "assert.h"

#if MYNEWT_VAL(UART_0)
  static const struct sensor_itf uart_0_itf = {
    .si_type = SENSOR_ITF_UART,
    .si_num = 0,
  };
#endif
 
#if MYNEWT_VAL(UART_1)
  static struct sensor_itf uart_1_itf = {
     .si_type = SENSOR_ITF_UART,
     .si_num = 1,
 };
 #endif

static struct origin_gps OriginGPS;
static struct origin_gps_cfg OriginGPSConfig;

void sensor_dev_create(void)
{
       console_printf("--- Sensor Creator ---\n");

#if MYNEWT_VAL(ORIGIN_GPS_OFB)
       console_printf("Origin GPS is present\n");

       int rc;
        rc = os_dev_create((struct os_dev *) &OriginGPS, 
            "origin_gps_0", 
            OS_DEV_INIT_PRIMARY, 
            0, 
            origin_gps_init, 
            (void *)&uart_0_itf);
        assert(rc == 0);

        rc = origin_gps_config(&OriginGPS, &OriginGPSConfig);
        assert(rc == 0);
#else
       console_printf("Origin GPS is NOT present\n");
#endif

#if MYNEWT_VAL(IAQ_CORE_OFB)
       console_printf("iAQ-Core is present\n");
#else
       console_printf("iAQ-Core is NOT present\n");
#endif

#if MYNEWT_VAL(CHIPCAP_2_OFB)
       console_printf("Chipcap 2 is present\n");
#else
       console_printf("Chipcap 2 is NOT present\n");
#endif

#if MYNEWT_VAL(SM_PWM_01C_OFB)
       console_printf("SM PWM 01C is present\n");
#else
       console_printf("SM PWM 01C is NOT present\n");
#endif
}