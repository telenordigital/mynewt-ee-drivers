#ifndef _SM_PWM_01C_H_
#define _SM_PWM_01C_H_

#include <os/os.h>
#include "os/os_dev.h"

#ifdef __cplusplus
extern "C" {
#endif

struct bno055_cfg {
    // Sampletime (seconds)
    uint32_t sampleTime;
};

struct sm_pwm_01c {
    struct os_dev dev;
    struct sensor sensor;
    struct sm_pwm_01c_cfg cfg;
    os_time_t last_read_time;
};

int sm_pwm_01c_init(struct os_dev *dev, void *arg);

int sm_pwm_01c_config(struct sm_pwm_01c *, struct bno055_cfg *);

#ifdef __cplusplus
}
#endif
#endif