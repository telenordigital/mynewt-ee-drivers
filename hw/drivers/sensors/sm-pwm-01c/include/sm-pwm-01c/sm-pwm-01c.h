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

#ifndef _SM_PWM_01C_H_
#define _SM_PWM_01C_H_

#include <os/os.h>
#include "os/os_dev.h"
#include "sensor/sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sm_pwm_01c_cfg {
    // Sampletime (seconds)
    uint32_t sampleTime;
};

struct sm_pwm_01c {
    struct os_dev dev;
    struct sensor sensor;
    struct sm_pwm_01c_cfg cfg;
    os_time_t last_read_time;
};

int sm_pwm_01c_init(struct os_dev * dev, void * arg);

int sm_pwm_01c_config(struct sm_pwm_01c * dev, struct sm_pwm_01c_cfg * cfg);

#ifdef __cplusplus
}
#endif
#endif