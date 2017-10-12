
#include "console/console.h"

void sensor_dev_create(void)
{
       console_printf("--- Sensor Creator ---\n");

#if MYNEWT_VAL(ORIGIN_GPS_OFB)
       console_printf("Origin GPS is present\n");
/*    rc = os_dev_create((struct os_dev *) &bno055, "bno055_0",
      OS_DEV_INIT_PRIMARY, 0, bno055_init, (void *)&i2c_0_itf_bno);
    assert(rc == 0);

    rc = config_bno055_sensor();
    assert(rc == 0);
    */
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